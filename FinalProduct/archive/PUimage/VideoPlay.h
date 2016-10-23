#pragma once

#include "PUimage.h"
#include "VideoPlay.h"
#include "afxdialogex.h"


#include "Cvvimage.h"
#include "opencv\cv.h"
#include "opencv\highgui.h"
#include "afxcmn.h"

using namespace cv;
using namespace std;
// CVideoPlay dialog

class CVideoPlay : public CDialogEx
{
	DECLARE_DYNAMIC(CVideoPlay)

public:
	CVideoPlay(CWnd* pParent = NULL);   // standard constructor
	virtual ~CVideoPlay();

// Dialog Data
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	CString vPath;
	int m_run;
	IplImage* TheImage;
	afx_msg void OnPaint();

	void ShowImage(IplImage* img, UINT ID);
	void ResizeImage(IplImage* img);
	afx_msg void OnBnClickedReadvideoButton();
	afx_msg void OnBnClickedPlayButton();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//afx_msg void OnBnClickedButton1();
	//afx_msg void OnBnClickedButton2();
	afx_msg void OnEnChangeEdit1();
	CString alpha;
	CString lambda_c;
	CString fl;
	CString fh;
	CString chromAttenuation;
	CSliderCtrl alpha_slider;
	CSliderCtrl lambda_slider;
	CSliderCtrl fl_slider;
	CSliderCtrl fh_slider;
	CSliderCtrl chromAtten_slider;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton6();
	//afx_msg void OnBnClickedButton3();
};
