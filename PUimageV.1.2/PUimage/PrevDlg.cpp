// PrevDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PUimage.h"
#include "PrevDlg.h"
#include "afxdialogex.h"
#include "opencv/cv.h"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2\opencv.hpp>
#include <string.h>
#include "Cvvimage.h"

using namespace std;
using namespace cv;

SCROLLINFO scroll;

// CPrevDlg dialog

IMPLEMENT_DYNAMIC(CPrevDlg, CDialogEx)

CPrevDlg::CPrevDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPrevDlg::IDD, pParent)
{
	
}

CPrevDlg::~CPrevDlg()
{
}

void CPrevDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPrevDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON1, &CPrevDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CPrevDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CPrevDlg message handlers


BOOL CPrevDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CWnd* pWnd = GetDlgItem(IDC_PREIVIEWPIC);
	pWnd->SetWindowPos(NULL, 0, 0, 640, 480, SWP_NOMOVE);

	ShowImage();

	return TRUE;
}


void CPrevDlg::OnPaint()
{
	CPaintDC dc(this);
	CDialog::UpdateWindow();                
	ShowImage();
}

void CPrevDlg::ShowImage(void)
{
	CDC* pDC = GetDlgItem(IDC_PREIVIEWPIC)->GetDC();
	HDC hDC = pDC->GetSafeHdc();                
	CRect rect;
	GetDlgItem(IDC_PREIVIEWPIC)->GetClientRect(&rect);
	int rw = rect.right - rect.left;   
	int rh = rect.bottom - rect.top;
	int iw = m_image.Width();
	int ih = m_image.Height();
	int tx = (int)(rw - iw) / 2;                                       
	int ty = (int)(rh - ih) / 2;
	SetRect(rect, tx, ty, tx + iw, ty + ih);

	m_image.DrawToHDC(hDC, &rect);
	ReleaseDC(pDC);
}



void CPrevDlg::OnBnClickedButton1()
{
	MessageBox(_T("Exit now will discard any unsaved changes."), _T("Error"),
		MB_ICONWARNING | MB_OK);
	CDialog::OnOK();
	return;
}


void CPrevDlg::OnBnClickedButton2()
{
	CString filter = "Bitmap Files(*.bmp)|*.bmp|JPEG Files(*.jpg)|*.jpg|PNG Files(*.png)|*.png|All Files(*.*)|*.*||";
	CFileDialog SaveImageDlg(false, "*.bmp", "img1", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, NULL);
	if (SaveImageDlg.DoModal() == IDOK)
	{
		m_image.Save(SaveImageDlg.GetPathName());

	}
	else
		return;
}
