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
#include <propkey.h>

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
#include "afxwin.h"

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
	ON_COMMAND(ID_PROCESS_LAPLACEEDGE, &CPUimageView::OnProcessLaplaceedge)
	//ON_COMMAND(ID_DETECT_CRICLEDETECT, &CPUimageView::OnDetectCricledetect)
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
	ON_COMMAND(ID_VIDEO_EULERIANVIDEOMAGNIFICATION, &CPUimageView::OnVideoEulerianvideomagnification)
	ON_COMMAND(ID_HISTOGRAM_RGBHISTOGRAM, &CPUimageView::OnHistogramRgbhistogram)
	ON_COMMAND(ID_DETECT_COLORDETECT, &CPUimageView::OnDetectColordetect)
	ON_COMMAND(ID_PROCESS_SOBEL, &CPUimageView::OnProcessSobel)
	ON_COMMAND(ID_DETECT_CIRCLEDETECT, &CPUimageView::OnDetectCircledetect)
	ON_COMMAND(ID_VIDEO_TEST32813, &CPUimageView::OnVideoTest32813)
END_MESSAGE_MAP()

// CPUimageView construction/destruction

CPUimageView::CPUimageView()
{
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
	CvvImage & img = pDoc->m_image;
	
	int height = img.Height();
	int width = img.Width();
	
	CRect r = CRect(0,0,width, height);
	pDC->m_hDC;

	BitBlt(pDC->m_hDC, 0, 0, r.Width(), r.Height(), pDC->m_hDC,
		0, 0, SRCCOPY);

	//ReleaseDC();

	//pDC->StretchBlt(r.left, r.top, r.Width(), r.Height(), pDC, 0, 0, 48, 48, SRCCOPY);
	CWnd::SetWindowPos(NULL, 0, 0, r.Width(), r.Height(), SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOMOVE);
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

//image rotate 90 degree
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

//image rotate 180 degree
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

//image rotate degree the user input
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

//image resize based on the ratio the user input
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

//zoom in 1.2 image
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
	resize(src, dst, Size(src.cols* 1.2, src.rows * 1.2), 0, 0, INTER_LINEAR);//a bilinear interpolation
	IplImage img = dst;
	CvvImage cimg;
	cimg.CopyOf(&img);

	CPrevDlg dlg;
	dlg.m_image = cimg;
	dlg.DoModal();
	waitKey(0);

}

//zoom out 0.7 image
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
	resize(src, dst, Size(src.cols* 0.7, src.rows *0.7), 0, 0, INTER_LINEAR);//a bilinear interpolation
	IplImage img = dst;
	CvvImage cimg;
	cimg.CopyOf(&img);

	CPrevDlg dlg;
	dlg.m_image = cimg;
	dlg.DoModal();
	waitKey(0);
}


// image global histogram equlization
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

	//change the color image from BGR to YCrCb format
	cvtColor(img, img_hist_equalized, CV_BGR2YCrCb); 
	//split the image into channels
	split(img_hist_equalized, channels); 
	//equalize histogram on the 1st channel (Y)
	equalizeHist(channels[0], channels[0]); 
	//merge 3 channels including the modified 1st channel into one image
	merge(channels, img_hist_equalized); 
	//change the color image from YCrCb to BGR format (to display image properly)
	cvtColor(img_hist_equalized, img_hist_equalized, CV_YCrCb2BGR); 


	IplImage temp = img_hist_equalized;
	CvvImage cimg;
	cimg.CopyOf(&temp);

	CPrevDlg dlg;
	dlg.m_image = cimg;
	dlg.DoModal();
	waitKey(0);

}

//brightness diaglog
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

//contrast dialog 
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
	//set contrast value as 1.8 and brightness value 50
	Mat new_mats = autoBrightContrast(mats, 1.8, 50);
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
	//transfer rbg to cielab, any color-space with a luminance channel will work fine
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
	// 5 x 5 kernel used in Gaussian smoothing (blurring), Both dimension of the kernel should be positive and odd
	//sigmaX - Standard deviation in X direction. If 0 is used, it will automatically calculated from the kernel size
	//sigmaY - Standard deviation in Y direction.If 0 is used, it will take the same value as the sigmaX.
	GaussianBlur(src, dst, Size(5, 5), 0, 0);
	IplImage img = dst;
	CvvImage cimg;
	cimg.CopyOf(&img);

	CPrevDlg dlg;
	dlg.m_image = cimg;
	dlg.DoModal();
	waitKey(0);
}

//Median filtering is widely used in edge detection algorithms because under certain conditions, it preserves edges while removing noise
void CPUimageView::OnFilterMedian()
{
	
	CPUimageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	Mat src = pDoc->matImg;

	Mat dst;
	medianBlur(src, dst, 15);//size of filter is 15

	IplImage img = dst;
	CvvImage cimg;
	cimg.CopyOf(&img);

	CPrevDlg dlg;
	dlg.m_image = cimg;
	dlg.DoModal();
	waitKey(0);
}

// This filter is able to reduce noise of the image while preserving the edges. 
//The drawback of this type of filter is that it takes longer time to process
void CPUimageView::OnFilterBilateral()
{
	CPUimageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	Mat src = pDoc->matImg;
	Mat dst;

	//Diameter of each pixel neighbourhood is 15, sigma in the color and coordinate space is 80
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

	//ksize is (5,5), anchor is at the middle of the kernel
	blur(src, dst, Size(5, 5), Point(-1, -1));
	IplImage img = dst;
	CvvImage cimg;
	cimg.CopyOf(&img);

	CPrevDlg dlg;
	dlg.m_image = cimg;
	dlg.DoModal();
	waitKey(0);
}

//eulerian dialog
void CPUimageView::OnVideoEulerian()
{
	CEulerianDlg dlg;
	dlg.DoModal();
}

//preview dialog

void CPUimageView::OnPreviewPreview()
{
	
	CPUimageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//AfxGetApp()->OnFileNew();
	//AfxGetMainWnd()->SendMessage(ID_FILE_NEW, NULL);
	//Mat image = pDoc->matImg;
	POSITION pos = AfxGetApp()->GetFirstDocTemplatePosition();
	CDocTemplate* pTemplate = AfxGetApp()->GetNextDocTemplate(pos);
	//pTemplate = AfxGetApp()->GetNextDocTemplate(pos);  //But, I want the second one

	CPUimageDoc* pSim = (CPUimageDoc*)pTemplate->OpenDocumentFile(NULL);  //This create and shows the new document (whose class I called CSimulatorDoc)
	pSim->matImg = pDoc->matImg;
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

void CPUimageView::OnDetectCannyedgedetect()
{
	Mat src, src_gray;
	Mat dst, detected_edges;

	int edgeThresh = 1;
	int lowThreshold = 50;
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


//Eulerian Color manification dialog
void CPUimageView::OnVideoEulerianvideomagnification()
{
	CVideoPlay dlg;
	dlg.DoModal();
}


void CPUimageView::OnHistogramRgbhistogram()
{
	const float scale_factor(1.2f);
	const int min_neighbors(1);

	CPUimageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	Mat src = pDoc->matImg;
	Mat dst;

	if (!src.data)
		return;

	/// Separate the image in 3 places ( B, G and R )
	vector<Mat> bgr_planes;
	split(src, bgr_planes);

	/// Establish the number of bins
	int histSize = 256;

	/// Set the ranges ( for B,G,R) )
	float range[] = { 0, 256 };
	const float* histRange = { range };

	bool uniform = true; bool accumulate = false;

	Mat b_hist, g_hist, r_hist;

	/// Compute the histograms:
	calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);

	// Draw the histograms for B, G and R
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);

	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

	/// Normalize the result to [ 0, histImage.rows ]
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	/// Draw for each channel
	for (int i = 1; i < histSize; i++)
	{
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(b_hist.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(g_hist.at<float>(i))),
			Scalar(0, 255, 0), 2, 8, 0);
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(r_hist.at<float>(i))),
			Scalar(0, 0, 255), 2, 8, 0);
	}

	/// Display
	namedWindow("RGB Histogram", CV_WINDOW_AUTOSIZE);
	imshow("RGB Histogram", histImage);

	waitKey(0);
}


void CPUimageView::OnDetectColordetect()
{
	CPUimageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	Mat bgr_image = pDoc->matImg;

	if (!bgr_image.data)
		return;
	Mat drawing;
	detectarea(bgr_image, drawing);
	/// Show in a window
	namedWindow("Result without the circle", CV_WINDOW_AUTOSIZE);
	imshow("Result without the circle", drawing);
	cv::waitKey(0);
	
}

void CPUimageView::detectarea(Mat bgr_image, Mat& drawing)
{
	cv::Mat orig_image = bgr_image.clone();
	cv::waitKey(0);
	cv::medianBlur(bgr_image, bgr_image, 3);
	//bilateralFilter(bgr_image, bgr_image, 15, 80, 80);
	cv::waitKey(0);

	// Convert input image to HSV
	cv::Mat hsv_image;
	cv::cvtColor(bgr_image, hsv_image, cv::COLOR_BGR2HSV);

	// Threshold the HSV image, keep only the red pixels
	cv::Mat red_hue_image;
	cv::inRange(hsv_image, cv::Scalar(0, 85, 100), cv::Scalar(15, 255, 255), red_hue_image);
	blur(red_hue_image, red_hue_image, Size(3, 3));
	cv::waitKey(0);

	Mat threshold_output;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	/// Detect edges using Threshold
	threshold(red_hue_image, threshold_output, 100, 255, THRESH_BINARY);

	/// Find contours
	findContours(threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));


	/// Approximate contours to polygons + get bounding rects and circles
	vector<vector<Point> > contours_poly(contours.size());
	vector<Rect> boundRect(contours.size());
	vector<Point2f>center(contours.size());
	vector<float>radius(contours.size());

	for (int i = 0; i < contours.size(); i++)
	{
		approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
		boundRect[i] = boundingRect(Mat(contours_poly[i]));
		minEnclosingCircle((Mat)contours_poly[i], center[i], radius[i]);
	}

	RNG rng(12345);
	/// Draw polygonal contour + bonding rects + circles
	drawing = bgr_image.clone();
	for (int i = 0; i< contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours_poly, i, (0, 250, 124), 2, 8, vector<Vec4i>(), 0, Point());
		//rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0);
		circle(drawing, center[i], (int)radius[i], color, 2, 8, 0);
	}


}

void CPUimageView::OnProcessSobel()
{
	CPUimageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	Mat src1 = pDoc->matImg;

	if (!src1.data)
		return;

	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	Mat src_gray, grad;
	cvtColor(src1, src_gray, CV_BGR2GRAY);
	char* window_name = "Sobel Demo - Simple Edge Detector";
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;

	/// Gradient X
	//Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
	Sobel(src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);

	/// Gradient Y
	//Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
	Sobel(src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);

	/// Total Gradient (approximate)
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

	imshow(window_name, grad);

	waitKey(0);
}


void CPUimageView::OnDetectCircledetect()
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
	HoughCircles(src_gray, circles, CV_HOUGH_GRADIENT, 1, src_gray.rows / 15, 100, 20, 0, 0);

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


void CPUimageView::OnInitialUpdate()
{

	CPUimageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CView::OnInitialUpdate();
	CvvImage & img = pDoc->m_image;
	

	CSize sizeTotal;
	if (img.GetImage()){
		int height = img.Height();
		int width = img.Width();
		sizeTotal = CSize(width, height);
	}
	else{
		sizeTotal.cx = sizeTotal.cy = 100;
	}
	//SetScrollSizes(MM_TEXT, sizeTotal);
}


void CPUimageView::OnVideoTest32813()
{

}
