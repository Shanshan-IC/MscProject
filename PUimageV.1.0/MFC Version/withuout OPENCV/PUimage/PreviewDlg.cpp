// PreviewDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PreviewDlg.h"
#include "MainFrm.h"
#include "PUimageDoc.h"
#include "PUimageView.h"

SCROLLINFO scroll;

static BOOL scrollSign;

static int yCurrentScroll;
static int yScrollMax;
static int yScrollMin;

static int xCurrentScroll;
static int xScrollMax;
static int xScrollMin;


IMPLEMENT_DYNAMIC(CPreviewDlg, CDialog)

CPreviewDlg::CPreviewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPreviewDlg::IDD, pParent)
{
	m_nType = 0;
	m_bEnableClose = true;
}

CPreviewDlg::~CPreviewDlg()
{
}

void CPreviewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPreviewDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

BOOL CPreviewDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	CPUimageView* pView = (CPUimageView*)pMain->GetActiveView();

	scrollSign = FALSE;

	CRect rect;
	GetClientRect(&rect);

	yCurrentScroll = 0;
	yScrollMax = 0;
	yScrollMin = 0;

	xCurrentScroll = 0;
	xScrollMax = 0;
	xScrollMin = 0;

	xScrollMax = max(pView->m_nTempWidth - rect.Width(), 0);
	scroll.cbSize = sizeof(scroll);
	scroll.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
	scroll.nMin = xScrollMin;
	scroll.nMax = pView->m_nTempWidth;
	scroll.nPage = rect.Width();
	scroll.nPos = 0;
	SetScrollInfo(SB_HORZ, &scroll, TRUE);

	yScrollMax = max(pView->m_nTempHeight - rect.Height(), 0);
	scroll.cbSize = sizeof(scroll);
	scroll.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
	scroll.nMin = yScrollMin;
	scroll.nMax = pView->m_nTempHeight;
	scroll.nPage = rect.Height();
	scroll.nPos = 0;
	SetScrollInfo(SB_VERT, &scroll, TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
void CPreviewDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	CPUimageView* pView = (CPUimageView*)pMain->GetActiveView();

	CDC*	pDC = GetDC();
	CDC		memDC;
	CBitmap MemBitmap;
	CRect	rect;

	// get the region
	GetClientRect(rect);

	//initial
	memDC.CreateCompatibleDC(NULL);

	MemBitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());

	memDC.SelectObject(MemBitmap);
	memDC.FillSolidRect(0, 0, rect.Width(), rect.Height(), RGB(255, 255, 255));

	// Do not call CDialog::OnPaint() for painting messages
	if (scrollSign)
	{
		Graphics graph(memDC.m_hDC);
		Bitmap bitmap(pView->m_nTempWidth, pView->m_nTempHeight, pView->m_nTempWidth * 4, PixelFormat32bppRGB, pView->m_pImageTempBuffer);
		graph.DrawImage(&bitmap, -xCurrentScroll, -yCurrentScroll);
	}
	else
	{
		Graphics graph(memDC.m_hDC);
		Bitmap bitmap(pView->m_nTempWidth, pView->m_nTempHeight, pView->m_nTempWidth * 4, PixelFormat32bppRGB, pView->m_pImageTempBuffer);
		graph.DrawImage(&bitmap, -xCurrentScroll, -yCurrentScroll);

		CRect rect;
		GetClientRect(&rect);

		xScrollMax = max(pView->m_nTempWidth - rect.Width(), 0);
		scroll.cbSize = sizeof(scroll);
		scroll.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
		scroll.nMin = xScrollMin;
		scroll.nMax = pView->m_nTempWidth;
		scroll.nPage = rect.Width();
		scroll.nPos = 0;
		SetScrollInfo(SB_HORZ, &scroll, TRUE);

		yScrollMax = max(pView->m_nTempHeight - rect.Height(), 0);
		scroll.cbSize = sizeof(scroll);
		scroll.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
		scroll.nMin = yScrollMin;
		scroll.nMax = pView->m_nTempHeight;
		scroll.nPage = rect.Height();
		scroll.nPos = 0;
		SetScrollInfo(SB_VERT, &scroll, TRUE);
	}

	// copy
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

	ReleaseDC(pDC);
}

/******************************************************************************
*level deal with the image
******************************************************************************/
void CPreviewDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	int xDelta;
	int yDelta = 0;

	xCurrentScroll = GetScrollPos(SB_HORZ);

	switch (nSBCode)
	{
	case SB_PAGEUP:
		xCurrentScroll -= 20;
		break;
	case SB_PAGEDOWN:
		xCurrentScroll += 20;
		break;
	case SB_LINELEFT:
		xCurrentScroll -= 5;
		break;
	case SB_LINERIGHT:
		xCurrentScroll += 5;
		break;
	case SB_THUMBPOSITION:
		xCurrentScroll = nPos;
		break;
	case SB_THUMBTRACK:
		xCurrentScroll = nPos;
		break;
	default:;
	}

	xCurrentScroll = max(0, xCurrentScroll);
	xCurrentScroll = min(xScrollMax, xCurrentScroll);

	if (xCurrentScroll == GetScrollPos(SB_HORZ))return;

	scrollSign = TRUE;
	xDelta = xCurrentScroll - GetScrollPos(SB_HORZ);

	ScrollWindowEx(-xDelta, -yDelta, NULL, NULL, NULL, (LPRECT)NULL, SW_INVALIDATE);
	UpdateWindow();

	SetScrollPos(SB_HORZ, xCurrentScroll, TRUE);

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

/******************************************************************************
*�verticle
******************************************************************************/
void CPreviewDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	int xDelta = 0;
	int yDelta;
	int yNewPos;

	yCurrentScroll = GetScrollPos(SB_VERT);

	switch (nSBCode)
	{
	case SB_PAGEUP:
		yNewPos = yCurrentScroll - 20;
		break;
	case SB_PAGEDOWN:
		yNewPos = yCurrentScroll + 20;
		break;
	case SB_LINEUP:
		yNewPos = yCurrentScroll - 5;
		break;
	case SB_LINEDOWN:
		yNewPos = yCurrentScroll + 5;
		break;
	case SB_THUMBPOSITION:
		yNewPos = nPos;
		break;
	case SB_THUMBTRACK:
		yNewPos = nPos;
		break;
	default:
		yNewPos = yCurrentScroll;
	}

	yNewPos = max(0, yNewPos);
	yNewPos = min(yScrollMax, yNewPos);

	if (yNewPos == yCurrentScroll)
		return;

	scrollSign = TRUE;
	yDelta = yNewPos - yCurrentScroll;
	yCurrentScroll = yNewPos;

	ScrollWindowEx(-xDelta, -yDelta, NULL, NULL, NULL, (LPRECT)NULL, SW_INVALIDATE);
	UpdateWindow();

	SetScrollPos(SB_VERT, yCurrentScroll, TRUE);

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CPreviewDlg::OnDestroy()
{
	CDialog::OnDestroy();

	if (m_nType == 0)
		delete this;
}

BOOL CPreviewDlg::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void CPreviewDlg::OnOK()
{
	//OnOK();
}

void CPreviewDlg::OnCancel()
{
	if (m_bEnableClose)
	{
		CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
		CPUimageView* pView = (CPUimageView*)pMain->GetActiveView();

		if (m_nType == 2)
			if (IDYES == MessageBox(L"The image is changed, whether to save", L"PU image", MB_YESNO))
				pView->OnFileSave();

		CDialog::OnCancel();
	}
}