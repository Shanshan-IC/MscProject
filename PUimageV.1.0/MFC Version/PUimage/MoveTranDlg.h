#pragma once

// CMoveTranDlg 

#include "PreviewDlg.h"

class CMoveTranDlg : public CDialog
{
	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CMoveTranDlg)

public:
	int		m_nType;		// type
	int		m_nX;			// level offset
	int		m_nY;			// verticle offset

	CMoveTranDlg(CWnd* pParent = NULL);
	virtual ~CMoveTranDlg();

	void Refresh();						// Refresh
	virtual BOOL OnInitDialog();		// Initial Dialog

	afx_msg void OnBnClickedRadioNormal();
	afx_msg void OnBnClickedRadioSize();
	afx_msg void OnEnChangeEditX();
	afx_msg void OnEnChangeEditY();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedOk();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 

private:
	CPreviewDlg*	dlg;
	bool			m_bModify;


	enum { IDD = IDD_MOVETRAN };
};
