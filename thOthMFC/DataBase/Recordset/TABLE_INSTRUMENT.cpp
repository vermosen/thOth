// TABLE_INSTRUMENT.h : Implementation of the CTABLE_INSTRUMENT class



// CTABLE_INSTRUMENT implementation

// code generated on samedi 2 novembre 2013, 17:44

#include "stdafx.h"
#include "DataBase/Recordset/TABLE_INSTRUMENT.h"

IMPLEMENT_DYNAMIC(CTABLE_INSTRUMENT, CRecordset)

	CTABLE_INSTRUMENT::CTABLE_INSTRUMENT(CDatabase* pdb)
	: CRecordset(pdb) {

		m_ID_INSTRUMENT = 0;
		m_DES = L"";
		m_ISSUE_DATE;
		m_EXPIRY_DATE;
		m_nFields = 4;
		m_nDefaultType = dynaset;
	
	}
// #error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CTABLE_INSTRUMENT::GetDefaultConnect() {

	return _T("DSN=CIRCE;Description=HTF platform;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2013;WSID=MACBOOKWIN;DATABASE=CIRCE;ServerSPN=IdSourceCirce;");

}

CString CTABLE_INSTRUMENT::GetDefaultSQL() {

	return _T("[dbo].[TABLE_INSTRUMENT]");

}

void CTABLE_INSTRUMENT::DoFieldExchange(CFieldExchange* pFX) {

	pFX->SetFieldType(CFieldExchange::outputColumn);
	// Macros such as RFX_Text() and RFX_Int() are dependent on the
	// type of the member variable, not the type of the field in the database.
	// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[ID_INSTRUMENT]"), m_ID_INSTRUMENT);
	RFX_Text(pFX, _T("[DES]"), m_DES);
	RFX_Date(pFX, _T("[ISSUE_DATE]"), m_ISSUE_DATE);
	RFX_Date(pFX, _T("[EXPIRY_DATE]"), m_EXPIRY_DATE);

}
/////////////////////////////////////////////////////////////////////////////
// CTABLE_INSTRUMENT diagnostics

#ifdef _DEBUG
void CTABLE_INSTRUMENT::AssertValid() const {

	CRecordset::AssertValid();

}

void CTABLE_INSTRUMENT::Dump(CDumpContext& dc) const {

	CRecordset::Dump(dc);

}
#endif //_DEBUG
