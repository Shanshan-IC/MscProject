
// PUimageView.h : interface of the CPUimageView class
//

#pragma once


class CPUimageView : public CView
{
protected: // create from serialization only
	CPUimageView();
	DECLARE_DYNCREATE(CPUimageView)

// Attributes
public:
	CPUimageDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CPUimageView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnHistogramEqulization();
	afx_msg void OnProcessContrast();
	afx_msg void OnProcessAuto();
	afx_msg void OnHistogramContrastlimitedadaptiveequalizaiton();
	afx_msg void OnFilterGaussian();
	afx_msg void OnFilterMedian();
//	afx_msg void OnFilterLaplaciansharpen();
	afx_msg void OnProcessBrightness();
	afx_msg void OnVideoEulerian();
	afx_msg void OnPreviewPreview();
	afx_msg void OnProcessSkindetect();
	afx_msg void OnVideoMotion();
	afx_msg void OnAdditionMorp();
	afx_msg void OnProcessLaplaceedge();
	afx_msg void OnDetectCricledetect();
	afx_msg void OnDetectCannyedgedetect();
	afx_msg void OnDetectCornerdetect();

public:

	afx_msg void OnDetectCascadeclassifier();
	afx_msg void OnImageRotate90();
	afx_msg void OnImageRotate180();
	afx_msg void OnImageRotate();
	afx_msg void OnImageResize();
	afx_msg void OnImageZoomin();
	afx_msg void OnImageZoomout();
	afx_msg void OnFilterBilateral();
	afx_msg void OnFilterNormalizedblock();
};

#ifndef _DEBUG  // debug version in PUimageView.cpp
inline CPUimageDoc* CPUimageView::GetDocument() const
   { return reinterpret_cast<CPUimageDoc*>(m_pDocument); }
#endif

