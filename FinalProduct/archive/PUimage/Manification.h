#pragma once

/*************************************Includes ******************************/
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <list>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/opencv.hpp"
/****************************************************************************/
#define OUTPUT_FILE	"Video_Magnified.avi"
#define OUT_WINDOW	"After Eulerian Magnification Window"


using namespace cv;
using namespace std;


class Manification
{
private:
	int alpha;
	float lambda_c;
	float fl;
	float fh;
	float chromAttenuation;
	
		

public:
	Manification(int _alpha, float _lambda_c, float _fl, float _fh, float _chromAttenuation);
	~Manification();

	float delta = 0;
	float lambda = 0;
	int levels = 5;
	int length = 0;
	double rate = 22;
	std::vector<cv::Mat> lowpass1;
	std::vector<cv::Mat> lowpass2;
	int curLevel = 0;
	float exaggeration_factor = 3.0;

	void test();
	bool buildGaussianPyramid(const Mat &img, const int levels, vector<Mat> &pyramid);
	bool buildLaplacianPyramid(const Mat &img, const int levels, vector<Mat> &pyramid);
	void concat(const vector<Mat> &frames, Mat &dst);
	void createIdealBandpassFilter(cv::Mat &filter, double fl, double fh, double rate);
	void temporalIdealFilter(const Mat &src, Mat &dst);
	void deConcat(const Mat &src, const Size &frameSize, vector<cv::Mat> &frames);
	void amplify2(const Mat &src, Mat &dst);
	void upsamplingFromGaussianPyramid(const Mat &src, const int levels, Mat &dst);
	void reconImgFromLaplacianPyramid(const std::vector<cv::Mat> &pyramid, const int levels,cv::Mat &dst);
	void colorManification(const string& filename);

};

