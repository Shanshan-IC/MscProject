#pragma once
#include "afxcmn.h"

#include "opencv/cv.h"			// Computer Vision Lib Header
#include "opencv/highgui.h"	// HighGUI Vision Lib Header
// RotateDlg dialog

class RotateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(RotateDlg)

public:
	RotateDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~RotateDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	
	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_Slider;
	CString m_SliderValue;
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	cv::Mat m_mat;
	afx_msg void OnBnClickedButton1();
};
