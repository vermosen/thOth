// TABLE_INSTRUMENT.h : Declaration of the CTABLE_INSTRUMENT

#pragma once

#include "afxdb.h"
// code generated on samedi 2 novembre 2013, 17:44
class CTABLE_INSTRUMENT : public CRecordset {

public:
	CTABLE_INSTRUMENT(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CTABLE_INSTRUMENT)

	// Field/Param Data

	// The string types below (if present) reflect the actual data type of the
	// database field - CStringA for ANSI datatypes and CStringW for Unicode
	// datatypes. This is to prevent the ODBC driver from performing potentially
	// unnecessary conversions.  If you wish, you may change these members to
	// CString types and the ODBC driver will perform all necessary conversions.
	// (Note: You must use an ODBC driver version that is version 3.5 or greater
	// to support both Unicode and these conversions).

	long m_ID_INSTRUMENT;
	CStringW m_DES;
	CTime m_ISSUE_DATE;
	CTime m_EXPIRY_DATE;

	// Overrides
	// Wizard generated virtual function overrides
public:
	virtual CString GetDefaultConnect();	// Default connection string

	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support

	// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


