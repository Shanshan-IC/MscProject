#pragma once

#include "PreviewDlg.h"
#include "afxcmn.h"

class CThresholdDlg : public CDialog
{
	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CThresholdDlg)

public:
	CSliderCtrl m_SliderNum;	// slider of Threshold 
	int			m_nNum;			// Threshold parameter
	int			m_nPos;


	CThresholdDlg(CWnd* pParent = NULL);
	virtual ~CThresholdDlg();

	void Refresh();						// refresh

	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeNum();		// change the Threshold 
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 

private:
	CPreviewDlg*	dlg;				// preview
	bool			m_bModify;			// whether to change the image


	enum { IDD = IDD_THRESHOLD };
};
