// EulerianColor.cpp : implementation file
//

#include "stdafx.h"
#include "PUimage.h"
#include "EulerianColor.h"
#include "afxdialogex.h"
#include "opencv2/opencv.hpp"
#include "VideoProcessor.h"
#include <string>

#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// CEulerianColor dialog

IMPLEMENT_DYNAMIC(CEulerianColor, CDialogEx)

CEulerianColor::CEulerianColor(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEulerianColor::IDD, pParent)
	, alpha(_T(""))
	, lambda_c(_T(""))
	, fl(_T(""))
	, fh(_T(""))
	, chromAttenuation(_T(""))
{

}

CEulerianColor::~CEulerianColor()
{
}

void CEulerianColor::DoDataExchange(CDataExchange* pDX)
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


BEGIN_MESSAGE_MAP(CEulerianColor, CDialogEx)
	ON_WM_HSCROLL()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CEulerianColor::OnNMCustomdrawSlider1)
	ON_BN_CLICKED(IDOK, &CEulerianColor::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CEulerianColor::OnBnClickedButton1)
END_MESSAGE_MAP()


// CEulerianColor message handlers


BOOL CEulerianColor::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	alpha_slider.SetRangeMin(0, false);
	alpha_slider.SetRangeMax(100, false);
	alpha_slider.SetPos(10);
	alpha = "10";

	lambda_slider.SetRangeMin(0, false);
	lambda_slider.SetRangeMax(1000, false);
	lambda_slider.SetPos(80);
	lambda_c = "80";

	fl_slider.SetRange(0, 100);
	fl_slider.SetPos(5);
	fl = "0.05";

	fh_slider.SetRangeMin(0, false);
	fh_slider.SetRangeMax(100, false);
	fh_slider.SetPos(40);
	fh = "0.4";

	chromAtten_slider.SetRangeMin(0, false);
	chromAtten_slider.SetRangeMax(100, false);
	chromAtten_slider.SetPos(10);
	chromAttenuation = "0.1";

	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CEulerianColor::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CSliderCtrl   *pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER1);
	switch (pScrollBar->GetDlgCtrlID())
	{
		
	case IDC_SLIDER1:
	{
		alpha.Format(L"%ld", pSlidCtrl->GetPos());
		UpdateData(false);
		break;
	}
	case IDC_SLIDER2:
	{
		pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER2);
		lambda_c.Format(L"%ld", pSlidCtrl->GetPos());
		UpdateData(false);
		break;
	}
	case IDC_SLIDER3:
	{
		pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER3);
		fl.Format(L"%2f", float(pSlidCtrl->GetPos()) / 100.0);
		UpdateData(false);
		break;
	}
	case IDC_SLIDER4:
	{
		pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER4);
		fh.Format(L"%2f", float(pSlidCtrl->GetPos()) / 100.0);
		UpdateData(false);
		break;
	}
	case IDC_SLIDER5:
	{
		pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER5);
		chromAttenuation.Format(L"%2f", float(pSlidCtrl->GetPos()) / 100.0);
		UpdateData(false);
		break;
	}
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CEulerianColor::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void CEulerianColor::OnBnClickedOk()
{
	
	int _alpha = _ttoi(alpha);
	int _lambda_c = _ttoi(lambda_c);
	int _fl = _ttoi(fl);
	int _fh = _ttoi(fh);
	int _chromAttenuation = _ttoi(chromAttenuation);

	string input_filename = "baby.avi";
	string output_filename = "test.avi";

	VideoProcessor vid_proc;
	vid_proc.setInput(input_filename);
	vid_proc.setOutputVideo(output_filename);

	vid_proc.colorMagnify();
	CDialogEx::OnOK();
}


void CEulerianColor::OnBnClickedButton1()
{
	VideoCapture cap("D:\\baby.avi"); // open the video file for reading

	if (!cap.isOpened())  // if not success, exit program
		cout << "Cannot open the video file" << endl;
		return;

	double fps = cap.get(CV_CAP_PROP_FPS); //get the frames per seconds of the video
	namedWindow("MyVideo", CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"

	while (1)
	{
		Mat frame;
		bool bSuccess = cap.read(frame); // read a new frame from video
		if (!bSuccess) //if not success, break loop
		{
			cout << "Cannot read the frame from video file" << endl;
			break;
		}
		imshow("MyVideo", frame); //show the frame in "MyVideo" window
		if (waitKey(30) == 27) //wait for 'esc' key press for 30 ms. If 'esc' key is pressed, break loop
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}
	return;

}
