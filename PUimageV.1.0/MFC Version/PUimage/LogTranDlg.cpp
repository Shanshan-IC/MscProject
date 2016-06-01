// LogTranDlg.cpp 
//

#include "stdafx.h"
#include "PUimage.h"
#include "LogTranDlg.h"
#include "GrayOperator.h"
#include "Mainfrm.h"
#include "PUimageDoc.h"
#include "PUimageView.h"
#include <cmath>


IMPLEMENT_DYNAMIC(CLogTranDlg, CDialog)

CLogTranDlg::CLogTranDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLogTranDlg::IDD, pParent)
	, m_nPosA(0)
	, m_nPosB(0)
	, m_nA(0)
	, m_nB(0)
{

}

CLogTranDlg::~CLogTranDlg()
{
	SAFE_DELETE(dlg);
}

void CLogTranDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Slider(pDX, IDC_SLIDERA, m_nPosA);
	DDX_Slider(pDX, IDC_SLIDERB, m_nPosB);
	DDX_Text(pDX, IDC_EDITA, m_nA);
	DDX_Text(pDX, IDC_EDITB, m_nB);
	DDX_Control(pDX, IDC_PREV, m_stiPrev);
}


BEGIN_MESSAGE_MAP(CLogTranDlg, CDialog)
	ON_EN_CHANGE(IDC_EDITA, &CLogTranDlg::OnEnChangeEdita)
	ON_EN_CHANGE(IDC_EDITB, &CLogTranDlg::OnEnChangeEditb)
	ON_WM_HSCROLL()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_SAVE, &CLogTranDlg::OnBnClickedSave)
	ON_BN_CLICKED(IDOK, &CLogTranDlg::OnBnClickedOk)
END_MESSAGE_MAP()


/******************************************************************************
*	Initial Dialog
******************************************************************************/
BOOL CLogTranDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	dlg = new CPreviewDlg(this);

	dlg->m_nType = 1;
	dlg->m_bEnableClose = false;
	dlg->Create(IDD_PREVIEW);
	dlg->ShowWindow(SW_SHOW);

	m_nA = m_nPosA = 0;
	m_nPosA = 50;
	m_nB = m_nPosB = 25;
	UpdateData(FALSE);

	((CSliderCtrl*)GetDlgItem(IDC_SLIDERA))->SetRange(-100, 100);

	return TRUE;  // return TRUE unless you set the focus to a control

}

/******************************************************************************
*	Refresh
******************************************************************************/
void CLogTranDlg::Refresh()
{
	UpdateData(TRUE);


	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	CPUimageView* pView = (CPUimageView*)pMain->GetActiveView();

	LogTrans(pView->m_pImageBuffer, pView->m_pImageTempBuffer,
		pView->m_nPicWidth, pView->m_nPicHeight, m_nA, m_nB * 0.001);

	dlg->Refresh();

	CDC*	pDC = m_stiPrev.GetDC();
	CRect	rect;
	CDC		memDC;
	CBitmap MemBitmap;

	m_stiPrev.GetClientRect(rect);

	memDC.CreateCompatibleDC(NULL);

	MemBitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());

	memDC.SelectObject(MemBitmap);
	memDC.FillSolidRect(0, 0, rect.Width(), rect.Height(), RGB(255, 255, 255));

	Graphics graph(memDC.GetSafeHdc());

	graph.FillRectangles(&SolidBrush(Color::White),
		&Rect(0, 0, rect.Width(), rect.Height()),
		1);

	graph.DrawLine(&Pen(Color::Black), 10, 10, 10, 280);
	graph.DrawLine(&Pen(Color::Black), 10, 10, 5, 15);
	graph.DrawLine(&Pen(Color::Black), 10, 10, 15, 15);

	graph.DrawLine(&Pen(Color::Black), 10, 280, 290, 280);
	graph.DrawLine(&Pen(Color::Black), 290, 280, 285, 285);
	graph.DrawLine(&Pen(Color::Black), 290, 280, 285, 275);

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
	// y
	graph.DrawString(strNum, -1, &font,
		PointF(10, 25), &SolidBrush(Color::Black));

	Matrix matrix1;
	Matrix matrix2(0, 1, 1, 0, 0, 0);	//

	matrix1.Translate(10, 280);
	matrix1.Rotate(270);
	matrix1.Multiply(&matrix2);
	graph.SetTransform(&matrix1);


	// mapping table
	double map[256];

	// calculate
	for (int i = 0; i < 256; i++)
		map[i] = log((double)i + 1.0) / (double)(m_nB*0.001) + m_nA;


	GraphicsPath path;

	path.StartFigure();
	for (int i = 0; i < 255; i++)
		path.AddLine(i, (int)map[i], i + 1, (int)map[i + 1]);

	graph.DrawPath(&Pen(Color::Black), &path);

	// copy
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

	m_stiPrev.ReleaseDC(pDC);
}

/******************************************************************************
*	Change the parameter A
******************************************************************************/
void CLogTranDlg::OnEnChangeEdita()
{
	UpdateData(TRUE);

	if (m_nA < -100)
		m_nA = 100;
	else if (m_nA > 100)
		m_nA = 100;

	m_nPosA = m_nA;
	UpdateData(FALSE);
	Refresh();
	m_bModify = true;
}

/******************************************************************************
*	Change the parameter B
******************************************************************************/
void CLogTranDlg::OnEnChangeEditb()
{
	UpdateData(TRUE);

	if (m_nB < 0)
		m_nB = 0;
	else if (m_nB > 100)
		m_nB = 100;

	m_nPosB = m_nB;
	UpdateData(FALSE);
	Refresh();
	m_bModify = true;
}

/******************************************************************************
*	Scroll
******************************************************************************/
void CLogTranDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	UpdateData(TRUE);

	if (pScrollBar == GetDlgItem(IDC_SLIDERA))
		m_nA = m_nPosA;
	else
		m_nB = m_nPosB;

	UpdateData(FALSE);
	Refresh();
	m_bModify = true;

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

/******************************************************************************
*	painting
******************************************************************************/
void CLogTranDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	Refresh();
}

void CLogTranDlg::OnBnClickedSave()
{
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	CPUimageView* pView = (CPUimageView*)pMain->GetActiveView();

	pView->OnFileSave();
	m_bModify = false;
}


void CLogTranDlg::OnBnClickedOk()
{
	if (m_bModify)
	{
		if (IDYES == MessageBox(L"The image is changed, whether to save it", L"PU image", MB_YESNO))
			OnBnClickedSave();
	}

	OnOK();
}