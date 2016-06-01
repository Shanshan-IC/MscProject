#pragma once
#include "afxwin.h"
#include "PreviewDlg.h"


// CStretchDlg 

class CStretchDlg : public CDialog
{
	// control point typle
	enum PointType
	{
		PT_NULL,		// control point 1
		PT_POINT_ONE,	// control point 2
		PT_POINT_TWO	// control point 3
	};

	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CStretchDlg)

public:
	CStatic m_stiPrev;				// preview
	float	m_dPsX1;				// control point 1 x
	float	m_dPsY1;				// control point 1 y
	float	m_dPsX2;				// control point 2 x
	float	m_dPsY2;				// control point 2 y

	CStretchDlg(CWnd* pParent = NULL);
	virtual ~CStretchDlg();

	void Refresh();							// Refresh

	virtual BOOL OnInitDialog();			// 
	afx_msg void OnPaint();					// 
	afx_msg void OnEnChangePointoneX();		// change control point 1 x
	afx_msg void OnEnChangePointoneY();		// change control point 1 y
	afx_msg void OnEnChangePointtwoX();		// change control point 2 x
	afx_msg void OnEnChangePointtwoY();		// change control point 2 y
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);

	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV

private:
	CPreviewDlg*	dlg;			// preview
	bool			m_bModify;		// whether to modify the image
	bool			m_bIsDraging;	// whether to drag
	int				m_nPointType;	// current control point type


	enum { IDD = IDD_STRETCH };
};
