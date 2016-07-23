// ContrastDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PUimage.h"
#include "PUimageDoc.h"
#include "ContrastDlg.h"
#include "afxdialogex.h"
#include "BrightContrast.h"
#include "PrevDlg.h"
#include "opencv2/highgui/highgui.hpp"

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>

using namespace cv;
using namespace std;
// CContrastDlg dialog

IMPLEMENT_DYNAMIC(CContrastDlg, CDialogEx)

CContrastDlg::CContrastDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CContrastDlg::IDD, pParent)
	, m_SliderValue(_T(""))
{

}

CContrastDlg::~CContrastDlg()
{
}

void CContrastDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_Slider);
	DDX_Text(pDX, IDC_EDIT1, m_SliderValue);
}


BEGIN_MESSAGE_MAP(CContrastDlg, CDialogEx)
	ON_WM_HSCROLL()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON1, &CContrastDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CContrastDlg message handlers


BOOL CContrastDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//set the range of slider from 1.0 to 3.0, and default value is 1.0
	m_Slider.SetRangeMin(1.0, false);
	m_Slider.SetRangeMax(3.0, false);
	m_SliderValue = "1.0";
	
	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

//edit value is set to the slider value
void CContrastDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
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

//according to the value set by the user, call the brightness and contrast function
void CContrastDlg::OnBnClickedButton1()
{
	double beta = atof(m_SliderValue);
	Mat temp = autoBrightContrast(m_mat, beta, 30);
	IplImage img = temp;
	CvvImage cimg;
	cimg.CopyOf(&img);

	CPrevDlg dlg;
	dlg.m_image = cimg;
	dlg.DoModal();
	waitKey(0);
	CDialogEx::OnOK();
}
