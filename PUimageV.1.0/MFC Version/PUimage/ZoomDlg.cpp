// ZoomDlg.cpp 
//

#include "stdafx.h"
#include "PUimage.h"
#include "ZoomDlg.h"
#include "GeoOperator.h"
#include "Mainfrm.h"
#include "PUimageDoc.h"
#include "PUimageView.h"


IMPLEMENT_DYNAMIC(CZoomDlg, CDialog)

CZoomDlg::CZoomDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CZoomDlg::IDD, pParent)
	, m_nWidth(0)
	, m_nHeight(0)
	, m_nType(0)
	, m_bIsPro(TRUE)
{
}

CZoomDlg::~CZoomDlg()
{
}

void CZoomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_WIDTH, m_nWidth);
	DDX_Text(pDX, IDC_HEIGHT, m_nHeight);
	DDX_CBIndex(pDX, IDC_MODE, m_nType);
	DDX_Check(pDX, IDC_PRO, m_bIsPro);
}


BEGIN_MESSAGE_MAP(CZoomDlg, CDialog)
	ON_BN_CLICKED(IDC_PREV, &CZoomDlg::OnBnClickedPrev)
	ON_EN_CHANGE(IDC_WIDTH, &CZoomDlg::OnEnChangeWidth)
	ON_EN_CHANGE(IDC_HEIGHT, &CZoomDlg::OnEnChangeHeight)
	ON_BN_CLICKED(IDC_PRO, &CZoomDlg::OnBnClickedPro)
	ON_BN_CLICKED(IDC_SAVE, &CZoomDlg::OnBnClickedSave)
	ON_BN_CLICKED(IDOK, &CZoomDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CZoomDlg 消息处理程序

/******************************************************************************
*	Preview
******************************************************************************/
void CZoomDlg::OnBnClickedPrev()
{
	Refresh();

	CPreviewDlg dlg;
	dlg.m_nType = 1;
	dlg.DoModal();
}

/******************************************************************************
*	Rezoom
******************************************************************************/
void CZoomDlg::Refresh()
{
	UpdateData(TRUE);

	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	CPUimageView* pView = (CPUimageView*)pMain->GetActiveView();
	double fx = (double)m_nWidth / pView->m_nPicWidth;
	double fy = (double)m_nHeight / pView->m_nPicHeight;

	SAFE_DELETE_ARRAY(pView->m_pImageTempBuffer);

	if (m_nType == 0)
		ZoomNormal(pView->m_pImageBuffer, pView->m_pImageTempBuffer,
			pView->m_nPicWidth, pView->m_nPicHeight, pView->m_nTempWidth,
			pView->m_nTempHeight, fx, fy);
	else
		ZoomInterpolation(pView->m_pImageBuffer, pView->m_pImageTempBuffer,
			pView->m_nPicWidth, pView->m_nPicHeight,
			pView->m_nTempWidth, pView->m_nTempHeight,
			fx, fy);
	m_bModify = true;
}

/******************************************************************************
*	Initial
******************************************************************************/
BOOL CZoomDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	CPUimageView* pView = (CPUimageView*)pMain->GetActiveView();

	m_nWidth = m_nSrcWidth = pView->m_nPicWidth;
	m_nHeight = m_nSrcHeight = pView->m_nPicHeight;

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CZoomDlg::OnEnChangeWidth()
{
	UpdateData(TRUE);

	if (m_nWidth > 4000)
		m_nWidth = 4000;
	if (m_nWidth <= 0)
		m_nWidth = 1;

	UpdateData(FALSE);
	RefreshSize(true);
}

void CZoomDlg::OnEnChangeHeight()
{
	UpdateData(TRUE);

	if (m_nHeight > 4000)
		m_nHeight = 4000;
	if (m_nHeight <= 0)
		m_nHeight = 1;

	UpdateData(FALSE);
	RefreshSize(false);
}

void CZoomDlg::OnBnClickedPro()
{
	RefreshSize(true);
}

/******************************************************************************
*	Calculate the size of image
******************************************************************************/
void CZoomDlg::RefreshSize(bool width)
{
	UpdateData(TRUE);

	if (!m_bIsPro)
		return;

	if (width)	//based on the width to modify the height
	{
		double fx = (double)m_nWidth / m_nSrcWidth;
		m_nHeight = (int)(m_nSrcHeight * fx);
	}
	else		//based on the height to modify the width
	{
		double fy = (double)m_nHeight / m_nSrcHeight;
		m_nWidth = (int)(m_nSrcWidth * fy);
	}

	UpdateData(FALSE);
}

void CZoomDlg::OnBnClickedSave()
{
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	CPUimageView* pView = (CPUimageView*)pMain->GetActiveView();

	Refresh();
	pView->OnFileSave();
	m_bModify = false;
}

void CZoomDlg::OnBnClickedOk()
{
	if (m_bModify)
	{
		if (IDYES == MessageBox(L"The image is changed, whether to save it", L"PU image", MB_YESNO))
			OnBnClickedSave();
	}

	OnOK();
}
