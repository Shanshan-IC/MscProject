#include "StdAfx.h"
#include "improve.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#pragma warning ( disable : 4018)

int GetAsh(BYTE** imageBuf, int x, int y)
{
	int clr;
	clr = (imageBuf[y][x * 4] + imageBuf[y][x * 4 + 1]
		+ imageBuf[y][x * 4 + 2]) / 3;
	return clr;
}

/********************************************************
* Transform the pixel to array
********************************************************/
BYTE** CreatImage(BYTE* image, unsigned int width, unsigned int height, int bt = 4)
{
	BYTE** imageBuf = (BYTE**)malloc(sizeof(BYTE*)*(height));
	for (int y = 0; y<height; y++)
	{
		//imageBuf pointer to the index of the frst address of the row
		imageBuf[y] = image + y*width*bt;
	}
	return imageBuf;
}

/**************************************************
* set the pixel gray
**************************************************/
void SetPixelXY(BYTE** imageBuf1, int x, int y, int a)
{
	imageBuf1[y][x * 4] = a;
	imageBuf1[y][x * 4 + 1] = a;
	imageBuf1[y][x * 4 + 2] = a;
	imageBuf1[y][x * 4 + 3] = 255;
}

/**************************************************
* calculate the color neighbor
* imageBuf		object
* w,h			size of image
* templt		model
* tw			region size
* x,y			position of pixel
* cn			0,blue, 1, green, 2, red
**************************************************/
int TempltExcuteCl(BYTE** imageBuf0, int w, int h, int* templt, int tw, int x, int y, int cn)
{
	int i, j;
	int m = 0;                      // calculate the sum
	int px, py;
	//calculate every gray neighbour
	for (i = 0; i<tw; i++)
	{
		for (j = 0; j<tw; j++)
		{
			//calculate where should the model pixel be in the original image 
			py = y - tw / 2 + i;
			px = x - tw / 2 + j;
			//sum
			m += imageBuf0[py][px * 4 + cn] * templt[i*tw + j];
		}
	}
	return m;
}

/**************************************************
* calculate the gray neighbor
* imageBuf		object
* w,h			size of image
* templt		model
* tw			region size
* x,y			position of pixel
**************************************************/
int TempltExcuteAsh(BYTE** imageBuf0, int w, int h,
	int* templt, int tw, int x, int y)
{
	int i, j;
	int m = 0;                      // calculate the sum
	int px, py;
	//calculate every gray neighbour
	for (i = 0; i<tw; i++)
	{
		for (j = 0; j<tw; j++)
		{
			//calculate where should the model pixel be in the original image 
			py = y - tw / 2 + i;
			px = x - tw / 2 + j;
			//sum
			m += GetAsh(imageBuf0, px, py) * templt[i*tw + j];
		}
	}
	return m;
}

/**************************************************
* simple smooth
* image0		original image
* image1		result image after smooth
* w,h			width and height of image
* size			length of smooth
**************************************************/
void SmoothAsh(BYTE* image0, BYTE* image1,
	unsigned int w, unsigned int h, unsigned int size)
{
	//transfter the image to the mattrix 
	BYTE** imageBuf0 = CreatImage(image0, w, h);
	BYTE** imageBuf1 = CreatImage(image1, w, h);
	//define the model
	int* templt;
	int x, y;
	int a;
	int scale;

	//set the model
	templt = new int[size * size];
	for (x = 0; x<size*size; x++)
	{
		templt[x] = 1;
	}
	//set the factor
	scale = size*size;

	//calculate every pixel 
	for (y = size / 2; y<h - size / 2; y++)
	{
		for (x = size / 2; x<w - size / 2; x++)
		{
			a = TempltExcuteAsh(imageBuf0, w, h, templt, size, x, y);
			a /= scale;
			// if it is over
			a = a>255 ? 255 : a;
			a = a<0 ? 0 : a;
			SetPixelXY(imageBuf1, x, y, a);
		}
	}

	//free the buffer
	delete[] templt;
	free(imageBuf0);
	free(imageBuf1);
}

/**************************************************
* simple smooth for color image
* image0		original image
* image1		result image after smooth
* w,h			width and height of image
* size			length of smooth
**************************************************/
void SmoothCl(BYTE* image0, BYTE* image1,
	unsigned int w, unsigned int h, unsigned int size)
{
	//transfter the image to the mattrix 
	BYTE** imageBuf0 = CreatImage(image0, w, h);
	BYTE** imageBuf1 = CreatImage(image1, w, h);
	//define the model
	int* templt;
	int x, y, c;
	int a;
	int scale;

	//set the model
	templt = new int[size * size];
	for (x = 0; x<size*size; x++)
	{
		templt[x] = 1;
	}
	//set the factor
	scale = size*size;

	//calculate every pixel 
	for (y = size / 2; y<h - size / 2; y++)
	{
		for (x = size / 2; x<w - size / 2; x++)
		{
			for (c = 0; c<3; c++)
			{
				a = TempltExcuteCl(imageBuf0, w, h, templt, size, x, y, c);
				a /= scale;
				// if it is over
				a = a>255 ? 255 : a;
				a = a<0 ? 0 : a;
				imageBuf1[y][x * 4 + c] = a;
			}
		}
	}

	//free the buffer
	delete[] templt;
	free(imageBuf0);
	free(imageBuf1);
}

/**************************************************
* Gaussian smooth for color image
* image0		original image
* image1		result image after smooth
* w,h			width and height of image
**************************************************/
void SmoothGaussCl(BYTE* image0, BYTE* image1, unsigned int w, unsigned int h)
{
	//transfter the image to the mattrix 
	BYTE** imageBuf0 = CreatImage(image0, w, h);
	BYTE** imageBuf1 = CreatImage(image1, w, h);
	//define the model
	int templt[9] = { 1,2,1,2,4,2,1,2,1 };
	int x, y, c;
	int a;
	int scale;

	//set the factor
	scale = 16;

	//calculate every pixel
	for (y = 1; y<h - 1; y++)
		for (x = 1; x<w - 1; x++)
			for (c = 0; c<3; c++)
			{
				//deal with the neighbour based on gaussian model
				a = TempltExcuteCl(imageBuf0, w, h, templt, 3, x, y, c);
				a /= scale;
				// if it is over
				a = a>255 ? 255 : a;
				a = a<0 ? 0 : a;
				imageBuf1[y][x * 4 + c] = a;
			}

	//free the buffer
	free(imageBuf0);
	free(imageBuf1);
}

/**************************************************
* sort the gray neighbour to Get the value based on the model
* imageBuf		object
* templt		model
* tw			region size
* x,y			position of pixel
**************************************************/
int MedianValueAsh(BYTE** imageBuf0, int w, int h, int* templt, int tw, int x, int y)
{
	int i, j, k;
	int px, py, c;
	int* value;                //save the value
	int count;                 //save the number of pixel
	value = new int[tw*tw];
	k = 0;
	//get the gray value from the sample windows
	for (i = 0; i<tw; i++)
	{
		for (j = 0; j<tw; j++)
		{
			py = y - tw / 2 + i;
			px = x - tw / 2 + j;
			// If it is in the windows
			if (templt[i*tw + j]>0)
			{
				//save
				value[k] = GetAsh(imageBuf0, px, py);
				k++;
			}
		}
	}
	//save the number of pixel
	count = k;
	//sort
	for (i = 0; i<count - 1; i++)
	{
		k = i;
		for (j = i + 1; j<count; j++)
			if (value[j]<value[k]) k = j;
		c = value[i];
		value[i] = value[k];
		value[k] = c;
	}
	//get the median
	c = value[count / 2];
	//free the memory
	delete[] value;
	return c;
}

/**************************************************
* median smooth for gray image
* image0		original image
* image1		result image after smooth
* w,h			width and height of image
* size			length of smooth
**************************************************/
void SmoothMedianAsh(BYTE* image0, BYTE* image1, unsigned int w, unsigned int h, unsigned int size)
{
	//transfter the image to the mattrix 
	BYTE** imageBuf0 = CreatImage(image0, w, h);
	BYTE** imageBuf1 = CreatImage(image1, w, h);
	//define the model
	int* templt;
	int x, y;
	int a;
	int scale;

	//set the model
	templt = new int[size * size];
	for (x = 0; x<size*size; x++) templt[x] = 1;

	//set the factor
	scale = 1;

	//calculate every pixel 
	for (y = size / 2; y<h - size / 2; y++)
		for (x = size / 2; x<w - size / 2; x++)
		{
			//Get the median from the sample window
			a = MedianValueAsh(imageBuf0, w, h, templt, size, x, y);
			a /= scale;
			// if it is over
			a = a>255 ? 255 : a;
			a = a<0 ? 0 : a;
			SetPixelXY(imageBuf1, x, y, a);
		}

	//free the buffer
	delete[] templt;
	free(imageBuf0);
	free(imageBuf1);
}

/**************************************************
* get the median
* imageBuf		object
* w,h			size of image
* templt		model
* tw			region size
* x,y			position of pixel
* cn			0,blue, 1, green, 2, red
**************************************************/
int MedianValueCl(BYTE** imageBuf0, int w, int h, int* templt, int tw, int x, int y, int cn)
{
	int i, j, k;
	int px, py, c;
	int* value;                //save the value
	int count;                //save the number of pixel
	value = new int[tw*tw];
	k = 0;
	//get the gray value from the sample windows
	for (i = 0; i<tw; i++)
	{
		for (j = 0; j<tw; j++)
		{
			py = y - tw / 2 + i;
			px = x - tw / 2 + j;
			// If it is in the windows
			if (templt[i*tw + j]>0)
			{
				//save
				value[k] = imageBuf0[py][px * 4 + cn];
				k++;
			}
		}
	}

	count = k;

	vector<int> nums(tw*tw);

	for (int i = 0; i < tw*tw; i++)
		nums[i] = value[i];

	//sort
	sort(nums.begin(), nums.end());

	//get the median
	c = nums[count / 2];
	//free 
	delete[] value;
	return c;
}

/**************************************************
* median smooth
* image0		original image
* image1		result image after smooth
* w,h			width and height of image
* size			length of smooth
**************************************************/
void SmoothMedianCl(BYTE* image0, BYTE* image1, unsigned int w, unsigned int h, unsigned int size)
{
	//transfter the image to the mattrix 
	BYTE** imageBuf0 = CreatImage(image0, w, h);
	BYTE** imageBuf1 = CreatImage(image1, w, h);
	//define the model
	int* templt;
	int x, y, c;
	int a;
	int scale;

	//set the model
	templt = new int[size * size];

	for (x = 0; x<size*size; x++)
	{
		templt[x] = 1;
	}
	//set the factor
	scale = 1;

	//calculate every pixel 
	for (y = size / 2; y<h - size / 2; y++)
	{
		for (x = size / 2; x<w - size / 2; x++)
		{
			for (c = 0; c<3; c++)
			{
				//get the median of gray from the sample window
				a = MedianValueCl(imageBuf0, w, h, templt, size, x, y, c);
				a /= scale;
				// if it is over
				a = a>255 ? 255 : a;
				a = a<0 ? 0 : a;
				imageBuf1[y][x * 4 + c] = a;
			}
		}
	}
	///free the buffer
	delete[] templt;
	free(imageBuf0);
	free(imageBuf1);
}


/**************************************************
* lowpass spatial smooth   scale = 3
* image0		original image
* image1		result image after smooth
* w,h			width and height of image
**************************************************/
void SharpLaplacianAsh(BYTE* image0, BYTE* image1, unsigned int w, unsigned int h)
{
	//transfter the image to the mattrix 
	BYTE** imageBuf0 = CreatImage(image0, w, h);
	BYTE** imageBuf1 = CreatImage(image1, w, h);
	//set the model
	int templt[9] = { -1,-1,-1,-1,8,-1,-1,-1,-1 };
	int x, y;
	int a;
	int scale;

	scale = 3;//set the factor

			  //calculate every pixel 
	for (y = 1; y<h - 1; y++)
		for (x = 1; x<w - 1; x++)
		{
			//based on lowpass spatial model
			a = TempltExcuteAsh(imageBuf0, w, h, templt, 3, x, y);
			a /= scale;
			// enhance the central pixel
			a = GetAsh(imageBuf0, x, y) + a;
			// if it is over
			a = a>255 ? 255 : a;
			a = a<0 ? 0 : a;
			SetPixelXY(imageBuf1, x, y, a);
		}

	//free the buffer
	free(imageBuf0);
	free(imageBuf1);
}

/**************************************************
* lowpass spatial smooth   scale = 3
* image0		original image
* image1		result image after smooth
* w,h			width and height of image
**************************************************/
void SharpLaplacianCl(BYTE* image0, BYTE* image1, unsigned int w, unsigned int h)
{
	//transfter the image to the mattrix 
	BYTE** imageBuf0 = CreatImage(image0, w, h);
	BYTE** imageBuf1 = CreatImage(image1, w, h);
	//define the model
	int templt[9] = { -1,-1,-1,-1,8,-1,-1,-1,-1 };
	int x, y, c;
	int a;
	int scale;

	//set the factor
	scale = 3;

	//calculate every pixel 
	for (y = 1; y<h - 1; y++)
	{
		for (x = 1; x<w - 1; x++)
		{
			for (c = 0; c<3; c++)
			{
				//based on lowpass spatial model
				a = TempltExcuteCl(imageBuf0, w, h, templt, 3, x, y, c);
				a /= scale;
				// enhance the central pixel
				a = imageBuf0[y][x * 4 + c] + a;
				// if it is over
				a = a>255 ? 255 : a;
				a = a<0 ? 0 : a;
				imageBuf1[y][x * 4 + c] = a;
			}
		}
	}
	//free the buffer
	free(imageBuf0);
	free(imageBuf1);
}

void SetPixel(BYTE* image1, unsigned int n, int a)
{
	image1[n] = a;
	image1[n + 1] = a;
	image1[n + 2] = a;
	image1[n + 3] = 255;
}


/**************************************************
* sobel edge  smooth   scale = 0.5
* image0		original image
* image1		result image after smooth
* w,h			width and height of image
* when type is true, get the maxium between the level and
* verticle directory, otherwise to get the median
**************************************************/
void SideSobel(BYTE* image0, BYTE* image1, unsigned int w, unsigned int h, bool type)
{
	int x, y, a, aHr, aHg, aHb, aVr, aVg, aVb, aH, aV;
	long n;
	double scale = 0.5;
	//calculate every pixel 
	for (y = 1; y < h - 1; y++)
		for (x = 1; x < w - 1; x++)
		{
			//calculate the offset
			n = (y*w + x) * 4;
			//gray difference of red level
			aHr = abs((image0[n - w * 4 - 4] + image0[n - 4] * 2 + image0[n + w * 4 - 4])
				- (image0[n - w * 4 + 4] + image0[n + 4] * 2 + image0[n + w * 4 + 4]));
			//gray difference of red verticle
			aVr = abs((image0[n - w * 4 - 4] + image0[n - w * 4] * 2 + image0[n - w * 4 + 4])
				- (image0[n + w * 4 - 4] + image0[n + w * 4] * 2 + image0[n + w * 4 + 4]));
			//gray difference of green level
			aHg = abs((image0[n - w * 4 - 4 + 1] + image0[n - 4 + 1] * 2 + image0[n + w * 4 - 4 + 1])
				- (image0[n - w * 4 + 4 + 1] + image0[n + 4 + 1] * 2 + image0[n + w * 4 + 4 + 1]));
			//gray difference of green verticle
			aVg = abs((image0[n - w * 4 - 4 + 1] + image0[n - w * 4 + 1] * 2 + image0[n - w * 4 + 4 + 1])
				- (image0[n + w * 4 - 4 + 1] + image0[n + w * 4 + 1] * 2 + image0[n + w * 4 + 4 + 1]));
			//gray difference of blue level
			aHb = abs((image0[n - w * 4 - 4 + 2] + image0[n - 4 + 2] * 2 + image0[n + w * 4 - 4 + 2])
				- (image0[n - w * 4 + 4 + 2] + image0[n + 4 + 2] * 2 + image0[n + w * 4 + 4 + 2]));
			//gray difference of blue verticle
			aVb = abs((image0[n - w * 4 - 4 + 2] + image0[n - w * 4 + 2] * 2 + image0[n - w * 4 + 4 + 2])
				- (image0[n + w * 4 - 4 + 2] + image0[n + w * 4 + 2] * 2 + image0[n + w * 4 + 4 + 2]));

			//sum of level
			aH = aHr + aHg + aHb;
			//sum of verticle
			aV = aVr + aVg + aVb;

			if (type)
			{
				//get the mixium one
				if (aH > aV) a = aH;
				else a = aV;
			}
			else
			{
				//get the median
				a = (aH + aV) / 2;
			}
			a = a *scale;
			a = a>255 ? 255 : a;
			//result
			SetPixel(image1, n, a);
		}
}


/**************************************************
* binarization
* image0		original image
* image1		result image after smooth
* w,h			width and height of image
* k				threshold
**************************************************/
void ToTwoValue(BYTE* image0, BYTE* image1, unsigned int w, unsigned int h, int K)
{
	//transfter the image to the mattrix 
	BYTE** imageBuf0 = CreatImage(image0, w, h);
	BYTE** imageBuf1 = CreatImage(image1, w, h);
	int x, y;

	//calculate every pixel 
	for (y = 0; y<h; y++)
		for (x = 0; x<w; x++)
		{
			//If it is a single one, then mark black
			if (GetAsh(imageBuf0, x, y) >= K)
			{
				SetPixelXY(imageBuf1, x, y, 255);
			}
			//otherwise, mark white
			else
			{
				SetPixelXY(imageBuf1, x, y, 0);
			}
		}

	//free the buffer
	free(imageBuf0);
	free(imageBuf1);
}

/**************************************************
* substraction
* image0		original image
* image1		result image after smooth
* w,h			width and height of image
**************************************************/
void Subtract(BYTE* image0, BYTE* image1, unsigned int w, unsigned int h)
{
	//transfter the image to the mattrix 
	BYTE** imageBuf0 = CreatImage(image0, w, h);
	BYTE** imageBuf1 = CreatImage(image1, w, h);
	int x, y;
	int a;

	//calculate every pixel
	for (y = 0; y<h; y++)
		for (x = 0; x<w; x++)
		{
			// Get the gray
			a = GetAsh(imageBuf0, x, y);
			// substraction
			a = a - GetAsh(imageBuf1, x, y);
			// if it is over
			a = a>255 ? 255 : a;
			a = a<0 ? 0 : a;
			SetPixelXY(imageBuf1, x, y, a);
		}

	//free the buffer
	free(imageBuf0);
	free(imageBuf1);
}

/**************************************************
* addition
* image0		original image
* image1		result image after smooth
* w,h			width and height of image
**************************************************/
void AshAdd(BYTE* image0, BYTE* image1, unsigned int w, unsigned int h)
{
	//transfter the image to the mattrix 
	BYTE** imageBuf0 = CreatImage(image0, w, h);
	BYTE** imageBuf1 = CreatImage(image1, w, h);
	int x, y, c;
	int a;

	//calculate every pixel
	for (y = 0; y<h; y++)
		for (x = 0; x<w; x++)
		{
			// Get the gray
			a = GetAsh(imageBuf0, x, y);
			//addition
			a = a + GetAsh(imageBuf1, x, y);
			// if it is over
			a = a>255 ? 255 : a;
			a = a<0 ? 0 : a;
			SetPixelXY(imageBuf1, x, y, a);
		}

	//free the buffer
	free(imageBuf0);
	free(imageBuf1);
}