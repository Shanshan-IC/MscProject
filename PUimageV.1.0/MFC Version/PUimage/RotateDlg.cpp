// RotateDlg.cpp 
//

#include "stdafx.h"
#include "PUimage.h"
#include "RotateDlg.h"
#include "GeoOperator.h"
#include "Mainfrm.h"
#include "PUimageDoc.h"
#include "PUimageView.h"


#define PI 3.1415926535

IMPLEMENT_DYNAMIC(CRotateDlg, CDialog)

CRotateDlg::CRotateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRotateDlg::IDD, pParent)
	, m_nAngle(0)
	, m_nPos(0)
	, m_nType(0)
{
}

CRotateDlg::~CRotateDlg()
{
}

void CRotateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ANGLE, m_nAngle);
	DDX_Slider(pDX, IDC_SLIDER, m_nPos);
	DDX_CBIndex(pDX, IDC_MODE, m_nType);
}

BEGIN_MESSAGE_MAP(CRotateDlg, CDialog)
	ON_BN_CLICKED(IDC_PREV, &CRotateDlg::OnBnClickedPrev)
	ON_EN_CHANGE(IDC_ANGLE, &CRotateDlg::OnEnChangeAngle)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_SAVE, &CRotateDlg::OnBnClickedSave)
	ON_BN_CLICKED(IDOK, &CRotateDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CRotateDlg

/******************************************************************************
*	Initial
******************************************************************************/
BOOL CRotateDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Change the range of rotation angle
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER))->SetRange(0, 360);

	return TRUE;  // return TRUE unless you set the focus to a control

}

/******************************************************************************
*	Preview
******************************************************************************/
void CRotateDlg::OnBnClickedPrev()
{
	Refresh();

	CPreviewDlg dlg;
	dlg.m_nType = 1;
	dlg.DoModal();
}

/******************************************************************************
*	Re-rotate
******************************************************************************/
void CRotateDlg::Refresh()
{
	UpdateData(TRUE);

	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	CPUimageView* pView = (CPUimageView*)pMain->GetActiveView();

	SAFE_DELETE_ARRAY(pView->m_pImageTempBuffer);

	if (m_nType == 0)
		RotateNormal(pView->m_pImageBuffer, pView->m_pImageTempBuffer,
			pView->m_nPicWidth, pView->m_nPicHeight, pView->m_nTempWidth,
			pView->m_nTempHeight, m_nAngle / 180.0 * PI);
	else
		RotateInterpolation(pView->m_pImageBuffer, pView->m_pImageTempBuffer,
			pView->m_nPicWidth, pView->m_nPicHeight, pView->m_nTempWidth,
			pView->m_nTempHeight, m_nAngle / 180.0 * PI);
}

/******************************************************************************
*	when changing the angle
******************************************************************************/
void CRotateDlg::OnEnChangeAngle()
{
	UpdateData(TRUE);

	if (m_nAngle < 0)
		m_nAngle = 0;
	if (m_nAngle > 360)
		m_nAngle = 360;

	m_nPos = m_nAngle;

	UpdateData(FALSE);
}

/******************************************************************************
*	levle scroll
******************************************************************************/
void CRotateDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	UpdateData(TRUE);
	m_nAngle = m_nPos;
	UpdateData(FALSE);

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CRotateDlg::OnBnClickedSave()
{
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	CPUimageView* pView = (CPUimageView*)pMain->GetActiveView();

	Refresh();
	pView->OnFileSave();
	m_bModify = false;
}

void CRotateDlg::OnBnClickedOk()
{
	if (m_bModify)
	{
		if (IDYES == MessageBox(L"The image is changed, whether to save it", L"PU image", MB_YESNO))
			OnBnClickedSave();
	}

	OnOK();
}
