#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CContrastDlg dialog

class CContrastDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CContrastDlg)

public:
	CContrastDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CContrastDlg();
	void Show_picture();
// Dialog Data
	enum { IDD = IDD_CONTRAST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_Slider;
	CString m_SliderValue;
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedOk();
	cv::Mat m_mat;
};
