#pragma once
#include "afxwin.h"

// CHistogramDlg

class CHistogramDlg : public CDialog
{
	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CHistogramDlg)

public:
	CStatic m_stiHistogram;		// Histogram region
	int		m_nLimitLow;		// Histogram Lower
	int		m_nLimitUp;			// Histogram Upper
	long	m_lCounts[256];		// Count number based on Histogram level
	long	m_nPixelCount;		// Count pixel
	CPoint	m_psMove;			// Record the mouse position
	int		m_nIsDraging;		// Whether the mouse is gragged
	int		m_nGray;			// Gray level of current mouse position
	float	m_dPer;				// Posibabilities


	CHistogramDlg(CWnd* pParent = NULL);	// structure
	virtual ~CHistogramDlg();

	afx_msg void OnEnChangeLimitLower();	// Change the gray lower
	afx_msg void OnEnChangeLimitUp();		// Change the gray upper
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();			// initial gray number
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	enum { IDD = IDD_HISTOGRAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 

private:
	void Refresh(void);

	enum DragingType
	{
		DT_NULL,		// Not drag
		DT_LOW,			// drag lower
		DT_UP			// drag upper
	};
};
