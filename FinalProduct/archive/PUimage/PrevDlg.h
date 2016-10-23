#pragma once


// CPrevDlg dialog

#include "opencv2/opencv.hpp"
#include "opencv/cv.h"
#include "Cvvimage.h"
using namespace cv;
using namespace std;


class CPrevDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPrevDlg)
public:
	int X_image;
	int Y_image;
	CvvImage m_image;
public:
	CPrevDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPrevDlg();

// Dialog Data
	enum { IDD = IDD_PREV };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	
	void ShowImage(void);
	afx_msg void OnPaint();

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedFileSaveAs();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
