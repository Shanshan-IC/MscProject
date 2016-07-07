#pragma once



void LineTrans(BYTE* pixel, BYTE* tempPixel, UINT width, UINT height, 
			  double slope, double inter);

void LogTrans(BYTE* pixel, BYTE* tempPixel, UINT width, UINT height, 
			  double a, double b);

void PowerTrans(BYTE* pixel, BYTE* tempPixel, UINT width, UINT height, 
				double b, double c, double r);

void ExpTrans(BYTE* pixel, BYTE* tempPixel, UINT width, UINT height, 
			  double a, double b, double c);
