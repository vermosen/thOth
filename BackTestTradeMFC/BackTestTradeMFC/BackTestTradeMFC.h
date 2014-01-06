
// BackTestTradeMFC.h : main header file for the BackTestTradeMFC application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resources/resource.h"       // main symbols


// CBackTestTradeMFCApp:
// See BackTestTradeMFC.cpp for the implementation of this class
//

class CBackTestTradeMFCApp : public CWinApp {

public:
	CBackTestTradeMFCApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

};

extern CBackTestTradeMFCApp theApp;
