
// BrightDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PUimage.h"
#include "BrightDlg.h"
#include "PrevDlg.h"
#include "afxdialogex.h"
#include "BrightContrast.h"
#include "opencv2/highgui/highgui.hpp"

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>


#include "PUimageDoc.h"
using namespace cv;
using namespace std;
// CBrightDlg dialog

IMPLEMENT_DYNAMIC(CBrightDlg, CDialogEx)

CBrightDlg::CBrightDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBrightDlg::IDD, pParent)
	, m_SliderValue(_T(""))
{

}

CBrightDlg::~CBrightDlg()
{
}

void CBrightDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_Slider);
	DDX_Text(pDX, IDC_EDIT1, m_SliderValue);
}


BEGIN_MESSAGE_MAP(CBrightDlg, CDialogEx)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON1, &CBrightDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CBrightDlg message handlers


BOOL CBrightDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//set the range of slider from 0 to 100, and default value is 0
	m_Slider.SetRangeMin(0, false);
	m_Slider.SetRangeMax(100, false);
	m_SliderValue = "0";
	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

//edit value is set to the slider value
void CBrightDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
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


void CBrightDlg::OnBnClickedButton1()
{
	int alpha = _ttoi(m_SliderValue);
	Mat temp = autoBrightContrast(m_mat, 2.2, alpha);
	IplImage img = temp;
	CvvImage cimg;
	cimg.CopyOf(&img);

	CPrevDlg dlg;
	dlg.m_image = cimg;
	dlg.DoModal();
	waitKey(0);
	CDialogEx::OnOK();
}
