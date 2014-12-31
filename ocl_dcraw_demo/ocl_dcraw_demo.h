// ocl_dcraw_demo.h : main header file for the ocl_dcraw_demo application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// Cocl_dcraw_demoApp:
// See ocl_dcraw_demo.cpp for the implementation of this class
//

class Cocl_dcraw_demoApp : public CWinApp
{
public:
	Cocl_dcraw_demoApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	afx_msg void OnFileOpen();
	DECLARE_MESSAGE_MAP()
};

extern Cocl_dcraw_demoApp theApp;