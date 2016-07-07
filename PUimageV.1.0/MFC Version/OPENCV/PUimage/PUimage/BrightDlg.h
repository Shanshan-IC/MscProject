#pragma once
#include "afxcmn.h"
#include "opencv/highgui.h"

// CBrightDlg dialog

class CBrightDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBrightDlg)

public:
	CBrightDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CBrightDlg();

// Dialog Data
	enum { IDD = IDD_BRIGHT };
	cv::Mat m_mat;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_Slider;
	CString m_SliderValue;
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedOk();
};
