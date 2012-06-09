# Microsoft Developer Studio Project File - Name="AIPI" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=AIPI - Win32 Unicode_Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AIPI.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AIPI.mak" CFG="AIPI - Win32 Unicode_Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AIPI - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "AIPI - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "AIPI - Win32 Unicode_Debug" (based on "Win32 (x86) Application")
!MESSAGE "AIPI - Win32 Unicode_Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AIPI - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "UTInclude" /I "DXBaseClasses" /I "DXInclude" /I "Common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D _WIN32_WINNT=0x400 /D "TARGET_WMF9" /Yu"stdafx.h" /FD /Zm400 /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x440a /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x440a /i "UTInclude" /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 strmiids.lib common\wmvcore.lib msvcrt.lib shlwapi.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"libcmt.lib"

!ELSEIF  "$(CFG)" == "AIPI - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "UTInclude" /I "DXBaseClasses" /I "DXInclude" /I "Common" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D _WIN32_WINNT=0x400 /D "TARGET_WMF9" /Yu"stdafx.h" /FD /Zm400 /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x440a /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x440a /i "UTInclude" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 strmiids.lib common\wmvcore.lib msvcrtd.lib shlwapi.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "AIPI - Win32 Unicode_Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "AIPI___Win32_Unicode_Debug"
# PROP BASE Intermediate_Dir "AIPI___Win32_Unicode_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "AIPI___Win32_Unicode_Debug"
# PROP Intermediate_Dir "AIPI___Win32_Unicode_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "UTInclude" /I "DXBaseClasses" /I "DXInclude" /I "Common" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /D "UNICODE" /D _WIN32_WINNT=0x400 /D "TARGET_WMF9" /Yu"stdafx.h" /FD /Zm400 /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x440a /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x440a /i "UTInclude" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 strmiids.lib common\wmvcore.lib msvcrtd.lib shlwapi.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /nodefaultlib:"msvcrt.lib gdiplus.lib" /pdbtype:sept

!ELSEIF  "$(CFG)" == "AIPI - Win32 Unicode_Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "AIPI___Win32_Unicode_Release"
# PROP BASE Intermediate_Dir "AIPI___Win32_Unicode_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "AIPI___Win32_Unicode_Release"
# PROP Intermediate_Dir "AIPI___Win32_Unicode_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "UTInclude" /I "DXBaseClasses" /I "DXInclude" /I "Common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /D "UNICODE" /D _WIN32_WINNT=0x400 /D "TARGET_WMF9" /Yu"stdafx.h" /FD /Zm400 /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x440a /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x440a /i "UTInclude" /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 strmiids.lib common\wmvcore.lib msvcrt.lib shlwapi.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386 /nodefaultlib:"libcmt.lib"

!ENDIF 

# Begin Target

# Name "AIPI - Win32 Release"
# Name "AIPI - Win32 Debug"
# Name "AIPI - Win32 Unicode_Debug"
# Name "AIPI - Win32 Unicode_Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AIPI.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPI.rc
# End Source File
# Begin Source File

SOURCE=.\Aipi_CParser.cpp
# End Source File
# Begin Source File

SOURCE=.\Aipi_Emitter.cpp
# End Source File
# Begin Source File

SOURCE=.\Aipi_Error.cpp
# End Source File
# Begin Source File

SOURCE=.\Aipi_ExpParser.cpp
# End Source File
# Begin Source File

SOURCE=.\Aipi_ExpParserFile.cpp
# End Source File
# Begin Source File

SOURCE=.\Aipi_ExpParserFileGlobal.cpp
# End Source File
# Begin Source File

SOURCE=.\Aipi_ExpParserGUI.cpp
# End Source File
# Begin Source File

SOURCE=.\Aipi_ExpParserGUIGlobal.cpp
# End Source File
# Begin Source File

SOURCE=.\Aipi_ExpParserRT.cpp
# End Source File
# Begin Source File

SOURCE=.\Aipi_Init.cpp
# End Source File
# Begin Source File

SOURCE=.\Aipi_Lexer.cpp
# End Source File
# Begin Source File

SOURCE=.\Aipi_Main.cpp
# End Source File
# Begin Source File

SOURCE=.\Aipi_Parser.cpp
# End Source File
# Begin Source File

SOURCE=.\Aipi_ParserFile.cpp
# End Source File
# Begin Source File

SOURCE=.\Aipi_ParserGUI.cpp
# End Source File
# Begin Source File

SOURCE=.\Aipi_ScriptCode.cpp
# End Source File
# Begin Source File

SOURCE=.\Aipi_ScriptLocation.cpp
# End Source File
# Begin Source File

SOURCE=.\Aipi_STableClass.cpp
# End Source File
# Begin Source File

SOURCE=.\Aipi_STableGlobalLiteral.cpp
# End Source File
# Begin Source File

SOURCE=.\Aipi_STableGlobalNumeric.cpp
# End Source File
# Begin Source File

SOURCE=.\Aipi_STableLiteral.cpp
# End Source File
# Begin Source File

SOURCE=.\Aipi_STableLocalLiteral.cpp
# End Source File
# Begin Source File

SOURCE=.\Aipi_STableLocalNumeric.cpp
# End Source File
# Begin Source File

SOURCE=.\Aipi_STableNumeric.cpp
# End Source File
# Begin Source File

SOURCE=.\Aipi_Symbol.cpp
# End Source File
# Begin Source File

SOURCE=.\Aipi_SymbolTable.cpp
# End Source File
# Begin Source File

SOURCE=.\Aipi_Tokenizer.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPIDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPIEditorDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPIEditorView.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPIGlobalFunctions.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPIGlobals.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPITabView.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPITreeDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPITreeView.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPIView.cpp
# End Source File
# Begin Source File

SOURCE=.\CalendarDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartAxisOptionDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartBarCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartLinePropDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartPointPropDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartSerieDelDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartSeriePropDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartSurfacePropDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\CntrItem.cpp
# End Source File
# Begin Source File

SOURCE=.\ColourPicker.cpp
# End Source File
# Begin Source File

SOURCE=.\ColourPopup.cpp
# End Source File
# Begin Source File

SOURCE=.\CommandDlgBar.cpp
# End Source File
# Begin Source File

SOURCE=.\DocTemplateEx.cpp
# End Source File
# Begin Source File

SOURCE=.\DxfCadDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DxfDrawingView.cpp
# End Source File
# Begin Source File

SOURCE=.\DxfProgressDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EditInfoCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\FileFinder.cpp
# End Source File
# Begin Source File

SOURCE=.\FindInFilesDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FindInFilesExtDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FunctionProperties.cpp
# End Source File
# Begin Source File

SOURCE=.\GoToDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphAxisDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphBarCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphCoordinatesDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ImageCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ImageDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ImageFilterDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\InductionTabView.cpp
# End Source File
# Begin Source File

SOURCE=.\InfoCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\jb_playvideo.cpp
# End Source File
# Begin Source File

SOURCE=.\jb_videoglobals.cpp
# End Source File
# Begin Source File

SOURCE=.\JukeBoxDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ListMultiOptionCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ListOptionCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MediaPlayerDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\mp_playvideo.cpp
# End Source File
# Begin Source File

SOURCE=.\mp_videoglobals.cpp
# End Source File
# Begin Source File

SOURCE=.\NewProjectEndPage.cpp
# End Source File
# Begin Source File

SOURCE=.\NewProjectIntroPage.cpp
# End Source File
# Begin Source File

SOURCE=.\NewProjectPage1.cpp
# End Source File
# Begin Source File

SOURCE=.\NewProjectPage2.cpp
# End Source File
# Begin Source File

SOURCE=.\NewProjectSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\NSChartBarCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\NSChartDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\OleDBConnectionDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\OleDBConnectionProp.cpp
# End Source File
# Begin Source File

SOURCE=.\OleDBDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\OutputTabView.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXShellNamespaceNavigator.cpp
# End Source File
# Begin Source File

SOURCE=.\PageCellSizeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PageEditDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PageFileDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PageFormatDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PageInsertDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PageOptionsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PathFinder.cpp
# End Source File
# Begin Source File

SOURCE=.\ProjectProperties.cpp
# End Source File
# Begin Source File

SOURCE=.\PropertiesBar.cpp
# End Source File
# Begin Source File

SOURCE=.\QueryProperties.cpp
# End Source File
# Begin Source File

SOURCE=.\ResourceProperties.cpp
# End Source File
# Begin Source File

SOURCE=.\RuleProperties.cpp
# End Source File
# Begin Source File

SOURCE=.\StaticMeterCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StringInputDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\VariableProperties.cpp
# End Source File
# Begin Source File

SOURCE=.\WorkspaceLocation.cpp
# End Source File
# Begin Source File

SOURCE=.\WorkspaceTabDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\WorkspaceTabView.cpp
# End Source File
# Begin Source File

SOURCE=.\WorkspaceTree1.cpp
# End Source File
# Begin Source File

SOURCE=.\WorkspaceView.cpp
# End Source File
# Begin Source File

SOURCE=.\ZoomViewDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AIPI.h
# End Source File
# Begin Source File

SOURCE=.\Aipi_CParser.h
# End Source File
# Begin Source File

SOURCE=.\Aipi_Emitter.h
# End Source File
# Begin Source File

SOURCE=.\Aipi_Error.h
# End Source File
# Begin Source File

SOURCE=.\Aipi_ExpParser.h
# End Source File
# Begin Source File

SOURCE=.\Aipi_ExpParserFile.h
# End Source File
# Begin Source File

SOURCE=.\Aipi_ExpParserFileGlobal.h
# End Source File
# Begin Source File

SOURCE=.\Aipi_ExpParserGUI.h
# End Source File
# Begin Source File

SOURCE=.\Aipi_ExpParserGUIGlobal.h
# End Source File
# Begin Source File

SOURCE=.\Aipi_ExpParserRT.h
# End Source File
# Begin Source File

SOURCE=.\Aipi_Init.h
# End Source File
# Begin Source File

SOURCE=.\Aipi_Lexer.h
# End Source File
# Begin Source File

SOURCE=.\Aipi_Main.h
# End Source File
# Begin Source File

SOURCE=.\Aipi_Parser.h
# End Source File
# Begin Source File

SOURCE=.\Aipi_ParserFile.h
# End Source File
# Begin Source File

SOURCE=.\Aipi_ParserGUI.h
# End Source File
# Begin Source File

SOURCE=.\Aipi_ScriptCode.h
# End Source File
# Begin Source File

SOURCE=.\Aipi_ScriptLocation.h
# End Source File
# Begin Source File

SOURCE=.\Aipi_STableClass.h
# End Source File
# Begin Source File

SOURCE=.\Aipi_STableGlobalLiteral.h
# End Source File
# Begin Source File

SOURCE=.\Aipi_STableGlobalNumeric.h
# End Source File
# Begin Source File

SOURCE=.\Aipi_STableLiteral.h
# End Source File
# Begin Source File

SOURCE=.\Aipi_STableLocalLiteral.h
# End Source File
# Begin Source File

SOURCE=.\Aipi_STableLocalNumeric.h
# End Source File
# Begin Source File

SOURCE=.\Aipi_STableNumeric.h
# End Source File
# Begin Source File

SOURCE=.\Aipi_Symbol.h
# End Source File
# Begin Source File

SOURCE=.\Aipi_SymbolTable.h
# End Source File
# Begin Source File

SOURCE=.\Aipi_Tokenizer.h
# End Source File
# Begin Source File

SOURCE=.\AIPIDoc.h
# End Source File
# Begin Source File

SOURCE=.\AIPIEditorDoc.h
# End Source File
# Begin Source File

SOURCE=.\AIPIEditorView.h
# End Source File
# Begin Source File

SOURCE=.\AIPIGlobalFunctions.h
# End Source File
# Begin Source File

SOURCE=.\AIPIGlobals.h
# End Source File
# Begin Source File

SOURCE=.\AIPITabView.h
# End Source File
# Begin Source File

SOURCE=.\AIPITreeDoc.h
# End Source File
# Begin Source File

SOURCE=.\AIPITreeView.h
# End Source File
# Begin Source File

SOURCE=.\AIPIView.h
# End Source File
# Begin Source File

SOURCE=.\CalendarDlg.h
# End Source File
# Begin Source File

SOURCE=.\ChartAxisOptionDlg.h
# End Source File
# Begin Source File

SOURCE=.\ChartBarCtrl.h
# End Source File
# Begin Source File

SOURCE=.\ChartLinePropDlg.h
# End Source File
# Begin Source File

SOURCE=.\ChartPointPropDlg.h
# End Source File
# Begin Source File

SOURCE=.\ChartSerieDelDlg.h
# End Source File
# Begin Source File

SOURCE=.\ChartSeriePropDlg.h
# End Source File
# Begin Source File

SOURCE=.\ChartSurfacePropDlg.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\CntrItem.h
# End Source File
# Begin Source File

SOURCE=.\ColourPicker.h
# End Source File
# Begin Source File

SOURCE=.\ColourPopup.h
# End Source File
# Begin Source File

SOURCE=.\CommandDlgBar.h
# End Source File
# Begin Source File

SOURCE=.\DocTemplateEx.h
# End Source File
# Begin Source File

SOURCE=.\DxfCadDlg.h
# End Source File
# Begin Source File

SOURCE=.\DxfDrawingView.h
# End Source File
# Begin Source File

SOURCE=.\DxfProgressDlg.h
# End Source File
# Begin Source File

SOURCE=.\EditInfoCtrl.h
# End Source File
# Begin Source File

SOURCE=.\FileFinder.h
# End Source File
# Begin Source File

SOURCE=.\FindInFilesDlg.h
# End Source File
# Begin Source File

SOURCE=.\FindInFilesExtDlg.h
# End Source File
# Begin Source File

SOURCE=.\FunctionProperties.h
# End Source File
# Begin Source File

SOURCE=.\GoToDlg.h
# End Source File
# Begin Source File

SOURCE=.\GraphAxisDlg.h
# End Source File
# Begin Source File

SOURCE=.\GraphBarCtrl.h
# End Source File
# Begin Source File

SOURCE=.\GraphCoordinatesDlg.h
# End Source File
# Begin Source File

SOURCE=.\ImageCtrl.h
# End Source File
# Begin Source File

SOURCE=.\ImageDlg.h
# End Source File
# Begin Source File

SOURCE=.\ImageFilterDlg.h
# End Source File
# Begin Source File

SOURCE=.\InductionTabView.h
# End Source File
# Begin Source File

SOURCE=.\InfoCtrl.h
# End Source File
# Begin Source File

SOURCE=.\jb_playvideo.h
# End Source File
# Begin Source File

SOURCE=.\JukeBoxDlg.h
# End Source File
# Begin Source File

SOURCE=.\ListMultiOptionCtrl.h
# End Source File
# Begin Source File

SOURCE=.\ListOptionCtrl.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MediaPlayerDlg.h
# End Source File
# Begin Source File

SOURCE=.\mediatypes.h
# End Source File
# Begin Source File

SOURCE=.\memdc.h
# End Source File
# Begin Source File

SOURCE=.\mp_playvideo.h
# End Source File
# Begin Source File

SOURCE=.\NewProjectEndPage.h
# End Source File
# Begin Source File

SOURCE=.\NewProjectIntroPage.h
# End Source File
# Begin Source File

SOURCE=.\NewProjectPage1.h
# End Source File
# Begin Source File

SOURCE=.\NewProjectPage2.h
# End Source File
# Begin Source File

SOURCE=.\NewProjectSheet.h
# End Source File
# Begin Source File

SOURCE=.\NSChartBarCtrl.h
# End Source File
# Begin Source File

SOURCE=.\NSChartDlg.h
# End Source File
# Begin Source File

SOURCE=.\OleDBConnectionDlg.h
# End Source File
# Begin Source File

SOURCE=.\OleDBConnectionProp.h
# End Source File
# Begin Source File

SOURCE=.\OleDBDlg.h
# End Source File
# Begin Source File

SOURCE=.\OutputTabView.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXShellNamespaceNavigator.h
# End Source File
# Begin Source File

SOURCE=.\PageCellSizeDlg.h
# End Source File
# Begin Source File

SOURCE=.\PageEditDlg.h
# End Source File
# Begin Source File

SOURCE=.\PageFileDlg.h
# End Source File
# Begin Source File

SOURCE=.\PageFormatDlg.h
# End Source File
# Begin Source File

SOURCE=.\PageInsertDlg.h
# End Source File
# Begin Source File

SOURCE=.\PageOptionsDlg.h
# End Source File
# Begin Source File

SOURCE=.\PathFinder.h
# End Source File
# Begin Source File

SOURCE=.\ProjectProperties.h
# End Source File
# Begin Source File

SOURCE=.\PropertiesBar.h
# End Source File
# Begin Source File

SOURCE=.\QueryProperties.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ResourceProperties.h
# End Source File
# Begin Source File

SOURCE=.\RuleProperties.h
# End Source File
# Begin Source File

SOURCE=.\StaticMeterCtrl.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\StringInputDlg.h
# End Source File
# Begin Source File

SOURCE=.\tstl.h
# End Source File
# Begin Source File

SOURCE=.\VariableProperties.h
# End Source File
# Begin Source File

SOURCE=.\WorkspaceLocation.h
# End Source File
# Begin Source File

SOURCE=.\WorkspaceTabDoc.h
# End Source File
# Begin Source File

SOURCE=.\WorkspaceTabView.h
# End Source File
# Begin Source File

SOURCE=.\WorkspaceTree1.h
# End Source File
# Begin Source File

SOURCE=.\WorkspaceView.h
# End Source File
# Begin Source File

SOURCE=.\ZoomViewDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\AI_02.ico
# End Source File
# Begin Source File

SOURCE=".\res\Aipi Cuad 16.ico"
# End Source File
# Begin Source File

SOURCE=".\res\Aipi Cuad 24.ico"
# End Source File
# Begin Source File

SOURCE=".\res\Aipi Cuad 32.ico"
# End Source File
# Begin Source File

SOURCE=".\res\Aipi Cuad 48.ico"
# End Source File
# Begin Source File

SOURCE=".\res\AIPI pi_16_16.ico"
# End Source File
# Begin Source File

SOURCE=".\res\AIPI pi_32_32.ico"
# End Source File
# Begin Source File

SOURCE=".\res\Aipi Red 48.ico"
# End Source File
# Begin Source File

SOURCE=.\res\aipi.bmp
# End Source File
# Begin Source File

SOURCE=.\res\AIPI.ico
# End Source File
# Begin Source File

SOURCE=.\res\AIPI.rc2
# End Source File
# Begin Source File

SOURCE=.\res\AIPI_01.ico
# End Source File
# Begin Source File

SOURCE=.\res\aipi_blu.ico
# End Source File
# Begin Source File

SOURCE=.\res\AIPIDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\aipiIcon.ico
# End Source File
# Begin Source File

SOURCE=.\res\aipty.bmp
# End Source File
# Begin Source File

SOURCE=.\res\apj.ico
# End Source File
# Begin Source File

SOURCE=.\res\ARW08UP.ICO
# End Source File
# Begin Source File

SOURCE=.\Baner16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Baner16.bmp
# End Source File
# Begin Source File

SOURCE=.\Baner256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Baner256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BitmapImage.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00004.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00005.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00006.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00007.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BOOK01B.ICO
# End Source File
# Begin Source File

SOURCE=.\res\BOOK02.ICO
# End Source File
# Begin Source File

SOURCE=.\res\BOOK03.ICO
# End Source File
# Begin Source File

SOURCE=.\res\BOOK04.ICO
# End Source File
# Begin Source File

SOURCE=.\res\BOOKS01.ICO
# End Source File
# Begin Source File

SOURCE=.\res\BOOKS02.ICO
# End Source File
# Begin Source File

SOURCE=.\res\BOOKS04.ICO
# End Source File
# Begin Source File

SOURCE=.\res\calendar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\chartbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\checkboxes.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CHECKMRK.ICO
# End Source File
# Begin Source File

SOURCE=.\res\close_pr.ico
# End Source File
# Begin Source File

SOURCE=.\res\CLSDFOLD.ICO
# End Source File
# Begin Source File

SOURCE=.\res\coolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CRDFLE01.ICO
# End Source File
# Begin Source File

SOURCE=.\res\CRDFLE03.ICO
# End Source File
# Begin Source File

SOURCE=.\res\CRDFLE10.ICO
# End Source File
# Begin Source File

SOURCE=.\res\csv.ico
# End Source File
# Begin Source File

SOURCE=.\res\cur00001.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00002.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00004.cur
# End Source File
# Begin Source File

SOURCE=.\res\DISKS01.ICO
# End Source File
# Begin Source File

SOURCE=.\res\DISKS04.ICO
# End Source File
# Begin Source File

SOURCE=.\res\Document1_16x16.ico
# End Source File
# Begin Source File

SOURCE=.\res\Document1_32x32.ico
# End Source File
# Begin Source File

SOURCE=.\res\Document3_16x16.ico
# End Source File
# Begin Source File

SOURCE=.\res\Dragmove.cur
# End Source File
# Begin Source File

SOURCE=.\res\drop_mov.cur
# End Source File
# Begin Source File

SOURCE=.\res\empty_sc.bmp
# End Source File
# Begin Source File

SOURCE=.\res\file_pro.ico
# End Source File
# Begin Source File

SOURCE=.\res\FILES01A.ICO
# End Source File
# Begin Source File

SOURCE=.\res\FILES01B.ICO
# End Source File
# Begin Source File

SOURCE=.\res\FILES02A.ICO
# End Source File
# Begin Source File

SOURCE=.\res\FILES03A.ICO
# End Source File
# Begin Source File

SOURCE=.\res\FILES03B.ICO
# End Source File
# Begin Source File

SOURCE=.\res\FILES08.ICO
# End Source File
# Begin Source File

SOURCE=.\res\FILES09.ICO
# End Source File
# Begin Source File

SOURCE=.\res\font.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GRAPH06.ICO
# End Source File
# Begin Source File

SOURCE=.\res\hardware.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00003.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00004.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00005.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00006.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00007.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00008.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00009.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00010.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00011.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00012.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00013.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00014.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00015.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00016.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00017.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00018.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00019.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00020.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00021.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00022.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00023.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00024.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon12.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon3.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon4.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon5.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon7.ico
# End Source File
# Begin Source File

SOURCE=.\res\IDB_SPLASHWINDOW.bmp
# End Source File
# Begin Source File

SOURCE=.\res\idr_aipi.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_ipit.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_proj.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_scin.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_tree.ico
# End Source File
# Begin Source File

SOURCE=.\res\ieset.bmp
# End Source File
# Begin Source File

SOURCE=.\res\imageDlg.bmp
# End Source File
# Begin Source File

SOURCE=.\res\imagelis.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Juan_Aipi_16_16.ico
# End Source File
# Begin Source File

SOURCE=.\res\LIGHTON.ICO
# End Source File
# Begin Source File

SOURCE=.\res\List.bmp
# End Source File
# Begin Source File

SOURCE=.\res\listboxc.bmp
# End Source File
# Begin Source File

SOURCE=.\res\listchec.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mainfram.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mainframe.bmp
# End Source File
# Begin Source File

SOURCE=.\res\meterctr.bmp
# End Source File
# Begin Source File

SOURCE=".\res\Microsoft Excel File_16x16.ico"
# End Source File
# Begin Source File

SOURCE=".\res\Microsoft ExcelA_32x32.ico"
# End Source File
# Begin Source File

SOURCE=.\res\MISC02.ICO
# End Source File
# Begin Source File

SOURCE=.\res\MISC03.ICO
# End Source File
# Begin Source File

SOURCE=.\res\MISC13.ICO
# End Source File
# Begin Source File

SOURCE=.\res\MISC14.ICO
# End Source File
# Begin Source File

SOURCE=.\res\MISC15.ICO
# End Source File
# Begin Source File

SOURCE=.\res\MIXER01A.ICO
# End Source File
# Begin Source File

SOURCE=.\res\MMCON03C.ICO
# End Source File
# Begin Source File

SOURCE=.\res\MMCON03F.ICO
# End Source File
# Begin Source File

SOURCE=.\res\MMCON03G.ICO
# End Source File
# Begin Source File

SOURCE=.\res\MSGBOX01.ICO
# End Source File
# Begin Source File

SOURCE=.\res\MSGBOX02.ICO
# End Source File
# Begin Source File

SOURCE=.\res\MSGBOX03.ICO
# End Source File
# Begin Source File

SOURCE=.\res\MSGBOX04.ICO
# End Source File
# Begin Source File

SOURCE=.\res\multilis.bmp
# End Source File
# Begin Source File

SOURCE=.\res\NET01.ICO
# End Source File
# Begin Source File

SOURCE=.\res\new_proj.ico
# End Source File
# Begin Source File

SOURCE=.\res\nodrop.cur
# End Source File
# Begin Source File

SOURCE=.\res\NOTE07.ICO
# End Source File
# Begin Source File

SOURCE=.\res\NOTE11.ICO
# End Source File
# Begin Source File

SOURCE=.\res\nschart.bmp
# End Source File
# Begin Source File

SOURCE=.\res\open_pro.ico
# End Source File
# Begin Source File

SOURCE=.\res\optionba.bmp
# End Source File
# Begin Source File

SOURCE=.\res\plarge.bmp
# End Source File
# Begin Source File

SOURCE=.\res\POINT13.ICO
# End Source File
# Begin Source File

SOURCE=.\res\POINT14.ICO
# End Source File
# Begin Source File

SOURCE=.\res\proj_new.bmp
# End Source File
# Begin Source File

SOURCE=.\res\proj_ope.bmp
# End Source File
# Begin Source File

SOURCE=.\res\project.bmp
# End Source File
# Begin Source File

SOURCE=.\res\projtype.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rtf.ico
# End Source File
# Begin Source File

SOURCE=.\res\ruleimag.bmp
# End Source File
# Begin Source File

SOURCE=.\res\scintity.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Sort_32x32.ico
# End Source File
# Begin Source File

SOURCE=.\res\ssn_file.ico
# End Source File
# Begin Source File

SOURCE=.\res\stop_fin.ico
# End Source File
# Begin Source File

SOURCE=.\res\tabaipii.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tabinduc.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tablisti.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tabtreei.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tfdropcopy.cur
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tre.ico
# End Source File
# Begin Source File

SOURCE=.\res\tree.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tree_typ.ico
# End Source File
# Begin Source File

SOURCE=.\res\treeedty.bmp
# End Source File
# Begin Source File

SOURCE=.\res\treeimages.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TxtExt_16x16.ico
# End Source File
# Begin Source File

SOURCE=.\res\VB_Letters.ico
# End Source File
# Begin Source File

SOURCE=.\res\VisualStudio_Project_16x16.ico
# End Source File
# Begin Source File

SOURCE=.\res\VJ_Letter32.ico
# End Source File
# Begin Source File

SOURCE=.\res\VS_AddProject_16x16.ico
# End Source File
# Begin Source File

SOURCE=.\res\VS_NewProject_16x16.ico
# End Source File
# Begin Source File

SOURCE=.\res\VS_OpenProject_16x16.ico
# End Source File
# Begin Source File

SOURCE=.\res\WAIT01.CUR
# End Source File
# Begin Source File

SOURCE=.\res\Water16.bmp
# End Source File
# Begin Source File

SOURCE=.\Water16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Water256.bmp
# End Source File
# Begin Source File

SOURCE=.\Water256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WordPadExt_16x16.ico
# End Source File
# Begin Source File

SOURCE=.\res\workspac.bmp
# End Source File
# Begin Source File

SOURCE=.\res\xls.ico
# End Source File
# End Group
# Begin Group "UTSource"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=.\UTSource\COPYTREE.CPP
# End Source File
# Begin Source File

SOURCE=.\UTSource\DIR.CPP
# End Source File
# Begin Source File

SOURCE=.\UTSource\DSTRLIST.CPP
# End Source File
# Begin Source File

SOURCE=.\UTSource\FILE.CPP
# End Source File
# Begin Source File

SOURCE=.\UTSource\MFCToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OX3DTabView.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXAdvancedAssert.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXAdvancedAssertMail.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXBackgroundPainter.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXBitmapButton.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXBitmapMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXBitmapMenuOrganizer.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXBMPFilePickerCombo.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXBrowseColorEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXBrowseDirEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXButtonAppearanceDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXCalculatorCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXCalculatorEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXCalendar.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXCalendarEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXCalendarPopup.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXCaptionPainter.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXChildFrameState.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXColorPickerButton.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXColorPickerCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXCoolComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXCoolControlOrganizer.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXCoolCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXCoolToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXCustomizeBackgroundPage.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXCustomizeCaptionPage.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXCustomizeCommandsPage.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXCustomizeCoolControlsPage.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXCustomizeInstanceManagerPage.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXCustomizeIntelliMousePage.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXCustomizeManager.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXCustomizePage.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXCustomizeShortkeysPage.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXCustomizeSplashWindowPage.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXCustomizeTabbedMDIPage.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXCustomizeToolbarsPage.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXCustomizeTrayIconPage.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXCustomizeWorkspaceStatePage.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\Oxdib.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXDlgBar.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXDockTabCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXDocTemplateSpy.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXDragDockContext.CPP
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXDragDropCommands.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXEditList.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXFolderPickerDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXFontComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXFontPickerButton.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXFrameWndDock.CPP
# End Source File
# Begin Source File

SOURCE=.\UTSource\oxgridedit.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXGridHdr.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXGridList.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXHistoryCombo.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXHistoryCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXHookWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXImageListBox.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXInstanceManager.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXIntelliMouse.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXIPEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXItemTip.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXItemTipWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXLayoutManager.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXListBoxEx.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXListEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXMaskedEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXMDIFloatWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXMenuBar.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXMultiComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXOptionTreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXPhysicalEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXPhysicalEditEx.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXPopupBarCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXPreviewDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXPropertiesWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXPropertyDescriptionPane.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXPropertyTree.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXRectTracker.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXRegistryItem.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXRegistryValFile.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXScrollWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXSeparator.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXShellFolderTree.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXShortcutBar.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXShortkeysOrganizer.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXSizeCtrlBar.CPP
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXSizeDlgBar.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXSizeDockBar.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXSizeToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXSkinnedComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXSkinnedSpinCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXSkinnedTabCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXSkins.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXSpinCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXSplashWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXSplashWndDIB.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXSplitterColRowState.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXSplitterRect.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXStatic.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXStaticText.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXSzMiniDockFrmWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXTabClientWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXTaskbarIcon.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXToolTipCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXTreeCal.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXTreeCombo.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXTreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXTreeEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXTreeHeader.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXTreeItem.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXUxTheme.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\OXWorkspaceState.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\Path.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\UTBStrOp.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\Xstatus4.cpp
# End Source File
# Begin Source File

SOURCE=.\UTSource\XSTRING.CPP
# End Source File
# End Group
# Begin Group "UTInclude"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=.\UTInclude\MFCToolBar.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OX3DTabView.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXAdvancedAssert.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXAdvancedAssertMail.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXBitmapButton.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXBitmapMenu.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXBitmapMenuOrganizer.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXBrowseColorEdit.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXBrowseDirEdit.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXCalculatorCtrl.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXCalculatorEdit.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXCalendar.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXCalendarEdit.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXCalendarPopup.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXChildFrameState.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXCoolComboBox.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXCoolCtrl.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXCoolToolBar.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXDockTabCtrl.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXDocTemplateSpy.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXDragDockContext.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXEdit.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXEditList.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXFolderPickerDlg.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXFontComboBox.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\oxframewnddock.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\oxgridedit.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXGridHdr.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXGridList.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXHistoryCtrl.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXHookWnd.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXIPEdit.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXItemTip.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXItemTipWnd.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXLayoutManager.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXListBoxEx.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXListEdit.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXMaskedEdit.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXMDIFloatWnd.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXPhysicalEdit.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXPhysicalEditEx.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXPropertiesWnd.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXPropertyDescriptionPane.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXPropertyTree.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXRectTracker.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXRegistryItem.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXScrollWnd.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXShellFolderTree.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXShortcut.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\oxsizectrlbar.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXSizeDlgBar.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXSizeDockBar.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXSizeToolBar.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXSkinnedComboBox.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXSkinnedSpinCtrl.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXSkinnedTabCtrl.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXSkins.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXSpinCtrl.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXSplitterColRowState.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXSplitterRect.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXStaticText.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\oxszminidockfrmwnd.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXTabClientWnd.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXToolTipCtrl.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXTreeCal.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXTreeCombo.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXTreeCtrl.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXTreeEdit.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXTreeHeader.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXTreeItem.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXUxTheme.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\OXWorkspaceState.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\utbstrop.h
# End Source File
# Begin Source File

SOURCE=.\UTInclude\XSTATUS4.h
# End Source File
# End Group
# Begin Group "GDIPlusInclude"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=.\ImplementationGDIPLUS\GdiPlus.h
# End Source File
# Begin Source File

SOURCE=.\ImplementationGDIPLUS\GdiPlusBase.h
# End Source File
# Begin Source File

SOURCE=.\ImplementationGDIPLUS\GdiPlusBitmap.h
# End Source File
# Begin Source File

SOURCE=.\ImplementationGDIPLUS\GdiPlusBrush.h
# End Source File
# Begin Source File

SOURCE=.\ImplementationGDIPLUS\GdiPlusCachedBitmap.h
# End Source File
# Begin Source File

SOURCE=.\ImplementationGDIPLUS\GdiPlusColor.h
# End Source File
# Begin Source File

SOURCE=.\ImplementationGDIPLUS\GdiPlusColorMatrix.h
# End Source File
# Begin Source File

SOURCE=.\ImplementationGDIPLUS\GdiPlusEnums.h
# End Source File
# Begin Source File

SOURCE=.\ImplementationGDIPLUS\GdiPlusFlat.h
# End Source File
# Begin Source File

SOURCE=.\ImplementationGDIPLUS\GdiPlusFont.h
# End Source File
# Begin Source File

SOURCE=.\ImplementationGDIPLUS\GdiPlusFontCollection.h
# End Source File
# Begin Source File

SOURCE=.\ImplementationGDIPLUS\GdiPlusFontFamily.h
# End Source File
# Begin Source File

SOURCE=.\ImplementationGDIPLUS\GdiPlusGpStubs.h
# End Source File
# Begin Source File

SOURCE=.\ImplementationGDIPLUS\GdiPlusGraphics.h
# End Source File
# Begin Source File

SOURCE=.\ImplementationGDIPLUS\GdiPlusHeaders.h
# End Source File
# Begin Source File

SOURCE=.\ImplementationGDIPLUS\GdiPlusimageAttributes.h
# End Source File
# Begin Source File

SOURCE=.\ImplementationGDIPLUS\GdiPlusImageCodec.h
# End Source File
# Begin Source File

SOURCE=.\ImplementationGDIPLUS\GdiPlusImaging.h
# End Source File
# Begin Source File

SOURCE=.\ImplementationGDIPLUS\GdiPlusInit.h
# End Source File
# Begin Source File

SOURCE=.\ImplementationGDIPLUS\GdiPlusLineCaps.h
# End Source File
# Begin Source File

SOURCE=.\ImplementationGDIPLUS\GdiPlusMatrix.h
# End Source File
# Begin Source File

SOURCE=.\ImplementationGDIPLUS\GdiPlusMem.h
# End Source File
# Begin Source File

SOURCE=.\ImplementationGDIPLUS\GdiPlusMetaFile.h
# End Source File
# Begin Source File

SOURCE=.\ImplementationGDIPLUS\GdiPlusMetaHeader.h
# End Source File
# Begin Source File

SOURCE=.\ImplementationGDIPLUS\GdiPlusPath.h
# End Source File
# Begin Source File

SOURCE=.\ImplementationGDIPLUS\GdiPlusPen.h
# End Source File
# Begin Source File

SOURCE=.\ImplementationGDIPLUS\GdiPlusPixelFormats.h
# End Source File
# Begin Source File

SOURCE=.\ImplementationGDIPLUS\GdiPlusRegion.h
# End Source File
# Begin Source File

SOURCE=.\ImplementationGDIPLUS\GdiPlusStringFormat.h
# End Source File
# Begin Source File

SOURCE=.\ImplementationGDIPLUS\GdiPlusTypes.h
# End Source File
# End Group
# Begin Group "MVImage"

# PROP Default_Filter "cpp, h"
# Begin Source File

SOURCE=.\mvImage\mvImage.cpp
# End Source File
# Begin Source File

SOURCE=.\mvImage\mvImage.h
# End Source File
# End Group
# Begin Group "WndImage"

# PROP Default_Filter "cpp, h"
# Begin Source File

SOURCE=.\WndImage\WndImage.cpp
# End Source File
# Begin Source File

SOURCE=.\WndImage\WndImage.h
# End Source File
# End Group
# Begin Group "NSChart"

# PROP Default_Filter "cpp, h"
# Begin Source File

SOURCE=.\NSChart\NSChartCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\NSChart\NSChartCtrl.h
# End Source File
# End Group
# Begin Group "ChartCtrl"

# PROP Default_Filter "cpp, h"
# Begin Source File

SOURCE=.\ChartCtrl\ChartAxis.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartAxis.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartAxisLabel.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartAxisLabel.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartCtrl.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartGrid.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartGrid.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartLegend.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartLegend.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartLineSerie.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartLineSerie.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartObject.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartPointsSerie.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartPointsSerie.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartSerie.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartSerie.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartSurfaceSerie.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartSurfaceSerie.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartTitle.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartTitle.h
# End Source File
# End Group
# Begin Group "CalendarCtrl"

# PROP Default_Filter "cpp, h"
# Begin Source File

SOURCE=.\CalendarCtrl\CalendarCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\CalendarCtrl\CalendarCtrl.h
# End Source File
# End Group
# Begin Group "3DMeterCtrl"

# PROP Default_Filter "cpp, h"
# Begin Source File

SOURCE=.\3DMeterCtrl\3DMeterCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\3DMeterCtrl\3DMeterCtrl.h
# End Source File
# End Group
# Begin Group "ImageProcess"

# PROP Default_Filter "cpp, h"
# Begin Source File

SOURCE=.\ImageProcess\CimageProcess.cpp
# End Source File
# Begin Source File

SOURCE=.\ImageProcess\CimageProcess.h
# End Source File
# End Group
# Begin Group "GraphBar"

# PROP Default_Filter "cpp, h"
# Begin Source File

SOURCE=.\GraphBar\coords.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphBar\coords.h
# End Source File
# Begin Source File

SOURCE=.\GraphBar\f2doff.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphBar\f2doff.h
# End Source File
# Begin Source File

SOURCE=.\GraphBar\gen_prop_dlgs.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphBar\gen_prop_dlgs.h
# End Source File
# Begin Source File

SOURCE=.\GraphBar\graph_general.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphBar\graph_general.h
# End Source File
# Begin Source File

SOURCE=.\GraphBar\graph_props.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphBar\graph_props.h
# End Source File
# Begin Source File

SOURCE=.\GraphBar\graphcombobox.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphBar\graphcombobox.h
# End Source File
# Begin Source File

SOURCE=.\GraphBar\GraphContainer.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphBar\GraphContainer.h
# End Source File
# Begin Source File

SOURCE=.\GraphBar\GraphFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphBar\GraphFrame.h
# End Source File
# Begin Source File

SOURCE=.\GraphBar\graphpanel.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphBar\graphpanel.h
# End Source File
# Begin Source File

SOURCE=.\GraphBar\GraphWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphBar\GraphWnd.h
# End Source File
# Begin Source File

SOURCE=.\GraphBar\grres.h
# End Source File
# Begin Source File

SOURCE=.\GraphBar\gruler.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphBar\gruler.h
# End Source File
# Begin Source File

SOURCE=.\GraphBar\points.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphBar\points.h
# End Source File
# Begin Source File

SOURCE=.\GraphBar\pviewbar.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphBar\pviewbar.h
# End Source File
# Begin Source File

SOURCE=.\GraphBar\sizecbar.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphBar\sizecbar.h
# End Source File
# End Group
# Begin Group "ScintillaCtrl"

# PROP Default_Filter "cpp, h"
# Begin Source File

SOURCE=.\ScintillaCtrl\ScintillaCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ScintillaCtrl\ScintillaCtrl.h
# End Source File
# Begin Source File

SOURCE=.\ScintillaCtrl\ScintillaDocView.cpp
# End Source File
# Begin Source File

SOURCE=.\ScintillaCtrl\ScintillaDocView.h
# End Source File
# Begin Source File

SOURCE=.\ScintillaCtrl\ScintillaResource.h
# End Source File
# End Group
# Begin Group "ScriptObject"

# PROP Default_Filter "cpp, h"
# Begin Source File

SOURCE=.\ScriptObject\SafeArrayHelper.cpp
# End Source File
# Begin Source File

SOURCE=.\ScriptObject\SafeArrayHelper.h
# End Source File
# Begin Source File

SOURCE=.\ScriptObject\ScriptObject.cpp
# End Source File
# Begin Source File

SOURCE=.\ScriptObject\ScriptObject.h
# End Source File
# End Group
# Begin Group "SQLQuery"

# PROP Default_Filter "cpp, h"
# Begin Source File

SOURCE=.\SQLQuery\SQLQuery.cpp
# End Source File
# Begin Source File

SOURCE=.\SQLQuery\SQLQuery.h
# End Source File
# End Group
# Begin Group "CadLib"

# PROP Default_Filter "cpp, h"
# Begin Source File

SOURCE=.\CadLib\Interface\CadLib.cpp
# End Source File
# Begin Source File

SOURCE=.\CadLib\Interface\CadLib.h
# End Source File
# Begin Source File

SOURCE=.\CadLib\Interface\DrawingDef.h
# End Source File
# Begin Source File

SOURCE=.\CadLib\Interface\DXFDef.h
# End Source File
# End Group
# Begin Group "TreeEditorCtrl"

# PROP Default_Filter "cpp, h"
# Begin Source File

SOURCE=.\TreeEditorCtrl\EditTreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\TreeEditorCtrl\EditTreeCtrl.h
# End Source File
# Begin Source File

SOURCE=.\TreeEditorCtrl\TreeType.cpp
# End Source File
# Begin Source File

SOURCE=.\TreeEditorCtrl\TreeType.h
# End Source File
# End Group
# Begin Group "ComboListCtrl"

# PROP Default_Filter "cpp, h"
# Begin Source File

SOURCE=.\ComboListCtrl\CheckHeadCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ComboListCtrl\CheckHeadCtrl.h
# End Source File
# Begin Source File

SOURCE=.\ComboListCtrl\ComboListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ComboListCtrl\ComboListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\ComboListCtrl\InPlaceCombo.cpp
# End Source File
# Begin Source File

SOURCE=.\ComboListCtrl\InPlaceCombo.h
# End Source File
# Begin Source File

SOURCE=.\ComboListCtrl\InPlaceEditCombo.cpp
# End Source File
# Begin Source File

SOURCE=.\ComboListCtrl\InPlaceEditCombo.h
# End Source File
# End Group
# Begin Group "RollupCtrl"

# PROP Default_Filter "cpp, h"
# Begin Source File

SOURCE=.\RollupCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\RollupCtrl.h
# End Source File
# End Group
# Begin Group "GridCtrl"

# PROP Default_Filter "cpp, h"
# Begin Source File

SOURCE=.\GridCtrl\CellRange.h
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\GridCell.cpp
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\GridCell.h
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\GridCellBase.cpp
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\GridCellBase.h
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\NewCellTypes\GridCellCheck.cpp
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\NewCellTypes\GridCellCheck.h
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\NewCellTypes\GridCellCombo.cpp
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\NewCellTypes\GridCellCombo.h
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\NewCellTypes\GridCellDateTime.cpp
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\NewCellTypes\GridCellDateTime.h
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\NewCellTypes\GridCellNumeric.cpp
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\NewCellTypes\GridCellNumeric.h
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\GridCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\GridCtrl.h
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\GridDropTarget.cpp
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\GridDropTarget.h
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\NewCellTypes\GridURLCell.cpp
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\NewCellTypes\GridURLCell.h
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\InPlaceEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\InPlaceEdit.h
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\MemDC.h
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\TitleTip.cpp
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\TitleTip.h
# End Source File
# End Group
# Begin Group "DataFileCSV"

# PROP Default_Filter "cpp, h"
# Begin Source File

SOURCE=.\DataFileCSV\CDataFile.cpp
# End Source File
# Begin Source File

SOURCE=.\DataFileCSV\CDataFile.h
# End Source File
# End Group
# Begin Group "BasicExcel"

# PROP Default_Filter "cpp, h"
# Begin Source File

SOURCE=.\BasicExcel\BasicExcelVC6.cpp
# End Source File
# Begin Source File

SOURCE=.\BasicExcel\BasicExcelVC6.hpp
# End Source File
# End Group
# Begin Group "ConsoleCombo"

# PROP Default_Filter "cpp, h"
# Begin Source File

SOURCE=.\ConsoleCombo.cpp
# End Source File
# Begin Source File

SOURCE=.\ConsoleCombo.h
# End Source File
# Begin Source File

SOURCE=.\Input.cpp
# End Source File
# Begin Source File

SOURCE=.\Input.h
# End Source File
# End Group
# Begin Group "PerfTimer"

# PROP Default_Filter "cpp, h"
# Begin Source File

SOURCE=.\PerfTimer\PerfTimer.cpp
# End Source File
# Begin Source File

SOURCE=.\PerfTimer\PerfTimer.h
# End Source File
# End Group
# Begin Group "ScintillaWnd"

# PROP Default_Filter "cpp, h"
# Begin Source File

SOURCE=.\ScintillaWnd\ScintillaWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\ScintillaWnd\ScintillaWnd.h
# End Source File
# End Group
# Begin Group "AIPI_Engine"

# PROP Default_Filter "cpp, h"
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_CmdLocation.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_CmdLocation.h
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_CR_LEX.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_CR_LEX.h
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_CR_MEA.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_CR_MEA.h
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_CR_Priority.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_CR_Priority.h
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_CR_Recency.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_CR_Recency.h
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_CR_RecencyTags.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_CR_RecencyTags.h
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_CR_Specificity.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_CR_Specificity.h
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_LHS.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_LHS.h
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_PM.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_PM.h
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RepCond.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RepCond.h
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_AM.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_AM.h
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_BM.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_BM.h
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_BMCond.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_BMCond.h
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_BME.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_BME.h
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_Cond.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_Cond.h
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_DNode.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_DNode.h
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_JNode.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_JNode.h
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_Links.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_Links.h
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_NCC.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_NCC.h
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_NCCNode.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_NCCNode.h
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_Net.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_Net.h
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_Network.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_Network.h
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_NN.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_NN.h
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_NNode.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_NNode.h
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_Node.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_Node.h
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_NodeCond.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_NodeCond.h
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_NumNode.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_NumNode.h
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_NumVars.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_NumVars.h
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_Operations.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_Operations.h
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_PNode.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_PNode.h
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_TK.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_TK.h
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_TypeDouble.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_TypeDouble.h
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_TypeFloat.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_TypeFloat.h
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_TypeInt.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_TypeInt.h
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_TypeLong.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_TypeLong.h
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_TypeString.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_TypeString.h
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_Vars.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RETE_Vars.h
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RHS.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RHS.h
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RHSCmd.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_RHSCmd.h
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_WM.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPI_Engine\Aipi_WM.h
# End Source File
# End Group
# Begin Group "AIPI_DecisionTree"

# PROP Default_Filter "cpp, h"
# Begin Source File

SOURCE=.\AIPI_DecisionTree\Aipi_DT_AVF.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPI_DecisionTree\Aipi_DT_AVF.h
# End Source File
# Begin Source File

SOURCE=.\AIPI_DecisionTree\Aipi_DT_ID3.cpp
# End Source File
# Begin Source File

SOURCE=.\AIPI_DecisionTree\Aipi_DT_ID3.h
# End Source File
# End Group
# Begin Group "AIPI_Interpreter"

# PROP Default_Filter "cpp, h"
# End Group
# Begin Source File

SOURCE=.\AIPI.reg
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\ImplementationGDIPLUS\GdiPlus.lib
# End Source File
# End Target
# End Project
