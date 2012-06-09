// AIPIEditorView.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "AIPIEditorDoc.h"
#include "AIPIEditorView.h"
#include "WorkspaceTabView.h"
#include "WorkspaceTabDoc.h"
#include "FindInFilesDlg.h"
#include "FindInFilesExtDlg.h"
#include "FileFinder.h"
#include "GoToDlg.h"
#include "ZoomViewDlg.h"



#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CAIPIEditorView
const TCHAR AIPIKeyWords[] = 
  _T("and AND and_eq answer ANSWER ask ASK asm auto bitand bitor bool break ")
  _T("case CASE catch char CHAR cin CIN class CLASS compl const CONST const_cast continue CONTINUE cout COUT ")
  _T("default delete DELETE do DO double DOUBLE dynamic_cast else ELSE enum explicit export extern false FALSE float FLOAT for FOR ")
  _T("friend goto GOTO if IF image IMAGE inline int INT long LONG mutable namespace new not NOT not_eq ")
  _T("operator or OR or_eq private protected public ")
  _T("register reinterpret_cast return rule RULE short SHORT signed sizeof static static_cast string STRING struct switch SWITCH")
  _T("template then THEN this throw true TRUE try typedef typeid typename union unsigned using ")
  _T("virtual void volatile wchar_t while WHILE xor xor_eq ");

/////////////////////////////////////////////////////////////////////////////
// CAIPIEditorView

IMPLEMENT_DYNCREATE(CAIPIEditorView, CScintillaView)

CAIPIEditorView::CAIPIEditorView()
{
	
	g_fcurrentPos = 0;
	g_currentPos = 0;
	
	m_nCol = 0;
	m_nPasteLength = 0;
	//nRuleSyntaxError = 0;
	

	g_bNotificationModified = false;

	m_bFindInFiles = true;
		
	m_bFlagPaste = false;
	
	m_bFlagWriteRule = false;
	m_bFlagWriteFunction = false;
	m_bFlagWriteJSFunction = false;
	m_bFlagWriteVBSFunction = false;
	m_bFlagWriteVBSFUNCTION = false;
	m_bFlagWriteVariable = false;
	m_bFlagWriteClass = false;
	m_bFlagWriteQuery = false;
	m_bFlagWriteError = false;

	m_bFlagEditClass = false;
	m_bFlagEditRule = false;
	m_bFlagEditFunction = false;
	m_bFlagEditJSFunction = false;
	m_bFlagEditVBSFunction = false;
	m_bFlagEditVBSFUNCTION = false;
	m_bFlagEditQuery = false;
	
	
	m_bRuleCloseParenthesis = false;
	m_bFunctionCloseParenthesis = false;
	m_bJSFunctionCloseParenthesis = false;
	m_bVBSFunctionCloseParenthesis = false;
	m_bVBSFUNCTIONCloseParenthesis = false;
	m_bVariableSemiColon = false;
	m_bClassOpenBrace = false;
	m_bQueryEqual = false;
	
	m_bFlagBeforeInsert = false;
	m_bFlagBeforeInsert = false;
	m_bFlagInsertText = false;
	m_bFlagDeleteText = false;
	m_bFlagUndoInsert = false;
	m_bFlagRedoInsert = false;

	

	
	m_DocumentLength = 0;
	m_StartLimit = 0;
	m_iModificationType = 0;
	m_lookahead = UNDEFINE;

}

CAIPIEditorView::~CAIPIEditorView()
{
}


BEGIN_MESSAGE_MAP(CAIPIEditorView, CScintillaView)
	//{{AFX_MSG_MAP(CAIPIEditorView)
	ON_COMMAND(ID_OPTIONS_VIEW_LINENUMBERS, OnOptionsViewLineNumbers)
	ON_COMMAND(ID_OPTIONS_SELECTION_MARGIN, OnOptionsSelectionMargin)
	ON_COMMAND(ID_OPTIONS_FOLD_MARGIN, OnOptionsFoldMargin)
	ON_COMMAND(ID_OPTIONS_ADDMARKER, OnOptionsAddMarker)
	ON_COMMAND(ID_OPTIONS_DELETEMARKER, OnOptionsDeleteMarker)
	ON_COMMAND(ID_OPTIONS_FIND_NEXTMARKER, OnOptionsFindNextMarker)
	ON_COMMAND(ID_OPTIONS_FIND_PREVMARKER, OnOptionsFindPrevMarker)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_VIEW_LINENUMBERS, OnUpdateOptionsViewLineNumbers)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_SELECTION_MARGIN, OnUpdateOptionsSelectionMargin)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_FOLD_MARGIN, OnUpdateOptionsFoldMargin)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_ADDMARKER, OnUpdateOptionsAddMarker)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_DELETEMARKER, OnUpdateOptionsDeleteMarker)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_LINE, OnUpdateLine) 
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_STYLE, OnUpdateStyle) 
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_FOLD, OnUpdateFold) 
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_OVR, OnUpdateInsert)
	ON_WM_ACTIVATE()
	ON_COMMAND(ID_BUILD, OnBuildView)
	ON_COMMAND(ID_EDIT_FINDINFILES, OnEditFindInFiles)
	ON_UPDATE_COMMAND_UI(ID_EDIT_FINDINFILES, OnUpdateEditFindInFiles)
	ON_COMMAND(ID_EDIT_FIND_EXT, OnEditFindExt)
	ON_UPDATE_COMMAND_UI(ID_EDIT_FIND_EXT, OnUpdateEditFindExt)
	ON_COMMAND(ID_EDIT_FINDINFILES_STOP, OnEditFindinFilesStop)
	ON_UPDATE_COMMAND_UI(ID_EDIT_FINDINFILES_STOP, OnUpdateEditFindinFilesStop)
	ON_COMMAND(ID_TEST, OnTest)
	ON_COMMAND(ID_SETTINGS_SKIN_CLASSIC, OnSettingsSkinClassic)
	ON_COMMAND(ID_SETTINGS_SKIN_OFFICEXP, OnSettingsSkinOfficeXP)
	ON_COMMAND(ID_SETTINGS_SKIN_OFFICE2003, OnSettingsSkinOffice2003)
	ON_COMMAND(ID_FILE_PAGE_SETUP, OnFilePageSetup)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_COMMAND(ID_EDIT_REDO, OnEditRedo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, OnUpdateEditRedo)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_OPTIONS_VIEW_WHITESPACE, OnOptionsViewWhitespace)
	ON_COMMAND(ID_OPTIONS_VIEW_LINEEND, OnOptionsViewLineEnd)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_VIEW_WHITESPACE, OnUpdateOptionsViewWhitespace)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_VIEW_LINEEND, OnUpdateOptionsViewLineEnd)
	ON_COMMAND(ID_OPTIONS_VIEW_INDENTLINE, OnOptionsViewIndentLine)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_VIEW_INDENTLINE, OnUpdateOptionsViewIndentLine)
	ON_COMMAND(ID_VIEW_ZOOM, OnViewZoom)
	ON_COMMAND(ID_OPTIONS_AUTOINDENT, OnOptionsAutoindent)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_AUTOINDENT, OnUpdateOptionsAutoindent)
	ON_COMMAND(ID_OPTIONS_DELETEALLMARKERS, OnOptionsDeleteAllMarkers)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_DELETEALLMARKERS, OnUpdateOptionsDeleteAllMarkers)
	ON_COMMAND(ID_OPTIONS_COMMENTBLOCK, OnOptionsCommentBlock)
	ON_COMMAND(ID_OPTIONS_COMMENTLINE, OnOptionsCommentLine)
	ON_COMMAND(ID_OPTIONS_UNCOMMENT, OnOptionsUncomment)
	ON_COMMAND(ID_VIEW_ZOOM_IN, OnViewZoomIn)
	ON_COMMAND(ID_VIEW_ZOOM_OUT, OnViewZoomOut)
	ON_COMMAND(ID_APP_EXIT, OnAppExit)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EDIT_GOTO, OnEditGoto)
	ON_COMMAND(ID_OPTIONS_AUTOCOMPLETE, OnOptionsAutocomplete)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_AUTOCOMPLETE, OnUpdateOptionsAutocomplete)
	ON_COMMAND(ID_OPTIONS_UPPERCASE, OnOptionsUppercase)
	ON_COMMAND(ID_OPTION_LOWERCASE, OnOptionLowercase)
	ON_COMMAND(ID_BUILD_CURRENT_FILE, OnBuildCurrentFile)
	ON_UPDATE_COMMAND_UI(ID_BUILD_CURRENT_FILE, OnUpdateBuildCurrentFile)
	ON_COMMAND(ID_BUILD_PROJECT, OnBuildProject)
	ON_UPDATE_COMMAND_UI(ID_BUILD_PROJECT, OnUpdateBuildProject)
	ON_COMMAND(ID_BUILD_INSERT_BREAKPOINT, OnBuildInsertBreakpoint)
	ON_UPDATE_COMMAND_UI(ID_BUILD_INSERT_BREAKPOINT, OnUpdateBuildInsertBreakpoint)
	ON_COMMAND(ID_BUILD_CLEAR_BREAKPOINTS, OnBuildClearBreakpoints)
	ON_UPDATE_COMMAND_UI(ID_BUILD_CLEAR_BREAKPOINTS, OnUpdateBuildClearBreakpoints)
	ON_COMMAND(ID_OPTIONS_MODIFIED_NOTFICATION, OnOptionsModifiedNotfication)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_MODIFIED_NOTFICATION, OnUpdateOptionsModifiedNotfication)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAIPIEditorView drawing



void CAIPIEditorView::OnDraw(CDC* pDC)
{
	CAIPIEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}



/////////////////////////////////////////////////////////////////////////////
// CAIPIEditorView printing
/*
BOOL CAIPIEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CAIPIEditorView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add extra initialization before printing
}

void CAIPIEditorView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add cleanup after printing
}
*/
/////////////////////////////////////////////////////////////////////////////
// CAIPIEditorView diagnostics

#ifdef _DEBUG
void CAIPIEditorView::AssertValid() const
{
	CScintillaView::AssertValid();
}

void CAIPIEditorView::Dump(CDumpContext& dc) const
{
	CScintillaView::Dump(dc);
}

CAIPIEditorDoc* CAIPIEditorView::GetDocument() // non-debug version is inline
{
	
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAIPIEditorDoc)));
	return static_cast<CAIPIEditorDoc*>(m_pDocument);
	
	/*
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAIPIEditorDoc)));
	return (CAIPIEditorDoc*)m_pDocument;
	*/
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAIPIEditorView message handlers
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////
/// Scintilla Editor options ////
/////////////////////////////////////////////////////////////////////////////////////////
void CAIPIEditorView::SetAStyle(int style, COLORREF fore, COLORREF back, int size, const char* face) 
{
  CScintillaCtrl& rCtrl = GetCtrl();

	rCtrl.StyleSetFore(style, fore);
	rCtrl.StyleSetBack(style, back);
	if (size >= 1)
		rCtrl.StyleSetSize(style, size);
	if (face) 
		rCtrl.StyleSetFont(style, face);
}

void CAIPIEditorView::DefineMarker(int marker, int markerType, COLORREF fore, COLORREF back) 
{
  CScintillaCtrl& rCtrl = GetCtrl();

	rCtrl.MarkerDefine(marker, markerType);
	rCtrl.MarkerSetFore(marker, fore);
	rCtrl.MarkerSetBack(marker, back);
}


void CAIPIEditorView::OnInitialUpdate() 
{
	/*
	COXBitmapMenu menu;
	menu.LoadMenu(IDR_SCINTITYPE);
	CMenu* pMenu = menu.GetSubMenu(1);
	pMenu->RemoveMenu(14, MF_BYPOSITION);
	*/
	
	CAipi_Init ini;
	ini.Initialize();


	CScintillaView::OnInitialUpdate();
	m_bViewWS = false;
	m_bIndentationWSVisible = true;
	m_bViewEOL = false;
	m_bViewIndent = false;
	m_bAutoIndent = true;
	m_bAutoComplete = true;
	m_nMarkers = 0;
	m_nBreakpoints = 0;
	
	
	
  CScintillaCtrl& rCtrl = GetCtrl();

  //Setup the Lexer
  rCtrl.SetLexer(SCLEX_AIPI);
  rCtrl.SetKeyWords(0, AIPIKeyWords);
  
  //rCtrl.ClearDocumentStyle(0);
  

  //Setup styles
  
  SetAStyle(STYLE_DEFAULT, RGB(0, 0, 0), RGB(0xff, 0xff, 0xff), 11, "Verdana");
  SetAStyle(STYLE_LINENUMBER, RGB(0, 255, 255), RGB(0xff , 0xffff, 0xffff), 11, "Arial");
  
  
  rCtrl.StyleClearAll();
  SetAStyle(SCE_AIPI_DEFAULT, RGB(0, 0, 0));
  SetAStyle(SCE_AIPI_COMMENT, RGB(0, 0x80, 0));
  SetAStyle(SCE_AIPI_COMMENTLINE, RGB(0, 0x80, 0));
  SetAStyle(SCE_AIPI_COMMENTDOC, RGB(0, 0x80, 0));
  SetAStyle(SCE_AIPI_COMMENTLINEDOC, RGB(0, 0x80, 0));
  SetAStyle(SCE_AIPI_COMMENTDOCKEYWORD, RGB(0, 0x80, 0));
  SetAStyle(SCE_AIPI_COMMENTDOCKEYWORDERROR, RGB(0, 0x80, 0));
  SetAStyle(SCE_AIPI_NUMBER, RGB(0xff, 0, 0));
  SetAStyle(SCE_AIPI_WORD, RGB(0, 0, 0x80));
  
  rCtrl.StyleSetBold(SCE_AIPI_WORD, 1);
  //set the backgroundcolor of brace highlights
  rCtrl.StyleSetBack(STYLE_BRACELIGHT, RGB(230, 240, 255));
  //Braces light
  rCtrl.SetStyleBits(7);

  //Setup Calltips
  rCtrl.CallTipSetFore(RGB(0, 0, 0));
  rCtrl.CallTipSetBack(RGB(255, 255, 225));
  //rCtrl.CallTipUseStyle(STYLE_CALLTIP);
  
      
  
  SetAStyle(SCE_AIPI_STRING, RGB(128, 0, 0));
  SetAStyle(SCE_AIPI_CHARACTER, RGB(0, 120, 255));
  SetAStyle(SCE_AIPI_VAR, RGB(153, 102, 51));
 
  
  SetAStyle(SCE_AIPI_PROP, RGB(108, 108, 108));
  SetAStyle(SCE_AIPI_IDENTIFIER, RGB(0, 0, 0));
  SetAStyle(SCE_AIPI_PREPROCESSOR, RGB(0x80, 0x80, 0));
  SetAStyle(SCE_AIPI_OPERATOR, RGB(0, 0, 255));

  //Setup folding
  rCtrl.SetMarginWidthN(2, 16);
  rCtrl.SetMarginSensitiveN(2, TRUE);
  rCtrl.SetMarginTypeN(2, SC_MARGIN_SYMBOL);
  rCtrl.SetMarginMaskN(2, SC_MASK_FOLDERS);
  rCtrl.SetProperty(_T("fold"), _T("1"));

 

  

  //Setup markers
	DefineMarker(SC_MARKNUM_FOLDEROPEN, SC_MARK_MINUS, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0xFF));
	DefineMarker(SC_MARKNUM_FOLDER, SC_MARK_PLUS, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));
	DefineMarker(SC_MARKNUM_FOLDERSUB, SC_MARK_EMPTY, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));
	DefineMarker(SC_MARKNUM_FOLDERTAIL, SC_MARK_EMPTY, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));
	DefineMarker(SC_MARKNUM_FOLDEREND, SC_MARK_EMPTY, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));
	DefineMarker(SC_MARKNUM_FOLDEROPENMID, SC_MARK_EMPTY, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));
	DefineMarker(SC_MARKNUM_FOLDERMIDTAIL, SC_MARK_EMPTY, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));

	//Set folding flags
 	rCtrl.SetFoldFlags(16, 0);
	//Allow notifications for folding actions
   rCtrl.SetModEventMask(SC_MOD_BEFOREINSERT|SC_MOD_INSERTTEXT |SC_MOD_BEFOREDELETE| SC_MOD_DELETETEXT | SC_PERFORMED_UNDO 
	   |SC_PERFORMED_REDO| SC_LASTSTEPINUNDOREDO |SC_MULTISTEPUNDOREDO| SC_MULTILINEUNDOREDO , 0);


  //Setup auto completion
  rCtrl.AutoCSetSeparator(10); //Use a separator of line feed

  //Setup call tips
  rCtrl.SetMouseDwellTime(1000);	

  //Set indentation lines	
  rCtrl.SetIndentationGuides(m_bViewIndent, 0);

  //Set highlightbraces
  rCtrl.SetHighlightGuide(0, 0);
  
  // Set tabwidth to 8
  rCtrl.SetTabWidth(8, 0);
  // Set indention to 8
  rCtrl.SetIndent(8, 0);

  // Set the caret blinking time to 400 milliseconds
  rCtrl.SetCaretPeriod(400, 0);	

  //Set line ending mode to CRLF
  //This mode saves the file without strange symbols in the line endings
  //The Aipi file Lexer just support this format
  rCtrl.SetEOLMode(0);
 
  //Set zooming capabilities
  rCtrl.SetZoom(0, 0);

  //Turn off the WM_CONTEXTMENU message default by Scintilla
  rCtrl.UsePopUp(0);

  
	

  

//Hide CommandDlgBar
  CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		
   if (pMainFrame->m_wndCommandDlgBar.IsVisible())
		pMainFrame->ShowControlBar(&(pMainFrame->m_wndCommandDlgBar), FALSE, FALSE);
	
   UpdateSkinMenus();
   FillAutoCompleteAIPIKeyWords();
   FillAutoCompleteJSCriptKeyWords();
	

  
#ifdef _DEBUG
  AfxDump(this);
#endif

#ifdef UNICODE_DEBUG
  AfxDump(this);
#endif
	
}


void CAIPIEditorView::OnOptionsAutoindent() 
{
	m_bAutoIndent = !m_bAutoIndent;
	
}




void CAIPIEditorView::OnOptionsAutocomplete() 
{
	
	m_bAutoComplete = !m_bAutoComplete;
}

void CAIPIEditorView::OnOptionsModifiedNotfication() 
{
	
	g_bNotificationModified = !g_bNotificationModified;	
}




void CAIPIEditorView::OnOptionsViewLineNumbers() 
{
	CScintillaCtrl& rCtrl = GetCtrl();
	int nMarginWidth = rCtrl.GetMarginWidthN(0);
	int iLastLine = rCtrl.GetLineCount();
  
	if (nMarginWidth)
	{
		rCtrl.SetMarginWidthN(0, 0);
	}
    else
	{		  
		if(iLastLine <= 1000 )
			rCtrl.SetMarginWidthN(0, 32);
		if(iLastLine > 1000 && iLastLine <= 1000000)
			rCtrl.SetMarginWidthN(0, 64);
		if(iLastLine > 1000000 && iLastLine <= 1000000000)
			rCtrl.SetMarginWidthN(0, 96);

	}
}


void CAIPIEditorView::OnOptionsViewWhitespace() 
{
	CScintillaCtrl& rCtrl = GetCtrl();
	m_bViewWS = !m_bViewWS;	

	if (m_bViewWS && m_bIndentationWSVisible)
		rCtrl.SetViewWS(SCWS_VISIBLEALWAYS, 0);
	else if (m_bViewWS)
		rCtrl.SetViewWS(SCWS_VISIBLEAFTERINDENT, 0);
	else
		rCtrl.SetViewWS(SCWS_INVISIBLE, 0);
}

void CAIPIEditorView::OnOptionsViewLineEnd() 
{
	CScintillaCtrl& rCtrl = GetCtrl();
	m_bViewEOL = !m_bViewEOL;	


	rCtrl.SetViewEOL(m_bViewEOL, 0);
	
}


void CAIPIEditorView::OnOptionsViewIndentLine() 
{
	CScintillaCtrl& rCtrl = GetCtrl();
	m_bViewIndent = !m_bViewIndent;	

  rCtrl.SetIndentationGuides(m_bViewIndent, 0);
}

void CAIPIEditorView::OnOptionsSelectionMargin() 
{
	CScintillaCtrl& rCtrl = GetCtrl();
	int nMarginWidth = rCtrl.GetMarginWidthN(1);
	if (nMarginWidth)
		rCtrl.SetMarginWidthN(1, 0);
	else
		rCtrl.SetMarginWidthN(1, 16);	
}


void CAIPIEditorView::OnOptionsFoldMargin() 
{
	CScintillaCtrl& rCtrl = GetCtrl();
	int nMarginWidth = rCtrl.GetMarginWidthN(2);
  if (nMarginWidth)
    rCtrl.SetMarginWidthN(2, 0);
  else
	  rCtrl.SetMarginWidthN(2, 16);
  
  
}


void CAIPIEditorView::OnOptionsUppercase() 
{
	
	CScintillaCtrl& rCtrl = GetCtrl();
	rCtrl.UpperCase();

}

void CAIPIEditorView::OnOptionLowercase() 
{
	
	CScintillaCtrl& rCtrl = GetCtrl();
	rCtrl.LowerCase();
	
}

void CAIPIEditorView::OnOptionsCommentBlock() 
{
	CScintillaCtrl& rCtrl = GetCtrl();
	
	long nStartSel = rCtrl.GetSelectionStart();
	long nEndSel = rCtrl.GetSelectionEnd();
	if (nStartSel != nEndSel )
	{
		long posStart = nStartSel;
		long posEnd = nEndSel + 3;
		
		rCtrl.InsertText(posStart, _T("/* "));
		rCtrl.InsertText(posEnd, _T(" */"));
		
	}

	WSPCommentRule( nStartSel + 1);
	WSPCommentClass( nStartSel + 1);


	LPSTR szTypeInt = "int";
	WSPCommentFunction( nStartSel + 1, szTypeInt, 3);
	WSPCommentVariable( nStartSel + 1, szTypeInt, 3);

	LPSTR szTypeLong = "long";
	WSPCommentFunction( nStartSel + 1, szTypeLong, 4);
	WSPCommentVariable( nStartSel + 1, szTypeLong, 4);

	LPSTR szTypeChar = "char";
	WSPCommentFunction( nStartSel + 1, szTypeChar, 4);
	WSPCommentVariable( nStartSel + 1, szTypeChar, 4);

	LPSTR szTypeShort = "short";
	WSPCommentFunction( nStartSel + 1, szTypeShort, 5);
	WSPCommentVariable( nStartSel + 1, szTypeShort, 5);

	LPSTR szTypeFloat = "float";
	WSPCommentFunction( nStartSel + 1, szTypeFloat, 5);
	WSPCommentVariable( nStartSel + 1, szTypeFloat, 5);

	LPSTR szTypeDouble = "double";
	WSPCommentFunction( nStartSel + 1, szTypeDouble, 6);
	WSPCommentVariable( nStartSel + 1, szTypeDouble, 6);

	LPSTR szTypeVoid = "void";
	WSPCommentFunction( nStartSel + 1, szTypeVoid, 4);
	


}


void CAIPIEditorView::OnOptionsCommentLine() 
{
	CScintillaCtrl& rCtrl = GetCtrl();
	
	long nStartSel = rCtrl.GetSelectionStart();
	long nEndSel = rCtrl.GetSelectionEnd();
	if (nStartSel != nEndSel )
	{	
		int lineStart = rCtrl.LineFromPosition(nStartSel);
		int lineEnd = rCtrl.LineFromPosition(nEndSel);

		if( lineStart < lineEnd )
		{
			int nLines = lineEnd - lineStart;
			for( int i = 0; i<=nLines; ++i)
			{
				int nLine = lineStart + i;
				long nPos = rCtrl.PositionFromLine(nLine);
				rCtrl.InsertText(nPos, _T("// "));
			}

		}
		else
		{
			rCtrl.InsertText(nStartSel, _T("// "));
		}
	}

	WSPCommentRule( nStartSel + 1);
	WSPCommentClass( nStartSel + 1);


	LPSTR szTypeInt = "int";
	WSPCommentFunction( nStartSel + 1, szTypeInt, 3);
	WSPCommentVariable( nStartSel + 1, szTypeInt, 3);

	LPSTR szTypeLong = "long";
	WSPCommentFunction( nStartSel + 1, szTypeLong, 4);
	WSPCommentVariable( nStartSel + 1, szTypeLong, 4);

	LPSTR szTypeChar = "char";
	WSPCommentFunction( nStartSel + 1, szTypeChar, 4);
	WSPCommentVariable( nStartSel + 1, szTypeChar, 4);

	LPSTR szTypeShort = "short";
	WSPCommentFunction( nStartSel + 1, szTypeShort, 5);
	WSPCommentVariable( nStartSel + 1, szTypeShort, 5);

	LPSTR szTypeFloat = "float";
	WSPCommentFunction( nStartSel + 1, szTypeFloat, 5);
	WSPCommentVariable( nStartSel + 1, szTypeFloat, 5);

	LPSTR szTypeDouble = "double";
	WSPCommentFunction( nStartSel + 1, szTypeDouble, 6);
	WSPCommentVariable( nStartSel + 1, szTypeDouble, 6);

	LPSTR szTypeVoid = "void";
	WSPCommentFunction( nStartSel + 1, szTypeVoid, 4);
	


}

void CAIPIEditorView::OnOptionsUncomment() 
{
	
	CScintillaCtrl& rCtrl = GetCtrl();
	
	LPSTR szOpenComment = "/*";
	LPSTR szCloseComment = "*/";
	LPSTR szLineComment = "//";

	LPSTR szText = " ";
	int pos = NOT_FOUND;

	rCtrl.TargetFromSelection();
	long posStart = rCtrl.GetTargetStart();
	long posEnd = rCtrl.GetTargetEnd();
	
	if( posStart != posEnd )
	{
		
		//Search for open comment symbol and replace with an empty string
		rCtrl.TargetFromSelection();
		posStart = rCtrl.GetTargetStart();
		rCtrl.SetSearchFlags(SCFIND_MATCHCASE);
		while( posStart != NOT_FOUND  )
		{
			posStart = rCtrl.SearchInTarget(strlen(szOpenComment), szOpenComment);
			if( posStart == NOT_FOUND )
				break;
			rCtrl.ReplaceTarget(strlen(szText), szText, 0);
			posStart = posStart + 3;
			rCtrl.SetTargetStart(posStart);
			rCtrl.SetTargetEnd(posEnd);
			

		}
	
		//Search for close comment symbol and replace with an empty string
		rCtrl.TargetFromSelection();
		posStart = rCtrl.GetTargetStart();
		rCtrl.SetSearchFlags(SCFIND_MATCHCASE);
		while( posStart != NOT_FOUND  )
		{
			posStart = rCtrl.SearchInTarget(strlen(szCloseComment), szCloseComment);
			if( posStart == NOT_FOUND )
				break;
			rCtrl.ReplaceTarget(strlen(szText), szText, 0);
			posStart = posStart + 3;
			rCtrl.SetTargetStart(posStart);
			rCtrl.SetTargetEnd(posEnd);
			

		}
	
		//Search for line comment symbol and replace with an empty string
		rCtrl.TargetFromSelection();
		posStart = rCtrl.GetTargetStart();
		rCtrl.SetSearchFlags(SCFIND_MATCHCASE);
				
		while( posStart != NOT_FOUND  )
		{
			posStart = rCtrl.SearchInTarget(strlen(szLineComment), szLineComment);
			if( posStart == NOT_FOUND )
				break;
			rCtrl.ReplaceTarget(strlen(szText), szText, 0);
			posStart = posStart + 3;
			rCtrl.SetTargetStart(posStart);
			rCtrl.SetTargetEnd(posEnd);
			

		}
		
	}


	WSPCommentRule( posStart + 1);
	WSPCommentClass( posStart + 1);


	LPSTR szTypeInt = "int";
	WSPCommentFunction( posStart + 1, szTypeInt, 3);
	WSPCommentVariable( posStart + 1, szTypeInt, 3);

	LPSTR szTypeLong = "long";
	WSPCommentFunction( posStart + 1, szTypeLong, 4);
	WSPCommentVariable( posStart + 1, szTypeLong, 4);

	LPSTR szTypeChar = "char";
	WSPCommentFunction( posStart + 1, szTypeChar, 4);
	WSPCommentVariable( posStart + 1, szTypeChar, 4);

	LPSTR szTypeShort = "short";
	WSPCommentFunction( posStart + 1, szTypeShort, 5);
	WSPCommentVariable( posStart + 1, szTypeShort, 5);

	LPSTR szTypeFloat = "float";
	WSPCommentFunction( posStart + 1, szTypeFloat, 5);
	WSPCommentVariable( posStart + 1, szTypeFloat, 5);

	LPSTR szTypeDouble = "double";
	WSPCommentFunction( posStart + 1, szTypeDouble, 6);
	WSPCommentVariable( posStart + 1, szTypeDouble, 6);

	LPSTR szTypeVoid = "void";
	WSPCommentFunction( posStart + 1, szTypeVoid, 4);

}


void CAIPIEditorView::OnOptionsAddMarker() 
{
	if( m_nBreakpoints > 0 )
	{
		OnBuildClearBreakpoints();
		
	}
	
	CScintillaCtrl& rCtrl = GetCtrl();
  long nPos = rCtrl.GetCurrentPos();
  int nLine = rCtrl.LineFromPosition(nPos);
  
	rCtrl.MarkerDefine(0, SC_MARK_SMALLRECT);
	rCtrl.MarkerSetFore(0, RGB( 80, 0, 0 ));
	rCtrl.MarkerSetBack(0, RGB( 0, 255, 0 ));
	rCtrl.MarkerAdd(nLine, 0);	

	m_nMarkers++;
}




void CAIPIEditorView::OnOptionsDeleteMarker() 
{
	CScintillaCtrl& rCtrl = GetCtrl();
  long nPos = rCtrl.GetCurrentPos();
  int nLine = rCtrl.LineFromPosition(nPos);
  rCtrl.MarkerDelete(nLine, 0);
  
  m_nMarkers--;

}

void CAIPIEditorView::OnOptionsDeleteAllMarkers() 
{
		CScintillaCtrl& rCtrl = GetCtrl();
		rCtrl.MarkerDeleteAll(-1);

		m_nMarkers = 0;
	
}


void CAIPIEditorView::OnOptionsFindNextMarker() 
{
	CScintillaCtrl& rCtrl = GetCtrl();
  long  nPos = rCtrl.GetCurrentPos();
  int nLine = rCtrl.LineFromPosition(nPos);
  int nFoundLine = rCtrl.MarkerNext(nLine + 1, 0x1);
  if (nFoundLine >= 0)
    rCtrl.GotoLine(nFoundLine);
  else
    MessageBeep(MB_ICONHAND);	
}

void CAIPIEditorView::OnOptionsFindPrevMarker() 
{
	CScintillaCtrl& rCtrl = GetCtrl();
  long nPos = rCtrl.GetCurrentPos();
  int nLine = rCtrl.LineFromPosition(nPos);
  int nFoundLine = rCtrl.MarkerPrevious(nLine - 1, 0x1);
  if (nFoundLine >= 0)
    rCtrl.GotoLine(nFoundLine);
  else
    MessageBeep(MB_ICONHAND);	
}


void CAIPIEditorView::OnUpdateOptionsAutoindent(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bAutoIndent);
	
}




void CAIPIEditorView::OnUpdateOptionsAutocomplete(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bAutoComplete);	
	
}


void CAIPIEditorView::OnUpdateOptionsModifiedNotfication(CCmdUI* pCmdUI) 
{
	
	pCmdUI->SetCheck(g_bNotificationModified);	
}

void CAIPIEditorView::OnUpdateOptionsViewLineNumbers(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(GetCtrl().GetMarginWidthN(0) != 0);	
}

void CAIPIEditorView::OnUpdateOptionsViewWhitespace(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bViewWS);
	
}

void CAIPIEditorView::OnUpdateOptionsViewLineEnd(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bViewEOL);
	
}



void CAIPIEditorView::OnUpdateOptionsViewIndentLine(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bViewIndent);
}


void CAIPIEditorView::OnUpdateOptionsSelectionMargin(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(GetCtrl().GetMarginWidthN(1) != 0);		
}

void CAIPIEditorView::OnUpdateOptionsFoldMargin(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(GetCtrl().GetMarginWidthN(2) != 0);	
}

void CAIPIEditorView::OnUpdateOptionsAddMarker(CCmdUI* pCmdUI) 
{
	CScintillaCtrl& rCtrl = GetCtrl();
  long nPos = rCtrl.GetCurrentPos();
  int nLine = rCtrl.LineFromPosition(nPos);
  int nBits = rCtrl.MarkerGet(nLine);
  pCmdUI->Enable((nBits & 0x1) == 0);	
}

void CAIPIEditorView::OnUpdateOptionsDeleteMarker(CCmdUI* pCmdUI) 
{
	CScintillaCtrl& rCtrl = GetCtrl();
  long nPos = rCtrl.GetCurrentPos();
  int nLine = rCtrl.LineFromPosition(nPos);
  int nBits = rCtrl.MarkerGet(nLine);
  pCmdUI->Enable(nBits & 0x1);
}


void CAIPIEditorView::OnUpdateOptionsDeleteAllMarkers(CCmdUI* pCmdUI) 
{
	if( m_nMarkers > 0 )
	{
		pCmdUI->Enable(true);
	}
	else
	{
		pCmdUI->Enable(false);
	}
	
}

void CAIPIEditorView::OnUpdateInsert(CCmdUI* pCmdUI)
{
  CString sText;
  if (GetCtrl().GetOvertype())
    sText.LoadString(ID_INDICATOR_OVR);
	pCmdUI->SetText(sText);
}

void CAIPIEditorView::OnUpdateStyle(CCmdUI* pCmdUI)
{
   CScintillaCtrl& rCtrl = GetCtrl();
   int nPos = rCtrl.GetCurrentPos();
   int nStyle = rCtrl.GetStyleAt(nPos);
   CString sLine;
   sLine.Format(IDS_STYLE_INDICATOR, nStyle);
   pCmdUI->SetText(sLine);
} 

void CAIPIEditorView::OnUpdateFold(CCmdUI* pCmdUI)
{
  CScintillaCtrl& rCtrl = GetCtrl();
  long nPos = rCtrl.GetCurrentPos();
  int nLine = rCtrl.LineFromPosition(nPos);
  int nLevel = rCtrl.GetFoldLevel(nLine) & SC_FOLDLEVELNUMBERMASK;
  nLevel -= 1024;

  CString sLine;
  sLine.Format(IDS_FOLD_INDICATOR, nLevel);
  pCmdUI->SetText(sLine);
} 

void CAIPIEditorView::OnUpdateLine(CCmdUI* pCmdUI)
{
  CScintillaCtrl& rCtrl = GetCtrl();
  long nPos = rCtrl.GetCurrentPos();
  int nLine = rCtrl.LineFromPosition(nPos);
  int nColumn = rCtrl.GetColumn(nPos);

  CString sLine;
  sLine.Format(IDS_LINE_INDICATOR, nLine + 1, nColumn, nPos);
  pCmdUI->SetText(sLine);
} 
				
	

void CAIPIEditorView::OnUpdateUI(SCNotification* /*pSCNotification*/)
{
	CScintillaCtrl& rCtrl = GetCtrl();
	
	// do brace matching
	long lStart = rCtrl.GetCurrentPos();
    long lEnd = rCtrl.BraceMatch(lStart - 1, 0);
   
// if there is a matching brace highlight it
   if (lEnd >= 0)
       rCtrl.BraceHighlight(lStart-1, lEnd);
	   // if there is NO matching brace erase old highlight
   else
      rCtrl.BraceHighlight(-1, -1);

	//m_iModifyBeforeAfter= 0;
   /*
	CString str;
	int pos = rCtrl.GetCurrentPos();
	str.Format(_T("Update pos... %d"), pos);
	//AfxMessageBox(str);
*/

}

void CAIPIEditorView::OnKey(SCNotification* pSCNotification)
{
		/*
		int m_iKey = pSCNotification->ch;
		CString str;
		str.Format(_T("Key... %d"), m_iKey);
		AfxMessageBox(str);
 	   */
}



void CAIPIEditorView::OnModified(SCNotification* pSCNotification)
{
	
	
	m_iModificationType = pSCNotification->modificationType;
	
	if( g_bNotificationModified  )
	{
		//CString str;
		//str.Format(_T("Modified flag... %d"), g_bNotificationModified);
		//AfxMessageBox(str);
		WSPModified();
	}
	
	
	//int pos = pSCNotification->position;
	//CString	sTxt =	  pSCNotification->text;	

	/*
	CString str;
	str.Format(_T("Modified pos... %d"), pos);
	AfxMessageBox(str);
	str.Format(_T("Modified type... %d"), type);
	AfxMessageBox(str);
	AfxMessageBox(sTxt);
	*/
	
	/*
	CScintillaCtrl& rCtrl = GetCtrl();
	CString str;
	int p = rCtrl.GetCurrentPos();
	str.Format(_T("Modified pos... %d"), p);
	AfxMessageBox(str);
	*/

	/*
	SCNotification scn;
	scn.modificationType = SC_MOD_INSERTTEXT || SC_MOD_DELETETEXT;
	int pos = scn.position;
	int length = scn.length;
	int lines = scn.linesAdded;
	
	CString str;
	str.Format(_T("pos  %d"), pos);
	AfxMessageBox(str);
	str.Format(_T("length  %d"), length);
	AfxMessageBox(str);
	str.Format(_T("lines added  %d"), lines);
	AfxMessageBox(str);
	*/
	
	/*
	TextRange tr;
	tr.chrg.cpMin = nStartSel - 4;
	tr.chrg.cpMax = nEndSel;
	char sText[5];
	tr.lpstrText = sText;
	rCtrl.GetTextRange(&tr);
	*/


}




void CAIPIEditorView::OnSavePointLeft(SCNotification* /*pSCNotification*/)
{
	
	//CAIPIEditorDoc * pDoc = GetDocument();
	//pDoc->SetModifiedFlag(true);
	/*
	CScintillaCtrl& rCtrl = GetCtrl();
	long pos = rCtrl.GetCurrentPos();
	int symbol = rCtrl.GetCharAt(pos-1);
	
	if( symbol == SPACE || symbol == CARRIAGE_RETURN || symbol == NEW_LINE || symbol == HORIZONTAL_TAB || symbol == VERTICAL_TAB )
	{
		CAIPIEditorDoc * pDoc = GetDocument();
		pDoc->SetModifiedFlag(true);	
	}
	*/	
		
	
}



//A simple example of auto completion
void CAIPIEditorView::OnCharAdded(SCNotification* /*pSCNotification*/)
{
	CScintillaCtrl& rCtrl = GetCtrl();

	long pos = rCtrl.GetCurrentPos();
	int symbol = rCtrl.GetCharAt(pos-1);
	//CString str;
	//str.Format(_T("symbol  %d"), symbol);
	//AfxMessageBox(str);
	//Saves points for undo and redo
	if( symbol == SPACE || symbol == CARRIAGE_RETURN || symbol == HORIZONTAL_TAB )
	{
		rCtrl.SetSavePoint();
	}
	
	if( m_bAutoComplete)
	{
		if( symbol == PERIOD )
		{
			AutoCompleteJScript();	
		}
		
		AutoCompleteAIPIKeyWord( symbol);
		AutoCompleteJSDateArrayId();
		
	}
	if( m_bAutoIndent )
	{
		 AutoIndent(pos, symbol );
	}


	
	
  /*
  //Get the previous 12 characters and if it is "scintilla is" case insensitive
  //then display a list which allows "very cool", "easy" or the "way cool!!"
  int nStartSel = rCtrl.GetSelectionStart();
  int nEndSel = rCtrl.GetSelectionEnd();

  if ((nStartSel == nEndSel) && (nStartSel > 12))
  {
    
	TextRange tr;
    tr.chrg.cpMin = nStartSel - 13;
    tr.chrg.cpMax = nEndSel - 1;
    char sText[13];
    tr.lpstrText = sText;
    rCtrl.GetTextRange(&tr);

	CString str = _T("Mauricio\nErnesto\nAlfaro\nParada");

    if (_strcmpi(sText, "AIPI Project") == 0)
    {
      //Display the auto completion list
      //rCtrl.AutoCShow(0, _T("Conocimiento\nInteligencia\nLibertad"));
		rCtrl.AutoCShow(0, str);
    }
  }

  */
  
    
			
}

/*
void CAIPIEditorView::AutoCompleteGestion(long pos)
{
	
	CScintillaCtrl& rCtrl = GetCtrl();

	if( m_iModificationType == INSERTTEXT )
	{
		int D = 68;
		int a = 97;
		int t = 116;
		int e = 101;
		

		long posDate = WSPDetectKeyWord4( pos, D, a, t, e);
		if( posDate != NOT_FOUND )
		{
			CString str;
			str.Format(_T("Pos Date...%d  " ), posDate);
			AfxMessageBox(str);

			LPSTR szNew = "new";
			LPSTR szEqual = "=";

			long posNew = WSPSearchToken(posDate, 0, szNew);
			long posEqual = WSPSearchToken(posNew, 0, szEqual);
			str.Format(_T("Pos New...%d  " ), posNew);
			AfxMessageBox(str);
			str.Format(_T("Pos Equal...%d  " ), posEqual);
			AfxMessageBox(str);

			long currentPos = posEqual;
			int symbol = rCtrl.GetCharAt(currentPos -1);
			str.Format(_T("symbol  %d"), symbol);
			AfxMessageBox(str);

			while( !isAlphaNumeric(symbol) )
			{
				--currentPos;
				symbol = rCtrl.GetCharAt(currentPos);
				CString str;
				str.Format(_T("symbol  %d"), symbol);
				AfxMessageBox(str);
	
			}

			long posStart = rCtrl.WordStartPosition(currentPos, true);
			long posEnd = rCtrl.WordEndPosition(currentPos, true);
			CString strVar = WSPGetText(posStart, posEnd);
			AfxMessageBox(strVar);
		}
	}	

}
*/




void CAIPIEditorView::AutoCompleteJSDateArrayId()
{
	CScintillaCtrl& rCtrl = GetCtrl();
	int nStartSel = rCtrl.GetSelectionStart();
	int nEndSel = rCtrl.GetSelectionEnd();

	//JScript Object name Date
	if ((nStartSel == nEndSel) && (nStartSel > 4))
	{
    	TextRange tr;
		tr.chrg.cpMin = nStartSel - 5;
		tr.chrg.cpMax = nEndSel - 1;
		char chText[5];
		tr.lpstrText = chText;
		rCtrl.GetTextRange(&tr);
		//CString sText = (CString)chText;
		//AfxMessageBox(sText);

		if (_strcmpi(chText, "Date") == 0)
		{

			LPSTR szNew = "new";
			LPSTR szEqual = "=";

			long posDate = nStartSel -5;
			long posNew = WSPSearchToken(posDate, 0, szNew);
			if( posNew == NOT_FOUND )
			{
				return;
			}
			long posEqual = WSPSearchToken(posNew, 0, szEqual);
			if( posEqual == NOT_FOUND )
			{
				return;
			}
			/*
			CString str;
			str.Format(_T("Pos Date...%d  " ), posDate);
			AfxMessageBox(str);
			str.Format(_T("Pos New...%d  " ), posNew);
			AfxMessageBox(str);
			str.Format(_T("Pos Equal...%d  " ), posEqual);
			AfxMessageBox(str);
			*/
			
			long currentPos = posEqual;
			int symbol = rCtrl.GetCharAt(currentPos -1);
			//str.Format(_T("symbol  %d"), symbol);
			//AfxMessageBox(str);

			while( !isAlphaNumeric(symbol) )
			{
				--currentPos;
				if( currentPos < 0 )
				{
					return;
				}
				symbol = rCtrl.GetCharAt(currentPos);
				/*
				CString str;
				str.Format(_T("symbol  %d"), symbol);
				AfxMessageBox(str);
				*/
			}

			long posStart = rCtrl.WordStartPosition(currentPos, true);
			long posEnd = rCtrl.WordEndPosition(currentPos, true);
			CString strObj = WSPGetText(posStart, posEnd);
			//AfxMessageBox(strObj);
			mJScriptObj.insert(m_mJScriptObj::value_type(strObj, _T("Date")));

		}

	}

	//JScript Object name Array
	if ((nStartSel == nEndSel) && (nStartSel > 5))
	{
    	TextRange tr;
		tr.chrg.cpMin = nStartSel - 6;
		tr.chrg.cpMax = nEndSel - 1;
		char chText[6];
		tr.lpstrText = chText;
		rCtrl.GetTextRange(&tr);
		//CString sText = (CString)chText;
		//AfxMessageBox(sText);

		if (_strcmpi(chText, "Array") == 0)
		{
			LPSTR szNew = "new";
			LPSTR szEqual = "=";

			long posDate = nStartSel-6;
			long posNew = WSPSearchToken(posDate, 0, szNew);
			if( posNew == NOT_FOUND )
			{
				return;
			}
			long posEqual = WSPSearchToken(posNew, 0, szEqual);
			if( posEqual == NOT_FOUND )
			{
				return;
			}
			/*
			CString str;
			str.Format(_T("Pos Date...%d  " ), posDate);
			AfxMessageBox(str);
			str.Format(_T("Pos New...%d  " ), posNew);
			AfxMessageBox(str);
			str.Format(_T("Pos Equal...%d  " ), posEqual);
			AfxMessageBox(str);
			*/
			long currentPos = posEqual;
			int symbol = rCtrl.GetCharAt(currentPos -1);
			//str.Format(_T("symbol  %d"), symbol);
			//AfxMessageBox(str);

			while( !isAlphaNumeric(symbol) )
			{
				--currentPos;
				if( currentPos < 0 )
				{
					return;
				}
				symbol = rCtrl.GetCharAt(currentPos);
				CString str;
				//str.Format(_T("symbol  %d"), symbol);
				//AfxMessageBox(str);
			}

			long posStart = rCtrl.WordStartPosition(currentPos, true);
			long posEnd = rCtrl.WordEndPosition(currentPos, true);
			CString strObj = WSPGetText(posStart, posEnd);
			//AfxMessageBox(strObj);
			mJScriptObj.insert(m_mJScriptObj::value_type(strObj, _T("Array")));

		}

	}

}


void CAIPIEditorView::AutoCompleteJSDateArrayObj(int n, long nStartSel, long nEndSel )
{
	CScintillaCtrl& rCtrl = GetCtrl();
	int i = 0;
	CString sKeyWord = _T("");
	CString sAutoCompleteList = _T("");
	
	//Object name with n words
	if ((nStartSel == nEndSel) && (nStartSel > n))
	{
    	TextRange tr;
		tr.chrg.cpMin = nStartSel - (n-1);
		tr.chrg.cpMax = nEndSel - 1;
		char chText[16];
		tr.lpstrText = chText;
		rCtrl.GetTextRange(&tr);
		CString sText = (CString)chText;

		//Check for a Date Object
		m_mJScriptObj::iterator iter;
		iter = mJScriptObj.find(sText);
		if( iter != mJScriptObj.end())
		{
			if( iter->second == _T("Date") )
			{
				//AfxMessageBox(_T("Entro"));
				for( i = 0; i<20; ++i)
				{
					sKeyWord = m_sAutoCompleteDate[i];
					//AfxMessageBox(_T("KeyWord:"));
					//AfxMessageBox(sKeyWord);
					sAutoCompleteList += m_sAutoCompleteDate[i] + _T("\n");
			
				}	
				if( !sAutoCompleteList.IsEmpty() )
				{
					//AfxMessageBox(_T("Mostrar"));
					CScintillaCtrl& rCtrl = GetCtrl();
					rCtrl.AutoCShow(0, sAutoCompleteList);
				}
			}
			if( iter->second == _T("Array") )
			{
				//AfxMessageBox(_T("Entro"));
				for( i = 0; i<5; ++i)
				{
					sKeyWord = m_sAutoCompleteArray[i];
					//AfxMessageBox(_T("KeyWord:"));
					//AfxMessageBox(sKeyWord);
					sAutoCompleteList += m_sAutoCompleteArray[i] + _T("\n");
			
				}	
				if( !sAutoCompleteList.IsEmpty() )
				{
					//AfxMessageBox(_T("Mostrar"));
					CScintillaCtrl& rCtrl = GetCtrl();
					rCtrl.AutoCShow(0, sAutoCompleteList);
				}
			}
		}
		
	
	}
	

}


void CAIPIEditorView::AutoCompleteJScript()
{
	
	CScintillaCtrl& rCtrl = GetCtrl();
	int i = 0;
	CString sKeyWord = _T("");
	CString sAutoCompleteList = _T("");

	int nStartSel = rCtrl.GetSelectionStart();
	int nEndSel = rCtrl.GetSelectionEnd();

	//JScript Object: Math 
	if ((nStartSel == nEndSel) && (nStartSel > 4))
	{
    	TextRange tr;
		tr.chrg.cpMin = nStartSel - 5;
		tr.chrg.cpMax = nEndSel - 1;
		char chText[13];
		tr.lpstrText = chText;
		rCtrl.GetTextRange(&tr);
		//CString sText = (CString)chText;
		//AfxMessageBox(sText);
		//Check for a Math Object
		if (_strcmpi(chText, "Math") == 0)
		{
			for( i = 0; i<24; ++i)
			{
				sKeyWord = m_sAutoCompleteMath[i];
				//AfxMessageBox(_T("KeyWord:"));
				//AfxMessageBox(sKeyWord);
				sAutoCompleteList += m_sAutoCompleteMath[i] + _T("\n");
			}	
			if( !sAutoCompleteList.IsEmpty() )
			{
				//AfxMessageBox(_T("Mostrar"));
				CScintillaCtrl& rCtrl = GetCtrl();
				rCtrl.AutoCShow(0, sAutoCompleteList);
			}

		}
	}

	//JSCript Object: Date
	//JSCript Object: Array
	AutoCompleteJSDateArrayObj(1, nStartSel, nEndSel);	//Object name 1 word
	AutoCompleteJSDateArrayObj(2, nStartSel, nEndSel);	//Object name 2 words
	AutoCompleteJSDateArrayObj(3, nStartSel, nEndSel);	//Object name 3 words
	AutoCompleteJSDateArrayObj(4, nStartSel, nEndSel);	//Object name 4 words
	AutoCompleteJSDateArrayObj(5, nStartSel, nEndSel);	//Object name 5 words
	AutoCompleteJSDateArrayObj(6, nStartSel, nEndSel);	//Object name 6 words
	AutoCompleteJSDateArrayObj(7, nStartSel, nEndSel);	//Object name 7 words
	AutoCompleteJSDateArrayObj(8, nStartSel, nEndSel);	//Object name 8 words
	AutoCompleteJSDateArrayObj(9, nStartSel, nEndSel);	//Object name 9 words
	AutoCompleteJSDateArrayObj(10, nStartSel, nEndSel);	//Object name 10 words
	AutoCompleteJSDateArrayObj(11, nStartSel, nEndSel);	//Object name 11 words
	AutoCompleteJSDateArrayObj(12, nStartSel, nEndSel);	//Object name 12 words
	AutoCompleteJSDateArrayObj(13, nStartSel, nEndSel);	//Object name 13 words
	AutoCompleteJSDateArrayObj(14, nStartSel, nEndSel);	//Object name 14 words
	AutoCompleteJSDateArrayObj(15, nStartSel, nEndSel);	//Object name 15 words
	AutoCompleteJSDateArrayObj(16, nStartSel, nEndSel);	//Object name 16 words
	AutoCompleteJSDateArrayObj(17, nStartSel, nEndSel);	//Object name 17 words
	AutoCompleteJSDateArrayObj(18, nStartSel, nEndSel);	//Object name 18 words
	

	
  
}



void CAIPIEditorView::AutoCompleteAIPIKeyWord(int symbol)
{
	int i = 0;
	CString sKeyWord = _T("");
	CString sAutoCompleteList = _T("");

	if( isAlphabetic(symbol)) 
	{
		TCHAR buffer[2];
		wsprintf(buffer, _T("%c"), symbol);
		m_sCurrentWord += (CString)buffer;
		//AfxMessageBox(_T("Current Word:"));
		//AfxMessageBox(m_sCurrentWord);
		
		int wordSize = m_sCurrentWord.GetLength();

		switch( wordSize )
		{
			case 2:
				for( i = 0; i<AUTOCOMPLETEKEYWORD_SIZE; ++i)
				{
					sKeyWord = m_sAutoCompleteKeyWord[i];
					//AfxMessageBox(_T("KeyWord:"));
					//AfxMessageBox(sKeyWord);
					sKeyWord = sKeyWord.Left(2);
					//AfxMessageBox(sKeyWord);
					if( sKeyWord == m_sCurrentWord )
					{
						//AfxMessageBox(_T("Entro:"));
						sAutoCompleteList += m_sAutoCompleteKeyWord[i] + _T("\n");
					}
				}
				if( !sAutoCompleteList.IsEmpty() )
				{
					CScintillaCtrl& rCtrl = GetCtrl();
					rCtrl.AutoCShow(2, sAutoCompleteList);
				}
				break;
			case 3:
				for(  i = 0; i<AUTOCOMPLETEKEYWORD_SIZE; ++i)
				{
					sKeyWord = m_sAutoCompleteKeyWord[i];
					//AfxMessageBox(_T("KeyWord:"));
					//AfxMessageBox(sKeyWord);
					sKeyWord = sKeyWord.Left(3);
					//AfxMessageBox(sKeyWord);
					if( sKeyWord == m_sCurrentWord )
					{
						//AfxMessageBox(_T("Entro:"));
						sAutoCompleteList += m_sAutoCompleteKeyWord[i] + _T("\n");
						//AfxMessageBox(sAutoCompleteList);
					}
				}
				if( !sAutoCompleteList.IsEmpty() )
				{
					CScintillaCtrl& rCtrl = GetCtrl();
					rCtrl.AutoCShow(3, sAutoCompleteList);
				}
				break;
			case 4:
				for(  i = 0; i<AUTOCOMPLETEKEYWORD_SIZE; ++i)
				{
					sKeyWord = m_sAutoCompleteKeyWord[i];
					//AfxMessageBox(_T("KeyWord:"));
					//AfxMessageBox(sKeyWord);
					sKeyWord = sKeyWord.Left(4);
					//AfxMessageBox(sKeyWord);
					if( sKeyWord == m_sCurrentWord )
					{
						//AfxMessageBox(_T("Entro:"));
						sAutoCompleteList += m_sAutoCompleteKeyWord[i] + _T("\n");
						//AfxMessageBox(sAutoCompleteList);
					}
				}
				if( !sAutoCompleteList.IsEmpty() )
				{
					CScintillaCtrl& rCtrl = GetCtrl();
					rCtrl.AutoCShow(4, sAutoCompleteList);
				}
				break;
			case 5:
				for(  i = 0; i<AUTOCOMPLETEKEYWORD_SIZE; ++i)
				{
					sKeyWord = m_sAutoCompleteKeyWord[i];
					//AfxMessageBox(_T("KeyWord:"));
					//AfxMessageBox(sKeyWord);
					sKeyWord = sKeyWord.Left(5);
					//AfxMessageBox(sKeyWord);
					if( sKeyWord == m_sCurrentWord )
					{
						//AfxMessageBox(_T("Entro:"));
						sAutoCompleteList += m_sAutoCompleteKeyWord[i] + _T("\n");
						//AfxMessageBox(sAutoCompleteList);
					}
				}
				if( !sAutoCompleteList.IsEmpty() )
				{
					CScintillaCtrl& rCtrl = GetCtrl();
					rCtrl.AutoCShow(5, sAutoCompleteList);
				}
				break;
			case 6:
				for(  i = 0; i<AUTOCOMPLETEKEYWORD_SIZE; ++i)
				{
					sKeyWord = m_sAutoCompleteKeyWord[i];
					//AfxMessageBox(_T("KeyWord:"));
					//AfxMessageBox(sKeyWord);
					sKeyWord = sKeyWord.Left(6);
					//AfxMessageBox(sKeyWord);
					if( sKeyWord == m_sCurrentWord )
					{
						//AfxMessageBox(_T("Entro:"));
						sAutoCompleteList += m_sAutoCompleteKeyWord[i] + _T("\n");
						//AfxMessageBox(sAutoCompleteList);
					}
				}
				if( !sAutoCompleteList.IsEmpty() )
				{
					CScintillaCtrl& rCtrl = GetCtrl();
					rCtrl.AutoCShow(6, sAutoCompleteList);
				}
				break;
			case 7:
				for(  i = 0; i<AUTOCOMPLETEKEYWORD_SIZE; ++i)
				{
					sKeyWord = m_sAutoCompleteKeyWord[i];
					//AfxMessageBox(_T("KeyWord:"));
					//AfxMessageBox(sKeyWord);
					sKeyWord = sKeyWord.Left(7);
					//AfxMessageBox(sKeyWord);
					if( sKeyWord == m_sCurrentWord )
					{
						//AfxMessageBox(_T("Entro:"));
						sAutoCompleteList += m_sAutoCompleteKeyWord[i] + _T("\n");
						//AfxMessageBox(sAutoCompleteList);
					}
				}
				if( !sAutoCompleteList.IsEmpty() )
				{
					CScintillaCtrl& rCtrl = GetCtrl();
					rCtrl.AutoCShow(7, sAutoCompleteList);
				}
				break;
			case 8:
				for(  i = 0; i<AUTOCOMPLETEKEYWORD_SIZE; ++i)
				{
					sKeyWord = m_sAutoCompleteKeyWord[i];
					//AfxMessageBox(_T("KeyWord:"));
					//AfxMessageBox(sKeyWord);
					sKeyWord = sKeyWord.Left(8);
					//AfxMessageBox(sKeyWord);
					if( sKeyWord == m_sCurrentWord )
					{
						//AfxMessageBox(_T("Entro:"));
						sAutoCompleteList += m_sAutoCompleteKeyWord[i] + _T("\n");
						//AfxMessageBox(sAutoCompleteList);
					}
				}
				if( !sAutoCompleteList.IsEmpty() )
				{
					CScintillaCtrl& rCtrl = GetCtrl();
					rCtrl.AutoCShow(8, sAutoCompleteList);
				}
				break;
			case 9:
				for(  i = 0; i<AUTOCOMPLETEKEYWORD_SIZE; ++i)
				{
					sKeyWord = m_sAutoCompleteKeyWord[i];
					//AfxMessageBox(_T("KeyWord:"));
					//AfxMessageBox(sKeyWord);
					sKeyWord = sKeyWord.Left(9);
					//AfxMessageBox(sKeyWord);
					if( sKeyWord == m_sCurrentWord )
					{
						//AfxMessageBox(_T("Entro:"));
						sAutoCompleteList += m_sAutoCompleteKeyWord[i] + _T("\n");
						//AfxMessageBox(sAutoCompleteList);
					}
				}
				if( !sAutoCompleteList.IsEmpty() )
				{
					CScintillaCtrl& rCtrl = GetCtrl();
					rCtrl.AutoCShow(9, sAutoCompleteList);
				}
				break;
			
				
		}

		

	}
	else
	{
		m_sCurrentWord.Empty();
	}
	



}


	

void CAIPIEditorView::AutoIndent(long pos, int symbol) 
{
	CScintillaCtrl& rCtrl = GetCtrl();	

	/*
	if ( symbol == OPEN_BRACE )
	{
		m_nCol = rCtrl.GetColumn(pos-1);
		int nWidth = rCtrl.GetIndent();
		int curLine = rCtrl.LineFromPosition(pos);
		int nIndent = rCtrl.GetLineIndentation(curLine);
		int nextIndentCol = nWidth + m_nCol;
		int nextLinePos = rCtrl.PositionFromLine(curLine + 2);
		int nextIndentPos = nextIndentCol + nextLinePos;
		//rCtrl.GotoPos(nextIndentPos);
		
	}
	else if( symbol == CLOSE_BRACE )
	{
		char szCloseBrace[] = "}";
		char szEmpty[] = "";
		long closePos = 0;
		rCtrl.SetTargetStart(pos-1);
		rCtrl.SetTargetEnd(pos);
		rCtrl.SearchInTarget(strlen(szCloseBrace), szCloseBrace);
		rCtrl.ReplaceTarget(strlen(szEmpty), szEmpty);
		
		int line = rCtrl.LineFromPosition(pos-1);
		closePos = rCtrl.FindColumn(line , m_nCol, 0);
		rCtrl.InsertText(closePos, szCloseBrace);
		return;	
	}
	*/


	
	if( symbol == CARRIAGE_RETURN || symbol == NEW_LINE )
	{	
////// AutoIndent code ///////////////////////	
	
		TCHAR lineBuff[1000];
		
		int curLine = rCtrl.LineFromPosition(pos);
		int lineLength = rCtrl.LineLength(curLine);
		
		if( curLine > 0 && lineLength <= 2)
		{
			int prevLineLength = rCtrl.LineLength(curLine - 1);
			if( prevLineLength < sizeof(lineBuff) )
			{
				WORD buffLen = sizeof(lineBuff);
				memcpy(lineBuff, &buffLen, sizeof(buffLen));
				rCtrl.GetLine(curLine -1, (static_cast<TCHAR *>(lineBuff)),0);
				
				lineBuff[prevLineLength] = '\0';
				for( int pos = 0; lineBuff[pos]; pos++)
				{
					if( lineBuff[pos] != ' ' && lineBuff[pos] != '\t')
					{
						lineBuff[pos] = '\0';
					}
				}
				rCtrl.ReplaceSel((static_cast<TCHAR *>(lineBuff)), 0);

			}
		}
	
	}
	
}



//////////////////////////////////////////////////////////////////////////////////////////////////
//// Workspace Functions /////
//////////////////////////////////////////////////////////////////////////////////////////////////
long CAIPIEditorView::WSPSearchToken(long posStart, long posEnd, LPSTR szToken)
{
	CScintillaCtrl& rCtrl = GetCtrl();

	rCtrl.SetTargetStart(posStart);
	rCtrl.SetTargetEnd(posEnd);
	rCtrl.SetSearchFlags(SCFIND_MATCHCASE);
	long posTokenStart = rCtrl.SearchInTarget(strlen(szToken), szToken);
	
	/*
	CString str;
	str.Format(_T("TOKEN Start Position .. %d"), posTokenStart);
	AfxMessageBox(str);
	*/
	return posTokenStart;
}


CString CAIPIEditorView::WSPGetText(long posStart, long posEnd)
{
	const STRING_LIMIT_LENGTH = 100000;
	CScintillaCtrl& rCtrl = GetCtrl();
	CString sName = _T("EMPTY");

	
	if( posStart >= posEnd )
		return sName;

	int iLength = posEnd - posStart + 1;
	
	//Gets name
	TextRange tr;
	tr.chrg.cpMin = posStart;
	tr.chrg.cpMax = posEnd;
	char chName[TEXT_LENGTH];
	
	tr.lpstrText = chName;

	if (iLength > STRING_LIMIT_LENGTH )
	{
		//rCtrl.GetText(TEXT_LENGTH, chName);
		return _T("OVERLOAD"); 
	}
	else if ( iLength > TEXT_LENGTH )
	{
		tr.chrg.cpMin = posStart;
		tr.chrg.cpMax = posStart + 15;
		char chStartName[16];
		tr.lpstrText = chStartName;
		rCtrl.GetTextRange(&tr);
		CString sStartName = (CString)chStartName;
			
		tr.chrg.cpMin = posEnd-15;
		tr.chrg.cpMax = posEnd;
		char chEndName[16];
		tr.lpstrText = chEndName;
		rCtrl.GetTextRange(&tr);
		CString sEndName = (CString)chEndName;
		sName = sStartName + _T("...") + sEndName; 
	}
	else
	{
		rCtrl.GetTextRange(&tr);
		sName = (CString)chName;
	
	}	
	
	
	//AfxMessageBox(sName);
return sName;
}




int CAIPIEditorView::WSPAddNodeTree1(CString sName, CString sParam, int image)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mWSPTree1::iterator iter;
	HTREEITEM hChild = NULL;

	CString sFullName = sName + sParam;
	LPTSTR lpszFullName	= sFullName.GetBuffer(TEXT_LENGTH);
	
	//Check if the rule name already exist in the workspace
	iter = pMainFrame->gmWSPTree1.find(sName);
	if( iter != pMainFrame->gmWSPTree1.end())
	{	
  		pMainFrame->m_wndOutputTabView.AddMsg1(_T("WARNING: Element...[ ") + sName + _T(" ] already exist."));
		return P_UNSUCCESS;
	}
	else
	{
		CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
		CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
		CScintillaView* pView = (CScintillaView*) pChild->GetActiveView();
		ASSERT(pView);
		CAIPIEditorDoc* pDoc = (CAIPIEditorDoc*)pView->GetDocument();
		ASSERT_VALID(pDoc);
		CString strFilePath = pDoc->GetPathName();
		CString strFileName = pDoc->GetTitle();
		//AfxMessageBox(strFilePath);
		//AfxMessageBox(strFileName);
		
		
		//Add rule to the Workspace
		hChild = pMainFrame->m_wndWorkspaceTabView.AddTreeItem1(hTProjectRoot, lpszFullName, (HTREEITEM)TVI_SORT, image);
		CWorkspaceTree1 wsp1;
		wsp1.addElement(sName, hChild, strFilePath, strFileName);

		return P_SUCCESS;
		//pMainFrame->m_wndPropertiesBar.InsertEditProperty(_T("Hola"), _T("No Desc"), _T("Data"));

	}
								
return P_UNSUCCESS;
}


int CAIPIEditorView::WSPAddNodeTypeTree1(CString sName, CString sParam, int image, int type)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mWSPTree1::iterator iter;
	
	CString sFullName = sName + sParam;
	LPTSTR lpszFullName	= sFullName.GetBuffer(TEXT_LENGTH);
	//AfxMessageBox(sName);
	//AfxMessageBox(sParam);

	
	//Check if the rule name already exist in the workspace
	iter = pMainFrame->gmWSPTree1.find(sName);
	if( iter != pMainFrame->gmWSPTree1.end())
	{	
  		pMainFrame->m_wndOutputTabView.AddMsg1(_T("WARNING: Element...[ ") + sName + _T(" ] already exist."));
		return P_UNSUCCESS;
	}
	else
	{
		CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
		CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
		CScintillaView* pView = (CScintillaView*) pChild->GetActiveView();
		ASSERT(pView);
		CAIPIEditorDoc* pDoc = (CAIPIEditorDoc*)pView->GetDocument();
		ASSERT_VALID(pDoc);
		CString strFilePath = pDoc->GetPathName();
		CString strFileName = pDoc->GetTitle();
		//AfxMessageBox(strFilePath);
		//AfxMessageBox(strFileName);

		CScintillaCtrl& rCtrl = GetCtrl();
		LPSTR lpName = (LPSTR)sName.GetBuffer(0); 
		int line = 0;
		long currentPos = rCtrl.GetCurrentPos();
		long pos = WSPSearchToken( currentPos, 0, lpName);
		if( pos != NOT_FOUND )
		{
			line = rCtrl.LineFromPosition(pos);
		}
		else
		{
			line = rCtrl.LineFromPosition(currentPos);
		}
		
		
		//Add rule to the Workspace
		CWorkspaceTree1 wsp1;
		CWorkspaceLocation wsploc;
		HTREEITEM hChild = NULL;
	
		CString str;
		switch( type)
		{

		case AIPI_CLASS:
			hChild = pMainFrame->m_wndWorkspaceTabView.AddTreeItem1(hTProjectClass, lpszFullName, (HTREEITEM)TVI_SORT, image);
			pMainFrame->m_wndWorkspaceTabView.m_treeCtrl1.Expand(hTProjectClass ,TVE_EXPAND);
			wsp1.addElement(sName, hChild, strFilePath, strFileName);
			wsploc.addLocation(hChild, pos, line, sName, strFilePath, AIPI_CLASS);

			/*
			str.Format(_T("Class HTREEITEM...%d  " ), hTProjectClass);
			AfxMessageBox(str);
			AfxMessageBox(_T("CLASS"));
			*/

			break;
		case AIPI_FUNCTION:
			hChild = pMainFrame->m_wndWorkspaceTabView.AddTreeItem1(hTProjectFunction, lpszFullName, (HTREEITEM)TVI_SORT, image);
			pMainFrame->m_wndWorkspaceTabView.m_treeCtrl1.Expand(hTProjectFunction ,TVE_EXPAND);
			wsp1.addElement(sName, hChild, strFilePath, strFileName);
			wsploc.addLocation(hChild, pos, line, sName, strFilePath, AIPI_FUNCTION);
			
			/*
			str.Format(_T("Function HTREEITEM...%d  " ), hTProjectFunction);
			AfxMessageBox(str);
			AfxMessageBox(_T("FUNCTION"));
			*/
			break;
		case AIPI_QUERY:
			hChild = pMainFrame->m_wndWorkspaceTabView.AddTreeItem1(hTProjectQuery, lpszFullName, (HTREEITEM)TVI_SORT, image);
			pMainFrame->m_wndWorkspaceTabView.m_treeCtrl1.Expand(hTProjectQuery ,TVE_EXPAND);
			wsp1.addElement(sName, hChild, strFilePath, strFileName);
			wsploc.addLocation(hChild, pos, line, sName, strFilePath, AIPI_QUERY);
			
			/*
			str.Format(_T("Query HTREEITEM...%d  " ), hTProjectQuery);
			AfxMessageBox(str);
			AfxMessageBox(_T("QUERY"));
			*/
			break;
		case AIPI_RULE:
			hChild = pMainFrame->m_wndWorkspaceTabView.AddTreeItem1(hTProjectRule, lpszFullName, (HTREEITEM)TVI_SORT, image);
			pMainFrame->m_wndWorkspaceTabView.m_treeCtrl1.Expand(hTProjectRule ,TVE_EXPAND);
			wsp1.addElement(sName, hChild, strFilePath, strFileName);
			wsploc.addLocation(hChild, pos, line, sName, strFilePath, AIPI_RULE);
			
			/*
			str.Format(_T("Rule HTREEITEM...%d  " ), hTProjectRule);
			AfxMessageBox(str);
			AfxMessageBox(_T("RULE"));
			AfxMessageBox(sName);
			*/
			

			break;

		case AIPI_VARIABLE:
			hChild = pMainFrame->m_wndWorkspaceTabView.AddTreeItem1(hTProjectVariable, lpszFullName, (HTREEITEM)TVI_SORT, image);
			pMainFrame->m_wndWorkspaceTabView.m_treeCtrl1.Expand(hTProjectVariable ,TVE_EXPAND);
			wsp1.addElement(sName, hChild, strFilePath, strFileName);
			wsploc.addLocation(hChild, pos, line, sName, strFilePath, AIPI_VARIABLE);

			/*
			str.Format(_T("Variable HTREEITEM...%d  " ), hTProjectVariable);
			AfxMessageBox(str);
			AfxMessageBox(_T("VARIABLE"));
			*/
			
			break;

		}
			
		//wsploc.printLocation();
		return P_SUCCESS;
	

	}
								
return P_UNSUCCESS;
}



int CAIPIEditorView::WSPDeleteNodeTree1(CString sName)
{
	
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mWSPTree1::iterator iter;
	CWorkspaceTree1 wsp1;
	CWorkspaceLocation wsploc;
	
	//Check if the rule name already exist in the workspace
	HTREEITEM hChild = wsp1.findItem(sName);
	if( hChild != NULL)
	{	
  		//Delete Rule from the Workspace	
  		pMainFrame->m_wndWorkspaceTabView.DeleteTree1(hChild);
		wsp1.eraseElement(sName);
		wsploc.eraseLocation(hChild);
		return P_SUCCESS;
	}

	return P_UNSUCCESS;

}






void CAIPIEditorView::WSPPaste()
{
	if( m_iModificationType == INSERTTEXT )
	{
	
		LPSTR szOpenComment = "/*";
		LPSTR szCloseComment = "*/";
		CScintillaCtrl& rCtrl = GetCtrl();
	
		CString str;

		//Gets the position of the clipboard paste 
		long nStartSel = rCtrl.GetCurrentPos();
		//str.Format(_T("Sel pos1 After Insert... %d"), nStartSel);
		//AfxMessageBox(str);

		//Gets the end position of the clipboard paste	
		long nEndSel = m_nPasteLength + nStartSel;
		//str.Format(_T("End position of Paste Sel pos2... %d"), nEndSel);
		//AfxMessageBox(str);
	
		
		//Saves paste positions for Undo and Redo functions
		m_posPasteStart.push(nStartSel);
		m_posPasteEnd.push(nEndSel);
	
		/*
		str.Format(_T("PASTE START Stack last element...%d  " ), m_posPasteStart.top());
		AfxMessageBox(str);
		str.Format(_T("PASTE START Stack Size...%d  " ), m_posPasteStart.size());
		AfxMessageBox(str);
		str.Format(_T("PASTE END Stack last element...%d  " ), m_posPasteEnd.top());
		AfxMessageBox(str);
		str.Format(_T("PASTE END Stack Size...%d  " ), m_posPasteEnd.size());
		AfxMessageBox(str);
		*/	


		//Paste classes
		WSPAddSelectedClasses( nStartSel, nEndSel, true);

		//Paste queries
		WSPAddSelectedQueries( nStartSel, nEndSel, true);

		//Paste rules
		WSPAddSelectedRules(nStartSel, nEndSel, true);

		//Paste jscript functions
		WSPAddSelectedJSFunctions(nStartSel, nEndSel, true);
	
		//Paste visual basic script functions
		WSPAddSelectedVBSFunctions(nStartSel, nEndSel, true);
		WSPAddSelectedVBSFUNCTIONS(nStartSel, nEndSel, true);
	
		//Paste functions
		//Return type: Integer (int)
		LPSTR szTypeInt = "int";
		WSPAddSelectedFunctions( nStartSel, nEndSel, szTypeInt, 3, true);
		WSPAddSelectedVariables( nStartSel, nEndSel, szTypeInt, 3, true);

		//Return type: Character (char)
		LPSTR szTypeChar = "char";
		WSPAddSelectedFunctions( nStartSel, nEndSel, szTypeChar, 4, true);
		WSPAddSelectedVariables( nStartSel, nEndSel, szTypeChar, 4, true);


		//Return type: Void (void)
		LPSTR szTypeVoid = "void";
		WSPAddSelectedFunctions( nStartSel, nEndSel, szTypeVoid, 4, true);
		WSPAddSelectedVariables( nStartSel, nEndSel, szTypeVoid, 4, true);


		//Return type: Long integer (long)
		LPSTR szTypeLong = "long";
		WSPAddSelectedFunctions( nStartSel, nEndSel, szTypeLong, 4, true);
		WSPAddSelectedVariables( nStartSel, nEndSel, szTypeLong, 4, true);


		//Return type: Floating point (float)
		LPSTR szTypeFloat = "float";
		WSPAddSelectedFunctions( nStartSel, nEndSel, szTypeFloat, 5, true);
		WSPAddSelectedVariables( nStartSel, nEndSel, szTypeFloat, 5, true);

	
		//Return type: Short integer (long)
		LPSTR szTypeShort = "short";
		WSPAddSelectedFunctions( nStartSel, nEndSel, szTypeShort, 5, true);
		WSPAddSelectedVariables( nStartSel, nEndSel, szTypeShort, 5, true);

	
		//Return type: Double floating point (double)
		LPSTR szTypeDouble = "double";
		WSPAddSelectedFunctions( nStartSel, nEndSel, szTypeDouble, 6, true);
		WSPAddSelectedVariables( nStartSel, nEndSel, szTypeDouble, 6, true);

		
		
		
		m_bFlagPaste = false;	
	
	}

}


void CAIPIEditorView::WSPDelete()
{
	if( m_iModificationType == BEFOREDELETE )
	{
		CScintillaCtrl& rCtrl = GetCtrl();
		CString str;
		
		long nStartSel = rCtrl.GetSelectionStart();
		long nEndSel = rCtrl.GetSelectionEnd();
		
		if( nStartSel != nEndSel )
		{
			
			//Delete selected classes
			WSPDeleteSelectedClasses( nStartSel, nEndSel, true);
			
			//Delete selected queries
			WSPDeleteSelectedQueries( nStartSel, nEndSel, true);

			//Delete selected rules
			WSPDeleteSelectedRules(nStartSel, nEndSel, true);


			//Delete selected jscript functions
			WSPDeleteSelectedJSFunctions(nStartSel, nEndSel, true);


			//Delete selected visual basic script functions
			WSPDeleteSelectedVBSFunctions(nStartSel, nEndSel, true);
			WSPDeleteSelectedVBSFUNCTIONS(nStartSel, nEndSel, true);


			//Delete selected functions
			//Return type: Integer (int)
			LPSTR szTypeInt = "int";
			WSPDeleteSelectedFunctions( nStartSel, nEndSel, szTypeInt, 3, true);
			WSPDeleteSelectedVariables( nStartSel, nEndSel, szTypeInt, 3, true);

			//Return type: Character (char)
			LPSTR szTypeChar = "char";
			WSPDeleteSelectedFunctions( nStartSel, nEndSel, szTypeChar, 4, true);
			WSPDeleteSelectedVariables( nStartSel, nEndSel, szTypeChar, 4, true);


			//Return type: Void (void)
			LPSTR szTypeVoid = "void";
			WSPDeleteSelectedFunctions( nStartSel, nEndSel, szTypeVoid, 4, true);
			WSPDeleteSelectedVariables( nStartSel, nEndSel, szTypeVoid, 4, true);


			//Return type: Long integer (long)
			LPSTR szTypeLong = "long";
			WSPDeleteSelectedFunctions( nStartSel, nEndSel, szTypeLong, 4, true);
			WSPDeleteSelectedVariables( nStartSel, nEndSel, szTypeLong, 4, true);


			//Return type: Floating point (float)
			LPSTR szTypeFloat = "float";
			WSPDeleteSelectedFunctions( nStartSel, nEndSel, szTypeFloat, 5, true);
			WSPDeleteSelectedVariables( nStartSel, nEndSel, szTypeFloat, 5, true);

	
			//Return type: Short integer (long)
			LPSTR szTypeShort = "short";
			WSPDeleteSelectedFunctions( nStartSel, nEndSel, szTypeShort, 5, true);
			WSPDeleteSelectedVariables( nStartSel, nEndSel, szTypeShort, 5, true);

	
			//Return type: Double floating point (double)
			LPSTR szTypeDouble = "double";
			WSPDeleteSelectedFunctions( nStartSel, nEndSel, szTypeDouble, 6, true);
			WSPDeleteSelectedVariables( nStartSel, nEndSel, szTypeDouble, 6, true);

		}
		
	}

}


void CAIPIEditorView::WSPWriteVariable(long pos)
{
	CScintillaCtrl& rCtrl = GetCtrl();
	LPSTR szSemiColon = ";";

	CString str;
	if( m_iModificationType == INSERTTEXT )
	{
		
		int idType = WSPDetectIdentifierType( pos);
		

		if( idType != NOT_FOUND )
		{
			//AfxMessageBox(_T("WriteVariable"));
			long posSemiColon = WSPSearchToken( pos -1, m_DocumentLength, szSemiColon);
			long posIdType = WSPSearchNearestIdType(posSemiColon, 0);
	
			//str.Format(_T("Pos SemiColon ...%d  " ), posSemiColon);
			//AfxMessageBox(str);
			
			int r = WSPParseVariable( posIdType -1, posSemiColon);
			
			if( r == AIPI_ERROR && r == NOT_FOUND )
			{
				m_bFlagWriteVariable = true;
				
				
			}
		
			 
		}
		
		
		int r = WSPHandleVariableSemiColon( pos);
		//str.Format(_T("r...%d  " ), r);
		//AfxMessageBox(str);

		if ( r != AIPI_ERROR )
		{
			m_bFlagWriteError = false;
		}
		else
		{
			//AfxMessageBox(_T("WriteRule Error"));
			m_bFlagWriteError = true;
		}
		
		m_bFlagWriteVariable = false;
		

		
	}

}


void CAIPIEditorView::WSPWriteClass(long pos)
{
	CScintillaCtrl& rCtrl = GetCtrl();
	LPSTR szOpenBrace = "{";
	LPSTR szKeyWord = "CLASS";

	CString str;
	if( m_iModificationType == INSERTTEXT )
	{
		int C = 67;
        int L = 76;
		int A = 65;
		int S = 83;
		
		long posClass = WSPDetectKeyWord5( pos, C, L, A, S, S);
		
		if( posClass != NOT_FOUND )
		{
			//AfxMessageBox(_T("WriteVariable"));
			long posOpenBrace = WSPSearchToken( pos -1, m_DocumentLength, szOpenBrace);
			
			//str.Format(_T("Pos SemiColon ...%d  " ), posSemiColon);
			//AfxMessageBox(str);
			
			int r = WSPParseClass( posClass -1, posOpenBrace);
			
			if( r == AIPI_ERROR && r == NOT_FOUND )
			{
				m_bFlagWriteClass = true;
				
				
			}
		
			 
		}
		
		
		int r = WSPHandleClassOpenBrace( pos);
		//str.Format(_T("r...%d  " ), r);
		//AfxMessageBox(str);

		if ( r != AIPI_ERROR )
		{
			m_bFlagWriteError = false;
		}
		else
		{
			//AfxMessageBox(_T("WriteRule Error"));
			m_bFlagWriteError = true;
		}
		
		m_bFlagWriteClass = false;
		

		
	}

}



void CAIPIEditorView::WSPWriteQuery(long pos)
{
	CScintillaCtrl& rCtrl = GetCtrl();
	LPSTR szEqual = "=";
	LPSTR szKeyWord = "SQLQUERY";

	CString str;
	if( m_iModificationType == INSERTTEXT )
	{
		int S = 83;
		int Q = 81;
		int L = 76;
		int U = 85;
		int E = 69;
		int R = 82;
		int Y = 89;
		
		long posQuery = WSPDetectKeyWord8( pos, S, Q, L, Q, U, E, R, Y);
		
		if( posQuery != NOT_FOUND )
		{
			//AfxMessageBox(_T("WriteQuery"));
			long posEqual = WSPSearchToken( pos -1, m_DocumentLength, szEqual);
			
			//str.Format(_T("Pos Equal ...%d  " ), posEqual);
			//AfxMessageBox(str);
			
			int r = WSPParseQuery( posQuery -1, posEqual);
			
			if( r == AIPI_ERROR && r == NOT_FOUND )
			{
				m_bFlagWriteQuery = true;
				
				
			}
		
			 
		}
		
		
		int r = WSPHandleQueryEqual( pos);
		//str.Format(_T("r...%d  " ), r);
		//AfxMessageBox(str);

		if ( r != AIPI_ERROR )
		{
			m_bFlagWriteError = false;
		}
		else
		{
			//AfxMessageBox(_T("WriteQuery Error"));
			m_bFlagWriteError = true;
		}
		
		m_bFlagWriteQuery = false;
		

		
	}

}







long CAIPIEditorView::WSPSearchNearestIdType( long nStartSel, long nEndSel)
{
	CString sType[7] = { "int", "char", "void", "short", "float", "long", "double" };
	long posType[7];

	
	//Search for INT:
	LPSTR szInt = "int";
	posType[0] = WSPSearchToken( nStartSel, nEndSel, szInt);

	//Search for CHAR:
	LPSTR szChar = "char";
	posType[1] = WSPSearchToken( nStartSel, nEndSel, szChar);

	//Search for VOID:
	LPSTR szVoid = "void";
	posType[2] = WSPSearchToken( nStartSel, nEndSel, szVoid);

	//Search for SHORT
	LPSTR szShort = "short";
	posType[3] = WSPSearchToken( nStartSel, nEndSel, szShort);

	//Search for FLOAT:
	LPSTR szFloat = "float";
	posType[4] = WSPSearchToken( nStartSel, nEndSel, szFloat);

	//Search for LONG:
	LPSTR szLong = "long";
	posType[5] = WSPSearchToken( nStartSel, nEndSel, szLong);

	//Search for DOUBLE:
	LPSTR szDouble = "double";
	posType[6] = WSPSearchToken( nStartSel, nEndSel, szDouble);

	int	posNearest = posType[0];
	CString typeNearest = sType[0];
	for( int i = 0; i<7; ++i )
	{
		if( posNearest < posType[i] )
		{
			posNearest = posType[i];
			typeNearest = sType[i];
			//AfxMessageBox(_T("entro"));
		}
	}

	m_sCurrentType = typeNearest;
	//AfxMessageBox(m_sCurrentType);
	
return posNearest;
	
}


void CAIPIEditorView::WSPWriteFunction(long pos)
{
	CScintillaCtrl& rCtrl = GetCtrl();
	LPSTR szOpenParenthesis = "(";
	LPSTR szCloseParenthesis = ")";

	CString str;
	if( m_iModificationType == INSERTTEXT )
	{
		
		int idType = WSPDetectIdentifierType( pos);
		

		if( idType != NOT_FOUND )
		{
			//AfxMessageBox(_T("WriteFunction"));
			long posCloseParenthesis = WSPSearchToken( pos -1, m_DocumentLength, szCloseParenthesis);
			long posOpenParenthesis = WSPSearchToken( posCloseParenthesis, 0, szOpenParenthesis);
			long posIdType = WSPSearchNearestIdType(posOpenParenthesis, 0);
	
			//str.Format(_T("Pos Close P...%d  " ), posCloseParenthesis);
			//AfxMessageBox(str);
			
			int r = WSPParseFunction( posIdType -1, posCloseParenthesis);
			
			if( r == AIPI_ERROR && r == NOT_FOUND )
			{
				m_bFlagWriteFunction = true;
				
				
			}
		
			 
		}
		
		
		int r = WSPHandleFunctionCloseParenthesis( pos);
		//str.Format(_T("r...%d  " ), r);
		//AfxMessageBox(str);

		if ( r != AIPI_ERROR )
		{
			m_bFlagWriteError = false;
		}
		else
		{
			//AfxMessageBox(_T("WriteRule Error"));
			m_bFlagWriteError = true;
		}
		
		m_bFlagWriteFunction = false;
		

		
	}


	
}



void CAIPIEditorView::WSPWriteVBSFunction(long pos)
{
	CScintillaCtrl& rCtrl = GetCtrl();
	LPSTR szOpenParenthesis = "(";
	LPSTR szCloseParenthesis = ")";
	LPSTR szKeyWord = "function";

	CString str;
	if( m_iModificationType == INSERTTEXT )
	{
		int F = 70;
		int u = 117;
		int n = 110;
		int c = 99;
		int t = 116;
		int i = 105;
		int o = 111;
		
		long posFunction = WSPDetectKeyWord8( pos, F, u, n, c, t, i, o, n);
		

		if( posFunction != NOT_FOUND )
		{
			//AfxMessageBox(_T("WriteFunction"));
			long posCloseParenthesis = WSPSearchToken( pos -1, m_DocumentLength, szCloseParenthesis);
			//str.Format(_T("Pos Close P...%d  " ), posCloseParenthesis);
			//AfxMessageBox(str);
			
			int r = WSPParseVBSFunction( posFunction -1, posCloseParenthesis);
			
			if( r == AIPI_ERROR && r == NOT_FOUND )
			{
				m_bFlagWriteVBSFunction = true;
			}
		
			 
		}
		
		
		int r = WSPHandleVBSFunctionCloseParenthesis( pos);
		//str.Format(_T("r...%d  " ), r);
		//AfxMessageBox(str);

		if ( r != AIPI_ERROR )
		{
			m_bFlagWriteError = false;
		}
		else
		{
			//AfxMessageBox(_T("WriteRule Error"));
			m_bFlagWriteError = true;
		}
		
		m_bFlagWriteVBSFunction = false;
		

		
	}


	
}



void CAIPIEditorView::WSPWriteVBSFUNCTION(long pos)
{
	CScintillaCtrl& rCtrl = GetCtrl();
	LPSTR szOpenParenthesis = "(";
	LPSTR szCloseParenthesis = ")";
	LPSTR szKeyWord = "function";

	CString str;
	if( m_iModificationType == INSERTTEXT )
	{
		int F = 70;
		int U = 85;
		int N = 78;
		int C = 67;
		int T = 84;
		int I = 73;
		int O = 79;

		long posFunction = WSPDetectKeyWord8( pos, F, U, N, C, T, I, O, N);
		

		if( posFunction != NOT_FOUND )
		{
			//AfxMessageBox(_T("WriteFunction"));
			long posCloseParenthesis = WSPSearchToken( pos -1, m_DocumentLength, szCloseParenthesis);
			//str.Format(_T("Pos Close P...%d  " ), posCloseParenthesis);
			//AfxMessageBox(str);
			
			int r = WSPParseVBSFunction( posFunction -1, posCloseParenthesis);
			
			if( r == AIPI_ERROR && r == NOT_FOUND )
			{
				m_bFlagWriteVBSFUNCTION = true;
				
				
			}
		
			 
		}
		
		
		int r = WSPHandleVBSFUNCTIONCloseParenthesis( pos);
		//str.Format(_T("r...%d  " ), r);
		//AfxMessageBox(str);

		if ( r != AIPI_ERROR )
		{
			m_bFlagWriteError = false;
		}
		else
		{
			//AfxMessageBox(_T("WriteRule Error"));
			m_bFlagWriteError = true;
		}
		
		m_bFlagWriteVBSFUNCTION = false;
		

		
	}


	
}


void CAIPIEditorView::WSPWriteJSFunction(long pos)
{
	CScintillaCtrl& rCtrl = GetCtrl();
	LPSTR szOpenParenthesis = "(";
	LPSTR szCloseParenthesis = ")";
	LPSTR szKeyWord = "function";

	CString str;
	if( m_iModificationType == INSERTTEXT )
	{
		int f = 102;
		int u = 117;
		int n = 110;
		int c = 99;
		int t = 116;
		int i = 105;
		int o = 111;
		
		long posFunction = WSPDetectKeyWord8( pos, f, u, n, c, t, i, o, n);
		

		if( posFunction != NOT_FOUND )
		{
			//AfxMessageBox(_T("WriteFunction"));
			long posCloseParenthesis = WSPSearchToken( pos -1, m_DocumentLength, szCloseParenthesis);
			//str.Format(_T("Pos Close P...%d  " ), posCloseParenthesis);
			//AfxMessageBox(str);
			
			int r = WSPParseJSFunction( posFunction -1, posCloseParenthesis);
			
			if( r == AIPI_ERROR && r == NOT_FOUND )
			{
				m_bFlagWriteJSFunction = true;
				
				
			}
		
			 
		}
		
		
		int r = WSPHandleJSFunctionCloseParenthesis( pos);
		//str.Format(_T("r...%d  " ), r);
		//AfxMessageBox(str);

		if ( r != AIPI_ERROR )
		{
			m_bFlagWriteError = false;
		}
		else
		{
			//AfxMessageBox(_T("WriteRule Error"));
			m_bFlagWriteError = true;
		}
		
		m_bFlagWriteJSFunction = false;
		

		
	}


	
}




void CAIPIEditorView::WSPWriteRule(long pos)
{
	CScintillaCtrl& rCtrl = GetCtrl();
	LPSTR szKeyWord = "RULE";
	LPSTR szOpenParenthesis = "(";
	LPSTR szCloseParenthesis = ")";
	LPSTR szDobleQuotation = "\"";
	

	CString str;
	if( m_iModificationType == INSERTTEXT )
	{
		int R = 82;
        int U = 85;
		int L = 76;
		int E = 69;
		long posRule = WSPDetectKeyWord4( pos, R, U, L, E);
		if( posRule != NOT_FOUND )
		{
			//AfxMessageBox(_T("WriteRule"));
			
			long posCloseParenthesis = WSPSearchToken( posRule, m_DocumentLength, szCloseParenthesis);
			//str.Format(_T("Pos Close P...%d  " ), posCloseParenthesis);
			//AfxMessageBox(str);
			int r = WSPParseRule( posRule -1, posCloseParenthesis);
			
			if( r == AIPI_ERROR && r == NOT_FOUND )
			{
				m_bFlagWriteRule = true;
			}
			

		
		}

		int r = WSPHandleRuleCloseParenthesis( pos);
		//str.Format(_T("r...%d  " ), r);
		//AfxMessageBox(str);

		if ( r != AIPI_ERROR )
		{
			m_bFlagWriteError = false;
		}
		else
		{
			//AfxMessageBox(_T("WriteRule Error"));
			m_bFlagWriteError = true;
		}
		
		m_bFlagWriteRule = false;
		
	}

}









long CAIPIEditorView::WSPDetectOpenComment(long pos)
{
	
	CString str;
	CScintillaCtrl& rCtrl = GetCtrl();

		
	
	if( m_iModificationType == BEFOREDELETE )
	{
		//AfxMessageBox(_T("BEFORE DELETE"));
		int prevSymbol = rCtrl.GetCharAt(pos -1);
		//str.Format(_T("Prev Symbol...%d  " ), prevSymbol);
		//AfxMessageBox(str);
		
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);

		int nextSymbol = rCtrl.GetCharAt(pos + 1);
		//str.Format(_T("Next Symbol...%d  " ), nextSymbol);
		//AfxMessageBox(str);

		int nextNextSymbol = rCtrl.GetCharAt(pos + 2);
		//str.Format(_T("Next Next Symbol...%d  " ), nextNextSymbol);
		//AfxMessageBox(str);
		
		
		
		//Check for open comments before delete text
		if( symbol == ASTERIC && prevSymbol == SLASH)
		{
			m_bFlagBeforeDelete = true;
			return pos -1;
			
		}
		if( symbol == SLASH && nextSymbol == ASTERIC )
		{
			m_bFlagBeforeDelete = true;
			return pos;
			
		}
		if( nextSymbol == SLASH && nextNextSymbol == ASTERIC )
		{
			m_bFlagBeforeDelete = true;
			return pos + 1;
			
		}

	}
	
	
	
	if( m_iModificationType == INSERTTEXT )
	{
		int prevSymbol = rCtrl.GetCharAt(pos -1);
		//str.Format(_T("Prev Symbol...%d  " ), prevSymbol);
		//AfxMessageBox(str);
		
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);

		int nextSymbol = rCtrl.GetCharAt(pos + 1);
		//str.Format(_T("Next Symbol...%d  " ), nextSymbol);
		//AfxMessageBox(str);

		
		
		//Check for open comments after insert text
		if( prevSymbol == SLASH && symbol == ASTERIC )
		{
			m_bFlagInsertText = true;
			return pos - 1;
		}
		if( symbol == SLASH && nextSymbol == ASTERIC )
		{
			m_bFlagInsertText = true;
			return pos;
		}

	}

return NOT_FOUND;

}


long CAIPIEditorView::WSPDetectCloseComment(long pos)
{
	CString str;
	CScintillaCtrl& rCtrl = GetCtrl();
	
	if( m_iModificationType == BEFOREDELETE )
	{
		//AfxMessageBox(_T("BEFORE DELETE"));
		int prevSymbol = rCtrl.GetCharAt(pos -1);
		//str.Format(_T("Prev Symbol...%d  " ), prevSymbol);
		//AfxMessageBox(str);
		
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);

		int nextSymbol = rCtrl.GetCharAt(pos + 1);
		//str.Format(_T("Next Symbol...%d  " ), nextSymbol);
		//AfxMessageBox(str);

		int nextNextSymbol = rCtrl.GetCharAt(pos + 2);
		//str.Format(_T("Next Next Symbol...%d  " ), nextNextSymbol);
		//AfxMessageBox(str);

		//Check for close comments 
		if( prevSymbol == ASTERIC && symbol == SLASH )
		{
			m_bFlagBeforeDelete = true;
			return pos -1;
			
		}
		if ( symbol == ASTERIC && nextSymbol == SLASH )
		{
			m_bFlagBeforeDelete = true;
			return pos;
			
		}
		if( nextSymbol == ASTERIC && nextNextSymbol == SLASH )
		{
			m_bFlagBeforeDelete = true;
			return pos + 1;
			
		}
	}
	
	if( m_iModificationType == INSERTTEXT )
	{
		//AfxMessageBox(_T("INSERT"));

		int prevSymbol = rCtrl.GetCharAt(pos -1);
		str.Format(_T("Prev Symbol...%d  " ), prevSymbol);
		//AfxMessageBox(str);
		
		
		int symbol = rCtrl.GetCharAt(pos);
		str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);
		
		int nextSymbol = rCtrl.GetCharAt(pos + 1);
		str.Format(_T("Next Symbol...%d  " ), nextSymbol);
		//AfxMessageBox(str);

		if( prevSymbol == ASTERIC && symbol == SLASH )
		{
			m_bFlagInsertText = true;
			return pos -1;
		}
		if( symbol == ASTERIC && nextSymbol == SLASH )
		{
			m_bFlagInsertText = true;
			return pos;
		}

	}

return NOT_FOUND;

}





long CAIPIEditorView::WSPDetectLineComment(long pos)
{
	
	CString str;

	CScintillaCtrl& rCtrl = GetCtrl();
	
	if( m_iModificationType == BEFOREDELETE )
	{
		//AfxMessageBox(_T("BEFORE DELETE"));

		int prevPrevSymbol = rCtrl.GetCharAt(pos - 2);
		//str.Format(_T("Prev Prev Symbol...%d  " ), prevPrevSymbol);
		//AfxMessageBox(str);

		int prevSymbol = rCtrl.GetCharAt(pos -1);
		//str.Format(_T("Prev Symbol...%d  " ), prevSymbol);
		//AfxMessageBox(str);
		
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);

		int nextSymbol = rCtrl.GetCharAt(pos + 1);
		//str.Format(_T("Next Symbol...%d  " ), nextSymbol);
		//AfxMessageBox(str);

		int nextNextSymbol = rCtrl.GetCharAt(pos + 2);
		//str.Format(_T("Next Next Symbol...%d  " ), nextNextSymbol);
		//AfxMessageBox(str);

		int nextNextNextSymbol = rCtrl.GetCharAt(pos + 3);
		//str.Format(_T("Next Next Next Symbol...%d  " ), nextNextNextSymbol);
		//AfxMessageBox(str);

		if( prevPrevSymbol != SLASH && prevSymbol == SLASH && symbol == SLASH && nextSymbol != SLASH )
		{
			m_bFlagBeforeDelete = true;
			return pos - 1;
		}
		if( prevSymbol != SLASH && symbol == SLASH && nextSymbol == SLASH && nextNextSymbol != SLASH )
		{
			m_bFlagBeforeDelete = true;
			return pos;
		}
		if( symbol != SLASH && nextSymbol == SLASH && nextNextSymbol == SLASH && nextNextNextSymbol != SLASH )
		{
			m_bFlagBeforeDelete = true;
			return pos + 1;
		}



	}
	
	if( m_iModificationType == INSERTTEXT )
	{
		int prevPrevSymbol = rCtrl.GetCharAt(pos - 2);
		//str.Format(_T("Prev Prev Symbol...%d  " ), prevPrevSymbol);
		//AfxMessageBox(str);
		
		int prevSymbol = rCtrl.GetCharAt(pos -1);
		//str.Format(_T("Prev Symbol...%d  " ), prevSymbol);
		//AfxMessageBox(str);
		
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);

		int nextSymbol = rCtrl.GetCharAt(pos + 1);
		//str.Format(_T("Next Symbol...%d  " ), nextSymbol);
		//AfxMessageBox(str);

		int nextNextSymbol = rCtrl.GetCharAt(pos + 2);
		//str.Format(_T("Next Next Symbol...%d  " ), nextNextSymbol);
		//AfxMessageBox(str);

		//int nextNextNextSymbol = rCtrl.GetCharAt(pos + 3);
		//str.Format(_T("Next Next Next Symbol...%d  " ), nextNextNextSymbol);
		//AfxMessageBox(str);

		if( prevPrevSymbol != SLASH && prevSymbol == SLASH && symbol == SLASH && nextSymbol != SLASH )
		{
			m_bFlagInsertText = true;
			return pos -1;	
		}
		if( prevSymbol != SLASH && symbol == SLASH && nextSymbol == SLASH && nextNextSymbol != SLASH )
		{
			m_bFlagInsertText = true;
			return pos;
		}
		/*
		if( symbol != SLASH && nextSymbol == SLASH && nextNextSymbol == SLASH && nextNextNextSymbol != SLASH )
		{
			return pos + 1;
		}
		*/

	}
	

return NOT_FOUND;
}


int CAIPIEditorView::WSPDetectIdentifierType(long pos)
{
	int posIdType = NOT_FOUND;
	
	//Identifiers types:
	//Type : INT
	int i = 105;
	int n = 110;
	int t = 116;
	posIdType = WSPDetectKeyWord3(pos, i, n, t);
	if ( posIdType != NOT_FOUND )
	{
		g_currentPos = posIdType;
		return C_INT; 
	}


	//Type : CHAR
	int c = 99;
	int h = 104;
	int a = 97;
	int r = 114;
	posIdType = WSPDetectKeyWord4(pos, c, h, a, r);
	if ( posIdType != NOT_FOUND )
	{
		g_currentPos = posIdType;
		return C_CHAR; 
	}

	//Type : LONG
	int l = 108;
	int o = 111;
	int g = 103;
	posIdType = WSPDetectKeyWord4(pos, l, o, n, g);
	if ( posIdType != NOT_FOUND )
	{
		g_currentPos = posIdType;
		return C_LONG; 
	}

	//TYPE : VOID
	int v = 118;
	int d = 100;
	posIdType = WSPDetectKeyWord4(pos, v, o, i, d);
	if ( posIdType != NOT_FOUND )
	{
		g_currentPos = posIdType;
		return C_VOID; 
	}

	//TYPE : SHORT
	int s = 115;
	posIdType = WSPDetectKeyWord5(pos, s, h, o, r, t);
	if ( posIdType != NOT_FOUND )
	{
		g_currentPos = posIdType;
		return C_SHORT; 
	}


	//TYPE : FLOAT
	int f = 102;
	posIdType = WSPDetectKeyWord5(pos, f, l, o, a, t);
	if ( posIdType != NOT_FOUND )
	{
		g_currentPos = posIdType;
		return C_FLOAT; 
	}

	//TYPE : DOUBLE
	int u = 117;
	int b = 98;
	int e = 101;
	posIdType = WSPDetectKeyWord6(pos, d, o, u, b, l, e);
	if ( posIdType != NOT_FOUND )
	{
		g_currentPos = posIdType;
		return C_DOUBLE; 
	}
	

return NOT_FOUND;
}




long CAIPIEditorView::WSPDetectKeyWord3( long pos, int l1, int l2, int l3)
{
	CString str;
	CScintillaCtrl& rCtrl = GetCtrl();
	
	if( m_iModificationType == BEFOREDELETE || m_iModificationType == INSERTTEXT )
	{
		int prevSymbol3 = rCtrl.GetCharAt( pos - 3 );
		//str.Format(_T("PrevSymbol3...%d  " ), prevSymbol3);
		//AfxMessageBox(str);
		
		int prevSymbol2 = rCtrl.GetCharAt( pos - 2);
		//str.Format(_T("PrevSymbol2...%d  " ), prevSymbol2);
		//AfxMessageBox(str);
		
		int prevSymbol1 = rCtrl.GetCharAt( pos - 1);
		//str.Format(_T("PrevSymbol1...%d  " ), prevSymbol1);
		//AfxMessageBox(str);
		
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);
		
		int nextSymbol1 = rCtrl.GetCharAt(pos + 1);
		//str.Format(_T("NextSymbol1...%d  " ), nextSymbol1);
		//AfxMessageBox(str);

		int nextSymbol2 = rCtrl.GetCharAt(pos + 2);
		//str.Format(_T("NextSymbol2...%d  " ), nextSymbol2);
		//AfxMessageBox(str);

		int nextSymbol3 = rCtrl.GetCharAt(pos + 3);
		//str.Format(_T("NextSymbol3...%d  " ), nextSymbol3);
		//AfxMessageBox(str);

		int nextSymbol4 = rCtrl.GetCharAt(pos + 4);
		//str.Format(_T("NextSymbol4...%d  " ), nextSymbol4);
		//AfxMessageBox(str);

		if(    (prevSymbol3 == SPACE || prevSymbol3 == NEW_LINE || prevSymbol3 == CARRIAGE_RETURN || prevSymbol3 == NUL || prevSymbol3 == HORIZONTAL_TAB)
			&& prevSymbol2 == l1 
			&& prevSymbol1 == l2 
			&& symbol == l3 
			&& (nextSymbol1 == SPACE || nextSymbol1 == NEW_LINE || nextSymbol1 == CARRIAGE_RETURN || nextSymbol1 ==  NUL || nextSymbol1 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			return pos - 2;
		}

		if(    (prevSymbol2 == SPACE || prevSymbol2 == NEW_LINE || prevSymbol2 == CARRIAGE_RETURN || prevSymbol2 == NUL || prevSymbol2 == HORIZONTAL_TAB)
			&& prevSymbol1 == l1 
			&& symbol == l2 
			&& nextSymbol1 == l3 
			&& (nextSymbol2 == SPACE || nextSymbol2 == NEW_LINE || nextSymbol2 == CARRIAGE_RETURN || nextSymbol2 ==  NUL || nextSymbol2 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			return pos - 1;
		}
			
		if(    (prevSymbol1 == SPACE || prevSymbol1 == NEW_LINE || prevSymbol1 == CARRIAGE_RETURN || prevSymbol1 == NUL || prevSymbol1 == HORIZONTAL_TAB)
			&& symbol == l1 
			&& nextSymbol1 == l2 
			&& nextSymbol2 == l3 
			&& (nextSymbol3 == SPACE || nextSymbol3 == NEW_LINE || nextSymbol3 == CARRIAGE_RETURN || nextSymbol3 ==  NUL || nextSymbol3 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			return pos;
		}
		if(    (symbol == SPACE || symbol == NEW_LINE || symbol == CARRIAGE_RETURN || symbol == NUL || symbol == HORIZONTAL_TAB)
			&& nextSymbol1 == l1 
			&& nextSymbol2 == l2 
			&& nextSymbol3 == l3 
			&& (nextSymbol4 == SPACE || nextSymbol4 == NEW_LINE || nextSymbol4 == CARRIAGE_RETURN || nextSymbol4 ==  NUL || nextSymbol4 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			if( isAlphaNumeric(prevSymbol1) )
			{
				return pos + 1;
			}
		}


	}

	
return NOT_FOUND;
}

long CAIPIEditorView::WSPDetectKeyWordEdit3( long pos, int l1, int l2, int l3)
{

	if( m_iModificationType == INSERTTEXT || m_iModificationType == BEFOREDELETE )
	{
		CString str;
		CScintillaCtrl& rCtrl = GetCtrl();
				
		int prevSymbol4 = rCtrl.GetCharAt( pos - 4 );
		//str.Format(_T("PrevSymbol4...%d  " ), prevSymbol4);
		//AfxMessageBox(str);
		
		
		int prevSymbol3 = rCtrl.GetCharAt( pos - 3 );
		//str.Format(_T("PrevSymbol3...%d  " ), prevSymbol3);
		//AfxMessageBox(str);
		
		int prevSymbol2 = rCtrl.GetCharAt( pos - 2);
		//str.Format(_T("PrevSymbol2...%d  " ), prevSymbol2);
		//AfxMessageBox(str);
		
		int prevSymbol1 = rCtrl.GetCharAt( pos - 1);
		//str.Format(_T("PrevSymbol1...%d  " ), prevSymbol1);
		//AfxMessageBox(str);
		
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);
		
		int nextSymbol1 = rCtrl.GetCharAt(pos + 1);
		//str.Format(_T("NextSymbol1...%d  " ), nextSymbol1);
		//AfxMessageBox(str);

		int nextSymbol2 = rCtrl.GetCharAt(pos + 2);
		//str.Format(_T("NextSymbol2...%d  " ), nextSymbol2);
		//AfxMessageBox(str);

		int nextSymbol3 = rCtrl.GetCharAt(pos + 3);
		//str.Format(_T("NextSymbol3...%d  " ), nextSymbol3);
		//AfxMessageBox(str);

		int nextSymbol4 = rCtrl.GetCharAt(pos + 4);
		//str.Format(_T("NextSymbol4...%d  " ), nextSymbol4);
		//AfxMessageBox(str);
	
		//Check cases of inserting a wrong caracter between the keyword
			if( prevSymbol1 == l3 )
			{
			   //AfxMessageBox(_T("Case prevS = l3"));
				//Case letter l3
				if(	prevSymbol2 == l2 && prevSymbol3 == l1 
				&&  (prevSymbol4 == SPACE || prevSymbol4 == NEW_LINE || prevSymbol4 == CARRIAGE_RETURN || prevSymbol4 ==  NUL || prevSymbol4 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					return pos-3; 
				}
			}
            else if( prevSymbol1 == l2 )
			{
				//AfxMessageBox(_T("Case prevS = l2"));
				//Case letter l2
				if(	prevSymbol2 == l1   
				&&  (prevSymbol3 == SPACE || prevSymbol3 == NEW_LINE || prevSymbol3 == CARRIAGE_RETURN || prevSymbol3 ==  NUL || prevSymbol3 == HORIZONTAL_TAB )
				&& nextSymbol1 == l3
				&& (nextSymbol2 == SPACE || nextSymbol2 == NEW_LINE || nextSymbol2 == CARRIAGE_RETURN || nextSymbol2 ==  NUL || nextSymbol2 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					return pos-2; 
				}
			}
			
			else if ( prevSymbol1 == l1 )
			{
				//AfxMessageBox(_T("Case prevS = l1"));
				
				//Case letter l1
				if(	(prevSymbol2 == SPACE || prevSymbol2 == NEW_LINE || prevSymbol2 == CARRIAGE_RETURN || prevSymbol2 ==  NUL || prevSymbol2 == HORIZONTAL_TAB )
				&& nextSymbol1 == l2 && nextSymbol2 == l3
				&& (nextSymbol3 == SPACE || nextSymbol3 == NEW_LINE || nextSymbol3 == CARRIAGE_RETURN || nextSymbol3 ==  NUL || nextSymbol3 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					return pos- 1; 
				}
			}
			if ( prevSymbol1 != SPACE || prevSymbol1 != NEW_LINE || prevSymbol1 != CARRIAGE_RETURN || prevSymbol1 != NUL || prevSymbol1 != HORIZONTAL_TAB )
			{
				//AfxMessageBox(_T("Case prevS = Space"));
				
				//Case letter empty
				if( nextSymbol1 == l1 && nextSymbol2 == l2 && nextSymbol3 == l3
				&& (nextSymbol4 == SPACE || nextSymbol4 == NEW_LINE || nextSymbol4 == CARRIAGE_RETURN || nextSymbol4 ==  NUL || nextSymbol4 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					if( isAlphaNumeric(prevSymbol2) )
					{
						return pos + 1;
					}
				}
			}

				
		
	}

	

return NOT_FOUND;
}


long CAIPIEditorView::WSPDetectKeyWord4( long pos, int l1, int l2, int l3, int l4)
{
	if( m_iModificationType == BEFOREDELETE || m_iModificationType == INSERTTEXT )
	{
		
		CString str;
		CScintillaCtrl& rCtrl = GetCtrl();
				
		int prevSymbol4 = rCtrl.GetCharAt( pos - 4 );
		//str.Format(_T("PrevSymbol4...%d  " ), prevSymbol4);
		//AfxMessageBox(str);
		
		
		int prevSymbol3 = rCtrl.GetCharAt( pos - 3 );
		//str.Format(_T("PrevSymbol3...%d  " ), prevSymbol3);
		//AfxMessageBox(str);
		
		int prevSymbol2 = rCtrl.GetCharAt( pos - 2);
		//str.Format(_T("PrevSymbol2...%d  " ), prevSymbol2);
		//AfxMessageBox(str);
		
		int prevSymbol1 = rCtrl.GetCharAt( pos - 1);
		//str.Format(_T("PrevSymbol1...%d  " ), prevSymbol1);
		//AfxMessageBox(str);
		
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);
		
		int nextSymbol1 = rCtrl.GetCharAt(pos + 1);
		//str.Format(_T("NextSymbol1...%d  " ), nextSymbol1);
		//AfxMessageBox(str);

		int nextSymbol2 = rCtrl.GetCharAt(pos + 2);
		//str.Format(_T("NextSymbol2...%d  " ), nextSymbol2);
		//AfxMessageBox(str);

		int nextSymbol3 = rCtrl.GetCharAt(pos + 3);
		//str.Format(_T("NextSymbol3...%d  " ), nextSymbol3);
		//AfxMessageBox(str);

		int nextSymbol4 = rCtrl.GetCharAt(pos + 4);
		//str.Format(_T("NextSymbol4...%d  " ), nextSymbol4);
		//AfxMessageBox(str);


		int nextSymbol5 = rCtrl.GetCharAt(pos + 5);
		//str.Format(_T("NextSymbol5...%d  " ), nextSymbol5);
		//AfxMessageBox(str);

		
		if(    (prevSymbol4 == SPACE || prevSymbol4 == NEW_LINE || prevSymbol4 == CARRIAGE_RETURN || prevSymbol4 == NUL || prevSymbol4 == HORIZONTAL_TAB)
			&& prevSymbol3 == l1 
			&& prevSymbol2 == l2 
			&& prevSymbol1 == l3 
			&& symbol == l4 
			&& (nextSymbol1 == SPACE || nextSymbol1 == NEW_LINE || nextSymbol1 == CARRIAGE_RETURN || nextSymbol1 ==  NUL || nextSymbol1 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
		
			return pos -3;
		}

		if(    (prevSymbol3 == SPACE || prevSymbol3 == NEW_LINE || prevSymbol3 == CARRIAGE_RETURN || prevSymbol3 == NUL || prevSymbol3 == HORIZONTAL_TAB)
			&& prevSymbol2 == l1 
			&& prevSymbol1 == l2 
			&& symbol == l3 
			&& nextSymbol1 == l4 
			&& (nextSymbol2 == SPACE || nextSymbol2 == NEW_LINE || nextSymbol2 == CARRIAGE_RETURN || nextSymbol2 ==  NUL || nextSymbol2 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			
			return pos - 2;
		}
			
		if(    (prevSymbol2 == SPACE || prevSymbol2 == NEW_LINE || prevSymbol2 == CARRIAGE_RETURN || prevSymbol2 == NUL || prevSymbol2 == HORIZONTAL_TAB)
			&& prevSymbol1 == l1 
			&& symbol == l2 
			&& nextSymbol1 == l3 
			&& nextSymbol2 == l4 
			&& (nextSymbol3 == SPACE || nextSymbol3 == NEW_LINE || nextSymbol3 == CARRIAGE_RETURN || nextSymbol3 ==  NUL || nextSymbol3 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			
			return pos - 1;
		}

		if(    (prevSymbol1 == SPACE || prevSymbol1 == NEW_LINE || prevSymbol1 == CARRIAGE_RETURN || prevSymbol1 == NUL || prevSymbol1 == HORIZONTAL_TAB)
			&& symbol == l1 
			&& nextSymbol1 == l2 
			&& nextSymbol2 == l3 
			&& nextSymbol3 == l4 
			&& (nextSymbol4 == SPACE || nextSymbol4 == NEW_LINE || nextSymbol4 == CARRIAGE_RETURN || nextSymbol4 ==  NUL || nextSymbol4 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
		
			return pos;
		}

		if(    (symbol == SPACE || symbol == NEW_LINE || symbol == CARRIAGE_RETURN || symbol == NUL || symbol == HORIZONTAL_TAB)
			&& nextSymbol1 == l1 
			&& nextSymbol2 == l2 
			&& nextSymbol3 == l3 
			&& nextSymbol4 == l4 
			&& (nextSymbol5 == SPACE || nextSymbol5 == NEW_LINE || nextSymbol5 == CARRIAGE_RETURN || nextSymbol5 ==  NUL || nextSymbol5 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			if( isAlphaNumeric(prevSymbol1) )
			{
				return pos + 1;
			}
		}


	}

return NOT_FOUND;
}


long CAIPIEditorView::WSPDetectKeyWordEdit4( long pos, int l1, int l2, int l3, int l4)
{
	
	
	if( m_iModificationType == INSERTTEXT || m_iModificationType == BEFOREDELETE )
	{
		CString str;
		CScintillaCtrl& rCtrl = GetCtrl();
		
		int prevSymbol5 = rCtrl.GetCharAt( pos - 5 );
		//str.Format(_T("PrevSymbol5...%d  " ), prevSymbol5);
		//AfxMessageBox(str);
		
		
		int prevSymbol4 = rCtrl.GetCharAt( pos - 4 );
		//str.Format(_T("PrevSymbol4...%d  " ), prevSymbol4);
		//AfxMessageBox(str);
		
		
		int prevSymbol3 = rCtrl.GetCharAt( pos - 3 );
		//str.Format(_T("PrevSymbol3...%d  " ), prevSymbol3);
		//AfxMessageBox(str);
		
		int prevSymbol2 = rCtrl.GetCharAt( pos - 2);
		//str.Format(_T("PrevSymbol2...%d  " ), prevSymbol2);
		//AfxMessageBox(str);
		
		int prevSymbol1 = rCtrl.GetCharAt( pos - 1);
		//str.Format(_T("PrevSymbol1...%d  " ), prevSymbol1);
		//AfxMessageBox(str);
		
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);
		
		int nextSymbol1 = rCtrl.GetCharAt(pos + 1);
		//str.Format(_T("NextSymbol1...%d  " ), nextSymbol1);
		//AfxMessageBox(str);
		
		int nextSymbol2 = rCtrl.GetCharAt(pos + 2);
		//str.Format(_T("NextSymbol2...%d  " ), nextSymbol2);
		//AfxMessageBox(str);
		
		int nextSymbol3 = rCtrl.GetCharAt(pos + 3);
		//str.Format(_T("NextSymbol3...%d  " ), nextSymbol3);
		//AfxMessageBox(str);
		
		int nextSymbol4 = rCtrl.GetCharAt(pos + 4);
		//str.Format(_T("NextSymbol4...%d  " ), nextSymbol4);
		//AfxMessageBox(str);
		
		
		int nextSymbol5 = rCtrl.GetCharAt(pos + 5);
		//str.Format(_T("NextSymbol5...%d  " ), nextSymbol5);
		//AfxMessageBox(str);
		
		//Check cases of inserting a wrong caracter between the keyword
		if( prevSymbol1 == l4 )
		{
			//AfxMessageBox(_T("Case prevS = l4"));
			//Case letter l4
			if(	prevSymbol2 == l3 && prevSymbol3 == l2 && prevSymbol4 == l1 
				&&  (prevSymbol5 == SPACE || prevSymbol5 == NEW_LINE || prevSymbol5 == CARRIAGE_RETURN || prevSymbol5 ==  NUL || prevSymbol5 == HORIZONTAL_TAB )
				)
			{	  
				//AfxMessageBox(_T("Detected"));
				return pos-3; 
			}
		}
		
		
		if( prevSymbol1 == l3 )
		{
			//AfxMessageBox(_T("Case prevS = l3"));
			//Case letter l3
			if(	prevSymbol2 == l2 && prevSymbol3 == l1  
				&&  (prevSymbol4 == SPACE || prevSymbol4 == NEW_LINE || prevSymbol4 == CARRIAGE_RETURN || prevSymbol4 ==  NUL || prevSymbol4 == HORIZONTAL_TAB )
				&& nextSymbol1 == l4
				&& (nextSymbol2 == SPACE || nextSymbol2 == NEW_LINE || nextSymbol2 == CARRIAGE_RETURN || nextSymbol2 ==  NUL || nextSymbol2 == HORIZONTAL_TAB )
				)
			{	  
				//AfxMessageBox(_T("Detected"));
				return pos-2; 
			}
		}
		if( prevSymbol1 == l2 )
		{
			//AfxMessageBox(_T("Case prevS = l2"));
			//Case letter l2
			if(	prevSymbol2 == l1  
				&&  (prevSymbol3 == SPACE || prevSymbol3 == NEW_LINE || prevSymbol3 == CARRIAGE_RETURN || prevSymbol3 ==  NUL || prevSymbol3 == HORIZONTAL_TAB )
				&& nextSymbol1 == l3 && nextSymbol2 == l4
				&& (nextSymbol3 == SPACE || nextSymbol3 == NEW_LINE || nextSymbol3 == CARRIAGE_RETURN || nextSymbol3 ==  NUL || nextSymbol3 == HORIZONTAL_TAB )
				)
			{	  
				//AfxMessageBox(_T("Detected"));
				return pos-2; 
			}
		}
		
		if ( prevSymbol1 == l1 )
		{
			//AfxMessageBox(_T("Case prevS = l1"));
			
			//Case letter l1
			if(	(prevSymbol2 == SPACE || prevSymbol2 == NEW_LINE || prevSymbol2 == CARRIAGE_RETURN || prevSymbol2 ==  NUL || prevSymbol2 == HORIZONTAL_TAB )
				&& nextSymbol1 == l2 && nextSymbol2 == l3 && nextSymbol3 == l4 
				&& (nextSymbol4 == SPACE || nextSymbol4 == NEW_LINE || nextSymbol4 == CARRIAGE_RETURN || nextSymbol4 ==  NUL || nextSymbol4 == HORIZONTAL_TAB )
				)
			{	  
				//AfxMessageBox(_T("Detected"));
				return pos-1; 
			}
		}
		
		if ( prevSymbol1 != SPACE || prevSymbol1 != NEW_LINE || prevSymbol1 != CARRIAGE_RETURN || prevSymbol1 != NUL || prevSymbol1 != HORIZONTAL_TAB )
		{
			//AfxMessageBox(_T("Case prevS = Space"));
			
			//Case letter empty
			if( nextSymbol1 == l1 && nextSymbol2 == l2 && nextSymbol3 == l3 && nextSymbol4 == l4  
				&& (nextSymbol5 == SPACE || nextSymbol5 == NEW_LINE || nextSymbol5 == CARRIAGE_RETURN || nextSymbol5 ==  NUL || nextSymbol5 == HORIZONTAL_TAB )
				)
			{	  
				//AfxMessageBox(_T("Detected"));
				if( isAlphaNumeric(prevSymbol2) )
				{
					return pos + 1;
				}
			}
		}
		
		
		
		
		
		
	}
	
	
	return NOT_FOUND;
}





long CAIPIEditorView::WSPDetectKeyWord5( long pos, int l1, int l2, int l3, int l4 , int l5 )
{
	CString str;
	CScintillaCtrl& rCtrl = GetCtrl();
		
	if( m_iModificationType == BEFOREDELETE || m_iModificationType == INSERTTEXT )
	{
		
		int prevSymbol5 = rCtrl.GetCharAt( pos - 5 );
		//str.Format(_T("PrevSymbol5...%d  " ), prevSymbol5);
		//AfxMessageBox(str);
		
		
		int prevSymbol4 = rCtrl.GetCharAt( pos - 4 );
		//str.Format(_T("PrevSymbol4...%d  " ), prevSymbol4);
		//AfxMessageBox(str);
		
		
		int prevSymbol3 = rCtrl.GetCharAt( pos - 3 );
		//str.Format(_T("PrevSymbol3...%d  " ), prevSymbol3);
		//AfxMessageBox(str);
		
		int prevSymbol2 = rCtrl.GetCharAt( pos - 2);
		//str.Format(_T("PrevSymbol2...%d  " ), prevSymbol2);
		//AfxMessageBox(str);
		
		int prevSymbol1 = rCtrl.GetCharAt( pos - 1);
		//str.Format(_T("PrevSymbol1...%d  " ), prevSymbol1);
		//AfxMessageBox(str);
		
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);
		
		int nextSymbol1 = rCtrl.GetCharAt(pos + 1);
		//str.Format(_T("NextSymbol1...%d  " ), nextSymbol1);
		//AfxMessageBox(str);

		int nextSymbol2 = rCtrl.GetCharAt(pos + 2);
		//str.Format(_T("NextSymbol2...%d  " ), nextSymbol2);
		//AfxMessageBox(str);

		int nextSymbol3 = rCtrl.GetCharAt(pos + 3);
		//str.Format(_T("NextSymbol3...%d  " ), nextSymbol3);
		//AfxMessageBox(str);

		int nextSymbol4 = rCtrl.GetCharAt(pos + 4);
		//str.Format(_T("NextSymbol4...%d  " ), nextSymbol4);
		//AfxMessageBox(str);


		int nextSymbol5 = rCtrl.GetCharAt(pos + 5);
		//str.Format(_T("NextSymbol5...%d  " ), nextSymbol5);
		//AfxMessageBox(str);

		int nextSymbol6 = rCtrl.GetCharAt(pos + 6);
		//str.Format(_T("NextSymbol6...%d  " ), nextSymbol6);
		//AfxMessageBox(str);
		
		if(    (prevSymbol5 == SPACE || prevSymbol5 == NEW_LINE || prevSymbol5 == CARRIAGE_RETURN || prevSymbol5 == NUL || prevSymbol5 == HORIZONTAL_TAB)
			&& prevSymbol4 == l1 
			&& prevSymbol3 == l2 
			&& prevSymbol2 == l3 
			&& prevSymbol1 == l4 
			&& symbol == l5 
			&& (nextSymbol1 == SPACE || nextSymbol1 == NEW_LINE || nextSymbol1 == CARRIAGE_RETURN || nextSymbol1 ==  NUL || nextSymbol1 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			return pos - 4;
		}
			
		if(    (prevSymbol4 == SPACE || prevSymbol4 == NEW_LINE || prevSymbol4 == CARRIAGE_RETURN || prevSymbol4 == NUL || prevSymbol4 == HORIZONTAL_TAB)
			&& prevSymbol3 == l1
			&& prevSymbol2 == l2
			&& prevSymbol1 == l3
			&& symbol == l4 
			&& nextSymbol1 == l5 
			&& (nextSymbol2 == SPACE || nextSymbol2 == NEW_LINE || nextSymbol2 == CARRIAGE_RETURN || nextSymbol2 ==  NUL || nextSymbol2 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			return pos - 3;
		}

		if(    (prevSymbol3 == SPACE || prevSymbol3 == NEW_LINE || prevSymbol3 == CARRIAGE_RETURN || prevSymbol3 == NUL || prevSymbol3 == HORIZONTAL_TAB)
			&& prevSymbol2 == l1
			&& prevSymbol1 == l2
			&& symbol == l3 
			&& nextSymbol1 == l4 
			&& nextSymbol2 == l5 
			&& (nextSymbol3 == SPACE || nextSymbol3 == NEW_LINE || nextSymbol3 == CARRIAGE_RETURN || nextSymbol3 ==  NUL || nextSymbol3 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			return pos -2;
		}

		if(    (prevSymbol2 == SPACE || prevSymbol2 == NEW_LINE || prevSymbol2 == CARRIAGE_RETURN || prevSymbol2 == NUL || prevSymbol2 == HORIZONTAL_TAB)
			&& prevSymbol1 == l1
			&& symbol == l2 
			&& nextSymbol1 == l3 
			&& nextSymbol2 == l4 
			&& nextSymbol3 == l5 
			&& (nextSymbol4 == SPACE || nextSymbol4 == NEW_LINE || nextSymbol4 == CARRIAGE_RETURN || nextSymbol4 ==  NUL || nextSymbol4 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			return pos - 1;
		}

		if(    (prevSymbol1 == SPACE || prevSymbol1 == NEW_LINE || prevSymbol1 == CARRIAGE_RETURN || prevSymbol1 == NUL || prevSymbol1 == HORIZONTAL_TAB)
			&& symbol == l1 
			&& nextSymbol1 == l2 
			&& nextSymbol2 == l3 
			&& nextSymbol3 == l4 
			&& nextSymbol4 == l5
			&& (nextSymbol5 == SPACE || nextSymbol5 == NEW_LINE || nextSymbol5 == CARRIAGE_RETURN || nextSymbol5 ==  NUL || nextSymbol5 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			return pos;
		}

		if(    (symbol == SPACE || symbol == NEW_LINE || symbol == CARRIAGE_RETURN || symbol == NUL || symbol == HORIZONTAL_TAB)
			&& nextSymbol1 == l1 
			&& nextSymbol2 == l2 
			&& nextSymbol3 == l3 
			&& nextSymbol4 == l4 
			&& nextSymbol5 == l5 
			&& (nextSymbol6 == SPACE || nextSymbol6 == NEW_LINE || nextSymbol6 == CARRIAGE_RETURN || nextSymbol6 ==  NUL || nextSymbol6 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			if( isAlphaNumeric(prevSymbol1) )
			{
				return pos + 1;
			}
		}
	}


return NOT_FOUND;
}



long CAIPIEditorView::WSPDetectKeyWordEdit5( long pos, int l1, int l2, int l3, int l4, int l5)
{
	if( m_iModificationType == INSERTTEXT || m_iModificationType == BEFOREDELETE )
	{
		CString str;
		CScintillaCtrl& rCtrl = GetCtrl();
				
		int prevSymbol6 = rCtrl.GetCharAt( pos - 6 );
		//str.Format(_T("PrevSymbol6...%d  " ), prevSymbol6);
		//AfxMessageBox(str);
		

		int prevSymbol5 = rCtrl.GetCharAt( pos - 5 );
		//str.Format(_T("PrevSymbol5...%d  " ), prevSymbol5);
		//AfxMessageBox(str);
		
		
		int prevSymbol4 = rCtrl.GetCharAt( pos - 4 );
		//str.Format(_T("PrevSymbol4...%d  " ), prevSymbol4);
		//AfxMessageBox(str);
		
		
		int prevSymbol3 = rCtrl.GetCharAt( pos - 3 );
		//str.Format(_T("PrevSymbol3...%d  " ), prevSymbol3);
		//AfxMessageBox(str);
		
		int prevSymbol2 = rCtrl.GetCharAt( pos - 2);
		//str.Format(_T("PrevSymbol2...%d  " ), prevSymbol2);
		//AfxMessageBox(str);
		
		int prevSymbol1 = rCtrl.GetCharAt( pos - 1);
		//str.Format(_T("PrevSymbol1...%d  " ), prevSymbol1);
		//AfxMessageBox(str);
		
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);
		
		int nextSymbol1 = rCtrl.GetCharAt(pos + 1);
		//str.Format(_T("NextSymbol1...%d  " ), nextSymbol1);
		//AfxMessageBox(str);

		int nextSymbol2 = rCtrl.GetCharAt(pos + 2);
		//str.Format(_T("NextSymbol2...%d  " ), nextSymbol2);
		//AfxMessageBox(str);

		int nextSymbol3 = rCtrl.GetCharAt(pos + 3);
		//str.Format(_T("NextSymbol3...%d  " ), nextSymbol3);
		//AfxMessageBox(str);

		int nextSymbol4 = rCtrl.GetCharAt(pos + 4);
		//str.Format(_T("NextSymbol4...%d  " ), nextSymbol4);
		//AfxMessageBox(str);


		int nextSymbol5 = rCtrl.GetCharAt(pos + 5);
		//str.Format(_T("NextSymbol5...%d  " ), nextSymbol5);
		//AfxMessageBox(str);

		int nextSymbol6 = rCtrl.GetCharAt(pos + 6);
		//str.Format(_T("NextSymbol6...%d  " ), nextSymbol6);
		//AfxMessageBox(str);

		//Check cases of inserting a wrong caracter between the keyword
		
            if( prevSymbol1 == l5 )
			{
				//AfxMessageBox(_T("Case prevS = l5"));
				//Case letter l5
				if(	prevSymbol2 == l4 && prevSymbol3 == l3 && prevSymbol4 == l2 && prevSymbol5 == l1 
				&&  (prevSymbol6 == SPACE || prevSymbol6 == NEW_LINE || prevSymbol6 == CARRIAGE_RETURN || prevSymbol6 ==  NUL || prevSymbol6 == HORIZONTAL_TAB )
				&& (nextSymbol1 == SPACE || nextSymbol1 == NEW_LINE || nextSymbol1 == CARRIAGE_RETURN || nextSymbol1 ==  NUL || nextSymbol1 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					return pos-5; 
				}
			}
			
			if( prevSymbol1 == l4 )
			{
				//AfxMessageBox(_T("Case prevS = l4"));
				//Case letter l4
				if(	prevSymbol2 == l3  && prevSymbol3 == l2 && prevSymbol4 == l1
				&&  (prevSymbol5 == SPACE || prevSymbol5 == NEW_LINE || prevSymbol5 == CARRIAGE_RETURN || prevSymbol5 ==  NUL || prevSymbol5 == HORIZONTAL_TAB )
				&& nextSymbol1 == l5
				&& (nextSymbol2 == SPACE || nextSymbol2 == NEW_LINE || nextSymbol2 == CARRIAGE_RETURN || nextSymbol2 ==  NUL || nextSymbol2 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					return pos-2; 
				}
			}
			
			if( prevSymbol1 == l3 )
			{
				//AfxMessageBox(_T("Case prevS = o"));
				//Case letter o
				if(	prevSymbol2 == l2  && prevSymbol3 == l1 
				&&  (prevSymbol4 == SPACE || prevSymbol4 == NEW_LINE || prevSymbol4 == CARRIAGE_RETURN || prevSymbol4 ==  NUL || prevSymbol4 == HORIZONTAL_TAB )
				&& nextSymbol1 == l4 && nextSymbol2 == l5
				&& (nextSymbol3 == SPACE || nextSymbol3 == NEW_LINE || nextSymbol3 == CARRIAGE_RETURN || nextSymbol3 ==  NUL || nextSymbol3 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					return pos-3; 
				}
			}
			
			if( prevSymbol1 == l2 )
			{
				//AfxMessageBox(_T("Case prevS = l2"));
				//Case letter 12
				if(	prevSymbol2 == l1 
				&&  (prevSymbol3 == SPACE || prevSymbol3 == NEW_LINE || prevSymbol3 == CARRIAGE_RETURN || prevSymbol3 ==  NUL || prevSymbol3 == HORIZONTAL_TAB )
				&& nextSymbol1 == l3 && nextSymbol2 == l4 && nextSymbol3 == l5
				&& (nextSymbol4 == SPACE || nextSymbol4 == NEW_LINE || nextSymbol4 == CARRIAGE_RETURN || nextSymbol4 ==  NUL || nextSymbol4 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					return pos-2; 
				}
			}
			
			if ( prevSymbol1 == l1 )
			{
				//AfxMessageBox(_T("Case prevS = l1"));
				
				//Case letter l1
				if(	(prevSymbol2 == SPACE || prevSymbol2 == NEW_LINE || prevSymbol2 == CARRIAGE_RETURN || prevSymbol2 ==  NUL || prevSymbol2 == HORIZONTAL_TAB )
				&& nextSymbol1 == l2 && nextSymbol2 == l3 && nextSymbol3 == l4 && nextSymbol4 == l5
				&& (nextSymbol5 == SPACE || nextSymbol5 == NEW_LINE || nextSymbol5 == CARRIAGE_RETURN || nextSymbol5 ==  NUL || nextSymbol5 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					return pos-1; 
				}
			}


			if ( prevSymbol1 != SPACE || prevSymbol1 != NEW_LINE || prevSymbol1 != CARRIAGE_RETURN || prevSymbol1 != NUL || prevSymbol1 != HORIZONTAL_TAB )
			{
				//AfxMessageBox(_T("Case prevS = Space"));
				
				//Case letter empty
				if( nextSymbol1 == l1 && nextSymbol2 == l2 && nextSymbol3 == l3 && nextSymbol4 == l4 && nextSymbol5 == l5 
				&& (nextSymbol6 == SPACE || nextSymbol6 == NEW_LINE || nextSymbol6 == CARRIAGE_RETURN || nextSymbol6 ==  NUL || nextSymbol6 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					if( isAlphaNumeric(prevSymbol2) )
					{
						return pos + 1;
					}
				}
			}
		
		
		
	}


return NOT_FOUND;
}





long CAIPIEditorView::WSPDetectKeyWord6( long pos, int l1, int l2, int l3, int l4, int l5, int l6)
{
	
	if( m_iModificationType == BEFOREDELETE || m_iModificationType == INSERTTEXT )
	{
		CString str;
		CScintillaCtrl& rCtrl = GetCtrl();
	
		int prevSymbol6 = rCtrl.GetCharAt( pos - 6 );
		//str.Format(_T("PrevSymbol6...%d  " ), prevSymbol6);
		//AfxMessageBox(str);
		
		
		int prevSymbol5 = rCtrl.GetCharAt( pos - 5 );
		//str.Format(_T("PrevSymbol5...%d  " ), prevSymbol5);
		//AfxMessageBox(str);
		
		
		int prevSymbol4 = rCtrl.GetCharAt( pos - 4 );
		//str.Format(_T("PrevSymbol4...%d  " ), prevSymbol4);
		//AfxMessageBox(str);
		
		
		int prevSymbol3 = rCtrl.GetCharAt( pos - 3 );
		//str.Format(_T("PrevSymbol3...%d  " ), prevSymbol3);
		//AfxMessageBox(str);
		
		int prevSymbol2 = rCtrl.GetCharAt( pos - 2);
		//str.Format(_T("PrevSymbol2...%d  " ), prevSymbol2);
		//AfxMessageBox(str);
		
		int prevSymbol1 = rCtrl.GetCharAt( pos - 1);
		//str.Format(_T("PrevSymbol1...%d  " ), prevSymbol1);
		//AfxMessageBox(str);
		
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);
		
		int nextSymbol1 = rCtrl.GetCharAt(pos + 1);
		//str.Format(_T("NextSymbol1...%d  " ), nextSymbol1);
		//AfxMessageBox(str);

		int nextSymbol2 = rCtrl.GetCharAt(pos + 2);
		//str.Format(_T("NextSymbol2...%d  " ), nextSymbol2);
		//AfxMessageBox(str);

		int nextSymbol3 = rCtrl.GetCharAt(pos + 3);
		//str.Format(_T("NextSymbol3...%d  " ), nextSymbol3);
		//AfxMessageBox(str);

		int nextSymbol4 = rCtrl.GetCharAt(pos + 4);
		//str.Format(_T("NextSymbol4...%d  " ), nextSymbol4);
		//AfxMessageBox(str);


		int nextSymbol5 = rCtrl.GetCharAt(pos + 5);
		//str.Format(_T("NextSymbol5...%d  " ), nextSymbol5);
		//AfxMessageBox(str);

		int nextSymbol6 = rCtrl.GetCharAt(pos + 6);
		//str.Format(_T("NextSymbol6...%d  " ), nextSymbol6);
		//AfxMessageBox(str);
		
		int nextSymbol7 = rCtrl.GetCharAt(pos + 7);
		//str.Format(_T("NextSymbol7...%d  " ), nextSymbol7);
		//AfxMessageBox(str);



		
		if(    (prevSymbol6 == SPACE || prevSymbol6 == NEW_LINE || prevSymbol6 == CARRIAGE_RETURN || prevSymbol6 == NUL || prevSymbol6 == HORIZONTAL_TAB)
			&& prevSymbol5 == l1
			&& prevSymbol4 == l2
			&& prevSymbol3 == l3
			&& prevSymbol2 == l4 
			&& prevSymbol1 == l5 
			&& symbol == l6 
			&& (nextSymbol1 == SPACE || nextSymbol1 == NEW_LINE || nextSymbol1 == CARRIAGE_RETURN || nextSymbol1 ==  NUL || nextSymbol1 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			return pos - 5;
		}

		if(    (prevSymbol5 == SPACE || prevSymbol5 == NEW_LINE || prevSymbol5 == CARRIAGE_RETURN || prevSymbol5 == NUL || prevSymbol5 == HORIZONTAL_TAB)
			&& prevSymbol4 == l1 
			&& prevSymbol3 == l2 
			&& prevSymbol2 == l3 
			&& prevSymbol1 == l4 
			&& symbol == l5 
			&& nextSymbol1 == l6 
			&& (nextSymbol2 == SPACE || nextSymbol2 == NEW_LINE || nextSymbol2 == CARRIAGE_RETURN || nextSymbol2 ==  NUL || nextSymbol2 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			return pos - 4;
		}
			
		if(    (prevSymbol4 == SPACE || prevSymbol4 == NEW_LINE || prevSymbol4 == CARRIAGE_RETURN || prevSymbol4 == NUL || prevSymbol4 == HORIZONTAL_TAB)
			&& prevSymbol3 == l1
			&& prevSymbol2 == l2
			&& prevSymbol1 == l3
			&& symbol == l4 
			&& nextSymbol1 == l5 
			&& nextSymbol2 == l6 
			&& (nextSymbol3 == SPACE || nextSymbol3 == NEW_LINE || nextSymbol3 == CARRIAGE_RETURN || nextSymbol3 ==  NUL || nextSymbol3 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			return pos - 3;
		}

		if(    (prevSymbol3 == SPACE || prevSymbol3 == NEW_LINE || prevSymbol3 == CARRIAGE_RETURN || prevSymbol3 == NUL || prevSymbol3 == HORIZONTAL_TAB)
			&& prevSymbol2 == l1
			&& prevSymbol1 == l2
			&& symbol == l3 
			&& nextSymbol1 == l4 
			&& nextSymbol2 == l5 
			&& nextSymbol3 == l6 
			&& (nextSymbol4 == SPACE || nextSymbol4 == NEW_LINE || nextSymbol4 == CARRIAGE_RETURN || nextSymbol4 ==  NUL || nextSymbol4 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			return pos -2;
		}

		if(    (prevSymbol2 == SPACE || prevSymbol2 == NEW_LINE || prevSymbol2 == CARRIAGE_RETURN || prevSymbol2 == NUL || prevSymbol2 == HORIZONTAL_TAB)
			&& prevSymbol1 == l1
			&& symbol == l2 
			&& nextSymbol1 == l3 
			&& nextSymbol2 == l4 
			&& nextSymbol3 == l5 
			&& nextSymbol4 == l6 
			&& (nextSymbol5 == SPACE || nextSymbol5 == NEW_LINE || nextSymbol5 == CARRIAGE_RETURN || nextSymbol5 ==  NUL || nextSymbol5 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			return pos - 1;
		}

		if(    (prevSymbol1 == SPACE || prevSymbol1 == NEW_LINE || prevSymbol1 == CARRIAGE_RETURN || prevSymbol1 == NUL || prevSymbol1 == HORIZONTAL_TAB)
			&& symbol == l1 
			&& nextSymbol1 == l2 
			&& nextSymbol2 == l3 
			&& nextSymbol3 == l4 
			&& nextSymbol4 == l5
			&& nextSymbol5 == l6
			&& (nextSymbol6 == SPACE || nextSymbol6 == NEW_LINE || nextSymbol6 == CARRIAGE_RETURN || nextSymbol6 ==  NUL || nextSymbol6 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			return pos;
		}

		if(    (symbol == SPACE || symbol == NEW_LINE || symbol == CARRIAGE_RETURN || symbol == NUL || symbol == HORIZONTAL_TAB)
			&& nextSymbol1 == l1 
			&& nextSymbol2 == l2 
			&& nextSymbol3 == l3 
			&& nextSymbol4 == l4 
			&& nextSymbol5 == l5 
			&& nextSymbol6 == l6 
			&& (nextSymbol7 == SPACE || nextSymbol7 == NEW_LINE || nextSymbol7 == CARRIAGE_RETURN || nextSymbol7 ==  NUL || nextSymbol7 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			if( isAlphaNumeric(prevSymbol1) )
			{
				return pos + 1;
			}
		}
	}


return NOT_FOUND;
}


long CAIPIEditorView::WSPDetectKeyWordEdit6( long pos, int l1, int l2, int l3, int l4, int l5, int l6)
{
	
	if( m_iModificationType == INSERTTEXT || m_iModificationType == BEFOREDELETE )
	{
		CString str;
		CScintillaCtrl& rCtrl = GetCtrl();
		
		int prevSymbol7 = rCtrl.GetCharAt( pos - 7 );
		//str.Format(_T("PrevSymbol7...%d  " ), prevSymbol7);
		//AfxMessageBox(str);
		
	
		int prevSymbol6 = rCtrl.GetCharAt( pos - 6 );
		//str.Format(_T("PrevSymbol6...%d  " ), prevSymbol6);
		//AfxMessageBox(str);
		

		int prevSymbol5 = rCtrl.GetCharAt( pos - 5 );
		//str.Format(_T("PrevSymbol5...%d  " ), prevSymbol5);
		//AfxMessageBox(str);
		
		
		int prevSymbol4 = rCtrl.GetCharAt( pos - 4 );
		//str.Format(_T("PrevSymbol4...%d  " ), prevSymbol4);
		//AfxMessageBox(str);
		
		
		int prevSymbol3 = rCtrl.GetCharAt( pos - 3 );
		//str.Format(_T("PrevSymbol3...%d  " ), prevSymbol3);
		//AfxMessageBox(str);
		
		int prevSymbol2 = rCtrl.GetCharAt( pos - 2);
		//str.Format(_T("PrevSymbol2...%d  " ), prevSymbol2);
		//AfxMessageBox(str);
		
		int prevSymbol1 = rCtrl.GetCharAt( pos - 1);
		//str.Format(_T("PrevSymbol1...%d  " ), prevSymbol1);
		//AfxMessageBox(str);
		
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);
		
		int nextSymbol1 = rCtrl.GetCharAt(pos + 1);
		//str.Format(_T("NextSymbol1...%d  " ), nextSymbol1);
		//AfxMessageBox(str);

		int nextSymbol2 = rCtrl.GetCharAt(pos + 2);
		//str.Format(_T("NextSymbol2...%d  " ), nextSymbol2);
		//AfxMessageBox(str);

		int nextSymbol3 = rCtrl.GetCharAt(pos + 3);
		//str.Format(_T("NextSymbol3...%d  " ), nextSymbol3);
		//AfxMessageBox(str);

		int nextSymbol4 = rCtrl.GetCharAt(pos + 4);
		//str.Format(_T("NextSymbol4...%d  " ), nextSymbol4);
		//AfxMessageBox(str);


		int nextSymbol5 = rCtrl.GetCharAt(pos + 5);
		//str.Format(_T("NextSymbol5...%d  " ), nextSymbol5);
		//AfxMessageBox(str);

		int nextSymbol6 = rCtrl.GetCharAt(pos + 6);
		//str.Format(_T("NextSymbol6...%d  " ), nextSymbol6);
		//AfxMessageBox(str);

		int nextSymbol7 = rCtrl.GetCharAt(pos + 7);
		//str.Format(_T("NextSymbol7...%d  " ), nextSymbol7);
		//AfxMessageBox(str);


		//Check cases of inserting a wrong caracter between the keyword
			if( prevSymbol1 == l6 )
			{
			   //AfxMessageBox(_T("Case prevS = l6"));
				//Case letter l6
				if(	prevSymbol2 == l5 && prevSymbol3 == l4 && prevSymbol4 == l3 && prevSymbol5 == l2 && prevSymbol6 == l1
				&&  (prevSymbol7 == SPACE || prevSymbol7 == NEW_LINE || prevSymbol7 == CARRIAGE_RETURN || prevSymbol7 ==  NUL || prevSymbol7 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					return pos-6; 
				}
			}
            
			if( prevSymbol1 == l5 )
			{
				//AfxMessageBox(_T("Case prevS = l5"));
				//Case letter l5
				if(	prevSymbol2 == l4 && prevSymbol3 == l3 && prevSymbol4 == l2 && prevSymbol5 == l1 
				&&  (prevSymbol6 == SPACE || prevSymbol6 == NEW_LINE || prevSymbol6 == CARRIAGE_RETURN || prevSymbol6 ==  NUL || prevSymbol6 == HORIZONTAL_TAB )
				&& nextSymbol1 == l6
				&& (nextSymbol2 == SPACE || nextSymbol2 == NEW_LINE || nextSymbol2 == CARRIAGE_RETURN || nextSymbol2 ==  NUL || nextSymbol2 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					return pos-5; 
				}
			}
			
			if( prevSymbol1 == l4 )
			{
				//AfxMessageBox(_T("Case prevS = l4"));
				//Case letter l4
				if(	prevSymbol2 == l3  && prevSymbol3 == l2 && prevSymbol4 == l1
				&&  (prevSymbol5 == SPACE || prevSymbol5 == NEW_LINE || prevSymbol5 == CARRIAGE_RETURN || prevSymbol5 ==  NUL || prevSymbol5 == HORIZONTAL_TAB )
				&& nextSymbol1 == l5 && nextSymbol2 == l6
				&& (nextSymbol3 == SPACE || nextSymbol3 == NEW_LINE || nextSymbol3 == CARRIAGE_RETURN || nextSymbol3 ==  NUL || nextSymbol3 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					return pos-2; 
				}
			}
			
			if( prevSymbol1 == l3 )
			{
				//AfxMessageBox(_T("Case prevS = l3"));
				//Case letter l3
				if(	prevSymbol2 == l2  && prevSymbol3 == l1 
				&&  (prevSymbol4 == SPACE || prevSymbol4 == NEW_LINE || prevSymbol4 == CARRIAGE_RETURN || prevSymbol4 ==  NUL || prevSymbol4 == HORIZONTAL_TAB )
				&& nextSymbol1 == l4 && nextSymbol2 == l5 && nextSymbol3 == l6
				&& (nextSymbol4 == SPACE || nextSymbol4 == NEW_LINE || nextSymbol4 == CARRIAGE_RETURN || nextSymbol4 ==  NUL || nextSymbol4 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					return pos-3; 
				}
			}
			
			if( prevSymbol1 == l2 )
			{
				//AfxMessageBox(_T("Case prevS = l2"));
				//Case letter l2
				if(	prevSymbol2 == l1 
				&&  (prevSymbol3 == SPACE || prevSymbol3 == NEW_LINE || prevSymbol3 == CARRIAGE_RETURN || prevSymbol3 ==  NUL || prevSymbol3 == HORIZONTAL_TAB )
				&& nextSymbol1 == l3 && nextSymbol2 == l4 && nextSymbol3 == l5 && nextSymbol4 == l6
				&& (nextSymbol5 == SPACE || nextSymbol5 == NEW_LINE || nextSymbol5 == CARRIAGE_RETURN || nextSymbol5 ==  NUL || nextSymbol5 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					return pos-2; 
				}
			}
			
			if ( prevSymbol1 == l1 )
			{
				//AfxMessageBox(_T("Case prevS = l1"));
				
				//Case letter l1
				if(	(prevSymbol2 == SPACE || prevSymbol2 == NEW_LINE || prevSymbol2 == CARRIAGE_RETURN || prevSymbol2 ==  NUL || prevSymbol2 == HORIZONTAL_TAB )
				&& nextSymbol1 == l2 && nextSymbol2 == l3 && nextSymbol3 == l4 && nextSymbol4 == l5 && nextSymbol5 == l6
				&& (nextSymbol6 == SPACE || nextSymbol6 == NEW_LINE || nextSymbol6 == CARRIAGE_RETURN || nextSymbol6 ==  NUL || nextSymbol6 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					return pos-1; 
				}
			}
			
			if ( prevSymbol1 != SPACE || prevSymbol1 != NEW_LINE || prevSymbol1 != CARRIAGE_RETURN || prevSymbol1 != NUL || prevSymbol1 != HORIZONTAL_TAB )
			{
				//AfxMessageBox(_T("Case prevS = Space"));
				
				//Case letter empty
				if( nextSymbol1 == l1 && nextSymbol2 == l2 && nextSymbol3 == l3 && nextSymbol4 == l4 && nextSymbol5 == l5 && nextSymbol6 == l6 
				&& (nextSymbol7 == SPACE || nextSymbol7 == NEW_LINE || nextSymbol7 == CARRIAGE_RETURN || nextSymbol7 ==  NUL || nextSymbol7 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					if( isAlphaNumeric(prevSymbol2) )
					{
						return pos + 1;
					}
				}
			}

			
		
		
			
		
	}


return NOT_FOUND;
}





long CAIPIEditorView::WSPDetectKeyWord7( long pos, int l1, int l2, int l3, int l4, int l5, int l6, int l7)
{
	
	if( m_iModificationType == BEFOREDELETE || m_iModificationType == INSERTTEXT )
	{
		CString str;
		CScintillaCtrl& rCtrl = GetCtrl();
	
		int prevSymbol7 = rCtrl.GetCharAt( pos -  7);
		//str.Format(_T("PrevSymbol7...%d  " ), prevSymbol7);
		//AfxMessageBox(str);
		
		int prevSymbol6 = rCtrl.GetCharAt( pos - 6 );
		//str.Format(_T("PrevSymbol6...%d  " ), prevSymbol6);
		//AfxMessageBox(str);
		
		
		int prevSymbol5 = rCtrl.GetCharAt( pos - 5 );
		//str.Format(_T("PrevSymbol5...%d  " ), prevSymbol5);
		//AfxMessageBox(str);
		
		
		int prevSymbol4 = rCtrl.GetCharAt( pos - 4 );
		//str.Format(_T("PrevSymbol4...%d  " ), prevSymbol4);
		//AfxMessageBox(str);
		
		
		int prevSymbol3 = rCtrl.GetCharAt( pos - 3 );
		//str.Format(_T("PrevSymbol3...%d  " ), prevSymbol3);
		//AfxMessageBox(str);
		
		int prevSymbol2 = rCtrl.GetCharAt( pos - 2);
		//str.Format(_T("PrevSymbol2...%d  " ), prevSymbol2);
		//AfxMessageBox(str);
		
		int prevSymbol1 = rCtrl.GetCharAt( pos - 1);
		//str.Format(_T("PrevSymbol1...%d  " ), prevSymbol1);
		//AfxMessageBox(str);
		
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);
		
		int nextSymbol1 = rCtrl.GetCharAt(pos + 1);
		//str.Format(_T("NextSymbol1...%d  " ), nextSymbol1);
		//AfxMessageBox(str);

		int nextSymbol2 = rCtrl.GetCharAt(pos + 2);
		//str.Format(_T("NextSymbol2...%d  " ), nextSymbol2);
		//AfxMessageBox(str);

		int nextSymbol3 = rCtrl.GetCharAt(pos + 3);
		//str.Format(_T("NextSymbol3...%d  " ), nextSymbol3);
		//AfxMessageBox(str);

		int nextSymbol4 = rCtrl.GetCharAt(pos + 4);
		//str.Format(_T("NextSymbol4...%d  " ), nextSymbol4);
		//AfxMessageBox(str);


		int nextSymbol5 = rCtrl.GetCharAt(pos + 5);
		//str.Format(_T("NextSymbol5...%d  " ), nextSymbol5);
		//AfxMessageBox(str);

		int nextSymbol6 = rCtrl.GetCharAt(pos + 6);
		//str.Format(_T("NextSymbol6...%d  " ), nextSymbol6);
		//AfxMessageBox(str);
		
		int nextSymbol7 = rCtrl.GetCharAt(pos + 7);
		//str.Format(_T("NextSymbol7...%d  " ), nextSymbol7);
		//AfxMessageBox(str);

		int nextSymbol8 = rCtrl.GetCharAt(pos + 8);
		//str.Format(_T("NextSymbol8...%d  " ), nextSymbol8);
		//AfxMessageBox(str);
	

		
		if(    (prevSymbol7 == SPACE || prevSymbol7 == NEW_LINE || prevSymbol7 == CARRIAGE_RETURN || prevSymbol7 == NUL || prevSymbol7 == HORIZONTAL_TAB)
			&& prevSymbol6 == l1
			&& prevSymbol5 == l2
			&& prevSymbol4 == l3
			&& prevSymbol3 == l4 
			&& prevSymbol2 == l5 
			&& prevSymbol1 == l6 
			&& symbol == l7 
			&& (nextSymbol1 == SPACE || nextSymbol1 == NEW_LINE || nextSymbol1 == CARRIAGE_RETURN || nextSymbol1 ==  NUL || nextSymbol1 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			return pos - 6;
		}

		if(    (prevSymbol6 == SPACE || prevSymbol6 == NEW_LINE || prevSymbol6 == CARRIAGE_RETURN || prevSymbol6 == NUL || prevSymbol6 == HORIZONTAL_TAB)
			&& prevSymbol5 == l1 
			&& prevSymbol4 == l2 
			&& prevSymbol3 == l3 
			&& prevSymbol2 == l4 
			&& prevSymbol1 == l5 
			&& symbol == l6 
			&& nextSymbol1 == l7 
			&& (nextSymbol2 == SPACE || nextSymbol2 == NEW_LINE || nextSymbol2 == CARRIAGE_RETURN || nextSymbol2 ==  NUL || nextSymbol2 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			return pos - 5;
		}
			
		if(    (prevSymbol5 == SPACE || prevSymbol5 == NEW_LINE || prevSymbol5 == CARRIAGE_RETURN || prevSymbol5 == NUL || prevSymbol5 == HORIZONTAL_TAB)
			&& prevSymbol4 == l1
			&& prevSymbol3 == l2
			&& prevSymbol2 == l3
			&& prevSymbol1 == l4
			&& symbol == l5 
			&& nextSymbol1 == l6 
			&& nextSymbol2 == l7 
			&& (nextSymbol3 == SPACE || nextSymbol3 == NEW_LINE || nextSymbol3 == CARRIAGE_RETURN || nextSymbol3 ==  NUL || nextSymbol3 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			return pos - 4;
		}

		if(    (prevSymbol4 == SPACE || prevSymbol4 == NEW_LINE || prevSymbol4 == CARRIAGE_RETURN || prevSymbol4 == NUL || prevSymbol4 == HORIZONTAL_TAB)
			&& prevSymbol3 == l1
			&& prevSymbol2 == l2
			&& prevSymbol1 == l3
			&& symbol == l4 
			&& nextSymbol1 == l5 
			&& nextSymbol2 == l6 
			&& nextSymbol3 == l7 
			&& (nextSymbol4 == SPACE || nextSymbol4 == NEW_LINE || nextSymbol4 == CARRIAGE_RETURN || nextSymbol4 ==  NUL || nextSymbol4 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			return pos -3;
		}

		if(    (prevSymbol3 == SPACE || prevSymbol3 == NEW_LINE || prevSymbol3 == CARRIAGE_RETURN || prevSymbol3 == NUL || prevSymbol3 == HORIZONTAL_TAB)
			&& prevSymbol2 == l1
			&& prevSymbol1 == l2
			&& symbol == l3 
			&& nextSymbol1 == l4 
			&& nextSymbol2 == l5 
			&& nextSymbol3 == l6 
			&& nextSymbol4 == l7 
			&& (nextSymbol5 == SPACE || nextSymbol5 == NEW_LINE || nextSymbol5 == CARRIAGE_RETURN || nextSymbol5 ==  NUL || nextSymbol5 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			return pos - 2;
		}

		if(    (prevSymbol2 == SPACE || prevSymbol2 == NEW_LINE || prevSymbol2 == CARRIAGE_RETURN || prevSymbol2 == NUL || prevSymbol2 == HORIZONTAL_TAB)
			&& prevSymbol1 == l1
			&& symbol == l2 
			&& nextSymbol1 == l3 
			&& nextSymbol2 == l4 
			&& nextSymbol3 == l5 
			&& nextSymbol4 == l6
			&& nextSymbol5 == l7
			&& (nextSymbol6 == SPACE || nextSymbol6 == NEW_LINE || nextSymbol6 == CARRIAGE_RETURN || nextSymbol6 ==  NUL || nextSymbol6 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			return pos - 1;
		}

		if(    (prevSymbol1 == SPACE || prevSymbol1 == NEW_LINE || prevSymbol1 == CARRIAGE_RETURN || prevSymbol1 == NUL || prevSymbol1 == HORIZONTAL_TAB)
			&& symbol == l1 
			&& nextSymbol1 == l2 
			&& nextSymbol2 == l3 
			&& nextSymbol3 == l4 
			&& nextSymbol4 == l5
			&& nextSymbol5 == l6
			&& nextSymbol6 == l7
			&& (nextSymbol7 == SPACE || nextSymbol7 == NEW_LINE || nextSymbol7 == CARRIAGE_RETURN || nextSymbol7 ==  NUL || nextSymbol7 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			return pos;
		}

		if(    (symbol == SPACE || symbol == NEW_LINE || symbol == CARRIAGE_RETURN || symbol == NUL || symbol == HORIZONTAL_TAB)
			&& nextSymbol1 == l1 
			&& nextSymbol2 == l2 
			&& nextSymbol3 == l3 
			&& nextSymbol4 == l4 
			&& nextSymbol5 == l5 
			&& nextSymbol6 == l6 
			&& nextSymbol7 == l7
			&& (nextSymbol8 == SPACE || nextSymbol8 == NEW_LINE || nextSymbol8 == CARRIAGE_RETURN || nextSymbol8 ==  NUL || nextSymbol8 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			if( isAlphaNumeric(prevSymbol1) )
			{
				return pos + 1;
			}
		}
	}


return NOT_FOUND;
}


long CAIPIEditorView::WSPDetectKeyWordEdit7( long pos, int l1, int l2, int l3, int l4, int l5, int l6, int l7)
{
	
	if( m_iModificationType == INSERTTEXT || m_iModificationType == BEFOREDELETE )
	{
		CString str;
		CScintillaCtrl& rCtrl = GetCtrl();
		
		int prevSymbol8 = rCtrl.GetCharAt( pos - 8 );
		//str.Format(_T("PrevSymbol8...%d  " ), prevSymbol8);
		//AfxMessageBox(str);
		
		int prevSymbol7 = rCtrl.GetCharAt( pos - 7 );
		//str.Format(_T("PrevSymbol7...%d  " ), prevSymbol7);
		//AfxMessageBox(str);
		
	
		int prevSymbol6 = rCtrl.GetCharAt( pos - 6 );
		//str.Format(_T("PrevSymbol6...%d  " ), prevSymbol6);
		//AfxMessageBox(str);
		

		int prevSymbol5 = rCtrl.GetCharAt( pos - 5 );
		//str.Format(_T("PrevSymbol5...%d  " ), prevSymbol5);
		//AfxMessageBox(str);
		
		
		int prevSymbol4 = rCtrl.GetCharAt( pos - 4 );
		//str.Format(_T("PrevSymbol4...%d  " ), prevSymbol4);
		//AfxMessageBox(str);
		
		
		int prevSymbol3 = rCtrl.GetCharAt( pos - 3 );
		//str.Format(_T("PrevSymbol3...%d  " ), prevSymbol3);
		//AfxMessageBox(str);
		
		int prevSymbol2 = rCtrl.GetCharAt( pos - 2);
		//str.Format(_T("PrevSymbol2...%d  " ), prevSymbol2);
		//AfxMessageBox(str);
		
		int prevSymbol1 = rCtrl.GetCharAt( pos - 1);
		//str.Format(_T("PrevSymbol1...%d  " ), prevSymbol1);
		//AfxMessageBox(str);
		
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);
		
		int nextSymbol1 = rCtrl.GetCharAt(pos + 1);
		//str.Format(_T("NextSymbol1...%d  " ), nextSymbol1);
		//AfxMessageBox(str);

		int nextSymbol2 = rCtrl.GetCharAt(pos + 2);
		//str.Format(_T("NextSymbol2...%d  " ), nextSymbol2);
		//AfxMessageBox(str);

		int nextSymbol3 = rCtrl.GetCharAt(pos + 3);
		//str.Format(_T("NextSymbol3...%d  " ), nextSymbol3);
		//AfxMessageBox(str);

		int nextSymbol4 = rCtrl.GetCharAt(pos + 4);
		//str.Format(_T("NextSymbol4...%d  " ), nextSymbol4);
		//AfxMessageBox(str);


		int nextSymbol5 = rCtrl.GetCharAt(pos + 5);
		//str.Format(_T("NextSymbol5...%d  " ), nextSymbol5);
		//AfxMessageBox(str);

		int nextSymbol6 = rCtrl.GetCharAt(pos + 6);
		//str.Format(_T("NextSymbol6...%d  " ), nextSymbol6);
		//AfxMessageBox(str);

		int nextSymbol7 = rCtrl.GetCharAt(pos + 7);
		//str.Format(_T("NextSymbol7...%d  " ), nextSymbol7);
		//AfxMessageBox(str);

		int nextSymbol8 = rCtrl.GetCharAt(pos + 8);
		//str.Format(_T("NextSymbol8...%d  " ), nextSymbol8);
		//AfxMessageBox(str);



		//Check cases of inserting a wrong caracter between the keyword
		
			if( prevSymbol1 == l7 )
			{
			   //AfxMessageBox(_T("Case prevS = l7"));
				//Case letter l7
				if(	prevSymbol2 == l6 && prevSymbol3 == l5 && prevSymbol4 == l4 && prevSymbol5 == l3 && prevSymbol6 == l2 && prevSymbol7 == l1
				&&  (prevSymbol8 == SPACE || prevSymbol8 == NEW_LINE || prevSymbol8 == CARRIAGE_RETURN || prevSymbol8 ==  NUL || prevSymbol8 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					return pos-7; 
				}
			}
            else if( prevSymbol1 == l6 )
			{
				//AfxMessageBox(_T("Case prevS = l6"));
				//Case letter l6
				if(	prevSymbol2 == l5 && prevSymbol3 == l4 && prevSymbol4 == l3 && prevSymbol5 == l2 && prevSymbol6 == l1
				&&  (prevSymbol7 == SPACE || prevSymbol7 == NEW_LINE || prevSymbol7 == CARRIAGE_RETURN || prevSymbol7 ==  NUL || prevSymbol7 == HORIZONTAL_TAB )
				&& nextSymbol1 == l7
				&& (nextSymbol2 == SPACE || nextSymbol2 == NEW_LINE || nextSymbol2 == CARRIAGE_RETURN || nextSymbol2 ==  NUL || nextSymbol2 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					return pos-6; 
				}
			}
			
			else if( prevSymbol1 == l5 )
			{
				//AfxMessageBox(_T("Case prevS = l5"));
				//Case letter l5
				if(	prevSymbol2 == l4  && prevSymbol3 == l3 && prevSymbol4 == l2 && prevSymbol5 == l1
				&&  (prevSymbol6 == SPACE || prevSymbol6 == NEW_LINE || prevSymbol6 == CARRIAGE_RETURN || prevSymbol6 ==  NUL || prevSymbol6 == HORIZONTAL_TAB )
				&& nextSymbol1 == l6 && nextSymbol2 == l7
				&& (nextSymbol3 == SPACE || nextSymbol3 == NEW_LINE || nextSymbol3 == CARRIAGE_RETURN || nextSymbol3 ==  NUL || nextSymbol3 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					return pos-5; 
				}
			}
			
			else if( prevSymbol1 == l4 )
			{
				//AfxMessageBox(_T("Case prevS = l4"));
				//Case letter l4
				if(	prevSymbol2 == l3  && prevSymbol3 == l2 && prevSymbol4 == l1
				&&  (prevSymbol5 == SPACE || prevSymbol5 == NEW_LINE || prevSymbol5 == CARRIAGE_RETURN || prevSymbol5 ==  NUL || prevSymbol5 == HORIZONTAL_TAB )
				&& nextSymbol1 == l5 && nextSymbol2 == l6 && nextSymbol3 == l7
				&& (nextSymbol4 == SPACE || nextSymbol4 == NEW_LINE || nextSymbol4 == CARRIAGE_RETURN || nextSymbol4 ==  NUL || nextSymbol4 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					return pos-4; 
				}
			}
			
			else if( prevSymbol1 == l3 )
			{
				//AfxMessageBox(_T("Case prevS = l3"));
				//Case letter l3
				if(	prevSymbol2 == l2 && prevSymbol3 == l1
				&&  (prevSymbol4 == SPACE || prevSymbol4 == NEW_LINE || prevSymbol4 == CARRIAGE_RETURN || prevSymbol4 ==  NUL || prevSymbol4 == HORIZONTAL_TAB )
				&& nextSymbol1 == l4 && nextSymbol2 == l5 && nextSymbol3 == l6 && nextSymbol4 == l7
				&& (nextSymbol5 == SPACE || nextSymbol5 == NEW_LINE || nextSymbol5 == CARRIAGE_RETURN || nextSymbol5 ==  NUL || nextSymbol5 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					return pos-3; 
				}
			}

			else if( prevSymbol1 == l2 )
			{
				//AfxMessageBox(_T("Case prevS = l3"));
				//Case letter l3
				if(	prevSymbol2 == l1
				&&  (prevSymbol3 == SPACE || prevSymbol3 == NEW_LINE || prevSymbol3 == CARRIAGE_RETURN || prevSymbol3 ==  NUL || prevSymbol3 == HORIZONTAL_TAB )
				&& nextSymbol1 == l3 && nextSymbol2 == l4 && nextSymbol3 == l5 && nextSymbol4 == l6 && nextSymbol5 == l7
				&& (nextSymbol6 == SPACE || nextSymbol6 == NEW_LINE || nextSymbol6 == CARRIAGE_RETURN || nextSymbol6 ==  NUL || nextSymbol6 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					return pos-2; 
				}
			}

			else if ( prevSymbol1 == l1 )
			{
				//AfxMessageBox(_T("Case prevS = l1"));
				
				//Case letter l1
				if(	(prevSymbol2 == SPACE || prevSymbol2 == NEW_LINE || prevSymbol2 == CARRIAGE_RETURN || prevSymbol2 ==  NUL || prevSymbol2 == HORIZONTAL_TAB )
				&& nextSymbol1 == l2 && nextSymbol2 == l3 && nextSymbol3 == l4 && nextSymbol4 == l5 && nextSymbol5 == l6 && nextSymbol6 == l7
				&& (nextSymbol7 == SPACE || nextSymbol7 == NEW_LINE || nextSymbol7 == CARRIAGE_RETURN || nextSymbol7 ==  NUL || nextSymbol7 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					return pos-1; 
				}
			}
			if ( prevSymbol1 != SPACE || prevSymbol1 != NEW_LINE || prevSymbol1 != CARRIAGE_RETURN || prevSymbol1 != NUL || prevSymbol1 != HORIZONTAL_TAB )
			{
				//AfxMessageBox(_T("Case prevS = Space"));
				
				//Case letter empty
				if( nextSymbol1 == l1 && nextSymbol2 == l2 && nextSymbol3 == l3 && nextSymbol4 == l4 && nextSymbol5 == l5 && nextSymbol6 == l6 && nextSymbol7 == l7
				&& (nextSymbol8 == SPACE || nextSymbol8 == NEW_LINE || nextSymbol8 == CARRIAGE_RETURN || nextSymbol8 ==  NUL || nextSymbol8 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					if( isAlphaNumeric(prevSymbol2) )
					{
						return pos + 1;
					}
				}
			}

			
		
		
			
		
	}


return NOT_FOUND;
}



long CAIPIEditorView::WSPDetectKeyWord8( long pos, int l1, int l2, int l3, int l4, int l5, int l6, int l7, int l8)
{
	
	if( m_iModificationType == BEFOREDELETE || m_iModificationType == INSERTTEXT )
	{
		CString str;
		CScintillaCtrl& rCtrl = GetCtrl();
	
		int prevSymbol8 = rCtrl.GetCharAt( pos - 8);
		//str.Format(_T("PrevSymbol8...%d  " ), prevSymbol8);
		//AfxMessageBox(str);
		
		
		
		int prevSymbol7 = rCtrl.GetCharAt( pos -  7);
		//str.Format(_T("PrevSymbol7...%d  " ), prevSymbol7);
		//AfxMessageBox(str);
		
		int prevSymbol6 = rCtrl.GetCharAt( pos - 6 );
		//str.Format(_T("PrevSymbol6...%d  " ), prevSymbol6);
		//AfxMessageBox(str);
		
		
		int prevSymbol5 = rCtrl.GetCharAt( pos - 5 );
		//str.Format(_T("PrevSymbol5...%d  " ), prevSymbol5);
		//AfxMessageBox(str);
		
		
		int prevSymbol4 = rCtrl.GetCharAt( pos - 4 );
		//str.Format(_T("PrevSymbol4...%d  " ), prevSymbol4);
		//AfxMessageBox(str);
		
		
		int prevSymbol3 = rCtrl.GetCharAt( pos - 3 );
		//str.Format(_T("PrevSymbol3...%d  " ), prevSymbol3);
		//AfxMessageBox(str);
		
		int prevSymbol2 = rCtrl.GetCharAt( pos - 2);
		//str.Format(_T("PrevSymbol2...%d  " ), prevSymbol2);
		//AfxMessageBox(str);
		
		int prevSymbol1 = rCtrl.GetCharAt( pos - 1);
		//str.Format(_T("PrevSymbol1...%d  " ), prevSymbol1);
		//AfxMessageBox(str);
		
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);
		
		int nextSymbol1 = rCtrl.GetCharAt(pos + 1);
		//str.Format(_T("NextSymbol1...%d  " ), nextSymbol1);
		//AfxMessageBox(str);

		int nextSymbol2 = rCtrl.GetCharAt(pos + 2);
		//str.Format(_T("NextSymbol2...%d  " ), nextSymbol2);
		//AfxMessageBox(str);

		int nextSymbol3 = rCtrl.GetCharAt(pos + 3);
		//str.Format(_T("NextSymbol3...%d  " ), nextSymbol3);
		//AfxMessageBox(str);

		int nextSymbol4 = rCtrl.GetCharAt(pos + 4);
		//str.Format(_T("NextSymbol4...%d  " ), nextSymbol4);
		//AfxMessageBox(str);


		int nextSymbol5 = rCtrl.GetCharAt(pos + 5);
		//str.Format(_T("NextSymbol5...%d  " ), nextSymbol5);
		//AfxMessageBox(str);

		int nextSymbol6 = rCtrl.GetCharAt(pos + 6);
		//str.Format(_T("NextSymbol6...%d  " ), nextSymbol6);
		//AfxMessageBox(str);
		
		int nextSymbol7 = rCtrl.GetCharAt(pos + 7);
		//str.Format(_T("NextSymbol7...%d  " ), nextSymbol7);
		//AfxMessageBox(str);

		int nextSymbol8 = rCtrl.GetCharAt(pos + 8);
		//str.Format(_T("NextSymbol8...%d  " ), nextSymbol8);
		//AfxMessageBox(str);
	
		int nextSymbol9 = rCtrl.GetCharAt(pos + 9);
		//str.Format(_T("NextSymbol9...%d  " ), nextSymbol9);
		//AfxMessageBox(str);
	
		
		if(    (prevSymbol8 == SPACE || prevSymbol8 == NEW_LINE || prevSymbol8 == CARRIAGE_RETURN || prevSymbol8 == NUL || prevSymbol8 == HORIZONTAL_TAB)
			&& prevSymbol7 == l1
			&& prevSymbol6 == l2
			&& prevSymbol5 == l3
			&& prevSymbol4 == l4
			&& prevSymbol3 == l5 
			&& prevSymbol2 == l6 
			&& prevSymbol1 == l7 
			&& symbol == l8 
			&& (nextSymbol1 == SPACE || nextSymbol1 == NEW_LINE || nextSymbol1 == CARRIAGE_RETURN || nextSymbol1 ==  NUL || nextSymbol1 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			return pos - 7;
		}

		if(    (prevSymbol7 == SPACE || prevSymbol7 == NEW_LINE || prevSymbol7 == CARRIAGE_RETURN || prevSymbol7 == NUL || prevSymbol7 == HORIZONTAL_TAB)
			&& prevSymbol6 == l1
			&& prevSymbol5 == l2 
			&& prevSymbol4 == l3 
			&& prevSymbol3 == l4 
			&& prevSymbol2 == l5 
			&& prevSymbol1 == l6 
			&& symbol == l7 
			&& nextSymbol1 == l8 
			&& (nextSymbol2 == SPACE || nextSymbol2 == NEW_LINE || nextSymbol2 == CARRIAGE_RETURN || nextSymbol2 ==  NUL || nextSymbol2 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			return pos - 6;
		}
			
		if(    (prevSymbol6 == SPACE || prevSymbol6 == NEW_LINE || prevSymbol6 == CARRIAGE_RETURN || prevSymbol6 == NUL || prevSymbol6 == HORIZONTAL_TAB)
			&& prevSymbol5 == l1
			&& prevSymbol4 == l2
			&& prevSymbol3 == l3
			&& prevSymbol2 == l4
			&& prevSymbol1 == l5
			&& symbol == l6 
			&& nextSymbol1 == l7 
			&& nextSymbol2 == l8 
			&& (nextSymbol3 == SPACE || nextSymbol3 == NEW_LINE || nextSymbol3 == CARRIAGE_RETURN || nextSymbol3 ==  NUL || nextSymbol3 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			return pos - 5;
		}

		if(    (prevSymbol5 == SPACE || prevSymbol5 == NEW_LINE || prevSymbol5 == CARRIAGE_RETURN || prevSymbol5 == NUL || prevSymbol5 == HORIZONTAL_TAB)
			&& prevSymbol4 == l1
			&& prevSymbol3 == l2
			&& prevSymbol2 == l3
			&& prevSymbol1 == l4
			&& symbol == l5 
			&& nextSymbol1 == l6 
			&& nextSymbol2 == l7 
			&& nextSymbol3 == l8 
			&& (nextSymbol4 == SPACE || nextSymbol4 == NEW_LINE || nextSymbol4 == CARRIAGE_RETURN || nextSymbol4 ==  NUL || nextSymbol4 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			return pos -4;
		}

		if(    (prevSymbol4 == SPACE || prevSymbol4 == NEW_LINE || prevSymbol4 == CARRIAGE_RETURN || prevSymbol4 == NUL || prevSymbol4 == HORIZONTAL_TAB)
			&& prevSymbol3 == l1
			&& prevSymbol2 == l2
			&& prevSymbol1 == l3
			&& symbol == l4 
			&& nextSymbol1 == l5 
			&& nextSymbol2 == l6 
			&& nextSymbol3 == l7 
			&& nextSymbol4 == l8 
			&& (nextSymbol5 == SPACE || nextSymbol5 == NEW_LINE || nextSymbol5 == CARRIAGE_RETURN || nextSymbol5 ==  NUL || nextSymbol5 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			return pos - 3;
		}

		if(    (prevSymbol3 == SPACE || prevSymbol3 == NEW_LINE || prevSymbol3 == CARRIAGE_RETURN || prevSymbol3 == NUL || prevSymbol3 == HORIZONTAL_TAB)
			&& prevSymbol2 == l1
			&& prevSymbol1 == l2
			&& symbol == l3 
			&& nextSymbol1 == l4 
			&& nextSymbol2 == l5 
			&& nextSymbol3 == l6 
			&& nextSymbol4 == l7
			&& nextSymbol5 == l8
			&& (nextSymbol6 == SPACE || nextSymbol6 == NEW_LINE || nextSymbol6 == CARRIAGE_RETURN || nextSymbol6 ==  NUL || nextSymbol6 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			return pos - 2;
		}

		if(    (prevSymbol2 == SPACE || prevSymbol2 == NEW_LINE || prevSymbol2 == CARRIAGE_RETURN || prevSymbol2 == NUL || prevSymbol2 == HORIZONTAL_TAB)
			&& prevSymbol1 == l1
			&& symbol == l2 
			&& nextSymbol1 == l3 
			&& nextSymbol2 == l4 
			&& nextSymbol3 == l5 
			&& nextSymbol4 == l6
			&& nextSymbol5 == l7
			&& nextSymbol6 == l8
			&& (nextSymbol7 == SPACE || nextSymbol7 == NEW_LINE || nextSymbol7 == CARRIAGE_RETURN || nextSymbol7 ==  NUL || nextSymbol7 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			return pos -1;
		}

		if(    (prevSymbol1 == SPACE || prevSymbol1 == NEW_LINE || prevSymbol1 == CARRIAGE_RETURN || prevSymbol1 == NUL || prevSymbol1 == HORIZONTAL_TAB)
			&& symbol == l1 
			&& nextSymbol1 == l2 
			&& nextSymbol2 == l3 
			&& nextSymbol3 == l4 
			&& nextSymbol4 == l5
			&& nextSymbol5 == l6
			&& nextSymbol6 == l7
			&& nextSymbol7 == l8
			&& (nextSymbol8 == SPACE || nextSymbol8 == NEW_LINE || nextSymbol8 == CARRIAGE_RETURN || nextSymbol8 ==  NUL || nextSymbol8 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			return pos;
		}

		if(    (symbol == SPACE || symbol == NEW_LINE || symbol == CARRIAGE_RETURN || symbol == NUL || symbol == HORIZONTAL_TAB)
			&& nextSymbol1 == l1 
			&& nextSymbol2 == l2 
			&& nextSymbol3 == l3 
			&& nextSymbol4 == l4 
			&& nextSymbol5 == l5 
			&& nextSymbol6 == l6 
			&& nextSymbol7 == l7
			&& nextSymbol8 == l8
			&& (nextSymbol9 == SPACE || nextSymbol9 == NEW_LINE || nextSymbol9 == CARRIAGE_RETURN || nextSymbol9 ==  NUL || nextSymbol9 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			if( isAlphaNumeric(prevSymbol1) )
			{
				return pos + 1;
			}
		}
	}


return NOT_FOUND;
}


long CAIPIEditorView::WSPDetectKeyWordEdit8( long pos, int l1, int l2, int l3, int l4, int l5, int l6, int l7, int l8)
{
	
	if( m_iModificationType == INSERTTEXT || m_iModificationType == BEFOREDELETE )
	{
		CString str;
		CScintillaCtrl& rCtrl = GetCtrl();
		
		int prevSymbol9 = rCtrl.GetCharAt( pos - 9 );
		//str.Format(_T("PrevSymbol9...%d  " ), prevSymbol9);
		//AfxMessageBox(str);
		
		
		int prevSymbol8 = rCtrl.GetCharAt( pos - 8 );
		//str.Format(_T("PrevSymbol8...%d  " ), prevSymbol8);
		//AfxMessageBox(str);
		
		int prevSymbol7 = rCtrl.GetCharAt( pos - 7 );
		//str.Format(_T("PrevSymbol7...%d  " ), prevSymbol7);
		//AfxMessageBox(str);
		
	
		int prevSymbol6 = rCtrl.GetCharAt( pos - 6 );
		//str.Format(_T("PrevSymbol6...%d  " ), prevSymbol6);
		//AfxMessageBox(str);
		

		int prevSymbol5 = rCtrl.GetCharAt( pos - 5 );
		//str.Format(_T("PrevSymbol5...%d  " ), prevSymbol5);
		//AfxMessageBox(str);
		
		
		int prevSymbol4 = rCtrl.GetCharAt( pos - 4 );
		//str.Format(_T("PrevSymbol4...%d  " ), prevSymbol4);
		//AfxMessageBox(str);
		
		
		int prevSymbol3 = rCtrl.GetCharAt( pos - 3 );
		//str.Format(_T("PrevSymbol3...%d  " ), prevSymbol3);
		//AfxMessageBox(str);
		
		int prevSymbol2 = rCtrl.GetCharAt( pos - 2);
		//str.Format(_T("PrevSymbol2...%d  " ), prevSymbol2);
		//AfxMessageBox(str);
		
		int prevSymbol1 = rCtrl.GetCharAt( pos - 1);
		//str.Format(_T("PrevSymbol1...%d  " ), prevSymbol1);
		//AfxMessageBox(str);
		
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);
		
		int nextSymbol1 = rCtrl.GetCharAt(pos + 1);
		//str.Format(_T("NextSymbol1...%d  " ), nextSymbol1);
		//AfxMessageBox(str);

		int nextSymbol2 = rCtrl.GetCharAt(pos + 2);
		//str.Format(_T("NextSymbol2...%d  " ), nextSymbol2);
		//AfxMessageBox(str);

		int nextSymbol3 = rCtrl.GetCharAt(pos + 3);
		//str.Format(_T("NextSymbol3...%d  " ), nextSymbol3);
		//AfxMessageBox(str);

		int nextSymbol4 = rCtrl.GetCharAt(pos + 4);
		//str.Format(_T("NextSymbol4...%d  " ), nextSymbol4);
		//AfxMessageBox(str);


		int nextSymbol5 = rCtrl.GetCharAt(pos + 5);
		//str.Format(_T("NextSymbol5...%d  " ), nextSymbol5);
		//AfxMessageBox(str);

		int nextSymbol6 = rCtrl.GetCharAt(pos + 6);
		//str.Format(_T("NextSymbol6...%d  " ), nextSymbol6);
		//AfxMessageBox(str);

		int nextSymbol7 = rCtrl.GetCharAt(pos + 7);
		//str.Format(_T("NextSymbol7...%d  " ), nextSymbol7);
		//AfxMessageBox(str);

		int nextSymbol8 = rCtrl.GetCharAt(pos + 8);
		//str.Format(_T("NextSymbol8...%d  " ), nextSymbol8);
		//AfxMessageBox(str);

		int nextSymbol9 = rCtrl.GetCharAt(pos + 9);
		//str.Format(_T("NextSymbol9...%d  " ), nextSymbol9);
		//AfxMessageBox(str);


		//Check cases of inserting a wrong caracter between the keyword
			if( prevSymbol1 == l8 )
			{
			   //AfxMessageBox(_T("Case prevS = l8"));
				//Case letter l8
				if(	prevSymbol2 == l7 && prevSymbol3 == l6 && prevSymbol4 == l5 && prevSymbol5 == l4 && prevSymbol6 == l3 && prevSymbol7 == l2 && prevSymbol8 == l1
				&&  (prevSymbol9 == SPACE || prevSymbol9 == NEW_LINE || prevSymbol9 == CARRIAGE_RETURN || prevSymbol9 ==  NUL || prevSymbol9 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					return pos-8; 
				}
			}
            if( prevSymbol1 == l7 )
			{
				//AfxMessageBox(_T("Case prevS = l7"));
				//Case letter l7
				if(	prevSymbol2 == l6 && prevSymbol3 == l5 && prevSymbol4 == l4 && prevSymbol5 == l3 && prevSymbol6 == l2 && prevSymbol7 == l1
				&&  (prevSymbol8 == SPACE || prevSymbol8 == NEW_LINE || prevSymbol8 == CARRIAGE_RETURN || prevSymbol8 ==  NUL || prevSymbol8 == HORIZONTAL_TAB )
				&& nextSymbol1 == l8
				&& (nextSymbol2 == SPACE || nextSymbol2 == NEW_LINE || nextSymbol2 == CARRIAGE_RETURN || nextSymbol2 ==  NUL || nextSymbol2 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					return pos-7; 
				}
			}
			
			if( prevSymbol1 == l6 )
			{
				//AfxMessageBox(_T("Case prevS = l6"));
				//Case letter l6
				if(	prevSymbol2 == l5  && prevSymbol3 == l4 && prevSymbol4 == l3 && prevSymbol5 == l2 && prevSymbol6 == l1
				&&  (prevSymbol7 == SPACE || prevSymbol7 == NEW_LINE || prevSymbol7 == CARRIAGE_RETURN || prevSymbol7 ==  NUL || prevSymbol7 == HORIZONTAL_TAB )
				&& nextSymbol1 == l7 && nextSymbol2 == l8
				&& (nextSymbol3 == SPACE || nextSymbol3 == NEW_LINE || nextSymbol3 == CARRIAGE_RETURN || nextSymbol3 ==  NUL || nextSymbol3 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					return pos-6; 
				}
			}
			
			if( prevSymbol1 == l5 )
			{
				//AfxMessageBox(_T("Case prevS = l5"));
				//Case letter l5
				if(	prevSymbol2 == l4  && prevSymbol3 == l3 && prevSymbol4 == l2 && prevSymbol5 == l1
				&&  (prevSymbol6 == SPACE || prevSymbol6 == NEW_LINE || prevSymbol6 == CARRIAGE_RETURN || prevSymbol6 ==  NUL || prevSymbol6 == HORIZONTAL_TAB )
				&& nextSymbol1 == l6 && nextSymbol2 == l7 && nextSymbol3 == l8
				&& (nextSymbol4 == SPACE || nextSymbol4 == NEW_LINE || nextSymbol4 == CARRIAGE_RETURN || nextSymbol4 ==  NUL || nextSymbol4 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					return pos-5; 
				}
			}
			
			if( prevSymbol1 == l4 )
			{
				//AfxMessageBox(_T("Case prevS = l4"));
				//Case letter l4
				if(	prevSymbol2 == l3 && prevSymbol3 == l2 && prevSymbol4 == l1
				&&  (prevSymbol5 == SPACE || prevSymbol5 == NEW_LINE || prevSymbol5 == CARRIAGE_RETURN || prevSymbol5 ==  NUL || prevSymbol5 == HORIZONTAL_TAB )
				&& nextSymbol1 == l5 && nextSymbol2 == l6 && nextSymbol3 == l7 && nextSymbol4 == l8
				&& (nextSymbol5 == SPACE || nextSymbol5 == NEW_LINE || nextSymbol5 == CARRIAGE_RETURN || nextSymbol5 ==  NUL || nextSymbol5 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					return pos-4; 
				}
			}

			if( prevSymbol1 == l3 )
			{
				//AfxMessageBox(_T("Case prevS = l3"));
				//Case letter l3
				if(	prevSymbol2 == l2 && prevSymbol3 == l1
				&&  (prevSymbol4 == SPACE || prevSymbol4 == NEW_LINE || prevSymbol4 == CARRIAGE_RETURN || prevSymbol4 ==  NUL || prevSymbol4 == HORIZONTAL_TAB )
				&& nextSymbol1 == l4 && nextSymbol2 == l5 && nextSymbol3 == l6 && nextSymbol4 == l7 && nextSymbol5 == l8
				&& (nextSymbol6 == SPACE || nextSymbol6 == NEW_LINE || nextSymbol6 == CARRIAGE_RETURN || nextSymbol6 ==  NUL || nextSymbol6 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					return pos-3; 
				}
			}

			if( prevSymbol1 == l2 )
			{
				//AfxMessageBox(_T("Case prevS = l2"));
				//Case letter l2
				if(	prevSymbol2 == l1 
				&&  (prevSymbol3 == SPACE || prevSymbol3 == NEW_LINE || prevSymbol3 == CARRIAGE_RETURN || prevSymbol3 ==  NUL || prevSymbol3 == HORIZONTAL_TAB )
				&& nextSymbol1 == l3 && nextSymbol2 == l4 && nextSymbol3 == l5 && nextSymbol4 == l6 && nextSymbol5 == l7 && nextSymbol6 == l8
				&& (nextSymbol7 == SPACE || nextSymbol7 == NEW_LINE || nextSymbol7 == CARRIAGE_RETURN || nextSymbol7 ==  NUL || nextSymbol7 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					return pos-2; 
				}
			}


			if ( prevSymbol1 == l1 )
			{
				//AfxMessageBox(_T("Case prevS = l1"));
				
				//Case letter l1
				if(	(prevSymbol2 == SPACE || prevSymbol2 == NEW_LINE || prevSymbol2 == CARRIAGE_RETURN || prevSymbol2 ==  NUL || prevSymbol2 == HORIZONTAL_TAB )
				&& nextSymbol1 == l2 && nextSymbol2 == l3 && nextSymbol3 == l4 && nextSymbol4 == l5 && nextSymbol5 == l6 && nextSymbol6 == l7 && nextSymbol7 == l8
				&& (nextSymbol8 == SPACE || nextSymbol8 == NEW_LINE || nextSymbol8 == CARRIAGE_RETURN || nextSymbol8 ==  NUL || nextSymbol8 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					return pos-1; 
				}
			}
			
			if ( prevSymbol1 != SPACE || prevSymbol1 != NEW_LINE || prevSymbol1 != CARRIAGE_RETURN || prevSymbol1 != NUL || prevSymbol1 != HORIZONTAL_TAB )
			{
				//AfxMessageBox(_T("Case prevS = Space"));
				
				//Case letter empty
				if( nextSymbol1 == l1 && nextSymbol2 == l2 && nextSymbol3 == l3 && nextSymbol4 == l4 && nextSymbol5 == l5 && nextSymbol6 == l6 && nextSymbol7 == l7 && nextSymbol8 == l8
				&& (nextSymbol9 == SPACE || nextSymbol9 == NEW_LINE || nextSymbol9 == CARRIAGE_RETURN || nextSymbol9 ==  NUL || nextSymbol9 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					if( isAlphaNumeric(prevSymbol2) )
					{
						return pos + 1; 
					}
				}
			}

			
		
		
			
		
	}


return NOT_FOUND;
}




long CAIPIEditorView::WSPDetectKeyWord9( long pos, int l1, int l2, int l3, int l4, int l5, int l6, int l7, int l8, int l9)
{
	
	if( m_iModificationType == BEFOREDELETE || m_iModificationType == INSERTTEXT )
	{
		CString str;
		CScintillaCtrl& rCtrl = GetCtrl();
	
		int prevSymbol9 = rCtrl.GetCharAt( pos - 9);
		//str.Format(_T("PrevSymbol9...%d  " ), prevSymbol9);
		//AfxMessageBox(str);
				
		int prevSymbol8 = rCtrl.GetCharAt( pos - 8);
		//str.Format(_T("PrevSymbol8...%d  " ), prevSymbol8);
		//AfxMessageBox(str);
			
		
		int prevSymbol7 = rCtrl.GetCharAt( pos -  7);
		//str.Format(_T("PrevSymbol7...%d  " ), prevSymbol7);
		//AfxMessageBox(str);
		
		int prevSymbol6 = rCtrl.GetCharAt( pos - 6 );
		//str.Format(_T("PrevSymbol6...%d  " ), prevSymbol6);
		//AfxMessageBox(str);
		
		
		int prevSymbol5 = rCtrl.GetCharAt( pos - 5 );
		//str.Format(_T("PrevSymbol5...%d  " ), prevSymbol5);
		//AfxMessageBox(str);
		
		
		int prevSymbol4 = rCtrl.GetCharAt( pos - 4 );
		//str.Format(_T("PrevSymbol4...%d  " ), prevSymbol4);
		//AfxMessageBox(str);
		
		
		int prevSymbol3 = rCtrl.GetCharAt( pos - 3 );
		//str.Format(_T("PrevSymbol3...%d  " ), prevSymbol3);
		//AfxMessageBox(str);
		
		int prevSymbol2 = rCtrl.GetCharAt( pos - 2);
		//str.Format(_T("PrevSymbol2...%d  " ), prevSymbol2);
		//AfxMessageBox(str);
		
		int prevSymbol1 = rCtrl.GetCharAt( pos - 1);
		//str.Format(_T("PrevSymbol1...%d  " ), prevSymbol1);
		//AfxMessageBox(str);
		
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);
		
		int nextSymbol1 = rCtrl.GetCharAt(pos + 1);
		//str.Format(_T("NextSymbol1...%d  " ), nextSymbol1);
		//AfxMessageBox(str);

		int nextSymbol2 = rCtrl.GetCharAt(pos + 2);
		//str.Format(_T("NextSymbol2...%d  " ), nextSymbol2);
		//AfxMessageBox(str);

		int nextSymbol3 = rCtrl.GetCharAt(pos + 3);
		//str.Format(_T("NextSymbol3...%d  " ), nextSymbol3);
		//AfxMessageBox(str);

		int nextSymbol4 = rCtrl.GetCharAt(pos + 4);
		//str.Format(_T("NextSymbol4...%d  " ), nextSymbol4);
		//AfxMessageBox(str);


		int nextSymbol5 = rCtrl.GetCharAt(pos + 5);
		//str.Format(_T("NextSymbol5...%d  " ), nextSymbol5);
		//AfxMessageBox(str);

		int nextSymbol6 = rCtrl.GetCharAt(pos + 6);
		//str.Format(_T("NextSymbol6...%d  " ), nextSymbol6);
		//AfxMessageBox(str);
		
		int nextSymbol7 = rCtrl.GetCharAt(pos + 7);
		//str.Format(_T("NextSymbol7...%d  " ), nextSymbol7);
		//AfxMessageBox(str);

		int nextSymbol8 = rCtrl.GetCharAt(pos + 8);
		//str.Format(_T("NextSymbol8...%d  " ), nextSymbol8);
		//AfxMessageBox(str);
	
		int nextSymbol9 = rCtrl.GetCharAt(pos + 9);
		//str.Format(_T("NextSymbol9...%d  " ), nextSymbol9);
		//AfxMessageBox(str);

		int nextSymbol10 = rCtrl.GetCharAt(pos + 10);
		//str.Format(_T("NextSymbol10...%d  " ), nextSymbol10);
		//AfxMessageBox(str);
	
	
		
		if(    (prevSymbol9 == SPACE || prevSymbol9 == NEW_LINE || prevSymbol9 == CARRIAGE_RETURN || prevSymbol9 == NUL || prevSymbol9 == HORIZONTAL_TAB)
			&& prevSymbol8 == l1
			&& prevSymbol7 == l2
			&& prevSymbol6 == l3
			&& prevSymbol5 == l4
			&& prevSymbol4 == l5
			&& prevSymbol3 == l6 
			&& prevSymbol2 == l7 
			&& prevSymbol1 == l8 
			&& symbol == l9 
			&& (nextSymbol1 == SPACE || nextSymbol1 == NEW_LINE || nextSymbol1 == CARRIAGE_RETURN || nextSymbol1 ==  NUL || nextSymbol1 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			return pos - 8;
		}

		if(    (prevSymbol8 == SPACE || prevSymbol8 == NEW_LINE || prevSymbol8 == CARRIAGE_RETURN || prevSymbol8 == NUL || prevSymbol8 == HORIZONTAL_TAB)
			&& prevSymbol7 == l1
			&& prevSymbol6 == l2
			&& prevSymbol5 == l3 
			&& prevSymbol4 == l4 
			&& prevSymbol3 == l5 
			&& prevSymbol2 == l6 
			&& prevSymbol1 == l7 
			&& symbol == l8 
			&& nextSymbol1 == l9 
			&& (nextSymbol2 == SPACE || nextSymbol2 == NEW_LINE || nextSymbol2 == CARRIAGE_RETURN || nextSymbol2 ==  NUL || nextSymbol2 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			return pos - 7;
		}
			
		if(    (prevSymbol7 == SPACE || prevSymbol7 == NEW_LINE || prevSymbol7 == CARRIAGE_RETURN || prevSymbol7 == NUL || prevSymbol7 == HORIZONTAL_TAB)
			&& prevSymbol6 == l1
			&& prevSymbol5 == l2
			&& prevSymbol4 == l3
			&& prevSymbol3 == l4
			&& prevSymbol2 == l5
			&& prevSymbol1 == l6
			&& symbol == l7 
			&& nextSymbol1 == l8 
			&& nextSymbol2 == l9 
			&& (nextSymbol3 == SPACE || nextSymbol3 == NEW_LINE || nextSymbol3 == CARRIAGE_RETURN || nextSymbol3 ==  NUL || nextSymbol3 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			return pos - 6;
		}

		if(    (prevSymbol6 == SPACE || prevSymbol6 == NEW_LINE || prevSymbol6 == CARRIAGE_RETURN || prevSymbol6 == NUL || prevSymbol6 == HORIZONTAL_TAB)
			&& prevSymbol5 == l1
			&& prevSymbol4 == l2
			&& prevSymbol3 == l3
			&& prevSymbol2 == l4
			&& prevSymbol1 == l5
			&& symbol == l6 
			&& nextSymbol1 == l7 
			&& nextSymbol2 == l8 
			&& nextSymbol3 == l9 
			&& (nextSymbol4 == SPACE || nextSymbol4 == NEW_LINE || nextSymbol4 == CARRIAGE_RETURN || nextSymbol4 ==  NUL || nextSymbol4 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			return pos -5;
		}

		if(    (prevSymbol5 == SPACE || prevSymbol5 == NEW_LINE || prevSymbol5 == CARRIAGE_RETURN || prevSymbol5 == NUL || prevSymbol5 == HORIZONTAL_TAB)
			&& prevSymbol4 == l1
			&& prevSymbol3 == l2
			&& prevSymbol2 == l3
			&& prevSymbol1 == l4
			&& symbol == l5 
			&& nextSymbol1 == l6 
			&& nextSymbol2 == l7 
			&& nextSymbol3 == l8 
			&& nextSymbol4 == l9 
			&& (nextSymbol5 == SPACE || nextSymbol5 == NEW_LINE || nextSymbol5 == CARRIAGE_RETURN || nextSymbol5 ==  NUL || nextSymbol5 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			return pos - 4;
		}

		if(    (prevSymbol4 == SPACE || prevSymbol4 == NEW_LINE || prevSymbol4 == CARRIAGE_RETURN || prevSymbol4 == NUL || prevSymbol4 == HORIZONTAL_TAB)
			&& prevSymbol3 == l1
			&& prevSymbol2 == l2
			&& prevSymbol1 == l3
			&& symbol == l4 
			&& nextSymbol1 == l5 
			&& nextSymbol2 == l6 
			&& nextSymbol3 == l7 
			&& nextSymbol4 == l8
			&& nextSymbol5 == l9
			&& (nextSymbol6 == SPACE || nextSymbol6 == NEW_LINE || nextSymbol6 == CARRIAGE_RETURN || nextSymbol6 ==  NUL || nextSymbol6 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			return pos - 3;
		}

		if(    (prevSymbol3 == SPACE || prevSymbol3 == NEW_LINE || prevSymbol3 == CARRIAGE_RETURN || prevSymbol3 == NUL || prevSymbol3 == HORIZONTAL_TAB)
			&& prevSymbol2 == l1
			&& prevSymbol1 == l2
			&& symbol == l3 
			&& nextSymbol1 == l4 
			&& nextSymbol2 == l5 
			&& nextSymbol3 == l6 
			&& nextSymbol4 == l7
			&& nextSymbol5 == l8
			&& nextSymbol6 == l9
			&& (nextSymbol7 == SPACE || nextSymbol7 == NEW_LINE || nextSymbol7 == CARRIAGE_RETURN || nextSymbol7 ==  NUL || nextSymbol7 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			return pos - 2;
		}

		if(    (prevSymbol2 == SPACE || prevSymbol2 == NEW_LINE || prevSymbol2 == CARRIAGE_RETURN || prevSymbol2 == NUL || prevSymbol2 == HORIZONTAL_TAB)
			&& prevSymbol1 == l1 
			&& symbol == l2 
			&& nextSymbol1 == l3 
			&& nextSymbol2 == l4 
			&& nextSymbol3 == l5 
			&& nextSymbol4 == l6
			&& nextSymbol5 == l7
			&& nextSymbol6 == l8
			&& nextSymbol7 == l9
			&& (nextSymbol8 == SPACE || nextSymbol8 == NEW_LINE || nextSymbol8 == CARRIAGE_RETURN || nextSymbol8 ==  NUL || nextSymbol8 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			return pos - 1;
		}
	
		if(    (prevSymbol1 == SPACE || prevSymbol1 == NEW_LINE || prevSymbol1 == CARRIAGE_RETURN || prevSymbol1 == NUL || prevSymbol1 == HORIZONTAL_TAB)
			&& symbol == l1 
			&& nextSymbol1 == l2 
			&& nextSymbol2 == l3 
			&& nextSymbol3 == l4 
			&& nextSymbol4 == l5
			&& nextSymbol5 == l6
			&& nextSymbol6 == l7
			&& nextSymbol7 == l8
			&& nextSymbol8 == l9
			&& (nextSymbol9 == SPACE || nextSymbol9 == NEW_LINE || nextSymbol9 == CARRIAGE_RETURN || nextSymbol9 ==  NUL || nextSymbol9 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			return pos;
		}
		
		if(    (symbol == SPACE || symbol == NEW_LINE || symbol == CARRIAGE_RETURN || symbol == NUL || symbol == HORIZONTAL_TAB)
			&& nextSymbol1 == l1 
			&& nextSymbol2 == l2 
			&& nextSymbol3 == l3 
			&& nextSymbol4 == l4 
			&& nextSymbol5 == l5 
			&& nextSymbol6 == l6 
			&& nextSymbol7 == l7
			&& nextSymbol8 == l8
			&& nextSymbol9 == l9
			&& (nextSymbol10 == SPACE || nextSymbol10 == NEW_LINE || nextSymbol10 == CARRIAGE_RETURN || nextSymbol10 ==  NUL || nextSymbol10 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			if( isAlphaNumeric(prevSymbol1) )
			{
				return pos + 1;
			}
		}
	}


return NOT_FOUND;
}


long CAIPIEditorView::WSPDetectKeyWordEdit9( long pos, int l1, int l2, int l3, int l4, int l5, int l6, int l7, int l8, int l9)
{
	
	if( m_iModificationType == INSERTTEXT || m_iModificationType == BEFOREDELETE )
	{
		CString str;
		CScintillaCtrl& rCtrl = GetCtrl();
		
		int prevSymbol10 = rCtrl.GetCharAt( pos - 10 );
		//str.Format(_T("PrevSymbol10...%d  " ), prevSymbol10);
		//AfxMessageBox(str);
		
		
		int prevSymbol9 = rCtrl.GetCharAt( pos - 9 );
		//str.Format(_T("PrevSymbol9...%d  " ), prevSymbol9);
		//AfxMessageBox(str);
		
		
		int prevSymbol8 = rCtrl.GetCharAt( pos - 8 );
		//str.Format(_T("PrevSymbol8...%d  " ), prevSymbol8);
		//AfxMessageBox(str);
		
		int prevSymbol7 = rCtrl.GetCharAt( pos - 7 );
		//str.Format(_T("PrevSymbol7...%d  " ), prevSymbol7);
		//AfxMessageBox(str);
		
	
		int prevSymbol6 = rCtrl.GetCharAt( pos - 6 );
		//str.Format(_T("PrevSymbol6...%d  " ), prevSymbol6);
		//AfxMessageBox(str);
		

		int prevSymbol5 = rCtrl.GetCharAt( pos - 5 );
		//str.Format(_T("PrevSymbol5...%d  " ), prevSymbol5);
		//AfxMessageBox(str);
		
		
		int prevSymbol4 = rCtrl.GetCharAt( pos - 4 );
		//str.Format(_T("PrevSymbol4...%d  " ), prevSymbol4);
		//AfxMessageBox(str);
		
		
		int prevSymbol3 = rCtrl.GetCharAt( pos - 3 );
		//str.Format(_T("PrevSymbol3...%d  " ), prevSymbol3);
		//AfxMessageBox(str);
		
		int prevSymbol2 = rCtrl.GetCharAt( pos - 2);
		//str.Format(_T("PrevSymbol2...%d  " ), prevSymbol2);
		//AfxMessageBox(str);
		
		int prevSymbol1 = rCtrl.GetCharAt( pos - 1);
		//str.Format(_T("PrevSymbol1...%d  " ), prevSymbol1);
		//AfxMessageBox(str);
		
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);
		
		int nextSymbol1 = rCtrl.GetCharAt(pos + 1);
		//str.Format(_T("NextSymbol1...%d  " ), nextSymbol1);
		//AfxMessageBox(str);

		int nextSymbol2 = rCtrl.GetCharAt(pos + 2);
		//str.Format(_T("NextSymbol2...%d  " ), nextSymbol2);
		//AfxMessageBox(str);

		int nextSymbol3 = rCtrl.GetCharAt(pos + 3);
		//str.Format(_T("NextSymbol3...%d  " ), nextSymbol3);
		//AfxMessageBox(str);

		int nextSymbol4 = rCtrl.GetCharAt(pos + 4);
		//str.Format(_T("NextSymbol4...%d  " ), nextSymbol4);
		//AfxMessageBox(str);


		int nextSymbol5 = rCtrl.GetCharAt(pos + 5);
		//str.Format(_T("NextSymbol5...%d  " ), nextSymbol5);
		//AfxMessageBox(str);

		int nextSymbol6 = rCtrl.GetCharAt(pos + 6);
		//str.Format(_T("NextSymbol6...%d  " ), nextSymbol6);
		//AfxMessageBox(str);

		int nextSymbol7 = rCtrl.GetCharAt(pos + 7);
		//str.Format(_T("NextSymbol7...%d  " ), nextSymbol7);
		//AfxMessageBox(str);

		int nextSymbol8 = rCtrl.GetCharAt(pos + 8);
		//str.Format(_T("NextSymbol8...%d  " ), nextSymbol8);
		//AfxMessageBox(str);

		int nextSymbol9 = rCtrl.GetCharAt(pos + 9);
		//str.Format(_T("NextSymbol9...%d  " ), nextSymbol9);
		//AfxMessageBox(str);

		int nextSymbol10 = rCtrl.GetCharAt(pos + 10);
		//str.Format(_T("NextSymbol9...%d  " ), nextSymbol9);
		//AfxMessageBox(str);


		//Check cases of inserting a wrong caracter between the keyword
		
			if( prevSymbol1 == l9 )
			{
			   //AfxMessageBox(_T("Case prevS = l9"));
				//Case letter l9
				if(	prevSymbol2 == l8 && prevSymbol3 == l7 && prevSymbol4 == l6 && prevSymbol5 == l5 && prevSymbol6 == l4 && prevSymbol7 == l3 && prevSymbol8 == l2 && prevSymbol9 == l1
				&&  (prevSymbol10 == SPACE || prevSymbol10 == NEW_LINE || prevSymbol10 == CARRIAGE_RETURN || prevSymbol10 ==  NUL || prevSymbol10 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					return pos-9; 
				}
			}
            if( prevSymbol1 == l8 )
			{
				//AfxMessageBox(_T("Case prevS = l8"));
				//Case letter l8
				if(	prevSymbol2 == l7 && prevSymbol3 == l6 && prevSymbol4 == l5 && prevSymbol5 == l4 && prevSymbol6 == l3 && prevSymbol7 == l2 && prevSymbol8 == l1
				&&  (prevSymbol9 == SPACE || prevSymbol9 == NEW_LINE || prevSymbol9 == CARRIAGE_RETURN || prevSymbol9 ==  NUL || prevSymbol9 == HORIZONTAL_TAB )
				&& nextSymbol1 == l9
				&& (nextSymbol2 == SPACE || nextSymbol2 == NEW_LINE || nextSymbol2 == CARRIAGE_RETURN || nextSymbol2 ==  NUL || nextSymbol2 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					return pos-8; 
				}
			}
			
			if( prevSymbol1 == l7 )
			{
				//AfxMessageBox(_T("Case prevS = l7"));
				//Case letter l7
				if(	prevSymbol2 == l6  && prevSymbol3 == l5 && prevSymbol4 == l4 && prevSymbol5 == l3 && prevSymbol6 == l2 && prevSymbol7 == l1
				&&  (prevSymbol8 == SPACE || prevSymbol8 == NEW_LINE || prevSymbol8 == CARRIAGE_RETURN || prevSymbol8 ==  NUL || prevSymbol8 == HORIZONTAL_TAB )
				&& nextSymbol1 == l8 && nextSymbol2 == l9
				&& (nextSymbol3 == SPACE || nextSymbol3 == NEW_LINE || nextSymbol3 == CARRIAGE_RETURN || nextSymbol3 ==  NUL || nextSymbol3 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					return pos-7; 
				}
			}
			
			if( prevSymbol1 == l6 )
			{
				//AfxMessageBox(_T("Case prevS = l6"));
				//Case letter l6
				if(	prevSymbol2 == l5  && prevSymbol3 == l4 && prevSymbol4 == l3 && prevSymbol5 == l2 && prevSymbol6 == l1
				&&  (prevSymbol7 == SPACE || prevSymbol7 == NEW_LINE || prevSymbol7 == CARRIAGE_RETURN || prevSymbol7 ==  NUL || prevSymbol7 == HORIZONTAL_TAB )
				&& nextSymbol1 == l7 && nextSymbol2 == l8 && nextSymbol3 == l9
				&& (nextSymbol4 == SPACE || nextSymbol4 == NEW_LINE || nextSymbol4 == CARRIAGE_RETURN || nextSymbol4 ==  NUL || nextSymbol4 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					return pos-6; 
				}
			}
			
			if( prevSymbol1 == l5 )
			{
				//AfxMessageBox(_T("Case prevS = l5"));
				//Case letter l5
				if(	prevSymbol2 == l4 && prevSymbol3 == l3 && prevSymbol4 == l2 && prevSymbol5 == l1
				&&  (prevSymbol6 == SPACE || prevSymbol6 == NEW_LINE || prevSymbol6 == CARRIAGE_RETURN || prevSymbol6 ==  NUL || prevSymbol6 == HORIZONTAL_TAB )
				&& nextSymbol1 == l6 && nextSymbol2 == l7 && nextSymbol3 == l8 && nextSymbol4 == l9
				&& (nextSymbol5 == SPACE || nextSymbol5 == NEW_LINE || nextSymbol5 == CARRIAGE_RETURN || nextSymbol5 ==  NUL || nextSymbol5 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					return pos-5; 
				}
			}

			if( prevSymbol1 == l4 )
			{
				//AfxMessageBox(_T("Case prevS = l4"));
				//Case letter l4
				if(	prevSymbol2 == l3 && prevSymbol3 == l2 && prevSymbol4 == l1
				&&  (prevSymbol5 == SPACE || prevSymbol5 == NEW_LINE || prevSymbol5 == CARRIAGE_RETURN || prevSymbol5 ==  NUL || prevSymbol5 == HORIZONTAL_TAB )
				&& nextSymbol1 == l5 && nextSymbol2 == l6 && nextSymbol3 == l7 && nextSymbol4 == l8 && nextSymbol5 == l9
				&& (nextSymbol6 == SPACE || nextSymbol6 == NEW_LINE || nextSymbol6 == CARRIAGE_RETURN || nextSymbol6 ==  NUL || nextSymbol6 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					return pos-3; 
				}
			}

			if( prevSymbol1 == l3 )
			{
				//AfxMessageBox(_T("Case prevS = l3"));
				//Case letter l3
				if(	prevSymbol2 == l2 && prevSymbol3 == l1
				&&  (prevSymbol4 == SPACE || prevSymbol4 == NEW_LINE || prevSymbol4 == CARRIAGE_RETURN || prevSymbol4 ==  NUL || prevSymbol4 == HORIZONTAL_TAB )
				&& nextSymbol1 == l4 && nextSymbol2 == l5 && nextSymbol3 == l6 && nextSymbol4 == l7 && nextSymbol5 == l8 && nextSymbol6 == l9
				&& (nextSymbol7 == SPACE || nextSymbol7 == NEW_LINE || nextSymbol7 == CARRIAGE_RETURN || nextSymbol7 ==  NUL || nextSymbol7 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					return pos-2; 
				}
			}
			
			if( prevSymbol1 == l2 )
			{
				//AfxMessageBox(_T("Case prevS = l2"));
				//Case letter l2
				if(	prevSymbol2 == l1 
				&&  (prevSymbol3 == SPACE || prevSymbol3 == NEW_LINE || prevSymbol3 == CARRIAGE_RETURN || prevSymbol3 ==  NUL || prevSymbol3 == HORIZONTAL_TAB )
				&& nextSymbol1 == l3 && nextSymbol2 == l4 && nextSymbol3 == l5 && nextSymbol4 == l6 && nextSymbol5 == l7 && nextSymbol6 == l8 && nextSymbol7 == l9
				&& (nextSymbol8 == SPACE || nextSymbol8 == NEW_LINE || nextSymbol8 == CARRIAGE_RETURN || nextSymbol8 ==  NUL || nextSymbol8 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					return pos-1; 
				}
			}

			if ( prevSymbol1 == l1 )
			{
				//AfxMessageBox(_T("Case prevS = l1"));
				
				//Case letter l1
				if(	(prevSymbol2 == SPACE || prevSymbol2 == NEW_LINE || prevSymbol2 == CARRIAGE_RETURN || prevSymbol2 ==  NUL || prevSymbol2 == HORIZONTAL_TAB )
				&& nextSymbol1 == l2 && nextSymbol2 == l3 && nextSymbol3 == l4 && nextSymbol4 == l5 && nextSymbol5 == l6 && nextSymbol6 == l7 && nextSymbol7 == l8 && nextSymbol8 == l9
				&& (nextSymbol9 == SPACE || nextSymbol9 == NEW_LINE || nextSymbol9 == CARRIAGE_RETURN || nextSymbol9 ==  NUL || nextSymbol9 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					return pos; 
				}
			}
			if ( prevSymbol1 != SPACE || prevSymbol1 != NEW_LINE || prevSymbol1 != CARRIAGE_RETURN || prevSymbol1 != NUL || prevSymbol1 != HORIZONTAL_TAB )
			{
				//AfxMessageBox(_T("Case prevS = Space"));
				
				//Case letter empty
				if( nextSymbol1 == l1 && nextSymbol2 == l2 && nextSymbol3 == l3 && nextSymbol4 == l4 && nextSymbol5 == l5 && nextSymbol6 == l6 && nextSymbol7 == l7 && nextSymbol8 == l8 && nextSymbol9 == l9
				&& (nextSymbol10 == SPACE || nextSymbol10 == NEW_LINE || nextSymbol10 == CARRIAGE_RETURN || nextSymbol10 ==  NUL || nextSymbol10 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					if( isAlphaNumeric(prevSymbol2) )
					{
						return pos + 1;
					}
				}
			}

			
		
		
			
		
	}


return NOT_FOUND;
}



long CAIPIEditorView::WSPDetectRuleKeyWord(long pos)
{
	CString str;
	CScintillaCtrl& rCtrl = GetCtrl();
	int R = 82;
	int U = 85;
	int L = 76;
	int E = 69;
	
	

	if( m_iModificationType == BEFOREDELETE )
	{
		int prevSymbol4 = rCtrl.GetCharAt( pos - 4 );
		//str.Format(_T("PrevSymbol4...%d  " ), prevSymbol4);
		//AfxMessageBox(str);
		
		
		int prevSymbol3 = rCtrl.GetCharAt( pos - 3 );
		//str.Format(_T("PrevSymbol3...%d  " ), prevSymbol3);
		//AfxMessageBox(str);
		
		int prevSymbol2 = rCtrl.GetCharAt( pos - 2);
		//str.Format(_T("PrevSymbol2...%d  " ), prevSymbol2);
		//AfxMessageBox(str);
		
		int prevSymbol1 = rCtrl.GetCharAt( pos - 1);
		//str.Format(_T("PrevSymbol1...%d  " ), prevSymbol1);
		//AfxMessageBox(str);
		
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);
		
		int nextSymbol1 = rCtrl.GetCharAt(pos + 1);
		//str.Format(_T("NextSymbol1...%d  " ), nextSymbol1);
		//AfxMessageBox(str);

		int nextSymbol2 = rCtrl.GetCharAt(pos + 2);
		//str.Format(_T("NextSymbol2...%d  " ), nextSymbol2);
		//AfxMessageBox(str);

		int nextSymbol3 = rCtrl.GetCharAt(pos + 3);
		//str.Format(_T("NextSymbol3...%d  " ), nextSymbol3);
		//AfxMessageBox(str);

		int nextSymbol4 = rCtrl.GetCharAt(pos + 4);
		//str.Format(_T("NextSymbol4...%d  " ), nextSymbol4);
		//AfxMessageBox(str);


		int nextSymbol5 = rCtrl.GetCharAt(pos + 5);
		//str.Format(_T("NextSymbol5...%d  " ), nextSymbol5);
		//AfxMessageBox(str);

		
		if(    (prevSymbol4 == SPACE || prevSymbol4 == NEW_LINE || prevSymbol4 == CARRIAGE_RETURN || prevSymbol4 == NUL || prevSymbol4 == HORIZONTAL_TAB)
			&& prevSymbol3 == R 
			&& prevSymbol2 == U 
			&& prevSymbol1 == L 
			&& symbol == E 
			&& (nextSymbol1 == SPACE || nextSymbol1 == NEW_LINE || nextSymbol1 == CARRIAGE_RETURN || nextSymbol1 ==  NUL || nextSymbol1 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			m_bFlagBeforeDelete = true;
			return pos -3;
		}

		if(    (prevSymbol3 == SPACE || prevSymbol3 == NEW_LINE || prevSymbol3 == CARRIAGE_RETURN || prevSymbol3 == NUL || prevSymbol3 == HORIZONTAL_TAB)
			&& prevSymbol2 == R 
			&& prevSymbol1 == U 
			&& symbol == L 
			&& nextSymbol1 == E 
			&& (nextSymbol2 == SPACE || nextSymbol2 == NEW_LINE || nextSymbol2 == CARRIAGE_RETURN || nextSymbol2 ==  NUL || nextSymbol2 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			m_bFlagBeforeDelete = true;
			return pos - 2;
		}
			
		if(    (prevSymbol2 == SPACE || prevSymbol2 == NEW_LINE || prevSymbol2 == CARRIAGE_RETURN || prevSymbol2 == NUL || prevSymbol2 == HORIZONTAL_TAB)
			&& prevSymbol1 == R 
			&& symbol == U 
			&& nextSymbol1 == L 
			&& nextSymbol2 == E 
			&& (nextSymbol3 == SPACE || nextSymbol3 == NEW_LINE || nextSymbol3 == CARRIAGE_RETURN || nextSymbol3 ==  NUL || nextSymbol3 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			m_bFlagBeforeDelete = true;
			return pos - 1;
		}

		if(    (prevSymbol1 == SPACE || prevSymbol1 == NEW_LINE || prevSymbol1 == CARRIAGE_RETURN || prevSymbol1 == NUL || prevSymbol1 == HORIZONTAL_TAB)
			&& symbol == R 
			&& nextSymbol1 == U 
			&& nextSymbol2 == L 
			&& nextSymbol3 == E 
			&& (nextSymbol4 == SPACE || nextSymbol4 == NEW_LINE || nextSymbol4 == CARRIAGE_RETURN || nextSymbol4 ==  NUL || nextSymbol4 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			m_bFlagBeforeDelete = true;
			return pos;
		}

		if(    (symbol == SPACE || symbol == NEW_LINE || symbol == CARRIAGE_RETURN || symbol == NUL || symbol == HORIZONTAL_TAB)
			&& nextSymbol1 == R 
			&& nextSymbol2 == U 
			&& nextSymbol3 == L 
			&& nextSymbol4 == E 
			&& (nextSymbol5 == SPACE || nextSymbol5 == NEW_LINE || nextSymbol5 == CARRIAGE_RETURN || nextSymbol5 ==  NUL || nextSymbol5 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			m_bFlagBeforeDelete = true;
			return pos - 1;
		}


	}


	if( m_iModificationType == INSERTTEXT )
	{
				
		int prevSymbol4 = rCtrl.GetCharAt( pos - 4 );
		//str.Format(_T("PrevSymbol4...%d  " ), prevSymbol4);
		//AfxMessageBox(str);
		
		
		int prevSymbol3 = rCtrl.GetCharAt( pos - 3 );
		//str.Format(_T("PrevSymbol3...%d  " ), prevSymbol3);
		//AfxMessageBox(str);
		
		int prevSymbol2 = rCtrl.GetCharAt( pos - 2);
		//str.Format(_T("PrevSymbol2...%d  " ), prevSymbol2);
		//AfxMessageBox(str);
		
		int prevSymbol1 = rCtrl.GetCharAt( pos - 1);
		//str.Format(_T("PrevSymbol1...%d  " ), prevSymbol1);
		//AfxMessageBox(str);
		
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);
		
		int nextSymbol1 = rCtrl.GetCharAt(pos + 1);
		//str.Format(_T("NextSymbol1...%d  " ), nextSymbol1);
		//AfxMessageBox(str);

		int nextSymbol2 = rCtrl.GetCharAt(pos + 2);
		//str.Format(_T("NextSymbol2...%d  " ), nextSymbol2);
		//AfxMessageBox(str);

		int nextSymbol3 = rCtrl.GetCharAt(pos + 3);
		//str.Format(_T("NextSymbol3...%d  " ), nextSymbol3);
		//AfxMessageBox(str);

		int nextSymbol4 = rCtrl.GetCharAt(pos + 4);
		//str.Format(_T("NextSymbol4...%d  " ), nextSymbol4);
		//AfxMessageBox(str);


		int nextSymbol5 = rCtrl.GetCharAt(pos + 5);
		//str.Format(_T("NextSymbol5...%d  " ), nextSymbol5);
		//AfxMessageBox(str);

		if(    (prevSymbol4 == SPACE || prevSymbol4 == NEW_LINE || prevSymbol4 == CARRIAGE_RETURN || prevSymbol4 == NUL || prevSymbol4 == HORIZONTAL_TAB)
			&& prevSymbol3 == R 
			&& prevSymbol2 == U 
			&& prevSymbol1 == L 
			&& symbol == E 
			&& (nextSymbol1 == SPACE || nextSymbol1 == NEW_LINE || nextSymbol1 == CARRIAGE_RETURN || nextSymbol1 ==  NUL || nextSymbol1 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			m_bFlagInsertText = true;
			return pos -3;
		}

		if(    (prevSymbol3 == SPACE || prevSymbol3 == NEW_LINE || prevSymbol3 == CARRIAGE_RETURN || prevSymbol3 == NUL || prevSymbol3 == HORIZONTAL_TAB)
			&& prevSymbol2 == R 
			&& prevSymbol1 == U 
			&& symbol == L 
			&& nextSymbol1 == E 
			&& (nextSymbol2 == SPACE || nextSymbol2 == NEW_LINE || nextSymbol2 == CARRIAGE_RETURN || nextSymbol2 ==  NUL || nextSymbol2 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			m_bFlagInsertText = true;
			return pos - 2;
		}
			
		if(    (prevSymbol2 == SPACE || prevSymbol2 == NEW_LINE || prevSymbol2 == CARRIAGE_RETURN || prevSymbol2 == NUL || prevSymbol2 == HORIZONTAL_TAB)
			&& prevSymbol1 == R 
			&& symbol == U 
			&& nextSymbol1 == L 
			&& nextSymbol2 == E 
			&& (nextSymbol3 == SPACE || nextSymbol3 == NEW_LINE || nextSymbol3 == CARRIAGE_RETURN || nextSymbol3 ==  NUL || nextSymbol3 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			m_bFlagInsertText = true;
			return pos - 1;
		}

		if(    (prevSymbol1 == SPACE || prevSymbol1 == NEW_LINE || prevSymbol1 == CARRIAGE_RETURN || prevSymbol1 == NUL || prevSymbol1 == HORIZONTAL_TAB)
			&& symbol == R 
			&& nextSymbol1 == U 
			&& nextSymbol2 == L 
			&& nextSymbol3 == E 
			&& (nextSymbol4 == SPACE || nextSymbol4 == NEW_LINE || nextSymbol4 == CARRIAGE_RETURN || nextSymbol4 ==  NUL || nextSymbol4 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			m_bFlagInsertText = true;
			return pos;
		}

		if(    (symbol == SPACE || symbol == NEW_LINE || symbol == CARRIAGE_RETURN || symbol == NUL || symbol == HORIZONTAL_TAB)
			&& nextSymbol1 == R 
			&& nextSymbol2 == U 
			&& nextSymbol3 == L 
			&& nextSymbol4 == E 
			&& (nextSymbol5 == SPACE || nextSymbol5 == NEW_LINE || nextSymbol5 == CARRIAGE_RETURN || nextSymbol5 ==  NUL || nextSymbol5 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			m_bFlagInsertText = true;
			return pos - 1;
		}

	
	}


/*
	if( m_iModificationType == BEFOREINSERT )
	{
		int prevSymbol4 = rCtrl.GetCharAt( pos - 4 );
		//str.Format(_T("PrevSymbol4...%d  " ), prevSymbol4);
		//AfxMessageBox(str);
		
		
		int prevSymbol3 = rCtrl.GetCharAt( pos - 3 );
		//str.Format(_T("PrevSymbol3...%d  " ), prevSymbol3);
		//AfxMessageBox(str);
		
		int prevSymbol2 = rCtrl.GetCharAt( pos - 2);
		//str.Format(_T("PrevSymbol2...%d  " ), prevSymbol2);
		//AfxMessageBox(str);
		
		int prevSymbol1 = rCtrl.GetCharAt( pos - 1);
		//str.Format(_T("PrevSymbol1...%d  " ), prevSymbol1);
		//AfxMessageBox(str);
		
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);
		
		int nextSymbol1 = rCtrl.GetCharAt(pos + 1);
		//str.Format(_T("NextSymbol1...%d  " ), nextSymbol1);
		//AfxMessageBox(str);

		int nextSymbol2 = rCtrl.GetCharAt(pos + 2);
		//str.Format(_T("NextSymbol2...%d  " ), nextSymbol2);
		//AfxMessageBox(str);

		int nextSymbol3 = rCtrl.GetCharAt(pos + 3);
		//str.Format(_T("NextSymbol3...%d  " ), nextSymbol3);
		//AfxMessageBox(str);

		//int nextSymbol4 = rCtrl.GetCharAt(pos + 4);
		//str.Format(_T("NextSymbol4...%d  " ), nextSymbol4);
		//AfxMessageBox(str);


		int nextSymbol5 = rCtrl.GetCharAt(pos + 5);
		str.Format(_T("NextSymbol5...%d  " ), nextSymbol5);
		//AfxMessageBox(str);

		if(    (prevSymbol4 == SPACE || prevSymbol4 == NEW_LINE || prevSymbol4 == CARRIAGE_RETURN || prevSymbol4 == NUL || prevSymbol4 == HORIZONTAL_TAB)
			&& prevSymbol3 == R 
			&& prevSymbol2 == U 
			&& prevSymbol1 == L 
			&& (symbol == SPACE || symbol == NEW_LINE || symbol == CARRIAGE_RETURN || symbol ==  NUL || symbol == HORIZONTAL_TAB )
			
		  )
		{
			//AfxMessageBox(_T("Detected"));
			m_bFlagBeforeInsert = true;
			return pos -3;
		}
		
		if(    (prevSymbol3 == SPACE || prevSymbol3 == NEW_LINE || prevSymbol3 == CARRIAGE_RETURN || prevSymbol3 == NUL || prevSymbol3 == HORIZONTAL_TAB)
			&& prevSymbol2 == R 
			&& prevSymbol1 == U 
			&& symbol == E 
			&& (nextSymbol1 == SPACE || nextSymbol1 == NEW_LINE || nextSymbol1 == CARRIAGE_RETURN || nextSymbol1 ==  NUL || nextSymbol1 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			m_bFlagBeforeInsert = true;
			return pos - 2;
		}
			
		if(    (prevSymbol2 == SPACE || prevSymbol2 == NEW_LINE || prevSymbol2 == CARRIAGE_RETURN || prevSymbol2 == NUL || prevSymbol2 == HORIZONTAL_TAB)
			&& prevSymbol1 == R 
			&& symbol == L 
			&& nextSymbol1 == E 
			&& (nextSymbol2 == SPACE || nextSymbol2 == NEW_LINE || nextSymbol2 == CARRIAGE_RETURN || nextSymbol2 ==  NUL || nextSymbol2 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			m_bFlagBeforeInsert = true;
			return pos - 1;
		}

		if(    (prevSymbol1 == SPACE || prevSymbol1 == NEW_LINE || prevSymbol1 == CARRIAGE_RETURN || prevSymbol1 == NUL || prevSymbol1 == HORIZONTAL_TAB)
			&& symbol == U 
			&& nextSymbol1 == L 
			&& nextSymbol2 == E 
			&& (nextSymbol3 == SPACE || nextSymbol3 == NEW_LINE || nextSymbol3 == CARRIAGE_RETURN || nextSymbol3 ==  NUL || nextSymbol3 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			m_bFlagBeforeInsert = true;
			return pos;
		}

	}




	if( m_iModificationType == DELETETEXT )
	{
		int prevSymbol4 = rCtrl.GetCharAt( pos - 4 );
		//str.Format(_T("PrevSymbol4...%d  " ), prevSymbol4);
		//AfxMessageBox(str);
		
		
		int prevSymbol3 = rCtrl.GetCharAt( pos - 3 );
		//str.Format(_T("PrevSymbol3...%d  " ), prevSymbol3);
		//AfxMessageBox(str);
		
		int prevSymbol2 = rCtrl.GetCharAt( pos - 2);
		//str.Format(_T("PrevSymbol2...%d  " ), prevSymbol2);
		//AfxMessageBox(str);
		
		int prevSymbol1 = rCtrl.GetCharAt( pos - 1);
		//str.Format(_T("PrevSymbol1...%d  " ), prevSymbol1);
		//AfxMessageBox(str);
		
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);
		
		int nextSymbol1 = rCtrl.GetCharAt(pos + 1);
		//str.Format(_T("NextSymbol1...%d  " ), nextSymbol1);
		//AfxMessageBox(str);

		int nextSymbol2 = rCtrl.GetCharAt(pos + 2);
		//str.Format(_T("NextSymbol2...%d  " ), nextSymbol2);
		//AfxMessageBox(str);

		int nextSymbol3 = rCtrl.GetCharAt(pos + 3);
		//str.Format(_T("NextSymbol3...%d  " ), nextSymbol3);
		//AfxMessageBox(str);

		//int nextSymbol4 = rCtrl.GetCharAt(pos + 4);
		//str.Format(_T("NextSymbol4...%d  " ), nextSymbol4);
		//AfxMessageBox(str);


		int nextSymbol5 = rCtrl.GetCharAt(pos + 5);
		str.Format(_T("NextSymbol5...%d  " ), nextSymbol5);
		//AfxMessageBox(str);

		if(    (prevSymbol4 == SPACE || prevSymbol4 == NEW_LINE || prevSymbol4 == CARRIAGE_RETURN || prevSymbol4 == NUL || prevSymbol4 == HORIZONTAL_TAB)
			&& prevSymbol3 == R 
			&& prevSymbol2 == U 
			&& prevSymbol1 == L 
			&& (symbol == SPACE || symbol == NEW_LINE || symbol == CARRIAGE_RETURN || symbol ==  NUL || symbol == HORIZONTAL_TAB )
			
		  )
		{
			
			//AfxMessageBox(_T("Detected"));
			m_bFlagDeleteText = true;
			return pos -3;
		}
		
		if(    (prevSymbol3 == SPACE || prevSymbol3 == NEW_LINE || prevSymbol3 == CARRIAGE_RETURN || prevSymbol3 == NUL || prevSymbol3 == HORIZONTAL_TAB)
			&& prevSymbol2 == R 
			&& prevSymbol1 == U 
			&& symbol == E 
			&& (nextSymbol1 == SPACE || nextSymbol1 == NEW_LINE || nextSymbol1 == CARRIAGE_RETURN || nextSymbol1 ==  NUL || nextSymbol1 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			m_bFlagDeleteText = true;
			return pos - 2;
		}
			
		if(    (prevSymbol2 == SPACE || prevSymbol2 == NEW_LINE || prevSymbol2 == CARRIAGE_RETURN || prevSymbol2 == NUL || prevSymbol2 == HORIZONTAL_TAB)
			&& prevSymbol1 == R 
			&& symbol == L 
			&& nextSymbol1 == E 
			&& (nextSymbol2 == SPACE || nextSymbol2 == NEW_LINE || nextSymbol2 == CARRIAGE_RETURN || nextSymbol2 ==  NUL || nextSymbol2 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			m_bFlagDeleteText = true;
			return pos - 1;
		}

		if(    (prevSymbol1 == SPACE || prevSymbol1 == NEW_LINE || prevSymbol1 == CARRIAGE_RETURN || prevSymbol1 == NUL || prevSymbol1 == HORIZONTAL_TAB)
			&& symbol == U 
			&& nextSymbol1 == L 
			&& nextSymbol2 == E 
			&& (nextSymbol3 == SPACE || nextSymbol3 == NEW_LINE || nextSymbol3 == CARRIAGE_RETURN || nextSymbol3 ==  NUL || nextSymbol3 == HORIZONTAL_TAB )
		  )
		{
			//AfxMessageBox(_T("Detected"));
			m_bFlagDeleteText = true;
			return pos;
		}


	}
	
*/
	
return NOT_FOUND;

}


long CAIPIEditorView::WSPDetectRuleKeyWordEdit( long pos)
{
	
	
	if( m_iModificationType == INSERTTEXT || m_iModificationType == BEFOREDELETE )
	{
		CString str;
		CScintillaCtrl& rCtrl = GetCtrl();
		int R = 82;
		int U = 85;
		int L = 76;
		int E = 69;
		


		int prevSymbol5 = rCtrl.GetCharAt( pos - 5 );
		//str.Format(_T("PrevSymbol5...%d  " ), prevSymbol5);
		//AfxMessageBox(str);
		
		
		int prevSymbol4 = rCtrl.GetCharAt( pos - 4 );
		//str.Format(_T("PrevSymbol4...%d  " ), prevSymbol4);
		//AfxMessageBox(str);
		
		
		int prevSymbol3 = rCtrl.GetCharAt( pos - 3 );
		//str.Format(_T("PrevSymbol3...%d  " ), prevSymbol3);
		//AfxMessageBox(str);
		
		int prevSymbol2 = rCtrl.GetCharAt( pos - 2);
		//str.Format(_T("PrevSymbol2...%d  " ), prevSymbol2);
		//AfxMessageBox(str);
		
		int prevSymbol1 = rCtrl.GetCharAt( pos - 1);
		//str.Format(_T("PrevSymbol1...%d  " ), prevSymbol1);
		//AfxMessageBox(str);
		
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);
		
		int nextSymbol1 = rCtrl.GetCharAt(pos + 1);
		//str.Format(_T("NextSymbol1...%d  " ), nextSymbol1);
		//AfxMessageBox(str);

		int nextSymbol2 = rCtrl.GetCharAt(pos + 2);
		//str.Format(_T("NextSymbol2...%d  " ), nextSymbol2);
		//AfxMessageBox(str);

		int nextSymbol3 = rCtrl.GetCharAt(pos + 3);
		//str.Format(_T("NextSymbol3...%d  " ), nextSymbol3);
		//AfxMessageBox(str);

		int nextSymbol4 = rCtrl.GetCharAt(pos + 4);
		//str.Format(_T("NextSymbol4...%d  " ), nextSymbol4);
		//AfxMessageBox(str);


		int nextSymbol5 = rCtrl.GetCharAt(pos + 5);
		//str.Format(_T("NextSymbol5...%d  " ), nextSymbol5);
		//AfxMessageBox(str);

		//Check cases of inserting a wrong caracter between the keyword
		if( symbol != R && symbol != U && symbol != L && symbol != E )
		{
			
			
			if( prevSymbol1 == E )
			{
			   //AfxMessageBox(_T("Case prevS = E"));
				//Case letter E
				if(	prevSymbol2 == L && prevSymbol3 == U && prevSymbol4 == R 
				&&  (prevSymbol5 == SPACE || prevSymbol5 == NEW_LINE || prevSymbol5 == CARRIAGE_RETURN || prevSymbol5 ==  NUL || prevSymbol5 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					return pos-3; 
				}
			}
            else if( prevSymbol1 == L )
			{
				//AfxMessageBox(_T("Case prevS = L"));
				//Case letter L
				if(	prevSymbol2 == U && prevSymbol3 == R  
				&&  (prevSymbol4 == SPACE || prevSymbol4 == NEW_LINE || prevSymbol4 == CARRIAGE_RETURN || prevSymbol4 ==  NUL || prevSymbol4 == HORIZONTAL_TAB )
				&& nextSymbol1 == E
				&& (nextSymbol2 == SPACE || nextSymbol2 == NEW_LINE || nextSymbol2 == CARRIAGE_RETURN || nextSymbol2 ==  NUL || nextSymbol2 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					return pos-2; 
				}
			}
			
			else if( prevSymbol1 == U )
			{
				//AfxMessageBox(_T("Case prevS = U"));
				//Case letter L
				if(	prevSymbol2 == R  
				&&  (prevSymbol3 == SPACE || prevSymbol3 == NEW_LINE || prevSymbol3 == CARRIAGE_RETURN || prevSymbol3 ==  NUL || prevSymbol3 == HORIZONTAL_TAB )
				&& nextSymbol1 == L && nextSymbol2 == E
				&& (nextSymbol3 == SPACE || nextSymbol3 == NEW_LINE || nextSymbol3 == CARRIAGE_RETURN || nextSymbol3 ==  NUL || nextSymbol3 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					return pos-2; 
				}
			}
			
			else if ( prevSymbol1 == R )
			{
				//AfxMessageBox(_T("Case prevS = R"));
				
				//Case letter R
				if(	(prevSymbol2 == SPACE || prevSymbol2 == NEW_LINE || prevSymbol2 == CARRIAGE_RETURN || prevSymbol2 ==  NUL || prevSymbol2 == HORIZONTAL_TAB )
				&& nextSymbol1 == U && nextSymbol2 == L && nextSymbol3 == E 
				&& (nextSymbol4 == SPACE || nextSymbol4 == NEW_LINE || nextSymbol4 == CARRIAGE_RETURN || nextSymbol4 ==  NUL || nextSymbol4 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					return pos-1; 
				}
			}
			
			if ( prevSymbol1 != SPACE || prevSymbol1 != NEW_LINE || prevSymbol1 != CARRIAGE_RETURN || prevSymbol1 != NUL || prevSymbol1 != HORIZONTAL_TAB )
			{
				//AfxMessageBox(_T("Case prevS = Space"));
				
				//Case letter empty
				if( nextSymbol1 == R && nextSymbol2 == U && nextSymbol3 == L && nextSymbol4 == E  
				&& (nextSymbol5 == SPACE || nextSymbol5 == NEW_LINE || nextSymbol5 == CARRIAGE_RETURN || nextSymbol5 ==  NUL || nextSymbol5 == HORIZONTAL_TAB )
				)
				{	  
					//AfxMessageBox(_T("Detected"));
					return pos + 1; 
				}
			}

			
		}
		
			
		
	}


return NOT_FOUND;
}





void CAIPIEditorView::WSPRuleUndo()
{
	
	
	CScintillaCtrl& rCtrl = GetCtrl();
	CString str;
	
	
	//1- Insert text step by step
	//2- Undo step by step ( Deletes the inserted text)
	if( m_iModificationType == PERFORMED_UNDO )
	{
		//AfxMessageBox(_T("Performed Undo"));

		long pos = rCtrl.GetCurrentPos();
		//str.Format(_T("Pos...%d  " ), pos);
		//AfxMessageBox(str);	
		if( !m_posPasteStart.empty() && !m_posPasteEnd.empty() )
		{
			if( m_posPasteEnd.top() == pos )
			{
				//AfxMessageBox(_T("paste entro"));
				long posStart = m_posPasteStart.top();
				WSPDeleteSelectedRules(posStart, pos, false);
				m_posPasteStart.pop();
				m_posPasteEnd.pop();
			}

		}
		
		int symbol = rCtrl.GetCharAt(pos - 1);
		//str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);
		if( symbol == CLOSE_PARENTHESIS )
		{
			WSPDeleteRule(pos -1, true);		
	
		}
	}

	//1- Deletes text step by step
	//2- Undo step by step ( Adds the deleted text again)
	if( m_iModificationType == MULTISTEP_UNDOINSERT )
	{
		//AfxMessageBox(_T("MultiStep UndoInsert"));
		
		if( m_bFlagUndoInsert == false )
		{
		 g_currentPos = rCtrl.GetCurrentPos();
		 m_StartLimit = g_currentPos;
		 //str.Format(_T("Start Pos...%d  " ), m_StartLimit);
		 //AfxMessageBox(str);
		 m_bFlagUndoInsert = true;
		  	
		 
		}

		long pos = g_currentPos++;
		//str.Format(_T("End Pos...%d  " ), pos);
		//AfxMessageBox(str);
			
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);
		
		if( symbol == CLOSE_PARENTHESIS )
		{
			WSPAddRule(pos, true);
			m_StartLimit = pos;	
				
		}
				
	}	
	
	

		
	//Detects the last step for the Undo and Redo functions
	if( m_iModificationType == LASTSTEPUNDOINSERT || m_iModificationType == LASTSTEPUNDOREDO )
	{
		//AfxMessageBox(_T("last step undo"));
		
		m_bFlagUndoInsert = false;
		long pos = g_currentPos++;
		
		//str.Format(_T("End Pos...%d  " ), pos);
		//AfxMessageBox(str);
			
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);

		
		if( symbol == CLOSE_PARENTHESIS )
		{
			WSPAddRule( pos, true);
			m_StartLimit = pos;	
			
		}
		
	}
	
	//1- Paste some text on the editor (Insert rules)
	//2- Undo the paste process (Delete inserted rules)
	if( m_iModificationType == MULTILINEUNDOINSERT )
	{
		//AfxMessageBox(_T("Multiline Undo INSERT"));
		
		long posStart = rCtrl.GetCurrentPos();
		//str.Format(_T("Pos Start...%d  " ), posStart);
		//AfxMessageBox(str);	
		
		//Gets the end position of the clipboard paste	
		long posEnd = m_nPasteLength + posStart;
		//str.Format(_T("Pos End...%d  " ), posEnd);
		//AfxMessageBox(str);	
		
		WSPDeleteSelectedRules(posStart, posEnd, true);

	}

	//1- Delete a selection block text
	//2- Undo the erase process ( Add deleted rules)
	if( m_iModificationType == MULTILINEUNDODELETE )
	{
		//AfxMessageBox(_T("Multiline Undo DELETE"));
		
		
		long posStart = rCtrl.GetCurrentPos();
		//str.Format(_T("Pos Start...%d  " ), posStart);
		//AfxMessageBox(str);	
		
		//Gets the end position of the clipboard paste	
		long posEnd = m_nPasteLength + posStart;
		//str.Format(_T("Pos End...%d  " ), posEnd);
		//AfxMessageBox(str);	
		
		WSPAddSelectedRules(posStart, posEnd, true);

	}

	

}


void CAIPIEditorView::WSPRuleRedo()
{
	CScintillaCtrl& rCtrl = GetCtrl();
	CString str;
	
	//1- Delete rules
	//2- Undo process adds rules deleted
	//3- Redo process deletes the rules added
	if( m_iModificationType == MULTILINEREDO )
	{
		//AfxMessageBox(_T("multiline redo"));
		long pos = rCtrl.GetCurrentPos();
		//str.Format(_T("Pos...%d  " ), pos);
		//AfxMessageBox(str);
			
		int symbol = rCtrl.GetCharAt(pos - 1);
		//str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);

		if( symbol == CLOSE_PARENTHESIS )
		{
			WSPDeleteRule( pos -1, true);	
		}
		
	}
	
	//1- Undo process deletes rules step by step
	//2- Redo process adds rules deleted step by step
	if( m_iModificationType == PERFORMED_REDO || m_iModificationType == LASTSTEPREDO)
	{
		//AfxMessageBox(_T("Performed Redo y Last Redo"));
		if( m_bFlagRedoInsert == false )
		{
		 g_currentPos = rCtrl.GetCurrentPos();
		 m_StartLimit = g_currentPos;
		 //str.Format(_T("Start Pos...%d  " ), m_StartLimit);
		 //AfxMessageBox(str);
		 m_bFlagRedoInsert = true;
	 
		}

		long pos = g_currentPos++;
		//str.Format(_T("End Pos...%d  " ), pos);
		//AfxMessageBox(str);
			
		int symbol = rCtrl.GetCharAt(pos-1);
		//str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);
		
		if( symbol == CLOSE_PARENTHESIS )
		{
			WSPAddRule(pos - 1, true);
		}

		if( m_iModificationType == LASTSTEPREDO )
		{
			m_bFlagRedoInsert = false;
		}

	}

	//1- Paste several selected rules
	//2- Undo process deletes the pasted rules
	//3- Redo process add the deleted rules
	if( m_iModificationType == MULTILINEREDOINSERT )
	{
		//AfxMessageBox(_T("multiline redo INSERT "));

		long posStart = rCtrl.GetCurrentPos();
		//str.Format(_T("Pos Start...%d  " ), posStart);
		//AfxMessageBox(str);	
		
		//Gets the end position of the clipboard paste	
		long posEnd = m_nPasteLength + posStart;
		//str.Format(_T("Pos End...%d  " ), posEnd);
		//AfxMessageBox(str);	
		
		WSPAddSelectedRules(posStart, posEnd, true);

	}

	//1- Delete several selected rules
	//2- Undo process add the selected rules deleted
	//2- Redo process deletes the rules added
	if( m_iModificationType == MULTILINEREDODELETE )
	{
		//AfxMessageBox(_T("multiline redo DELETE "));
		
		long posStart = rCtrl.GetCurrentPos();
		//str.Format(_T("Pos Start...%d  " ), posStart);
		//AfxMessageBox(str);	
		
		//Gets the end position of the clipboard paste	
		long posEnd = m_nPasteLength + posStart;
		//str.Format(_T("Pos End...%d  " ), posEnd);
		//AfxMessageBox(str);	
		
		WSPDeleteSelectedRules(posStart, posEnd, true);


	}

}




void CAIPIEditorView::WSPCommentRule(long pos )
{
	LPSTR szKeyWord = "RULE";
	LPSTR szOpenParenthesis = "(";
	LPSTR szCloseParenthesis = ")";
	LPSTR szDobleQuotation = "\"";
	LPSTR szOpenComment = "/*";
	LPSTR szCloseComment = "*/";
	LPSTR szLineComment = "//";

	
	CScintillaCtrl& rCtrl = GetCtrl();
	CString str;
		
	
	
	if( m_iModificationType == BEFOREDELETE )
	{
		long posOpenComment = WSPDetectOpenComment(pos-1);
		
		/// Detecting open comment token ///
		if( posOpenComment != NOT_FOUND )
		{
			long posCloseComment = WSPSearchToken( posOpenComment, m_DocumentLength, szCloseComment);
			//str.Format(_T("Pos Close Comment %d"), posCloseComment);
			//AfxMessageBox(str);
			
			if( posCloseComment != NOT_FOUND )
			{
				WSPAddSelectedRules(posOpenComment, posCloseComment, false);
				WSPAddSelectedRules(posOpenComment, posCloseComment, true);
			}
			else
			{
				WSPAddSelectedRules(posOpenComment, m_DocumentLength -1, true);
			}
		}
				
			
		/// Detecting close comment token ///
		long posCloseComment = WSPDetectCloseComment(pos-1);	
	
		if( posCloseComment != NOT_FOUND )
		{
			//AfxMessageBox(_T("CLOSE COMMENT Before Delete Detectado"));
			long posOpenComment = WSPSearchToken(posCloseComment, 0, szOpenComment);
			//str.Format(_T("Pos Open Comment %d"), posOpenComment);
			//AfxMessageBox(str);
			
			if( posOpenComment != NOT_FOUND)
			{
				//WSPAddSelectedRules(posOpenComment, posCloseComment, false);
				long posNextCloseComment = WSPSearchToken(posCloseComment + 3, m_DocumentLength , szCloseComment);
				//str.Format(_T("Pos Next Close Comment %d"), posNextCloseComment);
				//AfxMessageBox(str);
				if( posNextCloseComment != NOT_FOUND )
				{
					WSPDeleteSelectedRules(posCloseComment, posNextCloseComment, true);
				}
			}

		}

		/// Detecting line comments ////
		
		long posLineComment = WSPDetectLineComment( pos-1);
	
		if( posLineComment != NOT_FOUND )
		{
			//AfxMessageBox(_T("LINE COMMENT Before Delete Detectado"));
			int nLine = rCtrl.LineFromPosition(posLineComment);
			long posStartLine = rCtrl.PositionFromLine(nLine);
			long posEndLine	= rCtrl.GetLineEndPosition( nLine);
			long posRule = WSPSearchToken(posStartLine, posEndLine, szKeyWord);
			long posCloseParenthesis = WSPSearchToken( posRule, m_DocumentLength, szCloseParenthesis);
			//str.Format(_T("PosRule %d"), posRule);
			//AfxMessageBox(str);
			if( posRule != NOT_FOUND )
			{
				int r = WSPParseRule( posRule -1, posCloseParenthesis);
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					WSPAddRule(posRule + 5, false);
				}
			}
			
		}

	}
	


	if( m_iModificationType == INSERTTEXT )
	{
		/// Detecting open comment token ///
		long posOpenComment = WSPDetectOpenComment(pos);

		if( posOpenComment != NOT_FOUND  )
		{
			//AfxMessageBox(_T("OPEN COMMENT Insert Detectado"));
			

			long posCloseComment = WSPSearchToken(posOpenComment, m_DocumentLength, szCloseComment);	
			//str.Format(_T("Pos Close Comment %d"), posCloseComment);
			//AfxMessageBox(str);
			if( posCloseComment != NOT_FOUND )
			{
				WSPDeleteSelectedRules( posOpenComment, posCloseComment, false);	
			}
			else
			{
				//WSPDeleteSelectedRules( posOpenDocument, docLength, false);
			}
		}

		/// Detecting close comment token ///	
		long posCloseComment = WSPDetectCloseComment(pos);
		
		if( posCloseComment != NOT_FOUND )
		{
			//AfxMessageBox(_T("CLOSE COMMENT Insert Detectado"));
			
			long posPrevOpenComment = WSPSearchToken(posCloseComment, 0, szOpenComment);
			//str.Format(_T("Prev Pos Open Comment %d"), posPrevOpenComment);
			//AfxMessageBox(str);
			long posPrevCloseComment = WSPSearchToken(posCloseComment - 3, 0, szCloseComment);	
			//str.Format(_T("Prev Pos Close Comment %d"), posPrevCloseComment);
			//AfxMessageBox(str);
			
			if( posPrevOpenComment != NOT_FOUND && posPrevOpenComment > posPrevCloseComment )
			{
				//AfxMessageBox(_T("Detectado"));
				WSPDeleteSelectedRules(posPrevOpenComment, posCloseComment, false);	
			}
			
			long posNextCloseComment = WSPSearchToken( posCloseComment + 3, m_DocumentLength, szCloseComment);
			//str.Format(_T("Pos Next Close Comment %d"), posNextCloseComment);
			//AfxMessageBox(str);
			if( posNextCloseComment != NOT_FOUND )
			{
				WSPAddSelectedRules(posCloseComment + 3, posNextCloseComment +3, true);
			}
			else
			{
				//WSPAddSelectedRules(posCloseComment - 1, docLength);
			}
	
		}

			
		/// Detecting line comments ////
		long posLineComment = WSPDetectLineComment( pos);

		if( posLineComment != NOT_FOUND )
		{
			//AfxMessageBox(_T("LINE COMMENT Insert Detectado"));
				
			int nLine = rCtrl.LineFromPosition(posLineComment);
			long posStartLine = rCtrl.PositionFromLine(nLine);
			long posEndLine	= rCtrl.GetLineEndPosition( nLine);
			long posRule = WSPSearchToken(posStartLine, posEndLine, szKeyWord);
			long posCloseParenthesis = WSPSearchToken( posRule, m_DocumentLength, szCloseParenthesis);
			/*
			str.Format(_T("Pos Rule %d"), posRule);
			AfxMessageBox(str);
			str.Format(_T("Pos Close Parenthesis %d"), posCloseParenthesis);
			AfxMessageBox(str);
			*/
			if( posRule != NOT_FOUND )
			{
				int r = WSPParseRule( posRule -1, posCloseParenthesis);
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					//AfxMessageBox(_T("No Error"));
					WSPDeleteRule( posRule + 5, false );
				}
			}
			
		}

	}

}




void CAIPIEditorView::WSPCommentFunction(long pos, LPSTR szType, int typelen )
{
	
	LPSTR szOpenParenthesis = "(";
	LPSTR szCloseParenthesis = ")";
	LPSTR szOpenComment = "/*";
	LPSTR szCloseComment = "*/";
	LPSTR szLineComment = "//";

	
	CScintillaCtrl& rCtrl = GetCtrl();
	CString str;
		
	
	
	if( m_iModificationType == BEFOREDELETE )
	{
		long posOpenComment = WSPDetectOpenComment(pos-1);
		
		/// Detecting open comment token ///
		if( posOpenComment != NOT_FOUND )
		{
			long posCloseComment = WSPSearchToken( posOpenComment, m_DocumentLength, szCloseComment);
			//str.Format(_T("Pos Close Comment %d"), posCloseComment);
			//AfxMessageBox(str);
			
			if( posCloseComment != NOT_FOUND )
			{
				WSPAddSelectedFunctions(posOpenComment, posCloseComment, szType, typelen, false);
				WSPAddSelectedFunctions(posOpenComment, posCloseComment, szType, typelen, true);
			}
			else
			{
				WSPAddSelectedFunctions(posOpenComment, m_DocumentLength -1, szType, typelen, true);
			}
		}
				
			
		/// Detecting close comment token ///
		long posCloseComment = WSPDetectCloseComment(pos-1);	
	
		if( posCloseComment != NOT_FOUND )
		{
			//AfxMessageBox(_T("CLOSE COMMENT Before Delete Detectado"));
			long posOpenComment = WSPSearchToken(posCloseComment, 0, szOpenComment);
			//str.Format(_T("Pos Open Comment %d"), posOpenComment);
			//AfxMessageBox(str);
			
			if( posOpenComment != NOT_FOUND)
			{
				//WSPAddSelectedRules(posOpenComment, posCloseComment, false);
				long docLength = rCtrl.GetTextLength();
				long posNextCloseComment = WSPSearchToken(posCloseComment + 3, docLength, szCloseComment);
				//str.Format(_T("Pos Next Close Comment %d"), posNextCloseComment);
				//AfxMessageBox(str);
				if( posNextCloseComment != NOT_FOUND )
				{
					WSPDeleteSelectedFunctions(posCloseComment, posNextCloseComment, szType, typelen, true);
				}
			}

		}

		/// Detecting line comments ////
		
		long posLineComment = WSPDetectLineComment( pos -1);
	
		if( posLineComment != NOT_FOUND )
		{
			//AfxMessageBox(_T("LINE COMMENT Before Delete Detectado"));
			int nLine = rCtrl.LineFromPosition(posLineComment);
			long posStartLine = rCtrl.PositionFromLine(nLine);
			long posEndLine	= rCtrl.GetLineEndPosition( nLine);
			long posIdType = WSPSearchToken(posLineComment, posEndLine, szType);
			long posCloseParenthesis = WSPSearchToken( posIdType, m_DocumentLength, szCloseParenthesis); 
			//str.Format(_T("PosIdType %d"), posIdType);
			//AfxMessageBox(str);
		
			if( posIdType != NOT_FOUND )
			{
				int r = WSPParseFunction( posIdType -1, posCloseParenthesis );
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					WSPAddFunction(posIdType + typelen, false );
				}
			}
			
		}

	}
	


	if( m_iModificationType == INSERTTEXT )
	{
		/// Detecting open comment token ///
		long posOpenComment = WSPDetectOpenComment(pos);

		if( posOpenComment != NOT_FOUND  )
		{
			//AfxMessageBox(_T("OPEN COMMENT Insert Detectado"));
			

			long posCloseComment = WSPSearchToken(posOpenComment, m_DocumentLength, szCloseComment);	
			//str.Format(_T("Pos Close Comment %d"), posCloseComment);
			//AfxMessageBox(str);
			if( posCloseComment != NOT_FOUND )
			{
				WSPDeleteSelectedFunctions( posOpenComment, posCloseComment, szType, typelen, false);	
			}
			else
			{
				//WSPDeleteSelectedFunctions( posOpenDocument, m_DocumentLength, szType, typelen, false);
			}
		}

		/// Detecting close comment token ///	
		long posCloseComment = WSPDetectCloseComment(pos);
		
		if( posCloseComment != NOT_FOUND )
		{
			/*
			AfxMessageBox(_T("CLOSE COMMENT FUNCTION Insert Detectado"));
			CString s = szType;
			AfxMessageBox(s);
			*/
			long posPrevOpenComment = WSPSearchToken(posCloseComment, 0, szOpenComment);
			//str.Format(_T("Prev Pos Open Comment %d"), posPrevOpenComment);
			//AfxMessageBox(str);
			long posPrevCloseComment = WSPSearchToken(posCloseComment - 3, 0, szCloseComment);	
			//str.Format(_T("Prev Pos Close Comment %d"), posPrevCloseComment);
			//AfxMessageBox(str);
			
			if( posPrevOpenComment != NOT_FOUND && posPrevOpenComment > posPrevCloseComment )
			{
				//AfxMessageBox(_T("Detectado"));
				WSPDeleteSelectedFunctions(posPrevOpenComment, posCloseComment, szType, typelen, false);	
			}
				
			long posNextCloseComment = WSPSearchToken( posCloseComment + 3, m_DocumentLength, szCloseComment);
			//str.Format(_T("Pos Next Close Comment %d"), posNextCloseComment);
			//AfxMessageBox(str);
			
			if( posNextCloseComment != NOT_FOUND )
			{
				WSPAddSelectedFunctions(posCloseComment + 3, posNextCloseComment + 3, szType, typelen, true);
			}
			else
			{
				//WSPAddSelectedFunctions(posCloseComment - 1, m_DocumentLength, szType, typelen, true);
			}
	
		}

			
		/// Detecting line comments ////
		long posLineComment = WSPDetectLineComment( pos );

		if( posLineComment != NOT_FOUND )
		{
			//AfxMessageBox(_T("LINE COMMENT Insert Detectado"));
				
			int nLine = rCtrl.LineFromPosition(posLineComment);
			long posStartLine = rCtrl.PositionFromLine(nLine);
			long posEndLine	= rCtrl.GetLineEndPosition( nLine);
			long posIdType = WSPSearchNearestIdType(posLineComment, posEndLine);
			long posCloseParenthesis = WSPSearchToken( posIdType, m_DocumentLength, szCloseParenthesis); 
			
			if( posIdType != NOT_FOUND )
			{
				int r = WSPParseFunction( posIdType -1, posCloseParenthesis );
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					WSPDeleteFunction( posIdType + typelen, false );
				}
			}
			
		}

	}

  

}


void CAIPIEditorView::WSPCommentJSFunction(long pos )
{
	
	LPSTR szOpenParenthesis = "(";
	LPSTR szCloseParenthesis = ")";
	LPSTR szOpenComment = "/*";
	LPSTR szCloseComment = "*/";
	LPSTR szLineComment = "//";

	
	CScintillaCtrl& rCtrl = GetCtrl();
	CString str;
		
	
	
	if( m_iModificationType == BEFOREDELETE )
	{
		long posOpenComment = WSPDetectOpenComment(pos-1);
		
		/// Detecting open comment token ///
		if( posOpenComment != NOT_FOUND )
		{
			long posCloseComment = WSPSearchToken( posOpenComment, m_DocumentLength, szCloseComment);
			//str.Format(_T("Pos Close Comment %d"), posCloseComment);
			//AfxMessageBox(str);
			
			if( posCloseComment != NOT_FOUND )
			{
				WSPAddSelectedJSFunctions(posOpenComment, posCloseComment, false);
				WSPAddSelectedJSFunctions(posOpenComment, posCloseComment, true);
			}
			else
			{
				WSPAddSelectedJSFunctions(posOpenComment, m_DocumentLength -1, true);
			}
		}
				
			
		/// Detecting close comment token ///
		long posCloseComment = WSPDetectCloseComment(pos-1);	
	
		if( posCloseComment != NOT_FOUND )
		{
			//AfxMessageBox(_T("CLOSE COMMENT Before Delete Detectado"));
			long posOpenComment = WSPSearchToken(posCloseComment, 0, szOpenComment);
			//str.Format(_T("Pos Open Comment %d"), posOpenComment);
			//AfxMessageBox(str);
			
			if( posOpenComment != NOT_FOUND)
			{
				//WSPAddSelectedRules(posOpenComment, posCloseComment, false);
				long docLength = rCtrl.GetTextLength();
				long posNextCloseComment = WSPSearchToken(posCloseComment + 3, docLength, szCloseComment);
				//str.Format(_T("Pos Next Close Comment %d"), posNextCloseComment);
				//AfxMessageBox(str);
				if( posNextCloseComment != NOT_FOUND )
				{
					WSPDeleteSelectedJSFunctions(posCloseComment, posNextCloseComment, true);
				}
			}

		}

		/// Detecting line comments ////
		
		long posLineComment = WSPDetectLineComment( pos -1);
	
		if( posLineComment != NOT_FOUND )
		{
			LPSTR szKeyWord = "function";
			//AfxMessageBox(_T("LINE COMMENT Before Delete Detectado"));
			int nLine = rCtrl.LineFromPosition(posLineComment);
			long posStartLine = rCtrl.PositionFromLine(nLine);
			long posEndLine	= rCtrl.GetLineEndPosition( nLine);
			long posFunction = WSPSearchToken(posLineComment, posEndLine, szKeyWord);
			long posCloseParenthesis = WSPSearchToken( posFunction, m_DocumentLength, szCloseParenthesis); 
			//str.Format(_T("PosIdType %d"), posIdType);
			//AfxMessageBox(str);
		
			if( posFunction != NOT_FOUND )
			{
				int r = WSPParseJSFunction( posFunction -1, posCloseParenthesis );
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					WSPAddJSFunction(posFunction + 8, false );
				}
			}
			
		}

	}
	


	if( m_iModificationType == INSERTTEXT )
	{
		/// Detecting open comment token ///
		long posOpenComment = WSPDetectOpenComment(pos);

		if( posOpenComment != NOT_FOUND  )
		{
			//AfxMessageBox(_T("OPEN COMMENT Insert Detectado"));
			

			long posCloseComment = WSPSearchToken(posOpenComment, m_DocumentLength, szCloseComment);	
			//str.Format(_T("Pos Close Comment %d"), posCloseComment);
			//AfxMessageBox(str);
			if( posCloseComment != NOT_FOUND )
			{
				WSPDeleteSelectedJSFunctions( posOpenComment, posCloseComment, false);	
			}
			else
			{
				//WSPDeleteSelectedJSFunctions( posOpenDocument, m_DocumentLength, false);
			}
		}

		/// Detecting close comment token ///	
		long posCloseComment = WSPDetectCloseComment(pos);
		
		if( posCloseComment != NOT_FOUND )
		{
			/*
			AfxMessageBox(_T("CLOSE COMMENT FUNCTION Insert Detectado"));
			CString s = szType;
			AfxMessageBox(s);
			*/
			long posPrevOpenComment = WSPSearchToken(posCloseComment, 0, szOpenComment);
			//str.Format(_T("Prev Pos Open Comment %d"), posPrevOpenComment);
			//AfxMessageBox(str);
			long posPrevCloseComment = WSPSearchToken(posCloseComment - 3, 0, szCloseComment);	
			//str.Format(_T("Prev Pos Close Comment %d"), posPrevCloseComment);
			//AfxMessageBox(str);
			
			if( posPrevOpenComment != NOT_FOUND && posPrevOpenComment > posPrevCloseComment )
			{
				//AfxMessageBox(_T("Detectado"));
				WSPDeleteSelectedJSFunctions(posPrevOpenComment, posCloseComment, false);	
			}
				
			long posNextCloseComment = WSPSearchToken( posCloseComment + 3, m_DocumentLength, szCloseComment);
			//str.Format(_T("Pos Next Close Comment %d"), posNextCloseComment);
			//AfxMessageBox(str);
			
			if( posNextCloseComment != NOT_FOUND )
			{
				WSPAddSelectedJSFunctions(posCloseComment + 3, posNextCloseComment + 3, true);
			}
			else
			{
				//WSPAddSelectedJSFunctions(posCloseComment - 1, m_DocumentLength, true);
			}
	
		}

			
		/// Detecting line comments ////
		long posLineComment = WSPDetectLineComment( pos );

		if( posLineComment != NOT_FOUND )
		{
			//AfxMessageBox(_T("LINE COMMENT Insert Detectado"));
			LPSTR szKeyWord = "function";
			
			int nLine = rCtrl.LineFromPosition(posLineComment);
			long posStartLine = rCtrl.PositionFromLine(nLine);
			long posEndLine	= rCtrl.GetLineEndPosition( nLine);
			long posFunction = WSPSearchToken(posLineComment, posEndLine, szKeyWord);
			long posCloseParenthesis = WSPSearchToken( posFunction, m_DocumentLength, szCloseParenthesis); 
			
			if( posFunction != NOT_FOUND )
			{
				int r = WSPParseJSFunction( posFunction -1, posCloseParenthesis );
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					WSPDeleteJSFunction( posFunction + 8, false );
				}
			}
			
		}

	}

  

}





void CAIPIEditorView::WSPCommentVBSFunction(long pos )
{
	
	LPSTR szOpenParenthesis = "(";
	LPSTR szCloseParenthesis = ")";
	LPSTR szOpenComment = "/*";
	LPSTR szCloseComment = "*/";
	LPSTR szLineComment = "//";

	
	CScintillaCtrl& rCtrl = GetCtrl();
	CString str;
		
	
	
	if( m_iModificationType == BEFOREDELETE )
	{
		long posOpenComment = WSPDetectOpenComment(pos-1);
		
		/// Detecting open comment token ///
		if( posOpenComment != NOT_FOUND )
		{
			long posCloseComment = WSPSearchToken( posOpenComment, m_DocumentLength, szCloseComment);
			//str.Format(_T("Pos Close Comment %d"), posCloseComment);
			//AfxMessageBox(str);
			
			if( posCloseComment != NOT_FOUND )
			{
				WSPAddSelectedVBSFunctions(posOpenComment, posCloseComment, false);
				WSPAddSelectedVBSFunctions(posOpenComment, posCloseComment, true);
			}
			else
			{
				WSPAddSelectedVBSFunctions(posOpenComment, m_DocumentLength -1, true);
			}
		}
				
			
		/// Detecting close comment token ///
		long posCloseComment = WSPDetectCloseComment(pos-1);	
	
		if( posCloseComment != NOT_FOUND )
		{
			//AfxMessageBox(_T("CLOSE COMMENT Before Delete Detectado"));
			long posOpenComment = WSPSearchToken(posCloseComment, 0, szOpenComment);
			//str.Format(_T("Pos Open Comment %d"), posOpenComment);
			//AfxMessageBox(str);
			
			if( posOpenComment != NOT_FOUND)
			{
				//WSPAddSelectedRules(posOpenComment, posCloseComment, false);
				long docLength = rCtrl.GetTextLength();
				long posNextCloseComment = WSPSearchToken(posCloseComment + 3, docLength, szCloseComment);
				//str.Format(_T("Pos Next Close Comment %d"), posNextCloseComment);
				//AfxMessageBox(str);
				if( posNextCloseComment != NOT_FOUND )
				{
					WSPDeleteSelectedVBSFunctions(posCloseComment, posNextCloseComment, true);
				}
			}

		}

		/// Detecting line comments ////
		
		long posLineComment = WSPDetectLineComment( pos -1);
	
		if( posLineComment != NOT_FOUND )
		{
			LPSTR szKeyWord = "Function";
			//AfxMessageBox(_T("LINE COMMENT Before Delete Detectado"));
			int nLine = rCtrl.LineFromPosition(posLineComment);
			long posStartLine = rCtrl.PositionFromLine(nLine);
			long posEndLine	= rCtrl.GetLineEndPosition( nLine);
			long posFunction = WSPSearchToken(posLineComment, posEndLine, szKeyWord);
			long posCloseParenthesis = WSPSearchToken( posFunction, m_DocumentLength, szCloseParenthesis); 
			//str.Format(_T("PosIdType %d"), posIdType);
			//AfxMessageBox(str);
		
			if( posFunction != NOT_FOUND )
			{
				int r = WSPParseVBSFunction( posFunction -1, posCloseParenthesis );
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					WSPAddVBSFunction(posFunction + 8, false );
				}
			}
			
		}

	}
	


	if( m_iModificationType == INSERTTEXT )
	{
		/// Detecting open comment token ///
		long posOpenComment = WSPDetectOpenComment(pos);

		if( posOpenComment != NOT_FOUND  )
		{
			//AfxMessageBox(_T("OPEN COMMENT Insert Detectado"));
			

			long posCloseComment = WSPSearchToken(posOpenComment, m_DocumentLength, szCloseComment);	
			//str.Format(_T("Pos Close Comment %d"), posCloseComment);
			//AfxMessageBox(str);
			if( posCloseComment != NOT_FOUND )
			{
				WSPDeleteSelectedVBSFunctions( posOpenComment, posCloseComment, false);	
			}
			else
			{
				//WSPDeleteSelectedVBSFunctions( posOpenDocument, m_DocumentLength, false);
			}
		}

		/// Detecting close comment token ///	
		long posCloseComment = WSPDetectCloseComment(pos);
		
		if( posCloseComment != NOT_FOUND )
		{
			/*
			AfxMessageBox(_T("CLOSE COMMENT FUNCTION Insert Detectado"));
			CString s = szType;
			AfxMessageBox(s);
			*/
			long posPrevOpenComment = WSPSearchToken(posCloseComment, 0, szOpenComment);
			//str.Format(_T("Prev Pos Open Comment %d"), posPrevOpenComment);
			//AfxMessageBox(str);
			long posPrevCloseComment = WSPSearchToken(posCloseComment - 3, 0, szCloseComment);	
			//str.Format(_T("Prev Pos Close Comment %d"), posPrevCloseComment);
			//AfxMessageBox(str);
			
			if( posPrevOpenComment != NOT_FOUND && posPrevOpenComment > posPrevCloseComment )
			{
				//AfxMessageBox(_T("Detectado"));
				WSPDeleteSelectedVBSFunctions(posPrevOpenComment, posCloseComment, false);	
			}
				
			long posNextCloseComment = WSPSearchToken( posCloseComment + 3, m_DocumentLength, szCloseComment);
			//str.Format(_T("Pos Next Close Comment %d"), posNextCloseComment);
			//AfxMessageBox(str);
			
			if( posNextCloseComment != NOT_FOUND )
			{
				WSPAddSelectedVBSFunctions(posCloseComment + 3, posNextCloseComment + 3, true);
			}
			else
			{
				//WSPAddSelectedVBSFunctions(posCloseComment - 1, m_DocumentLength, true);
			}
	
		}

			
		/// Detecting line comments ////
		long posLineComment = WSPDetectLineComment( pos );

		if( posLineComment != NOT_FOUND )
		{
			//AfxMessageBox(_T("LINE COMMENT Insert Detectado"));
			LPSTR szKeyWord = "Function";
			
			int nLine = rCtrl.LineFromPosition(posLineComment);
			long posStartLine = rCtrl.PositionFromLine(nLine);
			long posEndLine	= rCtrl.GetLineEndPosition( nLine);
			long posFunction = WSPSearchToken(posLineComment, posEndLine, szKeyWord);
			long posCloseParenthesis = WSPSearchToken( posFunction, m_DocumentLength, szCloseParenthesis); 
			
			if( posFunction != NOT_FOUND )
			{
				int r = WSPParseVBSFunction( posFunction -1, posCloseParenthesis );
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					WSPDeleteVBSFunction( posFunction + 8, false );
				}
			}
			
		}

	}

  

}


void CAIPIEditorView::WSPCommentVBSFUNCTION(long pos )
{
	
	LPSTR szOpenParenthesis = "(";
	LPSTR szCloseParenthesis = ")";
	LPSTR szOpenComment = "/*";
	LPSTR szCloseComment = "*/";
	LPSTR szLineComment = "//";

	
	CScintillaCtrl& rCtrl = GetCtrl();
	CString str;
		
	
	
	if( m_iModificationType == BEFOREDELETE )
	{
		long posOpenComment = WSPDetectOpenComment(pos-1);
		
		/// Detecting open comment token ///
		if( posOpenComment != NOT_FOUND )
		{
			long posCloseComment = WSPSearchToken( posOpenComment, m_DocumentLength, szCloseComment);
			//str.Format(_T("Pos Close Comment %d"), posCloseComment);
			//AfxMessageBox(str);
			
			if( posCloseComment != NOT_FOUND )
			{
				WSPAddSelectedVBSFUNCTIONS(posOpenComment, posCloseComment, false);
				WSPAddSelectedVBSFUNCTIONS(posOpenComment, posCloseComment, true);
			}
			else
			{
				WSPAddSelectedVBSFUNCTIONS(posOpenComment, m_DocumentLength -1, true);
			}
		}
				
			
		/// Detecting close comment token ///
		long posCloseComment = WSPDetectCloseComment(pos-1);	
	
		if( posCloseComment != NOT_FOUND )
		{
			//AfxMessageBox(_T("CLOSE COMMENT Before Delete Detectado"));
			long posOpenComment = WSPSearchToken(posCloseComment, 0, szOpenComment);
			//str.Format(_T("Pos Open Comment %d"), posOpenComment);
			//AfxMessageBox(str);
			
			if( posOpenComment != NOT_FOUND)
			{
				//WSPAddSelectedRules(posOpenComment, posCloseComment, false);
				long docLength = rCtrl.GetTextLength();
				long posNextCloseComment = WSPSearchToken(posCloseComment + 3, docLength, szCloseComment);
				//str.Format(_T("Pos Next Close Comment %d"), posNextCloseComment);
				//AfxMessageBox(str);
				if( posNextCloseComment != NOT_FOUND )
				{
					WSPDeleteSelectedVBSFUNCTIONS(posCloseComment, posNextCloseComment, true);
				}
			}

		}

		/// Detecting line comments ////
		
		long posLineComment = WSPDetectLineComment( pos -1);
	
		if( posLineComment != NOT_FOUND )
		{
			LPSTR szKeyWord = "FUNCTION";
			//AfxMessageBox(_T("LINE COMMENT Before Delete Detectado"));
			int nLine = rCtrl.LineFromPosition(posLineComment);
			long posStartLine = rCtrl.PositionFromLine(nLine);
			long posEndLine	= rCtrl.GetLineEndPosition( nLine);
			long posFunction = WSPSearchToken(posLineComment, posEndLine, szKeyWord);
			long posCloseParenthesis = WSPSearchToken( posFunction, m_DocumentLength, szCloseParenthesis); 
			//str.Format(_T("PosIdType %d"), posIdType);
			//AfxMessageBox(str);
		
			if( posFunction != NOT_FOUND )
			{
				int r = WSPParseVBSFunction( posFunction -1, posCloseParenthesis );
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					WSPAddVBSFUNCTION(posFunction + 8, false );
				}
			}
			
		}

	}
	


	if( m_iModificationType == INSERTTEXT )
	{
		/// Detecting open comment token ///
		long posOpenComment = WSPDetectOpenComment(pos);

		if( posOpenComment != NOT_FOUND  )
		{
			//AfxMessageBox(_T("OPEN COMMENT Insert Detectado"));
			

			long posCloseComment = WSPSearchToken(posOpenComment, m_DocumentLength, szCloseComment);	
			//str.Format(_T("Pos Close Comment %d"), posCloseComment);
			//AfxMessageBox(str);
			if( posCloseComment != NOT_FOUND )
			{
				WSPDeleteSelectedVBSFUNCTIONS( posOpenComment, posCloseComment, false);	
			}
			else
			{
				//WSPDeleteSelectedVBSFUNCTIONS( posOpenDocument, m_DocumentLength, false);
			}
		}

		/// Detecting close comment token ///	
		long posCloseComment = WSPDetectCloseComment(pos);
		
		if( posCloseComment != NOT_FOUND )
		{
			/*
			AfxMessageBox(_T("CLOSE COMMENT FUNCTION Insert Detectado"));
			CString s = szType;
			AfxMessageBox(s);
			*/
			long posPrevOpenComment = WSPSearchToken(posCloseComment, 0, szOpenComment);
			//str.Format(_T("Prev Pos Open Comment %d"), posPrevOpenComment);
			//AfxMessageBox(str);
			long posPrevCloseComment = WSPSearchToken(posCloseComment - 3, 0, szCloseComment);	
			//str.Format(_T("Prev Pos Close Comment %d"), posPrevCloseComment);
			//AfxMessageBox(str);
			
			if( posPrevOpenComment != NOT_FOUND && posPrevOpenComment > posPrevCloseComment )
			{
				//AfxMessageBox(_T("Detectado"));
				WSPDeleteSelectedVBSFUNCTIONS(posPrevOpenComment, posCloseComment, false);	
			}
				
			long posNextCloseComment = WSPSearchToken( posCloseComment + 3, m_DocumentLength, szCloseComment);
			//str.Format(_T("Pos Next Close Comment %d"), posNextCloseComment);
			//AfxMessageBox(str);
			
			if( posNextCloseComment != NOT_FOUND )
			{
				WSPAddSelectedVBSFUNCTIONS(posCloseComment + 3, posNextCloseComment + 3, true);
			}
			else
			{
				//WSPAddSelectedVBSFUNCTIONS(posCloseComment - 1, m_DocumentLength, true);
			}
	
		}

			
		/// Detecting line comments ////
		long posLineComment = WSPDetectLineComment( pos );

		if( posLineComment != NOT_FOUND )
		{
			//AfxMessageBox(_T("LINE COMMENT Insert Detectado"));
			LPSTR szKeyWord = "FUNCTION";
			
			int nLine = rCtrl.LineFromPosition(posLineComment);
			long posStartLine = rCtrl.PositionFromLine(nLine);
			long posEndLine	= rCtrl.GetLineEndPosition( nLine);
			long posFunction = WSPSearchToken(posLineComment, posEndLine, szKeyWord);
			long posCloseParenthesis = WSPSearchToken( posFunction, m_DocumentLength, szCloseParenthesis); 
			
			if( posFunction != NOT_FOUND )
			{
				int r = WSPParseVBSFunction( posFunction -1, posCloseParenthesis );
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					WSPDeleteVBSFUNCTION( posFunction + 8, false );
				}
			}
			
		}

	}

  

}








void CAIPIEditorView::WSPCommentVariable(long pos, LPSTR szType, int typelen )
{
	
	
	LPSTR szOpenComment = "/*";
	LPSTR szCloseComment = "*/";
	LPSTR szLineComment = "//";

	
	CScintillaCtrl& rCtrl = GetCtrl();
	CString str;
		
	
	
	if( m_iModificationType == BEFOREDELETE )
	{
		long posOpenComment = WSPDetectOpenComment(pos-1);
		
		/// Detecting open comment token ///
		if( posOpenComment != NOT_FOUND )
		{
			long posCloseComment = WSPSearchToken( posOpenComment, m_DocumentLength, szCloseComment);
			//str.Format(_T("Pos Close Comment %d"), posCloseComment);
			//AfxMessageBox(str);
			
			if( posCloseComment != NOT_FOUND )
			{
				WSPAddSelectedVariables(posOpenComment, posCloseComment, szType, typelen, false);
				WSPAddSelectedVariables(posOpenComment, posCloseComment, szType, typelen, true);
			}
			else
			{
				WSPAddSelectedVariables(posOpenComment, m_DocumentLength -1, szType, typelen, true);
			}
		}
				
			
		/// Detecting close comment token ///
		long posCloseComment = WSPDetectCloseComment(pos-1);	
	
		if( posCloseComment != NOT_FOUND )
		{
			//AfxMessageBox(_T("CLOSE COMMENT Before Delete Detectado"));
			long posOpenComment = WSPSearchToken(posCloseComment, 0, szOpenComment);
			//str.Format(_T("Pos Open Comment %d"), posOpenComment);
			//AfxMessageBox(str);
			
			if( posOpenComment != NOT_FOUND)
			{
				//WSPAddSelectedRules(posOpenComment, posCloseComment, false);
				long docLength = rCtrl.GetTextLength();
				long posNextCloseComment = WSPSearchToken(posCloseComment + 3, docLength, szCloseComment);
				//str.Format(_T("Pos Next Close Comment %d"), posNextCloseComment);
				//AfxMessageBox(str);
				if( posNextCloseComment != NOT_FOUND )
				{
					WSPDeleteSelectedVariables(posCloseComment, posNextCloseComment, szType, typelen, true);
				}
			}

		}

		/// Detecting line comments ////
		
		long posLineComment = WSPDetectLineComment( pos -1);
	
		if( posLineComment != NOT_FOUND )
		{
			LPSTR szSemiColon = ";";
			
			//AfxMessageBox(_T("LINE COMMENT Before Delete Detectado"));
			int nLine = rCtrl.LineFromPosition(posLineComment);
			long posStartLine = rCtrl.PositionFromLine(nLine);
			long posEndLine	= rCtrl.GetLineEndPosition( nLine);
			long posIdType = WSPSearchToken(posLineComment, posEndLine, szType);
			long posSemiColon = WSPSearchToken( posIdType, m_DocumentLength, szSemiColon); 
			//str.Format(_T("PosIdType %d"), posIdType);
			//AfxMessageBox(str);
		
			if( posIdType != NOT_FOUND )
			{
				int r = WSPParseVariable( posIdType -1, posSemiColon );
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					WSPAddVariable(posIdType + typelen, false );
				}
			}
			
		}

	}
	


	if( m_iModificationType == INSERTTEXT )
	{
		/// Detecting open comment token ///
		long posOpenComment = WSPDetectOpenComment(pos);

		if( posOpenComment != NOT_FOUND  )
		{
			//AfxMessageBox(_T("OPEN COMMENT Insert Detectado"));
			

			long posCloseComment = WSPSearchToken(posOpenComment, m_DocumentLength, szCloseComment);	
			//str.Format(_T("Pos Close Comment %d"), posCloseComment);
			//AfxMessageBox(str);
			if( posCloseComment != NOT_FOUND )
			{
				WSPDeleteSelectedVariables( posOpenComment, posCloseComment, szType, typelen, false);	
			}
			else
			{
				//WSPDeleteSelectedVariables( posOpenDocument, m_DocumentLength, szType, typelen, false);
			}
		}

		/// Detecting close comment token ///	
		long posCloseComment = WSPDetectCloseComment(pos);
		
		if( posCloseComment != NOT_FOUND )
		{
			//AfxMessageBox(_T("CLOSE COMMENT VARIABLE Insert Detectado"));
			//CString s = szType;
			//AfxMessageBox(s);
			
			long posPrevOpenComment = WSPSearchToken(posCloseComment, 0, szOpenComment);
			//str.Format(_T("Prev Pos Open Comment %d"), posPrevOpenComment);
			//AfxMessageBox(str);
			long posPrevCloseComment = WSPSearchToken(posCloseComment - 3, 0, szCloseComment);	
			//str.Format(_T("Prev Pos Close Comment %d"), posPrevCloseComment);
			//AfxMessageBox(str);
			
			if( posPrevOpenComment != NOT_FOUND && posPrevOpenComment > posPrevCloseComment )
			{
				//AfxMessageBox(_T("Detectado"));
				WSPDeleteSelectedVariables(posPrevOpenComment, posCloseComment, szType, typelen, false);	
			}
				
			long posNextCloseComment = WSPSearchToken( posCloseComment + 3, m_DocumentLength, szCloseComment);
			//str.Format(_T("Pos Next Close Comment %d"), posNextCloseComment);
			//AfxMessageBox(str);
			
			if( posNextCloseComment != NOT_FOUND )
			{
				WSPAddSelectedVariables(posCloseComment + 3, posNextCloseComment + 3, szType, typelen, true);
			}
			else
			{
				//WSPAddSelectedVariables(posCloseComment - 1, m_DocumentLength, szType, typelen, true);
			}
	
		}

			
		/// Detecting line comments ////
		long posLineComment = WSPDetectLineComment( pos);

		if( posLineComment != NOT_FOUND )
		{
			//AfxMessageBox(_T("LINE COMMENT Insert Detectado"));
			LPSTR szSemiColon = ";";	
			int nLine = rCtrl.LineFromPosition(posLineComment);
			long posStartLine = rCtrl.PositionFromLine(nLine);
			long posEndLine	= rCtrl.GetLineEndPosition( nLine);
			long posIdType = WSPSearchNearestIdType(posLineComment, posEndLine);
			long posSemiColon = WSPSearchToken( posIdType, m_DocumentLength, szSemiColon); 
			
			if( posIdType != NOT_FOUND )
			{
				int r = WSPParseVariable( posIdType -1, posSemiColon );
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					WSPDeleteVariable( posIdType + typelen, false );
				}
			}
			
		}

	}

  

}



void CAIPIEditorView::WSPCommentClass(long pos )
{
	
	LPSTR szOpenComment = "/*";
	LPSTR szCloseComment = "*/";
	LPSTR szLineComment = "//";

	
	CScintillaCtrl& rCtrl = GetCtrl();
	CString str;
		
	
	
	if( m_iModificationType == BEFOREDELETE )
	{
		long posOpenComment = WSPDetectOpenComment(pos-1);
		
		/// Detecting open comment token ///
		if( posOpenComment != NOT_FOUND )
		{
			long posCloseComment = WSPSearchToken( posOpenComment, m_DocumentLength, szCloseComment);
			//str.Format(_T("Pos Close Comment %d"), posCloseComment);
			//AfxMessageBox(str);
			
			if( posCloseComment != NOT_FOUND )
			{
				WSPAddSelectedClasses(posOpenComment, posCloseComment, false);
				WSPAddSelectedClasses(posOpenComment, posCloseComment, true);
			}
			else
			{
				WSPAddSelectedClasses(posOpenComment, m_DocumentLength -1, true);
			}
		}
				
			
		/// Detecting close comment token ///
		long posCloseComment = WSPDetectCloseComment(pos-1);	
	
		if( posCloseComment != NOT_FOUND )
		{
			//AfxMessageBox(_T("CLOSE COMMENT Before Delete Detectado"));
			long posOpenComment = WSPSearchToken(posCloseComment, 0, szOpenComment);
			//str.Format(_T("Pos Open Comment %d"), posOpenComment);
			//AfxMessageBox(str);
			
			if( posOpenComment != NOT_FOUND)
			{
				//WSPAddSelectedRules(posOpenComment, posCloseComment, false);
				long docLength = rCtrl.GetTextLength();
				long posNextCloseComment = WSPSearchToken(posCloseComment + 3, docLength, szCloseComment);
				//str.Format(_T("Pos Next Close Comment %d"), posNextCloseComment);
				//AfxMessageBox(str);
				if( posNextCloseComment != NOT_FOUND )
				{
					WSPDeleteSelectedClasses(posCloseComment, posNextCloseComment, true);
				}
			}

		}

		/// Detecting line comments ////
		
		long posLineComment = WSPDetectLineComment( pos -1);
	
		if( posLineComment != NOT_FOUND )
		{
			LPSTR szOpenBrace = "{";
			LPSTR szKeyWord = "CLASS";
			
			//AfxMessageBox(_T("LINE COMMENT Before Delete Detectado"));
			int nLine = rCtrl.LineFromPosition(posLineComment);
			long posStartLine = rCtrl.PositionFromLine(nLine);
			long posEndLine	= rCtrl.GetLineEndPosition( nLine);
			long posClass = WSPSearchToken(posLineComment, posEndLine, szKeyWord);
			long posOpenBrace = WSPSearchToken( posClass, m_DocumentLength, szOpenBrace); 

			
			//str.Format(_T("PosIdType %d"), posIdType);
			//AfxMessageBox(str);
		
			if( posClass != NOT_FOUND )
			{
				int r = WSPParseClass( posClass -1, posOpenBrace );
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					WSPAddClass(posClass + 5, false );
				}
			}
			
		}

	}
	


	if( m_iModificationType == INSERTTEXT )
	{
		/// Detecting open comment token ///
		long posOpenComment = WSPDetectOpenComment(pos);

		if( posOpenComment != NOT_FOUND  )
		{
			//AfxMessageBox(_T("OPEN COMMENT Insert Detectado"));
			

			long posCloseComment = WSPSearchToken(posOpenComment, m_DocumentLength, szCloseComment);	
			//str.Format(_T("Pos Close Comment %d"), posCloseComment);
			//AfxMessageBox(str);
			if( posCloseComment != NOT_FOUND )
			{
				WSPDeleteSelectedClasses( posOpenComment, posCloseComment, false);	
			}
			else
			{
				//WSPDeleteSelectedClasses( posOpenDocument, m_DocumentLength,  false);
			}
		}

		/// Detecting close comment token ///	
		long posCloseComment = WSPDetectCloseComment(pos);
		
		if( posCloseComment != NOT_FOUND )
		{
			//AfxMessageBox(_T("CLOSE COMMENT VARIABLE Insert Detectado"));
			//CString s = szType;
			//AfxMessageBox(s);
			
			long posPrevOpenComment = WSPSearchToken(posCloseComment, 0, szOpenComment);
			//str.Format(_T("Prev Pos Open Comment %d"), posPrevOpenComment);
			//AfxMessageBox(str);
			long posPrevCloseComment = WSPSearchToken(posCloseComment - 3, 0, szCloseComment);	
			//str.Format(_T("Prev Pos Close Comment %d"), posPrevCloseComment);
			//AfxMessageBox(str);
			
			if( posPrevOpenComment != NOT_FOUND && posPrevOpenComment > posPrevCloseComment )
			{
				//AfxMessageBox(_T("Detectado"));
				WSPDeleteSelectedClasses(posPrevOpenComment, posCloseComment, false);	
			}
				
			long posNextCloseComment = WSPSearchToken( posCloseComment + 3, m_DocumentLength, szCloseComment);
			//str.Format(_T("Pos Next Close Comment %d"), posNextCloseComment);
			//AfxMessageBox(str);
			
			if( posNextCloseComment != NOT_FOUND )
			{
				WSPAddSelectedClasses(posCloseComment + 3, posNextCloseComment + 3,  true);
			}
			else
			{
				//WSPAddSelectedClasses(posCloseComment - 1, m_DocumentLength, true);
			}
	
		}

			
		/// Detecting line comments ////
		long posLineComment = WSPDetectLineComment( pos);

		if( posLineComment != NOT_FOUND )
		{
			//AfxMessageBox(_T("LINE COMMENT Insert Detectado"));
			LPSTR szOpenBrace = "{";
			LPSTR szKeyWord = "CLASS";
			
			
			int nLine = rCtrl.LineFromPosition(posLineComment);
			long posStartLine = rCtrl.PositionFromLine(nLine);
			long posEndLine	= rCtrl.GetLineEndPosition( nLine);
			long posClass = WSPSearchToken(posLineComment, posEndLine, szKeyWord);
			long posOpenBrace = WSPSearchToken( posClass, m_DocumentLength, szOpenBrace); 
			
			if( posClass != NOT_FOUND )
			{
				int r = WSPParseClass( posClass -1, posOpenBrace );
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					WSPDeleteClass( posClass + 5, false );
				}
			}
			
		}

	}

  

}


void CAIPIEditorView::WSPCommentQuery(long pos )
{
	
	LPSTR szOpenComment = "/*";
	LPSTR szCloseComment = "*/";
	LPSTR szLineComment = "//";

	
	CScintillaCtrl& rCtrl = GetCtrl();
	CString str;
		
	
	
	if( m_iModificationType == BEFOREDELETE )
	{
		long posOpenComment = WSPDetectOpenComment(pos-1);
		
		/// Detecting open comment token ///
		if( posOpenComment != NOT_FOUND )
		{
			long posCloseComment = WSPSearchToken( posOpenComment, m_DocumentLength, szCloseComment);
			//str.Format(_T("Pos Close Comment %d"), posCloseComment);
			//AfxMessageBox(str);
			
			if( posCloseComment != NOT_FOUND )
			{
				WSPAddSelectedQueries(posOpenComment, posCloseComment, false);
				WSPAddSelectedQueries(posOpenComment, posCloseComment, true);
			}
			else
			{
				WSPAddSelectedQueries(posOpenComment, m_DocumentLength -1, true);
			}
		}
				
			
		/// Detecting close comment token ///
		long posCloseComment = WSPDetectCloseComment(pos-1);	
	
		if( posCloseComment != NOT_FOUND )
		{
			//AfxMessageBox(_T("CLOSE COMMENT Before Delete Detectado"));
			long posOpenComment = WSPSearchToken(posCloseComment, 0, szOpenComment);
			//str.Format(_T("Pos Open Comment %d"), posOpenComment);
			//AfxMessageBox(str);
			
			if( posOpenComment != NOT_FOUND)
			{
				//WSPAddSelectedRules(posOpenComment, posCloseComment, false);
				long docLength = rCtrl.GetTextLength();
				long posNextCloseComment = WSPSearchToken(posCloseComment + 3, docLength, szCloseComment);
				//str.Format(_T("Pos Next Close Comment %d"), posNextCloseComment);
				//AfxMessageBox(str);
				if( posNextCloseComment != NOT_FOUND )
				{
					WSPDeleteSelectedQueries(posCloseComment, posNextCloseComment, true);
				}
			}

		}

		/// Detecting line comments ////
		
		long posLineComment = WSPDetectLineComment( pos -1);
	
		if( posLineComment != NOT_FOUND )
		{
			LPSTR szEqual = "=";
			LPSTR szKeyWord = "SQLQUERY";
			
			//AfxMessageBox(_T("LINE COMMENT Before Delete Detectado"));
			int nLine = rCtrl.LineFromPosition(posLineComment);
			long posStartLine = rCtrl.PositionFromLine(nLine);
			long posEndLine	= rCtrl.GetLineEndPosition( nLine);
			long posQuery = WSPSearchToken(posLineComment, posEndLine, szKeyWord);
			long posEqual = WSPSearchToken( posQuery, m_DocumentLength, szEqual); 

			
			//str.Format(_T("PosIdType %d"), posIdType);
			//AfxMessageBox(str);
		
			if( posQuery != NOT_FOUND )
			{
				int r = WSPParseQuery( posQuery -1, posEqual );
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					WSPAddQuery(posQuery + 8, false );
				}
			}
			
		}

	}
	


	if( m_iModificationType == INSERTTEXT )
	{
		/// Detecting open comment token ///
		long posOpenComment = WSPDetectOpenComment(pos);

		if( posOpenComment != NOT_FOUND  )
		{
			//AfxMessageBox(_T("OPEN COMMENT Insert Detectado"));
			

			long posCloseComment = WSPSearchToken(posOpenComment, m_DocumentLength, szCloseComment);	
			//str.Format(_T("Pos Close Comment %d"), posCloseComment);
			//AfxMessageBox(str);
			if( posCloseComment != NOT_FOUND )
			{
				WSPDeleteSelectedQueries( posOpenComment, posCloseComment, false);	
			}
			else
			{
				//WSPDeleteSelectedQueries( posOpenDocument, m_DocumentLength,  false);
			}
		}

		/// Detecting close comment token ///	
		long posCloseComment = WSPDetectCloseComment(pos);
		
		if( posCloseComment != NOT_FOUND )
		{
			//AfxMessageBox(_T("CLOSE COMMENT VARIABLE Insert Detectado"));
			//CString s = szType;
			//AfxMessageBox(s);
			
			long posPrevOpenComment = WSPSearchToken(posCloseComment, 0, szOpenComment);
			//str.Format(_T("Prev Pos Open Comment %d"), posPrevOpenComment);
			//AfxMessageBox(str);
			long posPrevCloseComment = WSPSearchToken(posCloseComment - 3, 0, szCloseComment);	
			//str.Format(_T("Prev Pos Close Comment %d"), posPrevCloseComment);
			//AfxMessageBox(str);
			
			if( posPrevOpenComment != NOT_FOUND && posPrevOpenComment > posPrevCloseComment )
			{
				//AfxMessageBox(_T("Detectado"));
				WSPDeleteSelectedQueries(posPrevOpenComment, posCloseComment, false);	
			}
				
			long posNextCloseComment = WSPSearchToken( posCloseComment + 3, m_DocumentLength, szCloseComment);
			//str.Format(_T("Pos Next Close Comment %d"), posNextCloseComment);
			//AfxMessageBox(str);
			
			if( posNextCloseComment != NOT_FOUND )
			{
				WSPAddSelectedQueries(posCloseComment + 3, posNextCloseComment + 3,  true);
			}
			else
			{
				//WSPAddSelectedQueries(posCloseComment - 1, m_DocumentLength, true);
			}
	
		}

			
		/// Detecting line comments ////
		long posLineComment = WSPDetectLineComment( pos);

		if( posLineComment != NOT_FOUND )
		{
			//AfxMessageBox(_T("LINE COMMENT Insert Detectado"));
			LPSTR szEqual = "=";
			LPSTR szKeyWord = "SQLQUERY";
			
			
			int nLine = rCtrl.LineFromPosition(posLineComment);
			long posStartLine = rCtrl.PositionFromLine(nLine);
			long posEndLine	= rCtrl.GetLineEndPosition( nLine);
			long posQuery = WSPSearchToken(posLineComment, posEndLine, szKeyWord);
			long posEqual = WSPSearchToken( posQuery, m_DocumentLength, szEqual); 
			
			if( posQuery != NOT_FOUND )
			{
				int r = WSPParseQuery( posQuery -1, posEqual );
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					WSPDeleteQuery( posQuery + 8, false );
				}
			}
			
		}

	}

  

}



int CAIPIEditorView::WSPHandleVariableSemiColon(long pos )
{
	
	CString str;
	
	int r = AIPI_ERROR;

	if( m_iModificationType == BEFOREDELETE )
	{
		CScintillaCtrl& rCtrl = GetCtrl();
		bool bDetected = false;
		//str.Format(_T("Flg Write Rule...%d  " ), m_bFlagWriteRule);
		//AfxMessageBox(str);

	
		//AfxMessageBox(_T("Before Delete"));
		
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);

		int prevSymbol = rCtrl.GetCharAt(pos -1 );
		//str.Format(_T("Prev Symbol...%d  " ), prevSymbol);
		//AfxMessageBox(str);
		
		
		if( symbol != SEMICOLON && prevSymbol == SEMICOLON )
		{
			//AfxMessageBox(_T("Detec Comma"));
			bDetected = true;
		}
		
		
		if( symbol == SEMICOLON && prevSymbol != SEMICOLON )
		{
			//AfxMessageBox(_T("Detec Comma"));
			bDetected = true;
			

		}

		if( bDetected )
		{
			LPSTR szSemiColon = ";";
			
			long posSemiColon = WSPSearchToken( pos - 1, m_DocumentLength, szSemiColon);
			long posIdType = WSPSearchNearestIdType(posSemiColon, 0);
	
	
			
			//str.Format(_T("Pos IdType...%d  " ), posIdType);
			//AfxMessageBox(str);
			//str.Format(_T("Pos SemiColon...%d  " ), posSemiColon);
			//AfxMessageBox(str);
			//AfxMessageBox(m_sCurrentType);
	
			if( posIdType != NOT_FOUND && posSemiColon != NOT_FOUND )
			{
				int r = WSPParseVariable( posIdType -1, posSemiColon);
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					//AfxMessageBox(_T("In"));				
					int typeLength = m_sCurrentType.GetLength();	
					//Check for comments
					bool lnComment = WSPCheckLineComment( posIdType, posIdType + typeLength );
					if( lnComment )
					{
						m_bFlagEditVariable = false;
						return SIMPLE_COMMENT;
					}
					bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posIdType );
					if( blkComment )
					{
						m_bFlagEditVariable = false;
						return COMPLEX_COMMENT;
					}
									
					//AfxMessageBox(_T("BOOL TRUE"));
					m_bVariableSemiColon = true;
					return r = P_SUCCESS;
				}
							
			}
		}
		
	}


	if( m_iModificationType == DELETETEXT )
	{
		
		CScintillaCtrl& rCtrl = GetCtrl();
		
		//AfxMessageBox(_T("After Delete"));
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);
	
		
		if( m_bVariableSemiColon && symbol != SEMICOLON )
		{
			CString sEmptyNode = _T("");
			WSPDeleteNodeTree1(sEmptyNode);
			
			LPSTR szSemiColon = ";";
						
			long posIdType = WSPSearchNearestIdType(pos, 0);
					  
			if( posIdType != NOT_FOUND )
			{
				int typeLength = m_sCurrentType.GetLength();
				long posSemiColon = WSPSearchToken(posIdType, pos + 1, szSemiColon); 
				
				/*
				str.Format(_T("Pos IdType...%d  " ), posIdType);
				AfxMessageBox(str);
				str.Format(_T("Pos SemiColon...%d  " ), posSemiColon);
				AfxMessageBox(str);
				*/
				  
				CString sVariableName = WSPGetText(posIdType + typeLength, posSemiColon);
				if( sVariableName == _T("OVERLOAD"))
				{
					return AIPI_ERROR;
				}
				
				if( sVariableName != _T("EMPTY") )
				{
					sVariableName.TrimRight();
					sVariableName.TrimLeft();
					//AfxMessageBox(sVariableName);
					r = WSPDeleteNodeTree1(sVariableName);
				}
					
					
			}
		
		}
		
		m_bVariableSemiColon = false;
		

	}

	if( m_iModificationType == INSERTTEXT )
	{
		CScintillaCtrl& rCtrl = GetCtrl();
		//CString str;	
		//AfxMessageBox(_T("Insert Text"));
		
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Global Symbol...%d  " ), symbol);
		//AfxMessageBox(str);
		
		if( symbol == SEMICOLON )
		{
			
			//AfxMessageBox(_T("Add SemiColon"));
			//str.Format(_T("Flg Write Var...%d  " ), m_bFlagWriteError);
			//AfxMessageBox(str);

			int r = WSPAddVariable( pos, true);
			//str.Format(_T("r...%d  " ), r);
			//AfxMessageBox(str);

			
			if( r != AIPI_ERROR  )
			{
				return r;
				//AfxMessageBox(_T("Rula Addee"));	
				//m_bFlagWriteRule = false;
			}
			
		}

	}

//str.Format(_T("r...%d  " ), r);
//AfxMessageBox(str);
			
return r;

}





int CAIPIEditorView::WSPHandleVariableSemiColonEdit(long pos, LPSTR szType, int typelen )
{
	
	CString str;
	
	int r = AIPI_ERROR;

	if( m_iModificationType == BEFOREDELETE )
	{
		CScintillaCtrl& rCtrl = GetCtrl();
		bool bDetected = false;
		//str.Format(_T("Flg Write Rule...%d  " ), m_bFlagWriteRule);
		//AfxMessageBox(str);
		
		//AfxMessageBox(_T("Before Delete"));
		
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);

		int prevSymbol = rCtrl.GetCharAt(pos -1 );
		//str.Format(_T("Prev Symbol...%d  " ), prevSymbol);
		//AfxMessageBox(str);
		
		
		if( symbol != SEMICOLON && prevSymbol == SEMICOLON )
		{
			//AfxMessageBox(_T("Detec SemiColon"));
			bDetected = true;
	
		}
		
		
		if( symbol == SEMICOLON && prevSymbol != SEMICOLON )
		{
			//AfxMessageBox(_T("Detec SemiColon"));
			bDetected = true;
			

		}

		if( bDetected )
		{
			//AfxMessageBox(_T("Detected"));
			
			LPSTR szSemiColon = ";";
			
			long posSemiColon = WSPSearchToken( pos -1, m_DocumentLength, szSemiColon);
			long posIdType = WSPSearchToken(posSemiColon, 0, szType);
	
			
			/*
			str.Format(_T("Pos IdType...%d  " ), posIdType);
			AfxMessageBox(str);
			str.Format(_T("Pos SemiColon...%d  " ), posSemiColon);
			AfxMessageBox(str);
			*/
				

			if( posIdType != NOT_FOUND && posSemiColon != NOT_FOUND )
			{
				int r = WSPParseVariable( posIdType -1, posSemiColon);
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					//AfxMessageBox(_T("In"));
					m_sCurrentType = WSPGetText( posIdType, posIdType + typelen);
					//AfxMessageBox(m_sCurrentType);
					//Check for comments
					bool lnComment = WSPCheckLineComment( posIdType, posIdType + typelen );
					if( lnComment )
					{
						m_bFlagEditVariable = false;
						return SIMPLE_COMMENT;
					}
					bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posIdType );
					if( blkComment )
					{
						m_bFlagEditVariable = false;
						return COMPLEX_COMMENT;
					}
				
					
					//AfxMessageBox(_T("BOOL TRUE"));
					m_bVariableSemiColon = true;
				
					return r = P_SUCCESS;
				}

				
			}
		}
		
	}


	if( m_iModificationType == DELETETEXT )
	{
		
		CScintillaCtrl& rCtrl = GetCtrl();
		
		//AfxMessageBox(_T("After Delete"));
		int symbol = rCtrl.GetCharAt(pos);
		/*
		str.Format(_T("Symbol...%d  " ), symbol);
		AfxMessageBox(str);
		str.Format(_T("Bool Close P...%d  " ), m_bFunctionCloseParenthesis);
		AfxMessageBox(str);
		str.Format(_T("type len...%d  " ), typelen);
		AfxMessageBox(str);
		*/

		LPSTR szSemiColon = ";";
				
		if( m_bVariableSemiColon && symbol != SEMICOLON )
		{
			//AfxMessageBox(_T("DeleteText In"));
			
			CString sEmptyNode = _T("");
			WSPDeleteNodeTree1(sEmptyNode);
			
			//LPSTR szSemiColon = ";";
						
			long posIdType = WSPSearchToken(pos, 0, szType);
			long posSemiColon = pos;
		  
			
			CString sType = szType;
			//AfxMessageBox(sType);
			
			
			/*
			str.Format(_T("Pos Id...%d  " ), posIdType);
			AfxMessageBox(str);
			
			str.Format(_T("Pos SemiColon...%d  " ), posSemiColon);
			AfxMessageBox(str);
			*/
			
			
			
			if( sType != m_sCurrentType )
			{
				return AIPI_ERROR;
			}
			

			if( posIdType != NOT_FOUND )
			{
				/*
				str.Format(_T("Pos IdType...%d  " ), posIdType);
				AfxMessageBox(str);
				str.Format(_T("Type Len...%d  " ), typelen);
				AfxMessageBox(str);
				str.Format(_T("Pos SemiColon...%d  " ), posSemiColon);
				AfxMessageBox(str);
				AfxMessageBox(m_sCurrentType);
				*/
				
				CString sVariableName = WSPGetText(posIdType + typelen, posSemiColon);
				if( sVariableName == _T("OVERLOAD") )
				{
					//AfxMessageBox(sVariableName);
					return AIPI_ERROR;
					
				}
				
				if( sVariableName != _T("EMPTY") )
				{
					sVariableName.TrimRight();
					sVariableName.TrimLeft();
					//AfxMessageBox(_T("Delete Var"));
					//AfxMessageBox(sVariableName);
					r = WSPDeleteNodeTree1(sVariableName);
					
				}	
			}
		
		}
		
		m_bVariableSemiColon = false;
		

	}

	if( m_iModificationType == INSERTTEXT )
	{
		CScintillaCtrl& rCtrl = GetCtrl();
		//CString str;	
		//AfxMessageBox(_T("Insert Text"));
		
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Global Symbol...%d  " ), symbol);
		//AfxMessageBox(str);
		
		if( symbol == SEMICOLON )
		{
			
			//AfxMessageBox(_T("Add Close Parenthesis"));
			//str.Format(_T("Flg Write Rule...%d  " ), m_bFlagWriteError);
			//AfxMessageBox(str);

			int r = WSPAddVariable( pos, true);
			//str.Format(_T("r...%d  " ), r);
			//AfxMessageBox(str);

			
			if( r != AIPI_ERROR  )
			{
				return r;
				//AfxMessageBox(_T("Rula Addee"));	
				//m_bFlagWriteRule = false;
			}
			
		}

	}

//str.Format(_T("r...%d  " ), r);
//AfxMessageBox(str);
			
return r;

}





int CAIPIEditorView::WSPHandleClassOpenBrace(long pos )
{
	
	CString str;
	
	int r = AIPI_ERROR;

	if( m_iModificationType == BEFOREDELETE )
	{
		CScintillaCtrl& rCtrl = GetCtrl();
		bool bDetected = false;
		//str.Format(_T("Flg Write Rule...%d  " ), m_bFlagWriteRule);
		//AfxMessageBox(str);

	
		//AfxMessageBox(_T("Before Delete"));
		
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);

		int prevSymbol = rCtrl.GetCharAt(pos -1 );
		//str.Format(_T("Prev Symbol...%d  " ), prevSymbol);
		//AfxMessageBox(str);
		
		
		if( symbol != OPEN_BRACE && prevSymbol == OPEN_BRACE )
		{
			//AfxMessageBox(_T("Detec Brace"));
			bDetected = true;
		}
		
		
		if( symbol == OPEN_BRACE && prevSymbol != OPEN_BRACE )
		{
			//AfxMessageBox(_T("Detec Brace"));
			bDetected = true;
			

		}

		if( bDetected )
		{
			LPSTR szOpenBrace = "{";
			LPSTR szKeyWord = "CLASS";
			
			long posOpenBrace = WSPSearchToken( pos - 1, m_DocumentLength, szOpenBrace);
			long posClass = WSPSearchToken(posOpenBrace, 0, szKeyWord);
	
	
			
			//str.Format(_T("Pos Class...%d  " ), posClass);
			//AfxMessageBox(str);
			//str.Format(_T("Pos OpenBrace...%d  " ), posOpenBrace);
			//AfxMessageBox(str);
			//AfxMessageBox(m_sCurrentType);
	
			if( posClass != NOT_FOUND && posOpenBrace != NOT_FOUND )
			{
				int r = WSPParseClass( posClass -1, posOpenBrace);
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					//Check for comments
					bool lnComment = WSPCheckLineComment( posClass, posClass + 5 );
					if( lnComment )
					{
						m_bFlagEditClass = false;
						return SIMPLE_COMMENT;
					}
					bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posClass );
					if( blkComment )
					{
						m_bFlagEditClass = false;
						return COMPLEX_COMMENT;
					}
									
					//AfxMessageBox(_T("BOOL TRUE"));
					m_bClassOpenBrace = true;
					return r = P_SUCCESS;
				}
							
			}
		}
		
	}


	if( m_iModificationType == DELETETEXT )
	{
		
		CScintillaCtrl& rCtrl = GetCtrl();
		
		//AfxMessageBox(_T("After Delete"));
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);
	
		
		if( m_bClassOpenBrace && symbol != OPEN_BRACE )
		{
			CString sEmptyNode = _T("");
			WSPDeleteNodeTree1(sEmptyNode);
			
			LPSTR szOpenBrace = "{";
			LPSTR szKeyWord = "CLASS";
			
			
			long posClass = WSPSearchToken(pos, 0, szKeyWord);
			long posOpenBrace = pos;
					  
			if( posClass != NOT_FOUND )
			{
						
				CString sClassName = WSPGetText(posClass + 5, posOpenBrace);
				if( sClassName == _T("OVERLOAD") )
				{
					return AIPI_ERROR;
				}
				
				if( sClassName != _T("EMPTY") )
				{
					sClassName.TrimRight();
					sClassName.TrimLeft();
					//AfxMessageBox(sFunctionName);
					//AfxMessageBox(_T("Delete Rule"));
					//AfxMessageBox(sRuleName);
					r = WSPDeleteNodeTree1(sClassName);
					
				}	
			}
		
		}
		
		m_bClassOpenBrace = false;
		

	}

	if( m_iModificationType == INSERTTEXT )
	{
		CScintillaCtrl& rCtrl = GetCtrl();
		//CString str;	
		//AfxMessageBox(_T("Insert Text"));
		
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Global Symbol...%d  " ), symbol);
		//AfxMessageBox(str);
		
		if( symbol == OPEN_BRACE )
		{
			
			//AfxMessageBox(_T("Add OpenBrace"));
			//str.Format(_T("Flg Write Var...%d  " ), m_bFlagWriteError);
			//AfxMessageBox(str);

			int r = WSPAddClass( pos, true);
			//str.Format(_T("r...%d  " ), r);
			//AfxMessageBox(str);

			
			if( r != AIPI_ERROR  )
			{
				return r;
				//AfxMessageBox(_T("Rula Addee"));	
				//m_bFlagWriteRule = false;
			}
			
		}

	}

//str.Format(_T("r...%d  " ), r);
//AfxMessageBox(str);
			
return r;

}


int CAIPIEditorView::WSPHandleQueryEqual(long pos )
{
	
	CString str;
	
	int r = AIPI_ERROR;

	if( m_iModificationType == BEFOREDELETE )
	{
		CScintillaCtrl& rCtrl = GetCtrl();
		bool bDetected = false;
		//str.Format(_T("Flg Write Rule...%d  " ), m_bFlagWriteRule);
		//AfxMessageBox(str);

	
		//AfxMessageBox(_T("Before Delete"));
		
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);

		int prevSymbol = rCtrl.GetCharAt(pos -1 );
		//str.Format(_T("Prev Symbol...%d  " ), prevSymbol);
		//AfxMessageBox(str);
		
		
		if( symbol != EQUAL && prevSymbol == EQUAL )
		{
			//AfxMessageBox(_T("Detec Brace"));
			bDetected = true;
		}
		
		
		if( symbol == EQUAL && prevSymbol != EQUAL )
		{
			//AfxMessageBox(_T("Detec Brace"));
			bDetected = true;
			

		}

		if( bDetected )
		{
			LPSTR szEqual = "=";
			LPSTR szKeyWord = "SQLQUERY";
			
			long posEqual = WSPSearchToken( pos - 1, m_DocumentLength, szEqual);
			long posQuery = WSPSearchToken(posEqual, 0, szKeyWord);
	
	
			
			//str.Format(_T("Pos Query...%d  " ), posQuery);
			//AfxMessageBox(str);
			//str.Format(_T("Pos Equal...%d  " ), posEqual);
			//AfxMessageBox(str);
			//AfxMessageBox(m_sCurrentType);
	
			if( posQuery != NOT_FOUND && posEqual != NOT_FOUND )
			{
				int r = WSPParseQuery( posQuery -1, posEqual);
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					//Check for comments
					bool lnComment = WSPCheckLineComment( posQuery, posQuery + 8 );
					if( lnComment )
					{
						m_bFlagEditQuery = false;
						return SIMPLE_COMMENT;
					}
					bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posQuery );
					if( blkComment )
					{
						m_bFlagEditQuery = false;
						return COMPLEX_COMMENT;
					}
									
					//AfxMessageBox(_T("BOOL TRUE"));
					m_bQueryEqual = true;
					return r = P_SUCCESS;
				}
							
			}
		}
		
	}


	if( m_iModificationType == DELETETEXT )
	{
		
		CScintillaCtrl& rCtrl = GetCtrl();
		
		//AfxMessageBox(_T("After Delete"));
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);
	
		
		if( m_bQueryEqual && symbol != EQUAL )
		{
			CString sEmptyNode = _T("");
			WSPDeleteNodeTree1(sEmptyNode);
			
			LPSTR szEqual = "=";
			LPSTR szKeyWord = "SQLQUERY";
			
			
			long posQuery = WSPSearchToken(pos, 0, szKeyWord);
			long posEqual = pos;
					  
			if( posQuery != NOT_FOUND )
			{
						
				CString sQueryName = WSPGetText(posQuery + 8, posEqual);
				if( sQueryName == _T("OVERLOAD") )
				{
					return AIPI_ERROR;
				}
				
				if( sQueryName != _T("EMPTY") )
				{
					sQueryName.TrimRight();
					sQueryName.TrimLeft();
					//AfxMessageBox(sQueryName);
					//AfxMessageBox(_T("Delete Query"));
					//AfxMessageBox(sQueryName);
					r = WSPDeleteNodeTree1(sQueryName);
					
				}	
			}
		
		}
		
		m_bQueryEqual = false;
		

	}

	if( m_iModificationType == INSERTTEXT )
	{
		CScintillaCtrl& rCtrl = GetCtrl();
		//CString str;	
		//AfxMessageBox(_T("Insert Text"));
		
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Global Symbol...%d  " ), symbol);
		//AfxMessageBox(str);
		
		if( symbol == EQUAL )
		{
			
			//AfxMessageBox(_T("Add Equal"));
			//str.Format(_T("Flg Write Var...%d  " ), m_bFlagWriteError);
			//AfxMessageBox(str);

			int r = WSPAddQuery( pos, true);
			//str.Format(_T("r...%d  " ), r);
			//AfxMessageBox(str);

			
			if( r != AIPI_ERROR  )
			{
				return r;
				//AfxMessageBox(_T("Rula Addee"));	
				//m_bFlagWriteRule = false;
			}
			
		}

	}

//str.Format(_T("r...%d  " ), r);
//AfxMessageBox(str);
			
return r;

}




int CAIPIEditorView::WSPHandleJSFunctionCloseParenthesis(long pos)
{
	CString str;
	
	int r = AIPI_ERROR;

	if( m_iModificationType == BEFOREDELETE )
	{
		CScintillaCtrl& rCtrl = GetCtrl();
		bool bDetected = false;
			
		//AfxMessageBox(_T("Before Delete"));
		
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);

		int prevSymbol = rCtrl.GetCharAt(pos -1 );
		//str.Format(_T("Prev Symbol...%d  " ), prevSymbol);
		//AfxMessageBox(str);
		
		
		if( symbol != CLOSE_PARENTHESIS && prevSymbol == CLOSE_PARENTHESIS )
		{
			//AfxMessageBox(_T("Detec Close Parenthesis"));
			bDetected = true;
		}
		
		
		if( symbol == CLOSE_PARENTHESIS && prevSymbol != CLOSE_PARENTHESIS )
		{
			//AfxMessageBox(_T("Detec Close Parenthesis"));
			bDetected = true;
			

		}

		if( bDetected )
		{
			LPSTR szKeyWord = "function";
			LPSTR szCloseParenthesis = ")";
			
			long posFunction = WSPSearchToken( pos, 0, szKeyWord );
			//long posCloseParenthesis = WSPSearchToken( posFunction, m_DocumentLength, szCloseParenthesis);
			long posCloseParenthesis = pos;
			
			//str.Format(_T("Pos Rule...%d  " ), posRule);
			//AfxMessageBox(str);
			//str.Format(_T("Pos Close Parenthesis...%d  " ), posCloseParenthesis);
			//AfxMessageBox(str);
			
	
			if( posFunction != NOT_FOUND && posCloseParenthesis != NOT_FOUND )
			{
				int iniSymbol = rCtrl.GetCharAt( posFunction -1 );
				int endSymbol =rCtrl.GetCharAt( posFunction + 8 );
				//str.Format(_T("ini...%d  " ), iniSymbol);
				//AfxMessageBox(str);
				//str.Format(_T("end...%d  " ), endSymbol);
				//AfxMessageBox(str);
				if(
					(	   iniSymbol != SPACE && iniSymbol != NEW_LINE && iniSymbol != CARRIAGE_RETURN 
						&& iniSymbol != NUL && iniSymbol != HORIZONTAL_TAB )
						|| (     endSymbol != SPACE && endSymbol != NEW_LINE && endSymbol != CARRIAGE_RETURN 
						&& endSymbol != NUL && endSymbol != HORIZONTAL_TAB )
					)
					{
						return NOT_FOUND;
					}
		
				
					int r = WSPParseJSFunction( posFunction -1, posCloseParenthesis);
					if( r != AIPI_ERROR && r != NOT_FOUND )
					{
						//AfxMessageBox(_T("In"));				
				
						//Check for comments
						bool lnComment = WSPCheckLineComment( posFunction, posFunction + 8);
						if( lnComment )
						{
							m_bFlagEditJSFunction = false;
							return SIMPLE_COMMENT;
						}
						bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posFunction );
						if( blkComment )
						{
							m_bFlagEditJSFunction = false;
							return COMPLEX_COMMENT;
						}
					
						//AfxMessageBox(_T("BOOL TRUE"));
						m_bJSFunctionCloseParenthesis = true;
						return r = P_SUCCESS;
					}
					
				
			}
		}
		
	}


	if( m_iModificationType == DELETETEXT )
	{
		
		CScintillaCtrl& rCtrl = GetCtrl();
		
		//AfxMessageBox(_T("After Delete"));
		int symbol = rCtrl.GetCharAt(pos);
		str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);
	
		
		if( m_bJSFunctionCloseParenthesis && symbol != CLOSE_PARENTHESIS )
		{
			CString sEmptyNode = _T("");
			WSPDeleteNodeTree1(sEmptyNode);
			
			LPSTR szKeyWord = "function";
						
			long posFunction = WSPSearchToken(pos, 0, szKeyWord);
			long posCloseParenthesis = pos;

			if( posFunction != NOT_FOUND )
			{
				LPSTR szOpenParenthesis = "(";
				long posOpenParenthesis = WSPSearchToken(posFunction, posCloseParenthesis, szOpenParenthesis); 
				
				CString sFunctionName = WSPGetText(posFunction + 8, posOpenParenthesis);
				if( sFunctionName == _T("OVERLOAD" ))
				{
					return AIPI_ERROR;
				}
								
				if( sFunctionName != _T("EMPTY") )
				{
					sFunctionName.TrimRight();
					sFunctionName.TrimLeft();
					r = WSPDeleteNodeTree1(sFunctionName);
					
				}
	
					
			}
		
		}
		
		m_bJSFunctionCloseParenthesis = false;
		

	}

	if( m_iModificationType == INSERTTEXT )
	{
		CScintillaCtrl& rCtrl = GetCtrl();
		//CString str;	
		//AfxMessageBox(_T("Insert Text"));
		
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Global Symbol...%d  " ), symbol);
		//AfxMessageBox(str);
		
		if( symbol == CLOSE_PARENTHESIS )
		{
			
			//AfxMessageBox(_T("Add Close Parenthesis"));
			//str.Format(_T("Flg Write Rule...%d  " ), m_bFlagWriteError);
			//AfxMessageBox(str);

			int r = WSPAddJSFunction( pos, true);
			//str.Format(_T("r...%d  " ), r);
			//AfxMessageBox(str);

			
			if( r != AIPI_ERROR  )
			{
				return r;
				//AfxMessageBox(_T("Rula Addee"));	
				//m_bFlagWriteRule = false;
			}
			
		}

	}

//str.Format(_T("r...%d  " ), r);
//AfxMessageBox(str);
			
return r;

}




int CAIPIEditorView::WSPHandleVBSFunctionCloseParenthesis(long pos)
{
	CString str;
	
	int r = AIPI_ERROR;

	if( m_iModificationType == BEFOREDELETE )
	{
		CScintillaCtrl& rCtrl = GetCtrl();
		bool bDetected = false;
		//str.Format(_T("Flg Write Rule...%d  " ), m_bFlagWriteRule);
		//AfxMessageBox(str);

	
		//AfxMessageBox(_T("Before Delete"));
		
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);

		int prevSymbol = rCtrl.GetCharAt(pos -1 );
		//str.Format(_T("Prev Symbol...%d  " ), prevSymbol);
		//AfxMessageBox(str);
		
		
		if( symbol != CLOSE_PARENTHESIS && prevSymbol == CLOSE_PARENTHESIS )
		{
			//AfxMessageBox(_T("Detec Close Parenthesis"));
			bDetected = true;
		}
		
		
		if( symbol == CLOSE_PARENTHESIS && prevSymbol != CLOSE_PARENTHESIS )
		{
			//AfxMessageBox(_T("Detec Close Parenthesis"));
			bDetected = true;
			

		}

		if( bDetected )
		{
			LPSTR szKeyWord = "Function";
			LPSTR szCloseParenthesis = ")";
			

			long posFunction = WSPSearchToken( pos, 0, szKeyWord );
			//long posCloseParenthesis = WSPSearchToken( posFunction, m_DocumentLength, szCloseParenthesis);
			long posCloseParenthesis = pos;
			
			//str.Format(_T("Pos Rule...%d  " ), posRule);
			//AfxMessageBox(str);
			//str.Format(_T("Pos Close Parenthesis...%d  " ), posCloseParenthesis);
			//AfxMessageBox(str);
			
	
			if( posFunction != NOT_FOUND && posCloseParenthesis != NOT_FOUND )
			{
				int iniSymbol = rCtrl.GetCharAt( posFunction -1 );
				int endSymbol =rCtrl.GetCharAt( posFunction + 8 );
				//str.Format(_T("ini...%d  " ), iniSymbol);
				//AfxMessageBox(str);
				//str.Format(_T("end...%d  " ), endSymbol);
				//AfxMessageBox(str);
				if(
					(	   iniSymbol != SPACE && iniSymbol != NEW_LINE && iniSymbol != CARRIAGE_RETURN 
						&& iniSymbol != NUL && iniSymbol != HORIZONTAL_TAB )
						|| (     endSymbol != SPACE && endSymbol != NEW_LINE && endSymbol != CARRIAGE_RETURN 
						&& endSymbol != NUL && endSymbol != HORIZONTAL_TAB )
					)
					{
						return NOT_FOUND;
					}
		
				
					int r = WSPParseVBSFunction( posFunction -1, posCloseParenthesis);
					if( r != AIPI_ERROR && r != NOT_FOUND )
					{
						//AfxMessageBox(_T("In"));				
				
						//Check for comments
						bool lnComment = WSPCheckLineComment( posFunction, posFunction + 8);
						if( lnComment )
						{
							m_bFlagEditVBSFunction = false;
							return SIMPLE_COMMENT;
						}
						bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posFunction );
						if( blkComment )
						{
							m_bFlagEditVBSFunction = false;
							return COMPLEX_COMMENT;
						}
					
						//AfxMessageBox(_T("BOOL TRUE"));
						m_bVBSFunctionCloseParenthesis = true;
						return r = P_SUCCESS;
					}
					
				
			}
		}
		
	}


	if( m_iModificationType == DELETETEXT )
	{
		
		CScintillaCtrl& rCtrl = GetCtrl();
		
		//AfxMessageBox(_T("After Delete"));
		int symbol = rCtrl.GetCharAt(pos);
		str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);
	
		
		if( m_bVBSFunctionCloseParenthesis && symbol != CLOSE_PARENTHESIS )
		{
			CString sEmptyNode = _T("");
			WSPDeleteNodeTree1(sEmptyNode);
			
			LPSTR szKeyWord = "Function";
						
			long posFunction = WSPSearchToken(pos, 0, szKeyWord);
			long posCloseParenthesis = pos;

			if( posFunction != NOT_FOUND )
			{
				LPSTR szOpenParenthesis = "(";
				long posOpenParenthesis = WSPSearchToken(posFunction, posCloseParenthesis, szOpenParenthesis); 
				
				CString sFunctionName = WSPGetText(posFunction + 8, posOpenParenthesis);
				if( sFunctionName == _T("OVERLOAD" ))
				{
					return AIPI_ERROR;
				}
								
				if( sFunctionName != _T("EMPTY") )
				{
					sFunctionName.TrimRight();
					sFunctionName.TrimLeft();
					r = WSPDeleteNodeTree1(sFunctionName);
					
				}
			
					
			}
		
		}
		
		m_bVBSFunctionCloseParenthesis = false;
		

	}

	if( m_iModificationType == INSERTTEXT )
	{
		CScintillaCtrl& rCtrl = GetCtrl();
		//CString str;	
		//AfxMessageBox(_T("Insert Text"));
		
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Global Symbol...%d  " ), symbol);
		//AfxMessageBox(str);
		
		if( symbol == CLOSE_PARENTHESIS )
		{
			
			//AfxMessageBox(_T("Add Close Parenthesis"));
			//str.Format(_T("Flg Write Rule...%d  " ), m_bFlagWriteError);
			//AfxMessageBox(str);

			int r = WSPAddVBSFunction( pos, true);
			//str.Format(_T("r...%d  " ), r);
			//AfxMessageBox(str);

			
			if( r != AIPI_ERROR  )
			{
				return r;
				//AfxMessageBox(_T("Rula Addee"));	
				//m_bFlagWriteRule = false;
			}
			
		}

	}

//str.Format(_T("r...%d  " ), r);
//AfxMessageBox(str);
			
return r;

}


int CAIPIEditorView::WSPHandleVBSFUNCTIONCloseParenthesis(long pos)
{
	CString str;
	
	int r = AIPI_ERROR;

	if( m_iModificationType == BEFOREDELETE )
	{
		CScintillaCtrl& rCtrl = GetCtrl();
		bool bDetected = false;
		//str.Format(_T("Flg Write Rule...%d  " ), m_bFlagWriteRule);
		//AfxMessageBox(str);

	
		//AfxMessageBox(_T("Before Delete"));
		
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);

		int prevSymbol = rCtrl.GetCharAt(pos -1 );
		//str.Format(_T("Prev Symbol...%d  " ), prevSymbol);
		//AfxMessageBox(str);
		
		
		if( symbol != CLOSE_PARENTHESIS && prevSymbol == CLOSE_PARENTHESIS )
		{
			//AfxMessageBox(_T("Detec Close Parenthesis"));
			bDetected = true;
		}
		
		
		if( symbol == CLOSE_PARENTHESIS && prevSymbol != CLOSE_PARENTHESIS )
		{
			//AfxMessageBox(_T("Detec Close Parenthesis"));
			bDetected = true;
			

		}

		if( bDetected )
		{
			LPSTR szKeyWord = "FUNCTION";
			LPSTR szCloseParenthesis = ")";
			

			long posFunction = WSPSearchToken( pos, 0, szKeyWord );
			long posCloseParenthesis = WSPSearchToken( posFunction, m_DocumentLength, szCloseParenthesis);
	
			
			//str.Format(_T("Pos Rule...%d  " ), posRule);
			//AfxMessageBox(str);
			//str.Format(_T("Pos Close Parenthesis...%d  " ), posCloseParenthesis);
			//AfxMessageBox(str);
			
	
			if( posFunction != NOT_FOUND && posCloseParenthesis != NOT_FOUND )
			{
				int iniSymbol = rCtrl.GetCharAt( posFunction -1 );
				int endSymbol =rCtrl.GetCharAt( posFunction + 8 );
				//str.Format(_T("ini...%d  " ), iniSymbol);
				//AfxMessageBox(str);
				//str.Format(_T("end...%d  " ), endSymbol);
				//AfxMessageBox(str);
				if(
					(	   iniSymbol != SPACE && iniSymbol != NEW_LINE && iniSymbol != CARRIAGE_RETURN 
						&& iniSymbol != NUL && iniSymbol != HORIZONTAL_TAB )
						|| (     endSymbol != SPACE && endSymbol != NEW_LINE && endSymbol != CARRIAGE_RETURN 
						&& endSymbol != NUL && endSymbol != HORIZONTAL_TAB )
					)
					{
						return NOT_FOUND;
					}
		
				
					int r = WSPParseVBSFunction( posFunction -1, posCloseParenthesis);
					if( r != AIPI_ERROR && r != NOT_FOUND )
					{
						//AfxMessageBox(_T("In"));				
				
						//Check for comments
						bool lnComment = WSPCheckLineComment( posFunction, posFunction + 8);
						if( lnComment )
						{
							m_bFlagEditVBSFUNCTION = false;
							return SIMPLE_COMMENT;
						}
						bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posFunction );
						if( blkComment )
						{
							m_bFlagEditVBSFUNCTION = false;
							return COMPLEX_COMMENT;
						}
					}
					
					//AfxMessageBox(_T("BOOL TRUE"));
					m_bVBSFUNCTIONCloseParenthesis = true;
					return r = P_SUCCESS;
					
				
			}
		}
		
	}


	if( m_iModificationType == DELETETEXT )
	{
		
		CScintillaCtrl& rCtrl = GetCtrl();
		
		//AfxMessageBox(_T("After Delete"));
		int symbol = rCtrl.GetCharAt(pos);
		str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);
	
		
		if( m_bVBSFUNCTIONCloseParenthesis && symbol != CLOSE_PARENTHESIS )
		{
			CString sEmptyNode = _T("");
			WSPDeleteNodeTree1(sEmptyNode);
			
			LPSTR szKeyWord = "FUNCTION";
						
			long posFunction = WSPSearchToken(pos, 0, szKeyWord);
			long posCloseParenthesis = pos;

			if( posFunction != NOT_FOUND )
			{
				LPSTR szOpenParenthesis = "(";
				long posOpenParenthesis = WSPSearchToken(posFunction, posCloseParenthesis, szOpenParenthesis); 
				
				CString sFunctionName = WSPGetText(posFunction + 8, posOpenParenthesis);
				if( sFunctionName == _T("OVERLOAD" ))
				{
					return AIPI_ERROR;
				}
								
				if( sFunctionName != _T("EMPTY") )
				{
					sFunctionName.TrimRight();
					sFunctionName.TrimLeft();
					r = WSPDeleteNodeTree1(sFunctionName);
					
				}
				
			}
		
		}
		
		m_bVBSFUNCTIONCloseParenthesis = false;
		

	}

	if( m_iModificationType == INSERTTEXT )
	{
		CScintillaCtrl& rCtrl = GetCtrl();
		//CString str;	
		//AfxMessageBox(_T("Insert Text"));
		
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Global Symbol...%d  " ), symbol);
		//AfxMessageBox(str);
		
		if( symbol == CLOSE_PARENTHESIS )
		{
			
			//AfxMessageBox(_T("Add Close Parenthesis"));
			//str.Format(_T("Flg Write Rule...%d  " ), m_bFlagWriteError);
			//AfxMessageBox(str);

			int r = WSPAddVBSFUNCTION( pos, true);
			//str.Format(_T("r...%d  " ), r);
			//AfxMessageBox(str);

			
			if( r != AIPI_ERROR  )
			{
				return r;
				//AfxMessageBox(_T("Rula Addee"));	
				//m_bFlagWriteRule = false;
			}
			
		}

	}

//str.Format(_T("r...%d  " ), r);
//AfxMessageBox(str);
			
return r;

}





int CAIPIEditorView::WSPHandleFunctionCloseParenthesis(long pos )
{
	
	CString str;
	
	int r = AIPI_ERROR;

	if( m_iModificationType == BEFOREDELETE )
	{
		CScintillaCtrl& rCtrl = GetCtrl();
		bool bDetected = false;
		//str.Format(_T("Flg Write Rule...%d  " ), m_bFlagWriteRule);
		//AfxMessageBox(str);

	
		//AfxMessageBox(_T("Before Delete"));
		
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);

		int prevSymbol = rCtrl.GetCharAt(pos -1 );
		//str.Format(_T("Prev Symbol...%d  " ), prevSymbol);
		//AfxMessageBox(str);
		
		
		if( symbol != CLOSE_PARENTHESIS && prevSymbol == CLOSE_PARENTHESIS )
		{
			//AfxMessageBox(_T("Detec Close Parenthesis"));
			bDetected = true;
		}
		
		
		if( symbol == CLOSE_PARENTHESIS && prevSymbol != CLOSE_PARENTHESIS )
		{
			//AfxMessageBox(_T("Detec Close Parenthesis"));
			bDetected = true;
			

		}

		if( bDetected )
		{
			LPSTR szCloseParenthesis = ")";
			LPSTR szOpenParenthesis = "(";

			long posCloseParenthesis = WSPSearchToken( pos -1, m_DocumentLength, szCloseParenthesis);
			long posOpenParenthesis = WSPSearchToken( posCloseParenthesis, 0, szOpenParenthesis);
			long posIdType = WSPSearchNearestIdType(posOpenParenthesis, 0);
	
	
			
			//str.Format(_T("Pos IdType...%d  " ), posIdType);
			//AfxMessageBox(str);
			//str.Format(_T("Pos Close Parenthesis...%d  " ), posCloseParenthesis);
			//AfxMessageBox(str);
			//AfxMessageBox(m_sCurrentType);
	
			if( posIdType != NOT_FOUND && posCloseParenthesis != NOT_FOUND )
			{
				int r = WSPParseFunction( posIdType -1, posCloseParenthesis);
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					//AfxMessageBox(_T("In"));				
					int typeLength = m_sCurrentType.GetLength();	
					//Check for comments
					bool lnComment = WSPCheckLineComment( posIdType, posIdType + typeLength );
					if( lnComment )
					{
						m_bFlagEditFunction = false;
						return SIMPLE_COMMENT;
					}
					bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posIdType );
					if( blkComment )
					{
						m_bFlagEditFunction = false;
						return COMPLEX_COMMENT;
					}
				
					//AfxMessageBox(_T("BOOL TRUE"));
					m_bFunctionCloseParenthesis = true;
					return r = P_SUCCESS;
				}
							
			}
		}
		
	}


	if( m_iModificationType == DELETETEXT )
	{
		
		CScintillaCtrl& rCtrl = GetCtrl();
		
		//AfxMessageBox(_T("After Delete"));
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);
	
		
		if( m_bFunctionCloseParenthesis && symbol != CLOSE_PARENTHESIS )
		{
			CString sEmptyNode = _T("");
			WSPDeleteNodeTree1(sEmptyNode);
			
			LPSTR szOpenParenthesis = "(";
						
			long posIdType = WSPSearchNearestIdType(pos, 0);
			long posCloseParenthesis = pos + 1;
		  
			if( posIdType != NOT_FOUND )
			{
				int typeLength = m_sCurrentType.GetLength();
				long posOpenParenthesis = WSPSearchToken(posIdType, posCloseParenthesis, szOpenParenthesis); 
							
				CString sFunctionName = WSPGetText(posIdType + typeLength, posOpenParenthesis);
				
				if( sFunctionName == _T("OVERLOAD") )
				{
					return AIPI_ERROR;
				}
				
				if( sFunctionName != _T("EMPTY") )
				{
					sFunctionName.TrimRight();
					sFunctionName.TrimLeft();
					//AfxMessageBox(sFunctionName);
					//AfxMessageBox(_T("Delete Rule"));
					//AfxMessageBox(sRuleName);
					r = WSPDeleteNodeTree1(sFunctionName);
					
				}	
			}
		
		}
		
		m_bFunctionCloseParenthesis = false;
		

	}

	if( m_iModificationType == INSERTTEXT )
	{
		CScintillaCtrl& rCtrl = GetCtrl();
		//CString str;	
		//AfxMessageBox(_T("Insert Text"));
		
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Global Symbol...%d  " ), symbol);
		//AfxMessageBox(str);
		
		if( symbol == CLOSE_PARENTHESIS )
		{
			
			//AfxMessageBox(_T("Add Close Parenthesis"));
			//str.Format(_T("Flg Write Rule...%d  " ), m_bFlagWriteError);
			//AfxMessageBox(str);

			int r = WSPAddFunction( pos, true);
			//str.Format(_T("r...%d  " ), r);
			//AfxMessageBox(str);

			
			if( r != AIPI_ERROR  )
			{
				return r;
				//AfxMessageBox(_T("Rula Addee"));	
				//m_bFlagWriteRule = false;
			}
			
		}

	}

//str.Format(_T("r...%d  " ), r);
//AfxMessageBox(str);
			
return r;

}




int CAIPIEditorView::WSPHandleFunctionCloseParenthesisEdit(long pos, LPSTR szType, int typelen )
{
	
	CString str;
	
	int r = AIPI_ERROR;

	if( m_iModificationType == BEFOREDELETE )
	{
		CScintillaCtrl& rCtrl = GetCtrl();
		bool bDetected = false;
		//str.Format(_T("Flg Write Rule...%d  " ), m_bFlagWriteRule);
		//AfxMessageBox(str);
		
		//AfxMessageBox(_T("Before Delete"));
		
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);

		int prevSymbol = rCtrl.GetCharAt(pos -1 );
		//str.Format(_T("Prev Symbol...%d  " ), prevSymbol);
		//AfxMessageBox(str);
		
		
		if( symbol != CLOSE_PARENTHESIS && prevSymbol == CLOSE_PARENTHESIS )
		{
			//AfxMessageBox(_T("Detec Close Parenthesis"));
			bDetected = true;
	
		}
		
		
		if( symbol == CLOSE_PARENTHESIS && prevSymbol != CLOSE_PARENTHESIS )
		{
			//AfxMessageBox(_T("Detec Close Parenthesis"));
			bDetected = true;
			

		}

		if( bDetected )
		{
			//AfxMessageBox(_T("Detected"));
			
			LPSTR szCloseParenthesis = ")";
			LPSTR szOpenParenthesis = "(";

			long posCloseParenthesis = WSPSearchToken( pos -1, m_DocumentLength, szCloseParenthesis);
			long posOpenParenthesis = WSPSearchToken( posCloseParenthesis, 0, szOpenParenthesis);
			long posIdType = WSPSearchToken(posOpenParenthesis, 0, szType);
	
			
			/*
			str.Format(_T("Pos IdType...%d  " ), posIdType);
			AfxMessageBox(str);
			str.Format(_T("Pos Close Parenthesis...%d  " ), posCloseParenthesis);
			AfxMessageBox(str);
			*/
				

			if( posIdType != NOT_FOUND && posCloseParenthesis != NOT_FOUND )
			{
				int r = WSPParseFunction( posIdType -1, posCloseParenthesis);
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					//AfxMessageBox(_T("In"));
					m_sCurrentType = WSPGetText( posIdType, posIdType + typelen);
					//AfxMessageBox(m_sCurrentType);
					//Check for comments
					bool lnComment = WSPCheckLineComment( posIdType, posIdType + typelen );
					if( lnComment )
					{
						m_bFlagEditFunction = false;
						return SIMPLE_COMMENT;
					}
					bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posIdType );
					if( blkComment )
					{
						m_bFlagEditFunction = false;
						return COMPLEX_COMMENT;
					}
									
					//AfxMessageBox(_T("BOOL TRUE"));
					m_bFunctionCloseParenthesis = true;
					return r = P_SUCCESS;
				}	
				
			}
		}
		
	}


	if( m_iModificationType == DELETETEXT )
	{
		
		CScintillaCtrl& rCtrl = GetCtrl();
		
		//AfxMessageBox(_T("After Delete"));
		int symbol = rCtrl.GetCharAt(pos);
		/*
		str.Format(_T("Symbol...%d  " ), symbol);
		AfxMessageBox(str);
		str.Format(_T("Bool Close P...%d  " ), m_bFunctionCloseParenthesis);
		AfxMessageBox(str);
		str.Format(_T("type len...%d  " ), typelen);
		AfxMessageBox(str);
		*/

		LPSTR szCloseParenthesis = ")";
		LPSTR szOpenParenthesis = "(";
		
		if( m_bFunctionCloseParenthesis && symbol != CLOSE_PARENTHESIS )
		{
			//AfxMessageBox(_T("DeleteText In"));
			
			CString sEmptyNode = _T("");
			WSPDeleteNodeTree1(sEmptyNode);
			
			LPSTR szOpenParenthesis = "(";
						
			long posOpenParenthesis = WSPSearchToken( pos, 0, szOpenParenthesis);
			long posIdType = WSPSearchToken(posOpenParenthesis, 0, szType);
			long posCloseParenthesis = pos;
		  
			
			CString sType = szType;
			//AfxMessageBox(sType);
			//AfxMessageBox(m_sCurrentType);
			/*
			str.Format(_T("Pos open Parenthesis...%d  " ), posOpenParenthesis);
			AfxMessageBox(str);
			str.Format(_T("Pos close Parenthesis...%d  " ), posCloseParenthesis);
			AfxMessageBox(str);
			str.Format(_T("Pos Id...%d  " ), posIdType);
			AfxMessageBox(str);
			*/
			
			
			if( sType != m_sCurrentType )
			{
				return AIPI_ERROR;
			}
			

			if( posIdType != NOT_FOUND )
			{
				CString sFunctionName = WSPGetText(posIdType + typelen, posOpenParenthesis);
				if( sFunctionName == _T("OVERLOAD") )
				{
					//AfxMessageBox(sFunctionName);
					return AIPI_ERROR;
				}
			
				
				if( sFunctionName != _T("EMPTY") )
				{
					sFunctionName.TrimRight();
					sFunctionName.TrimLeft();
					//AfxMessageBox(_T("Delete Rule"));
					//AfxMessageBox(sRuleName);
					r = WSPDeleteNodeTree1(sFunctionName);
					
				}	
			}
		
		}
		
		m_bFunctionCloseParenthesis = false;
		

	}

	if( m_iModificationType == INSERTTEXT )
	{
		CScintillaCtrl& rCtrl = GetCtrl();
		//CString str;	
		//AfxMessageBox(_T("Insert Text"));
		
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Global Symbol...%d  " ), symbol);
		//AfxMessageBox(str);
		
		if( symbol == CLOSE_PARENTHESIS )
		{
			
			//AfxMessageBox(_T("Add Close Parenthesis"));
			//str.Format(_T("Flg Write Rule...%d  " ), m_bFlagWriteError);
			//AfxMessageBox(str);

			int r = WSPAddFunction( pos, true);
			//str.Format(_T("r...%d  " ), r);
			//AfxMessageBox(str);

			
			if( r != AIPI_ERROR  )
			{
				return r;
				//AfxMessageBox(_T("Rula Addee"));	
				//m_bFlagWriteRule = false;
			}
			
		}

	}

//str.Format(_T("r...%d  " ), r);
//AfxMessageBox(str);
			
return r;

}



int CAIPIEditorView::WSPHandleRuleCloseParenthesis(long pos)
{
	CString str;
	
	int r = AIPI_ERROR;

	if( m_iModificationType == BEFOREDELETE )
	{
		CScintillaCtrl& rCtrl = GetCtrl();
		bool bDetected = false;
		//str.Format(_T("Flg Write Rule...%d  " ), m_bFlagWriteRule);
		//AfxMessageBox(str);
		

	
		//AfxMessageBox(_T("Before Delete"));
		
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);

		int prevSymbol = rCtrl.GetCharAt(pos -1 );
		//str.Format(_T("Prev Symbol...%d  " ), prevSymbol);
		//AfxMessageBox(str);
		
		
		if( symbol != CLOSE_PARENTHESIS && prevSymbol == CLOSE_PARENTHESIS )
		{
			//AfxMessageBox(_T("Detec Close Parenthesis"));
			bDetected = true;
		}
		
		
		if( symbol == CLOSE_PARENTHESIS && prevSymbol != CLOSE_PARENTHESIS )
		{
			//AfxMessageBox(_T("Detec Close Parenthesis"));
			bDetected = true;
			

		}

		if( bDetected )
		{
			LPSTR szKeyWord = "RULE";
			LPSTR szCloseParenthesis = ")";
			

			long posRule = WSPSearchToken( pos, 0, szKeyWord );
			//long posCloseParenthesis = WSPSearchToken( posRule, m_DocumentLength, szCloseParenthesis);
			long posCloseParenthesis = pos;
			/*
			str.Format(_T("Pos Rule...%d  " ), posRule);
			AfxMessageBox(str);
			str.Format(_T("Pos Close Parenthesis...%d  " ), posCloseParenthesis);
			AfxMessageBox(str);
			*/
	
			if( posRule != NOT_FOUND && posCloseParenthesis != NOT_FOUND )
			{
				int iniSymbol = rCtrl.GetCharAt( posRule -1 );
				int endSymbol =rCtrl.GetCharAt( posRule + 4 );
				//str.Format(_T("ini...%d  " ), iniSymbol);
				//AfxMessageBox(str);
				//str.Format(_T("end...%d  " ), endSymbol);
				//AfxMessageBox(str);
				if(
					(	   iniSymbol != SPACE && iniSymbol != NEW_LINE && iniSymbol != CARRIAGE_RETURN 
						&& iniSymbol != NUL && iniSymbol != HORIZONTAL_TAB )
						|| (     endSymbol != SPACE && endSymbol != NEW_LINE && endSymbol != CARRIAGE_RETURN 
						&& endSymbol != NUL && endSymbol != HORIZONTAL_TAB )
					)
					{
						return NOT_FOUND;
					}
		
				
					int r = WSPParseRule( posRule -1, posCloseParenthesis);
					if( r != AIPI_ERROR && r != NOT_FOUND )
					{
						//AfxMessageBox(_T("In"));				
				
						//Check for comments
						bool lnComment = WSPCheckLineComment( posRule, posRule + 4);
						if( lnComment )
						{
							m_bFlagEditRule = false;
							return SIMPLE_COMMENT;
						}
						bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posRule );
						if( blkComment )
						{
							m_bFlagEditRule = false;
							return COMPLEX_COMMENT;
						}
										
						//AfxMessageBox(_T("BOOL TRUE"));
						m_bRuleCloseParenthesis = true;
						return r = P_SUCCESS;
					}
					
				
			}
		}
		
	}


	if( m_iModificationType == DELETETEXT )
	{
		
		CScintillaCtrl& rCtrl = GetCtrl();
		
		//AfxMessageBox(_T("After Delete"));
		int symbol = rCtrl.GetCharAt(pos);
		str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);
		//str.Format(_T("Flg Rule Close Parenthesis...%d  " ), m_bRuleCloseParenthesis );
		//AfxMessageBox(str);

		
		if( m_bRuleCloseParenthesis && symbol != CLOSE_PARENTHESIS )
		{
			CString sEmptyNode = _T("");
			WSPDeleteNodeTree1(sEmptyNode);
			
			LPSTR szKeyWord = "RULE";
			LPSTR szOpenParenthesis = "(";
			LPSTR szDobleQuotation = "\"";
			
			long posRule = WSPSearchToken(pos, 0, szKeyWord);
			long posCloseParenthesis = pos;

			if( posRule != NOT_FOUND )
			{
				long posStartDobleQuotation = WSPSearchToken( posRule, posCloseParenthesis, szDobleQuotation);
				long posEndDobleQuotation = WSPSearchToken(posStartDobleQuotation + 1, posCloseParenthesis, szDobleQuotation);
				long posOpenParenthesis = WSPSearchToken(posEndDobleQuotation, posCloseParenthesis, szOpenParenthesis); 

			
				CString sRuleName = WSPGetText(posStartDobleQuotation+ 1, posEndDobleQuotation);
				if( sRuleName == _T("OVERLOAD") )
				{
					//AfxMessageBox(sRuleName);
					return AIPI_ERROR;
				}
				if( sRuleName != _T("EMPTY") )
				{
					sRuleName = WSPFormatRuleNameOpt(sRuleName);
					//AfxMessageBox(_T("Delete Rule"));
					//AfxMessageBox(sRuleName);
					r = WSPDeleteNodeTree1(sRuleName);
					
				}	
			}
		
		}
		
		m_bRuleCloseParenthesis = false;
		

	}

	if( m_iModificationType == INSERTTEXT )
	{
		CScintillaCtrl& rCtrl = GetCtrl();
		//CString str;	
		//AfxMessageBox(_T("Insert Text"));
		
		int symbol = rCtrl.GetCharAt(pos);
		//str.Format(_T("Global Symbol...%d  " ), symbol);
		//AfxMessageBox(str);
		
		if( symbol == CLOSE_PARENTHESIS )
		{
			
			//AfxMessageBox(_T("Add Close Parenthesis"));
			//str.Format(_T("Flg Write Rule...%d  " ), m_bFlagWriteError);
			//AfxMessageBox(str);

			int r = WSPAddRule( pos, true);
			//str.Format(_T("r...%d  " ), r);
			//AfxMessageBox(str);

			
			if( r != AIPI_ERROR  )
			{
				return r;
				//AfxMessageBox(_T("Rula Addee"));	
				//m_bFlagWriteRule = false;
			}
			
		}

	}

//str.Format(_T("r...%d  " ), r);
//AfxMessageBox(str);
			
return r;

}



void CAIPIEditorView::WSPHandleEditClassKeyWord( long pos)
{
	
	if( m_iModificationType == BEFOREDELETE )
	{
		long relPos = 0;
		bool bFlag = false;

		int C = 67;
		int L = 76;
		int A = 65;
		int S = 83;
				
		long posClass = WSPDetectKeyWord5(pos-1, C, L, A, S, S);
		if ( posClass != NOT_FOUND )
		{
			//AfxMessageBox(_T("delete detectado"));
			LPSTR szOpenBrace = "{";
			long posOpenBrace = WSPSearchToken( posClass, m_DocumentLength, szOpenBrace);
			int r = WSPParseClass( posClass - 1, posOpenBrace);
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				WSPDeleteClass( pos, true);
			}
			
		}
		else
		{
			posClass = WSPDetectKeyWord5(pos, C, L, A, S, S);
			if ( posClass != NOT_FOUND )
			{
				//AfxMessageBox(_T("delete detectado"));
				LPSTR szOpenBrace = "{";
				long posOpenBrace = WSPSearchToken( posClass, m_DocumentLength, szOpenBrace);
				int r = WSPParseClass( posClass - 1, posOpenBrace);
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					WSPDeleteClass( pos, true);
				}
				
			}
			else
			{
						
				CScintillaCtrl& rCtrl = GetCtrl();
				int symbol = rCtrl.GetCharAt(pos);
				CString str;
				//str.Format(_T("Symbol...%d  " ), symbol);
				//AfxMessageBox(str);
				if( symbol != C && symbol != L && symbol != A && symbol != S   )
				{
					//AfxMessageBox(_T("Hola1"));
	
					relPos = pos;
					bFlag = true;
				}
				else
				{
				
					symbol = rCtrl.GetCharAt(pos -1);
					if( symbol != C && symbol != L && symbol != A && symbol != S  )
					{
						//AfxMessageBox(_T("Hola2"));
						relPos = pos -1;
						bFlag = true;		
					}
				}
			
				if( bFlag )
				{
					
					int C = 67;
					int L = 76;
					int A = 65;
					int S = 83;
				
					posClass = WSPDetectKeyWordEdit5( relPos, C, L, A, S, S);
					if( posClass != NOT_FOUND )
					{
						//AfxMessageBox(_T("In to....."));
						//m_bFlagWriteRule = false;
						LPSTR szOpenBrace = "{";
						

						long posOpenBrace = WSPSearchToken(posClass, m_DocumentLength, szOpenBrace);
						int r = WSPParseClassEdit( posClass, posOpenBrace);
						if( r != AIPI_ERROR && r != NOT_FOUND )
						{
							//AfxMessageBox(_T("In"));				
							//Check for comments
							bool lnComment = WSPCheckLineComment( posClass, posClass + 6);
							if( lnComment )
							{
								m_bFlagEditClass = false;
								return;
							}
							bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posClass );
							if( blkComment )
							{
								m_bFlagEditClass = false;
								return;
							}


							CString sClassName = WSPGetText(posClass + 6, posOpenBrace);
							if( sClassName == _T("OVERLOAD") )
							{
								//AfxMessageBox(sClassName);
								return;
							}
							
							if( sClassName != _T("EMPTY") )
							{
								sClassName.TrimRight();
								sClassName.TrimLeft();
								CString sClassParameter = _T("");
								//CString sFullRuleName = m_sRuleName + sRuleParameter; 
								//AfxMessageBox(m_sTokenName);
								//r = WSPAddNodeTree1(sClassName, sClassParameter, 8);
								r = WSPAddNodeTypeTree1(sClassName, sClassParameter, 14, AIPI_CLASS);
								//CWorkspaceTabView tab;
								//tab.printWSPTree1();
								
							}
						}
			
						
					}
				}
			}
		}
	}

	if( m_iModificationType == INSERTTEXT )
	{
		int C = 67;
		int L = 76;
		int A = 65;
		int S = 83;
						
		long posClass = WSPDetectKeyWord5(pos, C, L, A, S, S);
		if ( posClass != NOT_FOUND )
		{
			//AfxMessageBox(_T("insert detectado"));
			//CString str;
			//str.Format(_T("Write Rule Flag... %d"), m_bFlagWriteRule);
			//AfxMessageBox(str);
			LPSTR szOpenBrace = "{";
			long posOpenBrace = WSPSearchToken(posClass, m_DocumentLength, szOpenBrace);
			int r = WSPParseClass( posClass - 1, posOpenBrace);
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				WSPAddClass( pos, true);
			}
			
		}
		else
		{
			posClass = WSPDetectKeyWordEdit5( pos, C, L, A, S, S);
			if( posClass != NOT_FOUND )
			{
				//AfxMessageBox(_T("In to the detected edit"));
				LPSTR szOpenBrace = "{";
												
				long posOpenBrace = WSPSearchToken(posClass, m_DocumentLength, szOpenBrace);
				int r = WSPParseClassEdit( posClass, posOpenBrace);
			
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					//AfxMessageBox(_T("In"));				
				
					//Check for comments
					bool lnComment = WSPCheckLineComment( posClass, posClass + 6);
					if( lnComment )
					{
						m_bFlagEditClass = false;
						return;
					}
					bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posClass );
					if( blkComment )
					{
						m_bFlagEditClass = false;
						return;
					}
					
					CString sClassName = WSPGetText(posClass + 6, posOpenBrace);
					if( sClassName == _T("OVERLOAD") )
					{
						//AfxMessageBox(sClassName);
						return;
					}
					
					if( sClassName != _T("EMPTY") )
					{
						sClassName.TrimRight();
						sClassName.TrimLeft();
						//AfxMessageBox(sClassName);

						r = WSPDeleteNodeTree1(sClassName);
					
					}
					
				}

			}
		}

	}

}



void CAIPIEditorView::WSPHandleEditQueryKeyWord( long pos)
{
	
	if( m_iModificationType == BEFOREDELETE )
	{
		long relPos = 0;
		bool bFlag = false;

		int S = 83;
		int Q = 81;
		int L = 76;
		int U = 85;
		int E = 69;
		int R = 82;
		int Y = 89;
				
		long posQuery = WSPDetectKeyWord8(pos-1, S, Q, L, Q, U, E, R, Y);
		if ( posQuery != NOT_FOUND )
		{
			//AfxMessageBox(_T("delete detectado"));
			LPSTR szEqual = "=";
			long posEqual = WSPSearchToken( posQuery, m_DocumentLength, szEqual);
			int r = WSPParseQuery( posQuery - 1, posEqual);
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				WSPDeleteQuery( pos, true);
			}
			
		}
		else
		{
			posQuery = WSPDetectKeyWord8(pos, S, Q, L, Q, U, E, R, Y);
			if ( posQuery != NOT_FOUND )
			{
				//AfxMessageBox(_T("delete detectado"));
				LPSTR szEqual = "=";
				long posEqual = WSPSearchToken( posQuery, m_DocumentLength, szEqual);
				int r = WSPParseQuery( posQuery - 1, posEqual);
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					WSPDeleteQuery( pos, true);
				}
				
			}
			else
			{
						
				CScintillaCtrl& rCtrl = GetCtrl();
				int symbol = rCtrl.GetCharAt(pos);
				CString str;
				//str.Format(_T("Symbol...%d  " ), symbol);
				//AfxMessageBox(str);
				if( symbol != S && symbol != Q && symbol != L && symbol != U && symbol != E && symbol != R && symbol != Y   )
				{
					//AfxMessageBox(_T("Hola1"));
	
					relPos = pos;
					bFlag = true;
				}
				else
				{
				
					symbol = rCtrl.GetCharAt(pos -1);
					if( symbol != S && symbol != Q && symbol != L && symbol != U && symbol != E && symbol != R && symbol != Y  )
					{
						//AfxMessageBox(_T("Hola2"));
						relPos = pos -1;
						bFlag = true;		
					}
				}
			
				if( bFlag )
				{
					
					int S = 83;
					int Q = 81;
					int L = 76;
					int U = 85;
					int E = 69;
					int R = 82;
					int Y = 89;
		
				
					posQuery = WSPDetectKeyWordEdit8( relPos, S, Q, L, Q, U, E, R, Y);
					if( posQuery != NOT_FOUND )
					{
						//AfxMessageBox(_T("In to....."));
						//m_bFlagWriteRule = false;
						LPSTR szEqual = "=";
						

						long posEqual = WSPSearchToken(posQuery, m_DocumentLength, szEqual);
						int r = WSPParseQueryEdit( posQuery, posEqual);
						if( r != AIPI_ERROR && r != NOT_FOUND )
						{
							//AfxMessageBox(_T("In"));				
							//Check for comments
							bool lnComment = WSPCheckLineComment( posQuery, posQuery + 9);
							if( lnComment )
							{
								m_bFlagEditQuery = false;
								return;
							}
							bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posQuery );
							if( blkComment )
							{
								m_bFlagEditQuery = false;
								return;
							}


							CString sQueryName = WSPGetText(posQuery + 9, posEqual);
							if( sQueryName == _T("OVERLOAD") )
							{
								//AfxMessageBox(sClassName);
								return;
							}
							
							if( sQueryName != _T("EMPTY") )
							{
								sQueryName.TrimRight();
								sQueryName.TrimLeft();
								CString sQueryParameter = _T("");
								//CString sFullRuleName = m_sRuleName + sRuleParameter; 
								//AfxMessageBox(m_sTokenName);
								//r = WSPAddNodeTree1(sClassName, sClassParameter, 8);
								r = WSPAddNodeTypeTree1(sQueryName, sQueryParameter, 4, AIPI_QUERY);
								//CWorkspaceTabView tab;
								//tab.printWSPTree1();
								
							}
						}
			
						
					}
				}
			}
		}
	}

	if( m_iModificationType == INSERTTEXT )
	{
		int S = 83;
		int Q = 81;
		int L = 76;
		int U = 85;
		int E = 69;
		int R = 82;
		int Y = 89;
						
		long posQuery = WSPDetectKeyWord8(pos, S, Q, L, Q, U, E, R, Y);
		if ( posQuery != NOT_FOUND )
		{
			//AfxMessageBox(_T("insert detectado"));
			//CString str;
			//str.Format(_T("Write Rule Flag... %d"), m_bFlagWriteRule);
			//AfxMessageBox(str);
			LPSTR szEqual = "=";
			long posEqual = WSPSearchToken(posQuery, m_DocumentLength, szEqual);
			int r = WSPParseQuery( posQuery - 1, posEqual);
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				WSPAddQuery( pos, true);
			}
			
		}
		else
		{
			posQuery = WSPDetectKeyWordEdit8( pos, S, Q, L, Q, U, E, R, Y);
			if( posQuery != NOT_FOUND )
			{
				//AfxMessageBox(_T("In to the detected edit"));
				LPSTR szEqual = "=";
												
				long posEqual = WSPSearchToken(posQuery, m_DocumentLength, szEqual);
				int r = WSPParseQueryEdit( posQuery, posEqual);
			
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					//AfxMessageBox(_T("In"));				
				
					//Check for comments
					bool lnComment = WSPCheckLineComment( posQuery, posQuery + 9);
					if( lnComment )
					{
						m_bFlagEditQuery = false;
						return;
					}
					bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posQuery );
					if( blkComment )
					{
						m_bFlagEditQuery = false;
						return;
					}
					
					CString sQueryName = WSPGetText(posQuery + 9, posEqual);
					if( sQueryName == _T("OVERLOAD") )
					{
						//AfxMessageBox(sClassName);
						return;
					}
					
					if( sQueryName != _T("EMPTY") )
					{
						sQueryName.TrimRight();
						sQueryName.TrimLeft();
						//AfxMessageBox(sClassName);

						r = WSPDeleteNodeTree1(sQueryName);
					
					}
					
				}

			}
		}

	}

}





void CAIPIEditorView::WSPHandleEditJSFunctionKeyWord( long pos)
{
	
	if( m_iModificationType == BEFOREDELETE )
	{
		long relPos = 0;
		bool bFlag = false;

		int f = 102;
		int u = 117;
		int n = 110;
		int c = 99;
		int t = 116;
		int i = 105;
		int o = 111;
		
				
		long posFunction = WSPDetectKeyWord8(pos-1, f, u, n, c, t, i, o, n);
		if ( posFunction != NOT_FOUND )
		{
			//AfxMessageBox(_T("delete detectado"));
			LPSTR szCloseParenthesis = ")";
			long posCloseParenthesis = WSPSearchToken( posFunction, m_DocumentLength, szCloseParenthesis);
			int r = WSPParseJSFunction( posFunction - 1, posCloseParenthesis);
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				WSPDeleteJSFunction( pos, true);
			}
			
		}
		else
		{
			posFunction = WSPDetectKeyWord8(pos, f, u, n, c, t, i, o, n);
			if ( posFunction != NOT_FOUND )
			{
				//AfxMessageBox(_T("delete detectado"));
				LPSTR szCloseParenthesis = ")";
				long posCloseParenthesis = WSPSearchToken( posFunction, m_DocumentLength, szCloseParenthesis);
				int r = WSPParseJSFunction( posFunction - 1, posCloseParenthesis);
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					WSPDeleteJSFunction( pos, true);
				}
				
			}
			else
			{
						
				CScintillaCtrl& rCtrl = GetCtrl();
				int symbol = rCtrl.GetCharAt(pos);
				CString str;
				//str.Format(_T("Symbol...%d  " ), symbol);
				//AfxMessageBox(str);
				if( symbol != f && symbol != u && symbol != n && symbol != c && symbol != t && symbol != i && symbol != o )
				{
					//AfxMessageBox(_T("Hola1"));
	
					relPos = pos;
					bFlag = true;
				}
				else
				{
				
					symbol = rCtrl.GetCharAt(pos -1);
					if( symbol != f && symbol != u && symbol != n && symbol != c && symbol != t && symbol != i && symbol != o  )
					{
						//AfxMessageBox(_T("Hola2"));
						relPos = pos -1;
						bFlag = true;		
					}
				}
			
				if( bFlag )
				{
					int f = 102;
					int u = 117;
					int n = 110;
					int c = 99;
					int t = 116;
					int i = 105;
					int o = 111;
		
					
					posFunction = WSPDetectKeyWordEdit8( relPos, f, u, n, c, t, i, o, n);
					if( posFunction != NOT_FOUND )
					{
						//AfxMessageBox(_T("In to....."));
						//m_bFlagWriteRule = false;
						LPSTR szCloseParenthesis = ")";
						

						long posCloseParenthesis = WSPSearchToken(posFunction, m_DocumentLength, szCloseParenthesis);
						int r = WSPParseJSFunctionEdit( posFunction, posCloseParenthesis);
						if( r != AIPI_ERROR && r != NOT_FOUND )
						{
							//AfxMessageBox(_T("In"));				
							//Check for comments
							bool lnComment = WSPCheckLineComment( posFunction, posFunction + 9);
							if( lnComment )
							{
								m_bFlagEditJSFunction = false;
								return;
							}
							bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posFunction );
							if( blkComment )
							{
								m_bFlagEditJSFunction = false;
								return;
							}
							
							LPSTR szOpenParenthesis = "(";

							long posOpenParenthesis = WSPSearchToken(posFunction, posCloseParenthesis, szOpenParenthesis); 
							CString sFunctionName = WSPGetText(posFunction + 9, posOpenParenthesis);
							if( sFunctionName == _T("OVERLOAD") )
							{
								//AfxMessageBox(sClassName);
								return;
							}
							
							if( sFunctionName != _T("EMPTY") )
							{
								
								CString sParameter = WSPFormatParameters( posOpenParenthesis, posCloseParenthesis );
								if( sParameter != _T("COMMENT_ERROR") )
								{
									sFunctionName.TrimRight();
									sFunctionName.TrimLeft();

									CString sFunctionParameter = _T("(") + sParameter + _T(")");
									//CString sFullRuleName = m_sRuleName + sRuleParameter; 
									//AfxMessageBox(m_sTokenName);
									//r = WSPAddNodeTree1(sFunctionName, sFunctionParameter, 4);
									r = WSPAddNodeTypeTree1(sFunctionName, sFunctionParameter, 10, AIPI_FUNCTION);
									//CWorkspaceTabView tab;
									//tab.printWSPTree1();
								}
							}
						}
			
						
					}
				}
			}
		}
	}

	if( m_iModificationType == INSERTTEXT )
	{
		int f = 102;
		int u = 117;
		int n = 110;
		int c = 99;
		int t = 116;
		int i = 105;
		int o = 111;
						
		long posFunction = WSPDetectKeyWord8(pos, f, u, n, c, t, i, o, n);
		if ( posFunction != NOT_FOUND )
		{
			//AfxMessageBox(_T("insert detectado"));
			//CString str;
			//str.Format(_T("Write Rule Flag... %d"), m_bFlagWriteRule);
			//AfxMessageBox(str);
			LPSTR szCloseParenthesis = ")";
			long posCloseParenthesis = WSPSearchToken(posFunction, m_DocumentLength, szCloseParenthesis);
			int r = WSPParseJSFunction( posFunction - 1, posCloseParenthesis);
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				WSPAddJSFunction( pos, true);
			}
			
		}
		else
		{
			posFunction = WSPDetectKeyWordEdit8( pos, f, u, n, c, t, i, o, n);
			if( posFunction != NOT_FOUND )
			{
				//AfxMessageBox(_T("In to the detected edit"));
				LPSTR szCloseParenthesis = ")";
												
				long posCloseParenthesis = WSPSearchToken(posFunction, m_DocumentLength, szCloseParenthesis);
				int r = WSPParseJSFunctionEdit( posFunction, posCloseParenthesis);
			
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					//AfxMessageBox(_T("In"));				
				
					//Check for comments
					bool lnComment = WSPCheckLineComment( posFunction, posFunction + 9);
					if( lnComment )
					{
						m_bFlagEditJSFunction = false;
						return;
					}
					bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posFunction );
					if( blkComment )
					{
						m_bFlagEditJSFunction = false;
						return;
					}
					
					LPSTR szOpenParenthesis = "(";
				
					long posOpenParenthesis = WSPSearchToken(posFunction, posCloseParenthesis, szOpenParenthesis);
					CString sFunctionName = WSPGetText(posFunction + 9, posOpenParenthesis);
					if( sFunctionName == _T("OVERLOAD") )
					{
						//AfxMessageBox(sFunctionName);
						return;
					}
							
					
					if( sFunctionName != _T("EMPTY") )
					{
						sFunctionName.TrimRight();
						sFunctionName.TrimLeft();
						//AfxMessageBox(sFunctionName);
						r = WSPDeleteNodeTree1(sFunctionName);
					
					}
					
				}

			}
		}

	}

}




void CAIPIEditorView::WSPHandleEditVBSFunctionKeyWord( long pos)
{
	
	if( m_iModificationType == BEFOREDELETE )
	{
		long relPos = 0;
		bool bFlag = false;

		int F = 70;
		int u = 117;
		int n = 110;
		int c = 99;
		int t = 116;
		int i = 105;
		int o = 111;
		
				
		long posFunction = WSPDetectKeyWord8(pos-1, F, u, n, c, t, i, o, n);
		if ( posFunction != NOT_FOUND )
		{
			//AfxMessageBox(_T("delete detectado"));
			LPSTR szCloseParenthesis = ")";
			long posCloseParenthesis = WSPSearchToken( posFunction, m_DocumentLength, szCloseParenthesis);
			int r = WSPParseVBSFunction( posFunction - 1, posCloseParenthesis);
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				WSPDeleteVBSFunction( pos, true);
			}
			
		}
		else
		{
			posFunction = WSPDetectKeyWord8(pos, F, u, n, c, t, i, o, n);
			if ( posFunction != NOT_FOUND )
			{
				//AfxMessageBox(_T("delete detectado"));
				LPSTR szCloseParenthesis = ")";
				long posCloseParenthesis = WSPSearchToken( posFunction, m_DocumentLength, szCloseParenthesis);
				int r = WSPParseVBSFunction( posFunction - 1, posCloseParenthesis);
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					WSPDeleteVBSFunction( pos, true);
				}
				
			}
			else
			{
						
				CScintillaCtrl& rCtrl = GetCtrl();
				int symbol = rCtrl.GetCharAt(pos);
				CString str;
				//str.Format(_T("Symbol...%d  " ), symbol);
				//AfxMessageBox(str);
				if( symbol != F && symbol != u && symbol != n && symbol != c && symbol != t && symbol != i && symbol != o )
				{
					//AfxMessageBox(_T("Hola1"));
	
					relPos = pos;
					bFlag = true;
				}
				else
				{
				
					symbol = rCtrl.GetCharAt(pos -1);
					if( symbol != F && symbol != u && symbol != n && symbol != c && symbol != t && symbol != i && symbol != o  )
					{
						//AfxMessageBox(_T("Hola2"));
						relPos = pos -1;
						bFlag = true;		
					}
				}
			
				if( bFlag )
				{
					int F = 70;
					int u = 117;
					int n = 110;
					int c = 99;
					int t = 116;
					int i = 105;
					int o = 111;
		
					
					posFunction = WSPDetectKeyWordEdit8( relPos, F, u, n, c, t, i, o, n);
					if( posFunction != NOT_FOUND )
					{
						//AfxMessageBox(_T("In to....."));
						//m_bFlagWriteRule = false;
						LPSTR szCloseParenthesis = ")";
						

						long posCloseParenthesis = WSPSearchToken(posFunction, m_DocumentLength, szCloseParenthesis);
						int r = WSPParseJSFunctionEdit( posFunction, posCloseParenthesis);
						if( r != AIPI_ERROR && r != NOT_FOUND )
						{
							//AfxMessageBox(_T("In"));				
							//Check for comments
							bool lnComment = WSPCheckLineComment( posFunction, posFunction + 9);
							if( lnComment )
							{
								m_bFlagEditVBSFunction = false;
								return;
							}
							bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posFunction );
							if( blkComment )
							{
								m_bFlagEditVBSFunction = false;
								return;
							}
							
							LPSTR szOpenParenthesis = "(";

							long posOpenParenthesis = WSPSearchToken(posFunction, posCloseParenthesis, szOpenParenthesis); 
							CString sFunctionName = WSPGetText(posFunction + 9, posOpenParenthesis);
							if( sFunctionName == _T("OVERLOAD") )
							{
								//AfxMessageBox(sClassName);
								return;
							}
							
							if( sFunctionName != _T("EMPTY") )
							{
								
								CString sParameter = WSPFormatParameters( posOpenParenthesis, posCloseParenthesis );
								if( sParameter != _T("COMMENT_ERROR") )
								{
									sFunctionName.TrimRight();
									sFunctionName.TrimLeft();

									CString sFunctionParameter = _T("(") + sParameter + _T(")");
									//CString sFullRuleName = m_sRuleName + sRuleParameter; 
									//AfxMessageBox(m_sTokenName);
									//r = WSPAddNodeTree1(sFunctionName, sFunctionParameter, 4);
									r = WSPAddNodeTypeTree1(sFunctionName, sFunctionParameter, 12, AIPI_FUNCTION);
						
									//CWorkspaceTabView tab;
									//tab.printWSPTree1();
								}
							}
						}
			
						
					}
				}
			}
		}
	}

	if( m_iModificationType == INSERTTEXT )
	{
		int F = 70;
		int u = 117;
		int n = 110;
		int c = 99;
		int t = 116;
		int i = 105;
		int o = 111;
						
		long posFunction = WSPDetectKeyWord8(pos, F, u, n, c, t, i, o, n);
		if ( posFunction != NOT_FOUND )
		{
			//AfxMessageBox(_T("insert detectado"));
			//CString str;
			//str.Format(_T("Write Rule Flag... %d"), m_bFlagWriteRule);
			//AfxMessageBox(str);
			LPSTR szCloseParenthesis = ")";
			long posCloseParenthesis = WSPSearchToken(posFunction, m_DocumentLength, szCloseParenthesis);
			int r = WSPParseVBSFunction( posFunction - 1, posCloseParenthesis);
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				WSPAddVBSFunction( pos, true);
			}
			
		}
		else
		{
			posFunction = WSPDetectKeyWordEdit8( pos, F, u, n, c, t, i, o, n);
			if( posFunction != NOT_FOUND )
			{
				//AfxMessageBox(_T("In to the detected edit"));
				LPSTR szCloseParenthesis = ")";
												
				long posCloseParenthesis = WSPSearchToken(posFunction, m_DocumentLength, szCloseParenthesis);
				int r = WSPParseVBSFunctionEdit( posFunction, posCloseParenthesis);
			
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					//AfxMessageBox(_T("In"));				
				
					//Check for comments
					bool lnComment = WSPCheckLineComment( posFunction, posFunction + 9);
					if( lnComment )
					{
						m_bFlagEditVBSFunction = false;
						return;
					}
					bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posFunction );
					if( blkComment )
					{
						m_bFlagEditVBSFunction = false;
						return;
					}
					
					LPSTR szOpenParenthesis = "(";
				
					long posOpenParenthesis = WSPSearchToken(posFunction, posCloseParenthesis, szOpenParenthesis);
					CString sFunctionName = WSPGetText(posFunction + 9, posOpenParenthesis);
					if( sFunctionName == _T("OVERLOAD") )
					{
						//AfxMessageBox(sFunctionName);
						return;
					}
							
					
					if( sFunctionName != _T("EMPTY") )
					{
						sFunctionName.TrimRight();
						sFunctionName.TrimLeft();
						//AfxMessageBox(sFunctionName);
						r = WSPDeleteNodeTree1(sFunctionName);
					
					}
					
				}

			}
		}

	}

}




void CAIPIEditorView::WSPHandleEditVBSFUNCTIONKeyWord( long pos)
{
	
	if( m_iModificationType == BEFOREDELETE )
	{
		long relPos = 0;
		bool bFlag = false;

		int F = 70;
		int U = 85;
		int N = 78;
		int C = 67;
		int T = 84;
		int I = 73;
		int O = 79;
		
				
		long posFunction = WSPDetectKeyWord8(pos-1, F, U, N, C, T, I, O, N);
		if ( posFunction != NOT_FOUND )
		{
			//AfxMessageBox(_T("delete detectado"));
			LPSTR szCloseParenthesis = ")";
			long posCloseParenthesis = WSPSearchToken( posFunction, m_DocumentLength, szCloseParenthesis);
			int r = WSPParseVBSFunction( posFunction - 1, posCloseParenthesis);
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				WSPDeleteVBSFunction( pos, true);
			}
			
		}
		else
		{
			posFunction = WSPDetectKeyWord8(pos, F, U, N, C, T, I, O, N);
			if ( posFunction != NOT_FOUND )
			{
				//AfxMessageBox(_T("delete detectado"));
				LPSTR szCloseParenthesis = ")";
				long posCloseParenthesis = WSPSearchToken( posFunction, m_DocumentLength, szCloseParenthesis);
				int r = WSPParseVBSFunction( posFunction - 1, posCloseParenthesis);
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					WSPDeleteVBSFunction( pos, true);
				}
				
			}
			else
			{
						
				CScintillaCtrl& rCtrl = GetCtrl();
				int symbol = rCtrl.GetCharAt(pos);
				CString str;
				//str.Format(_T("Symbol...%d  " ), symbol);
				//AfxMessageBox(str);
				if( symbol != F && symbol != U && symbol != N && symbol != C && symbol != T && symbol != I && symbol != O )
				{
					//AfxMessageBox(_T("Hola1"));
	
					relPos = pos;
					bFlag = true;
				}
				else
				{
				
					symbol = rCtrl.GetCharAt(pos -1);
					if( symbol != F && symbol != U && symbol != N && symbol != C && symbol != T && symbol != I && symbol != O  )
					{
						//AfxMessageBox(_T("Hola2"));
						relPos = pos -1;
						bFlag = true;		
					}
				}
			
				if( bFlag )
				{
					
					int F = 70;
					int U = 85;
					int N = 78;
					int C = 67;
					int T = 84;
					int I = 73;
					int O = 79;
		
					posFunction = WSPDetectKeyWordEdit8( relPos, F, U, N, C, T, I, O, N);
					if( posFunction != NOT_FOUND )
					{
						//AfxMessageBox(_T("In to....."));
						//m_bFlagWriteRule = false;
						LPSTR szCloseParenthesis = ")";
						

						long posCloseParenthesis = WSPSearchToken(posFunction, m_DocumentLength, szCloseParenthesis);
						int r = WSPParseVBSFunctionEdit( posFunction, posCloseParenthesis);
						if( r != AIPI_ERROR && r != NOT_FOUND )
						{
							//AfxMessageBox(_T("In"));				
							//Check for comments
							bool lnComment = WSPCheckLineComment( posFunction, posFunction + 9);
							if( lnComment )
							{
								m_bFlagEditVBSFunction = false;
								return;
							}
							bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posFunction );
							if( blkComment )
							{
								m_bFlagEditVBSFunction = false;
								return;
							}
							
							LPSTR szOpenParenthesis = "(";

							long posOpenParenthesis = WSPSearchToken(posFunction, posCloseParenthesis, szOpenParenthesis); 
							CString sFunctionName = WSPGetText(posFunction + 9, posOpenParenthesis);
							if( sFunctionName == _T("OVERLOAD") )
							{
								//AfxMessageBox(sClassName);
								return;
							}
							
							if( sFunctionName != _T("EMPTY") )
							{
								
								CString sParameter = WSPFormatParameters( posOpenParenthesis, posCloseParenthesis );
								if( sParameter != _T("COMMENT_ERROR") )
								{
									sFunctionName.TrimRight();
									sFunctionName.TrimLeft();

									CString sFunctionParameter = _T("(") + sParameter + _T(")");
									//CString sFullRuleName = m_sRuleName + sRuleParameter; 
									//AfxMessageBox(m_sTokenName);
									//r = WSPAddNodeTree1(sFunctionName, sFunctionParameter, 4);
									r = WSPAddNodeTypeTree1(sFunctionName, sFunctionParameter, 12, AIPI_FUNCTION );
						
									//CWorkspaceTabView tab;
									//tab.printWSPTree1();
								}
							}
						}
			
						
					}
				}
			}
		}
	}

	if( m_iModificationType == INSERTTEXT )
	{
		int F = 70;
		int u = 117;
		int n = 110;
		int c = 99;
		int t = 116;
		int i = 105;
		int o = 111;
						
		long posFunction = WSPDetectKeyWord8(pos, F, u, n, c, t, i, o, n);
		if ( posFunction != NOT_FOUND )
		{
			//AfxMessageBox(_T("insert detectado"));
			//CString str;
			//str.Format(_T("Write Rule Flag... %d"), m_bFlagWriteRule);
			//AfxMessageBox(str);
			LPSTR szCloseParenthesis = ")";
			long posCloseParenthesis = WSPSearchToken(posFunction, m_DocumentLength, szCloseParenthesis);
			int r = WSPParseJSFunction( posFunction - 1, posCloseParenthesis);
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				WSPAddVBSFunction( pos, true);
			}
			
		}
		else
		{
			posFunction = WSPDetectKeyWordEdit8( pos, F, u, n, c, t, i, o, n);
			if( posFunction != NOT_FOUND )
			{
				//AfxMessageBox(_T("In to the detected edit"));
				LPSTR szCloseParenthesis = ")";
												
				long posCloseParenthesis = WSPSearchToken(posFunction, m_DocumentLength, szCloseParenthesis);
				int r = WSPParseVBSFunctionEdit( posFunction, posCloseParenthesis);
			
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					//AfxMessageBox(_T("In"));				
				
					//Check for comments
					bool lnComment = WSPCheckLineComment( posFunction, posFunction + 9);
					if( lnComment )
					{
						m_bFlagEditVBSFunction = false;
						return;
					}
					bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posFunction );
					if( blkComment )
					{
						m_bFlagEditVBSFunction = false;
						return;
					}
					
					LPSTR szOpenParenthesis = "(";
				
					long posOpenParenthesis = WSPSearchToken(posFunction, posCloseParenthesis, szOpenParenthesis);
					CString sFunctionName = WSPGetText(posFunction + 9, posOpenParenthesis);
					if( sFunctionName == _T("OVERLOAD") )
					{
						//AfxMessageBox(sFunctionName);
						return;
					}
							
					
					if( sFunctionName != _T("EMPTY") )
					{
						sFunctionName.TrimRight();
						sFunctionName.TrimLeft();
						//AfxMessageBox(sFunctionName);
						r = WSPDeleteNodeTree1(sFunctionName);
					
					}
					
				}

			}
		}

	}

}




void CAIPIEditorView::WSPHandleEditRuleKeyWord( long pos)
{
	CString str;
	
	if( m_iModificationType == BEFOREDELETE )
	{
		long relPos = 0;
		bool bFlag = false;
		int R = 82;
		int U = 85;
		int L = 76;
		int E = 69;

		long posRule = WSPDetectKeyWord4(pos-1, R, U, L, E);
		if ( posRule != NOT_FOUND )
		{
			//AfxMessageBox(_T("delete detectado"));
			LPSTR szCloseParenthesis = ")";
			long posCloseParenthesis = WSPSearchToken( posRule, m_DocumentLength, szCloseParenthesis);
			int r = WSPParseRule( posRule - 1, posCloseParenthesis);
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				WSPDeleteRule( pos + 5, true);
			}
			
		}
		
		else
		{
			posRule = WSPDetectKeyWord4(pos, R, U, L, E);
			if ( posRule != NOT_FOUND )
			{
				//AfxMessageBox(_T("delete detectado"));
				LPSTR szCloseParenthesis = ")";
				long posCloseParenthesis = WSPSearchToken( posRule, m_DocumentLength, szCloseParenthesis);
				int r = WSPParseRule( posRule - 1, posCloseParenthesis);
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					WSPDeleteRule( pos + 5, true);
				}
				
			}
			else
			{
				CScintillaCtrl& rCtrl = GetCtrl();
				int symbol = rCtrl.GetCharAt(pos);
			
				//str.Format(_T("Symbol...%d  " ), symbol);
				//AfxMessageBox(str);
				if( symbol != R && symbol != U && symbol != L && symbol != E )
				{
					//AfxMessageBox(_T("Hola1"));
	
					relPos = pos;
					bFlag = true;
				}
				else
				{
				
					symbol = rCtrl.GetCharAt(pos -1);
					if( symbol != R && symbol != U && symbol != L && symbol != E )
					{
						//AfxMessageBox(_T("Hola2"));
						relPos = pos -1;
						bFlag = true;		
					}
				}
			
				if( bFlag )
				{
					int R = 82;
					int U = 85;
					int L = 76;
					int E = 69;

					//str.Format(_T("Relative pos...%d  " ), relPos);
					//AfxMessageBox(str);
			
					posRule = WSPDetectKeyWordEdit4( relPos, R, U, L, E);
					if( posRule != NOT_FOUND )
					{
						//AfxMessageBox(_T("In to....."));
						//m_bFlagWriteRule = false;
						LPSTR szOpenParenthesis = "(";
						LPSTR szCloseParenthesis = ")";
						LPSTR szDobleQuotation = "\"";

						long posCloseParenthesis = WSPSearchToken(posRule, m_DocumentLength, szCloseParenthesis);
						int r = WSPParseRuleEdit( posRule, posCloseParenthesis);
						if( r != AIPI_ERROR && r != NOT_FOUND )
						{
							//AfxMessageBox(_T("In"));				
							//Check for comments
							bool lnComment = WSPCheckLineComment( posRule, posRule + 4);
							if( lnComment )
							{
								m_bFlagEditRule = false;
								return;
							}
							bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posRule );
							if( blkComment )
							{
								m_bFlagEditRule = false;
								return;
							}


							long posStartDobleQuotation = WSPSearchToken( posRule, posCloseParenthesis, szDobleQuotation);
							long posEndDobleQuotation = WSPSearchToken(posStartDobleQuotation + 1, posCloseParenthesis, szDobleQuotation);
							long posOpenParenthesis = WSPSearchToken(posEndDobleQuotation, posCloseParenthesis, szOpenParenthesis); 

			
							CString sRuleName = WSPGetText(posStartDobleQuotation+ 1, posEndDobleQuotation);
							if( sRuleName == _T("OVERLOAD") )
							{
								//AfxMessageBox(sRuleName);
								return;
							}
							

							if( sRuleName != _T("EMPTY") )
							{
								
								CString sParameter = WSPFormatParameters( posOpenParenthesis, posCloseParenthesis );
								if( sParameter != _T("COMMENT_ERROR") )
								{
									sRuleName = WSPFormatRuleNameOpt(sRuleName);
									CString sRuleParameter = _T("(") + sParameter + _T(")");
									//CString sFullRuleName = m_sRuleName + sRuleParameter; 
									//AfxMessageBox(m_sTokenName);
									//r = WSPAddNodeTree1(sRuleName, sRuleParameter, 2);
									r = WSPAddNodeTypeTree1(sRuleName, sRuleParameter, 2, AIPI_RULE);
						
									//CWorkspaceTabView tab;
									//tab.printWSPTree1();
								}
							}
						}
					}
				}
			}
		}
	}

	if( m_iModificationType == INSERTTEXT )
	{
		int R = 82;
		int U = 85;
		int L = 76;
		int E = 69;

		long posRule = WSPDetectKeyWord4(pos, R, U, L, E);
		if ( posRule != NOT_FOUND )
		{
			//AfxMessageBox(_T("insert detectado"));
			//CString str;
			//str.Format(_T("Write Rule Flag... %d"), m_bFlagWriteRule);
			//AfxMessageBox(str);
		
			WSPAddRule( pos + 5, true);
			
		}
		else
		{
			posRule = WSPDetectKeyWordEdit4( pos, R, U, L, E);
			if( posRule != NOT_FOUND )
			{
				//m_bFlagWriteRule = false;
				//AfxMessageBox(_T("In to the detected edit"));
				LPSTR szOpenParenthesis = "(";
				LPSTR szCloseParenthesis = ")";
				LPSTR szDobleQuotation = "\"";
				
				long posCloseParenthesis = WSPSearchToken(posRule, m_DocumentLength, szCloseParenthesis);
				int r = WSPParseRuleEdit( posRule, posCloseParenthesis);
			
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					//AfxMessageBox(_T("In"));				
				
					//Check for comments
					bool lnComment = WSPCheckLineComment( posRule, posRule + 4);
					if( lnComment )
					{
						m_bFlagEditRule = false;
						return;
					}
					bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posRule );
					if( blkComment )
					{
						m_bFlagEditRule = false;
						return;
					}

					long posStartDobleQuotation = WSPSearchToken( posRule, posCloseParenthesis, szDobleQuotation);
					long posEndDobleQuotation = WSPSearchToken(posStartDobleQuotation + 1, posCloseParenthesis, szDobleQuotation);
					long posOpenParenthesis = WSPSearchToken(posEndDobleQuotation, posCloseParenthesis, szOpenParenthesis); 

			
					CString sRuleName = WSPGetText(posStartDobleQuotation+ 1, posEndDobleQuotation);
					if( sRuleName == _T("OVERLOAD") )
					{
						//AfxMessageBox(sRuleName);
						return;
					}
					if( sRuleName != _T("EMPTY") )
					{
						sRuleName = WSPFormatRuleNameOpt(sRuleName);
						r = WSPDeleteNodeTree1(sRuleName);
									
					}
				}

			}
		}

	}

}



void CAIPIEditorView::WSPHandleFunctionEditIntKeyWord( long pos)
{
	
	if( m_iModificationType == BEFOREDELETE )
	{
		long relPos = 0;
		bool bFlag = false;
		int i = 105;
		int n = 110;
		int t = 116;
		
		long posIdType = WSPDetectKeyWord3(pos-1, i, n, t);
		if ( posIdType != NOT_FOUND )
		{
			//AfxMessageBox(_T("delete detectado"));
			LPSTR szCloseParenthesis = ")";
			long posCloseParenthesis = WSPSearchToken( posIdType, m_DocumentLength, szCloseParenthesis);
			int r = WSPParseFunction( posIdType - 1, posCloseParenthesis);
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				WSPDeleteFunction( pos, true);
			}
			
		}
		else
		{
			posIdType = WSPDetectKeyWord3(pos, i, n, t);
			if ( posIdType != NOT_FOUND )
			{
				//AfxMessageBox(_T("delete detectado"));
				LPSTR szCloseParenthesis = ")";
				long posCloseParenthesis = WSPSearchToken( posIdType, m_DocumentLength, szCloseParenthesis);
				int r = WSPParseFunction( posIdType -1, posCloseParenthesis);
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
			
					WSPDeleteFunction( pos, true);
					
				}
			}
			else
			{
						
				CScintillaCtrl& rCtrl = GetCtrl();
				int symbol = rCtrl.GetCharAt(pos);
				CString str;
				//str.Format(_T("Symbol...%d  " ), symbol);
				//AfxMessageBox(str);
				if( symbol != i && symbol != n && symbol != t  )
				{
					//AfxMessageBox(_T("Hola1"));
	
					relPos = pos;
					bFlag = true;
				}
				else
				{
				
					symbol = rCtrl.GetCharAt(pos -1);
					if( symbol != i && symbol != n && symbol != t )
					{
						//AfxMessageBox(_T("Hola2"));
						relPos = pos -1;
						bFlag = true;		
					}
				}
			
				if( bFlag )
				{
					int i = 105;
					int n = 110;
					int t = 116;
				
					posIdType = WSPDetectKeyWordEdit3( relPos, i, n, t);
					if( posIdType != NOT_FOUND )
					{
						//AfxMessageBox(_T("In to....."));
						//m_bFlagWriteRule = false;
						LPSTR szOpenParenthesis = "(";
						LPSTR szCloseParenthesis = ")";
					

						long posCloseParenthesis = WSPSearchToken(posIdType, m_DocumentLength, szCloseParenthesis);
						int r = WSPParseFunctionEdit( posIdType, posCloseParenthesis, C_INT, 3);
						if( r != AIPI_ERROR && r != NOT_FOUND )
						{
							//AfxMessageBox(_T("In"));				
							//Check for comments
							bool lnComment = WSPCheckLineComment( posIdType, posIdType + 4);
							if( lnComment )
							{
								m_bFlagEditFunction = false;
								return;
							}
							bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posIdType );
							if( blkComment )
							{
								m_bFlagEditFunction = false;
								return;
							}


							long posOpenParenthesis = WSPSearchToken(posIdType, posCloseParenthesis, szOpenParenthesis); 
							CString sFunctionName = WSPGetText(posIdType + 4, posOpenParenthesis);
							if( sFunctionName == _T("OVERLOAD") )
							{
								//AfxMessageBox(sFunctionName);
								return;
							}
							
							if( sFunctionName != _T("EMPTY") )
							{
								
								CString sParameter = WSPFormatParameters( posOpenParenthesis, posCloseParenthesis );
								if( sParameter != _T("COMMENT_ERROR") )
								{
									sFunctionName.TrimRight();
									sFunctionName.TrimLeft();
									CString sFunctionParameter = _T("(") + sParameter + _T(")");
									//CString sFullRuleName = m_sRuleName + sRuleParameter; 
									//AfxMessageBox(m_sTokenName);
									//r = WSPAddNodeTree1(sFunctionName, sFunctionParameter, 4);
									r = WSPAddNodeTypeTree1(sFunctionName, sFunctionParameter, 6, AIPI_FUNCTION);
						
									//CWorkspaceTabView tab;
									//tab.printWSPTree1();
								}
							}
						}
			
						
					}
				}
			}
		}
	}

	if( m_iModificationType == INSERTTEXT )
	{
		int i = 105;
		int n = 110;
		int t = 116;
		
		long posIdType = WSPDetectKeyWord3(pos, i, n, t);
		if ( posIdType != NOT_FOUND )
		{
			//AfxMessageBox(_T("insert detectado"));
			//CString str;
			//str.Format(_T("Write Rule Flag... %d"), m_bFlagWriteRule);
			//AfxMessageBox(str);
			LPSTR szCloseParenthesis = ")";
			long posCloseParenthesis = WSPSearchToken(posIdType, m_DocumentLength, szCloseParenthesis);
			int r = WSPParseFunction( posIdType - 1, posCloseParenthesis);
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				WSPAddFunction( pos ,true);
			}
			
		}
		else
		{
			posIdType = WSPDetectKeyWordEdit3( pos, i, n, t);
			if( posIdType != NOT_FOUND )
			{
				//m_bFlagWriteRule = false;
				//AfxMessageBox(_T("In to the detected edit"));
				LPSTR szOpenParenthesis = "(";
				LPSTR szCloseParenthesis = ")";
								
				long posCloseParenthesis = WSPSearchToken(posIdType, m_DocumentLength, szCloseParenthesis);
				int r = WSPParseFunctionEdit( posIdType, posCloseParenthesis, C_INT, 3);
			
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					//AfxMessageBox(_T("In"));				
				
					//Check for comments
					bool lnComment = WSPCheckLineComment( posIdType, posIdType + 4);
					if( lnComment )
					{
						m_bFlagEditFunction = false;
						return;
					}
					bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posIdType );
					if( blkComment )
					{
						m_bFlagEditFunction = false;
						return;
					}
					
					long posOpenParenthesis = WSPSearchToken(posIdType, posCloseParenthesis, szOpenParenthesis);
					CString sFunctionName = WSPGetText(posIdType + 4, posOpenParenthesis);
					if( sFunctionName == _T("OVERLOAD") )
					{
						//AfxMessageBox(sFunctionName);
						return;
					}
					

					if( sFunctionName != _T("EMPTY") )
					{
						sFunctionName.TrimRight();
						sFunctionName.TrimLeft();
						//AfxMessageBox(sFunctionName);
						r = WSPDeleteNodeTree1(sFunctionName);
					
					}
					
				}

			}
		}

	}

}



void CAIPIEditorView::WSPHandleVariableEditIntKeyWord( long pos)
{
	
	if( m_iModificationType == BEFOREDELETE )
	{
		long relPos = 0;
		bool bFlag = false;
		int i = 105;
		int n = 110;
		int t = 116;
		
		long posIdType = WSPDetectKeyWord3(pos-1, i, n, t);
		if ( posIdType != NOT_FOUND )
		{
			//AfxMessageBox(_T("delete detectado"));
			LPSTR szSemiColon = ";";
			long posSemiColon = WSPSearchToken( posIdType, m_DocumentLength, szSemiColon);
			int r = WSPParseVariable( posIdType - 1, posSemiColon);
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				WSPDeleteVariable( pos, true);
			}
			
		}
		else
		{
			posIdType = WSPDetectKeyWord3(pos, i, n, t);
			if ( posIdType != NOT_FOUND )
			{
				//AfxMessageBox(_T("delete detectado"));
				LPSTR szSemiColon = ";";
				long posSemiColon = WSPSearchToken( posIdType, m_DocumentLength, szSemiColon);
				int r = WSPParseVariable( posIdType -1, posSemiColon);
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
			
					WSPDeleteVariable( pos, true);
					
				}
			}
			else
			{
						
				CScintillaCtrl& rCtrl = GetCtrl();
				int symbol = rCtrl.GetCharAt(pos);
				CString str;
				//str.Format(_T("Symbol...%d  " ), symbol);
				//AfxMessageBox(str);
				if( symbol != i && symbol != n && symbol != t  )
				{
					//AfxMessageBox(_T("Hola1"));
	
					relPos = pos;
					bFlag = true;
				}
				else
				{
				
					symbol = rCtrl.GetCharAt(pos -1);
					if( symbol != i && symbol != n && symbol != t )
					{
						//AfxMessageBox(_T("Hola2"));
						relPos = pos -1;
						bFlag = true;		
					}
				}
			
				if( bFlag )
				{
					int i = 105;
					int n = 110;
					int t = 116;
				
					posIdType = WSPDetectKeyWordEdit3( relPos, i, n, t);
					if( posIdType != NOT_FOUND )
					{
						//AfxMessageBox(_T("In to....."));
						//m_bFlagWriteRule = false;
						
						LPSTR szSemiColon = ";";
					
						long posSemiColon = WSPSearchToken(posIdType, m_DocumentLength, szSemiColon);
						int r = WSPParseVariableEdit( posIdType, posSemiColon, C_INT, 3);
						if( r != AIPI_ERROR && r != NOT_FOUND )
						{
							//AfxMessageBox(_T("In"));				
							//Check for comments
							bool lnComment = WSPCheckLineComment( posIdType, posIdType + 4);
							if( lnComment )
							{
								m_bFlagEditVariable = false;
								return;
							}
							bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posIdType );
							if( blkComment )
							{
								m_bFlagEditVariable = false;
								return;
							}


							CString sVariableName = WSPGetText(posIdType + 4, posSemiColon);
							if( sVariableName == _T("OVERLOAD") )
							{
								//AfxMessageBox(sVariableName);
								return;
							}
							
							if( sVariableName != _T("EMPTY") )
							{
								sVariableName.TrimRight();
								sVariableName.TrimLeft();
								CString sVariableParameter = _T("");
								//CString sFullRuleName = m_sRuleName + sRuleParameter; 
								//AfxMessageBox(m_sTokenName);
								//r = WSPAddNodeTree1(sVariableName, sVariableParameter, 6);
								r = WSPAddNodeTypeTree1(sVariableName, sVariableParameter, 8, AIPI_VARIABLE);
						
								//CWorkspaceTabView tab;
								//tab.printWSPTree1();
								
							}
						}
			
						
					}
				}
			}
		}
	}

	if( m_iModificationType == INSERTTEXT )
	{
		int i = 105;
		int n = 110;
		int t = 116;
		
		long posIdType = WSPDetectKeyWord3(pos, i, n, t);
		if ( posIdType != NOT_FOUND )
		{
			//AfxMessageBox(_T("insert detectado"));
			//CString str;
			//str.Format(_T("Write Rule Flag... %d"), m_bFlagWriteRule);
			//AfxMessageBox(str);
			LPSTR szSemiColon = ";";
			long posSemiColon = WSPSearchToken(posIdType, m_DocumentLength, szSemiColon);
			int r = WSPParseVariable( posIdType - 1, posSemiColon);
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				WSPAddVariable( pos, true);
			}
			
		}
		else
		{
			posIdType = WSPDetectKeyWordEdit3( pos, i, n, t);
			if( posIdType != NOT_FOUND )
			{
				//m_bFlagWriteRule = false;
				//AfxMessageBox(_T("In to the detected edit"));
				LPSTR szSemiColon = ";";
								
				long posSemiColon = WSPSearchToken(posIdType, m_DocumentLength, szSemiColon);
				int r = WSPParseVariableEdit( posIdType, posSemiColon, C_INT, 3);
			
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					//AfxMessageBox(_T("In"));				
				
					//Check for comments
					bool lnComment = WSPCheckLineComment( posIdType, posIdType + 4);
					if( lnComment )
					{
						m_bFlagEditVariable = false;
						return;
					}
					bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posIdType );
					if( blkComment )
					{
						m_bFlagEditVariable = false;
						return;
					}
					
					CString sVariableName = WSPGetText(posIdType + 4, posSemiColon);
					if( sVariableName == _T("OVERLOAD") )
					{
						//AfxMessageBox(sVariableName);
						return;
					}
					
					if( sVariableName != _T("EMPTY") )
					{
						sVariableName.TrimRight();
						sVariableName.TrimLeft();
						//AfxMessageBox(sFunctionName);
						r = WSPDeleteNodeTree1(sVariableName);
					
					}
					
				}

			}
		}

	}

}












						
void CAIPIEditorView::WSPHandleFunctionEditLongKeyWord( long pos)
{
	
	if( m_iModificationType == BEFOREDELETE )
	{
		long relPos = 0;
		bool bFlag = false;
		int l = 108;
		int o = 111;
		int n = 110;
		int g = 103;
		
		long posIdType = WSPDetectKeyWord4(pos-1, l, o, n, g);
		if ( posIdType != NOT_FOUND )
		{
			//AfxMessageBox(_T("delete detectado"));
			LPSTR szCloseParenthesis = ")";
			long posCloseParenthesis = WSPSearchToken( posIdType, m_DocumentLength, szCloseParenthesis);

				/*
				CString str;
				str.Format(_T("pos Id Type Type... %d"), posIdType);
				AfxMessageBox(str);
				str.Format(_T("Pos Close Par...%d  " ), posCloseParenthesis);
				AfxMessageBox(str);
				*/
	

			int r = WSPParseFunction( posIdType - 1, posCloseParenthesis);
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				//AfxMessageBox(_T("delete"));
				WSPDeleteFunction( pos, true);
			}
			
		}
		else
		{
			posIdType = WSPDetectKeyWord4(pos, l, o, n, g);
			if ( posIdType != NOT_FOUND )
			{
				//AfxMessageBox(_T("delete detectado"));
				LPSTR szCloseParenthesis = ")";
				long posCloseParenthesis = WSPSearchToken( posIdType, m_DocumentLength, szCloseParenthesis);
				int r = WSPParseFunction( posIdType - 1, posCloseParenthesis);
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					WSPDeleteFunction( pos, true);
				}
				
			}
			else
			{
				//AfxMessageBox(_T("Else"));		
				CScintillaCtrl& rCtrl = GetCtrl();
				int symbol = rCtrl.GetCharAt(pos);
				CString str;
				//str.Format(_T("Symbol...%d  " ), symbol);
				//AfxMessageBox(str);
				if( symbol != l && symbol != o && symbol != n && symbol != g  )
				{
					//AfxMessageBox(_T("Hola1"));
	
					relPos = pos;
					bFlag = true;
				}
				else
				{
				
					symbol = rCtrl.GetCharAt(pos -1);
					if( symbol != l && symbol != o && symbol != n && symbol != g )
					{
						//AfxMessageBox(_T("Hola2"));
						relPos = pos -1;
						bFlag = true;		
					}
				}
			
				if( bFlag )
				{
					int l = 108;
					int o = 111;
					int n = 110;
					int g = 103;
		
					posIdType = WSPDetectKeyWordEdit4( relPos, l, o, n, g);
					if( posIdType != NOT_FOUND )
					{
						//AfxMessageBox(_T("In to....."));
						//m_bFlagWriteRule = false;
						LPSTR szOpenParenthesis = "(";
						LPSTR szCloseParenthesis = ")";
					

						long posCloseParenthesis = WSPSearchToken(posIdType, m_DocumentLength, szCloseParenthesis);
						int r = WSPParseFunctionEdit( posIdType, posCloseParenthesis, C_LONG, 4);
						if( r != AIPI_ERROR && r != NOT_FOUND )
						{
							//AfxMessageBox(_T("In"));				
							//Check for comments
							bool lnComment = WSPCheckLineComment( posIdType, posIdType + 5);
							if( lnComment )
							{
								m_bFlagEditFunction = false;
								return;
							}
							bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posIdType );
							if( blkComment )
							{
								m_bFlagEditFunction = false;
								return;
							}


							long posOpenParenthesis = WSPSearchToken(posIdType, posCloseParenthesis, szOpenParenthesis); 
							CString sFunctionName = WSPGetText(posIdType + 5, posOpenParenthesis);
							if( sFunctionName == _T("OVERLOAD") )
							{
								//AfxMessageBox(sFunctionName);
								return;
							}

							
							if( sFunctionName != _T("EMPTY") )
							{
								
								CString sParameter = WSPFormatParameters( posOpenParenthesis, posCloseParenthesis );
								if( sParameter != _T("COMMENT_ERROR") )
								{
									sFunctionName.TrimRight();
									sFunctionName.TrimLeft();
									CString sFunctionParameter = _T("(") + sParameter + _T(")");
									//CString sFullRuleName = m_sRuleName + sRuleParameter; 
									//AfxMessageBox(m_sTokenName);
									//r = WSPAddNodeTree1(sFunctionName, sFunctionParameter, 4);
									r = WSPAddNodeTypeTree1(sFunctionName, sFunctionParameter, 6, AIPI_FUNCTION);
						
									//CWorkspaceTabView tab;
									//tab.printWSPTree1();
								}
							}
						}
			
						
					}
				}
			}
		}
	}

	if( m_iModificationType == INSERTTEXT )
	{
		int l = 108;
		int o = 111;
		int n = 110;
		int g = 103;
		
		long posIdType = WSPDetectKeyWord4(pos, l, o, n, g);
		if ( posIdType != NOT_FOUND )
		{
			//AfxMessageBox(_T("insert detectado"));
			//CString str;
			//str.Format(_T("Write Rule Flag... %d"), m_bFlagWriteRule);
			//AfxMessageBox(str);
			LPSTR szCloseParenthesis = ")";
			long posCloseParenthesis = WSPSearchToken(posIdType, m_DocumentLength, szCloseParenthesis);
			int r = WSPParseFunction( posIdType - 1, posCloseParenthesis);
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				WSPAddFunction( pos, true);
			}
			
		}
		else
		{
			posIdType = WSPDetectKeyWordEdit4( pos, l, o, n, g);
			if( posIdType != NOT_FOUND )
			{
				//m_bFlagWriteRule = false;
				//AfxMessageBox(_T("In to the detected edit"));
				LPSTR szOpenParenthesis = "(";
				LPSTR szCloseParenthesis = ")";
								
				long posCloseParenthesis = WSPSearchToken(posIdType, m_DocumentLength, szCloseParenthesis);
				int r = WSPParseFunctionEdit( posIdType, posCloseParenthesis, C_LONG, 4);
			
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					//AfxMessageBox(_T("In"));				
				
					//Check for comments
					bool lnComment = WSPCheckLineComment( posIdType, posIdType + 5);
					if( lnComment )
					{
						m_bFlagEditFunction = false;
						return;
					}
					bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posIdType );
					if( blkComment )
					{
						m_bFlagEditFunction = false;
						return;
					}
					
					long posOpenParenthesis = WSPSearchToken(posIdType, posCloseParenthesis, szOpenParenthesis);
					CString sFunctionName = WSPGetText(posIdType + 5, posOpenParenthesis);
					if( sFunctionName == _T("OVERLOAD") )
					{
						//AfxMessageBox(sFunctionName);
						return;
					}
					
					if( sFunctionName != _T("EMPTY") )
					{
						sFunctionName.TrimRight();
						sFunctionName.TrimLeft();
						//AfxMessageBox(sFunctionName);
						r = WSPDeleteNodeTree1(sFunctionName);
					
					}
					
				}

			}
		}

	}

}




void CAIPIEditorView::WSPHandleVariableEditLongKeyWord( long pos)
{
	
	if( m_iModificationType == BEFOREDELETE )
	{
		long relPos = 0;
		bool bFlag = false;
		int l = 108;
		int o = 111;
		int n = 110;
		int g = 103;
		
		long posIdType = WSPDetectKeyWord4(pos-1, l, o, n, g);
		if ( posIdType != NOT_FOUND )
		{
			//AfxMessageBox(_T("delete detectado"));
			LPSTR szSemiColon = ";";
			long posSemiColon = WSPSearchToken( posIdType, m_DocumentLength, szSemiColon);
			
				/*
				CString str;
				str.Format(_T("pos Id Type Type... %d"), posIdType);
				AfxMessageBox(str);
				str.Format(_T("Pos SemiColon...%d  " ), posSemiColon);
				AfxMessageBox(str);
				*/
			
			int r = WSPParseVariable( posIdType - 1, posSemiColon);
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				//AfxMessageBox(_T("Delete"));
				WSPDeleteVariable( pos, true);
			}
			
		}
		else
		{
			posIdType = WSPDetectKeyWord4(pos, l, o, n, g);
			if ( posIdType != NOT_FOUND )
			{
				//AfxMessageBox(_T("delete detectado"));
				LPSTR szSemiColon = ";";
				long posSemiColon = WSPSearchToken( posIdType, m_DocumentLength, szSemiColon);
				int r = WSPParseVariable( posIdType - 1, posSemiColon);
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					WSPDeleteVariable( pos, true );
				}
				
			}
			else
			{
						
				CScintillaCtrl& rCtrl = GetCtrl();
				int symbol = rCtrl.GetCharAt(pos);
				CString str;
				//str.Format(_T("Symbol...%d  " ), symbol);
				//AfxMessageBox(str);
				if( symbol != l && symbol != o && symbol != n && symbol != g  )
				{
					//AfxMessageBox(_T("Hola1"));
	
					relPos = pos;
					bFlag = true;
				}
				else
				{
				
					symbol = rCtrl.GetCharAt(pos -1);
					if( symbol != l && symbol != o && symbol != n && symbol != g )
					{
						//AfxMessageBox(_T("Hola2"));
						relPos = pos -1;
						bFlag = true;		
					}
				}
			
				if( bFlag )
				{
					int l = 108;
					int o = 111;
					int n = 110;
					int g = 103;
		
					posIdType = WSPDetectKeyWordEdit4( relPos, l, o, n, g);
					if( posIdType != NOT_FOUND )
					{
						//AfxMessageBox(_T("In to....."));
						//m_bFlagWriteRule = false;
						LPSTR szSemiColon = ";";
						
						long posSemiColon = WSPSearchToken(posIdType, m_DocumentLength, szSemiColon);
						int r = WSPParseVariableEdit( posIdType, posSemiColon, C_LONG, 4);
						if( r != AIPI_ERROR && r != NOT_FOUND )
						{
							//AfxMessageBox(_T("In"));				
							//Check for comments
							bool lnComment = WSPCheckLineComment( posIdType, posIdType + 5);
							if( lnComment )
							{
								m_bFlagEditVariable = false;
								return;
							}
							bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posIdType );
							if( blkComment )
							{
								m_bFlagEditVariable = false;
								return;
							}


							CString sVariableName = WSPGetText(posIdType + 5, posSemiColon);
							if( sVariableName == _T("OVERLOAD") )
							{
								//AfxMessageBox(sVariableName);
								return;
							}
							
							if( sVariableName != _T("EMPTY") )
							{
								sVariableName.TrimRight();
								sVariableName.TrimLeft();
								CString sVariableParameter = _T("");
								//CString sFullRuleName = m_sRuleName + sRuleParameter; 
								//AfxMessageBox(m_sTokenName);
								//r = WSPAddNodeTree1(sVariableName, sVariableParameter, 6);
								r = WSPAddNodeTypeTree1(sVariableName, sVariableParameter, 8, AIPI_VARIABLE);
						
								//CWorkspaceTabView tab;
								//tab.printWSPTree1();
								
							}
						}
			
						
					}
				}
			}
		}
	}

	if( m_iModificationType == INSERTTEXT )
	{
		int l = 108;
		int o = 111;
		int n = 110;
		int g = 103;
		
		long posIdType = WSPDetectKeyWord4(pos, l, o, n, g);
		if ( posIdType != NOT_FOUND )
		{
			//AfxMessageBox(_T("insert detectado"));
			//CString str;
			//str.Format(_T("Write Rule Flag... %d"), m_bFlagWriteRule);
			//AfxMessageBox(str);
			LPSTR szSemiColon = ";";
			long posSemiColon = WSPSearchToken(posIdType, m_DocumentLength, szSemiColon);
			int r = WSPParseVariable( posIdType - 1, posSemiColon);
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				WSPAddVariable( pos, true);
			}
			
		}
		else
		{
			posIdType = WSPDetectKeyWordEdit4( pos, l, o, n, g);
			if( posIdType != NOT_FOUND )
			{
				//m_bFlagWriteRule = false;
				//AfxMessageBox(_T("In to the detected edit"));
				LPSTR szSemiColon = ";";
								
				long posSemiColon = WSPSearchToken(posIdType, m_DocumentLength, szSemiColon);
				int r = WSPParseVariableEdit( posIdType, posSemiColon, C_LONG, 4);
			
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					//AfxMessageBox(_T("In"));				
				
					//Check for comments
					bool lnComment = WSPCheckLineComment( posIdType, posIdType + 5);
					if( lnComment )
					{
						m_bFlagEditVariable = false;
						return;
					}
					bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posIdType );
					if( blkComment )
					{
						m_bFlagEditVariable = false;
						return;
					}
					
					CString sVariableName = WSPGetText(posIdType + 5, posSemiColon);
					if( sVariableName == _T("OVERLOAD") )
					{
						//AfxMessageBox(sVariableName);
						return;
					}
					
					
					if( sVariableName != _T("EMPTY") )
					{
						sVariableName.TrimRight();
						sVariableName.TrimLeft();
						//AfxMessageBox(sVariableName);

						r = WSPDeleteNodeTree1(sVariableName);
					
					}
					
				}

			}
		}

	}

}










void CAIPIEditorView::WSPHandleFunctionEditFloatKeyWord( long pos)
{
	
	if( m_iModificationType == BEFOREDELETE )
	{
		long relPos = 0;
		bool bFlag = false;
		int f = 102;
		int l = 108;
		int o = 111;
		int a = 97;
		int t = 116;
		
		long posIdType = WSPDetectKeyWord5(pos-1, f, l, o, a, t);
		if ( posIdType != NOT_FOUND )
		{
			//AfxMessageBox(_T("delete detectado"));
			LPSTR szCloseParenthesis = ")";
			long posCloseParenthesis = WSPSearchToken( posIdType, m_DocumentLength, szCloseParenthesis);
			int r = WSPParseFunction( posIdType - 1, posCloseParenthesis);
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				WSPDeleteFunction( pos, true);
			}
			
		}
		else
		{
			posIdType = WSPDetectKeyWord5(pos, f, l, o, a, t);
			if ( posIdType != NOT_FOUND )
			{
				//AfxMessageBox(_T("delete detectado"));
				LPSTR szCloseParenthesis = ")";
				long posCloseParenthesis = WSPSearchToken( posIdType, m_DocumentLength, szCloseParenthesis);
				int r = WSPParseFunction( posIdType - 1, posCloseParenthesis);
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					WSPDeleteFunction( pos, true);
				}
				
			}
			else
			{
						
				CScintillaCtrl& rCtrl = GetCtrl();
				int symbol = rCtrl.GetCharAt(pos);
				CString str;
				//str.Format(_T("Symbol...%d  " ), symbol);
				//AfxMessageBox(str);
				if( symbol != f && symbol != l && symbol != o && symbol != a && symbol != t  )
				{
					//AfxMessageBox(_T("Hola1"));
	
					relPos = pos;
					bFlag = true;
				}
				else
				{
				
					symbol = rCtrl.GetCharAt(pos -1);
					if( symbol != f && symbol != l && symbol != o && symbol != a && symbol != t )
					{
						//AfxMessageBox(_T("Hola2"));
						relPos = pos -1;
						bFlag = true;		
					}
				}
			
				if( bFlag )
				{
					int f = 102;
					int l = 108;
					int o = 111;
					int a = 97;
					int t = 116;
		
		
					posIdType = WSPDetectKeyWordEdit5( relPos, f, l, o, a, t);
					if( posIdType != NOT_FOUND )
					{
						//AfxMessageBox(_T("In to....."));
						//m_bFlagWriteRule = false;
						LPSTR szOpenParenthesis = "(";
						LPSTR szCloseParenthesis = ")";
					

						long posCloseParenthesis = WSPSearchToken(posIdType, m_DocumentLength, szCloseParenthesis);
						int r = WSPParseFunctionEdit( posIdType, posCloseParenthesis, C_FLOAT, 5);
						if( r != AIPI_ERROR && r != NOT_FOUND )
						{
							//AfxMessageBox(_T("In"));				
							//Check for comments
							bool lnComment = WSPCheckLineComment( posIdType, posIdType + 6);
							if( lnComment )
							{
								m_bFlagEditFunction = false;
								return;
							}
							bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posIdType );
							if( blkComment )
							{
								m_bFlagEditFunction = false;
								return;
							}


							long posOpenParenthesis = WSPSearchToken(posIdType, posCloseParenthesis, szOpenParenthesis); 
							CString sFunctionName = WSPGetText(posIdType + 6, posOpenParenthesis);
							if( sFunctionName == _T("OVERLOAD") )
							{
								//AfxMessageBox(sFunctionName);
								return;
							}
					
							
							if( sFunctionName != _T("EMPTY") )
							{
								
								CString sParameter = WSPFormatParameters( posOpenParenthesis, posCloseParenthesis );
								if( sParameter != _T("COMMENT_ERROR") )
								{
									sFunctionName.TrimRight();
									sFunctionName.TrimLeft();

									CString sFunctionParameter = _T("(") + sParameter + _T(")");
									//CString sFullRuleName = m_sRuleName + sRuleParameter; 
									//AfxMessageBox(m_sTokenName);
									//r = WSPAddNodeTree1(sFunctionName, sFunctionParameter, 4);
									r = WSPAddNodeTypeTree1(sFunctionName, sFunctionParameter, 6, AIPI_FUNCTION);
									//CWorkspaceTabView tab;
									//tab.printWSPTree1();
								}
							}
						}
			
						
					}
				}
			}
		}
	}

	if( m_iModificationType == INSERTTEXT )
	{
		int f = 102;
		int l = 108;
		int o = 111;
		int a = 97;
		int t = 116;
		
		long posIdType = WSPDetectKeyWord5(pos, f, l, o, a, t);
		if ( posIdType != NOT_FOUND )
		{
			//AfxMessageBox(_T("insert detectado"));
			//CString str;
			//str.Format(_T("Write Rule Flag... %d"), m_bFlagWriteRule);
			//AfxMessageBox(str);
			LPSTR szCloseParenthesis = ")";
			long posCloseParenthesis = WSPSearchToken(posIdType, m_DocumentLength, szCloseParenthesis);
			int r = WSPParseFunction( posIdType - 1, posCloseParenthesis);
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				WSPAddFunction( pos, true);
			}
			
		}
		else
		{
			posIdType = WSPDetectKeyWordEdit5( pos, f, l, o, a, t);
			if( posIdType != NOT_FOUND )
			{
				//m_bFlagWriteRule = false;
				//AfxMessageBox(_T("In to the detected edit"));
				LPSTR szOpenParenthesis = "(";
				LPSTR szCloseParenthesis = ")";
								
				long posCloseParenthesis = WSPSearchToken(posIdType, m_DocumentLength, szCloseParenthesis);
				int r = WSPParseFunctionEdit( posIdType, posCloseParenthesis, C_FLOAT, 5);
			
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					//AfxMessageBox(_T("In"));				
				
					//Check for comments
					bool lnComment = WSPCheckLineComment( posIdType, posIdType + 6);
					if( lnComment )
					{
						m_bFlagEditFunction = false;
						return;
					}
					bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posIdType );
					if( blkComment )
					{
						m_bFlagEditFunction = false;
						return;
					}
					
					long posOpenParenthesis = WSPSearchToken(posIdType, posCloseParenthesis, szOpenParenthesis);
					CString sFunctionName = WSPGetText(posIdType + 6, posOpenParenthesis);
					if( sFunctionName == _T("OVERLOAD") )
					{
						//AfxMessageBox(sFunctionName);
						return;
					}
					
					
					if( sFunctionName != _T("EMPTY") )
					{
						sFunctionName.TrimRight();
						sFunctionName.TrimLeft();
						//AfxMessageBox(sFunctionName);
						r = WSPDeleteNodeTree1(sFunctionName);
					
					}
					
				}

			}
		}

	}

}



void CAIPIEditorView::WSPHandleVariableEditFloatKeyWord( long pos)
{
	
	if( m_iModificationType == BEFOREDELETE )
	{
		long relPos = 0;
		bool bFlag = false;
		int f = 102;
		int l = 108;
		int o = 111;
		int a = 97;
		int t = 116;
		
		long posIdType = WSPDetectKeyWord5(pos-1, f, l, o, a, t);
		if ( posIdType != NOT_FOUND )
		{
			//AfxMessageBox(_T("delete detectado"));
			LPSTR szSemiColon = ";";
			long posSemiColon = WSPSearchToken( posIdType, m_DocumentLength, szSemiColon);
			int r = WSPParseVariable( posIdType - 1, posSemiColon);
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				WSPDeleteVariable( pos, true);
			}
			
		}
		else
		{
			posIdType = WSPDetectKeyWord5(pos, f, l, o, a, t);
			if ( posIdType != NOT_FOUND )
			{
				//AfxMessageBox(_T("delete detectado"));
				LPSTR szSemiColon = ";";
				long posSemiColon = WSPSearchToken( posIdType, m_DocumentLength, szSemiColon);
				int r = WSPParseVariable( posIdType - 1, posSemiColon);
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					WSPDeleteVariable( pos, true);
				}
				
			}
			else
			{
						
				CScintillaCtrl& rCtrl = GetCtrl();
				int symbol = rCtrl.GetCharAt(pos);
				CString str;
				//str.Format(_T("Symbol...%d  " ), symbol);
				//AfxMessageBox(str);
				if( symbol != f && symbol != l && symbol != o && symbol != a && symbol != t  )
				{
					//AfxMessageBox(_T("Hola1"));
	
					relPos = pos;
					bFlag = true;
				}
				else
				{
				
					symbol = rCtrl.GetCharAt(pos -1);
					if( symbol != f && symbol != l && symbol != o && symbol != a && symbol != t )
					{
						//AfxMessageBox(_T("Hola2"));
						relPos = pos -1;
						bFlag = true;		
					}
				}
			
				if( bFlag )
				{
					int f = 102;
					int l = 108;
					int o = 111;
					int a = 97;
					int t = 116;
		
		
					posIdType = WSPDetectKeyWordEdit5( relPos, f, l, o, a, t);
					if( posIdType != NOT_FOUND )
					{
						//AfxMessageBox(_T("In to....."));
						//m_bFlagWriteRule = false;
						LPSTR szSemiColon = ";";
					
						long posSemiColon = WSPSearchToken(posIdType, m_DocumentLength, szSemiColon);
						int r = WSPParseVariableEdit( posIdType, posSemiColon, C_FLOAT, 5);
						if( r != AIPI_ERROR && r != NOT_FOUND )
						{
							//AfxMessageBox(_T("In"));				
							//Check for comments
							bool lnComment = WSPCheckLineComment( posIdType, posIdType + 6);
							if( lnComment )
							{
								m_bFlagEditVariable = false;
								return;
							}
							bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posIdType );
							if( blkComment )
							{
								m_bFlagEditVariable = false;
								return;
							}


							CString sVariableName = WSPGetText(posIdType + 6, posSemiColon);
							if( sVariableName == _T("OVERLOAD") )
							{
								//AfxMessageBox(sVariableName);
								return;
							}
							
							if( sVariableName != _T("EMPTY") )
							{
								sVariableName.TrimRight();
								sVariableName.TrimLeft();
								CString sVariableParameter = _T("");
								//CString sFullRuleName = m_sRuleName + sRuleParameter; 
								//AfxMessageBox(m_sTokenName);
								//r = WSPAddNodeTree1(sVariableName, sVariableParameter, 6);
								r = WSPAddNodeTypeTree1(sVariableName, sVariableParameter, 8, AIPI_VARIABLE);
								//CWorkspaceTabView tab;
								//tab.printWSPTree1();
								
							}
						}
			
						
					}
				}
			}
		}
	}

	if( m_iModificationType == INSERTTEXT )
	{
		int f = 102;
		int l = 108;
		int o = 111;
		int a = 97;
		int t = 116;
		
		long posIdType = WSPDetectKeyWord5(pos, f, l, o, a, t);
		if ( posIdType != NOT_FOUND )
		{
			//AfxMessageBox(_T("insert detectado"));
			//CString str;
			//str.Format(_T("Write Rule Flag... %d"), m_bFlagWriteRule);
			//AfxMessageBox(str);
			LPSTR szSemiColon = ";";
			long posSemiColon = WSPSearchToken(posIdType, m_DocumentLength, szSemiColon);
			int r = WSPParseVariable( posIdType - 1, posSemiColon);
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				WSPAddVariable( pos, true );
			}
			
		}
		else
		{
			posIdType = WSPDetectKeyWordEdit5( pos, f, l, o, a, t);
			if( posIdType != NOT_FOUND )
			{
				//m_bFlagWriteRule = false;
				//AfxMessageBox(_T("In to the detected edit"));
				LPSTR szSemiColon = ";";
								
				long posSemiColon = WSPSearchToken(posIdType, m_DocumentLength, szSemiColon);
				int r = WSPParseVariableEdit( posIdType, posSemiColon, C_FLOAT, 5);
			
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					//AfxMessageBox(_T("In"));				
				
					//Check for comments
					bool lnComment = WSPCheckLineComment( posIdType, posIdType + 6);
					if( lnComment )
					{
						m_bFlagEditVariable = false;
						return;
					}
					bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posIdType );
					if( blkComment )
					{
						m_bFlagEditVariable = false;
						return;
					}
					
					CString sVariableName = WSPGetText(posIdType + 6, posSemiColon);
					if( sVariableName == _T("OVERLOAD") )
					{
						//AfxMessageBox(sVariableName);
						return;
					}
					
					if( sVariableName != _T("EMPTY") )
					{
						sVariableName.TrimRight();
						sVariableName.TrimLeft();
						//AfxMessageBox(sVariableName);

						r = WSPDeleteNodeTree1(sVariableName);
					
					}
					
				}

			}
		}

	}

}









void CAIPIEditorView::WSPHandleFunctionEditShortKeyWord( long pos)
{
	
	if( m_iModificationType == BEFOREDELETE )
	{
		long relPos = 0;
		bool bFlag = false;
		int s = 115;
		int h = 104;
		int o = 111;
		int r = 114;
		int t = 116;
		
		long posIdType = WSPDetectKeyWord5(pos-1, s, h, o, r, t);
		if ( posIdType != NOT_FOUND )
		{
			//AfxMessageBox(_T("delete detectado"));
			LPSTR szCloseParenthesis = ")";
			long posCloseParenthesis = WSPSearchToken( posIdType, m_DocumentLength, szCloseParenthesis);
			int r = WSPParseFunction( posIdType - 1, posCloseParenthesis);
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				WSPDeleteFunction( pos, true);
			}
			
		}
		else
		{
			posIdType = WSPDetectKeyWord5(pos, s, h, o, r, t);
			if ( posIdType != NOT_FOUND )
			{
				//AfxMessageBox(_T("delete detectado"));
				LPSTR szCloseParenthesis = ")";
				long posCloseParenthesis = WSPSearchToken( posIdType, m_DocumentLength, szCloseParenthesis);
				int r = WSPParseFunction( posIdType - 1, posCloseParenthesis);
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					WSPDeleteFunction( pos, true);
				}
				
			}
			else
			{
						
				CScintillaCtrl& rCtrl = GetCtrl();
				int symbol = rCtrl.GetCharAt(pos);
				CString str;
				//str.Format(_T("Symbol...%d  " ), symbol);
				//AfxMessageBox(str);
				if( symbol != s && symbol != h && symbol != o && symbol != r && symbol != t  )
				{
					//AfxMessageBox(_T("Hola1"));
	
					relPos = pos;
					bFlag = true;
				}
				else
				{
				
					symbol = rCtrl.GetCharAt(pos -1);
					if( symbol != s && symbol != h && symbol != o && symbol != r && symbol != t )
					{
						//AfxMessageBox(_T("Hola2"));
						relPos = pos -1;
						bFlag = true;		
					}
				}
			
				if( bFlag )
				{
					int s = 115;
					int h = 104;
					int o = 111;
					int r = 114;
					int t = 116;
		
		
					posIdType = WSPDetectKeyWordEdit5( relPos, s, h, o, r, t);
					if( posIdType != NOT_FOUND )
					{
						//AfxMessageBox(_T("In to....."));
						//m_bFlagWriteRule = false;
						LPSTR szOpenParenthesis = "(";
						LPSTR szCloseParenthesis = ")";
					

						long posCloseParenthesis = WSPSearchToken(posIdType, m_DocumentLength, szCloseParenthesis);
						int r = WSPParseFunctionEdit( posIdType, posCloseParenthesis, C_SHORT, 5);
						if( r != AIPI_ERROR && r != NOT_FOUND )
						{
							//AfxMessageBox(_T("In"));				
							//Check for comments
							bool lnComment = WSPCheckLineComment( posIdType, posIdType + 6);
							if( lnComment )
							{
								m_bFlagEditFunction = false;
								return;
							}
							bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posIdType );
							if( blkComment )
							{
								m_bFlagEditFunction = false;
								return;
							}


							long posOpenParenthesis = WSPSearchToken(posIdType, posCloseParenthesis, szOpenParenthesis); 
							CString sFunctionName = WSPGetText(posIdType + 6, posOpenParenthesis);
							if( sFunctionName == _T("OVERLOAD") )
							{
								//AfxMessageBox(sFunctionName);
								return;
							}
							
							if( sFunctionName != _T("EMPTY") )
							{
								
								CString sParameter = WSPFormatParameters( posOpenParenthesis, posCloseParenthesis );
								if( sParameter != _T("COMMENT_ERROR") )
								{
									sFunctionName.TrimRight();
									sFunctionName.TrimLeft();

									CString sFunctionParameter = _T("(") + sParameter + _T(")");
									//CString sFullRuleName = m_sRuleName + sRuleParameter; 
									//AfxMessageBox(m_sTokenName);
									//r = WSPAddNodeTree1(sFunctionName, sFunctionParameter, 4);
									r = WSPAddNodeTypeTree1(sFunctionName, sFunctionParameter, 6, AIPI_FUNCTION);
									//CWorkspaceTabView tab;
									//tab.printWSPTree1();
								}
							}
						}
			
						
					}
				}
			}
		}
	}

	if( m_iModificationType == INSERTTEXT )
	{
		int s = 115;
		int h = 104;
		int o = 111;
		int r = 114;
		int t = 116;
		
		long posIdType = WSPDetectKeyWord5(pos, s, h, o, r, t);
		if ( posIdType != NOT_FOUND )
		{
			//AfxMessageBox(_T("insert detectado"));
			//CString str;
			//str.Format(_T("Write Rule Flag... %d"), m_bFlagWriteRule);
			//AfxMessageBox(str);
			LPSTR szCloseParenthesis = ")";
			long posCloseParenthesis = WSPSearchToken(posIdType, m_DocumentLength, szCloseParenthesis);
			int r = WSPParseFunction( posIdType - 1, posCloseParenthesis);
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				WSPAddFunction( pos, true);
			}
		
		}
		else
		{
			posIdType = WSPDetectKeyWordEdit5( pos, s, h, o, r, t);
			if( posIdType != NOT_FOUND )
			{
				//m_bFlagWriteRule = false;
				//AfxMessageBox(_T("In to the detected edit"));
				LPSTR szOpenParenthesis = "(";
				LPSTR szCloseParenthesis = ")";
								
				long posCloseParenthesis = WSPSearchToken(posIdType, m_DocumentLength, szCloseParenthesis);
				int r = WSPParseFunctionEdit( posIdType, posCloseParenthesis, C_SHORT, 5);
			
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					//AfxMessageBox(_T("In"));				
				
					//Check for comments
					bool lnComment = WSPCheckLineComment( posIdType, posIdType + 6);
					if( lnComment )
					{
						m_bFlagEditFunction = false;
						return;
					}
					bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posIdType );
					if( blkComment )
					{
						m_bFlagEditFunction = false;
						return;
					}
					
					long posOpenParenthesis = WSPSearchToken(posIdType, posCloseParenthesis, szOpenParenthesis);
					CString sFunctionName = WSPGetText(posIdType + 6, posOpenParenthesis);
					if( sFunctionName == _T("OVERLOAD") )
					{
						//AfxMessageBox(sFunctionName);
						return;
					}
					
					if( sFunctionName != _T("EMPTY") )
					{
						sFunctionName.TrimRight();
						sFunctionName.TrimLeft();
						//AfxMessageBox(sFunctionName);

						r = WSPDeleteNodeTree1(sFunctionName);
					
					}
					
				}

			}
		}

	}

}




void CAIPIEditorView::WSPHandleVariableEditShortKeyWord( long pos)
{
	
	if( m_iModificationType == BEFOREDELETE )
	{
		long relPos = 0;
		bool bFlag = false;
		int s = 115;
		int h = 104;
		int o = 111;
		int r = 114;
		int t = 116;
		
		long posIdType = WSPDetectKeyWord5(pos-1, s, h, o, r, t);
		if ( posIdType != NOT_FOUND )
		{
			//AfxMessageBox(_T("delete detectado"));
			LPSTR szSemiColon = ";";
			long posSemiColon = WSPSearchToken( posIdType, m_DocumentLength, szSemiColon);
			int r = WSPParseVariable( posIdType - 1, posSemiColon);
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				WSPDeleteVariable( pos, true);
			}
			
		}
		else
		{
			posIdType = WSPDetectKeyWord5(pos, s, h, o, r, t);
			if ( posIdType != NOT_FOUND )
			{
				//AfxMessageBox(_T("delete detectado"));
				LPSTR szSemiColon = ";";
				long posSemiColon = WSPSearchToken( posIdType, m_DocumentLength, szSemiColon);
				int r = WSPParseVariable( posIdType - 1, posSemiColon);
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					WSPDeleteVariable( pos, true);
				}
				
			}
			else
			{
						
				CScintillaCtrl& rCtrl = GetCtrl();
				int symbol = rCtrl.GetCharAt(pos);
				CString str;
				//str.Format(_T("Symbol...%d  " ), symbol);
				//AfxMessageBox(str);
				if( symbol != s && symbol != h && symbol != o && symbol != r && symbol != t  )
				{
					//AfxMessageBox(_T("Hola1"));
	
					relPos = pos;
					bFlag = true;
				}
				else
				{
				
					symbol = rCtrl.GetCharAt(pos -1);
					if( symbol != s && symbol != h && symbol != o && symbol != r && symbol != t )
					{
						//AfxMessageBox(_T("Hola2"));
						relPos = pos -1;
						bFlag = true;		
					}
				}
			
				if( bFlag )
				{
					int s = 115;
					int h = 104;
					int o = 111;
					int r = 114;
					int t = 116;
		
		
					posIdType = WSPDetectKeyWordEdit5( relPos, s, h, o, r, t);
					if( posIdType != NOT_FOUND )
					{
						//AfxMessageBox(_T("In to....."));
						//m_bFlagWriteRule = false;
						LPSTR szSemiColon = ";";
					
						long posSemiColon = WSPSearchToken(posIdType, m_DocumentLength, szSemiColon);
						int r = WSPParseVariableEdit( posIdType, posSemiColon, C_SHORT, 5);
						if( r != AIPI_ERROR && r != NOT_FOUND )
						{
							//AfxMessageBox(_T("In"));				
							//Check for comments
							bool lnComment = WSPCheckLineComment( posIdType, posIdType + 6);
							if( lnComment )
							{
								m_bFlagEditVariable = false;
								return;
							}
							bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posIdType );
							if( blkComment )
							{
								m_bFlagEditVariable = false;
								return;
							}


							CString sVariableName = WSPGetText(posIdType + 6, posSemiColon);
							if( sVariableName == _T("OVERLOAD") )
							{
								//AfxMessageBox(sVariableName);
								return;
							}
							
							if( sVariableName != _T("EMPTY") )
							{
								sVariableName.TrimRight();
								sVariableName.TrimLeft();

								CString sVariableParameter = _T("");
								//CString sFullRuleName = m_sRuleName + sRuleParameter; 
								//AfxMessageBox(m_sTokenName);
								//r = WSPAddNodeTree1(sVariableName, sVariableParameter, 6);
								r = WSPAddNodeTypeTree1(sVariableName, sVariableParameter, 8, AIPI_VARIABLE);
								
							}
						}
			
						
					}
				}
			}
		}
	}

	if( m_iModificationType == INSERTTEXT )
	{
		int s = 115;
		int h = 104;
		int o = 111;
		int r = 114;
		int t = 116;
		
		long posIdType = WSPDetectKeyWord5(pos, s, h, o, r, t);
		if ( posIdType != NOT_FOUND )
		{
			//AfxMessageBox(_T("insert detectado"));
			//CString str;
			//str.Format(_T("Write Rule Flag... %d"), m_bFlagWriteRule);
			//AfxMessageBox(str);
			LPSTR szSemiColon = ";";
			long posSemiColon = WSPSearchToken(posIdType, m_DocumentLength, szSemiColon);
			int r = WSPParseVariable( posIdType - 1, posSemiColon);
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				WSPAddVariable( pos, true);
			}
			
		}
		else
		{
			posIdType = WSPDetectKeyWordEdit5( pos, s, h, o, r, t);
			if( posIdType != NOT_FOUND )
			{
				//m_bFlagWriteRule = false;
				//AfxMessageBox(_T("In to the detected edit"));
				
				LPSTR szSemiColon = ";";
								
				long posSemiColon = WSPSearchToken(posIdType, m_DocumentLength, szSemiColon);
				int r = WSPParseVariableEdit( posIdType, posSemiColon, C_SHORT, 5);
			
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					//AfxMessageBox(_T("In"));				
				
					//Check for comments
					bool lnComment = WSPCheckLineComment( posIdType, posIdType + 6);
					if( lnComment )
					{
						m_bFlagEditVariable = false;
						return;
					}
					bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posIdType );
					if( blkComment )
					{
						m_bFlagEditVariable = false;
						return;
					}
					
					CString sVariableName = WSPGetText(posIdType + 6, posSemiColon);
					if( sVariableName == _T("OVERLOAD") )
					{
						//AfxMessageBox(sVariableName);
						return;
					}
					
					
					if( sVariableName != _T("EMPTY") )
					{
						sVariableName.TrimRight();
						sVariableName.TrimLeft();
						//AfxMessageBox(sFunctionName);
						r = WSPDeleteNodeTree1(sVariableName);
					
					}
					
				}

			}
		}

	}

}





















void CAIPIEditorView::WSPHandleFunctionEditCharKeyWord( long pos)
{
	
	if( m_iModificationType == BEFOREDELETE )
	{
		long relPos = 0;
		bool bFlag = false;
		int c = 99;
		int h = 104;
		int a = 97;
		int r = 114;
		
		long posIdType = WSPDetectKeyWord4(pos-1, c, h, a, r);
		if ( posIdType != NOT_FOUND )
		{
			//AfxMessageBox(_T("delete detectado"));
			LPSTR szCloseParenthesis = ")";
			long posCloseParenthesis = WSPSearchToken( posIdType, m_DocumentLength, szCloseParenthesis);
			int r = WSPParseFunction( posIdType - 1, posCloseParenthesis);
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				WSPDeleteFunction( pos, true);
			}
			
		}
		else
		{
			posIdType = WSPDetectKeyWord4(pos, c, h, a, r);
			if ( posIdType != NOT_FOUND )
			{
				//AfxMessageBox(_T("delete detectado"));
				LPSTR szCloseParenthesis = ")";
				long posCloseParenthesis = WSPSearchToken( posIdType, m_DocumentLength, szCloseParenthesis);
				int r = WSPParseFunction( posIdType - 1, posCloseParenthesis);
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					WSPDeleteFunction( pos, true);
				}
				
			}
			else
			{
						
				CScintillaCtrl& rCtrl = GetCtrl();
				int symbol = rCtrl.GetCharAt(pos);
				CString str;
				//str.Format(_T("Symbol...%d  " ), symbol);
				//AfxMessageBox(str);
				if( symbol != c && symbol != h && symbol != a && symbol != r  )
				{
					//AfxMessageBox(_T("Hola1"));
	
					relPos = pos;
					bFlag = true;
				}
				else
				{
				
					symbol = rCtrl.GetCharAt(pos -1);
					if( symbol != c && symbol != h && symbol != a && symbol != r )
					{
						//AfxMessageBox(_T("Hola2"));
						relPos = pos -1;
						bFlag = true;		
					}
				}
			
				if( bFlag )
				{
					int c = 99;
					int h = 104;
					int a = 97;
					int r = 114;
		
		
					posIdType = WSPDetectKeyWordEdit4( relPos, c, h, a, r);
					if( posIdType != NOT_FOUND )
					{
						//AfxMessageBox(_T("In to....."));
						//m_bFlagWriteRule = false;
						LPSTR szOpenParenthesis = "(";
						LPSTR szCloseParenthesis = ")";
					

						long posCloseParenthesis = WSPSearchToken(posIdType, m_DocumentLength, szCloseParenthesis);
						int r = WSPParseFunctionEdit( posIdType, posCloseParenthesis, C_CHAR, 4);
						if( r != AIPI_ERROR && r != NOT_FOUND )
						{
							//AfxMessageBox(_T("In"));				
							//Check for comments
							bool lnComment = WSPCheckLineComment( posIdType, posIdType + 5);
							if( lnComment )
							{
								m_bFlagEditFunction = false;
								return;
							}
							bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posIdType );
							if( blkComment )
							{
								m_bFlagEditFunction = false;
								return;
							}


							long posOpenParenthesis = WSPSearchToken(posIdType, posCloseParenthesis, szOpenParenthesis); 
							CString sFunctionName = WSPGetText(posIdType + 5, posOpenParenthesis);
							if( sFunctionName == _T("OVERLOAD") )
							{
								//AfxMessageBox(sFunctionName);
								return;
							}
							
							
							if( sFunctionName != _T("EMPTY") )
							{
								CString sParameter = WSPFormatParameters( posOpenParenthesis, posCloseParenthesis );
								if( sParameter != _T("COMMENT_ERROR") )
								{
									sFunctionName.TrimRight();
									sFunctionName.TrimLeft();
									CString sFunctionParameter = _T("(") + sParameter + _T(")");
									//CString sFullRuleName = m_sRuleName + sRuleParameter; 
									//AfxMessageBox(m_sTokenName);
									//r = WSPAddNodeTree1(sFunctionName, sFunctionParameter, 4);
									r = WSPAddNodeTypeTree1(sFunctionName, sFunctionParameter, 6, AIPI_FUNCTION);
									//CWorkspaceTabView tab;
									//tab.printWSPTree1();
								}
							}
						}
			
						
					}
				}
			}
		}
	}

	if( m_iModificationType == INSERTTEXT )
	{
		int c = 99;
		int h = 104;
		int a = 97;
		int r = 114;
		
		
		long posIdType = WSPDetectKeyWord4(pos, c, h, a, r);
		if ( posIdType != NOT_FOUND )
		{
			//AfxMessageBox(_T("insert detectado"));
			//CString str;
			//str.Format(_T("Write Rule Flag... %d"), m_bFlagWriteRule);
			//AfxMessageBox(str);
			LPSTR szCloseParenthesis = ")";
			long posCloseParenthesis = WSPSearchToken(posIdType, m_DocumentLength, szCloseParenthesis);
			int r = WSPParseFunction( posIdType - 1, posCloseParenthesis);
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				WSPAddFunction( pos, true);
			}
			
		}
		else
		{
			posIdType = WSPDetectKeyWordEdit4( pos, c, h, a, r);
			if( posIdType != NOT_FOUND )
			{
				//m_bFlagWriteRule = false;
				//AfxMessageBox(_T("In to the detected edit"));
				LPSTR szOpenParenthesis = "(";
				LPSTR szCloseParenthesis = ")";
								
				long posCloseParenthesis = WSPSearchToken(posIdType, m_DocumentLength, szCloseParenthesis);
				int r = WSPParseFunctionEdit( posIdType, posCloseParenthesis, C_CHAR, 4);
			
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					//AfxMessageBox(_T("In"));				
				
					//Check for comments
					bool lnComment = WSPCheckLineComment( posIdType, posIdType + 5);
					if( lnComment )
					{
						m_bFlagEditFunction = false;
						return;
					}
					bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posIdType );
					if( blkComment )
					{
						m_bFlagEditFunction = false;
						return;
					}
					
					long posOpenParenthesis = WSPSearchToken(posIdType, posCloseParenthesis, szOpenParenthesis);
					CString sFunctionName = WSPGetText(posIdType + 5, posOpenParenthesis);
					
					if( sFunctionName == _T("OVERLOAD") )
					{
						//AfxMessageBox(sFunctionName);
						return;
					}
					
					
					if( sFunctionName != _T("EMPTY") )
					{
						sFunctionName.TrimRight();
						sFunctionName.TrimLeft();
						//AfxMessageBox(sFunctionName);
						r = WSPDeleteNodeTree1(sFunctionName);
					
					}
					
				}

			}
		}

	}

}




void CAIPIEditorView::WSPHandleVariableEditCharKeyWord( long pos)
{
	
	if( m_iModificationType == BEFOREDELETE )
	{
		long relPos = 0;
		bool bFlag = false;
		int c = 99;
		int h = 104;
		int a = 97;
		int r = 114;
		
		long posIdType = WSPDetectKeyWord4(pos-1, c, h, a, r);
		if ( posIdType != NOT_FOUND )
		{
			//AfxMessageBox(_T("delete detectado"));
			LPSTR szSemiColon = ";";
			long posSemiColon = WSPSearchToken( posIdType, m_DocumentLength, szSemiColon);
			int r = WSPParseVariable( posIdType - 1, posSemiColon);
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				WSPDeleteVariable( pos, true);
			}
			
		}
		else
		{
			posIdType = WSPDetectKeyWord4(pos, c, h, a, r);
			if ( posIdType != NOT_FOUND )
			{
				//AfxMessageBox(_T("delete detectado"));
				LPSTR szSemiColon = ";";
				long posSemiColon = WSPSearchToken( posIdType, m_DocumentLength, szSemiColon);
				int r = WSPParseVariable( posIdType - 1, posSemiColon);
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					WSPDeleteVariable( pos, true);
				}
				
			}
			else
			{
						
				CScintillaCtrl& rCtrl = GetCtrl();
				int symbol = rCtrl.GetCharAt(pos);
				CString str;
				//str.Format(_T("Symbol...%d  " ), symbol);
				//AfxMessageBox(str);
				if( symbol != c && symbol != h && symbol != a && symbol != r  )
				{
					//AfxMessageBox(_T("Hola1"));
	
					relPos = pos;
					bFlag = true;
				}
				else
				{
				
					symbol = rCtrl.GetCharAt(pos -1);
					if( symbol != c && symbol != h && symbol != a && symbol != r )
					{
						//AfxMessageBox(_T("Hola2"));
						relPos = pos -1;
						bFlag = true;		
					}
				}
			
				if( bFlag )
				{
					int c = 99;
					int h = 104;
					int a = 97;
					int r = 114;
		
		
					posIdType = WSPDetectKeyWordEdit4( relPos, c, h, a, r);
					if( posIdType != NOT_FOUND )
					{
						//AfxMessageBox(_T("In to....."));
						//m_bFlagWriteRule = false;
						LPSTR szSemiColon = ";";
					

						long posSemiColon = WSPSearchToken(posIdType, m_DocumentLength, szSemiColon);
						int r = WSPParseVariableEdit( posIdType, posSemiColon, C_CHAR, 4);
						if( r != AIPI_ERROR && r != NOT_FOUND )
						{
							//AfxMessageBox(_T("In"));				
							//Check for comments
							bool lnComment = WSPCheckLineComment( posIdType, posIdType + 5);
							if( lnComment )
							{
								m_bFlagEditVariable = false;
								return;
							}
							bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posIdType );
							if( blkComment )
							{
								m_bFlagEditVariable = false;
								return;
							}


							CString sVariableName = WSPGetText(posIdType + 5, posSemiColon);
							if( sVariableName == _T("OVERLOAD") )
							{
								//AfxMessageBox(sVariableName);
								return;
							}
							
							
							if( sVariableName != _T("EMPTY") )
							{
								sVariableName.TrimRight();
								sVariableName.TrimLeft();
								CString sVariableParameter = _T("");
								//CString sFullRuleName = m_sRuleName + sRuleParameter; 
								//AfxMessageBox(m_sTokenName);
								//r = WSPAddNodeTree1(sVariableName, sVariableParameter, 6);
								r = WSPAddNodeTypeTree1(sVariableName, sVariableParameter, 8, AIPI_VARIABLE);
								//CWorkspaceTabView tab;
								//tab.printWSPTree1();
							}
						}
			
						
					}
				}
			}
		}
	}

	if( m_iModificationType == INSERTTEXT )
	{
		int c = 99;
		int h = 104;
		int a = 97;
		int r = 114;
		
		
		long posIdType = WSPDetectKeyWord4(pos, c, h, a, r);
		if ( posIdType != NOT_FOUND )
		{
			//AfxMessageBox(_T("insert detectado"));
			//CString str;
			//str.Format(_T("Write Rule Flag... %d"), m_bFlagWriteRule);
			//AfxMessageBox(str);
			LPSTR szSemiColon = ";";
			long posSemiColon = WSPSearchToken(posIdType, m_DocumentLength, szSemiColon);
			int r = WSPParseVariable( posIdType - 1, posSemiColon);
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				WSPAddVariable( pos, true);
			}
			
		}
		else
		{
			posIdType = WSPDetectKeyWordEdit4( pos, c, h, a, r);
			if( posIdType != NOT_FOUND )
			{
				//m_bFlagWriteRule = false;
				//AfxMessageBox(_T("In to the detected edit"));
				LPSTR szSemiColon = ";";
												
				long posSemiColon = WSPSearchToken(posIdType, m_DocumentLength, szSemiColon);
				int r = WSPParseVariableEdit( posIdType, posSemiColon, C_CHAR, 4);
			
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					//AfxMessageBox(_T("In"));				
				
					//Check for comments
					bool lnComment = WSPCheckLineComment( posIdType, posIdType + 5);
					if( lnComment )
					{
						m_bFlagEditVariable = false;
						return;
					}
					bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posIdType );
					if( blkComment )
					{
						m_bFlagEditVariable = false;
						return;
					}
					
					CString sVariableName = WSPGetText(posIdType + 5, posSemiColon);
					if( sVariableName == _T("OVERLOAD") )
					{
						//AfxMessageBox(sVariableName);
						return;
					}
					
					
					if( sVariableName != _T("EMPTY") )
					{
						sVariableName.TrimRight();
						sVariableName.TrimLeft();
						//AfxMessageBox(sVariableName);
						r = WSPDeleteNodeTree1(sVariableName);
					
					}
					
				}

			}
		}

	}

}








void CAIPIEditorView::WSPHandleFunctionEditVoidKeyWord( long pos)
{
	
	if( m_iModificationType == BEFOREDELETE )
	{
		long relPos = 0;
		bool bFlag = false;
		int v = 118;
		int o = 111;
		int i = 105;
		int d = 100;
		
		long posIdType = WSPDetectKeyWord4(pos-1, v, o, i, d);
		if ( posIdType != NOT_FOUND )
		{
			//AfxMessageBox(_T("delete detectado"));
			LPSTR szCloseParenthesis = ")";
			long posCloseParenthesis = WSPSearchToken( posIdType, m_DocumentLength, szCloseParenthesis);
			int r = WSPParseFunction( posIdType - 1, posCloseParenthesis);
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				WSPDeleteFunction( pos, true);
			}
			
		}
		else
		{
			posIdType = WSPDetectKeyWord4(pos, v, o, i, d);
			if ( posIdType != NOT_FOUND )
			{
				//AfxMessageBox(_T("delete detectado"));
				LPSTR szCloseParenthesis = ")";
				long posCloseParenthesis = WSPSearchToken( posIdType, m_DocumentLength, szCloseParenthesis);
				int r = WSPParseFunction( posIdType - 1, posCloseParenthesis);
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					WSPDeleteFunction( pos, true);
				}
				
			}
			else
			{
						
				CScintillaCtrl& rCtrl = GetCtrl();
				int symbol = rCtrl.GetCharAt(pos);
				CString str;
				//str.Format(_T("Symbol...%d  " ), symbol);
				//AfxMessageBox(str);
				if( symbol != v && symbol != o && symbol != i && symbol != d  )
				{
					//AfxMessageBox(_T("Hola1"));
	
					relPos = pos;
					bFlag = true;
				}
				else
				{
				
					symbol = rCtrl.GetCharAt(pos -1);
					if( symbol != v && symbol != o && symbol != i && symbol != d )
					{
						//AfxMessageBox(_T("Hola2"));
						relPos = pos -1;
						bFlag = true;		
					}
				}
			
				if( bFlag )
				{
					int v = 118;
					int o = 111;
					int i = 105;
					int d = 100;
		
		
					posIdType = WSPDetectKeyWordEdit4( relPos, v, o, i, d);
					if( posIdType != NOT_FOUND )
					{
						//AfxMessageBox(_T("In to....."));
						//m_bFlagWriteRule = false;
						LPSTR szOpenParenthesis = "(";
						LPSTR szCloseParenthesis = ")";
					

						long posCloseParenthesis = WSPSearchToken(posIdType, m_DocumentLength, szCloseParenthesis);
						int r = WSPParseFunctionEdit( posIdType, posCloseParenthesis, C_VOID, 4);
						if( r != AIPI_ERROR && r != NOT_FOUND )
						{
							//AfxMessageBox(_T("In"));				
							//Check for comments
							bool lnComment = WSPCheckLineComment( posIdType, posIdType + 5);
							if( lnComment )
							{
								m_bFlagEditFunction = false;
								return;
							}
							bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posIdType );
							if( blkComment )
							{
								m_bFlagEditFunction = false;
								return;
							}


							long posOpenParenthesis = WSPSearchToken(posIdType, posCloseParenthesis, szOpenParenthesis); 
							CString sFunctionName = WSPGetText(posIdType + 5, posOpenParenthesis);
							if( sFunctionName == _T("OVERLOAD") )
							{
								//AfxMessageBox(sFunctionName);
								return;
							}
							if( sFunctionName != _T("EMPTY") )
							{
								CString sParameter = WSPFormatParameters( posOpenParenthesis, posCloseParenthesis );
								if( sParameter != _T("COMMENT_ERROR") )
								{
									sFunctionName.TrimRight();
									sFunctionName.TrimLeft();
									CString sFunctionParameter = _T("(") + sParameter + _T(")");
									//CString sFullRuleName = m_sRuleName + sRuleParameter; 
									//AfxMessageBox(m_sTokenName);
									//r = WSPAddNodeTree1(sFunctionName, sFunctionParameter, 4);
									r = WSPAddNodeTypeTree1(sFunctionName, sFunctionParameter, 6, AIPI_FUNCTION);
						
									//CWorkspaceTabView tab;
									//tab.printWSPTree1();
								}
							}
						}
			
						
					}
				}
			}
		}
	}

	if( m_iModificationType == INSERTTEXT )
	{
		int v = 118;
		int o = 111;
		int i = 105;
		int d = 100;
		
		
		long posIdType = WSPDetectKeyWord4(pos, v, o, i, d);
		if ( posIdType != NOT_FOUND )
		{
			//AfxMessageBox(_T("insert detectado"));
			//CString str;
			//str.Format(_T("Write Rule Flag... %d"), m_bFlagWriteRule);
			//AfxMessageBox(str);
			LPSTR szCloseParenthesis = ")";
			long posCloseParenthesis = WSPSearchToken(posIdType, m_DocumentLength, szCloseParenthesis);
			int r = WSPParseFunction( posIdType - 1, posCloseParenthesis);
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				WSPAddFunction( pos, true);
			}
			
		}
		else
		{
			posIdType = WSPDetectKeyWordEdit4( pos, v, o, i, d);
			if( posIdType != NOT_FOUND )
			{
				//m_bFlagWriteRule = false;
				//AfxMessageBox(_T("In to the detected edit"));
				LPSTR szOpenParenthesis = "(";
				LPSTR szCloseParenthesis = ")";
								
				long posCloseParenthesis = WSPSearchToken(posIdType, m_DocumentLength, szCloseParenthesis);
				int r = WSPParseFunctionEdit( posIdType, posCloseParenthesis, C_VOID, 4);
			
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					//AfxMessageBox(_T("In"));				
				
					//Check for comments
					bool lnComment = WSPCheckLineComment( posIdType, posIdType + 5);
					if( lnComment )
					{
						m_bFlagEditFunction = false;
						return;
					}
					bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posIdType );
					if( blkComment )
					{
						m_bFlagEditFunction = false;
						return;
					}
					
					long posOpenParenthesis = WSPSearchToken(posIdType, posCloseParenthesis, szOpenParenthesis);
					CString sFunctionName = WSPGetText(posIdType + 5, posOpenParenthesis);
					if( sFunctionName == _T("OVERLOAD") )
					{
						//AfxMessageBox(sFunctionName);
						return;
					}
					
					if( sFunctionName != _T("EMPTY") )
					{
						sFunctionName.TrimRight();
						sFunctionName.TrimLeft();
						//AfxMessageBox(sFunctionName);
						r = WSPDeleteNodeTree1(sFunctionName);
					
					}
					
				}

			}
		}

	}

}



void CAIPIEditorView::WSPHandleFunctionEditDoubleKeyWord( long pos)
{
	
	if( m_iModificationType == BEFOREDELETE )
	{
		long relPos = 0;
		bool bFlag = false;
		int d = 100;
		int o = 111;
		int u = 117;
		int b = 98;
		int l = 108;
		int e = 101;
		
		long posIdType = WSPDetectKeyWord6(pos-1, d, o, u, b, l, e);
		if ( posIdType != NOT_FOUND )
		{
			//AfxMessageBox(_T("delete detectado"));
			LPSTR szCloseParenthesis = ")";
			long posCloseParenthesis = WSPSearchToken( posIdType, m_DocumentLength, szCloseParenthesis);
			int r = WSPParseFunction( posIdType - 1, posCloseParenthesis);
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				WSPDeleteFunction( pos, true);
			}
			
		}
		else
		{
			//AfxMessageBox(_T("Else"));
			posIdType = WSPDetectKeyWord6(pos, d, o, u, b, l, e);
			if ( posIdType != NOT_FOUND )
			{
				//AfxMessageBox(_T("delete detectado"));
				LPSTR szCloseParenthesis = ")";
				long posCloseParenthesis = WSPSearchToken( posIdType, m_DocumentLength, szCloseParenthesis);
				int r = WSPParseFunction( posIdType - 1, posCloseParenthesis);
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					WSPDeleteFunction( pos, true);
				}
				
			}
			else
			{
						
				CScintillaCtrl& rCtrl = GetCtrl();
				int symbol = rCtrl.GetCharAt(pos);
				CString str;
				//str.Format(_T("Symbol...%d  " ), symbol);
				//AfxMessageBox(str);
				if( symbol != d && symbol != o && symbol != u && symbol != b && symbol != l &&  symbol != e)
				{
					//AfxMessageBox(_T("Hola1"));
	
					relPos = pos;
					bFlag = true;
				}
				else
				{
				
					symbol = rCtrl.GetCharAt(pos -1);
					if( symbol != d && symbol != o && symbol != u && symbol != b && symbol != l &&  symbol != e )
					{
						//AfxMessageBox(_T("Hola2"));
						relPos = pos -1;
						bFlag = true;		
					}
				}
			
				if( bFlag )
				{
					int d = 100;
					int o = 111;
					int u = 117;
					int b = 98;
					int l = 108;
					int e = 101;
		
		
		
					posIdType = WSPDetectKeyWordEdit6( relPos, d, o, u, b, l, e);
					if( posIdType != NOT_FOUND )
					{
						//AfxMessageBox(_T("In to....."));
						//m_bFlagWriteRule = false;
						LPSTR szOpenParenthesis = "(";
						LPSTR szCloseParenthesis = ")";
					

						long posCloseParenthesis = WSPSearchToken(posIdType, m_DocumentLength, szCloseParenthesis);
						int r = WSPParseFunctionEdit( posIdType, posCloseParenthesis, C_DOUBLE, 6);
						if( r != AIPI_ERROR && r != NOT_FOUND )
						{
							//AfxMessageBox(_T("In"));				
							//Check for comments
							bool lnComment = WSPCheckLineComment( posIdType, posIdType + 7);
							if( lnComment )
							{
								m_bFlagEditFunction = false;
								return;
							}
							bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posIdType );
							if( blkComment )
							{
								m_bFlagEditFunction = false;
								return;
							}


							long posOpenParenthesis = WSPSearchToken(posIdType, posCloseParenthesis, szOpenParenthesis); 
							CString sFunctionName = WSPGetText(posIdType + 7, posOpenParenthesis);
							if( sFunctionName == _T("OVERLOAD") )
							{
								//AfxMessageBox(sFunctionName);
								return;
							}
							
							if( sFunctionName != _T("EMPTY") )
							{
								CString sParameter = WSPFormatParameters( posOpenParenthesis, posCloseParenthesis );
								if( sParameter != _T("COMMENT_ERROR") )
								{
									sFunctionName.TrimRight();
									sFunctionName.TrimLeft();

									CString sFunctionParameter = _T("(") + sParameter + _T(")");
									//CString sFullRuleName = m_sRuleName + sRuleParameter; 
									//AfxMessageBox(m_sTokenName);
									//r = WSPAddNodeTree1(sFunctionName, sFunctionParameter, 4);
									r = WSPAddNodeTypeTree1(sFunctionName, sFunctionParameter, 4, AIPI_FUNCTION);
									//CWorkspaceTabView tab;
									//tab.printWSPTree1();
								}
							}
						}
			
						
					}
				}
			}
		}
	}

	if( m_iModificationType == INSERTTEXT )
	{
		int d = 100;
		int o = 111;
		int u = 117;
		int b = 98;
		int l = 108;
		int e = 101;
		
		
		long posIdType = WSPDetectKeyWord6(pos, d, o, u, b, l, e);
		if ( posIdType != NOT_FOUND )
		{
			//AfxMessageBox(_T("insert detectado"));
			//CString str;
			//str.Format(_T("Write Rule Flag... %d"), m_bFlagWriteRule);
			//AfxMessageBox(str);
			LPSTR szCloseParenthesis = ")";
			long posCloseParenthesis = WSPSearchToken(posIdType, m_DocumentLength, szCloseParenthesis);
			int r = WSPParseFunction( posIdType - 1, posCloseParenthesis);
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				WSPAddFunction( pos, true);
			}
			
		}
		else
		{
			posIdType = WSPDetectKeyWordEdit6( pos, d, o, u, b, l, e);
			if( posIdType != NOT_FOUND )
			{
				//m_bFlagWriteRule = false;
				//AfxMessageBox(_T("In to the detected edit"));
				LPSTR szOpenParenthesis = "(";
				LPSTR szCloseParenthesis = ")";
								
				long posCloseParenthesis = WSPSearchToken(posIdType, m_DocumentLength, szCloseParenthesis);
				int r = WSPParseFunctionEdit( posIdType, posCloseParenthesis, C_DOUBLE, 6);
			
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					//AfxMessageBox(_T("In"));				
				
					//Check for comments
					bool lnComment = WSPCheckLineComment( posIdType, posIdType + 7);
					if( lnComment )
					{
						m_bFlagEditFunction = false;
						return;
					}
					bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posIdType );
					if( blkComment )
					{
						m_bFlagEditFunction = false;
						return;
					}
					
					long posOpenParenthesis = WSPSearchToken(posIdType, posCloseParenthesis, szOpenParenthesis);
					CString sFunctionName = WSPGetText(posIdType + 7, posOpenParenthesis);
					if( sFunctionName == _T("OVERLOAD") )
					{
						//AfxMessageBox(sFunctionName);
						return;
					}
							
					
					if( sFunctionName != _T("EMPTY") )
					{
						sFunctionName.TrimRight();
						sFunctionName.TrimLeft();
						//AfxMessageBox(sFunctionName);
						r = WSPDeleteNodeTree1(sFunctionName);
					
					}
					
				}

			}
		}

	}

}




void CAIPIEditorView::WSPHandleVariableEditDoubleKeyWord( long pos)
{
	
	if( m_iModificationType == BEFOREDELETE )
	{
		long relPos = 0;
		bool bFlag = false;
		int d = 100;
		int o = 111;
		int u = 117;
		int b = 98;
		int l = 108;
		int e = 101;
		
		long posIdType = WSPDetectKeyWord6(pos-1, d, o, u, b, l, e);
		if ( posIdType != NOT_FOUND )
		{
			//AfxMessageBox(_T("delete detectado"));
			LPSTR szSemiColon = ";";
			long posSemiColon = WSPSearchToken( posIdType, m_DocumentLength, szSemiColon);
			int r = WSPParseVariable( posIdType - 1, posSemiColon);
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				WSPDeleteVariable( pos, true);
			}
			
		}
		else
		{
			//AfxMessageBox(_T("Else"));
			posIdType = WSPDetectKeyWord6(pos, d, o, u, b, l, e);
			if ( posIdType != NOT_FOUND )
			{
				//AfxMessageBox(_T("delete detectado"));
				LPSTR szSemiColon = ";";
				long posSemiColon = WSPSearchToken( posIdType, m_DocumentLength, szSemiColon);
				int r = WSPParseVariable( posIdType - 1, posSemiColon);
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					WSPDeleteVariable( pos, true);
				}
				
			}
			else
			{
						
				CScintillaCtrl& rCtrl = GetCtrl();
				int symbol = rCtrl.GetCharAt(pos);
				CString str;
				//str.Format(_T("Symbol...%d  " ), symbol);
				//AfxMessageBox(str);
				if( symbol != d && symbol != o && symbol != u && symbol != b && symbol != l &&  symbol != e)
				{
					//AfxMessageBox(_T("Hola1"));
	
					relPos = pos;
					bFlag = true;
				}
				else
				{
				
					symbol = rCtrl.GetCharAt(pos -1);
					if( symbol != d && symbol != o && symbol != u && symbol != b && symbol != l &&  symbol != e )
					{
						//AfxMessageBox(_T("Hola2"));
						relPos = pos -1;
						bFlag = true;		
					}
				}
			
				if( bFlag )
				{
					int d = 100;
					int o = 111;
					int u = 117;
					int b = 98;
					int l = 108;
					int e = 101;
		
		
		
					posIdType = WSPDetectKeyWordEdit6( relPos, d, o, u, b, l, e);
					if( posIdType != NOT_FOUND )
					{
						//AfxMessageBox(_T("In to....."));
						LPSTR szSemiColon = ";";
						
						long posSemiColon = WSPSearchToken(posIdType, m_DocumentLength, szSemiColon);
						int r = WSPParseVariableEdit( posIdType, posSemiColon, C_DOUBLE, 6);
						if( r != AIPI_ERROR && r != NOT_FOUND )
						{
							//AfxMessageBox(_T("In"));				
							//Check for comments
							bool lnComment = WSPCheckLineComment( posIdType, posIdType + 7);
							if( lnComment )
							{
								m_bFlagEditVariable = false;
								return;
							}
							bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posIdType );
							if( blkComment )
							{
								m_bFlagEditVariable = false;
								return;
							}

							CString sVariableName = WSPGetText(posIdType + 7, posSemiColon);
							if( sVariableName == _T("OVERLOAD") )
							{
								//AfxMessageBox(sVariableName);
								return;
							}
							
							
							if( sVariableName != _T("EMPTY") )
							{
								sVariableName.TrimRight();
								sVariableName.TrimLeft();

								CString sVariableParameter = _T("");
								//CString sFullRuleName = m_sRuleName + sRuleParameter; 
								//AfxMessageBox(m_sTokenName);
								//r = WSPAddNodeTree1(sVariableName, sVariableParameter, 6);
								r = WSPAddNodeTypeTree1(sVariableName, sVariableParameter, 8, AIPI_VARIABLE);
								//CWorkspaceTabView tab;
								//tab.printWSPTree1();
								
							}
						}
			
						
					}
				}
			}
		}
	}

	if( m_iModificationType == INSERTTEXT )
	{
		int d = 100;
		int o = 111;
		int u = 117;
		int b = 98;
		int l = 108;
		int e = 101;
		
		
		long posIdType = WSPDetectKeyWord6(pos, d, o, u, b, l, e);
		if ( posIdType != NOT_FOUND )
		{
			//AfxMessageBox(_T("insert detectado"));
			//CString str;
			//str.Format(_T("Write Rule Flag... %d"), m_bFlagWriteRule);
			//AfxMessageBox(str);
			LPSTR szSemiColon = ";";
			long posSemiColon = WSPSearchToken(posIdType, m_DocumentLength, szSemiColon);
			int r = WSPParseVariable( posIdType - 1, posSemiColon);
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				WSPAddVariable( pos, true);
			}
			
		}
		else
		{
			posIdType = WSPDetectKeyWordEdit6( pos, d, o, u, b, l, e);
			if( posIdType != NOT_FOUND )
			{
				//m_bFlagWriteRule = false;
				//AfxMessageBox(_T("In to the detected edit"));
				LPSTR szSemiColon = ";";
											
				long posSemiColon = WSPSearchToken(posIdType, m_DocumentLength, szSemiColon);
				int r = WSPParseVariableEdit( posIdType, posSemiColon, C_DOUBLE, 6);
			
				if( r != AIPI_ERROR && r != NOT_FOUND )
				{
					//AfxMessageBox(_T("In"));				
				
					//Check for comments
					bool lnComment = WSPCheckLineComment( posIdType, posIdType + 7);
					if( lnComment )
					{
						m_bFlagEditVariable = false;
						return;
					}
					bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posIdType );
					if( blkComment )
					{
						m_bFlagEditVariable = false;
						return;
					}
					
					CString sVariableName = WSPGetText(posIdType + 7, posSemiColon);
					if( sVariableName == _T("OVERLOAD") )
					{
						//AfxMessageBox(sVariableName);
						return;
					}
					
					if( sVariableName != _T("EMPTY") )
					{
						sVariableName.TrimRight();
						sVariableName.TrimLeft();
						//AfxMessageBox(sVariableName);

						r = WSPDeleteNodeTree1(sVariableName);
					
					}
					
				}

			}
		}

	}

}











void CAIPIEditorView::WSPEditRule(long pos)
{
	CScintillaCtrl& rCtrl = GetCtrl();
	
	LPSTR szKeyWord = "RULE";
	LPSTR szOpenParenthesis = "(";
	LPSTR szCloseParenthesis = ")";
	LPSTR szDobleQuotation = "\"";
	
	
	//LPSTR szOpenComment = "/*";
	//LPSTR szCloseComment = "*/";
	//LPSTR szLineComment = "//";

	/*
	CString sOldRuleName, sNewRuleName;
	CString sOldRuleParameter, sNewRuleParameter;
	CString sOldFullRuleName = _T("");
	CString sNewFullRuleName = _T("");
	CString sParameter;
	*/				
		
	CString str;
	//str.Format(_T("Pos  %d"), pos);
	//AfxMessageBox(str);
	//AfxMessageBox(_T("hola"));
	
	if( m_iModificationType == BEFOREDELETE || m_iModificationType == DELETETEXT )
	{
		WSPHandleRuleCloseParenthesis(pos);
	}

	WSPHandleEditRuleKeyWord( pos);
	WSPCommentRule( pos);
	


	long posRule = WSPSearchToken(pos, 0, szKeyWord);
	long posCloseParenthesis = WSPSearchToken(posRule, m_DocumentLength, szCloseParenthesis);
	
	//str.Format(_T("Write Rule Flag... %d"), m_bFlagWriteRule);
	//AfxMessageBox(str);
		
	if( posRule != NOT_FOUND && posCloseParenthesis != NOT_FOUND && m_bFlagWriteRule == false )
	{
		//WSPHandleEditRuleKeyWord( pos);
			
		/*
		str.Format(_T("Modification Type... %d"), m_iModificationType);
		AfxMessageBox(str);
		str.Format(_T("Pos Rule...%d  " ), posRule);
		AfxMessageBox(str);
		str.Format(_T("Pos Close Parenthesis...%d  " ), posCloseParenthesis);
		AfxMessageBox(str);
		*/
	 
		int r = WSPParseRule( posRule -1, posCloseParenthesis );
		//AfxMessageBox(_T("No ha Entrado"));

		
		if( r != AIPI_ERROR && r != NOT_FOUND )
		{			
			bool lnComment = WSPCheckLineComment( posRule, posRule + 4);
			if( lnComment )
			{
				m_bFlagEditRule = false;
				return;
			}
			bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posRule );
			if( blkComment )
			{
				m_bFlagEditRule = false;
				return;
			}
		
	
			
			//AfxMessageBox(_T("Entro0"));
			
				
			long posStartDobleQuotation = WSPSearchToken(posRule, posCloseParenthesis, szDobleQuotation);
			long posEndDobleQuotation = WSPSearchToken( posStartDobleQuotation + 1, posCloseParenthesis, szDobleQuotation);
			long posOpenParenthesis = WSPSearchToken(posEndDobleQuotation, posCloseParenthesis, szOpenParenthesis);
				
				
			//str.Format(_T("posStartDobleQuotation... %d"), posStartDobleQuotation);
			//AfxMessageBox(str);
			//str.Format(_T("posCloseParenthesis... %d"), posCloseParenthesis);
			//AfxMessageBox(str);
			//str.Format(_T("flag... %d"),m_bFlagWriteRule);
			//AfxMessageBox(str);
			

			if( pos >= posRule /*posStartDobleQuotation*/ && pos <= posCloseParenthesis && m_bFlagWriteRule == false )
			{
					
				//AfxMessageBox(_T("Entro1"));
				m_bFlagEditRule = true;
					
										
				if(m_bFlagEditRule != false )
				{
					//AfxMessageBox(_T("Get In"));
						
					CString sOldRuleName, sNewRuleName;
					CString sOldRuleParameter, sNewRuleParameter;
					CString sOldFullRuleName = _T("");
					CString sNewFullRuleName = _T("");
					CString sParameter;
							
					//Detects the SC_MOD_BEFOREINSERT and SC_MOD_BEFOREDELETE Modified notifications
					if( m_iModificationType == BEFOREINSERT || m_iModificationType == BEFOREDELETE )
					{
						//AfxMessageBox(_T("OLD"));
						sOldRuleName = WSPGetText(posStartDobleQuotation + 1, posEndDobleQuotation);
						if( sOldRuleName == _T("OVERLOAD" ))
						{
							return;
						}
						
						sOldRuleName = WSPFormatRuleNameOpt(sOldRuleName);
						sParameter = WSPFormatParameters(posOpenParenthesis, posCloseParenthesis);
						if( sParameter != _T("COMMENT_ERROR") )
						{
							//AfxMessageBox(sOldRuleName);
							sOldRuleParameter = _T("(") + sParameter + _T(")");
							//AfxMessageBox(sOldParameter);
							sOldFullRuleName = sOldRuleName + sOldRuleParameter;
							//AfxMessageBox(sOldFullRuleName);
							//LPTSTR lpszOldRuleName	= sOldRuleName.GetBuffer(TEXTLENGTH);
						}
						else
						{
							return;
						}
					}
					
					//Detects the SC_MOD_INSERTTEXT and SC_MOD_DELETETEXT Modified notifications
					if( m_iModificationType == INSERTTEXT || m_iModificationType == DELETETEXT )
					{	
						//AfxMessageBox(_T("NEW"));
						//AfxMessageBox(str);
															
						sNewRuleName = WSPGetText(posStartDobleQuotation + 1, posEndDobleQuotation);
						if( sNewRuleName == _T("OVERLOAD" ))
						{
							return;
						}
						sNewRuleName = WSPFormatRuleNameOpt(sNewRuleName);
						sParameter = WSPFormatParameters(posOpenParenthesis, posCloseParenthesis);
						if( sParameter != _T("COMMENT_ERROR") )
						{
							//AfxMessageBox(sNewRuleName);
							sNewRuleParameter = _T("(") + sParameter + _T(")");
							//AfxMessageBox(sNewParameter);
							sNewFullRuleName = sNewRuleName + sNewRuleParameter;
							//AfxMessageBox(sNewFullRuleName);
							//LPTSTR lpszNewRuleName	= sNewRuleName.GetBuffer(TEXTLENGTH);
						}
						else
						{
							return;
						}
					}
					
					//str.Format(_T("Modification Type... %d"), m_iModificationType);
					//AfxMessageBox(str);
					//AfxMessageBox(sOldRuleName);	
					//AfxMessageBox(sNewRuleName);
					//AfxMessageBox(m_sCurrentRuleName);
					
					//Check if the rule name already exist in the workspace
					CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
					
					CWorkspaceTree1 wsp1;
										
					HTREEITEM hChild = NULL;
					int f = wsp1.findNodeTree1Members(sOldRuleName);
					if( f != NOT_FOUND )
					{	
						//AfxMessageBox(_T("Found"));
						HTREEITEM hChild = wsp1.m_HItem;
						CString sFilePath = wsp1.m_FilePath;
						CString sFileName = wsp1.m_FileName;
						
						//str.Format(_T("Modification Type... %d"), m_iModificationType);
						//AfxMessageBox(str);
						
							/*						
							AfxMessageBox(_T("Old"));
							AfxMessageBox(sOldFullRuleName);
							AfxMessageBox(_T("New"));
							AfxMessageBox(sNewFullRuleName);
							*/								
							

						//AfxMessageBox(_T("Parser In"));
						int r = WSPParseRule(posRule -1, posCloseParenthesis);
				
						if( r != AIPI_ERROR && r != NOT_FOUND )
						{
							//AfxMessageBox(_T("No hay Error parser"));
							//AfxMessageBox(sNewRuleName);
							if( sNewFullRuleName == _T(""))
							{
								//m_nRuleSyntaxError++;
								//TCHAR buffer[8];
								//CString sNoError =_T("");
								//sNoError =  _itot( m_nRuleSyntaxError, buffer, 10 );
								//sNewFullRuleName = _T("Rule Syntax Error:") + sNoError;
								//AfxMessageBox(sNewFullRuleName);
								//AfxMessageBox(_T("Error"));
								//str.Format(_T("pos... %d"), pos);
								//AfxMessageBox(str);
													
							}

								
							pMainFrame->m_wndWorkspaceTabView.EditTreeItem1(sNewFullRuleName, hChild);
							wsp1.eraseElement(sOldRuleName);
							wsp1.addElement(sNewRuleName, hChild, sFilePath, sFileName);
							//Update location
							CWorkspaceLocation loc;
							loc.eraseLocation(hChild);
							int line = rCtrl.LineFromPosition(posRule); 
							loc.addLocation(hChild,posRule, line+1, sNewRuleName, sFilePath, AIPI_RULE);
							//AfxMessageBox(sNewRuleName);
						}
						else
						{
							//AfxMessageBox(_T("Error en parser"));
							sNewRuleName = _T("");						
							WSPDeleteNodeTree1(sNewRuleName);
						}
							
					}
					else if ( sNewRuleName != _T("") )
					{
							
						//AfxMessageBox(_T("ELSE IF"));
						
						//str.Format(_T("Flg Write Rule error...%d  " ), m_bFlagWriteError);
						//AfxMessageBox(str);
						//str.Format(_T("Modification Type... %d"), m_iModificationType);
						//AfxMessageBox(str);
					
						if( m_bFlagWriteError )
						{
							WSPAddRule(pos, true);
							m_bFlagWriteError = false;
						}
					
					}
					else
					{
						//AfxMessageBox(_T("ANOTHER ELSE"));
						
					}
				}
			}
					
			m_bFlagEditRule = false;
			//m_bFlagWriteRule = false;
		
		
		}
		else
		{
			//AfxMessageBox(_T("ELSE"));
			//Parser error
			if( m_iModificationType == DELETETEXT || m_iModificationType == INSERTTEXT )
			{
				//AfxMessageBox(_T("Delete"));
				CString sRuleName = _T("");
				WSPDeleteNodeTree1(sRuleName);
				m_bFlagWriteError = true;
			}
		}
	}


}





void CAIPIEditorView::WSPEditJSFunction(long pos)
{
	CScintillaCtrl& rCtrl = GetCtrl();
	
	LPSTR szKeyWord = "function";
	LPSTR szOpenParenthesis = "(";
	LPSTR szCloseParenthesis = ")";
		
	
	//LPSTR szOpenComment = "/*";
	//LPSTR szCloseComment = "*/";
	//LPSTR szLineComment = "//";

	/*
	CString sOldRuleName, sNewRuleName;
	CString sOldRuleParameter, sNewRuleParameter;
	CString sOldFullRuleName = _T("");
	CString sNewFullRuleName = _T("");
	CString sParameter;
	*/				
		
	CString str;
	//str.Format(_T("Pos  %d"), pos);
	//AfxMessageBox(str);
	//AfxMessageBox(_T("hola"));
	
	if( m_iModificationType == BEFOREDELETE || m_iModificationType == DELETETEXT )
	{
		WSPHandleJSFunctionCloseParenthesis(pos);
	}

	WSPHandleEditJSFunctionKeyWord( pos);
	WSPCommentJSFunction( pos);
	


	long posFunction = WSPSearchToken(pos, 0, szKeyWord);
	long posCloseParenthesis = WSPSearchToken(posFunction, m_DocumentLength, szCloseParenthesis);
	
	//str.Format(_T("Write Rule Flag... %d"), m_bFlagWriteRule);
	//AfxMessageBox(str);
		
	if( posFunction != NOT_FOUND && posCloseParenthesis != NOT_FOUND && m_bFlagWriteJSFunction == false )
	{
		//WSPHandleEditRuleKeyWord( pos);
			
		/*
		str.Format(_T("Modification Type... %d"), m_iModificationType);
		AfxMessageBox(str);
		str.Format(_T("Pos Rule...%d  " ), posRule);
		AfxMessageBox(str);
		str.Format(_T("Pos Close Parenthesis...%d  " ), posCloseParenthesis);
		AfxMessageBox(str);
		*/
	 
		int r = WSPParseJSFunction( posFunction -1, posCloseParenthesis );
		//AfxMessageBox(_T("No ha Entrado"));

		
		if( r != AIPI_ERROR && r != NOT_FOUND )
		{			
			bool lnComment = WSPCheckLineComment( posFunction, posFunction + 8);
			if( lnComment )
			{
				m_bFlagEditFunction = false;
				return;
			}
			bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posFunction );
			if( blkComment )
			{
				m_bFlagEditFunction = false;
				return;
			}
		
	
			
			//AfxMessageBox(_T("Entro0"));
			long posOpenParenthesis = WSPSearchToken(posFunction, posCloseParenthesis, szOpenParenthesis);
				
				
			//str.Format(_T("posCloseParenthesis... %d"), posCloseParenthesis);
			//AfxMessageBox(str);
			//str.Format(_T("flag... %d"),m_bFlagWriteRule);
			//AfxMessageBox(str);
			

			if( pos >= posFunction /*posStartDobleQuotation*/ && pos <= posCloseParenthesis && m_bFlagWriteJSFunction == false )
			{
					
				//AfxMessageBox(_T("Entro1"));
				m_bFlagEditJSFunction = true;
					
										
				if(m_bFlagEditJSFunction != false )
				{
					//AfxMessageBox(_T("Get In"));
						
					CString sOldFunctionName, sNewFunctionName;
					CString sOldFunctionParameter, sNewFunctionParameter;
					CString sOldFullFunctionName = _T("");
					CString sNewFullFunctionName = _T("");
					CString sParameter;
							
					//Detects the SC_MOD_BEFOREINSERT and SC_MOD_BEFOREDELETE Modified notifications
					if( m_iModificationType == BEFOREINSERT || m_iModificationType == BEFOREDELETE )
					{
						//AfxMessageBox(_T("OLD"));
						sOldFunctionName = WSPGetText(posFunction + 8, posOpenParenthesis);
						if( sOldFunctionName == _T("OVERLOAD" ))
						{
							return;
						}
						sOldFunctionName.TrimRight();
						sOldFunctionName.TrimLeft();

						sParameter = WSPFormatParameters(posOpenParenthesis, posCloseParenthesis);
						if( sParameter != _T("COMMENT_ERROR") )
						{
							//AfxMessageBox(sOldFunctionName);
							sOldFunctionParameter = _T("(") + sParameter + _T(")");
							//AfxMessageBox(sOldParameter);
							sOldFullFunctionName = sOldFunctionName + sOldFunctionParameter;
							//AfxMessageBox(sOldFullRuleName);
							//LPTSTR lpszOldRuleName	= sOldRuleName.GetBuffer(TEXTLENGTH);
						}
						else
						{
							return;
						}
					}
					
					//Detects the SC_MOD_INSERTTEXT and SC_MOD_DELETETEXT Modified notifications
					if( m_iModificationType == INSERTTEXT || m_iModificationType == DELETETEXT )
					{	
						//AfxMessageBox(_T("NEW"));
						//AfxMessageBox(str);
															
						sNewFunctionName = WSPGetText(posFunction + 8, posOpenParenthesis);
						if( sNewFunctionName == _T("OVERLOAD" ))
						{
							return;
						}
						sNewFunctionName.TrimRight();
						sNewFunctionName.TrimLeft();

						sParameter = WSPFormatParameters(posOpenParenthesis, posCloseParenthesis);
						if( sParameter != _T("COMMENT_ERROR") )
						{
							//AfxMessageBox(sNewFunctionName);
							//sNewRuleParameter = WSPGetText(posOpenParenthesis, posCloseParenthesis +1);
							sNewFunctionParameter = _T("(") + sParameter + _T(")");
							//AfxMessageBox(sNewParameter);
							sNewFullFunctionName = sNewFunctionName + sNewFunctionParameter;
							//AfxMessageBox(sNewFullRuleName);
							//LPTSTR lpszNewRuleName	= sNewRuleName.GetBuffer(TEXTLENGTH);
						}
						else
						{
							return;
						}
					}
					
					//str.Format(_T("Modification Type... %d"), m_iModificationType);
					//AfxMessageBox(str);
					//AfxMessageBox(sOldRuleName);	
					//AfxMessageBox(sNewRuleName);
					//AfxMessageBox(m_sCurrentRuleName);
					
					//Check if the rule name already exist in the workspace
					CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
					CWorkspaceTree1 wsp;
					int f = wsp.findNodeTree1Members(sOldFunctionName);
					
					if( f != NOT_FOUND )
					{	
						//AfxMessageBox(_T("Found"));
						
						HTREEITEM hChild = wsp.m_HItem;
						CString sFilePath = wsp.m_FilePath;
						CString sFileName = wsp.m_FileName;
						
						//str.Format(_T("Modification Type... %d"), m_iModificationType);
						//AfxMessageBox(str);
						
							/*						
							AfxMessageBox(_T("Old"));
							AfxMessageBox(sOldFullRuleName);
							AfxMessageBox(_T("New"));
							AfxMessageBox(sNewFullRuleName);
							*/								
							

						//AfxMessageBox(_T("Parser In"));
						int r = WSPParseJSFunction(posFunction -1, posCloseParenthesis);
				
						if( r != AIPI_ERROR && r != NOT_FOUND )
						{
							//AfxMessageBox(_T("No hay Error parser"));
							//AfxMessageBox(sNewRuleName);
							if( sNewFullFunctionName == _T(""))
							{
								//m_nRuleSyntaxError++;
								//TCHAR buffer[8];
								//CString sNoError =_T("");
								//sNoError =  _itot( m_nRuleSyntaxError, buffer, 10 );
								//sNewFullRuleName = _T("Rule Syntax Error:") + sNoError;
								//AfxMessageBox(sNewFullRuleName);
								//AfxMessageBox(_T("Error"));
								//str.Format(_T("pos... %d"), pos);
								//AfxMessageBox(str);
													
							}

								
							pMainFrame->m_wndWorkspaceTabView.EditTreeItem1(sNewFullFunctionName, hChild);
							wsp.eraseElement(sOldFunctionName);
							wsp.addElement(sNewFunctionName, hChild, sFilePath, sFileName);

							//Update location
							CWorkspaceLocation loc;
							loc.eraseLocation(hChild);
							int line = rCtrl.LineFromPosition(posFunction); 
							loc.addLocation(hChild,posFunction, line+1, sNewFunctionName, sFilePath, AIPI_FUNCTION);
							
						}
						else
						{
							//AfxMessageBox(_T("Error en parser"));
							sNewFunctionName = _T("");						
							WSPDeleteNodeTree1(sNewFunctionName);
						}
							
					}
					else if ( sNewFunctionName != _T("") )
					{
							
						//AfxMessageBox(_T("ELSE IF"));
						
						//str.Format(_T("Flg Write Rule error...%d  " ), m_bFlagWriteError);
						//AfxMessageBox(str);
						//str.Format(_T("Modification Type... %d"), m_iModificationType);
						//AfxMessageBox(str);
					
						if( m_bFlagWriteError )
						{
							WSPAddJSFunction(pos, true);
							m_bFlagWriteError = false;
						}
					
					}
					else
					{
						//AfxMessageBox(_T("ANOTHER ELSE"));
						
					}
				}
			}
					
			m_bFlagEditJSFunction = false;
			//m_bFlagWriteRule = false;
		
		
		}
		else
		{
			//AfxMessageBox(_T("ELSE"));
			//Parser error
			if( m_iModificationType == DELETETEXT || m_iModificationType == INSERTTEXT )
			{
				//AfxMessageBox(_T("Delete"));
				CString sFunctionName = _T("");
				WSPDeleteNodeTree1(sFunctionName);
				m_bFlagWriteError = true;
			}
		}
	}


}


void CAIPIEditorView::WSPEditVBSFunction(long pos)
{
	CScintillaCtrl& rCtrl = GetCtrl();
	
	LPSTR szKeyWord = "Function";
	LPSTR szOpenParenthesis = "(";
	LPSTR szCloseParenthesis = ")";
		
	
	//LPSTR szOpenComment = "/*";
	//LPSTR szCloseComment = "*/";
	//LPSTR szLineComment = "//";

	/*
	CString sOldRuleName, sNewRuleName;
	CString sOldRuleParameter, sNewRuleParameter;
	CString sOldFullRuleName = _T("");
	CString sNewFullRuleName = _T("");
	CString sParameter;
	*/				
		
	CString str;
	//str.Format(_T("Pos  %d"), pos);
	//AfxMessageBox(str);
	//AfxMessageBox(_T("hola"));
	
	if( m_iModificationType == BEFOREDELETE || m_iModificationType == DELETETEXT )
	{
		WSPHandleVBSFunctionCloseParenthesis(pos);
	}

	WSPHandleEditVBSFunctionKeyWord( pos);
	WSPCommentVBSFunction( pos);
	


	long posFunction = WSPSearchToken(pos, 0, szKeyWord);
	long posCloseParenthesis = WSPSearchToken(posFunction, m_DocumentLength, szCloseParenthesis);
	
	//str.Format(_T("Write Rule Flag... %d"), m_bFlagWriteRule);
	//AfxMessageBox(str);
		
	if( posFunction != NOT_FOUND && posCloseParenthesis != NOT_FOUND && m_bFlagWriteJSFunction == false )
	{
		//WSPHandleEditRuleKeyWord( pos);
			
		/*
		str.Format(_T("Modification Type... %d"), m_iModificationType);
		AfxMessageBox(str);
		str.Format(_T("Pos Rule...%d  " ), posRule);
		AfxMessageBox(str);
		str.Format(_T("Pos Close Parenthesis...%d  " ), posCloseParenthesis);
		AfxMessageBox(str);
		*/
	 
		int r = WSPParseVBSFunction( posFunction -1, posCloseParenthesis );
		//AfxMessageBox(_T("No ha Entrado"));

		
		if( r != AIPI_ERROR && r != NOT_FOUND )
		{			
			bool lnComment = WSPCheckLineComment( posFunction, posFunction + 8);
			if( lnComment )
			{
				m_bFlagEditVBSFunction = false;
				return;
			}
			bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posFunction );
			if( blkComment )
			{
				m_bFlagEditVBSFunction = false;
				return;
			}
		
	
			
			//AfxMessageBox(_T("Entro0"));
			long posOpenParenthesis = WSPSearchToken(posFunction, posCloseParenthesis, szOpenParenthesis);
				
				
			//str.Format(_T("posCloseParenthesis... %d"), posCloseParenthesis);
			//AfxMessageBox(str);
			//str.Format(_T("flag... %d"),m_bFlagWriteRule);
			//AfxMessageBox(str);
			

			if( pos >= posFunction /*posStartDobleQuotation*/ && pos <= posCloseParenthesis && m_bFlagWriteJSFunction == false )
			{
					
				//AfxMessageBox(_T("Entro1"));
				m_bFlagEditVBSFunction = true;
					
										
				if(m_bFlagEditVBSFunction != false )
				{
					//AfxMessageBox(_T("Get In"));
						
					CString sOldFunctionName, sNewFunctionName;
					CString sOldFunctionParameter, sNewFunctionParameter;
					CString sOldFullFunctionName = _T("");
					CString sNewFullFunctionName = _T("");
					CString sParameter;
							
					//Detects the SC_MOD_BEFOREINSERT and SC_MOD_BEFOREDELETE Modified notifications
					if( m_iModificationType == BEFOREINSERT || m_iModificationType == BEFOREDELETE )
					{
						//AfxMessageBox(_T("OLD"));
						sOldFunctionName = WSPGetText(posFunction + 8, posOpenParenthesis);
						if( sOldFunctionName == _T("OVERLOAD" ))
						{
							return;
						}
						sOldFunctionName.TrimRight();
						sOldFunctionName.TrimLeft();

						sParameter = WSPFormatParameters(posOpenParenthesis, posCloseParenthesis);
						if( sParameter != _T("COMMENT_ERROR") )
						{
							//AfxMessageBox(sOldFunctionName);
							sOldFunctionParameter = _T("(") + sParameter + _T(")");
							//AfxMessageBox(sOldParameter);
							sOldFullFunctionName = sOldFunctionName + sOldFunctionParameter;
							//AfxMessageBox(sOldFullRuleName);
							//LPTSTR lpszOldRuleName	= sOldRuleName.GetBuffer(TEXTLENGTH);
						}
						else
						{
							return;
						}
					}
					
					//Detects the SC_MOD_INSERTTEXT and SC_MOD_DELETETEXT Modified notifications
					if( m_iModificationType == INSERTTEXT || m_iModificationType == DELETETEXT )
					{	
						//AfxMessageBox(_T("NEW"));
						//AfxMessageBox(str);
															
						sNewFunctionName = WSPGetText(posFunction + 8, posOpenParenthesis);
						if( sNewFunctionName == _T("OVERLOAD" ))
						{
							return;
						}
						sNewFunctionName.TrimRight();
						sNewFunctionName.TrimLeft();

						sParameter = WSPFormatParameters(posOpenParenthesis, posCloseParenthesis);
						if( sParameter != _T("COMMENT_ERROR") )
						{
							//AfxMessageBox(sNewFunctionName);
							//sNewRuleParameter = WSPGetText(posOpenParenthesis, posCloseParenthesis +1);
							sNewFunctionParameter = _T("(") + sParameter + _T(")");
							//AfxMessageBox(sNewParameter);
							sNewFullFunctionName = sNewFunctionName + sNewFunctionParameter;
							//AfxMessageBox(sNewFullRuleName);
							//LPTSTR lpszNewRuleName	= sNewRuleName.GetBuffer(TEXTLENGTH);
						}
						else
						{
							return;
						}
					}
					
					//str.Format(_T("Modification Type... %d"), m_iModificationType);
					//AfxMessageBox(str);
					//AfxMessageBox(sOldRuleName);	
					//AfxMessageBox(sNewRuleName);
					//AfxMessageBox(m_sCurrentRuleName);
					
					//Check if the rule name already exist in the workspace
					CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
					CWorkspaceTree1 wsp;
					int f = wsp.findNodeTree1Members(sOldFunctionName);
					if( f != NOT_FOUND )
					{	
						//AfxMessageBox(_T("Found"));
						
						HTREEITEM hChild = wsp.m_HItem;
						CString sFilePath = wsp.m_FilePath;
						CString sFileName = wsp.m_FileName;
						
						//str.Format(_T("Modification Type... %d"), m_iModificationType);
						//AfxMessageBox(str);
						
							/*						
							AfxMessageBox(_T("Old"));
							AfxMessageBox(sOldFullRuleName);
							AfxMessageBox(_T("New"));
							AfxMessageBox(sNewFullRuleName);
							*/								
							

						//AfxMessageBox(_T("Parser In"));
						int r = WSPParseVBSFunction(posFunction -1, posCloseParenthesis);
				
						if( r != AIPI_ERROR && r != NOT_FOUND )
						{
							//AfxMessageBox(_T("No hay Error parser"));
							//AfxMessageBox(sNewRuleName);
							if( sNewFullFunctionName == _T(""))
							{
								//m_nRuleSyntaxError++;
								//TCHAR buffer[8];
								//CString sNoError =_T("");
								//sNoError =  _itot( m_nRuleSyntaxError, buffer, 10 );
								//sNewFullRuleName = _T("Rule Syntax Error:") + sNoError;
								//AfxMessageBox(sNewFullRuleName);
								//AfxMessageBox(_T("Error"));
								//str.Format(_T("pos... %d"), pos);
								//AfxMessageBox(str);
													
							}

								
							pMainFrame->m_wndWorkspaceTabView.EditTreeItem1(sNewFullFunctionName, hChild);
							wsp.eraseElement(sOldFunctionName);
							wsp.addElement(sNewFunctionName, hChild, sFilePath, sFileName);

							//Update location
							CWorkspaceLocation loc;
							loc.eraseLocation(hChild);
							int line = rCtrl.LineFromPosition(posFunction); 
							loc.addLocation(hChild, posFunction, line+1, sNewFunctionName, sFilePath, AIPI_FUNCTION);
						}
						else
						{
							//AfxMessageBox(_T("Error en parser"));
							sNewFunctionName = _T("");						
							WSPDeleteNodeTree1(sNewFunctionName);
						}
							
					}
					else if ( sNewFunctionName != _T("") )
					{
							
						//AfxMessageBox(_T("ELSE IF"));
						
						//str.Format(_T("Flg Write Rule error...%d  " ), m_bFlagWriteError);
						//AfxMessageBox(str);
						//str.Format(_T("Modification Type... %d"), m_iModificationType);
						//AfxMessageBox(str);
					
						if( m_bFlagWriteError )
						{
							WSPAddVBSFunction(pos, true);
							m_bFlagWriteError = false;
						}
					
					}
					else
					{
						//AfxMessageBox(_T("ANOTHER ELSE"));
						
					}
				}
			}
					
			m_bFlagEditVBSFunction = false;
			//m_bFlagWriteRule = false;
		
		
		}
		else
		{
			//AfxMessageBox(_T("ELSE"));
			//Parser error
			if( m_iModificationType == DELETETEXT || m_iModificationType == INSERTTEXT )
			{
				//AfxMessageBox(_T("Delete"));
				CString sFunctionName = _T("");
				WSPDeleteNodeTree1(sFunctionName);
				m_bFlagWriteError = true;
			}
		}
	}


}



void CAIPIEditorView::WSPEditVBSFUNCTION(long pos)
{
	CScintillaCtrl& rCtrl = GetCtrl();
	
	LPSTR szKeyWord = "FUNCTION";
	LPSTR szOpenParenthesis = "(";
	LPSTR szCloseParenthesis = ")";
		
	
	//LPSTR szOpenComment = "/*";
	//LPSTR szCloseComment = "*/";
	//LPSTR szLineComment = "//";

	/*
	CString sOldRuleName, sNewRuleName;
	CString sOldRuleParameter, sNewRuleParameter;
	CString sOldFullRuleName = _T("");
	CString sNewFullRuleName = _T("");
	CString sParameter;
	*/				
		
	CString str;
	//str.Format(_T("Pos  %d"), pos);
	//AfxMessageBox(str);
	//AfxMessageBox(_T("hola"));
	
	if( m_iModificationType == BEFOREDELETE || m_iModificationType == DELETETEXT )
	{
		WSPHandleVBSFUNCTIONCloseParenthesis(pos);
	}

	WSPHandleEditVBSFUNCTIONKeyWord( pos);
	WSPCommentVBSFUNCTION( pos);
	


	long posFunction = WSPSearchToken(pos, 0, szKeyWord);
	long posCloseParenthesis = WSPSearchToken(posFunction, m_DocumentLength, szCloseParenthesis);
	
	//str.Format(_T("Write Rule Flag... %d"), m_bFlagWriteRule);
	//AfxMessageBox(str);
		
	if( posFunction != NOT_FOUND && posCloseParenthesis != NOT_FOUND && m_bFlagWriteJSFunction == false )
	{
		//WSPHandleEditRuleKeyWord( pos);
			
		/*
		str.Format(_T("Modification Type... %d"), m_iModificationType);
		AfxMessageBox(str);
		str.Format(_T("Pos Rule...%d  " ), posRule);
		AfxMessageBox(str);
		str.Format(_T("Pos Close Parenthesis...%d  " ), posCloseParenthesis);
		AfxMessageBox(str);
		*/
	 
		int r = WSPParseVBSFunction( posFunction -1, posCloseParenthesis );
		//AfxMessageBox(_T("No ha Entrado"));

		
		if( r != AIPI_ERROR && r != NOT_FOUND )
		{			
			bool lnComment = WSPCheckLineComment( posFunction, posFunction + 8);
			if( lnComment )
			{
				m_bFlagEditVBSFunction = false;
				return;
			}
			bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posFunction );
			if( blkComment )
			{
				m_bFlagEditVBSFunction = false;
				return;
			}
		
	
			
			//AfxMessageBox(_T("Entro0"));
			long posOpenParenthesis = WSPSearchToken(posFunction, posCloseParenthesis, szOpenParenthesis);
				
				
			//str.Format(_T("posCloseParenthesis... %d"), posCloseParenthesis);
			//AfxMessageBox(str);
			//str.Format(_T("flag... %d"),m_bFlagWriteRule);
			//AfxMessageBox(str);
			

			if( pos >= posFunction /*posStartDobleQuotation*/ && pos <= posCloseParenthesis && m_bFlagWriteJSFunction == false )
			{
					
				//AfxMessageBox(_T("Entro1"));
				m_bFlagEditVBSFUNCTION = true;
					
										
				if(m_bFlagEditVBSFUNCTION != false )
				{
					//AfxMessageBox(_T("Get In"));
						
					CString sOldFunctionName, sNewFunctionName;
					CString sOldFunctionParameter, sNewFunctionParameter;
					CString sOldFullFunctionName = _T("");
					CString sNewFullFunctionName = _T("");
					CString sParameter;
							
					//Detects the SC_MOD_BEFOREINSERT and SC_MOD_BEFOREDELETE Modified notifications
					if( m_iModificationType == BEFOREINSERT || m_iModificationType == BEFOREDELETE )
					{
						//AfxMessageBox(_T("OLD"));
						sOldFunctionName = WSPGetText(posFunction + 8, posOpenParenthesis);
						if( sOldFunctionName == _T("OVERLOAD" ))
						{
							return;
						}
						sOldFunctionName.TrimRight();
						sOldFunctionName.TrimLeft();

						sParameter = WSPFormatParameters(posOpenParenthesis, posCloseParenthesis);
						if( sParameter != _T("COMMENT_ERROR") )
						{
							//AfxMessageBox(sOldFunctionName);
							sOldFunctionParameter = _T("(") + sParameter + _T(")");
							//AfxMessageBox(sOldParameter);
							sOldFullFunctionName = sOldFunctionName + sOldFunctionParameter;
							//AfxMessageBox(sOldFullRuleName);
							//LPTSTR lpszOldRuleName	= sOldRuleName.GetBuffer(TEXTLENGTH);
						}
						else
						{
							return;
						}
					}
					
					//Detects the SC_MOD_INSERTTEXT and SC_MOD_DELETETEXT Modified notifications
					if( m_iModificationType == INSERTTEXT || m_iModificationType == DELETETEXT )
					{	
						//AfxMessageBox(_T("NEW"));
						//AfxMessageBox(str);
															
						sNewFunctionName = WSPGetText(posFunction + 8, posOpenParenthesis);
						if( sNewFunctionName == _T("OVERLOAD" ))
						{
							return;
						}
						sNewFunctionName.TrimRight();
						sNewFunctionName.TrimLeft();

						sParameter = WSPFormatParameters(posOpenParenthesis, posCloseParenthesis);
						if( sParameter != _T("COMMENT_ERROR") )
						{
							//AfxMessageBox(sNewFunctionName);
							//sNewRuleParameter = WSPGetText(posOpenParenthesis, posCloseParenthesis +1);
							sNewFunctionParameter = _T("(") + sParameter + _T(")");
							//AfxMessageBox(sNewParameter);
							sNewFullFunctionName = sNewFunctionName + sNewFunctionParameter;
							//AfxMessageBox(sNewFullRuleName);
							//LPTSTR lpszNewRuleName	= sNewRuleName.GetBuffer(TEXTLENGTH);
						}
						else
						{
							return;
						}
					}
					
					//str.Format(_T("Modification Type... %d"), m_iModificationType);
					//AfxMessageBox(str);
					//AfxMessageBox(sOldRuleName);	
					//AfxMessageBox(sNewRuleName);
					//AfxMessageBox(m_sCurrentRuleName);
					
					//Check if the rule name already exist in the workspace
					CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
					CWorkspaceTree1 wsp;
					int f = wsp.findNodeTree1Members(sOldFunctionName);

					if( f != NOT_FOUND )
					{	
						//AfxMessageBox(_T("Found"));
						
						HTREEITEM hChild = wsp.m_HItem;
						CString sFilePath = wsp.m_FilePath;
						CString sFileName = wsp.m_FileName;
						
						
						//str.Format(_T("Modification Type... %d"), m_iModificationType);
						//AfxMessageBox(str);
						
							/*						
							AfxMessageBox(_T("Old"));
							AfxMessageBox(sOldFullRuleName);
							AfxMessageBox(_T("New"));
							AfxMessageBox(sNewFullRuleName);
							*/								
							

						//AfxMessageBox(_T("Parser In"));
						int r = WSPParseVBSFunction(posFunction -1, posCloseParenthesis);
				
						if( r != AIPI_ERROR && r != NOT_FOUND )
						{
							//AfxMessageBox(_T("No hay Error parser"));
							//AfxMessageBox(sNewRuleName);
							if( sNewFullFunctionName == _T(""))
							{
								//m_nRuleSyntaxError++;
								//TCHAR buffer[8];
								//CString sNoError =_T("");
								//sNoError =  _itot( m_nRuleSyntaxError, buffer, 10 );
								//sNewFullRuleName = _T("Rule Syntax Error:") + sNoError;
								//AfxMessageBox(sNewFullRuleName);
								//AfxMessageBox(_T("Error"));
								//str.Format(_T("pos... %d"), pos);
								//AfxMessageBox(str);
													
							}

								
							pMainFrame->m_wndWorkspaceTabView.EditTreeItem1(sNewFullFunctionName, hChild);
							wsp.eraseElement(sOldFunctionName);
							wsp.addElement(sNewFunctionName, hChild, sFilePath, sFileName);

							//Update location
							CWorkspaceLocation loc;
							loc.eraseLocation(hChild);
							int line = rCtrl.LineFromPosition(posFunction); 
							loc.addLocation(hChild,posFunction, line+1, sNewFunctionName, sFilePath, AIPI_FUNCTION);
						}
						else
						{
							//AfxMessageBox(_T("Error en parser"));
							sNewFunctionName = _T("");						
							WSPDeleteNodeTree1(sNewFunctionName);
						}
							
					}
					else if ( sNewFunctionName != _T("") )
					{
							
						//AfxMessageBox(_T("ELSE IF"));
						
						//str.Format(_T("Flg Write Rule error...%d  " ), m_bFlagWriteError);
						//AfxMessageBox(str);
						//str.Format(_T("Modification Type... %d"), m_iModificationType);
						//AfxMessageBox(str);
					
						if( m_bFlagWriteError )
						{
							WSPAddVBSFUNCTION(pos, true);
							m_bFlagWriteError = false;
						}
					
					}
					else
					{
						//AfxMessageBox(_T("ANOTHER ELSE"));
						
					}
				}
			}
					
			m_bFlagEditVBSFUNCTION = false;
			//m_bFlagWriteRule = false;
		
		
		}
		else
		{
			//AfxMessageBox(_T("ELSE"));
			//Parser error
			if( m_iModificationType == DELETETEXT || m_iModificationType == INSERTTEXT )
			{
				//AfxMessageBox(_T("Delete"));
				CString sFunctionName = _T("");
				WSPDeleteNodeTree1(sFunctionName);
				m_bFlagWriteError = true;
			}
		}
	}


}







void CAIPIEditorView::WSPEditFunction(long pos, LPSTR szType, int typelen)
{
	CScintillaCtrl& rCtrl = GetCtrl();
	
	LPSTR szOpenParenthesis = "(";
	LPSTR szCloseParenthesis = ")";
	
	
	//LPSTR szOpenComment = "/*";
	//LPSTR szCloseComment = "*/";
	//LPSTR szLineComment = "//";

	/*
	CString sOldRuleName, sNewRuleName;
	CString sOldRuleParameter, sNewRuleParameter;
	CString sOldFullRuleName = _T("");
	CString sNewFullRuleName = _T("");
	CString sParameter;
	*/				
		
	CString str;
	//str.Format(_T("Pos  %d"), pos);
	//AfxMessageBox(str);

	//AfxMessageBox(_T("hola"));
	
	if( m_iModificationType == BEFOREDELETE || m_iModificationType == DELETETEXT )
	{
		WSPHandleFunctionCloseParenthesisEdit(pos, szType, typelen);
	}

	WSPCommentFunction( pos, szType, typelen);
	


	long posIdType = WSPSearchToken(pos, 0, szType);
	long posCloseParenthesis = WSPSearchToken(posIdType, m_DocumentLength, szCloseParenthesis);
	long posOpenParenthesis = WSPSearchToken(posIdType, posCloseParenthesis, szOpenParenthesis);

	/*
	str.Format(_T("pos Id Type Type... %d"), posIdType);
	AfxMessageBox(str);
	str.Format(_T("Pos Open Parenthesis...%d  " ), posOpenParenthesis);
	AfxMessageBox(str);
	str.Format(_T("Pos Close Parenthesis...%d  " ), posCloseParenthesis);
	AfxMessageBox(str);
	*/
	
	if( posOpenParenthesis == NOT_FOUND )
	{
		
		posOpenParenthesis = WSPSearchToken(posCloseParenthesis, 0, szOpenParenthesis);
		posIdType = WSPSearchToken(posOpenParenthesis, 0, szType);
		long posPrevCloseParenthesis = WSPSearchToken( posIdType, m_DocumentLength, szCloseParenthesis); 
		
		if( m_iModificationType == DELETETEXT)
		{
				/*
				AfxMessageBox(_T("no hallado"));
				str.Format(_T("pos Id Type Type... %d"), posIdType);
				AfxMessageBox(str);
				str.Format(_T("Pos Open Parenthesis...%d  " ), posOpenParenthesis);
				AfxMessageBox(str);
				str.Format(_T("Pos Prev Close Parenthesis...%d  " ), posPrevCloseParenthesis);
				AfxMessageBox(str);
				str.Format(_T("Pos Close Parenthesis...%d  " ), posCloseParenthesis);
				AfxMessageBox(str);
				*/
				int r = WSPParseFunction( posIdType -1, posCloseParenthesis );
				/*
				str.Format(_T("r...%d  " ), r);
				AfxMessageBox(str);
				str.Format(_T("current Pos...%d  " ), g_currentPos);
				AfxMessageBox(str);
				*/
		
				if( r == AIPI_ERROR || r == NOT_FOUND )
				{			
					//AfxMessageBox(_T("Delete"));
					CString sFunctionName = _T("");
					WSPDeleteNodeTree1(sFunctionName);
					//m_bFlagWriteError = true;
				}
			
			}
		
		
		
	}
	
	//str.Format(_T("Write Rule Flag... %d"), m_bFlagWriteFunction);
	//AfxMessageBox(str);
		
	if( posIdType != NOT_FOUND && posCloseParenthesis != NOT_FOUND && m_bFlagWriteFunction == false )
	{
		
		/*
		str.Format(_T("pos Id Type Type... %d"), posIdType);
		AfxMessageBox(str);
		str.Format(_T("Pos Open Parenthesis...%d  " ), posOpenParenthesis);
		AfxMessageBox(str);
		str.Format(_T("Pos Close Parenthesis...%d  " ), posCloseParenthesis);
		AfxMessageBox(str);
		*/
		
		int r = WSPParseFunction( posIdType -1, posCloseParenthesis );
		//AfxMessageBox(_T("No ha Entrado"));
			
		if( r != AIPI_ERROR && r != NOT_FOUND )
		{			
			bool lnComment = WSPCheckLineComment( posIdType, posIdType + typelen);
			if( lnComment )
			{
				m_bFlagEditFunction = false;
				return;
			}
			bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posIdType );
			if( blkComment )
			{
				m_bFlagEditFunction = false;
				return;
			}
		
	
			
			//AfxMessageBox(_T("Entro0"));
			
				
				
			//str.Format(_T("posStartDobleQuotation... %d"), posStartDobleQuotation);
			//AfxMessageBox(str);
			//str.Format(_T("posCloseParenthesis... %d"), posCloseParenthesis);
			//AfxMessageBox(str);
			//str.Format(_T("flag... %d"),m_bFlagWriteRule);
			//AfxMessageBox(str);
			

			if( pos >= posIdType + typelen && pos <= posCloseParenthesis && m_bFlagWriteFunction == false )
			{
					
				//AfxMessageBox(_T("Entro1"));
				m_bFlagEditFunction = true;
					
										
				if(m_bFlagEditFunction != false )
				{
					//AfxMessageBox(_T("Get In"));
						
					CString sOldFunctionName, sNewFunctionName;
					CString sOldFunctionParameter, sNewFunctionParameter;
					CString sOldFullFunctionName = _T("");
					CString sNewFullFunctionName = _T("");
					CString sParameter;
							
					//Detects the SC_MOD_BEFOREINSERT and SC_MOD_BEFOREDELETE Modified notifications
					if( m_iModificationType == BEFOREINSERT || m_iModificationType == BEFOREDELETE )
					{
						//AfxMessageBox(_T("OLD"));
						sOldFunctionName = WSPGetText(posIdType + typelen, posOpenParenthesis);
						if( sOldFunctionName == _T("OVERLOAD" ))
						{
							return;
						}
						sOldFunctionName.TrimRight();
						sOldFunctionName.TrimLeft();

						sParameter = WSPFormatParameters(posOpenParenthesis, posCloseParenthesis);
						if( sParameter != _T("COMMENT_ERROR") )
						{
							//AfxMessageBox(sOldFunctionName);
							sOldFunctionParameter = _T("(") + sParameter + _T(")");
							//AfxMessageBox(sOldParameter);
							sOldFullFunctionName = sOldFunctionName + sOldFunctionParameter;
							//AfxMessageBox(sOldFullRuleName);
							//LPTSTR lpszOldRuleName	= sOldRuleName.GetBuffer(TEXTLENGTH);
						}
						else
						{
							return;
						}
					}
					
					//Detects the SC_MOD_INSERTTEXT and SC_MOD_DELETETEXT Modified notifications
					if( m_iModificationType == INSERTTEXT || m_iModificationType == DELETETEXT )
					{	
						//AfxMessageBox(_T("NEW"));
						//AfxMessageBox(str);
															
						sNewFunctionName = WSPGetText(posIdType + typelen, posOpenParenthesis);
						if( sNewFunctionName == _T("OVERLOAD" ))
						{
							return;
						}
						sNewFunctionName.TrimRight();
						sNewFunctionName.TrimLeft();

						sParameter = WSPFormatParameters(posOpenParenthesis, posCloseParenthesis);
						if( sParameter != _T("COMMENT_ERROR") )
						{
							//AfxMessageBox(sNewFunctionName);
							//sNewRuleParameter = WSPGetText(posOpenParenthesis, posCloseParenthesis +1);
							sNewFunctionParameter = _T("(") + sParameter + _T(")");
							//AfxMessageBox(sNewParameter);
							sNewFullFunctionName = sNewFunctionName + sNewFunctionParameter;
							//AfxMessageBox(sNewFullRuleName);
							//LPTSTR lpszNewRuleName	= sNewRuleName.GetBuffer(TEXTLENGTH);
						}
						else
						{
							return;
						}
					}
					
					//str.Format(_T("Modification Type... %d"), m_iModificationType);
					//AfxMessageBox(str);
					//AfxMessageBox(sOldRuleName);	
					//AfxMessageBox(sNewRuleName);
					//AfxMessageBox(m_sCurrentRuleName);
					
					//Check if the rule name already exist in the workspace
					CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
					CWorkspaceTree1 wsp;
					int f = wsp.findNodeTree1Members(sOldFunctionName);
					
					if( f != NOT_FOUND )
					{	
						//AfxMessageBox(_T("Found"));
						
						HTREEITEM hChild = wsp.m_HItem;
						CString sFilePath = wsp.m_FilePath;
						CString sFileName = wsp.m_FileName;
						
						//str.Format(_T("Modification Type... %d"), m_iModificationType);
						//AfxMessageBox(str);
						
							/*						
							AfxMessageBox(_T("Old"));
							AfxMessageBox(sOldFullFunctionName);
							AfxMessageBox(_T("New"));
							AfxMessageBox(sNewFullFunctionName);
							*/								
							

						//AfxMessageBox(_T("Parser In"));
						int r = WSPParseFunction(posIdType -1, posCloseParenthesis);
						
						/*
						str.Format(_T("Pos IdType...%d  " ), posIdType);
						AfxMessageBox(str);
						str.Format(_T("Pos Close Parenthesis...%d  " ), posCloseParenthesis);
						AfxMessageBox(str);
						*/
				
						if( r != AIPI_ERROR && r != NOT_FOUND )
						{
							//AfxMessageBox(_T("No hay Error parser"));
							//AfxMessageBox(sNewRuleName);
							if( sNewFullFunctionName == _T(""))
							{
								//m_nRuleSyntaxError++;
								//TCHAR buffer[8];
								//CString sNoError =_T("");
								//sNoError =  _itot( m_nRuleSyntaxError, buffer, 10 );
								//sNewFullRuleName = _T("Rule Syntax Error:") + sNoError;
								//AfxMessageBox(sNewFullRuleName);
								//AfxMessageBox(_T("Error"));
								//str.Format(_T("pos... %d"), pos);
								//AfxMessageBox(str);
													
							}

								
							pMainFrame->m_wndWorkspaceTabView.EditTreeItem1(sNewFullFunctionName, hChild);
							wsp.eraseElement(sOldFunctionName);
							wsp.addElement(sNewFunctionName, hChild, sFilePath, sFileName);

							//Update location
							CWorkspaceLocation loc;
							loc.eraseLocation(hChild);
							int line = rCtrl.LineFromPosition(posIdType); 
							loc.addLocation(hChild,posIdType, line+1, sNewFunctionName, sFilePath, AIPI_FUNCTION);
							
						}
						else
						{
							//AfxMessageBox(_T("Error en parser"));
							sNewFunctionName = _T("");						
							WSPDeleteNodeTree1(sNewFunctionName);
						}
							
					}
					else if ( sNewFunctionName != _T("") )
					{
							
						//AfxMessageBox(_T("ELSE IF"));
						
						//str.Format(_T("Flg Write Rule error...%d  " ), m_bFlagWriteError);
						//AfxMessageBox(str);
						//str.Format(_T("Modification Type... %d"), m_iModificationType);
						//AfxMessageBox(str);
					
						if( m_bFlagWriteError )
						{
							WSPAddFunction(pos, true);
							m_bFlagWriteError = false;
						}
					
					}
					else
					{
						//AfxMessageBox(_T("ANOTHER ELSE"));
						
					}
				}
			}
					
			m_bFlagEditFunction = false;
			//m_bFlagWriteRule = false;
		
		
		}
		else
		{
			//AfxMessageBox(_T("ELSE"));
			//Parser error
			if( m_iModificationType == DELETETEXT || m_iModificationType == INSERTTEXT )
			{
				//AfxMessageBox(_T("Delete"));
				CString sFunctionName = _T("");
				WSPDeleteNodeTree1(sFunctionName);
				m_bFlagWriteError = true;
			}
		}
	}


}




void CAIPIEditorView::WSPEditVariable(long pos, LPSTR szType, int typelen)
{
	CScintillaCtrl& rCtrl = GetCtrl();
	
	
	LPSTR szSemiColon = ";";
	
	/*
	CString sOldRuleName, sNewRuleName;
	CString sOldRuleParameter, sNewRuleParameter;
	CString sOldFullRuleName = _T("");
	CString sNewFullRuleName = _T("");
	CString sParameter;
	*/				
		
	CString str;
	//str.Format(_T("Pos  %d"), pos);
	//AfxMessageBox(str);

	//AfxMessageBox(_T("hola"));
	
	if( m_iModificationType == BEFOREDELETE || m_iModificationType == DELETETEXT )
	{
		WSPHandleVariableSemiColonEdit(pos, szType, typelen);
	}

	WSPCommentVariable( pos, szType, typelen);
	


	long posIdType = WSPSearchToken(pos, 0, szType);
	long posSemiColon = WSPSearchToken(posIdType, m_DocumentLength, szSemiColon);
	

	/*
	str.Format(_T("pos Id Type Type... %d"), posIdType);
	AfxMessageBox(str);
	str.Format(_T("Pos SemiColon...%d  " ), posSemiColon);
	AfxMessageBox(str);
	*/
	
	
	//str.Format(_T("Write Rule Flag... %d"), m_bFlagWriteFunction);
	//AfxMessageBox(str);
		
	if( posIdType != NOT_FOUND && posSemiColon != NOT_FOUND && m_bFlagWriteVariable == false )
	{
		
		/*
		str.Format(_T("pos Id Type Type... %d"), posIdType);
		AfxMessageBox(str);
		str.Format(_T("Pos Open Parenthesis...%d  " ), posOpenParenthesis);
		AfxMessageBox(str);
		str.Format(_T("Pos Close Parenthesis...%d  " ), posCloseParenthesis);
		AfxMessageBox(str);
		*/
		
		int r = WSPParseVariable( posIdType -1, posSemiColon );
		//AfxMessageBox(_T("No ha Entrado"));
			
		if( r != AIPI_ERROR && r != NOT_FOUND )
		{			
			bool lnComment = WSPCheckLineComment( posIdType, posIdType + typelen);
			if( lnComment )
			{
				m_bFlagEditVariable = false;
				return;
			}
			bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posIdType );
			if( blkComment )
			{
				m_bFlagEditVariable = false;
				return;
			}
		
	
			
			//AfxMessageBox(_T("Entro0"));
			
				
				
			//str.Format(_T("posStartDobleQuotation... %d"), posStartDobleQuotation);
			//AfxMessageBox(str);
			//str.Format(_T("posCloseParenthesis... %d"), posCloseParenthesis);
			//AfxMessageBox(str);
			//str.Format(_T("flag... %d"),m_bFlagWriteRule);
			//AfxMessageBox(str);
			

			if( pos >= posIdType + typelen && pos <= posSemiColon && m_bFlagWriteVariable == false )
			{
					
				//AfxMessageBox(_T("Entro1"));
				m_bFlagEditVariable = true;
					
										
				if(m_bFlagEditVariable != false )
				{
					//AfxMessageBox(_T("Get In"));
						
					CString sOldVariableName, sNewVariableName;
					CString sOldVariableParameter, sNewVariableParameter;
					CString sParameter;
							
					//Detects the SC_MOD_BEFOREINSERT and SC_MOD_BEFOREDELETE Modified notifications
					if( m_iModificationType == BEFOREINSERT || m_iModificationType == BEFOREDELETE )
					{
						//AfxMessageBox(_T("OLD"));
						sOldVariableName = WSPGetText(posIdType + typelen, posSemiColon);
						if( sOldVariableName == _T("OVERLOAD" ))
						{
							return;
						}
						sOldVariableName.TrimRight();
						sOldVariableName.TrimLeft();

						
					}
					
					//Detects the SC_MOD_INSERTTEXT and SC_MOD_DELETETEXT Modified notifications
					if( m_iModificationType == INSERTTEXT || m_iModificationType == DELETETEXT )
					{	
						//AfxMessageBox(_T("NEW"));
						//AfxMessageBox(str);
															
						sNewVariableName = WSPGetText(posIdType + typelen, posSemiColon);
						if( sNewVariableName == _T("OVERLOAD" ))
						{
							return;
						}
						sNewVariableName.TrimRight();
						sNewVariableName.TrimLeft();

						
					}
					
					//str.Format(_T("Modification Type... %d"), m_iModificationType);
					//AfxMessageBox(str);
					//AfxMessageBox(sOldRuleName);	
					//AfxMessageBox(sNewRuleName);
					//AfxMessageBox(m_sCurrentRuleName);
					
					//Check if the rule name already exist in the workspace
					CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
					CWorkspaceTree1 wsp;
					int f = wsp.findNodeTree1Members(sOldVariableName);
					
					if( f != NOT_FOUND )
					{	
						//AfxMessageBox(_T("Found"));
						
						HTREEITEM hChild = wsp.m_HItem;
						CString sFilePath = wsp.m_FilePath;
						CString sFileName = wsp.m_FileName;
						
						//str.Format(_T("Modification Type... %d"), m_iModificationType);
						//AfxMessageBox(str);
						
							/*						
							AfxMessageBox(_T("Old"));
							AfxMessageBox(sOldVariableName);
							AfxMessageBox(_T("New"));
							AfxMessageBox(sNewVariableName);
							*/								
							

						//AfxMessageBox(_T("Parser In"));
						int r = WSPParseVariable(posIdType -1, posSemiColon);
						
						/*
						str.Format(_T("Pos IdType...%d  " ), posIdType);
						AfxMessageBox(str);
						str.Format(_T("Pos SemiColon...%d  " ), posSemiColon);
						AfxMessageBox(str);
						*/
				
						if( r != AIPI_ERROR && r != NOT_FOUND )
						{
							//AfxMessageBox(_T("No hay Error parser"));
							//AfxMessageBox(sNewRuleName);
							if( sNewVariableName == _T(""))
							{
								//m_nRuleSyntaxError++;
								//TCHAR buffer[8];
								//CString sNoError =_T("");
								//sNoError =  _itot( m_nRuleSyntaxError, buffer, 10 );
								//sNewFullRuleName = _T("Rule Syntax Error:") + sNoError;
								//AfxMessageBox(sNewFullRuleName);
								//AfxMessageBox(_T("Error"));
								//str.Format(_T("pos... %d"), pos);
								//AfxMessageBox(str);
													
							}

								
							pMainFrame->m_wndWorkspaceTabView.EditTreeItem1(sNewVariableName, hChild);
							wsp.eraseElement(sOldVariableName);
							wsp.addElement(sNewVariableName, hChild, sFilePath, sFileName);

							//Update location
							CWorkspaceLocation loc;
							loc.eraseLocation(hChild);
							int line = rCtrl.LineFromPosition(posIdType); 
							loc.addLocation(hChild, posIdType, line+1, sNewVariableName, sFilePath, AIPI_VARIABLE);
						}
						else
						{
							//AfxMessageBox(_T("Error en parser"));
							sNewVariableName = _T("");						
							WSPDeleteNodeTree1(sNewVariableName);
						}
							
					}
					else if ( sNewVariableName != _T("") )
					{
							
						//AfxMessageBox(_T("ELSE IF"));
						
						//str.Format(_T("Flg Write Rule error...%d  " ), m_bFlagWriteError);
						//AfxMessageBox(str);
						//str.Format(_T("Modification Type... %d"), m_iModificationType);
						//AfxMessageBox(str);
					
						if( m_bFlagWriteError )
						{
							WSPAddVariable(pos, true);
							m_bFlagWriteError = false;
						}
					
					}
					else
					{
						//AfxMessageBox(_T("ANOTHER ELSE"));
						
					}
				}
			}
					
			m_bFlagEditVariable = false;
			//m_bFlagWriteRule = false;
		
		
		}
		else
		{
			//AfxMessageBox(_T("ELSE"));
			//Parser error
			if( m_iModificationType == DELETETEXT || m_iModificationType == INSERTTEXT )
			{
				//AfxMessageBox(_T("Delete"));
				CString sVariableName = _T("");
				WSPDeleteNodeTree1(sVariableName);
				m_bFlagWriteError = true;
			}
		}
	}


}





void CAIPIEditorView::WSPEditClass(long pos)
{
	CScintillaCtrl& rCtrl = GetCtrl();
	
	
	LPSTR szOpenBrace = "{";
	LPSTR szKeyWord = "CLASS";
	/*
	CString sOldRuleName, sNewRuleName;
	CString sOldRuleParameter, sNewRuleParameter;
	CString sOldFullRuleName = _T("");
	CString sNewFullRuleName = _T("");
	CString sParameter;
	*/				
		
	CString str;
	//str.Format(_T("Pos  %d"), pos);
	//AfxMessageBox(str);

	//AfxMessageBox(_T("hola"));
	
	if( m_iModificationType == BEFOREDELETE || m_iModificationType == DELETETEXT )
	{

		WSPHandleClassOpenBrace(pos);
	}

	WSPHandleEditClassKeyWord( pos);
	WSPCommentClass( pos);
	
	


	long posClass = WSPSearchToken(pos, 0, szKeyWord);
	long posOpenBrace = WSPSearchToken(posClass, m_DocumentLength, szOpenBrace);
	

	/*
	str.Format(_T("pos Id Type Type... %d"), posIdType);
	AfxMessageBox(str);
	str.Format(_T("Pos SemiColon...%d  " ), posSemiColon);
	AfxMessageBox(str);
	*/
	
	
	//str.Format(_T("Write Rule Flag... %d"), m_bFlagWriteFunction);
	//AfxMessageBox(str);
		
	if( posClass != NOT_FOUND && posOpenBrace != NOT_FOUND && m_bFlagWriteClass == false )
	{
		
		/*
		str.Format(_T("pos Id Type Type... %d"), posIdType);
		AfxMessageBox(str);
		str.Format(_T("Pos Open Parenthesis...%d  " ), posOpenParenthesis);
		AfxMessageBox(str);
		str.Format(_T("Pos Close Parenthesis...%d  " ), posCloseParenthesis);
		AfxMessageBox(str);
		*/
		
		int r = WSPParseClass( posClass -1, posOpenBrace );
		//AfxMessageBox(_T("No ha Entrado"));
			
		if( r != AIPI_ERROR && r != NOT_FOUND )
		{			
			bool lnComment = WSPCheckLineComment( posClass, posClass + 5);
			if( lnComment )
			{
				m_bFlagEditClass = false;
				return;
			}
			bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posClass );
			if( blkComment )
			{
				m_bFlagEditClass = false;
				return;
			}
		
	
			
			//AfxMessageBox(_T("Entro0"));
			
				
				
			//str.Format(_T("posStartDobleQuotation... %d"), posStartDobleQuotation);
			//AfxMessageBox(str);
			//str.Format(_T("posCloseParenthesis... %d"), posCloseParenthesis);
			//AfxMessageBox(str);
			//str.Format(_T("flag... %d"),m_bFlagWriteRule);
			//AfxMessageBox(str);
			

			if( pos >= posClass + 5 && pos <= posOpenBrace && m_bFlagWriteClass == false )
			{
					
				//AfxMessageBox(_T("Entro1"));
				m_bFlagEditClass = true;
					
										
				if(m_bFlagEditClass != false )
				{
					//AfxMessageBox(_T("Get In"));
						
					CString sOldClassName, sNewClassName;
					CString sOldClassParameter, sNewClassParameter;
					CString sParameter;
							
					//Detects the SC_MOD_BEFOREINSERT and SC_MOD_BEFOREDELETE Modified notifications
					if( m_iModificationType == BEFOREINSERT || m_iModificationType == BEFOREDELETE )
					{
						//AfxMessageBox(_T("OLD"));
						sOldClassName = WSPGetText(posClass + 5, posOpenBrace);
						if( sOldClassName == _T("OVERLOAD" ))
						{
							return;
						}
						sOldClassName.TrimRight();
						sOldClassName.TrimLeft();

						
					}
					
					//Detects the SC_MOD_INSERTTEXT and SC_MOD_DELETETEXT Modified notifications
					if( m_iModificationType == INSERTTEXT || m_iModificationType == DELETETEXT )
					{	
						//AfxMessageBox(_T("NEW"));
						//AfxMessageBox(str);
															
						sNewClassName = WSPGetText(posClass + 5, posOpenBrace);
						if( sNewClassName == _T("OVERLOAD" ))
						{
							return;
						}
						sNewClassName.TrimRight();
						sNewClassName.TrimLeft();

						
					}
					
					//str.Format(_T("Modification Type... %d"), m_iModificationType);
					//AfxMessageBox(str);
					//AfxMessageBox(sOldRuleName);	
					//AfxMessageBox(sNewRuleName);
					//AfxMessageBox(m_sCurrentRuleName);
					
					//Check if the rule name already exist in the workspace
					CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
					CWorkspaceTree1 wsp;
					int f = wsp.findNodeTree1Members(sOldClassName);
					
					if( f != NOT_FOUND )
					{	
						//AfxMessageBox(_T("Found"));
						
						HTREEITEM hChild = wsp.m_HItem;
						CString   sFilePath = wsp.m_FilePath;
						CString   sFileName = wsp.m_FileName;
						
						//str.Format(_T("Modification Type... %d"), m_iModificationType);
						//AfxMessageBox(str);
						
							/*						
							AfxMessageBox(_T("Old"));
							AfxMessageBox(sOldVariableName);
							AfxMessageBox(_T("New"));
							AfxMessageBox(sNewVariableName);
							*/								
							

						//AfxMessageBox(_T("Parser In"));
						int r = WSPParseClass(posClass -1, posOpenBrace);
						
						/*
						str.Format(_T("Pos IdType...%d  " ), posIdType);
						AfxMessageBox(str);
						str.Format(_T("Pos SemiColon...%d  " ), posSemiColon);
						AfxMessageBox(str);
						*/
				
						if( r != AIPI_ERROR && r != NOT_FOUND )
						{
							//AfxMessageBox(_T("No hay Error parser"));
							//AfxMessageBox(sNewRuleName);
							if( sNewClassName == _T(""))
							{
								//m_nRuleSyntaxError++;
								//TCHAR buffer[8];
								//CString sNoError =_T("");
								//sNoError =  _itot( m_nRuleSyntaxError, buffer, 10 );
								//sNewFullRuleName = _T("Rule Syntax Error:") + sNoError;
								//AfxMessageBox(sNewFullRuleName);
								//AfxMessageBox(_T("Error"));
								//str.Format(_T("pos... %d"), pos);
								//AfxMessageBox(str);
													
							}

								
							pMainFrame->m_wndWorkspaceTabView.EditTreeItem1(sNewClassName, hChild);
							wsp.eraseElement(sOldClassName);
							wsp.addElement(sNewClassName, hChild, sFilePath, sFileName);

							//Update location
							CWorkspaceLocation loc;
							loc.eraseLocation(hChild);
							int line = rCtrl.LineFromPosition(posClass); 
							loc.addLocation(hChild,posClass, line+1, sNewClassName, sFilePath, AIPI_CLASS);
							
						}
						else
						{
							//AfxMessageBox(_T("Error en parser"));
							sNewClassName = _T("");						
							WSPDeleteNodeTree1(sNewClassName);
						}
							
					}
					else if ( sNewClassName != _T("") )
					{
							
						//AfxMessageBox(_T("ELSE IF"));
						
						//str.Format(_T("Flg Write Rule error...%d  " ), m_bFlagWriteError);
						//AfxMessageBox(str);
						//str.Format(_T("Modification Type... %d"), m_iModificationType);
						//AfxMessageBox(str);
					
						if( m_bFlagWriteError )
						{
							WSPAddClass(pos, true);
							m_bFlagWriteError = false;
						}
					
					}
					else
					{
						//AfxMessageBox(_T("ANOTHER ELSE"));
						
					}
				}
			}
					
			m_bFlagEditClass = false;
			//m_bFlagWriteRule = false;
		
		
		}
		else
		{
			//AfxMessageBox(_T("ELSE"));
			//Parser error
			if( m_iModificationType == DELETETEXT || m_iModificationType == INSERTTEXT )
			{
				//AfxMessageBox(_T("Delete"));
				CString sClassName = _T("");
				WSPDeleteNodeTree1(sClassName);
				m_bFlagWriteError = true;
			}
		}
	}


}



void CAIPIEditorView::WSPEditQuery(long pos)
{
	CScintillaCtrl& rCtrl = GetCtrl();
	
	
	LPSTR szEqual = "=";
	LPSTR szKeyWord = "SQLQUERY";
	/*
	CString sOldRuleName, sNewRuleName;
	CString sOldRuleParameter, sNewRuleParameter;
	CString sOldFullRuleName = _T("");
	CString sNewFullRuleName = _T("");
	CString sParameter;
	*/				
		
	CString str;
	//str.Format(_T("Pos  %d"), pos);
	//AfxMessageBox(str);

	//AfxMessageBox(_T("hola"));
	
	if( m_iModificationType == BEFOREDELETE || m_iModificationType == DELETETEXT )
	{
		WSPHandleQueryEqual(pos);
	}

	WSPHandleEditQueryKeyWord( pos);
	WSPCommentQuery( pos);
	
	


	long posQuery = WSPSearchToken(pos, 0, szKeyWord);
	long posEqual = WSPSearchToken(posQuery, m_DocumentLength, szEqual);
	

	/*
	str.Format(_T("pos Id Type Type... %d"), posIdType);
	AfxMessageBox(str);
	str.Format(_T("Pos SemiColon...%d  " ), posSemiColon);
	AfxMessageBox(str);
	*/
	
	
	//str.Format(_T("Write Rule Flag... %d"), m_bFlagWriteFunction);
	//AfxMessageBox(str);
		
	if( posQuery != NOT_FOUND && posEqual != NOT_FOUND && m_bFlagWriteQuery == false )
	{
		
		/*
		str.Format(_T("pos Id Type Type... %d"), posIdType);
		AfxMessageBox(str);
		str.Format(_T("Pos Open Parenthesis...%d  " ), posOpenParenthesis);
		AfxMessageBox(str);
		str.Format(_T("Pos Close Parenthesis...%d  " ), posCloseParenthesis);
		AfxMessageBox(str);
		*/
		
		int r = WSPParseQuery( posQuery -1, posEqual );
		//AfxMessageBox(_T("No ha Entrado"));
			
		if( r != AIPI_ERROR && r != NOT_FOUND )
		{			
			bool lnComment = WSPCheckLineComment( posQuery, posQuery + 8);
			if( lnComment )
			{
				m_bFlagEditQuery = false;
				return;
			}
			bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posQuery );
			if( blkComment )
			{
				m_bFlagEditQuery = false;
				return;
			}
		
	
			
			//AfxMessageBox(_T("Entro0"));
			
				
				
			//str.Format(_T("posStartDobleQuotation... %d"), posStartDobleQuotation);
			//AfxMessageBox(str);
			//str.Format(_T("posCloseParenthesis... %d"), posCloseParenthesis);
			//AfxMessageBox(str);
			//str.Format(_T("flag... %d"),m_bFlagWriteRule);
			//AfxMessageBox(str);
			

			if( pos >= posQuery + 8 && pos <= posEqual && m_bFlagWriteQuery == false )
			{
					
				//AfxMessageBox(_T("Entro1"));
				m_bFlagEditQuery = true;
					
										
				if(m_bFlagEditQuery != false )
				{
					//AfxMessageBox(_T("Get In"));
						
					CString sOldQueryName, sNewQueryName;
					CString sOldQueryParameter, sNewQueryParameter;
					CString sParameter;
							
					//Detects the SC_MOD_BEFOREINSERT and SC_MOD_BEFOREDELETE Modified notifications
					if( m_iModificationType == BEFOREINSERT || m_iModificationType == BEFOREDELETE )
					{
						//AfxMessageBox(_T("OLD"));
						sOldQueryName = WSPGetText(posQuery + 8, posEqual);
						if( sOldQueryName == _T("OVERLOAD" ))
						{
							return;
						}
						sOldQueryName.TrimRight();
						sOldQueryName.TrimLeft();

						
					}
					
					//Detects the SC_MOD_INSERTTEXT and SC_MOD_DELETETEXT Modified notifications
					if( m_iModificationType == INSERTTEXT || m_iModificationType == DELETETEXT )
					{	
						//AfxMessageBox(_T("NEW"));
						//AfxMessageBox(str);
															
						sNewQueryName = WSPGetText(posQuery + 8, posEqual);
						if( sNewQueryName == _T("OVERLOAD" ))
						{
							return;
						}
						sNewQueryName.TrimRight();
						sNewQueryName.TrimLeft();

						
					}
					
					//str.Format(_T("Modification Type... %d"), m_iModificationType);
					//AfxMessageBox(str);
					//AfxMessageBox(sOldRuleName);	
					//AfxMessageBox(sNewRuleName);
					//AfxMessageBox(m_sCurrentRuleName);
					
					//Check if the rule name already exist in the workspace
					CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
					CWorkspaceTree1 wsp;
					int f = wsp.findNodeTree1Members(sOldQueryName);
					
					if( f != NOT_FOUND )
					{	
						//AfxMessageBox(_T("Found"));
						
						HTREEITEM hChild = wsp.m_HItem;
						CString   sFilePath = wsp.m_FilePath;
						CString   sFileName = wsp.m_FileName;
						
						//str.Format(_T("Modification Type... %d"), m_iModificationType);
						//AfxMessageBox(str);
						
							/*						
							AfxMessageBox(_T("Old"));
							AfxMessageBox(sOldVariableName);
							AfxMessageBox(_T("New"));
							AfxMessageBox(sNewVariableName);
							*/								
							

						//AfxMessageBox(_T("Parser In"));
						int r = WSPParseQuery(posQuery -1, posEqual);
						
						/*
						str.Format(_T("Pos IdType...%d  " ), posIdType);
						AfxMessageBox(str);
						str.Format(_T("Pos SemiColon...%d  " ), posSemiColon);
						AfxMessageBox(str);
						*/
				
						if( r != AIPI_ERROR && r != NOT_FOUND )
						{
							//AfxMessageBox(_T("No hay Error parser"));
							//AfxMessageBox(sNewRuleName);
							if( sNewQueryName == _T(""))
							{
								//m_nRuleSyntaxError++;
								//TCHAR buffer[8];
								//CString sNoError =_T("");
								//sNoError =  _itot( m_nRuleSyntaxError, buffer, 10 );
								//sNewFullRuleName = _T("Rule Syntax Error:") + sNoError;
								//AfxMessageBox(sNewFullRuleName);
								//AfxMessageBox(_T("Error"));
								//str.Format(_T("pos... %d"), pos);
								//AfxMessageBox(str);
													
							}

								
							pMainFrame->m_wndWorkspaceTabView.EditTreeItem1(sNewQueryName, hChild);
							wsp.eraseElement(sOldQueryName);
							wsp.addElement(sNewQueryName, hChild, sFilePath, sFileName);

							//Update location
							CWorkspaceLocation loc;
							loc.eraseLocation(hChild);
							int line = rCtrl.LineFromPosition(posQuery); 
							loc.addLocation(hChild,posQuery, line+1, sNewQueryName, sFilePath, AIPI_QUERY);
							
						}
						else
						{
							//AfxMessageBox(_T("Error en parser"));
							sNewQueryName = _T("");						
							WSPDeleteNodeTree1(sNewQueryName);
						}
							
					}
					else if ( sNewQueryName != _T("") )
					{
							
						//AfxMessageBox(_T("ELSE IF"));
						
						//str.Format(_T("Flg Write Rule error...%d  " ), m_bFlagWriteError);
						//AfxMessageBox(str);
						//str.Format(_T("Modification Type... %d"), m_iModificationType);
						//AfxMessageBox(str);
					
						if( m_bFlagWriteError )
						{
							WSPAddQuery(pos, true);
							m_bFlagWriteError = false;
						}
					
					}
					else
					{
						//AfxMessageBox(_T("ANOTHER ELSE"));
						
					}
				}
			}
					
			m_bFlagEditQuery = false;
			//m_bFlagWriteRule = false;
		
		
		}
		else
		{
			//AfxMessageBox(_T("ELSE"));
			//Parser error
			if( m_iModificationType == DELETETEXT || m_iModificationType == INSERTTEXT )
			{
				//AfxMessageBox(_T("Delete"));
				CString sQueryName = _T("");
				WSPDeleteNodeTree1(sQueryName);
				m_bFlagWriteError = true;
			}
		}
	}


}



BOOL CAIPIEditorView::WSPCheckLineComment(long posToken, long posEnd)
{
	LPSTR szLineComment = "//";
	CScintillaCtrl& rCtrl = GetCtrl();
	BOOL bLineComment = false; 

	//CString str;
	//Checking for line comments
	//AfxMessageBox(_T("Check LINE COMMENT"));
	
	int tokenLine = rCtrl.LineFromPosition(posToken);
	//str.Format(_T("Line Comment... %d"), tkLine);
	//AfxMessageBox(str);

	long posStartTokenLine = rCtrl.PositionFromLine(tokenLine);
	//str.Format(_T("Pos Start Line Comment... %d"), posStartTokenLine);
	//AfxMessageBox(str);		
								
	//AfxMessageBox(_T("Search Pos Line Comment"));
	long posLineComment = WSPSearchToken( posStartTokenLine, posEnd, szLineComment );

	if( posLineComment != NOT_FOUND )
	{
		bLineComment = true;
	}

return bLineComment;

}


BOOL CAIPIEditorView::WSPCheckBlockComment(long posStart, long posEnd, long posToken )
{
	LPSTR szOpenComment = "/*";
	LPSTR szCloseComment = "*/";
	BOOL bBlockComment = false;
	CString str;
	
	//str.Format(_T("Pos Start... %d"), posStart);
	//AfxMessageBox(str);
	
	//str.Format(_T("Pos End... %d"), posEnd);
	//AfxMessageBox(str);
	//Return FALSE: Don´t manage the block comment
	//Return TRUE: Manage the block comment
	//Checking for block comments
	
	//AfxMessageBox(_T("Check BLOCK COMMENT"));
	//AfxMessageBox(_T("posOpenComment"));
	long posOpenComment = WSPSearchToken(posToken, posStart, szOpenComment);
	//str.Format(_T("Open Comment... %d"), posOpenComment);
	//AfxMessageBox(str);
	
	if( posOpenComment != NOT_FOUND )
	{
		//AfxMessageBox(_T("posCloseComment"));
		long posCloseComment = WSPSearchToken(posOpenComment, posEnd, szCloseComment);
		//str.Format(_T("Close Comment... %d"), posCloseComment);
		//AfxMessageBox(str);
	
		
		if( posCloseComment != NOT_FOUND )
		{
			//The block comment is above the current identifier
			//Don´t manage the comment 
			if( posCloseComment < posToken )
			{
				bBlockComment = false;
			}
			//The block comment is between the current identifier
			//Manage the comment
			else if( posOpenComment < posToken && posCloseComment > posToken )
			{
				bBlockComment = true;
			}
		}
		else
		{	//SEMANTIC ERROR
			//No close comment was found, but an open comment was found
			//Don´t manage the comment
			bBlockComment = false;
		}
	}
	else
	{ //There is no open comment above the current identifier
	  //Don´t manage the comment
		bBlockComment = false;
	}
	
	 
return bBlockComment;
}


int CAIPIEditorView::WSPMatchToken(int tk )
{
	CAipi_Lexer lex;
	//AfxMessageBox(_T("Hello"));


	CString str;
	/*
	str.Format(_T("Token entrante...%d  " ), tk);
	AfxMessageBox(str);
	str.Format(_T("Look ahead...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/

	if( m_lookahead == _TEOF )
	{
		//AfxMessageBox(_T("Empty"));
		return AIPI_ERROR;
	}

	//str.Format(_T("Current Pos...%d  " ), g_currentPos);
	//AfxMessageBox(str);
	//TCHAR buffer[80];
	//wsprintf(buffer, _T("Letra: %c"), tk);
	//AfxMessageBox(buffer);
	//AfxMessageBox(m_sTokenName);
	
	if (m_lookahead == tk)
	{
		//AfxMessageBox(_T("Prev Token"));
		//AfxMessageBox(m_sTokenName);
		
		++g_currentPos;
		m_lookahead = WSPGetToken();
		//AfxMessageBox(_T("Hello2"));
		//str.Format(_T("Next Look ahead...%d  " ), m_lookahead);
		//AfxMessageBox(str);
		//wsprintf(buffer, _T("Letra: %c"), tk);
		//AfxMessageBox(buffer);
		//AfxMessageBox(m_sTokenName);
		//str.Format(_T("Current Pos...%d  " ), g_currentPos);
		//AfxMessageBox(str);
					
	
	}
	else 
	{	
		
		//CAipi_Error err;
		//err.displayError(SINTAX, SINTAX_ERROR, _T("Symbol doesn't match.") );
		return AIPI_ERROR;
	}

return FOUND;
}




bool CAIPIEditorView::isDigit(int c)
{
	
	if( c >= 48 && c <= 57 )
	{
		return TRUE;
	}
	
	return FALSE;

}



bool CAIPIEditorView::isAlphabetic(int c)
{
	
	if( ( c >= 65  && c <= 90 ) || ( c >= 97 && c <= 122 ) )
	{	
		return TRUE;
	}
	
	return FALSE;

}

	
bool CAIPIEditorView::isAlphaNumeric(int c)
{
	if( isAlphabetic( c ) || isDigit( c ) || c == 95 )
	{
		return TRUE;
	}
		
	return FALSE;
}




bool CAIPIEditorView::isPunctuator(int c)
{
	if(		c == SEMICOLON 
		||	c == OPEN_PARENTHESIS 
		||	c == CLOSE_PARENTHESIS 
		||	c == OPEN_BRACKET 
		||	c == CLOSE_BRACKET 
		||	c == OPEN_BRACE 
		||	c == CLOSE_BRACE 
		||	c == COMMA 
		||	c == COLON 
		||	c == PERIOD 
		||	c == NUMBER_SIGN 
		||  c == AT_SYMBOL 
	   )
	{
		return TRUE;
	}
		
	return FALSE;
	

}


bool CAIPIEditorView::isOperator(int c)
{
	if( (c > 59 && c < 63) 
		|| c == EXCLAMATION 
		|| c == PLUS_SIGN 
		|| c == MINUS_SIGN 
		|| c == ASTERIC 
		|| c == SLASH 
		|| c == CARET 
		|| c == EQUIVALENCY 
		|| c == QUESTION 
		|| c == PERCENT 
		|| c == AMPERSAND 
		|| c == VERTICAL_BAR 
		|| c == COLON 
	   )
	{
		return TRUE;
	}
	
	return FALSE;

}


bool CAIPIEditorView::isTypeName(CString s)
{
	if(		s == _T("void") 
		||	s == _T("char")
		||	s == _T("short")
		||	s == _T("int")
		||	s == _T("long")
		||	s == _T("float")
		||	s == _T("double")
		||	s == _T("signed")
		||	s == _T("unsigned")
		
	   )
	{
		return TRUE;
	}
	
	return FALSE;

}


LPSTR CAIPIEditorView::WSPGetIdentifierType( int idType )
{
	LPSTR szIdentifierType = "";
	
	switch( idType)
	{
		case C_INT:
			szIdentifierType = "int";
			break;
		case C_CHAR:
			szIdentifierType = "char";
			break;
		case C_LONG:
			szIdentifierType = "long";
			break;
		case C_VOID:
			szIdentifierType = "void";
			break;
		case C_FLOAT:
			szIdentifierType = "float";
			break;
		case C_SHORT:
			szIdentifierType = "short";
			break;
		case C_DOUBLE:
			szIdentifierType = "double";
			break;
		}

return szIdentifierType;
}


int CAIPIEditorView::WSPGetIdentifierLength( int idType)
{
	int iIdentifierLength = 0;
	
	switch( idType)
	{
		case C_INT:
			iIdentifierLength = 3;
			break;
		case C_CHAR:
			iIdentifierLength = 4;
			break;
		case C_LONG:
			iIdentifierLength = 4;
			break;
		case C_VOID:
			iIdentifierLength = 4;
			break;
		case C_FLOAT:
			iIdentifierLength = 5;
			break;
		case C_SHORT:
			iIdentifierLength = 5;
			break;
		case C_DOUBLE:
			iIdentifierLength = 6;
			break;
		}

return iIdentifierLength;
}


int CAIPIEditorView::WSPGetToken()
{
	CScintillaCtrl& rCtrl = GetCtrl();

	int tempPos = 0;
	static long intForm = 1000;  //Identifier internal form
	int count = 0;
	int symbol = rCtrl.GetCharAt(g_currentPos);
	int pos1 = 0;
	int pos2 = 0;
	
	//CString str;
	//str.Format(_T("Symbol...%d  " ), symbol);
	//AfxMessageBox(str);
		
	//Skip over white space and newline
	while( symbol == SPACE || symbol == CARRIAGE_RETURN || symbol == NEW_LINE || symbol == HORIZONTAL_TAB || symbol == VERTICAL_TAB )
	{
		if( symbol == NEW_LINE )
		{
			++g_currentLine;
		}
		
		//str.Format(_T("Pos...%d  " ), g_currentPos);
		//AfxMessageBox(str);
		++g_currentPos;

		
		symbol = rCtrl.GetCharAt(g_currentPos);
		//str.Format(_T("Space Symbol...%d  " ), symbol);
		//AfxMessageBox(str);
		
	}
		
	//Comments
	if( symbol == SLASH )
	{	
		//AfxMessageBox(_T("identifico slash 1"));
		tempPos = g_currentPos;
		
		int next_symbol = rCtrl.GetCharAt(++tempPos );
			
		//Simple comment
		if( next_symbol == SLASH )
		{
			pos1 = g_currentPos;
			//str.Format(_T("Next Symbol...%d  " ), next_symbol);
			//AfxMessageBox(str);
			//AfxMessageBox(_T("identifico slash 2"));
		
				
				
			while ( symbol != CARRIAGE_RETURN && symbol != NEW_LINE  && symbol != NUL )
			{
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				//str.Format(_T("Simple Comment Symbol...%d  " ), symbol);
				//AfxMessageBox(str);
				//str.Format(_T("Pos en Comment Simple...%d  " ), tempPos);
				//AfxMessageBox(str);
					
			}
				
			//AfxMessageBox(_T("Salio del while"));
			pos2 = tempPos;
			g_currentPos = pos2;
			
			
			m_sTokenName = _T("");
			//m_sTokenName = WSPGetText(pos1, pos2);
			if( m_sTokenName == _T("STOP_ERROR") )
			{
				AfxMessageBox(_T("The application will be close"));
				return STOP_ERROR;
			}
			
			return COMMENT;

				
		}
		//Complex comment
		else if( next_symbol == ASTERIC )
		{
			
			pos1 = g_currentPos;

			//str.Format(_T("Next Symbol...%d  " ), next_symbol);
			//AfxMessageBox(str);
			//AfxMessageBox(_T("identifico * 1"));
			

			do//find end comment
			{
				while ( symbol != ASTERIC )
				{
					if( symbol == NEW_LINE )
						++g_currentLine;

					
					++tempPos;
					symbol = rCtrl.GetCharAt(tempPos);

					if (tempPos > MAX_COMMENT_LENGTH )
					{
						return UNDEFINE;
					}
					CString str;
					str.Format(_T("Complex Comment Symbol...%d  " ), symbol);
					//AfxMessageBox(str);
					//str.Format(_T("Pos en Comment Complex...%d  " ), tempPos);
					//AfxMessageBox(str);
				}
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);

			}while( symbol != SLASH );
			
			
			//AfxMessageBox(_T("Salio del do while"));
			pos2 = ++tempPos;
			g_currentPos = pos2;

			m_sTokenName = _T("");
			/*
			m_sTokenName = WSPGetText(pos1, pos2);
			
			if( m_sTokenName == _T("STOP_ERROR") )
			{
				AfxMessageBox(_T("The application will be close"));
				return STOP_ERROR;
			}
			*/

			//str.Format(_T("Char Last Pos...%d  " ), pos2);
			//AfxMessageBox(str);
			symbol = rCtrl.GetCharAt(g_currentPos);
			if( symbol != SPACE )
			{
				--g_currentPos;
			}
			return COMMENT;
			
		}
		
			
	}


	//Check for operators
	if( isOperator( symbol ))
	{
		//AfxMessageBox(_T("Entro"));

		switch( symbol )
		{
			case EQUAL:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					m_sTokenName = WSPGetText(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return ET;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					m_sTokenName = WSPGetText(g_currentPos, g_currentPos + 1);
					return AS;
				}
				
			case EXCLAMATION:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					m_sTokenName = WSPGetText(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return NE;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					m_sTokenName = WSPGetText(g_currentPos, g_currentPos + 1);
					return NOT_OP;
				}
				
			case AMPERSAND:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == AMPERSAND )
				{
					m_sTokenName = WSPGetText(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return AND_OP;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					m_sTokenName = WSPGetText(g_currentPos, g_currentPos + 1);
					
					return AND_BIT;
				}
				
			case VERTICAL_BAR:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == VERTICAL_BAR )
				{
					m_sTokenName = WSPGetText(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return OR_OP;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					m_sTokenName = WSPGetText(g_currentPos, g_currentPos + 1);
					return OR_BIT;
				}
				
			case LESS_THAN:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					m_sTokenName = WSPGetText(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return LE;
				}
				else if ( symbol == LESS_THAN )
				{
					m_sTokenName = WSPGetText(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return RIGHT_OP;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					m_sTokenName = WSPGetText(g_currentPos, g_currentPos + 1);
					return LT;
				}
				
			case GREATER_THAN:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					m_sTokenName = WSPGetText(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return GE;
				}
				else if ( symbol == GREATER_THAN )
				{
					m_sTokenName = WSPGetText(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return LEFT_OP;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					m_sTokenName = WSPGetText(g_currentPos, g_currentPos + 1);
					return GT;
				}
				
			case PLUS_SIGN:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					//str.Format(_T("Symbol...%d  " ), symbol);
					//AfxMessageBox(str);
				
					m_sTokenName = WSPGetText(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return ADD_ASSIGN;
				}
				else if ( symbol == PLUS_SIGN )
				{
					//str.Format(_T("Symbol...%d  " ), symbol);
					//AfxMessageBox(str);
				
					m_sTokenName = WSPGetText(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return INC_OP;
				}
				else
				{
				
					//str.Format(_T("Symbol Sum...%d  " ), symbol);
					//AfxMessageBox(str);
					symbol = rCtrl.GetCharAt(g_currentPos);
					m_sTokenName = WSPGetText(g_currentPos, g_currentPos+1);
					return PLUS_SIGN;
				}
				
			case MINUS_SIGN:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					m_sTokenName = WSPGetText(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return SUB_ASSIGN;
				}
				else if ( symbol == MINUS_SIGN )
				{
					m_sTokenName = WSPGetText(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return DEC_OP;
				}
				else if ( symbol == GT )
				{
					m_sTokenName = WSPGetText(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return PTR_OP;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					m_sTokenName = WSPGetText(g_currentPos, g_currentPos +1);
					return MINUS_SIGN;
				}
				
			case ASTERIC:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					m_sTokenName = WSPGetText(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return MUL_ASSIGN;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					m_sTokenName = WSPGetText(g_currentPos, g_currentPos + 1);
					return ASTERIC;
				}
				
			case SLASH:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					m_sTokenName = WSPGetText(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return DIV_ASSIGN;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					m_sTokenName = WSPGetText(g_currentPos, g_currentPos + 1);
					return SLASH;
				}
				
			case PERCENT:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					m_sTokenName = WSPGetText(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return MOD_ASSIGN;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					m_sTokenName = WSPGetText(g_currentPos, g_currentPos + 1);
					return PERCENT;
				}
			
			case COLON:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == COLON )
				{
					m_sTokenName = WSPGetText(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return SCOPE_OP;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					m_sTokenName = WSPGetText(g_currentPos, g_currentPos + 1);
					return COLON;
				}
			
			case CARET:
				m_sTokenName = WSPGetText(g_currentPos, g_currentPos + 1);
				return XOR_BIT;
				
			
			case EQUIVALENCY:
				m_sTokenName = WSPGetText(g_currentPos, g_currentPos + 1);
				return NOT_BIT;
			
			case QUESTION:
				m_sTokenName = WSPGetText(g_currentPos, g_currentPos + 1);
				return QUESTION;

		}

		
	}


	//Check for punctuators
	if( isPunctuator(symbol) )
	{
		
		switch( symbol )
		{
					
			case SEMICOLON:
				m_sTokenName = WSPGetText(g_currentPos, g_currentPos + 1);
				return SEMICOLON;
			
			case OPEN_PARENTHESIS:
				m_sTokenName = WSPGetText(g_currentPos, g_currentPos + 1);
				return OPEN_PARENTHESIS;
			
			case CLOSE_PARENTHESIS:
				m_sTokenName = WSPGetText(g_currentPos, g_currentPos + 1);
				return CLOSE_PARENTHESIS;
			
			case OPEN_BRACKET:
				m_sTokenName = WSPGetText(g_currentPos, g_currentPos + 1);
				return OPEN_BRACKET;
			
			case CLOSE_BRACKET:
				m_sTokenName = WSPGetText(g_currentPos, g_currentPos + 1);
				return CLOSE_BRACKET;

			case OPEN_BRACE:
				m_sTokenName = WSPGetText(g_currentPos, g_currentPos + 1);
				return OPEN_BRACE;

			case CLOSE_BRACE:
				m_sTokenName = WSPGetText(g_currentPos, g_currentPos + 1);
				return CLOSE_BRACE;
			/*
			case COLON:
				m_sTokenName = WSPGetText(g_currentPos, g_currentPos + 1);
				tokz.addToken(g_currentPos, g_currentPos+1, g_currentLine, COLON, m_sTokenName, PUNCTUATOR);
				tokz.v_addToken(g_currentPos, g_currentPos+1, g_currentLine, COLON, m_sTokenName, PUNCTUATOR);
				return COLON;
			*/

			case COMMA:
				m_sTokenName = WSPGetText(g_currentPos, g_currentPos + 1);
				return COMMA;

			case PERIOD:
				m_sTokenName = WSPGetText(g_currentPos, g_currentPos + 1);
				return PERIOD;

			case NUMBER_SIGN:
				m_sTokenName = WSPGetText(g_currentPos, g_currentPos + 1);
				return NUMBER_SIGN;

			case AT_SYMBOL:
				m_sTokenName = WSPGetText(g_currentPos, g_currentPos + 1);
				return AT_SYMBOL;
		
		}
		
		
	}

	
	//Double Quoted Strings
	if( symbol == DOBLE_QUOTATION )
	{
		//AfxMessageBox(_T("entro a string"));
		
		pos1 = g_currentPos;
		++g_currentPos;
		
		symbol = rCtrl.GetCharAt(g_currentPos);
		
		//Empty string tokens
		if( symbol == DOBLE_QUOTATION )
		{
			//AfxMessageBox(_T("Entro a double quotation 2"));
			pos2 = g_currentPos + 1;
			m_sTokenName = WSPGetText(pos1+1, pos2-1);
						
			return LITERAL;
		}
		
		
		
		while(symbol != DOBLE_QUOTATION && symbol != CARRIAGE_RETURN && symbol != NUL )
		{
			count++;
			if (count >= TEXT_LENGTH -1)
			{
				return UNDEFINE;
			}

			if (tempPos > m_DocumentLength )
			{
				return UNDEFINE;
			}

			symbol = rCtrl.GetCharAt(g_currentPos);
			
			/*
			CString str;
			AfxMessageBox(_T("entro al while literal"));
			str.Format(_T("Symbol...%d  " ), symbol);
			AfxMessageBox(str);
			*/
	
			//Check for \n escape sequence
			if( symbol == BACK_SLASH )
			{
				//AfxMessageBox(_T("entro a slash"));
				
				tempPos = g_currentPos;
				++tempPos;
				int escSymbol = rCtrl.GetCharAt(tempPos);
				
				switch (escSymbol) 
				{
					//  Escape /a  alert
					case 97:
						m_sTokenName = WSPGetText(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					
					//  Escape /b backspace
					case 98:
						m_sTokenName = WSPGetText(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					//  Escape /f forward feed page
					case 102:
						m_sTokenName = WSPGetText(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					//  Escape /n  new line	
					case 110:
						m_sTokenName = WSPGetText(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					//  Escape /r  carriage return
					case 114:
						m_sTokenName = WSPGetText(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					//  Escape /t  horizontal tab
					case 116:
						m_sTokenName = WSPGetText(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					//  Escape /v  vertical tab
					case 118:
						m_sTokenName = WSPGetText(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					//  Symbol /'  single quotes
					case 27:
						m_sTokenName = WSPGetText(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					
					//  Symbol /"  double quotes
					case 34:
						m_sTokenName = WSPGetText(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					
						//  Symbol //  back slash
					case 92:
						m_sTokenName = WSPGetText(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					
					//AfxMessageBox(_T("reconocio escape"));
				}
				
				if( escSymbol != 34 )
				{
					symbol = escSymbol;
				}
			
			
			}
			
			
			++g_currentPos;
			
		}

		if( symbol == NEW_LINE || symbol == NUL )
		{
			/*
			AfxMessageBox(_T("Error carriage return"));	
			CString str;
			str.Format(_T("Symbol...%d  " ), symbol);
			AfxMessageBox(str);
			*/
			CAipi_Error err;
			err.displayGUIError(LEXICAL, LEX_ERROR, _T("Close string symbol is missed") );
			return LEX_ERROR;
		}
		
			pos2 = g_currentPos;
			m_sTokenName = WSPGetText(pos1+1, pos2-1);
			
	
		
		symbol = rCtrl.GetCharAt(g_currentPos);
		
		if( symbol != SPACE )
		{
			//AfxMessageBox(_T("No hay Espacio"));
			--g_currentPos;
		}
		
		return LITERAL;

		
	}
	

	//Single Quoted Strings
	if( symbol == SINGLE_QUOTATION )
	{
		//AfxMessageBox(_T("entro a string"));
		
		pos1 = g_currentPos;
		++g_currentPos;
		
		symbol = rCtrl.GetCharAt(g_currentPos);
		//Empty char tokens
		if( symbol == SINGLE_QUOTATION )
		{
			//AfxMessageBox(_T("Entro a single quotation 2"));
			pos2 = g_currentPos + 1;
			m_sTokenName = WSPGetText(pos1, pos2);
						
			return LITERAL;
		}
		
		
		while(symbol != SINGLE_QUOTATION && symbol != CARRIAGE_RETURN && symbol != NUL )
		{
			symbol = rCtrl.GetCharAt(g_currentPos);
			
			//str.Format(_T("Symbol...%d  " ), symbol);
			//AfxMessageBox(str);
	
			//Check for \n escape sequence
			if( symbol == BACK_SLASH )
			{
				//AfxMessageBox(_T("entro a slash"));
				
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				
				switch (symbol) 
				{
					//  Escape /a  alert
					case 97:
						m_sTokenName = WSPGetText(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					
					//  Escape /b backspace
					case 98:
						m_sTokenName = WSPGetText(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					//  Escape /f forward feed page
					case 102:
						m_sTokenName = WSPGetText(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					//  Escape /n  new line	
					case 110:
						m_sTokenName = WSPGetText(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					//  Escape /r  carriage return
					case 114:
						m_sTokenName = WSPGetText(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					//  Escape /t  horizontal tab
					case 116:
						m_sTokenName = WSPGetText(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					//  Escape /v  vertical tab
					case 118:
						m_sTokenName = WSPGetText(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					//  Symbol /'  single quotes
					case 27:
						m_sTokenName = WSPGetText(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					
					//  Symbol /"  double quotes
					case 34:
						m_sTokenName = WSPGetText(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					
						//  Symbol //  back slash
					case 92:
						m_sTokenName = WSPGetText(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					
					//AfxMessageBox(_T("reconocio escape"));
				}
			}
			++g_currentPos;
		}
		if( symbol == NEW_LINE || symbol == NUL )
		{
				CAipi_Error err;
				err.displayGUIError(LEXICAL, LEX_ERROR, _T("Close string symbol is missed") );
				return LEX_ERROR;
		}
		
			
		pos2 = g_currentPos;
		

		m_sTokenName = WSPGetText(pos1, pos2);
				
		symbol = rCtrl.GetCharAt(g_currentPos);
		if( symbol != SPACE )
		{
			--g_currentPos;
		}
		
		return LITERAL;

		
	}



	//Numbers (Natural and Real )
	if( isDigit(symbol)  )
	{
		pos1 = g_currentPos;
		g_currentDigit_Type = NAT_NUMBER;
		int countPeriod = 0;

		while( isDigit(symbol) || symbol == PERIOD )
		{
			++g_currentPos;
			//str.Format(_T("Pos en Nat Number...%d  " ), g_currentPos);
			//AfxMessageBox(str);

			symbol = rCtrl.GetCharAt(g_currentPos);
			//str.Format(_T("Nat Num Symbol...%d  " ), symbol);
			//AfxMessageBox(str);
			
			if( symbol == PERIOD )
			{
				g_currentDigit_Type = REAL_NUMBER;
				++countPeriod;
			}
			
		}

		if( countPeriod > 1 )
		{
			CAipi_Error err;
			err.displayGUIError(LEXICAL, LEX_ERROR, _T("Period symbol is repeated") );
			return LEX_ERROR;
		}
		
		pos2 = g_currentPos;
		m_sTokenName = WSPGetText(pos1, pos2);
		
		symbol = rCtrl.GetCharAt(g_currentPos);
		if( symbol != SPACE )
		{
			--g_currentPos;
		}
		return DIGIT;
	}

	
	//Identifiers and KeyWords
	if( isAlphabetic(symbol) || symbol == UNDERSCORE )
	{
		pos1 = g_currentPos;
		
		while( isAlphaNumeric(symbol))
		{
			++g_currentPos;
			CString str;
			//str.Format(_T("Pos en Identifier...%d  " ), g_currentPos);
			//AfxMessageBox(str);

			symbol = rCtrl.GetCharAt(g_currentPos);
			//str.Format(_T("Id Symbol...%d  " ), symbol);
			//AfxMessageBox(str);
			
		}
		
		
		pos2 = g_currentPos;
		symbol = rCtrl.GetCharAt(g_currentPos);
		if( symbol != SPACE )
		{
			--g_currentPos;
		}
		
		m_sTokenName = WSPGetText(pos1, pos2);
		
		if( m_sTokenName == _T("STOP_ERROR") )
		{
			return STOP_ERROR;
		}
		CString str;
		//str.Format(_T("Id Symbol...%d  " ), symbol);
		//AfxMessageBox(str);
		//AfxMessageBox(m_sTokenName);
			
		//Check type token
		if( isTypeName(m_sTokenName) )
		{
			return IDENTIFIER_TYPE;
		}
		else if( m_sTokenName == _T("RULE") )
		{
			return AIPI_RULE;
		}
		else if( m_sTokenName == _T("CLASS") )
		{
			return AIPI_CLASS;
		}
		else if( m_sTokenName == _T("SQLQUERY") )
		{
			return AIPI_SQLQUERY;
		}
		else if( m_sTokenName == _T("function") )
		{
			return JS_FUNCTION;
		}
		else if( m_sTokenName == _T("Function") || m_sTokenName == _T("FUNCTION") )
		{
			return VBS_FUNCTION;
		}
		else
		{
			return IDENTIFIER;
		}

		
	}

		
	if (symbol == NUL )
	{
		//AfxMessageBox(_T("Fin del archivo"));
		return _TEOF;
		
	}

		
return UNDEFINE;
}




int CAIPIEditorView::WSPParseVariable(long nStartSel, long nEndSel )
{
	//Check for variable identifier
	int match = NOT_FOUND;
	g_currentPos = nStartSel;

	m_lookahead = WSPGetToken();
	match = WSPMatchToken(IDENTIFIER_TYPE);
	
	if( match != NOT_FOUND )
	{
		//AfxMessageBox(_T("Hola1"));
		m_sCurrentVariableName  = m_sTokenName;
		match = WSPMatchToken(IDENTIFIER);
		
		if( match != AIPI_ERROR )
		{
	
			int match = WSPMatchToken(SEMICOLON);
			
			if( match != AIPI_ERROR )
			{
				//AfxMessageBox(_T("VARIABLE DECLARATION DETECTED!!!"));
				//Checking limit position of parser analysis
					if( g_currentPos < nEndSel )
					{
						return AIPI_ERROR;
					}
					else
					{
						return P_SUCCESS;
					}
				
			}
			
			//--g_currentPos;	
			//AfxMessageBox(_T("Equal"));
			//Check for variable asignation
			match = WSPMatchToken(EQUAL);
			if( match != AIPI_ERROR )
			{
				
				//AfxMessageBox(_T("Digit"));
				match = WSPMatchToken(DIGIT);
				if( match != AIPI_ERROR )
				{
					//AfxMessageBox(_T("Semicolon"));
					match = WSPMatchToken(SEMICOLON);
					if( match != AIPI_ERROR )
					{
						//AfxMessageBox(_T("VARIABLE DECLARATION DETECTED!!!"));
						//Checking limit position of parser analysis
						if( g_currentPos < nEndSel )
						{
							return AIPI_ERROR;
						}
						else
						{
							return P_SUCCESS;
						}
					}
				}
				else
				{
					//--g_currentPos;
					match = WSPMatchToken(LITERAL);
					if( match != AIPI_ERROR )
					{
						match = WSPMatchToken(SEMICOLON);
						if( match != AIPI_ERROR )
						{
							//AfxMessageBox(_T("VARIABLE DECLARATION DETECTED!!!"));
							//Checking limit position of parser analysis
							if( g_currentPos < nEndSel )
							{
								return AIPI_ERROR;
							}
							else
							{
								return P_SUCCESS;
							}
						}
					
					}
								
				}
			}
			else
			{
				//AfxMessageBox(_T("ERROR ASIGNATION SYMBOL Not Found!!!"));
				return AIPI_ERROR;
			}
		}
		else
		{
			//AfxMessageBox(_T("ERROR VARIABLE NAME Not Found!!!"));
			return AIPI_ERROR;
		}
	
	}
	else
	{
		//AfxMessageBox(_T("ERROR TYPE KEYWORD Not Found!!!"));
		return AIPI_ERROR;
	}



return NOT_FOUND;

}




int CAIPIEditorView::WSPParseVariableEdit(long nStartSel, long nEndSel, int type, int typelen )
{
	//Check for variable identifier
	
	int match = NOT_FOUND;
	g_currentPos = nStartSel + typelen;
	CString str;
	
	m_lookahead = type;
	//CString str;
	match = WSPMatchToken(type);
	
	if( match != NOT_FOUND )
	{
		//AfxMessageBox(_T("Hola1"));
		m_sCurrentVariableName  = m_sTokenName;
		match = WSPMatchToken(IDENTIFIER);
		
		if( match != AIPI_ERROR )
		{
	
			int match = WSPMatchToken(SEMICOLON);
			
			if( match != AIPI_ERROR )
			{
				//AfxMessageBox(_T("VARIABLE DECLARATION DETECTED!!!"));
				//Checking limit position of parser analysis
					if( g_currentPos < nEndSel )
					{
						return AIPI_ERROR;
					}
					else
					{
						return P_SUCCESS;
					}
				
			}
			
			//--g_currentPos;	
			//AfxMessageBox(_T("Equal"));
			//Check for variable asignation
			match = WSPMatchToken(EQUAL);
			if( match != AIPI_ERROR )
			{
				
				//AfxMessageBox(_T("Digit"));
				match = WSPMatchToken(DIGIT);
				if( match != AIPI_ERROR )
				{
					//AfxMessageBox(_T("Semicolon"));
					match = WSPMatchToken(SEMICOLON);
					if( match != AIPI_ERROR )
					{
						//AfxMessageBox(_T("VARIABLE DECLARATION DETECTED!!!"));
						//Checking limit position of parser analysis
						if( g_currentPos < nEndSel )
						{
							return AIPI_ERROR;
						}
						else
						{
							return P_SUCCESS;
						}
					}
				}
				else
				{
					//--g_currentPos;
					match = WSPMatchToken(LITERAL);
					if( match != AIPI_ERROR )
					{
						match = WSPMatchToken(SEMICOLON);
						if( match != AIPI_ERROR )
						{
							//AfxMessageBox(_T("VARIABLE DECLARATION DETECTED!!!"));
							//Checking limit position of parser analysis
							if( g_currentPos < nEndSel )
							{
								return AIPI_ERROR;
							}
							else
							{
								return P_SUCCESS;
							}
						}
					
					}
								
				}
			}
			else
			{
				//AfxMessageBox(_T("ERROR ASIGNATION SYMBOL Not Found!!!"));
				return AIPI_ERROR;
			}
		}
		else
		{
			//AfxMessageBox(_T("ERROR VARIABLE NAME Not Found!!!"));
			return AIPI_ERROR;
		}
	
	}
	else
	{
		//AfxMessageBox(_T("ERROR TYPE KEYWORD Not Found!!!"));
		return AIPI_ERROR;
	}



return NOT_FOUND;

}

int CAIPIEditorView::WSPParseVBSFunction( long nStartSel, long nEndSel )
{
	int match = NOT_FOUND;
	g_currentPos = nStartSel;
	CString str;
	m_lookahead = WSPGetToken();
	match = WSPMatchToken(VBS_FUNCTION);
	
	if( match != NOT_FOUND )
	{
		//AfxMessageBox(_T("tipo"));
		m_sCurrentFunctionName  = m_sTokenName;
		match = WSPMatchToken(IDENTIFIER);
		if( match != AIPI_ERROR )
		{
			//AfxMessageBox(m_sCurrentFunctionName);
			match = WSPMatchToken(OPEN_PARENTHESIS);
			if( match != AIPI_ERROR )
			{
				//AfxMessageBox(_T("open parentesis"));
				while(m_lookahead != CLOSE_PARENTHESIS && g_currentPos <= nEndSel )
				{
					++g_currentPos;
					m_lookahead = WSPGetToken();
					//str.Format(_T("Look ahead...%d  " ), m_lookahead);
					//AfxMessageBox(str);
					
					
					//Symbols not allowed between the parenthesis
					switch( m_lookahead)
					{
					case OPEN_BRACE:
						return AIPI_ERROR;
					
					case CLOSE_BRACE:
						return AIPI_ERROR;
					
					case OPEN_PARENTHESIS:
						return AIPI_ERROR;
					
					case NUL:
						return AIPI_ERROR;
					}
													
				}
				
				//str.Format(_T("g_currentPos...%d  " ), g_currentPos);
				//AfxMessageBox(str);
				
					
				match = WSPMatchToken(CLOSE_PARENTHESIS);
				if( match != AIPI_ERROR )
				{
					//Checking limit position of parser analysis
					if( g_currentPos < nEndSel )
					{
						return AIPI_ERROR;
					}
					else
					{
						//AfxMessageBox(_T("close parentesis"));
						return P_SUCCESS;
					}
				}
				else
				{
					//AfxMessageBox(_T("ERROR CLOSE PARENTHESIS Not Found!!!"));
					return AIPI_ERROR;
				}
			}
			else
			{
				//AfxMessageBox(_T("ERROR OPEN PARENTHESIS Not Found!!!"));
				return AIPI_ERROR;
			}
		}
		else
		{
			//AfxMessageBox(_T("ERROR FUNCTION NAME Not Found!!!"));
			return AIPI_ERROR;
		}
	}
	else
	{
		//AfxMessageBox(_T("ERROR TYPE KEYWORD Not Found!!!"));
		return AIPI_ERROR;
	}
	
return NOT_FOUND;

}


int CAIPIEditorView::WSPParseVBSFunctionEdit( long nStartSel, long nEndSel )
{
	int match = NOT_FOUND;
	g_currentPos = nStartSel + 8;
	CString str;
	
	m_lookahead = VBS_FUNCTION;
	//CString str;
	
	match = WSPMatchToken(VBS_FUNCTION);
	
	if( match != NOT_FOUND )
	{
		//AfxMessageBox(_T("tipo"));
		m_sCurrentFunctionName  = m_sTokenName;
		match = WSPMatchToken(IDENTIFIER);
		if( match != AIPI_ERROR )
		{
			//AfxMessageBox(m_sCurrentFunctionName);
			
			match = WSPMatchToken(OPEN_PARENTHESIS);
			if( match != AIPI_ERROR )
			{
				//AfxMessageBox(_T("open parentesis"));
				while(m_lookahead != CLOSE_PARENTHESIS && g_currentPos <= nEndSel )
				{
					++g_currentPos;
					m_lookahead = WSPGetToken();
					//str.Format(_T("Look ahead...%d  " ), m_lookahead);
					//AfxMessageBox(str);
					
					
					//Symbols not allowed between the parenthesis
					switch( m_lookahead)
					{
					case OPEN_BRACE:
						return AIPI_ERROR;
					
					case CLOSE_BRACE:
						return AIPI_ERROR;
					
					case OPEN_PARENTHESIS:
						return AIPI_ERROR;
					
					case NUL:
						return AIPI_ERROR;
					}
													
				}
				
				match = WSPMatchToken(CLOSE_PARENTHESIS);
				if( match != AIPI_ERROR )
				{
					//AfxMessageBox(_T("close parentesis"));
					//Checking limit position of parser analysis
					if( g_currentPos < nEndSel )
					{
						return AIPI_ERROR;
					}
					else
					{
						return P_SUCCESS;
					}
				}
				else
				{
					//AfxMessageBox(_T("ERROR CLOSE PARENTHESIS Not Found!!!"));
					return AIPI_ERROR;
				}
			}
			else
			{
				//AfxMessageBox(_T("ERROR OPEN PARENTHESIS Not Found!!!"));
				return AIPI_ERROR;
			}
		}
		else
		{
			//AfxMessageBox(_T("ERROR FUNCTION NAME Not Found!!!"));
			return AIPI_ERROR;
		}
	}
	else
	{
		//AfxMessageBox(_T("ERROR TYPE KEYWORD Not Found!!!"));
		return AIPI_ERROR;
	}
	
return NOT_FOUND;

}


















int CAIPIEditorView::WSPParseJSFunction( long nStartSel, long nEndSel )
{
	int match = NOT_FOUND;
	g_currentPos = nStartSel;
	CString str;
	m_lookahead = WSPGetToken();
	match = WSPMatchToken(JS_FUNCTION);
	
	if( match != NOT_FOUND )
	{
		//AfxMessageBox(_T("tipo"));
		m_sCurrentFunctionName  = m_sTokenName;
		match = WSPMatchToken(IDENTIFIER);
		if( match != AIPI_ERROR )
		{
			//AfxMessageBox(m_sCurrentFunctionName);
			match = WSPMatchToken(OPEN_PARENTHESIS);
			if( match != AIPI_ERROR )
			{
				//AfxMessageBox(_T("open parentesis"));
				while(m_lookahead != CLOSE_PARENTHESIS && g_currentPos <= nEndSel )
				{
					++g_currentPos;
					m_lookahead = WSPGetToken();
					//str.Format(_T("Look ahead...%d  " ), m_lookahead);
					//AfxMessageBox(str);
					
					
					//Symbols not allowed between the parenthesis
					switch( m_lookahead)
					{
					case OPEN_BRACE:
						return AIPI_ERROR;
					
					case CLOSE_BRACE:
						return AIPI_ERROR;
					
					case OPEN_PARENTHESIS:
						return AIPI_ERROR;
					
					case NUL:
						return AIPI_ERROR;
					}
													
				}
				
				//str.Format(_T("g_currentPos...%d  " ), g_currentPos);
				//AfxMessageBox(str);
				
					
				match = WSPMatchToken(CLOSE_PARENTHESIS);
				if( match != AIPI_ERROR )
				{
					//Checking limit position of parser analysis
					if( g_currentPos < nEndSel )
					{
						return AIPI_ERROR;
					}
					else
					{
						//AfxMessageBox(_T("close parentesis"));
						return P_SUCCESS;
					}
				}
				else
				{
					//AfxMessageBox(_T("ERROR CLOSE PARENTHESIS Not Found!!!"));
					return AIPI_ERROR;
				}
			}
			else
			{
				//AfxMessageBox(_T("ERROR OPEN PARENTHESIS Not Found!!!"));
				return AIPI_ERROR;
			}
		}
		else
		{
			//AfxMessageBox(_T("ERROR FUNCTION NAME Not Found!!!"));
			return AIPI_ERROR;
		}
	}
	else
	{
		//AfxMessageBox(_T("ERROR TYPE KEYWORD Not Found!!!"));
		return AIPI_ERROR;
	}
	
return NOT_FOUND;

}


int CAIPIEditorView::WSPParseJSFunctionEdit( long nStartSel, long nEndSel )
{
	int match = NOT_FOUND;
	g_currentPos = nStartSel + 8;
	CString str;
	
	m_lookahead = JS_FUNCTION;
	//CString str;
	
	match = WSPMatchToken(JS_FUNCTION);
	
	if( match != NOT_FOUND )
	{
		//AfxMessageBox(_T("tipo"));
		m_sCurrentFunctionName  = m_sTokenName;
		match = WSPMatchToken(IDENTIFIER);
		if( match != AIPI_ERROR )
		{
			//AfxMessageBox(m_sCurrentFunctionName);
			
			match = WSPMatchToken(OPEN_PARENTHESIS);
			if( match != AIPI_ERROR )
			{
				//AfxMessageBox(_T("open parentesis"));
				while(m_lookahead != CLOSE_PARENTHESIS && g_currentPos <= nEndSel )
				{
					++g_currentPos;
					m_lookahead = WSPGetToken();
					//str.Format(_T("Look ahead...%d  " ), m_lookahead);
					//AfxMessageBox(str);
					
					
					//Symbols not allowed between the parenthesis
					switch( m_lookahead)
					{
					case OPEN_BRACE:
						return AIPI_ERROR;
					
					case CLOSE_BRACE:
						return AIPI_ERROR;
					
					case OPEN_PARENTHESIS:
						return AIPI_ERROR;
					
					case NUL:
						return AIPI_ERROR;
					}
													
				}
				
				match = WSPMatchToken(CLOSE_PARENTHESIS);
				if( match != AIPI_ERROR )
				{
					//AfxMessageBox(_T("close parentesis"));
					//Checking limit position of parser analysis
					if( g_currentPos < nEndSel )
					{
						return AIPI_ERROR;
					}
					else
					{
						return P_SUCCESS;
					}
				}
				else
				{
					//AfxMessageBox(_T("ERROR CLOSE PARENTHESIS Not Found!!!"));
					return AIPI_ERROR;
				}
			}
			else
			{
				//AfxMessageBox(_T("ERROR OPEN PARENTHESIS Not Found!!!"));
				return AIPI_ERROR;
			}
		}
		else
		{
			//AfxMessageBox(_T("ERROR FUNCTION NAME Not Found!!!"));
			return AIPI_ERROR;
		}
	}
	else
	{
		//AfxMessageBox(_T("ERROR TYPE KEYWORD Not Found!!!"));
		return AIPI_ERROR;
	}
	
return NOT_FOUND;

}





int CAIPIEditorView::WSPParseFunction( long nStartSel, long nEndSel )
{
	int match = NOT_FOUND;
	g_currentPos = nStartSel;
	CString str;
	m_lookahead = WSPGetToken();
	match = WSPMatchToken(IDENTIFIER_TYPE);
	
	if( match != NOT_FOUND )
	{
		//AfxMessageBox(_T("tipo"));
		m_sCurrentFunctionName  = m_sTokenName;
		match = WSPMatchToken(IDENTIFIER);
		if( match != AIPI_ERROR )
		{
			//AfxMessageBox(m_sCurrentFunctionName);
			match = WSPMatchToken(OPEN_PARENTHESIS);
			if( match != AIPI_ERROR )
			{
				//AfxMessageBox(_T("open parentesis"));
				while(m_lookahead != CLOSE_PARENTHESIS && g_currentPos <= nEndSel )
				{
					++g_currentPos;
					m_lookahead = WSPGetToken();
					//str.Format(_T("Look ahead...%d  " ), m_lookahead);
					//AfxMessageBox(str);
					
					
					//Symbols not allowed between the parenthesis
					switch( m_lookahead)
					{
					case OPEN_BRACE:
						return AIPI_ERROR;
					
					case CLOSE_BRACE:
						return AIPI_ERROR;
					
					case OPEN_PARENTHESIS:
						return AIPI_ERROR;
					
					case NUL:
						return AIPI_ERROR;
					}
													
				}
				
				//str.Format(_T("g_currentPos...%d  " ), g_currentPos);
				//AfxMessageBox(str);
				
					
				match = WSPMatchToken(CLOSE_PARENTHESIS);
				if( match != AIPI_ERROR )
				{
					//Checking limit position of parser analysis
					if( g_currentPos < nEndSel )
					{
						return AIPI_ERROR;
					}
					else
					{
						//AfxMessageBox(_T("close parentesis"));
						return P_SUCCESS;
					}
				}
				else
				{
					//AfxMessageBox(_T("ERROR CLOSE PARENTHESIS Not Found!!!"));
					return AIPI_ERROR;
				}
			}
			else
			{
				//AfxMessageBox(_T("ERROR OPEN PARENTHESIS Not Found!!!"));
				return AIPI_ERROR;
			}
		}
		else
		{
			//AfxMessageBox(_T("ERROR FUNCTION NAME Not Found!!!"));
			return AIPI_ERROR;
		}
	}
	else
	{
		//AfxMessageBox(_T("ERROR TYPE KEYWORD Not Found!!!"));
		return AIPI_ERROR;
	}
	
return NOT_FOUND;

}


int CAIPIEditorView::WSPParseFunctionEdit( long nStartSel, long nEndSel, int type, int typelen )
{
	int match = NOT_FOUND;
	g_currentPos = nStartSel + typelen;
	CString str;
	
	m_lookahead = type;
	//CString str;
	
	match = WSPMatchToken(type);
	
	if( match != NOT_FOUND )
	{
		//AfxMessageBox(_T("tipo"));
		m_sCurrentFunctionName  = m_sTokenName;
		match = WSPMatchToken(IDENTIFIER);
		if( match != AIPI_ERROR )
		{
			//AfxMessageBox(m_sCurrentFunctionName);
			
			match = WSPMatchToken(OPEN_PARENTHESIS);
			if( match != AIPI_ERROR )
			{
				//AfxMessageBox(_T("open parentesis"));
				while(m_lookahead != CLOSE_PARENTHESIS && g_currentPos <= nEndSel )
				{
					++g_currentPos;
					m_lookahead = WSPGetToken();
					//str.Format(_T("Look ahead...%d  " ), m_lookahead);
					//AfxMessageBox(str);
					
					
					//Symbols not allowed between the parenthesis
					switch( m_lookahead)
					{
					case OPEN_BRACE:
						return AIPI_ERROR;
					
					case CLOSE_BRACE:
						return AIPI_ERROR;
					
					case OPEN_PARENTHESIS:
						return AIPI_ERROR;
					
					case NUL:
						return AIPI_ERROR;
					}
													
				}
				
				match = WSPMatchToken(CLOSE_PARENTHESIS);
				if( match != AIPI_ERROR )
				{
					//AfxMessageBox(_T("close parentesis"));
					//Checking limit position of parser analysis
					if( g_currentPos < nEndSel )
					{
						return AIPI_ERROR;
					}
					else
					{
						return P_SUCCESS;
					}
				}
				else
				{
					//AfxMessageBox(_T("ERROR CLOSE PARENTHESIS Not Found!!!"));
					return AIPI_ERROR;
				}
			}
			else
			{
				//AfxMessageBox(_T("ERROR OPEN PARENTHESIS Not Found!!!"));
				return AIPI_ERROR;
			}
		}
		else
		{
			//AfxMessageBox(_T("ERROR FUNCTION NAME Not Found!!!"));
			return AIPI_ERROR;
		}
	}
	else
	{
		//AfxMessageBox(_T("ERROR TYPE KEYWORD Not Found!!!"));
		return AIPI_ERROR;
	}
	
return NOT_FOUND;

}


int CAIPIEditorView::WSPAddVariable( long pos, bool commentFlag )
{
		
	//AfxMessageBox(_T("ADD VARIABLE"));
	
	LPSTR szSemiColon = ";";
		
	int r = AIPI_ERROR;
	
	CString str;
	//str.Format(_T("Modification Type... %d"), m_iModificationType);
	//AfxMessageBox(str);	


	CScintillaCtrl& rCtrl = GetCtrl();
		
	long posSemiColon = WSPSearchToken( pos -1, m_DocumentLength, szSemiColon);
	long posIdType = WSPSearchNearestIdType(posSemiColon, 0);
	
	/*
	str.Format(_T("Pos IdType...%d  " ), posIdType);
	AfxMessageBox(str);
	str.Format(_T("Pos SemiColon...%d  " ), posSemiColon);
	AfxMessageBox(str);
	AfxMessageBox(m_sCurrentType);
	*/
	if( posIdType != NOT_FOUND && posSemiColon != NOT_FOUND )
	{
		if( pos >= posIdType && pos <= posSemiColon )
		{
			//AfxMessageBox(_T("Rango"));
			
			r = WSPParseVariable( posIdType -1, posSemiColon);
			
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				//AfxMessageBox(_T("In"));
				int typeLength = m_sCurrentType.GetLength();
				//Check for comments
				if( commentFlag )
				{
					bool lnComment = WSPCheckLineComment( posIdType, posIdType + typeLength);
					if( lnComment )
					{
						m_bFlagEditVariable = false;
						return SIMPLE_COMMENT;
					}
					bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posIdType );
					if( blkComment )
					{
						m_bFlagEditVariable = false;
						return COMPLEX_COMMENT;
					}
				}

				CString sVariableName = WSPGetText(posIdType + typeLength, posSemiColon);
				if( sVariableName == _T("OVERLOAD" ))
				{
					return AIPI_ERROR;
				}
				
				if( sVariableName != _T("EMPTY") )
				{
					sVariableName.TrimRight();
					sVariableName.TrimLeft();

					CString sVariableParameter = _T("");
					//CString sFullRuleName = m_sRuleName + sRuleParameter; 
					//AfxMessageBox(m_sTokenName);
					//r = WSPAddNodeTree1(sVariableName, sVariableParameter, 6);
					r = WSPAddNodeTypeTree1(sVariableName, sVariableParameter, 8, AIPI_VARIABLE);	
					//CWorkspaceTabView tab;
					//tab.printWSPTree1();
					
				}
			}
		
		}
	}
	

return r;

}


int CAIPIEditorView::WSPDeleteVariable( long pos, bool commentFlag )
{
	//AfxMessageBox(_T("DELETE VARIABLE"));
	
	LPSTR szSemiColon = ";";
	
	int r = AIPI_ERROR;
	
	CString str;
	//str.Format(_T("Modification Type... %d"), m_iModificationType);
	//AfxMessageBox(str);	


	CScintillaCtrl& rCtrl = GetCtrl();

	long posSemiColon = WSPSearchToken( pos -1, m_DocumentLength, szSemiColon);
	long posIdType = WSPSearchNearestIdType(posSemiColon, 0);	
	
	
	/*
	str.Format(_T("Pos IdType...%d  " ), posIdType);
	AfxMessageBox(str);
	str.Format(_T("Pos SemiColon...%d  " ), posSemiColon);
	AfxMessageBox(str);
	*/
	
	if( posIdType != NOT_FOUND && posSemiColon != NOT_FOUND )
	{
		//AfxMessageBox(_T("hello"));
		
		if( pos >= posIdType && pos <= posSemiColon )
		{
			r = WSPParseVariable( posIdType -1, posSemiColon);
			
				//AfxMessageBox(_T("hello2"));
		
			
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				//AfxMessageBox(_T("In"));				
				int typeLength = m_sCurrentType.GetLength();

				//Check for comments
				if( commentFlag )
				{
					bool lnComment = WSPCheckLineComment( posIdType, posIdType + typeLength);
					if( lnComment )
					{
						m_bFlagEditVariable = false;
						return SIMPLE_COMMENT;
					}
					bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posIdType );
					if( blkComment )
					{
						m_bFlagEditVariable = false;
						return COMPLEX_COMMENT;
					}
				}

				CString sVariableName = WSPGetText(posIdType + typeLength, posSemiColon);
				if( sVariableName == _T("OVERLOAD" ))
				{
					return AIPI_ERROR;
				}

				
				if( sVariableName != _T("EMPTY") )
				{
					sVariableName.TrimRight();
					sVariableName.TrimLeft();
					r = WSPDeleteNodeTree1(sVariableName);
					
				}
			}
		
		}
	}
	

return r;	
	

}

int CAIPIEditorView::WSPAddQuery( long pos, bool commentFlag )
{
		
	//AfxMessageBox(_T("ADD VARIABLE"));
	
	LPSTR szEqual = "=";
	LPSTR szKeyWord = "SQLQUERY";
		
	int r = AIPI_ERROR;
	
	CString str;
	//str.Format(_T("Modification Type... %d"), m_iModificationType);
	//AfxMessageBox(str);	


	CScintillaCtrl& rCtrl = GetCtrl();
		
	long posEqual = WSPSearchToken( pos -1, m_DocumentLength, szEqual);
	long posQuery = WSPSearchToken(posEqual, 0, szKeyWord);
	
	/*
	str.Format(_T("Pos Query...%d  " ), posQuery);
	AfxMessageBox(str);
	str.Format(_T("Pos Equal..%d  " ), posEqual);
	AfxMessageBox(str);
	//AfxMessageBox(m_sCurrentType);
	*/
	if( posQuery != NOT_FOUND && posEqual != NOT_FOUND )
	{
		if( pos >= posQuery && pos <= posEqual )
		{
			//AfxMessageBox(_T("Rango"));
			
			r = WSPParseQuery( posQuery -1, posEqual);
			
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				//AfxMessageBox(_T("In"));
				//Check for comments
				if( commentFlag )
				{
					bool lnComment = WSPCheckLineComment( posQuery, posQuery + 8);
					if( lnComment )
					{
						m_bFlagEditQuery = false;
						return SIMPLE_COMMENT;
					}
					bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posQuery );
					if( blkComment )
					{
						m_bFlagEditQuery = false;
						return COMPLEX_COMMENT;
					}
				}

				CString sQueryName = WSPGetText(posQuery + 8, posEqual);
				if( sQueryName == _T("OVERLOAD" ))
				{
					return AIPI_ERROR;
				}
				
				if( sQueryName != _T("EMPTY") )
				{
					sQueryName.TrimRight();
					sQueryName.TrimLeft();
					CString sQueryParameter = _T("");
					//CString sFullRuleName = m_sRuleName + sRuleParameter; 
					//AfxMessageBox(m_sTokenName);
					//r = WSPAddNodeTree1(sClassName, sClassParameter, 8);
					r = WSPAddNodeTypeTree1(sQueryName, sQueryParameter, 4, AIPI_QUERY);	
					//CWorkspaceTabView tab;
					//tab.printWSPTree1();
					
				}
			}
		
		}
	}
	

return r;

}

int CAIPIEditorView::WSPDeleteQuery( long pos, bool commentFlag )
{
	//AfxMessageBox(_T("DELETE VARIABLE"));
	
	LPSTR szEqual = "=";
	LPSTR szKeyWord = "SQLQUERY";
	
	int r = AIPI_ERROR;
	
	CString str;
	//str.Format(_T("Modification Type... %d"), m_iModificationType);
	//AfxMessageBox(str);	


	CScintillaCtrl& rCtrl = GetCtrl();

	long posEqual = WSPSearchToken( pos -1, m_DocumentLength, szEqual);
	long posQuery = WSPSearchToken(posEqual, 0, szKeyWord);	
	
	
	/*
	str.Format(_T("Pos Query...%d  " ), posQuery);
	AfxMessageBox(str);
	str.Format(_T("Pos Equal...%d  " ), posEqual);
	AfxMessageBox(str);
	*/
	
	if( posQuery != NOT_FOUND && posEqual != NOT_FOUND )
	{
		//AfxMessageBox(_T("hello"));
		
		if( pos >= posQuery && pos <= posEqual )
		{
			r = WSPParseQuery( posQuery -1, posEqual);
			
				//AfxMessageBox(_T("hello2"));
		
			
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				
				//Check for comments
				if( commentFlag )
				{
					bool lnComment = WSPCheckLineComment( posQuery, posQuery + 8);
					if( lnComment )
					{
						m_bFlagEditQuery = false;
						return SIMPLE_COMMENT;
					}
					bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posQuery );
					if( blkComment )
					{
						m_bFlagEditQuery = false;
						return COMPLEX_COMMENT;
					}
				}

				CString sQueryName = WSPGetText(posQuery + 8, posEqual);
				if( sQueryName == _T("OVERLOAD" ))
				{
					return AIPI_ERROR;
				}
				

				if( sQueryName != _T("EMPTY") )
				{
					sQueryName.TrimRight();
					sQueryName.TrimLeft();
					r = WSPDeleteNodeTree1(sQueryName);
					
				}
			}
		
		}
	}
	

return r;	
	

}




int CAIPIEditorView::WSPAddClass( long pos, bool commentFlag )
{
		
	//AfxMessageBox(_T("ADD VARIABLE"));
	
	LPSTR szOpenBrace = "{";
	LPSTR szKeyWord = "CLASS";
		
	int r = AIPI_ERROR;
	
	CString str;
	//str.Format(_T("Modification Type... %d"), m_iModificationType);
	//AfxMessageBox(str);	


	CScintillaCtrl& rCtrl = GetCtrl();
		
	long posOpenBrace = WSPSearchToken( pos -1, m_DocumentLength, szOpenBrace);
	long posClass = WSPSearchToken(posOpenBrace, 0, szKeyWord);
	
	/*
	str.Format(_T("Pos Class...%d  " ), posClass);
	AfxMessageBox(str);
	str.Format(_T("Pos OpenBrace...%d  " ), posOpenBrace);
	AfxMessageBox(str);
	AfxMessageBox(m_sCurrentType);
	*/
	if( posClass != NOT_FOUND && posOpenBrace != NOT_FOUND )
	{
		if( pos >= posClass && pos <= posOpenBrace )
		{
			//AfxMessageBox(_T("Rango"));
			
			r = WSPParseClass( posClass -1, posOpenBrace);
			
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				//AfxMessageBox(_T("In"));
				//Check for comments
				if( commentFlag )
				{
					bool lnComment = WSPCheckLineComment( posClass, posClass + 5);
					if( lnComment )
					{
						m_bFlagEditClass = false;
						return SIMPLE_COMMENT;
					}
					bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posClass );
					if( blkComment )
					{
						m_bFlagEditClass = false;
						return COMPLEX_COMMENT;
					}
				}

				CString sClassName = WSPGetText(posClass + 5, posOpenBrace);
				if( sClassName == _T("OVERLOAD" ))
				{
					return AIPI_ERROR;
				}
				
				if( sClassName != _T("EMPTY") )
				{
					sClassName.TrimRight();
					sClassName.TrimLeft();
					CString sClassParameter = _T("");
					//CString sFullRuleName = m_sRuleName + sRuleParameter; 
					//AfxMessageBox(m_sTokenName);
					//r = WSPAddNodeTree1(sClassName, sClassParameter, 8);
					r = WSPAddNodeTypeTree1(sClassName, sClassParameter, 14, AIPI_CLASS);	
					//CWorkspaceTabView tab;
					//tab.printWSPTree1();
					
				}
			}
		
		}
	}
	

return r;

}











int CAIPIEditorView::WSPDeleteClass( long pos, bool commentFlag )
{
	//AfxMessageBox(_T("DELETE VARIABLE"));
	
	LPSTR szOpenBrace = "{";
	LPSTR szKeyWord = "CLASS";
	
	int r = AIPI_ERROR;
	
	CString str;
	//str.Format(_T("Modification Type... %d"), m_iModificationType);
	//AfxMessageBox(str);	


	CScintillaCtrl& rCtrl = GetCtrl();

	long posOpenBrace = WSPSearchToken( pos -1, m_DocumentLength, szOpenBrace);
	long posClass = WSPSearchToken(posOpenBrace, 0, szKeyWord);	
	
	
	/*
	str.Format(_T("Pos Class...%d  " ), posClass);
	AfxMessageBox(str);
	str.Format(_T("Pos OpenBrace...%d  " ), posOpenBrace);
	AfxMessageBox(str);
	*/
	
	if( posClass != NOT_FOUND && posOpenBrace != NOT_FOUND )
	{
		//AfxMessageBox(_T("hello"));
		
		if( pos >= posClass && pos <= posOpenBrace )
		{
			r = WSPParseClass( posClass -1, posOpenBrace);
			
				//AfxMessageBox(_T("hello2"));
		
			
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				
				//Check for comments
				if( commentFlag )
				{
					bool lnComment = WSPCheckLineComment( posClass, posClass + 5);
					if( lnComment )
					{
						m_bFlagEditClass = false;
						return SIMPLE_COMMENT;
					}
					bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posClass );
					if( blkComment )
					{
						m_bFlagEditClass = false;
						return COMPLEX_COMMENT;
					}
				}

				CString sClassName = WSPGetText(posClass + 5, posOpenBrace);
				if( sClassName == _T("OVERLOAD" ))
				{
					return AIPI_ERROR;
				}
				

				if( sClassName != _T("EMPTY") )
				{
					sClassName.TrimRight();
					sClassName.TrimLeft();
					r = WSPDeleteNodeTree1(sClassName);
					
				}
			}
		
		}
	}
	

return r;	
	

}








int CAIPIEditorView::WSPAddFunction( long pos, bool commentFlag )
{
		
	//AfxMessageBox(_T("ADD FUNCTION"));
	
	LPSTR szOpenParenthesis = "(";
	LPSTR szCloseParenthesis = ")";
	
	int r = AIPI_ERROR;
	
	CString str;
	//str.Format(_T("Modification Type... %d"), m_iModificationType);
	//AfxMessageBox(str);	


	CScintillaCtrl& rCtrl = GetCtrl();
		
	long posCloseParenthesis = WSPSearchToken( pos -1, m_DocumentLength, szCloseParenthesis);
	long posOpenParenthesis = WSPSearchToken( posCloseParenthesis, 0, szOpenParenthesis);
	long posIdType = WSPSearchNearestIdType(posOpenParenthesis, 0);
	
	/*
	str.Format(_T("Pos IdType...%d  " ), posIdType);
	AfxMessageBox(str);
	str.Format(_T("Pos Open Parenthesis...%d  " ), posOpenParenthesis);
	AfxMessageBox(str);
	str.Format(_T("Pos Close Parenthesis...%d  " ), posCloseParenthesis);
	AfxMessageBox(str);
	AfxMessageBox(m_sCurrentType);
	*/

	if( posIdType != NOT_FOUND && posCloseParenthesis != NOT_FOUND && posOpenParenthesis != NOT_FOUND )
	{
		if( pos >= posIdType && pos <= posCloseParenthesis )
		{
			//AfxMessageBox(_T("Rango"));
			
			r = WSPParseFunction( posIdType -1, posCloseParenthesis);
			
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				//AfxMessageBox(_T("In"));
				int typeLength = m_sCurrentType.GetLength();
				//Check for comments
				if( commentFlag )
				{
					bool lnComment = WSPCheckLineComment( posIdType, posIdType + typeLength);
					if( lnComment )
					{
						m_bFlagEditFunction = false;
						return SIMPLE_COMMENT;
					}
					bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posIdType );
					if( blkComment )
					{
						m_bFlagEditFunction = false;
						return COMPLEX_COMMENT;
					}
				}

				long posOpenParenthesis = WSPSearchToken(posIdType, posCloseParenthesis, szOpenParenthesis); 
				
			
				CString sFunctionName = WSPGetText(posIdType + typeLength, posOpenParenthesis);
				if( sFunctionName == _T("OVERLOAD" ))
				{
					return AIPI_ERROR;
				}
				
				if( sFunctionName != _T("EMPTY") )
				{
					CString sParameter = WSPFormatParameters( posOpenParenthesis, posCloseParenthesis );
					if( sParameter != _T("COMMENT_ERROR") )
					{
						sFunctionName.TrimRight();
						sFunctionName.TrimLeft();

						CString sFunctionParameter = _T("(") + sParameter + _T(")");
						//CString sFullRuleName = m_sRuleName + sRuleParameter; 
						//AfxMessageBox(m_sTokenName);
						//r = WSPAddNodeTree1(sFunctionName, sFunctionParameter, 4);
						r = WSPAddNodeTypeTree1(sFunctionName, sFunctionParameter, 6, AIPI_FUNCTION);
						//CWorkspaceTabView tab;
						//tab.printWSPTree1();
					}
				}
			}
		
		}
	}
	

return r;

}


int CAIPIEditorView::WSPDeleteFunction( long pos, bool commentFlag )
{
	//AfxMessageBox(_T("DELETE FUNCTION"));
	
	LPSTR szOpenParenthesis = "(";
	LPSTR szCloseParenthesis = ")";
		
	int r = AIPI_ERROR;
	
	CString str;
	//str.Format(_T("Modification Type... %d"), m_iModificationType);
	//AfxMessageBox(str);	


	CScintillaCtrl& rCtrl = GetCtrl();

	long posCloseParenthesis = WSPSearchToken( pos -1, m_DocumentLength, szCloseParenthesis);
	long posOpenParenthesis = WSPSearchToken( posCloseParenthesis, 0, szOpenParenthesis);
	long posIdType = WSPSearchNearestIdType(posOpenParenthesis, 0);	
	
	
	/*
	str.Format(_T("Pos IdType...%d  " ), posIdType);
	AfxMessageBox(str);
	str.Format(_T("Pos Close Parenthesis...%d  " ), posCloseParenthesis);
	AfxMessageBox(str);
	*/
	
	if( posIdType != NOT_FOUND && posCloseParenthesis != NOT_FOUND && posOpenParenthesis != NOT_FOUND )
	{
		if( pos >= posIdType && pos <= posCloseParenthesis )
		{
			r = WSPParseFunction( posIdType -1, posCloseParenthesis);
			
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				//AfxMessageBox(_T("In"));				
				int typeLength = m_sCurrentType.GetLength();

				//Check for comments
				if( commentFlag )
				{
					bool lnComment = WSPCheckLineComment( posIdType, posIdType + typeLength);
					if( lnComment )
					{
						m_bFlagEditRule = false;
						return SIMPLE_COMMENT;
					}
					bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posIdType );
					if( blkComment )
					{
						m_bFlagEditRule = false;
						return COMPLEX_COMMENT;
					}
				}

				CString sFunctionName = WSPGetText(posIdType + typeLength, posOpenParenthesis);
				if( sFunctionName == _T("OVERLOAD" ))
				{
					return AIPI_ERROR;
				}
				
				
				if( sFunctionName != _T("EMPTY") )
				{
					sFunctionName.TrimRight();
					sFunctionName.TrimLeft();
					r = WSPDeleteNodeTree1(sFunctionName);
					
				}
			}
		
		}
	}
	

return r;	
	

}



int CAIPIEditorView::WSPAddJSFunction( long pos, bool commentFlag )
{
		
	//AfxMessageBox(_T("ADD FUNCTION"));
	
	LPSTR szOpenParenthesis = "(";
	LPSTR szCloseParenthesis = ")";
	LPSTR szKeyWord = "function";
	
	int r = AIPI_ERROR;
	
	CString str;
	//str.Format(_T("Modification Type... %d"), m_iModificationType);
	//AfxMessageBox(str);	


	CScintillaCtrl& rCtrl = GetCtrl();
		
	long posCloseParenthesis = WSPSearchToken( pos -1, m_DocumentLength, szCloseParenthesis);
	long posOpenParenthesis = WSPSearchToken( posCloseParenthesis, 0, szOpenParenthesis);
	long posFunction = WSPSearchToken(posOpenParenthesis, 0, szKeyWord);
	
	/*
	str.Format(_T("Pos IdType...%d  " ), posIdType);
	AfxMessageBox(str);
	str.Format(_T("Pos Close Parenthesis...%d  " ), posCloseParenthesis);
	AfxMessageBox(str);
	AfxMessageBox(m_sCurrentType);
	*/
	if( posFunction != NOT_FOUND && posCloseParenthesis != NOT_FOUND && posOpenParenthesis != NOT_FOUND )
	{
		if( pos >= posFunction && pos <= posCloseParenthesis )
		{
			//AfxMessageBox(_T("Rango"));
			
			r = WSPParseJSFunction( posFunction -1, posCloseParenthesis);
			
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				//AfxMessageBox(_T("In"));
				//Check for comments
				if( commentFlag )
				{
					bool lnComment = WSPCheckLineComment( posFunction, posFunction + 8);
					if( lnComment )
					{
						m_bFlagEditJSFunction = false;
						return SIMPLE_COMMENT;
					}
					bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posFunction );
					if( blkComment )
					{
						m_bFlagEditJSFunction = false;
						return COMPLEX_COMMENT;
					}
				}

				long posOpenParenthesis = WSPSearchToken(posFunction, posCloseParenthesis, szOpenParenthesis); 
				
			
				CString sFunctionName = WSPGetText(posFunction + 8, posOpenParenthesis);
				if( sFunctionName == _T("OVERLOAD" ))
				{
					return AIPI_ERROR;
				}
				
				if( sFunctionName != _T("EMPTY") )
				{
					CString sParameter = WSPFormatParameters( posOpenParenthesis, posCloseParenthesis );
					if( sParameter != _T("COMMENT_ERROR") )
					{
						sFunctionName.TrimRight();
						sFunctionName.TrimLeft();

						CString sFunctionParameter = _T("(") + sParameter + _T(")");
						//CString sFullRuleName = m_sRuleName + sRuleParameter; 
						//AfxMessageBox(m_sTokenName);
						//r = WSPAddNodeTree1(sFunctionName, sFunctionParameter, 10);
						r = WSPAddNodeTypeTree1(sFunctionName, sFunctionParameter, 10, AIPI_FUNCTION);
						//CWorkspaceTabView tab;
						//tab.printWSPTree1();
					}
				}
			}
		
		}
	}
	

return r;

}

int CAIPIEditorView::WSPDeleteJSFunction( long pos, bool commentFlag )
{
	//AfxMessageBox(_T("DELETE FUNCTION"));
	
	LPSTR szOpenParenthesis = "(";
	LPSTR szCloseParenthesis = ")";
	LPSTR szKeyWord = "function";
	
		
	int r = AIPI_ERROR;
	
	CString str;
	//str.Format(_T("Modification Type... %d"), m_iModificationType);
	//AfxMessageBox(str);	


	CScintillaCtrl& rCtrl = GetCtrl();

	long posCloseParenthesis = WSPSearchToken( pos -1, m_DocumentLength, szCloseParenthesis);
	long posOpenParenthesis = WSPSearchToken( posCloseParenthesis, 0, szOpenParenthesis);
	long posFunction = WSPSearchToken(posOpenParenthesis, 0, szKeyWord);	
	
	
	/*
	str.Format(_T("Pos IdType...%d  " ), posIdType);
	AfxMessageBox(str);
	str.Format(_T("Pos Close Parenthesis...%d  " ), posCloseParenthesis);
	AfxMessageBox(str);
	*/
	
	if( posFunction != NOT_FOUND && posCloseParenthesis != NOT_FOUND && posOpenParenthesis != NOT_FOUND )
	{
		if( pos >= posFunction && pos <= posCloseParenthesis )
		{
			r = WSPParseJSFunction( posFunction -1, posCloseParenthesis);
			
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				//AfxMessageBox(_T("In"));				
				//Check for comments
				if( commentFlag )
				{
					bool lnComment = WSPCheckLineComment( posFunction, posFunction + 8);
					if( lnComment )
					{
						m_bFlagEditJSFunction = false;
						return SIMPLE_COMMENT;
					}
					bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posFunction );
					if( blkComment )
					{
						m_bFlagEditJSFunction = false;
						return COMPLEX_COMMENT;
					}
				}

				CString sFunctionName = WSPGetText(posFunction + 8, posOpenParenthesis);
				if( sFunctionName == _T("OVERLOAD" ))
				{
					return AIPI_ERROR;
				}
				
				
				if( sFunctionName != _T("EMPTY") )
				{
					sFunctionName.TrimRight();
					sFunctionName.TrimLeft();
					r = WSPDeleteNodeTree1(sFunctionName);
					
				}
			}
		
		}
	}
	

return r;	
	

}




int CAIPIEditorView::WSPAddVBSFunction( long pos, bool commentFlag )
{
		
	//AfxMessageBox(_T("ADD FUNCTION"));
	
	LPSTR szOpenParenthesis = "(";
	LPSTR szCloseParenthesis = ")";
	LPSTR szKeyWord = "Function";
	
	int r = AIPI_ERROR;
	
	CString str;
	//str.Format(_T("Modification Type... %d"), m_iModificationType);
	//AfxMessageBox(str);	


	CScintillaCtrl& rCtrl = GetCtrl();
		
	long posCloseParenthesis = WSPSearchToken( pos -1, m_DocumentLength, szCloseParenthesis);
	long posOpenParenthesis = WSPSearchToken( posCloseParenthesis, 0, szOpenParenthesis);
	long posFunction = WSPSearchToken(posOpenParenthesis, 0, szKeyWord);
	
	/*
	str.Format(_T("Pos IdType...%d  " ), posIdType);
	AfxMessageBox(str);
	str.Format(_T("Pos Close Parenthesis...%d  " ), posCloseParenthesis);
	AfxMessageBox(str);
	AfxMessageBox(m_sCurrentType);
	*/
	if( posFunction != NOT_FOUND && posCloseParenthesis != NOT_FOUND && posOpenParenthesis != NOT_FOUND )
	{
		if( pos >= posFunction && pos <= posCloseParenthesis )
		{
			//AfxMessageBox(_T("Rango"));
			
			r = WSPParseVBSFunction( posFunction -1, posCloseParenthesis);
			
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				//AfxMessageBox(_T("In"));
				//Check for comments
				if( commentFlag )
				{
					bool lnComment = WSPCheckLineComment( posFunction, posFunction + 8);
					if( lnComment )
					{
						m_bFlagEditVBSFunction = false;
						return SIMPLE_COMMENT;
					}
					bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posFunction );
					if( blkComment )
					{
						m_bFlagEditVBSFunction = false;
						return COMPLEX_COMMENT;
					}
				}

				long posOpenParenthesis = WSPSearchToken(posFunction, posCloseParenthesis, szOpenParenthesis); 
				
			
				CString sFunctionName = WSPGetText(posFunction + 8, posOpenParenthesis);
				if( sFunctionName == _T("OVERLOAD" ))
				{
					return AIPI_ERROR;
				}
				
				if( sFunctionName != _T("EMPTY") )
				{
					CString sParameter = WSPFormatParameters( posOpenParenthesis, posCloseParenthesis );
					if( sParameter != _T("COMMENT_ERROR") )
					{
						sFunctionName.TrimRight();
						sFunctionName.TrimLeft();

						CString sFunctionParameter = _T("(") + sParameter + _T(")");
						//CString sFullRuleName = m_sRuleName + sRuleParameter; 
						//AfxMessageBox(m_sTokenName);
						//r = WSPAddNodeTree1(sFunctionName, sFunctionParameter, 12);
						r = WSPAddNodeTypeTree1(sFunctionName, sFunctionParameter, 12, AIPI_FUNCTION);
						//CWorkspaceTabView tab;
						//tab.printWSPTree1();
					}
				}
			}
		
		}
	}
	

return r;

}



int CAIPIEditorView::WSPDeleteVBSFunction( long pos, bool commentFlag )
{
	//AfxMessageBox(_T("DELETE FUNCTION"));
	
	LPSTR szOpenParenthesis = "(";
	LPSTR szCloseParenthesis = ")";
	LPSTR szKeyWord = "Function";
			
	int r = AIPI_ERROR;
	
	CString str;
	//str.Format(_T("Modification Type... %d"), m_iModificationType);
	//AfxMessageBox(str);	


	CScintillaCtrl& rCtrl = GetCtrl();

	long posCloseParenthesis = WSPSearchToken( pos -1, m_DocumentLength, szCloseParenthesis);
	long posOpenParenthesis = WSPSearchToken( posCloseParenthesis, 0, szOpenParenthesis);
	long posFunction = WSPSearchToken(posOpenParenthesis, 0, szKeyWord);	
	
	
	/*
	str.Format(_T("Pos IdType...%d  " ), posIdType);
	AfxMessageBox(str);
	str.Format(_T("Pos Close Parenthesis...%d  " ), posCloseParenthesis);
	AfxMessageBox(str);
	*/
	
	if( posFunction != NOT_FOUND && posCloseParenthesis != NOT_FOUND && posOpenParenthesis != NOT_FOUND )
	{
		if( pos >= posFunction && pos <= posCloseParenthesis )
		{
			r = WSPParseVBSFunction( posFunction -1, posCloseParenthesis);
			
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				//AfxMessageBox(_T("In"));				
				//Check for comments
				if( commentFlag )
				{
					bool lnComment = WSPCheckLineComment( posFunction, posFunction + 8);
					if( lnComment )
					{
						m_bFlagEditVBSFunction = false;
						return SIMPLE_COMMENT;
					}
					bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posFunction );
					if( blkComment )
					{
						m_bFlagEditVBSFunction = false;
						return COMPLEX_COMMENT;
					}
				}

				CString sFunctionName = WSPGetText(posFunction + 8, posOpenParenthesis);
				if( sFunctionName == _T("OVERLOAD" ))
				{
					return AIPI_ERROR;
				}
				
				
				if( sFunctionName != _T("EMPTY") )
				{
					sFunctionName.TrimRight();
					sFunctionName.TrimLeft();
					r = WSPDeleteNodeTree1(sFunctionName);
					
				}
			}
		
		}
	}
	

return r;	
	

}







int CAIPIEditorView::WSPAddVBSFUNCTION( long pos, bool commentFlag )
{
		
	//AfxMessageBox(_T("ADD FUNCTION"));
	
	LPSTR szOpenParenthesis = "(";
	LPSTR szCloseParenthesis = ")";
	LPSTR szKeyWord = "FUNCTION";
	
	int r = AIPI_ERROR;
	
	CString str;
	//str.Format(_T("Modification Type... %d"), m_iModificationType);
	//AfxMessageBox(str);	


	CScintillaCtrl& rCtrl = GetCtrl();
		
	long posCloseParenthesis = WSPSearchToken( pos -1, m_DocumentLength, szCloseParenthesis);
	long posOpenParenthesis = WSPSearchToken( posCloseParenthesis, 0, szOpenParenthesis);
	long posFunction = WSPSearchToken(posOpenParenthesis, 0, szKeyWord);
	
	/*
	str.Format(_T("Pos IdType...%d  " ), posIdType);
	AfxMessageBox(str);
	str.Format(_T("Pos Close Parenthesis...%d  " ), posCloseParenthesis);
	AfxMessageBox(str);
	AfxMessageBox(m_sCurrentType);
	*/
	if( posFunction != NOT_FOUND && posCloseParenthesis != NOT_FOUND && posOpenParenthesis != NOT_FOUND )
	{
		if( pos >= posFunction && pos <= posCloseParenthesis )
		{
			//AfxMessageBox(_T("Rango"));
			
			r = WSPParseVBSFunction( posFunction -1, posCloseParenthesis);
			
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				//AfxMessageBox(_T("In"));
				//Check for comments
				if( commentFlag )
				{
					bool lnComment = WSPCheckLineComment( posFunction, posFunction + 8);
					if( lnComment )
					{
						m_bFlagEditVBSFunction = false;
						return SIMPLE_COMMENT;
					}
					bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posFunction );
					if( blkComment )
					{
						m_bFlagEditVBSFunction = false;
						return COMPLEX_COMMENT;
					}
				}

				long posOpenParenthesis = WSPSearchToken(posFunction, posCloseParenthesis, szOpenParenthesis); 
				
			
				CString sFunctionName = WSPGetText(posFunction + 8, posOpenParenthesis);
				if( sFunctionName == _T("OVERLOAD" ))
				{
					return AIPI_ERROR;
				}
				
				if( sFunctionName != _T("EMPTY") )
				{
					CString sParameter = WSPFormatParameters( posOpenParenthesis, posCloseParenthesis );
					if( sParameter != _T("COMMENT_ERROR") )
					{
						sFunctionName.TrimRight();
						sFunctionName.TrimLeft();

						CString sFunctionParameter = _T("(") + sParameter + _T(")");
						//CString sFullRuleName = m_sRuleName + sRuleParameter; 
						//AfxMessageBox(m_sTokenName);
						//r = WSPAddNodeTree1(sFunctionName, sFunctionParameter, 4);
						r = WSPAddNodeTypeTree1(sFunctionName, sFunctionParameter, 12, AIPI_FUNCTION);
						//CWorkspaceTabView tab;
						//tab.printWSPTree1();
					}
				}
			}
		
		}
	}
	

return r;

}


int CAIPIEditorView::WSPDeleteVBSFUNCTION( long pos, bool commentFlag )
{
	//AfxMessageBox(_T("DELETE FUNCTION"));
	
	LPSTR szOpenParenthesis = "(";
	LPSTR szCloseParenthesis = ")";
	LPSTR szKeyWord = "FUNCTION";
			
	int r = AIPI_ERROR;
	
	CString str;
	//str.Format(_T("Modification Type... %d"), m_iModificationType);
	//AfxMessageBox(str);	


	CScintillaCtrl& rCtrl = GetCtrl();

	long posCloseParenthesis = WSPSearchToken( pos -1, m_DocumentLength, szCloseParenthesis);
	long posOpenParenthesis = WSPSearchToken( posCloseParenthesis, 0, szOpenParenthesis);
	long posFunction = WSPSearchToken(posOpenParenthesis, 0, szKeyWord);	
	
	
	/*
	str.Format(_T("Pos IdType...%d  " ), posIdType);
	AfxMessageBox(str);
	str.Format(_T("Pos Close Parenthesis...%d  " ), posCloseParenthesis);
	AfxMessageBox(str);
	*/
	
	if( posFunction != NOT_FOUND && posCloseParenthesis != NOT_FOUND && posOpenParenthesis != NOT_FOUND )
	{
		if( pos >= posFunction && pos <= posCloseParenthesis )
		{
			r = WSPParseVBSFunction( posFunction -1, posCloseParenthesis);
			
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				//AfxMessageBox(_T("In"));				
				//Check for comments
				if( commentFlag )
				{
					bool lnComment = WSPCheckLineComment( posFunction, posFunction + 8);
					if( lnComment )
					{
						m_bFlagEditVBSFunction = false;
						return SIMPLE_COMMENT;
					}
					bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posFunction );
					if( blkComment )
					{
						m_bFlagEditVBSFunction = false;
						return COMPLEX_COMMENT;
					}
				}

				CString sFunctionName = WSPGetText(posFunction + 8, posOpenParenthesis);
				if( sFunctionName == _T("OVERLOAD" ))
				{
					return AIPI_ERROR;
				}
				
				
				if( sFunctionName != _T("EMPTY") )
				{
					sFunctionName.TrimRight();
					sFunctionName.TrimLeft();
					r = WSPDeleteNodeTree1(sFunctionName);
					
				}
			}
		
		}
	}
	

return r;	
	

}




int CAIPIEditorView::WSPAddRule( long pos, bool commentFlag )
{
		
	//AfxMessageBox(_T("ADD RULE"));
	
	LPSTR szKeyWord = "RULE";
	LPSTR szOpenParenthesis = "(";
	LPSTR szCloseParenthesis = ")";
	LPSTR szDobleQuotation = "\"";
	
	int r = AIPI_ERROR;
	
	CString str;
	//str.Format(_T("Modification Type... %d"), m_iModificationType);
	//AfxMessageBox(str);	


	CScintillaCtrl& rCtrl = GetCtrl();
		
	long posRule = WSPSearchToken( pos, 0, szKeyWord);
	long posCloseParenthesis = WSPSearchToken( posRule, m_DocumentLength, szCloseParenthesis);
	/*
	str.Format(_T("Pos Rule...%d  " ), posRule);
	AfxMessageBox(str);
	str.Format(_T("Pos Close Parenthesis...%d  " ), posCloseParenthesis);
	AfxMessageBox(str);
	*/
	
	if( posRule != NOT_FOUND && posCloseParenthesis != NOT_FOUND )
	{
		if( pos >= posRule && pos <= posCloseParenthesis )
		{
			//AfxMessageBox(_T("Rango"));
			
			r = WSPParseRule( posRule -1, posCloseParenthesis);
			
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				//AfxMessageBox(_T("In"));				
				//Check for comments
				if( commentFlag)
				{
					bool lnComment = WSPCheckLineComment( posRule, posRule + 4);
					if( lnComment )
					{
						m_bFlagEditRule = false;
						return SIMPLE_COMMENT;
					}
					bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posRule );
					if( blkComment )
					{
						m_bFlagEditRule = false;
						return COMPLEX_COMMENT;
					}
				}


				long posStartDobleQuotation = WSPSearchToken( posRule, posCloseParenthesis, szDobleQuotation);
				long posEndDobleQuotation = WSPSearchToken(posStartDobleQuotation + 1, posCloseParenthesis, szDobleQuotation);
				long posOpenParenthesis = WSPSearchToken(posEndDobleQuotation, posCloseParenthesis, szOpenParenthesis); 

			
				CString sRuleName = WSPGetText(posStartDobleQuotation+ 1, posEndDobleQuotation);
				if( sRuleName == _T("OVERLOAD" ))
				{
					return AIPI_ERROR;
				}
				
				if( sRuleName != _T("EMPTY") )
				{
					CString sParameter = WSPFormatParameters( posOpenParenthesis, posCloseParenthesis );
					if( sParameter != _T("COMMENT_ERROR") )
					{
						sRuleName = WSPFormatRuleNameOpt(sRuleName);

						CString sRuleParameter = _T("(") + sParameter + _T(")");
						//CString sFullRuleName = m_sRuleName + sRuleParameter; 
						//AfxMessageBox(m_sTokenName);
						//r = WSPAddNodeTree1(sRuleName, sRuleParameter, 2);
						r = WSPAddNodeTypeTree1(sRuleName, sRuleParameter, 2, AIPI_RULE);
						//CWorkspaceTabView tab;
						//tab.printWSPTree1();
					}
				}
			}
		
		}
	}
	

return r;

}

int CAIPIEditorView::WSPDeleteRule( long pos, bool commentFlag )
{
	//commentFlag = Check for comments in the rule declaration
	//AfxMessageBox(_T("DELETE RULE"));
	
	LPSTR szKeyWord = "RULE";
	LPSTR szOpenParenthesis = "(";
	LPSTR szCloseParenthesis = ")";
	LPSTR szDobleQuotation = "\"";
	
	int r = AIPI_ERROR;
	
	CString str;
	//str.Format(_T("Modification Type... %d"), m_iModificationType);
	//AfxMessageBox(str);	


	CScintillaCtrl& rCtrl = GetCtrl();
		
	long posRule = WSPSearchToken( pos, 0, szKeyWord);
	long posCloseParenthesis = WSPSearchToken( posRule, m_DocumentLength, szCloseParenthesis);
	
	/*
	str.Format(_T("Pos Rule...%d  " ), posRule);
	AfxMessageBox(str);
	str.Format(_T("Pos Close Parenthesis...%d  " ), posCloseParenthesis);
	AfxMessageBox(str);
	*/
	
	if( posRule != NOT_FOUND && posCloseParenthesis != NOT_FOUND )
	{
		if( pos >= posRule && pos <= posCloseParenthesis )
		{
			r = WSPParseRule( posRule -1, posCloseParenthesis);
			
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				//AfxMessageBox(_T("In"));				
				if( commentFlag )
				{
					//Check for comments
					bool lnComment = WSPCheckLineComment( posRule, posRule + 4);
					if( lnComment )
					{
						m_bFlagEditRule = false;
						return SIMPLE_COMMENT;
					}
					bool blkComment = WSPCheckBlockComment( 0, m_DocumentLength, posRule );
					if( blkComment )
					{
						m_bFlagEditRule = false;
						return COMPLEX_COMMENT;
					}
				}

				long posStartDobleQuotation = WSPSearchToken( posRule, posCloseParenthesis, szDobleQuotation);
				long posEndDobleQuotation = WSPSearchToken(posStartDobleQuotation + 1, posCloseParenthesis, szDobleQuotation);
				long posOpenParenthesis = WSPSearchToken(posEndDobleQuotation, posCloseParenthesis, szOpenParenthesis); 

			
				CString sRuleName = WSPGetText(posStartDobleQuotation+ 1, posEndDobleQuotation);
				if( sRuleName == _T("OVERLOAD" ))
				{
					return AIPI_ERROR;
				}
				if( sRuleName != _T("EMPTY") )
				{
					sRuleName = WSPFormatRuleNameOpt(sRuleName);
					//AfxMessageBox(sRuleName);
				
					r = WSPDeleteNodeTree1(sRuleName);
					
				}
			}
		
		}
	}
	

return r;	
	

}

int CAIPIEditorView::WSPParseRuleEdit(long nStartSel, long nEndSel)
{
	int match = NOT_FOUND;
	g_currentPos = nStartSel + 4;
	m_lookahead = AIPI_RULE;
	//CString str;
	
	match = WSPMatchToken(AIPI_RULE);
	//AfxMessageBox(_T("Hola0"));
	if( match != AIPI_ERROR )
	{
		//AfxMessageBox(_T("Hola1"));
		m_sCurrentRuleName = WSPFormatRuleNameOpt(m_sTokenName);
		//AfxMessageBox(m_sCurrentRuleName);
		match = WSPMatchToken(LITERAL);
		
		if( match != AIPI_ERROR )
		{
			//AfxMessageBox(_T("Hola2"));
			match = WSPMatchToken(OPEN_PARENTHESIS);
			if( match != AIPI_ERROR )
			{
				while(m_lookahead != CLOSE_PARENTHESIS && g_currentPos <= nEndSel  )
				{
					//AfxMessageBox(_T("Hola3"));
					++g_currentPos;
					m_lookahead = WSPGetToken();
					//str.Format(_T("Look ahead...%d  " ), m_lookahead);
					//AfxMessageBox(str);
					

					//symbols not allowed between the parenthesis
					switch( m_lookahead)
					{
					case OPEN_BRACE:
						return AIPI_ERROR;
					
					case CLOSE_BRACE:
						return AIPI_ERROR;
					
					case OPEN_PARENTHESIS:
						return AIPI_ERROR;
					
					case NUL:
						return AIPI_ERROR;
					}
					
				}
				
				match = WSPMatchToken(CLOSE_PARENTHESIS);
				if( match != AIPI_ERROR )
				{
					//Checking limit position of parser analysis
					if( g_currentPos < nEndSel )
					{
						return AIPI_ERROR;
					}
					else
					{
						//The parser was successfull
						return P_SUCCESS;
					}
				}
				else
				{
					//AfxMessageBox(_T("ERROR CLOSE PARENTHESIS Not Found!!!"));
					return AIPI_ERROR;
				}
			}
			else
			{
				//AfxMessageBox(_T("ERROR OPEN PARENTHESIS Not Found!!!"));
				return AIPI_ERROR;
			}
		}
		else
		{
			//AfxMessageBox(_T("ERROR RULE NAME Not Found!!!"));
			return AIPI_ERROR;
		}
	}
	else
	{
		//AfxMessageBox(_T("ERROR RULE KEYWORD Not Found!!!"));
		return AIPI_ERROR;
	}

	
return NOT_FOUND;
}



int CAIPIEditorView::WSPParseQuery(long nStartSel, long nEndSel )
{
	//Check for variable identifier
	int match = NOT_FOUND;
	g_currentPos = nStartSel;

	m_lookahead = WSPGetToken();
	match = WSPMatchToken(AIPI_SQLQUERY);
	
	if( match != NOT_FOUND )
	{
		//AfxMessageBox(_T("Hola1"));
		m_sCurrentQueryName  = m_sTokenName;
		
		//AfxMessageBox(m_sCurrentQueryName);

		match = WSPMatchToken(IDENTIFIER);
		
		if( match != AIPI_ERROR )
		{
			//AfxMessageBox(_T("Hola2"));
			int match = WSPMatchToken(EQUAL);
			
			if( match != AIPI_ERROR )
			{
				//AfxMessageBox(_T("QUERY DECLARATION DETECTED!!!"));
				//Checking limit position of parser analysis
					if( g_currentPos < nEndSel )
					{
						return AIPI_ERROR;
					}
					else
					{
						return P_SUCCESS;
					}
				
			}
							
		}
		else
		{
			//AfxMessageBox(_T("ERROR QUERY NAME Not Found!!!"));
			return AIPI_ERROR;
		}
	
	}
	else
	{
		//AfxMessageBox(_T("ERROR QUERY KEYWORD Not Found!!!"));
		return AIPI_ERROR;
	}



return NOT_FOUND;

}



int CAIPIEditorView::WSPParseQueryEdit(long nStartSel, long nEndSel )
{
	//Check for variable identifier
	int match = NOT_FOUND;
	g_currentPos = nStartSel + 8;
	m_lookahead = AIPI_SQLQUERY;
	//CString str;
	
	match = WSPMatchToken(AIPI_SQLQUERY);

	if( match != NOT_FOUND )
	{
		//AfxMessageBox(_T("Hola1"));
		m_sCurrentQueryName  = m_sTokenName;
		match = WSPMatchToken(IDENTIFIER);
		
		if( match != AIPI_ERROR )
		{
	
			int match = WSPMatchToken(EQUAL);
			
			if( match != AIPI_ERROR )
			{
				//AfxMessageBox(_T("VARIABLE DECLARATION DETECTED!!!"));
				//Checking limit position of parser analysis
					if( g_currentPos < nEndSel )
					{
						return AIPI_ERROR;
					}
					else
					{
						return P_SUCCESS;
					}
				
			}
							
		}
		else
		{
			//AfxMessageBox(_T("ERROR CLASS NAME Not Found!!!"));
			return AIPI_ERROR;
		}
	
	}
	else
	{
		//AfxMessageBox(_T("ERROR CLASS KEYWORD Not Found!!!"));
		return AIPI_ERROR;
	}



return NOT_FOUND;

}





int CAIPIEditorView::WSPParseClass(long nStartSel, long nEndSel )
{
	//Check for variable identifier
	int match = NOT_FOUND;
	g_currentPos = nStartSel;

	m_lookahead = WSPGetToken();
	match = WSPMatchToken(AIPI_CLASS);
	
	if( match != NOT_FOUND )
	{
		//AfxMessageBox(_T("Hola1"));
		m_sCurrentClassName  = m_sTokenName;
		//AfxMessageBox(m_sCurrentClassName);
		match = WSPMatchToken(IDENTIFIER);
		

		if( match != AIPI_ERROR )
		{
			//AfxMessageBox(_T("Hola2"));
			int match = WSPMatchToken(OPEN_BRACE);
			
			if( match != AIPI_ERROR )
			{
				//AfxMessageBox(_T("VARIABLE DECLARATION DETECTED!!!"));
				//Checking limit position of parser analysis
					if( g_currentPos < nEndSel )
					{
						return AIPI_ERROR;
					}
					else
					{
						return P_SUCCESS;
					}
				
			}
							
		}
		else
		{
			//AfxMessageBox(_T("ERROR CLASS NAME Not Found!!!"));
			return AIPI_ERROR;
		}
	
	}
	else
	{
		//AfxMessageBox(_T("ERROR CLASS KEYWORD Not Found!!!"));
		return AIPI_ERROR;
	}



return NOT_FOUND;

}






int CAIPIEditorView::WSPParseClassEdit(long nStartSel, long nEndSel )
{
	//Check for variable identifier
	int match = NOT_FOUND;
	g_currentPos = nStartSel + 5;
	m_lookahead = AIPI_CLASS;
	//CString str;
	
	match = WSPMatchToken(AIPI_CLASS);

	if( match != NOT_FOUND )
	{
		//AfxMessageBox(_T("Hola1"));
		m_sCurrentClassName  = m_sTokenName;
		match = WSPMatchToken(IDENTIFIER);
		
		if( match != AIPI_ERROR )
		{
	
			int match = WSPMatchToken(OPEN_BRACE);
			
			if( match != AIPI_ERROR )
			{
				//AfxMessageBox(_T("VARIABLE DECLARATION DETECTED!!!"));
				//Checking limit position of parser analysis
					if( g_currentPos < nEndSel )
					{
						return AIPI_ERROR;
					}
					else
					{
						return P_SUCCESS;
					}
				
			}
							
		}
		else
		{
			//AfxMessageBox(_T("ERROR CLASS NAME Not Found!!!"));
			return AIPI_ERROR;
		}
	
	}
	else
	{
		//AfxMessageBox(_T("ERROR CLASS KEYWORD Not Found!!!"));
		return AIPI_ERROR;
	}



return NOT_FOUND;

}











int CAIPIEditorView::WSPParseRule(long nStartSel, long nEndSel)
{
	LPSTR szKeyWord = "RULE";
	int match = NOT_FOUND;
	g_currentPos = nStartSel;
	m_lookahead = WSPGetToken();
	
	CString str;
	//str.Format(_T("PosRule...%d  " ), nStartSel);
	//AfxMessageBox(str);
	
	//str.Format(_T("Look ahead...%d  " ), m_lookahead);
	//AfxMessageBox(str);
					
	
	match = WSPMatchToken(AIPI_RULE);
	//AfxMessageBox(_T("Hola0"));
	if( match != AIPI_ERROR )
	{
		//AfxMessageBox(_T("Hola1"));
		m_sCurrentRuleName = WSPFormatRuleNameOpt(m_sTokenName);
		//AfxMessageBox(m_sCurrentRuleName);
		match = WSPMatchToken(LITERAL);
		
		if( match != AIPI_ERROR )
		{
			//AfxMessageBox(_T("Hola2"));
			match = WSPMatchToken(OPEN_PARENTHESIS);
			if( match != AIPI_ERROR )
			{
				while(m_lookahead != CLOSE_PARENTHESIS && g_currentPos <= nEndSel  )
				{
					//AfxMessageBox(_T("Hola3"));
					++g_currentPos;
					m_lookahead = WSPGetToken();
					//str.Format(_T("Look ahead...%d  " ), m_lookahead);
					//AfxMessageBox(str);
					

					//symbols not allowed between the parenthesis
					switch( m_lookahead)
					{
					case OPEN_BRACE:
						return AIPI_ERROR;
					
					case CLOSE_BRACE:
						return AIPI_ERROR;
					
					case OPEN_PARENTHESIS:
						return AIPI_ERROR;
					
					case NUL:
						return AIPI_ERROR;
					}
					
				}
				
				match = WSPMatchToken(CLOSE_PARENTHESIS);
				if( match != AIPI_ERROR )
				{
					//Checking limit position of parser analysis
					if( g_currentPos < nEndSel )
					{
						return AIPI_ERROR;
					}
					else
					{
						//The parser was successfull
						return P_SUCCESS;
					}
				}
				else
				{
					//AfxMessageBox(_T("ERROR CLOSE PARENTHESIS Not Found!!!"));
					return AIPI_ERROR;
				}
			}
			else
			{
				//AfxMessageBox(_T("ERROR OPEN PARENTHESIS Not Found!!!"));
				return AIPI_ERROR;
			}
		}
		else
		{
			//AfxMessageBox(_T("ERROR RULE NAME Not Found!!!"));
			return AIPI_ERROR;
		}
	}
	else
	{
		//AfxMessageBox(_T("ERROR RULE KEYWORD Not Found!!!"));
		return AIPI_ERROR;
	}

	
return NOT_FOUND;
}











void CAIPIEditorView::WSPAddSelectedRules(long nStartSel, long nEndSel, bool commentFlag)
{
	LPSTR szKeyWord = "RULE";
	LPSTR szOpenParenthesis = "(";
	LPSTR szCloseParenthesis = ")";
	LPSTR szDobleQuotation = "\"";
	long posRule = 0;
	long posStart = nStartSel; 
	CScintillaCtrl& rCtrl = GetCtrl();
	
	CString str;
	
	do 
	{	
		
		if( posStart == NOT_FOUND )
		{
			posStart = nEndSel;
		}
		//AfxMessageBox(_T("PosRule"));
		posRule = WSPSearchToken(posStart, nEndSel, szKeyWord);	
		//str.Format(_T("Pos Rule %d"), posRule);
		//AfxMessageBox(str);

		//str.Format(_T("Pos Start %d"), posStart);
		//AfxMessageBox(str);

		
	
		if( posRule != NOT_FOUND  )
		{
			long posNextRule = WSPSearchToken(posRule + 5, nEndSel, szKeyWord );
			//str.Format(_T("posNextRule... %d"), posNextRule);
			//AfxMessageBox(str);
		
			
			
			//Check if the keyword it´s not part of another larger word
			int prevSymbol = rCtrl.GetCharAt( posRule - 1 );
			//str.Format(_T("Prev Symbol %d"), prevSymbol);
			//AfxMessageBox(str);
			if( prevSymbol != SPACE && prevSymbol != NEW_LINE && prevSymbol != CARRIAGE_RETURN && prevSymbol != NUL && prevSymbol != HORIZONTAL_TAB)
			{
				posStart = posNextRule;
				continue;
			}
			int postSymbol = rCtrl.GetCharAt( posRule + 4 );
			//str.Format(_T("Post Symbol %d"), postSymbol);
			//AfxMessageBox(str);
			
			if( postSymbol != SPACE && postSymbol != NEW_LINE && postSymbol != CARRIAGE_RETURN && postSymbol != NUL && prevSymbol != HORIZONTAL_TAB)
			{
				posStart = posNextRule;
				continue;		
			}
			
			if( commentFlag )
			{
				//Check for line comment at the begining of the rule
				bool lnComment = WSPCheckLineComment(posRule, posRule + 4);
				if( lnComment )
				{
					//AfxMessageBox(_T("Line comment found"));
					posStart = posRule + 5;
					continue;
				}

				//Check for block comment between the rule
				bool blkComment = WSPCheckBlockComment(nStartSel, nEndSel, posRule);
				//str.Format(_T(" handle Block Comment 2... %d"), blkComment);
				//AfxMessageBox(str);
			
				if( blkComment )
				{
					posStart = posNextRule;
					continue;
				}
			}

			
			long posCloseParenthesis = WSPSearchToken( posRule, nEndSel, szCloseParenthesis); 
			
			int r = WSPParseRule( posRule -1, posCloseParenthesis );
			
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				long posStartDobleQuotation = WSPSearchToken( posRule, posCloseParenthesis, szDobleQuotation);
				long posEndDobleQuotation = WSPSearchToken(posStartDobleQuotation + 1, posCloseParenthesis, szDobleQuotation);
				long posOpenParenthesis = WSPSearchToken(posEndDobleQuotation, posCloseParenthesis, szOpenParenthesis); 

				CString sRuleName = WSPGetText(posStartDobleQuotation+ 1, posEndDobleQuotation);
				if( sRuleName == _T("OVERLOAD" ))
				{
					return;
				}
								
				if( sRuleName != _T("EMPTY") )
				{
					CString sParameter = WSPFormatParameters( posOpenParenthesis, posCloseParenthesis );
					if( sParameter != _T("COMMENT_ERROR") )
					{
						sRuleName = WSPFormatRuleNameOpt(sRuleName);
						CString sRuleParameter = _T("(") + sParameter + _T(")");
						//CString sFullRuleName = m_sRuleName + sRuleParameter; 
						//AfxMessageBox(m_sTokenName);
						//AfxMessageBox(_T("Close P"));
						//WSPAddNodeTree1(sRuleName, sRuleParameter, 2);
						WSPAddNodeTypeTree1(sRuleName, sRuleParameter, 2, AIPI_RULE);
						//CWorkspaceTabView tab;
						//tab.printWSPTree1();
					}
				}
				
				posRule = posNextRule;				
				//posRule = WSPSearchToken(posCloseParenthesis, nEndSel, szKeyWord);
				//str.Format(_T("END CICLE   PosRule... %d"), posRule);
				//AfxMessageBox(str);

				
				if( posRule != NOT_FOUND )
				{
					posStart = posRule;
					
				}
				
			}
			else
			{
				posStart = posRule + 5;
			}
		}
		
	
	}while( posRule != NOT_FOUND );

}


void CAIPIEditorView::WSPAddSelectedFunctions(long nStartSel, long nEndSel, LPSTR szType, int typelen, bool commentFlag)
{
	LPSTR szOpenParenthesis = "(";
	LPSTR szCloseParenthesis = ")";
	long posIdType = 0;
	long posStart = nStartSel; 
	CScintillaCtrl& rCtrl = GetCtrl();
	
	CString str;
	
	do 
	{	
		
		if( posStart == NOT_FOUND )
		{
			posStart = nEndSel;
		}
		//AfxMessageBox(_T("PosIdType"));
		posIdType = WSPSearchToken(posStart, nEndSel, szType);	
		//str.Format(_T("Pos IdType %d"), posIdType);
		//AfxMessageBox(str);

		//str.Format(_T("Pos Start %d"), posStart);
		//AfxMessageBox(str);

		
	
		if( posIdType != NOT_FOUND  )
		{
			long posNextType = WSPSearchToken(posIdType + typelen + 1, nEndSel, szType );
			//str.Format(_T("posNextType... %d"), posNextType);
			//AfxMessageBox(str);
		
			
			
			//Check if the keyword it´s not part of another larger word
			int prevSymbol = rCtrl.GetCharAt( posIdType - 1 );
			//str.Format(_T("Prev Symbol %d"), prevSymbol);
			//AfxMessageBox(str);
			if( prevSymbol != SPACE && prevSymbol != NEW_LINE && prevSymbol != CARRIAGE_RETURN && prevSymbol != NUL && prevSymbol != HORIZONTAL_TAB)
			{
				posStart = posNextType;
				continue;
			}
			int postSymbol = rCtrl.GetCharAt( posIdType + typelen );
			//str.Format(_T("Post Symbol %d"), postSymbol);
			//AfxMessageBox(str);
			
			if( postSymbol != SPACE && postSymbol != NEW_LINE && postSymbol != CARRIAGE_RETURN && postSymbol != NUL && prevSymbol != HORIZONTAL_TAB)
			{
				posStart = posNextType;
				continue;		
			}
			
			if( commentFlag )
			{
				//Check for line comment at the begining of the rule
				bool lnComment = WSPCheckLineComment(posIdType, posIdType + typelen);
				if( lnComment )
				{
					//AfxMessageBox(_T("Line comment found"));
					posStart = posIdType + typelen +1;
					continue;
				}

				//Check for block comment between the rule
				bool blkComment = WSPCheckBlockComment(nStartSel, nEndSel, posIdType);
				//str.Format(_T(" handle Block Comment 2... %d"), blkComment);
				//AfxMessageBox(str);
			
				if( blkComment )
				{
					posStart = posNextType;
					continue;
				}
			}

			
			long posCloseParenthesis = WSPSearchToken( posIdType, nEndSel, szCloseParenthesis); 
			
			int r = WSPParseFunction( posIdType -1, posCloseParenthesis );
			
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				long posOpenParenthesis = WSPSearchToken(posIdType, posCloseParenthesis, szOpenParenthesis); 
				
				CString sFunctionName = WSPGetText(posIdType + typelen, posOpenParenthesis);
				if( sFunctionName == _T("OVERLOAD" ))
				{
					return;
				}
				
				if( sFunctionName != _T("EMPTY") )
				{
					
					CString sParameter = WSPFormatParameters( posOpenParenthesis, posCloseParenthesis );
					if( sParameter != _T("COMMENT_ERROR") )
					{
						sFunctionName.TrimRight();
						sFunctionName.TrimLeft();

						CString sFunctionParameter = _T("(") + sParameter + _T(")");
						//CString sFullRuleName = m_sRuleName + sRuleParameter; 
						//AfxMessageBox(m_sTokenName);
						//r = WSPAddNodeTree1(sFunctionName, sFunctionParameter, 4);
						r = WSPAddNodeTypeTree1(sFunctionName, sFunctionParameter, 6, AIPI_FUNCTION);
						//CWorkspaceTabView tab;
						//tab.printWSPTree1();
					}
				}
				
				
				posIdType = posNextType;				
				//str.Format(_T("END CICLE   PosIdType... %d"), posIdType);
				//AfxMessageBox(str);

				
				if( posIdType != NOT_FOUND )
				{
					posStart = posIdType;
					
				}
				
			}
			else
			{
				posStart = posIdType + typelen +1;
			}
		}
		
	
	}while( posIdType != NOT_FOUND );

}	


void CAIPIEditorView::WSPAddSelectedJSFunctions(long nStartSel, long nEndSel, bool commentFlag)
{
	LPSTR szKeyWord = "function";
	LPSTR szOpenParenthesis = "(";
	LPSTR szCloseParenthesis = ")";
	long posFunction = 0;
	long posStart = nStartSel; 
	CScintillaCtrl& rCtrl = GetCtrl();
	
	CString str;
	
	do 
	{	
		
		if( posStart == NOT_FOUND )
		{
			posStart = nEndSel;
		}
		//AfxMessageBox(_T("PosRule"));
		posFunction = WSPSearchToken(posStart, nEndSel, szKeyWord);	
		//str.Format(_T("Pos Rule %d"), posRule);
		//AfxMessageBox(str);

		//str.Format(_T("Pos Start %d"), posStart);
		//AfxMessageBox(str);

		
	
		if( posFunction != NOT_FOUND  )
		{
			long posNextFunction = WSPSearchToken(posFunction + 9, nEndSel, szKeyWord );
			//str.Format(_T("posNextRule... %d"), posNextRule);
			//AfxMessageBox(str);
		
			
			
			//Check if the keyword it´s not part of another larger word
			int prevSymbol = rCtrl.GetCharAt( posFunction - 1 );
			//str.Format(_T("Prev Symbol %d"), prevSymbol);
			//AfxMessageBox(str);
			if( prevSymbol != SPACE && prevSymbol != NEW_LINE && prevSymbol != CARRIAGE_RETURN && prevSymbol != NUL && prevSymbol != HORIZONTAL_TAB)
			{
				posStart = posNextFunction;
				continue;
			}
			int postSymbol = rCtrl.GetCharAt( posFunction + 8 );
			//str.Format(_T("Post Symbol %d"), postSymbol);
			//AfxMessageBox(str);
			
			if( postSymbol != SPACE && postSymbol != NEW_LINE && postSymbol != CARRIAGE_RETURN && postSymbol != NUL && prevSymbol != HORIZONTAL_TAB)
			{
				posStart = posNextFunction;
				continue;		
			}
			
			if( commentFlag )
			{
				//Check for line comment at the begining of the rule
				bool lnComment = WSPCheckLineComment(posFunction, posFunction + 8);
				if( lnComment )
				{
					//AfxMessageBox(_T("Line comment found"));
					posStart = posFunction + 5;
					continue;
				}

				//Check for block comment between the rule
				bool blkComment = WSPCheckBlockComment(nStartSel, nEndSel, posFunction);
				//str.Format(_T(" handle Block Comment 2... %d"), blkComment);
				//AfxMessageBox(str);
			
				if( blkComment )
				{
					posStart = posNextFunction;
					continue;
				}
			}

			
			long posCloseParenthesis = WSPSearchToken( posFunction, nEndSel, szCloseParenthesis); 
			
			int r = WSPParseJSFunction( posFunction -1, posCloseParenthesis );
			
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				long posOpenParenthesis = WSPSearchToken(posFunction, posCloseParenthesis, szOpenParenthesis); 

				CString sFunctionName = WSPGetText(posFunction + 8, posOpenParenthesis);
				if( sFunctionName == _T("OVERLOAD" ))
				{
					return;
				}
				
				if( sFunctionName != _T("EMPTY") )
				{
					
					CString sParameter = WSPFormatParameters( posOpenParenthesis, posCloseParenthesis );
					if( sParameter != _T("COMMENT_ERROR") )
					{
						sFunctionName.TrimRight();
						sFunctionName.TrimLeft();

						CString sFunctionParameter = _T("(") + sParameter + _T(")");
						//CString sFullRuleName = m_sRuleName + sRuleParameter; 
						//AfxMessageBox(m_sTokenName);
						//r = WSPAddNodeTree1(sFunctionName, sFunctionParameter, 10);
						r = WSPAddNodeTypeTree1(sFunctionName, sFunctionParameter, 10, AIPI_FUNCTION);
						//CWorkspaceTabView tab;
						//tab.printWSPTree1();
					}
				}

				posFunction = posNextFunction;				
				//posRule = WSPSearchToken(posCloseParenthesis, nEndSel, szKeyWord);
				//str.Format(_T("END CICLE   PosRule... %d"), posRule);
				//AfxMessageBox(str);

				
				if( posFunction != NOT_FOUND )
				{
					posStart = posFunction;
					
				}
				
			}
			else
			{
				posStart = posFunction + 8;
			}
		}
		
	
	}while( posFunction != NOT_FOUND );
	

}	




void CAIPIEditorView::WSPAddSelectedVBSFunctions(long nStartSel, long nEndSel, bool commentFlag)
{
	LPSTR szKeyWord = "Function";
	LPSTR szOpenParenthesis = "(";
	LPSTR szCloseParenthesis = ")";
	long posFunction = 0;
	long posStart = nStartSel; 
	CScintillaCtrl& rCtrl = GetCtrl();
	
	CString str;
	
	do 
	{	
		
		if( posStart == NOT_FOUND )
		{
			posStart = nEndSel;
		}
		//AfxMessageBox(_T("PosRule"));
		posFunction = WSPSearchToken(posStart, nEndSel, szKeyWord);	
		//str.Format(_T("Pos Rule %d"), posRule);
		//AfxMessageBox(str);

		//str.Format(_T("Pos Start %d"), posStart);
		//AfxMessageBox(str);

		
	
		if( posFunction != NOT_FOUND  )
		{
			long posNextFunction = WSPSearchToken(posFunction + 9, nEndSel, szKeyWord );
			//str.Format(_T("posNextRule... %d"), posNextRule);
			//AfxMessageBox(str);
		
			
			
			//Check if the keyword it´s not part of another larger word
			int prevSymbol = rCtrl.GetCharAt( posFunction - 1 );
			//str.Format(_T("Prev Symbol %d"), prevSymbol);
			//AfxMessageBox(str);
			if( prevSymbol != SPACE && prevSymbol != NEW_LINE && prevSymbol != CARRIAGE_RETURN && prevSymbol != NUL && prevSymbol != HORIZONTAL_TAB)
			{
				posStart = posNextFunction;
				continue;
			}
			int postSymbol = rCtrl.GetCharAt( posFunction + 8 );
			//str.Format(_T("Post Symbol %d"), postSymbol);
			//AfxMessageBox(str);
			
			if( postSymbol != SPACE && postSymbol != NEW_LINE && postSymbol != CARRIAGE_RETURN && postSymbol != NUL && prevSymbol != HORIZONTAL_TAB)
			{
				posStart = posNextFunction;
				continue;		
			}
			
			if( commentFlag )
			{
				//Check for line comment at the begining of the rule
				bool lnComment = WSPCheckLineComment(posFunction, posFunction + 8);
				if( lnComment )
				{
					//AfxMessageBox(_T("Line comment found"));
					posStart = posFunction + 5;
					continue;
				}

				//Check for block comment between the rule
				bool blkComment = WSPCheckBlockComment(nStartSel, nEndSel, posFunction);
				//str.Format(_T(" handle Block Comment 2... %d"), blkComment);
				//AfxMessageBox(str);
			
				if( blkComment )
				{
					posStart = posNextFunction;
					continue;
				}
			}

			
			long posCloseParenthesis = WSPSearchToken( posFunction, nEndSel, szCloseParenthesis); 
			
			int r = WSPParseVBSFunction( posFunction -1, posCloseParenthesis );
			
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				long posOpenParenthesis = WSPSearchToken(posFunction, posCloseParenthesis, szOpenParenthesis); 

				CString sFunctionName = WSPGetText(posFunction + 8, posOpenParenthesis);
				if( sFunctionName == _T("OVERLOAD" ))
				{
					return;
				}
				
				if( sFunctionName != _T("EMPTY") )
				{
					
					CString sParameter = WSPFormatParameters( posOpenParenthesis, posCloseParenthesis );
					if( sParameter != _T("COMMENT_ERROR") )
					{
						sFunctionName.TrimRight();
						sFunctionName.TrimLeft();

						CString sFunctionParameter = _T("(") + sParameter + _T(")");
						//CString sFullRuleName = m_sRuleName + sRuleParameter; 
						//AfxMessageBox(m_sTokenName);
						//r = WSPAddNodeTree1(sFunctionName, sFunctionParameter, 12);
						r = WSPAddNodeTypeTree1(sFunctionName, sFunctionParameter, 12, AIPI_FUNCTION);
						//CWorkspaceTabView tab;
						//tab.printWSPTree1();
					}
				}

				posFunction = posNextFunction;				
				//posRule = WSPSearchToken(posCloseParenthesis, nEndSel, szKeyWord);
				//str.Format(_T("END CICLE   PosRule... %d"), posRule);
				//AfxMessageBox(str);

				
				if( posFunction != NOT_FOUND )
				{
					posStart = posFunction;
					
				}
				
			}
			else
			{
				posStart = posFunction + 8;
			}
		}
		
	
	}while( posFunction != NOT_FOUND );
	

}	

void CAIPIEditorView::WSPAddSelectedVBSFUNCTIONS(long nStartSel, long nEndSel, bool commentFlag)
{
	LPSTR szKeyWord = "FUNCTION";
	LPSTR szOpenParenthesis = "(";
	LPSTR szCloseParenthesis = ")";
	long posFunction = 0;
	long posStart = nStartSel; 
	CScintillaCtrl& rCtrl = GetCtrl();
	
	CString str;
	
	do 
	{	
		
		if( posStart == NOT_FOUND )
		{
			posStart = nEndSel;
		}
		//AfxMessageBox(_T("PosRule"));
		posFunction = WSPSearchToken(posStart, nEndSel, szKeyWord);	
		//str.Format(_T("Pos Rule %d"), posRule);
		//AfxMessageBox(str);

		//str.Format(_T("Pos Start %d"), posStart);
		//AfxMessageBox(str);

		
	
		if( posFunction != NOT_FOUND  )
		{
			long posNextFunction = WSPSearchToken(posFunction + 9, nEndSel, szKeyWord );
			//str.Format(_T("posNextRule... %d"), posNextRule);
			//AfxMessageBox(str);
		
			
			
			//Check if the keyword it´s not part of another larger word
			int prevSymbol = rCtrl.GetCharAt( posFunction - 1 );
			//str.Format(_T("Prev Symbol %d"), prevSymbol);
			//AfxMessageBox(str);
			if( prevSymbol != SPACE && prevSymbol != NEW_LINE && prevSymbol != CARRIAGE_RETURN && prevSymbol != NUL && prevSymbol != HORIZONTAL_TAB)
			{
				posStart = posNextFunction;
				continue;
			}
			int postSymbol = rCtrl.GetCharAt( posFunction + 8 );
			//str.Format(_T("Post Symbol %d"), postSymbol);
			//AfxMessageBox(str);
			
			if( postSymbol != SPACE && postSymbol != NEW_LINE && postSymbol != CARRIAGE_RETURN && postSymbol != NUL && prevSymbol != HORIZONTAL_TAB)
			{
				posStart = posNextFunction;
				continue;		
			}
			
			if( commentFlag )
			{
				//Check for line comment at the begining of the rule
				bool lnComment = WSPCheckLineComment(posFunction, posFunction + 8);
				if( lnComment )
				{
					//AfxMessageBox(_T("Line comment found"));
					posStart = posFunction + 5;
					continue;
				}

				//Check for block comment between the rule
				bool blkComment = WSPCheckBlockComment(nStartSel, nEndSel, posFunction);
				//str.Format(_T(" handle Block Comment 2... %d"), blkComment);
				//AfxMessageBox(str);
			
				if( blkComment )
				{
					posStart = posNextFunction;
					continue;
				}
			}

			
			long posCloseParenthesis = WSPSearchToken( posFunction, nEndSel, szCloseParenthesis); 
			
			int r = WSPParseVBSFunction( posFunction -1, posCloseParenthesis );
			
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				long posOpenParenthesis = WSPSearchToken(posFunction, posCloseParenthesis, szOpenParenthesis); 

				CString sFunctionName = WSPGetText(posFunction + 8, posOpenParenthesis);
				if( sFunctionName == _T("OVERLOAD" ))
				{
					return;
				}
				
				if( sFunctionName != _T("EMPTY") )
				{
					
					CString sParameter = WSPFormatParameters( posOpenParenthesis, posCloseParenthesis );
					if( sParameter != _T("COMMENT_ERROR") )
					{
						sFunctionName.TrimRight();
						sFunctionName.TrimLeft();

						CString sFunctionParameter = _T("(") + sParameter + _T(")");
						//CString sFullRuleName = m_sRuleName + sRuleParameter; 
						//AfxMessageBox(m_sTokenName);
						//r = WSPAddNodeTree1(sFunctionName, sFunctionParameter, 12);
						r = WSPAddNodeTypeTree1(sFunctionName, sFunctionParameter, 12, AIPI_FUNCTION);
						//CWorkspaceTabView tab;
						//tab.printWSPTree1();
					}
				}

				posFunction = posNextFunction;				
				//posRule = WSPSearchToken(posCloseParenthesis, nEndSel, szKeyWord);
				//str.Format(_T("END CICLE   PosRule... %d"), posRule);
				//AfxMessageBox(str);

				
				if( posFunction != NOT_FOUND )
				{
					posStart = posFunction;
					
				}
				
			}
			else
			{
				posStart = posFunction + 8;
			}
		}
		
	
	}while( posFunction != NOT_FOUND );
	

}	





void CAIPIEditorView::WSPAddSelectedVariables(long nStartSel, long nEndSel, LPSTR szType, int typelen, bool commentFlag)
{
	LPSTR szSemiColon = ";";
	long posIdType = 0;
	long posStart = nStartSel; 
	CScintillaCtrl& rCtrl = GetCtrl();
	
	CString str;
	
	do 
	{	
		
		if( posStart == NOT_FOUND )
		{
			posStart = nEndSel;
		}
		//AfxMessageBox(_T("PosIdType"));
		posIdType = WSPSearchToken(posStart, nEndSel, szType);	
		//str.Format(_T("Pos IdType %d"), posIdType);
		//AfxMessageBox(str);

		//str.Format(_T("Pos Start %d"), posStart);
		//AfxMessageBox(str);

		
	
		if( posIdType != NOT_FOUND  )
		{
			long posNextType = WSPSearchToken(posIdType + typelen + 1, nEndSel, szType );
			//str.Format(_T("posNextType... %d"), posNextType);
			//AfxMessageBox(str);
		
			
			
			//Check if the keyword it´s not part of another larger word
			int prevSymbol = rCtrl.GetCharAt( posIdType - 1 );
			//str.Format(_T("Prev Symbol %d"), prevSymbol);
			//AfxMessageBox(str);
			if( prevSymbol != SPACE && prevSymbol != NEW_LINE && prevSymbol != CARRIAGE_RETURN && prevSymbol != NUL && prevSymbol != HORIZONTAL_TAB)
			{
				posStart = posNextType;
				continue;
			}
			int postSymbol = rCtrl.GetCharAt( posIdType + typelen );
			//str.Format(_T("Post Symbol %d"), postSymbol);
			//AfxMessageBox(str);
			
			if( postSymbol != SPACE && postSymbol != NEW_LINE && postSymbol != CARRIAGE_RETURN && postSymbol != NUL && prevSymbol != HORIZONTAL_TAB)
			{
				posStart = posNextType;
				continue;		
			}
			
			if( commentFlag )
			{
				//Check for line comment at the begining of the rule
				bool lnComment = WSPCheckLineComment(posIdType, posIdType + typelen);
				if( lnComment )
				{
					//AfxMessageBox(_T("Line comment found"));
					posStart = posIdType + typelen +1;
					continue;
				}

				//Check for block comment between the rule
				bool blkComment = WSPCheckBlockComment(nStartSel, nEndSel, posIdType);
				//str.Format(_T(" handle Block Comment 2... %d"), blkComment);
				//AfxMessageBox(str);
			
				if( blkComment )
				{
					posStart = posNextType;
					continue;
				}
			}

			
			long posSemiColon = WSPSearchToken( posIdType, nEndSel, szSemiColon); 
			
			int r = WSPParseVariable( posIdType -1, posSemiColon );
			
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				CString sVariableName = WSPGetText(posIdType + typelen, posSemiColon);
				if( sVariableName == _T("OVERLOAD" ))
				{
					return;
				}
				
				if( sVariableName != _T("EMPTY") )
				{
					sVariableName.TrimRight();
					sVariableName.TrimLeft();

					CString sVariableParameter = _T("");
					//CString sFullRuleName = m_sRuleName + sRuleParameter; 
					//AfxMessageBox(m_sTokenName);
					//r = WSPAddNodeTree1(sVariableName, sVariableParameter, 6);
					r = WSPAddNodeTypeTree1(sVariableName, sVariableParameter, 8, AIPI_VARIABLE);	
				
				}
				
				
				posIdType = posNextType;				
				//str.Format(_T("END CICLE   PosIdType... %d"), posIdType);
				//AfxMessageBox(str);

				
				if( posIdType != NOT_FOUND )
				{
					posStart = posIdType;
					
				}
				
			}
			else
			{
				posStart = posIdType + typelen +1;
			}
		}
		
	
	}while( posIdType != NOT_FOUND );

}	


void CAIPIEditorView::WSPAddSelectedClasses(long nStartSel, long nEndSel, bool commentFlag)
{
	LPSTR szOpenBrace = "{";
	LPSTR szKeyWord = "CLASS";
	long posClass = 0;
	long posStart = nStartSel; 
	CScintillaCtrl& rCtrl = GetCtrl();
	
	CString str;
	
	do 
	{	
		
		if( posStart == NOT_FOUND )
		{
			posStart = nEndSel;
		}
		//AfxMessageBox(_T("PosIdType"));
		posClass = WSPSearchToken(posStart, nEndSel, szKeyWord);	
		//str.Format(_T("Pos IdType %d"), posIdType);
		//AfxMessageBox(str);

		//str.Format(_T("Pos Start %d"), posStart);
		//AfxMessageBox(str);

		
	
		if( posClass != NOT_FOUND  )
		{
			long posNextClass = WSPSearchToken(posClass + 6, nEndSel, szKeyWord );
			//str.Format(_T("posNextType... %d"), posNextType);
			//AfxMessageBox(str);
		
			
			
			//Check if the keyword it´s not part of another larger word
			int prevSymbol = rCtrl.GetCharAt( posClass - 1 );
			//str.Format(_T("Prev Symbol %d"), prevSymbol);
			//AfxMessageBox(str);
			if( prevSymbol != SPACE && prevSymbol != NEW_LINE && prevSymbol != CARRIAGE_RETURN && prevSymbol != NUL && prevSymbol != HORIZONTAL_TAB)
			{
				posStart = posNextClass;
				continue;
			}
			int postSymbol = rCtrl.GetCharAt( posClass + 5 );
			//str.Format(_T("Post Symbol %d"), postSymbol);
			//AfxMessageBox(str);
			
			if( postSymbol != SPACE && postSymbol != NEW_LINE && postSymbol != CARRIAGE_RETURN && postSymbol != NUL && prevSymbol != HORIZONTAL_TAB)
			{
				posStart = posNextClass;
				continue;		
			}
			
			if( commentFlag )
			{
				//Check for line comment at the begining of the rule
				bool lnComment = WSPCheckLineComment(posClass, posClass + 5);
				if( lnComment )
				{
					//AfxMessageBox(_T("Line comment found"));
					posStart = posClass + 6;
					continue;
				}

				//Check for block comment between the rule
				bool blkComment = WSPCheckBlockComment(nStartSel, nEndSel, posClass);
				//str.Format(_T(" handle Block Comment 2... %d"), blkComment);
				//AfxMessageBox(str);
			
				if( blkComment )
				{
					posStart = posNextClass;
					continue;
				}
			}

			
			long posOpenBrace = WSPSearchToken( posClass, nEndSel, szOpenBrace); 
			
			int r = WSPParseClass( posClass -1, posOpenBrace );
			
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				CString sClassName = WSPGetText(posClass + 5, posOpenBrace);
				if( sClassName == _T("OVERLOAD" ))
				{
					return;
				}
				
				if( sClassName != _T("EMPTY") )
				{
					sClassName.TrimRight();
					sClassName.TrimLeft();

					CString sClassParameter = _T("");
					//CString sFullRuleName = m_sRuleName + sRuleParameter; 
					//AfxMessageBox(m_sTokenName);
					//r = WSPAddNodeTree1(sClassName, sClassParameter, 8);
					r = WSPAddNodeTypeTree1(sClassName, sClassParameter, 14, AIPI_CLASS);	
				
				}
				
				
				posClass = posNextClass;				
				//str.Format(_T("END CICLE   PosIdType... %d"), posIdType);
				//AfxMessageBox(str);

				
				if( posClass != NOT_FOUND )
				{
					posStart = posClass;
					
				}
				
			}
			else
			{
				posStart = posClass + 6;
			}
		}
		
	
	}while( posClass != NOT_FOUND );

}	



void CAIPIEditorView::WSPAddSelectedQueries(long nStartSel, long nEndSel, bool commentFlag)
{
	LPSTR szEqual = "=";
	LPSTR szKeyWord = "SQLQUERY";
	long posQuery = 0;
	long posStart = nStartSel; 
	CScintillaCtrl& rCtrl = GetCtrl();
	
	CString str;
	
	do 
	{	
		
		if( posStart == NOT_FOUND )
		{
			posStart = nEndSel;
		}
		//AfxMessageBox(_T("PosIdType"));
		posQuery = WSPSearchToken(posStart, nEndSel, szKeyWord);	
		//str.Format(_T("Pos IdType %d"), posIdType);
		//AfxMessageBox(str);

		//str.Format(_T("Pos Start %d"), posStart);
		//AfxMessageBox(str);

		
	
		if( posQuery != NOT_FOUND  )
		{
			long posNextQuery = WSPSearchToken(posQuery + 9, nEndSel, szKeyWord );
			//str.Format(_T("posNextType... %d"), posNextType);
			//AfxMessageBox(str);
		
			
			
			//Check if the keyword it´s not part of another larger word
			int prevSymbol = rCtrl.GetCharAt( posQuery - 1 );
			//str.Format(_T("Prev Symbol %d"), prevSymbol);
			//AfxMessageBox(str);
			if( prevSymbol != SPACE && prevSymbol != NEW_LINE && prevSymbol != CARRIAGE_RETURN && prevSymbol != NUL && prevSymbol != HORIZONTAL_TAB)
			{
				posStart = posNextQuery;
				continue;
			}
			int postSymbol = rCtrl.GetCharAt( posQuery + 8 );
			//str.Format(_T("Post Symbol %d"), postSymbol);
			//AfxMessageBox(str);
			
			if( postSymbol != SPACE && postSymbol != NEW_LINE && postSymbol != CARRIAGE_RETURN && postSymbol != NUL && prevSymbol != HORIZONTAL_TAB)
			{
				posStart = posNextQuery;
				continue;		
			}
			
			if( commentFlag )
			{
				//Check for line comment at the begining of the rule
				bool lnComment = WSPCheckLineComment(posQuery, posQuery + 8);
				if( lnComment )
				{
					//AfxMessageBox(_T("Line comment found"));
					posStart = posQuery + 9;
					continue;
				}

				//Check for block comment between the rule
				bool blkComment = WSPCheckBlockComment(nStartSel, nEndSel, posQuery);
				//str.Format(_T(" handle Block Comment 2... %d"), blkComment);
				//AfxMessageBox(str);
			
				if( blkComment )
				{
					posStart = posNextQuery;
					continue;
				}
			}

			
			long posEqual = WSPSearchToken( posQuery, nEndSel, szEqual); 
			
			int r = WSPParseQuery( posQuery -1, posEqual );
			
			if( r != AIPI_ERROR && r != NOT_FOUND )
			{
				CString sQueryName = WSPGetText(posQuery + 8, posEqual);
				if( sQueryName == _T("OVERLOAD" ))
				{
					return;
				}
				
				if( sQueryName != _T("EMPTY") )
				{
					sQueryName.TrimRight();
					sQueryName.TrimLeft();

					CString sQueryParameter = _T("");
					//CString sFullRuleName = m_sRuleName + sRuleParameter; 
					//AfxMessageBox(m_sTokenName);
					//r = WSPAddNodeTree1(sQueryName, sQueryParameter, 4);
					r = WSPAddNodeTypeTree1(sQueryName, sQueryParameter, 4, AIPI_QUERY);	
				
				}
				
				
				posQuery = posNextQuery;				
				//str.Format(_T("END CICLE   PosIdType... %d"), posIdType);
				//AfxMessageBox(str);

				
				if( posQuery != NOT_FOUND )
				{
					posStart = posQuery;
					
				}
				
			}
			else
			{
				posStart = posQuery + 9;
			}
		}
		
	
	}while( posQuery != NOT_FOUND );

}	



void CAIPIEditorView::WSPDeleteSelectedRules(long nStartSel, long nEndSel, bool commentFlag)
{
		LPSTR szKeyWord = "RULE";
		LPSTR szCloseParenthesis = ")";
		
			
		CScintillaCtrl& rCtrl = GetCtrl();
		//Gets the position of the clipboard paste 
		//long nStartSel = rCtrl.GetSelectionStart();
		//long nEndSel = rCtrl.GetSelectionEnd();
			
		long posRule = 0;
		long posStart = nStartSel; 
		
		
		CString str;
		
		//str.Format(_T("Start Sel %d"), nStartSel);
		//AfxMessageBox(str);
		//str.Format(_T("End Sel %d"), nEndSel);
		//AfxMessageBox(str);

		//Check for rules that are cut in the beginnig selection
		//and the syntaxis is incomplete
		long posPrevRule = WSPSearchToken(nStartSel, 0, szKeyWord);
		long posCurrentCloseParenthesis = WSPSearchToken(nStartSel, nEndSel, szCloseParenthesis);
		if( posPrevRule != NOT_FOUND && posCurrentCloseParenthesis != NOT_FOUND )
		{
			int r = WSPParseRule( posPrevRule -1, posCurrentCloseParenthesis);
			if( r != AIPI_ERROR || r != NOT_FOUND )
			{
				//Then the rule is cut, it must be deleted
				WSPDeleteRule(nStartSel, true);
			}	
		}
		
	
		do 
		{	
		
			if( posStart == NOT_FOUND )
			{
				posStart = nEndSel;
			}
			//AfxMessageBox(_T("PosRule"));
			posRule = WSPSearchToken(posStart, nEndSel, szKeyWord);	
			str.Format(_T("Pos Rule %d"), posRule);
			//AfxMessageBox(str);
			
	

			//str.Format(_T("Pos Start %d"), posStart);
			//AfxMessageBox(str);
			
			if( posRule != NOT_FOUND  )
			{
				long posNextRule = WSPSearchToken(posRule + 4, nEndSel, szKeyWord );
				//str.Format(_T("posNextRule... %d"), posNextRule);
				//AfxMessageBox(str);
					
				//Check if the keyword it´s not part of another larger word
				int prevSymbol = rCtrl.GetCharAt( posRule - 1 );
				//str.Format(_T("Prev Symbol %d"), prevSymbol);
				//AfxMessageBox(str);
				if( prevSymbol != SPACE && prevSymbol != NEW_LINE && prevSymbol != CARRIAGE_RETURN && prevSymbol != NUL )
				{
					posStart = posNextRule;
					continue;
				}
				int postSymbol = rCtrl.GetCharAt( posRule + 4 );
				//str.Format(_T("Post Symbol %d"), postSymbol);
				//AfxMessageBox(str);
			
				if( postSymbol != SPACE && postSymbol != NEW_LINE && postSymbol != CARRIAGE_RETURN && postSymbol != NUL )
				{
					posStart = posNextRule;
					continue;		
				}
			
				if( commentFlag )
				{
					//Check for line comment at the begining of the rule
					bool lnComment = WSPCheckLineComment(posRule, posRule + 4);
					if( lnComment )
					{
						//AfxMessageBox(_T("Line comment found"));
						posStart = posRule + 5;
						continue;
					}

					//Check for block comment between the rule
				
					bool blkComment = WSPCheckBlockComment(nStartSel, nEndSel, posRule);
					//str.Format(_T(" handle Block Comment 2... %d"), blkComment);
					//AfxMessageBox(str);
			
					if( blkComment )
					{
						posStart = posNextRule;
						continue;
					}
				}
				
				
				
				//str.Format(_T("Current Token... %d"), m_lookahead);
				//AfxMessageBox(str);
				//AfxMessageBox(m_sTokenName);
				long posCloseParenthesis = WSPSearchToken( posRule, nEndSel, szCloseParenthesis);
				if( posCloseParenthesis != NOT_FOUND )
				{
					int r = WSPParseRule( posRule -1, posCloseParenthesis);
					if( r == AIPI_ERROR || r == NOT_FOUND )
					{
						posStart = posNextRule;
						continue;
					}
				}

				LPSTR szDobleQuotation = "\"";
				//AfxMessageBox(_T("entro al parser"));
				long posStartDobleQuotation = WSPSearchToken(posRule, nEndSel, szDobleQuotation );
				//str.Format(_T("Pos Start DobleQ...%d  " ), posStartDobleQuotation);
				//AfxMessageBox(str);
				if( posStartDobleQuotation != NOT_FOUND )
				{
					long posEndDobleQuotation = WSPSearchToken(posStartDobleQuotation + 1, nEndSel, szDobleQuotation);
					//str.Format(_T("Pos End DobleQ...%d  " ), posEndDobleQuotation);
					//AfxMessageBox(str);
					if ( posEndDobleQuotation != NOT_FOUND )
					{
					
						CString sRuleName =  WSPGetText( posStartDobleQuotation +1, posEndDobleQuotation );
						if( sRuleName == _T("OVERLOAD" ))
						{
							return;
						}
						
						if( sRuleName != _T("EMPTY") )
						{
							sRuleName = WSPFormatRuleNameOpt(sRuleName );
							//AfxMessageBox(_T("sRuleName:::"));
							//AfxMessageBox(sRuleName);
							WSPDeleteNodeTree1(sRuleName);
							
						}
						
						posStart = posNextRule;
						continue;
					}
					else
					{
						return;
					}
				
				}
				else
				{
					return;
				}
				//str.Format(_T("END CICLE   PosRule... %d"), posRule);
				//AfxMessageBox(str);
				
				
			}
		
	
		}while( posRule != NOT_FOUND );
	

}


void CAIPIEditorView::WSPDeleteSelectedJSFunctions(long nStartSel, long nEndSel, bool commentFlag)
{
		LPSTR szKeyWord = "function";
		LPSTR szCloseParenthesis = ")";
			
		CScintillaCtrl& rCtrl = GetCtrl();
		//Gets the position of the clipboard paste 
		//long nStartSel = rCtrl.GetSelectionStart();
		//long nEndSel = rCtrl.GetSelectionEnd();
			
		long posFunction = 0;
		long posStart = nStartSel; 
		
		
		CString str;
		
		//str.Format(_T("Start Sel %d"), nStartSel);
		//AfxMessageBox(str);
		//str.Format(_T("End Sel %d"), nEndSel);
		//AfxMessageBox(str);

		//Check for jscript function that is cut in the beginnig selection
		//and the syntaxis is incomplete
		long posPrevFunction = WSPSearchToken(nStartSel, 0, szKeyWord);
		long posCurrentCloseParenthesis = WSPSearchToken(nStartSel, nEndSel, szCloseParenthesis);
		if( posPrevFunction != NOT_FOUND && posCurrentCloseParenthesis != NOT_FOUND )
		{
			int r = WSPParseJSFunction( posPrevFunction -1, posCurrentCloseParenthesis);
			if( r != AIPI_ERROR || r != NOT_FOUND )
			{
				//Then the variable is cut, it must be deleted
				WSPDeleteJSFunction(nStartSel, true);
			}	
		}
		
				
	
		do 
		{	
		
			if( posStart == NOT_FOUND )
			{
				posStart = nEndSel;
			}
			//AfxMessageBox(_T("PosRule"));
			posFunction = WSPSearchToken(posStart, nEndSel, szKeyWord);	
			//str.Format(_T("Pos Function %d"), posFunction);
			//AfxMessageBox(str);

			//str.Format(_T("Pos Start %d"), posStart);
			//AfxMessageBox(str);
			
			if( posFunction != NOT_FOUND  )
			{
				long posNextFunction = WSPSearchToken(posFunction + 8, nEndSel, szKeyWord );
				//str.Format(_T("posNextRule... %d"), posNextRule);
				//AfxMessageBox(str);
					
				//Check if the keyword it´s not part of another larger word
				int prevSymbol = rCtrl.GetCharAt( posFunction - 1 );
				//str.Format(_T("Prev Symbol %d"), prevSymbol);
				//AfxMessageBox(str);
				if( prevSymbol != SPACE && prevSymbol != NEW_LINE && prevSymbol != CARRIAGE_RETURN && prevSymbol != NUL )
				{
					posStart = posNextFunction;
					continue;
				}
				int postSymbol = rCtrl.GetCharAt( posFunction + 8 );
				//str.Format(_T("Post Symbol %d"), postSymbol);
				//AfxMessageBox(str);
			
				if( postSymbol != SPACE && postSymbol != NEW_LINE && postSymbol != CARRIAGE_RETURN && postSymbol != NUL )
				{
					posStart = posNextFunction;
					continue;		
				}
			
				if( commentFlag )
				{
					//Check for line comment at the begining of the rule
					bool lnComment = WSPCheckLineComment(posFunction, posFunction + 8);
					if( lnComment )
					{
						//AfxMessageBox(_T("Line comment found"));
						posStart = posFunction + 9;
						continue;
					}

					//Check for block comment between the rule
				
					bool blkComment = WSPCheckBlockComment(nStartSel, nEndSel, posFunction);
					//str.Format(_T(" handle Block Comment 2... %d"), blkComment);
					//AfxMessageBox(str);
			
					if( blkComment )
					{
						posStart = posNextFunction;
						continue;
					}
				}
				
				
				LPSTR szCloseParenthesis = ")";
		
				//str.Format(_T("Current Token... %d"), m_lookahead);
				//AfxMessageBox(str);
				//AfxMessageBox(m_sTokenName);
				long posCloseParenthesis = WSPSearchToken( posFunction, nEndSel, szCloseParenthesis);
				if( posCloseParenthesis != NOT_FOUND )
				{
					int r = WSPParseJSFunction( posFunction -1, posCloseParenthesis);
					if( r == AIPI_ERROR || r == NOT_FOUND )
					{
						posStart = posNextFunction;
						continue;
					}
				}
				LPSTR szOpenParenthesis = "(";
				long posOpenParenthesis = WSPSearchToken(posFunction, nEndSel, szOpenParenthesis);
				//str.Format(_T("Pos Open Parent...%d  " ), posOpenParenthesis);
				//AfxMessageBox(str);
				
				if ( posOpenParenthesis != NOT_FOUND )
				{
					
					CString sFunctionName = WSPGetText(posFunction + 8, posOpenParenthesis);
					if( sFunctionName == _T("OVERLOAD" ))
					{
						return;
					}
						
					if( sFunctionName != _T("EMPTY") )
					{
						sFunctionName.TrimRight();
						sFunctionName.TrimLeft();
						WSPDeleteNodeTree1(sFunctionName);
					}

					posStart = posNextFunction;
					continue;
					
				}
				else
				{
					return;
				}
			}			
			else
			{
				return;
			}
			//str.Format(_T("END CICLE   PosRule... %d"), posRule);
			//AfxMessageBox(str);
			
		}while( posFunction != NOT_FOUND );
	

}



void CAIPIEditorView::WSPDeleteSelectedVBSFunctions(long nStartSel, long nEndSel, bool commentFlag)
{
		LPSTR szKeyWord = "Function";
		LPSTR szCloseParenthesis = ")";
			
		CScintillaCtrl& rCtrl = GetCtrl();
		//Gets the position of the clipboard paste 
		//long nStartSel = rCtrl.GetSelectionStart();
		//long nEndSel = rCtrl.GetSelectionEnd();
			
		long posFunction = 0;
		long posStart = nStartSel; 
		
		
		CString str;
		
		//str.Format(_T("Start Sel %d"), nStartSel);
		//AfxMessageBox(str);
		//str.Format(_T("End Sel %d"), nEndSel);
		//AfxMessageBox(str);

		//Check for jscript function that is cut in the beginnig selection
		//and the syntaxis is incomplete
		long posPrevFunction = WSPSearchToken(nStartSel, 0, szKeyWord);
		long posCurrentCloseParenthesis = WSPSearchToken(nStartSel, nEndSel, szCloseParenthesis);
		if( posPrevFunction != NOT_FOUND && posCurrentCloseParenthesis != NOT_FOUND )
		{
			int r = WSPParseVBSFunction( posPrevFunction -1, posCurrentCloseParenthesis);
			if( r != AIPI_ERROR || r != NOT_FOUND )
			{
				//Then the variable is cut, it must be deleted
				WSPDeleteVBSFunction(nStartSel, true);
			}	
		}
		
				
	
		do 
		{	
		
			if( posStart == NOT_FOUND )
			{
				posStart = nEndSel;
			}
			//AfxMessageBox(_T("PosRule"));
			posFunction = WSPSearchToken(posStart, nEndSel, szKeyWord);	
			//str.Format(_T("Pos Function %d"), posFunction);
			//AfxMessageBox(str);

			//str.Format(_T("Pos Start %d"), posStart);
			//AfxMessageBox(str);
			
			if( posFunction != NOT_FOUND  )
			{
				long posNextFunction = WSPSearchToken(posFunction + 8, nEndSel, szKeyWord );
				//str.Format(_T("posNextRule... %d"), posNextRule);
				//AfxMessageBox(str);
					
				//Check if the keyword it´s not part of another larger word
				int prevSymbol = rCtrl.GetCharAt( posFunction - 1 );
				//str.Format(_T("Prev Symbol %d"), prevSymbol);
				//AfxMessageBox(str);
				if( prevSymbol != SPACE && prevSymbol != NEW_LINE && prevSymbol != CARRIAGE_RETURN && prevSymbol != NUL )
				{
					posStart = posNextFunction;
					continue;
				}
				int postSymbol = rCtrl.GetCharAt( posFunction + 8 );
				//str.Format(_T("Post Symbol %d"), postSymbol);
				//AfxMessageBox(str);
			
				if( postSymbol != SPACE && postSymbol != NEW_LINE && postSymbol != CARRIAGE_RETURN && postSymbol != NUL )
				{
					posStart = posNextFunction;
					continue;		
				}
			
				if( commentFlag )
				{
					//Check for line comment at the begining of the rule
					bool lnComment = WSPCheckLineComment(posFunction, posFunction + 8);
					if( lnComment )
					{
						//AfxMessageBox(_T("Line comment found"));
						posStart = posFunction + 9;
						continue;
					}

					//Check for block comment between the rule
				
					bool blkComment = WSPCheckBlockComment(nStartSel, nEndSel, posFunction);
					//str.Format(_T(" handle Block Comment 2... %d"), blkComment);
					//AfxMessageBox(str);
			
					if( blkComment )
					{
						posStart = posNextFunction;
						continue;
					}
				}
				
				
				LPSTR szCloseParenthesis = ")";
		
				//str.Format(_T("Current Token... %d"), m_lookahead);
				//AfxMessageBox(str);
				//AfxMessageBox(m_sTokenName);
				long posCloseParenthesis = WSPSearchToken( posFunction, nEndSel, szCloseParenthesis);
				if( posCloseParenthesis != NOT_FOUND )
				{
					int r = WSPParseVBSFunction( posFunction -1, posCloseParenthesis);
					if( r == AIPI_ERROR || r == NOT_FOUND )
					{
						posStart = posNextFunction;
						continue;
					}
				}
				LPSTR szOpenParenthesis = "(";
				long posOpenParenthesis = WSPSearchToken(posFunction, nEndSel, szOpenParenthesis);
				//str.Format(_T("Pos Open Parent...%d  " ), posOpenParenthesis);
				//AfxMessageBox(str);
				
				if ( posOpenParenthesis != NOT_FOUND )
				{
					
					CString sFunctionName = WSPGetText(posFunction + 8, posOpenParenthesis);
					if( sFunctionName == _T("OVERLOAD" ))
					{
						return;
					}
						
					if( sFunctionName != _T("EMPTY") )
					{
						sFunctionName.TrimRight();
						sFunctionName.TrimLeft();
						WSPDeleteNodeTree1(sFunctionName);
					}

					posStart = posNextFunction;
					continue;
					
				}
				else
				{
					return;
				}
			}			
			else
			{
				return;
			}
			//str.Format(_T("END CICLE   PosRule... %d"), posRule);
			//AfxMessageBox(str);
			
		}while( posFunction != NOT_FOUND );
	

}



void CAIPIEditorView::WSPDeleteSelectedVBSFUNCTIONS(long nStartSel, long nEndSel, bool commentFlag)
{
		LPSTR szKeyWord = "FUNCTION";
		LPSTR szCloseParenthesis = ")";
			
		CScintillaCtrl& rCtrl = GetCtrl();
		//Gets the position of the clipboard paste 
		//long nStartSel = rCtrl.GetSelectionStart();
		//long nEndSel = rCtrl.GetSelectionEnd();
			
		long posFunction = 0;
		long posStart = nStartSel; 
		
		
		CString str;
		
		//str.Format(_T("Start Sel %d"), nStartSel);
		//AfxMessageBox(str);
		//str.Format(_T("End Sel %d"), nEndSel);
		//AfxMessageBox(str);

		//Check for jscript function that is cut in the beginnig selection
		//and the syntaxis is incomplete
		long posPrevFunction = WSPSearchToken(nStartSel, 0, szKeyWord);
		long posCurrentCloseParenthesis = WSPSearchToken(nStartSel, nEndSel, szCloseParenthesis);
		if( posPrevFunction != NOT_FOUND && posCurrentCloseParenthesis != NOT_FOUND )
		{
			int r = WSPParseVBSFunction( posPrevFunction -1, posCurrentCloseParenthesis);
			if( r != AIPI_ERROR || r != NOT_FOUND )
			{
				//Then the variable is cut, it must be deleted
				WSPDeleteVBSFunction(nStartSel, true);
			}	
		}
		
				
	
		do 
		{	
		
			if( posStart == NOT_FOUND )
			{
				posStart = nEndSel;
			}
			//AfxMessageBox(_T("PosRule"));
			posFunction = WSPSearchToken(posStart, nEndSel, szKeyWord);	
			//str.Format(_T("Pos Function %d"), posFunction);
			//AfxMessageBox(str);

			//str.Format(_T("Pos Start %d"), posStart);
			//AfxMessageBox(str);
			
			if( posFunction != NOT_FOUND  )
			{
				long posNextFunction = WSPSearchToken(posFunction + 8, nEndSel, szKeyWord );
				//str.Format(_T("posNextRule... %d"), posNextRule);
				//AfxMessageBox(str);
					
				//Check if the keyword it´s not part of another larger word
				int prevSymbol = rCtrl.GetCharAt( posFunction - 1 );
				//str.Format(_T("Prev Symbol %d"), prevSymbol);
				//AfxMessageBox(str);
				if( prevSymbol != SPACE && prevSymbol != NEW_LINE && prevSymbol != CARRIAGE_RETURN && prevSymbol != NUL )
				{
					posStart = posNextFunction;
					continue;
				}
				int postSymbol = rCtrl.GetCharAt( posFunction + 8 );
				//str.Format(_T("Post Symbol %d"), postSymbol);
				//AfxMessageBox(str);
			
				if( postSymbol != SPACE && postSymbol != NEW_LINE && postSymbol != CARRIAGE_RETURN && postSymbol != NUL )
				{
					posStart = posNextFunction;
					continue;		
				}
			
				if( commentFlag )
				{
					//Check for line comment at the begining of the rule
					bool lnComment = WSPCheckLineComment(posFunction, posFunction + 8);
					if( lnComment )
					{
						//AfxMessageBox(_T("Line comment found"));
						posStart = posFunction + 9;
						continue;
					}

					//Check for block comment between the rule
				
					bool blkComment = WSPCheckBlockComment(nStartSel, nEndSel, posFunction);
					//str.Format(_T(" handle Block Comment 2... %d"), blkComment);
					//AfxMessageBox(str);
			
					if( blkComment )
					{
						posStart = posNextFunction;
						continue;
					}
				}
				
				
				LPSTR szCloseParenthesis = ")";
		
				//str.Format(_T("Current Token... %d"), m_lookahead);
				//AfxMessageBox(str);
				//AfxMessageBox(m_sTokenName);
				long posCloseParenthesis = WSPSearchToken( posFunction, nEndSel, szCloseParenthesis);
				if( posCloseParenthesis != NOT_FOUND )
				{
					int r = WSPParseVBSFunction( posFunction -1, posCloseParenthesis);
					if( r == AIPI_ERROR || r == NOT_FOUND )
					{
						posStart = posNextFunction;
						continue;
					}
				}
				LPSTR szOpenParenthesis = "(";
				long posOpenParenthesis = WSPSearchToken(posFunction, nEndSel, szOpenParenthesis);
				//str.Format(_T("Pos Open Parent...%d  " ), posOpenParenthesis);
				//AfxMessageBox(str);
				
				if ( posOpenParenthesis != NOT_FOUND )
				{
					
					CString sFunctionName = WSPGetText(posFunction + 8, posOpenParenthesis);
					if( sFunctionName == _T("OVERLOAD" ))
					{
						return;
					}
						
					if( sFunctionName != _T("EMPTY") )
					{
						sFunctionName.TrimRight();
						sFunctionName.TrimLeft();
						WSPDeleteNodeTree1(sFunctionName);
					}

					posStart = posNextFunction;
					continue;
					
				}
				else
				{
					return;
				}
			}			
			else
			{
				return;
			}
			//str.Format(_T("END CICLE   PosRule... %d"), posRule);
			//AfxMessageBox(str);
			
		}while( posFunction != NOT_FOUND );
	

}



void CAIPIEditorView::WSPDeleteSelectedFunctions(long nStartSel, long nEndSel, LPSTR szType, int typelen, bool commentFlag)
{
			
		CScintillaCtrl& rCtrl = GetCtrl();
		//Gets the position of the clipboard paste 
		//long nStartSel = rCtrl.GetSelectionStart();
		//long nEndSel = rCtrl.GetSelectionEnd();
			
		long posIdType = 0;
		long posStart = nStartSel; 
		LPSTR szOpenParenthesis = "(";
		LPSTR szCloseParenthesis = ")";

		
		CString str;
		
		//str.Format(_T("Start Sel %d"), nStartSel);
		//AfxMessageBox(str);
		//str.Format(_T("End Sel %d"), nEndSel);
		//AfxMessageBox(str);

		//Check for function that are cut in the beginnig selection
		//and the syntaxis is incomplete
		long posPrevIdType = WSPSearchToken(nStartSel, 0, szType);
		long posCurrentCloseParenthesis = WSPSearchToken(nStartSel, nEndSel, szCloseParenthesis);
		if( posPrevIdType != NOT_FOUND && posCurrentCloseParenthesis != NOT_FOUND )
		{
			int r = WSPParseFunction( posPrevIdType -1, posCurrentCloseParenthesis);
			if( r != AIPI_ERROR || r != NOT_FOUND )
			{
				//Then the function is cut, it must be deleted
				WSPDeleteFunction(nStartSel, true);
			}	
		}
				
	
		do 
		{	
		
			if( posStart == NOT_FOUND )
			{
				posStart = nEndSel;
			}
			
			posIdType = WSPSearchToken(posStart, nEndSel, szType);	
			//str.Format(_T("FUNCTION Pos IdType %d"), posIdType);
			//AfxMessageBox(str);

			//str.Format(_T("Pos Start %d"), posStart);
			//AfxMessageBox(str);
			
			if( posIdType != NOT_FOUND  )
			{
				long posNextType = WSPSearchToken(posIdType + typelen, nEndSel, szType );
				//str.Format(_T("posNextType... %d"), posNextType);
				//AfxMessageBox(str);
					
				//Check if the keyword it´s not part of another larger word
				int prevSymbol = rCtrl.GetCharAt( posIdType - 1 );
				//str.Format(_T("Prev Symbol %d"), prevSymbol);
				//AfxMessageBox(str);
				if( prevSymbol != SPACE && prevSymbol != NEW_LINE && prevSymbol != CARRIAGE_RETURN && prevSymbol != NUL )
				{
					posStart = posNextType;
					continue;
				}
				int postSymbol = rCtrl.GetCharAt( posIdType + typelen );
				//str.Format(_T("Post Symbol %d"), postSymbol);
				//AfxMessageBox(str);
			
				if( postSymbol != SPACE && postSymbol != NEW_LINE && postSymbol != CARRIAGE_RETURN && postSymbol != NUL )
				{
					posStart = posNextType;
					continue;		
				}
			
				if( commentFlag )
				{
					//Check for line comment at the begining of the rule
					bool lnComment = WSPCheckLineComment(posIdType, posIdType + typelen);
					if( lnComment )
					{
						//AfxMessageBox(_T("Line comment found"));
						posStart = posIdType + typelen + 1;
						continue;
					}

					//Check for block comment between the rule
				
					bool blkComment = WSPCheckBlockComment(nStartSel, nEndSel, posIdType);
					//str.Format(_T(" handle Block Comment 2... %d"), blkComment);
					//AfxMessageBox(str);
			
					if( blkComment )
					{
						posStart = posNextType;
						continue;
					}
				}
				

				
				long posCloseParenthesis = WSPSearchToken( posIdType, nEndSel, szCloseParenthesis);
				//str.Format(_T("Pos Close Parent...%d  " ), posCloseParenthesis);
				//AfxMessageBox(str);
				if( posCloseParenthesis != NOT_FOUND )
				{
					int r = WSPParseFunction( posIdType -1, posCloseParenthesis);
					if( r == AIPI_ERROR || r == NOT_FOUND )
					{
						//AfxMessageBox(_T("Function error"));
						posStart = posNextType;
						continue;
					}
				}

				long posOpenParenthesis = WSPSearchToken(posIdType, nEndSel, szOpenParenthesis);
				//str.Format(_T("Pos Open Parent...%d  " ), posOpenParenthesis);
				//AfxMessageBox(str);
				
				if ( posOpenParenthesis != NOT_FOUND )
				{
					
						CString sFunctionName = WSPGetText(posIdType + typelen, posOpenParenthesis);
						if( sFunctionName == _T("OVERLOAD" ))
						{
							return;
						}
						
						if( sFunctionName != _T("EMPTY") )
						{
							sFunctionName.TrimRight();
							sFunctionName.TrimLeft();
							WSPDeleteNodeTree1(sFunctionName);
					
						}

						posStart = posNextType;
						continue;
					
				}
				else
				{
					return;
				}
			}
			else
			{
				return;
			}
			//str.Format(_T("END CICLE   PosIdType... %d"), posIdType);
			//AfxMessageBox(str);
		}while( posIdType != NOT_FOUND );
	

}


void CAIPIEditorView::WSPDeleteSelectedVariables(long nStartSel, long nEndSel, LPSTR szType, int typelen, bool commentFlag)
{
			
		CScintillaCtrl& rCtrl = GetCtrl();
		//Gets the position of the clipboard paste 
		//long nStartSel = rCtrl.GetSelectionStart();
		//long nEndSel = rCtrl.GetSelectionEnd();
		LPSTR szSemiColon = ";";	
		long posIdType = 0;
		long posStart = nStartSel; 
		
		
		CString str;
		
		//str.Format(_T("Start Sel %d"), nStartSel);
		//AfxMessageBox(str);
		//str.Format(_T("End Sel %d"), nEndSel);
		//AfxMessageBox(str);
	
		//Check for variable that are cut in the beginnig selection
		//and the syntaxis is incomplete
		long posPrevIdType = WSPSearchToken(nStartSel, 0, szType);
		long posCurrentSemiColon = WSPSearchToken(nStartSel, nEndSel, szSemiColon);
		if( posPrevIdType != NOT_FOUND && posCurrentSemiColon != NOT_FOUND )
		{
			int r = WSPParseVariable( posPrevIdType -1, posCurrentSemiColon);
			if( r != AIPI_ERROR || r != NOT_FOUND )
			{
				//Then the variable is cut, it must be deleted
				WSPDeleteVariable(nStartSel, true);
			}	
		}
				
	
		do 
		{	
		
			if( posStart == NOT_FOUND )
			{
				posStart = nEndSel;
			}
			
			posIdType = WSPSearchToken(posStart, nEndSel, szType);	
			//str.Format(_T("VAR Pos IdType %d"), posIdType);
			//AfxMessageBox(str);

			//str.Format(_T("Pos Start %d"), posStart);
			//AfxMessageBox(str);
			
			if( posIdType != NOT_FOUND  )
			{
				long posNextType = WSPSearchToken(posIdType + typelen, nEndSel, szType );
				//str.Format(_T("posNextRule... %d"), posNextRule);
				//AfxMessageBox(str);
					
				//Check if the keyword it´s not part of another larger word
				int prevSymbol = rCtrl.GetCharAt( posIdType - 1 );
				//str.Format(_T("Prev Symbol %d"), prevSymbol);
				//AfxMessageBox(str);
				if( prevSymbol != SPACE && prevSymbol != NEW_LINE && prevSymbol != CARRIAGE_RETURN && prevSymbol != NUL )
				{
					posStart = posNextType;
					continue;
				}
				int postSymbol = rCtrl.GetCharAt( posIdType + typelen );
				//str.Format(_T("Post Symbol %d"), postSymbol);
				//AfxMessageBox(str);
			
				if( postSymbol != SPACE && postSymbol != NEW_LINE && postSymbol != CARRIAGE_RETURN && postSymbol != NUL )
				{
					posStart = posNextType;
					continue;		
				}
			
				if( commentFlag )
				{
					//Check for line comment at the begining of the rule
					bool lnComment = WSPCheckLineComment(posIdType, posIdType + typelen);
					if( lnComment )
					{
						//AfxMessageBox(_T("Line comment found"));
						posStart = posIdType + typelen + 1;
						continue;
					}

					//Check for block comment between the rule
				
					bool blkComment = WSPCheckBlockComment(nStartSel, nEndSel, posIdType);
					//str.Format(_T(" handle Block Comment 2... %d"), blkComment);
					//AfxMessageBox(str);
			
					if( blkComment )
					{
						posStart = posNextType;
						continue;
					}
				}
				

				
				long posSemiColon = WSPSearchToken(posIdType, nEndSel, szSemiColon);
				//str.Format(_T("Pos Open Parent...%d  " ), posOpenParenthesis);
				//AfxMessageBox(str);
				

				if ( posSemiColon != NOT_FOUND )
				{
					int r = WSPParseVariable( posIdType -1, posSemiColon);
					if( r == AIPI_ERROR || r == NOT_FOUND )
					{
						//AfxMessageBox(_T("Variable error"));
						posStart = posNextType;
						continue;
					}
					
					CString sVariableName = WSPGetText(posIdType + typelen, posSemiColon);
					if( sVariableName == _T("OVERLOAD" ))
					{
						return;
					}
					
					
					if( sVariableName != _T("EMPTY") )
					{
						sVariableName.TrimRight();
						sVariableName.TrimLeft();

						WSPDeleteNodeTree1(sVariableName);
					
					}

					posStart = posNextType;
					continue;
					
				}
				else
				{
					return;
				}
			}
			else
			{
				return;
			}
			//str.Format(_T("END CICLE   PosRule... %d"), posRule);
			//AfxMessageBox(str);
		}while( posIdType != NOT_FOUND );
	

}



void CAIPIEditorView::WSPDeleteSelectedClasses(long nStartSel, long nEndSel,  bool commentFlag)
{
		
		LPSTR szKeyWord = "CLASS";
		LPSTR szOpenBrace = "{";
				

		CScintillaCtrl& rCtrl = GetCtrl();
		//Gets the position of the clipboard paste 
		//long nStartSel = rCtrl.GetSelectionStart();
		//long nEndSel = rCtrl.GetSelectionEnd();
			
		long posClass = 0;
		long posStart = nStartSel; 
		
		
		CString str;
		
		//str.Format(_T("Start Sel %d"), nStartSel);
		//AfxMessageBox(str);
		//str.Format(_T("End Sel %d"), nEndSel);
		//AfxMessageBox(str);
		
		//Check for class that are cut in the beginnig selection
		//and the syntaxis is incomplete
		long posPrevClass = WSPSearchToken(nStartSel, 0, szKeyWord);
		long posCurrentOpenBrace = WSPSearchToken(nStartSel, nEndSel, szOpenBrace);
		if( posPrevClass != NOT_FOUND && posCurrentOpenBrace != NOT_FOUND )
		{
			int r = WSPParseClass( posPrevClass -1, posCurrentOpenBrace);
			if( r != AIPI_ERROR || r != NOT_FOUND )
			{
				//Then the variable is cut, it must be deleted
				WSPDeleteClass(nStartSel, true);
			}	
		}
				
	
		do 
		{	
		
			if( posStart == NOT_FOUND )
			{
				posStart = nEndSel;
			}
			
			posClass = WSPSearchToken(posStart, nEndSel, szKeyWord);	
			//str.Format(_T("VAR Pos IdType %d"), posIdType);
			//AfxMessageBox(str);

			//str.Format(_T("Pos Start %d"), posStart);
			//AfxMessageBox(str);
			
			if( posClass != NOT_FOUND  )
			{
				long posNextClass = WSPSearchToken(posClass + 5, nEndSel, szKeyWord );
				//str.Format(_T("posNextRule... %d"), posNextRule);
				//AfxMessageBox(str);
					
				//Check if the keyword it´s not part of another larger word
				int prevSymbol = rCtrl.GetCharAt( posClass - 1 );
				//str.Format(_T("Prev Symbol %d"), prevSymbol);
				//AfxMessageBox(str);
				if( prevSymbol != SPACE && prevSymbol != NEW_LINE && prevSymbol != CARRIAGE_RETURN && prevSymbol != NUL )
				{
					posStart = posNextClass;
					continue;
				}
				int postSymbol = rCtrl.GetCharAt( posClass + 5 );
				//str.Format(_T("Post Symbol %d"), postSymbol);
				//AfxMessageBox(str);
			
				if( postSymbol != SPACE && postSymbol != NEW_LINE && postSymbol != CARRIAGE_RETURN && postSymbol != NUL )
				{
					posStart = posNextClass;
					continue;		
				}
			
				if( commentFlag )
				{
					//Check for line comment at the begining of the rule
					bool lnComment = WSPCheckLineComment(posClass, posClass + 5);
					if( lnComment )
					{
						//AfxMessageBox(_T("Line comment found"));
						posStart = posClass + 6;
						continue;
					}

					//Check for block comment between the rule
				
					bool blkComment = WSPCheckBlockComment(nStartSel, nEndSel, posClass);
					//str.Format(_T(" handle Block Comment 2... %d"), blkComment);
					//AfxMessageBox(str);
			
					if( blkComment )
					{
						posStart = posNextClass;
						continue;
					}
				}
				

				long posOpenBrace = WSPSearchToken(posClass, nEndSel, szOpenBrace);
				//str.Format(_T("Pos Open Parent...%d  " ), posOpenParenthesis);
				//AfxMessageBox(str);
				

				if ( posOpenBrace != NOT_FOUND )
				{
					int r = WSPParseClass( posClass -1, posOpenBrace);
					if( r == AIPI_ERROR || r == NOT_FOUND )
					{
						//AfxMessageBox(_T("Variable error"));
						posStart = posNextClass;
						continue;
					}
					
					CString sClassName = WSPGetText(posClass + 5, posOpenBrace);
					if( sClassName == _T("OVERLOAD" ))
					{
						return;
					}
					
					if( sClassName != _T("EMPTY") )
					{
						sClassName.TrimRight();
						sClassName.TrimLeft();

						WSPDeleteNodeTree1(sClassName);
					
					}

					posStart = posNextClass;
					continue;
					
				}
				else
				{
					return;
				}
			}
			else
			{
				return;
			}
			//str.Format(_T("END CICLE   PosRule... %d"), posRule);
			//AfxMessageBox(str);
		}while( posClass != NOT_FOUND );
	

}


void CAIPIEditorView::WSPDeleteSelectedQueries(long nStartSel, long nEndSel,  bool commentFlag)
{
		
		LPSTR szKeyWord = "SQLQUERY";
		LPSTR szEqual = "=";
				

		CScintillaCtrl& rCtrl = GetCtrl();
		//Gets the position of the clipboard paste 
		//long nStartSel = rCtrl.GetSelectionStart();
		//long nEndSel = rCtrl.GetSelectionEnd();
			
		long posQuery = 0;
		long posStart = nStartSel; 
		
		
		CString str;
		
		//str.Format(_T("Start Sel %d"), nStartSel);
		//AfxMessageBox(str);
		//str.Format(_T("End Sel %d"), nEndSel);
		//AfxMessageBox(str);
		
		//Check for class that are cut in the beginnig selection
		//and the syntaxis is incomplete
		long posPrevQuery = WSPSearchToken(nStartSel, 0, szKeyWord);
		long posCurrentEqual = WSPSearchToken(nStartSel, nEndSel, szEqual);
		if( posPrevQuery != NOT_FOUND && posCurrentEqual != NOT_FOUND )
		{
			int r = WSPParseQuery( posPrevQuery -1, posCurrentEqual);
			if( r != AIPI_ERROR || r != NOT_FOUND )
			{
				//Then the variable is cut, it must be deleted
				WSPDeleteQuery(nStartSel, true);
			}	
		}
				
	
		do 
		{	
		
			if( posStart == NOT_FOUND )
			{
				posStart = nEndSel;
			}
			
			posQuery = WSPSearchToken(posStart, nEndSel, szKeyWord);	
			//str.Format(_T("VAR Pos IdType %d"), posIdType);
			//AfxMessageBox(str);

			//str.Format(_T("Pos Start %d"), posStart);
			//AfxMessageBox(str);
			
			if( posQuery != NOT_FOUND  )
			{
				long posNextQuery = WSPSearchToken(posQuery + 8, nEndSel, szKeyWord );
				//str.Format(_T("posNextQuery... %d"), posNextQuery);
				//AfxMessageBox(str);
					
				//Check if the keyword it´s not part of another larger word
				int prevSymbol = rCtrl.GetCharAt( posQuery - 1 );
				//str.Format(_T("Prev Symbol %d"), prevSymbol);
				//AfxMessageBox(str);
				if( prevSymbol != SPACE && prevSymbol != NEW_LINE && prevSymbol != CARRIAGE_RETURN && prevSymbol != NUL )
				{
					posStart = posNextQuery;
					continue;
				}
				int postSymbol = rCtrl.GetCharAt( posQuery + 8 );
				//str.Format(_T("Post Symbol %d"), postSymbol);
				//AfxMessageBox(str);
			
				if( postSymbol != SPACE && postSymbol != NEW_LINE && postSymbol != CARRIAGE_RETURN && postSymbol != NUL )
				{
					posStart = posNextQuery;
					continue;		
				}
			
				if( commentFlag )
				{
					//Check for line comment at the begining of the rule
					bool lnComment = WSPCheckLineComment(posQuery, posQuery + 8);
					if( lnComment )
					{
						//AfxMessageBox(_T("Line comment found"));
						posStart = posQuery + 9;
						continue;
					}

					//Check for block comment between the rule
				
					bool blkComment = WSPCheckBlockComment(nStartSel, nEndSel, posQuery);
					//str.Format(_T(" handle Block Comment 2... %d"), blkComment);
					//AfxMessageBox(str);
			
					if( blkComment )
					{
						posStart = posNextQuery;
						continue;
					}
				}
				

				long posEqual = WSPSearchToken(posQuery, nEndSel, szEqual);
				//str.Format(_T("Pos Open Parent...%d  " ), posOpenParenthesis);
				//AfxMessageBox(str);
				

				if ( posEqual != NOT_FOUND )
				{
					int r = WSPParseQuery( posQuery -1, posEqual);
					if( r == AIPI_ERROR || r == NOT_FOUND )
					{
						//AfxMessageBox(_T("Variable error"));
						posStart = posNextQuery;
						continue;
					}
					
					CString sQueryName = WSPGetText(posQuery + 8, posEqual);
					if( sQueryName == _T("OVERLOAD" ))
					{
						return;
					}
					
					if( sQueryName != _T("EMPTY") )
					{
						sQueryName.TrimRight();
						sQueryName.TrimLeft();

						WSPDeleteNodeTree1(sQueryName);
					
					}

					posStart = posNextQuery;
					continue;
					
				}
				else
				{
					return;
				}
			}
			else
			{
				return;
			}
			//str.Format(_T("END CICLE   PosRule... %d"), posRule);
			//AfxMessageBox(str);
		}while( posQuery != NOT_FOUND );
	

}




CString CAIPIEditorView::WSPFormatRuleNameOpt(CString name)
{
	//CPerfTimer t;
	//t.Start();
	
	int	pos = 0;
	int prevPos = 0;		
	while( pos != NOT_FOUND )
	{
		prevPos = pos;
		pos = name.Find(_T(" "), pos );
		
		if( pos == NOT_FOUND )
		{
			name.TrimRight();
			//AfxMessageBox(name);
			//StopTimer(t, _T("Format Rule Name OPTIMIZED...."));
			return name;
		}
		
		if( pos > prevPos )
		{
			name += _T(" ");
			pos++;
			continue;
			//AfxMessageBox(_T("Hello"));
		}
		
		name.Delete(pos, 1);
			
		//CString str;
		//str.Format(_T("Current Pos... %d"), pos);
		//AfxMessageBox(str);
		//AfxMessageBox(name);
		
	}
	
	//StopTimer(t, _T("Format Rule Name OPTIMIZED...."));
	
	//AfxMessageBox(name);
return name;
}
	

CString CAIPIEditorView::WSPFormatRuleName(CString name)
{
	
	//CPerfTimer t;
	//t.Start();
	
	
	CString formatName = _T("");
	int pos = 0;
	int n = 0;
	int len = name.GetLength();

	/*
	pos = name.Find(_T(' '), pos );
	CString str;
	str.Format(_T("Current Pos... %d"), pos);
	AfxMessageBox(str);
			
	if( pos == NOT_FOUND )
	{
		return name;
	}	
	*/

	for( int i = 0; i<len; ++i )
	{
		++n;
		if( name.GetAt(i) == _T(' ') )
		{
			--n;
			continue;
				
		}
		
		/*			
		CString str;
		str.Format(_T("Current Pos... %d"), i);
		AfxMessageBox(str);
		*/

		if ( i != n )
		{
			
			n = i;
			formatName += _T(" ");
		}
		
		formatName += name[i]; 
		
	}

	//StopTimer(t, _T("Format Rule Name NORMAL...."));
	
	//AfxMessageBox(formatName);

return formatName;
}


int CAIPIEditorView::WSPCountFunctParameters(long posOpenParenthesis, long posCloseParenthesis )
{
	int nParameters = 1;
	LPSTR szComma = ",";
	CString sParameter = _T("");

		

	for( long i = posOpenParenthesis; i< posCloseParenthesis; ++i )
	{
		int pos = WSPSearchToken( i, posCloseParenthesis, szComma);
		if( pos != NOT_FOUND )
		{
			sParameter = WSPGetText(i, pos);
			sParameter.TrimLeft();
			sParameter.TrimRight();
			//AfxMessageBox(sParameter);

			m_vParameters.push_back(sParameter);
			++nParameters;
			i = pos+1;
		}
		else
		{
			sParameter = WSPGetText(posOpenParenthesis, posCloseParenthesis);
			if( sParameter == _T("") )
			{
				//AfxMessageBox(_T("Empty"));
				return 0;
			}
			else
			{
				sParameter.TrimLeft();
				sParameter.TrimRight();
				m_vParameters.push_back(sParameter);
				return 1;
			}
		}

		
	}


/*
CString str;
str.Format(_T("n Parameters...%d  " ), nParameters);
AfxMessageBox(str);
*/
return nParameters;
}




CString  CAIPIEditorView::WSPFormatParameters( long posOpenParenthesis, long posCloseParenthesis )
{
	CScintillaCtrl& rCtrl = GetCtrl();
	CString sParameters;
	//CString str;
	long posStart = 0;
	long posEnd = 0;
	bool bFlagInit = false;
	
	//Process parameters for format
	for(long l = posOpenParenthesis; l< posCloseParenthesis; ++l )
	{
		int symbol = rCtrl.GetCharAt(l);
		//str.Format(_T("Pos...%d  " ), l);
		//AfxMessageBox(str);
		//str.Format(_T("Symbol...%d  " ), symbol);
		//AfxMessageBox(str);
				
				
		//Check for especial symbols
		if( symbol == COMMA )
		{
			sParameters += _T(",");
		}
		if( symbol == EQUAL )
		{
			sParameters += _T("=");
		}
		if( symbol == PERIOD)
		{
			sParameters += _T(".");
		}
		if( symbol == COLON )
		{
			sParameters += _T(":");
		}
		if( symbol == AMPERSAND)
		{
			sParameters += _T("&");
		}
		if( symbol == ASTERIC)
		{
			//Check for block comments inside parameters range
			int prevSymbol = rCtrl.GetCharAt(l-1);
			if( prevSymbol == SLASH )
			{
				LPSTR szCloseComment = "*/";
				long posCloseComment =  WSPSearchToken(l, posCloseParenthesis, szCloseComment );
				if( posCloseComment != NOT_FOUND )
				{
					l = posCloseComment + 1;
				}
				else
				{
					return _T("COMMENT_ERROR");
				}
			}
			else
			{
				sParameters += _T("*");
			}
		}
		

		CAipi_Lexer lex;
		if( lex.isAlphaNumeric(symbol)  )
		{
			posStart = l;
			while ( lex.isAlphaNumeric(symbol) )
			{
				++l;
				symbol = rCtrl.GetCharAt(l);
				//str.Format(_T("Alfanumeric Symbol...%d  " ), symbol);
				//AfxMessageBox(str);
				
			}
			posEnd = l;
			--l;
			
			//str.Format(_T("Pos Start...%d  " ), posStart);
			//AfxMessageBox(str);
			//str.Format(_T("Pos Open Parenthesis...%d  " ), posOpenParenthesis);
			//AfxMessageBox(str);
			if ( bFlagInit  == true )
			{
				//AfxMessageBox(_T("Detected"));
				sParameters += _T(" ");
			}
			//sParameters += _T(" ");
			sParameters += WSPGetText(posStart, posEnd );
				bFlagInit = true;
			
			
		}	
	}

	//sParameters += WSPGetText(posOpenParenthesis, posCloseParenthesis );
return sParameters;
}



void CAIPIEditorView::WSPModified()
{
	//CString str;
	//str.Format(_T("Modification Type... %d"), m_iModificationType);
	//AfxMessageBox(str);
	
	/*
	if(		   m_iModificationType != INSERTTEXT && m_iModificationType != DELETETEXT 	
			&& m_iModificationType != LASTSTEPUNDO && m_iModificationType != LASTSTEPREDO 
			&& m_iModificationType != MULTISTEPUNDO && m_iModificationType != MULTISTEPREDO  
			&& m_iModificationType != PERFORMED_UNDO && m_iModificationType != PERFORMED_REDO 
			&& m_iModificationType != BEFOREDELETE && m_iModificationType != BEFOREINSERT  )
	{
		str.Format(_T("Modification Type... %d"), m_iModificationType);
		//AfxMessageBox(str);
		
		CScintillaCtrl& rCtrl = GetCtrl();
		long pos = rCtrl.GetCurrentPos();
		str.Format(_T("End Pos...%d  " ), pos);
		AfxMessageBox(str);
		
	}
	*/
		
	CScintillaCtrl& rCtrl = GetCtrl();
	m_DocumentLength = rCtrl.GetLength();
		
	long pos = rCtrl.GetCurrentPos();
	
	if( m_bFlagPaste )
	{
		WSPPaste();
	}
	else
	{
		//AfxMessageBox(_T("WSPMod"));	
		
		WSPDelete();
		
		WSPRuleUndo();
		WSPRuleRedo();
			
		WSPWriteClass( pos);	
		WSPEditClass( pos);

		WSPWriteQuery( pos);	
		WSPEditQuery( pos);


		WSPWriteRule(pos);
		WSPEditRule( pos);

		WSPWriteJSFunction(pos);
		WSPEditJSFunction( pos);

		WSPWriteVBSFunction(pos);
		WSPEditVBSFunction( pos);

		WSPWriteVBSFUNCTION(pos);
		WSPEditVBSFUNCTION( pos);



		WSPWriteFunction(pos);
			
		LPSTR szInt = "int";
		WSPHandleFunctionEditIntKeyWord( pos);
		WSPEditFunction(pos, szInt, 3);
			
		LPSTR szChar = "char";
		WSPHandleFunctionEditCharKeyWord( pos);
		WSPEditFunction(pos, szChar, 4);
			
		LPSTR szLong = "long";
		WSPHandleFunctionEditLongKeyWord( pos);
		WSPEditFunction(pos, szLong, 4);

		LPSTR szVoid = "void";
		WSPHandleFunctionEditVoidKeyWord( pos);
		WSPEditFunction(pos, szVoid, 4);


		LPSTR szFloat = "float";
		WSPHandleFunctionEditFloatKeyWord( pos);
		WSPEditFunction(pos, szFloat, 5);

		LPSTR szShort = "short";
		WSPHandleFunctionEditShortKeyWord( pos);
		WSPEditFunction(pos, szShort, 5);

			
		LPSTR szDouble = "double";
		WSPHandleFunctionEditDoubleKeyWord( pos);
		WSPEditFunction(pos, szDouble, 6);

		WSPWriteVariable( pos);

		WSPHandleVariableEditIntKeyWord( pos);
		WSPEditVariable(pos, szInt, 3);
			
		WSPHandleVariableEditCharKeyWord( pos);
		WSPEditVariable(pos, szChar, 4);

		WSPHandleVariableEditLongKeyWord( pos);
		WSPEditVariable(pos, szLong, 4);

		WSPHandleVariableEditFloatKeyWord( pos);
		WSPEditVariable(pos, szFloat, 5);

		WSPHandleVariableEditShortKeyWord( pos);
		WSPEditVariable(pos, szShort, 5);

		WSPHandleVariableEditDoubleKeyWord( pos);
		WSPEditVariable(pos, szDouble, 6);
			
		//AutoCompleteGestion(pos);
			
	}


}





//A simple example of call tips
void CAIPIEditorView::OnDwellStart(SCNotification* pSCNotification)
{
	CScintillaCtrl& rCtrl = GetCtrl();
	
  CWnd* pFocusWnd = GetFocus();
  if (pFocusWnd && (pFocusWnd->GetSafeHwnd() == rCtrl.GetSafeHwnd()))
  {
		long posStart = rCtrl.WordStartPosition( pSCNotification->position, true);
		long posEnd = rCtrl.WordEndPosition( pSCNotification->position, true);
		/*
		CString str;
		str.Format(_T("start  %d"), start);
		AfxMessageBox(str);
		str.Format(_T("end  %d"), end);
		AfxMessageBox(str);
		*/
		CString sWord = WSPGetText(posStart, posEnd);
		
		if( sWord != _T("EMPTY") )
		{
			//AfxMessageBox(sWord);
			rCtrl.CallTipShow(pSCNotification->position, sWord);
		}


  
  }



/*
  //Only display the call tip if the scintilla window has focus
  CWnd* pFocusWnd = GetFocus();
  if (pFocusWnd && (pFocusWnd->GetSafeHwnd() == rCtrl.GetSafeHwnd()))
  {
	//Get the previous 7 characters and next 7 characters around
    //the current dwell position and if it is "author " in case sensitive
    //then display "PJ Naughter" as a call tip
    TextRange tr;
    tr.chrg.cpMin = max(0, pSCNotification->position - 7);
    tr.chrg.cpMax = min(pSCNotification->position + 7, rCtrl.GetLength());
    char cText[15];
    memset(cText, 0, sizeof(cText));
    tr.lpstrText = cText;
    rCtrl.GetTextRange(&tr);

    //Display the call tip
  #if (_MSC_VER >= 1400)
    _strupr_s(cText, sizeof(cText));
  #else  
    _strupr(cText);
  #endif
    if (strstr(cText, "AUTHOR "))
	  
	  rCtrl.CallTipShow(pSCNotification->position, _T("PJ Naughter"));
  }

*/

  

}

void CAIPIEditorView::OnDwellEnd(SCNotification* /*pSCNotification*/)
{
  CScintillaCtrl& rCtrl = GetCtrl();

  //Cancel any outstanding call tip
  if (rCtrl.CallTipActive())
    rCtrl.CallTipCancel();
}

void CAIPIEditorView::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
  //Let the base class do its thing
	CScintillaView::OnActivate(nState, pWndOther, bMinimized);

  CScintillaCtrl& rCtrl = GetCtrl();

  //Cancel any outstanding call tip
	if (nState == WA_INACTIVE && rCtrl.CallTipActive())
    rCtrl.CallTipCancel();
}

void CAIPIEditorView::OnModifyAttemptRO(SCNotification* /*pSCNotification*/)
{
	
	if (AfxMessageBox(IDP_ALLOW_MODIFY_READONLY_FILE, MB_YESNO) == IDYES)
    GetCtrl().SetReadOnly(FALSE);
	
}





///////////////////////////////////////////////////////////////////////////////////////////////////////
/// Script Languages ////
///////////////////////////////////////////////////////////////////////////////////////////////////////




void CAIPIEditorView::OnBuildView() 
{
	
	g_includeDirective = false;
	g_dataSource = DATA_GUI;
	
	CAipi_Main main;
	main.runInterp();

		
}

/*
void CAIPIEditorView::OnDebugBuild() 
{
	// Reset Scintilla Markers 
	
	CScintillaCtrl& rCtrl = GetCtrl();
	rCtrl.MarkerDeleteAll(0);

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndWorkspaceTabView.DeleteAllTree1();
	//pMainFrame->m_wndOutputTabView.DeleteAllList1();
	pMainFrame->m_wndOutputTabView.DeleteAllList2();
	pMainFrame->m_wndOutputTabView.DeleteAllList3();

	m_ScriptObj.SetLanguage(_T("VBScript"));
	AddCode();

	if (pMainFrame->m_wndOutputTabView.IsVisible() == FALSE)
	{
				//Set visible at first
			pMainFrame->ShowControlBar(&pMainFrame->m_wndOutputTabView, TRUE ,TRUE);
	}

	

	//FindFunction(_T("Pueblo"));

	//CScintillaView::FindTextSimple(_T("Pueblo"), 0, 0, 0,0);

///////////////////////////////////////////////////////////////////////////	
	//Test Article Sample code
	CString strParam, strProc;
	m_ctlParameter.GetWindowText( strParam );
	m_ctlFunctions.GetWindowText( strProc );

	CSafeArrayHelper sfHelper;
	try{
		_variant_t var;
		if (strProc.IsEmpty())
			sfHelper.Create(VT_VARIANT, 1, 0, 0);	// (void) parameter
		else
		{
			sfHelper.Create(VT_VARIANT, 1, 0, 1);	// 1 parameter
			var = _bstr_t(strParam);
		}
		sfHelper.PutElement(0, (void*)&var);	// parameter1 -> index 0
		LPSAFEARRAY sa =  sfHelper.GetArray();
		_variant_t varRet;
		if (m_ScriptObj.RunProcedure(strProc, &sa, &varRet))
			m_ctlResult.SetWindowText( (LPCTSTR)(_bstr_t(varRet)) );
		else
		{
			CString strError = m_ScriptObj.GetErrorString();
			m_ctlResult.SetWindowText( strError );
		}
	}
	catch(...)
	{
		CString strError = m_ScriptObj.GetErrorString();
		m_ctlResult.SetWindowText( strError );
	}
//////////////////////////////////////////////////////////////////////////////////
	
		
}
*/


void CAIPIEditorView::FillFunctionsTree()
{

	//Handle Internationational
	LANGID dwLanguageID = GetSystemLanguagePrimaryID();

	int nCount = m_ScriptObj.GetMethodsCount();

	HTREEITEM hTRoot = NULL;
	HTREEITEM hTItem1 = NULL;

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndWorkspaceTabView.IsVisible())
	{
		
		
		hTRoot = pMainFrame->m_wndWorkspaceTabView.AddTreeItem1((HTREEITEM)NULL, _T("Reglas1"), (HTREEITEM)TVI_ROOT, 0);
		for(int index=0; index<nCount; index++)
		{
			LPTSTR strFunc = (LPTSTR)m_ScriptObj.GetNameAt( index );
			
			hTItem1 = pMainFrame->m_wndWorkspaceTabView.AddTreeItem1(hTRoot, strFunc, (HTREEITEM)TVI_SORT, 2);
		
		}
	}		


}



void CAIPIEditorView::ScriptLoadCode(long nStartSel, long nEndSel) 
{
	const int CODE_LENGTH = 100000;
	CScintillaCtrl& rCtrl = GetCtrl();
	CString strCode= _T("EMPTY");
	
	
	if( nEndSel > m_DocumentLength )
	{
		nEndSel = m_DocumentLength;
	}

	int iLength = nEndSel - nStartSel + 1;
	
	TextRange tr;
	tr.chrg.cpMin = nStartSel;
	tr.chrg.cpMax = nEndSel;
	char chCode[CODE_LENGTH];
						
	tr.lpstrText = chCode;
			
	if (iLength > CODE_LENGTH )
	{
		rCtrl.GetText(CODE_LENGTH, chCode);
	}
	else
	{
		//AfxMessageBox(_T("else"));
		rCtrl.GetTextRange(&tr);
		
		
	}	

	rCtrl.GetTextRange(&tr);
	strCode = (CString)chCode;
	//AfxMessageBox(strCode);
	
	CString sLanguage = _T("VBScript");
	//CString sLanguage = _T("JScript");

	m_ScriptObj.Reset();
	m_ScriptObj.SetLanguage( sLanguage );
	m_ScriptObj.LoadScript(strCode);
	
	if (!m_ScriptObj.AddScript( strCode ))
	{
		ScriptDisplayError(nStartSel);
	}
	
	
}


void CAIPIEditorView::ScriptExecute(CString strProc, long posStartProc, long posOpenParenthesis, long posCloseParenthesis)
{
	CString sResult = _T("EMPTY");

	int nParam = WSPCountFunctParameters(posOpenParenthesis, posCloseParenthesis);
	
	CSafeArrayHelper sfHelper;
	try
	{
		_variant_t var;
		
		sfHelper.Create(VT_VARIANT, 1, 0, nParam);

		int v_size = m_vParameters.size();
		/*
		CString str;
		str.Format(_T("nElements %d"), v_size);
		AfxMessageBox(str);
		*/
		for(int i=0; i< nParam; ++i)
		{
			
			CString sParam = m_vParameters.at(i);
			
			//AfxMessageBox(sParam);

			var = _bstr_t(sParam);
			sfHelper.PutElement(i, (void*)&var);
		}
		
		//AfxMessageBox(_T("Try"));
		LPSAFEARRAY sa = sfHelper.GetArray();
		_variant_t varRet;
		
		if( m_ScriptObj.RunProcedure(strProc, &sa, &varRet))
		{
			//AfxMessageBox(_T("Run"));
			sResult = (LPCTSTR)_bstr_t(varRet);
			//AfxMessageBox(sResult);
		}
		else
		{
			//AfxMessageBox(_T("Error"));
			CString sError = m_ScriptObj.GetErrorString();
			ScriptDisplayError(posStartProc);
			//AfxMessageBox(sError);
		}
	}
	catch(...)
	{
		//AfxMessageBox(_T("Catch"));
		CString sError = m_ScriptObj.GetErrorString();
		//AfxMessageBox(sError);
	}



}

void CAIPIEditorView::ScriptDisplayError(long nStartSel)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	_bstr_t line = _T("");
	
	CScintillaCtrl& rCtrl = GetCtrl();

	// Initilaize error markers
	rCtrl.MarkerDefine(0, SC_MARK_ARROW);
	rCtrl.MarkerSetFore(0, RGB( 80, 0, 0 ));
	rCtrl.MarkerSetBack(0, RGB( 255, 0, 0 ));
	

	LPTSTR lpsErrLine =_T("0");
	LPTSTR lpsErrPos = _T("0");
	LPTSTR lpsErrCode = _T("0");
	LPTSTR lpsErrDesc = _T("No description has found for this error");
	int type = JSCRIPT_ERROR;
	
	//Handle Internationational
	LANGID dwLanguageID = GetSystemLanguagePrimaryID();

	switch( dwLanguageID)
	{
	case LANG_SPANISH:
		//errLine = _bstr_t(_T("Línea: "))  +  _itot( g_currentLine, buff, 10 );
		//errPos = _bstr_t(_T("Pos. "))  +  _itot(g_currentPos, buff, 10);
		break;
	default:
		//errLine = _bstr_t(_T("Line: "))  +  _itot( g_currentLine, buff, 10 );
		//errPos = _bstr_t(_T("Pos. "))  +  _itot(g_currentPos, buff, 10);
		break;
	}

	
	//LPTSTR strErrorLineNumber = (LPTSTR)line;
	CString strErrScriptLine = m_ScriptObj.GetErrorLineNumber();
	int nErrScriptLine = _ttoi(strErrScriptLine);
	int nStartScriptLine = rCtrl.LineFromPosition(nStartSel);
	int nErrLine = nStartScriptLine + nErrScriptLine;
	TCHAR buffer[8];
	CString strErrLine = _itot( nErrLine, buffer, 10 );
	lpsErrLine = strErrLine.GetBuffer(0);  
	strErrLine.ReleaseBuffer();
	
	lpsErrPos = _T(" - ");
	

	CString strErrCode = m_ScriptObj.GetErrorNumber();
	lpsErrCode = strErrCode.GetBuffer(0);
	strErrCode.ReleaseBuffer();
	

	CString strErrDesc = m_ScriptObj.GetErrorDescription();
	lpsErrDesc = strErrDesc.GetBuffer(0);
	strErrDesc.ReleaseBuffer();
	//LPTSTR strErrorDesc = (LPTSTR)m_ScriptObj.GetErrorDescription();



	// Set error marker to proper line
	/*
	rCtrl.MarkerAdd((nErrLine - 1), 0);
	rCtrl.GotoLine(nErrLine - 1);
	*/
	

	if ( pMainFrame->m_wndOutputTabView.IsVisible())
    {
		
		pMainFrame->m_wndOutputTabView.m_TabViewContainer.SetActivePageIndex(1);
		LVITEM  Item = pMainFrame->m_wndOutputTabView.AddListItem2(0, 0, _T(""), type);
		pMainFrame->m_wndOutputTabView.AddListSubItem2(Item, 0, 1, lpsErrLine);
		pMainFrame->m_wndOutputTabView.AddListSubItem2(Item, 0, 2, lpsErrPos);
		pMainFrame->m_wndOutputTabView.AddListSubItem2(Item, 0, 3, lpsErrDesc);
		pMainFrame->m_wndOutputTabView.AddListSubItem2(Item, 0, 4, lpsErrCode);
	}
	
	m_ScriptObj.ClearError();


}


void CAIPIEditorView::ErrorMark(int nLine)
{

	CScintillaCtrl& rCtrl = GetCtrl();
	
	// Reset Scintilla Markers 
	rCtrl.MarkerDeleteAll(0);

	// Initilaize error markers
	rCtrl.MarkerDefine(0, SC_MARK_ARROW);
	rCtrl.MarkerSetFore(0, RGB( 80, 0, 0 ));
	rCtrl.MarkerSetBack(0, RGB( 255, 0, 0 ));
	
	// Set error marker to proper line
	rCtrl.MarkerAdd((nLine - 1), 0);
	rCtrl.GotoLine(nLine - 1);
	

}


void CAIPIEditorView::InsertProperties()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndPropertiesBar.InsertEditProperty(_T("Hola"), _T("No Desc"), _T("Data"));
	pMainFrame->m_wndPropertiesBar.InsertEditProperty(_T("Adios"), _T("No Desc"), _T("Data"));

}


BOOL CAIPIEditorView::FindText(LPCTSTR lpszText)
{
	
	//flags
	BOOL bNext = FALSE;					//TRUE
	BOOL bCase = FALSE;					//SCFIND_MATCHCASE
	BOOL bWord = FALSE;					//SCFIND_WHOLEWORD
	BOOL bRegularExpression = FALSE;    //SCFIND_REGEXP
	
	BOOL bFound = CScintillaView::FindTextSimple(lpszText, bNext, bCase, bWord, bRegularExpression);
	
	
	//If the text was found return TRUE 
	return bFound;


	
}

void CAIPIEditorView::OnEditFindExt() 
{
	
	
	CFindInFilesDlg fnd;
	CScintillaCtrl& rCtrl = GetCtrl();
	TCHAR cText[16];
    
	rCtrl.GetSelText(cText);
	fnd.m_strFind = cText;	

	if ( fnd.DoModal() == IDOK )
	{
		


		CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		
		pMainFrame->m_wndOutputTabView.DeleteAllList3();
		pMainFrame->m_wndOutputTabView.FindExtDesc(fnd.m_strFind, fnd.m_chkMatchCase, fnd.m_chkWholeWord, fnd.m_chkRegExp);
		pMainFrame->m_wndOutputTabView.m_TabViewContainer.SetActivePageIndex(2);

		if (pMainFrame->m_wndOutputTabView.IsVisible() == FALSE)
		{
				//Set visible at first
			pMainFrame->ShowControlBar(&pMainFrame->m_wndOutputTabView, TRUE ,TRUE);
		}

		g_findText = fnd.m_strFind;
		static int nItem = 0;
		pMainFrame->AddComboItem(g_findText, nItem);
		nItem++;


		

	}
	
	
	
}

void CAIPIEditorView::OnEditFindInFiles() 
{

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CFindInFilesExtDlg fnd;
	CScintillaCtrl& rCtrl = GetCtrl();
	TCHAR cText[16];
    
	rCtrl.GetSelText(cText);
	fnd.m_sFindText = cText;
	
	m_bFindInFiles = false;
	
	/*
	COXBitmapMenu menu;
	menu.LoadMenu(IDR_SCINTITYPE);
	menu.EnableMenuItem(ID_EDIT_FINDINFILES_STOP, MF_ENABLED);
	*/
	
	

	if ( fnd.DoModal() == IDOK )
	{
		int maxSize = (int)fnd.m_editMaxSize.GetValue();
		int minSize = (int)fnd.m_editMinSize.GetValue();
	
		
		CString sMsg = _T("Searching for word:  ") + fnd.m_sFindText + _T("..."); 
		if (pMainFrame->m_wndOutputTabView.IsVisible() == FALSE)
		{
				//Set visible at first
			pMainFrame->ShowControlBar(&pMainFrame->m_wndOutputTabView, TRUE ,TRUE);
			
		}
		pMainFrame->m_wndOutputTabView.m_TabViewContainer.SetActivePageIndex(2);

		pMainFrame->m_wndStatusBar.SetPaneText( 0, sMsg, RGB(0,0,0), TRUE);
		pMainFrame->m_wndStatusBar.ResetBar(1);
		
		pMainFrame->m_wndOutputTabView.DeleteAllList3();
		pMainFrame->m_wndOutputTabView.FindInFiles(fnd.m_sFindText, fnd.m_sBaseFolder, fnd.m_sFileMask, fnd.m_bSubFolders, fnd.m_bSize, minSize, maxSize);
		
		g_findText = fnd.m_sFindText;

		static int nItem = 0;
		pMainFrame->AddComboItem(g_findText, nItem);
		nItem++;


		
		
	}
	
	
	m_bFindInFiles = true;
	

	pMainFrame->m_wndStatusBar.ResetBar(1, TRUE);
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Process finish"), RGB(0,0,0), TRUE);	

	
}


void CAIPIEditorView::OnEditFindinFilesStop() 
{
	//CFileFinder f;
	//f._bStopSearch = true;
	

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndOutputTabView.FindInFiles(_T(""), _T(""), _T(""), 0, 0, 0, 0);

	
}








void CAIPIEditorView::OnUpdateEditFindInFiles(CCmdUI* pCmdUI) 
{
	CScintillaView::OnUpdateNeedText(pCmdUI);
	pCmdUI->Enable(m_bFindInFiles);

}



void CAIPIEditorView::OnOpenDocument(LPCTSTR path_name)
{
		
	CAIPIApp* pApp = (CAIPIApp*)AfxGetApp();
	pApp->m_pAIPIEditorDocTemplate->OpenDocumentFile(path_name);

}



void CAIPIEditorView::OnUpdateEditFindExt(CCmdUI* pCmdUI) 
{
	
	CScintillaView::OnUpdateNeedText(pCmdUI);
}



void CAIPIEditorView::OnUpdateEditFindinFilesStop(CCmdUI* pCmdUI) 
{
	
	CScintillaView::OnUpdateNeedText(pCmdUI);
	pCmdUI->Enable(!m_bFindInFiles);
	
}


void CAIPIEditorView::OnTest() 
{
	// TODO: Add your command handler code here
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndWorkspaceTabView.PoblateTree1();
	//pMainFrame->m_wndWorkspaceTabView.PoblateTree2();
	///pMainFrame->m_wndWorkspaceTabView.PoblateTree3();

	/*
	const int SIZE = 10;
	std::vector<int> vTest;
	vector <int>::iterator iter;

		
	for(int i = 0; i<10; ++i)
	{
		vTest.insert(vTest.begin()+i, 20);
	}
*/


}


void CAIPIEditorView::FindCurrentDirFiles()
{
	CString currentDir;
	GetCurrentDirectory( MAX_SIZE_PATH, currentDir.GetBufferSetLength(MAX_SIZE_PATH) );
	//AfxMessageBox(currentDir);
	currentDir.ReleaseBuffer();

	CFileFind finder;
	BOOL bContinue;
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	if( bContinue = finder.FindFile(_T("*.*")) )
	{
		while(bContinue)
		{
			bContinue = finder.FindNextFile();
			CString strName = finder.GetFileName();
			CString strPath = finder.GetFilePath();
			pMainFrame->m_wndOutputTabView.AddMsg1(strName);		
		}

	}
  
}


void CAIPIEditorView::FindCurrentProjectFiles()
{
	
	
	SetCurrentDirectory(g_projectRoot);
	//AfxMessageBox(g_projectRoot);

	CFileFind finder;
	BOOL bContinue;
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->g_vDirectives.clear();	

	if( bContinue = finder.FindFile(_T("*.knw")) )
	{
		while(bContinue)
		{
			bContinue = finder.FindNextFile();
			CString strPath = finder.GetFilePath();
			pMainFrame->g_vDirectives.push_back(strPath);
			pMainFrame->m_wndOutputTabView.AddMsg1(strPath);
			//AfxMessageBox(strPath);
		}

	}
	
  
}


void CAIPIEditorView::FillAutoCompleteAIPIKeyWords()
{
	m_sAutoCompleteKeyWord[0] = _T("RULE");
	m_sAutoCompleteKeyWord[1] = _T("RULEADD");
	m_sAutoCompleteKeyWord[2] = _T("IF");
	m_sAutoCompleteKeyWord[3] = _T("INT");
	m_sAutoCompleteKeyWord[4] = _T("INTEGER");
	m_sAutoCompleteKeyWord[5] = _T("INTERNAL");
	m_sAutoCompleteKeyWord[6] = _T("INFERNAL");
	m_sAutoCompleteKeyWord[7] = _T("INTO");
	m_sAutoCompleteKeyWord[8] = _T("RULEDELETE");
	m_sAutoCompleteKeyWord[9] = _T("RULEREMOVE");
	m_sAutoCompleteKeyWord[10] = _T("RULER");
	m_sAutoCompleteKeyWord[11] = _T("RUDE");



}

void CAIPIEditorView::FillAutoCompleteJSCriptKeyWords()
{
	//mPeriodKeyWords.insert(m_mPeriodKeyWords::value_type(_T("Math"), _T("JScript")));
	
	//JScript Object: Math 
	m_sAutoCompleteMath[0] = _T("abs");
	m_sAutoCompleteMath[1] = _T("acos");
	m_sAutoCompleteMath[2] = _T("asin");
	m_sAutoCompleteMath[3] = _T("atan");
	m_sAutoCompleteMath[4] = _T("ceil");
	m_sAutoCompleteMath[5] = _T("cos");
	m_sAutoCompleteMath[6] = _T("exp");
	m_sAutoCompleteMath[7] = _T("floor");
	m_sAutoCompleteMath[8] = _T("log");
	m_sAutoCompleteMath[9] = _T("max");
	m_sAutoCompleteMath[10] = _T("min");
	m_sAutoCompleteMath[11] = _T("pow");
	m_sAutoCompleteMath[12] = _T("random");
	m_sAutoCompleteMath[13] = _T("round");
	m_sAutoCompleteMath[14] = _T("sin");
	m_sAutoCompleteMath[15] = _T("sqrt");
	m_sAutoCompleteMath[16] = _T("tan");

	m_sAutoCompleteMath[17] = _T("E");
	m_sAutoCompleteMath[18] = _T("LN2");
	m_sAutoCompleteMath[19] = _T("LN10");
	m_sAutoCompleteMath[20] = _T("LOG2E");
	m_sAutoCompleteMath[21] = _T("PI");
	m_sAutoCompleteMath[22] = _T("SQRT1_2");
	m_sAutoCompleteMath[23] = _T("SQRT2");


	//JScript Object: Date
	m_sAutoCompleteDate[0] = _T("getDate");
	m_sAutoCompleteDate[1] = _T("getDay");
	m_sAutoCompleteDate[2] = _T("getHours");
	m_sAutoCompleteDate[3] = _T("getMinutes");
	m_sAutoCompleteDate[4] = _T("getMonth");
	m_sAutoCompleteDate[5] = _T("getSecond");
	m_sAutoCompleteDate[6] = _T("getTime");
	m_sAutoCompleteDate[7] = _T("getTimeZoneoffset");
	m_sAutoCompleteDate[8] = _T("getYear");
	m_sAutoCompleteDate[9] = _T("parse");
	m_sAutoCompleteDate[10] = _T("setDate");
	m_sAutoCompleteDate[11] = _T("setHours");
	m_sAutoCompleteDate[12] = _T("setMinutes");
	m_sAutoCompleteDate[13] = _T("setMonth");
	m_sAutoCompleteDate[14] = _T("setSeconds");
	m_sAutoCompleteDate[15] = _T("setTime");
	m_sAutoCompleteDate[16] = _T("setYear");
	m_sAutoCompleteDate[17] = _T("toGMTString");
	m_sAutoCompleteDate[18] = _T("toLocateString");
	m_sAutoCompleteDate[19] = _T("UTC");
	

	//JScript Object: Array
	m_sAutoCompleteArray[0] = _T("length");
	m_sAutoCompleteArray[1] = _T("prototype");
	m_sAutoCompleteArray[2] = _T("join");
	m_sAutoCompleteArray[3] = _T("reverse");
	m_sAutoCompleteArray[4] = _T("sort");
	
}



void CAIPIEditorView::OnSettingsSkinClassic() 
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->OnSettingsSkinClassic();
	pMainFrame->CheckMenuSkinType();
	CAipi_Tokenizer tk;
	
}

void CAIPIEditorView::OnSettingsSkinOfficeXP() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->OnSettingsSkinOfficeXP();
	pMainFrame->CheckMenuSkinType();
	
	
}

void CAIPIEditorView::OnSettingsSkinOffice2003() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->OnSettingsSkinOffice2003();
	pMainFrame->CheckMenuSkinType();
	

}


void CAIPIEditorView::UpdateSkinMenus()
{
	
   /*
	TCHAR buffer[8];
   CString	str =  _itot( g_iSkinType, buffer, 10 );
   AfxMessageBox(_T("CAIPIEditorView"));
   AfxMessageBox(str);
	*/

	switch(g_iSkinType)
	{
	case OXSkinClassic:
		OnSettingsSkinClassic();
		break;
	case OXSkinOfficeXP:
		OnSettingsSkinOfficeXP();
		break;
	case OXSkinOffice2003:
		OnSettingsSkinOffice2003();
		break;

	}

}

void CAIPIEditorView::StopTimer(CPerfTimer t, CString msg)
{
	
	CString str;
	str.Format(msg + _T("%0.4f"),t.Elapsed());
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndOutputTabView.IsVisible())
	{
		pMainFrame->m_wndOutputTabView.m_TabViewContainer.SetActivePageIndex(0);
		pMainFrame->m_wndOutputTabView.AddMsg1(str);
		
	}
	t.Stop();

}

/*
void CAIPIEditorView::OnFileNew() 
{
	CAIPIApp* pApp = (CAIPIApp*)AfxGetApp();
	pApp->m_pAIPIEditorDocTemplate->OpenDocumentFile(NULL);
	
	g_bNotificationModified = true;


}
*/



void CAIPIEditorView::OnFilePageSetup() 
{
	CScintillaView::OnFilePageSetup();

}



void CAIPIEditorView::OnEditUndo() 
{
	CScintillaView::OnEditUndo();	
}

void CAIPIEditorView::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
	CScintillaView::OnUpdateEditUndo(pCmdUI);
	
}

void CAIPIEditorView::OnEditRedo() 
{
	CScintillaView::OnEditRedo();	
}

void CAIPIEditorView::OnUpdateEditRedo(CCmdUI* pCmdUI) 
{
	CScintillaView::OnUpdateEditRedo(pCmdUI);	
}

void CAIPIEditorView::OnEditPaste() 
{
	
	CString fromClipboard;
	
	
	if ( OpenClipboard() ) 
	{
		HANDLE hData = GetClipboardData( CF_TEXT );
		char * buffer = (char*)GlobalLock( hData );
		fromClipboard = buffer;
		
		GlobalUnlock( hData );
		CloseClipboard();
	}
	
	m_nPasteLength = fromClipboard.GetLength();
	m_bFlagPaste = true;
	
		
	CScintillaView::OnEditPaste();
	
	
	
	
	
}

void CAIPIEditorView::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	CScintillaView::OnUpdateNeedPaste(pCmdUI);
		
}

void CAIPIEditorView::OnEditClear() 
{
	CScintillaCtrl& rCtrl = GetCtrl();
	long nStartSel = rCtrl.GetSelectionStart();
	long nEndSel = rCtrl.GetSelectionEnd();
	//Handle selected areas in the editor
	if( nStartSel != nEndSel )
	{
		if( m_iModificationType == BEFOREDELETE )
		{
				WSPDeleteSelectedRules(nStartSel, nEndSel, true);
		}
	}
		
	CScintillaView::OnEditClear();
	
}


void CAIPIEditorView::OnViewZoomIn() 
{
	CScintillaCtrl& rCtrl = GetCtrl();
	rCtrl.ZoomIn();
}

void CAIPIEditorView::OnViewZoomOut() 
{
	
	CScintillaCtrl& rCtrl = GetCtrl();
	rCtrl.ZoomOut();	
}


void CAIPIEditorView::OnViewZoom() 
{
	CZoomViewDlg dlg;
	if( dlg.DoModal() == IDOK )
	{
		 
		if(dlg.m_iValue < 0 ||  dlg.m_iValue > 400 )
		{
			AfxMessageBox(_T("The number must be between 0 and 400."));
			return;			
		}
		
		int percent = dlg.m_iValue;
		int zoom = (-percent + 100)/-10;
		CScintillaCtrl& rCtrl = GetCtrl();
		rCtrl.SetZoom(zoom, 0);
	}
	
}















void CAIPIEditorView::OnAppExit() 
{
	// TODO: Add your command handler code here
	/*
	AfxMessageBox(g_projectName);

	if( g_projectName != _T("") && g_projectRoot != _T("") )
	{
		
		//Save Workspace on Exit
		CAIPIApp* pApp = (CAIPIApp*)AfxGetApp();

		CString sFileName = g_projectName + _T(".apj");
		CString sFilePath = g_projectRoot + _T("\\") + sFileName;
		AfxMessageBox(sFilePath);

		pApp->m_pAIPIProjDocTemplate->OpenDocumentFile(sFilePath);
		CWorkspaceTabDoc *pDoc = CWorkspaceTabDoc::GetWorkspaceDoc();
		//pDoc->SetModifiedFlag(TRUE);
		pDoc->ProjectSave(sFilePath);
		//pDoc->ProjectClose();
	}
*/

	ASSERT(AfxGetApp()->m_pMainWnd != NULL);
    AfxGetApp()->m_pMainWnd->SendMessage(WM_CLOSE);
	

}





void CAIPIEditorView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	
	COXBitmapMenu menu;
	menu.LoadMenu(IDR_SCINTITYPE);
	CMenu* pMenuPopup = menu.GetSubMenu(1);

	pMenuPopup->SetDefaultItem(0, MF_BYPOSITION | MF_ENABLED);
	pMenuPopup->EnableMenuItem(1, MF_BYPOSITION | MF_ENABLED);

	pMenuPopup->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, AfxGetMainWnd());
	
}

void CAIPIEditorView::OnEditGoto() 
{
	CGoToDlg dlg;
	if( dlg.DoModal() == IDOK )
	{
		m_nMarkers++;
	}
	
}





void CAIPIEditorView::OnBuildCurrentFile() 
{
	g_includeDirective = false;
	g_dataSource = DATA_FILE;
	
	CAipi_Main main;
	main.runInterp();
	
}

void CAIPIEditorView::OnUpdateBuildCurrentFile(CCmdUI* pCmdUI) 
{
	CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
	CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
	CScintillaView* pView = (CScintillaView*) pChild->GetActiveView();
	ASSERT(pView);
	CAIPIEditorDoc* pDoc = (CAIPIEditorDoc*)pView->GetDocument();
	ASSERT_VALID(pDoc);
	
	CString strFilePath = pDoc->GetPathName();
	g_currentFile = strFilePath;
	CString strFileName = pDoc->GetTitle();
	CString strExt = strFilePath.Right(3);

	//AfxMessageBox(strFilePath);
	//AfxMessageBox(strFileName);
	if( strExt == _T("knw") || strExt == _T("txt") )
	{
		CString strMenu = _T("Build File (") + strFileName + _T(".") + strExt + _T(")");
		pCmdUI->SetText(strMenu);
	}
	else
	{
		CString strMenu = _T("Build File (.knw)");
		pCmdUI->SetText(strMenu);
	}

}


void CAIPIEditorView::OnBuildProject() 
{
	//Flag indicating to not apply the #include statement
	g_includeDirective = false;
	
	FindCurrentProjectFiles();

	//AfxMessageBox(_T("On Build Project"));
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CString filePath;	
	CAipi_ParserFile fparser;

	for( int i = 0; i < pMainFrame->g_vDirectives.size(); ++i )
	{
		filePath = pMainFrame->g_vDirectives.at(i);
		//AfxMessageBox(filePath);
		fparser.initParser(filePath);
		fparser.translation_unit();
		fparser.endParser();
		
		
	}

	pMainFrame->g_vDirectives.clear();
	
}

void CAIPIEditorView::OnUpdateBuildProject(CCmdUI* pCmdUI) 
{
	CString strMenu = _T("Build Project (") + g_projectName + _T(".apj)");
	pCmdUI->SetText(strMenu);
}

void CAIPIEditorView::OnBuildInsertBreakpoint() 
{
	
	if( m_nMarkers > 0 )
	{
		OnOptionsDeleteAllMarkers();
		
	}
	
	CScintillaCtrl& rCtrl = GetCtrl();
	long nPos = rCtrl.GetCurrentPos();
	int nLine = rCtrl.LineFromPosition(nPos);

	int markerType = rCtrl.MarkerGet(nLine);
	/*
	CString str;
	str.Format(_T("Marker .. %d"), m_MarkerType );
	AfxMessageBox(str);
	*/

	if( markerType == 0 )
	{
  		rCtrl.MarkerDefine(0, SC_MARK_CIRCLE);
		rCtrl.MarkerSetFore(0, RGB( 128, 0, 0 ));
		rCtrl.MarkerSetBack(0, RGB( 128, 0, 0 ));
		rCtrl.MarkerAdd(nLine, 0);
		++m_nBreakpoints;
		
	}
	else
	{
		rCtrl.MarkerDelete(nLine, 0);
		--m_nBreakpoints;
	}
  
	
}

void CAIPIEditorView::OnUpdateBuildInsertBreakpoint(CCmdUI* pCmdUI) 
{

  CScintillaCtrl& rCtrl = GetCtrl();
  long nPos = rCtrl.GetCurrentPos();
  int nLine = rCtrl.LineFromPosition(nPos);
  int nBits = rCtrl.MarkerGet(nLine);
   		
	
	if( nBits == 0 )
	{
		pCmdUI->SetText(_T("Insert/Remove Breakpoint"));
	}
	else
	{
		pCmdUI->SetText(_T("Remove Breakpoint"));	
	}
	
}

void CAIPIEditorView::OnBuildClearBreakpoints() 
{
	CScintillaCtrl& rCtrl = GetCtrl();
	rCtrl.MarkerDeleteAll(-1);
	m_nBreakpoints = 0;
	
}

void CAIPIEditorView::OnUpdateBuildClearBreakpoints(CCmdUI* pCmdUI) 
{
	if( m_nBreakpoints > 0 )
	{
		pCmdUI->Enable(true);
	}
	else
	{
		pCmdUI->Enable(false);
	}
	
}



