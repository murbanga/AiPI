// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__D8B6B507_1871_4621_AE09_4BA4D5E5A19C__INCLUDED_)
#define AFX_STDAFX_H__D8B6B507_1871_4621_AE09_4BA4D5E5A19C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable:4786)
#pragma warning(disable:4005)
#pragma warning (disable:4018)
#pragma warning (disable:4284)
#pragma warning(disable: 4503)

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#define WM_CCOMMAND WM_USER + 1 //For ConsoleCombo in CCommandDlgBar

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxtempl.h>		// MFC template support
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
//For the CAIPITreeApp
#include <afxadv.h>         // Support to MRU Files in File Menu
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxrich.h>		// MFC rich edit classes
#include <afxpriv.h>		// ATL USES_CONVERSION macros enable

//#include "AIPIGlobalFunctions.h"
#include "AIPIGlobals.h"

//TCHAR STL
#include ".\tstl.h"

//#include <map>
//Inference engine
//typedef std::map<std::tstring, std::tstring> g_mWM;
//g_mWM	gmWM;

//Process timer
#include ".\PerfTimer\PerfTimer.h"


//Pull in support for Scintilla
#include "scintilla\include\platform.h"
#include "scintilla\include\scintilla.h"
#include "scintilla\include\SciLexer.h"

//Init GDIPlus library
#include ".\ImplementationGDIPLUS\GdiPlus.h"
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")



//Customization Manager
//#define OX_CUSTOMIZE_TOOLBARS

#define OX_CUSTOMIZE_COMMANDS
#define OX_CUSTOMIZE_SHORTKEYS
#define OX_CUSTOMIZE_WORKSPACE_STATE
#define OX_CUSTOMIZE_INSTANCE_MANAGER
#define OX_CUSTOMIZE_TRAYICON
#define OX_CUSTOMIZE_SPLASHWINDOW
#define OX_CUSTOMIZE_BACKGROUND
#define OX_CUSTOMIZE_COOLCONTROLS
#define OX_CUSTOMIZE_INTELLIMOUSE
#define OX_CUSTOMIZE_CAPTION
#define OX_CUSTOMIZE_TABBEDMDI


//SQLQuery access to ATL/OLE DB COM technology  

#define _ATL_APARTMENT_THREADED
#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
class CQueryModule : public CComModule
{
public:
	LONG Unlock();
	LONG Lock();
	LPCTSTR FindOneOf(LPCTSTR p1, LPCTSTR p2);
	DWORD dwThreadID;
};
extern CQueryModule _Module;

#include <atlcom.h>
#include <atldbcli.h>
#include <atlconv.h>
#include <atldbsch.h>
#include <OLEDBERR.h>


//includes for CAIPITreeView and CAIPITreeDoc
//
#include <dlgs.h>
#include <string.h>
#include <direct.h>
#include <io.h>

#include ".\TreeEditorCtrl\TreeType.h"
#include ".\TreeEditorCtrl\EditTreeCtrl.h"
#define ARRAY_SIZE(ARRAY) (sizeof(ARRAY) / sizeof(*ARRAY))

// Comment/Uncomment to Activate/Deactivate my traces
//#define MY_TRACE_ON

#ifdef MY_TRACE_ON
	#define MyTRACE(VAR) TRACE(_T("%s(%d) : %s\n"), __FILE__, __LINE__, VAR)
#else
	#define MyTRACE
#endif

#define BUFF_SIZE	120


//Ultimate Toolbox Asserts
#include "OXAdvancedAssert.h"

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__D8B6B507_1871_4621_AE09_4BA4D5E5A19C__INCLUDED_)
