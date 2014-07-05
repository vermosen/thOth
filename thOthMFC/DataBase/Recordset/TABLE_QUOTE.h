// TABLE_QUOTE.h : Declaration of the CTABLE_QUOTE
#pragma once

#include "afxdb.h"
#include "conversions/DateTime/DateTime.h"
// code generated on samedi 2 novembre 2013, 18:03

#include <thOth/types.hpp>
#include <thOth/quote/quote.hpp>

struct dbQuote{													// dbQuote struct											

	LONGLONG         ID_INSTRUMENT;
	TIMESTAMP_STRUCT QUOTE_TIME   ;
	thOth::quote     TRADE        ;

};

class CTABLE_QUOTE : public CRecordset {

public:

	void testInsert();

	CTABLE_QUOTE(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CTABLE_QUOTE)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

private:
	LONGLONG	m_ID_QUOTE;
	dbQuote     m_quoteData;

//accessors
public:
	thOth::dateTime getQuoteDateTime() const;
	thOth::quote    getQuotevalue   () const;

// Overrides
	// Wizard generated virtual function overrides
	public:
	virtual CString GetDefaultConnect();					// Default connection string

	virtual CString GetDefaultSQL(); 						// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);		// RFX support

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


