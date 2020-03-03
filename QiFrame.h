// QiFrame.h : main header file for the QiFrame application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CQiFrameApp:
// See QiFrame.cpp for the implementation of this class
//

class CQiFrameApp : public CWinApp
{
public:
	CQiFrameApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CQiFrameApp theApp;