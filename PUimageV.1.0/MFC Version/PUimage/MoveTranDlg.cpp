// MoveTranDlg.cpp 

#include "stdafx.h"
#include "PUimage.h"
#include "MoveTranDlg.h"
#include "Mainfrm.h"
#include "PUimageDoc.h"
#include "PUimageView.h"
#include "GeoOperator.h"


// CMoveTranDlg

IMPLEMENT_DYNAMIC(CMoveTranDlg, CDialog)

CMoveTranDlg::CMoveTranDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMoveTranDlg::IDD, pParent)
	, m_nType(0)
	, m_nX(0)
	, m_nY(0)
{

}

CMoveTranDlg::~CMoveTranDlg()
{
	SAFE_DELETE(dlg);
}

void CMoveTranDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_NORMAL, m_nType);
	DDX_Text(pDX, IDC_EDIT_X, m_nX);
	DDX_Text(pDX, IDC_EDIT_Y, m_nY);
}

BEGIN_MESSAGE_MAP(CMoveTranDlg, CDialog)
	ON_BN_CLICKED(IDC_RADIO_NORMAL, &CMoveTranDlg::OnBnClickedRadioNormal)
	ON_BN_CLICKED(IDC_RADIO_SIZE, &CMoveTranDlg::OnBnClickedRadioSize)
	ON_EN_CHANGE(IDC_EDIT_X, &CMoveTranDlg::OnEnChangeEditX)
	ON_EN_CHANGE(IDC_EDIT_Y, &CMoveTranDlg::OnEnChangeEditY)
	ON_BN_CLICKED(IDC_SAVE, &CMoveTranDlg::OnBnClickedSave)
	ON_BN_CLICKED(IDOK, &CMoveTranDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMoveTranDlg

/******************************************************************************
*	On Initial Dialog
******************************************************************************/
BOOL CMoveTranDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	dlg = new CPreviewDlg(this);

	dlg->m_nType = 1;
	dlg->m_bEnableClose = false;
	dlg->Create(IDD_PREVIEW);
	dlg->ShowWindow(SW_SHOW);

	return TRUE;  // return TRUE unless you set the focus to a control
}

/******************************************************************************
*	Refresh
******************************************************************************/
void CMoveTranDlg::Refresh()
{
	UpdateData(TRUE);

	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	CPUimageView* pView = (CPUimageView*)pMain->GetActiveView();

	SAFE_DELETE_ARRAY(pView->m_pImageTempBuffer);
	pView->m_nTempWidth = pView->m_nPicWidth;
	pView->m_nTempHeight = pView->m_nPicHeight;

	if (m_nType == 0)
		MoveTransNormal(pView->m_pImageBuffer, pView->m_pImageTempBuffer,
			pView->m_nPicWidth, pView->m_nPicHeight, m_nX, m_nY);
	else
		MoveTransSize(pView->m_pImageBuffer, pView->m_pImageTempBuffer,
			pView->m_nPicWidth, pView->m_nPicHeight, m_nX, m_nY,
			pView->m_nTempWidth, pView->m_nTempHeight);

	dlg->Refresh();
}

void CMoveTranDlg::OnBnClickedRadioNormal()
{
	Refresh();
}

void CMoveTranDlg::OnBnClickedRadioSize()
{
	Refresh();
}

void CMoveTranDlg::OnEnChangeEditX()
{
	Refresh();
}

void CMoveTranDlg::OnEnChangeEditY()
{
	Refresh();
}

void CMoveTranDlg::OnBnClickedSave()
{
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	CPUimageView* pView = (CPUimageView*)pMain->GetActiveView();

	pView->OnFileSave();
	m_bModify = false;
}

void CMoveTranDlg::OnBnClickedOk()
{
	if (m_bModify)
	{
		if (IDYES == MessageBox(L"The image is changed, whether to save it", L"PU image", MB_YESNO))
			OnBnClickedSave();
	}

	OnOK();
}