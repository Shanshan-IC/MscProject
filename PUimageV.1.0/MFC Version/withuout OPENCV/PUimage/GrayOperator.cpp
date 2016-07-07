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

