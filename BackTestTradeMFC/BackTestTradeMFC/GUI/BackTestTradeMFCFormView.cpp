// BackTestTradeMFCFormView.cpp : implementation file
//

#include "stdafx.h"
#include "BackTestTradeMFC.h"

#include "GUI/BackTestTradeMFCFormView.h"

#include "thOth/portfolio.h"
#include "thOth/strategy/marketOrder.h"

#include <boost/lexical_cast.hpp>

IMPLEMENT_DYNCREATE(CBackTestTradeMFCFormView, CFormView)

CBackTestTradeMFCFormView::CBackTestTradeMFCFormView()						// CBackTestTradeMFCFormView
: CFormView(CBackTestTradeMFCFormView::IDD) {

	m_db = new CDatabase;													// database initialization
	m_edit = new CEdit;														// edit initialization

	m_startDatePicker = new CDateTimeCtrl;									// date pickers
	m_startTimePicker = new CDateTimeCtrl;
	m_endDatePicker = new CDateTimeCtrl;
	m_endTimePicker = new CDateTimeCtrl;

	m_InsertFileButton = new CButton;										// interface buttons
	m_requestButton = new CButton;
	m_testButton = new CButton;

	m_timeSeries = new thOth::TimeSeries<thOth::quoteDetails>;				// internal data
	m_startDate = new thOth::dateTime;
	m_endDate = new thOth::dateTime;

	std::wstring connStr;													// connection string

	connStr += L"Driver={SQL Server Native Client 11.0};";
	connStr += L"Database=CIRCE;";
	connStr += L"Server=MACBOOKWIN;";
	connStr += L"Trusted_Connection=yes;";
	
	if (m_db != NULL)														// opens database connexion
		m_db->Open(_T("DSN=IDSourceCirce;"), 0, FALSE, connStr.c_str());

}

CBackTestTradeMFCFormView::~CBackTestTradeMFCFormView() {

	delete m_db;
	delete m_edit;

	delete m_startDatePicker;
	delete m_startTimePicker;
	delete m_endDatePicker;
	delete m_endTimePicker;

	delete m_InsertFileButton;
	delete m_requestButton;
	delete m_testButton;

	delete m_startDate;
	delete m_endDate;
	delete m_timeSeries;

}

void CBackTestTradeMFCFormView::DoDataExchange(CDataExchange* pDX) {
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAIN_EDIT, *m_edit);

	DDX_Control(pDX, IDC_BUTTON1, *m_requestButton);
	DDX_Control(pDX, IDC_BUTTON2, *m_InsertFileButton);
	DDX_Control(pDX, IDC_BUTTON3, *m_testButton);

	DDX_Control(pDX, IDC_DateTimePICKER1, *m_startDatePicker);
	DDX_Control(pDX, IDC_DateTimePICKER2, *m_startTimePicker);
	DDX_Control(pDX, IDC_DateTimePICKER3, *m_endDatePicker);
	DDX_Control(pDX, IDC_DateTimePICKER4, *m_endTimePicker);
}

BEGIN_MESSAGE_MAP(CBackTestTradeMFCFormView, CFormView)
	ON_WM_PAINT()
	ON_WM_CREATE()

	ON_EN_CHANGE(IDC_MAIN_EDIT, &CBackTestTradeMFCFormView::OnEnChangeMainEdit)
	ON_EN_UPDATE(IDC_MAIN_EDIT, &CBackTestTradeMFCFormView::OnUpdateMainEdit)

	ON_BN_CLICKED(IDC_BUTTON1, &CBackTestTradeMFCFormView::OnRequestButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON2, &CBackTestTradeMFCFormView::OnInsertFileButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON3, &CBackTestTradeMFCFormView::OnTestButtonClicked)

	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DateTimePICKER1, &CBackTestTradeMFCFormView::OnDtnDateTimeChangeStartDatePicker)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DateTimePICKER2, &CBackTestTradeMFCFormView::OnDtnDateTimeChangeStartDatePicker)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DateTimePICKER3, &CBackTestTradeMFCFormView::OnDtnDateTimeChangeEndDatepicker)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DateTimePICKER4, &CBackTestTradeMFCFormView::OnDtnDateTimeChangeEndDatepicker)
END_MESSAGE_MAP()

// CBackTestTradeMFCFormView diagnostics

#ifdef _DEBUG
void CBackTestTradeMFCFormView::AssertValid() const {

	CFormView::AssertValid();

}

#ifndef _WIN32_WCE
void CBackTestTradeMFCFormView::Dump(CDumpContext& dc) const {

	CFormView::Dump(dc);

}
#endif
#endif //_DEBUG

void CBackTestTradeMFCFormView::OnInitialUpdate() {

	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}

void CBackTestTradeMFCFormView::AppendTextToEditCtrl(CEdit& edit, LPCTSTR pszText) {

	// get the initial text length
	int nLength = edit.GetWindowTextLength();
	// put the selection at the end of text
	edit.SetSel(nLength, nLength);
	// replace the selection
	edit.ReplaceSel(pszText);

}

void CBackTestTradeMFCFormView::OnEnChangeMainEdit() {

	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	//
	// TODO:  Add your control notification handler code here
}

void CBackTestTradeMFCFormView::OnUpdateMainEdit() {

	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	//
	// TODO:  Add your control notification handler code here
}

void CBackTestTradeMFCFormView::OnPaint() {

	CPaintDC dc(this);																	// device context for painting

	CRect rect;																			// Get the client rect.
	GetClientRect(&rect);

	CDC memoryDC;																		// Prepare for memory DC drawing.

	if (rect.Width() > 0 && rect.Height() > 0 &&
		memoryDC.CreateCompatibleDC(&dc)) {

		m_edit->SetWindowPos(															// Draw edit
			this, rect.left + 5, 
			rect.top + 200, 
			rect.Width() - 10, 
			rect.Height() - 205, 
			SWP_NOZORDER);

		//CBitmap bitmap;																// sample 
		//if (bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height()))
		//{
		//	CDC* pDC = &memoryDC;
		//
		//	// Select bitmap into memory DC.
		//	CBitmap* pOldBitmap = pDC->SelectObject(&bitmap);
		//
		//	// Set up the memory DC for drawing graphics and text.
		//	CPen pen(PS_SOLID, 1, RGB(0, 0, 255));
		//	CPen* pOldPen = pDC->SelectObject(&pen);
		//	CBrush* pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
		//	COLORREF oldTextColor = pDC->SetTextColor(RGB(0, 0, 255));
		//	int oldBkMode = pDC->SetBkMode(TRANSPARENT);
		//
		//	// Fill the background.
		//	pDC->FillSolidRect(&rect, RGB(0, 255, 0));
		//
		//	// Draw a rectangle representing the display size.
		//	// The rectangle needs to be offset due to scrolling position.
		//	CRect dispRect;
		//	dispRect.SetRect(0, 0,
		//		m_scrollHelper->GetDisplaySize().cx,
		//		m_scrollHelper->GetDisplaySize().cy);
		//	dispRect.OffsetRect(-m_scrollHelper->GetScrollPos().cx,
		//		-m_scrollHelper->GetScrollPos().cy);
		//	pDC->Rectangle(&dispRect);
		//
		//	// Draw text information.
		//	DrawScrollInfo(pDC);
		//
		//	// Do the bitblt.
		//	dc.BitBlt(0, 0, rect.Width(), rect.Height(),
		//		pDC, 0, 0, SRCCOPY);
		//
		//	// Restore DC state.
		//	pDC->SetBkMode(oldBkMode);
		//	pDC->SetTextColor(oldTextColor);
		//	pDC->SelectObject(pOldBrush);
		//	pDC->SelectObject(pOldPen);
		//	pDC->SelectObject(pOldBitmap);
		//}
	}
}

int CBackTestTradeMFCFormView::OnCreate(LPCREATESTRUCT lpCreateStruct) {

	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

void CBackTestTradeMFCFormView::OnTestButtonClicked() {

	// test 1 : db request and build a time series object
	CTABLE_QUOTE *rs = new CTABLE_QUOTE(m_db);											// Create a recordset

	std::vector<thOth::dateTime> dates;
	std::vector<thOth::quoteDetails> quotes;
	std::wstring reqStr;																// SQL request
	reqStr.append(_T("SELECT * FROM TABLE_QUOTE WHERE(QUOTE_TIME >= '"));
	reqStr.append(_T("2013-Oct-25 10:00:00.000"));
	reqStr.append(_T("' AND QUOTE_TIME < '"));
	reqStr.append(_T("2013-Oct-25 10:30:00.000"));
	reqStr.append(_T("')"));

	rs->Open(CRecordset::forwardOnly, reqStr.c_str());									// request

	if (rs->IsBOF()) {

		AppendTextToEditCtrl(*m_edit,
			_T("No Data found for the passed parameters."));
		delete rs;
		return;

	}

	else {

		while (!rs->IsEOF()) {
					
			m_timeSeries->insert(														// fill the TS object
				std::pair<thOth::dateTime, thOth::quoteDetails>(					
				rs->getQuoteDateTime(), rs->getQuoteDetails()));

			rs->MoveNext();

		}

	}

	delete rs;

	for (thOth::TimeSeries<thOth::quoteDetails>::const_iterator It
		= m_timeSeries->cbegin(); It != m_timeSeries->cend(); It++) {
	
		thOth::quoteDetails test = It->second;
		float quoteVal = test.QUOTE_VALUE;
	
	}

	// test 2 : create a portfolio of simple strategies related to the ts
	thOth::portfolio port;

	// default ctor-> current time
	port.push_back(boost::shared_ptr<thOth::strategy>(
		new thOth::marketOrder));

	// trade on May the 5th at 15:30:12
	port.push_back(boost::shared_ptr<thOth::strategy>(
		new thOth::marketOrder(thOth::dateTime(2014, 5, 5,
			boost::posix_time::time_duration(15, 30, 12, 0)))));

}

void CBackTestTradeMFCFormView::OnInsertFileButtonClicked() {

	// TODO: Add your control notification handler code here

}

// CBackTestTradeMFCFormView message handlers
void CBackTestTradeMFCFormView::OnRequestButtonClicked() {

	// TODO: Add your control notification handler code here
	delete m_timeSeries;																// delete the former data set
	m_timeSeries = new thOth::TimeSeries<thOth::quoteDetails>();						// TODO: make a better allocation step

	thOth::dateTime st = thOth::dateTime::currentTime();								// Start Chrono-> boost chrono ?

	CTABLE_QUOTE *rs = new CTABLE_QUOTE(m_db);											// Create a recordset

	try{

		std::wstring reqStr;															// SQL request
		reqStr.append(_T("SELECT * FROM TABLE_QUOTE WHERE(QUOTE_TIME >= '"))
			.append(boost::posix_time::to_simple_wstring(*m_startDate))
			.append(_T("' AND QUOTE_TIME < '"))
			.append(boost::posix_time::to_simple_wstring(*m_endDate))
			.append(_T("')"));

		rs->Open(CRecordset::forwardOnly, reqStr.c_str());								// request

		if (rs->IsBOF()) {
		
			AppendTextToEditCtrl(*m_edit, 
				_T("No Data found for the passed parameters."));
			delete rs;
			return;
		
		}
		
		do  {

			m_timeSeries->insert(std::pair<thOth::dateTime, thOth::quoteDetails>(		// fill the TS object
				rs->getQuoteDateTime(), rs->getQuoteDetails()));
			rs->MoveNext();

		} while (!rs->IsEOF());

		delete rs;

	}
	catch (...) {
	
		AppendTextToEditCtrl(*m_edit, 
			_T("An unknown error occured...\r\n"));
	
	}

	thOth::dateTime end = thOth::dateTime::currentTime();								// chrono

	std::wstring summaryStr;															// summary
	summaryStr.append(_T("\r\n\r\nRequest Summary : \r\n"))
		.append(_T("----------------\r\n"))
		.append(_T("request performed in "))
		.append(boost::lexical_cast<std::wstring>(end - st))
		.append(_T("seconds\r\n"))
		.append(boost::lexical_cast<std::wstring>(m_timeSeries->size()))
		.append(_T(" quotes successfully read,\r\n"))
		.append(_T("\r\nThe 100 first trade recorded:\r\n"));

	int i = 0;
	for (thOth::TimeSeries<thOth::quoteDetails>::const_iterator It = m_timeSeries->begin();
		(It != m_timeSeries->end() && i < 100); It++) {

		if (It->second.QUOTE_TYPE == thOth::Trade) {

			summaryStr.append(_T("Time: "))
				.append(boost::lexical_cast<std::wstring>(It->first))
				.append(_T(", Price: "))
				.append(boost::lexical_cast<std::wstring>(It->second.QUOTE_VALUE))
				.append(_T("\r\n"));
			i++;

		}
			
	}

	AppendTextToEditCtrl(*m_edit, summaryStr.c_str());

}

void CBackTestTradeMFCFormView::OnDtnDateTimeChangeStartDatePicker(
	NMHDR *pNMHDR, LRESULT *pResult) {

	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);

	SYSTEMTIME rawDate;																		// retrieve Date from controls
	m_startDatePicker->GetTime(&rawDate);

	SYSTEMTIME rawTime;																		// retrieve Date from controls
	m_startTimePicker->GetTime(&rawTime);

	rawDate.wHour = rawTime.wHour;															// merge the two data
	rawDate.wMinute = rawTime.wMinute;
	rawDate.wSecond = rawTime.wSecond;
	rawDate.wMilliseconds = 0;

	m_startDate->~dateTime();	

	m_startDate = new (m_startDate)thOth::dateTime(											// TODO : change data members
		thOth::dateTimeConversion(&rawDate));	

	*pResult = 0;

}

void CBackTestTradeMFCFormView::OnDtnDateTimeChangeEndDatepicker(
	NMHDR *pNMHDR, LRESULT *pResult) {

	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	
	SYSTEMTIME rawDate;																		// retrieve Date from controls
	m_endDatePicker->GetTime(&rawDate);

	SYSTEMTIME rawTime;																		// retrieve Date from controls
	m_endTimePicker->GetTime(&rawTime);

	rawDate.wHour = rawTime.wHour;															// merge the two data
	rawDate.wMinute = rawTime.wMinute;
	rawDate.wSecond = rawTime.wSecond;
	rawDate.wMilliseconds = 0;

	m_endDate->~dateTime();																	// reallocate m_startDate
	

	
	m_endDate = new (m_endDate)thOth::dateTime(												// TODO : change data members
		thOth::dateTimeConversion(&rawDate));												

	*pResult = 0;

}
