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
bool buildGaussianPyramid(const Mat &img, const int levels,vector<Mat> &pyramid);//color

void reconImgFromLaplacianPyramid(const vector<Mat> &pyramid, const int levels, Mat &dst);
void upsamplingFromGaussianPyramid(const Mat &src, const int levels, Mat &dst);

void temporalIIRFilter(const Mat &src, Mat &dst);
void amplify(const Mat &src, Mat &dst);
void attenuate(Mat &src, Mat &dst);

void motion();
void color();