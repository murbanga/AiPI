// Aipi_Error.h: interface for the CAipi_Error class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_ERROR_H__698A3D03_7841_42E4_868C_22422EA4517C__INCLUDED_)
#define AFX_AIPI_ERROR_H__698A3D03_7841_42E4_868C_22422EA4517C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAipi_Error  
{
public:
	CAipi_Error();
	virtual ~CAipi_Error();

	inline CAipi_Error( CString msg, CString lnk, int categ )
	{
		m_ErrorMsg = msg;
		m_ErrorLink = lnk;
		m_ErrorCateg = categ;
	}

	inline void CAipi_Error::setMessage(CString msg)
	{
		m_ErrorMsg = msg;

	}

	inline void CAipi_Error::setLink(CString lnk)
	{
		m_ErrorLink = lnk;

	}

	inline void CAipi_Error::setCateg(int categ)
	{
		m_ErrorCateg = categ;
	}
	
	
	inline CString CAipi_Error::getMessage()
	{
		return m_ErrorMsg;
	}
	
	inline CString CAipi_Error::getLink()
	{
		return m_ErrorLink;
	}

	
	inline int CAipi_Error::getCateg()
	{
		return m_ErrorCateg;
	}



public:

	CAipi_Error* CAipi_Error::addError(int index, CString msg, CString lnk, int categ);
	int			openDocFile(LPCTSTR lpszPathName);
	void		displayGUIError(int e, int type, CString desc);
	void		displayFileError(int e, int type, CString desc);
	void		displayRunTimeFileError(int e, int type, CString path, CString desc);
	void		errorMark(unsigned int line);
	void		printError();
	int         findErrorMembers(int e);
	


public:
	CString		m_ErrorMsg;
	CString		m_ErrorLink;
	int			m_ErrorCateg;




};	

#endif // !defined(AFX_AIPI_ERROR_H__698A3D03_7841_42E4_868C_22422EA4517C__INCLUDED_)
