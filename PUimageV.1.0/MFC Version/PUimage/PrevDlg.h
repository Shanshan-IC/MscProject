#pragma once
#include "afxwin.h"
#include "resource.h"

class CPrevDlg : public CDialog
{
	DECLARE_MESSAGE_MAP()
	DECLARE_DYNCREATE(CPrevDlg)

public:
	// control
	CString		m_strNum;				// number of image
	CScrollBar	m_ScrollBar;			// scroll bar
	CStatic		m_staPrev;				// preview iamge

	CPrevDlg(CWnd* pParent = NULL);		// structure
	virtual ~CPrevDlg();

	void Redraw(void);					// draw 

	afx_msg void OnPaint();				// draw
	afx_msg void OnBnClickedOpen();		// open file
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	// hsrocll

	enum { IDD = IDD_PREV };			// dialog box

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV

private:
	int				m_nPicNum;			// number of image in the directory
	CString			m_strPath;			// current directory
	CStringArray	m_FilesNameAry;		// save directory
	int				m_nPos;				// index
};
