
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//rotate image, return new image after 
Mat rotate(Mat src, double angle)
{
	Mat dst;
	// get rotation matrix for rotating the image around its pt
	Point2f pt(src.cols / 2., src.rows / 2.);
	//rotate angle 
	Mat r = getRotationMatrix2D(pt, angle, 1.0);
	//set the size of the output image
	warpAffine(src, dst, r, Size(src.cols, src.rows)); 
	return dst;
}
