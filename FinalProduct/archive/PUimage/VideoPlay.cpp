// VideoPlay.cpp : implementation file
//

#include "stdafx.h"
#include "PUimage.h"
#include "VideoPlay.h"
#include "afxdialogex.h"
#include "Motion.h"
#include "Manification.h"

#include "Cvvimage.h"
#include "opencv\cv.h"
#include "opencv\highgui.h"

using namespace cv;
using namespace std;

// CVideoPlay dialog

IMPLEMENT_DYNAMIC(CVideoPlay, CDialogEx)

CVideoPlay::CVideoPlay(CWnd* pParent /*=NULL*/)
	: CDialogEx(CVideoPlay::IDD, pParent)
	, alpha(_T(""))
	, lambda_c(_T(""))
	, fl(_T(""))
	, fh(_T(""))
	, chromAttenuation(_T(""))
{

}

CVideoPlay::~CVideoPlay()
{
}

void CVideoPlay::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, alpha);
	DDX_Text(pDX, IDC_EDIT2, lambda_c);
	DDX_Text(pDX, IDC_EDIT3, fl);
	DDX_Text(pDX, IDC_EDIT4, fh);
	DDX_Text(pDX, IDC_EDIT5, chromAttenuation);
	DDX_Control(pDX, IDC_SLIDER1, alpha_slider);
	DDX_Control(pDX, IDC_SLIDER2, lambda_slider);
	DDX_Control(pDX, IDC_SLIDER3, fl_slider);
	DDX_Control(pDX, IDC_SLIDER4, fh_slider);
	DDX_Control(pDX, IDC_SLIDER5, chromAtten_slider);
}


BEGIN_MESSAGE_MAP(CVideoPlay, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_ReadVideo_Button, &CVideoPlay::OnBnClickedReadvideoButton)
	ON_BN_CLICKED(IDC_Play_Button, &CVideoPlay::OnBnClickedPlayButton)
	ON_WM_CTLCOLOR()
	//ON_BN_CLICKED(IDC_BUTTON1, &CVideoPlay::OnBnClickedButton1)
	//ON_BN_CLICKED(IDC_BUTTON2, &CVideoPlay::OnBnClickedButton2)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDCANCEL, &CVideoPlay::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON4, &CVideoPlay::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON6, &CVideoPlay::OnBnClickedButton6)
	//ON_BN_CLICKED(IDC_BUTTON3, &CVideoPlay::OnBnClickedButton3)
END_MESSAGE_MAP()


// CVideoPlay message handlers


BOOL CVideoPlay::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CvSize ImgSize;
	ImgSize.height = 256;
	ImgSize.width = 256;
	TheImage = cvCreateImage(ImgSize, IPL_DEPTH_8U, 3);


	alpha_slider.SetRangeMin(0, false);
	alpha_slider.SetRangeMax(100, false);
	alpha_slider.SetPos(80);
	alpha = "80";

	lambda_slider.SetRangeMin(0, false);
	lambda_slider.SetRangeMax(1000, false);
	lambda_slider.SetPos(80);
	lambda_c = "80";

	fl_slider.SetRange(0, 100);
	fl_slider.SetPos(90);
	fl = "0.9";

	fh_slider.SetRangeMin(0, false);
	fh_slider.SetRangeMax(100, false);
	fh_slider.SetPos(100);
	fh = "1";

	chromAtten_slider.SetRangeMin(0, false);
	chromAtten_slider.SetRangeMax(100, false);
	chromAtten_slider.SetPos(10);
	chromAttenuation = "0.1";

	UpdateData(false);


	return TRUE;
}


void CVideoPlay::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
	}
	else
	{
		CDialogEx::OnPaint();
		CDialog::OnPaint();
		CDialog::UpdateWindow();
	}
}

void CVideoPlay::ResizeImage(IplImage* img)
{
	int w = img->width;
	int h = img->height;
	int max = (w>h) ? w : h;
	float scale = (float)((float)max / 256.0f);
	int nw = (int)(w / scale);
	int nh = (int)(h / scale);

	int tlx = (nw>nh) ? 0 : (int)(256 - nw) / 2;
	int tly = (nw>nh) ? (int)(256 - nh) / 2 : 0;
	cvSetImageROI(TheImage, cvRect(tlx, tly, nw, nh));
	cvResize(img, TheImage);
	cvResetImageROI(TheImage);
}

void CVideoPlay::ShowImage(IplImage* img, UINT ID)
{
	CDC* pDC = GetDlgItem(ID)->GetDC();
	HDC hDC = pDC->GetSafeHdc();
	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	int rw = rect.right - rect.left;
	int rh = rect.bottom - rect.top;
	int iw = img->width;
	int ih = img->height;
	int tx = (int)(rw - iw) / 2;
	int ty = (int)(rh - ih) / 2;

	SetRect(rect, tx, ty, tx + iw, ty + ih);
	CvvImage cimg;
	cimg.CopyOf(img);
	cimg.DrawToHDC(hDC, &rect);

	ReleaseDC(pDC);
}



void CVideoPlay::OnBnClickedReadvideoButton()
{
	CFileDialog dlg(
		TRUE,
		_T("*.avi"),
		NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("*.avi;*.mp4;*.mov|*.avi;*.mp4;*.mov| All Files(*.*)|(*.*)||"),
		NULL
		);
	dlg.m_ofn.lpstrTitle = _T("Open Video");
	if (dlg.DoModal() != IDOK)
		return;
	vPath = dlg.GetPathName();
	GetDlgItem(IDC_Play_Button)->EnableWindow(TRUE);
	//GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	CvCapture* myCapture = cvCreateFileCapture(vPath);
	IplImage* myImage = cvQueryFrame(myCapture);
	if (!myImage) return;
	cvZero(TheImage); 
	ResizeImage(myImage);
	ShowImage(TheImage, IDC_ShowImg);
	cvReleaseCapture(&myCapture);;
}


void CVideoPlay::OnBnClickedPlayButton()
{
	CvCapture *pCapture = NULL;
	IplImage* pFrame = NULL;
	if (vPath == " ")
	{
		MessageBox("Pleas choose video files!");
		return;
	}
	else
	{
		if (!(pCapture = cvCreateFileCapture(vPath)))
		{
			MessageBox("Failed to open video files!");
			return;
		}
	}
	//GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	GetDlgItem(IDC_ReadVideo_Button)->EnableWindow(FALSE);
	GetDlgItem(IDC_Play_Button)->EnableWindow(FALSE);
	//GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);

	cvNamedWindow("videoSmile");
	cvResizeWindow("videoSmile", 1, 1);
	HWND hWnd = (HWND)cvGetWindowHandle("videoSmile");
	HWND hParent = ::GetParent(hWnd);
	HWND hwnd1 = ::FindWindow(NULL, "PlayVideo");
	::SetParent(hWnd, hwnd1);
	::ShowWindow(hParent, SW_HIDE);


	int frames = (int)cvGetCaptureProperty(pCapture, CV_CAP_PROP_FRAME_COUNT);
	int numfrm = 0;
	if (TheImage)
		cvZero(TheImage);

	m_run = 1;
	while ((numfrm<frames)&(m_run == 1))
	{
		pFrame = cvQueryFrame(pCapture);
		IplImage* newframe = cvCloneImage(pFrame);
		ResizeImage(newframe); 
		ShowImage(TheImage, IDC_ShowImg);
		if (cvWaitKey(20) == 27) break;
		numfrm++;
		cvReleaseImage(&newframe);
	}
	m_run = 0;

	if (TheImage)
	{
		cvZero(TheImage);
		ShowImage(TheImage, IDC_ShowImg);
	}

	//GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	GetDlgItem(IDC_ReadVideo_Button)->EnableWindow(TRUE);
	GetDlgItem(IDC_Play_Button)->EnableWindow(TRUE);
	//GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);

	cvReleaseCapture(&pCapture);
	cvDestroyWindow("videoSmile");
	return;
}


HBRUSH CVideoPlay::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	return hbr;
}

/*
void CVideoPlay::OnBnClickedButton1()
{
	CFileDialog dlg(
		TRUE, _T("*.bmp"), NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("image files(*.bmp;*.jpg)|*.bmp;*.jpg|All Files(*.*)|*.*||"),
		NULL
		);
	dlg.m_ofn.lpstrTitle = _T("Open Image");
	if (dlg.DoModal() != IDOK) { MessageBox(_T("no picture")); }
	CString mPath = dlg.GetPathName();
	IplImage* ipl = cvLoadImage(mPath, 1);
	if (!ipl) return;

	if (TheImage) cvZero(TheImage);

	ResizeImage(ipl);
	ShowImage(TheImage, IDC_ShowImg);
	cvReleaseImage(&ipl);;
}
*/

/*
void CVideoPlay::OnBnClickedButton2()
{
	IplImage* gray = 0, *edge = 0;
	gray = cvCreateImage(cvSize(256, 256), IPL_DEPTH_8U, 1);
	edge = cvCreateImage(cvSize(256, 256), IPL_DEPTH_8U, 1);
	cvCvtColor(TheImage, gray, CV_BGR2GRAY);
	cvCanny(gray, edge, 30, 100, 3);

	cvCvtColor(edge, TheImage, CV_GRAY2BGR);
	ShowImage(TheImage, IDC_ShowImg);

	cvReleaseImage(&gray);
	cvReleaseImage(&edge);
}
*/


void CVideoPlay::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CSliderCtrl   *pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER1);
	switch (pScrollBar->GetDlgCtrlID())
	{

	case IDC_SLIDER1:
	{
		alpha.Format(_T("%ld"), pSlidCtrl->GetPos());
		UpdateData(false);
		break;
	}
	case IDC_SLIDER2:
	{
		pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER2);
		lambda_c.Format(_T("%ld"), pSlidCtrl->GetPos());
		UpdateData(false);
		break;
	}
	case IDC_SLIDER3:
	{
		pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER3);
		fl.Format(_T("%2f"), float(pSlidCtrl->GetPos() / 100.0));
		UpdateData(false);
		break;
	}
	case IDC_SLIDER4:
	{
		pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER4);
		fh.Format(_T("%2f"), float(pSlidCtrl->GetPos()) / 100.0);
		UpdateData(false);
		break;
	}
	case IDC_SLIDER5:
	{
		pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER5);
		chromAttenuation.Format(_T("%2f"), float(pSlidCtrl->GetPos()) / 100.0);
		UpdateData(false);
		break;
	}
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CVideoPlay::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CVideoPlay::OnBnClickedButton4()
{
	if (vPath == " ")
	{
		MessageBox("Pleas choose video files!");
		return;
	}
	string s((LPCTSTR)vPath);
	Manification colormani = Manification(100, 80, 0.8,1, 0.1);
	colormani.colorManification(s);
}


void CVideoPlay::OnBnClickedButton6()
{
	if (vPath == " ")
	{
		MessageBox("Pleas choose video files!");
		return;
	}
	int _alpha = atoi(alpha);
	float _lambda_c = atof(lambda_c);
	float _fl = atof(fl);
	float _fh = atof(fh);
	float _chromAttenuation = atof(chromAttenuation);

	string s((LPCTSTR)vPath);
	Manification colormani = Manification(_alpha, _lambda_c, _fl, _fh, _chromAttenuation);
	colormani.colorManification(s);

}

/*
void CVideoPlay::OnBnClickedButton3()
{
	CvSize size;
	IplImage *img = cvLoadImage("fr1.jpg");
	size.width = img->width;
	size.height = img->height;
	int fps = 25;
	CvVideoWriter *writer = cvCreateVideoWriter(
		"image2video.avi",
		-1,
		fps,
		size
		);

	if (writer == NULL)
		std::cout << "No videowrite here!" << '\nl';
	cv::VideoCapture cap("fr%d.jpg");
	cv::Mat frame;
	while (1)
	{
		cap >> fra
		sprintf( filename, "fr%d.jpg", i );

		img = cvLoadImage(filename); //imagem b&w
		cvWriteFrame(writer,img);

		 i++;
	}

	cvReleaseVideoWriter(&writer);
	cvReleaseImage(&img);
}
*/