#include "Histogram.h"
#include "StdAfx.h"



#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"

#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;


byte * matToBytes(Mat image)
{
	int size = image.total() * image.elemSize();
	byte * bytes = new byte[size];  // you will have to delete[] that later
	std::memcpy(bytes, image.data, size * sizeof(byte));
	return bytes;
}


void HistogramEqualization(BYTE* image0, BYTE* image1, unsigned int w, unsigned int h)
{
	//convert the array to mattrix
	/*
	Mat image0Mat = Mat(w, h, CV_8UC3, image0).clone();
	Mat image1Mat = Mat(w, h, CV_8UC3, image1).clone();
	imshow("1", image1Mat);
	imshow("2", image0Mat);
	/// Convert to grayscale
	cvtColor(image0Mat, image0Mat, CV_BGR2GRAY);

	/// Apply Histogram Equalization
	equalizeHist(image0Mat, image1Mat);

	char* equalized_window = "Equalized Image";
	namedWindow(equalized_window, CV_WINDOW_AUTOSIZE);
	imshow(equalized_window, image1Mat);
	waitKey(0);*/

	Mat dst;

	/// Load image
	Mat img = cv::imread("D:\\3.png");
	vector<Mat> channels;
	Mat img_hist_equalized;

	cvtColor(img, img_hist_equalized, CV_BGR2YCrCb); //change the color image from BGR to YCrCb format

	split(img_hist_equalized, channels); //split the image into channels

	equalizeHist(channels[0], channels[0]); //equalize histogram on the 1st channel (Y)

	merge(channels, img_hist_equalized); //merge 3 channels including the modified 1st channel into one image

	cvtColor(img_hist_equalized, img_hist_equalized, CV_YCrCb2BGR); //change the color image from YCrCb to BGR format (to display image properly)

	//create windows
	namedWindow("Original Image", CV_WINDOW_AUTOSIZE);
	namedWindow("Histogram Equalized", CV_WINDOW_AUTOSIZE);

	//show the image
	imshow("Original Image", img);
	imshow("Histogram Equalized", img_hist_equalized);

	waitKey(0); //wait for key press

	destroyAllWindows(); //destroy all open windows

}


void HistogramEqualizationContrast(BYTE* image0, BYTE* image1, unsigned int w, unsigned int h)
{
	//Mat img = imread("D:\\3.png"); //input image

	// READ RGB color image and convert it to Lab
	cv::Mat bgr_image = cv::imread("D:\\3.png");
	cv::Mat lab_image;
	cv::cvtColor(bgr_image, lab_image, CV_BGR2Lab);

	// Extract the L channel
	std::vector<cv::Mat> lab_planes(3);
	cv::split(lab_image, lab_planes);  // now we have the L image in lab_planes[0]

	// apply the CLAHE algorithm to the L channel
	cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
	clahe->setClipLimit(4);
	cv::Mat dst;
	clahe->apply(lab_planes[0], dst);

	// Merge the the color planes back into an Lab image
	dst.copyTo(lab_planes[0]);
	cv::merge(lab_planes, lab_image);

	// convert back to RGB
	cv::Mat image_clahe;
	cv::cvtColor(lab_image, image_clahe, CV_Lab2BGR);

	// display the results  (you might also want to see lab_planes[0] before and after).
	cv::imshow("image original", bgr_image);
	cv::imshow("image CLAHE", image_clahe);
	cv::waitKey();
}