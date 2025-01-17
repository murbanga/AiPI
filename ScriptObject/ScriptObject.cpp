///////////////////////////////////////////////////////////////////////////////
//	File:		ScriptObject.cpp
//	Version:	1.0
//
//	Author:		Ernest Laurentin
//	E-mail:		elaurentin@sympatico.ca
//
//	This class implements MSScript control
//	It can interface script from resource file or text file
//
//	This code may be used in compiled form in any way you desire. This
//	file may be redistributed unmodified by any means PROVIDING it is
//	not sold for profit without the authors written consent, and
//	providing that this notice and the authors name and all copyright
//	notices remains intact.
//
//	An email letting me know how you are using it would be nice as well.
//
//	This file is provided "as is" with no expressed or implied warranty.
//	The author accepts no liability for any damage/loss of business that
//	this c++ class may cause.
//
//	Version history
//
//	1.0	- Initial release.
//	1.1 - Bug fixes for VC7 and Unicode
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <comutil.h>
#include "ScriptObject.h"


///////////////////////////////////////////////////////////////////////////////
// Construction
CScriptObject::CScriptObject()
{
	CommonConstruct(); // will throw exception if failed
}


CScriptObject::~CScriptObject()
{
	// Destroy object- and release
	m_pScript = NULL;
}


///////////////////////////////////////////////////////////////////////////////
// Members

///////////////////////////////////////////////////////////////////////////////
// CommonConstruct
void CScriptObject::CommonConstruct()
{
	HRESULT hr = m_pScript.CreateInstance(__uuidof(ScriptControl));
	_com_util::CheckError( hr ); // will throw an exception if failed

	// will not come here if exception
	_tcscpy(m_szLanguage, LANGUAGE_DEFAULT);
	m_pScript->PutAllowUI( VARIANT_TRUE );
	m_pScript->PutLanguage( _bstr_t(m_szLanguage ) );
	
}


///////////////////////////////////////////////////////////////////////////////
// GetLanguage : Get current script language
LPCTSTR CScriptObject::GetLanguage()
{
	return m_szLanguage;
}


///////////////////////////////////////////////////////////////////////////////
// SetLanguage : Set current script language
void CScriptObject::SetLanguage(LPCTSTR szLanguage)
{
	_tcscpy(m_szLanguage, szLanguage);

	if (m_pScript != NULL)
	{
		m_pScript->PutLanguage( _bstr_t( szLanguage ) );
		m_pScript->Reset();
		m_FunctionList.clear();
	}
}


///////////////////////////////////////////////////////////////////////////////
// GetMethodsCount
int  CScriptObject::GetMethodsCount() const
{
	return m_FunctionList.size();
}


///////////////////////////////////////////////////////////////////////////////
// GetNameAt : Get method name at specified index
LPCTSTR CScriptObject::GetNameAt(unsigned int index)
{
	if( index >= 0 && index < m_FunctionList.size())
	{
		stl_string_list::iterator iter = m_FunctionList.begin();
		while( index > 0)
		{
			iter++;
			index--;
		}
		return (*iter).c_str();
	}
	return TEXT("");
}


///////////////////////////////////////////////////////////////////////////////
// Reset : Reset script control object
void CScriptObject::Reset()
{
	if (m_pScript != NULL)
	{
		m_pScript->Reset();

		// empty list...
		m_FunctionList.clear();
	}
}


///////////////////////////////////////////////////////////////////////////////
// GetErrorString : Get Script error string
LPCTSTR CScriptObject::GetErrorString()
{
	m_szError[0] = 0;
	if (m_pScript != NULL)
	{
		try{
			IScriptErrorPtr pError = m_pScript->GetError();
			if (pError != NULL)
			{
				_bstr_t str  = _bstr_t("ScriptError: ") + pError->GetDescription() + _bstr_t(".");
						str += pError->GetText() + _bstr_t(", in line ");
						str += _bstr_t(pError->GetLine());
				int count = __min(str.length(), ERROR_DESC_LEN); // string may be truncated...
				_tcsncpy(m_szError, (LPCTSTR) str, count);
				m_szError[count] = 0;
			    pError->Clear();
			}
		}
		catch(_com_error& e)
		{
			TRACE( (LPTSTR)e.Description() );
			TRACE( (LPTSTR)"\n" );
		}
	}

	return m_szError;
}

// GetErrorLineNumber : Get Script error line number
LPCTSTR CScriptObject::GetErrorLineNumber()
{
	m_szErrorLineNumber[0] = 0;
	
	if (m_pScript != NULL)
	{
		try{
			IScriptErrorPtr pError = m_pScript->GetError();
			if (pError != NULL)
			{
				_bstr_t line  =  _bstr_t(pError->GetLine());
									
				int count = __min(line.length(), ERROR_NUM_LEN); // string may be truncated...
				_tcsncpy(m_szErrorLineNumber, (LPCTSTR) line, count);
				m_szErrorLineNumber[count] = 0;
			    //pError->Clear();
			}
		}
		catch(_com_error& e)
		{
			TRACE( (LPTSTR)e.Description() );
			TRACE( (LPTSTR)"\n" );
		}
	}
	
	return m_szErrorLineNumber;	
}


// GetErrorColumnNumber : Get Script error line number
LPCTSTR CScriptObject::GetErrorColumn()
{
	m_szErrorColNumber[0] = 0;
	
	if (m_pScript != NULL)
	{
		try{
			IScriptErrorPtr pError = m_pScript->GetError();
			if (pError != NULL)
			{
				_bstr_t col  =  _bstr_t(pError->GetColumn());
									
				int count = __min(col.length(), ERROR_COL_LEN); // string may be truncated...
				_tcsncpy(m_szErrorColNumber, (LPCTSTR) col, count);
				m_szErrorColNumber[count] = 0;
			    //pError->Clear();
			}
		}
		catch(_com_error& e)
		{
			TRACE( (LPTSTR)e.Description() );
			TRACE( (LPTSTR)"\n" );
		}
	}
	
	return m_szErrorColNumber;	
}


// GetErrorHelpFile : Get Script error help file
LPCTSTR CScriptObject::GetErrorHelpFile()
{
	m_szErrorHelpFile[0] = 0;
	
	if (m_pScript != NULL)
	{
		try{
			IScriptErrorPtr pError = m_pScript->GetError();
			if (pError != NULL)
			{
				_bstr_t helpfile  =  _bstr_t(pError->GetHelpFile());
									
				int count = __min(helpfile.length(), ERROR_HELPFILE_LEN); // string may be truncated...
				_tcsncpy(m_szErrorHelpFile, (LPCTSTR) helpfile, count);
				m_szErrorHelpFile[count] = 0;
			    //pError->Clear();
			}
		}
		catch(_com_error& e)
		{
			TRACE( (LPTSTR)e.Description() );
			TRACE( (LPTSTR)"\n" );
		}
	}
	
	return m_szErrorHelpFile;	
}



// GetErrorNumber : Get Script error number
LPCTSTR CScriptObject::GetErrorNumber()
{
	m_szErrorNumber[0] = 0;
	
	if (m_pScript != NULL)
	{
		try{
			IScriptErrorPtr pError = m_pScript->GetError();
			if (pError != NULL)
			{
				_bstr_t num  =  _bstr_t(pError->GetNumber());
									
				int count = __min(num.length(), ERROR_NUM_LEN); // string may be truncated...
				_tcsncpy(m_szErrorNumber, (LPCTSTR) num, count);
				m_szErrorNumber[count] = 0;
			    //pError->Clear();
			}
		}
		catch(_com_error& e)
		{
			TRACE( (LPTSTR)e.Description() );
			TRACE( (LPTSTR)"\n" );
		}
	}
	
	return m_szErrorNumber;	
}




// GetErrorDescription : Get Script error description
LPCTSTR CScriptObject::GetErrorDescription()
{
	m_szErrorDescription[0] = 0;
	if (m_pScript != NULL)
	{
		try{
			IScriptErrorPtr pError = m_pScript->GetError();
			if (pError != NULL)
			{
				_bstr_t desc  = _bstr_t("ScriptError: ") + pError->GetDescription() + _bstr_t(".");
						
				int count = __min(desc.length(), ERROR_DESC_LEN); // string may be truncated...
				_tcsncpy(m_szErrorDescription, (LPCTSTR) desc, count);
				m_szErrorDescription[count] = 0;
			    //pError->Clear();
			}
		}
		catch(_com_error& e)
		{
			TRACE( (LPTSTR)e.Description() );
			TRACE( (LPTSTR)"\n" );
		}
	}

	return m_szErrorDescription;	
}

// GetErrorDescription : Get Script error description
void CScriptObject::ClearError()
{
	
	if (m_pScript != NULL)
	{
		try{
			IScriptErrorPtr pError = m_pScript->GetError();
			if (pError != NULL)
			{
				pError->Clear();
			}
		}
		catch(_com_error& e)
		{
			TRACE( (LPTSTR)e.Description() );
			TRACE( (LPTSTR)"\n" );
		}
	}
	
}


///////////////////////////////////////////////////////////////////////////////
// GetMethodsName: Get methods name list
bool CScriptObject::GetMethodsName()
{
	bool bResult = false;
	if (m_pScript != NULL)
	{
		IScriptProcedureCollectionPtr pIProcedures = m_pScript->GetProcedures();

		// empty list...
		m_FunctionList.clear();

		try{
			long count = pIProcedures->GetCount();
			for(long index=1; index <= count; index++)
			{
				IScriptProcedurePtr pIProcPtr = pIProcedures->GetItem( _variant_t(index) );
				_bstr_t name = pIProcPtr->GetName();
				m_FunctionList.insert(m_FunctionList.end(), (LPCTSTR) name );
				pIProcPtr = NULL;
			}

			bResult = true;
		}
		catch(...)
		{
			// Just catch the exception, call GetErrorString()
			// to retreive last error
		}

		pIProcedures = NULL;
	}
	return bResult;
}


///////////////////////////////////////////////////////////////////////////////
// GetScriptFunction
//		Get Script function name, this is useful for script with case sensitive
//		function name.
LPCTSTR CScriptObject::GetScriptFunction(LPCTSTR szName)
{
	stl_string_list::iterator iter = m_FunctionList.begin();
	while( iter != m_FunctionList.end() )
	{
		if ((*iter).compare(szName) == 0)
			return (*iter).c_str();
		iter++;
	}
	return TEXT("");
}


//////////////////////////////////////////////////////////////////////////
// LoadScriptResource:
//		Load a Script resource.  This function loads and insert all functions
//		and procedures to the component.  The script resource may contain comments
//		as well.  Global variables may also be defined. You may want to see the
//		script resource as a Module file in Visual Basic.
//////////////////////////////////////////////////////////////////////////
bool CScriptObject::LoadScriptResource(LPCTSTR lpName, LPCTSTR lpType, HINSTANCE hInstance )
{
	try{
		if (m_pScript)
		{
			HRSRC res = ::FindResource(hInstance, lpName, lpType);
			ASSERT( res != NULL);
			BYTE* pbytes = (BYTE*) LockResource(LoadResource(hInstance, res ));
			ASSERT( pbytes != NULL);
			_bstr_t strCode = (LPCSTR) (pbytes);
			m_pScript->AddCode( strCode );
			GetMethodsName();
			return true;
		}
	}
	catch(...)
	{
		// Just catch the exception, call GetErrorString()
		// to retreive last error
	}
	return false;
}


///////////////////////////////////////////////////////////////////////////////
// LoadScript
//		Load a Script File.  This function loads and insert all functions and
//		procedures to the component.  The script file may contain comments as well.
//		Global variables may also be define. You may want to see the script file
//		as a Module file in Visual Basic.
//		The script file is probably a simple text file (ASCII format)
///////////////////////////////////////////////////////////////////////////////
bool CScriptObject::LoadScript(LPCTSTR szFilename)
{
	HANDLE hFile = CreateFile(szFilename, GENERIC_READ, FILE_SHARE_READ,
			NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		DWORD dwSize = GetFileSize(hFile, NULL);
		if (0xFFFFFFFF != dwSize)
		{
			BYTE* pbytes = (BYTE*) GlobalAlloc(GPTR, dwSize+1);
			if (pbytes != NULL)
			{
				DWORD dwRead = 0;
				bool bResult = false;
				if (ReadFile(hFile, pbytes, dwSize, &dwRead, NULL))
				{
					try{
						if (m_pScript)
						{
							_bstr_t strCode = (LPCSTR) (pbytes);
							m_pScript->AddCode( strCode );
							GetMethodsName();
							bResult = true;
						}
					}
					catch(...)
					{
						// Just catch the exception, call GetErrorString()
						// to retreive last error
					}

					GlobalFree( (HGLOBAL) pbytes);
					CloseHandle(hFile);
					return bResult;
				}

				GlobalFree( (HGLOBAL) pbytes);
			}
		}

		CloseHandle(hFile);
		return false;
	}

	return false;
}


///////////////////////////////////////////////////////////////////////////////
// AddScript
//		Use this function to add a script function, useful for internal use
//		not global script (resource file).
///////////////////////////////////////////////////////////////////////////////
bool CScriptObject::AddScript(LPCTSTR szCode)
{
	try {
		if (m_pScript != NULL)
		{
			ULONG ref = m_pScript->AddRef();
			_bstr_t strCode = szCode;
			m_pScript->AddCode( strCode );
			GetMethodsName();
			ref = m_pScript->Release();
			return true;
		}
	}
	catch(...)
	{
		// Just catch the exception, call GetErrorString()
		// to retreive last error
		ULONG ref = m_pScript->Release();
	}
	return false;
}


///////////////////////////////////////////////////////////////////////////////
// ExecuteStatement
//		Use this function to execute a "Sub routine" - no arguments
///////////////////////////////////////////////////////////////////////////////
bool CScriptObject::ExecuteStatement(LPCTSTR szStatement)
{
	try {
		if (m_pScript != NULL)
		{
			ULONG ref = m_pScript->AddRef();
			m_pScript->ExecuteStatement( _bstr_t(szStatement) );
			ref = m_pScript->Release();
			return true;
		}
	}
	catch(...)
	{
		// Just catch the exception, call GetErrorString()
		// to retreive last error
		ULONG ref = m_pScript->Release();
	}
	
	return false;
}


///////////////////////////////////////////////////////////////////////////////
// RunProcedure
//		Use this function to run a "Procedure" or "Function" - with arguments
///////////////////////////////////////////////////////////////////////////////
bool CScriptObject::RunProcedure(LPCTSTR szProcName, SAFEARRAY** saParameters, VARIANT* varRet)
{
	// required argument
	ASSERT( saParameters != NULL);
	ASSERT( varRet  != NULL);

	try {
		if (m_pScript != NULL)
		{
			ULONG ref = m_pScript->AddRef();
			bool  bResult = false;
			_bstr_t szFunc  = GetScriptFunction(szProcName);
			if (szFunc.length() > 0)
			{
				*varRet = m_pScript->Run(szFunc, saParameters);
				bResult = true;
			}
			ref = m_pScript->Release();
			return bResult;
		}
	}
	catch(...)
	{
		// Just catch the exception, call GetErrorString()
		// to retreive last error
		ULONG ref = m_pScript->Release();
	}
	return false;
}

