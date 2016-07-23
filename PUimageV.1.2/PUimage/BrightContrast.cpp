#include "BrightContrast.h"

#include "StdAfx.h"
#include "opencv2/highgui/highgui.hpp"

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>

using namespace cv;
using namespace std;

cv::Mat autoBrightContrast(cv::Mat image, int alpha, int beta)
{
	//initial the same size and type of original image
	cv::Mat new_image = Mat::zeros(image.size(), image.type());

	for (int y = 0; y < image.rows; y++)
	{
		for (int x = 0; x < image.cols; x++)
		{
			for (int c = 0; c < 3; c++)
			{
				/// Do the operation new_image(i,j) = alpha*image(i,j) + beta
				//only consider 3 channel image with BGR color 
				new_image.at<Vec3b>(y, x)[c] =
					saturate_cast<uchar>(alpha*(image.at<Vec3b>(y, x)[c]) + beta); 
					//saturate_cast is to make sure the value is valid
			}
		}
	}
	return new_image;
}// Brightness.cpp : implementation file
//