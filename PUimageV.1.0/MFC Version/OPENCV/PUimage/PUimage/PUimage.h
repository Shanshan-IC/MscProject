
// PUimage.h : main header file for the PUimage application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CPUimageApp:
// See PUimage.cpp for the implementation of this class
//

class CPUimageApp : public CWinApp
{
public:
	CPUimageApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPUimageApp theApp;
