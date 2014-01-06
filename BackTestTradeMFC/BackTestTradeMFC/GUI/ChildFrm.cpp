
// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "BackTestTradeMFC.h"

#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
END_MESSAGE_MAP()

// CChildFrame construction/destruction

CChildFrame::CChildFrame() {

	// TODO: add member initialization code here

}

CChildFrame::~CChildFrame() {}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs) {

	// TODO: Modify the Window class or styles here by modifying the CREATESTRUCT cs
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.style |= WS_OVERLAPPED | WS_SYSMENU | WS_BORDER;

	cs.cy = ::GetSystemMetrics(SM_CYSCREEN) / 3;							// Size the window to 1/3 screen size and center it
	cs.cx = ::GetSystemMetrics(SM_CXSCREEN) / 3;

	return TRUE;

}

// CChildFrame diagnostics
#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}
#endif //_DEBUG

// CChildFrame message handlers
