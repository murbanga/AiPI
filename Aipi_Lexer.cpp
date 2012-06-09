// Aipi_Lexer.cpp: implementation of the CAipi_Lexer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AIPI.h"
#include "Aipi_Lexer.h"

#include "../MainFrm.h"
#include "../ChildFrm.h"
#include "../OutputTabView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAipi_Lexer::CAipi_Lexer()
{
	
}

CAipi_Lexer::~CAipi_Lexer()
{

}



int CAipi_Lexer::testGetTextFileRange(fpos_t pos1, fpos_t pos2)
{

	const static _TCHAR BASED_CODE szFilter[] = _T("KB Files (*.txt)|*.txt|All Files (*.*)|*.*||");
	CFileDialog openDlg( TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_EXPLORER, szFilter, NULL );
	
	if(openDlg.DoModal()==IDOK)
	{	
		CString fileName( openDlg.GetPathName() );
		const  TCHAR* cFileName = (LPCTSTR) fileName; 

		if( (g_fp = _tfopen(cFileName, _T("r") )) == NULL )
		{
			CAipi_Error err;
			err.displayFileError(FILE_READ, STOP_ERROR, _T("Unable to open file") );
			return STOP_ERROR;	
		}

		getTextFileRange(pos1, pos2);
		
		fclose(g_fp);
	}

return 0;	
}

void CAipi_Lexer::testScanFile()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	int tok_type = UNDEFINE;

	TCHAR symbol;
	//TCHAR buffer[MAX_TK_LEN];
	CString str;
	
	const static _TCHAR BASED_CODE szFilter[] = _T("KB Files (*.knw)|*.knw|All Files (*.*)|*.*||");
	CFileDialog openDlg( TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_EXPLORER, szFilter, NULL );
	
	if(openDlg.DoModal()==IDOK)
	{	
		CString fileName( openDlg.GetPathName() );
		const  TCHAR* cFileName = (LPCTSTR) fileName; 
		
		if( (g_fp = _tfopen(cFileName, _T("r") )) == NULL )
		{
			CAipi_Error err;
			err.displayFileError(FILE_READ, STOP_ERROR, _T("Unable to read file") );
			return;	
		}
		
		//Find end positon of file
		fseek( g_fp, 0L, SEEK_END);
		long fendPos = ftell(g_fp);

		//Reset to the begining of file
		fseek( g_fp, 0L, SEEK_SET);
		
		
		while( (symbol = _gettc(g_fp) ) != _TEOF  )
		{
			//str.Format(_T("symbol%d  " ), symbol);
			//pMainFrame->m_wndOutputTabView.AddMsg1(str);
			/*
			wsprintf(buffer, _T("Letra: %c"), symbol);
			AfxMessageBox(buffer);
			wsprintf(buffer, _T("ASCII: %d"), symbol);
			AfxMessageBox(buffer);
			g_fcurrentPos = ftell(g_fp);
			str.Format(_T("Pos...%d  " ), g_fcurrentPos);
			AfxMessageBox(str);
			*/
			
			
			tok_type = testGetTokenFile(symbol);
			if( tok_type == STOP_ERROR || tok_type == LEX_ERROR  )
			{
				break;
			}

			

			str.Format(_T("Token Type...%d  " ), tok_type);
			AfxMessageBox(str);
			pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, g_fcurrentPos*100/fendPos);

		
		}
		
		fclose(g_fp);
	}

	

}




void CAipi_Lexer::testScanGUI()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
	CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
	CScintillaView* pView = (CScintillaView*) pChild->GetActiveView();
	ASSERT(pView);
	CScintillaCtrl& rCtrl = pView->GetCtrl();
	
	CString str;
	//TCHAR buffer[MAX_TK_LEN];
	int tok = UNDEFINE;
	long endPos = m_guiDocumentLen;


	while ( tok != NUL )
	{
		int symbol = rCtrl.GetCharAt(g_currentPos);
		//str.Format(_T("symbol%d  " ), symbol);
		//pMainFrame->m_wndOutputTabView.AddMsg1(str);
		
		/*
			wsprintf(buffer, _T("Letra: %c"), symbol);
			AfxMessageBox(buffer);
			wsprintf(buffer, _T("ASCII: %d"), symbol);
			AfxMessageBox(buffer);
			g_fcurrentPos = ftell(g_fp);
			str.Format(_T("Pos...%d  " ), g_currentPos);
			AfxMessageBox(str);
		*/
		
		tok = testGetTokenGUI();
		str.Format(_T("Token Type...%d  " ), tok);
		AfxMessageBox(str);
			

		if( tok == STOP_ERROR || tok == LEX_ERROR  )
		{
			break;
		}
		pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, g_currentPos*100/endPos);
		++g_currentPos;
		
	}


}




////////////////////////////////////////////////////////////
////  Begin getTokenGUIExp /////
///This is only for expression parser
///////////////////////////////////////////////////////////


int CAipi_Lexer::getTokenGUIExp()
{
	CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
	CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
	CScintillaView* pView = (CScintillaView*) pChild->GetActiveView();
	ASSERT(pView);
	CScintillaCtrl& rCtrl = pView->GetCtrl();

	CAipi_Tokenizer  tokz;
	int tempPos = 0;
	int symbol = rCtrl.GetCharAt(g_currentPos);
	int pos1 = 0;
	int pos2 = 0;
	tstring tk = _T("");
			
	//Skip over white space and newline
	while( symbol == SPACE || symbol == CARRIAGE_RETURN || symbol == NEW_LINE || symbol == HORIZONTAL_TAB || symbol == VERTICAL_TAB )
	{
		if( symbol == NUL )
		{
			return NUL;
		}
		
		if( symbol == NEW_LINE )
		{
			++g_currentLine;
		}
		
		++g_currentPos;
		symbol = rCtrl.GetCharAt(g_currentPos);
		
	}
	
	
	//Comments
	if( symbol == SLASH )
	{	
		tempPos = g_currentPos;
		int next_symbol = rCtrl.GetCharAt(++tempPos );
			
		//Simple comment
		if( next_symbol == SLASH )
		{
			pos1 = g_currentPos;
			while ( symbol != CARRIAGE_RETURN && symbol != NEW_LINE  && symbol != NUL  )
			{
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
			}
				
			pos2 = tempPos;
			g_currentPos = pos2;
			return COMMENT;
		}
		//Complex comment
		else if( next_symbol == ASTERIC )
		{
			pos1 = g_currentPos;
			do//find end comment
			{
				while ( symbol != ASTERIC && symbol != NUL )
				{
					if( symbol == NEW_LINE )
					{
						++g_currentLine;
					}
					
					++tempPos;
					symbol = rCtrl.GetCharAt(tempPos);
				}
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				
				if( symbol == NUL )
				{
					CAipi_Error err;
					err.displayFileError(LEXICAL, LEX_ERROR, _T("Close comment is missed") );
					return LEX_ERROR;
				}

			}while( symbol != SLASH && symbol != NUL );
			
			pos2 = ++tempPos;
			g_currentPos = pos2;
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
		switch( symbol )
		{
			case EQUAL:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					g_currentPos = tempPos;
					return ET;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					return AS;
				}
				
			case EXCLAMATION:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					g_currentPos = tempPos;
					return NE;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					return NOT_OP;
				}
				
			case AMPERSAND:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == AMPERSAND )
				{
					g_currentPos = tempPos;
					return AND_OP;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					return AND_BIT;
				}
				
			case VERTICAL_BAR:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == VERTICAL_BAR )
				{
					g_currentPos = tempPos;
					return OR_OP;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					return OR_BIT;
				}
				
			case LESS_THAN:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					g_currentPos = tempPos;
					return LE;
				}
				else if ( symbol == LESS_THAN )
				{
					g_currentPos = tempPos;
					return RIGHT_OP;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					return LT;
				}
				
			case GREATER_THAN:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					g_currentPos = tempPos;
					return GE;
				}
				else if ( symbol == GREATER_THAN )
				{
					g_currentPos = tempPos;
					return LEFT_OP;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					return GT;
				}
				
			case PLUS_SIGN:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					g_currentPos = tempPos;
					return ADD_ASSIGN;
				}
				else if ( symbol == PLUS_SIGN )
				{
					g_currentPos = tempPos;
					return INC_OP;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					return PLUS_SIGN;
				}
				break;
			case MINUS_SIGN:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					g_currentPos = tempPos;
					return SUB_ASSIGN;
				}
				else if ( symbol == MINUS_SIGN )
				{
					g_currentPos = tempPos;
					return DEC_OP;
				}
				else if ( symbol == GT )
				{
					g_currentPos = tempPos;
					return PTR_OP;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					return MINUS_SIGN;
				}
				
			case ASTERIC:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					g_currentPos = tempPos;
					return MUL_ASSIGN;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					return ASTERIC;
				}
				
			case SLASH:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					g_currentPos = tempPos;
					return DIV_ASSIGN;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					return SLASH;
				}
				
			case PERCENT:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					g_currentPos = tempPos;
					return MOD_ASSIGN;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					return PERCENT;
				}
				
			
			case COLON:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == COLON )
				{
					g_currentPos = tempPos;
					return SCOPE_OP;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					return COLON;
				}
				
			case CARET:
				return XOR_BIT;
			
			case EQUIVALENCY:
				return NOT_BIT;
			
			case QUESTION:
				return QUESTION;

		}

		
	}


	//Check for punctuators
	if( isPunctuator(symbol) )
	{
		switch( symbol )
		{
			case SEMICOLON:
				return SEMICOLON;
			case OPEN_PARENTHESIS:
				return OPEN_PARENTHESIS;
			case CLOSE_PARENTHESIS:
				return CLOSE_PARENTHESIS;
			case OPEN_BRACKET:
				return OPEN_BRACKET;
			case CLOSE_BRACKET:
				return CLOSE_BRACKET;
			case OPEN_BRACE:
				return OPEN_BRACE;
			case CLOSE_BRACE:
				return CLOSE_BRACE;
			case COMMA:
				return COMMA;
			/*
			case COLON:
				return COLON;
			*/
			case PERIOD:
				return PERIOD;
			case NUMBER_SIGN:
				return NUMBER_SIGN;
			case AT_SYMBOL:
				return AT_SYMBOL;
		
		}
		
	}

	
	//Double Quoted Strings
	if( symbol == DOBLE_QUOTATION )
	{
		pos1 = g_currentPos;
		++g_currentPos;
		symbol = rCtrl.GetCharAt(g_currentPos);
		
		if( symbol == DOBLE_QUOTATION )
		{
			pos2 = g_currentPos + 1;
			tstring tk = getTextRange(pos1, pos2);
			return LITERAL;
		}
			
		while(symbol != DOBLE_QUOTATION && symbol != CARRIAGE_RETURN && symbol != NUL )
		{
			symbol = rCtrl.GetCharAt(g_currentPos);
			//Check for \n escape sequence
			if( symbol == BACK_SLASH )
			{
				tempPos = g_currentPos;
				++tempPos;
				int escSymbol = rCtrl.GetCharAt(tempPos);
				
				switch (escSymbol) 
				{
					//  Escape /a  alert
					case 97:
						g_currentPos = tempPos;
						break;
					//  Escape /b backspace
					case 98:
						g_currentPos = tempPos;
						break;
					//  Escape /f forward feed page
					case 102:
						g_currentPos = tempPos;
						break;
					//  Escape /n  new line	
					case 110:
						g_currentPos = tempPos;
						break;
					//  Escape /r  carriage return
					case 114:
						g_currentPos = tempPos;
						break;
					//  Escape /t  horizontal tab
					case 116:
						g_currentPos = tempPos;
						break;
					//  Escape /v  vertical tab
					case 118:
						g_currentPos = tempPos;
						break;
					//  Symbol /'  single quotes
					case 27:
						g_currentPos = tempPos;
						break;
					//  Symbol /"  double quotes
					case 34:
						g_currentPos = tempPos;
						break;
					//  Symbol //  back slash
					case 92:
						g_currentPos = tempPos;
						break;
					
				}
				
				if( escSymbol != 34 )
				{
					symbol = escSymbol;
				}
			
			}
					
			++g_currentPos;
		}
		if( symbol == CARRIAGE_RETURN || symbol == NUL)
		{
			CAipi_Error err;
			err.displayGUIError(LEXICAL, LEX_ERROR, _T("Close string symbol is missed") );
			return LEX_ERROR;
		}
		
		pos2 = g_currentPos;
		symbol = rCtrl.GetCharAt(g_currentPos);
		
		if( symbol != SPACE )
		{
			--g_currentPos;
		}
		
		return LITERAL;
		
	}
	

	//Single Quoted Strings
	if( symbol == SINGLE_QUOTATION )
	{
		pos1 = g_currentPos;
		++g_currentPos;
		symbol = rCtrl.GetCharAt(g_currentPos);
		if( symbol == SINGLE_QUOTATION )
		{
			pos2 = g_currentPos + 1;
			return LITERAL;
		}
				
		while(symbol != SINGLE_QUOTATION && symbol != CARRIAGE_RETURN && symbol != _TEOF )
		{
			symbol = rCtrl.GetCharAt(g_currentPos);
			
			//Check for \n escape sequence
			if( symbol == BACK_SLASH )
			{
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				
				switch (symbol) 
				{
					//  Escape /a  alert
					case 97:
						g_currentPos = tempPos;
						break;
					
					//  Escape /b backspace
					case 98:
						g_currentPos = tempPos;
						break;
					//  Escape /f forward feed page
					case 102:
						g_currentPos = tempPos;
						break;
					//  Escape /n  new line	
					case 110:
						g_currentPos = tempPos;
						break;
					//  Escape /r  carriage return
					case 114:
						g_currentPos = tempPos;
						break;
					//  Escape /t  horizontal tab
					case 116:
						g_currentPos = tempPos;
						break;
					//  Escape /v  vertical tab
					case 118:
						g_currentPos = tempPos;
						break;
					//  Symbol /'  single quotes
					case 27:
						g_currentPos = tempPos;
						break;
					//  Symbol /"  double quotes
					case 34:
						g_currentPos = tempPos;
						break;
					//  Symbol //  back slash
					case 92:
						g_currentPos = tempPos;
						break;
					
				}
			}
			++g_currentPos;
		}
		if( symbol == CARRIAGE_RETURN || symbol == NUL )
		{
				CAipi_Error err;
				err.displayGUIError(LEXICAL, LEX_ERROR, _T("Close string symbol is missed") );
				return LEX_ERROR;
		}
					
		pos2 = g_currentPos;
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

		while( isDigit(symbol) || symbol == PERIOD && symbol != NUL )
		{
			++g_currentPos;
			symbol = rCtrl.GetCharAt(g_currentPos);
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
		CAipi_Symbol symb;
		pos1 = g_currentPos;
		while( isAlphaNumeric(symbol) && symbol != NUL )
		{
			++g_currentPos;
			symbol = rCtrl.GetCharAt(g_currentPos);
		}
		
		pos2 = g_currentPos;
		symbol = rCtrl.GetCharAt(g_currentPos);
		if( symbol != SPACE )
		{
			--g_currentPos;
		}
		
		int keyWord = symb.findKeyWord(tk);
		if( keyWord != NOT_FOUND )
		{
			return keyWord;
		}
		else
		{
			return IDENTIFIER;
		}
		
	}
	if (symbol == NUL )
	{
		return NUL;
		
	}

	
		
return UNDEFINE;
}

/////////////////////////////////////////////////////
/////   End getTokenGUIExp ///////
//////////////////////////////////////////////////////






//////////////////////////////////////////////////////////
//// Begin testGetTokenGUIExp ////////////
///This is only for expression parser
///////////////////////////////////////////////////////////

int CAipi_Lexer::testGetTokenGUIExp()
{
	CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
	CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
	CScintillaView* pView = (CScintillaView*) pChild->GetActiveView();
	ASSERT(pView);
	CScintillaCtrl& rCtrl = pView->GetCtrl();

	CAipi_Tokenizer  tokz;
	CString str;
	
	int tempPos = 0;
	int symbol = rCtrl.GetCharAt(g_currentPos);
	int pos1 = 0;
	int pos2 = 0;
	tstring tk = _T("");
	
	//str.Format(_T("Symbol...%d  " ), symbol);
	//AfxMessageBox(str);
		
	//Skip over white space and newline
	while( symbol == SPACE || symbol == CARRIAGE_RETURN || symbol == NEW_LINE || symbol == HORIZONTAL_TAB || symbol == VERTICAL_TAB )
	{
		if( symbol == NUL )
		{
			return NUL;
		}
		
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
			
			
			
			tk = getTextRange(pos1, pos2);
			if( tk == _T("STOP_ERROR") )
			{
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
				while ( symbol != ASTERIC && symbol != NUL )
				{
					if( symbol == NEW_LINE )
						++g_currentLine;

					
					++tempPos;
					symbol = rCtrl.GetCharAt(tempPos);
					//str.Format(_T("Complex Comment Symbol...%d  " ), symbol);
					//AfxMessageBox(str);
					//str.Format(_T("Pos en Comment Complex...%d  " ), tempPos);
					//AfxMessageBox(str);
				}
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);

			}while( symbol != SLASH && symbol != NUL );
			
			
			//AfxMessageBox(_T("Salio del do while"));
			pos2 = ++tempPos;
			g_currentPos = pos2;

			tk = getTextRange(pos1, pos2);
			if( tk == _T("STOP_ERROR") )
			{
				return STOP_ERROR;
			}
			
			
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
					tk = getTextRange(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return ET;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos + 1);
					return AS;
				}
				
			case EXCLAMATION:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return NE;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos + 1);
					return NOT_OP;
				}
				
			case AMPERSAND:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == AMPERSAND )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return AND_OP;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos + 1);
					return AND_BIT;
				}
				
			case VERTICAL_BAR:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == VERTICAL_BAR )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return OR_OP;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos + 1);
					return OR_BIT;
						
				}
				
			case LESS_THAN:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return LE;
				}
				else if ( symbol == LESS_THAN )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return RIGHT_OP;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos + 1);
					return LT;	
				}
				
			case GREATER_THAN:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return GE;
				}
				else if ( symbol == GREATER_THAN )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return LEFT_OP;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos + 1);
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
				
					tk = getTextRange(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return ADD_ASSIGN;
				}
				else if ( symbol == PLUS_SIGN )
				{
					//str.Format(_T("Symbol...%d  " ), symbol);
					//AfxMessageBox(str);
				
					tk = getTextRange(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return INC_OP;
				}
				else
				{
				
					//str.Format(_T("Symbol Sum...%d  " ), symbol);
					//AfxMessageBox(str);
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos+1);
					return PLUS_SIGN;
					
				}
				
			case MINUS_SIGN:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return SUB_ASSIGN;
				}
				else if ( symbol == MINUS_SIGN )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return DEC_OP;
				}
				else if ( symbol == GT )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return PTR_OP;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos +1);
					return MINUS_SIGN;
				}
				
			case ASTERIC:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return MUL_ASSIGN;	
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos + 1);
					return ASTERIC;
				}
				
			case SLASH:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return DIV_ASSIGN;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos + 1);
					return SLASH;
				}
				
			case PERCENT:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return MOD_ASSIGN;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos + 1);
					return PERCENT;
				}
				
			
			case COLON:
				//str.Format(_T("Symbol COLON...%d  " ), symbol);
				//AfxMessageBox(str);

				tempPos = g_currentPos;
				++tempPos;
				
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == COLON )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return SCOPE_OP;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos + 1);
					return COLON;
				}
				break;
			
			case CARET:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				return XOR_BIT;
			
			case EQUIVALENCY:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				return NOT_BIT;
			
			case QUESTION:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				return QUESTION;

		}

	}


	//Check for punctuators
	if( isPunctuator(symbol) )
	{
		
		switch( symbol )
		{
					
			case SEMICOLON:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				return SEMICOLON;
			case OPEN_PARENTHESIS:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				return OPEN_PARENTHESIS;
			case CLOSE_PARENTHESIS:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				return CLOSE_PARENTHESIS;
			case OPEN_BRACKET:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				return OPEN_BRACKET;
			case CLOSE_BRACKET:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				return CLOSE_BRACKET;
			case OPEN_BRACE:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				return OPEN_BRACE;
			case CLOSE_BRACE:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				return CLOSE_BRACE;
			case COMMA:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				return COMMA;
			/*
			case COLON:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				return COLON;
			*/
			case PERIOD:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				return PERIOD;
			case NUMBER_SIGN:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				return NUMBER_SIGN;
			case AT_SYMBOL:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
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
		
		if( symbol == DOBLE_QUOTATION )
		{
			//AfxMessageBox(_T("Entro a double quotation 2"));
			pos2 = g_currentPos + 1;
			tstring tk = getTextRange(pos1, pos2);
			return LITERAL;
		}
		
		
		
		while(symbol != DOBLE_QUOTATION && symbol != CARRIAGE_RETURN && symbol != NUL )
		{
			symbol = rCtrl.GetCharAt(g_currentPos);
			
			/*
			AfxMessageBox(_T("entro al while"));
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
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					
					//  Escape /b backspace
					case 98:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					//  Escape /f forward feed page
					case 102:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					//  Escape /n  new line	
					case 110:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					//  Escape /r  carriage return
					case 114:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					//  Escape /t  horizontal tab
					case 116:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					//  Escape /v  vertical tab
					case 118:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					//  Symbol /'  single quotes
					case 27:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					
					//  Symbol /"  double quotes
					case 34:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					
						//  Symbol //  back slash
					case 92:
						tk = getTextRange(tempPos -1, tempPos + 1); 
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

		if( symbol == CARRIAGE_RETURN || symbol == NUL )
		{
			AfxMessageBox(_T("Eror carriage return"));	
			CAipi_Error err;
			err.displayGUIError(LEXICAL, LEX_ERROR, _T("Close string symbol is missed") );
			return LEX_ERROR;
		}
		
			pos2 = g_currentPos;
			tstring tk = getTextRange(pos1, pos2);
			if( tk == _T("STOP_ERROR") )
			{
				return STOP_ERROR;
			}
			
					
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
		if( symbol == SINGLE_QUOTATION )
		{
			//AfxMessageBox(_T("Entro a single quotation 2"));
			pos2 = g_currentPos + 1;
			tstring tk = getTextRange(pos1, pos2);
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
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					
					//  Escape /b backspace
					case 98:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					//  Escape /f forward feed page
					case 102:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					//  Escape /n  new line	
					case 110:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					//  Escape /r  carriage return
					case 114:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					//  Escape /t  horizontal tab
					case 116:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					//  Escape /v  vertical tab
					case 118:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					//  Symbol /'  single quotes
					case 27:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					
					//  Symbol /"  double quotes
					case 34:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					
						//  Symbol //  back slash
					case 92:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					
					//AfxMessageBox(_T("reconocio escape"));
				}
			}
			++g_currentPos;
		}
		if( symbol == CARRIAGE_RETURN || symbol == NUL )
		{
				CAipi_Error err;
				err.displayGUIError(LEXICAL, LEX_ERROR, _T("Close string symbol is missed") );
				return LEX_ERROR;
		}
		
			
		pos2 = g_currentPos;
		

		tstring tk = getTextRange(pos1, pos2);
		if( tk == _T("STOP_ERROR") )
		{
			return STOP_ERROR;
		}
		
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

		while( isDigit(symbol) || symbol == PERIOD && symbol != NUL )
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
		tk = getTextRange(pos1, pos2);
		if( tk == _T("STOP_ERROR") )
		{
			return STOP_ERROR;
		}
		
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
		CAipi_Symbol symb;

		pos1 = g_currentPos;
		
		while( isAlphaNumeric(symbol) && symbol != NUL )
		{
			++g_currentPos;
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
		
		

		tk = getTextRange(pos1, pos2);
		if( tk == _T("STOP_ERROR") )
		{
			return STOP_ERROR;
		}
		
		int keyWord = symb.findKeyWord(tk);
		if( keyWord != NOT_FOUND )
		{
			return keyWord;
		}
		else
		{
			
			//str.Format(_T("Char Last Pos...%d  " ), pos2);
			//AfxMessageBox(str);
			

			return IDENTIFIER;
		}

		
	}

	if (symbol == NUL )
	{
		//AfxMessageBox(_T("Fin del archivo"));
		return NUL;
		
	}

		
		
return UNDEFINE;
}

///////////////////////////////////////////////////////
///// End testGetTokenGUIExp  ////
///////////////////////////////////////////////////////







////////////////////////////////////////////////////////////
//// Begin  addTokenizerGUIExp   ////
////////////////////////////////////////////////////////////
int CAipi_Lexer::addTokenizerGUIExp()
{
	CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
	CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
	CScintillaView* pView = (CScintillaView*) pChild->GetActiveView();
	ASSERT(pView);
	CScintillaCtrl& rCtrl = pView->GetCtrl();

	CAipi_Tokenizer  tokz;
	CString str;
	
	int tempPos = 0;
	//static long g_currentId_IForm = 1000;

	int symbol = rCtrl.GetCharAt(g_currentPos);
	int pos1 = 0;
	int pos2 = 0;
	tstring tk = _T("");
	
	//str.Format(_T("Symbol...%d  " ), symbol);
	//AfxMessageBox(str);
		
	//Skip over white space and newline
	while( symbol == SPACE || symbol == CARRIAGE_RETURN || symbol == NEW_LINE || symbol == HORIZONTAL_TAB || symbol == VERTICAL_TAB )
	{
		if( symbol == NUL )
		{
			return NUL;
		}
		
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
			
			
			
			tk = getTextRange(pos1, pos2);
			if( tk == _T("STOP_ERROR") )
			{
				return STOP_ERROR;
			}
			
			
			//tokz.addToken(pos1, pos2, g_currentLine, SIMPLE_COMMENT, tk, COMMENT);
			tokz.v_addToken(pos1, pos2, g_currentLine, SIMPLE_COMMENT, tk, COMMENT);
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
				while ( symbol != ASTERIC && symbol != NUL)
				{
					/*
					if( symbol == NEW_LINE )
						++g_currentLine;
					*/
					
					++tempPos;
					symbol = rCtrl.GetCharAt(tempPos);
					//str.Format(_T("Complex Comment Symbol...%d  " ), symbol);
					//AfxMessageBox(str);
					//str.Format(_T("Pos en Comment Complex...%d  " ), tempPos);
					//AfxMessageBox(str);
				}
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);

				if( symbol == NUL )
				{
					CAipi_Error err;
					err.displayGUIError(LEXICAL, LEX_ERROR, _T("Close comment is missed") );
					return LEX_ERROR;
				}

			}while( symbol != SLASH );
			
			
			//AfxMessageBox(_T("Salio del do while"));
			pos2 = ++tempPos;
			g_currentPos = pos2;

			tk = getTextRange(pos1, pos2);
			if( tk == _T("STOP_ERROR") )
			{
				return STOP_ERROR;
			}
			
			//tokz.addToken(pos1, pos2, g_currentLine, COMPLEX_COMMENT, tk, COMMENT);
			tokz.v_addToken(pos1, pos2, g_currentLine, COMPLEX_COMMENT, tk, COMMENT);
			
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
					tk = getTextRange(tempPos -1, tempPos + 1);
					//tokz.addToken(tempPos -1, tempPos +1, g_currentLine, ET, tk, OPERATOR);
					tokz.v_addToken(tempPos -1, tempPos +1, g_currentLine, ET, tk, ET);
					g_currentPos = tempPos;
					return ET;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos + 1);
					//tokz.addToken(g_currentPos, g_currentPos + 1, g_currentLine, AS, tk, OPERATOR);
					tokz.v_addToken(g_currentPos, g_currentPos + 1, g_currentLine, AS, tk, AS);
					return AS;
				}
				
			case EXCLAMATION:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					//tokz.addToken(tempPos -1, tempPos +1, g_currentLine, NE, tk, OPERATOR);
					tokz.v_addToken(tempPos -1, tempPos +1, g_currentLine, NE, tk, NE);
					g_currentPos = tempPos;
					return NE;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos + 1);
					//tokz.addToken(g_currentPos, g_currentPos + 1, g_currentLine, NOT_OP, tk, OPERATOR);
					tokz.v_addToken(g_currentPos, g_currentPos + 1, g_currentLine, NOT_OP, tk, NOT_OP);
					return NOT_OP;
				}
				
			case AMPERSAND:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == AMPERSAND )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					//tokz.addToken(tempPos -1, tempPos +1, g_currentLine, AND_OP, tk, OPERATOR);
					tokz.v_addToken(tempPos -1, tempPos +1, g_currentLine, AND_OP, tk, AND_OP);
					g_currentPos = tempPos;
					return AND_OP;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos + 1);
					//tokz.addToken(g_currentPos, g_currentPos + 1, g_currentLine, AND_BIT, tk, OPERATOR);
					tokz.v_addToken(g_currentPos, g_currentPos + 1, g_currentLine, AND_BIT, tk, AND_BIT);
					return AND_BIT;
				}
				
			case VERTICAL_BAR:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == VERTICAL_BAR )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					//tokz.addToken(tempPos -1, tempPos +1, g_currentLine, OR_OP, tk, OPERATOR);
					tokz.v_addToken(tempPos -1, tempPos +1, g_currentLine, OR_OP, tk, OR_OP);
					g_currentPos = tempPos;
					return OR_OP;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos + 1);
					//tokz.addToken(g_currentPos, g_currentPos + 1, g_currentLine, OR_BIT, tk, OPERATOR);	
					tokz.v_addToken(g_currentPos, g_currentPos + 1, g_currentLine, OR_BIT, tk, OR_BIT);
					return OR_BIT;
				}
				
			case LESS_THAN:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					//tokz.addToken(tempPos -1, tempPos +1, g_currentLine, LE, tk, OPERATOR);
					tokz.v_addToken(tempPos -1, tempPos +1, g_currentLine, LE, tk, LE);
					g_currentPos = tempPos;
					return LE;
				}
				else if ( symbol == LESS_THAN )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					//tokz.addToken(tempPos -1, tempPos +1, g_currentLine, RIGHT_OP, tk, OPERATOR);
					tokz.v_addToken(tempPos -1, tempPos +1, g_currentLine, RIGHT_OP, tk, RIGHT_OP);
					g_currentPos = tempPos;
					return RIGHT_OP;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos + 1);
					//tokz.addToken(g_currentPos, g_currentPos + 1, g_currentLine, LT, tk, OPERATOR);	
					tokz.v_addToken(g_currentPos, g_currentPos + 1, g_currentLine, LT, tk, LT);
					return LT;
				}
				
			case GREATER_THAN:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					//tokz.addToken(tempPos -1, tempPos +1, g_currentLine, GE, tk, OPERATOR);
					tokz.v_addToken(tempPos -1, tempPos +1, g_currentLine, GE, tk, GE);
					g_currentPos = tempPos;
					return GE;
				}
				else if ( symbol == GREATER_THAN )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					//tokz.addToken(tempPos -1, tempPos +1, g_currentLine, LEFT_OP, tk, OPERATOR);
					tokz.v_addToken(tempPos -1, tempPos +1, g_currentLine, LEFT_OP, tk, LEFT_OP);
					g_currentPos = tempPos;
					return LEFT_OP;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos + 1);
					//tokz.addToken(g_currentPos, g_currentPos + 1, g_currentLine, GT, tk, OPERATOR);	
					tokz.v_addToken(g_currentPos, g_currentPos + 1, g_currentLine, GT, tk, GT);
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
				
					tk = getTextRange(tempPos -1, tempPos + 1);
					//tokz.addToken(tempPos -1, tempPos +1, g_currentLine, ADD_ASSIGN, tk, OPERATOR);
					tokz.v_addToken(tempPos -1, tempPos +1, g_currentLine, ADD_ASSIGN, tk, ADD_ASSIGN);
					g_currentPos = tempPos;
					return ADD_ASSIGN;
				}
				else if ( symbol == PLUS_SIGN )
				{
					//str.Format(_T("Symbol...%d  " ), symbol);
					//AfxMessageBox(str);
				
					tk = getTextRange(tempPos -1, tempPos + 1);
					//tokz.addToken(tempPos -1, tempPos +1, g_currentLine, INC_OP, tk, OPERATOR);
					tokz.v_addToken(tempPos -1, tempPos +1, g_currentLine, INC_OP, tk, INC_OP);
					g_currentPos = tempPos;
					return INC_OP;
				}
				else
				{
				
					//str.Format(_T("Symbol Sum...%d  " ), symbol);
					//AfxMessageBox(str);
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos+1);
					//tokz.addToken(g_currentPos, g_currentPos+1, g_currentLine, PLUS_SIGN, tk, OPERATOR);
					tokz.v_addToken(g_currentPos, g_currentPos+1, g_currentLine, PLUS_SIGN, tk, PLUS_SIGN);
					return PLUS_SIGN;
				}
				
			case MINUS_SIGN:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					//tokz.addToken(tempPos -1, tempPos +1, g_currentLine, SUB_ASSIGN, tk, OPERATOR);
					tokz.v_addToken(tempPos -1, tempPos +1, g_currentLine, SUB_ASSIGN, tk, SUB_ASSIGN);
					g_currentPos = tempPos;
					return SUB_ASSIGN;
				}
				else if ( symbol == MINUS_SIGN )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					//tokz.addToken(tempPos -1, tempPos +1, g_currentLine, DEC_OP, tk, OPERATOR);
					tokz.v_addToken(tempPos -1, tempPos +1, g_currentLine, DEC_OP, tk, DEC_OP);
					g_currentPos = tempPos;
					return DEC_OP;
				}
				else if ( symbol == GT )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					//tokz.addToken(tempPos -1, tempPos +1, g_currentLine, PTR_OP, tk, OPERATOR);
					tokz.v_addToken(tempPos -1, tempPos +1, g_currentLine, PTR_OP, tk, PTR_OP);
					g_currentPos = tempPos;
					return PTR_OP;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos +1);
					//tokz.addToken(g_currentPos, g_currentPos +1, g_currentLine, MINUS_SIGN, tk, OPERATOR);
					tokz.v_addToken(g_currentPos, g_currentPos +1, g_currentLine, MINUS_SIGN, tk, MINUS_SIGN);
					return MINUS_SIGN;
				}
				
			case ASTERIC:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					//tokz.addToken(tempPos -1, tempPos +1, g_currentLine, MUL_ASSIGN, tk, OPERATOR);
					tokz.v_addToken(tempPos -1, tempPos +1, g_currentLine, MUL_ASSIGN, tk, MUL_ASSIGN);
					g_currentPos = tempPos;
					return MUL_ASSIGN;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos + 1);
					//tokz.addToken(g_currentPos, g_currentPos + 1, g_currentLine, ASTERIC, tk, OPERATOR);
					tokz.v_addToken(g_currentPos, g_currentPos + 1, g_currentLine, ASTERIC, tk, ASTERIC);
					return ASTERIC;
				}
				
			case SLASH:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					//tokz.addToken(tempPos -1, tempPos +1, g_currentLine, DIV_ASSIGN, tk, OPERATOR);
					tokz.v_addToken(tempPos -1, tempPos +1, g_currentLine, DIV_ASSIGN, tk, DIV_ASSIGN);
					g_currentPos = tempPos;
					return DIV_ASSIGN;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos + 1);
					//tokz.addToken(g_currentPos, g_currentPos +1, g_currentLine, SLASH, tk, OPERATOR);
					tokz.v_addToken(g_currentPos, g_currentPos +1, g_currentLine, SLASH, tk, SLASH);
					return SLASH;
				}
				
			case PERCENT:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					//tokz.addToken(tempPos -1, tempPos +1, g_currentLine, MOD_ASSIGN, tk, OPERATOR);
					tokz.v_addToken(tempPos -1, tempPos +1, g_currentLine, MOD_ASSIGN, tk, MOD_ASSIGN);
					g_currentPos = tempPos;
					return MOD_ASSIGN;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos + 1);
					//tokz.addToken(g_currentPos, g_currentPos +1, g_currentLine, PERCENT, tk, OPERATOR);
					tokz.v_addToken(g_currentPos, g_currentPos +1, g_currentLine, PERCENT, tk, PERCENT);
					return PERCENT;
				}
				
			
			case COLON:
				//str.Format(_T("Symbol COLON...%d  " ), symbol);
				//AfxMessageBox(str);

				tempPos = g_currentPos;
				++tempPos;
				
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == COLON )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					//tokz.addToken(tempPos -1, tempPos +1, g_currentLine, SCOPE_OP, tk, OPERATOR);
					tokz.v_addToken(tempPos -1, tempPos +1, g_currentLine, SCOPE_OP, tk, SCOPE_OP);
					g_currentPos = tempPos;
					return SCOPE_OP;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos + 1);
					//tokz.addToken(g_currentPos, g_currentPos + 1, g_currentLine, COLON, tk, OPERATOR);
					tokz.v_addToken(g_currentPos, g_currentPos + 1, g_currentLine, COLON, tk, COLON);
					return COLON;
				}
				
			
			case CARET:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				//tokz.addToken(g_currentPos, g_currentPos+1, g_currentLine, XOR_BIT, tk, OPERATOR);
				tokz.v_addToken(g_currentPos, g_currentPos+1, g_currentLine, XOR_BIT, tk, XOR_BIT);
				return XOR_BIT;
			
			case EQUIVALENCY:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				//tokz.addToken(g_currentPos, g_currentPos+1, g_currentLine, NOT_BIT, tk, OPERATOR);
				tokz.v_addToken(g_currentPos, g_currentPos+1, g_currentLine, NOT_BIT, tk, NOT_BIT);
				return NOT_BIT;
			
			case QUESTION:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				//tokz.addToken(g_currentPos, g_currentPos+1, g_currentLine, QUESTION, tk, OPERATOR);
				tokz.v_addToken(g_currentPos, g_currentPos+1, g_currentLine, QUESTION, tk, QUESTION);
				return QUESTION;

		}

		
	}


	//Check for punctuators
	if( isPunctuator(symbol) )
	{
		
		switch( symbol )
		{
					
			case SEMICOLON:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				//tokz.addToken(g_currentPos, g_currentPos+1, g_currentLine, SEMICOLON, tk, PUNCTUATOR);
				tokz.v_addToken(g_currentPos, g_currentPos+1, g_currentLine, SEMICOLON, tk, SEMICOLON);
				return SEMICOLON;
			case OPEN_PARENTHESIS:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				//tokz.addToken(g_currentPos, g_currentPos+1, g_currentLine, OPEN_PARENTHESIS, tk, PUNCTUATOR);
				tokz.v_addToken(g_currentPos, g_currentPos+1, g_currentLine, OPEN_PARENTHESIS, tk,	OPEN_PARENTHESIS);
				return OPEN_PARENTHESIS;
			case CLOSE_PARENTHESIS:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				//tokz.addToken(g_currentPos, g_currentPos+1, g_currentLine, CLOSE_PARENTHESIS, tk, PUNCTUATOR);
				tokz.v_addToken(g_currentPos, g_currentPos+1, g_currentLine, CLOSE_PARENTHESIS, tk, CLOSE_PARENTHESIS);
				return CLOSE_PARENTHESIS;
			case OPEN_BRACKET:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				//tokz.addToken(g_currentPos, g_currentPos+1, g_currentLine, OPEN_BRACKET, tk, PUNCTUATOR);
				tokz.v_addToken(g_currentPos, g_currentPos+1, g_currentLine, OPEN_BRACKET, tk, OPEN_BRACKET);
				return OPEN_BRACKET;
			case CLOSE_BRACKET:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				//tokz.addToken(g_currentPos, g_currentPos+1, g_currentLine, CLOSE_BRACKET, tk, PUNCTUATOR);
				tokz.v_addToken(g_currentPos, g_currentPos+1, g_currentLine, CLOSE_BRACKET, tk, CLOSE_BRACKET);
				return CLOSE_BRACKET;
			case OPEN_BRACE:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				//tokz.addToken(g_currentPos, g_currentPos+1, g_currentLine, OPEN_BRACE, tk, PUNCTUATOR);
				tokz.v_addToken(g_currentPos, g_currentPos+1, g_currentLine, OPEN_BRACE, tk, OPEN_BRACE);
				return OPEN_BRACE;
			case CLOSE_BRACE:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				//tokz.addToken(g_currentPos, g_currentPos+1, g_currentLine, CLOSE_BRACE, tk, PUNCTUATOR);
				tokz.v_addToken(g_currentPos, g_currentPos+1, g_currentLine, CLOSE_BRACE, tk, CLOSE_BRACE);
				return CLOSE_BRACE;
			case COMMA:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				//tokz.addToken(g_currentPos, g_currentPos+1, g_currentLine, COMMA, tk, PUNCTUATOR);
				tokz.v_addToken(g_currentPos, g_currentPos+1, g_currentLine, COMMA, tk, COMMA);
				return COMMA;
			/*
			case COLON:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				//tokz.addToken(g_currentPos, g_currentPos+1, g_currentLine, COLON, tk, PUNCTUATOR);
				tokz.v_addToken(g_currentPos, g_currentPos+1, g_currentLine, COLON, tk, COLON);
				return COMMA;
			*/
			case PERIOD:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				//tokz.addToken(g_currentPos, g_currentPos+1, g_currentLine, PERIOD, tk, PUNCTUATOR);
				tokz.v_addToken(g_currentPos, g_currentPos+1, g_currentLine, PERIOD, tk, PERIOD);
				return PERIOD;
			case NUMBER_SIGN:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				//tokz.addToken(g_currentPos, g_currentPos+1, g_currentLine, NUMBER_SIGN, tk, PUNCTUATOR);
				tokz.v_addToken(g_currentPos, g_currentPos+1, g_currentLine, NUMBER_SIGN, tk, NUMBER_SIGN);
				return NUMBER_SIGN;
			case AT_SYMBOL:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				//tokz.addToken(g_currentPos, g_currentPos+1, g_currentLine, AT_SYMBOL, tk, PUNCTUATOR);
				tokz.v_addToken(g_currentPos, g_currentPos+1, g_currentLine, AT_SYMBOL, tk, AT_SYMBOL);
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
		
		if( symbol == DOBLE_QUOTATION )
		{
			//AfxMessageBox(_T("Entro a double quotation 2"));
			pos2 = g_currentPos + 1;
			tstring tk = getTextRange(pos1, pos2);
			tokz.v_addToken(pos1, pos2, g_currentLine, STRING_LITERAL, tk, LITERAL);	
			return LITERAL;
		}
		
		
		
		while(symbol != DOBLE_QUOTATION && symbol != CARRIAGE_RETURN && symbol != NUL )
		{
			symbol = rCtrl.GetCharAt(g_currentPos);
			
			/*
			AfxMessageBox(_T("entro al while"));
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
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, ALERT, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, ALERT, tk, ALERT);
						break;
					
					//  Escape /b backspace
					case 98:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, BACKSPACE, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, BACKSPACE, tk, BACKSPACE);
						break;
					//  Escape /f forward feed page
					case 102:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, FORWARD_FEED, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, FORWARD_FEED, tk, FORWARD_FEED);
						break;
					//  Escape /n  new line	
					case 110:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, NEW_LINE, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, NEW_LINE, tk, NEW_LINE);
						break;
					//  Escape /r  carriage return
					case 114:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, CARRIAGE_RETURN, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, CARRIAGE_RETURN, tk, CARRIAGE_RETURN);
						break;
					//  Escape /t  horizontal tab
					case 116:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, HORIZONTAL_TAB, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, HORIZONTAL_TAB, tk, HORIZONTAL_TAB);
						break;
					//  Escape /v  vertical tab
					case 118:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, VERTICAL_TAB, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, VERTICAL_TAB, tk, VERTICAL_TAB);
						break;
					//  Symbol /'  single quotes
					case 27:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, SINGLE_QUOTATION, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, SINGLE_QUOTATION, tk, SINGLE_QUOTATION);
						break;
					
					//  Symbol /"  double quotes
					case 34:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, DOBLE_QUOTATION, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, DOBLE_QUOTATION, tk, DOBLE_QUOTATION);
						break;
					
						//  Symbol //  back slash
					case 92:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, BACK_SLASH, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, BACK_SLASH, tk, BACK_SLASH);
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

		if( symbol == CARRIAGE_RETURN || symbol == NUL )
		{
			AfxMessageBox(_T("Eror carriage return"));	
			CAipi_Error err;
			err.displayGUIError(LEXICAL, LEX_ERROR, _T("Close string symbol is missed") );
			return LEX_ERROR;
		}
		
			pos2 = g_currentPos;
			tstring tk = getTextRange(pos1, pos2);
			if( tk == _T("STOP_ERROR") )
			{
				return STOP_ERROR;
			}
			
			++g_currentId_IForm;
			CAipi_Symbol symb;
			symb.addId_IntForm(tk, g_currentId_IForm);
			int repIdForm = symb.findId_IntForm(tk);
			if( repIdForm != NOT_FOUND )
			{
				tokz.v_addToken(pos1, pos2, g_currentLine, repIdForm, tk, LITERAL);	
			}
			else
			{
				tokz.v_addToken(pos1, pos2, g_currentLine, g_currentId_IForm, tk, LITERAL);
			}
		
	
		
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
		if( symbol == SINGLE_QUOTATION )
		{
			//AfxMessageBox(_T("Entro a single quotation 2"));
			pos2 = g_currentPos + 1;
			tstring tk = getTextRange(pos1, pos2);

			
			
			++g_currentId_IForm;
			CAipi_Symbol symb;
			symb.addId_IntForm(tk, g_currentId_IForm);
			int repIdForm = symb.findId_IntForm(tk);
			if( repIdForm != NOT_FOUND )
			{
				tokz.v_addToken(pos1, pos2, g_currentLine, repIdForm, tk, LITERAL);
			}
			else
			{
				tokz.v_addToken(pos1, pos2, g_currentLine, g_currentId_IForm, tk, LITERAL);
			}

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
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, ALERT, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, ALERT, tk, ALERT);
						break;
					
					//  Escape /b backspace
					case 98:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, BACKSPACE, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, BACKSPACE, tk, BACKSPACE);
						break;
					//  Escape /f forward feed page
					case 102:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, FORWARD_FEED, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, FORWARD_FEED, tk, FORWARD_FEED);
						break;
					//  Escape /n  new line	
					case 110:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, NEW_LINE, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, NEW_LINE, tk, NEW_LINE);

						break;
					//  Escape /r  carriage return
					case 114:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, CARRIAGE_RETURN, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, CARRIAGE_RETURN, tk, CARRIAGE_RETURN);
						break;
					//  Escape /t  horizontal tab
					case 116:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, HORIZONTAL_TAB, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, HORIZONTAL_TAB, tk, HORIZONTAL_TAB);
						break;
					//  Escape /v  vertical tab
					case 118:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, VERTICAL_TAB, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, VERTICAL_TAB, tk, VERTICAL_TAB);
						break;
					//  Symbol /'  single quotes
					case 27:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, SINGLE_QUOTATION, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, SINGLE_QUOTATION, tk, SINGLE_QUOTATION);
						break;
					
					//  Symbol /"  double quotes
					case 34:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, DOBLE_QUOTATION, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, DOBLE_QUOTATION, tk, DOBLE_QUOTATION);
						break;
					
						//  Symbol //  back slash
					case 92:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, BACK_SLASH, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, BACK_SLASH, tk, BACK_SLASH);
						break;
					
					//AfxMessageBox(_T("reconocio escape"));
				}
			}
			++g_currentPos;
		}
		if( symbol == CARRIAGE_RETURN || symbol == NUL )
		{
				CAipi_Error err;
				err.displayGUIError(LEXICAL, LEX_ERROR, _T("Close string symbol is missed") );
				return LEX_ERROR;
		}
		
			
		pos2 = g_currentPos;
		

		tstring tk = getTextRange(pos1, pos2);
		if( tk == _T("STOP_ERROR") )
		{
			return STOP_ERROR;
		}
		
		++g_currentId_IForm;
		CAipi_Symbol symb;
		symb.addId_IntForm(tk, g_currentId_IForm);
		int repIdForm = symb.findId_IntForm(tk);
		if( repIdForm != NOT_FOUND )
		{
			tokz.v_addToken(pos1, pos2, g_currentLine, repIdForm, tk, LITERAL);
		}
		else
		{
			tokz.v_addToken(pos1, pos2, g_currentLine, g_currentId_IForm, tk, LITERAL);
		}
		
		
		
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

		while( isDigit(symbol) || symbol == PERIOD && symbol != NUL)
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
		tk = getTextRange(pos1, pos2);
		if( tk == _T("STOP_ERROR") )
		{
			return STOP_ERROR;
		}

		double g_currentId_IForm = _tcstod(tk.data(), NULL);
		tokz.v_addToken(pos1, pos2, g_currentLine, g_currentId_IForm, tk, DIGIT);

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
		while( isAlphaNumeric(symbol) && symbol != NUL )
		{
			++g_currentPos;
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
		
		

		tk = getTextRange(pos1, pos2);
		if( tk == _T("STOP_ERROR") )
		{
			return STOP_ERROR;
		}
		CAipi_Symbol symb;
		int keyWord = symb.findKeyWord(tk);
		if( keyWord != NOT_FOUND )
		{
			//tokz.addToken(pos1, pos2, g_currentLine, kw, tk, KEYWORD);
			tokz.v_addToken(pos1, pos2, g_currentLine, keyWord, tk, keyWord);
			return keyWord;
		}
		else
		{
			++g_currentId_IForm;
			symb.addId_IntForm(tk, g_currentId_IForm);
			int repIdForm = symb.findId_IntForm(tk);
			if( repIdForm != NOT_FOUND )
			{
				tokz.v_addToken(pos1, pos2, g_currentLine, repIdForm, tk, IDENTIFIER);
			}
			else
			{
				tokz.v_addToken(pos1, pos2, g_currentLine, g_currentId_IForm, tk, IDENTIFIER);
			}
			//str.Format(_T("Char Last Pos...%d  " ), pos2);
			//AfxMessageBox(str);
			

			return IDENTIFIER;
		}

		
	}

	if (symbol == NUL )
	{
		//AfxMessageBox(_T("Fin del archivo"));
		return NUL;
		
	}

	
		
return UNDEFINE;
}
/////////////////////////////////////////////////////
//// End addTokenizerGUIExp /////
//////////////////////////////////////////////////// 










///////////////////////////////////////////////////////
///// Begin getTokenGUI ////
///////////////////////////////////////////////////////
int CAipi_Lexer::getTokenGUI()
{
	CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
	CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
	CScintillaView* pView = (CScintillaView*) pChild->GetActiveView();
	ASSERT(pView);
	CScintillaCtrl& rCtrl = pView->GetCtrl();

	int tempPos = 0;
	int symbol = rCtrl.GetCharAt(g_currentPos);
	int pos1 = 0;
	int pos2 = 0;
	tstring tk = _T("");
		
	//Skip over white space and newline
	while( symbol == SPACE || symbol == CARRIAGE_RETURN || symbol == NEW_LINE || symbol == HORIZONTAL_TAB || symbol == VERTICAL_TAB )
	{
		if( symbol == NUL)
		{
			return NUL;
		}
		
		if( symbol == NEW_LINE )
		{
			++g_currentLine;
		}
		
		++g_currentPos;
		symbol = rCtrl.GetCharAt(g_currentPos);
		
	}


		
	//Comments
	if( symbol == SLASH )
	{	
		tempPos = g_currentPos;
		int next_symbol = rCtrl.GetCharAt(++tempPos );
			
		//Simple comment
		if( next_symbol == SLASH )
		{
			pos1 = g_currentPos;
			while ( symbol != CARRIAGE_RETURN && symbol != NEW_LINE  && symbol != NUL )
			{
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
					
			}
				
			pos2 = tempPos;
			g_currentPos = pos2;
			return COMMENT;
		}
		//Complex comment
		else if( next_symbol == ASTERIC )
		{
			pos1 = g_currentPos;
			
			do//find end comment
			{
				while ( symbol != ASTERIC && symbol != NUL )
				{
					if( symbol == NEW_LINE )
					{
						++g_currentLine;
					}
					++tempPos;
					symbol = rCtrl.GetCharAt(tempPos);
					
				}
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == NUL )
				{
					CAipi_Error err;
					err.displayGUIError(LEXICAL, LEX_ERROR, _T("Close comment is missed") );
					return LEX_ERROR;
				}

			}while( symbol != SLASH  );
			
			pos2 = ++tempPos;
			g_currentPos = pos2;
	
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
		switch( symbol )
		{
			case EQUAL:
				
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					g_currentPos = tempPos;
					return ET;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					return AS;
				}
				
			case EXCLAMATION:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					g_currentPos = tempPos;
					return NE;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					return NOT_OP;
				}
				
			case AMPERSAND:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == AMPERSAND )
				{
					g_currentPos = tempPos;
					return AND_OP;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					return AND_BIT;
				}
				
			case VERTICAL_BAR:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == VERTICAL_BAR )
				{
					g_currentPos = tempPos;
					return OR_OP;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					return OR_BIT;
				}
				
			case LESS_THAN:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					g_currentPos = tempPos;
					return LE;
				}
				else if ( symbol == LESS_THAN )
				{
					g_currentPos = tempPos;
					return RIGHT_OP;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					return LT;
				}
				
			case GREATER_THAN:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					g_currentPos = tempPos;
					return GE;
				}
				else if ( symbol == GREATER_THAN )
				{
					g_currentPos = tempPos;
					return LEFT_OP;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					return GT;
				}
				
			case PLUS_SIGN:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					g_currentPos = tempPos;
					return ADD_ASSIGN;
				}
				else if ( symbol == PLUS_SIGN )
				{
					g_currentPos = tempPos;
					return INC_OP;
				}
				else
				{
				   	symbol = rCtrl.GetCharAt(g_currentPos);
					return PLUS_SIGN;
				}
				
			case MINUS_SIGN:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					g_currentPos = tempPos;
					return SUB_ASSIGN;
				}
				else if ( symbol == MINUS_SIGN )
				{
					g_currentPos = tempPos;
					return DEC_OP;
				}
				else if ( symbol == GT )
				{
					g_currentPos = tempPos;
					return PTR_OP;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					return MINUS_SIGN;
				}
				
			case ASTERIC:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					g_currentPos = tempPos;
					return MUL_ASSIGN;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					return ASTERIC;
				}
				
			case SLASH:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					g_currentPos = tempPos;
					return DIV_ASSIGN;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					return SLASH;
				}
				
			case PERCENT:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					g_currentPos = tempPos;
					return MOD_ASSIGN;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					return PERCENT;
				}
			
			case COLON:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == COLON )
				{
					g_currentPos = tempPos;
					return SCOPE_OP;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					return COLON;
				}
			
			case CARET:
				return XOR_BIT;
				
			
			case EQUIVALENCY:
				return NOT_BIT;
			
			case QUESTION:
				return QUESTION;

		}
	
	}


	//Check for punctuators
	if( isPunctuator(symbol) )
	{
		switch( symbol )
		{
					
			case SEMICOLON:
				return SEMICOLON;
			
			case OPEN_PARENTHESIS:
				return OPEN_PARENTHESIS;
			
			case CLOSE_PARENTHESIS:
				return CLOSE_PARENTHESIS;
				//Reserve for large identifier
			/*
			case OPEN_BRACKET:
				return OPEN_BRACKET;
			*/
			case CLOSE_BRACKET:
				return CLOSE_BRACKET;
						
			case OPEN_BRACE:
				return OPEN_BRACE;

			case CLOSE_BRACE:
				return CLOSE_BRACE;
			/*
			case COLON:
				return COLON;
			*/

			case COMMA:
				return COMMA;

			case PERIOD:
				return PERIOD;

			case NUMBER_SIGN:
				return NUMBER_SIGN;

			case AT_SYMBOL:
				return AT_SYMBOL;
		
		}
		
	}

	
	//Double Quoted Strings
	if( symbol == DOBLE_QUOTATION )
	{
		pos1 = g_currentPos;
		++g_currentPos;
		symbol = rCtrl.GetCharAt(g_currentPos);
		
		//Empty string tokens
		if( symbol == DOBLE_QUOTATION )
		{
			pos2 = g_currentPos + 1;
			return LITERAL;
		}
		
		
		
		while(symbol != DOBLE_QUOTATION && symbol != CARRIAGE_RETURN && symbol != NUL  )
		{
			symbol = rCtrl.GetCharAt(g_currentPos);
			
			//Check for \n escape sequence
			if( symbol == BACK_SLASH )
			{
				tempPos = g_currentPos;
				++tempPos;
				int escSymbol = rCtrl.GetCharAt(tempPos);
				
				switch (escSymbol) 
				{
					//  Escape /a  alert
					case 97:
						g_currentPos = tempPos;
						break;
					//  Escape /b backspace
					case 98:
						g_currentPos = tempPos;
						break;
					//  Escape /f forward feed page
					case 102:
						g_currentPos = tempPos;
						break;
					//  Escape /n  new line	
					case 110:
						g_currentPos = tempPos;
						break;
					//  Escape /r  carriage return
					case 114:
						g_currentPos = tempPos;
						break;
					//  Escape /t  horizontal tab
					case 116:
						g_currentPos = tempPos;
						break;
					//  Escape /v  vertical tab
					case 118:
						g_currentPos = tempPos;
						break;
					//  Symbol /'  single quotes
					case 27:
						g_currentPos = tempPos;
						break;
					
					//  Symbol /"  double quotes
					case 34:
						g_currentPos = tempPos;
						break;
					
						//  Symbol //  back slash
					case 92:
						g_currentPos = tempPos;
						break;
										
				}
				
				if( escSymbol != 34 )
				{
					symbol = escSymbol;
				}
			
			}
				
			++g_currentPos;
		}

		if( symbol == CARRIAGE_RETURN || symbol == NUL )
		{
			CAipi_Error err;
			err.displayGUIError(LEXICAL, LEX_ERROR, _T("Close string symbol is missed") );
			return LEX_ERROR;
		}
		
		pos2 = g_currentPos;
		symbol = rCtrl.GetCharAt(g_currentPos);
		
		if( symbol != SPACE )
		{
			--g_currentPos;
		}
		
		return LITERAL;
		
	}
	

	//Single Quoted Strings
	if( symbol == SINGLE_QUOTATION )
	{
		pos1 = g_currentPos;
		++g_currentPos;
		symbol = rCtrl.GetCharAt(g_currentPos);
		//Empty char tokens
		if( symbol == SINGLE_QUOTATION )
		{
			pos2 = g_currentPos + 1;
			return LITERAL;
		}
		
		
		while(symbol != SINGLE_QUOTATION && symbol != CARRIAGE_RETURN && symbol != NUL  )
		{
			symbol = rCtrl.GetCharAt(g_currentPos);
			
			//Check for \n escape sequence
			if( symbol == BACK_SLASH )
			{
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				
				switch (symbol) 
				{
					//  Escape /a  alert
					case 97:
						g_currentPos = tempPos;
						break;
					//  Escape /b backspace
					case 98:
						g_currentPos = tempPos;
						break;
					//  Escape /f forward feed page
					case 102:
						g_currentPos = tempPos;
						break;
					//  Escape /n  new line	
					case 110:
						g_currentPos = tempPos;
						break;
					//  Escape /r  carriage return
					case 114:
						g_currentPos = tempPos;
						break;
					//  Escape /t  horizontal tab
					case 116:
						g_currentPos = tempPos;
						break;
					//  Escape /v  vertical tab
					case 118:
						g_currentPos = tempPos;
						break;
					//  Symbol /'  single quotes
					case 27:
						g_currentPos = tempPos;
						break;
					
					//  Symbol /"  double quotes
					case 34:
						g_currentPos = tempPos;
						break;
					
						//  Symbol //  back slash
					case 92:
						g_currentPos = tempPos;
						break;
										
				}
			}
			++g_currentPos;
		}
		if( symbol == CARRIAGE_RETURN || symbol == NUL )
		{
				CAipi_Error err;
				err.displayGUIError(LEXICAL, LEX_ERROR, _T("Close string symbol is missed") );
				return LEX_ERROR;
		}
				
		pos2 = g_currentPos;
		symbol = rCtrl.GetCharAt(g_currentPos);
		if( symbol != SPACE )
		{
			--g_currentPos;
		}
		
		return LITERAL;
		
	}



	//Aipi Variable
	if( symbol == DOLLAR )
	{
		pos1 = g_currentPos;
		++g_currentPos;
		symbol = rCtrl.GetCharAt(g_currentPos);
		//Empty char tokens
		if( symbol == DOLLAR )
		{
			pos2 = g_currentPos + 1;
			return AIPI_VAR;
		}
		
		
		while(symbol != DOLLAR && symbol != CARRIAGE_RETURN && symbol != NUL)
		{
			symbol = rCtrl.GetCharAt(g_currentPos);
			++g_currentPos;
		}
		if( symbol == CARRIAGE_RETURN || symbol == NUL  )
		{
				CAipi_Error err;
				err.displayGUIError(LEXICAL, LEX_ERROR, _T("Close variable symbol is missed") );
				return LEX_ERROR;
		}
			
		pos2 = g_currentPos;
		symbol = rCtrl.GetCharAt(g_currentPos);
		if( symbol != SPACE )
		{
			--g_currentPos;
		}
		
		return AIPI_VAR;
		
	}



	//Numbers (Natural and Real )
	if( isDigit(symbol)  )
	{
		pos1 = g_currentPos;
		g_currentDigit_Type = NAT_NUMBER;
		int countPeriod = 0;

		while( isDigit(symbol) || symbol == PERIOD && symbol != NUL )
		{
			++g_currentPos;
			symbol = rCtrl.GetCharAt(g_currentPos);
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
		symbol = rCtrl.GetCharAt(g_currentPos);
		if( symbol != SPACE )
		{
			--g_currentPos;
			
		}
		return DIGIT;
	}



	//Aipi Identifier with spaces
	if( symbol == OPEN_BRACKET )
	{
		pos1 = g_currentPos;
		++g_currentPos;
		symbol = rCtrl.GetCharAt(g_currentPos);

		while( symbol == SPACE || symbol == CARRIAGE_RETURN || symbol == NEW_LINE || symbol == HORIZONTAL_TAB || symbol == VERTICAL_TAB )
		{
		  	if( symbol == NUL )
			{
				return NUL;
			}

			if( symbol == NEW_LINE )
			{
				++g_currentLine;
			}

			++g_currentPos;
			 symbol = rCtrl.GetCharAt(g_currentPos);
		}
		
		//Check for array symbol
		if( isDigit(symbol) || symbol == CLOSE_BRACKET )
		{
			g_currentPos = pos1;
			symbol = rCtrl.GetCharAt(g_currentPos);
			return OPEN_BRACKET;
		}
		
		while(symbol != CLOSE_BRACKET && symbol != CARRIAGE_RETURN && symbol != NUL  )
		{
			symbol = rCtrl.GetCharAt(g_currentPos);
			++g_currentPos;
		}
		if( symbol == CARRIAGE_RETURN || symbol == NUL )
		{
				CAipi_Error err;
				err.displayGUIError(LEXICAL, LEX_ERROR, _T("Close identifier symbol is missed") );
				return LEX_ERROR;
		}
					
		pos2 = g_currentPos;
		symbol = rCtrl.GetCharAt(g_currentPos);
		if( symbol != SPACE )
		{
			--g_currentPos;
		}
		
		return IDENTIFIER;

		
	}


	//Identifiers and KeyWords
	if( isAlphabetic(symbol) || symbol == UNDERSCORE )
	{
		pos1 = g_currentPos;
		
		while( isAlphaNumeric(symbol) && symbol != NUL )
		{
			++g_currentPos;
			symbol = rCtrl.GetCharAt(g_currentPos);
			
		}
		
		pos2 = g_currentPos;
		symbol = rCtrl.GetCharAt(g_currentPos);
		if( symbol != SPACE )
		{
			--g_currentPos;
		}
		
		CAipi_Symbol symb;
		int keyWord = symb.findKeyWord(tk);
		
		if( keyWord != NOT_FOUND )
		{
			return keyWord;
		}
		else
		{
			return IDENTIFIER;
		}

		
	}

	if( symbol == NUL )
	{
		return NUL;
	}
	
	
		
return UNDEFINE;
}
///////////////////////////////////////////////////////////////
/// End getTokenGUI ///
///////////////////////////////////////////////////////////////







void CAipi_Lexer::createTokenizerGUI()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
	CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
	CScintillaView* pView = (CScintillaView*) pChild->GetActiveView();
	ASSERT(pView);
	CScintillaCtrl& rCtrl = pView->GetCtrl();
	
	int tok = UNDEFINE;
	long endPos = getGUIDocumentLen();
	m_guiDocumentLen = endPos;

	
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Lexer analyzer..."), RGB(0,0,0), TRUE);
	while ( tok != NUL )
	{
		int symbol = rCtrl.GetCharAt(g_currentPos);
		tok = addTokenizerGUI();
		/*
		CString str;
		str.Format(_T("TOK...%d  " ), tok);
		AfxMessageBox(str);
		*/	
		
		if( tok == STOP_ERROR || tok == LEX_ERROR  )
		{
			break;
		}
	
		pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, g_currentPos*100/endPos);
		++g_currentPos;
		
	}

}








///////////////////////////////////////////////////////
///// Begin getTokenGUI test////
///////////////////////////////////////////////////////
int CAipi_Lexer::testGetTokenGUI()
{
	CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
	CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
	CScintillaView* pView = (CScintillaView*) pChild->GetActiveView();
	ASSERT(pView);
	CScintillaCtrl& rCtrl = pView->GetCtrl();

	CAipi_Tokenizer  tokz;
	CString str;
	
	int tempPos = 0;
	static long g_currentId_IForm = 1000;  //Identifier internal form

	int symbol = rCtrl.GetCharAt(g_currentPos);
	int pos1 = 0;
	int pos2 = 0;
	tstring tk = _T("");
	
	//str.Format(_T("Symbol...%d  " ), symbol);
	//AfxMessageBox(str);
		
	//Skip over white space and newline
	while( symbol == SPACE || symbol == CARRIAGE_RETURN || symbol == NEW_LINE || symbol == HORIZONTAL_TAB || symbol == VERTICAL_TAB )
	{
		if( symbol == NUL)
		{
			return NUL;
		}
		
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
				/*
				str.Format(_T("Simple Comment Symbol...%d  " ), symbol);
				AfxMessageBox(str);
				str.Format(_T("Pos en Comment Simple...%d  " ), tempPos);
				AfxMessageBox(str);
				*/	
			}
				
			//AfxMessageBox(_T("Salio del while"));
			pos2 = tempPos;
			g_currentPos = pos2;
			//str.Format(_T("Pos en Comment Simple...%d  " ), pos2);
			//AfxMessageBox(str);
				
			
			
			
			tk = getTextRange(pos1, pos2);
			
			if( tk == _T("STOP_ERROR") )
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
				while ( symbol != ASTERIC && symbol != NUL )
				{
					if( symbol == NEW_LINE )
						++g_currentLine;

					
					++tempPos;
					symbol = rCtrl.GetCharAt(tempPos);
					//str.Format(_T("Complex Comment Symbol...%d  " ), symbol);
					//AfxMessageBox(str);
					//str.Format(_T("Pos en Comment Complex...%d  " ), tempPos);
					//AfxMessageBox(str);
				}
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);

			}while( symbol != SLASH && symbol != NUL );
			
			
			//AfxMessageBox(_T("Salio del do while"));
			pos2 = ++tempPos;
			g_currentPos = pos2;

			tk = getTextRange(pos1, pos2);
			
			if( tk == _T("STOP_ERROR") )
			{
				AfxMessageBox(_T("The application will be close"));
				return STOP_ERROR;
			}
			
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
					tk = getTextRange(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return ET;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos + 1);
					return AS;
				}
				
			case EXCLAMATION:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return NE;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos + 1);
					return NOT_OP;
				}
				
			case AMPERSAND:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == AMPERSAND )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return AND_OP;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos + 1);
					return AND_BIT;
				}
				
			case VERTICAL_BAR:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == VERTICAL_BAR )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return OR_OP;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos + 1);
					return OR_BIT;
				}
				
			case LESS_THAN:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return LE;
				}
				else if ( symbol == LESS_THAN )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return RIGHT_OP;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos + 1);
					return LT;
				}
				
			case GREATER_THAN:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return GE;
				}
				else if ( symbol == GREATER_THAN )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return LEFT_OP;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos + 1);
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
				
					tk = getTextRange(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return ADD_ASSIGN;
				}
				else if ( symbol == PLUS_SIGN )
				{
					//str.Format(_T("Symbol...%d  " ), symbol);
					//AfxMessageBox(str);
					tk = getTextRange(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return INC_OP;
				}
				else
				{
				   	//str.Format(_T("Symbol Sum...%d  " ), symbol);
					//AfxMessageBox(str);
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos+1);
					return PLUS_SIGN;
				}
				
			case MINUS_SIGN:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return SUB_ASSIGN;
				}
				else if ( symbol == MINUS_SIGN )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return DEC_OP;
				}
				else if ( symbol == GT )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return PTR_OP;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos +1);
					return MINUS_SIGN;
				}
				
			case ASTERIC:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return MUL_ASSIGN;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos + 1);
					return ASTERIC;
				}
				
			case SLASH:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return DIV_ASSIGN;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos + 1);
					return SLASH;
				}
				
			case PERCENT:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return MOD_ASSIGN;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos + 1);
					return PERCENT;
				}
			
			case COLON:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == COLON )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					g_currentPos = tempPos;
					return SCOPE_OP;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos + 1);
					return COLON;
				}
			
			case CARET:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				return XOR_BIT;
				
			
			case EQUIVALENCY:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				return NOT_BIT;
			
			case QUESTION:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				return QUESTION;

		}

		
	}


	//Check for punctuators
	if( isPunctuator(symbol) )
	{
		
		switch( symbol )
		{
					
			case SEMICOLON:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				return SEMICOLON;
			
			case OPEN_PARENTHESIS:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				return OPEN_PARENTHESIS;
			
			case CLOSE_PARENTHESIS:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				return CLOSE_PARENTHESIS;
				//Reserve for large identifier
			/*
			case OPEN_BRACKET:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				return OPEN_BRACKET;
			*/
			case CLOSE_BRACKET:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				return CLOSE_BRACKET;
						
			case OPEN_BRACE:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				return OPEN_BRACE;

			case CLOSE_BRACE:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				return CLOSE_BRACE;
			/*
			case COLON:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				return COLON;
			*/

			case COMMA:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				return COMMA;

			case PERIOD:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				return PERIOD;

			case NUMBER_SIGN:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				return NUMBER_SIGN;

			case AT_SYMBOL:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
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
			tstring tk = getTextRange(pos1, pos2);
			return LITERAL;
		}
		
		
		
		while(symbol != DOBLE_QUOTATION && symbol != CARRIAGE_RETURN && symbol != NUL )
		{
			symbol = rCtrl.GetCharAt(g_currentPos);
			/*
			AfxMessageBox(_T("entro al while"));
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
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					
					//  Escape /b backspace
					case 98:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					//  Escape /f forward feed page
					case 102:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					//  Escape /n  new line	
					case 110:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					//  Escape /r  carriage return
					case 114:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					//  Escape /t  horizontal tab
					case 116:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					//  Escape /v  vertical tab
					case 118:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					//  Symbol /'  single quotes
					case 27:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					
					//  Symbol /"  double quotes
					case 34:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					
						//  Symbol //  back slash
					case 92:
						tk = getTextRange(tempPos -1, tempPos + 1); 
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

		if( symbol == CARRIAGE_RETURN || symbol == NUL )
		{
			AfxMessageBox(_T("Error carriage return"));	
			CAipi_Error err;
			err.displayGUIError(LEXICAL, LEX_ERROR, _T("Close string symbol is missed") );
			return LEX_ERROR;
		}
		
		pos2 = g_currentPos;
		tstring tk = getTextRange(pos1, pos2);
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
			tstring tk = getTextRange(pos1, pos2);
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
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					
					//  Escape /b backspace
					case 98:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					//  Escape /f forward feed page
					case 102:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					//  Escape /n  new line	
					case 110:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					//  Escape /r  carriage return
					case 114:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					//  Escape /t  horizontal tab
					case 116:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					//  Escape /v  vertical tab
					case 118:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					//  Symbol /'  single quotes
					case 27:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					
					//  Symbol /"  double quotes
					case 34:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					
						//  Symbol //  back slash
					case 92:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						break;
					
					//AfxMessageBox(_T("reconocio escape"));
				}
			}
			++g_currentPos;
		}
		if( symbol == CARRIAGE_RETURN || symbol == NUL )
		{
				CAipi_Error err;
				err.displayGUIError(LEXICAL, LEX_ERROR, _T("Close string symbol is missed") );
				return LEX_ERROR;
		}
		
			
		pos2 = g_currentPos;
		

		tstring tk = getTextRange(pos1, pos2);
		symbol = rCtrl.GetCharAt(g_currentPos);
		if( symbol != SPACE )
		{
			--g_currentPos;
		}
		
		return LITERAL;

		
	}



	//Aipi Variable
	if( symbol == DOLLAR )
	{
		//AfxMessageBox(_T("entro a dollar"));
		
		pos1 = g_currentPos;
		++g_currentPos;
		
		symbol = rCtrl.GetCharAt(g_currentPos);
		//Empty char tokens
		if( symbol == DOLLAR )
		{
			//AfxMessageBox(_T("Entro a dollar 2"));
			pos2 = g_currentPos + 1;
			tstring tk = getTextRange(pos1, pos2);
			return AIPI_VAR;
		}
		
		
		while(symbol != DOLLAR && symbol != CARRIAGE_RETURN && symbol != NUL )
		{
			symbol = rCtrl.GetCharAt(g_currentPos);
			//str.Format(_T("Symbol...%d  " ), symbol);
			//AfxMessageBox(str);
			++g_currentPos;
		}
		if( symbol == CARRIAGE_RETURN || symbol == NUL )
		{
				CAipi_Error err;
				err.displayGUIError(LEXICAL, LEX_ERROR, _T("Close string symbol is missed") );
				return LEX_ERROR;
		}
		
			
		pos2 = g_currentPos;
		

		tstring tk = getTextRange(pos1, pos2);
		symbol = rCtrl.GetCharAt(g_currentPos);
		if( symbol != SPACE )
		{
			--g_currentPos;
		}
		
		return AIPI_VAR;

		
	}




	//Numbers (Natural and Real )
	if( isDigit(symbol)  )
	{
		pos1 = g_currentPos;
		g_currentDigit_Type = NAT_NUMBER;
		int countPeriod = 0;

		while( isDigit(symbol) || symbol == PERIOD && symbol != NUL)
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
		tk = getTextRange(pos1, pos2);
		
		
		symbol = rCtrl.GetCharAt(g_currentPos);
		if( symbol != SPACE )
		{
			//AfxMessageBox(_T("no space"));
			--g_currentPos;
			
		}
		return DIGIT;
	}






	//Aipi Identifier with spaces
	if( symbol == OPEN_BRACKET )
	{
		//AfxMessageBox(_T("entro a open bracket"));
		
		pos1 = g_currentPos;
		++g_currentPos;
		
		symbol = rCtrl.GetCharAt(g_currentPos);

		while( symbol == SPACE || symbol == CARRIAGE_RETURN || symbol == NEW_LINE || symbol == HORIZONTAL_TAB || symbol == VERTICAL_TAB )
		{
		  
			if( symbol == NUL )
			{
				return NUL;
			}
			if( symbol == NEW_LINE )
			{
				++g_currentLine;
			}

		++g_currentPos;
		  symbol = rCtrl.GetCharAt(g_currentPos);
		}
		
		//str.Format(_T("Pos...%d  " ), g_currentPos);
		//AfxMessageBox(str);
		//++g_currentPos;
		//symbol = rCtrl.GetCharAt(g_currentPos);
		 //str.Format(_T("Symbol...%d  " ), symbol);
			

		//Check for array symbol
		if( isDigit(symbol) || symbol == CLOSE_BRACKET )
		{
			//AfxMessageBox(_T("lexer"));
	
			g_currentPos = pos1;
			tk = getTextRange(g_currentPos, g_currentPos + 1);
			
			symbol = rCtrl.GetCharAt(g_currentPos);
			//str.Format(_T("Symbol...%d  " ), symbol);
			return OPEN_BRACKET;
		}
		
		while(symbol != CLOSE_BRACKET && symbol != CARRIAGE_RETURN && symbol != NUL )
		{
			symbol = rCtrl.GetCharAt(g_currentPos);
			//str.Format(_T("Symbol...%d  " ), symbol);
			//AfxMessageBox(str);
			++g_currentPos;
		}
		if( symbol == CARRIAGE_RETURN || symbol == NUL )
		{
				CAipi_Error err;
				err.displayGUIError(LEXICAL, LEX_ERROR, _T("Close string symbol is missed") );
				return LEX_ERROR;
		}
		
			
		pos2 = g_currentPos;
		
		tstring tk = getTextRange(pos1, pos2);
		
		symbol = rCtrl.GetCharAt(g_currentPos);
		if( symbol != SPACE )
		{
			--g_currentPos;
		}
		//AfxMessageBox(_T("IDENTIFIER"));
		return IDENTIFIER;

		
	}


	//Identifiers and KeyWords
	if( isAlphabetic(symbol) || symbol == UNDERSCORE )
	{
		//AfxMessageBox(_T("IDENTIFIERS y KEYWORDS"));

		
		pos1 = g_currentPos;
		
		while( isAlphaNumeric(symbol) && symbol != NUL )
		{
			++g_currentPos;
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
		
		tk = getTextRange(pos1, pos2);
		
		//AfxMessageBox(_T("tk:"));
		//AfxMessageBox(tk.data());
		
		if( tk == _T("STOP_ERROR") )
		{
			return STOP_ERROR;
		}
		
		CAipi_Symbol symb;
		int keyWord = symb.findKeyWord(tk);
		
		if( keyWord != NOT_FOUND )
		{
			//AfxMessageBox(_T("Found KeyWord"));
			return keyWord;
		}
		else
		{
			//str.Format(_T("Char Last Pos...%d  " ), pos2);
			//AfxMessageBox(str);
			return IDENTIFIER;
		}

		
	}

	if( symbol == NUL )
	{
		return NUL;
	}
	
	
	
		
return UNDEFINE;
}
///////////////////////////////////////////////////////////////
/// End getTokenGUI ///
///////////////////////////////////////////////////////////////





///////////////////////////////////////////////////////////////
/// Begin addTokenizerGUI////
///////////////////////////////////////////////////////////////////////////////////////////////
int CAipi_Lexer::addTokenizerGUI()
{
	CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
	CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
	CScintillaView* pView = (CScintillaView*) pChild->GetActiveView();
	ASSERT(pView);
	CScintillaCtrl& rCtrl = pView->GetCtrl();

	CAipi_Tokenizer  tokz;
	CString str;
	
	int tempPos = 0;
	//static long g_currentId_IForm = 1000;  //Identifier internal form

	int symbol = rCtrl.GetCharAt(g_currentPos);
	int pos1 = 0;
	int pos2 = 0;
	tstring tk = _T("");
	
	//str.Format(_T("Symbol...%d  " ), symbol);
	//AfxMessageBox(str);
	//str.Format(_T("Int Form...%d  " ), g_currentId_IForm);
	//AfxMessageBox(str);
		
	//Skip over white space and newline
	while( symbol == SPACE || symbol == CARRIAGE_RETURN || symbol == NEW_LINE || symbol == HORIZONTAL_TAB || symbol == VERTICAL_TAB )
	{
		if( symbol == NUL )
		{
			return NUL;
		}
		
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
				/*
				str.Format(_T("Simple Comment Symbol...%d  " ), symbol);
				AfxMessageBox(str);
				str.Format(_T("Pos en Comment Simple...%d  " ), tempPos);
				AfxMessageBox(str);
				*/	
			}
				
			//AfxMessageBox(_T("Salio del while"));
			pos2 = tempPos;
			g_currentPos = pos2;
			//str.Format(_T("Pos en Comment Simple...%d  " ), pos2);
			//AfxMessageBox(str);
				
			
			
			
			tk = getTextRange(pos1, pos2);
			if( tk == _T("STOP_ERROR") )
			{
				AfxMessageBox(_T("Token out of range.The application will be close"));
				return STOP_ERROR;
			}
			
			
			//tokz.addToken(pos1, pos2, g_currentLine, SIMPLE_COMMENT, tk, COMMENT);
			tokz.v_addToken(pos1, pos2, g_currentLine, SIMPLE_COMMENT, tk, COMMENT);
			
			
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
				while ( symbol != ASTERIC && symbol != NUL )
				{
					/*
					if( symbol == NEW_LINE )
						++g_currentLine;
					*/	
					
					++tempPos;
					symbol = rCtrl.GetCharAt(tempPos);
					//str.Format(_T("Complex Comment Symbol...%d  " ), symbol);
					//AfxMessageBox(str);
					//str.Format(_T("Pos en Comment Complex...%d  " ), tempPos);
					//AfxMessageBox(str);
				}
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);

				if( symbol == NUL )
				{
					CAipi_Error err;
					err.displayGUIError(LEXICAL, LEX_ERROR, _T("Close comment is missed") );
					return LEX_ERROR;
				}

			
			}while( symbol != SLASH  );
			
			
			//AfxMessageBox(_T("Salio del do while"));
			pos2 = ++tempPos;
			g_currentPos = pos2;

			tk = getTextRange(pos1, pos2);
			
			if( tk == _T("STOP_ERROR") )
			{
				AfxMessageBox(_T("Token out of range.The application will be close"));
				return STOP_ERROR;
			}
			
			//tokz.addToken(pos1, pos2, g_currentLine, COMPLEX_COMMENT, tk, COMMENT);
			tokz.v_addToken(pos1, pos2, g_currentLine, COMPLEX_COMMENT, tk, COMMENT);
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
					tk = getTextRange(tempPos -1, tempPos + 1);
					//tokz.addToken(tempPos -1, tempPos +1, g_currentLine, ET, tk, OPERATOR);
					tokz.v_addToken(tempPos -1, tempPos +1, g_currentLine, ET, tk, ET);
					g_currentPos = tempPos;
					return ET;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos + 1);
					//tokz.addToken(g_currentPos, g_currentPos + 1, g_currentLine, AS, tk, OPERATOR);
					tokz.v_addToken(g_currentPos, g_currentPos + 1, g_currentLine, AS, tk, AS);
					return AS;
				}
				
			case EXCLAMATION:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					//tokz.addToken(tempPos -1, tempPos +1, g_currentLine, NE, tk, OPERATOR);
					tokz.v_addToken(tempPos -1, tempPos +1, g_currentLine, NE, tk, NE);
					g_currentPos = tempPos;
					return NE;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos + 1);
					//tokz.addToken(g_currentPos, g_currentPos + 1, g_currentLine, NOT_OP, tk, OPERATOR);
					tokz.v_addToken(g_currentPos, g_currentPos + 1, g_currentLine, NOT_OP, tk, NOT_OP);
					return NOT_OP;
				}
				
			case AMPERSAND:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == AMPERSAND )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					//tokz.addToken(tempPos -1, tempPos +1, g_currentLine, AND_OP, tk, OPERATOR);
					tokz.v_addToken(tempPos -1, tempPos +1, g_currentLine, AND_OP, tk, AND_OP);
					g_currentPos = tempPos;
					return AND_OP;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos + 1);
					//tokz.addToken(g_currentPos, g_currentPos + 1, g_currentLine, AND_BIT, tk, OPERATOR);
					tokz.v_addToken(g_currentPos, g_currentPos + 1, g_currentLine, AND_BIT, tk, AND_BIT);
					return AND_BIT;
				}
				
			case VERTICAL_BAR:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == VERTICAL_BAR )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					//tokz.addToken(tempPos -1, tempPos +1, g_currentLine, OR_OP, tk, OPERATOR);
					tokz.v_addToken(tempPos -1, tempPos +1, g_currentLine, OR_OP, tk, OR_OP);
					g_currentPos = tempPos;
					return OR_OP;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos + 1);
					//tokz.addToken(g_currentPos, g_currentPos + 1, g_currentLine, OR_BIT, tk, OPERATOR);
					tokz.v_addToken(g_currentPos, g_currentPos + 1, g_currentLine, OR_BIT, tk, OR_BIT);
					return OR_BIT;
				}
				
			case LESS_THAN:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					//tokz.addToken(tempPos -1, tempPos +1, g_currentLine, LE, tk, OPERATOR);
					tokz.v_addToken(tempPos -1, tempPos +1, g_currentLine, LE, tk, LE);
					g_currentPos = tempPos;
					return LE;
				}
				else if ( symbol == LESS_THAN )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					//tokz.addToken(tempPos -1, tempPos +1, g_currentLine, RIGHT_OP, tk, OPERATOR);
					tokz.v_addToken(tempPos -1, tempPos +1, g_currentLine, RIGHT_OP, tk, RIGHT_OP);
					g_currentPos = tempPos;
					return RIGHT_OP;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos + 1);
					//tokz.addToken(g_currentPos, g_currentPos + 1, g_currentLine, LT, tk, OPERATOR);
					tokz.v_addToken(g_currentPos, g_currentPos + 1, g_currentLine, LT, tk, LT);
					return LT;
				}
				
			case GREATER_THAN:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					//tokz.addToken(tempPos -1, tempPos +1, g_currentLine, GE, tk, OPERATOR);
					tokz.v_addToken(tempPos -1, tempPos +1, g_currentLine, GE, tk, GE);
					g_currentPos = tempPos;
					return GE;
				}
				else if ( symbol == GREATER_THAN )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					//tokz.addToken(tempPos -1, tempPos +1, g_currentLine, LEFT_OP, tk, OPERATOR);
					tokz.v_addToken(tempPos -1, tempPos +1, g_currentLine, LEFT_OP, tk, LEFT_OP);
					g_currentPos = tempPos;
					return LEFT_OP;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos + 1);
					//tokz.addToken(g_currentPos, g_currentPos + 1, g_currentLine, GT, tk, OPERATOR);
					tokz.v_addToken(g_currentPos, g_currentPos + 1, g_currentLine, GT, tk, GT);
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
				
					tk = getTextRange(tempPos -1, tempPos + 1);
					tokz.v_addToken(tempPos -1, tempPos +1, g_currentLine, ADD_ASSIGN, tk, ADD_ASSIGN);
					//tokz.addToken(tempPos -1, tempPos +1, g_currentLine, ADD_ASSIGN, tk, OPERATOR);
					g_currentPos = tempPos;
					return ADD_ASSIGN;
				}
				else if ( symbol == PLUS_SIGN )
				{
					//str.Format(_T("Symbol...%d  " ), symbol);
					//AfxMessageBox(str);
				
					tk = getTextRange(tempPos -1, tempPos + 1);
					//tokz.addToken(tempPos -1, tempPos +1, g_currentLine, INC_OP, tk, OPERATOR);
					tokz.v_addToken(tempPos -1, tempPos +1, g_currentLine, INC_OP, tk, INC_OP);
					g_currentPos = tempPos;
					return INC_OP;
				}
				else
				{
				
					//str.Format(_T("Symbol Sum...%d  " ), symbol);
					//AfxMessageBox(str);
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos+1);
					//tokz.addToken(g_currentPos, g_currentPos+1, g_currentLine, PLUS_SIGN, tk, OPERATOR);
					tokz.v_addToken(g_currentPos, g_currentPos+1, g_currentLine, PLUS_SIGN, tk, PLUS_SIGN);
					return PLUS_SIGN;
				}
				
			case MINUS_SIGN:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					//tokz.addToken(tempPos -1, tempPos +1, g_currentLine, SUB_ASSIGN, tk, OPERATOR);
					tokz.v_addToken(tempPos -1, tempPos +1, g_currentLine, SUB_ASSIGN, tk, SUB_ASSIGN);
					g_currentPos = tempPos;
					return SUB_ASSIGN;
				}
				else if ( symbol == MINUS_SIGN )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					//tokz.addToken(tempPos -1, tempPos +1, g_currentLine, DEC_OP, tk, OPERATOR);
					tokz.v_addToken(tempPos -1, tempPos +1, g_currentLine, DEC_OP, tk, DEC_OP);
					g_currentPos = tempPos;
					return DEC_OP;
				}
				else if ( symbol == GT )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					//tokz.addToken(tempPos -1, tempPos +1, g_currentLine, PTR_OP, tk, OPERATOR);
					tokz.v_addToken(tempPos -1, tempPos +1, g_currentLine, PTR_OP, tk, PTR_OP);
					g_currentPos = tempPos;
					return PTR_OP;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos +1);
					//tokz.addToken(g_currentPos, g_currentPos +1, g_currentLine, MINUS_SIGN, tk, OPERATOR);
					tokz.v_addToken(g_currentPos, g_currentPos +1, g_currentLine, MINUS_SIGN, tk, MINUS_SIGN);
					return MINUS_SIGN;
				}
				
			case ASTERIC:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					//tokz.addToken(tempPos -1, tempPos +1, g_currentLine, MUL_ASSIGN, tk, OPERATOR);
					tokz.v_addToken(tempPos -1, tempPos +1, g_currentLine, MUL_ASSIGN, tk, MUL_ASSIGN);
					g_currentPos = tempPos;
					return MUL_ASSIGN;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos + 1);
					//tokz.addToken(g_currentPos, g_currentPos + 1, g_currentLine, ASTERIC, tk, OPERATOR);
					tokz.v_addToken(g_currentPos, g_currentPos + 1, g_currentLine, ASTERIC, tk, ASTERIC);
					return ASTERIC;
				}
				
			case SLASH:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					//tokz.addToken(tempPos -1, tempPos +1, g_currentLine, DIV_ASSIGN, tk, OPERATOR);
					tokz.v_addToken(tempPos -1, tempPos +1, g_currentLine, DIV_ASSIGN, tk, DIV_ASSIGN);
					g_currentPos = tempPos;
					return DIV_ASSIGN;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos + 1);
					//tokz.addToken(g_currentPos, g_currentPos +1, g_currentLine, SLASH, tk, OPERATOR);
					tokz.v_addToken(g_currentPos, g_currentPos +1, g_currentLine, SLASH, tk, SLASH);
					return SLASH;
				}
				
			case PERCENT:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == EQUAL )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					//tokz.addToken(tempPos -1, tempPos +1, g_currentLine, MOD_ASSIGN, tk, OPERATOR);
					tokz.v_addToken(tempPos -1, tempPos +1, g_currentLine, MOD_ASSIGN, tk, MOD_ASSIGN);
					g_currentPos = tempPos;
					return MOD_ASSIGN;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos + 1);
					//tokz.addToken(g_currentPos, g_currentPos +1, g_currentLine, PERCENT, tk, OPERATOR);
					tokz.v_addToken(g_currentPos, g_currentPos +1, g_currentLine, PERCENT, tk, PERCENT);
					return PERCENT;
				}
			
			case COLON:
				tempPos = g_currentPos;
				++tempPos;
				symbol = rCtrl.GetCharAt(tempPos);
				if( symbol == COLON )
				{
					tk = getTextRange(tempPos -1, tempPos + 1);
					//tokz.addToken(tempPos -1, tempPos +1, g_currentLine, SCOPE_OP, tk, OPERATOR);
					tokz.v_addToken(tempPos -1, tempPos +1, g_currentLine, SCOPE_OP, tk, SCOPE_OP);
					g_currentPos = tempPos;
					return SCOPE_OP;
				}
				else
				{
					symbol = rCtrl.GetCharAt(g_currentPos);
					tk = getTextRange(g_currentPos, g_currentPos + 1);
					//tokz.addToken(g_currentPos, g_currentPos + 1, g_currentLine, COLON, tk, OPERATOR);
					tokz.v_addToken(g_currentPos, g_currentPos + 1, g_currentLine, COLON, tk, COLON);
					return COLON;
				}
			
			case CARET:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				//tokz.addToken(g_currentPos, g_currentPos+1, g_currentLine, XOR_BIT, tk, OPERATOR);
				tokz.v_addToken(g_currentPos, g_currentPos+1, g_currentLine, XOR_BIT, tk, XOR_BIT);
				return XOR_BIT;
				
			
			case EQUIVALENCY:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				//tokz.addToken(g_currentPos, g_currentPos+1, g_currentLine, NOT_BIT, tk, OPERATOR);
				tokz.v_addToken(g_currentPos, g_currentPos+1, g_currentLine, NOT_BIT, tk, XOR_BIT);
				return NOT_BIT;
			
			case QUESTION:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				//tokz.addToken(g_currentPos, g_currentPos+1, g_currentLine, QUESTION, tk, OPERATOR);
				tokz.v_addToken(g_currentPos, g_currentPos+1, g_currentLine, QUESTION, tk, QUESTION);
				return QUESTION;

		}

		
	}


	//Check for punctuators
	if( isPunctuator(symbol) )
	{
		
		switch( symbol )
		{
					
			case SEMICOLON:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				//tokz.addToken(g_currentPos, g_currentPos+1, g_currentLine, SEMICOLON, tk, PUNCTUATOR);
				tokz.v_addToken(g_currentPos, g_currentPos+1, g_currentLine, SEMICOLON, tk, SEMICOLON);
				return SEMICOLON;
			
			case OPEN_PARENTHESIS:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				//tokz.addToken(g_currentPos, g_currentPos+1, g_currentLine, OPEN_PARENTHESIS, tk, PUNCTUATOR);
				tokz.v_addToken(g_currentPos, g_currentPos+1, g_currentLine, OPEN_PARENTHESIS, tk, OPEN_PARENTHESIS);
				return OPEN_PARENTHESIS;
			
			case CLOSE_PARENTHESIS:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				//tokz.addToken(g_currentPos, g_currentPos+1, g_currentLine, CLOSE_PARENTHESIS, tk, PUNCTUATOR);
				tokz.v_addToken(g_currentPos, g_currentPos+1, g_currentLine, CLOSE_PARENTHESIS, tk, CLOSE_PARENTHESIS);
				return CLOSE_PARENTHESIS;
				//Reserve for large identifier
			/*
			case OPEN_BRACKET:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				//tokz.addToken(g_currentPos, g_currentPos+1, g_currentLine, OPEN_BRACKET, tk, PUNCTUATOR);
				tokz.v_addToken(g_currentPos, g_currentPos+1, g_currentLine, OPEN_BRACKET, tk, OPEN_BRACKET);
				return OPEN_BRACKET;
			*/
			case CLOSE_BRACKET:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				//tokz.addToken(g_currentPos, g_currentPos+1, g_currentLine, CLOSE_BRACKET, tk, PUNCTUATOR);
				tokz.v_addToken(g_currentPos, g_currentPos+1, g_currentLine, CLOSE_BRACKET, tk, CLOSE_BRACKET);
				return CLOSE_BRACKET;
						
			case OPEN_BRACE:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				//tokz.addToken(g_currentPos, g_currentPos+1, g_currentLine, OPEN_BRACE, tk, PUNCTUATOR);
				tokz.v_addToken(g_currentPos, g_currentPos+1, g_currentLine, OPEN_BRACE, tk, OPEN_BRACE);
				return OPEN_BRACE;

			case CLOSE_BRACE:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				//tokz.addToken(g_currentPos, g_currentPos+1, g_currentLine, CLOSE_BRACE, tk, PUNCTUATOR);
				tokz.v_addToken(g_currentPos, g_currentPos+1, g_currentLine, CLOSE_BRACE, tk, CLOSE_BRACE);
				return CLOSE_BRACE;
			/*
			case COLON:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				tokz.addToken(g_currentPos, g_currentPos+1, g_currentLine, COLON, tk, PUNCTUATOR);
				//tokz.v_addToken(g_currentPos, g_currentPos+1, g_currentLine, COLON, tk, COLON);
				return COLON;
			*/

			case COMMA:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				//tokz.addToken(g_currentPos, g_currentPos+1, g_currentLine, COMMA, tk, PUNCTUATOR);
				tokz.v_addToken(g_currentPos, g_currentPos+1, g_currentLine, COMMA, tk, COMMA);
				return COMMA;

			case PERIOD:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				//tokz.addToken(g_currentPos, g_currentPos+1, g_currentLine, PERIOD, tk, PUNCTUATOR);
				tokz.v_addToken(g_currentPos, g_currentPos+1, g_currentLine, PERIOD, tk, PERIOD);
				return PERIOD;

			case NUMBER_SIGN:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				//tokz.addToken(g_currentPos, g_currentPos+1, g_currentLine, NUMBER_SIGN, tk, PUNCTUATOR);
				tokz.v_addToken(g_currentPos, g_currentPos+1, g_currentLine, NUMBER_SIGN, tk, NUMBER_SIGN);
				return NUMBER_SIGN;

			case AT_SYMBOL:
				tk = getTextRange(g_currentPos, g_currentPos + 1);
				//tokz.addToken(g_currentPos, g_currentPos+1, g_currentLine, AT_SYMBOL, tk, PUNCTUATOR);
				tokz.v_addToken(g_currentPos, g_currentPos+1, g_currentLine, AT_SYMBOL, tk, AT_SYMBOL);
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
			tstring tk = getTextRange(pos1, pos2);
			//Eliminates doble quotation symbols
			tk.erase(0, 1);
			//AfxMessageBox(tk.data());
			int len = tk.length();
			tk.erase(len-1);
			//AfxMessageBox(tk.data());
			
			++g_currentId_IForm;
			CAipi_Symbol symb;
			symb.addId_IntForm(tk, g_currentId_IForm);
			int repIdForm = symb.findId_IntForm(tk);
			if( repIdForm != NOT_FOUND )
			{
				tokz.v_addToken(pos1, pos2, g_currentLine, repIdForm, tk, LITERAL);
			}
			else
			{
				tokz.v_addToken(pos1, pos2, g_currentLine, g_currentId_IForm, tk, LITERAL);
			}
			
			return LITERAL;
		}
		
		
		
		while(symbol != DOBLE_QUOTATION && symbol != CARRIAGE_RETURN && symbol != NUL )
		{
			symbol = rCtrl.GetCharAt(g_currentPos);
			
			/*
			AfxMessageBox(_T("entro al while"));
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
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, ALERT, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, ALERT, tk, ALERT);
						break;
					
					//  Escape /b backspace
					case 98:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, BACKSPACE, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, BACKSPACE, tk, BACKSPACE);

						break;
					//  Escape /f forward feed page
					case 102:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, FORWARD_FEED, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, FORWARD_FEED, tk, FORWARD_FEED);
						break;
					//  Escape /n  new line	
					case 110:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, NEW_LINE, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, NEW_LINE, tk, NEW_LINE);
						break;
					//  Escape /r  carriage return
					case 114:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, CARRIAGE_RETURN, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, CARRIAGE_RETURN, tk, CARRIAGE_RETURN);
						break;
					//  Escape /t  horizontal tab
					case 116:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, HORIZONTAL_TAB, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, HORIZONTAL_TAB, tk, HORIZONTAL_TAB);
						break;
					//  Escape /v  vertical tab
					case 118:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, VERTICAL_TAB, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, VERTICAL_TAB, tk, VERTICAL_TAB);
						break;
					//  Symbol /'  single quotes
					case 27:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, SINGLE_QUOTATION, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, SINGLE_QUOTATION, tk, SINGLE_QUOTATION);
						break;
					
					//  Symbol /"  double quotes
					case 34:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, DOBLE_QUOTATION, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, DOBLE_QUOTATION, tk, DOBLE_QUOTATION);
						break;
					
						//  Symbol //  back slash
					case 92:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, BACK_SLASH, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, BACK_SLASH, tk, BACK_SLASH);
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

		if( symbol == CARRIAGE_RETURN || symbol == NUL )
		{
			//AfxMessageBox(_T("Error carriage return"));	
			CAipi_Error err;
			err.displayGUIError(LEXICAL, LEX_ERROR, _T("Close string symbol is missed") );
			return LEX_ERROR;
		}
		
			pos2 = g_currentPos;
			tstring tk = getTextRange(pos1, pos2);
			
			//Eliminates doble quotation symbols
			tk.erase(0, 1);
			//AfxMessageBox(tk.data());
			int len = tk.length();
			tk.erase(len-1);
			//AfxMessageBox(tk.data());
						
			++g_currentId_IForm;
			CAipi_Symbol symb;
			symb.addId_IntForm(tk, g_currentId_IForm);
			int repIdForm = symb.findId_IntForm(tk);
			if( repIdForm != NOT_FOUND )
			{
				tokz.v_addToken(pos1, pos2, g_currentLine, repIdForm, tk, LITERAL);	
			}
			else
			{
				tokz.v_addToken(pos1, pos2, g_currentLine, g_currentId_IForm, tk, LITERAL);
			}


		
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
			tstring tk = getTextRange(pos1, pos2);
			
			formatTkNameOpt(tk);
			
			++g_currentId_IForm;
			CAipi_Symbol symb;
			symb.addId_IntForm(tk, g_currentId_IForm);
			int repIdForm = symb.findId_IntForm(tk);
			if( repIdForm != NOT_FOUND )
			{
				tokz.v_addToken(pos1, pos2, g_currentLine, repIdForm, tk, LITERAL);	
			}
			else
			{
				tokz.v_addToken(pos1, pos2, g_currentLine, g_currentId_IForm, tk, LITERAL);
			}
			
			return LITERAL;
		}
		
		
		while(symbol != SINGLE_QUOTATION && symbol != CARRIAGE_RETURN && symbol != NUL   )
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
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, ALERT, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, ALERT, tk, ALERT);
						break;
					
					//  Escape /b backspace
					case 98:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, BACKSPACE, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, BACKSPACE, tk, BACKSPACE);
						break;
					//  Escape /f forward feed page
					case 102:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, FORWARD_FEED, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, FORWARD_FEED, tk, FORWARD_FEED);
						break;
					//  Escape /n  new line	
					case 110:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, NEW_LINE, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, NEW_LINE, tk, NEW_LINE);
						break;
					//  Escape /r  carriage return
					case 114:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, CARRIAGE_RETURN, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, CARRIAGE_RETURN, tk, CARRIAGE_RETURN);
						break;
					//  Escape /t  horizontal tab
					case 116:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, VERTICAL_TAB, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, VERTICAL_TAB, tk, VERTICAL_TAB);
						break;
					//  Escape /v  vertical tab
					case 118:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, VERTICAL_TAB, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, VERTICAL_TAB, tk, VERTICAL_TAB);
						break;
					//  Symbol /'  single quotes
					case 27:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, SINGLE_QUOTATION, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, SINGLE_QUOTATION, tk, SINGLE_QUOTATION);
						break;
					
					//  Symbol /"  double quotes
					case 34:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, DOBLE_QUOTATION, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, DOBLE_QUOTATION, tk, DOBLE_QUOTATION);
						break;
					
						//  Symbol //  back slash
					case 92:
						tk = getTextRange(tempPos -1, tempPos + 1); 
						g_currentPos = tempPos;
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, BACK_SLASH, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, BACK_SLASH, tk, BACK_SLASH);
						break;
					
					//AfxMessageBox(_T("reconocio escape"));
				}
			}
			++g_currentPos;
		}
		if( symbol == CARRIAGE_RETURN || symbol == NUL )
		{
				CAipi_Error err;
				err.displayGUIError(LEXICAL, LEX_ERROR, _T("Close string symbol is missed") );
				return LEX_ERROR;
		}
		
			
		pos2 = g_currentPos;
		

		tstring tk = getTextRange(pos1, pos2);
		tk = formatTkNameOpt(tk);

		++g_currentId_IForm;
		CAipi_Symbol symb;
		symb.addId_IntForm(tk, g_currentId_IForm);
		int repIdForm = symb.findId_IntForm(tk);
		if( repIdForm != NOT_FOUND )
		{
			tokz.v_addToken(pos1, pos2, g_currentLine, repIdForm, tk, LITERAL);	
		}
		else
		{
			tokz.v_addToken(pos1, pos2, g_currentLine, g_currentId_IForm, tk, LITERAL);
		}

		
		symbol = rCtrl.GetCharAt(g_currentPos);
		if( symbol != SPACE )
		{
			--g_currentPos;
		}
		
		return LITERAL;

		
	}



	//Aipi Variable
	if( symbol == DOLLAR )
	{
		//AfxMessageBox(_T("entro a dollar"));
		
		pos1 = g_currentPos;
		++g_currentPos;
		
		symbol = rCtrl.GetCharAt(g_currentPos);
		//Empty char tokens
		if( symbol == DOLLAR )
		{
			//AfxMessageBox(_T("Entro a dollar 2"));
			pos2 = g_currentPos + 1;
			tstring tk = getTextRange(pos1, pos2);

			formatTkNameOpt(tk);

			//tokz.addToken(pos1, pos2, g_currentLine, g_currentId_IForm, tk, AIPI_VAR);
			tokz.v_addToken(pos1, pos2, g_currentLine, g_currentId_IForm, tk, AIPI_VAR);
			
			return AIPI_VAR;
		}
		
		
		while(symbol != DOLLAR && symbol != CARRIAGE_RETURN && symbol != NUL )
		{
			symbol = rCtrl.GetCharAt(g_currentPos);
			
			//str.Format(_T("Symbol...%d  " ), symbol);
			//AfxMessageBox(str);
	
			
			++g_currentPos;
		}
		if( symbol == CARRIAGE_RETURN || symbol == NUL )
		{
				CAipi_Error err;
				err.displayGUIError(LEXICAL, LEX_ERROR, _T("Close variable symbol is missed") );
				return LEX_ERROR;
		}
		
			
		pos2 = g_currentPos;
		


		tk = getTextRange(pos1, pos2);
		tk = formatTkNameOpt(tk);
		
		
		++g_currentId_IForm;
		CAipi_Symbol symb;
		symb.addId_IntForm(tk, g_currentId_IForm);
		int repIdForm = symb.findId_IntForm(tk);
		if( repIdForm != NOT_FOUND )
		{
			tokz.v_addToken(pos1, pos2, g_currentLine, repIdForm, tk, AIPI_VAR);	
		}
		else
		{
			tokz.v_addToken(pos1, pos2, g_currentLine, g_currentId_IForm, tk, AIPI_VAR);
		
		}


		symbol = rCtrl.GetCharAt(g_currentPos);
		if( symbol != SPACE )
		{
			--g_currentPos;
		}
		
		return AIPI_VAR;

		
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
			if( symbol == NUL )
			{
				CAipi_Error err;
				err.displayGUIError(LEXICAL, LEX_ERROR, _T("Another symbol was expected after digit.") );
				return LEX_ERROR;
			}

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
		tk = getTextRange(pos1, pos2);
		if( tk == _T("STOP_ERROR") )
		{
			return STOP_ERROR;
		}

		double g_currentId_IForm = _tcstod(tk.data(), NULL);
		
		tokz.v_addToken(pos1, pos2, g_currentLine, g_currentId_IForm, tk, DIGIT);
		
		symbol = rCtrl.GetCharAt(g_currentPos);
		if( symbol != SPACE )
		{
			//AfxMessageBox(_T("no space"));
			--g_currentPos;
			
		}
		return DIGIT;
	}






	//Aipi Identifier with spaces
	if( symbol == OPEN_BRACKET )
	{
		//AfxMessageBox(_T("entro a open bracket"));
		
		pos1 = g_currentPos;
		++g_currentPos;
		
		symbol = rCtrl.GetCharAt(g_currentPos);

		while( symbol == SPACE || symbol == CARRIAGE_RETURN || symbol == NEW_LINE || symbol == HORIZONTAL_TAB || symbol == VERTICAL_TAB )
		{
		  
			if( symbol == NUL )
			{
				return NUL;
			}

			if( symbol == NEW_LINE )
			{
				++g_currentLine;
			}

		++g_currentPos;
		  symbol = rCtrl.GetCharAt(g_currentPos);
		}
		
		//str.Format(_T("Pos...%d  " ), g_currentPos);
		//AfxMessageBox(str);
		 //++g_currentPos;
		  //symbol = rCtrl.GetCharAt(g_currentPos);
		  //str.Format(_T("Symbol...%d  " ), symbol);
			

		//Check for array symbol
		if( isDigit(symbol) || symbol == CLOSE_BRACKET && symbol != NUL )
		{
			//AfxMessageBox(_T("lexer"));
	
			g_currentPos = pos1;
			tk = getTextRange(g_currentPos, g_currentPos + 1);
			//tokz.addToken(g_currentPos, g_currentPos+1, g_currentLine, OPEN_BRACKET, tk, PUNCTUATOR);
			tokz.v_addToken(g_currentPos, g_currentPos+1, g_currentLine, OPEN_BRACKET, tk, PUNCTUATOR);
			
			symbol = rCtrl.GetCharAt(g_currentPos);
			//str.Format(_T("Symbol...%d  " ), symbol);
		

			return OPEN_BRACKET;
		}
		/*
		//Empty char tokens
		if( symbol == CLOSE_BRACKET )
		{
			//AfxMessageBox(_T("Entro a "));
			
			pos2 = g_currentPos + 1;
			tstring tk = getTextRange(pos1, pos2);
			//tokz.addToken(pos1, pos2, g_currentLine, g_currentId_IForm, tk, IDENTIFIER);
			v_tokz.addToken(pos1, pos2, g_currentLine, g_currentId_IForm, tk, IDENTIFIER);
			return IDENTIFIER;
		}
		*/
		
		while(symbol != CLOSE_BRACKET && symbol != CARRIAGE_RETURN && symbol != NUL  )
		{
			symbol = rCtrl.GetCharAt(g_currentPos);
			
			//str.Format(_T("Symbol...%d  " ), symbol);
			//AfxMessageBox(str);
	
			
			++g_currentPos;
		}
		if( symbol == CARRIAGE_RETURN || symbol == NUL )
		{
				CAipi_Error err;
				err.displayGUIError(LEXICAL, LEX_ERROR, _T("Close identifier symbol is missed") );
				return LEX_ERROR;
		}
		
			
		pos2 = g_currentPos;
		tstring tk = getTextRange(pos1, pos2);
		tk = formatTkNameOpt(tk);
	
		++g_currentId_IForm;
		CAipi_Symbol symb;
		symb.addId_IntForm(tk, g_currentId_IForm);
		int repIdForm = symb.findId_IntForm(tk);
		if( repIdForm != NOT_FOUND )
		{
			tokz.v_addToken(pos1, pos2, g_currentLine, repIdForm, tk, IDENTIFIER);	
		}
		else
		{
			tokz.v_addToken(pos1, pos2, g_currentLine, g_currentId_IForm, tk, IDENTIFIER);	
			
		}

		symbol = rCtrl.GetCharAt(g_currentPos);
		if( symbol != SPACE )
		{
			--g_currentPos;
		}
		//AfxMessageBox(_T("ID"));
		return IDENTIFIER;

		
	}




	//Identifiers and KeyWords
	if( isAlphabetic(symbol) || symbol == UNDERSCORE )
	{
		//AfxMessageBox(_T("IDENTIFIERS y KEYWORDS"));

		pos1 = g_currentPos;
		
		while( isAlphaNumeric(symbol) )
		{
			++g_currentPos;
			//str.Format(_T("Pos en Identifier...%d  " ), g_currentPos);
			//AfxMessageBox(str);

			symbol = rCtrl.GetCharAt(g_currentPos);
			//str.Format(_T("Id Symbol...%d  " ), symbol);
			//AfxMessageBox(str);
			if( symbol == NUL )
			{
				CAipi_Error err;
				err.displayGUIError(LEXICAL, LEX_ERROR, _T("Another symbol was expected after character.") );
				return LEX_ERROR;
			}
			
		}
		
		
		
		pos2 = g_currentPos;
		symbol = rCtrl.GetCharAt(g_currentPos);
		if( symbol != SPACE )
		{
			--g_currentPos;
		}
		
		tk = getTextRange(pos1, pos2);
		
		//AfxMessageBox(_T("tk:"));
		//AfxMessageBox(tk.data());
		
		if( tk == _T("STOP_ERROR") )
		{
			return STOP_ERROR;
		}
		CAipi_Symbol symb;
		int keyWord = symb.findKeyWord(tk);
		
		if( keyWord != NOT_FOUND )
		{
			//AfxMessageBox(_T("Found KeyWord"));
			//tokz.addToken(pos1, pos2, g_currentLine, keyWord, tk, KEYWORD);
			tokz.v_addToken(pos1, pos2, g_currentLine, keyWord, tk, keyWord);
			return keyWord;
		}
		else
		{
			++g_currentId_IForm;
			symb.addId_IntForm(tk, g_currentId_IForm);
			int repIdForm = symb.findId_IntForm(tk);
			if( repIdForm != NOT_FOUND )
			{
				tokz.v_addToken(pos1, pos2, g_currentLine, repIdForm, tk, IDENTIFIER);	
			}
			else
			{
				
				tokz.v_addToken(pos1, pos2, g_currentLine, g_currentId_IForm, tk, IDENTIFIER);
			}

			//str.Format(_T("Char Last Pos...%d  " ), pos2);
			//AfxMessageBox(str);
			

			return IDENTIFIER;
		}

		
	}

		
	if (symbol == NUL )
	{
		//AfxMessageBox(_T("Fin del archivo"));
		return NUL;
		
	}

		
return UNDEFINE;
}

///////////////////////////////////////////////////////////////////////////////
//// End addTokenizerGUI ///
//////////////////////////////////////////////////////////////////////////////






///////////////////////////////////////////////////////////////////////
//// Begin addTokenizerFileExp ///
//This lexer is just for the expression parser 
////////////////////////////////////////////////////////////////////// 

int CAipi_Lexer::addTokenizerFileExp(TCHAR symbol)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CAipi_Tokenizer  tokz;
	
	CString str;
	//TCHAR buffer[MAX_TK_LEN];
	//fpos_t tempPos = 0;
	//static long g_currentId_IForm = 1000;


	g_fcurrentPos = ftell(g_fp);

	fpos_t pos1 = 0;
	fpos_t pos2 = 0;
	tstring tk = _T("");

	//Skip over white space and newline
	while( symbol == SPACE || symbol == CARRIAGE_RETURN || symbol == NEW_LINE || symbol == HORIZONTAL_TAB || symbol == VERTICAL_TAB )
	{
		if( symbol == _TEOF )
		{
			return _TEOF;
		}
		
		if( symbol == NEW_LINE )
		{
			++g_currentLine;
		}
		
		g_fcurrentPos = ftell(g_fp);
		
		/*
		str.Format(_T("Space Pos...%d  " ), g_fcurrentPos);
		AfxMessageBox(str);
		wsprintf(buffer, _T("Space Letra: %c"), symbol);
		AfxMessageBox(buffer);
		wsprintf(buffer, _T("Space ASCII: %d"), symbol);
		AfxMessageBox(buffer);
		*/

		symbol =  _gettc(g_fp);
		
	}

	//Comments
	if( symbol == SLASH )
	{	
		//AfxMessageBox(_T("identifico slash 1"));
		g_fcurrentPos = ftell(g_fp);
		pos1 = g_fcurrentPos - 1;
		//str.Format(_T("Pos del primer SLASH...%d  " ), g_fcurrentPos);
		//AfxMessageBox(str);
		
		
		symbol = _gettc(g_fp);
		g_fcurrentPos = ftell(g_fp);
			
					
		//Simple comment
		if( symbol == SLASH )
		{
			
			//str.Format(_T("Pos del segundo SLASH...%d  " ), g_fcurrentPos);
			//AfxMessageBox(str);		
		
		/*
			wsprintf(buffer, _T("Simple Comment Letra: %c"), symbol);
			AfxMessageBox(buffer);
			wsprintf(buffer, _T("Simple Comment ASCII: %d"), symbol);
			AfxMessageBox(buffer);
			AfxMessageBox(_T("identifico slash 2"));
			*/
			/*
			symbol =  _gettc(g_fp);
			g_fcurrentPos = ftell(g_fp);
			str.Format(_T("Pos antes de entrar al while...%d  " ), g_fcurrentPos);
			AfxMessageBox(str);
			wsprintf(buffer, _T("Simple Comment Txt Letra: %c"), symbol);
			AfxMessageBox(buffer);
			wsprintf(buffer, _T("Simple Comment Txt ASCII: %d"), symbol);
			AfxMessageBox(buffer);
		*/
				
			while ( symbol != CARRIAGE_RETURN && symbol != NEW_LINE  && symbol != _TEOF)
			{
									
				symbol =  _gettc(g_fp);	
				//g_fcurrentPos = ftell(g_fp);
				
				/*
				
				str.Format(_T("Cifclo While Pos...%d  " ), g_fcurrentPos);
				AfxMessageBox(str);
				AfxMessageBox(_T("texto comentario"));
				wsprintf(buffer, _T("Simple Comment Txt Letra: %c"), symbol);
				AfxMessageBox(buffer);
				wsprintf(buffer, _T("Simple Comment Txt ASCII: %d"), symbol);
				AfxMessageBox(buffer);
				*/

			}
				
			//AfxMessageBox(_T("Salio del while"));
			g_fcurrentPos = ftell(g_fp);
			pos2 = g_fcurrentPos - 2;
			
		
			//str.Format(_T("Commentario Pos...%d  " ), g_fcurrentPos);
			//AfxMessageBox(str);
		
			tk = getTextFileRange(pos1, pos2);
			
			if( tk == _T("STOP_ERROR") )
			{
				return STOP_ERROR;
			}

			fsetpos(g_fp, &pos2);
			
			//AfxMessageBox(tk.data());
			
			//tokz.addToken(pos1, pos2, g_currentLine, SIMPLE_COMMENT, tk, COMMENT);
			tokz.v_addToken(pos1, pos2, g_currentLine, SIMPLE_COMMENT, tk, COMMENT);
			return COMMENT;

				
		}
		//Complex comment
		else if( symbol == ASTERIC )
		{
			g_fcurrentPos = ftell(g_fp);
			pos1 = g_fcurrentPos - 2;
			symbol =  _gettc(g_fp);
			
			/*
			AfxMessageBox(_T("identifico ASTERISCO 1"));
			wsprintf(buffer, _T("Asterisco1 Comment Letra: %c"), symbol);
			AfxMessageBox(buffer);
			wsprintf(buffer, _T("Asterisco1 Comment ASCII: %d"), symbol);
			AfxMessageBox(buffer);
			str.Format(_T("Pos Asterisco1...%d  " ), g_fcurrentPos);
			AfxMessageBox(str);
			*/
				

			do//find end comment
			{
				while ( symbol != ASTERIC && symbol != _TEOF )
				{
					//if( symbol == NEW_LINE )
					//++g_currentLine;

				/*
				wsprintf(buffer, _T("Asteric Comment Letra: %c"), symbol);
				AfxMessageBox(buffer);
				wsprintf(buffer, _T("Asteric Comment ASCII: %d"), symbol);
				AfxMessageBox(buffer);
				AfxMessageBox(_T("Texto Comentario Asterisco"));
				str.Format(_T("While Asterisco Pos...%d  " ), g_fcurrentPos);
				AfxMessageBox(str);
				*/
				symbol =  _gettc(g_fp);
									
				}
				
				symbol =  _gettc(g_fp);
				
				if( symbol == _TEOF )
				{
					CAipi_Error err;
					err.displayFileError(LEXICAL, LEX_ERROR, _T("Close comment is missed") );
					return LEX_ERROR;
				}
				

			}while( symbol != SLASH );
			
			
			//AfxMessageBox(_T("Salio del do while"));
			g_fcurrentPos = ftell(g_fp);
			/*
			AfxMessageBox(_T("pos2 Complex Comment"));
			str.Format(_T("Pos2...%d  " ), g_fcurrentPos);
			AfxMessageBox(str);
			*/
			pos2 = g_fcurrentPos -2;
			tk = getTextFileRange(pos1, pos2);
			
			if( tk == _T("STOP_ERROR") )
			{
				return STOP_ERROR;
			}
			
			fsetpos(g_fp, &pos2);

			//AfxMessageBox(tk.data());
			
			
			//tokz.addToken(pos1, pos2, g_currentLine, COMPLEX_COMMENT, tk, COMMENT);
			tokz.v_addToken(pos1, pos2, g_currentLine, COMPLEX_COMMENT, tk, COMMENT);
			
			return COMMENT;
			
		}
		else
		{
			fsetpos(g_fp, &pos1);
			symbol = _gettc(g_fp);
			g_fcurrentPos = ftell(g_fp);

			/*
			AfxMessageBox(_T("Estoy en Comment ELSE"));
			str.Format(_T("Space Pos1...%d  " ), g_fcurrentPos);
			AfxMessageBox(str);
			
			wsprintf(buffer, _T("Space Letra: %c"), symbol);
			AfxMessageBox(buffer);
			wsprintf(buffer, _T("Space ASCII: %d"), symbol);
			AfxMessageBox(buffer);
		*/
			
		}
			
	}


	//Check for operators
	if( isOperator(symbol) )
	{
		/*
		wsprintf(buffer, _T("Switch1 Operator Letra: %c"), symbol);
		AfxMessageBox(buffer);
		wsprintf(buffer, _T("Switch1 ASCII: %d"), symbol);
		AfxMessageBox(buffer);
		str.Format(_T("Switch1 Pos...%d  " ), g_fcurrentPos);
		AfxMessageBox(str);
	*/
		switch( symbol )
		{
			
			case EQUAL:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				
				if( symbol == EQUAL )
				{
					/*
					AfxMessageBox(_T("entro =="));
					str.Format(_T("Pos...%d  " ), g_fcurrentPos);
					AfxMessageBox(str);
					*/
					tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
					//tokz.addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, ET, tk, OPERATOR);
					tokz.v_addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, ET, tk, ET);
					//fsetpos(g_fp, &g_fcurrentPos + 1);
					return EQUAL;
					
				}
				else
				{
					/*
					AfxMessageBox(_T("entro ="));
					str.Format(_T("Pos...%d  " ), g_fcurrentPos);
					AfxMessageBox(str);
					*/
					tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos);
					//tokz.addToken(g_fcurrentPos-1, g_fcurrentPos, g_currentLine, AS, tk, OPERATOR);
					tokz.v_addToken(g_fcurrentPos-1, g_fcurrentPos, g_currentLine, AS, tk, AS);
					//fsetpos(g_fp, &g_fcurrentPos );
					return AS;
				}
				
			case EXCLAMATION:
				
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
			
				if( symbol == EQUAL )
				{
					/*
					AfxMessageBox(_T("entro !="));
					str.Format(_T("Pos...%d  " ), g_fcurrentPos);
					AfxMessageBox(str);
					*/

					tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
					//tokz.addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, NE, tk, OPERATOR);
					tokz.v_addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, NE, tk, NE);
					//fsetpos(g_fp, &g_fcurrentPos + 1);
					return NE;
				}
				else
				{
					/*
					AfxMessageBox(_T("entro !"));
					str.Format(_T("Pos...%d  " ), g_fcurrentPos);
					AfxMessageBox(str);
					*/

					tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos);
					//tokz.addToken(g_fcurrentPos -1, g_fcurrentPos, g_currentLine, NOT_OP, tk, OPERATOR);
					tokz.v_addToken(g_fcurrentPos -1, g_fcurrentPos, g_currentLine, NOT_OP, tk, NOT_OP);
					//fsetpos(g_fp, &g_fcurrentPos);
					return NOT_OP;
				}
				

			case AMPERSAND:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
					
				if( symbol == AMPERSAND )
				{
					/*
					AfxMessageBox(_T("entro &&"));
					str.Format(_T("Pos...%d  " ), g_fcurrentPos);
					AfxMessageBox(str);
					*/

					tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
					//tokz.addToken(g_fcurrentPos -1, g_fcurrentPos + 1, g_currentLine, AND_OP, tk, OPERATOR);
					tokz.v_addToken(g_fcurrentPos -1, g_fcurrentPos + 1, g_currentLine, AND_OP, tk, AND_OP);
					return AND_OP;	
				}
				else
				{
					/*
					AfxMessageBox(_T("entro &"));
					str.Format(_T("Pos...%d  " ), g_fcurrentPos);
					AfxMessageBox(str);
					*/

					tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
					//tokz.addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, AND_BIT, tk, OPERATOR);
					tokz.v_addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, AND_BIT, tk, AND_BIT);
					return AND_BIT;
				}
				

		case VERTICAL_BAR:
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
				
			if( symbol == VERTICAL_BAR )
			{
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				//tokz.addToken(g_fcurrentPos -1, g_fcurrentPos + 1, g_currentLine, OR_OP, tk, OPERATOR);
				tokz.v_addToken(g_fcurrentPos -1, g_fcurrentPos + 1, g_currentLine, OR_OP, tk, OR_OP);
				return OR_OP;
			}
			else
			{
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				//tokz.addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, OR_BIT, tk, OPERATOR);
				tokz.v_addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, OR_BIT, tk, OR_BIT);
				return OR_BIT;
			}
			

		case LESS_THAN:
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			
			if( symbol == EQUAL )
			{
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				//tokz.addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, LE, tk, OPERATOR);
				tokz.v_addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, LE, tk, LE);
				return LE;
				
			}
			else if ( symbol == LESS_THAN )
			{
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				//tokz.addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, RIGHT_OP, tk, OPERATOR);
				tokz.v_addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, RIGHT_OP, tk, RIGHT_OP);
				return RIGHT_OP;
			}
			else
			{
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				//tokz.addToken(g_fcurrentPos -1 , g_fcurrentPos, g_currentLine, LT, tk, OPERATOR);
				tokz.v_addToken(g_fcurrentPos -1 , g_fcurrentPos, g_currentLine, LT, tk, LT);
				return LT;
			}
			

		case GREATER_THAN:
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
						
			if( symbol == EQUAL )
			{
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				//tokz.addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, GE, tk, OPERATOR);
				tokz.v_addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, GE, tk, GE);
				return GE;	
			}
			else if ( symbol == GREATER_THAN )
			{
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				//tokz.addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, LEFT_OP, tk, OPERATOR);
				tokz.v_addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, LEFT_OP, tk, LEFT_OP);
				return LEFT_OP;
			}
			else
			{
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				//tokz.addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, GT, tk, OPERATOR);
				tokz.v_addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, GT, tk, GT);
				return GT;
			}
			break;

		case PLUS_SIGN:
			
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			
			if( symbol == EQUAL )
			{
				//str.Format(_T("Symbol...%d  " ), symbol);
				//AfxMessageBox(str);
				
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				//tokz.addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, ADD_ASSIGN, tk, OPERATOR);
				tokz.v_addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, ADD_ASSIGN, tk, ADD_ASSIGN);
				return ADD_ASSIGN;
			}
			else if ( symbol == PLUS_SIGN )
			{
				//str.Format(_T("Symbol...%d  " ), symbol);
				//AfxMessageBox(str);
				
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				//tokz.addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, INC_OP, tk, OPERATOR);
				tokz.v_addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, INC_OP, tk, INC_OP);
				return INC_OP;
			}
			else
			{
				
				//str.Format(_T("Symbol Sum...%d  " ), symbol);
				//AfxMessageBox(str);
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				//tokz.addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, PLUS_SIGN, tk, OPERATOR);
				tokz.v_addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, PLUS_SIGN, tk, PLUS_SIGN);
				return PLUS_SIGN;
			}
			break;
		case MINUS_SIGN:
			
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			
			if( symbol == EQUAL )
			{
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				//tokz.addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, SUB_ASSIGN, tk, OPERATOR);
				tokz.v_addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, SUB_ASSIGN, tk, SUB_ASSIGN);
				return SUB_ASSIGN;
			}
			else if ( symbol == MINUS_SIGN )
			{
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				//tokz.addToken(g_fcurrentPos -1, g_fcurrentPos + 1, g_currentLine, DEC_OP, tk, OPERATOR);
				tokz.v_addToken(g_fcurrentPos -1, g_fcurrentPos + 1, g_currentLine, DEC_OP, tk, DEC_OP);
				return DEC_OP;
			}
			else if ( symbol == GT )
			{
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				//tokz.addToken(g_fcurrentPos -1, g_fcurrentPos + 1, g_currentLine, PTR_OP, tk, OPERATOR);
				tokz.v_addToken(g_fcurrentPos -1, g_fcurrentPos + 1, g_currentLine, PTR_OP, tk, PTR_OP);
				return PTR_OP;
			}
			else
			{
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				//tokz.addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, MINUS_SIGN, tk, OPERATOR);
				tokz.v_addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, MINUS_SIGN, tk, MINUS_SIGN);
				return MINUS_SIGN;
			}
		case ASTERIC:
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			
			if( symbol == EQUAL )
			{
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				//tokz.addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, MUL_ASSIGN, tk, OPERATOR);
				tokz.v_addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, MUL_ASSIGN, tk, MUL_ASSIGN);
				return MUL_ASSIGN;
			}
			else
			{
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				//tokz.addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, ASTERIC, tk, OPERATOR);
				tokz.v_addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, ASTERIC, tk, ASTERIC);
				return ASTERIC;
			}
			
		case SLASH:
			//str.Format(_T("Entro Slash Symbol...%d  " ), symbol);
			//AfxMessageBox(str);
			
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			
			if( symbol == EQUAL )
			{
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				//tokz.addToken(g_fcurrentPos -1, g_fcurrentPos + 1, g_currentLine, DIV_ASSIGN, tk, OPERATOR);
				tokz.v_addToken(g_fcurrentPos -1, g_fcurrentPos + 1, g_currentLine, DIV_ASSIGN, tk, DIV_ASSIGN);
				return DIV_ASSIGN;
			}
			else
			{
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				//tokz.addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, SLASH, tk, OPERATOR);
				tokz.v_addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, SLASH, tk, SLASH);
				return SLASH;
			}
			
		case PERCENT:
			
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			
			if( symbol == EQUAL )
			{
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				//tokz.addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, MOD_ASSIGN, tk, OPERATOR);
				tokz.v_addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, MOD_ASSIGN, tk, MOD_ASSIGN);
				return MOD_ASSIGN;
			}
			else
			{
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				//tokz.addToken(g_fcurrentPos, g_fcurrentPos, g_currentLine, PERCENT, tk, OPERATOR);
				tokz.v_addToken(g_fcurrentPos, g_fcurrentPos, g_currentLine, PERCENT, tk, PERCENT);
				return PERCENT;
			}
			
		
		case COLON:
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
				
			if( symbol == COLON )
			{
				/*
				AfxMessageBox(_T("entro =="));
				str.Format(_T("Pos...%d  " ), g_fcurrentPos);
				AfxMessageBox(str);
				*/
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				//tokz.addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, SCOPE_OP, tk, OPERATOR);
				tokz.v_addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, SCOPE_OP, tk, SCOPE_OP);
				return SCOPE_OP;
			}
			else
			{
				/*
				AfxMessageBox(_T("entro ="));
				str.Format(_T("Pos...%d  " ), g_fcurrentPos);
				AfxMessageBox(str);
				*/
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos);
				//tokz.addToken(g_fcurrentPos-1, g_fcurrentPos, g_currentLine, COLON, tk, OPERATOR);
				tokz.v_addToken(g_fcurrentPos-1, g_fcurrentPos, g_currentLine, COLON, tk, COLON);
				return COLON;
			}
			
			
		case CARET:
			
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			
			tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
			//tokz.addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, XOR_BIT, tk, OPERATOR);
			tokz.v_addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, XOR_BIT, tk, XOR_BIT);
			return XOR_BIT;

		case EQUIVALENCY:
			
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			
			tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
			//tokz.addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, NOT_BIT, tk, OPERATOR);
			tokz.v_addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, NOT_BIT, tk, NOT_BIT);
			return NOT_BIT;

		case QUESTION:
			
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			
			tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
			//tokz.addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, QUESTION, tk, OPERATOR);
			tokz.v_addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, QUESTION, tk, QUESTION);
			return QUESTION;
			
		}
		
		
		
	}

//Check for punctuators
	if( isPunctuator(symbol) )
	{
		
		switch( symbol )
		{
					
			case SEMICOLON:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
			
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				//tokz.addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, SEMICOLON, tk, PUNCTUATOR);
				tokz.v_addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, SEMICOLON, tk, SEMICOLON);
				return SEMICOLON;
			case OPEN_PARENTHESIS:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
			
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				//tokz.addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, OPEN_PARENTHESIS, tk, PUNCTUATOR);
				tokz.v_addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, OPEN_PARENTHESIS, tk, OPEN_PARENTHESIS);
				return OPEN_PARENTHESIS;
			case CLOSE_PARENTHESIS:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
			
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				//tokz.addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, CLOSE_PARENTHESIS, tk, PUNCTUATOR);
				tokz.v_addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, CLOSE_PARENTHESIS, tk, CLOSE_PARENTHESIS);
				return CLOSE_PARENTHESIS;
			case OPEN_BRACKET:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
							
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				//tokz.addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, OPEN_BRACKET, tk, PUNCTUATOR);
				tokz.v_addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, OPEN_BRACKET, tk, OPEN_BRACKET);
				return OPEN_BRACKET;
			case CLOSE_BRACKET:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
							
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				//tokz.addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, CLOSE_BRACKET, tk, PUNCTUATOR);
				tokz.v_addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, CLOSE_BRACKET, tk, CLOSE_BRACKET);
				return CLOSE_BRACKET;
			case OPEN_BRACE:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
			
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos);
				//tokz.addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, OPEN_BRACE, tk, PUNCTUATOR);
				tokz.v_addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, OPEN_BRACE, tk, OPEN_BRACE);
				return OPEN_BRACE;
			case CLOSE_BRACE:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
			
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				//tokz.addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, CLOSE_BRACE, tk, PUNCTUATOR);
				tokz.v_addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, CLOSE_BRACE, tk, CLOSE_BRACE);
				return CLOSE_BRACKET;
			case COMMA:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
			
				
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				//tokz.addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, COMMA, tk, PUNCTUATOR);
				tokz.v_addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, COMMA, tk, COMMA);
				return COMMA;
			case COLON:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
			
				
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos);
				//tokz.addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, COLON, tk, PUNCTUATOR);
				tokz.v_addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, COLON, tk, COLON);
				return COLON;
			case PERIOD:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
							
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				//tokz.addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, PERIOD, tk, PUNCTUATOR);
				tokz.v_addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, PERIOD, tk, PERIOD);
				return PERIOD;
			case NUMBER_SIGN:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
			
				
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				//tokz.addToken(g_fcurrentPos -1, g_fcurrentPos, g_currentLine, NUMBER_SIGN, tk, PUNCTUATOR);
				tokz.v_addToken(g_fcurrentPos -1, g_fcurrentPos, g_currentLine, NUMBER_SIGN, tk, NUMBER_SIGN);
				return NUMBER_SIGN;
			case AT_SYMBOL:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
			
				
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				//tokz.addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, AT_SYMBOL, tk, PUNCTUATOR);
				tokz.v_addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, AT_SYMBOL, tk, AT_SYMBOL);
				return AT_SYMBOL;
		
		}
		
	}


	//Double Quoted Strings
	if( symbol == DOBLE_QUOTATION )
	{
		//AfxMessageBox(_T("entro a string"));
		g_fcurrentPos = ftell(g_fp);
		pos1 = g_fcurrentPos - 1;
		
		//str.Format(_T("Pos del primer SLASH...%d  " ), g_fcurrentPos);
		//AfxMessageBox(str);
				
		symbol = _gettc(g_fp);
		
			/*
			str.Format(_T("symbol%d  " ), symbol);	
			pMainFrame->m_wndOutputTabView.AddMsg1(str);
			wsprintf(buffer, _T("Letra: %c"), symbol);
			AfxMessageBox(buffer);
			wsprintf(buffer, _T("ASCII: %d"), symbol);
			AfxMessageBox(buffer);
			*/
		
				
		while(symbol != DOBLE_QUOTATION && symbol != CARRIAGE_RETURN && symbol != _TEOF )
		{
			//symbol =  _gettc(g_fp);
			//str.Format(_T("While Symbol...%d  " ), symbol);
			//AfxMessageBox(str);
			/*
			if( symbol == DOBLE_QUOTATION )
			{
				CAipi_Error err;
				err.displayFileError(SYNTAX, LEX_ERROR, _T("Error"));
				return LEX_ERROR;
			}
			*/
			
			//Check for \n escape sequence
			if( symbol == BACK_SLASH )
			{
				//AfxMessageBox(_T("entro a slash"));
				
				fpos_t tempPos = ftell(g_fp);
				TCHAR escSymbol =  _gettc(g_fp);


				switch (escSymbol) 
				{
					//  Escape /a  alert
					case 97:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, ALERT, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, ALERT, tk, ALERT);
						break;
					
					//  Escape /b backspace
					case 98:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, BACKSPACE, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, BACKSPACE, tk, BACKSPACE);
						break;
					//  Escape /f forward feed page
					case 102:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, FORWARD_FEED, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, FORWARD_FEED, tk, FORWARD_FEED);
						break;
					//  Escape /n  new line	
					case 110:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, NEW_LINE, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, NEW_LINE, tk, NEW_LINE);
						break;
					//  Escape /r  carriage return
					case 114:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, CARRIAGE_RETURN, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, CARRIAGE_RETURN, tk, CARRIAGE_RETURN);
						break;
					//  Escape /t  horizontal tab
					case 116:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, HORIZONTAL_TAB, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, HORIZONTAL_TAB, tk, HORIZONTAL_TAB);
						break;
					//  Escape /v  vertical tab
					case 118:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, VERTICAL_TAB, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, VERTICAL_TAB, tk, VERTICAL_TAB);
						break;
					//  Symbol /'  single quotes
					case 27:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, SINGLE_QUOTATION, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, SINGLE_QUOTATION, tk, SINGLE_QUOTATION);
						break;
					
					//  Symbol /"  double quotes
					case 34:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, DOBLE_QUOTATION, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, DOBLE_QUOTATION, tk, DOBLE_QUOTATION);
						break;
					
						//  Symbol //  back slash
					case 92:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, BACK_SLASH, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, BACK_SLASH, tk, BACK_SLASH);
						break;
					
					//AfxMessageBox(_T("reconocio escape"));
				}//end switch

				if( escSymbol != 34 )
				{
					symbol = escSymbol;
				}

				
				
			
			}//end if

			symbol =  _gettc(g_fp);
			
		}//end while

		if( symbol == CARRIAGE_RETURN || symbol == _TEOF )
		{
				CAipi_Error err;
				err.displayFileError(LEXICAL, LEX_ERROR, _T("Close string symbol is missed") );
				return LEX_ERROR;
		}
		
			
		pos2 = ftell(g_fp);
		
		tk = getTextFileRange(pos1, pos2);
		if( tk == _T("STOP_ERROR") )
		{
			return STOP_ERROR;
		}
		
		++g_currentId_IForm;
		CAipi_Symbol symb;
		symb.addId_IntForm(tk, g_currentId_IForm);
		int repIdForm = symb.findId_IntForm(tk);
		if( repIdForm != NOT_FOUND )
		{
			tokz.v_addToken(pos1, pos2, g_currentLine, repIdForm, tk, LITERAL);	
		}		
		else
		{
			tokz.v_addToken(pos1, pos2, g_currentLine, g_currentId_IForm, tk, LITERAL);
		}
		
		//AfxMessageBox(_T("agrego string final"));		
		
		return LITERAL;

		
	}


	//Single Quoted Strings
	if( symbol == SINGLE_QUOTATION )
	{
		//AfxMessageBox(_T("entro a string"));
		g_fcurrentPos = ftell(g_fp);
		pos1 = g_fcurrentPos - 1;
		
		//str.Format(_T("Pos del primer SLASH...%d  " ), g_fcurrentPos);
		//AfxMessageBox(str);
				
		symbol = _gettc(g_fp);
		
			/*
			str.Format(_T("symbol%d  " ), symbol);	
			pMainFrame->m_wndOutputTabView.AddMsg1(str);
			wsprintf(buffer, _T("Letra: %c"), symbol);
			AfxMessageBox(buffer);
			wsprintf(buffer, _T("ASCII: %d"), symbol);
			AfxMessageBox(buffer);
			*/
		
				
		while(symbol != SINGLE_QUOTATION && symbol != CARRIAGE_RETURN && symbol != _TEOF )
		{
			//symbol =  _gettc(g_fp);
			//str.Format(_T("While Symbol...%d  " ), symbol);
			//AfxMessageBox(str);
			/*
			if( symbol == DOBLE_QUOTATION )
			{
				CAipi_Error err;
				err.displayFileError(SYNTAX, LEX_ERROR, _T("Error"));
				return LEX_ERROR;
			}
			*/
			
			//Check for \n escape sequence
			if( symbol == BACK_SLASH )
			{
				//AfxMessageBox(_T("entro a slash"));
				
				fpos_t tempPos = ftell(g_fp);
				TCHAR escSymbol =  _gettc(g_fp);


				switch (escSymbol) 
				{
					//  Escape /a  alert
					case 97:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, ALERT, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, ALERT, tk, LITERAL);
						break;
					
					//  Escape /b backspace
					case 98:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, BACKSPACE, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, BACKSPACE, tk, LITERAL);
						break;
					//  Escape /f forward feed page
					case 102:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, FORWARD_FEED, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, FORWARD_FEED, tk, LITERAL);
						break;
					//  Escape /n  new line	
					case 110:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, NEW_LINE, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, NEW_LINE, tk, LITERAL);
						break;
					//  Escape /r  carriage return
					case 114:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, CARRIAGE_RETURN, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, CARRIAGE_RETURN, tk, LITERAL);
						break;
					//  Escape /t  horizontal tab
					case 116:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, HORIZONTAL_TAB, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, HORIZONTAL_TAB, tk, LITERAL);
						break;
					//  Escape /v  vertical tab
					case 118:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, VERTICAL_TAB, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, VERTICAL_TAB, tk, LITERAL);
						break;
					//  Symbol /'  single quotes
					case 27:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, SINGLE_QUOTATION, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, SINGLE_QUOTATION, tk, LITERAL);
						break;
					
					//  Symbol /"  double quotes
					case 34:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, DOBLE_QUOTATION, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, DOBLE_QUOTATION, tk, LITERAL);
						break;
					
						//  Symbol //  back slash
					case 92:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, BACK_SLASH, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, BACK_SLASH, tk, LITERAL);
						break;
					
					//AfxMessageBox(_T("reconocio escape"));
				}//end switch

				if( escSymbol != 34 )
				{
					symbol = escSymbol;
				}

				
				
			
			}//end if

			symbol =  _gettc(g_fp);
			
		}//end while

		if( symbol == CARRIAGE_RETURN || symbol == _TEOF )
		{
				CAipi_Error err;
				err.displayFileError(LEXICAL, LEX_ERROR, _T("Close string symbol is missed") );
				return AIPI_ERROR;
		}
		
			
		pos2 = ftell(g_fp);
		
		
		
		
		tk = getTextFileRange(pos1, pos2);
		
		++g_currentId_IForm;
		CAipi_Symbol symb;
		symb.addId_IntForm(tk, g_currentId_IForm);
		int repIdForm = symb.findId_IntForm(tk);
		if( repIdForm != NOT_FOUND )
		{
			tokz.v_addToken(pos1, pos2, g_currentLine, repIdForm, tk, LITERAL);	
		}
		else
		{
			tokz.v_addToken(pos1, pos2, g_currentLine, g_currentId_IForm, tk, LITERAL);
		}
		
		//AfxMessageBox(_T("agrego string final"));		
		
		return LITERAL;

		
	}

		//Numbers (Natural and Real )
	if( isDigit(symbol)  )
	{
		//AfxMessageBox(_T("entro a digit"));

		g_fcurrentPos = ftell(g_fp);
		pos1 = g_fcurrentPos - 1;		
		
		g_currentDigit_Type = NAT_NUMBER;
		int countPeriod = 0;
		
		while( isDigit(symbol) || symbol == PERIOD && symbol != _TEOF )
		{
			
			//str.Format(_T("Pos en Nat Number...%d  " ), g_fcurrentPos);
			//AfxMessageBox(str);
			//wsprintf(buffer, _T("Number: %c"), symbol);
			//AfxMessageBox(buffer);
			//wsprintf(buffer, _T("ASCII: %d"), symbol);
			//AfxMessageBox(buffer);
			
			

			if( symbol == PERIOD )
			{
				g_currentDigit_Type = REAL_NUMBER;
				++countPeriod;
			}

			symbol = _gettc(g_fp);
			//str.Format(_T("Pos en Nat Number...%d  " ), g_fcurrentPos);
			//AfxMessageBox(str);
			//wsprintf(buffer, _T("After Number: %c"), symbol);
			//AfxMessageBox(buffer);
			//wsprintf(buffer, _T("ASCII: %d"), symbol);
			//AfxMessageBox(buffer);
			
			
		}

		if( countPeriod > 1 )
		{
			CAipi_Error err;
			err.displayFileError(LEXICAL, LEX_ERROR, _T("Period symbol is repeated")  );
			return LEX_ERROR;
		}
		
		g_fcurrentPos = ftell(g_fp);
		pos2 = --g_fcurrentPos;
		
		if( symbol == NEW_LINE )
		{
			pos2 = --g_fcurrentPos;
			++g_currentLine;
			//AfxMessageBox(_T("Detecto new line"));
		}
		if( symbol == _TEOF )
		{
			//AfxMessageBox(_T("_TEOF"));
			pos2 = ++g_fcurrentPos;
			fsetpos(g_fp, &g_fcurrentPos );
		}

		tk = getTextFileRange(pos1, pos2);
		if( tk == _T("STOP_ERROR") )
		{
			return STOP_ERROR;
		}
		
		double g_currentId_IForm = _tcstod(tk.data(), NULL);
		tokz.v_addToken(pos1, pos2, g_currentLine, g_currentId_IForm, tk, DIGIT);
		
		return DIGIT;
	}


		//Identifiers and KeyWords
	if( isAlphabetic(symbol) || symbol == UNDERSCORE )
	{
		g_fcurrentPos = ftell(g_fp);
		pos1 = g_fcurrentPos - 1;		
		
		while( isAlphaNumeric(symbol) && symbol != _TEOF )
		{
			symbol = _gettc(g_fp);
			//str.Format(_T("Pos en Identifier...%d  " ), g_fcurrentPos);
			//AfxMessageBox(str);

			//str.Format(_T("Id Symbol...%d  " ), symbol);
			//AfxMessageBox(str);
			
			
		}
		
		
		g_fcurrentPos = ftell(g_fp);
		pos2 = --g_fcurrentPos;

		if( symbol == NEW_LINE )
		{
			pos2 = --g_fcurrentPos;
			//++g_currentLine;
			//AfxMessageBox(_T("Detecto new line"));
		}
		if( symbol == _TEOF )
		{
			//AfxMessageBox(_T("_TEOF"));
			pos2 = ++g_fcurrentPos;
			fsetpos(g_fp, &g_fcurrentPos );
		}
	
		tk = getTextFileRange(pos1, pos2);
		if( tk == _T("STOP_ERROR") )
		{
			return STOP_ERROR;
		}

		CAipi_Symbol symb;
		int keyWord = symb.findKeyWord(tk);
		if( keyWord != NOT_FOUND )
		{
			//tokz.addToken(pos1, pos2, g_currentLine, kw, tk, KEYWORD);
			tokz.v_addToken(pos1, pos2, g_currentLine, keyWord, tk, keyWord);
			return keyWord;
		}
		else
		{
			
			++g_currentId_IForm;
			symb.addId_IntForm(tk, g_currentId_IForm);
			int repIdForm = symb.findId_IntForm(tk);
			if( repIdForm != NOT_FOUND )
			{
				tokz.v_addToken(pos1, pos2, g_currentLine, repIdForm, tk, IDENTIFIER);
			
			}
			else
			{
				tokz.v_addToken(pos1, pos2, g_currentLine, g_currentId_IForm, tk, IDENTIFIER);
			
			}

			//str.Format(_T("Char Last Pos...%d  " ), pos2);
			//AfxMessageBox(str);
			

			return IDENTIFIER;
		}

		
	}

			
	if (symbol == _TEOF )
	{
		//AfxMessageBox(_T("Fin del archivo"));
		return _TEOF;
		
	}


	/*
	str.Format(_T("symbol%d  " ), symbol);	
	pMainFrame->m_wndOutputTabView.AddMsg1(str);
	wsprintf(buffer, _T("Letra: %c"), symbol);
	AfxMessageBox(buffer);
	wsprintf(buffer, _T("ASCII: %d"), symbol);
	AfxMessageBox(buffer);
	
	*/
	
	fsetpos(g_fp, &g_fcurrentPos );

return UNDEFINE;

}
//////////////////////////////////////////////
//// End addTokenizerFileExp ////
////////////////////////////////////////////////








///////////////////////////////////////////////////////////////////////
//// Begin getTokenFileExp ///
//This lexer is just for the expression parser 
////////////////////////////////////////////////////////////////////// 
int CAipi_Lexer::getTokenFileExp(TCHAR symbol)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CAipi_Tokenizer  tokz;
	
	g_fcurrentPos = ftell(g_fp);

	fpos_t pos1 = 0;
	fpos_t pos2 = 0;
	tstring tk = _T("");

	//Skip over white space and newline
	while( symbol == SPACE || symbol == CARRIAGE_RETURN || symbol == NEW_LINE || symbol == HORIZONTAL_TAB || symbol == VERTICAL_TAB )
	{
		if( symbol == _TEOF )
		{
			return _TEOF;
		}
		
		if( symbol == NEW_LINE )
		{
			++g_currentLine;
		}
		
		g_fcurrentPos = ftell(g_fp);
		symbol =  _gettc(g_fp);
		
	}

	//Comments
	if( symbol == SLASH )
	{	
		g_fcurrentPos = ftell(g_fp);
		pos1 = g_fcurrentPos - 1;
		symbol = _gettc(g_fp);
		g_fcurrentPos = ftell(g_fp);
							
		//Simple comment
		if( symbol == SLASH )
		{
			while ( symbol != CARRIAGE_RETURN && symbol != NEW_LINE   && symbol != _TEOF)
			{
				symbol =  _gettc(g_fp);	
				
			}
				
			g_fcurrentPos = ftell(g_fp);
			pos2 = g_fcurrentPos - 2;
			tk = getTextFileRange(pos1, pos2);
			
			if( tk == _T("STOP_ERROR") )
			{
				return STOP_ERROR;
			}

			fsetpos(g_fp, &pos2);
			return COMMENT;
			
		}
		//Complex comment
		else if( symbol == ASTERIC )
		{
			g_fcurrentPos = ftell(g_fp);
			pos1 = g_fcurrentPos - 2;
			symbol =  _gettc(g_fp);
			do//find end comment
			{
				while ( symbol != ASTERIC && symbol != _TEOF )
				{
					if( symbol == NEW_LINE )
					{
						++g_currentLine;
					}

					symbol =  _gettc(g_fp);
				}
				
				symbol =  _gettc(g_fp);
				if( symbol == _TEOF )
				{
					CAipi_Error err;
					err.displayFileError(LEXICAL, LEX_ERROR, _T("Close comment is missed") );
					return LEX_ERROR;
				}
				
			}while( symbol != SLASH );
			
			g_fcurrentPos = ftell(g_fp);
			pos2 = g_fcurrentPos -2;
			fsetpos(g_fp, &pos2);
			return COMMENT;
			
		}
		else
		{
			fsetpos(g_fp, &pos1);
			symbol = _gettc(g_fp);
			g_fcurrentPos = ftell(g_fp);

		}
			
	}

	//Check for operators
	if( isOperator(symbol) )
	{
		
		switch( symbol )
		{
			case EQUAL:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				if( symbol == EQUAL )
				{
					return EQUAL;
				}
				else
				{
					return AS;
				}
				
			case EXCLAMATION:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				if( symbol == EQUAL )
				{
					return NE;	
				}
				else
				{
					return NOT_OP;
				}
			case AMPERSAND:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				if( symbol == AMPERSAND )
				{
					return AND_OP;
				}
				else
				{
					return AND_BIT;
				}
				

			case VERTICAL_BAR:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				if( symbol == VERTICAL_BAR )
				{
					return OR_OP;
				}
				else
				{
					return OR_BIT;
				}
				

			case LESS_THAN:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				if( symbol == EQUAL )
				{
					return LE;
				}
				else if ( symbol == LESS_THAN )
				{
					return RIGHT_OP;
				}
				else
				{
					return LT;
				}
				

			case GREATER_THAN:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				if( symbol == EQUAL )
				{
					return GE;
				}
				else if ( symbol == GREATER_THAN )
				{
					return LEFT_OP;
				}
				else
				{
					return GT;
				}
			

			case PLUS_SIGN:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				if( symbol == EQUAL )
				{
					return ADD_ASSIGN;
				}
				else if ( symbol == PLUS_SIGN )
				{
					return INC_OP;
				}
				else
				{
					return PLUS_SIGN;
				}
			
			case MINUS_SIGN:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				if( symbol == EQUAL )
				{
					return SUB_ASSIGN;
				}
				else if ( symbol == MINUS_SIGN )
				{
					return DEC_OP;
				}
				else if ( symbol == GT )
				{
					return PTR_OP;
				}
				else
				{
					return MINUS_SIGN;
				}
			
			case ASTERIC:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				if( symbol == EQUAL )
				{
					return MUL_ASSIGN;
				}
				else
				{
					return ASTERIC;
				}
			
			case SLASH:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				if( symbol == EQUAL )
				{
					return DIV_ASSIGN;
				}
				else
				{
					return SLASH;
				}
				
			case PERCENT:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				if( symbol == EQUAL )
				{
					return MOD_ASSIGN;
				}
				else
				{
					return PERCENT;
				}
			case COLON:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				if( symbol == COLON )
				{
					return SCOPE_OP;	
				}
				else
				{
					return COLON;
				}
						
			case CARET:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				return XOR_BIT;
			
			case EQUIVALENCY:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				return NOT_BIT;
			
			case QUESTION:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				return QUESTION;
				
			
		}
			
	}

//Check for punctuators
	if( isPunctuator(symbol) )
	{
		
		switch( symbol )
		{
					
			case SEMICOLON:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				return SEMICOLON;
			case OPEN_PARENTHESIS:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				return OPEN_PARENTHESIS;
			case CLOSE_PARENTHESIS:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				return CLOSE_PARENTHESIS;
			case OPEN_BRACKET:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				return OPEN_BRACKET;
			case CLOSE_BRACKET:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				return CLOSE_BRACKET;
			case OPEN_BRACE:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				return OPEN_BRACE;
			case CLOSE_BRACE:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				return CLOSE_BRACE;
			case COMMA:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				return COMMA;
			case COLON:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				return COLON;
			case PERIOD:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				return PERIOD;
			case NUMBER_SIGN:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				return NUMBER_SIGN;
			case AT_SYMBOL:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				return AT_SYMBOL;
		
		}
		
	}


	//Double Quoted Strings
	if( symbol == DOBLE_QUOTATION )
	{
		g_fcurrentPos = ftell(g_fp);
		pos1 = g_fcurrentPos - 1;
		symbol = _gettc(g_fp);
					
		while(symbol != DOBLE_QUOTATION && symbol != CARRIAGE_RETURN && symbol != _TEOF )
		{
			//Check for \n escape sequence
			if( symbol == BACK_SLASH )
			{
				fpos_t tempPos = ftell(g_fp);
				TCHAR escSymbol =  _gettc(g_fp);
				switch (escSymbol) 
				{
					//  Escape /a  alert
					case 97:
						break;
					
					//  Escape /b backspace
					case 98:
						break;
					//  Escape /f forward feed page
					case 102:
						break;
					//  Escape /n  new line	
					case 110:
						break;
					//  Escape /r  carriage return
					case 114:
						break;
					//  Escape /t  horizontal tab
					case 116:
						break;
					//  Escape /v  vertical tab
					case 118:
						break;
					//  Symbol /'  single quotes
					case 27:
						break;
					
					//  Symbol /"  double quotes
					case 34:
						break;
					
						//  Symbol //  back slash
					case 92:
						break;
					
					//AfxMessageBox(_T("reconocio escape"));
				}//end switch

				if( escSymbol != 34 )
				{
					symbol = escSymbol;
				}
			
			
			}//end if

			symbol =  _gettc(g_fp);
			
		}//end while

		if( symbol == CARRIAGE_RETURN || symbol == _TEOF )
		{
				CAipi_Error err;
				err.displayFileError(LEXICAL, LEX_ERROR, _T("Close string symbol is missed") );
				return LEX_ERROR;
		}
		
		pos2 = ftell(g_fp);
		return LITERAL;
	
	}


	//Single Quoted Strings
	if( symbol == SINGLE_QUOTATION )
	{
		g_fcurrentPos = ftell(g_fp);
		pos1 = g_fcurrentPos - 1;
		symbol = _gettc(g_fp);
				
		while(symbol != SINGLE_QUOTATION && symbol != CARRIAGE_RETURN && symbol != _TEOF )
		{
			//Check for \n escape sequence
			if( symbol == BACK_SLASH )
			{
				fpos_t tempPos = ftell(g_fp);
				TCHAR escSymbol =  _gettc(g_fp);

				switch (escSymbol) 
				{
					//  Escape /a  alert
					case 97:
						break;
					
					//  Escape /b backspace
					case 98:
						break;
					//  Escape /f forward feed page
					case 102:
						break;
					//  Escape /n  new line	
					case 110:
						break;
					//  Escape /r  carriage return
					case 114:
						break;
					//  Escape /t  horizontal tab
					case 116:
						break;
					//  Escape /v  vertical tab
					case 118:
						break;
					//  Symbol /'  single quotes
					case 27:
						break;
					//  Symbol /"  double quotes
					case 34:
						break;
					//  Symbol //  back slash
					case 92:
						break;
					
					
				}//end switch

				if( escSymbol != 34 )
				{
					symbol = escSymbol;
				}
	
			
			}//end if

			symbol =  _gettc(g_fp);
			
		}//end while

		if( symbol == CARRIAGE_RETURN || symbol == _TEOF )
		{
				CAipi_Error err;
				err.displayFileError(LEXICAL, LEX_ERROR, _T("Close string symbol is missed") );
				return AIPI_ERROR;
		}
			
		pos2 = ftell(g_fp);
		return LITERAL;
	
	}

	//Numbers (Natural and Real )
	if( isDigit(symbol)  )
	{
		g_fcurrentPos = ftell(g_fp);
		pos1 = g_fcurrentPos - 1;		
		g_currentDigit_Type = NAT_NUMBER;
		int countPeriod = 0;
	
		while( isDigit(symbol) || symbol == PERIOD && symbol != _TEOF )
		{
			if( symbol == PERIOD )
			{
				g_currentDigit_Type = REAL_NUMBER;
				++countPeriod;
			}

			symbol = _gettc(g_fp);
					
		}

		if( countPeriod > 1 )
		{
			CAipi_Error err;
			err.displayFileError(LEXICAL, LEX_ERROR, _T("Period symbol is repeated")  );
			return LEX_ERROR;
		}
		
		g_fcurrentPos = ftell(g_fp);
		pos2 = --g_fcurrentPos;
		
		if( symbol == NEW_LINE )
		{
			pos2 = --g_fcurrentPos;
			++g_currentLine;
		}
		if( symbol == _TEOF )
		{
			pos2 = ++g_fcurrentPos;
			fsetpos(g_fp, &g_fcurrentPos );
		}

		return DIGIT;
	}


		//Identifiers and KeyWords
	if( isAlphabetic(symbol) || symbol == UNDERSCORE )
	{
		CAipi_Symbol symb;
		
		g_fcurrentPos = ftell(g_fp);
		pos1 = g_fcurrentPos - 1;		
		
		while( isAlphaNumeric(symbol) && symbol != _TEOF )
		{
			symbol = _gettc(g_fp);
		}
		
		g_fcurrentPos = ftell(g_fp);
		pos2 = --g_fcurrentPos;

		if( symbol == NEW_LINE )
		{
			pos2 = --g_fcurrentPos;
			++g_currentLine;
		}
		if( symbol == _TEOF )
		{
			pos2 = ++g_fcurrentPos;
			fsetpos(g_fp, &g_fcurrentPos );
		}
	
		int keyWord = symb.findKeyWord(tk);
		if( keyWord != NOT_FOUND )
		{
			return keyWord;
		}
		else
		{
			return IDENTIFIER;
		}
		
	}

			
	if (symbol == _TEOF )
	{
		return _TEOF;
		
	}

	fsetpos(g_fp, &g_fcurrentPos );

return UNDEFINE;

}
///////////////////////////////////////////////////////////////////
//// End getTokenFileExp ////
///////////////////////////////////////////////////////////////////



















///////////////////////////////////////////////////////////////////////
//// Begin addTokenizerFileExp ///
//This lexer is just for the expression parser 
////////////////////////////////////////////////////////////////////// 

int CAipi_Lexer::testGetTokenFileExp(TCHAR symbol)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CAipi_Tokenizer  tokz;
	
	CString str;
	//TCHAR buffer[MAX_TK_LEN];
	//fpos_t tempPos = 0;
	g_fcurrentPos = ftell(g_fp);

	fpos_t pos1 = 0;
	fpos_t pos2 = 0;
	tstring tk = _T("");

	//Skip over white space and newline
	while( symbol == SPACE || symbol == CARRIAGE_RETURN || symbol == NEW_LINE || symbol == HORIZONTAL_TAB || symbol == VERTICAL_TAB )
	{
		if( symbol == _TEOF )
		{
			return _TEOF;
		}
		
		if( symbol == NEW_LINE )
		{
			++g_currentLine;
		}
		
		g_fcurrentPos = ftell(g_fp);
		
		/*
		str.Format(_T("Space Pos...%d  " ), g_fcurrentPos);
		AfxMessageBox(str);
		wsprintf(buffer, _T("Space Letra: %c"), symbol);
		AfxMessageBox(buffer);
		wsprintf(buffer, _T("Space ASCII: %d"), symbol);
		AfxMessageBox(buffer);
		*/

		symbol =  _gettc(g_fp);
		
	}

	//Comments
	if( symbol == SLASH )
	{	
		//AfxMessageBox(_T("identifico slash 1"));
		g_fcurrentPos = ftell(g_fp);
		pos1 = g_fcurrentPos - 1;
		//str.Format(_T("Pos del primer SLASH...%d  " ), g_fcurrentPos);
		//AfxMessageBox(str);
		
		
		symbol = _gettc(g_fp);
		g_fcurrentPos = ftell(g_fp);
			
					
		//Simple comment
		if( symbol == SLASH )
		{
			
			//str.Format(_T("Pos del segundo SLASH...%d  " ), g_fcurrentPos);
			//AfxMessageBox(str);		
		
		/*
			wsprintf(buffer, _T("Simple Comment Letra: %c"), symbol);
			AfxMessageBox(buffer);
			wsprintf(buffer, _T("Simple Comment ASCII: %d"), symbol);
			AfxMessageBox(buffer);
			AfxMessageBox(_T("identifico slash 2"));
			*/
			/*
			symbol =  _gettc(g_fp);
			g_fcurrentPos = ftell(g_fp);
			str.Format(_T("Pos antes de entrar al while...%d  " ), g_fcurrentPos);
			AfxMessageBox(str);
			wsprintf(buffer, _T("Simple Comment Txt Letra: %c"), symbol);
			AfxMessageBox(buffer);
			wsprintf(buffer, _T("Simple Comment Txt ASCII: %d"), symbol);
			AfxMessageBox(buffer);
		*/
				
			while ( symbol != CARRIAGE_RETURN && symbol != NEW_LINE   && symbol != _TEOF)
			{
									
				symbol =  _gettc(g_fp);	
				//g_fcurrentPos = ftell(g_fp);
				
				/*
				
				str.Format(_T("Cifclo While Pos...%d  " ), g_fcurrentPos);
				AfxMessageBox(str);
				AfxMessageBox(_T("texto comentario"));
				wsprintf(buffer, _T("Simple Comment Txt Letra: %c"), symbol);
				AfxMessageBox(buffer);
				wsprintf(buffer, _T("Simple Comment Txt ASCII: %d"), symbol);
				AfxMessageBox(buffer);
				*/

			}
				
			//AfxMessageBox(_T("Salio del while"));
			g_fcurrentPos = ftell(g_fp);
			pos2 = g_fcurrentPos - 2;
			
		
			//str.Format(_T("Commentario Pos...%d  " ), g_fcurrentPos);
			//AfxMessageBox(str);
		
			tk = getTextFileRange(pos1, pos2);
			
			if( tk == _T("STOP_ERROR") )
			{
				return STOP_ERROR;
			}

			fsetpos(g_fp, &pos2);
			
			//AfxMessageBox(tk.data());
			
			return COMMENT;

				
		}
		//Complex comment
		else if( symbol == ASTERIC )
		{
			g_fcurrentPos = ftell(g_fp);
			pos1 = g_fcurrentPos - 2;
			symbol =  _gettc(g_fp);
			
			/*
			AfxMessageBox(_T("identifico ASTERISCO 1"));
			wsprintf(buffer, _T("Asterisco1 Comment Letra: %c"), symbol);
			AfxMessageBox(buffer);
			wsprintf(buffer, _T("Asterisco1 Comment ASCII: %d"), symbol);
			AfxMessageBox(buffer);
			str.Format(_T("Pos Asterisco1...%d  " ), g_fcurrentPos);
			AfxMessageBox(str);
			*/
				

			do//find end comment
			{
				while ( symbol != ASTERIC && symbol != _TEOF )
				{
					if( symbol == NEW_LINE )
						++g_currentLine;

				/*
				wsprintf(buffer, _T("Asteric Comment Letra: %c"), symbol);
				AfxMessageBox(buffer);
				wsprintf(buffer, _T("Asteric Comment ASCII: %d"), symbol);
				AfxMessageBox(buffer);
				AfxMessageBox(_T("Texto Comentario Asterisco"));
				str.Format(_T("While Asterisco Pos...%d  " ), g_fcurrentPos);
				AfxMessageBox(str);
				*/
				symbol =  _gettc(g_fp);
									
				}
				
				symbol =  _gettc(g_fp);
				

			}while( symbol != SLASH && symbol != _TEOF );
			
			
			//AfxMessageBox(_T("Salio del do while"));
			g_fcurrentPos = ftell(g_fp);
			pos2 = g_fcurrentPos;
			tk = getTextFileRange(pos1, pos2);
			
			if( tk == _T("STOP_ERROR") )
			{
				return STOP_ERROR;
			}
			
			fsetpos(g_fp, &pos2);

			//AfxMessageBox(tk.data());
			
			return COMMENT;
			
		}
		else
		{
			fsetpos(g_fp, &pos1);
			symbol = _gettc(g_fp);
			g_fcurrentPos = ftell(g_fp);

			/*
			AfxMessageBox(_T("Estoy en Comment ELSE"));
			str.Format(_T("Space Pos1...%d  " ), g_fcurrentPos);
			AfxMessageBox(str);
			
			wsprintf(buffer, _T("Space Letra: %c"), symbol);
			AfxMessageBox(buffer);
			wsprintf(buffer, _T("Space ASCII: %d"), symbol);
			AfxMessageBox(buffer);
		*/
			
		}
			
	}


	//Check for operators
	if( isOperator(symbol) )
	{
		/*
		wsprintf(buffer, _T("Switch1 Operator Letra: %c"), symbol);
		AfxMessageBox(buffer);
		wsprintf(buffer, _T("Switch1 ASCII: %d"), symbol);
		AfxMessageBox(buffer);
		str.Format(_T("Switch1 Pos...%d  " ), g_fcurrentPos);
		AfxMessageBox(str);
	*/
		switch( symbol )
		{
			
			case EQUAL:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				
				if( symbol == EQUAL )
				{
					/*
					AfxMessageBox(_T("entro =="));
					str.Format(_T("Pos...%d  " ), g_fcurrentPos);
					AfxMessageBox(str);
					*/
					tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
					return ET;
				}
				else
				{
					/*
					AfxMessageBox(_T("entro ="));
					str.Format(_T("Pos...%d  " ), g_fcurrentPos);
					AfxMessageBox(str);
					*/
					tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos);
					return AS;
				}
				

			case EXCLAMATION:
				
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
			
				if( symbol == EQUAL )
				{
					/*
					AfxMessageBox(_T("entro !="));
					str.Format(_T("Pos...%d  " ), g_fcurrentPos);
					AfxMessageBox(str);
					*/

					tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
					return NE;
				}
				else
				{
					/*
					AfxMessageBox(_T("entro !"));
					str.Format(_T("Pos...%d  " ), g_fcurrentPos);
					AfxMessageBox(str);
					*/

					tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos);
					return NOT_OP;
				}
				

			case AMPERSAND:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
					
				if( symbol == AMPERSAND )
				{
					/*
					AfxMessageBox(_T("entro &&"));
					str.Format(_T("Pos...%d  " ), g_fcurrentPos);
					AfxMessageBox(str);
					*/

					tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
					return AND_OP;
				}
				else
				{
					/*
					AfxMessageBox(_T("entro &"));
					str.Format(_T("Pos...%d  " ), g_fcurrentPos);
					AfxMessageBox(str);
					*/

					tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
					return AND_BIT;
				}
				

		case VERTICAL_BAR:
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
				
			if( symbol == VERTICAL_BAR )
			{
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				return OR_OP;
			}
			else
			{
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				return OR_BIT;
			}
			

		case LESS_THAN:
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			
			if( symbol == EQUAL )
			{
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				return LE;					
			}
			else if ( symbol == LESS_THAN )
			{
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				return RIGHT_OP;
			}
			else
			{
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				return LT;
			}
			

		case GREATER_THAN:
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
						
			if( symbol == EQUAL )
			{
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				return GE;				
			}
			else if ( symbol == GREATER_THAN )
			{
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				return LEFT_OP;
			}
			else
			{
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				return GT;
			}
			

		case PLUS_SIGN:
			
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			
			if( symbol == EQUAL )
			{
				//str.Format(_T("Symbol...%d  " ), symbol);
				//AfxMessageBox(str);
				
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				return  ADD_ASSIGN;	
			}
			else if ( symbol == PLUS_SIGN )
			{
				//str.Format(_T("Symbol...%d  " ), symbol);
				//AfxMessageBox(str);
				
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				return INC_OP;
			}
			else
			{
				
				//str.Format(_T("Symbol Sum...%d  " ), symbol);
				//AfxMessageBox(str);
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				return PLUS_SIGN;
			}
			
		case MINUS_SIGN:
			
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			
			if( symbol == EQUAL )
			{
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				return SUB_ASSIGN;
			}
			else if ( symbol == MINUS_SIGN )
			{
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				return DEC_OP;	
			}
			else if ( symbol == GT )
			{
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				return PTR_OP;
			}
			else
			{
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				return MINUS_SIGN;
			}
			
		case ASTERIC:
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			
			if( symbol == EQUAL )
			{
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				return MUL_ASSIGN;
			}
			else
			{
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				return ASTERIC;
			}
			
		case SLASH:
			//str.Format(_T("Entro Slash Symbol...%d  " ), symbol);
			//AfxMessageBox(str);
			
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			
			if( symbol == EQUAL )
			{
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				return DIV_ASSIGN;
			}
			else
			{
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				return SLASH;
			}
			
		case PERCENT:
			
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			
			if( symbol == EQUAL )
			{
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				return MOD_ASSIGN;
			}
			else
			{
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				return PERCENT;
			}
			
		
		case COLON:
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
				
			if( symbol == COLON )
			{
				/*
				AfxMessageBox(_T("entro =="));
				str.Format(_T("Pos...%d  " ), g_fcurrentPos);
				AfxMessageBox(str);
				*/
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				return SCOPE_OP;
			}
			else
			{
				/*
				AfxMessageBox(_T("entro ="));
				str.Format(_T("Pos...%d  " ), g_fcurrentPos);
				AfxMessageBox(str);
				*/
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos);
				return COLON;
			}
			
			
		case CARET:
			
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			
			tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
			return XOR_BIT;

		case EQUIVALENCY:
			
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			
			tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
			return NOT_BIT;
			
		case QUESTION:
			
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			
			tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
			return QUESTION;
		
		}
		
		
		
	}

//Check for punctuators
	if( isPunctuator(symbol) )
	{
		
		switch( symbol )
		{
					
			case SEMICOLON:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				return SEMICOLON;
			case OPEN_PARENTHESIS:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				return OPEN_PARENTHESIS;
			case CLOSE_PARENTHESIS:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				return CLOSE_PARENTHESIS;
			case OPEN_BRACKET:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				return OPEN_BRACKET;
			case CLOSE_BRACKET:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				return CLOSE_BRACKET;
			case OPEN_BRACE:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos);
				return OPEN_BRACE;
			case CLOSE_BRACE:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				return CLOSE_BRACE;
			case COMMA:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				return COMMA;
			/*
			case COLON:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos);
				return COLON;
			*/
			case PERIOD:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				return PERIOD;
			case NUMBER_SIGN:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				return NUMBER_SIGN;
			case AT_SYMBOL:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				return AT_SYMBOL;
		
		}
		
	}


	//Double Quoted Strings
	if( symbol == DOBLE_QUOTATION )
	{
		//AfxMessageBox(_T("entro a string"));
		g_fcurrentPos = ftell(g_fp);
		pos1 = g_fcurrentPos - 1;
		
		//str.Format(_T("Pos del primer SLASH...%d  " ), g_fcurrentPos);
		//AfxMessageBox(str);
				
		symbol = _gettc(g_fp);
		
			/*
			str.Format(_T("symbol%d  " ), symbol);	
			pMainFrame->m_wndOutputTabView.AddMsg1(str);
			wsprintf(buffer, _T("Letra: %c"), symbol);
			AfxMessageBox(buffer);
			wsprintf(buffer, _T("ASCII: %d"), symbol);
			AfxMessageBox(buffer);
			*/
		
				
		while(symbol != DOBLE_QUOTATION && symbol != CARRIAGE_RETURN && symbol != _TEOF )
		{
			//symbol =  _gettc(g_fp);
			//str.Format(_T("While Symbol...%d  " ), symbol);
			//AfxMessageBox(str);
			/*
			if( symbol == DOBLE_QUOTATION )
			{
				CAipi_Error err;
				err.displayFileError(SYNTAX, LEX_ERROR, _T("Error"));
				return LEX_ERROR;
			}
			*/
			
			//Check for \n escape sequence
			if( symbol == BACK_SLASH )
			{
				//AfxMessageBox(_T("entro a slash"));
				
				fpos_t tempPos = ftell(g_fp);
				TCHAR escSymbol =  _gettc(g_fp);


				switch (escSymbol) 
				{
					//  Escape /a  alert
					case 97:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						break;
					
					//  Escape /b backspace
					case 98:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						break;
					//  Escape /f forward feed page
					case 102:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						break;
					//  Escape /n  new line	
					case 110:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						break;
					//  Escape /r  carriage return
					case 114:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						break;
					//  Escape /t  horizontal tab
					case 116:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						break;
					//  Escape /v  vertical tab
					case 118:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						break;
					//  Symbol /'  single quotes
					case 27:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						break;
					
					//  Symbol /"  double quotes
					case 34:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						break;
					
						//  Symbol //  back slash
					case 92:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						break;
					
					//AfxMessageBox(_T("reconocio escape"));
				}//end switch

				if( escSymbol != 34 )
				{
					symbol = escSymbol;
				}

				
				
			
			}//end if

			symbol =  _gettc(g_fp);
			
		}//end while

		if( symbol == CARRIAGE_RETURN || symbol == _TEOF )
		{
				CAipi_Error err;
				err.displayFileError(LEXICAL, LEX_ERROR, _T("Close string symbol is missed") );
				return LEX_ERROR;
		}
		
			
		pos2 = ftell(g_fp);
		
		tk = getTextFileRange(pos1, pos2);
		if( tk == _T("STOP_ERROR") )
		{
			return STOP_ERROR;
		}
		
		//AfxMessageBox(_T("agrego string final"));		
		return LITERAL;
	
	}


	//Single Quoted Strings
	if( symbol == SINGLE_QUOTATION )
	{
		//AfxMessageBox(_T("entro a string"));
		g_fcurrentPos = ftell(g_fp);
		pos1 = g_fcurrentPos - 1;
		
		//str.Format(_T("Pos del primer SLASH...%d  " ), g_fcurrentPos);
		//AfxMessageBox(str);
				
		symbol = _gettc(g_fp);
		
			/*
			str.Format(_T("symbol%d  " ), symbol);	
			pMainFrame->m_wndOutputTabView.AddMsg1(str);
			wsprintf(buffer, _T("Letra: %c"), symbol);
			AfxMessageBox(buffer);
			wsprintf(buffer, _T("ASCII: %d"), symbol);
			AfxMessageBox(buffer);
			*/
		
				
		while(symbol != SINGLE_QUOTATION && symbol != CARRIAGE_RETURN && symbol != _TEOF )
		{
			//symbol =  _gettc(g_fp);
			//str.Format(_T("While Symbol...%d  " ), symbol);
			//AfxMessageBox(str);
			/*
			if( symbol == DOBLE_QUOTATION )
			{
				CAipi_Error err;
				err.displayFileError(SYNTAX, LEX_ERROR, _T("Error"));
				return LEX_ERROR;
			}
			*/
			
			//Check for \n escape sequence
			if( symbol == BACK_SLASH )
			{
				//AfxMessageBox(_T("entro a slash"));
				
				fpos_t tempPos = ftell(g_fp);
				TCHAR escSymbol =  _gettc(g_fp);


				switch (escSymbol) 
				{
					//  Escape /a  alert
					case 97:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						break;
					
					//  Escape /b backspace
					case 98:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						break;
					//  Escape /f forward feed page
					case 102:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						break;
					//  Escape /n  new line	
					case 110:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						break;
					//  Escape /r  carriage return
					case 114:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						break;
					//  Escape /t  horizontal tab
					case 116:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						break;
					//  Escape /v  vertical tab
					case 118:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						break;
					//  Symbol /'  single quotes
					case 27:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						break;
					
					//  Symbol /"  double quotes
					case 34:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						break;
					
						//  Symbol //  back slash
					case 92:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						break;
					
					//AfxMessageBox(_T("reconocio escape"));
				}//end switch

				if( escSymbol != 34 )
				{
					symbol = escSymbol;
				}
			
			}//end if

			symbol =  _gettc(g_fp);
			
		}//end while

		if( symbol == CARRIAGE_RETURN || symbol == _TEOF )
		{
				CAipi_Error err;
				err.displayFileError(LEXICAL, LEX_ERROR, _T("Close string symbol is missed") );
				return AIPI_ERROR;
		}
		
			
		pos2 = ftell(g_fp);
		tk = getTextFileRange(pos1, pos2);
		//AfxMessageBox(_T("agrego string final"));		
		return LITERAL;
		
	}

	//Numbers (Natural and Real )
	if( isDigit(symbol)  )
	{
		//AfxMessageBox(_T("entro a digit"));
		g_fcurrentPos = ftell(g_fp);
		pos1 = g_fcurrentPos - 1;		
		g_currentDigit_Type = NAT_NUMBER;
		int countPeriod = 0;
		
		while( isDigit(symbol) || symbol == PERIOD && symbol != _TEOF )
		{
			//str.Format(_T("Pos en Nat Number...%d  " ), g_fcurrentPos);
			//AfxMessageBox(str);
			//wsprintf(buffer, _T("Number: %c"), symbol);
			//AfxMessageBox(buffer);
			//wsprintf(buffer, _T("ASCII: %d"), symbol);
			//AfxMessageBox(buffer);
			if( symbol == PERIOD )
			{
				g_currentDigit_Type = REAL_NUMBER;
				++countPeriod;
			}

			symbol = _gettc(g_fp);
			//str.Format(_T("Pos en Nat Number...%d  " ), g_fcurrentPos);
			//AfxMessageBox(str);
			//wsprintf(buffer, _T("After Number: %c"), symbol);
			//AfxMessageBox(buffer);
			//wsprintf(buffer, _T("ASCII: %d"), symbol);
			//AfxMessageBox(buffer);
		}

		if( countPeriod > 1 )
		{
			CAipi_Error err;
			err.displayFileError(LEXICAL, LEX_ERROR, _T("Period symbol is repeated")  );
			return LEX_ERROR;
		}
		
		g_fcurrentPos = ftell(g_fp);
		pos2 = --g_fcurrentPos;
		
		if( symbol == NEW_LINE )
		{
			pos2 = --g_fcurrentPos;
			++g_currentLine;
			//AfxMessageBox(_T("Detecto new line"));
		}
		if( symbol == _TEOF )
		{
			//AfxMessageBox(_T("_TEOF"));
			pos2 = ++g_fcurrentPos;
			fsetpos(g_fp, &g_fcurrentPos );
		}

		tk = getTextFileRange(pos1, pos2);
		if( tk == _T("STOP_ERROR") )
		{
			return STOP_ERROR;
		}
		
		return DIGIT;
	}


	//Identifiers and KeyWords
	if( isAlphabetic(symbol) || symbol == UNDERSCORE )
	{
		CAipi_Symbol symb;
		
		g_fcurrentPos = ftell(g_fp);
		pos1 = g_fcurrentPos - 1;		
		
		while( isAlphaNumeric(symbol) && symbol != _TEOF )
		{
			symbol = _gettc(g_fp);
			//str.Format(_T("Pos en Identifier...%d  " ), g_fcurrentPos);
			//AfxMessageBox(str);

			//str.Format(_T("Id Symbol...%d  " ), symbol);
			//AfxMessageBox(str);
			
			
		}
		
		g_fcurrentPos = ftell(g_fp);
		pos2 = --g_fcurrentPos;

		if( symbol == NEW_LINE )
		{
			pos2 = --g_fcurrentPos;
			++g_currentLine;
			//AfxMessageBox(_T("Detecto new line"));
		}
		if( symbol == _TEOF )
		{
			//AfxMessageBox(_T("_TEOF"));
			pos2 = ++g_fcurrentPos;
			fsetpos(g_fp, &g_fcurrentPos );
		}
	
		tk = getTextFileRange(pos1, pos2);
		if( tk == _T("STOP_ERROR") )
		{
			return STOP_ERROR;
		}

		
		int keyWord = symb.findKeyWord(tk);
		if( keyWord != NOT_FOUND )
		{
			return keyWord;
		}
		else
		{
			return IDENTIFIER;
		}

		
	}

		
	if (symbol == _TEOF )
	{
		//AfxMessageBox(_T("Fin del archivo"));
		return _TEOF;
		
	}


	/*
	str.Format(_T("symbol%d  " ), symbol);	
	pMainFrame->m_wndOutputTabView.AddMsg1(str);
	wsprintf(buffer, _T("Letra: %c"), symbol);
	AfxMessageBox(buffer);
	wsprintf(buffer, _T("ASCII: %d"), symbol);
	AfxMessageBox(buffer);
	
	*/
	
	fsetpos(g_fp, &g_fcurrentPos );

return UNDEFINE;

}
///////////////////////////////////////////////////////////////////
//// End testGetTokenFileExp ////
///////////////////////////////////////////////////////////////////











///////////////////////////////////////////////////////////
//// Begin getTokenFile ////
////////////////////////////////////////////////////////////

int CAipi_Lexer::getTokenFile(TCHAR symbol)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CAipi_Tokenizer  tokz;
	
	fpos_t pos1 = 0;
	fpos_t pos2 = 0;
	tstring tk = _T("");

	//Skip over white space and newline
	while( symbol == SPACE || symbol == CARRIAGE_RETURN || symbol == NEW_LINE || symbol == HORIZONTAL_TAB || symbol == VERTICAL_TAB )
	{
		if( symbol == _TEOF )
		{
			return _TEOF;
		}
		
		if( symbol == NEW_LINE )
		{
			++g_currentLine;
		}
		
		g_fcurrentPos = ftell(g_fp);
		
		symbol =  _gettc(g_fp);
		
	}


	//Comments
	if( symbol == SLASH )
	{	
		g_fcurrentPos = ftell(g_fp);
		pos1 = g_fcurrentPos - 1;
		symbol = _gettc(g_fp);
		g_fcurrentPos = ftell(g_fp);
			
		
			
		//Simple comment
		if( symbol == SLASH )
		{
			while ( symbol != CARRIAGE_RETURN && symbol != NEW_LINE  && symbol != _TEOF )
			{
				symbol =  _gettc(g_fp);
			
			}
				
			g_fcurrentPos = ftell(g_fp);
			pos2 = g_fcurrentPos - 2;
			fsetpos(g_fp, &pos2);
			fsetpos(g_fp, &g_fcurrentPos );
			return COMMENT;
				
		}
		//Complex comment
		else if( symbol == ASTERIC )
		{
			g_fcurrentPos = ftell(g_fp);
			pos1 = g_fcurrentPos - 2;
			symbol =  _gettc(g_fp);
			
			do//find end comment
			{
				while ( symbol != ASTERIC && symbol != _TEOF )
				{
					if( symbol == NEW_LINE )
					{
						++g_currentLine;
					}

					symbol =  _gettc(g_fp);
				}
				
				symbol =  _gettc(g_fp);
				if( symbol == _TEOF )
				{
					CAipi_Error err;
					err.displayFileError(LEXICAL, LEX_ERROR, _T("Close comment is missed") );
					return LEX_ERROR;
				}
				
		
			}while( symbol != SLASH );
			
			g_fcurrentPos = ftell(g_fp);
			pos2 = g_fcurrentPos -2;
			fsetpos(g_fp, &pos2);
			return COMMENT;
		}
		else
		{
			fsetpos(g_fp, &pos1);
			symbol = _gettc(g_fp);
			g_fcurrentPos = ftell(g_fp);
			
		}
			
	}


	//Check for operators
	if( isOperator(symbol) )
	{
		switch( symbol )
		{
			
			case EQUAL:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				
				if( symbol == EQUAL )
				{
					return ET;
				}
				else
				{
					return AS;
				}
			case EXCLAMATION:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
			
				if( symbol == EQUAL )
				{
					return NE;
				}
				else
				{
					return NOT_OP;

				}
			case AMPERSAND:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				if( symbol == AMPERSAND )
				{
					return AND_OP;
				}
				else
				{
					return AND_BIT;
				}
		case VERTICAL_BAR:
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			if( symbol == VERTICAL_BAR )
			{
				return OR_OP;
			}
			else
			{
				return OR_BIT;
			}
		case LESS_THAN:
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			if( symbol == EQUAL )
			{
				return LE;
				
			}
			else if ( symbol == LESS_THAN )
			{
				return RIGHT_OP;
			}
			else
			{
				return LT;
			}
		case GREATER_THAN:
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			if( symbol == EQUAL )
			{
				return GE;
			}
			else if ( symbol == GREATER_THAN )
			{
				return LEFT_OP;
			}
			else
			{
				return GT;
			}
		case PLUS_SIGN:
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			if( symbol == EQUAL )
			{
				return ADD_ASSIGN;
			}
			else if ( symbol == PLUS_SIGN )
			{
				return INC_OP;
			}
			else
			{
				return PLUS_SIGN;
			}
		case MINUS_SIGN:
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			if( symbol == EQUAL )
			{
				return SUB_ASSIGN;
			}
			else if ( symbol == MINUS_SIGN )
			{
				return DEC_OP;			
			}
			else if ( symbol == GT )
			{
				return PTR_OP;
				
			}
			else
			{
				return MINUS_SIGN;
			}
		case ASTERIC:
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			if( symbol == EQUAL )
			{
				return MUL_ASSIGN;
			}
			else
			{
				return ASTERIC;
			}
		case SLASH:
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			if( symbol == EQUAL )
			{
				return DIV_ASSIGN;
			}
			else
			{
				return SLASH;
			}
		case PERCENT:
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			if( symbol == EQUAL )
			{
				return MOD_ASSIGN;
			}
			else
			{
				return PERCENT;
			}
		case COLON:
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			if( symbol == COLON )
			{
				return SCOPE_OP;
			}
			else
			{
				return COLON;
			}
		case CARET:
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			return XOR_BIT;
		case EQUIVALENCY:
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			return NOT_BIT;

		case QUESTION:
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			return QUESTION;
		
		}
	
	}

//Check for punctuators
	if( isPunctuator(symbol) )
	{
		switch( symbol )
		{
					
			case SEMICOLON:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				return SEMICOLON;
			case OPEN_PARENTHESIS:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				return OPEN_PARENTHESIS;
			case CLOSE_PARENTHESIS:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				return CLOSE_PARENTHESIS;
			//Reserve for large identifiers
			/*
			case OPEN_BRACKET:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				return OPEN_BRACKET;
			*/
			case CLOSE_BRACKET:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				return CLOSE_BRACKET;
			case OPEN_BRACE:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				return OPEN_BRACE;
			case CLOSE_BRACE:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				return CLOSE_BRACE;
			case COMMA:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				return COMMA;
			/*
			case COLON:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
			
			*/
			case PERIOD:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				return PERIOD;
			case NUMBER_SIGN:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				return NUMBER_SIGN;
			case AT_SYMBOL:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				return AT_SYMBOL;
		
		}
	
	}


	//Double Quoted Strings
	if( symbol == DOBLE_QUOTATION )
	{
		g_fcurrentPos = ftell(g_fp);
		pos1 = g_fcurrentPos - 1;
		symbol = _gettc(g_fp);
		while(symbol != DOBLE_QUOTATION && symbol != CARRIAGE_RETURN  && symbol != _TEOF)
		{
			//Check for \n escape sequence
			if( symbol == BACK_SLASH )
			{
				fpos_t tempPos = ftell(g_fp);
				TCHAR escSymbol =  _gettc(g_fp);

				switch (escSymbol) 
				{
					//  Escape /a  alert
					case 97:
						break;
					
					//  Escape /b backspace
					case 98:
						break;
					//  Escape /f forward feed page
					case 102:
						break;
					//  Escape /n  new line	
					case 110:
						break;
					//  Escape /r  carriage return
					case 114:
						break;
					//  Escape /t  horizontal tab
					case 116:
						break;
					//  Escape /v  vertical tab
					case 118:
						break;
					//  Symbol /'  single quotes
					case 27:
						break;
					//  Symbol /"  double quotes
					case 34:
						break;
					//  Symbol //  back slash
					case 92:
						break;
				}//end switch

				if( escSymbol != 34 )
				{
					symbol = escSymbol;
				}
				
			}//end if

			symbol =  _gettc(g_fp);
			
		}//end while

		if( symbol == CARRIAGE_RETURN || symbol == _TEOF )
		{
				CAipi_Error err;
				err.displayFileError(LEXICAL, LEX_ERROR, _T("Close string symbol is missed") );
				return LEX_ERROR;
		}
					
		pos2 = ftell(g_fp);
		return LITERAL;

		
	}


	//Single Quoted Strings
	if( symbol == SINGLE_QUOTATION )
	{
		g_fcurrentPos = ftell(g_fp);
		pos1 = g_fcurrentPos - 1;
		symbol = _gettc(g_fp);
		while(symbol != SINGLE_QUOTATION && symbol != CARRIAGE_RETURN && symbol != _TEOF)
		{
			//Check for \n escape sequence
			if( symbol == BACK_SLASH )
			{
				fpos_t tempPos = ftell(g_fp);
				TCHAR escSymbol =  _gettc(g_fp);
				switch (escSymbol) 
				{
					//  Escape /a  alert
					case 97:
						break;
					//  Escape /b backspace
					case 98:
						break;
					//  Escape /f forward feed page
					case 102:
						break;
					//  Escape /n  new line	
					case 110:
						break;
					//  Escape /r  carriage return
					case 114:
						break;
					//  Escape /t  horizontal tab
					case 116:
						break;
					//  Escape /v  vertical tab
					case 118:
						break;
					//  Symbol /'  single quotes
					case 27:
						break;
					//  Symbol /"  double quotes
					case 34:
						break;
					//  Symbol //  back slash
					case 92:
						break;
									
				}//end switch

				if( escSymbol != 34 )
				{
					symbol = escSymbol;
				}
			
			}//end if

			symbol =  _gettc(g_fp);
			
		}//end while

		if( symbol == CARRIAGE_RETURN || symbol == _TEOF )
		{
				CAipi_Error err;
				err.displayFileError(LEXICAL, LEX_ERROR, _T("Close string symbol is missed") );
				return LEX_ERROR;
		}
					
		pos2 = ftell(g_fp);
		return LITERAL;
		
	}

	//Aipi Variables
	if( symbol == DOLLAR )
	{
		g_fcurrentPos = ftell(g_fp);
		pos1 = g_fcurrentPos - 1;
		symbol = _gettc(g_fp);

		//Skip over white space and newline
		while( symbol == SPACE || symbol == CARRIAGE_RETURN || symbol == NEW_LINE || symbol == HORIZONTAL_TAB || symbol == VERTICAL_TAB )
		{
			if( symbol == _TEOF )
			{
				return _TEOF;
			}
			
			if( symbol == NEW_LINE )
			{
				++g_currentLine;
			}
			symbol =  _gettc(g_fp);
		}
			
		while(symbol != DOLLAR && symbol != CARRIAGE_RETURN && symbol != _TEOF )
		{
			symbol =  _gettc(g_fp);
			
		}//end while

		if( symbol == CARRIAGE_RETURN || symbol == _TEOF )
		{
			CAipi_Error err;
			err.displayFileError(LEXICAL, LEX_ERROR, _T("Close variable symbol is missed") );
			return LEX_ERROR;
		}
		
		pos2 = ftell(g_fp);
		return AIPI_VAR;
		
	}

	//Numbers (Natural and Real )
	if( isDigit(symbol)  )
	{
		g_fcurrentPos = ftell(g_fp);
		pos1 = g_fcurrentPos - 1;		
		g_currentDigit_Type = NAT_NUMBER;
		int countPeriod = 0;
		
		while( isDigit(symbol) || symbol == PERIOD && symbol != _TEOF )
		{
			if( symbol == PERIOD )
			{
				g_currentDigit_Type = REAL_NUMBER;
				++countPeriod;
			}
			if( symbol == _TEOF )
			{
				pos2 = ++g_fcurrentPos;
				fsetpos(g_fp, &g_fcurrentPos );
			}

			symbol = _gettc(g_fp);
		
		}

		if( countPeriod > 1 )
		{
			CAipi_Error err;
			err.displayFileError(LEXICAL, LEX_ERROR, _T("Period symbol is repeated")  );
			return LEX_ERROR;
		}
		
		g_fcurrentPos = ftell(g_fp);
		pos2 = --g_fcurrentPos;
		
		if( symbol == NEW_LINE )
		{
			pos2 = --g_fcurrentPos;
			++g_currentLine;
		}

		return DIGIT;
	}



	//Aipi Identifier with spaces
	if( symbol == OPEN_BRACKET )
	{
		g_fcurrentPos = ftell(g_fp);
		pos1 = g_fcurrentPos - 1;
		symbol = _gettc(g_fp);
		
		//Skip over white space and newline
		while( symbol == SPACE || symbol == CARRIAGE_RETURN || symbol == NEW_LINE || symbol == HORIZONTAL_TAB || symbol == VERTICAL_TAB )
		{
			if( symbol == _TEOF )
			{
				return _TEOF;
			}

			if( symbol == NEW_LINE )
			{
				++g_currentLine;
			}
		
			symbol =  _gettc(g_fp);
		}
		
		//Check for array 
		if( isDigit(symbol) || symbol == CLOSE_BRACKET )
		{
			g_fcurrentPos = pos1+1;
			return OPEN_BRACKET;
		}
				
		while(symbol != CLOSE_BRACKET && symbol != CARRIAGE_RETURN &&  symbol != _TEOF )
		{
			symbol =  _gettc(g_fp);
					
		}//end while

		if( symbol == CARRIAGE_RETURN || symbol == _TEOF)
		{
				CAipi_Error err;
				err.displayFileError(LEXICAL, LEX_ERROR, _T("Close identifier symbol is missed") );
				return LEX_ERROR;
		}
		
		g_fcurrentPos = ftell(g_fp);
		pos2 = g_fcurrentPos;
		return IDENTIFIER;
		
	}

	//Identifiers and KeyWords
	if( isAlphabetic(symbol) || symbol == UNDERSCORE )
	{
		CAipi_Symbol symb;
		g_fcurrentPos = ftell(g_fp);
		pos1 = g_fcurrentPos - 1;
		
		while( isAlphaNumeric(symbol) && symbol != _TEOF )
		{
			symbol = _gettc(g_fp);
		}
		
		g_fcurrentPos = ftell(g_fp);
		pos2 = --g_fcurrentPos;
		
		if( symbol == NEW_LINE )
		{
			pos2 = --g_fcurrentPos;
			++g_currentLine;
		}
		
		if( symbol == _TEOF )
		{
			pos2 = ++g_fcurrentPos;
			fsetpos(g_fp, &g_fcurrentPos );
		}
				
		int kw = symb.findKeyWord(tk);
		if( kw != NOT_FOUND )
		{
			return kw;
		}
		else
		{
			return IDENTIFIER;
		}
		
	}
		
	
	if (symbol == _TEOF )
	{
		return _TEOF;
	}

	fsetpos(g_fp, &g_fcurrentPos );

return UNDEFINE;

}


//////////////////////////////////////////////////////////
//// End getTokenFile //////
//////////////////////////////////////////////////////////






void CAipi_Lexer::createTokenizerFile(CString fname)
{
	
	int tok = UNDEFINE;
	TCHAR symbol;
	const  TCHAR* cFileName = (LPCTSTR) fname; 
		
	if( (g_fp = _tfopen(cFileName, _T("r") )) == NULL )
	{
		CAipi_Error err;
		err.displayFileError(FILE_READ, STOP_ERROR, _T("Unable to read file") );
		return;	
	}
		
	//Find end positon of file
	fseek( g_fp, 0L, SEEK_END);
	long fendPos = ftell(g_fp);
	m_fileDocumentLen = fendPos;

	//Reset to the begining of file
	fseek( g_fp, 0L, SEEK_SET);
		
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Lexer analyzer..."), RGB(0,0,0), TRUE);
	while( (symbol = _gettc(g_fp) ) != _TEOF  )
	{
		tok = addTokenizerFile(symbol);

		/*
		CString str;
		str.Format(_T("TOK...%d  " ), tok);
		AfxMessageBox(str);
		*/

		if( tok == STOP_ERROR || tok == LEX_ERROR  )
		{
			break;
		}
		
		pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, g_fcurrentPos*100/fendPos);
	}
		
	fclose(g_fp);

}







///////////////////////////////////////////////////////////
//// Begin testGetTokenFile ////
////////////////////////////////////////////////////////////

int CAipi_Lexer::testGetTokenFile(TCHAR symbol)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CAipi_Tokenizer  tokz;
	
	CString str;
	//TCHAR buffer[MAX_TK_LEN];
	//fpos_t tempPos = 0;
	static long g_currentId_IForm = 1000;


	//g_fcurrentPos = ftell(g_fp);

	fpos_t pos1 = 0;
	fpos_t pos2 = 0;
	tstring tk = _T("");

	//Skip over white space and newline
	while( symbol == SPACE || symbol == CARRIAGE_RETURN || symbol == NEW_LINE || symbol == HORIZONTAL_TAB || symbol == VERTICAL_TAB )
	{
		if( symbol == _TEOF )
		{
			return _TEOF;
		}
		
		if( symbol == NEW_LINE )
		{
			++g_currentLine;
		}
		
		g_fcurrentPos = ftell(g_fp);
		
		/*
		AfxMessageBox(_T("ESPACIOS"));
		str.Format(_T("Space Pos...%d  " ), g_fcurrentPos);
		AfxMessageBox(str);
		wsprintf(buffer, _T("Space Letra: %c"), symbol);
		AfxMessageBox(buffer);
		wsprintf(buffer, _T("Space ASCII: %d"), symbol);
		AfxMessageBox(buffer);
		*/

		symbol =  _gettc(g_fp);
		
	}




	//Comments
	if( symbol == SLASH )
	{	
		//AfxMessageBox(_T("identifico slash 1"));
		
		g_fcurrentPos = ftell(g_fp);
		pos1 = g_fcurrentPos - 1;
		
		//str.Format(_T("Pos del primer SLASH...%d  " ), g_fcurrentPos);
		//AfxMessageBox(str);
		
		
		symbol = _gettc(g_fp);
		
		g_fcurrentPos = ftell(g_fp);
			
		
			
		//Simple comment
		if( symbol == SLASH )
		{
			
			//str.Format(_T("Pos del segundo SLASH...%d  " ), g_fcurrentPos);
			//AfxMessageBox(str);		
		
		/*
			wsprintf(buffer, _T("Simple Comment Letra: %c"), symbol);
			AfxMessageBox(buffer);
			wsprintf(buffer, _T("Simple Comment ASCII: %d"), symbol);
			AfxMessageBox(buffer);
			AfxMessageBox(_T("identifico slash 2"));
			*/
			/*
			symbol =  _gettc(g_fp);
			g_fcurrentPos = ftell(g_fp);
			str.Format(_T("Pos antes de entrar al while...%d  " ), g_fcurrentPos);
			AfxMessageBox(str);
			wsprintf(buffer, _T("Simple Comment Txt Letra: %c"), symbol);
			AfxMessageBox(buffer);
			wsprintf(buffer, _T("Simple Comment Txt ASCII: %d"), symbol);
			AfxMessageBox(buffer);
		*/
				
			while ( symbol != CARRIAGE_RETURN && symbol != NEW_LINE  && symbol != _TEOF )
			{
									
				symbol =  _gettc(g_fp);
			
				//g_fcurrentPos = ftell(g_fp);
				
				/*
				
				str.Format(_T("Cifclo While Pos...%d  " ), g_fcurrentPos);
				AfxMessageBox(str);
				AfxMessageBox(_T("texto comentario"));
				wsprintf(buffer, _T("Simple Comment Txt Letra: %c"), symbol);
				AfxMessageBox(buffer);
				wsprintf(buffer, _T("Simple Comment Txt ASCII: %d"), symbol);
				AfxMessageBox(buffer);
				*/

			}
				
			//AfxMessageBox(_T("Salio del while"));
			g_fcurrentPos = ftell(g_fp);
			pos2 = g_fcurrentPos - 2;
			
		
			//str.Format(_T("Commentario Pos...%d  " ), g_fcurrentPos);
			//AfxMessageBox(str);
		
			tk = getTextFileRange(pos1, pos2);
			fsetpos(g_fp, &pos2);
			
			//AfxMessageBox(tk.data());
			fsetpos(g_fp, &g_fcurrentPos );
			return COMMENT;

				
		}
		//Complex comment
		else if( symbol == ASTERIC )
		{
			g_fcurrentPos = ftell(g_fp);
			pos1 = g_fcurrentPos - 2;
			symbol =  _gettc(g_fp);
			
			/*
			AfxMessageBox(_T("identifico ASTERISCO 1"));
			wsprintf(buffer, _T("Asterisco1 Comment Letra: %c"), symbol);
			AfxMessageBox(buffer);
			wsprintf(buffer, _T("Asterisco1 Comment ASCII: %d"), symbol);
			AfxMessageBox(buffer);
			str.Format(_T("Pos Asterisco1...%d  " ), g_fcurrentPos);
			AfxMessageBox(str);
			*/
				

			do//find end comment
			{
				while ( symbol != ASTERIC && symbol != _TEOF )
				{
					if( symbol == NEW_LINE )
						++g_currentLine;

				/*
				wsprintf(buffer, _T("Asteric Comment Letra: %c"), symbol);
				AfxMessageBox(buffer);
				wsprintf(buffer, _T("Asteric Comment ASCII: %d"), symbol);
				AfxMessageBox(buffer);
				AfxMessageBox(_T("Texto Comentario Asterisco"));
				str.Format(_T("While Asterisco Pos...%d  " ), g_fcurrentPos);
				AfxMessageBox(str);
				*/
				
					symbol =  _gettc(g_fp);
					
					
				}
				
				symbol =  _gettc(g_fp);
				

			}while( symbol != SLASH && symbol != _TEOF );
			
			
			//AfxMessageBox(_T("Salio del do while"));
			g_fcurrentPos = ftell(g_fp);
			pos2 = g_fcurrentPos;
			tk = getTextFileRange(pos1, pos2);
			
			fsetpos(g_fp, &pos2);

			//AfxMessageBox(tk.data());
			fsetpos(g_fp, &g_fcurrentPos );
			return COMMENT;
			
		}
		else
		{
			fsetpos(g_fp, &pos1);
			symbol = _gettc(g_fp);
			g_fcurrentPos = ftell(g_fp);

			/*
			AfxMessageBox(_T("Estoy en Comment ELSE"));
			str.Format(_T("Space Pos1...%d  " ), g_fcurrentPos);
			AfxMessageBox(str);
			
			wsprintf(buffer, _T("Space Letra: %c"), symbol);
			AfxMessageBox(buffer);
			wsprintf(buffer, _T("Space ASCII: %d"), symbol);
			AfxMessageBox(buffer);
		*/
			
		}
			
	}


	//Check for operators
	if( isOperator(symbol) )
	{
		/*
		wsprintf(buffer, _T("Switch1 Operator Letra: %c"), symbol);
		AfxMessageBox(buffer);
		wsprintf(buffer, _T("Switch1 ASCII: %d"), symbol);
		AfxMessageBox(buffer);
		str.Format(_T("Switch1 Pos...%d  " ), g_fcurrentPos);
		AfxMessageBox(str);
	*/
		switch( symbol )
		{
			
			case EQUAL:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				
				if( symbol == EQUAL )
				{
					/*
					AfxMessageBox(_T("entro =="));
					str.Format(_T("Pos...%d  " ), g_fcurrentPos);
					AfxMessageBox(str);
					*/
					tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
					return ET;
				}
				else
				{
					/*
					AfxMessageBox(_T("entro ="));
					str.Format(_T("Pos...%d  " ), g_fcurrentPos);
					AfxMessageBox(str);
					*/
					tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos);
					return AS;
				}
				

			case EXCLAMATION:
				
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
			
				if( symbol == EQUAL )
				{
					/*
					AfxMessageBox(_T("entro !="));
					str.Format(_T("Pos...%d  " ), g_fcurrentPos);
					AfxMessageBox(str);
					*/

					tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
					return NE;
					
				}
				else
				{
					/*
					AfxMessageBox(_T("entro !"));
					str.Format(_T("Pos...%d  " ), g_fcurrentPos);
					AfxMessageBox(str);
					*/

					tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos);
					return NOT_OP;

				}
				

			case AMPERSAND:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
					
				if( symbol == AMPERSAND )
				{
					/*
					AfxMessageBox(_T("entro &&"));
					str.Format(_T("Pos...%d  " ), g_fcurrentPos);
					AfxMessageBox(str);
					*/

					tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
					return AND_OP;

				}
				else
				{
					/*
					AfxMessageBox(_T("entro &"));
					str.Format(_T("Pos...%d  " ), g_fcurrentPos);
					AfxMessageBox(str);
					*/

					tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
					return AND_BIT;
				}
				

		case VERTICAL_BAR:
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
				
			if( symbol == VERTICAL_BAR )
			{
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				return OR_OP;
			}
			else
			{
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				return OR_BIT;
			}
			

		case LESS_THAN:
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			
			if( symbol == EQUAL )
			{
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				return LE;
				
			}
			else if ( symbol == LESS_THAN )
			{
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				return RIGHT_OP;
				
			}
			else
			{
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				return LT;
			}
			

		case GREATER_THAN:
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
						
			if( symbol == EQUAL )
			{
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				return GE;
				
			}
			else if ( symbol == GREATER_THAN )
			{
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				return LEFT_OP;
				
			}
			else
			{
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				return GT;
			}
			

		case PLUS_SIGN:
			
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			
			if( symbol == EQUAL )
			{
				//str.Format(_T("Symbol...%d  " ), symbol);
				//AfxMessageBox(str);
				
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				return ADD_ASSIGN;

			}
			else if ( symbol == PLUS_SIGN )
			{
				//str.Format(_T("Symbol...%d  " ), symbol);
				//AfxMessageBox(str);
				
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				return INC_OP;
				
			}
			else
			{
				
				//str.Format(_T("Symbol Sum...%d  " ), symbol);
				//AfxMessageBox(str);
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				return PLUS_SIGN;
			}
			
		case MINUS_SIGN:
			
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			
			if( symbol == EQUAL )
			{
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				return SUB_ASSIGN;
				
			}
			else if ( symbol == MINUS_SIGN )
			{
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				return DEC_OP;			
			}
			else if ( symbol == GT )
			{
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				return PTR_OP;
				
			}
			else
			{
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				return MINUS_SIGN;
			}
			
		case ASTERIC:
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			
			if( symbol == EQUAL )
			{
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				return MUL_ASSIGN;
			}
			else
			{
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				return ASTERIC;
			}
			
		case SLASH:
			//str.Format(_T("Entro Slash Symbol...%d  " ), symbol);
			//AfxMessageBox(str);
			
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			
			if( symbol == EQUAL )
			{
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				return DIV_ASSIGN;
				
			}
			else
			{
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				return SLASH;
			}
			
		case PERCENT:
			
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			
			if( symbol == EQUAL )
			{
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				return MOD_ASSIGN;
				
			}
			else
			{
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				return PERCENT;
			}
		
		case COLON:
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
				
			if( symbol == COLON )
			{
				/*
				AfxMessageBox(_T("entro =="));
				str.Format(_T("Pos...%d  " ), g_fcurrentPos);
				AfxMessageBox(str);
				*/
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				return SCOPE_OP;
			}
			else
			{
				/*
				AfxMessageBox(_T("entro ="));
				str.Format(_T("Pos...%d  " ), g_fcurrentPos);
				AfxMessageBox(str);
				*/
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos);
				return COLON;
			}
			
		
		case CARET:
			
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			
			tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
			return XOR_BIT;

		case EQUIVALENCY:
			
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			
			tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
			return NOT_BIT;
		
		case QUESTION:
			
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			
			tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
			return QUESTION;
		
			
		}
		
		
		
	}

//Check for punctuators
	if( isPunctuator(symbol) )
	{
		
		switch( symbol )
		{
					
			case SEMICOLON:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
			
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				return SEMICOLON;
			
			case OPEN_PARENTHESIS:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
			
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				return OPEN_PARENTHESIS;

			case CLOSE_PARENTHESIS:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
			
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				return CLOSE_PARENTHESIS;
			//Reserve for large identifiers
			/*
			case OPEN_BRACKET:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
							
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				//tokz.addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, OPEN_BRACKET, tk, PUNCTUATOR);
				tokz.v_addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, OPEN_BRACKET, tk, PUNCTUATOR);
				return OPEN_BRACKET;
			*/
			case CLOSE_BRACKET:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
							
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				return CLOSE_BRACKET;

			case OPEN_BRACE:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
			
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos);
				return OPEN_BRACE;

			case CLOSE_BRACE:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
			
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				return CLOSE_BRACE;

			case COMMA:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				//AfxMessageBox(_T("COMMA"));
				
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				return COMMA;

			/*
			case COLON:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
			
				
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos);
				return COLON;
			*/
			case PERIOD:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
							
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				return PERIOD;


			case NUMBER_SIGN:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
			
				
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				return NUMBER_SIGN;


			case AT_SYMBOL:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
			
				
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				return AT_SYMBOL;

		
		}
		
				

		
	}


	//Double Quoted Strings
	if( symbol == DOBLE_QUOTATION )
	{
		//AfxMessageBox(_T("entro a string"));
		g_fcurrentPos = ftell(g_fp);
		pos1 = g_fcurrentPos - 1;
		
		//str.Format(_T("Pos del primer SLASH...%d  " ), g_fcurrentPos);
		//AfxMessageBox(str);
				
		symbol = _gettc(g_fp);
		
			/*
			str.Format(_T("symbol%d  " ), symbol);	
			pMainFrame->m_wndOutputTabView.AddMsg1(str);
			wsprintf(buffer, _T("Letra: %c"), symbol);
			AfxMessageBox(buffer);
			wsprintf(buffer, _T("ASCII: %d"), symbol);
			AfxMessageBox(buffer);
			*/
		
				
		while(symbol != DOBLE_QUOTATION && symbol != CARRIAGE_RETURN && symbol != _TEOF)
		{
			//symbol =  _gettc(g_fp);
			//str.Format(_T("While Symbol...%d  " ), symbol);
			//AfxMessageBox(str);
			/*
			if( symbol == DOBLE_QUOTATION )
			{
				CAipi_Error err;
				err.displayFileError(SYNTAX, LEX_ERROR, _T("Error"));
				return LEX_ERROR;
			}
			*/
			
			//Check for \n escape sequence
			if( symbol == BACK_SLASH )
			{
				//AfxMessageBox(_T("entro a slash"));
				
				fpos_t tempPos = ftell(g_fp);
				TCHAR escSymbol =  _gettc(g_fp);


				switch (escSymbol) 
				{
					//  Escape /a  alert
					case 97:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						break;
					
					//  Escape /b backspace
					case 98:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						break;
					//  Escape /f forward feed page
					case 102:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						break;
					//  Escape /n  new line	
					case 110:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						break;
					//  Escape /r  carriage return
					case 114:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						break;
					//  Escape /t  horizontal tab
					case 116:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						break;
					//  Escape /v  vertical tab
					case 118:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						break;
					//  Symbol /'  single quotes
					case 27:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						break;
					
					//  Symbol /"  double quotes
					case 34:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						break;
					
						//  Symbol //  back slash
					case 92:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						break;
					
					//AfxMessageBox(_T("reconocio escape"));
				}//end switch

				if( escSymbol != 34 )
				{
					symbol = escSymbol;
				}

				
				
			
			}//end if

			symbol =  _gettc(g_fp);
			
		}//end while

		if( symbol == CARRIAGE_RETURN || symbol == _TEOF )
		{
				CAipi_Error err;
				err.displayFileError(LEXICAL, LEX_ERROR, _T("Close string symbol is missed") );
				return LEX_ERROR;
		}
		
			
		pos2 = ftell(g_fp);
		
		tk = getTextFileRange(pos1, pos2);
		
		//Eliminates doble quotation symbols
		tk.erase(0, 1);
		//AfxMessageBox(tk.data());
		int len = tk.length();
		tk.erase(len-1);
		//AfxMessageBox(tk.data());
		//tk = getTextFileRange(pos1 + 1, pos2 -1);
		
		if( tk == _T("STOP_ERROR") )
		{
			return STOP_ERROR;
		}
		++g_currentId_IForm;
		//g_currentId_IForm = m_intForm;
		//AfxMessageBox(_T("agrego string final"));		
		
		return LITERAL;

		
	}


	//Single Quoted Strings
	if( symbol == SINGLE_QUOTATION )
	{
		//AfxMessageBox(_T("entro a string"));
		g_fcurrentPos = ftell(g_fp);
		pos1 = g_fcurrentPos - 1;
		
		//str.Format(_T("Pos del primer SLASH...%d  " ), g_fcurrentPos);
		//AfxMessageBox(str);
				
		symbol = _gettc(g_fp);
		
			/*
			str.Format(_T("symbol%d  " ), symbol);	
			pMainFrame->m_wndOutputTabView.AddMsg1(str);
			wsprintf(buffer, _T("Letra: %c"), symbol);
			AfxMessageBox(buffer);
			wsprintf(buffer, _T("ASCII: %d"), symbol);
			AfxMessageBox(buffer);
			*/
		
				
		while(symbol != SINGLE_QUOTATION && symbol != CARRIAGE_RETURN && symbol != _TEOF)
		{
			//symbol =  _gettc(g_fp);
			//str.Format(_T("While Symbol...%d  " ), symbol);
			//AfxMessageBox(str);
			/*
			if( symbol == DOBLE_QUOTATION )
			{
				CAipi_Error err;
				err.displayFileError(SYNTAX);
				return LEX_ERROR;
			}
			*/
			
			//Check for \n escape sequence
			if( symbol == BACK_SLASH )
			{
				//AfxMessageBox(_T("entro a slash"));
				
				fpos_t tempPos = ftell(g_fp);
				TCHAR escSymbol =  _gettc(g_fp);


				switch (escSymbol) 
				{
					//  Escape /a  alert
					case 97:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						break;
					
					//  Escape /b backspace
					case 98:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						break;
					//  Escape /f forward feed page
					case 102:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						break;
					//  Escape /n  new line	
					case 110:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						break;
					//  Escape /r  carriage return
					case 114:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						break;
					//  Escape /t  horizontal tab
					case 116:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						break;
					//  Escape /v  vertical tab
					case 118:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						break;
					//  Symbol /'  single quotes
					case 27:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						break;
					
					//  Symbol /"  double quotes
					case 34:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						break;
					
						//  Symbol //  back slash
					case 92:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						break;
					
					//AfxMessageBox(_T("reconocio escape"));
				}//end switch

				if( escSymbol != 34 )
				{
					symbol = escSymbol;
				}
			
			}//end if

			symbol =  _gettc(g_fp);
			
		}//end while

		if( symbol == CARRIAGE_RETURN || symbol == _TEOF )
		{
				CAipi_Error err;
				err.displayFileError(LEXICAL, LEX_ERROR, _T("Close string symbol is missed") );
				return LEX_ERROR;
		}
		
			
		pos2 = ftell(g_fp);
		
		tk = getTextFileRange(pos1, pos2);
		//Eliminates single quotation symbols
		//tk = getTextFileRange(pos1 + 1, pos2 -1);
		
		
		if( tk == _T("STOP_ERROR") )
		{
			return STOP_ERROR;
		}

		++g_currentId_IForm;
		//g_currentId_IForm = m_intForm;

		
		tk = formatTkNameOpt(tk);
		//AfxMessageBox(_T("agrego string final"));		
		
		return LITERAL;

		
	}





	//Aipi Variables
	if( symbol == DOLLAR )
	{
		//AfxMessageBox(_T("entro a string"));
		g_fcurrentPos = ftell(g_fp);
		pos1 = g_fcurrentPos - 1;
		
		//str.Format(_T("Pos del primer SLASH...%d  " ), g_fcurrentPos);
		//AfxMessageBox(str);
				
		symbol = _gettc(g_fp);

		//Skip over white space and newline
		while( symbol == SPACE || symbol == CARRIAGE_RETURN || symbol == NEW_LINE || symbol == HORIZONTAL_TAB || symbol == VERTICAL_TAB )
		{
			if( symbol == _TEOF )
			{
				return _TEOF;
			}
			
			
			if( symbol == NEW_LINE )
			{
				++g_currentLine;
			}
		
		

		symbol =  _gettc(g_fp);
		
		}
			
		/*
			str.Format(_T("symbol%d  " ), symbol);	
			pMainFrame->m_wndOutputTabView.AddMsg1(str);
			wsprintf(buffer, _T("Letra: %c"), symbol);
			AfxMessageBox(buffer);
			wsprintf(buffer, _T("ASCII: %d"), symbol);
			AfxMessageBox(buffer);
		*/
		
				
		while(symbol != DOLLAR && symbol != CARRIAGE_RETURN && symbol != _TEOF )
		{
			//symbol =  _gettc(g_fp);
			//str.Format(_T("While Symbol...%d  " ), symbol);
			//AfxMessageBox(str);
			/*
			if( symbol == DOBLE_QUOTATION )
			{
				CAipi_Error err;
				err.displayFileError(SYNTAX);
				return LEX_ERROR;
			}
			*/
			
			symbol =  _gettc(g_fp);
			
		}//end while

		if( symbol == CARRIAGE_RETURN || symbol == _TEOF )
		{
				CAipi_Error err;
				err.displayFileError(LEXICAL, LEX_ERROR, _T("Close string symbol is missed") );
				return LEX_ERROR;
		}
		
			
		pos2 = ftell(g_fp);
		
		tk = getTextFileRange(pos1, pos2);
		//Eliminates dollar symbols
		//tk = getTextFileRange(pos1 + 1, pos2 -1);

		if( tk == _T("STOP_ERROR") )
		{
			return STOP_ERROR;
		}
		
		//AfxMessageBox(_T("agrego string final"));		
		
		return AIPI_VAR;

		
	}





		//Numbers (Natural and Real )
	if( isDigit(symbol)  )
	{
		//AfxMessageBox(_T("entro a digit"));

		g_fcurrentPos = ftell(g_fp);
		pos1 = g_fcurrentPos - 1;		
				
		g_currentDigit_Type = NAT_NUMBER;
		int countPeriod = 0;

		
		while( isDigit(symbol) || symbol == PERIOD && symbol != _TEOF )
		{
			
			//str.Format(_T("Pos en Nat Number...%d  " ), g_fcurrentPos);
			//AfxMessageBox(str);
			//wsprintf(buffer, _T("Number: %c"), symbol);
			//AfxMessageBox(buffer);
			//wsprintf(buffer, _T("ASCII: %d"), symbol);
			//AfxMessageBox(buffer);
						

			if( symbol == PERIOD )
			{
				g_currentDigit_Type = REAL_NUMBER;
				++countPeriod;
			}
			
			if( symbol == _TEOF )
			{
				//AfxMessageBox(_T("_TEOF"));
				pos2 = ++g_fcurrentPos;
				fsetpos(g_fp, &g_fcurrentPos );
			}

			symbol = _gettc(g_fp);
			//str.Format(_T("Pos en Nat Number...%d  " ), g_fcurrentPos);
			//AfxMessageBox(str);
			//wsprintf(buffer, _T("After Number: %c"), symbol);
			//AfxMessageBox(buffer);
			//wsprintf(buffer, _T("ASCII: %d"), symbol);
			//AfxMessageBox(buffer);
							
			
				
			
		}

		if( countPeriod > 1 )
		{
			CAipi_Error err;
			err.displayFileError(LEXICAL, LEX_ERROR, _T("Period symbol is repeated")  );
			return LEX_ERROR;
		}
		
		g_fcurrentPos = ftell(g_fp);
		pos2 = --g_fcurrentPos;
		
		if( symbol == NEW_LINE )
		{
			pos2 = --g_fcurrentPos;
			++g_currentLine;
			//AfxMessageBox(_T("Detecto new line"));
		}

		tk = getTextFileRange(pos1, pos2);
		//AfxMessageBox(_T("DIGITO"));
		return DIGIT;
	}






	//Aipi Identifier with spaces
	if( symbol == OPEN_BRACKET )
	{
		//AfxMessageBox(_T("entro a Bracket"));
		g_fcurrentPos = ftell(g_fp);
		pos1 = g_fcurrentPos - 1;
		
		//str.Format(_T("current Pos ...%d  " ), g_fcurrentPos);
		//AfxMessageBox(str);
				
		symbol = _gettc(g_fp);
		
		//Skip over white space and newline
		while( symbol == SPACE || symbol == CARRIAGE_RETURN || symbol == NEW_LINE || symbol == HORIZONTAL_TAB || symbol == VERTICAL_TAB )
		{
			if( symbol == _TEOF )
			{
				return _TEOF;
			}
			
			
			if( symbol == NEW_LINE )
			{
				++g_currentLine;
			}
		
		

		symbol =  _gettc(g_fp);
		
		}
		/*	
		str.Format(_T("symbol%d  " ), symbol);	
		pMainFrame->m_wndOutputTabView.AddMsg1(str);
		wsprintf(buffer, _T("Letra: %c"), symbol);
		AfxMessageBox(buffer);
		wsprintf(buffer, _T("ASCII: %d"), symbol);
		AfxMessageBox(buffer);
		*/	

		//Check for array 
		if( isDigit(symbol) || symbol == CLOSE_BRACKET )
		{
			//AfxMessageBox(_T("Detecto Digit"));
			g_fcurrentPos = pos1+1;
			tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
			//AfxMessageBox(_T("OPEN BRACKET"));
			return OPEN_BRACKET;
		}
				
		while(symbol != CLOSE_BRACKET && symbol != CARRIAGE_RETURN && symbol != _TEOF )
		{
			symbol =  _gettc(g_fp);
			//str.Format(_T("While Symbol...%d  " ), symbol);
			//AfxMessageBox(str);
			/*
			if( symbol == DOBLE_QUOTATION )
			{
				CAipi_Error err;
				err.displayFileError(SYNTAX);
				return LEX_ERROR;
			}
			*/
			
					
		}//end while

		if( symbol == CARRIAGE_RETURN || symbol == _TEOF)
		{
				CAipi_Error err;
				err.displayFileError(LEXICAL, LEX_ERROR, _T("Close string symbol is missed") );
				return LEX_ERROR;
		}
		
			
		g_fcurrentPos = ftell(g_fp);
		pos2 = g_fcurrentPos;
		
		tk = getTextFileRange(pos1, pos2);
		
		if( tk == _T("STOP_ERROR") )
		{
			return STOP_ERROR;
		}
		
		//AfxMessageBox(_T("agrego string final"));		
		
		return IDENTIFIER;

		
	}






		//Identifiers and KeyWords
	if( isAlphabetic(symbol) || symbol == UNDERSCORE )
	{
		CAipi_Symbol symb;
		
		g_fcurrentPos = ftell(g_fp);
		pos1 = g_fcurrentPos - 1;
		
		//str.Format(_T("Pos 1 en Identifier...%d  " ), pos1);
		//AfxMessageBox(str);
		
		while( isAlphaNumeric(symbol) && symbol != _TEOF )
		{
			//AfxMessageBox(_T("While AlphaNumeric"));
			symbol = _gettc(g_fp);
			//g_fcurrentPos = ftell(g_fp);
			//str.Format(_T("Pos en Identifier...%d  " ), g_fcurrentPos);
			//AfxMessageBox(str);

			//str.Format(_T("Id Symbol...%d  " ), symbol);
			//AfxMessageBox(str);

			
		}
		
		g_fcurrentPos = ftell(g_fp);

		pos2 = --g_fcurrentPos;
		//str.Format(_T("Pos 2 en Identifier...%d  " ), pos2);
		//AfxMessageBox(str);
		
		
		
		if( symbol == NEW_LINE )
		{
			pos2 = --g_fcurrentPos;
			++g_currentLine;
			///AfxMessageBox(_T("Detecto new line"));
		}

		
		if( symbol == _TEOF )
		{
			//AfxMessageBox(_T("_TEOF"));
			pos2 = ++g_fcurrentPos;
			fsetpos(g_fp, &g_fcurrentPos );
		}
		
		
	
		tk = getTextFileRange(pos1, pos2);

		//symbol =  _gettc(g_fp);

		if( tk == _T("STOP_ERROR") )
		{
			return STOP_ERROR;
		}
		
		int kw = symb.findKeyWord(tk);
		if( kw != NOT_FOUND )
		{
			//AfxMessageBox(_T("KEYWORD"));
			return kw;
		}
		else
		{
			//AfxMessageBox(_T("IDENTIFICADOR"));
			//str.Format(_T("Char Last Pos...%d  " ), pos2);
			//AfxMessageBox(str);
			

			return IDENTIFIER;
		}

		
	}
    
	
		
	if (symbol == _TEOF )
	{
		//AfxMessageBox(_T("Fin del archivo"));
		return _TEOF;
		
	}

	/*
	str.Format(_T("symbol%d  " ), symbol);	
	pMainFrame->m_wndOutputTabView.AddMsg1(str);
	wsprintf(buffer, _T("Letra: %c"), symbol);
	AfxMessageBox(buffer);
	wsprintf(buffer, _T("ASCII: %d"), symbol);
	AfxMessageBox(buffer);
	
	*/
	
	fsetpos(g_fp, &g_fcurrentPos );

return UNDEFINE;

}


//////////////////////////////////////////////////////////
//// End getTokenFile //////
//////////////////////////////////////////////////////////












///////////////////////////////////////////////////////////
//// Begin addTokenizerFile ////
////////////////////////////////////////////////////////////

int CAipi_Lexer::addTokenizerFile(TCHAR symbol)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CAipi_Tokenizer  tokz;
	
	CString str;
	//TCHAR buffer[MAX_TK_LEN];
	//fpos_t tempPos = 0;
	//static long g_currentId_IForm = 1000;


	//g_fcurrentPos = ftell(g_fp);

	fpos_t pos1 = 0;
	fpos_t pos2 = 0;
	tstring tk = _T("");

	//Skip over white space and newline
	while( symbol == SPACE || symbol == CARRIAGE_RETURN || symbol == NEW_LINE || symbol == HORIZONTAL_TAB || symbol == VERTICAL_TAB )
	{
		if( symbol == _TEOF )
		{
			return _TEOF;
		}
		
		if( symbol == NEW_LINE )
		{
			++g_currentLine;
			
			/*
			AfxMessageBox(_T("Spaces LINE"));
			str.Format(_T("Line...%d  " ), g_currentLine);
			AfxMessageBox(str);
			str.Format(_T("Space Pos...%d  " ), g_fcurrentPos);
			AfxMessageBox(str);
			*/
			
		}
		
		g_fcurrentPos = ftell(g_fp);
		
		/*
		AfxMessageBox(_T("ESPACIOS"));
		str.Format(_T("Space Pos...%d  " ), g_fcurrentPos);
		AfxMessageBox(str);
		wsprintf(buffer, _T("Space Letra: %c"), symbol);
		AfxMessageBox(buffer);
		wsprintf(buffer, _T("Space ASCII: %d"), symbol);
		AfxMessageBox(buffer);
		*/

		symbol =  _gettc(g_fp);
		
	}




	//Comments
	if( symbol == SLASH )
	{	
		//AfxMessageBox(_T("identifico slash 1"));
		
		g_fcurrentPos = ftell(g_fp);
		pos1 = g_fcurrentPos - 1;
		
		//str.Format(_T("Pos del primer SLASH...%d  " ), g_fcurrentPos);
		//AfxMessageBox(str);
		
		
		symbol = _gettc(g_fp);
		
		g_fcurrentPos = ftell(g_fp);
			
		
			
		//Simple comment
		if( symbol == SLASH )
		{
			
			//str.Format(_T("Pos del segundo SLASH...%d  " ), g_fcurrentPos);
			//AfxMessageBox(str);		
		
		/*
			wsprintf(buffer, _T("Simple Comment Letra: %c"), symbol);
			AfxMessageBox(buffer);
			wsprintf(buffer, _T("Simple Comment ASCII: %d"), symbol);
			AfxMessageBox(buffer);
			AfxMessageBox(_T("identifico slash 2"));
			*/
			/*
			symbol =  _gettc(g_fp);
			g_fcurrentPos = ftell(g_fp);
			str.Format(_T("Pos antes de entrar al while...%d  " ), g_fcurrentPos);
			AfxMessageBox(str);
			wsprintf(buffer, _T("Simple Comment Txt Letra: %c"), symbol);
			AfxMessageBox(buffer);
			wsprintf(buffer, _T("Simple Comment Txt ASCII: %d"), symbol);
			AfxMessageBox(buffer);
		*/
				
			while ( symbol != CARRIAGE_RETURN && symbol != NEW_LINE  && symbol != _TEOF )
			{
									
				symbol =  _gettc(g_fp);

				
			
				//g_fcurrentPos = ftell(g_fp);
				
				/*
				
				str.Format(_T("Cifclo While Pos...%d  " ), g_fcurrentPos);
				AfxMessageBox(str);
				AfxMessageBox(_T("texto comentario"));
				wsprintf(buffer, _T("Simple Comment Txt Letra: %c"), symbol);
				AfxMessageBox(buffer);
				wsprintf(buffer, _T("Simple Comment Txt ASCII: %d"), symbol);
				AfxMessageBox(buffer);
				*/

			}
				
			//AfxMessageBox(_T("Salio del while"));
			g_fcurrentPos = ftell(g_fp);

			
			pos2 = g_fcurrentPos - 2;
			
		
			//str.Format(_T("Commentario Pos...%d  " ), g_fcurrentPos);
			//AfxMessageBox(str);
		
			tk = getTextFileRange(pos1, pos2);
			fsetpos(g_fp, &pos2);
			
			//AfxMessageBox(tk.data());
			//tokz.addToken(pos1, pos2, g_currentLine, SIMPLE_COMMENT, tk, COMMENT);
			tokz.v_addToken(pos1, pos2, g_currentLine, SIMPLE_COMMENT, tk, COMMENT);
			fsetpos(g_fp, &g_fcurrentPos );
			return COMMENT;

				
		}
		//Complex comment
		else if( symbol == ASTERIC )
		{
			g_fcurrentPos = ftell(g_fp);
			pos1 = g_fcurrentPos - 2;
			symbol =  _gettc(g_fp);
			
			/*
			AfxMessageBox(_T("identifico ASTERISCO 1"));
			wsprintf(buffer, _T("Asterisco1 Comment Letra: %c"), symbol);
			AfxMessageBox(buffer);
			wsprintf(buffer, _T("Asterisco1 Comment ASCII: %d"), symbol);
			AfxMessageBox(buffer);
			str.Format(_T("Pos Asterisco1...%d  " ), g_fcurrentPos);
			AfxMessageBox(str);
			*/
				

			do//find end comment
			{
				while ( symbol != ASTERIC && symbol != _TEOF )
				{
					/*
					if( symbol == NEW_LINE )
					{
						++g_currentLine;
						AfxMessageBox(_T("Complex Comment LINE"));
						str.Format(_T("Line...%d  " ), g_currentLine);
						AfxMessageBox(str);
						
					}
				*/
				//TCHAR buffer[200];
				//wsprintf(buffer, _T("Asteric Comment Letra: %c"), symbol);
				//AfxMessageBox(buffer);
				//wsprintf(buffer, _T("Asteric Comment ASCII: %d"), symbol);
				//AfxMessageBox(buffer);
				//AfxMessageBox(_T("Texto Comentario Asterisco"));
				//str.Format(_T("While Asterisco Pos...%d  " ), g_fcurrentPos);
				//AfxMessageBox(str);
				
				
					symbol =  _gettc(g_fp);
				
					
					
				}
				
				symbol =  _gettc(g_fp);
				
				if( symbol == _TEOF )
				{
					CAipi_Error err;
					err.displayFileError(LEXICAL, LEX_ERROR, _T("Close comment is missed") );
					return LEX_ERROR;
				}
				

			}while( symbol != SLASH );
			
			
			//AfxMessageBox(_T("Salio del do while"));
			g_fcurrentPos = ftell(g_fp);
			
			/*
			AfxMessageBox(_T("pos2 Complex Comment"));
			str.Format(_T("Pos2...%d  " ), g_fcurrentPos);
			AfxMessageBox(str);
			*/			
			
			pos2 = g_fcurrentPos;
			tk = getTextFileRange(pos1, pos2);
			
			fsetpos(g_fp, &pos2);

			//AfxMessageBox(tk.data());
			
			
			//tokz.addToken(pos1, pos2, g_currentLine, COMPLEX_COMMENT, tk, COMMENT);
			tokz.v_addToken(pos1, pos2, g_currentLine, COMPLEX_COMMENT, tk, COMMENT);
			
			fsetpos(g_fp, &g_fcurrentPos );
			return COMMENT;
			
		}
		else
		{
			fsetpos(g_fp, &pos1);
			symbol = _gettc(g_fp);
			g_fcurrentPos = ftell(g_fp);

			/*
			AfxMessageBox(_T("Estoy en Comment ELSE"));
			str.Format(_T("Space Pos1...%d  " ), g_fcurrentPos);
			AfxMessageBox(str);
			
			wsprintf(buffer, _T("Space Letra: %c"), symbol);
			AfxMessageBox(buffer);
			wsprintf(buffer, _T("Space ASCII: %d"), symbol);
			AfxMessageBox(buffer);
		*/
			
		}
			
	}


	//Check for operators
	if( isOperator(symbol) )
	{
		/*
		wsprintf(buffer, _T("Switch1 Operator Letra: %c"), symbol);
		AfxMessageBox(buffer);
		wsprintf(buffer, _T("Switch1 ASCII: %d"), symbol);
		AfxMessageBox(buffer);
		str.Format(_T("Switch1 Pos...%d  " ), g_fcurrentPos);
		AfxMessageBox(str);
	*/
		switch( symbol )
		{
			
			case EQUAL:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				
				if( symbol == EQUAL )
				{
					/*
					AfxMessageBox(_T("entro =="));
					str.Format(_T("Pos...%d  " ), g_fcurrentPos);
					AfxMessageBox(str);
					*/
					tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
					//tokz.addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, ET, tk, OPERATOR);
					tokz.v_addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, ET, tk, ET);
					return ET;
				}
				else
				{
					/*
					AfxMessageBox(_T("entro ="));
					str.Format(_T("Pos...%d  " ), g_fcurrentPos);
					AfxMessageBox(str);
					*/
					tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos);
					//tokz.addToken(g_fcurrentPos-1, g_fcurrentPos, g_currentLine, AS, tk, OPERATOR);
					tokz.v_addToken(g_fcurrentPos-1, g_fcurrentPos, g_currentLine, AS, tk, AS);
					return AS;
				}
				

			case EXCLAMATION:
				
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
			
				if( symbol == EQUAL )
				{
					/*
					AfxMessageBox(_T("entro !="));
					str.Format(_T("Pos...%d  " ), g_fcurrentPos);
					AfxMessageBox(str);
					*/

					tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
					//tokz.addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, NE, tk, OPERATOR);
					tokz.v_addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, NE, tk, NE);
					return NE;
					
				}
				else
				{
					/*
					AfxMessageBox(_T("entro !"));
					str.Format(_T("Pos...%d  " ), g_fcurrentPos);
					AfxMessageBox(str);
					*/

					tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos);
					//tokz.addToken(g_fcurrentPos -1, g_fcurrentPos, g_currentLine, NOT_OP, tk, OPERATOR);
					tokz.v_addToken(g_fcurrentPos -1, g_fcurrentPos, g_currentLine, NOT_OP, tk, NOT_OP);
					return NOT_OP;

				}
				

			case AMPERSAND:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
					
				if( symbol == AMPERSAND )
				{
					/*
					AfxMessageBox(_T("entro &&"));
					str.Format(_T("Pos...%d  " ), g_fcurrentPos);
					AfxMessageBox(str);
					*/

					tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
					//tokz.addToken(g_fcurrentPos -1, g_fcurrentPos + 1, g_currentLine, AND_OP, tk, OPERATOR);
					tokz.v_addToken(g_fcurrentPos -1, g_fcurrentPos + 1, g_currentLine, AND_OP, tk, AND_OP);
					return AND_OP;

				}
				else
				{
					/*
					AfxMessageBox(_T("entro &"));
					str.Format(_T("Pos...%d  " ), g_fcurrentPos);
					AfxMessageBox(str);
					*/

					tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
					//tokz.addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, AND_BIT, tk, OPERATOR);
					tokz.v_addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, AND_BIT, tk, AND_BIT);
					return AND_BIT;
				}
				

		case VERTICAL_BAR:
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
				
			if( symbol == VERTICAL_BAR )
			{
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				//tokz.addToken(g_fcurrentPos -1, g_fcurrentPos + 1, g_currentLine, OR_OP, tk, OPERATOR);
				tokz.v_addToken(g_fcurrentPos -1, g_fcurrentPos + 1, g_currentLine, OR_OP, tk, OR_OP);
				return OR_OP;
			}
			else
			{
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				//tokz.addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, OR_BIT, tk, OPERATOR);
				tokz.v_addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, OR_BIT, tk, OR_BIT);
				return OR_BIT;
			}
			

		case LESS_THAN:
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			
			if( symbol == EQUAL )
			{
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				//tokz.addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, LE, tk, OPERATOR);
				tokz.v_addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, LE, tk, LE);
				return LE;
				
			}
			else if ( symbol == LESS_THAN )
			{
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				//tokz.addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, RIGHT_OP, tk, OPERATOR);
				tokz.v_addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, RIGHT_OP, tk, RIGHT_OP);
				return RIGHT_OP;
				
			}
			else
			{
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				//tokz.addToken(g_fcurrentPos -1 , g_fcurrentPos, g_currentLine, LT, tk, OPERATOR);
				tokz.v_addToken(g_fcurrentPos -1 , g_fcurrentPos, g_currentLine, LT, tk, LT);
				return LT;
			}
			

		case GREATER_THAN:
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
						
			if( symbol == EQUAL )
			{
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				//tokz.addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, GE, tk, OPERATOR);
				tokz.v_addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, GE, tk, GE);
				return GE;
				
			}
			else if ( symbol == GREATER_THAN )
			{
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				//tokz.addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, LEFT_OP, tk, OPERATOR);
				tokz.v_addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, LEFT_OP, tk, LEFT_OP);
				return LEFT_OP;
				
			}
			else
			{
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				//tokz.addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, GT, tk, OPERATOR);
				tokz.v_addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, GT, tk, GT);
				return GT;
			}
			

		case PLUS_SIGN:
			
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			
			if( symbol == EQUAL )
			{
				//str.Format(_T("Symbol...%d  " ), symbol);
				//AfxMessageBox(str);
				
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				//tokz.addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, ADD_ASSIGN, tk, OPERATOR);
				tokz.v_addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, ADD_ASSIGN, tk, ADD_ASSIGN);
				return ADD_ASSIGN;

			}
			else if ( symbol == PLUS_SIGN )
			{
				//str.Format(_T("Symbol...%d  " ), symbol);
				//AfxMessageBox(str);
				
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				//tokz.addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, INC_OP, tk, OPERATOR);
				tokz.v_addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, INC_OP, tk, INC_OP);
				return INC_OP;
				
			}
			else
			{
				
				//str.Format(_T("Symbol Sum...%d  " ), symbol);
				//AfxMessageBox(str);
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				//tokz.addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, PLUS_SIGN, tk, OPERATOR);
				tokz.v_addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, PLUS_SIGN, tk, PLUS_SIGN);
				return PLUS_SIGN;
			}
			
		case MINUS_SIGN:
			
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			
			if( symbol == EQUAL )
			{
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				//tokz.addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, SUB_ASSIGN, tk, OPERATOR);
				tokz.v_addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, SUB_ASSIGN, tk, SUB_ASSIGN);
				return SUB_ASSIGN;
				
			}
			else if ( symbol == MINUS_SIGN )
			{
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				//tokz.addToken(g_fcurrentPos -1, g_fcurrentPos + 1, g_currentLine, DEC_OP, tk, OPERATOR);
				tokz.v_addToken(g_fcurrentPos -1, g_fcurrentPos + 1, g_currentLine, DEC_OP, tk, DEC_OP);
				return DEC_OP;			
			}
			else if ( symbol == GT )
			{
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				//tokz.addToken(g_fcurrentPos -1, g_fcurrentPos + 1, g_currentLine, PTR_OP, tk, OPERATOR);
				tokz.v_addToken(g_fcurrentPos -1, g_fcurrentPos + 1, g_currentLine, PTR_OP, tk, PTR_OP);
				return PTR_OP;
				
			}
			else
			{
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				//tokz.addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, MINUS_SIGN, tk, OPERATOR);
				tokz.v_addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, MINUS_SIGN, tk, MINUS_SIGN);
				return MINUS_SIGN;
			}
			
		case ASTERIC:
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			
			if( symbol == EQUAL )
			{
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				//tokz.addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, MUL_ASSIGN, tk, OPERATOR);
				tokz.v_addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, MUL_ASSIGN, tk, MUL_ASSIGN);
				return MUL_ASSIGN;
			}
			else
			{
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				//tokz.addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, ASTERIC, tk, OPERATOR);
				tokz.v_addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, ASTERIC, tk, ASTERIC);
				return ASTERIC;
			}
			
		case SLASH:
			//str.Format(_T("Entro Slash Symbol...%d  " ), symbol);
			//AfxMessageBox(str);
			
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			
			if( symbol == EQUAL )
			{
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				//tokz.addToken(g_fcurrentPos -1, g_fcurrentPos + 1, g_currentLine, DIV_ASSIGN, tk, OPERATOR);
				tokz.v_addToken(g_fcurrentPos -1, g_fcurrentPos + 1, g_currentLine, DIV_ASSIGN, tk, DIV_ASSIGN);
				return DIV_ASSIGN;
				
			}
			else
			{
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				//tokz.addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, SLASH, tk, OPERATOR);
				tokz.v_addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, SLASH, tk, SLASH);
				return SLASH;
			}
			
		case PERCENT:
			
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			
			if( symbol == EQUAL )
			{
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				//tokz.addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, MOD_ASSIGN, tk, OPERATOR);
				tokz.v_addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, MOD_ASSIGN, tk, MOD_ASSIGN);
				return MOD_ASSIGN;
				
			}
			else
			{
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				//tokz.addToken(g_fcurrentPos, g_fcurrentPos, g_currentLine, PERCENT, tk, OPERATOR);
				tokz.v_addToken(g_fcurrentPos, g_fcurrentPos, g_currentLine, PERCENT, tk, PERCENT);
				return PERCENT;
			}
		
		case COLON:
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
				
			if( symbol == COLON )
			{
				/*
				AfxMessageBox(_T("entro =="));
				str.Format(_T("Pos...%d  " ), g_fcurrentPos);
				AfxMessageBox(str);
				*/
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos + 1);
				//tokz.addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, SCOPE_OP, tk, OPERATOR);
				tokz.v_addToken(g_fcurrentPos -1, g_fcurrentPos +1, g_currentLine, SCOPE_OP, tk, SCOPE_OP);
				return SCOPE_OP;
			}
			else
			{
				/*
				AfxMessageBox(_T("entro ="));
				str.Format(_T("Pos...%d  " ), g_fcurrentPos);
				AfxMessageBox(str);
				*/
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos);
				//tokz.addToken(g_fcurrentPos-1, g_fcurrentPos, g_currentLine, COLON, tk, OPERATOR);
				tokz.v_addToken(g_fcurrentPos-1, g_fcurrentPos, g_currentLine, COLON, tk, COLON);
				return COLON;
			}
			
		
		case CARET:
			
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			
			tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
			//tokz.addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, XOR_BIT, tk, OPERATOR);
			tokz.v_addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, XOR_BIT, tk, XOR_BIT);
			return XOR_BIT;

		case EQUIVALENCY:
			
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			
			tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
			//tokz.addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, NOT_BIT, tk, OPERATOR);
			tokz.v_addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, NOT_BIT, tk, NOT_BIT);
			return NOT_BIT;

		case QUESTION:
			
			g_fcurrentPos = ftell(g_fp);
			symbol = _gettc(g_fp);
			
			tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
			//tokz.addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, QUESTION, tk, OPERATOR);
			tokz.v_addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, QUESTION, tk, QUESTION);
			return QUESTION;
			
		}
		
		
		
	}

//Check for punctuators
	if( isPunctuator(symbol) )
	{
		
		switch( symbol )
		{
					
			case SEMICOLON:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
			
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				//tokz.addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, SEMICOLON, tk, PUNCTUATOR);
				tokz.v_addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, SEMICOLON, tk, SEMICOLON);
				return SEMICOLON;
			
			case OPEN_PARENTHESIS:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
			
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				//tokz.addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, OPEN_PARENTHESIS, tk, PUNCTUATOR);
				tokz.v_addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, OPEN_PARENTHESIS, tk, OPEN_PARENTHESIS);
				return OPEN_PARENTHESIS;

			case CLOSE_PARENTHESIS:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
			
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				//tokz.addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, CLOSE_PARENTHESIS, tk, PUNCTUATOR);
				tokz.v_addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, CLOSE_PARENTHESIS, tk, CLOSE_PARENTHESIS);
				return CLOSE_PARENTHESIS;
			//Reserve for large identifiers
			/*
			case OPEN_BRACKET:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
							
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				//tokz.addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, OPEN_BRACKET, tk, PUNCTUATOR);
				tokz.v_addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, OPEN_BRACKET, tk, OPEN_BRACKET);
				return OPEN_BRACKET;
			*/
			case CLOSE_BRACKET:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
							
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				//tokz.addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, CLOSE_BRACKET, tk, PUNCTUATOR);
				tokz.v_addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, CLOSE_BRACKET, tk, CLOSE_BRACKET);
				return CLOSE_BRACKET;

			case OPEN_BRACE:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
			
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos);
				//tokz.addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, OPEN_BRACE, tk, PUNCTUATOR);
				tokz.v_addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, OPEN_BRACE, tk, OPEN_BRACE);
				return OPEN_BRACE;

			case CLOSE_BRACE:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
			
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				//tokz.addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, CLOSE_BRACE, tk, PUNCTUATOR);
				tokz.v_addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, CLOSE_BRACE, tk, CLOSE_BRACE);
				return CLOSE_BRACE;

			case COMMA:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
				//AfxMessageBox(_T("COMMA"));
				
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				//tokz.addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, COMMA, tk, PUNCTUATOR);
				tokz.v_addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, COMMA, tk, COMMA);
				return COMMA;

			/*
			case COLON:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
			
				
				tk = getTextFileRange(g_fcurrentPos -1, g_fcurrentPos);
				//tokz.addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, COLON, tk, PUNCTUATOR);
				tokz.v_addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, COLON, tk, COLON);
				return COLON;
			*/
			case PERIOD:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
							
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				//tokz.addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, PERIOD, tk, PUNCTUATOR);
				tokz.v_addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, PERIOD, tk, PERIOD);
				return PERIOD;


			case NUMBER_SIGN:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
			
				
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				//tokz.addToken(g_fcurrentPos -1, g_fcurrentPos, g_currentLine, NUMBER_SIGN, tk, PUNCTUATOR);
				tokz.v_addToken(g_fcurrentPos -1, g_fcurrentPos, g_currentLine, NUMBER_SIGN, tk, NUMBER_SIGN);
				return NUMBER_SIGN;


			case AT_SYMBOL:
				g_fcurrentPos = ftell(g_fp);
				symbol = _gettc(g_fp);
			
				
				tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
				//tokz.addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, AT_SYMBOL, tk, PUNCTUATOR);
				tokz.v_addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, AT_SYMBOL, tk, AT_SYMBOL);
				return AT_SYMBOL;

		
		}
		
				

		
	}


	//Double Quoted Strings
	if( symbol == DOBLE_QUOTATION )
	{
		//AfxMessageBox(_T("entro a string"));
		g_fcurrentPos = ftell(g_fp);
		pos1 = g_fcurrentPos - 1;
		
		//str.Format(_T("Pos del primer SLASH...%d  " ), g_fcurrentPos);
		//AfxMessageBox(str);
				
		symbol = _gettc(g_fp);
		
			/*
			str.Format(_T("symbol%d  " ), symbol);	
			pMainFrame->m_wndOutputTabView.AddMsg1(str);
			wsprintf(buffer, _T("Letra: %c"), symbol);
			AfxMessageBox(buffer);
			wsprintf(buffer, _T("ASCII: %d"), symbol);
			AfxMessageBox(buffer);
			*/
		
				
		while(symbol != DOBLE_QUOTATION && symbol != CARRIAGE_RETURN && symbol != _TEOF)
		{
			//symbol =  _gettc(g_fp);
			//str.Format(_T("While Symbol...%d  " ), symbol);
			//AfxMessageBox(str);
			/*
			if( symbol == DOBLE_QUOTATION )
			{
				CAipi_Error err;
				err.displayFileError(SYNTAX, LEX_ERROR, _T("Error"));
				return LEX_ERROR;
			}
			*/
			
			//Check for \n escape sequence
			if( symbol == BACK_SLASH )
			{
				//AfxMessageBox(_T("entro a slash"));
				
				fpos_t tempPos = ftell(g_fp);
				TCHAR escSymbol =  _gettc(g_fp);


				switch (escSymbol) 
				{
					//  Escape /a  alert
					case 97:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, ALERT, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, ALERT, tk, ALERT);
						break;
					
					//  Escape /b backspace
					case 98:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, BACKSPACE, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, BACKSPACE, tk, BACKSPACE);
						break;
					//  Escape /f forward feed page
					case 102:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, FORWARD_FEED, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, FORWARD_FEED, tk, FORWARD_FEED);
						break;
					//  Escape /n  new line	
					case 110:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, NEW_LINE, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, NEW_LINE, tk, NEW_LINE);
						break;
					//  Escape /r  carriage return
					case 114:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, CARRIAGE_RETURN, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, CARRIAGE_RETURN, tk, CARRIAGE_RETURN);
						break;
					//  Escape /t  horizontal tab
					case 116:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, HORIZONTAL_TAB, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, HORIZONTAL_TAB, tk, HORIZONTAL_TAB);
						break;
					//  Escape /v  vertical tab
					case 118:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, VERTICAL_TAB, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, VERTICAL_TAB, tk, VERTICAL_TAB);
						break;
					//  Symbol /'  single quotes
					case 27:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, SINGLE_QUOTATION, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, SINGLE_QUOTATION, tk, SINGLE_QUOTATION);
						break;
					
					//  Symbol /"  double quotes
					case 34:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, DOBLE_QUOTATION, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, DOBLE_QUOTATION, tk, DOBLE_QUOTATION);
						break;
					
						//  Symbol //  back slash
					case 92:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, BACK_SLASH, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, BACK_SLASH, tk, BACK_SLASH);
						break;
					
					//AfxMessageBox(_T("reconocio escape"));
				}//end switch

				if( escSymbol != 34 )
				{
					symbol = escSymbol;
				}

				
				
			
			}//end if

			symbol =  _gettc(g_fp);
			
		}//end while

		if( symbol == CARRIAGE_RETURN || symbol == _TEOF )
		{
				CAipi_Error err;
				err.displayFileError(LEXICAL, LEX_ERROR, _T("Close string symbol is missed") );
				return LEX_ERROR;
		}
		
			
		pos2 = ftell(g_fp);
		
		tk = getTextFileRange(pos1, pos2);
		
		//Eliminates doble quotation symbols
		tk.erase(0, 1);
		//AfxMessageBox(tk.data());
		int len = tk.length();
		tk.erase(len-1);
		//AfxMessageBox(tk.data());
		//tk = getTextFileRange(pos1 + 1, pos2 -1);
		
		if( tk == _T("STOP_ERROR") )
		{
			return STOP_ERROR;
		}

		++g_currentId_IForm;
		CAipi_Symbol symb;
		symb.addId_IntForm(tk, g_currentId_IForm);
		int repIdForm = symb.findId_IntForm(tk);
		if( repIdForm != NOT_FOUND )
		{
			tokz.v_addToken(pos1, pos2, g_currentLine, repIdForm, tk, LITERAL);	
		}
		else
		{
			tokz.v_addToken(pos1, pos2, g_currentLine, g_currentId_IForm, tk, LITERAL);
		
		}
		
		//AfxMessageBox(_T("agrego string final"));		
		
		return LITERAL;

		
	}


	//Single Quoted Strings
	if( symbol == SINGLE_QUOTATION )
	{
		//AfxMessageBox(_T("entro a string"));
		g_fcurrentPos = ftell(g_fp);
		pos1 = g_fcurrentPos - 1;
		
		//str.Format(_T("Pos del primer SLASH...%d  " ), g_fcurrentPos);
		//AfxMessageBox(str);
				
		symbol = _gettc(g_fp);
		
			/*
			str.Format(_T("symbol%d  " ), symbol);	
			pMainFrame->m_wndOutputTabView.AddMsg1(str);
			wsprintf(buffer, _T("Letra: %c"), symbol);
			AfxMessageBox(buffer);
			wsprintf(buffer, _T("ASCII: %d"), symbol);
			AfxMessageBox(buffer);
			*/
		
				
		while(symbol != SINGLE_QUOTATION && symbol != CARRIAGE_RETURN && symbol != _TEOF)
		{
			//symbol =  _gettc(g_fp);
			//str.Format(_T("While Symbol...%d  " ), symbol);
			//AfxMessageBox(str);
			/*
			if( symbol == DOBLE_QUOTATION )
			{
				CAipi_Error err;
				err.displayFileError(SYNTAX);
				return LEX_ERROR;
			}
			*/
			
			//Check for \n escape sequence
			if( symbol == BACK_SLASH )
			{
				//AfxMessageBox(_T("entro a slash"));
				
				fpos_t tempPos = ftell(g_fp);
				TCHAR escSymbol =  _gettc(g_fp);


				switch (escSymbol) 
				{
					//  Escape /a  alert
					case 97:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, ALERT, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, ALERT, tk, ALERT);
						break;
					
					//  Escape /b backspace
					case 98:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, BACKSPACE, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, BACKSPACE, tk, BACKSPACE);
						break;
					//  Escape /f forward feed page
					case 102:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, FORWARD_FEED, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, FORWARD_FEED, tk, FORWARD_FEED);
						break;
					//  Escape /n  new line	
					case 110:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, NEW_LINE, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, NEW_LINE, tk, NEW_LINE);

						break;
					//  Escape /r  carriage return
					case 114:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, CARRIAGE_RETURN, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, CARRIAGE_RETURN, tk, CARRIAGE_RETURN);
						break;
					//  Escape /t  horizontal tab
					case 116:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, HORIZONTAL_TAB, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, HORIZONTAL_TAB, tk, HORIZONTAL_TAB);
						break;
					//  Escape /v  vertical tab
					case 118:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, VERTICAL_TAB, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, VERTICAL_TAB, tk, VERTICAL_TAB);
						break;
					//  Symbol /'  single quotes
					case 27:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, SINGLE_QUOTATION, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, SINGLE_QUOTATION, tk, SINGLE_QUOTATION);
						break;
					
					//  Symbol /"  double quotes
					case 34:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, DOBLE_QUOTATION, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, DOBLE_QUOTATION, tk, DOBLE_QUOTATION);
						break;
					
						//  Symbol //  back slash
					case 92:
						tk = getTextFileRange(tempPos -1, tempPos + 1); 
						//tokz.addToken(tempPos -1, tempPos + 1, g_currentLine, BACK_SLASH, tk, LITERAL);
						tokz.v_addToken(tempPos -1, tempPos + 1, g_currentLine, BACK_SLASH, tk, BACK_SLASH);
						break;
					
					//AfxMessageBox(_T("reconocio escape"));
				}//end switch

				if( escSymbol != 34 )
				{
					symbol = escSymbol;
				}

				
				
			
			}//end if

			symbol =  _gettc(g_fp);
			
		}//end while

		if( symbol == CARRIAGE_RETURN || symbol == _TEOF )
		{
				CAipi_Error err;
				err.displayFileError(LEXICAL, LEX_ERROR, _T("Close string symbol is missed") );
				return LEX_ERROR;
		}
		
			
		pos2 = ftell(g_fp);
		
		tk = getTextFileRange(pos1, pos2);
		//Eliminates single quotation symbols
		//tk = getTextFileRange(pos1 + 1, pos2 -1);
		
		
		if( tk == _T("STOP_ERROR") )
		{
			return STOP_ERROR;
		}
		
		tk = formatTkNameOpt(tk);
		
		++g_currentId_IForm;
		CAipi_Symbol symb;
		symb.addId_IntForm(tk, g_currentId_IForm);
		int repIdForm = symb.findId_IntForm(tk);
		if( repIdForm != NOT_FOUND )
		{
			tokz.v_addToken(pos1, pos2, g_currentLine, repIdForm, tk, LITERAL);
		}
		else
		{
			tokz.v_addToken(pos1, pos2, g_currentLine, g_currentId_IForm, tk, LITERAL);
		}
		
		//AfxMessageBox(_T("agrego string final"));		
		
		return LITERAL;

		
	}





	//Aipi Variables
	if( symbol == DOLLAR )
	{
		//AfxMessageBox(_T("entro a string"));
		g_fcurrentPos = ftell(g_fp);
		pos1 = g_fcurrentPos - 1;
		
		//str.Format(_T("Pos del primer SLASH...%d  " ), g_fcurrentPos);
		//AfxMessageBox(str);
				
		symbol = _gettc(g_fp);

		//Skip over white space and newline
		while( symbol == SPACE || symbol == CARRIAGE_RETURN || symbol == NEW_LINE || symbol == HORIZONTAL_TAB || symbol == VERTICAL_TAB )
		{
			if( symbol == _TEOF )
			{
				return _TEOF;
			}
			
			
			if( symbol == NEW_LINE )
			{
				++g_currentLine;

				//AfxMessageBox(_T("Aipi Variable LINE"));
				//str.Format(_T("Line...%d  " ), g_currentLine);
				//AfxMessageBox(str);
						
			}
		
		

			symbol =  _gettc(g_fp);
		
		}
			
		/*
			str.Format(_T("symbol%d  " ), symbol);	
			pMainFrame->m_wndOutputTabView.AddMsg1(str);
			wsprintf(buffer, _T("Letra: %c"), symbol);
			AfxMessageBox(buffer);
			wsprintf(buffer, _T("ASCII: %d"), symbol);
			AfxMessageBox(buffer);
		*/
		
				
		while(symbol != DOLLAR && symbol != CARRIAGE_RETURN && symbol != _TEOF )
		{
			//symbol =  _gettc(g_fp);
			//str.Format(_T("While Symbol...%d  " ), symbol);
			//AfxMessageBox(str);
			/*
			if( symbol == DOBLE_QUOTATION )
			{
				CAipi_Error err;
				err.displayFileError(SYNTAX);
				return LEX_ERROR;
			}
			*/
			
			symbol =  _gettc(g_fp);
			
		}//end while

		if( symbol == CARRIAGE_RETURN || symbol == _TEOF )
		{
				CAipi_Error err;
				err.displayFileError(LEXICAL, LEX_ERROR, _T("Close variable symbol is missed") );
				return LEX_ERROR;
		}
		
			
		pos2 = ftell(g_fp);
		
		tk = getTextFileRange(pos1, pos2);
		//Eliminates dollar symbols
		//tk = getTextFileRange(pos1 + 1, pos2 -1);

		if( tk == _T("STOP_ERROR") )
		{
			return STOP_ERROR;
		}
		
		tk = formatTkNameOpt(tk);
		
		++g_currentId_IForm;
		CAipi_Symbol symb;
		symb.addId_IntForm(tk, g_currentId_IForm);
		int repIdForm = symb.findId_IntForm(tk);
		if( repIdForm != NOT_FOUND )
		{
			tokz.v_addToken(pos1, pos2, g_currentLine, repIdForm, tk, AIPI_VAR);	
		}
		else
		{
			tokz.v_addToken(pos1, pos2, g_currentLine, g_currentId_IForm, tk, AIPI_VAR);
		}
		
		//AfxMessageBox(_T("agrego string final"));		
		
		return AIPI_VAR;

		
	}





		//Numbers (Natural and Real )
	if( isDigit(symbol)  )
	{
		//AfxMessageBox(_T("entro a digit"));

		g_fcurrentPos = ftell(g_fp);
		pos1 = g_fcurrentPos - 1;		
		
		g_currentDigit_Type = NAT_NUMBER;
		int countPeriod = 0;
	
		while( isDigit(symbol) || symbol == PERIOD && symbol != _TEOF )
		{
			
			//str.Format(_T("Pos en Nat Number...%d  " ), g_fcurrentPos);
			//AfxMessageBox(str);
			//wsprintf(buffer, _T("Number: %c"), symbol);
			//AfxMessageBox(buffer);
			//wsprintf(buffer, _T("ASCII: %d"), symbol);
			//AfxMessageBox(buffer);
			

			if( symbol == PERIOD )
			{
				g_currentDigit_Type = REAL_NUMBER;
				++countPeriod;
			}
			if( symbol == _TEOF )
			{
				//AfxMessageBox(_T("_TEOF"));
				pos2 = ++g_fcurrentPos;
				fsetpos(g_fp, &g_fcurrentPos );
			}

			symbol = _gettc(g_fp);
			//str.Format(_T("Pos en Nat Number...%d  " ), g_fcurrentPos);
			//AfxMessageBox(str);
			//wsprintf(buffer, _T("After Number: %c"), symbol);
			//AfxMessageBox(buffer);
			//wsprintf(buffer, _T("ASCII: %d"), symbol);
			//AfxMessageBox(buffer);
							
			
				
			
		}

		if( countPeriod > 1 )
		{
			CAipi_Error err;
			err.displayFileError(LEXICAL, LEX_ERROR, _T("Period symbol is repeated")  );
			return LEX_ERROR;
		}
		
		g_fcurrentPos = ftell(g_fp);
		pos2 = --g_fcurrentPos;
		
		if( symbol == NEW_LINE )
		{
			pos2 = --g_fcurrentPos;
			++g_currentLine;

			//AfxMessageBox(_T("Numbers LINE"));
			//str.Format(_T("Line...%d  " ), g_currentLine);
			//AfxMessageBox(str);
						
			//AfxMessageBox(_T("Detecto new line"));
		}

		tk = getTextFileRange(pos1, pos2);
		if( tk == _T("STOP_ERROR") )
		{
			return STOP_ERROR;
		}

		double g_currentId_IForm = _tcstod(tk.data(), NULL);
		tokz.v_addToken(pos1, pos2, g_currentLine, g_currentId_IForm, tk, DIGIT);
		//AfxMessageBox(_T("DIGITO"));
		return DIGIT;
	}






	//Aipi Identifier with spaces
	if( symbol == OPEN_BRACKET )
	{
		//AfxMessageBox(_T("entro a Bracket"));
		g_fcurrentPos = ftell(g_fp);
		pos1 = g_fcurrentPos - 1;
		
		//str.Format(_T("current Pos ...%d  " ), g_fcurrentPos);
		//AfxMessageBox(str);
				
		symbol = _gettc(g_fp);
		
		//Skip over white space and newline
		while( symbol == SPACE || symbol == CARRIAGE_RETURN || symbol == NEW_LINE || symbol == HORIZONTAL_TAB || symbol == VERTICAL_TAB )
		{
			if( symbol == _TEOF )
			{
				return _TEOF;
			}
			
			
			if( symbol == NEW_LINE )
			{
				++g_currentLine;
				//AfxMessageBox(_T("Complex Comment LINE"));
				//str.Format(_T("Aipi Identifier LINE...%d  " ), g_currentLine);
				//AfxMessageBox(str);
						
			}
		
		symbol =  _gettc(g_fp);
		
		}
		/*	
		str.Format(_T("symbol%d  " ), symbol);	
		pMainFrame->m_wndOutputTabView.AddMsg1(str);
		wsprintf(buffer, _T("Letra: %c"), symbol);
		AfxMessageBox(buffer);
		wsprintf(buffer, _T("ASCII: %d"), symbol);
		AfxMessageBox(buffer);
		*/	

		//Check for array 
		if( isDigit(symbol) || symbol == CLOSE_BRACKET  && symbol != _TEOF )
		{
			//AfxMessageBox(_T("Detecto Digit"));
			g_fcurrentPos = pos1+1;
			tk = getTextFileRange(g_fcurrentPos - 1, g_fcurrentPos);
			//tokz.addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, OPEN_BRACKET, tk, PUNCTUATOR);
			tokz.v_addToken(g_fcurrentPos - 1, g_fcurrentPos, g_currentLine, OPEN_BRACKET, tk, PUNCTUATOR);
			//AfxMessageBox(_T("OPEN BRACKET"));
			return OPEN_BRACKET;
		}
				
		while(symbol != CLOSE_BRACKET && symbol != CARRIAGE_RETURN && symbol != _TEOF )
		{
			symbol =  _gettc(g_fp);
			//str.Format(_T("While Symbol...%d  " ), symbol);
			//AfxMessageBox(str);
			/*
			if( symbol == DOBLE_QUOTATION )
			{
				CAipi_Error err;
				err.displayFileError(SYNTAX);
				return LEX_ERROR;
			}
			*/
			
					
		}//end while

		if( symbol == CARRIAGE_RETURN || symbol == _TEOF)
		{
				CAipi_Error err;
				err.displayFileError(LEXICAL, LEX_ERROR, _T("Close identifier symbol is missed") );
				return LEX_ERROR;
		}
		
			
		g_fcurrentPos = ftell(g_fp);
		pos2 = g_fcurrentPos;
		
		tk = getTextFileRange(pos1, pos2);
		tk = formatTkNameOpt(tk);
		
		if( tk == _T("STOP_ERROR") )
		{
			return STOP_ERROR;
		}
		
		++g_currentId_IForm;
		CAipi_Symbol symb;
		symb.addId_IntForm(tk, g_currentId_IForm);
		int repIdForm = symb.findId_IntForm(tk);
		if( repIdForm != NOT_FOUND )
		{
			tokz.v_addToken(pos1, pos2, g_currentLine, repIdForm, tk, IDENTIFIER);
		}
		else
		{
			tokz.v_addToken(pos1, pos2, g_currentLine, g_currentId_IForm, tk, IDENTIFIER);
		
		}
		
		//AfxMessageBox(_T("agrego string final"));		
		
		return IDENTIFIER;

		
	}






	//Identifiers and KeyWords
	if( isAlphabetic(symbol) || symbol == UNDERSCORE )
	{
		g_fcurrentPos = ftell(g_fp);
		pos1 = g_fcurrentPos - 1;
		
		//str.Format(_T("Pos 1 en Identifier...%d  " ), pos1);
		//AfxMessageBox(str);
		
		while( isAlphaNumeric(symbol) && symbol != _TEOF)
		{
			//AfxMessageBox(_T("While AlphaNumeric"));
			symbol = _gettc(g_fp);
			//g_fcurrentPos = ftell(g_fp);
			//str.Format(_T("Pos en Identifier...%d  " ), g_fcurrentPos);
			//AfxMessageBox(str);

			//str.Format(_T("Id Symbol...%d  " ), symbol);
			//AfxMessageBox(str);
			
		}
	
		g_fcurrentPos = ftell(g_fp);
		pos2 = --g_fcurrentPos;
		//str.Format(_T("Pos 2 en Identifier...%d  " ), pos2);
		//AfxMessageBox(str);
		
		if( symbol == NEW_LINE )
		{
			pos2 = --g_fcurrentPos;
			/*
			++g_currentLine;
			AfxMessageBox(_T("Alpha Identifier LINE"));
			str.Format(_T("Line...%d  " ), g_currentLine);
			AfxMessageBox(str);
			*/			
			///AfxMessageBox(_T("Detecto new line"));
		}

		
		if( symbol == _TEOF )
		{
			//AfxMessageBox(_T("_TEOF"));
			pos2 = ++g_fcurrentPos;
			fsetpos(g_fp, &g_fcurrentPos );
		}
		
	
		tk = getTextFileRange(pos1, pos2);

		//symbol =  _gettc(g_fp);

		if( tk == _T("STOP_ERROR") )
		{
			return STOP_ERROR;
		}

		CAipi_Symbol symb;
		int keyword = symb.findKeyWord(tk);
		if( keyword != NOT_FOUND )
		{
			//AfxMessageBox(_T("KEYWORD"));
			tokz.v_addToken(pos1, pos2, g_currentLine, keyword, tk, keyword);
			return keyword;
		}
		else
		{
			++g_currentId_IForm;
			symb.addId_IntForm(tk, g_currentId_IForm);
			int repIdForm = symb.findId_IntForm(tk);
			if( repIdForm != NOT_FOUND )
			{
				tokz.v_addToken(pos1, pos2, g_currentLine, repIdForm, tk, IDENTIFIER);	
			}
			else
			{
				tokz.v_addToken(pos1, pos2, g_currentLine, g_currentId_IForm, tk, IDENTIFIER);
			}
			
			//str.Format(_T("Char Last Pos...%d  " ), pos2);
			//AfxMessageBox(str);
			

			return IDENTIFIER;
		}

		
	}

		
	if (symbol == _TEOF )
	{
		//AfxMessageBox(_T("Fin del archivo"));
		return _TEOF;
		
	}


	/*
	str.Format(_T("symbol%d  " ), symbol);	
	pMainFrame->m_wndOutputTabView.AddMsg1(str);
	wsprintf(buffer, _T("Letra: %c"), symbol);
	AfxMessageBox(buffer);
	wsprintf(buffer, _T("ASCII: %d"), symbol);
	AfxMessageBox(buffer);
	
	*/
	
	fsetpos(g_fp, &g_fcurrentPos );

return UNDEFINE;

}


//////////////////////////////////////////////////////////
//// End addTokenizerFile //////
//////////////////////////////////////////////////////////







unsigned long CAipi_Lexer::getGUIDocumentLen()
{
	CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
	CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
	CScintillaView* pView = (CScintillaView*) pChild->GetActiveView();
	ASSERT(pView);
	CScintillaCtrl& rCtrl = pView->GetCtrl();

	int len = rCtrl.GetLength();
	m_guiDocumentLen = len;

	/*
	CString str;
	str.Format(_T("Document Len...%d  " ), len);
	AfxMessageBox(str);
	*/
	return len;

}

unsigned long CAipi_Lexer::getFileDocumentLen(CString fname)
{
	const  TCHAR* cFileName = (LPCTSTR) fname; 
		
	if( (g_fp = _tfopen(cFileName, _T("r") )) == NULL )
	{
		CAipi_Error err;
		err.displayFileError(FILE_READ, STOP_ERROR, _T("Unable to read file") );
		return AIPI_ERROR;	
	}
		
	//Find end positon of file
	fseek( g_fp, 0L, SEEK_END);
	long fendPos = ftell(g_fp);
	m_fileDocumentLen = fendPos;

	/*
	CString str;
	str.Format(_T("Document Len...%d  " ), len);
	AfxMessageBox(str);
	*/
	return m_fileDocumentLen;

}



tstring CAipi_Lexer::getText(int len)
{
	TCHAR ch[1000];
		
	CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
	CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
	CScintillaView* pView = (CScintillaView*) pChild->GetActiveView();
	ASSERT(pView);
	CScintillaCtrl& rCtrl = pView->GetCtrl();
		
	
	int l = rCtrl.GetText(len, ch);
		
	//AfxMessageBox(ch);
			
return ch;		
}


int CAipi_Lexer::getCharAt(unsigned long pos)
{
	
	CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
	CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
	CScintillaView* pView = (CScintillaView*) pChild->GetActiveView();
	ASSERT(pView);
	CScintillaCtrl& rCtrl = pView->GetCtrl();

	int c = rCtrl.GetCharAt(pos);

	/*
	CString str;
	str.Format(_T("Char...%d  " ), c);
	AfxMessageBox(str);
	*/

return c;
}



tstring CAipi_Lexer::getTextRange(int pos1, int pos2)
{
	
	char ch[MAX_TK_LEN];
		
		
	CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
	CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
	CScintillaView* pView = (CScintillaView*) pChild->GetActiveView();
	ASSERT(pView);
	CScintillaCtrl& rCtrl = pView->GetCtrl();
	
	//Get document length
	int len = rCtrl.GetLength();
	tstring sToken = _T(""); 	

	if( pos1 < len && pos2 <= len )
	{
		CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		
		
		//Get the data from the control
		TextRange tr;

		tr.chrg.cpMin = pos1;
		tr.chrg.cpMax = pos2;
		tr.lpstrText = ch;
		rCtrl.GetTextRange(&tr);

		//CString strId;
		//strId = (LPSTR)ch;
		m_sToken = (LPSTR)ch;
		
		if( (pos2 - pos1) > MAX_TK_LEN )
		{
			//AfxMessageBox(_T("Text Range Error"));
			CAipi_Error err;
			err.displayGUIError(OVER_TK_LENGTH, LEX_ERROR, _T("The identifier..." + m_sToken + " is to long. Reduce the number of characters used in the identifier name.") );
			err.displayGUIError(DEBUG_STOP, STOP_ERROR, _T("The AIPI debugging process was unable to finish.") );
			err.errorMark(g_currentLine);
			return _T("STOP_ERROR");
		}
		else
		{		
			//AfxMessageBox(str);
			//sId = ((LPCTSTR)strId);
			//AfxMessageBox(sId.data());
			sToken = ((LPCTSTR)m_sToken);
			//AfxMessageBox(sToken.data());


		}
	}
	else
	{
		CAipi_Error err;
		err.displayGUIError(OVER_TK_LENGTH, LEX_ERROR, _T("Position parameters are incorrect") );
		err.displayGUIError(DEBUG_STOP, STOP_ERROR, _T("The AIPI debugging process was unable to finish.") );
		err.errorMark(g_currentLine);
		//exit(1);	
		return _T("STOP_ERROR");	

	}

	//AfxMessageBox(sToken.data());


    //AfxMessageBox(_T("Salio del getTextRange"));
return sToken; 
}






tstring CAipi_Lexer::getTextFileRange(fpos_t pos1, fpos_t pos2)
{
	/*
	AfxMessageBox(_T("GET TEXT FILE RANGE"));
	CString str;
	str.Format(_T("pos1...%d  " ), pos1);
	AfxMessageBox(str);
	str.Format(_T("pos2...%d  " ), pos2);
	AfxMessageBox(str);
	*/	
	
	TCHAR buffer[MAX_TK_LEN];
	TCHAR symbol;
	tstring tk = _T("");
	
	fpos_t pos = pos1;
	fsetpos(g_fp, &pos1);

	
	
	if( pos1 > pos2 )
	{
		CAipi_Error err;
		err.displayFileError(OVER_TK_LENGTH, LEX_ERROR, _T("Position parameters are incorrect") );
		err.displayFileError(DEBUG_STOP, STOP_ERROR, _T("The AIPI debugging process was unable to finish.") );
		err.errorMark(g_currentLine);
		//exit(1);
		return _T("STOP_ERROR");
		
	}


	while( pos < pos2  )
	{
		
		++pos;

		symbol =  _gettc(g_fp);
		wsprintf(buffer, _T("%c"), symbol);
		tk += buffer;
		
		/*
		str.Format(_T("Pos...%d  " ), pos);
		AfxMessageBox(str);
		//str.Format(_T("Space Pos...%d  " ), g_fcurrentPos);
		//AfxMessageBox(str);
		wsprintf(buffer, _T("Letra: %c"), symbol);
		AfxMessageBox(buffer);
		wsprintf(buffer, _T("ASCII: %d"), symbol);
		AfxMessageBox(buffer);
		*/
		if( symbol == NEW_LINE )
		{
			++pos;
			++g_currentLine;
			//wsprintf(buffer, _T("Letra: %c"), symbol);
			//AfxMessageBox(buffer);
			continue;
		}
	

		
	}

	m_sToken = tk.data();

	if( (pos2 - pos1) > MAX_TK_LEN )
	{
		CAipi_Error err;
		err.displayFileError(OVER_TK_LENGTH, LEX_ERROR, _T("The identifier..." + m_sToken + " is to long. Reduce the number of characters used in the identifier name.") );
		err.displayFileError(DEBUG_STOP, STOP_ERROR, _T("The AIPI debugging process was unable to finish.") );
		err.errorMark(g_currentLine);
		//exit(1);
		return _T("STOP_ERROR");		
	}

	//AfxMessageBox(tk.data());

return tk;

}


//Gives special format to tokens names with spaces 
tstring CAipi_Lexer::formatTkNameOpt(tstring name)
{
	/*
	CString str;
	int b = name.rfind(_T("'"));
	str.Format(_T("Pos Single Q... %d"), b);
	AfxMessageBox(str);	
	int len = name.length();
	str.Format(_T("Len... %d"), len);
	AfxMessageBox(str);	
	
	*/
		
	int lpos = name.rfind(_T(" "));
	//str.Format(_T("lpos... %d"), lpos);
	//AfxMessageBox(str);	

	int len = name.length();
	//str.Format(_T("Len... %d"), len);
	//AfxMessageBox(str);



	while( lpos < tstring::npos )
	{
		lpos = name.rfind(_T(" "));
		//str.Format(_T("find space pos... %d"), lpos);
		//AfxMessageBox(str);	

		len = name.length();
		//str.Format(_T("Len... %d"), len);
		//AfxMessageBox(str);
	
		//AfxMessageBox(name.data());
		
		if( lpos == len - 2 )
		{
			if( lpos < tstring::npos )
			{
				name.erase(lpos, 1);
			}
		
		}
		else
		{
			break;
		}
	}


	//CPerfTimer t;
	//t.Start();
	
	int	rpos = 0;
	int rprevPos = 0;		
	while( rpos < tstring::npos )
	{
		rprevPos = rpos;
		rpos = name.find(_T(" "));
		
				
		if( rpos > rprevPos && rpos != 1)
		{
			name.insert(rpos, _T("_") );
			rpos++;
			continue;
			//AfxMessageBox(_T("Append"));

		}
		

		if( rpos < tstring::npos )
		{
		
			name.erase(rpos, 1);
		}

		
			
		CString str;
		//str.Format(_T("Current Pos... %d"), rpos);
		//AfxMessageBox(str);
		//AfxMessageBox(name.data());
		
		
	}
	

	
	//Erase terminal symbols
	name.erase(0, 1);
	//AfxMessageBox(name.data());
	len = name.length();
	name.erase(len-1);
	//AfxMessageBox(name.data());
	
	
	//StopTimer(t, _T("Format Rule Name OPTIMIZED...."));
	//AfxMessageBox(_T("Format Data"));
	//AfxMessageBox(name.data());
return name;
}



bool CAipi_Lexer::isDigit(int c)
{
	
	if( c >= 48 && c <= 57 )
	{
		return TRUE;
	}
	
	return FALSE;

}



bool CAipi_Lexer::isAlphabetic(int c)
{
	
	if( ( c >= 65  && c <= 90 ) || ( c >= 97 && c <= 122 ) )
	{	
		return TRUE;
	}
	
	return FALSE;

}

	
bool CAipi_Lexer::isAlphaNumeric(int c)
{
	if( isAlphabetic( c ) || isDigit( c ) || c == 95 )
	{
		return TRUE;
	}
		
	return FALSE;
}


bool CAipi_Lexer::isUnicodeAlphabetic(int c)
{
	if( c >= 129 && c <= 168 )
	{
		return TRUE;
	}
	
	return FALSE;


}

bool CAipi_Lexer::isUnicodeSymbol(int c)
{
	if( c >= 169 && c <= 255 )
	{
		return TRUE;
	}
		
	return FALSE;
	

}


bool CAipi_Lexer::isPunctuator(int c)
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
		|| c == AT_SYMBOL 
	   )
	{
		return TRUE;
	}
		
	return FALSE;
	

}


bool CAipi_Lexer::isOperator(int c)
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


bool CAipi_Lexer::isTypeName(int c)
{
	if(		c == C_VOID 
		||	c == C_CHAR
		||	c == C_SHORT
		||	c == C_INT
		||	c == C_LONG
		||	c == C_FLOAT
		||	c == C_DOUBLE
		||	c == C_SIGNED
		||	c == C_UNSIGNED
		
	   )
	{
		return TRUE;
	}
	
	return FALSE;

}


