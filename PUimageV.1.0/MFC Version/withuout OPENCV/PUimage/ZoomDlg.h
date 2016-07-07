#pragma once


// CZoomDlg ¶Ô»°¿ò

#include "PreviewDlg.h"

class CZoomDlg : public CDialog
{
	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CZoomDlg)

public:
	int		m_nWidth;
	int		m_nHeight;
	BOOL	m_bIsPro;
	int		m_nType;

	CZoomDlg(CWnd* pParent = NULL);
	virtual ~CZoomDlg();

	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedPrev();
	afx_msg void OnEnChangeWidth();
	afx_msg void OnEnChangeHeight();
	afx_msg void OnBnClickedPro();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedOk();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 

private:
	int		m_nSrcWidth;			// width of initial image
	int		m_nSrcHeight;			// height of initial image

	void Refresh();					// Rezoom
	void RefreshSize(bool width);	// Calculate the size of image

private:
	bool			m_bModify;		// save the modify the image or not
	enum { IDD = IDD_ZOOM };
};
