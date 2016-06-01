#pragma once

#include "resource.h"

class CPreviewDlg : public CDialog
{
	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CPreviewDlg)

public:
	int		m_nType;
	bool	m_bEnableClose;

	CPreviewDlg(CWnd* pParent = NULL);
	virtual ~CPreviewDlg();

	virtual BOOL OnInitDialog();
	void OnOK();
	void OnCancel();

	void Refresh()
	{
		Invalidate();
	}

	afx_msg void OnPaint();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnDestroy();

	enum { IDD = IDD_PREVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
