#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BYTE unsigned char //1 BYTE
#define WORD unsigned short int //2 byte
#define DWORD unsigned int //4 byte
#define SDWORD signed int //4 byte
#define SBYTE signed char //1 byte
#define SWORD signed short int //2 byte


typedef struct {
	// k is from 1 to 16
	// Length[k] Huffman coding
	BYTE Length[17];
	//the minium Huffman number
	WORD minor_code[17];
	//the maxium Huffman number
	WORD major_code[17];
	BYTE V[65536];
} Huffman_table;


class JpegDecoder
{
public:

	JpegDecoder(FILE *f);

	~JpegDecoder(void);
	//Get JPEG Buffer after decode
	int GetJPEGBuffer(WORD X_image, WORD Y_image, BYTE **address_dest_buffer);
	//get width of the image
	int GetWidth() const { return width; }
	//get height of the image
	int GetHeight() const { return height; }

private:
	//width of the image
	DWORD	width;
	//height of the image
	DWORD	height;
	//pointer of JPEG file
	BYTE*	buf;
	//byte
	BYTE	bp;
	//word
	WORD	wp;
	//byte position
	DWORD	byte_pos;

	WORD	X_round;
	WORD	Y_round;
	//pixel array to store the decoded result
	BYTE*	im_buffer;
	//byte of image per raw
	DWORD	X_image_bytes;

	DWORD	y_inc_value;
	//Y, Cb, Cr sample level and verticle 
	BYTE	YH, YV, CbH, CbV, CrH, CrV;
	WORD	Hmax, Vmax;
	//4 Quant table 
	float*	QT[4];
	//DC Huffman Table
	Huffman_table HTDC[4];
	//AC Huffman Table
	Huffman_table HTAC[4];
	//Y, Cb, Cr NUMBER OF Huffman Table
	BYTE YQ_nr, CbQ_nr, CrQ_nr;
	//Y, Cb, Cr NUMBER OF Huffman Table for DC
	BYTE YDC_nr, CbDC_nr, CrDC_nr;
	//Y, Cb, Cr NUMBER OF Huffman Table for AC
	BYTE YAC_nr, CbAC_nr, CrAC_nr;
	//Remark
	BYTE Restart_markers;
	//MCU Remark
	WORD MCU_restart;
	SWORD DCY, DCCb, DCCr; // Coeficientii DC pentru Y,Cb,Cr

	SWORD DCT_coeff[64];

	BYTE Y[64], Cb[64], Cr[64];

	BYTE Y_1[64], Y_2[64], Y_3[64], Y_4[64];
	BYTE tab_1[64], tab_2[64], tab_3[64], tab_4[64];
	SWORD Cr_tab[256], Cb_tab[256]; // Precalculated Cr, Cb tables
	SWORD Cr_Cb_green_tab[65536];

	//offset
	BYTE d_k;
	// w1 is the first word in the memory; w2  is the second word in the memory
	WORD w1, w2;
	DWORD mask[17];

	int		shift_temp;

	BYTE*	rlimit_table;
	BYTE*	tempTable;
	char	error_string[90];
	void PrepareRangeLimitTable(void);
	void SkipKbits(BYTE k);
	SWORD GetKbits(BYTE k);
	void CalculateMask(void);
	//Initial Quant Table
	void InitQT();
	//Load Quant Table
	void LoadQuantTable(float *quant_table);
	//Load Huffman Table
	void LoadHuffmanTable(Huffman_table *HT);
	//Huffman Data Unit Process
	void ProcessHuffmanDataUnit(BYTE DC_nr, BYTE AC_nr, SWORD *previous_DC);
	//random arcsin transformation
	void IDCTTransform(SWORD *incoeff, BYTE *outcoeff, BYTE Q_nr);
	void Precalculate_Cr_Cb_Tables();
	//convertion of color space YCbCr->RGB
	void Convert8x8YCbCrToRGB(BYTE *Y, BYTE *Cb, BYTE *Cr, DWORD im_loc, DWORD X_image_bytes, BYTE *im_buffer);
	void Convert8x8YCbCrToRGBTab(BYTE *Y, BYTE *Cb, BYTE *Cr, BYTE *tab, DWORD im_loc, DWORD X_image_bytes, BYTE *im_buffer);
	void CalculateTabs();
	//intial for JPG decoding
	int InitJPGDecoding();
	//Get The Size of the File
	DWORD GetFileSize(FILE *fp);
	void Resync();
	//Decode MCU
	void DecodeMCU1x1(DWORD im_loc);
	void DecodeMCU2x1(DWORD im_loc);
	void DecodeMCU2x2(DWORD im_loc);
	void DecodeMCU1x2(DWORD im_loc);
	//Load JPEG Header
	bool LoadJPEGHeader(FILE* fp);
	//JPEG decoder function
	void DecodeJPEGImage();
};