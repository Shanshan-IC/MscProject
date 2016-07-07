
#if !defined(AFX_COOLTABCTRL_H__83DD41F0_25C9_417D_9353_777A80FAD1CF__INCLUDED_)
#define AFX_COOLTABCTRL_H__83DD41F0_25C9_417D_9353_777A80FAD1CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define TCS_UP			0x0001		///Up
#define TCS_DOWN		0x0002		///Down
#define TCS_MONOSPACE	0x0004		///Same width
#define TCS_ANIMATE		0x0008		///Windows movement
#define TCS_MASK		0x000f		

// CCoolTabCtrl window

class CCoolTabCtrl : public CWnd
{
public:
	class CPageItem
	{
		friend class CCoolTabCtrl;

		CWnd*		m_pWnd;		///windows : NULL
		UINT		m_nStyle;	///type: 0, normal; 1, dynamic
		CString		m_sText;	///Text
		HICON		m_hIcon;	///Icon
	public:
		CRect		m_rect;
	public:
		void SetPageStyle(UINT nStyle)
		{
			m_nStyle = nStyle;
		}

		UINT GetAreaWidth(CDC *pDC);
		void Draw(CDC *pDC, UINT nStyle, BOOL bActive);
	};
	DECLARE_DYNCREATE(CCoolTabCtrl)
	// Construction
public:
	CCoolTabCtrl();

	// Attributes
public:
	// Operations
public:

	// Implementation
public:
	void SetStyleMonoSpace(BOOL bEnable = TRUE);
	void SetStyleDirection(int Direction);		///Direction to get TCS_UP,TCS_DOWN
	void SetStyleAnimate(BOOL bEnable = TRUE);
	void UpdateWindow();
	BOOL m_bEraseBkgnd;
	UINT GetStyle();
	void SetStyle(UINT style);
	void DrawFrame(CDC *pDC);
	void* GetPageItem(UINT nIndex);
	void SetActivePage(int nIndex);
	BOOL AddPage(CRuntimeClass* pClass, UINT nIDTemplate, LPCTSTR sText, UINT IconID = NULL);
	CPageItem* AddPage(CWnd *pWnd, LPCTSTR sText, UINT IconID = NULL);
	void AutoSize();
	void GetClientRect(LPRECT lpRect);
	BOOL Create(UINT wStyle, const CRect & rect, CWnd * pParentWnd, UINT nID);
	virtual ~CCoolTabCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCoolTabCtrl)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CFont		m_font;
	int			m_nActivePage;
	UINT		m_nStyle;
	UINT		m_nBorder;
	CPtrList	m_PageList;
};


#endif // !defined(AFX_COOLTABCTRL_H__83DD41F0_25C9_417D_9353_777A80FAD1CF__INCLUDED_)
