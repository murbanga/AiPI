// Aipi_ScriptCode.h: interface for the CAipi_ScriptCode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_SCRIPTCODE_H__7A071A1A_55DE_4634_9EF7_B37C91339E49__INCLUDED_)
#define AFX_AIPI_SCRIPTCODE_H__7A071A1A_55DE_4634_9EF7_B37C91339E49__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAipi_ScriptCode  
{
public:
	CAipi_ScriptCode();
	virtual ~CAipi_ScriptCode();

	inline CAipi_ScriptCode(long iform, tstring name, long index1, long index2, long pos1, long pos2, int nparam, CString lang, CString def )
	{
		m_ScriptName		= name;
		m_StartIndex		= index1;
		m_EndIndex			= index2;
		m_StartPos			= pos1;
		m_EndPos			= pos2;
		m_nParameters		= nparam;
		m_ScriptLanguage	= lang;
		m_ScriptDefinition	= def;

	}

	inline void CAipi_ScriptCode::setScriptId(long iform)
	{
		m_ScriptId = iform;
	}

	
	inline void CAipi_ScriptCode::setScriptName(tstring name)
	{
		m_ScriptName = name;
	}

	inline void CAipi_ScriptCode::setStartIndex(long index1)
	{
		m_StartIndex = index1;
	}
	
	inline void CAipi_ScriptCode::setEndIndex(long index2)
	{
		m_EndIndex = index2;
	}

	inline void CAipi_ScriptCode::setStartPos(long pos1)
	{
		m_StartPos = pos1;
	}
	
	inline void CAipi_ScriptCode::setEndPos(long pos2)
	{
		m_EndPos = pos2;
	}

	inline void CAipi_ScriptCode::setParameters(int nparam)
	{
		m_nParameters = nparam;
	}

	inline void CAipi_ScriptCode::setScriptLanguage(CString lang)
	{
		m_ScriptLanguage = lang;
	}

	inline void CAipi_ScriptCode::setScriptDefinition(CString def)
	{
		m_ScriptDefinition = def;
	}

	inline long CAipi_ScriptCode::getScriptId()
	{
		return m_ScriptId;
	}
	
	inline tstring CAipi_ScriptCode::getScriptName()
	{
		return m_ScriptName;
	}


	inline long CAipi_ScriptCode::getStartIndex()
	{
		return m_StartIndex;
	}


	inline long CAipi_ScriptCode::getEndIndex()
	{
		return m_EndIndex;
	}

	inline long CAipi_ScriptCode::getStartPos()
	{
		return m_StartPos;
	}


	inline long CAipi_ScriptCode::getEndPos()
	{
		return m_EndPos;
	}


	inline int CAipi_ScriptCode::getParameters()
	{
		return m_nParameters;
	}

	inline CString CAipi_ScriptCode::getScriptLanguage()
	{
		return m_ScriptLanguage;
	}

	inline CString CAipi_ScriptCode::getScriptDefinition()
	{
		return m_ScriptDefinition;
	}

public:
CAipi_ScriptCode* CAipi_ScriptCode::addScriptCode(long iform, tstring name, long index1, long index2, long pos1, long pos2, int nparam, CString lang, CString def);
	void	eraseScriptCode(long id);
	void	clearScriptCode();	

	long    findId_Into_ScriptCode( long idform);

	tstring	findScriptName( long id);
	CString	findScriptDefinition( long id);
	CString	findScriptLanguage( long id);

	long	findScriptStartPos(long id);
	long	findScriptEndPos( long id);
	long	findScriptStartIndex( long id);
	long	findScriptEndIndex( long id);
	int		findScriptNoParameters( long id);
	int		findScriptMembers( long id);
	void	printScriptCode();



public:
	long			m_ScriptId;
	tstring			m_ScriptName;
	long			m_StartIndex;
	long			m_EndIndex;
	long			m_StartPos;
	long			m_EndPos;
	int				m_nParameters;
	CString			m_ScriptLanguage;
	CString			m_ScriptDefinition;


};

#endif // !defined(AFX_AIPI_SCRIPTCODE_H__7A071A1A_55DE_4634_9EF7_B37C91339E49__INCLUDED_)
