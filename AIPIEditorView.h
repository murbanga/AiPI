#if !defined(AFX_AIPIEDITORVIEW_H__FD49D6D2_197B_479F_9167_1708ECA57C0F__INCLUDED_)
#define AFX_AIPIEDITORVIEW_H__FD49D6D2_197B_479F_9167_1708ECA57C0F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AIPIEditorView.h : header file
//

#include ".\ScintillaCtrl\ScintillaDocView.h"
#include ".\ScriptObject\ScriptObject.h"
#include ".\ScriptObject\SafeArrayHelper.h"

#include "AIPI_Engine/Aipi_RETE_Network.h"

#include "Aipi_Main.h"
#include "Aipi_Lexer.h"
#include "WorkspaceTree1.h"

#include "OXSkinnedView.h"


/////////////////////////////////////////////////////////////////////////////
//Scintilla Modified Events Values (SCNotification.modificationType Flag)
#define INSERTTEXT				17
#define	DELETETEXT				18
#define MULTISTEP_UNDOINSERT	161
#define	MULTISTEPUNDO			162
#define	MULTISTEPREDO			193
#define	MULTISTEP_REDODELETE	194
#define	LASTSTEPUNDOINSERT		417
#define	LASTSTEPUNDO			418
#define	LASTSTEPREDO			449
#define	LASTSTEPREDODELETE		450
#define	BEFOREINSERT			1040
#define	MULTILINEUNDO			1056
#define	PERFORMED_REDO			1088
#define	BEFOREDELETE			2064
#define PERFORMED_UNDO			2080
#define	MULTILINEREDO			2112
#define	MULTILINEUNDODELETE		4385					
#define	MULTILINEUNDOINSERT		4386
#define	MULTILINEREDOINSERT		4417
#define	MULTILINEREDODELETE		4418
#define LASTSTEPUNDOREDO		4513



// CAIPIEditorView view
#define MAX_COMMENT_LENGTH	64
#define	TEXT_LENGTH			64
#define AUTOCOMPLETEKEYWORD_SIZE	12
#define AUTOCOMPLETEPERIOD_SIZE		8
	

#define EDITORBASEVIEW CScintillaView

class CAIPIEditorView : public COXSkinnedView<EDITORBASEVIEW>
{
protected: // create from serialization only
	

	CAIPIEditorView();
	DECLARE_DYNCREATE(CAIPIEditorView)

// Attributes
public:
	CAIPIEditorDoc* GetDocument();
    
protected:
	CScriptObject	m_ScriptObj;
	//Find in files flag
	BOOL			m_bFindInFiles;
	
	
	//Edit options flags
	BOOL			m_bViewWS;
	BOOL			m_bIndentationWSVisible;
	BOOL			m_bViewEOL;
	BOOL			m_bViewIndent;
	BOOL			m_bAutoIndent;
	BOOL			m_bAutoComplete;

	
	
	//Workspace modifications flags 
	BOOL			m_bFlagWriteRule;
	BOOL			m_bFlagWriteFunction;
	BOOL			m_bFlagWriteJSFunction;
	BOOL			m_bFlagWriteVBSFunction;
	BOOL			m_bFlagWriteVBSFUNCTION;
	BOOL			m_bFlagWriteVariable;
	BOOL			m_bFlagWriteClass;
	BOOL			m_bFlagWriteQuery;
	
	BOOL			m_bFlagWriteError;
	
	BOOL			m_bFlagEditClass;
	BOOL			m_bFlagEditRule;
	BOOL			m_bFlagEditFunction;
	BOOL			m_bFlagEditJSFunction;
	BOOL			m_bFlagEditVBSFunction;
	BOOL			m_bFlagEditVBSFUNCTION;
	BOOL			m_bFlagEditVariable;
	BOOL			m_bFlagEditQuery;

	BOOL			m_bFlagPaste;
		
	BOOL			m_bRuleCloseParenthesis;
	BOOL			m_bFunctionCloseParenthesis;
	BOOL			m_bJSFunctionCloseParenthesis;
	BOOL			m_bVBSFunctionCloseParenthesis;
	BOOL			m_bVBSFUNCTIONCloseParenthesis;
	BOOL			m_bVariableSemiColon;
	BOOL			m_bClassOpenBrace;
	BOOL			m_bQueryEqual;

	//Scintilla modified events flags
	BOOL			m_bFlagBeforeInsert;
	BOOL			m_bFlagBeforeDelete;
	BOOL			m_bFlagInsertText;
	BOOL			m_bFlagDeleteText;
	
	BOOL			m_bFlagUndoInsert;
	BOOL			m_bFlagRedoInsert;


	

	int				m_nMarkers;	
	int				m_nBreakpoints;	
	int				m_nCol;
	int				m_nPasteLength;
	//int				m_nRuleSyntaxError;
	
	
	long			m_DocumentLength;
	long			m_StartLimit;
	CString			m_sTokenName;
	CString			m_sCurrentClassName;
	CString			m_sCurrentQueryName;
	CString			m_sCurrentRuleName;
	CString			m_sCurrentFunctionName;
	CString			m_sCurrentVariableName;
	CString			m_sCurrentType;
	CString			m_sCurrentWord;
	CString         m_sTemp;
	int				m_iSymbol;
	int				m_iModificationType;	 //Detects the Modified notifications:
									//SC_MOD_BEFOREINSERT| SC_MOD_BEFOREDELETE and SC_MOD_INSERTTEXT | SC_MOD_DELETETEXT 
	long			m_lookahead;	//Parser look ahead
	
	

private:
	CString m_sAutoCompleteKeyWord[AUTOCOMPLETEKEYWORD_SIZE];
	CString	m_sAutoCompleteMath[24]; //JScript Object Math
	CString	m_sAutoCompleteDate[20]; //JSCript Object Date
	CString	m_sAutoCompleteArray[5]; //JSCript Object Array

	//Saves script function parameters
	vector<CString>	m_vParameters;

	//Saves keywords for autocomplete that appear with the period symbol
	typedef std::map<CString, CString> m_mPeriodKeyWords;
	m_mPeriodKeyWords	mPeriodKeyWords;
	//Saves keywors for script language JSCript
	typedef std::map<CString, CString> m_mJScriptObj;
	m_mJScriptObj	mJScriptObj;
	
	stack<long>		m_posPasteStart;
	stack<long>		m_posPasteEnd;
	

// Operations
protected:
 
	
  void ScriptLoadCode(long nStartSel, long nEndSel);
  void ScriptDisplayError(long nStartSel);
  void ScriptExecute(CString sProc, long posStartProc, long posOpenParenthesis, long posCloseParenthesis);	

  void AutoIndent(long pos, int symbol );
  
  void FillAutoCompleteAIPIKeyWords();
  void FillAutoCompleteJSCriptKeyWords();

  void AutoCompleteAIPIKeyWord( int symbol);
  void AutoCompleteJScript();
  void AutoCompleteJSDateArrayObj(int n, long nStart, long nEnd);
  void AutoCompleteJSDateArrayId();
  
   
  void SetAStyle(int style, COLORREF fore, COLORREF back=RGB(0xff, 0xff, 0xff), int size=-1, const char *face=0);
  void DefineMarker(int marker, int markerType, COLORREF fore, COLORREF back);
  void ErrorMark(int nLine);
  void FillFunctionsTree();	
  BOOL FindText(LPCTSTR lpszFind);
  void FindCurrentDirFiles();
  void FindCurrentProjectFiles();


  //Properties Window		
  void InsertProperties();


  //Lexer Functions
  bool		isDigit(int c);
  bool		isAlphabetic(int c);
  bool		isAlphaNumeric(int c);
  bool		isOperator(int c);
  bool		isPunctuator(int c);
  bool		isTypeName(CString s);


//Workspace Functions
  void		WSPWriteRule(long pos);
  void		WSPWriteFunction(long pos);
  void		WSPWriteJSFunction(long pos);
  void		WSPWriteVBSFunction(long pos);
  void		WSPWriteVBSFUNCTION(long pos);
  void		WSPWriteVariable(long pos);
  void		WSPWriteClass(long pos);
  void		WSPWriteQuery(long pos);
  
  void		WSPEditRule(long pos);
  void		WSPEditClass(long pos);
  void		WSPEditQuery(long pos);
  void		WSPEditJSFunction(long pos);
  void		WSPEditVBSFunction(long pos);
  void		WSPEditVBSFUNCTION(long pos);
  void		WSPEditFunction(long pos, LPSTR szType, int typelen);
  void		WSPEditVariable(long pos, LPSTR szType, int typelen);
  void		WSPRuleUndo();
  void		WSPRuleRedo();
  
  int		WSPHandleRuleCloseParenthesis( long pos);
  int		WSPHandleJSFunctionCloseParenthesis( long pos);
  int		WSPHandleVBSFunctionCloseParenthesis( long pos);
   int		WSPHandleVBSFUNCTIONCloseParenthesis( long pos);
  int		WSPHandleFunctionCloseParenthesis( long pos);
  int		WSPHandleFunctionCloseParenthesisEdit( long pos, LPSTR szType, int typelen);
  int		WSPHandleVariableSemiColon( long pos);
  int		WSPHandleVariableSemiColonEdit( long pos, LPSTR szType, int typelen);
  int		WSPHandleClassOpenBrace( long pos);	
  int		WSPHandleQueryEqual( long pos);	

  void		WSPHandleEditClassKeyWord( long pos);
   void		WSPHandleEditQueryKeyWord( long pos);
  void		WSPHandleEditRuleKeyWord( long pos);
  void      WSPHandleEditJSFunctionKeyWord( long pos);
  void      WSPHandleEditVBSFunctionKeyWord( long pos);
  void      WSPHandleEditVBSFUNCTIONKeyWord( long pos);
  void		WSPHandleFunctionEditIntKeyWord(long pos);
  void		WSPHandleFunctionEditLongKeyWord(long pos);
  void		WSPHandleFunctionEditFloatKeyWord(long pos);
  void		WSPHandleFunctionEditShortKeyWord(long pos);
  void		WSPHandleFunctionEditCharKeyWord( long pos);
  void		WSPHandleFunctionEditVoidKeyWord( long pos);
  void		WSPHandleFunctionEditDoubleKeyWord( long pos);

  void		WSPHandleVariableEditIntKeyWord(long pos);
  void		WSPHandleVariableEditLongKeyWord(long pos);
  void		WSPHandleVariableEditFloatKeyWord(long pos);
  void		WSPHandleVariableEditShortKeyWord(long pos);
  void		WSPHandleVariableEditCharKeyWord( long pos);
  void		WSPHandleVariableEditDoubleKeyWord( long pos);
  
  
  void		WSPCommentRule( long pos);
  void		WSPCommentClass( long pos);
  void		WSPCommentQuery( long pos);
  void		WSPCommentJSFunction( long pos);
  void		WSPCommentVBSFunction( long pos);
  void		WSPCommentVBSFUNCTION( long pos);
  void		WSPCommentFunction( long pos, LPSTR szType, int typelen);
  void		WSPCommentVariable( long pos, LPSTR szType, int typelen);
    
  void		WSPDeleteSelectedRules(long nStartSel, long nEndSel, bool commentFlag);
  void		WSPDeleteSelectedJSFunctions(long nStartSel, long nEndSel, bool commentFlag);
  void		WSPDeleteSelectedVBSFunctions(long nStartSel, long nEndSel, bool commentFlag);
  void		WSPDeleteSelectedVBSFUNCTIONS(long nStartSel, long nEndSel, bool commentFlag);
  void		WSPDeleteSelectedFunctions(long nStartSel, long nEndSel, LPSTR szType, int typelen, bool commentFlag);
  void		WSPDeleteSelectedVariables(long nStartSel, long nEndSel, LPSTR szType, int typelen, bool commentFlag);
  void		WSPAddSelectedRules(long nStartSel, long nEndSel, bool commentFlag);
  void		WSPAddSelectedJSFunctions(long nStartSel, long nEndSel, bool commentFlag);
  void		WSPAddSelectedVBSFunctions(long nStartSel, long nEndSel, bool commentFlag);
  void		WSPAddSelectedVBSFUNCTIONS(long nStartSel, long nEndSel, bool commentFlag);
  void		WSPAddSelectedFunctions( long nStartSel, long nEndSel, LPSTR szType, int typelen, bool commentFlag);
  void		WSPAddSelectedVariables( long nStartSel, long nEndSel, LPSTR szType, int typelen, bool commentFlag);
  void		WSPAddSelectedClasses( long nStartSel, long nEndSel, bool commentFlag);
  void		WSPDeleteSelectedClasses(long nStartSel, long nEndSel, bool commentFlag);
  void		WSPAddSelectedQueries( long nStartSel, long nEndSel, bool commentFlag);
  void		WSPDeleteSelectedQueries(long nStartSel, long nEndSel, bool commentFlag);

  int		WSPMatchToken(int token);
  int		WSPGetToken();
  int		WSPDetectIdentifierType ( long pos);
  
  long		WSPDetectKeyWord3( long pos, int l1, int l2, int l3);	 
  long		WSPDetectKeyWord4( long pos, int l1, int l2, int l3, int l4);
  long		WSPDetectKeyWord5( long pos, int l1, int l2, int l3, int l4, int l5);
  long		WSPDetectKeyWord6( long pos, int l1, int l2, int l3, int l4, int l5, int l6);
  long		WSPDetectKeyWord7( long pos, int l1, int l2, int l3, int l4, int l5, int l6, int l7);
  long		WSPDetectKeyWord8( long pos, int l1, int l2, int l3, int l4, int l5, int l6, int l7, int l8);
  long		WSPDetectKeyWord9( long pos, int l1, int l2, int l3, int l4, int l5, int l6, int l7, int l8, int l9);
  
  long		WSPDetectKeyWordEdit3( long pos, int l1, int l2, int l3);
  long		WSPDetectKeyWordEdit4( long pos, int l1, int l2, int l3, int l4);
  long		WSPDetectKeyWordEdit5( long pos, int l1, int l2, int l3, int l4, int l5);
  long		WSPDetectKeyWordEdit6( long pos, int l1, int l2, int l3, int l4, int l5, int l6);
  long		WSPDetectKeyWordEdit7( long pos, int l1, int l2, int l3, int l4, int l5, int l6, int l7);
  long		WSPDetectKeyWordEdit8( long pos, int l1, int l2, int l3, int l4, int l5, int l6, int l7, int l8);
  long		WSPDetectKeyWordEdit9( long pos, int l1, int l2, int l3, int l4, int l5, int l6, int l7, int l8, int l9);
  
  long		WSPDetectRuleKeyWord( long pos);
  long		WSPDetectRuleKeyWordEdit( long pos);

  long		WSPDetectOpenComment( long pos );
  long		WSPDetectCloseComment(long pos);
  long		WSPDetectLineComment( long pos);
   
  int		WSPParseJSFunction( long nStartSel, long nEndSel);
  int		WSPParseJSFunctionEdit(long nStartSel, long nEndSel);
  int		WSPParseVBSFunction( long nStartSel, long nEndSel);
  int		WSPParseVBSFunctionEdit(long nStartSel, long nEndSel);

  int		WSPParseFunction(long nStartSel, long nEndSel);
  int		WSPParseFunctionEdit(long nStartSel, long nEndSel, int type, int typelen);
  int		WSPParseRule(long nStartSel, long nEndSel);	
  int		WSPParseClass( long nStartSel, long EndSel);
  int		WSPParseClassEdit( long nStartSel, long EndSel);
  int		WSPParseQuery( long nStartSel, long EndSel);
  int		WSPParseQueryEdit( long nStartSel, long EndSel);
  int		WSPParseRuleEdit( long nStartSel, long nEndSel);
  int		WSPParseVariable(long nStartSel, long nEndSel);
  int		WSPParseVariableEdit(long nStartSel, long nEndSel, int type, int typelen);	
  
  BOOL		WSPCheckLineComment(long posToken, long posEnd);
  BOOL		WSPCheckBlockComment(long posStart, long posEnd, long posToken);
  
  void		WSPPaste();
  void		WSPDelete();
  void		WSPModified();
  long		WSPSearchToken(long posStart, long posEnd, LPSTR szToken);
  long		WSPSearchNearestIdType( long nStartSel, long nEndSel);
  int		WSPAddNodeTree1(CString sName, CString sParam, int image);
  int		WSPAddNodeTypeTree1(CString sName, CString sParam, int image, int type);
  int		WSPDeleteNodeTree1(CString sName);
  int		WSPAddRule(long pos, bool commentFlag);
  int		WSPDeleteRule(long pos, bool commentFlag);
  int		WSPAddClass( long pos, bool commentFlag);
  int		WSPDeleteClass( long pos, bool commentFlag);
  int		WSPAddQuery( long pos, bool commentFlag);
  int		WSPDeleteQuery( long pos, bool commentFlag);
  int		WSPAddFunction( long pos, bool commentFlag);
  int		WSPDeleteFunction( long pos, bool commentFlag);
  int		WSPAddJSFunction( long pos, bool commentFlag);	
  int		WSPDeleteJSFunction( long pos, bool commentFlag);
  int		WSPAddVBSFunction( long pos, bool commentFlag);	
  int		WSPDeleteVBSFunction( long pos, bool commentFlag);
  int		WSPAddVBSFUNCTION( long pos, bool commentFlag);
  int		WSPDeleteVBSFUNCTION( long pos, bool commentFlag);
  int		WSPAddVariable( long pos, bool commentFlag);
  int		WSPDeleteVariable( long pos, bool commentFlag);
  int		WSPGetIdentifierLength( int idType);
  int		WSPCountFunctParameters(long posOpenParenthesis, long posCloseParenthesis);

  LPSTR		WSPGetIdentifierType( int idType);
  CString 	WSPGetText(long posStart, long posEnd);
  CString   WSPFormatRuleName(CString name); 
  CString   WSPFormatRuleNameOpt(CString name);
  CString	WSPFormatParameters( long posOpenParenthesis, long posCloseParenthesis);
  
  


  
 // Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAIPIEditorView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
		//virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	
	//virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	//virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	
	
	
	//}}AFX_VIRTUAL
	

// Implementation
public:
	virtual ~CAIPIEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	//Workspace notification functions

protected:
	virtual void OnModified(SCNotification* pSCNotification);
	virtual void OnKey(SCNotification* pSCNotification);
	virtual void OnUpdateUI(SCNotification* pSCNotification);
	virtual void OnSavePointLeft( SCNotification* pSCNotification);	
	virtual void OnCharAdded(SCNotification* pSCNotification);
	virtual void OnDwellStart(SCNotification* pSCNotification);
    virtual void OnDwellEnd(SCNotification* pSCNotification);
    virtual void OnModifyAttemptRO(SCNotification* pSCNotification);
	
	
	
	void UpdateSkinMenus();
	void StopTimer( CPerfTimer t, CString msg);
	
	
public:
	void OnOpenDocument(LPCTSTR path_name);


// Generated message map functions
protected:
	//{{AFX_MSG(CAIPIEditorView)
	afx_msg void OnOptionsViewLineNumbers();
	afx_msg void OnOptionsSelectionMargin();
	afx_msg void OnOptionsFoldMargin();
	afx_msg void OnOptionsAddMarker();
	afx_msg void OnOptionsDeleteMarker();
	afx_msg void OnOptionsFindNextMarker();
	afx_msg void OnOptionsFindPrevMarker();
	afx_msg void OnUpdateOptionsViewLineNumbers(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOptionsSelectionMargin(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOptionsFoldMargin(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOptionsAddMarker(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOptionsDeleteMarker(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStyle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFold(CCmdUI* pCmdUI);
	afx_msg void OnUpdateInsert(CCmdUI* pCmdUI);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnBuildView();
	afx_msg void OnEditFindInFiles();
	afx_msg void OnUpdateEditFindInFiles(CCmdUI* pCmdUI);
	afx_msg void OnEditFindExt  (    );
	afx_msg void OnUpdateEditFindExt(CCmdUI* pCmdUI);
	afx_msg void OnEditFindinFilesStop();
	afx_msg void OnUpdateEditFindinFilesStop(CCmdUI* pCmdUI);
	afx_msg void OnTest();
	afx_msg void OnSettingsSkinClassic();
	afx_msg void OnSettingsSkinOfficeXP();
	afx_msg void OnSettingsSkinOffice2003();
	afx_msg void OnFilePageSetup();
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnEditRedo();
	afx_msg void OnUpdateEditRedo(CCmdUI* pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnOptionsViewWhitespace();
	afx_msg void OnOptionsViewLineEnd();
	afx_msg void OnUpdateOptionsViewWhitespace(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOptionsViewLineEnd(CCmdUI* pCmdUI);
	afx_msg void OnOptionsViewIndentLine();
	afx_msg void OnUpdateOptionsViewIndentLine(CCmdUI* pCmdUI);
	afx_msg void OnViewZoom();
	afx_msg void OnOptionsAutoindent();
	afx_msg void OnUpdateOptionsAutoindent(CCmdUI* pCmdUI);
	afx_msg void OnOptionsDeleteAllMarkers();
	afx_msg void OnUpdateOptionsDeleteAllMarkers(CCmdUI* pCmdUI);
	afx_msg void OnOptionsCommentBlock();
	afx_msg void OnOptionsCommentLine();
	afx_msg void OnOptionsUncomment();
	afx_msg void OnViewZoomIn();
	afx_msg void OnViewZoomOut();
	afx_msg void OnAppExit();
	afx_msg void OnEditClear();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEditGoto();
	afx_msg void OnOptionsAutocomplete();
	afx_msg void OnUpdateOptionsAutocomplete(CCmdUI* pCmdUI);
	afx_msg void OnOptionsUppercase();
	afx_msg void OnOptionLowercase();
	afx_msg void OnBuildCurrentFile();
	afx_msg void OnUpdateBuildCurrentFile(CCmdUI* pCmdUI);
	afx_msg void OnBuildProject();
	afx_msg void OnUpdateBuildProject(CCmdUI* pCmdUI);
	afx_msg void OnBuildInsertBreakpoint();
	afx_msg void OnUpdateBuildInsertBreakpoint(CCmdUI* pCmdUI);
	afx_msg void OnBuildClearBreakpoints();
	afx_msg void OnUpdateBuildClearBreakpoints(CCmdUI* pCmdUI);
	afx_msg void OnOptionsModifiedNotfication();
	afx_msg void OnUpdateOptionsModifiedNotfication(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in AIPIEditorView.cpp
inline CAIPIEditorDoc* CAIPIEditorView::GetDocument()
   { return (CAIPIEditorDoc*)m_pDocument; }
#endif


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AIPIEDITORVIEW_H__FD49D6D2_197B_479F_9167_1708ECA57C0F__INCLUDED_)
