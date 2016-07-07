#include "Brightness.h"
#include "StdAfx.h"
#include "opencv2/highgui/highgui.hpp"

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>

using namespace cv;
using namespace std;

void autoBrightContrast(int alpha, int beta)
{
	Mat image = imread("D:\\3.png");
	Mat new_image = Mat::zeros(image.size(), image.type());

	//double alpha = 2.2;
	//int beta = 50;

	/// Do the operation new_image(i,j) = alpha*image(i,j) + beta
	for (int y = 0; y < image.rows; y++)
	{
		for (int x = 0; x < image.cols; x++)
		{
			for (int c = 0; c < 3; c++)
			{
				new_image.at<Vec3b>(y, x)[c] =
					saturate_cast<uchar>(alpha*(image.at<Vec3b>(y, x)[c]) + beta);
			}
		}
	}

	/// Create Windows
	namedWindow("Original Image", 1);
	namedWindow("New Image", 1);

	/// Show stuff
	imshow("Original Image", image);
	imshow("New Image", new_image);

	/// Wait until user press some key
	waitKey();
}// Brightness.cpp : implementation file
//