// MainFrm.cpp : CMainFrame Class
//

#include "stdafx.h"
#include "PUimage.h"

#include "MainFrm.h"

#include "PUimageDoc.h"
#include "PUimageView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_NOTIFY(TVN_ITEMEXPANDED, IDC_MYTREECTRL, OnItemexpandedTree)
	ON_NOTIFY(TVN_SELCHANGED, IDC_MYTREECTRL, OnSelchangedTree)
	ON_COMMAND(ID_VIEW_CONTROL, &CMainFrame::OnViewControl)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CONTROL, &CMainFrame::OnUpdateViewControl)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_INDICATOR_PICNUM,	// number of image
	ID_INDICATOR_PICNAME,	// current image name 
	ID_SEPARATOR,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame structure

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create the tool bar¸\n");
		return -1;
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
			sizeof(indicators) / sizeof(UINT)))
	{
		TRACE0("Failed to create status bar¸\n");
		return -1;
	}

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	CreateCtrlBar();

	return 0;
}

/******************************************************************************
*	Create control windows
*	including the files directory and bitmap windows
******************************************************************************/
BOOL CMainFrame::CreateCtrlBar(void)
{
	if (!m_wndCtrlBar.Create(L"Control Window", this, 100))
	{
		TRACE0("Failed to create control windows.\n");
		return -1;
	}

	m_wndCtrlBar.SetBarStyle(m_wndCtrlBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	m_wndCtrlBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndCtrlBar, AFX_IDW_DOCKBAR_LEFT);	// On the left

															// Create tab control
	m_TabCtrl.Create(TCS_DOWN | WS_CHILD | WS_VISIBLE, CRect(0, 0, 100, 100), &m_wndCtrlBar, 125);

	// Create tree control
	if (!m_TreeCtrl.Create(WS_CHILD | WS_VISIBLE |
		TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT,
		CRect(0, 0, 0, 0), &m_TabCtrl, IDC_MYTREECTRL))
	{
		TRACE0("Fail to create.\n");
		return -1;
	}

	m_TreeCtrl.ModifyStyleEx(0, WS_EX_CLIENTEDGE);

	DWORD dwStyle = GetWindowLong(m_TreeCtrl.m_hWnd, GWL_STYLE);

	dwStyle |= TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT;
	SetWindowLong(m_TreeCtrl.m_hWnd, GWL_STYLE, dwStyle);

	m_hRoot = m_TreeCtrl.InsertItem(L"My computer");
	InsertLogicalDrives(m_hRoot);
	InsertDriveDir(m_hRoot);
	m_TreeCtrl.Expand(m_hRoot, TVE_EXPAND);

	// Add tree control to the tab control
	m_TabCtrl.AddPage(&m_TreeCtrl, L"Files List", IDI_DIR);
	m_TabCtrl.AddPage(RUNTIME_CLASS(CPrevDlg), IDD_PREV, L"Bitmaps", IDI_DIR);
	m_TabCtrl.UpdateWindow();

	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWnd::PreCreateWindow(cs))
		return FALSE;
	cs.style &= ~FWS_ADDTOTITLE;

	return TRUE;
}

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame Message program

/******************************************************************************
*	Insert system drive nodes to required parents node
******************************************************************************/
void CMainFrame::InsertLogicalDrives(HTREEITEM hParent)
{
	DWORD	szAllDriveStrings = GetLogicalDriveStrings(0, NULL);
	LPWSTR	pDriveStrings = new WCHAR[szAllDriveStrings + sizeof(_T(""))];
	LPWSTR	pDel = pDriveStrings;
	GetLogicalDriveStrings(szAllDriveStrings, pDriveStrings);
	size_t szDriveString = wcslen(pDriveStrings);
	while (szDriveString > 0)
	{
		m_TreeCtrl.InsertItem(pDriveStrings, hParent);
		pDriveStrings += szDriveString + 1;
		szDriveString = wcslen(pDriveStrings);
	}

	SAFE_DELETE_ARRAY(pDel);
}

/******************************************************************************
*	Insert all children of drive disks to required parents node
******************************************************************************/
void CMainFrame::InsertDriveDir(HTREEITEM hParent)
{
	HTREEITEM hChild = m_TreeCtrl.GetChildItem(hParent);
	while (hChild)
	{
		CString strText = m_TreeCtrl.GetItemText(hChild);
		if (strText.Right(1) != L"\\")
			strText += L"\\";
		strText += L"*.*";
		CFileFind file;
		BOOL bContinue = file.FindFile(strText);
		while (bContinue)
		{
			bContinue = file.FindNextFile();
			if (!file.IsDots())
				m_TreeCtrl.InsertItem(file.GetFileName(), hChild);
		}
		InsertDriveDir(hChild);
		hChild = m_TreeCtrl.GetNextItem(hChild, TVGN_NEXT);
		file.Close();
	}
}

/******************************************************************************
*	Insert sub direcotry to required parents node
******************************************************************************/
void CMainFrame::AddSubDir(HTREEITEM hParent)
{
	CString strPath = GetFullPath(hParent);
	if (strPath.Right(1) != "\\")
		strPath += "\\";
	strPath += L"*.*";
	CFileFind file;
	BOOL bContinue = file.FindFile(strPath);
	while (bContinue)
	{
		bContinue = file.FindNextFile();
		if (!file.IsDots())
			m_TreeCtrl.InsertItem(file.GetFileName(), hParent);
	}
}

/******************************************************************************
*	Get the nodes full path
******************************************************************************/
CString CMainFrame::GetFullPath(HTREEITEM hCurrent)
{
	CString strTemp;
	CString strReturn = L"";
	while (hCurrent != m_hRoot)
	{
		strTemp = m_TreeCtrl.GetItemText(hCurrent);
		if (strTemp.Right(1) != "\\")
			strTemp += L"\\";
		strReturn = strTemp + strReturn;
		hCurrent = m_TreeCtrl.GetParentItem(hCurrent);
	}

	return strReturn;
}

/******************************************************************************
*	Open the tree view function
******************************************************************************/
void CMainFrame::OnItemexpandedTree(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	TVITEM item = pNMTreeView->itemNew;
	if (item.hItem == m_hRoot)
		return;
	HTREEITEM hChild = m_TreeCtrl.GetChildItem(item.hItem);
	while (hChild)
	{
		AddSubDir(hChild);
		hChild = m_TreeCtrl.GetNextItem(hChild, TVGN_NEXT);
	}
	*pResult = 0;
}

/******************************************************************************
*	Get the image name based on the path
******************************************************************************/
void CMainFrame::GetAllFileNames(const CString& path, CStringArray& ary)
{
	ary.RemoveAll();

	CFileFind fileFind;
	CString filesPath = path + L"\\*.*";

	if (fileFind.FindFile(filesPath))
	{

		CString strPicPath;
		CString strExt;

		// If there are files  in the directory
		while (fileFind.FindNextFile())
		{
			strPicPath = fileFind.GetFileName();
			// Get the suffix
			strExt = strPicPath.Right(3);
			strExt.MakeLower();

			// If the suffix is bmp or jpg, then it is image file
			if (strExt == "bmp" || strExt == "jpg")
				ary.Add(strPicPath);
		}

		strPicPath = fileFind.GetFileName();
		//Get the suffix
		strExt = strPicPath.Right(3);
		strExt.MakeLower();

		// If the suffix is bmp or jpg, then it is image file
		if (strExt == "bmp" || strExt == "jpg")
			ary.Add(strPicPath);
	}

	fileFind.Close();
}

/******************************************************************************
*	Change tree view function
******************************************************************************/
void CMainFrame::OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	TVITEM item = pNMTreeView->itemNew;
	if (item.hItem == m_hRoot)
		return;
	CString str = GetFullPath(item.hItem);
	str = str.Left(str.GetLength() - 1);
	CFileFind fileFile;

	if (fileFile.FindFile(str))
	{
		CString strExt;

		fileFile.FindNextFile();
		if (!fileFile.IsDirectory() && !fileFile.IsDots())
		{
			strExt = str.Right(3);
			strExt.MakeLower();

			//If the suffix is bmp or jpg, then it is image file
			if (strExt == "bmp" || strExt == "jpg")
			{
				CPUimageView* pView = (CPUimageView*)GetActiveView();

				pView->ClearOffset();
				pView->OpenFile(str);
				pView->FixOffset();
				pView->RefreshIndicator();
			}
		}
	}
	fileFile.Close();

	*pResult = 0;
}

/******************************************************************************
*	Change the size of window
******************************************************************************/
void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);
	CPUimageView* pView = (CPUimageView*)GetActiveView();

	if (pView != NULL)
	{
		pView->ClearOffset();
		pView->FixOffset();
	}
}


/******************************************************************************
*	Control window menu update
******************************************************************************/
void CMainFrame::OnViewControl()
{
	BOOL bVisible = ((m_wndCtrlBar.IsWindowVisible()) != 0);

	ShowControlBar(&m_wndCtrlBar, !bVisible, FALSE);
	RecalcLayout();
}

/******************************************************************************
*	update view control
******************************************************************************/
void CMainFrame::OnUpdateViewControl(CCmdUI *pCmdUI)
{
	BOOL bVisible = ((m_wndCtrlBar.IsWindowVisible()) != 0);
	pCmdUI->SetCheck(bVisible);
}
