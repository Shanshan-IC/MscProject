// PUimageDoc.cpp
//

#include "stdafx.h"
#include "PUimage.h"

#include "PUimageDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPUimageDoc

IMPLEMENT_DYNCREATE(CPUimageDoc, CDocument)

BEGIN_MESSAGE_MAP(CPUimageDoc, CDocument)
END_MESSAGE_MAP()


// CPUimageDoc

CPUimageDoc::CPUimageDoc()
{

}

CPUimageDoc::~CPUimageDoc()
{
}

BOOL CPUimageDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}




void CPUimageDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}


// CPUimageDoc

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


// CPUimageDoc
