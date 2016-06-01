// PUimage.h : PUimage

#pragma once

#ifndef __AFXWIN_H__
#error "include stdafx.h to create PCH file"
#endif

#include "resource.h"       


// CPUimageApp:

class CPUimageApp : public CWinApp
{
public:
	CPUimageApp();


public:
	virtual BOOL InitInstance();


	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

private:
	GdiplusStartupInput m_GdiplusStartupInput;
	ULONG_PTR			m_GdiplusToken;
public:
	virtual int ExitInstance();
};

extern CPUimageApp theApp;