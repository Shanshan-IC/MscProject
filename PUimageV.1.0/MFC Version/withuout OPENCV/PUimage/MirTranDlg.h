#pragma once

#include "PreviewDlg.h"

class CMirTranDlg : public CDialog
{
	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CMirTranDlg)

public:
	int m_nType;			// type of mirror transformation

	CMirTranDlg(CWnd* pParent = NULL);
	virtual ~CMirTranDlg();

	void Refresh();					// mirror tranformation again and update preview windows
	virtual BOOL OnInitDialog();	// initial

	afx_msg void OnBnClickedMirrorH();
	afx_msg void OnBnClickedMirrorV();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedOk();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);// DDX/DDV 

private:
	CPreviewDlg*	dlg;		// preview
	bool			m_bModify;	// save the modify or not

	enum { IDD = IDD_MIRROR };
};
