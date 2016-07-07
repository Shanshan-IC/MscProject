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
#include "BrightContrast.h"
#include "SkinColor.h"
#include "Motion.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace cv;
using namespace std;
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
	ON_COMMAND(ID_FILTER_LAPLACIANSHARPEN, &CPUimageView::OnFilterLaplaciansharpen)
	ON_COMMAND(ID_PROCESS_BRIGHTNESS, &CPUimageView::OnProcessBrightness)
	ON_COMMAND(ID_VIDEO_EULERIAN, &CPUimageView::OnVideoEulerian)
	ON_COMMAND(ID_PREVIEW_PREVIEW, &CPUimageView::OnPreviewPreview)
	ON_COMMAND(ID_PROCESS_SKINDETECT, &CPUimageView::OnProcessSkindetect)
	ON_COMMAND(ID_VIDEO_MOTION, &CPUimageView::OnVideoMotion)
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

	//create windows
	namedWindow("Original Image", CV_WINDOW_AUTOSIZE);
	namedWindow("Histogram Equalized", CV_WINDOW_AUTOSIZE);

	//show the image
	imshow("Original Image", img);
	imshow("Histogram Equalized", img_hist_equalized);

	waitKey(0); //wait for key press

	destroyAllWindows(); //destroy all open windows

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
	autoBrightContrast(mats, 1.5, 20);
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

	// display the results  (you might also want to see lab_planes[0] before and after).
	cv::imshow("image original", bgr_image);
	cv::imshow("image CLAHE", image_clahe);
	cv::waitKey();
}


void CPUimageView::OnFilterGaussian()
{
	namedWindow("Original Image", CV_WINDOW_AUTOSIZE);
	namedWindow("Smoothed Image", CV_WINDOW_AUTOSIZE);

	CPUimageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	Mat src = pDoc->matImg;

	//show the loaded image
	imshow("Original Image", src);

	Mat dst;
	char zBuffer[35];

	for (int i = 1; i < 31; i = i + 2)
	{
		//copy the text to the "zBuffer"
		_snprintf_s(zBuffer, 35, "Kernel Size : %d x %d", i, i);
		//smooth the image using Gaussian kernel in the "src" and save it to "dst"
		GaussianBlur(src, dst, Size(i, i), 0, 0);
		//put the text in the "zBuffer" to the "dst" image
		putText(dst, zBuffer, Point(src.cols / 4, src.rows / 8), CV_FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255), 2);
		//show the blurred image with the text
		imshow("Smoothed Image", dst);
		//wait for 2 seconds
		int c = waitKey(2000);
		//if the "esc" key is pressed during the wait, return
		if (c == 27)
			return;
	}

	//make the "dst" image, black
	dst = Mat::zeros(src.size(), src.type());
	//copy the text to the "zBuffer"
	_snprintf_s(zBuffer, 35, "Press Any Key to Exit");
	//put the text in the "zBuffer" to the "dst" image
	putText(dst, zBuffer, Point(src.cols / 4, src.rows / 2), CV_FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255));
	//show the black image with the text
	imshow("Smoothed Image", dst);
	//wait for a key press infinitely
	waitKey(0);

}


void CPUimageView::OnFilterMedian()
{
	//create 2 empty windows
	namedWindow("Original Image", CV_WINDOW_AUTOSIZE);
	namedWindow("Smoothed Image", CV_WINDOW_AUTOSIZE);
	CPUimageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	Mat src = pDoc->matImg;

	//show the loaded image
	imshow("Original Image", src);
	Mat dst;
	char zBuffer[35];

	for (int i = 1; i < 31; i = i + 2)
	{
		//copy the text to the "zBuffer"
		_snprintf_s(zBuffer, 35, "Kernel Size : %d x %d", i, i);
		//smooth the image using Median kernel in the "src" and save it to "dst"
		medianBlur(src, dst, i);
		//put the text in the "zBuffer" to the "dst" image
		putText(dst, zBuffer, Point(src.cols / 4, src.rows / 8), CV_FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255), 2);
		//show the blurred image with the text
		imshow("Smoothed Image", dst);
		//wait for 2 seconds
		int c = waitKey(2000);
		//if the "esc" key is pressed during the wait, return
		if (c == 27)
			return;
	}

	//make the "dst" image, black
	dst = Mat::zeros(src.size(), src.type());
	//copy the text to the "zBuffer"
	_snprintf_s(zBuffer, 35, "Press Any Key to Exit");
	//put the text in the "zBuffer" to the "dst" image
	putText(dst, zBuffer, Point(src.cols / 4, src.rows / 2), CV_FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255));
	//show the black image with the text
	imshow("Smoothed Image", dst);

	//wait for a key press infinitely
	waitKey(0);
}


void CPUimageView::OnFilterLaplaciansharpen()
{

	CPUimageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	Mat src = pDoc->matImg;

	Mat src_gray, dst;
	int kernel_size = 3;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	char* window_name = "Laplace Image";

	int c;

	if (!src.data)
		return;

	/// Remove noise by blurring with a Gaussian filter
	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);

	/// Convert the image to grayscale
	cvtColor(src, src_gray, CV_BGR2GRAY);
	/// Create window
	namedWindow(window_name, CV_WINDOW_AUTOSIZE);
	/// Apply Laplace function
	Mat abs_dst;
	Laplacian(src_gray, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(dst, abs_dst);
	/// Show what you got
	imshow(window_name, abs_dst);
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

}


void CPUimageView::OnProcessSkindetect()
{
	// Load image & get skin proportions:
	Mat image = imread("shan.png");
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
	motion();
}
