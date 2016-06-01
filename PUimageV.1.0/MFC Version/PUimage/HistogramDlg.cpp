// HistogramDlg.cpp
//

#include "stdafx.h"
#include "PUimage.h"
#include "HistogramDlg.h"
#include "Mainfrm.h"
#include "PUimageDoc.h"
#include "PUimageView.h"

IMPLEMENT_DYNAMIC(CHistogramDlg, CDialog)

CHistogramDlg::CHistogramDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHistogramDlg::IDD, pParent)
	, m_nLimitLow(0)
	, m_nLimitUp(255)
	, m_nGray(0)
	, m_dPer(0)
{
	memset(m_lCounts, 0, sizeof(long) * 256);
	m_nIsDraging = DT_NULL;
}

CHistogramDlg::~CHistogramDlg()
{
}

void CHistogramDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_LIMIT_LOWER, m_nLimitLow);
	DDX_Text(pDX, IDC_LIMIT_UP, m_nLimitUp);
	DDX_Control(pDX, IDC_HISTOGRAM, m_stiHistogram);
	DDX_Text(pDX, IDC_STATIC_GRAY, m_nGray);
	DDX_Text(pDX, IDC_STATIC_PER, m_dPer);
}


BEGIN_MESSAGE_MAP(CHistogramDlg, CDialog)
	ON_EN_CHANGE(IDC_LIMIT_LOWER, &CHistogramDlg::OnEnChangeLimitLower)
	ON_EN_CHANGE(IDC_LIMIT_UP, &CHistogramDlg::OnEnChangeLimitUp)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CHistogramDlg 

/******************************************************************************
*	Initially calculate the number of gray
******************************************************************************/
BOOL CHistogramDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	CPUimageView* pView = (CPUimageView*)pMain->GetActiveView();

	for (UINT i = 0; i < pView->m_nPicWidth * pView->m_nPicHeight; i++)
	{
		int value = pView->m_pImageTempBuffer[i * 4];

		m_lCounts[value]++;
	}

	// Calculate pixel number
	m_nPixelCount = pView->m_nPicWidth * pView->m_nPicHeight;

	return TRUE;  // return TRUE unless you set the focus to a control

}


/******************************************************************************
*	Change the gray lower
******************************************************************************/
void CHistogramDlg::OnEnChangeLimitLower()
{
	UpdateData(TRUE);

	// limited
	if (m_nLimitLow < 0)
		m_nLimitLow = 0;
	else if (m_nLimitLow > 255)
		m_nLimitLow = 255;

	//If lower is bigger than upper, then swap them
	if (m_nLimitLow > m_nLimitUp)
	{
		int nTemp = m_nLimitLow;
		m_nLimitLow = m_nLimitUp;
		m_nLimitUp = nTemp;
	}

	Refresh();
	UpdateData(FALSE);
}


/******************************************************************************
*	Change the gray upper
******************************************************************************/
void CHistogramDlg::OnEnChangeLimitUp()
{
	UpdateData(TRUE);

	// limited
	if (m_nLimitUp < 0)
		m_nLimitUp = 0;
	else if (m_nLimitUp > 255)
		m_nLimitUp = 255;

	if (m_nLimitLow > m_nLimitUp)
	{
		int nTemp = m_nLimitLow;
		m_nLimitLow = m_nLimitUp;
		m_nLimitUp = nTemp;
	}

	Refresh();
	UpdateData(FALSE);
}

/******************************************************************************
*	Draw
******************************************************************************/
void CHistogramDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	Refresh();
}

/******************************************************************************
*	Refresh histogram diagram
******************************************************************************/
void CHistogramDlg::Refresh()
{
	CDC*	pDC = m_stiHistogram.GetDC();
	CRect	rect;
	CDC		memDC;
	CBitmap MemBitmap;

	// drarw
	m_stiHistogram.GetClientRect(rect);

	// initial
	memDC.CreateCompatibleDC(NULL);

	MemBitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());

	memDC.SelectObject(MemBitmap);
	memDC.FillSolidRect(0, 0, rect.Width(), rect.Height(), RGB(255, 255, 255));

	Graphics graph(memDC.GetSafeHdc());

	//white background
	graph.FillRectangles(&SolidBrush(Color::White),
		&Rect(0, 0, rect.Width(), rect.Height()),
		1);

	// draw x
	graph.DrawLine(&Pen(Color::Black), 10, 10, 10, 280);
	graph.DrawLine(&Pen(Color::Black), 10, 10, 5, 15);
	graph.DrawLine(&Pen(Color::Black), 10, 10, 15, 15);

	// draw y
	graph.DrawLine(&Pen(Color::Black), 10, 280, 290, 280);
	graph.DrawLine(&Pen(Color::Black), 290, 280, 285, 285);
	graph.DrawLine(&Pen(Color::Black), 290, 280, 285, 275);

	// draw (0,0)
	CString strNum;
	Font font(L"ËÎÌו", 10);
	strNum = L"0";
	graph.DrawString(strNum, -1, &font,
		PointF(8, 290), &SolidBrush(Color::Black));

	for (int i = 0; i < 256; i += 5)
	{
		if (i % 50 == 0)
			graph.DrawLine(&Pen(Color::Black), 10 + i, 280, 10 + i, 286);
		else if (i % 10 == 0)
			graph.DrawLine(&Pen(Color::Black), 10 + i, 280, 10 + i, 283);
	}

	//draw x line
	strNum = L"50";
	graph.DrawString(strNum, -1, &font,
		PointF(53, 290), &SolidBrush(Color::Black));
	strNum = L"100";
	graph.DrawString(strNum, -1, &font,
		PointF(100, 290), &SolidBrush(Color::Black));
	strNum = L"150";
	graph.DrawString(strNum, -1, &font,
		PointF(150, 290), &SolidBrush(Color::Black));
	strNum = L"200";
	graph.DrawString(strNum, -1, &font,
		PointF(200, 290), &SolidBrush(Color::Black));
	strNum = L"255";
	graph.DrawString(strNum, -1, &font,
		PointF(255, 290), &SolidBrush(Color::Black));

	//draw current gray region
	Pen pen(Color::Blue);

	pen.SetDashStyle(DashStyleDash);

	graph.DrawLine(&pen, 10 + m_nLimitLow, 280, 10 + m_nLimitLow, 10);
	graph.DrawLine(&pen, 10 + m_nLimitUp, 280, 10 + m_nLimitUp, 10);

	long lMax = 0;
	REAL dHeight = 0.0;

	// find the maxium
	for (int i = m_nLimitLow; i <= m_nLimitUp; i++)
		lMax = max(lMax, m_lCounts[i]);

	//draw y line
	strNum.Format(L"%d", lMax);
	graph.DrawString(strNum, -1, &font,
		PointF(10, 25), &SolidBrush(Color::Black));

	//draw the diagram
	for (int i = m_nLimitLow; i <= m_nLimitUp; i++)
	{
		dHeight = (REAL)(m_lCounts[i]) / lMax * 250;
		graph.DrawLine(&Pen(Color::Gray), i + 10.0f, 280.0f, i + 10.0f, 280 - dHeight);
	}

	// Copy
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

	m_stiHistogram.ReleaseDC(pDC);
}

/******************************************************************************
*	Mouse movement
******************************************************************************/
void CHistogramDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	CRect rect;

	m_stiHistogram.GetWindowRect(rect);

	if ((nFlags & MK_LBUTTON) && m_nIsDraging)
	{
		// offset
		int offset = point.x - m_psMove.x;

		// if offset is upper
		if (m_nIsDraging == DT_UP)
		{
			// if it is not over
			if ((offset + m_nLimitUp) <= 255)
			{
				if ((offset + m_nLimitUp) >= m_nLimitLow)
					m_nLimitUp += offset;
				else
					m_nLimitUp = m_nLimitLow;
			}
			else
				m_nLimitUp = 255;
		}
		else
		{
			// if it is not over
			if ((offset + m_nLimitLow) >= 0)
			{
				if ((offset + m_nLimitLow) <= m_nLimitUp)
					m_nLimitLow += offset;
				else
					m_nLimitLow = m_nLimitUp;
			}
			else
				m_nLimitLow = 0;
		}

		UpdateData(FALSE);
		Refresh();

		m_psMove = point;
	}
	else
		m_nIsDraging = DT_NULL;

	ClientToScreen(&point);

	// the mouse is in the gray position, if it is not in the 0-255 
	int x = point.x - rect.left - 10;

	if (abs(x - m_nLimitUp) > 3 && abs(x - m_nLimitLow) > 3)
		m_nIsDraging = DT_NULL;

	//if mouse is in the diagram
	if (rect.PtInRect(point))
	{
		if (x >= m_nLimitLow && x <= m_nLimitUp)
		{
			m_nGray = x;
			m_dPer = float(m_lCounts[x]) / m_nPixelCount * 100;
		}

		UpdateData(FALSE);
	}
}

BOOL CHistogramDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	CRect rect;
	CPoint point;

	GetCursorPos(&point);
	m_stiHistogram.GetWindowRect(rect);
	if (rect.PtInRect(point))
	{
		int x = point.x - rect.left - 10;

		if (abs(x - m_nLimitUp) <= 3 || abs(x - m_nLimitLow) <= 3)
		{
			SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
			return TRUE;
		}
	}

	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}

/******************************************************************************
*	check whether it is in the region between the lower and upper
******************************************************************************/
void CHistogramDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect rect;
	CPoint oldPoint = point;

	m_stiHistogram.GetWindowRect(rect);
	ClientToScreen(&point);
	int x = point.x - rect.left - 10;

	if (abs(x - m_nLimitUp) <= 3)
	{
		m_psMove = oldPoint;
		m_nIsDraging = DT_UP;
	}
	else if (abs(x - m_nLimitLow) <= 3)
	{
		m_psMove = oldPoint;
		m_nIsDraging = DT_LOW;
	}
}

/******************************************************************************
*	Release the mouse
******************************************************************************/
void CHistogramDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_nIsDraging = DT_NULL;
}
