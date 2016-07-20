#pragma once
#include "afxcmn.h"

#include "opencv/cv.h"			// Computer Vision Lib Header
#include "opencv/highgui.h"	// HighGUI Vision Lib Header
// CResizeDlg dialog

class CResizeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CResizeDlg)

public:
	CResizeDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CResizeDlg();

// Dialog Data
	enum { IDD = IDD_Resize };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_Slider;
	CString m_SliderValue;
	cv::Mat m_mat;
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedButton1();
};
