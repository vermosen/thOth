#pragma once
#include "afxwin.h"
#include <thOth/time/timeseries.h>
#include "DataBase/Recordset/TABLE_QUOTE.h"
#include "afxdtctl.h"
#include "conversions/DateTime/DateTime.h"

class CBackTestTradeMFCFormView : public CFormView {						// CBackTestTradeMFCFormView form view

	DECLARE_DYNCREATE(CBackTestTradeMFCFormView)

protected:
	CBackTestTradeMFCFormView();											// protected constructor used by dynamic creation
	virtual ~CBackTestTradeMFCFormView();

public:
	enum { IDD = IDD_BACKTESTTRADEMFCFORMVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

private:
	CEdit* m_edit;															// edit control

	CDateTimeCtrl* m_startDatePicker;										// date pickers
	CDateTimeCtrl* m_startTimePicker;
	CDateTimeCtrl* m_endTimePicker;
	CDateTimeCtrl* m_endDatePicker;

	CButton* m_requestButton;												// button to request the whole db content
	CButton* m_InsertFileButton;											// Button to load a defined file in the database
	CButton* m_testButton;													// launches a test 
	
	CDatabase* m_db;														// db object

	thOth::TimeSeries<thOth::quoteDetails>* m_timeSeries;					// current time series
	thOth::dateTime* m_startDate;
	thOth::dateTime* m_endDate;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);						// DDX/DDV support
	void AppendTextToEditCtrl(CEdit& edit, LPCTSTR pszText);

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnRequestButtonClicked();
	afx_msg void OnEnChangeMainEdit();
	afx_msg void OnUpdateMainEdit();
	afx_msg void OnInsertFileButtonClicked();
	afx_msg void OnPaint();
	afx_msg void OnInitialUpdate();
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTestButtonClicked();
	afx_msg void OnDtnDateTimeChangeStartDatePicker(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDtnDateTimeChangeEndDatepicker(NMHDR *pNMHDR, LRESULT *pResult);
};


