#pragma once
#include "afxcmn.h"


// CEulerianColor dialog

class CEulerianColor : public CDialogEx
{
	DECLARE_DYNAMIC(CEulerianColor)

public:
	CEulerianColor(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEulerianColor();

// Dialog Data
	enum { IDD = IDD_EULERIAN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
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
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
};
