#pragma once
#include "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\atlmfc\include\afxcmn.h"


// CBrightDlg dialog

class CBrightDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBrightDlg)

public:
	CBrightDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CBrightDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

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
