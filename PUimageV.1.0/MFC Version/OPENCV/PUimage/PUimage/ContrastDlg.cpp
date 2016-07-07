// ContrastDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PUimage.h"
#include "PUimageDoc.h"
#include "ContrastDlg.h"
#include "afxdialogex.h"
#include "BrightContrast.h"

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
	ON_BN_CLICKED(IDOK, &CContrastDlg::OnBnClickedOk)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CContrastDlg message handlers


BOOL CContrastDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_Slider.SetRangeMin(1.0, false);
	m_Slider.SetRangeMax(3.0, false);
	m_SliderValue = "1.0";
	
	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

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


void CContrastDlg::OnBnClickedOk()
{
	int beta = _ttoi(m_SliderValue);
	autoBrightContrast(m_mat, beta, 30);
	CDialogEx::OnOK();

}


