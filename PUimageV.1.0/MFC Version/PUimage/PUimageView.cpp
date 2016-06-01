// MagicHouseView.cpp : CPUimageView implement
//

#include "stdafx.h"
#include "PUimage.h"

#include "PUimageDoc.h"
#include "PUimageView.h"

#include "mainfrm.h"

#include "EffectDisplay.h"
#include "GeoOperator.h"
#include "PreviewDlg.h"
#include "MirTranDlg.h"
#include "ZoomDlg.h"
#include "RotateDlg.h"

#include "myDib.h"
#include "HistogramDlg.h"

#include "JpegDecoder.h"

#include "LineTranDlg.h"
#include "StretchDlg.h"
#include "ThresholdDlg.h"
#include "GrayOperator.h"
#include "LogTranDlg.h"
#include "PowerTranDlg.h"
#include "ExpTranDlg.h"
#include "MoveTranDlg.h"


#include "improve.h"
#include "Filter.h"

#include <iostream>
#include <string>
using namespace std;

#pragma warning ( disable : 4996)

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Image type
enum ShowType
{
	ST_NORMAL = 0,	// Normal
	ST_FIXWIDTH = 1,	// zoom to width
	ST_FIXHEIGHT = 2,	// zoom to height
	ST_FIXSCREEN = 3		// zoom to screen
};

typedef struct s_BM_header {
	WORD BMP_id; // 'B''M'
	DWORD size; // size in bytes of the BMP file
	DWORD zero_res; // 0
	DWORD offbits; // 54
	DWORD biSize; // 0x28
	DWORD Width;  // X
	DWORD Height;  // Y
	WORD  biPlanes; // 1
	WORD  biBitCount; // 24
	DWORD biCompression; // 0 = BI_RGB
	DWORD biSizeImage; // 0
	DWORD biXPelsPerMeter; // 0xB40
	DWORD biYPelsPerMeter; // 0xB40
	DWORD biClrUsed; //0
	DWORD biClrImportant; //0
} BM_header;

typedef struct s_RGB {
	BYTE B;
	BYTE G;
	BYTE R;
} RGB;

// CPUimageView

IMPLEMENT_DYNCREATE(CPUimageView, CView)

BEGIN_MESSAGE_MAP(CPUimageView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_MODE_NORMAL, &CPUimageView::OnModeNormal)
	ON_COMMAND(ID_MODE_WIDTH, &CPUimageView::OnModeWidth)
	ON_COMMAND(ID_MODE_HEIGHT, &CPUimageView::OnModeHeight)
	ON_COMMAND(ID_MODE_SCREEN, &CPUimageView::OnModeScreen)
	ON_UPDATE_COMMAND_UI(ID_MODE_NORMAL, &CPUimageView::OnUpdateModeNormal)
	ON_UPDATE_COMMAND_UI(ID_MODE_WIDTH, &CPUimageView::OnUpdateModeWidth)
	ON_UPDATE_COMMAND_UI(ID_MODE_HEIGHT, &CPUimageView::OnUpdateModeHeight)
	ON_UPDATE_COMMAND_UI(ID_MODE_SCREEN, &CPUimageView::OnUpdateModeScreen)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_SETCURSOR()
	ON_COMMAND(ID_IMAGE_PREV, &CPUimageView::OnImagePrev)
	ON_COMMAND(ID_IMAGE_NEXT, &CPUimageView::OnImageNext)
	ON_COMMAND(ID_IMAGE_FIRST, &CPUimageView::OnImageFirst)
	ON_COMMAND(ID_IMAGE_LAST, &CPUimageView::OnImageLast)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_PREV, &CPUimageView::OnUpdateImagePrev)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_NEXT, &CPUimageView::OnUpdateImageNext)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_FIRST, &CPUimageView::OnUpdateImageFirst)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_LAST, &CPUimageView::OnUpdateImageLast)
	ON_COMMAND(ID_EFFECT_NONE, &CPUimageView::OnEffectNone)
	ON_UPDATE_COMMAND_UI(ID_EFFECT_NONE, &CPUimageView::OnUpdateEffectNone)
	ON_COMMAND(ID_FILE_OPEN, &CPUimageView::OnFileOpen)
	ON_COMMAND(ID_MODE_BROWSE, &CPUimageView::OnModeBrowse)
	ON_COMMAND(ID_MODE_EDIT, &CPUimageView::OnModeEdit)
	ON_COMMAND(ID_POINT_HISTOGRAM, &CPUimageView::OnPointHistogram)
	ON_COMMAND(ID_FILE_SAVE, &CPUimageView::OnFileSave)
	ON_UPDATE_COMMAND_UI(ID_MODE_BROWSE, &CPUimageView::OnUpdateModeBrowse)
	ON_UPDATE_COMMAND_UI(ID_MODE_EDIT, &CPUimageView::OnUpdateModeEdit)
	ON_COMMAND(ID_POINT_LINETRAN, &CPUimageView::OnPointLinetran)
	ON_COMMAND(ID_POINT_STRETCH, &CPUimageView::OnPointStretch)
	ON_COMMAND(ID_POINT_EQUALIZE, &CPUimageView::OnPointEqualize)
	ON_COMMAND(ID_POINT_THRESHOLD, &CPUimageView::OnPointThreshold)
	ON_COMMAND(ID_POINT_LOG, &CPUimageView::OnPointLog)
	ON_COMMAND(ID_POINT_POWER, &CPUimageView::OnPointPower)
	ON_COMMAND(ID_POINT_EXP, &CPUimageView::OnPointExp)
	ON_COMMAND(ID_GEO_MOVE, &CPUimageView::OnGeoMove)
	ON_COMMAND(ID_GEO_MIRROR, &CPUimageView::OnGeoMirror)
	ON_COMMAND(ID_GEO_TRANSPOSE, &CPUimageView::OnGeoTranspose)
	ON_COMMAND(ID_GEO_ZOOM, &CPUimageView::OnGeoZoom)
	ON_COMMAND(ID_GEO_ROTATE, &CPUimageView::OnGeoRotate)
	ON_COMMAND(ID_IMPROVE_SMOOTH, &CPUimageView::OnImproveSmooth)
	ON_COMMAND(ID_IMPROVE_SMOOTHG, &CPUimageView::OnImproveSmoothg)
	ON_COMMAND(ID_IMPROVE_MEDIAN, &CPUimageView::OnImproveMedian)
	ON_COMMAND(ID_IMPROVE_SHARP, &CPUimageView::OnImproveSharp)
	ON_COMMAND(ID_IMPROVE_SOBEL, &CPUimageView::OnImproveSobel)
END_MESSAGE_MAP()

// CPUimageView Structure

CPUimageView::CPUimageView()
{
	m_bIsEditMode = false;
	m_nShowType = ST_NORMAL;
	m_bHeightOut = false;
	m_bWidhtOut = false;
	m_nXX = 0;
	m_nYY = 0;
	m_nXXMax = 0;
	m_nYYMax = 0;
	m_nPos = -1;

	m_pBitmap = NULL;
	m_bEffectDraw = false;
	m_nEffectDisplayType = EDT_NONE;

	m_pImageBuffer = NULL;
	m_pImageTempBuffer = NULL;
	m_nPicWidth = m_nPicHeight = 0;
}

CPUimageView::~CPUimageView()
{
	::delete m_pBitmap;

	FreeImageBuffer();
}

/******************************************************************************
*	Draw View
******************************************************************************/
void CPUimageView::OnDraw(CDC* pDC)
{
	CPUimageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect rect;
	GetClientRect(rect);

	CDC memDC;
	CBitmap MemBitmap;

	memDC.CreateCompatibleDC(NULL);

	MemBitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());

	// select black bitmap
	memDC.SelectObject(MemBitmap);
	memDC.FillSolidRect(0, 0, rect.Width(), rect.Height(), RGB(255, 255, 255));

	if (m_nPos >= 0)
		ShowPicture(&memDC, *m_pBitmap, m_nShowType);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

	MemBitmap.DeleteObject();
	memDC.DeleteDC();
}

/******************************************************************************
*	Open the file based on the path
******************************************************************************/
void CPUimageView::OpenFile(const CString& strPath)
{
	FreeImageBuffer();
	m_FilesNameAry.RemoveAll();

	int nIndex = strPath.ReverseFind('\\');
	m_strPath = strPath.Left(nIndex);
	CString strFileName = strPath.Right(strPath.GetLength() - nIndex - 1);

	CMainFrame::GetAllFileNames(m_strPath, m_FilesNameAry);
	m_nPicNum = (int)m_FilesNameAry.GetCount();

	m_nPos = 0;

	while (m_nPos < m_nPicNum && m_FilesNameAry[m_nPos] != strFileName)
		m_nPos++;

	PreDrawImage();
	m_bEffectDraw = true;
	Invalidate();

	if (m_bIsEditMode)
	{
		CString strPath = GetFilePath(m_nPos);
		GetImageBuffer(strPath);
	}
}

void CPUimageView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
}


BOOL CPUimageView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CPUimageView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{

}

void CPUimageView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{

}


#ifdef _DEBUG
void CPUimageView::AssertValid() const
{
	CView::AssertValid();
}

void CPUimageView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPUimageDoc* CPUimageView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPUimageDoc)));
	return (CPUimageDoc*)m_pDocument;
}
#endif //_DEBUG

/******************************************************************************
*	Open an image
******************************************************************************/
void CPUimageView::OnFileOpen()
{
	CFileDialog dlg(true, NULL, L"",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		L"All Image Files(*.bmp; *.jpg)|*.bmp; *.jpg|All Files(*.*)|*.*||");

	if (dlg.DoModal() == IDOK)
	{
		OpenFile(dlg.GetPathName());
		FixOffset();
		RefreshIndicator();
		Invalidate();
	}
}

/******************************************************************************
*Forbid drawing the background
******************************************************************************/
BOOL CPUimageView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

/******************************************************************************
*	Show the picture
******************************************************************************/
void CPUimageView::ShowPicture(CDC* pDC, Image& image, int nShowType)
{
	Graphics graph(pDC->GetSafeHdc());

	CRect winRect;
	GetClientRect(winRect);

	REAL x = 0.0;
	REAL y = 0.0;
	CSize showPicSize = GetShowPicSize(image, m_nShowType);
	REAL width = (REAL)showPicSize.cx;
	REAL height = (REAL)showPicSize.cy;

	if ((UINT)winRect.Width() > width)
		x = (winRect.Width() - width) / 2.0f;

	if ((UINT)winRect.Height() > height)
		y = ((UINT)winRect.Height() - height) / 2.0f;

	if (m_bWidhtOut)
		x += m_nXX;

	if (m_bHeightOut)
		y += m_nYY;

	m_nShowPicHeight = (int)height;
	m_nShowPicWidth = (int)width;

	graph.DrawImage(&image, x, y, width, height);
}

/******************************************************************************
*	set the show type
******************************************************************************/
void CPUimageView::SetShowType(int nType)
{
	m_nShowType = nType;
}

/******************************************************************************
*	Get the size of image based on the aksed mode
*	Return the size
******************************************************************************/
CSize CPUimageView::GetShowPicSize(Image& image, int nShowType)
{
	REAL width = (REAL)image.GetWidth();
	REAL height = (REAL)image.GetHeight();
	REAL c = 0.0f;

	CRect winRect;
	GetClientRect(winRect);

	switch (nShowType)
	{
	case ST_FIXWIDTH:	// Width Mode
		width = (REAL)winRect.Width();
		c = width / image.GetWidth();
		height = c * image.GetHeight();
		break;

	case ST_FIXHEIGHT:	// Height Mode
		height = (REAL)winRect.Height();
		c = height / image.GetHeight();
		width = c * image.GetWidth();

		break;

	case ST_FIXSCREEN:	// Zoom to the Screen

						// Based on the width mode
		width = (REAL)winRect.Width();
		c = width / image.GetWidth();

		// If it is not over the bound
		if (c * image.GetHeight() < winRect.Height())
			height = c * image.GetHeight();
		// If it is over, then choose the height mode
		else
		{
			height = (REAL)winRect.Height();
			c = height / image.GetHeight();
			width = c * image.GetWidth();
		}

		break;
	}

	return CSize((int)width, (int)height);
}


/******************************************************************************
*Click the mouse function
******************************************************************************/
void CPUimageView::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_psMove = point;

	CView::OnLButtonDown(nFlags, point);
}

/******************************************************************************
*	Modify offset of image
*	Based on the view module
******************************************************************************/
void CPUimageView::FixOffset()
{
	if (m_nPos < 0 || m_nPos >= m_nPicNum)
		return;

	Image image(GetFilePath(m_nPos));

	if (image.GetLastStatus() != Ok)
		return;

	m_bHeightOut = false;
	m_bWidhtOut = false;

	CSize imgSize = GetShowPicSize(image, m_nShowType);
	CRect rect;

	GetClientRect(rect);

	switch (m_nShowType)
	{
	case ST_NORMAL:
		if (imgSize.cx > rect.Width())
		{
			m_nXXMax = imgSize.cx - rect.Width();
			m_bWidhtOut = true;
		}

		if (imgSize.cy > rect.Height())
		{
			m_nYYMax = imgSize.cy - rect.Height();
			m_bHeightOut = true;
		}
		break;

	case ST_FIXWIDTH:
		if (imgSize.cy > rect.Height())
		{
			m_nYYMax = imgSize.cy - rect.Height();
			m_bHeightOut = true;
		}
		break;

	case ST_FIXHEIGHT:
		if (imgSize.cx > rect.Width())
		{
			m_nXXMax = imgSize.cx - rect.Width();
			m_bWidhtOut = true;
		}
		break;

	case ST_FIXSCREEN:
	default:;
	}
}

/******************************************************************************
*	Mouse movement
*	If the image is on the drag statement, modify the offset of image automatically
******************************************************************************/
void CPUimageView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (nFlags & MK_LBUTTON)
	{
		if (m_bWidhtOut)
		{
			m_nXX += point.x - m_psMove.x;
			if (m_nXX < 0 && abs(m_nXX) > m_nXXMax)
				m_nXX = -m_nXXMax;
			if (m_nXX > 0)
				m_nXX = 0;
		}

		if (m_bHeightOut)
		{
			m_nYY += point.y - m_psMove.y;
			if (m_nYY < 0 && abs(m_nYY) > m_nYYMax)
				m_nYY = -m_nYYMax;
			if (m_nYY > 0)
				m_nYY = 0;
		}

		m_psMove = point;

		Invalidate();
	}

	CView::OnMouseMove(nFlags, point);
}

/******************************************************************************
*	Change the cursor of the mouse
******************************************************************************/
BOOL CPUimageView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if (m_bHeightOut || m_bWidhtOut)
	{
		SetCursor(::LoadCursor(NULL, IDC_SIZEALL));
		return TRUE;
	}
	else
		return CView::OnSetCursor(pWnd, nHitTest, message);
}

/******************************************************************************
*	Predraw the image in the memory
******************************************************************************/
void CPUimageView::PreDrawImage(void)
{
	Image image(GetFilePath(m_nPos));

	::delete m_pBitmap;

	m_pBitmap = ::new Bitmap(image.GetWidth(), image.GetHeight(), PixelFormat32bppARGB);
	Graphics* graph = Graphics::FromImage(m_pBitmap);

	graph->DrawImage(&image, 0, 0, image.GetWidth(), image.GetHeight());
	SAFE_DELETE(graph);
}

/******************************************************************************
*	Update statement instructors
******************************************************************************/
void CPUimageView::RefreshIndicator()
{
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();

	CString strTemp;
	strTemp.Format(L"%d/%d", m_nPos + 1, m_nPicNum);
	pMain->UpdateIndicator(ID_INDICATOR_PICNUM, strTemp);
	pMain->UpdateIndicator(ID_INDICATOR_PICNAME, m_FilesNameAry[m_nPos]);
}

void CPUimageView::OnModeNormal()
{
	if (m_nShowType != ST_NORMAL)
	{
		m_nShowType = ST_NORMAL;
		FixOffset();
		Invalidate();
	}
}

void CPUimageView::OnModeWidth()
{
	if (m_nShowType != ST_FIXWIDTH)
	{
		m_nShowType = ST_FIXWIDTH;
		FixOffset();
		Invalidate();
	}
}

void CPUimageView::OnModeHeight()
{
	if (m_nShowType != ST_FIXHEIGHT)
	{
		m_nShowType = ST_FIXHEIGHT;
		FixOffset();
		Invalidate();
	}
}

void CPUimageView::OnModeScreen()
{
	if (m_nShowType != ST_FIXSCREEN)
	{
		m_nShowType = ST_FIXSCREEN;
		FixOffset();
		Invalidate();
	}
}

void CPUimageView::OnUpdateModeNormal(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_nShowType == ST_NORMAL);
}

void CPUimageView::OnUpdateModeWidth(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_nShowType == ST_FIXWIDTH);
}

void CPUimageView::OnUpdateModeHeight(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_nShowType == ST_FIXHEIGHT);
}

void CPUimageView::OnUpdateModeScreen(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_nShowType == ST_FIXSCREEN);
}

void CPUimageView::OnImagePrev()
{
	if (m_nPos <= 0)
		return;

	m_nPos--;

	PreDrawImage();
	ClearOffset();
	FixOffset();
	RefreshIndicator();
	m_bEffectDraw = true;
	Invalidate();
}

void CPUimageView::OnImageNext()
{
	if (m_nPos >= m_nPicNum - 1)
		return;

	m_nPos++;

	PreDrawImage();
	ClearOffset();
	FixOffset();
	RefreshIndicator();
	m_bEffectDraw = true;
	Invalidate();
}

void CPUimageView::OnImageFirst()
{
	m_nPos = 0;

	PreDrawImage();
	ClearOffset();
	FixOffset();
	RefreshIndicator();
	m_bEffectDraw = true;
	Invalidate();
}

void CPUimageView::OnImageLast()
{
	m_nPos = m_nPicNum - 1;

	PreDrawImage();
	ClearOffset();
	FixOffset();
	RefreshIndicator();
	m_bEffectDraw = true;
	Invalidate();
}

void CPUimageView::OnUpdateImagePrev(CCmdUI *pCmdUI)
{
	if (m_nPos <= 0 || m_bIsEditMode)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}

void CPUimageView::OnUpdateImageNext(CCmdUI *pCmdUI)
{
	if ((m_nPos < 0) || m_nPos >= m_nPicNum - 1 || m_bIsEditMode)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}

void CPUimageView::OnUpdateImageFirst(CCmdUI *pCmdUI)
{
	if (m_nPos < 0 || m_bIsEditMode)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}

void CPUimageView::OnUpdateImageLast(CCmdUI *pCmdUI)
{
	if (m_nPos < 0 || m_bIsEditMode)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}

void CPUimageView::OnEffectNone()
{
	m_nEffectDisplayType = EDT_NONE;
}

void CPUimageView::OnUpdateEffectNone(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_nEffectDisplayType == EDT_NONE);
}

void CPUimageView::OnModeBrowse()
{
	if (!m_bIsEditMode)
		return;

	FreeImageBuffer();
	m_bIsEditMode = false;
}

void CPUimageView::OnModeEdit()
{
	if (m_bIsEditMode)
		return;

	m_bIsEditMode = true;

	if (m_nPos != -1)
	{
		CString strPath = GetFilePath(m_nPos);
		GetImageBuffer(strPath);
	}
}

/******************************************************************************
*	Put the image info to the array based on the file path
******************************************************************************/
bool CPUimageView::GetImageBuffer(CString& strPath)
{
	CString fileNameExt = strPath.Right(3);
	string filePath = (LPCSTR)CStringA(strPath);

	if (fileNameExt == "jpg" || fileNameExt == "JPG")
	{
		FILE *fp;

		fp = fopen(filePath.c_str(), "rb");

		JpegDecoder dec(fp);
		fclose(fp);

		m_nPicWidth = m_nTempWidth = dec.GetWidth();
		m_nPicHeight = m_nTempHeight = dec.GetHeight();
		dec.GetJPEGBuffer(m_nPicWidth, m_nPicHeight, &m_pImageBuffer);
		int sizeb = m_nPicWidth * m_nPicHeight * 4;

		m_pImageTempBuffer = (BYTE*)malloc(sizeb);
		memcpy(m_pImageTempBuffer, m_pImageBuffer, sizeb);
	}

	if (fileNameExt == "bmp" || fileNameExt == "BMP")
	{
		MyDib* dib = new MyDib(strPath);

		int b = dib->GetBitsPerPixel();

		m_nPicWidth = m_nTempWidth = dib->GetWidth();
		m_nPicHeight = m_nTempHeight = dib->GetHeight();
		int sizeofbuffer = m_nPicWidth * m_nPicHeight * 4;
		m_pImageTempBuffer = (BYTE *)malloc(sizeofbuffer);

		m_pImageBuffer = (BYTE *)malloc(dib->GetBodySize());
		memcpy(m_pImageBuffer, dib->GetBits(), dib->GetBodySize());

		SAFE_DELETE(dib);

		if (b != 24 && b != 32 && b != 8)
		{
			free(m_pImageTempBuffer);
			free(m_pImageBuffer);
			MessageBox(L"The program can only deal with 24 or 32 color image or 8 gray image!");
			return false;
		}

		if (b == 32)
		{
			for (unsigned int i = 0; i < m_nPicWidth * 4; i += 4)
			{
				for (unsigned int j = 0; j < m_nPicHeight / 2; j++)
				{
					swap(m_pImageBuffer[j*m_nPicWidth * 4 + i], m_pImageBuffer[(m_nPicHeight - j - 1)*m_nPicWidth * 4 + i]);
					swap(m_pImageBuffer[j*m_nPicWidth * 4 + i + 1], m_pImageBuffer[(m_nPicHeight - j - 1)*m_nPicWidth * 4 + i + 1]);
					swap(m_pImageBuffer[j*m_nPicWidth * 4 + i + 2], m_pImageBuffer[(m_nPicHeight - j - 1)*m_nPicWidth * 4 + i + 2]);
					swap(m_pImageBuffer[j*m_nPicWidth * 4 + i + 3], m_pImageBuffer[(m_nPicHeight - j - 1)*m_nPicWidth * 4 + i + 3]);
				}
			}
			memcpy(m_pImageTempBuffer, m_pImageBuffer, sizeofbuffer);
		}

		if (b == 24)
		{
			int externWidth;
			externWidth = m_nPicWidth * 3;
			if (externWidth % 4 != 0)
				externWidth = 4 - externWidth % 4;
			else
				externWidth = 0;

			int k = 0;

			for (int n = m_nPicHeight - 1; n >= 0; n--)
			{
				for (UINT m = 0; m < m_nPicWidth * 3; m += 3)
				{
					m_pImageTempBuffer[k] = m_pImageBuffer[n*(m_nPicWidth * 3 + externWidth) + m];	//blue
					m_pImageTempBuffer[k + 1] = m_pImageBuffer[n*(m_nPicWidth * 3 + externWidth) + m + 1];//green
					m_pImageTempBuffer[k + 2] = m_pImageBuffer[n*(m_nPicWidth * 3 + externWidth) + m + 2];//red
					m_pImageTempBuffer[k + 3] = 255;
					k += 4;
				}
			}

			free(m_pImageBuffer);
			m_pImageBuffer = (BYTE *)malloc(sizeofbuffer);
			memcpy(m_pImageBuffer, m_pImageTempBuffer, sizeofbuffer);
		}

		if (b == 8) {

			int externWidth;
			externWidth = m_nPicWidth;
			if (externWidth % 4 != 0)
				externWidth = 4 - externWidth % 4;
			else
				externWidth = 0;

			int k = 0;

			for (int n = m_nPicHeight - 1; n >= 0; n--) {
				for (UINT m = 0; m<m_nPicWidth; m += 1) {

					m_pImageTempBuffer[k] = m_pImageBuffer[n*(m_nPicWidth + externWidth) + m];//blue
					m_pImageTempBuffer[k + 1] = m_pImageBuffer[n*(m_nPicWidth + externWidth) + m];//green
					m_pImageTempBuffer[k + 2] = m_pImageBuffer[n*(m_nPicWidth + externWidth) + m];//red
					m_pImageTempBuffer[k + 3] = 0;
					k += 4;
				}
			}

			free(m_pImageBuffer);
			m_pImageBuffer = (BYTE*)malloc(sizeofbuffer);
			memcpy(m_pImageBuffer, m_pImageTempBuffer, sizeofbuffer);
		}
	}

	return true;
}

/******************************************************************************
*	Release the image buffer
******************************************************************************/
void CPUimageView::FreeImageBuffer(void)
{
	if (m_pImageBuffer != NULL)
	{
		free(m_pImageBuffer);
		m_pImageBuffer = NULL;
	}

	if (m_pImageTempBuffer != NULL)
	{
		free(m_pImageTempBuffer);
		m_pImageTempBuffer = NULL;
	}
}

/******************************************************************************
*	Save the file
******************************************************************************/
void CPUimageView::OnFileSave()
{
	if (m_nPos == -1)
	{
		MessageBox(L"There are no image files!", L"PU Image", MB_ICONWARNING);
		return;
	}
	if (m_pImageTempBuffer == NULL)
	{
		MessageBox(L"There are no Files to save!", L"PU Image", MB_ICONWARNING);
		return;
	}
	CFileDialog SaveDlg(FALSE, L"bmp", L"No named", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR, L"Files format(*.bmp) |*.bmp||", NULL);
	if (SaveDlg.DoModal() == IDOK)
	{
		CString tempname = SaveDlg.GetPathName();
		string savePath = (LPCSTR)CStringA(tempname);
		WriteBufferToBMP(m_pImageTempBuffer, m_nTempWidth, m_nTempHeight, savePath.c_str());
		tempname.ReleaseBuffer();
		MessageBox(L"Files are saved successfully!");
	}
}

/******************************************************************************
*	Write the image to bmp files
*	im_buffer: Image info
*	X_bitmap:  Width
*	Y_bitmap:  Height
*	BMPname:	Files path of saving the bmp files
******************************************************************************/
void CPUimageView::WriteBufferToBMP(BYTE *im_buffer, WORD X_bitmap, WORD Y_bitmap, const char* BMPname)
{
	SWORD x, y;
	RGB *pixel;
	BM_header BH;
	FILE *fp_bitmap;
	DWORD im_loc_bytes;
	BYTE nr_fillingbytes, i;
	BYTE zero_byte = 0;

	fp_bitmap = fopen(BMPname, "wb");
	if (fp_bitmap == NULL)
	{
		AfxMessageBox(L"The file cannot be created.", MB_ICONWARNING);
		return;
	}

	if (X_bitmap % 4 != 0) nr_fillingbytes = 4 - ((X_bitmap * 3L) % 4);
	else nr_fillingbytes = 0;

	BH.BMP_id = 'M' * 256 + 'B';     fwrite(&BH.BMP_id, 2, 1, fp_bitmap);
	BH.size = 54 + Y_bitmap*(X_bitmap * 3 + nr_fillingbytes); fwrite(&BH.size, 4, 1, fp_bitmap);
	BH.zero_res = 0;             fwrite(&BH.zero_res, 4, 1, fp_bitmap);
	BH.offbits = 54;             fwrite(&BH.offbits, 4, 1, fp_bitmap);
	BH.biSize = 0x28;            fwrite(&BH.biSize, 4, 1, fp_bitmap);
	BH.Width = X_bitmap;	      fwrite(&BH.Width, 4, 1, fp_bitmap);
	BH.Height = Y_bitmap;	      fwrite(&BH.Height, 4, 1, fp_bitmap);
	BH.biPlanes = 1;             fwrite(&BH.biPlanes, 2, 1, fp_bitmap);
	BH.biBitCount = 24;          fwrite(&BH.biBitCount, 2, 1, fp_bitmap);
	BH.biCompression = 0;        fwrite(&BH.biCompression, 4, 1, fp_bitmap);
	BH.biSizeImage = 0;          fwrite(&BH.biSizeImage, 4, 1, fp_bitmap);
	BH.biXPelsPerMeter = 0xB40;  fwrite(&BH.biXPelsPerMeter, 4, 1, fp_bitmap);
	BH.biYPelsPerMeter = 0xB40;  fwrite(&BH.biYPelsPerMeter, 4, 1, fp_bitmap);
	BH.biClrUsed = 0;	          fwrite(&BH.biClrUsed, 4, 1, fp_bitmap);
	BH.biClrImportant = 0;	      fwrite(&BH.biClrImportant, 4, 1, fp_bitmap);

	im_loc_bytes = (DWORD)im_buffer + ((DWORD)Y_bitmap - 1)*X_bitmap * 4;

	for (y = 0; y<Y_bitmap; y++)
	{
		for (x = 0; x<X_bitmap; x++)
		{
			pixel = (RGB *)im_loc_bytes;
			fwrite(pixel, 3, 1, fp_bitmap);
			im_loc_bytes += 4;
		}
		for (i = 0; i<nr_fillingbytes; i++)
			fwrite(&zero_byte, 1, 1, fp_bitmap);
		im_loc_bytes -= 2L * X_bitmap * 4;
	}
	fclose(fp_bitmap);
}
void CPUimageView::OnUpdateModeBrowse(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(!m_bIsEditMode);
}

void CPUimageView::OnUpdateModeEdit(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bIsEditMode);
}

void CPUimageView::ResetImage()
{
	m_nTempWidth = m_nPicWidth;
	m_nTempHeight = m_nPicHeight;

	int sizeofbuffer = m_nTempWidth * m_nTempHeight * 4;
	SAFE_DELETE(m_pImageTempBuffer);

	m_pImageTempBuffer = new BYTE[sizeofbuffer];
	memcpy(m_pImageTempBuffer, m_pImageBuffer, sizeofbuffer);
}

void CPUimageView::OnPointLinetran()
{
	if (!m_bIsEditMode || m_nPos == -1)
	{
		MessageBox(L"Please open the image file, and choose the edit mode");
		return;
	}

	CLineTranDlg dlg;

	ResetImage();
	dlg.DoModal();
}

void CPUimageView::OnPointHistogram()
{
	if (!m_bIsEditMode || m_nPos == -1)
	{
		MessageBox(L"Please open the image file, and choose the edit mode");
		return;
	}

	CHistogramDlg dlg;

	ResetImage();
	dlg.DoModal();
}

void CPUimageView::OnPointStretch()
{
	if (!m_bIsEditMode || m_nPos == -1)
	{
		MessageBox(L"Please open the image file, and choose the edit mode");
		return;
	}

	CStretchDlg dlg;

	ResetImage();
	dlg.DoModal();
}

void CPUimageView::OnPointEqualize()
{
	if (!m_bIsEditMode || m_nPos == -1)
	{
		MessageBox(L"Please open the image file, and choose the edit mode");
		return;
	}

	GrayEqualize(m_pImageBuffer, m_pImageTempBuffer, m_nPicWidth, m_nPicHeight);


	CPreviewDlg dlg;

	dlg.m_nType = 2;
	dlg.DoModal();
	ResetImage();
}

void CPUimageView::OnPointThreshold()
{
	if (!m_bIsEditMode || m_nPos == -1)
	{
		MessageBox(L"Please open the image file, and choose the edit mode");
		return;
	}

	CThresholdDlg dlg;

	ResetImage();
	dlg.DoModal();
}

void CPUimageView::OnPointLog()
{
	if (!m_bIsEditMode || m_nPos == -1)
	{
		MessageBox(L"Please open the image file, and choose the edit mode");
		return;
	}

	CLogTranDlg dlg;

	ResetImage();
	dlg.DoModal();
}

void CPUimageView::OnPointPower()
{
	if (!m_bIsEditMode || m_nPos == -1)
	{
		MessageBox(L"Please open the image file, and choose the edit mode");
		return;
	}

	CPowerTranDlg dlg;

	ResetImage();
	dlg.DoModal();
}

void CPUimageView::OnPointExp()
{
	if (!m_bIsEditMode || m_nPos == -1)
	{
		MessageBox(L"Please open the image file, and choose the edit mode");
		return;
	}

	CExpTranDlg dlg;

	ResetImage();
	dlg.DoModal();
}

void CPUimageView::OnGeoMove()
{
	if (!m_bIsEditMode || m_nPos == -1)
	{
		MessageBox(L"Please open the image file, and choose the edit mode");
		return;
	}

	CMoveTranDlg dlg;
	ResetImage();
	dlg.DoModal();
}

void CPUimageView::OnGeoMirror()
{
	if (!m_bIsEditMode || m_nPos == -1)
	{
		MessageBox(L"Please open the image file, and choose the edit mode");
		return;
	}

	CMirTranDlg dlg;
	ResetImage();
	dlg.DoModal();
}

void CPUimageView::OnGeoTranspose()
{
	// Delete the array, transpose function will ask for space automatically
	SAFE_DELETE(m_pImageTempBuffer);

	Transpose(m_pImageBuffer, m_pImageTempBuffer,
		m_nPicWidth, m_nPicHeight, m_nTempWidth, m_nTempHeight);

	// Create preview dialog
	CPreviewDlg dlg;

	dlg.m_nType = 2;	// ask if save before exit
	dlg.DoModal();
	ResetImage();
}

void CPUimageView::OnGeoZoom()
{
	if (!m_bIsEditMode || m_nPos == -1)
	{
		MessageBox(L"Please open the image file, and choose the edit mode");
		return;
	}

	CZoomDlg dlg;
	dlg.DoModal();
}

void CPUimageView::OnGeoRotate()
{
	if (!m_bIsEditMode || m_nPos == -1)
	{
		MessageBox(L"Please open the image file, and choose the edit mode");
		return;
	}
	CRotateDlg dlg;
	dlg.DoModal();
}

void CPUimageView::OnImproveSmooth()
{
	if (!m_bIsEditMode || m_nPos == -1)
	{
		MessageBox(L"Please open the image file, and choose the edit mode");
		return;
	}

	ResetImage();
	SmoothCl(m_pImageBuffer, m_pImageTempBuffer, m_nPicWidth, m_nPicHeight, 10);


	CPreviewDlg dlg;

	dlg.m_nType = 2;
	dlg.DoModal();
}
void CPUimageView::OnImproveSmoothg()
{
	if (!m_bIsEditMode || m_nPos == -1)
	{
		MessageBox(L"Please open the image file, and choose the edit mode");
		return;
	}

	ResetImage();
	SmoothGaussCl(m_pImageBuffer, m_pImageTempBuffer, m_nPicWidth, m_nPicHeight);

	CPreviewDlg dlg;

	dlg.m_nType = 2;
	dlg.DoModal();
}

void CPUimageView::OnImproveMedian()
{
	if (!m_bIsEditMode || m_nPos == -1)
	{
		MessageBox(L"Please open the image file, and choose the edit mode");
		return;
	}

	ResetImage();
	SmoothMedianCl(m_pImageBuffer, m_pImageTempBuffer, m_nPicWidth, m_nPicHeight, 7);

	CPreviewDlg dlg;

	dlg.m_nType = 2;
	dlg.DoModal();
}

void CPUimageView::OnImproveSharp()
{
	if (!m_bIsEditMode || m_nPos == -1)
	{
		MessageBox(L"Please open the image file, and choose the edit mode");
		return;
	}

	ResetImage();
	SharpLaplacianCl(m_pImageBuffer, m_pImageTempBuffer, m_nPicWidth, m_nPicHeight);


	CPreviewDlg dlg;

	dlg.m_nType = 2;
	dlg.DoModal();
}

void CPUimageView::OnImproveSobel()
{
	if (!m_bIsEditMode || m_nPos == -1)
	{
		MessageBox(L"Please open the image file, and choose the edit mode");
		return;
	}

	ResetImage();

	int w = m_nPicWidth;
	int h = m_nPicHeight;

	BYTE* imageS1 = new BYTE[w*h * 4];
	BYTE* imageS2 = new BYTE[w*h * 4];
	SideSobel(m_pImageBuffer, imageS1, w, h, true);
	SideSobel(imageS1, imageS2, w, h, true);
	Subtract(imageS1, imageS2, w, h);
	ToTwoValue(imageS1, m_pImageTempBuffer, w, h, 100);
	delete[] imageS1;
	delete[] imageS2;

	CPreviewDlg dlg;

	dlg.m_nType = 2;
	dlg.DoModal();
}
