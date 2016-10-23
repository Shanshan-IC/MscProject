 /*************************  Includes  *******************************/
#include "stdafx.h"
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
#include "Motion.h"
/********************************************************************/

using namespace cv;
using namespace std;

// Change the file/path definitions to actual files/path names
#define INPUT_FILE	"face.mp4"
#define OUTPUT_FILE	"Video_Magnified.avi"
#define OUT_WINDOW	"Output Window"
#define INT_WINDOW "Input Window"



/*************************  Variables  *******************************/
using namespace cv;
using namespace std;


float fl = 0.9, fh = 1;
float lambda_c = 80;
int alpha = 80;
float chromAttenuation2 = 0.1;
float exaggeration_factor = 5.0;
float delta = 0;
float lambda = 0;
int levels = 6;
int length = 0;
double rate = 30;
std::vector<cv::Mat> lowpass1;
std::vector<cv::Mat> lowpass2;
int curLevel = 0;

/********************************************************************/


Mat LaplacianPyr(Mat img)
{
	Mat down, up, lap;
	pyrDown(img, down);
	pyrUp(down, up);
	lap = img - up;
	return lap;
}


bool buildLaplacianPyramid(const Mat &img, const int levels, vector<Mat> &pyramid)
{
	if (levels < 1)
	{
		perror("Levels should be larger than 1");
		return false;
	}
	pyramid.clear();
	Mat currentImg = img;
	for (int l = 0; l<levels; l++)
	{
		Mat down, up;
		pyrDown(currentImg, down);
		pyrUp(down, up, currentImg.size());
		Mat lap = currentImg - up;
		pyramid.push_back(lap);
		currentImg = down;
	}
	pyramid.push_back(currentImg);
	return true;
}


void reconImgFromLaplacianPyramid2(const vector<Mat> &pyramid, const int levels, Mat &dst)
{
	Mat currentImg = pyramid[levels];
	for (int l = levels - 1; l >= 0; l--)
	{
		Mat up;
		pyrUp(currentImg, up, pyramid[l].size());
		currentImg = up + pyramid[l];
	}
	dst = currentImg.clone();
}

void upsamplingFromGaussianPyramid(const cv::Mat &src,
	const int levels,
	cv::Mat &dst)
{
	cv::Mat currentLevel = src.clone();
	for (int i = 0; i < levels; ++i) {
		cv::Mat up;
		cv::pyrUp(currentLevel, up);
		currentLevel = up;
	}
	currentLevel.copyTo(dst);
}
void temporalIIRFilter(const Mat &src, Mat &dst)
{
	cv::Mat temp1 = (1 - fh)*lowpass1[curLevel] + fh*src;
	cv::Mat temp2 = (1 - fl)*lowpass2[curLevel] + fl*src;
	lowpass1[curLevel] = temp1;
	lowpass2[curLevel] = temp2;
	dst = lowpass1[curLevel] - lowpass2[curLevel];
}


void amplify(const Mat &src, Mat &dst)
{
	float currAlpha;
	//compute modified alpha for this level
	currAlpha = lambda / delta / 8 - 1;
	currAlpha *= exaggeration_factor;
	if (curLevel == levels || curLevel == 0)     // ignore the highest and lowest frequency band
		dst = src * 0;
	else
	{
		int mins = (alpha > currAlpha) ? currAlpha : alpha;
		dst = src * mins;
	}

}

void amplify2(const Mat &src, Mat &dst)
{
	dst = src * alpha;
}

void attenuate(Mat &src, Mat &dst)
{
	Mat planes[3];
	split(src, planes);
	planes[1] = planes[1] * chromAttenuation2;
	planes[2] = planes[2] * chromAttenuation2;
	merge(planes, 3, dst);
}


void motion()
{
	VideoCapture cap(INPUT_FILE);
	if (!cap.isOpened())
	{
		cout << "Error!! Unable to open input video file" << std::endl;
		getchar();
		return;
	}

	cvNamedWindow(OUT_WINDOW, CV_WINDOW_AUTOSIZE);
	cvMoveWindow(OUT_WINDOW, 20, 100);

	//cvSetMouseCallback(OUT_WINDOW, mouseEvent);

	Mat org, frame;
	Mat motion;
	Mat output;
	vector<Mat> pyramid;
	vector<Mat> filtered;

	Size czpSz = Size(cap.get(CV_CAP_PROP_FRAME_WIDTH), cap.get(CV_CAP_PROP_FRAME_HEIGHT));
	VideoWriter Out_Video;
	Out_Video.open(OUTPUT_FILE, // filename
		CV_FOURCC('M', 'J', 'P', 'G'), // codec to be used
		cap.get(CV_CAP_PROP_FPS),      // frame rate of the video
		czpSz // frame size
		);

	if (!Out_Video.isOpened())
	{
		cout << "Error!! Unable to create output video file" << std::endl;
		getchar();
		return;
	}

	int f_num = 0;
	while (1)
	{
		cap >> org;
		if (org.empty())
			break;

		frame = org.clone();
		frame.convertTo(frame, CV_32FC3, 1.0 / 255.0f);
		cvtColor(frame, frame, CV_BGR2Lab);

		Mat s = frame.clone();
		buildLaplacianPyramid(s, levels, pyramid);

		if (f_num == 0)
		{
			lowpass1 = pyramid;
			lowpass2 = pyramid;
			filtered = pyramid;
		}
		else
		{
			for (int i = 0; i<levels; ++i)
			{
				curLevel = i;
				temporalIIRFilter(pyramid.at(i), filtered.at(i));
			}

			// amplify each spatial frequency bands
			// according to Figure 6 of paper            
			cv::Size filterSize = filtered.at(0).size();
			int w = filterSize.width;
			int h = filterSize.height;

			delta = lambda_c / 8.0 / (1.0 + alpha);
			// the factor to boost alpha above the bound
			// (for better visualization)
			exaggeration_factor = 2.0;

			// compute the representative wavelength lambda
			// for the lowest spatial frequency band of Laplacian pyramid
			lambda = sqrt((float)(w*w + h*h)) / 3;  // 3 is experimental constant

			for (int i = levels; i >= 0; i--)
			{
				curLevel = i;
				amplify(filtered.at(i), filtered.at(i));

				// go one level down on pyramid
				// representative lambda will reduce by factor of 2
				lambda /= 2.0;
			}
		}

		// 4. reconstruct motion image from filtered pyramid
		reconImgFromLaplacianPyramid2(filtered, levels, motion);

		// 5. attenuate I, Q channels
		attenuate(motion, motion);

		// 6. combine source frame and motion image
		if (f_num > 0)    // don't amplify first frame
			s += motion;

		// 7. convert back to rgb color space and CV_8UC3
		output = s.clone();
		cvtColor(output, output, CV_Lab2BGR);
		output.convertTo(output, CV_8UC3, 255.0, 1.0 / 255.0);

		imshow(OUT_WINDOW, output);
		
		Out_Video.write(output);
		cout << f_num++;

		char c = waitKey(1);
		if (c == 27)
			break;
	}
}


void color()
{
	VideoCapture cap(INPUT_FILE);
	if (!cap.isOpened())
	{
		cout << "Error!! Unable to open input video file" << std::endl;
		getchar();
		return;
	}
	cv::Mat input, org, videoMat, downSampledFrame, downSampledMat, filteredMat, filteredFrame, filtered;
	cv::Mat output;
	Size czpSz = Size(cap.get(CV_CAP_PROP_FRAME_WIDTH), cap.get(CV_CAP_PROP_FRAME_HEIGHT));
	//Size czpSz = Size(320, 240);
	VideoWriter Out_Video;
	Out_Video.open(OUTPUT_FILE, // filename
		CV_FOURCC('M', 'J', 'P', 'G'), // codec to be used
		cap.get(CV_CAP_PROP_FPS),      // frame rate of the video
		czpSz // frame size
		);
	if (!Out_Video.isOpened())
	{
		cout << "Error!! Unable to create output video file" << std::endl;
		getchar();
		return;
	}
	while (1) {
		cap >> org;
		if (org.empty())
			break;
		length++;
	}

	VideoCapture cap_temp(INPUT_FILE);
	vector <Mat> frames, downSampledFrames, filteredFrames;
	while (1) {
		cap_temp >> org;
		if (org.empty())
			break;

		input = org.clone();
		input.convertTo(input, CV_32FC3);
		frames.push_back(input.clone());
		// spatial filtering
		std::vector<cv::Mat> pyramid;
		buildGaussianPyramid(input,levels, pyramid);
		downSampledFrames.push_back(pyramid.at(levels - 1));
	}

	// 2. concat all the frames into a single large Mat
	// where each column is a reshaped single frame
	// (for processing convenience)
	concat(downSampledFrames, videoMat);

	// 3. temporal filtering
	temporalIdealFilter(videoMat, filtered);

	// 4. amplify color motion
	amplify2(filtered, filtered);

	// 5. de-concat the filtered image into filtered frames
	deConcat(filtered, downSampledFrames.at(0).size(), filteredFrames);

	// 6. amplify each frame
	// by adding frame image and motions
	// and write into video
	Mat temp, motion;
	for (int i = 0; i<length - 1; ++i) {
		// up-sample the motion image        
		upsamplingFromGaussianPyramid(filteredFrames.at(i), levels, motion);
		resize(motion, motion, frames.at(i).size());
		temp = frames.at(i) + motion;
		output = temp.clone();
		double minVal, maxVal;
		minMaxLoc(output, &minVal, &maxVal); //find minimum and maximum intensities
		output.convertTo(output, CV_8UC3, 255.0 / (maxVal - minVal),
			-minVal * 255.0 / (maxVal - minVal));
		
		imshow(OUT_WINDOW, output);
		Out_Video.write(output);
		char c = waitKey(1);
		if (c == 27)
			break;
	}

} 


bool buildGaussianPyramid(const cv::Mat &img,
	const int levels,
	std::vector<cv::Mat> &pyramid)
{
	if (levels < 1){
		perror("Levels should be larger than 1");
		return false;
	}
	pyramid.clear();
	cv::Mat currentImg = img;
	for (int l = 0; l<levels; l++) {
		cv::Mat down;
		cv::pyrDown(currentImg, down);
		pyramid.push_back(down);
		currentImg = down;
	}
	return true;
}

void concat(const std::vector<cv::Mat> &frames,
	cv::Mat &dst)
{
	cv::Size frameSize = frames.at(0).size();
	cv::Mat temp(frameSize.width*frameSize.height, length - 1, CV_32FC3);
	for (int i = 0; i < length - 1; ++i) {
		// get a frame if any
		cv::Mat input = frames.at(i);
		// reshape the frame into one column
		cv::Mat reshaped = input.reshape(3, input.cols*input.rows).clone();
		cv::Mat line = temp.col(i);
		// save the reshaped frame to one column of the destinate big image
		reshaped.copyTo(line);
	}
	temp.copyTo(dst);
}

void temporalIdealFilter(const cv::Mat &src,
	cv::Mat &dst)
{
	cv::Mat channels[3];

	// split into 3 channels
	cv::split(src, channels);

	for (int i = 0; i < 3; ++i){

		cv::Mat current = channels[i];  // current channel
		cv::Mat tempImg;

		int width = cv::getOptimalDFTSize(current.cols);
		int height = cv::getOptimalDFTSize(current.rows);

		cv::copyMakeBorder(current, tempImg,
			0, height - current.rows,
			0, width - current.cols,
			cv::BORDER_CONSTANT, cv::Scalar::all(0));

		// do the DFT
		cv::dft(tempImg, tempImg, cv::DFT_ROWS | cv::DFT_SCALE);

		// construct the filter
		cv::Mat filter = tempImg.clone();
		createIdealBandpassFilter(filter, fl, fh, rate);

		// apply filter
		cv::mulSpectrums(tempImg, filter, tempImg, cv::DFT_ROWS);

		// do the inverse DFT on filtered image
		cv::idft(tempImg, tempImg, cv::DFT_ROWS | cv::DFT_SCALE);

		// copy back to the current channel
		tempImg(cv::Rect(0, 0, current.cols, current.rows)).copyTo(channels[i]);
	}
	// merge channels
	cv::merge(channels, 3, dst);

	// normalize the filtered image
	cv::normalize(dst, dst, 0, 1, CV_MINMAX);
}

void createIdealBandpassFilter(cv::Mat &filter, double fl, double fh, double rate)
{
	int width = filter.cols;
	int height = filter.rows;

	fl = 2 * fl * width / rate;
	fh = 2 * fh * width / rate;

	double response;

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			// filter response
			if (j >= fl && j <= fh)
				response = 1.0f;
			else
				response = 0.0f;
			filter.at<float>(i, j) = response;
		}
	}
}

void deConcat(const cv::Mat &src,
	const cv::Size &frameSize,
	std::vector<cv::Mat> &frames)
{
	for (int i = 0; i < length - 1; ++i) {    // get a line if any
		cv::Mat line = src.col(i).clone();
		cv::Mat reshaped = line.reshape(3, frameSize.height).clone();
		frames.push_back(reshaped);
	}
}
