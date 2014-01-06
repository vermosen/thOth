
// BackTestTradeMFCView.cpp : implementation of the CBackTestTradeMFCView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "BackTestTradeMFC.h"
#endif

#include "BackTestTradeMFCDoc.h"
#include "GUI/BackTestTradeMFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBackTestTradeMFCView

IMPLEMENT_DYNCREATE(CBackTestTradeMFCView, CView)

BEGIN_MESSAGE_MAP(CBackTestTradeMFCView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CBackTestTradeMFCView construction/destruction

CBackTestTradeMFCView::CBackTestTradeMFCView()
{
	// TODO: add construction code here

}

CBackTestTradeMFCView::~CBackTestTradeMFCView()
{
}

BOOL CBackTestTradeMFCView::PreCreateWindow(CREATESTRUCT& cs) {

	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CView::PreCreateWindow(cs);

}

// CBackTestTradeMFCView drawing

void CBackTestTradeMFCView::OnDraw(CDC* /*pDC*/)
{
	CBackTestTradeMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CBackTestTradeMFCView printing

BOOL CBackTestTradeMFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBackTestTradeMFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBackTestTradeMFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CBackTestTradeMFCView diagnostics

#ifdef _DEBUG
void CBackTestTradeMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CBackTestTradeMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBackTestTradeMFCDoc* CBackTestTradeMFCView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBackTestTradeMFCDoc)));
	return (CBackTestTradeMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CBackTestTradeMFCView message handlers
