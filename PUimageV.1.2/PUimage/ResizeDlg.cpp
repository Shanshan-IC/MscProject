// ResizeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PUimage.h"
#include "ResizeDlg.h"
#include "PrevDlg.h"
#include "Cvvimage.h"
#include "afxdialogex.h"
#include "opencv/cv.h"			// Computer Vision Lib Header
#include "opencv/highgui.h"	// HighGUI Vision Lib Header
#include "opencv2/opencv.hpp"


using namespace cv;
using namespace std;

// CResizeDlg dialog

IMPLEMENT_DYNAMIC(CResizeDlg, CDialogEx)

CResizeDlg::CResizeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CResizeDlg::IDD, pParent)
	, m_SliderValue(_T(""))
{

}

CResizeDlg::~CResizeDlg()
{
}

void CResizeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_Slider);
	DDX_Text(pDX, IDC_EDIT1, m_SliderValue);
}


BEGIN_MESSAGE_MAP(CResizeDlg, CDialogEx)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON1, &CResizeDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CResizeDlg message handlers


BOOL CResizeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_Slider.SetRangeMin(1, false);
	m_Slider.SetRangeMax(10, false);
	m_Slider.SetPos(3);
	m_SliderValue = "3";

	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CResizeDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (nSBCode == SB_THUMBPOSITION)
	{

		m_SliderValue.Format(_T("%ld"), nPos);
		UpdateData(false);
	}

	else
	{
		CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CResizeDlg::OnBnClickedButton1()
{
	double d = atof(m_SliderValue);
	Mat temp;
	resize(m_mat, temp, Size(m_mat.cols* d, m_mat.rows *d), 0, 0, INTER_LINEAR);

	IplImage img = temp;
	CvvImage cimg;
	cimg.CopyOf(&img);

	CPrevDlg dlg;
	dlg.m_image = cimg;
	dlg.DoModal();
	waitKey(0);
}
