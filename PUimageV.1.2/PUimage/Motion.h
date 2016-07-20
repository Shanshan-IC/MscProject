/*************************  Includes  *******************************/
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <list>
#include "opencv/cv.h"			// Computer Vision Lib Header
#include "opencv/highgui.h"	// HighGUI Vision Lib Header
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"

/********************************************************************/

using namespace cv;
using namespace std;

Mat LaplacianPyr(Mat img);
bool buildLaplacianPyramid(const Mat &img, const int levels, vector<Mat> &pyramid);//motion
void temporalIIRFilter(const Mat &src, Mat &dst);
void amplify(const Mat &src, Mat &dst);
void reconImgFromLaplacianPyramid2(const vector<Mat> &pyramid, const int levels, Mat &dst);
void attenuate(Mat &src, Mat &dst);

void motion();
void color();

bool buildGaussianPyramid(const cv::Mat &img, const int levels, std::vector<cv::Mat> &pyramid);
void temporalIdealFilter(const cv::Mat &src, cv::Mat &dst);
void upsamplingFromGaussianPyramid(const cv::Mat &src, const int levels, cv::Mat &dst);
void amplify2(const Mat &src, Mat &dst);
void createIdealBandpassFilter(cv::Mat &filter, double fl, double fh, double rate);

bool buildGaussianPyramid(const cv::Mat &img,
	const int levels,
	std::vector<cv::Mat> &pyramid);

void concat(const std::vector<cv::Mat> &frames,
	cv::Mat &dst);
void temporalIdealFilter(const cv::Mat &src,
	cv::Mat &dst);
void deConcat(const cv::Mat &src,
	const cv::Size &frameSize,
	std::vector<cv::Mat> &frames);