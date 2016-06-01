#pragma once

#include "PreviewDlg.h"

class CRotateDlg : public CDialog
{
	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CRotateDlg)

public:
	int m_nAngle;		// rotation angle
	int m_nPos;			// rotation angle pos
	int m_nType;		// rotation type

	CRotateDlg(CWnd* pParent = NULL);
	virtual ~CRotateDlg();

	void Refresh();
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedPrev();
	afx_msg void OnEnChangeAngle();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedSave();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 

private:
	bool	m_bModify;	// whether to modify the image

	enum { IDD = IDD_ROTATE };
};