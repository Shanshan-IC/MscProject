// MyDib.cpp 
//

#include "stdafx.h"
#include "PUimage.h"
#include "MyDib.h"


MyDib::MyDib(LPCTSTR dibName)
	: DibBits(NULL), DibInfo(NULL)
{
	//
	CFile fp(dibName, CFile::modeRead | CFile::typeBinary);

	BITMAPFILEHEADER bmfileheader;
	BITMAPINFOHEADER bmheader;

	ULONGLONG headpos;
	int PaletteSize = 0;
	int ret, cbHeaderSize;
	//get the file pointer position
	headpos = fp.GetPosition();
	//get bmp file header
	ret = fp.Read(&bmfileheader, sizeof(BITMAPFILEHEADER));

	if (bmfileheader.bfType != 0x4d42)
	{
		AfxMessageBox(L"Error!");
		return;
	}

	//get the bmp file info
	ret = fp.Read(&bmheader, sizeof(BITMAPINFOHEADER));
	//计算RGBQUAD的大小
	switch (bmheader.biBitCount)
	{
	case 1:
		PaletteSize = 2;
		break;
	case 4:
		PaletteSize = 16;
		break;
	case 8:
		PaletteSize = 256;
		break;
	}

	//get the memory for BITMAPINFO
	cbHeaderSize = sizeof(BITMAPINFOHEADER) + PaletteSize * sizeof(RGBQUAD);
	DibInfo = (BITMAPINFO*) new char[cbHeaderSize];
	DibInfo->bmiHeader = bmheader;

	if (PaletteSize)
	{
		ret = fp.Read(&(DibInfo->bmiColors[0]), PaletteSize * sizeof(RGBQUAD));
		if (ret != int(PaletteSize * sizeof(RGBQUAD)))
		{
			delete[] DibInfo;
			DibInfo = NULL;
			return;
		}
	}

	//allocate the memory for the pixel array, size based ono GetBodySize()
	DibBits = (void*) new char[GetBodySize()];
	//pointer move to DIB image array
	fp.Seek(headpos + bmfileheader.bfOffBits, CFile::begin);

	ret = fp.Read(DibBits, GetBodySize());
	if (ret != int(GetBodySize()))
	{
		delete[] DibInfo;
		delete[] DibBits;
		DibInfo = NULL;
		DibBits = NULL;
	}
	//close the file
	fp.Close();
}

MyDib::MyDib(CBitmap& ddb, CPalette* palette)
	: DibBits(NULL), DibInfo(NULL)
{
	BITMAP ddbinfo;
	//get  info of ddb
	ddb.GetBitmap(&ddbinfo);
	/*write the BITMAPINFO*/
	int w = ddbinfo.bmWidth;
	int h = ddbinfo.bmHeight;
	int BitsPerPixel = ddbinfo.bmPlanes*ddbinfo.bmBitsPixel;

	int i;
	int PaletteSize = 0, cbHeaderSize;

	//set the size of RGBQUAD array
	switch (BitsPerPixel)
	{
	case 1:
		PaletteSize = 2;
		break;
	case 4:
		PaletteSize = 16;
		break;
	case 8:
		PaletteSize = 256;
		break;
		//over 8, DIB doesnot need the palette
	case 15:
	case 16:
		BitsPerPixel = 16;
		break;
	}

	cbHeaderSize = sizeof(BITMAPINFOHEADER) + PaletteSize * sizeof(RGBQUAD);
	if (DibInfo) delete[] DibInfo;
	//allocate the memory for BITMAPINFO
	DibInfo = (BITMAPINFO*) new char[cbHeaderSize];
	//write BITMAPINFO
	DibInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	DibInfo->bmiHeader.biWidth = w;
	DibInfo->bmiHeader.biHeight = h;
	DibInfo->bmiHeader.biPlanes = 1;
	DibInfo->bmiHeader.biBitCount = short(BitsPerPixel);
	DibInfo->bmiHeader.biCompression = BI_RGB;
	DibInfo->bmiHeader.biSizeImage = BytesPerLine() * DibInfo->bmiHeader.biHeight;
	DibInfo->bmiHeader.biXPelsPerMeter =
		DibInfo->bmiHeader.biYPelsPerMeter = 3780;
	DibInfo->bmiHeader.biClrUsed = PaletteSize;
	DibInfo->bmiHeader.biClrImportant = PaletteSize;

	if (PaletteSize)
	{
		//set 0
		for (i = 0; i < PaletteSize; i++)
		{
			DibInfo->bmiColors[i].rgbRed = 0;
			DibInfo->bmiColors[i].rgbGreen = 0;
			DibInfo->bmiColors[i].rgbBlue = 0;
			DibInfo->bmiColors[i].rgbReserved = 0;
		}
	}

	//allocate the memory for DIB pixel array, size is based on GetBodySize()
	DibBits = (void*) new char[GetBodySize()];
	//if it is paletter, then copy it
	if (palette) CopyPalette(*palette);

	// DDB info copy tp DIB

	CWnd DesktopWnd;
	DesktopWnd.Attach(::GetDesktopWindow());
	CWindowDC dtpDC(&DesktopWnd);
	::GetDIBits(dtpDC.m_hDC,
		HBITMAP(ddb),
		0,
		ddbinfo.bmHeight,
		LPVOID(DibBits),
		DibInfo,
		DIB_RGB_COLORS
	);
	DesktopWnd.Detach();
}

MyDib::~MyDib()
{
	delete[] DibInfo;
	delete[] DibBits;
}

void* MyDib::GetBits()
{
	return DibBits;
}

int MyDib::GetBitsPerPixel()
{
	if (!DibInfo)return 0;
	return DibInfo->bmiHeader.biBitCount;
}

long MyDib::GetWidth()
{
	return DibInfo->bmiHeader.biWidth;
}

long MyDib::GetHeight()
{
	return DibInfo->bmiHeader.biHeight;
}

long MyDib::GetBodySize()
{
	return BytesPerLine() * DibInfo->bmiHeader.biHeight;
}

int MyDib::GetPaletteCount()
{
	int PaletteSize = 0;
	if (!DibInfo) return 0;
	switch (DibInfo->bmiHeader.biBitCount)
	{
	case 1:
		PaletteSize = 2;
		break;
	case 4:
		PaletteSize = 16;
		break;
	case 8:
		PaletteSize = 256;
		break;
	}
	return PaletteSize;
}

long MyDib::BytesPerLine()
{
	return ((((DibInfo->bmiHeader.biWidth * GetBitsPerPixel()) + 31) / 32) * 4);
}

int MyDib::SetToDC(CDC& dc, CRect& src, CPoint& dst)
{
	return ::SetDIBitsToDevice(
		dc.m_hDC,
		dst.x,
		dst.y,
		src.Width(),
		src.Height(),
		src.left,
		src.top,
		0,
		DibInfo->bmiHeader.biHeight,
		DibBits,
		DibInfo,
		DIB_RGB_COLORS
	);
}

int MyDib::StretchToDC(CDC& dc, CRect& src, CRect& dst, DWORD rop)
{
	return ::StretchDIBits(
		dc.m_hDC,
		dst.left,
		dst.top,
		dst.Width(),
		dst.Height(),
		src.left,
		src.top,
		src.Width(),
		src.Height(),
		DibBits,
		DibInfo,
		DIB_RGB_COLORS,
		rop
	);
}

void MyDib::SaveDIB(LPCTSTR dibName)
{

	if (!DibInfo)
	{
		AfxMessageBox(L"DIB info does not exit!");
		return;
	}

	//create cfile
	CFile file;
	if (!file.Open(dibName, CFile::modeCreate | CFile::modeReadWrite))
	{
		AfxMessageBox(L"Failed to create the file");
		return;
	}

	//Bitmap file header
	BITMAPFILEHEADER bmfileheader;

	long size = BytesPerLine() * DibInfo->bmiHeader.biHeight;
	int PaletteSize = GetPaletteCount();

	//get BMP file date
	bmfileheader.bfType = 0x4d42;// type"BM"
	bmfileheader.bfReserved1 = bmfileheader.bfReserved2 = 0;
	bmfileheader.bfOffBits =
		sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)
		+ PaletteSize * sizeof(RGBQUAD);
	bmfileheader.bfSize = bmfileheader.bfOffBits + size;

	//write the bitmap info and pixel arary to the disk
	file.Write(&bmfileheader, sizeof(BITMAPFILEHEADER));
	file.Write(DibInfo, sizeof(BITMAPINFOHEADER) + PaletteSize * sizeof(RGBQUAD));
	file.Write(DibBits, size);
	//close
	file.Close();
}

void MyDib::CopyPalette(CPalette& palette)
{
	int i;
	PALETTEENTRY *pe;

	if (!DibInfo->bmiHeader.biBitCount) return;
	if (palette.GetEntryCount() != DibInfo->bmiHeader.biBitCount) return;

	pe = new PALETTEENTRY[palette.GetEntryCount()];
	palette.GetPaletteEntries(0, palette.GetEntryCount(), pe);

	for (i = 0; i < palette.GetEntryCount(); i++)
	{
		DibInfo->bmiColors[i].rgbRed = pe[i].peRed;
		DibInfo->bmiColors[i].rgbGreen = pe[i].peGreen;
		DibInfo->bmiColors[i].rgbBlue = pe[i].peBlue;
		DibInfo->bmiColors[i].rgbReserved = 0;
	}

	delete[] pe;
}