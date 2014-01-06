// BackTestTradeMFCView.h : interface of the CBackTestTradeMFCView class

#pragma once

class CBackTestTradeMFCView : public CView {

	protected:														// create from serialization only
		CBackTestTradeMFCView();
		DECLARE_DYNCREATE(CBackTestTradeMFCView)

	// Attributes
	public:
		CBackTestTradeMFCDoc* GetDocument() const;

	// Operations
	public:

	// Overrides
	public:
		virtual void OnDraw(CDC* pDC);								// overridden to draw this view
		virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	protected:
		virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
		virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
		virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// Implementation
	public:
		virtual ~CBackTestTradeMFCView();
	#ifdef _DEBUG
		virtual void AssertValid() const;
		virtual void Dump(CDumpContext& dc) const;
	#endif

	protected:

	// Generated message map functions
	protected:
		DECLARE_MESSAGE_MAP()

};

#ifndef _DEBUG  // debug version in BackTestTradeMFCView.cpp
inline CBackTestTradeMFCDoc* CBackTestTradeMFCView::GetDocument() const
   { return reinterpret_cast<CBackTestTradeMFCDoc*>(m_pDocument); }
#endif

