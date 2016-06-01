#pragma once


// CLineTranDlg

#include "PreviewDlg.h"
#include "afxwin.h"

class CLineTranDlg : public CDialog
{
	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CLineTranDlg)

public:
	CStatic m_stiPrev;			//preview
	double	m_dSlope;			// Slope
	double	m_dIntercept;		//Intercept

	CLineTranDlg(CWnd* pParent = NULL);
	virtual ~CLineTranDlg();

	void Refresh();					// Refresh
	virtual BOOL OnInitDialog();	// OnInitial 

	afx_msg void OnEnChangeSlope();	// change the Slope
	afx_msg void OnEnChangeIntercept();
	// change the  Intercept
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	afx_msg void OnPaint();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 

private:
	CPreviewDlg*	dlg;
	bool			m_bModify;
	enum { IDD = IDD_LINETRAN };
};
