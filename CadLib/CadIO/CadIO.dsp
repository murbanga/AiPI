# Microsoft Developer Studio Project File - Name="CadIO" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=CadIO - Win32 Unicode_Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CadIO.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CadIO.mak" CFG="CadIO - Win32 Unicode_Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CadIO - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CadIO - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CadIO - Win32 Unicode_Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CadIO - Win32 Unicode_Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CadIO - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../Bin/Release/CadIO"
# PROP Intermediate_Dir "../Bin/Release/CadIO"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CADIO_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CADIO_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"../Bin/Release/CadIO.dll"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "CadIO - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../Bin/Debug/CadIO"
# PROP Intermediate_Dir "../Bin/Debug/CadIO"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CADIO_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CADIO_EXPORTS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"../Bin/Debug/CadIO.dll" /pdbtype:sept
# SUBTRACT LINK32 /incremental:no

!ELSEIF  "$(CFG)" == "CadIO - Win32 Unicode_Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "CadIO___Win32_Unicode_Debug"
# PROP BASE Intermediate_Dir "CadIO___Win32_Unicode_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "CadIO___Win32_Unicode_Debug"
# PROP Intermediate_Dir "CadIO___Win32_Unicode_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CADIO_EXPORTS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_USRDLL" /D "CADIO_EXPORTS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"../Bin/Debug/CadIO.dll" /pdbtype:sept
# SUBTRACT BASE LINK32 /incremental:no
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"../Bin/Debug/CadIO.dll" /pdbtype:sept
# SUBTRACT LINK32 /incremental:no

!ELSEIF  "$(CFG)" == "CadIO - Win32 Unicode_Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "CadIO___Win32_Unicode_Release"
# PROP BASE Intermediate_Dir "CadIO___Win32_Unicode_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "CadIO___Win32_Unicode_Release"
# PROP Intermediate_Dir "CadIO___Win32_Unicode_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CADIO_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_USRDLL" /D "CADIO_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"../Bin/Release/CadIO.dll"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"../Bin/Release/CadIO.dll"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "CadIO - Win32 Release"
# Name "CadIO - Win32 Debug"
# Name "CadIO - Win32 Unicode_Debug"
# Name "CadIO - Win32 Unicode_Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "DXF_S"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\DXFFile\Read\DRBlocks.cpp
# End Source File
# Begin Source File

SOURCE=..\DXFFile\Read\DREntities.cpp
# End Source File
# Begin Source File

SOURCE=..\DXFFile\Read\DRTables.cpp
# End Source File
# Begin Source File

SOURCE=..\DXFFile\Write\DWBlocks.cpp
# End Source File
# Begin Source File

SOURCE=..\DXFFile\Write\DWEntities.cpp
# End Source File
# Begin Source File

SOURCE=..\DXFFile\Write\DWTables.cpp
# End Source File
# Begin Source File

SOURCE=..\DXFFile\Base\DXFBase.cpp
# End Source File
# Begin Source File

SOURCE=..\DXFFile\Read\DXFRead.cpp
# End Source File
# Begin Source File

SOURCE=..\DXFFile\Write\DXFWrite.cpp
# End Source File
# End Group
# Begin Group "Drawing_S"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Drawing\View\DimView.cpp
# End Source File
# Begin Source File

SOURCE=..\Drawing\DrwIO.cpp
# End Source File
# Begin Source File

SOURCE=..\Drawing\MemDrw.cpp
# End Source File
# Begin Source File

SOURCE=..\Drawing\View\TextView.cpp
# End Source File
# Begin Source File

SOURCE=..\Drawing\View\View.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\CadIO.cpp
# End Source File
# Begin Source File

SOURCE=.\CadIO.rc
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "DXF_H"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\DXFFile\Read\DRBlocks.h
# End Source File
# Begin Source File

SOURCE=..\DXFFile\Read\DREntities.h
# End Source File
# Begin Source File

SOURCE=..\DXFFile\Read\DRTables.h
# End Source File
# Begin Source File

SOURCE=..\DXFFile\Write\DWBlocks.h
# End Source File
# Begin Source File

SOURCE=..\DXFFile\Write\DWEntities.h
# End Source File
# Begin Source File

SOURCE=..\DXFFile\Write\DWTables.h
# End Source File
# Begin Source File

SOURCE=..\DXFFile\Base\DXFBase.h
# End Source File
# Begin Source File

SOURCE=..\Interface\DXFDef.h
# End Source File
# Begin Source File

SOURCE=..\DXFFile\Read\DXFRead.h
# End Source File
# Begin Source File

SOURCE=..\DXFFile\Write\DXFWrite.h
# End Source File
# Begin Source File

SOURCE=..\DXFFile\Base\SimpleList.h
# End Source File
# End Group
# Begin Group "Drawing_H"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Drawing\View\Colors.h
# End Source File
# Begin Source File

SOURCE=..\Drawing\View\DimView.h
# End Source File
# Begin Source File

SOURCE=..\Interface\VC\DrawingDef.h
# End Source File
# Begin Source File

SOURCE=..\Drawing\DrwIO.h
# End Source File
# Begin Source File

SOURCE=..\Drawing\MemDrw.h
# End Source File
# Begin Source File

SOURCE=..\Drawing\View\TextView.h
# End Source File
# Begin Source File

SOURCE=..\Drawing\View\View.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\CadIO.def
# End Source File
# Begin Source File

SOURCE=.\CadIO.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
