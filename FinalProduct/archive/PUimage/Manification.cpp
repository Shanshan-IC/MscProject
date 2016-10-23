/*
This opencv/Visual Studio based on realtime application to manify color

Based on the work following, which is based on OpenCV and Qt
	Joseph Pan      <https://github.com/wzpan/QtEVM>

*/

#include "stdafx.h"
#include "Manification.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

//manification construction
Manification::Manification(int _alpha, float _lambda_c, float _fl, float _fh, float _chromAttenuation)
{
	alpha = _alpha;
	lambda_c = _lambda_c;
	fl = _fl;
	fh = _fh;
	chromAttenuation = _chromAttenuation;
}


Manification::~Manification()
{
}


/**
* An image sequence is decomposed into different spatial frequency bands using Gaussian pyramids
* Level of the Gaussian pyramid expanded to size of original image
* The reason why: 
* buildGaussianPyramid	-	construct a gaussian pyramid from a given image
*
* @param img		-	source image
* @param levels	-	levels of the destinate pyramids
* @param pyramid	-	destinate image
*
* @return true if success
*/
bool Manification::buildGaussianPyramid(const Mat &img, const int levels, vector<Mat> &pyramid)
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



bool Manification::buildLaplacianPyramid(const Mat &img, const int levels, vector<Mat> &pyramid)
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



/**
* concat	-	concat all the frames into a single large Mat
*              where each column is a reshaped single frame
* @param frames	-	frames of the video sequence
* @param dst		-	destinate concatnate image
*/
void Manification::concat(const vector<Mat> &frames, Mat &dst)
{
	cv::Size frameSize = frames.at(1).size();
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

void Manification::createIdealBandpassFilter(cv::Mat &filter, double fl, double fh, double rate)
{
	int width = filter.cols;
	int height = filter.rows;

	fl = 2 * fl * width / rate;
	fh = 2 * fh * width / rate;
	//fl = 16;
	//fh = 20;
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

/**
* temporalIdalFilter	-	temporal IIR filtering an image pyramid of concat-frames
* @param pyramid	-	source pyramid of concatenate frames
* @param filtered	-	concatenate filtered result
*/
void Manification::temporalIdealFilter(const Mat &src, Mat &dst)
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
	//imwrite("resres.jpg", dst);
	// normalize the filtered image
	cv::normalize(dst, dst, 0, 1, CV_MINMAX);
}

/**
* deConcat	-	de-concat the concatnate image into frames
*
* @param src       -   source concatnate image
* @param framesize	-	frame size
* @param frames	-	destinate frames
*/
void Manification::deConcat(const Mat &src, const Size &frameSize, vector<cv::Mat> &frames)
{
	for (int i = 0; i < length - 1; ++i)
	{    // get a line if any
		cv::Mat line = src.col(i).clone();
		cv::Mat reshaped = line.reshape(3, frameSize.height).clone();
		frames.push_back(reshaped);
	}
}

/**
* amplify2	-	amplify the image
*
* @param src       -   source image
*/
void Manification::amplify2(const Mat &src, Mat &dst)
{
	dst = src * alpha;
}

/**
* upsamplingFromGaussianPyramid	-	up-sampling an image from gaussian pyramid
*
* @param src		-	source image
* @param levels	-	levels of the pyramid
* @param dst		-	destinate image
*/
void Manification::upsamplingFromGaussianPyramid(const Mat &src, const int levels, Mat &dst)
{
	cv::Mat currentLevel = src.clone();
	for (int i = 0; i < levels; ++i) {
		cv::Mat up;
		cv::pyrUp(currentLevel, up);
		currentLevel = up;
	}
	currentLevel.copyTo(dst);
}

/**
* Color Manification - The main function of eulerian color magnification
*
* @param filename   -  filename of input video
*/
void Manification::colorManification(const string& filename)
{
	//read the input file
	//test();
	
	VideoCapture cap(filename);
	if (!cap.isOpened())
	{
		cout << "Error!! Unable to open input video file" << std::endl;
		getchar();
		return;
	}

	cv::Mat input, org, temp, videoMat, downSampledFrame, downSampledMat, filteredMat, filteredFrame, filtered;
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

	//to get the length
	while (1) {
		cap >> org;
		if (org.empty())
			break;
		length++;
	}

	VideoCapture cap_temp(filename);
	vector <Mat> frames, downSampledFrames, filteredFrames;
	while (1) {
		cap_temp >> input;
		if (input.empty())
			break;

		//input = org.clone();
		input.convertTo(temp, CV_32FC3);
		
		frames.push_back(temp);
		//spatial filtering an image
		std::vector<cv::Mat> pyramid;
		buildGaussianPyramid(temp, levels, pyramid);
		downSampledFrames.push_back(pyramid.at(levels - 1));
	}

	// 2. concat all the frames into a single large Mat
	// where each column is a reshaped single frame (for processing convenience)
	concat(downSampledFrames, videoMat);
	


	// 3. temporal filtering
	temporalIdealFilter(videoMat, filtered);

	// 4. amplify color image
	amplify2(filtered, filtered);

	// 5. de-concat the filtered image into filtered frames
	deConcat(filtered, downSampledFrames.at(0).size(), filteredFrames);


	
	// 6. amplify each frame
	// by adding frame image and motions
	// and write into video
	Mat motion;
	vector <Mat> tempres;
	Mat tempres2;
	int count = 0;
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
		Out_Video.write(output);
		
	
		imshow("The result", output);
		    
		char c = waitKey(1);
		if (c == 27)
			break;
	}

}


void Manification::reconImgFromLaplacianPyramid(const std::vector<cv::Mat> &pyramid,
	const int levels,
	cv::Mat &dst)
{
	cv::Mat currentImg = pyramid[levels];
	for (int l = levels - 1; l >= 0; l--) {
		cv::Mat up;
		cv::pyrUp(currentImg, up, pyramid[l].size());
		currentImg = up + pyramid[l];
	}
	dst = currentImg.clone();
}