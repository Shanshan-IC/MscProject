// RotateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PUimage.h"
#include "RotateDlg.h"
#include "afxdialogex.h"
#include "PrevDlg.h"
#include "AddFunct.h"
#include "opencv/cv.h"			// Computer Vision Lib Header
#include "opencv/highgui.h"	// HighGUI Vision Lib Header
// RotateDlg dialog

IMPLEMENT_DYNAMIC(RotateDlg, CDialogEx)

RotateDlg::RotateDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(RotateDlg::IDD, pParent)
	, m_SliderValue(_T(""))
{

}

RotateDlg::~RotateDlg()
{
}

void RotateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_Slider);
	DDX_Text(pDX, IDC_EDIT1, m_SliderValue);
}


BEGIN_MESSAGE_MAP(RotateDlg, CDialogEx)
	ON_WM_HSCROLL()
	
	ON_BN_CLICKED(IDC_BUTTON1, &RotateDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// RotateDlg message handlers


BOOL RotateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//initialize the range of slider is 0 to 360, and default value is 90
	m_Slider.SetRangeMin(0, false);
	m_Slider.SetRangeMax(360, false);
	m_Slider.SetPos(90);
	m_SliderValue = "90";

	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void RotateDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
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


void RotateDlg::OnBnClickedButton1()
{
	double d = atof(m_SliderValue);
	Mat temp = rotate(m_mat, d);
	IplImage img = temp;
	CvvImage cimg;
	cimg.CopyOf(&img);

	CPrevDlg dlg;
	dlg.m_image = cimg;
	dlg.DoModal();
	waitKey(0);
}
