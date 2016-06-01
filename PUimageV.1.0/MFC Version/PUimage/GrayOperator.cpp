#include "StdAfx.h"
#include "GrayOperator.h"
#include <cmath>
#include <iostream>
#include <fstream>
using namespace std;


/******************************************************************************
*	Linear transformation
*		pixel		initial pixel array
*		tempPixel	save pixel array
*		width		initial width
*		height		initial height
*		slope		slope of linear function
*		inter		inter of  of linear function
******************************************************************************/
void LineTrans(BYTE* pixel, BYTE* tempPixel, UINT width, UINT height,
	double slope, double inter)
{
	// mapping table
	BYTE map[256];

	// save temp value
	double dTemp;

	for (int i = 0; i < 256; i++)
	{
		// save
		dTemp = slope * i + inter;

		// if it is over them modify 
		if (dTemp < 0)
			dTemp = 0.0;
		else if (dTemp > 255)
			dTemp = 255;

		map[i] = int(dTemp + 0.5);
	}

	// look for the value in the mapping table after linear transformation
	for (UINT i = 0; i < width * height; i++)
	{
		for (int j = 0; j < 4; j++)
			tempPixel[i * 4 + j] = map[pixel[i * 4 + j]];
	}
}

/******************************************************************************
*	Logarithm transformation
*		pixel		initial pixel array
*		tempPixel	save pixel array
*		width		initial width
*		height		initial height
*		a			offset of up and down
*		b			offset of left and right
******************************************************************************/
void LogTrans(BYTE* pixel, BYTE* tempPixel, UINT width, UINT height,
	double a, double b)
{
	// mapping table
	BYTE map[256];

	// save temp value
	double dTemp;

	for (int i = 0; i < 256; i++)
	{
		dTemp = log((double)i + 1.0) / b + a;

		// if it is over them modify 
		if (dTemp < 0)
			dTemp = 0.0;
		else if (dTemp > 255)
			dTemp = 255;
		map[i] = int(dTemp + 0.5);
	}

	for (UINT i = 0; i < width * height; i++)
	{
		for (int j = 0; j < 4; j++)
			tempPixel[i * 4 + j] = map[pixel[i * 4 + j]];
	}
}

/******************************************************************************
*	Power transformation
*		pixel		initial pixel array
*		tempPixel	save pixel array
*		width		initial width
*		height		initial height
*		a			offset of up and down
*		b			offset of left and right
******************************************************************************/
void PowerTrans(BYTE* pixel, BYTE* tempPixel, UINT width, UINT height,
	double b, double c, double r)
{
	// mapping table
	BYTE map[256];

	// save temp value
	double dTemp;

	for (int i = 0; i < 256; i++)
	{
		dTemp = c * pow(i / 255.0, r) * 255 + b;

		// if it is over them modify 
		if (dTemp < 0)
			dTemp = 0.0;
		else if (dTemp > 255)
			dTemp = 255;

		map[i] = int(dTemp + 0.5);
	}

	for (UINT i = 0; i < width * height; i++)
	{
		for (int j = 0; j < 4; j++)
			tempPixel[i * 4 + j] = map[pixel[i * 4 + j]];
	}
}

/******************************************************************************
*	Index transformation
*		pixel		initial pixel array
*		tempPixel	save pixel array
*		width		initial width
*		height		initial height
*		a			offset of up and down
*		b			offset of left and right
******************************************************************************/
void ExpTrans(BYTE* pixel, BYTE* tempPixel, UINT width, UINT height,
	double a, double b, double c)
{
	// mapping table
	BYTE map[256];

	// save temp value
	double dTemp;

	for (int i = 0; i < 256; i++)
	{
		dTemp = pow(b, c * (i - a)) - 1;

		// if it is over them modify 
		if (dTemp < 0)
			dTemp = 0.0;
		else if (dTemp > 255)
			dTemp = 255;

		map[i] = int(dTemp + 0.5);
	}

	for (UINT i = 0; i < width * height; i++)
	{
		for (int j = 0; j < 4; j++)
			tempPixel[i * 4 + j] = map[pixel[i * 4 + j]];
	}
}


/******************************************************************************
*	Threshold transformation
*		pixel		initial pixel array
*		tempPixel	save pixel array
*		width		initial width
*		height		initial height
*		thr			threshold
******************************************************************************/
void ThresholdTrans(BYTE* pixel, BYTE* tempPixel, UINT width, UINT height, int thr)
{
	// mapping table
	BYTE map[256];

	for (int i = 0; i < 256; i++)
	{
		if (i >= thr)
			map[i] = 255;
		else
			map[i] = 0;
	}

	// look for the value in the mapping table after transformation
	for (UINT i = 0; i < width * height; i++)
	{
		int x = pixel[i * 4];

		tempPixel[i * 4] = tempPixel[i * 4 + 1] = tempPixel[i * 4 + 2] = map[x];
		tempPixel[i * 4 + 3] = 255;
	}
}

/******************************************************************************
*	Threshold stretch
*		pixel		initial pixel array
*		tempPixel	save pixel array
*		width		initial width
*		X1,Y1		Position of control point 1
*		X2,Y2		Position of control point 2
******************************************************************************/
void GrayStretch(BYTE* pixel, BYTE* tempPixel, UINT width, UINT height,
	float X1, float Y1, float X2, float Y2)
{
	// mapping table
	BYTE map[256];

	double dTemp;

	for (int x = 0; x < 256; x++)
	{
		// if it is on the first line
		if (x < X1)
		{
			if (fabs(X1 - 0) > 0.0001)
				dTemp = (float)Y1 / (float)X1 * x;
			else
				dTemp = 0;
		}
		// if it is on the second line
		else if (x <= X2)
		{
			if (fabs(X2 - X1) > 0.0001)
				dTemp = (float)(Y2 - Y1) / (float)(X2 - X1) * (x - X1) + Y1;
			else
				dTemp = x;
		}
		// if it is on the third line
		else
		{
			if (fabs(Y2 - 255) > 0.0001)
				dTemp = (float)(255 - Y2) / (float)(255 - X2) * (x - X2) + Y2;
			else
				dTemp = 255;
		}

		map[x] = int(dTemp + 0.5);
	}

	//look for the value in the mapping table after transformation
	for (UINT i = 0; i < width * height; i++)
	{
		int x = pixel[i * 4];

		tempPixel[i * 4] = tempPixel[i * 4 + 1] = tempPixel[i * 4 + 2] = map[x];
		tempPixel[i * 4 + 3] = 255;
	}
}

/******************************************************************************
*	Threshold stretch
*		pixel		initial pixel array
*		tempPixel	save pixel array
*		width		initial width
******************************************************************************/
void GrayEqualize(BYTE* pixel, BYTE* tempPixel, UINT width, UINT height)
{

	//mapping table
	BYTE map[256];
	long lCounts[256];

	memset(lCounts, 0, sizeof(long) * 256);

	// calculate
	for (UINT i = 0; i < width * height; i++)
	{
		int x = pixel[i * 4];
		lCounts[x]++;
	}

	long lTemp;

	for (int i = 0; i < 256; i++)
	{
		lTemp = 0;
		for (int j = 0; j <= i; j++)
			lTemp += lCounts[j];

		map[i] = (BYTE)(lTemp * 255.0f / width / height);
	}

	// look for the value in the mapping table after linear transformation
	for (UINT i = 0; i < width * height; i++)
	{
		int x = pixel[i * 4];

		tempPixel[i * 4] = tempPixel[i * 4 + 1] = tempPixel[i * 4 + 2] = map[x];
		tempPixel[i * 4 + 3] = 255;
	}
}