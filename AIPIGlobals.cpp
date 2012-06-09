//------------------------------------------------------------------------------
// File: AIPIGlobals.h
//
// Desc: 
//
// Copyright (c) MEAP.  All rights reserved.
//------------------------------------------------------------------------------


#include "stdafx.h"
#include ".\DataFileCSV\CDataFile.h"




//Gets the user language primary ID for international recognition   
LANGID langUser, langSystem, languagePrimaryID;
LCID   LCIDUser, LCIDSystem, languageLCID;  


//Id for database recognition with OLE DB
int			g_iDBProvider;
CString		g_sDBName;
CString		g_sDBUser;
CString		g_sDBPassword;
CString		g_sDBDNS;

//Id for applications skin style
int	g_iSkinType;

//Id for application workspace interface store option
int  g_iWorkspaceStore;
CString		g_sCurrentDir;
HTREEITEM hTProjectRoot;
HTREEITEM hTProjectRule;
HTREEITEM hTProjectFunction;
HTREEITEM hTProjectQuery;
HTREEITEM hTProjectVariable;
HTREEITEM hTProjectClass;


//File name for Decision Tree
CDataFile g_df;




//GridCtrl manipulation
int g_iRow;
int g_iColumn;
int g_iFixRow;
int g_iFixColumn;

//Command Window input
CString	g_currentCmdInput;

//CImageList creation flag for ClistOptionCtrl
bool g_ImageListFlag;


//External constants for AIPI RETE Network
int		g_currentTimeTag;
int		g_currentLHS;
int		g_currentRHS;
int		g_currentWM;

int		g_currentAM;
int		g_currentBM;
int		g_currentJNode;
int		g_currentTK;
long    g_currentFiredPM;

int		g_maxCRCicles; //Max cicles for conflict resolution test
int     g_CRStrategy; //Conflict resolution strategy	
bool    g_includeDirective;  //Flag for include files


//AIPI Interpreter global variables
int			g_dataSource;
int			g_TkzCurrentIndex;  //This is the tokenizer index  for structure CAipi_Tokenizer
int			g_TkzIndex1;
int         g_TkzIndex2;
CString		g_currentFile;
int			g_currentLine;
long		g_currentPos;
long		g_currentLookahead;
long		g_currentDocEndPos;
double		g_currentId_IForm;
int			g_currentDataCateg;
int			g_currentVarLoc;
int			g_currentParserClass;
bool		g_bStopFlag;
bool		g_bExecuteFlag;  


//Interpreter Errors
int			g_LexError;
int			g_SintaxError;
int			g_SemantError;
int			g_WarningError;
int			g_StopError;
int			g_QuestionError;
int			g_InfoError;


int			g_currentDigit_Type;

fpos_t		g_fcurrentPos;
FILE*		g_fp;
CString		g_fText;
CString		g_findText;



//AIPI Project settings
CString				g_projectName;
CString				g_projectAuthor;
CString				g_projectDesc;
CString				g_projectRoot;
CString				g_projectDate;
CString				g_projectInference;
CString				g_projectResource[4];



// External flag for notification message CNotificationModified
bool g_bNotificationModified; 
