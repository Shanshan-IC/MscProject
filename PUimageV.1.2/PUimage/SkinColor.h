#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
bool R1(int R, int G, int B);
bool R2(float Y, float Cr, float Cb);
bool R3(float H, float S, float V);
Mat GetSkin(Mat const &src);
