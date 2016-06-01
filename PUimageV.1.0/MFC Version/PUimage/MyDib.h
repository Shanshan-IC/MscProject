#pragma once

class MyDib : public CObject
{

private:
	BITMAPINFO*	DibInfo;
	void*		DibBits;


public:

	MyDib(LPCTSTR  dibName);//read DIB from the file
	MyDib(CBitmap& ddb, CPalette* palette);//read DIB from the DDB
	MyDib(int Width, int Height, int BitsPerPixel);//create new DIB

	~MyDib();

	//GET pixel array
	void*		GetBits();
	//GET pixel bit
	int			GetBitsPerPixel();
	//get the width of the image
	long		GetWidth();
	//get the height of the image
	long		GetHeight();
	//get the bytes per line
	long		BytesPerLine();
	//get the paletter
	CPalette*	GetPalette();
	//copy the paletter
	void		CopyPalette(CPalette&);
	//get the size of the paletter
	int	GetPaletteCount();
	//get the size of the array
	long		GetBodySize();
	//stretch out based on the required DC
	int			StretchToDC(CDC& dc, CRect& src, CRect& dst, DWORD rop = SRCCOPY);
	//out based on the required DC AND NOT CHANGE THE SIZE
	int			SetToDC(CDC& dc, CRect& src, CPoint& dst);
	//save
	void		SaveDIB(LPCTSTR dibName);
};
