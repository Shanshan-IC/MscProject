// PUimage.h : PUimage
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
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