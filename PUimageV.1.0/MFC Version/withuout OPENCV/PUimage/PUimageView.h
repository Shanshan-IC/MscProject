// PUimageView.h
//

#pragma once

class CPUimageView : public CView
{
	DECLARE_MESSAGE_MAP()
	DECLARE_DYNCREATE(CPUimageView)

public:
	byte*	m_pImageBuffer;				// edit the intial image pixel array
	byte*	m_pImageTempBuffer;			// pixel array after changes
	UINT	m_nPicWidth;				// the widht of the current image
	UINT	m_nPicHeight;				// the height of the current image
	UINT	m_nTempWidth;				// the widht of the changed image
	UINT	m_nTempHeight;				// the height of the changed image


	bool	m_bWidhtOut;				// whether the width is over the view
	bool	m_bHeightOut;				// whether the height is over the view
	bool	m_bIsEditMode;				// wheter is in the edit mode
	int		m_nShowType;				// type

	virtual ~CPUimageView();

	void ShowPicture(CDC* pDC, Image& image, int nShowType);
	// show picture
	void SetShowType(int nType);		// Set Show Type
	CSize GetShowPicSize(Image& image, int nShowType);
	// Get Show Picture Size

	void OpenFile(const CString& strPath);	// open the file
	
	/******************************************************************************
	*	clear the offset of the image
	******************************************************************************/
	void ClearOffset(void)
	{
		m_nXX = m_nYY = m_nXXMax = m_nYYMax = 0;
	}

	void FixOffset(void);	

	/***************************************************************************
	*	get the file full path
	***************************************************************************/
	CString GetFilePath(int nIndex)
	{
		ASSERT(nIndex >= 0 && nIndex < m_nPicNum);
		return m_strPath + L"\\" + m_FilesNameAry[nIndex];
	}

	void RefreshIndicator();			

	CPUimageDoc* GetDocument() const;
	virtual void OnDraw(CDC* pDC);		

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnFileOpen();			
	afx_msg void OnFileSave();			
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	afx_msg void OnModeBrowse();		
	afx_msg void OnModeEdit();			
	
	afx_msg void OnUpdateModeBrowse(CCmdUI *pCmdUI);
	afx_msg void OnUpdateModeEdit(CCmdUI *pCmdUI);

	afx_msg void OnModeNormal();
	afx_msg void OnModeWidth();
	afx_msg void OnModeHeight();
	afx_msg void OnModeScreen();
	afx_msg void OnUpdateModeNormal(CCmdUI *pCmdUI);
	afx_msg void OnUpdateModeWidth(CCmdUI *pCmdUI);
	afx_msg void OnUpdateModeHeight(CCmdUI *pCmdUI);
	afx_msg void OnUpdateModeScreen(CCmdUI *pCmdUI);
	afx_msg void OnImagePrev();
	afx_msg void OnImageNext();
	afx_msg void OnImageFirst();
	afx_msg void OnImageLast();
	afx_msg void OnUpdateImagePrev(CCmdUI *pCmdUI);
	afx_msg void OnUpdateImageNext(CCmdUI *pCmdUI);
	afx_msg void OnUpdateImageFirst(CCmdUI *pCmdUI);
	afx_msg void OnUpdateImageLast(CCmdUI *pCmdUI);

	afx_msg void OnEffectNone();
	afx_msg void OnUpdateEffectNone(CCmdUI *pCmdUI);

	afx_msg void OnPointLinetran();
	afx_msg void OnPointHistogram();
	afx_msg void OnPointLog();
	afx_msg void OnPointPower();
	afx_msg void OnPointExp();
	afx_msg void OnGeoMirror();
	afx_msg void OnGeoTranspose();
	afx_msg void OnGeoZoom();
	afx_msg void OnGeoRotate();
	afx_msg void OnImproveSmoothg();
	afx_msg void OnImproveMedian();
	afx_msg void OnImproveSharp();

protected:
	CPUimageView();

	virtual void OnInitialUpdate();		
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

private:
	int				m_nEffectDisplayType;// Effect Display Type
	bool			m_bEffectDraw;
	Bitmap*			m_pBitmap;
	int				m_nPicNum;			// number of pictures 
	CString			m_strPath;			// current file directory
	CStringArray	m_FilesNameAry;
	int				m_nPos;				// index of current file
	int				m_nShowPicHeight;	// Show  Height of the Picture
	int				m_nShowPicWidth;	//  Show  width of the Picture

	CPoint			m_psMove;			// mouse position
	int				m_nXX;				// offset of X
	int				m_nYY;				// offset of Y
	int				m_nXXMax;			// maxium offset of X
	int				m_nYYMax;			// maxium offset of Y

	void PreDrawImage(void);			// Predraw the image in the memory
	bool GetImageBuffer(CString& strPath);
	// Put the image info to the array based on the file path
	void FreeImageBuffer(void);			// Free Image Buffer

	void WriteBufferToBMP(BYTE *im_buffer, WORD X_bitmap, WORD Y_bitmap, const char* BMPname);
	// Write the image to bmp files
	void ResetImage();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
public:
	afx_msg void OnStatisticsHistogramstatistics();
	afx_msg void OnStatisticsImagestatistics();
	afx_msg void OnHistogramEqualize();
	afx_msg void OnHistogramEqualization();
	afx_msg void OnProcessAutoadjustment();
	afx_msg void OnProcessBrightness();
	afx_msg void OnProcessContrast();
	afx_msg void OnHistogramContrastlimitedadaptiveequalizaiton();
	afx_msg void OnVideoEulerian();
};

#ifndef _DEBUG 
inline CPUimageDoc* CPUimageView::GetDocument() const
   { return reinterpret_cast<CPUimageDoc*>(m_pDocument); }
#endif

