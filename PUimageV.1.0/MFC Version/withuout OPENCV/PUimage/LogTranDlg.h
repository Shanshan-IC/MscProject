#pragma once

#include "PreviewDlg.h"
#include "afxwin.h"

// CLogTranDlg

class CLogTranDlg : public CDialog
{
	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CLogTranDlg)

public:
	int		m_nPosA;		// slider A
	int		m_nPosB;		// slider B
	int		m_nA;			// parameter a
	int		m_nB;			// parameter b
	CStatic m_stiPrev;

	CLogTranDlg(CWnd* pParent = NULL);
	virtual ~CLogTranDlg();

	void Refresh();						// Refresh
	virtual BOOL OnInitDialog();

	afx_msg void OnEnChangeEdita();		// Change the parameter A
	afx_msg void OnEnChangeEditb();		//Change the parameter B
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	afx_msg void OnPaint();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedOk();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 

private:
	CPreviewDlg*	dlg;
	bool			m_bModify;

	enum { IDD = IDD_LOGTRAN };
};
