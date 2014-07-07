// TABLE_QUOTE.h : Implementation of the CTABLE_QUOTE class
// CTABLE_QUOTE implementation
// code generated on samedi 2 novembre 2013, 18:03

#include "stdafx.h"
#include "DataBase/Recordset/TABLE_QUOTE.h"

IMPLEMENT_DYNAMIC(CTABLE_QUOTE, CRecordset)

CTABLE_QUOTE::CTABLE_QUOTE(CDatabase* pdb)
	: CRecordset(pdb) {

	m_ID_QUOTE = 0;
	m_quoteData.ID_INSTRUMENT = 0;
	m_quoteData.QUOTE_TIME;
	m_quoteData.TRADE.type_ = thOth::Undefined;
	m_quoteData.TRADE.value_ = 0.0;
	m_quoteData.TRADE.volume_ = 0.0;
	m_nFields = 6;
	m_nDefaultType = dynaset;
}
// #error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CTABLE_QUOTE::GetDefaultConnect() {

	return _T("DSN=CIRCE;Description=HTF platform;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2013;WSID=MACBOOKWIN;DATABASE=CIRCE;ServerSPN=IdSourceCirce;");

}

CString CTABLE_QUOTE::GetDefaultSQL() {

	return _T("[dbo].[TABLE_QUOTE]");

}

void CTABLE_QUOTE::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);

	BYTE tempQuote = (BYTE)m_quoteData.TRADE.type_;				// prior conversion
	float tempValue = (float)m_quoteData.TRADE.value_;
	float tempVolume = (float)m_quoteData.TRADE.volume_;

// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_BigInt(pFX, _T("[ID_QUOTE]"), m_ID_QUOTE);
	RFX_BigInt(pFX, _T("[ID_INSTRUMENT]"), m_quoteData.ID_INSTRUMENT);
	RFX_Date(pFX, _T("[QUOTE_TIME]"), m_quoteData.QUOTE_TIME);
	RFX_Byte(pFX, _T("[QUOTE_TYPE]"), tempQuote);
	RFX_Single(pFX, _T("[QUOTE_VALUE]"), tempValue);
	RFX_Single(pFX, _T("[QUOTE_AMT]"), tempVolume);

}

// accessors
thOth::dateTime CTABLE_QUOTE::getQuoteDateTime() const {

	return thOth::dateTimeConversion(m_quoteData.QUOTE_TIME); 

}

thOth::quote CTABLE_QUOTE::getQuoteValue() const {

	return m_quoteData.TRADE;

}

/////////////////////////////////////////////////////////////////////////////
// CTABLE_QUOTE diagnostics
#ifdef _DEBUG
void CTABLE_QUOTE::AssertValid() const
{
	CRecordset::AssertValid();
}

void CTABLE_QUOTE::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


