#include "stdafx.h"
#include "JpegDecoder.h"

#pragma warning ( disable : 4996)

#define SOI 0xD8
#define EOI 0xD9
#define APP0 0xE0
#define SOF 0xC0
#define DQT 0xDB
#define DHT 0xC4
#define SOS 0xDA
#define DRI 0xDD
#define COM 0xFE


#define BYTE_p(i) bp=buf[(i)++]
#define WORD_p(i) wp=(((WORD)(buf[(i)]))<<8) + buf[(i)+1]; (i)+=2

#define RIGHT_SHIFT(x,shft)  \
	((shift_temp = (x)) < 0 ? \
	(shift_temp >> (shft)) | ((~(0L)) << (32-(shft))) : \
	(shift_temp >> (shft)))
#define DESCALE(x,n)  RIGHT_SHIFT((x) + (1L << ((n)-1)), n)
#define RANGE_MASK 1023L

typedef void (JpegDecoder::*decode_MCU_func)(DWORD);

// DCT parameter mattrix 
static BYTE zigzag[64] = { 0, 1, 5, 6,14,15,27,28,
2, 4, 7,13,16,26,29,42,
3, 8,12,17,25,30,41,43,
9,11,18,24,31,40,44,53,
10,19,23,32,39,45,52,54,
20,22,33,38,46,51,55,60,
21,34,37,47,50,56,59,61,
35,36,48,49,57,58,62,63 };

// sword code array
static SWORD neg_pow2[17] = { 0,-1,-3,-7,-15,-31,-63,-127,-255,-511,-1023,-2047,-4095,-8191,-16383,-32767 };

static DWORD start_neg_pow2 = (DWORD)neg_pow2;

//real value when decoding
static DWORD wordval;

#define exit_func(err) { strcpy(error_string, err); return 0;}

#ifdef _MSC_VER
WORD lookKbits(BYTE k)
{
	_asm {
		mov dl, k
		mov cl, 16
		sub cl, dl
		mov eax, [wordval]
		shr eax, cl
	}
}
WORD WORD_hi_lo(BYTE byte_high, BYTE byte_low)
{
	_asm {
		mov ah, byte_high
		mov al, byte_low
	}
}
SWORD get_svalue(BYTE k)
{
	_asm {
		xor ecx, ecx
		mov cl, k
		mov eax, [wordval]
		shl eax, cl
		shr eax, 16
		dec cl
		bt eax, ecx
		jc end_macro
		signed_value : inc cl
					   mov ebx, [start_neg_pow2]
					   add ax, word ptr[ebx + ecx * 2]
					   end_macro :
	}
}
#endif

#ifdef __WATCOMC__

WORD lookKbits(BYTE k);
#pragma aux lookKbits=\
	"mov eax,[wordval]"\
	"mov cl, 16"\
	"sub cl, dl"\
	"shr eax, cl"\
	parm [dl] \
	value [ax] \
	modify [eax cl];
WORD WORD_hi_lo(BYTE byte_high, BYTE BYTE_low);
#pragma aux WORD_hi_lo=\
	parm [ah] [al]\
	value [ax] \
	modify [ax];

SWORD get_svalue(BYTE k);
#pragma aux get_svalue=\
	"xor ecx, ecx"\
	"mov cl, al"\
	"mov eax,[wordval]"\
	"shl eax, cl"\
	"shr eax, 16"\
	"dec cl"\
	"bt eax,ecx"\
	"jc end_macro"\
	"signed_value:inc cl"\
	"mov ebx,[start_neg_pow2]"\
	"add ax,word ptr [ebx+ecx*2]"\
	"end_macro:"\
	parm [al]\
	modify [eax ebx ecx]\
	value [ax];
#endif

JpegDecoder::JpegDecoder(FILE* f)
{
	d_k = 0;
	LoadJPEGHeader(f);
	DecodeJPEGImage();
}

JpegDecoder::~JpegDecoder(void)
{
	free(buf);
	free(tempTable);
	for (int i = 0; i <= 3; i++)free(QT[i]);
}
/***************************************************************************
* Load JPEG Header
**************************************************************************/
bool JpegDecoder::LoadJPEGHeader(FILE* fp)
{
	DWORD length_of_file;
	BYTE vers, units;
	WORD Xdensity, Ydensity, Xthumbnail, Ythumbnail;
	WORD length;
	float *qtable;
	DWORD old_byte_pos;
	Huffman_table *htable;
	long j;
	BYTE precision, comp_id, nr_components;
	BYTE QT_info, HT_info;
	BYTE SOS_found, SOF_found;
	//read JPEG file and allocate memory
	length_of_file = GetFileSize(fp);
	buf = (BYTE *)malloc(length_of_file + 4);
	if (buf == NULL) exit_func("Not enough memory for loading file");
	fread(buf, length_of_file, 1, fp);
	//Check whether it is a valid file
	if ((buf[0] != 0xFF) || (buf[1] != SOI)) exit_func("Not a JPG file ?\n");
	if ((buf[2] != 0xFF) || (buf[3] != APP0)) exit_func("Invalid JPG file.");
	if ((buf[6] != 'J') || (buf[7] != 'F') || (buf[8] != 'I') || (buf[9] != 'F') ||
		(buf[10] != 0)) exit_func("Invalid JPG file.");
	//Initial�
	InitJPGDecoding();
	byte_pos = 11;
	//Get the JPEG version
	BYTE_p(byte_pos); vers = bp;
	if (vers != 1) exit_func("JFIF version not supported");
	BYTE_p(byte_pos);
	BYTE_p(byte_pos);  units = bp;
	WORD_p(byte_pos); Xdensity = wp; WORD_p(byte_pos); Ydensity = wp;

	BYTE_p(byte_pos); Xthumbnail = bp; BYTE_p(byte_pos); Ythumbnail = bp;
	if ((Xthumbnail != 0) || (Ythumbnail != 0))
		exit_func(" Cannot process JFIF thumbnailed files\n");
	//Decode, look for scan begining line 
	SOS_found = 0; SOF_found = 0; Restart_markers = 0;
	while ((byte_pos<length_of_file) && !SOS_found)
	{
		BYTE_p(byte_pos);
		if (bp != 0xFF) continue;
		// get the mark
		BYTE_p(byte_pos);
		switch (bp)
		{
		case DQT: WORD_p(byte_pos); length = wp;
			for (j = 0; j<wp - 2;)
			{
				old_byte_pos = byte_pos;
				BYTE_p(byte_pos); QT_info = bp;
				if ((QT_info >> 4) != 0)
					exit_func("16 bit quantization table not supported");
				qtable = QT[QT_info & 0xF];
				LoadQuantTable(qtable);//load the quant table
				j += byte_pos - old_byte_pos;
			}break;
		case DHT: WORD_p(byte_pos); length = wp;
			for (j = 0; j<wp - 2;)
			{
				old_byte_pos = byte_pos;
				BYTE_p(byte_pos); HT_info = bp;
				if ((HT_info & 0x10) != 0) htable = &HTAC[HT_info & 0xF];
				else htable = &HTDC[HT_info & 0xF];
				LoadHuffmanTable(htable);//load the Huffman table
				j += byte_pos - old_byte_pos;
			}break;
		case COM: WORD_p(byte_pos); length = wp;
			byte_pos += wp - 2;
			break;
		case DRI: Restart_markers = 1;
			WORD_p(byte_pos); length = wp;
			WORD_p(byte_pos);  MCU_restart = wp;
			if (MCU_restart == 0) Restart_markers = 0;
			break;
		case SOF: WORD_p(byte_pos); length = wp;
			BYTE_p(byte_pos); precision = bp;
			if (precision != 8) exit_func("Only 8 bit precision supported");
			WORD_p(byte_pos); height = wp; WORD_p(byte_pos); width = wp;
			BYTE_p(byte_pos); nr_components = bp;
			if (nr_components != 3) exit_func("Only truecolor JPGS supported");
			for (j = 1; j <= 3; j++)
			{
				BYTE_p(byte_pos); comp_id = bp;
				if ((comp_id == 0) || (comp_id>3)) exit_func("Only YCbCr format supported");
				switch (comp_id)
				{
				case 1: // Y
					BYTE_p(byte_pos); YH = bp >> 4; YV = bp & 0xF;
					BYTE_p(byte_pos); YQ_nr = bp;
					break;
				case 2: // Cb
					BYTE_p(byte_pos); CbH = bp >> 4; CbV = bp & 0xF;
					BYTE_p(byte_pos); CbQ_nr = bp;
					break;
				case 3: // Cr
					BYTE_p(byte_pos); CrH = bp >> 4; CrV = bp & 0xF;
					BYTE_p(byte_pos); CrQ_nr = bp;
					break;
				}
			}
			SOF_found = 1; break;
		case SOS: WORD_p(byte_pos); length = wp;
			BYTE_p(byte_pos); nr_components = bp;
			if (nr_components != 3) exit_func("Invalid SOS marker");
			for (j = 1; j <= 3; j++)
			{
				BYTE_p(byte_pos); comp_id = bp;
				if ((comp_id == 0) || (comp_id>3)) exit_func("Only YCbCr supported");
				switch (comp_id)
				{
				case 1: // Y
					BYTE_p(byte_pos); YDC_nr = bp >> 4; YAC_nr = bp & 0xF;
					break;
				case 2: // Cb
					BYTE_p(byte_pos); CbDC_nr = bp >> 4; CbAC_nr = bp & 0xF;
					break;
				case 3: // Cr
					BYTE_p(byte_pos); CrDC_nr = bp >> 4; CrAC_nr = bp & 0xF;
					break;
				}
			}
			BYTE_p(byte_pos); BYTE_p(byte_pos); BYTE_p(byte_pos);
			SOS_found = 1;
			break;

		case 0xFF:
			break;

		default:  WORD_p(byte_pos); length = wp;
			byte_pos += wp - 2;
			break;
		}
	}
	//if it is invalid file, then error message
	if (!SOS_found) exit_func("Invalid JPG file. No SOS marker found.");
	if (!SOF_found) exit_func("Progressive JPEGs not supported");
	if ((CbH>YH) || (CrH>YH)) exit_func("Vertical sampling factor for Y should be >= sampling factor for Cb,Cr");
	if ((CbV>YV) || (CrV>YV)) exit_func("Horizontal sampling factor for Y should be >= sampling factor for Cb,Cr");
	if ((CbH >= 2) || (CbV >= 2)) exit_func("Cb sampling factors should be = 1");
	if ((CrV >= 2) || (CrV >= 2)) exit_func("Cr sampling factors should be = 1");

	Hmax = YH, Vmax = YV;
	if (width % (Hmax * 8) == 0) X_round = width; // X_round = Multiple of Hmax*8
	else X_round = (width / (Hmax * 8) + 1)*(Hmax * 8);
	if (height % (Vmax * 8) == 0) Y_round = height; // Y_round = Multiple of Vmax*8
	else Y_round = (height / (Vmax * 8) + 1)*(Vmax * 8);
	//check the file is valid , then acllocate the memory
	im_buffer = (BYTE *)malloc(X_round*Y_round * 4);
	return true;
}
/***************************************************************************
*  allocate memory for sample_range_limit
**************************************************************************/
void JpegDecoder::PrepareRangeLimitTable()
{
	int j;
	rlimit_table = (BYTE *)malloc(5 * 256L + 128);
	tempTable = rlimit_table;
	memset((void *)rlimit_table, 0, 256);
	rlimit_table += 256;
	for (j = 0; j < 256; j++) rlimit_table[j] = j;
	for (j = 256; j < 640; j++) rlimit_table[j] = 255;
	memset((void *)(rlimit_table + 640), 0, 384);
	for (j = 0; j < 128; j++) rlimit_table[j + 1024] = j;
}
/***************************************************************************
* skip bits
**************************************************************************/
void JpegDecoder::SkipKbits(BYTE k)
{
	BYTE b_high, b_low;
	d_k += k;
	if (d_k >= 16)
	{
		d_k -= 16;
		w1 = w2;
		BYTE_p(byte_pos);
		if (bp != 0xFF) b_high = bp;
		else
		{
			if (buf[byte_pos] == 0) byte_pos++;
			else byte_pos--;
			b_high = 0xFF;
		}
		BYTE_p(byte_pos);
		if (bp != 0xFF) b_low = bp;
		else
		{
			if (buf[byte_pos] == 0) byte_pos++;
			else byte_pos--;
			b_low = 0xFF;
		}
		w2 = WORD_hi_lo(b_high, b_low);
	}
	wordval = ((DWORD)(w1) << 16) + w2;
	wordval <<= d_k;
	wordval >>= 16;
}
// Get K bits
SWORD JpegDecoder::GetKbits(BYTE k)
{
	SWORD signed_wordvalue;
	signed_wordvalue = get_svalue(k);
	SkipKbits(k);
	return signed_wordvalue;
}
// Calculate Mask
void JpegDecoder::CalculateMask()
{
	BYTE k;
	DWORD tmpdv;
	for (k = 0; k <= 16; k++) { tmpdv = 0x10000; mask[k] = (tmpdv >> k) - 1; }
}
//initial quant table and allocate the memory
void JpegDecoder::InitQT()
{
	BYTE i;
	for (i = 0; i <= 3; i++) QT[i] = (float *)malloc(sizeof(float) * 64);
}
// Load Quant Table
void JpegDecoder::LoadQuantTable(float *quant_table)
{
	float scalefactor[8] = { 1.0f, 1.387039845f, 1.306562965f, 1.175875602f,
		1.0f, 0.785694958f, 0.541196100f, 0.275899379f };
	BYTE j, row, col;

	for (j = 0; j <= 63; j++) quant_table[j] = buf[byte_pos + zigzag[j]];
	j = 0;
	for (row = 0; row <= 7; row++)
		for (col = 0; col <= 7; col++) {
			quant_table[j] *= scalefactor[row] * scalefactor[col];
			j++;
		}
	byte_pos += 64;
}
///Load Huffman Table
void JpegDecoder::LoadHuffmanTable(Huffman_table *HT)
{
	BYTE k, j;
	DWORD code;

	for (j = 1; j <= 16; j++) {
		BYTE_p(byte_pos);
		HT->Length[j] = bp;
	}
	for (k = 1; k <= 16; k++)
		for (j = 0; j<HT->Length[k]; j++) {
			BYTE_p(byte_pos);
			HT->V[WORD_hi_lo(k, j)] = bp;
		}
	code = 0;
	for (k = 1; k <= 16; k++) {
		HT->minor_code[k] = (WORD)code;
		for (j = 1; j <= HT->Length[k]; j++) code++;
		HT->major_code[k] = (WORD)(code - 1);
		code *= 2;
		if (HT->Length[k] == 0) {
			HT->minor_code[k] = 0xFFFF;
			HT->major_code[k] = 0;
		}
	}
}
////Huffman Data Unit Process
void JpegDecoder::ProcessHuffmanDataUnit(BYTE DC_nr, BYTE AC_nr, SWORD *previous_DC)
{
	BYTE nr, k, j, EOB_found;
	register WORD tmp_Hcode;
	BYTE size_val, count_0;

	WORD *min_code, *maj_code;
	WORD *max_val, *min_val;
	BYTE *huff_values;
	SWORD DCT_tcoeff[64];
	BYTE byte_temp;

	//start to Huffman decode
	min_code = HTDC[DC_nr].minor_code;
	maj_code = HTDC[DC_nr].major_code;
	huff_values = HTDC[DC_nr].V;

	for (nr = 0; nr < 64; nr++) DCT_tcoeff[nr] = 0;

	nr = 0;

	min_val = &min_code[1]; max_val = &maj_code[1];
	for (k = 1; k <= 16; k++)
	{
		tmp_Hcode = lookKbits(k);
		if ((tmp_Hcode <= *max_val) && (tmp_Hcode >= *min_val))
		{
			//look for a valid Huffman
			SkipKbits(k);
			size_val = huff_values[WORD_hi_lo(k, (BYTE)(tmp_Hcode - *min_val))];
			if (size_val == 0) DCT_tcoeff[0] = *previous_DC;
			else
			{
				DCT_tcoeff[0] = *previous_DC + GetKbits(size_val);
				*previous_DC = DCT_tcoeff[0];
			}
			break;
		}
		min_val++; max_val++;
	}

	// AC decode
	min_code = HTAC[AC_nr].minor_code;
	maj_code = HTAC[AC_nr].major_code;
	huff_values = HTAC[AC_nr].V;

	nr = 1; // AC
	EOB_found = 0;
	while ((nr <= 63) && (!EOB_found))
	{
		max_val = &maj_code[1]; min_val = &min_code[1];
		for (k = 1; k <= 16; k++)
		{
			tmp_Hcode = lookKbits(k);
			if ((tmp_Hcode <= *max_val) && (tmp_Hcode >= *min_val))
			{
				SkipKbits(k);
				byte_temp = huff_values[WORD_hi_lo(k, (BYTE)(tmp_Hcode -
					*min_val))];
				size_val = byte_temp & 0xF;
				count_0 = byte_temp >> 4;
				if (size_val == 0)
				{
					if (count_0 == 0) EOB_found = 1;
					else if (count_0 == 0xF) nr += 16; //skip 16 0
				}
				else
				{
					nr += count_0;
					DCT_tcoeff[nr++] = GetKbits(size_val);
				}
				break;
			}
			min_val++; max_val++;
		}
		if (k>16) nr++;
	}
	for (j = 0; j <= 63; j++) DCT_coeff[j] = DCT_tcoeff[zigzag[j]];
}
//quick discrete coeff transformation
void JpegDecoder::IDCTTransform(SWORD *incoeff, BYTE *outcoeff, BYTE Q_nr)
{
	BYTE x;
	SBYTE y;
	SWORD *inptr;
	BYTE *outptr;
	float workspace[64];
	float *wsptr;// workplace pointer
	float *quantptr; //quant table pointer
	float dcval;
	float tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
	float tmp10, tmp11, tmp12, tmp13;
	float z5, z10, z11, z12, z13;
	BYTE *range_limit = rlimit_table + 128;

	wsptr = workspace;
	inptr = incoeff;
	quantptr = QT[Q_nr];
	for (y = 0; y <= 7; y++)
	{
		if ((inptr[8] | inptr[16] | inptr[24] | inptr[32] | inptr[40] | inptr[48] | inptr[56]) == 0)
		{
			dcval = inptr[0] * quantptr[0];
			wsptr[0] = dcval;
			wsptr[8] = dcval;
			wsptr[16] = dcval;
			wsptr[24] = dcval;
			wsptr[32] = dcval;
			wsptr[40] = dcval;
			wsptr[48] = dcval;
			wsptr[56] = dcval;
			inptr++; quantptr++; wsptr++;
			continue;
		}
		//Even
		tmp0 = inptr[0] * quantptr[0];
		tmp1 = inptr[16] * quantptr[16];
		tmp2 = inptr[32] * quantptr[32];
		tmp3 = inptr[48] * quantptr[48];

		tmp10 = tmp0 + tmp2;
		tmp11 = tmp0 - tmp2;

		tmp13 = tmp1 + tmp3;
		tmp12 = (tmp1 - tmp3) * 1.414213562f - tmp13;

		tmp0 = tmp10 + tmp13;
		tmp3 = tmp10 - tmp13;
		tmp1 = tmp11 + tmp12;
		tmp2 = tmp11 - tmp12;

		//Odd
		tmp4 = inptr[8] * quantptr[8];
		tmp5 = inptr[24] * quantptr[24];
		tmp6 = inptr[40] * quantptr[40];
		tmp7 = inptr[56] * quantptr[56];

		z13 = tmp6 + tmp5;
		z10 = tmp6 - tmp5;
		z11 = tmp4 + tmp7;
		z12 = tmp4 - tmp7;

		tmp7 = z11 + z13;
		tmp11 = (z11 - z13) * 1.414213562f;

		z5 = (z10 + z12) * 1.847759065f;
		tmp10 = 1.082392200f * z12 - z5;
		tmp12 = -2.613125930f * z10 + z5;

		tmp6 = tmp12 - tmp7;
		tmp5 = tmp11 - tmp6;
		tmp4 = tmp10 + tmp5;

		wsptr[0] = tmp0 + tmp7;
		wsptr[56] = tmp0 - tmp7;
		wsptr[8] = tmp1 + tmp6;
		wsptr[48] = tmp1 - tmp6;
		wsptr[16] = tmp2 + tmp5;
		wsptr[40] = tmp2 - tmp5;
		wsptr[32] = tmp3 + tmp4;
		wsptr[24] = tmp3 - tmp4;
		inptr++;
		quantptr++;
		wsptr++;
	}

	//Deal with the info from workspace row
	outptr = outcoeff;
	wsptr = workspace;
	for (x = 0; x <= 7; x++)
	{
		// Even
		tmp10 = wsptr[0] + wsptr[4];
		tmp11 = wsptr[0] - wsptr[4];

		tmp13 = wsptr[2] + wsptr[6];
		tmp12 = (wsptr[2] - wsptr[6]) * 1.414213562f - tmp13;

		tmp0 = tmp10 + tmp13;
		tmp3 = tmp10 - tmp13;
		tmp1 = tmp11 + tmp12;
		tmp2 = tmp11 - tmp12;

		// Odd
		z13 = wsptr[5] + wsptr[3];
		z10 = wsptr[5] - wsptr[3];
		z11 = wsptr[1] + wsptr[7];
		z12 = wsptr[1] - wsptr[7];

		tmp7 = z11 + z13;
		tmp11 = (z11 - z13) * 1.414213562f;

		z5 = (z10 + z12) * 1.847759065f;
		tmp10 = 1.082392200f * z12 - z5;
		tmp12 = -2.613125930f * z10 + z5;

		tmp6 = tmp12 - tmp7;
		tmp5 = tmp11 - tmp6;
		tmp4 = tmp10 + tmp5;

		// Output
		outptr[0] = range_limit[(DESCALE((int)(tmp0 + tmp7), 3)) & 1023L];
		outptr[7] = range_limit[(DESCALE((int)(tmp0 - tmp7), 3)) & 1023L];
		outptr[1] = range_limit[(DESCALE((int)(tmp1 + tmp6), 3)) & 1023L];
		outptr[6] = range_limit[(DESCALE((int)(tmp1 - tmp6), 3)) & 1023L];
		outptr[2] = range_limit[(DESCALE((int)(tmp2 + tmp5), 3)) & 1023L];
		outptr[5] = range_limit[(DESCALE((int)(tmp2 - tmp5), 3)) & 1023L];
		outptr[4] = range_limit[(DESCALE((int)(tmp3 + tmp4), 3)) & 1023L];
		outptr[3] = range_limit[(DESCALE((int)(tmp3 - tmp4), 3)) & 1023L];

		wsptr += 8;
		outptr += 8;
	}
}
//Pre deal with the color space 
void JpegDecoder::Precalculate_Cr_Cb_Tables()
{
	WORD k;
	WORD Cr_v, Cb_v;
	for (k = 0; k <= 255; k++) Cr_tab[k] = (SWORD)((k - 128.0)*1.402);
	for (k = 0; k <= 255; k++) Cb_tab[k] = (SWORD)((k - 128.0)*1.772);

	for (Cr_v = 0; Cr_v <= 255; Cr_v++)
		for (Cb_v = 0; Cb_v <= 255; Cb_v++)
			Cr_Cb_green_tab[((WORD)(Cr_v) << 8) + Cb_v] = (int)(-0.34414*(Cb_v -
				128.0) - 0.71414*(Cr_v - 128.0));
}
//Convert 8x8 YCbCr workspace To RGB workspace
void JpegDecoder::Convert8x8YCbCrToRGB(BYTE *Y, BYTE *Cb, BYTE *Cr, DWORD im_loc, DWORD X_image_bytes, BYTE *im_buffer)
{
	DWORD x, y;
	BYTE im_nr;
	BYTE *Y_val = Y, *Cb_val = Cb, *Cr_val = Cr;
	BYTE *ibuffer = im_buffer + im_loc;

	for (y = 0; y<8; y++)
	{
		im_nr = 0;
		for (x = 0; x<8; x++)
		{
			ibuffer[im_nr++] = rlimit_table[*Y_val + Cb_tab[*Cb_val]]; //B
			ibuffer[im_nr++] = rlimit_table[*Y_val +
				Cr_Cb_green_tab[WORD_hi_lo(*Cr_val, *Cb_val)]]; //G
			ibuffer[im_nr++] = rlimit_table[*Y_val + Cr_tab[*Cr_val]]; // R
			Y_val++; Cb_val++; Cr_val++; im_nr++;
		}
		ibuffer += X_image_bytes;
	}
}
//Convert 8x8 YCbCr workspace To RGB workspace, different YCbCr
void JpegDecoder::Convert8x8YCbCrToRGBTab(BYTE *Y, BYTE *Cb, BYTE *Cr, BYTE *tab, DWORD im_loc, DWORD X_image_bytes, BYTE *im_buffer)
{
	DWORD x, y;
	BYTE nr, im_nr;
	BYTE Y_val, Cb_val, Cr_val;
	BYTE *ibuffer = im_buffer + im_loc;

	nr = 0;
	for (y = 0; y<8; y++)
	{
		im_nr = 0;
		for (x = 0; x<8; x++)
		{
			Y_val = Y[nr];
			Cb_val = Cb[tab[nr]]; Cr_val = Cr[tab[nr]];
			ibuffer[im_nr++] = rlimit_table[Y_val + Cb_tab[Cb_val]]; //B
			ibuffer[im_nr++] = rlimit_table[Y_val +
				Cr_Cb_green_tab[WORD_hi_lo(Cr_val, Cb_val)]]; //G
			ibuffer[im_nr++] = rlimit_table[Y_val + Cr_tab[Cr_val]]; // R
			nr++; im_nr++;
		}
		ibuffer += X_image_bytes;
	}
}
// Calculate Tabs 
void JpegDecoder::CalculateTabs()
{
	BYTE tab_temp[256];
	BYTE x, y;

	//convert array to 16*16 mattrix
	for (y = 0; y<16; y++)
		for (x = 0; x<16; x++)
			tab_temp[y * 16 + x] = (y / YV) * 8 + x / YH;

	//8*8 blanks
	for (y = 0; y<8; y++)
	{
		for (x = 0; x<8; x++)
			tab_1[y * 8 + x] = tab_temp[y * 16 + x];
		for (x = 8; x<16; x++)
			tab_2[y * 8 + (x - 8)] = tab_temp[y * 16 + x];
	}
	for (y = 8; y<16; y++)
	{
		for (x = 0; x<8; x++)
			tab_3[(y - 8) * 8 + x] = tab_temp[y * 16 + x];
		for (x = 8; x<16; x++)
			tab_4[(y - 8) * 8 + (x - 8)] = tab_temp[y * 16 + x];
	}
}
//Initial JPG Decoding
int JpegDecoder::InitJPGDecoding()
{
	byte_pos = 0;
	InitQT();
	CalculateMask();
	PrepareRangeLimitTable();
	Precalculate_Cr_Cb_Tables();
	return 1;
}
// Get File Size
DWORD JpegDecoder::GetFileSize(FILE *fp)
{
	DWORD pos;
	DWORD pos_cur;
	pos_cur = ftell(fp);
	fseek(fp, 0, SEEK_END);
	pos = ftell(fp);
	fseek(fp, pos_cur, SEEK_SET);
	return pos;
}

void JpegDecoder::Resync()
{
	byte_pos += 2;
	BYTE_p(byte_pos);
	if (bp == 0xFF) byte_pos++;
	w1 = WORD_hi_lo(bp, 0);
	BYTE_p(byte_pos);
	if (bp == 0xFF) byte_pos++;
	w1 += bp;
	BYTE_p(byte_pos);
	if (bp == 0xFF) byte_pos++;
	w2 = WORD_hi_lo(bp, 0);
	BYTE_p(byte_pos);
	if (bp == 0xFF) byte_pos++;
	w2 += bp;
	wordval = w1; d_k = 0;
	DCY = 0; DCCb = 0; DCCr = 0;
}
//Decode MCU 1*1
void JpegDecoder::DecodeMCU1x1(DWORD im_loc)
{
	// Y
	ProcessHuffmanDataUnit(YDC_nr, YAC_nr, &DCY);
	IDCTTransform(DCT_coeff, Y, YQ_nr);
	// Cb
	ProcessHuffmanDataUnit(CbDC_nr, CbAC_nr, &DCCb);
	IDCTTransform(DCT_coeff, Cb, CbQ_nr);
	// Cr
	ProcessHuffmanDataUnit(CrDC_nr, CrAC_nr, &DCCr);
	IDCTTransform(DCT_coeff, Cr, CrQ_nr);

	Convert8x8YCbCrToRGB(Y, Cb, Cr, im_loc, X_image_bytes, im_buffer);
}
//Decode MCU 2*1
void JpegDecoder::DecodeMCU2x1(DWORD im_loc)
{
	// Y
	ProcessHuffmanDataUnit(YDC_nr, YAC_nr, &DCY);
	IDCTTransform(DCT_coeff, Y_1, YQ_nr);
	ProcessHuffmanDataUnit(YDC_nr, YAC_nr, &DCY);
	IDCTTransform(DCT_coeff, Y_2, YQ_nr);
	// Cb
	ProcessHuffmanDataUnit(CbDC_nr, CbAC_nr, &DCCb);
	IDCTTransform(DCT_coeff, Cb, CbQ_nr);
	// Cr
	ProcessHuffmanDataUnit(CrDC_nr, CrAC_nr, &DCCr);
	IDCTTransform(DCT_coeff, Cr, CrQ_nr);

	Convert8x8YCbCrToRGBTab(Y_1, Cb, Cr, tab_1, im_loc, X_image_bytes, im_buffer);
	Convert8x8YCbCrToRGBTab(Y_2, Cb, Cr, tab_2, im_loc + 32, X_image_bytes, im_buffer);
}
//Decode MCU 2*2
void JpegDecoder::DecodeMCU2x2(DWORD im_loc)
{
	// Y
	ProcessHuffmanDataUnit(YDC_nr, YAC_nr, &DCY);
	IDCTTransform(DCT_coeff, Y_1, YQ_nr);
	ProcessHuffmanDataUnit(YDC_nr, YAC_nr, &DCY);
	IDCTTransform(DCT_coeff, Y_2, YQ_nr);
	ProcessHuffmanDataUnit(YDC_nr, YAC_nr, &DCY);
	IDCTTransform(DCT_coeff, Y_3, YQ_nr);
	ProcessHuffmanDataUnit(YDC_nr, YAC_nr, &DCY);
	IDCTTransform(DCT_coeff, Y_4, YQ_nr);
	// Cb
	ProcessHuffmanDataUnit(CbDC_nr, CbAC_nr, &DCCb);
	IDCTTransform(DCT_coeff, Cb, CbQ_nr);
	// Cr
	ProcessHuffmanDataUnit(CrDC_nr, CrAC_nr, &DCCr);
	IDCTTransform(DCT_coeff, Cr, CrQ_nr);

	Convert8x8YCbCrToRGBTab(Y_1, Cb, Cr, tab_1, im_loc, X_image_bytes, im_buffer);
	Convert8x8YCbCrToRGBTab(Y_2, Cb, Cr, tab_2, im_loc + 32, X_image_bytes, im_buffer);
	Convert8x8YCbCrToRGBTab(Y_3, Cb, Cr, tab_3, im_loc + y_inc_value, X_image_bytes, im_buffer);
	Convert8x8YCbCrToRGBTab(Y_4, Cb, Cr, tab_4, im_loc + y_inc_value + 32, X_image_bytes, im_buffer);
}
//Decode MCU 1*2
void JpegDecoder::DecodeMCU1x2(DWORD im_loc)
{
	// Y
	ProcessHuffmanDataUnit(YDC_nr, YAC_nr, &DCY);
	IDCTTransform(DCT_coeff, Y_1, YQ_nr);
	ProcessHuffmanDataUnit(YDC_nr, YAC_nr, &DCY);
	IDCTTransform(DCT_coeff, Y_2, YQ_nr);
	// Cb
	ProcessHuffmanDataUnit(CbDC_nr, CbAC_nr, &DCCb);
	IDCTTransform(DCT_coeff, Cb, CbQ_nr);
	// Cr
	ProcessHuffmanDataUnit(CrDC_nr, CrAC_nr, &DCCr);
	IDCTTransform(DCT_coeff, Cr, CrQ_nr);

	Convert8x8YCbCrToRGBTab(Y_1, Cb, Cr, tab_1, im_loc, X_image_bytes, im_buffer);
	Convert8x8YCbCrToRGBTab(Y_2, Cb, Cr, tab_3, im_loc + y_inc_value, X_image_bytes, im_buffer);
}
//Decode JPEG Image
void JpegDecoder::DecodeJPEGImage()
{
	decode_MCU_func decode_MCU;

	WORD x_mcu_cnt, y_mcu_cnt;
	DWORD nr_mcu;
	WORD X_MCU_nr, Y_MCU_nr;
	DWORD MCU_dim_x; //dimensiunea in bufferul imagine a unui MCU pe axa x
	DWORD im_loc_inc; // = 7 * X_round * 4 sau 15*X_round*4;
	DWORD im_loc; //locatia in bufferul imagine

	byte_pos -= 2;
	Resync();

	y_inc_value = 32 * X_round;

	CalculateTabs();

	if ((YH == 1) && (YV == 1)) decode_MCU = &JpegDecoder::DecodeMCU1x1;
	else {
		if (YH == 2)
		{
			if (YV == 2) decode_MCU = &JpegDecoder::DecodeMCU2x2;
			else decode_MCU = &JpegDecoder::DecodeMCU2x1;
		}
		else decode_MCU = &JpegDecoder::DecodeMCU1x2;
	}
	MCU_dim_x = Hmax * 8 * 4;

	Y_MCU_nr = Y_round / (Vmax * 8);
	X_MCU_nr = X_round / (Hmax * 8);

	X_image_bytes = X_round * 4; im_loc_inc = (Vmax * 8 - 1) * X_image_bytes;
	nr_mcu = 0; im_loc = 0;

	for (y_mcu_cnt = 0; y_mcu_cnt<Y_MCU_nr; y_mcu_cnt++)
	{
		for (x_mcu_cnt = 0; x_mcu_cnt<X_MCU_nr; x_mcu_cnt++)
		{
			(this->*decode_MCU)(im_loc);
			if ((Restart_markers) && ((nr_mcu + 1) % MCU_restart == 0)) Resync();
			nr_mcu++;
			im_loc += MCU_dim_x;
		}
		im_loc += im_loc_inc;
	}
}
// Get JPEG Buffer
int JpegDecoder::GetJPEGBuffer(WORD X_image, WORD Y_image, BYTE **address_dest_buffer)
{
	WORD y;
	DWORD dest_loc = 0;
	BYTE *src_buffer = im_buffer;
	BYTE *dest_buffer_start, *dest_buffer;

	DWORD src_bytes_per_line = X_round * 4;
	DWORD dest_bytes_per_line = X_image * 4;

	if ((X_round == X_image) && (Y_round == Y_image))
		*address_dest_buffer = im_buffer;

	else
	{
		dest_buffer_start = (BYTE *)malloc(X_image*Y_image * 4);
		if (dest_buffer_start == NULL) exit_func("Not enough memory for storing image");
		dest_buffer = dest_buffer_start;
		for (y = 0; y<Y_image; y++) {
			memcpy(dest_buffer, src_buffer, dest_bytes_per_line);
			src_buffer += src_bytes_per_line;
			dest_buffer += dest_bytes_per_line;
		}
		*address_dest_buffer = dest_buffer_start;
		free(im_buffer);
	}
	return 1;
}
