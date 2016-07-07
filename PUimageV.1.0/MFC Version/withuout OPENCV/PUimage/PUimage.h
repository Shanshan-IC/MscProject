// PUimage.h : PUimage
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
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