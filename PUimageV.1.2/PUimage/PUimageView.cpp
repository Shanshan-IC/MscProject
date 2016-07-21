// PUimageView.cpp : implementation of the CPUimageView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PUimage.h"
#endif

#include "PUimageDoc.h"
#include "PUimageView.h"


#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"

#include "ContrastDlg.h"
#include "BrightDlg.h"
#include "EulerianDlg.h"
#include "RotateDlg.h"
#include "ResizeDlg.h"
#include "PrevDlg.h"
#include "BrightContrast.h"
#include "SkinColor.h"
#include "Motion.h"
#include "AddFunct.h"
#include "VideoPlay.h"

#include "opencv2/opencv.hpp"
#include "VideoProcessor.h"

using namespace cv;
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPUimageView

IMPLEMENT_DYNCREATE(CPUimageView, CView)

BEGIN_MESSAGE_MAP(CPUimageView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_HISTOGRAM_EQULIZATION, &CPUimageView::OnHistogramEqulization)
	ON_COMMAND(ID_PROCESS_CONTRAST, &CPUimageView::OnProcessContrast)
	ON_COMMAND(ID_PROCESS_AUTO, &CPUimageView::OnProcessAuto)
	ON_COMMAND(ID_HISTOGRAM_CONTRASTLIMITEDADAPTIVEEQUALIZAITON, &CPUimageView::OnHistogramContrastlimitedadaptiveequalizaiton)
	ON_COMMAND(ID_FILTER_GAUSSIAN, &CPUimageView::OnFilterGaussian)
	ON_COMMAND(ID_FILTER_MEDIAN, &CPUimageView::OnFilterMedian)
	ON_COMMAND(ID_PROCESS_BRIGHTNESS, &CPUimageView::OnProcessBrightness)
	ON_COMMAND(ID_VIDEO_EULERIAN, &CPUimageView::OnVideoEulerian)
	ON_COMMAND(ID_PREVIEW_PREVIEW, &CPUimageView::OnPreviewPreview)
	ON_COMMAND(ID_PROCESS_SKINDETECT, &CPUimageView::OnProcessSkindetect)
	ON_COMMAND(ID_VIDEO_MOTION, &CPUimageView::OnVideoMotion)
	ON_COMMAND(ID_ADDITION_MORP, &CPUimageView::OnAdditionMorp)
	ON_COMMAND(ID_PROCESS_LAPLACEEDGE, &CPUimageView::OnProcessLaplaceedge)
	ON_COMMAND(ID_DETECT_CRICLEDETECT, &CPUimageView::OnDetectCricledetect)
	ON_COMMAND(ID_DETECT_CANNYEDGEDETECT, &CPUimageView::OnDetectCannyedgedetect)
	ON_COMMAND(ID_DETECT_CORNERDETECT, &CPUimageView::OnDetectCornerdetect)
	ON_COMMAND(ID_DETECT_CASCADECLASSIFIER, &CPUimageView::OnDetectCascadeclassifier)
	ON_COMMAND(ID_IMAGE_ROTATE90, &CPUimageView::OnImageRotate90)
	ON_COMMAND(ID_IMAGE_ROTATE180, &CPUimageView::OnImageRotate180)
	ON_COMMAND(ID_IMAGE_ROTATE, &CPUimageView::OnImageRotate)
	ON_COMMAND(ID_IMAGE_RESIZE, &CPUimageView::OnImageResize)
	ON_COMMAND(ID_IMAGE_ZOOMIN, &CPUimageView::OnImageZoomin)
	ON_COMMAND(ID_IMAGE_ZOOMOUT, &CPUimageView::OnImageZoomout)
	ON_COMMAND(ID_FILTER_BILATERAL, &CPUimageView::OnFilterBilateral)
	ON_COMMAND(ID_FILTER_NORMALIZEDBLOCK, &CPUimageView::OnFilterNormalizedblock)
	ON_COMMAND(ID_VIDEO_IMAGE2VIDEO, &CPUimageView::OnVideoImage2video)
	ON_COMMAND(ID_VIDEO_TEST, &CPUimageView::OnVideoTest)
	ON_COMMAND(ID_VIDEO_EULERIANVIDEOMAGNIFICATION, &CPUimageView::OnVideoEulerianvideomagnification)
END_MESSAGE_MAP()

// CPUimageView construction/destruction

CPUimageView::CPUimageView()
{
	// TODO: add construction code here

}

CPUimageView::~CPUimageView()
{
}

BOOL CPUimageView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CPUimageView drawing

void CPUimageView::OnDraw(CDC* pDC)
{
	CPUimageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CvvImage & img = pDoc->m_image;
	
	CRect r;
	GetClientRect(&r);
	img.DrawToHDC(pDC->GetSafeHdc(), r);
}


// CPUimageView printing

BOOL CPUimageView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPUimageView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPUimageView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CPUimageView diagnostics

#ifdef _DEBUG
void CPUimageView::AssertValid() const
{
	CView::AssertValid();
}

void CPUimageView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPUimageDoc* CPUimageView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPUimageDoc)));
	return (CPUimageDoc*)m_pDocument;
}
#endif //_DEBUG


// CPUimageView message handlers

void CPUimageView::OnHistogramEqulization()
{
	CPUimageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	Mat img = pDoc->matImg;
	Mat dst;

	vector<Mat> channels;
	Mat img_hist_equalized;

	cvtColor(img, img_hist_equalized, CV_BGR2YCrCb); //change the color image from BGR to YCrCb format

	split(img_hist_equalized, channels); //split the image into channels

	equalizeHist(channels[0], channels[0]); //equalize histogram on the 1st channel (Y)

	merge(channels, img_hist_equalized); //merge 3 channels including the modified 1st channel into one image

	cvtColor(img_hist_equalized, img_hist_equalized, CV_YCrCb2BGR); //change the color image from YCrCb to BGR format (to display image properly)


	IplImage temp = img_hist_equalized;
	CvvImage cimg;
	cimg.CopyOf(&temp);

	CPrevDlg dlg;
	dlg.m_image = cimg;
	dlg.DoModal();
	waitKey(0);

}


void CPUimageView::OnProcessContrast()
{
	CPUimageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CContrastDlg dlg;
	Mat src = pDoc->matImg;
	dlg.m_mat = src;
	dlg.DoModal();

	
}


void CPUimageView::OnProcessAuto()
{
	CPUimageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	Mat mats = pDoc->matImg;
	Mat new_mats = autoBrightContrast(mats, 2, 20);
	IplImage img = new_mats;
	CvvImage cimg;
	cimg.CopyOf(&img);

	CPrevDlg dlg;
	dlg.m_image = cimg;
	dlg.DoModal();
	waitKey(0);
}


void CPUimageView::OnHistogramContrastlimitedadaptiveequalizaiton()
{
	CPUimageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	Mat bgr_image = pDoc->matImg;

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

	IplImage temp = image_clahe;
	CvvImage cimg;
	cimg.CopyOf(&temp);

	CPrevDlg dlg;
	dlg.m_image = cimg;
	dlg.DoModal();
	waitKey(0);

}


void CPUimageView::OnFilterGaussian()
{
	CPUimageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	Mat src = pDoc->matImg;
	Mat dst;
	
	GaussianBlur(src, dst, Size(5, 5), 0, 0);
	IplImage img = dst;
	CvvImage cimg;
	cimg.CopyOf(&img);

	CPrevDlg dlg;
	dlg.m_image = cimg;
	dlg.DoModal();
	waitKey(0);
}


void CPUimageView::OnFilterMedian()
{
	
	CPUimageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	Mat src = pDoc->matImg;

	Mat dst;
	medianBlur(src, dst, 15);

	IplImage img = dst;
	CvvImage cimg;
	cimg.CopyOf(&img);

	CPrevDlg dlg;
	dlg.m_image = cimg;
	dlg.DoModal();
	waitKey(0);
}

void CPUimageView::OnProcessBrightness()
{
	CPUimageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CBrightDlg dlg;
	Mat src = pDoc->matImg;
	dlg.m_mat = src;
	dlg.DoModal();
}


void CPUimageView::OnVideoEulerian()
{
	CEulerianDlg dlg;
	dlg.DoModal();
}


void CPUimageView::OnPreviewPreview()
{
	CPUimageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CPrevDlg dlg;
	dlg.m_image = pDoc->m_image;
	dlg.DoModal();
}


void CPUimageView::OnProcessSkindetect()
{
	// Load image & get skin proportions:
	CPUimageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CBrightDlg dlg;
	Mat image = pDoc->matImg;
	Mat skin = GetSkin(image);

	// Show the results:
	namedWindow("original");
	namedWindow("skin");

	imshow("original", image);
	imshow("skin", skin);

	waitKey(0);
	return;
}


void CPUimageView::OnVideoMotion()
{
	color();
}


void CPUimageView::OnAdditionMorp()
{
	// TODO: Add your command handler code here
}



void CPUimageView::OnProcessLaplaceedge()
{
	Mat src, src_gray, dst;
	int kernel_size = 5;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	int c;

	// Load image & get skin proportions:
	CPUimageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	src = pDoc->matImg;
	if (!src.data)
		return;

	/// Remove noise by blurring with a Gaussian filter
	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);

	/// Convert the image to grayscale
	cvtColor(src, src_gray, CV_BGR2GRAY);
	/// Apply Laplace function
	Mat abs_dst;

	Laplacian(src_gray, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(dst, abs_dst);
	IplImage img = abs_dst;
	CvvImage cimg;
	cimg.CopyOf(&img);

	CPrevDlg dlg;
	dlg.m_image = cimg;
	dlg.DoModal();
	waitKey(0);

}


void CPUimageView::OnDetectCricledetect()
{
	CPUimageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	Mat src = pDoc->matImg;
	if (!src.data)
		return;
	Mat src_gray;
	cvtColor(src, src_gray, CV_BGR2GRAY);

	/// Reduce the noise so we avoid false circle detection
	GaussianBlur(src_gray, src_gray, Size(9, 9), 2, 2);

	vector<Vec3f> circles;

	/// Apply the Hough Transform to find the circles
	HoughCircles(src_gray, circles, CV_HOUGH_GRADIENT, 1, src_gray.rows / 15, 200, 100, 0, 0);

	/// Draw the circles detected
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		// circle center
		circle(src, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		// circle outline
		circle(src, center, radius, Scalar(0, 0, 255), 3, 8, 0);
	}

	/// Show your results
	namedWindow("Hough Circle Transform Demo", CV_WINDOW_AUTOSIZE);
	imshow("Hough Circle Transform Demo", src);

	waitKey(0);
}


void CPUimageView::OnDetectCannyedgedetect()
{
	Mat src, src_gray;
	Mat dst, detected_edges;

	int edgeThresh = 1;
	int lowThreshold = 0;
	int const max_lowThreshold = 100;
	int ratio = 3;
	int kernel_size = 5;
	char* window_name = "Edge Map";
	CPUimageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	src = pDoc->matImg;
	if (!src.data)
		return;
	/// Create a matrix of the same type and size as src (for dst)
	dst.create(src.size(), src.type());

	/// Convert the image to grayscale
	cvtColor(src, src_gray, CV_BGR2GRAY);

	/// Create a window
	namedWindow(window_name, CV_WINDOW_AUTOSIZE);

	blur(src_gray, detected_edges, Size(3, 3));

	/// Canny detector
	Canny(detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size);

	/// Using Canny's output as a mask, we display our result
	dst = Scalar::all(0);

	src.copyTo(dst, detected_edges);
	imshow(window_name, dst);

	/// Wait until user exit program by pressing a key
	waitKey(0);
}

void CPUimageView::OnDetectCornerdetect()
{
	CPUimageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	Mat src = pDoc->matImg;
	if (!src.data)
		return;
	
	Mat src_gray, myHarris_dst, myHarris_copy, Mc, myShiTomasi_dst;
	double myHarris_minVal; double myHarris_maxVal;
	const char* myHarris_window = "My Harris corner detector";
	const char* myShiTomasi_window = "My Shi Tomasi corner detector";
	double myShiTomasi_minVal = 0.0, myShiTomasi_maxVal=0.0;
	int myShiTomasi_qualityLevel = 50;
	int myHarris_qualityLevel = 50;
	int max_qualityLevel = 100;
	RNG rng(12345);

	cvtColor(src, src_gray, COLOR_BGR2GRAY);

	/// Set some parameters
	int blockSize = 3; int apertureSize = 3;

	/// My Harris matrix -- Using cornerEigenValsAndVecs
	myHarris_dst = Mat::zeros(src_gray.size(), CV_32FC(6));
	Mc = Mat::zeros(src_gray.size(), CV_32FC1);

	cornerEigenValsAndVecs(src_gray, myHarris_dst, blockSize, apertureSize, BORDER_DEFAULT);

	/* calculate Mc */
	for (int j = 0; j < src_gray.rows; j++)
	{
		for (int i = 0; i < src_gray.cols; i++)
		{
			float lambda_1 = myHarris_dst.at<Vec6f>(j, i)[0];
			float lambda_2 = myHarris_dst.at<Vec6f>(j, i)[1];
			Mc.at<float>(j, i) = lambda_1*lambda_2 - 0.04f*pow((lambda_1 + lambda_2), 2);
		}
	}
	namedWindow(myHarris_window, WINDOW_AUTOSIZE);
	minMaxLoc(Mc, &myHarris_minVal, &myHarris_maxVal, 0, 0, Mat());
	myHarris_copy = src.clone();

	if (myHarris_qualityLevel < 1) { myHarris_qualityLevel = 1; }

	for (int j = 0; j < src_gray.rows; j++)
	{
		for (int i = 0; i < src_gray.cols; i++)
		{
			if (Mc.at<float>(j, i) > myHarris_minVal + (myHarris_maxVal - myHarris_minVal)*myHarris_qualityLevel / max_qualityLevel)
			{
				circle(myHarris_copy, Point(i, j), 4, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), -1, 8, 0);
			}
		}
	}
	imshow(myHarris_window, myHarris_copy);

	myShiTomasi_dst = Mat::zeros(src_gray.size(), CV_32FC1);
	cornerMinEigenVal(src_gray, myShiTomasi_dst, blockSize, apertureSize, BORDER_DEFAULT);

	minMaxLoc(myShiTomasi_dst, &myShiTomasi_minVal, &myShiTomasi_maxVal, 0, 0, Mat());

	/* Create Window and Trackbar */
	Mat myShiTomasi_copy = src.clone();

	if (myShiTomasi_qualityLevel < 1) { myShiTomasi_qualityLevel = 1; }

	for (int j = 0; j < src_gray.rows; j++)
	{
		for (int i = 0; i < src_gray.cols; i++)
		{
			if (myShiTomasi_dst.at<float>(j, i) > myShiTomasi_minVal + (myShiTomasi_maxVal - myShiTomasi_minVal)*myShiTomasi_qualityLevel / max_qualityLevel)
			{
				circle(myShiTomasi_copy, Point(i, j), 4, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), -1, 8, 0);
			}
		}
	}
	namedWindow(myShiTomasi_window, WINDOW_AUTOSIZE);
	
	imshow(myShiTomasi_window, myShiTomasi_copy);

	waitKey(0);
}


void CPUimageView::OnDetectCascadeclassifier()
{
	const float scale_factor(1.2f);
	const int min_neighbors(1);

	CPUimageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	Mat img = pDoc->matImg;
	if (!img.data)
		return;
	Mat frame_gray;
	namedWindow("window1", 1);   imshow("window1", img);
	cvtColor(img, frame_gray, COLOR_BGR2GRAY);
	// Load Face cascade (.xml file)
	CascadeClassifier face_cascade;
	
	if (!face_cascade.load("D:\\opencv\\sources\\data\\haarcascades_cuda\\haarcascade_frontalface_alt2.xml")){ printf("--(!)Error loading face cascade\n"); return; };
	equalizeHist(frame_gray, frame_gray);
	vector<Rect> objs;
	face_cascade.detectMultiScale(frame_gray, objs, 2, 1, 0 | CASCADE_SCALE_IMAGE, Size(10, 10));

	Mat img_color = pDoc->matImg;
	for (int n = 0; n < objs.size(); n++) {
		rectangle(img_color, objs[n], Scalar(255, 0, 0), 8);
	}
	imshow("VJ Face Detector", img_color);
	waitKey(0);
}


void CPUimageView::OnImageRotate90()
{
	CPUimageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	Mat src = pDoc->matImg;
	if (!src.data)
		return;

	Mat dst;
	dst = rotate(src, 90);
	IplImage img = dst;
	CvvImage cimg;
	cimg.CopyOf(&img);

	CPrevDlg dlg;
	dlg.m_image = cimg;
	dlg.DoModal();
	waitKey(0);
}


void CPUimageView::OnImageRotate180()
{
	CPUimageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	Mat src = pDoc->matImg;
	if (!src.data)
		return;
	Mat dst;
	dst = rotate(src, 180);
	IplImage img = dst;
	CvvImage cimg;
	cimg.CopyOf(&img);

	CPrevDlg dlg;
	dlg.m_image = cimg;
	dlg.DoModal();
	waitKey(0);
}


void CPUimageView::OnImageRotate()
{
	CPUimageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	Mat src = pDoc->matImg;
	if (!src.data)
		return;
	RotateDlg dlg;
	dlg.m_mat = src;
	dlg.DoModal();
}


void CPUimageView::OnImageResize()
{
	CPUimageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	Mat src = pDoc->matImg;
	if (!src.data)
		return;
	CResizeDlg dlg;
	dlg.m_mat = src;
	dlg.DoModal();
}


void CPUimageView::OnImageZoomin()
{
	CPUimageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	Mat src = pDoc->matImg;
	if (!src.data)
		return;
	Mat dst;
	resize(src, dst, Size(src.cols* 0.7, src.rows * 0.7), 0, 0, INTER_LINEAR);
	IplImage img = dst;
	CvvImage cimg;
	cimg.CopyOf(&img);

	CPrevDlg dlg;
	dlg.m_image = cimg;
	dlg.DoModal();
	waitKey(0);

}


void CPUimageView::OnImageZoomout()
{
	CPUimageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	Mat src = pDoc->matImg;
	if (!src.data)
		return;

	Mat dst;
	resize(src, dst, Size(src.cols* 1.2, src.rows *1.2), 0, 0, INTER_LINEAR);
	IplImage img = dst;
	CvvImage cimg;
	cimg.CopyOf(&img);

	CPrevDlg dlg;
	dlg.m_image = cimg;
	dlg.DoModal();
	waitKey(0);
}


void CPUimageView::OnFilterBilateral()
{
	CPUimageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	Mat src = pDoc->matImg;
	Mat dst;

	bilateralFilter(src, dst, 15, 80, 80);
	IplImage img = dst;
	CvvImage cimg;
	cimg.CopyOf(&img);

	CPrevDlg dlg;
	dlg.m_image = cimg;
	dlg.DoModal();
	waitKey(0);
}

void CPUimageView::OnFilterNormalizedblock()
{
	CPUimageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	Mat src = pDoc->matImg;
	Mat dst;

	blur(src, dst, Size(5, 5), Point(-1, -1));
	IplImage img = dst;
	CvvImage cimg;
	cimg.CopyOf(&img);

	CPrevDlg dlg;
	dlg.m_image = cimg;
	dlg.DoModal();
	waitKey(0);
}


void CPUimageView::OnVideoImage2video()
{
	Size frameSize(1360, 1024);
	VideoCapture sequence("fr%d.jpg");
	Mat img;
	VideoWriter out_capture("video.avi", CV_FOURCC('M', 'J', 'P', 'G'), 30, Size(20, 20));
	while (true)
	{
		sequence >> img;
		if (img.empty())
			break;

		out_capture.write(img);
	}
}


void CPUimageView::OnVideoTest()
{
	CVideoPlay dlg;
	dlg.DoModal();
}


void CPUimageView::OnVideoEulerianvideomagnification()
{
	CVideoPlay dlg;
	dlg.DoModal();
}
