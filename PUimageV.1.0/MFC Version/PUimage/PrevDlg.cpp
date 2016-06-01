// PrevDlg.cpp 
//

#include "stdafx.h"
#include "PUimage.h"
#include "PrevDlg.h"

#include "mainfrm.h"

// CPrevDlg

IMPLEMENT_DYNCREATE(CPrevDlg, CDialog)

CPrevDlg::CPrevDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPrevDlg::IDD, pParent)
	, m_strNum(_T(""))
{
	m_nPos = -1;
}

CPrevDlg::~CPrevDlg()
{
	m_FilesNameAry.RemoveAll();
}

void CPrevDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PICNUM, m_strNum);
	DDX_Control(pDX, IDC_SCROLLBAR, m_ScrollBar);
	DDX_Control(pDX, IDC_PREV, m_staPrev);
}


BEGIN_MESSAGE_MAP(CPrevDlg, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_OPEN, &CPrevDlg::OnBnClickedOpen)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


/******************************************************************************
*	draw
******************************************************************************/
void CPrevDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rc;
	GetClientRect(&rc);

	int b = rc.bottom;
	int l = rc.left;
	int r = rc.right;
	int t = rc.top;

	GetDlgItem(IDC_SCROLLBAR)->MoveWindow(l + 5, b - 75, r - 10, 17, true);
	GetDlgItem(IDC_PICNUM)->MoveWindow(r - 120, b - 50, 120, 20, true);
	GetDlgItem(IDC_OPEN)->MoveWindow((r - l) / 2 - 35, b - 30, 80, 22, true);
	m_staPrev.MoveWindow(5, 5, rc.right - rc.left - 10, rc.bottom - rc.top - 80);

	Redraw();
}

/******************************************************************************
*	open the file
******************************************************************************/
void CPrevDlg::OnBnClickedOpen()
{
	CFileDialog dlg(
		true, NULL, NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		L"All image files (*.bmp;*.jpg)|*.bmp;*.jpg|Bitmap file(*.bmp)|*.bmp|JPG file(*.jpg)|*.jpg||");

	if (dlg.DoModal() == IDOK)
	{
		CString strTemp = dlg.GetPathName();
		int nIndex = strTemp.ReverseFind('\\');
		m_strPath = strTemp.Left(nIndex);	// directory

											//open all files in the directory
		CMainFrame::GetAllFileNames(m_strPath, m_FilesNameAry);
		m_nPicNum = (int)m_FilesNameAry.GetCount();

		m_nPos = 0;
		CString strFileName = dlg.GetFileName();

		//calculate the index
		while (m_nPos < m_nPicNum && m_FilesNameAry[m_nPos] != strFileName)
			m_nPos++;

		m_ScrollBar.SetScrollRange(0, m_nPicNum - 1);
		m_ScrollBar.SetScrollPos(m_nPos);
		m_strNum.Format(L"%d ,sum %d", m_nPos + 1, m_nPicNum);
		UpdateData(FALSE);

		Redraw();
	}
}

/******************************************************************************
*	draw in the preview
******************************************************************************/
void CPrevDlg::Redraw(void)
{
	CDC* pDC = m_staPrev.GetDC();
	Graphics graph(pDC->GetSafeHdc());
	CRect rect;

	m_staPrev.GetClientRect(rect);
	pDC->FillRect(rect, &CBrush(RGB(211, 211, 211)));

	if (m_nPos >= 0)
	{
		CString m_strFilePath = m_strPath + L"\\" + m_FilesNameAry[m_nPos];
		Image image(m_strFilePath);
		CRect rect;

		m_staPrev.GetClientRect(rect);

		REAL width = (REAL)image.GetWidth();
		REAL height = (REAL)image.GetHeight();
		REAL c = 0.0f;
		REAL x = 0.0f;
		REAL y = 0.0f;

		// zoom to width
		width = (REAL)rect.Width();
		c = width / image.GetWidth();

		// if it is not over
		if (c * image.GetHeight() < rect.Height())
			height = c * image.GetHeight();
		// otherwise, zoom to height
		else
		{
			height = (REAL)rect.Height();
			c = height / image.GetHeight();
			width = c * image.GetWidth();
		}

		// make the image in the middle
		if ((UINT)rect.Width() > width)
			x = (rect.Width() - width) / 2.0f;

		if ((UINT)rect.Height() > height)
			y = ((UINT)rect.Height() - height) / 2.0f;

		graph.DrawImage(&image, x, y, width, height);
	}

	ReleaseDC(pDC);
}

/******************************************************************************
*	hscroll
******************************************************************************/
void CPrevDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	switch (nSBCode)
	{
	case SB_LINERIGHT:
	{
		if (m_nPos < m_nPicNum - 1)
		{
			m_nPos += 1;
			m_ScrollBar.SetScrollPos(m_nPos);
			m_strNum.Format(L"�� %d ��,�� %d ��", m_nPos + 1, m_nPicNum);
			UpdateData(FALSE);

			Redraw();
		}

	}
	break;
	case SB_LINELEFT:
	{
		if (m_nPos > 0)
		{
			m_nPos -= 1;
			m_ScrollBar.SetScrollPos(m_nPos);
			m_strNum.Format(L"�� %d ��,�� %d ��", m_nPos + 1, m_nPicNum);
			UpdateData(FALSE);

			Redraw();
		}
	}
	break;
	default:
		break;
	}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
