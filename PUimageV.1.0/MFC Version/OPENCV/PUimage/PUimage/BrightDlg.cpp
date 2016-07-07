// BrightDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PUimage.h"
#include "BrightDlg.h"
#include "afxdialogex.h"
#include "BrightContrast.h"

#include "PUimageDoc.h"

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
	ON_BN_CLICKED(IDOK, &CBrightDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CBrightDlg message handlers


BOOL CBrightDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_Slider.SetRangeMin(0, false);
	m_Slider.SetRangeMax(100, false);
	m_SliderValue = "0";
	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


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


void CBrightDlg::OnBnClickedOk()
{
	int alpha = _ttoi(m_SliderValue);
	autoBrightContrast(m_mat, 2.2, alpha);
	CDialogEx::OnOK();
}
