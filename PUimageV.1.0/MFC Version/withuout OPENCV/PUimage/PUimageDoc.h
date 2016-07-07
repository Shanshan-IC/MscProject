// PUimageDoc.h
//


#pragma once


class CPUimageDoc : public CDocument
{
protected: 
	CPUimageDoc();
	DECLARE_DYNCREATE(CPUimageDoc)

public:

public:

public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

public:
	virtual ~CPUimageDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

protected:
	DECLARE_MESSAGE_MAP()
};


