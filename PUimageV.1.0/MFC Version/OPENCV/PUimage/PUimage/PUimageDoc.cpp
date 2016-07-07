
// PUimageDoc.cpp : implementation of the CPUimageDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PUimage.h"
#endif

#include "PUimageDoc.h"
#include <string.h>


#include <propkey.h>
using namespace std;
using namespace cv;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPUimageDoc

IMPLEMENT_DYNCREATE(CPUimageDoc, CDocument)

BEGIN_MESSAGE_MAP(CPUimageDoc, CDocument)
END_MESSAGE_MAP()


// CPUimageDoc construction/destruction

CPUimageDoc::CPUimageDoc()
{
	// TODO: add one-time construction code here

}

CPUimageDoc::~CPUimageDoc()
{
}

BOOL CPUimageDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CPUimageDoc serialization

void CPUimageDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CPUimageDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CPUimageDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CPUimageDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CPUimageDoc diagnostics

#ifdef _DEBUG
void CPUimageDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPUimageDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPUimageDoc commands


BOOL CPUimageDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	//if (!CDocument::OnOpenDocument(lpszPathName))
		//return FALSE;
	//m_image.Load(lpszPathName);
	
	CFileDialog dlgOpenFile(true, _T("*.bmp"), NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY, _T("image file(*.bmp;*.jpg)|*.bmp;*.jpg|All Files(*.*)|*.*|"), NULL);

	string imgPath;
	if (dlgOpenFile.DoModal() == IDOK)
	{
		//get image path  
		imgPath = dlgOpenFile.GetPathName(); 
	}
	else
		return FALSE;

	matImg = imread(imgPath);
	if (matImg.empty())
	{
		AfxMessageBox("Error loading source image!", MB_ICONSTOP | MB_OK);
		return FALSE;
	}


	//Mat to CvvImage  
	iplSrcImg = matImg;    //注：浅拷贝只复制数据头  
	
	m_image.CopyOf(&iplSrcImg);
	return TRUE;
}


BOOL CPUimageDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	m_image.Save(lpszPathName);
	return TRUE;
	//return CDocument::OnSaveDocument(lpszPathName);
}
