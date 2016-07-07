#include "StdAfx.h"
#include "GeoOperator.h"
#include <algorithm>
using namespace std;
#include <cmath>

#include <iostream>
#include <ctime>

/******************************************************************************
*	Translation transformation
*		pixel		initial pixel array
*		tempPixel	save pixel array
*		width		initial width
*		height		initial height
*		xx			offset x
*		yy			offset y
******************************************************************************/
bool MoveTransNormal(BYTE* pixel, BYTE*& tempPixel, int width, int height,
	int xx, int yy)
{
	// size of output
	int size = width * height * 4;

	tempPixel = new BYTE[size];
	memset(tempPixel, 255, size);

	// whether the offset is reasonable
	if (xx >= width || yy >= height || xx <= -width || yy <= -height)
		return false;

	int		y = 0;							// y after transformation
	BYTE*	copyPixel = NULL;				// point to the initial position
	BYTE*	objPixel = NULL;				// point to the initial position of copied image
	int		copyWidth = width - abs(xx);	// width of copied image

	for (int j = 0; j < height; j++)
	{
		// Point to the inital image j row
		copyPixel = pixel + j * width * 4;

		// modify the position of copied image
		if (xx < 0)
			copyPixel += abs(xx) * 4;

		// calculate the y after transformation
		y = j + yy;

		if (y >= 0 && y < height)
		{
			objPixel = tempPixel + y * width * 4;

			if (xx > 0)
				objPixel += abs(xx) * 4;

			// copy a row picture
			memcpy(objPixel, copyPixel, copyWidth * 4);
		}
	}

	return true;
}

/******************************************************************************
*	Translation transformation
*		pixel		initial pixel array
*		tempPixel	save pixel array
*		width		initial width
*		height		initial height
*		xx			offset x
*		yy			offset y
*		outWidth	[out] width of output
*		outHeight	[out] height of output
******************************************************************************/
void MoveTransSize(BYTE* pixel, BYTE*& tempPixel, int width, int height,
	int xx, int yy, UINT& outWidth, UINT& outHeight)
{
	outWidth = width + abs(xx);
	outHeight = height + abs(yy);

	int size = outWidth * outHeight * 4;

	tempPixel = new BYTE[size];
	memset(tempPixel, 255, size);

	int		x = 0;
	int		y = 0;
	BYTE*	copyPixel = NULL;
	BYTE*	objPixel = NULL;

	if (xx > 0)
		x = xx;
	if (yy > 0)
		y = yy;

	for (int j = 0; j < height; j++)
	{
		copyPixel = pixel + j * width * 4;
		objPixel = tempPixel + y * outWidth * 4 + x * 4;
		y++;

		memcpy(objPixel, copyPixel, width * 4);
	}
}

/******************************************************************************
*	Verticle Mirror transformation
*		pixel		initial pixel array
*		tempPixel	save pixel array
*		width		initial width
*		height		initial height
******************************************************************************/
void HMirrorTrans(BYTE* pixel, BYTE*& tempPixel, int width, int height)
{
	int size = width * height * 4;

	tempPixel = new BYTE[size];
	memset(tempPixel, 255, size);

	int		x = 0;
	int		y = 0;
	BYTE*	copyPixel = NULL;
	BYTE*	objPixel = NULL;

	for (int j = 0; j < height; j++)
	{
		y = j;

		for (int i = 0; i < width; i++)
		{
			x = width - i - 1;

			copyPixel = pixel + j * width * 4 + i * 4;
			objPixel = tempPixel + y * width * 4 + x * 4;
			memcpy(objPixel, copyPixel, 4);
		}
	}
}

/******************************************************************************
*	Level Mirror transformation
*		pixel		initial pixel array
*		tempPixel	save pixel array
*		width		initial width
*		height		initial height
******************************************************************************/
void VMirrorTrans(BYTE* pixel, BYTE*& tempPixel, int width, int height)
{
	int size = width * height * 4;

	tempPixel = new BYTE[size];
	memset(tempPixel, 255, size);

	int		x = 0;
	int		y = 0;
	BYTE*	copyPixel = NULL;
	BYTE*	objPixel = NULL;

	for (int j = 0; j < height; j++)
	{
		y = height - j - 1;

		for (int i = 0; i < width; i++)
		{
			x = i;

			copyPixel = pixel + j * width * 4 + i * 4;
			objPixel = tempPixel + y * width * 4 + x * 4;
			memcpy(objPixel, copyPixel, 4);
		}
	}
}


/******************************************************************************
*	Transposition transformation
*		pixel		initial pixel array
*		tempPixel	save pixel array
*		width		initial width
*		height		initial height
*		xx			offset x
*		yy			offset y
*		outWidth	[out] width of output
*		outHeight	[out] height of output
******************************************************************************/
void Transpose(BYTE* pixel, BYTE*& tempPixel, int width, int height, UINT& outWidth, UINT& outHeight)
{
	//width and height after transformation
	outWidth = (UINT)height;
	outHeight = (UINT)width;

	int size = outWidth * outHeight * 4;

	tempPixel = new BYTE[size];
	memset(tempPixel, 0, size);

	BYTE*	copyPixel = NULL;
	BYTE*	objPixel = NULL;
	int		x = 0;
	int		y = 0;
	int		tempJ = 0;

	for (UINT j = 0; j < outHeight; j++)
	{
		x = j;

		tempJ = j * outWidth * 4;
		for (UINT i = 0; i < outWidth; i++)
		{
			y = i;
			copyPixel = pixel + y * width * 4 + x * 4;
			objPixel = tempPixel + tempJ + i * 4;
			memcpy(objPixel, copyPixel, 4);
		}
	}
}

/******************************************************************************
*	Zoom function(nearest interpolation)
*		pixel		initial pixel array
*		tempPixel	save pixel array
*		width		initial width
*		height		initial height
*		fx			level zoom factor
*		fy			verticle zoom factor
*		outWidth	[out] width of output
*		outHeight	[out] height of output
******************************************************************************/
void ZoomNormal(BYTE* pixel, BYTE*& tempPixel, int width, int height,
	UINT& outWidth, UINT& outHeight, double fx, double fy)
{
	outWidth = (UINT)(width * fx);
	outHeight = (UINT)(height * fy);

	int size = outWidth * outHeight * 4;

	tempPixel = new BYTE[size];
	memset(tempPixel, 255, size);

	BYTE*	copyPixel = NULL;
	BYTE*	objPixel = NULL;
	int		x = 0;
	int		y = 0;
	long	tempY;
	long	tempJ;

	for (UINT j = 0; j < outHeight; j++)
	{
		//get the nearest y
		y = (int)(j / fy + 0.5);

		// modify y
		if (y >= height)
			y--;

		tempY = y * width * 4;
		tempJ = j * outWidth * 4;

		for (UINT i = 0; i < outWidth; i++)
		{
			//get the nearest x
			x = (int)(i / fx + 0.5);

			// modify x
			if (x >= width)
				x--;
			copyPixel = pixel + tempY + x * 4;
			objPixel = tempPixel + tempJ + i * 4;
			memcpy(objPixel, copyPixel, 4);
		}
	}
}


/******************************************************************************
*	Zoom function(bothway interpolation)
*		pixel		initial pixel array
*		tempPixel	save pixel array
*		width		initial width
*		height		initial height
*		fx			level zoom factor
*		fy			verticle zoom factor
*		outWidth	[out] width of output
*		outHeight	[out] height of output
******************************************************************************/
void ZoomInterpolation(BYTE* pixel, BYTE*& tempPixel, int width, int height,
	UINT& outWidth, UINT& outHeight, double fx, double fy)
{

	outWidth = (UINT)(width * fx + 0.5);
	outHeight = (UINT)(height * fy + 0.5);

	int size = outWidth * outHeight * 4;

	tempPixel = new BYTE[size];
	memset(tempPixel, 255, size);

	BYTE*	copyPixel = NULL;
	BYTE*	objPixel = NULL;
	double	x = 0.0;
	double	y = 0.0;
	long	tempJ = 0;

	for (UINT j = 0; j < outHeight; j++)
	{
		y = j / fy;
		tempJ = j * outWidth * 4;

		for (UINT i = 0; i < outWidth; i++)
		{
			x = i / fx;
			objPixel = tempPixel + tempJ + i * 4;

			int	x1, x2, y1, y2;

			x1 = (int)x;
			x2 = x1 + 1;
			y1 = (int)y;
			y2 = y1 + 1;

			BYTE clr1, clr2, clr3, clr4;
			double u, v;

			u = x - x1;
			v = y - y1;

			for (int k = 0; k < 3; k++)
			{

				if ((x >= width - 1) && (y >= height - 1))
				{
					clr1 = pixel[(y1 * width + x1) * 4 + k];	// (x1, y1)
					objPixel[k] = clr1;
				}
				else if (x >= width - 1)
				{
					clr1 = pixel[(y1 * width + x1) * 4 + k];	// (x1, y1)
					clr3 = pixel[(y2 * width + x1) * 4 + k];	// (x1, y2)
					objPixel[k] = (BYTE)(clr1 * (1 - v) + clr3 * v);
				}
				else if (y >= height - 1)
				{
					clr1 = pixel[(y1 * width + x1) * 4 + k];	// (x1, y1)
					clr2 = pixel[(y1 * width + x2) * 4 + k];	// (x2, y1)
					objPixel[k] = (BYTE)(clr1 * (1 - u) + clr2 * u);
				}
				else
				{
					clr1 = pixel[(y1 * width + x1) * 4 + k];	// (x1, y1)
					clr2 = pixel[(y1 * width + x2) * 4 + k];	// (x2, y1)
					clr3 = pixel[(y2 * width + x1) * 4 + k];	// (x1, y2)
					clr4 = pixel[(y2 * width + x2) * 4 + k];	// (x2, y2)

					double f1, f2;

					f1 = clr1 * (1 - u) + clr2 * u;
					f2 = clr3 * (1 - u) + clr4 * u;
					objPixel[k] = (BYTE)(f1 * (1 - v) + f2 * v);
				}
			}
		}
	}
}

/******************************************************************************
*	Rotation transformation(Nearest)
*		pixel		initial pixel array
*		tempPixel	save pixel array
*		width		initial width
*		height		initial height
*		outWidth	[out] width of output
*		outHeight	[out] height of output
*		angle		rotate angle
******************************************************************************/
void RotateNormal(BYTE* pixel, BYTE*& tempPixel, int width, int height,
	UINT& outWidth, UINT& outHeight, double angle)
{
	// initial four angle position
	int srcX1, srcX2, srcX3, srcX4;
	int srcY1, srcY2, srcY3, srcY4;

	srcX1 = 0;
	srcY1 = 0;
	srcX2 = width - 1;
	srcY2 = 0;
	srcX3 = 0;
	srcY3 = height - 1;
	srcX4 = width - 1;
	srcY4 = height - 1;

	//calculate sin and cos
	double fSin = sin(angle);
	double fCos = cos(angle);

	// four angles position after rotation
	double tranX1, tranX2, tranX3, tranX4;
	double tranY1, tranY2, tranY3, tranY4;

	tranX1 = fCos * srcX1 + fSin * srcY1;
	tranY1 = -fSin * srcX1 + fCos * srcY1;
	tranX2 = fCos * srcX2 + fSin * srcY2;
	tranY2 = -fSin * srcX2 + fCos * srcY2;
	tranX3 = fCos * srcX3 + fSin * srcY3;
	tranY3 = -fSin * srcX3 + fCos * srcY3;
	tranX4 = fCos * srcX4 + fSin * srcY4;
	tranY4 = -fSin * srcX4 + fCos * srcY3;

	//rotate image size
	outWidth = (UINT)(max(fabs(tranX4 - tranX1), fabs(tranX3 - tranX2)) + 1.5);
	outHeight = (UINT)(max(fabs(tranY4 - tranY1), fabs(tranY3 - tranY2)) + 1.5);

	tempPixel = new BYTE[outWidth * outHeight * 4];
	memset(tempPixel, 255, outWidth * outHeight * 4);

	double num1 = -0.5*outWidth*fCos - 0.5*outHeight*fSin + 0.5*width;
	double num2 = 0.5*outWidth*fSin - 0.5*outHeight*fCos + 0.5*height;

	BYTE*	copyPixel = NULL;
	BYTE*	objPixel = NULL;
	int		x = 0;
	int		y = 0;

	for (long j = 0; j < (long)outHeight; j++)
	{
		for (long i = 0; i < (long)outWidth; i++)
		{
			x = (int)(i * fCos + j * fSin + num1 + 0.5);
			y = (int)(-i * fSin + j * fCos + num2 + 0.5);

			if (x == width)
				x--;
			if (y == height)
				y--;

			copyPixel = pixel + y * width * 4 + x * 4;
			objPixel = tempPixel + j * outWidth * 4 + i * 4;

			if (x >= 0 && x < width && y >= 0 && y < height)
				memcpy(objPixel, copyPixel, 4);
		}
	}
}

/******************************************************************************
*	Rotation transformation(Bothway)
*		pixel		initial pixel array
*		tempPixel	save pixel array
*		width		initial width
*		height		initial height
*		outWidth	[out] width of output
*		outHeight	[out] height of output
*		angle		rotate angle
******************************************************************************/
void RotateInterpolation(BYTE* pixel, BYTE*& tempPixel, int width, int height,
	UINT& outWidth, UINT& outHeight, double angle)
{

	// initial four angle position
	int srcX1, srcX2, srcX3, srcX4;
	int srcY1, srcY2, srcY3, srcY4;

	srcX1 = 0;
	srcY1 = 0;
	srcX2 = width - 1;
	srcY2 = 0;
	srcX3 = 0;
	srcY3 = height - 1;
	srcX4 = width - 1;
	srcY4 = height - 1;

	//calculate sin and cos
	double fSin = sin(angle);
	double fCos = cos(angle);

	// four angles position after rotation
	double tranX1, tranX2, tranX3, tranX4;
	double tranY1, tranY2, tranY3, tranY4;

	tranX1 = fCos * srcX1 + fSin * srcY1;
	tranY1 = -fSin * srcX1 + fCos * srcY1;
	tranX2 = fCos * srcX2 + fSin * srcY2;
	tranY2 = -fSin * srcX2 + fCos * srcY2;
	tranX3 = fCos * srcX3 + fSin * srcY3;
	tranY3 = -fSin * srcX3 + fCos * srcY3;
	tranX4 = fCos * srcX4 + fSin * srcY4;
	tranY4 = -fSin * srcX4 + fCos * srcY3;

	// image size
	outWidth = (UINT)(max(fabs(tranX4 - tranX1), fabs(tranX3 - tranX2)) + 1.5);
	outHeight = (UINT)(max(fabs(tranY4 - tranY1), fabs(tranY3 - tranY2)) + 1.5);

	tempPixel = new BYTE[outWidth * outHeight * 4];
	memset(tempPixel, 255, outWidth * outHeight * 4);

	double num1 = -0.5*outWidth*fCos - 0.5*outHeight*fSin + 0.5*width;
	double num2 = 0.5*outWidth*fSin - 0.5*outHeight*fCos + 0.5*height;

	BYTE*	copyPixel = NULL;
	BYTE*	objPixel = NULL;
	double	x = 0.0;
	double	y = 0.0;
	long	tempJ = 0;

	for (long j = 0; j < (long)outHeight; j++)
	{
		tempJ = j * outWidth * 4;

		for (long i = 0; i < (long)outWidth; i++)
		{
			x = i * fCos + j * fSin + num1;
			y = -i * fSin + j * fCos + num2;

			//over the boundary, then calculate the next pixel
			if (x > width || x < 0 || y > height || y < 0)
				continue;

			objPixel = tempPixel + tempJ + i * 4;

			//nearest four position
			int	x1, x2, y1, y2;

			x1 = (int)x;
			x2 = x1 + 1;
			y1 = (int)y;
			y2 = y1 + 1;
			//pixel of four angles
			BYTE clr1, clr2, clr3, clr4;
			double u, v;

			u = x - x1;
			v = y - y1;

			//calculate the three colors
			for (int k = 0; k < 3; k++)
			{
				// if the position is in the right down corner
				if ((x >= width - 1) && (y >= height - 1))
				{
					clr1 = pixel[(y1 * width + x1) * 4 + k];	// (x1, y1)
					objPixel[k] = clr1;
				}
				// if it is out of the last column
				else if (x >= width - 1)
				{
					clr1 = pixel[(y1 * width + x1) * 4 + k];	// (x1, y1)
					clr3 = pixel[(y2 * width + x1) * 4 + k];	// (x1, y2)
					objPixel[k] = (BYTE)(clr1 * (1 - v) + clr3 * v);
				}
				// if it is out of the last row
				else if (y >= height - 1)
				{
					clr1 = pixel[(y1 * width + x1) * 4 + k];	// (x1, y1)
					clr2 = pixel[(y1 * width + x2) * 4 + k];	// (x2, y1)
					objPixel[k] = (BYTE)(clr1 * (1 - u) + clr2 * u);
				}
				else
				{
					clr1 = pixel[(y1 * width + x1) * 4 + k];	// (x1, y1)
					clr2 = pixel[(y1 * width + x2) * 4 + k];	// (x2, y1)
					clr3 = pixel[(y2 * width + x1) * 4 + k];	// (x1, y2)
					clr4 = pixel[(y2 * width + x2) * 4 + k];	// (x2, y2)

					double f1, f2;

					f1 = clr1 * (1 - u) + clr2 * u;
					f2 = clr3 * (1 - u) + clr4 * u;
					objPixel[k] = (BYTE)(f1 * (1 - v) + f2 * v);
				}
			}
		}
	}
}