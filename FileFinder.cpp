//////////////////////////////////////////////////////////////////////
//	Implemented by Samuel Gonzalo 
//
//	You may freely use or modify this code 
//////////////////////////////////////////////////////////////////////
//
// FileFinder.cpp: implementation of the CFileFinder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AIPI.h"
#include "FileFinder.h"
#include "MainFrm.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileFinder::CFileFinder()
{
	_bStopSearch = false;
	_pFileFinderProc = NULL;
	_pCustomParam = NULL;
	
}

CFileFinder::~CFileFinder()
{

}

int CFileFinder::FindFiles(LPCTSTR szBaseFolder, LPCTSTR szFileMask, BOOL bSubFolders)
{
	CFindOpts opts;

	opts.sBaseFolder = szBaseFolder;
	opts.sFileMask = szFileMask;
	opts.bSubfolders = bSubFolders;

	// Get all files, but no directories
	opts.FindAllFiles();

	Find(opts);

	return GetFileCount();
}

int CFileFinder::Find(CFileFinder::CFindOpts &opts)
{
	CFileFind	finder;
	CString		sFullMask;
	CFindOpts	subOpts;
	BOOL		bFound, bValidFile;
	CTime		timeFile;

	_bStopSearch = false;

	opts.sBaseFolder = CPathFinder::AddBackSlash(opts.sBaseFolder);

	// Find directories
	if (opts.bSubfolders)
	{
		sFullMask = opts.sBaseFolder + CString("*.*");
		bFound = finder.FindFile(sFullMask);
		while ((bFound) && (!_bStopSearch))
		{
			bFound = finder.FindNextFile();
													
			if ((finder.IsDirectory()) && (!finder.IsDots()))
			{
				subOpts = opts;
				subOpts.sBaseFolder = opts.sBaseFolder + finder.GetFileName();

				// Recursive call
				Find(subOpts);
			}
		}
	}

	finder.Close();
	
	
	_sSearchingFolder = opts.sBaseFolder;

	// Call callback procedure
	if (_pFileFinderProc != NULL)
		_pFileFinderProc(this, FF_FOLDER, _pCustomParam);

	sFullMask = opts.sBaseFolder + opts.sFileMask;
	//AfxMessageBox(sFullMask);
	bFound = finder.FindFile(sFullMask);
	while ((bFound) && (!_bStopSearch))
	{
		
	
		
		bFound = finder.FindNextFile();
		if (!finder.IsDots())
		{
			// check constrains
			bValidFile = TRUE;
			if (opts.dwOptionsFlags & FIND_ATTRIBUTES)
			{
				bValidFile = finder.MatchesMask(opts.dwFileAttributes);
			}

			if (bValidFile && (opts.dwOptionsFlags & FIND_SIZE))
			{
				bValidFile = ((opts.nMinSize <= finder.GetLength()) &&
							(opts.nMaxSize >= finder.GetLength()));
			}

			if (bValidFile && (opts.dwOptionsFlags & FIND_DATEMODIFIED))
			{
				finder.GetLastWriteTime(timeFile);
				bValidFile = ((timeFile >= opts.tMinModified) && 
								(timeFile <= opts.tMaxModified));
			}

			if (bValidFile && (opts.dwOptionsFlags & FIND_DATECREATED))
			{
				finder.GetCreationTime(timeFile);
				bValidFile = ((timeFile >= opts.tMinCreated) && 
								(timeFile <= opts.tMaxCreated));
			}

			if (bValidFile && (opts.dwOptionsFlags & FIND_DATEACCESSED))
			{
				finder.GetLastAccessTime(timeFile);
				bValidFile = ((timeFile >= opts.tMinAccessed) && 
								(timeFile <= opts.tMaxAccessed));
			}

			if (bValidFile && (opts.dwOptionsFlags & FIND_TEXT))
			{
				
				
				//bValidFile = FindTextInFile(finder.GetFilePath(), opts.sFindText);
				bValidFile = FindTextInFileAipi(finder.GetFilePath(), opts.sFindText);
			}



			/*
			// Add file to list
			if (bValidFile)
			{
				CString sName = finder.GetFilePath();
				if (finder.IsDirectory()) sName += _T("\\");
				_aFilesFound.Add(sName);
			}

			// Call callback procedure
			if (_pFileFinderProc != NULL)
				_pFileFinderProc(this, bValidFile ? FF_FOUND : FF_DISCARDED, _pCustomParam);
				*/

			if (bValidFile)
			{
				CString sName = finder.GetFilePath();
				if (finder.IsDirectory()) sName += "\\";

				// file name
				CString sN = finder.GetFileName();
				// position of dot in founded file
				int dot = sN.ReverseFind('.');
				// position of dot in mask
				int dotM = opts.sFileMask.ReverseFind('.');
				// get extension of founded file
				CString sFound = sN.Right(sN.GetLength() - dot - 1);
				// get extension of mask
				CString sMask = opts.sFileMask.Right(opts.sFileMask.GetLength() - dotM - 1);
				// position of * in mask
				int iPos = sMask.Find('*');

				// if "." exists in extension of mask
				if(dotM != -1)
				{
					// if length of extensions of mask and founded file are equal
					// for ex. mask: *.res, *.re?, founded file: answer.res
					if(sFound.GetLength() == sMask.GetLength())
					{
						_aFilesFound.Add(sName);
						bValidFile = TRUE;
					}
					// if length of extensions of mask and founded file are not equal
					if(sFound.GetLength() != sMask.GetLength())
					{
						// * exists in mask
						// for ex. mask: *.res*, founded file: answer.resa
						if(iPos != -1)
						{
							_aFilesFound.Add(sName);
							bValidFile = TRUE;
						}
						// * don't exists in mask
						else bValidFile = FALSE;
					}

				}
				else 
				{
					_aFilesFound.Add(sName);
					bValidFile = TRUE;
				}

			} // Call callback procedure
	
			if (_pFileFinderProc != NULL)
				_pFileFinderProc(this, bValidFile ? FF_FOUND : FF_DISCARDED, _pCustomParam);



		}
	}

	return GetFileCount();
}


BOOL CFileFinder::FindTextInFile(LPCTSTR szFile, LPCTSTR szText)
{
	if ((szText == NULL) || (szText == _T(""))) return FALSE;

	CFile file;

	if (!file.Open(szFile, CFile::modeRead)) return FALSE;

	const UINT	nCMinBufSize = 128;
	CString		sText = _T("");
	CString		sFindText(szText);
	UINT		nFindTextLen = sFindText.GetLength()*sizeof(TCHAR);
	UINT		nBufSize = 128; 
	UINT		nReadSize;
	UINT		nCharRead;
	LPTSTR		pTextBuf;
	BOOL		bTextFound;
	int			nLoopCount = 0;

	
	if ((2 * nFindTextLen) > nCMinBufSize)
		nBufSize = (2 * nFindTextLen);

	nReadSize = nBufSize - nFindTextLen;
	sFindText.MakeUpper();

	do
	{


		pTextBuf = sText.GetBuffer(nBufSize);
		
		
		if (pTextBuf[0] == 0x0)
		{
			memset((void*)pTextBuf, ' ', nFindTextLen);
			
		}
		else
		{
			memcpy((void*)pTextBuf, pTextBuf + (nBufSize - nFindTextLen), nFindTextLen );
			
		}
		
			
		nCharRead = file.Read(pTextBuf + nFindTextLen, nReadSize);
		
				
		sText.ReleaseBuffer(nFindTextLen + nCharRead);
		sText.Remove('\0');
		sText.MakeUpper();
		//AfxMessageBox(sText);		
		
		
		bTextFound = (sText.Find(sFindText) != -1);
			
		// Call callback procedure
		if (_pFileFinderProc != NULL)
		{
			nLoopCount++;
			if (nLoopCount == 10)
			{
				nLoopCount = 0;
				_pFileFinderProc(this, FF_FINDTEXT, _pCustomParam);
			}
		}
			
		
			
		
	} 
	while ((nCharRead == nReadSize) && !bTextFound);

	file.Close();

	return bTextFound;
}




/*

BOOL CFileFinder::FindTextInFile(LPCTSTR szFile, LPCTSTR szText)
{
	if ((szText == NULL) || (szText == _T(""))) return FALSE;
	
	
	CPathFinder	path(szFile);
	CTime	tModified;

	
	CString		sText = _T("");
	CString     sTempText = _T("");
	CString		sFindText(szText);

	CString	sFileSize	= _T("Undefine");
	CString sFileDate	= _T("Undefine");
	CString sPath		= _T("Undefine");
	CString sPos		= _T("Undefine");
	CString sLine		= _T("Undefine");
	CString	sFileName	= _T("Undefine");

	BOOL		bTextFound = FALSE;
	BOOL		bTempBool = FALSE;
	int			nLoopCount = 0;
	int iBufferSize = 1024;
	static int funcCall = 0;
	__int64	nSize64;
	long	nSize;
	_TCHAR buffer[1024];

	g_currentLine = 0;
	g_fcurrentPos = 0;
	
	
	
	//AfxMessageBox(szFile);
	
	sFindText.MakeUpper();
	

	
	
	
	// Byte-order mark goes at the begining of the UNICODE file
	_TCHAR bom;
	
		CFile* pFile = new CFile();
		pFile->Open( szFile, CFile::modeRead );
		pFile->Read( &bom, sizeof(_TCHAR) );
		pFile->Close();

		
		// If we are reading UNICODE file
		if ( bom == _TCHAR(0xFEFF ) )
		{
			
		

			  
			CFile* pFile = new CFile();
			pFile->Open( szFile, CFile::modeRead );
			
			
				
				pFile->Read( &bom, sizeof(_TCHAR) );
				UINT nCharRead = pFile->Read( buffer, _tcslen(buffer)*sizeof(_TCHAR) );
				while ( nCharRead != 0 )
				{
					
					buffer[nCharRead] = _T('\0');

					sTempText = buffer;

					// Release extra characters
					int nLen = sTempText.GetLength();
					strText = sTempText.Left( nLen/2 );

					sText = sTempText;
					sText.ReleaseBuffer();
					sText.Remove('\0');
					sText.MakeUpper();

					bTextFound = (sText.Find(sFindText) != -1);
					if( bTextFound)
					{
						//AfxMessageBox(sText);
						g_fcurrentPos = pFile->GetPosition();
						bTempBool = TRUE;
					}
					// Call callback procedure
					if (_pFileFinderProc != NULL)
					{
						nLoopCount++;
						if (nLoopCount == 10)
						{
							nLoopCount = 0;
							_pFileFinderProc(this, FF_FINDTEXT, _pCustomParam);
						}
					}

					nCharRead = pFile->Read( buffer, _tcslen(buffer)*sizeof(_TCHAR) );
				}
			pFile->Close();
		}
		
		
		
		// If we are reading ANSI file
		//else
		//{
						

			CStdioFile* pStdioFile = new CStdioFile();
			pStdioFile->Open( szFile, CFile::modeRead );
			

			while ( pStdioFile->ReadString( sTempText ) )
			{
				++g_currentLine;
				
				sText = sTempText;
				sText.ReleaseBuffer();
				sText.Remove('\0');
				sText.MakeUpper();
				//AfxMessageBox(sText);

				
				bTextFound = (sText.Find(sFindText) != -1);
								

				if( bTextFound)
				{
							
					//AfxMessageBox(sText);
					UINT fPos = pStdioFile->GetPosition();
					UINT fLen = pStdioFile->GetLength();
					if( fPos != fLen )
					{
						fPos = fPos -2;
					}
					UINT nTxtPos = sText.Find(sFindText);
					UINT nTxtLen = sText.GetLength();
					g_fcurrentPos = fPos - (nTxtLen - nTxtPos);
					bTempBool = TRUE;

					sPos = _itot(g_fcurrentPos, buffer, 10);
					sLine = _itot(g_currentLine + 1, buffer, 10);

					LPTSTR lpszLine		= sLine.GetBuffer(iBufferSize);
					LPTSTR lpszPos		=  sPos.GetBuffer(iBufferSize);
					LPTSTR lpszText		= (LPTSTR)sText.GetBuffer(iBufferSize);
					g_fText = sText;

					//if( _findTextInFiles != funcCall)
					//{
						//AfxMessageBox(_T("Entro"));
						
						// File size
						path.GetFileSize(nSize64);
						nSize = (long) (nSize64 / (__int64)1024);
	
						if (nSize < 10)
							sFileSize.Format(_T("%ld B"), nSize64);
						else
							sFileSize.Format(_T("%ld KB"), nSize);

						// File modified date
						path.GetFileTime(tModified);
						sFileDate = tModified.FormatGmt(_T("%d-%m-%Y %I:%M %p"));
						sPath = path.GetLocation();
						sFileName = path.GetFileName();   
		
	
						LPTSTR lpszFilePath	= (LPTSTR)sPath.GetBuffer(iBufferSize);
						LPTSTR lpszFileName	= (LPTSTR)sFileName.GetBuffer(iBufferSize);
						LPTSTR lpszFileSize	= (LPTSTR)sFileSize.GetBuffer(iBufferSize);
						LPTSTR lpszFileDate	= (LPTSTR)sFileDate.GetBuffer(iBufferSize);


																
						// Call callback procedure
						if (_pFileFinderProc != NULL)
						{
							nLoopCount++;
							if (nLoopCount == 10)
							{
								nLoopCount = 0;
								_pFileFinderProc(this, FF_FINDTEXT, _pCustomParam);
							}
						}
						

						// Add file to list
						if (bTempBool)
						{
							CString sName = sPath + _T("\\") + sFileName;
							//CFileFind	finder;
							//CString sName = finder.GetFilePath();
							//if (finder.IsDirectory()) sName += "\\";
							_aFilesFound.Add(sName);
						}

						// Call callback procedure
						if (_pFileFinderProc != NULL)
							_pFileFinderProc(this, bTempBool ? FF_FOUND : FF_DISCARDED, _pCustomParam);

						//CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
						//pMainFrame->m_wndOutputTabView.AddFindInFilesListCtrl3(lpszPos, lpszLine, lpszFilePath, lpszFileName, lpszFileSize, lpszFileDate, lpszText); 
						//pMainFrame->m_wndOutputTabView.FileFinderProc(this, FF_FOUND, _pCustomParam);
						 //pMainFrame->m_wndOutputTabView.FileFinderProcParam(this, FF_FOUND, _pCustomParam,lpszPos, lpszLine, lpszFilePath, lpszFileName, lpszFileSize, lpszFileDate, lpszText );	
				}
				

			}
			
			pStdioFile->Close();
		//}

	++funcCall;					
		
return bTempBool;	

}
*/



BOOL CFileFinder::FindTextInFileAipi(LPCTSTR szFile, LPCTSTR szText)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 0, 0);
	pMainFrame->m_wndStatusBar.SetUpBar(1, TRUE, TRUE);
	

	if ((szText == NULL) || (szText == _T(""))) return FALSE;
	
	
	
	CString		sText = _T("");
	CString     sTempText = _T("");
	CString		sFindText(szText);

	BOOL		bTextFound = FALSE;
	BOOL		bValidFile = FALSE;
	

	g_currentLine = -1;
	g_fcurrentPos = 0;
	
	
	sFindText.MakeUpper();

	
	


	CFileException e;
	CStdioFile* pStdioFile = new CStdioFile();
	if( !pStdioFile->Open( szFile, CFile::modeRead ))
	{
//#ifdef _DEBUG
   //afxDump << _T("File could not be opened " << e.m_cause << "\n");
//#endif
		return FALSE;
	}
	
	CString str;
	DWORD fLen  = pStdioFile->GetLength();
	//str.Format(_T("File Len %d"), fLen);
	//AfxMessageBox(str);

		
	while ( pStdioFile->ReadString( sTempText ) )
	{
		
		//Status Bar
		long lPos = pStdioFile->GetPosition();
		

		pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, (lPos*100)/fLen);
		

		++g_currentLine;
				
		sText = sTempText;
		sTempText.ReleaseBuffer();
		sText.ReleaseBuffer();
		sText.Remove('\0');
		sText.MakeUpper();
		//AfxMessageBox(sText);

		bTextFound = (sText.Find(sFindText) != -1);
								
		if( bTextFound)
		{
			//AfxMessageBox(sText);
			//str.Format(_T("File Pos %d"), lPos);
			//AfxMessageBox(str);
			
			UINT fPos = pStdioFile->GetPosition();
			UINT fLen = pStdioFile->GetLength();
			if( fPos != fLen )
				fPos = fPos -2;
			
			UINT nTxtPos = sText.Find(sFindText);
			UINT nTxtLen = sText.GetLength();
			g_fcurrentPos = fPos - (nTxtLen - nTxtPos);
			bValidFile = TRUE;

			g_fText = sTempText;

			CPathFinder	path(szFile);			
		
			CString sPath = path.GetLocation();
			CString sFileName = path.GetFileName(); 
			CString sName = sPath + sFileName;
			_aFilesFound.Add(sName);


			CFileStatus status;
			pStdioFile->GetStatus( status ); 
			pMainFrame->m_wndOutputTabView.m_fSize = status.m_size;
			pMainFrame->m_wndOutputTabView.m_fDate = status.m_mtime;
			


			
						
			// Call callback procedure
			if (_pFileFinderProc != NULL)
			{
				_pFileFinderProc(this, bValidFile ? FF_FOUND : FF_DISCARDED, _pCustomParam);
			}

							
		}
				

	}
			
	pStdioFile->Close();
		

	
return FALSE;	

}



BOOL CFileFinder::FindTextInFileExt(LPCTSTR szFile, LPCTSTR szText)
{
	if ((szText == NULL) || (szText == _T(""))) return FALSE;
	
	
	CString		sText = _T("");
	CString     sTempText = _T("");
	CString		sFindText(szText);

	BOOL		bTextFound = FALSE;
	BOOL		bValidFile = FALSE;
	

	g_currentLine = 0;
	g_fcurrentPos = 0;
	int nLoopCount = 0;
	
	
	sFindText.MakeUpper();


	CFileException e;
	CStdioFile* pStdioFile = new CStdioFile();
	if( !pStdioFile->Open( szFile, CFile::modeRead ))
	{
		return FALSE;
	}
			

	while ( pStdioFile->ReadString( sTempText ) )
	{
		++g_currentLine;
				
		sText = sTempText;
		sTempText.ReleaseBuffer();
		sText.ReleaseBuffer();
		sText.Remove('\0');
		sText.MakeUpper();
		//AfxMessageBox(sText);

		bTextFound = (sText.Find(sFindText) != -1);
								
		if( bTextFound)
		{
			//AfxMessageBox(sText);
			UINT fPos = pStdioFile->GetPosition();
			UINT fLen = pStdioFile->GetLength();
			if( fPos != fLen )
				fPos = fPos -2;
			
			UINT nTxtPos = sText.Find(sFindText);
			UINT nTxtLen = sText.GetLength();
			g_fcurrentPos = fPos - (nTxtLen - nTxtPos);
			bValidFile = TRUE;

			g_fText = sTempText;

				
			// Call callback procedure
			if (_pFileFinderProc != NULL)
			{
				nLoopCount++;
				if (nLoopCount == 10)
				{
					nLoopCount = 0;
					_pFileFinderProc(this, FF_FINDTEXT, _pCustomParam);
				}
			}

							
		}
				

	}
			
	pStdioFile->Close();
		

	
return bValidFile;	

}


int CFileFinder::GetFileCount()
{
	return _aFilesFound.GetSize();
}

int CFileFinder::FindPathItem(LPCTSTR szPath)
{
	bool	bFound;
	int		nIndex;

	for (nIndex = 0; nIndex < _aFilesFound.GetSize(); nIndex++)
	{
		bFound = (_aFilesFound[nIndex].CompareNoCase(szPath) == 0);
		if (bFound) break;
	}

	return (bFound ? nIndex : -1);
}

CPathFinder CFileFinder::GetFilePath(int nIndex)
{
	/*
	if ((nIndex < 0) || (nIndex >= GetFileCount())) return _T("");

	return _aFilesFound[nIndex];
	*/
	if ((nIndex < 0) || (nIndex >= GetFileCount())) return _T("");
	CPathFinder t(_aFilesFound[nIndex]);
	return t;

}

LPCTSTR	CFileFinder::GetSearchingFolder()
{
	return _sSearchingFolder;
}

void CFileFinder::RemoveAt(int nIndex)
{
	if ((nIndex < 0) || (nIndex >= GetFileCount())) return;

	_aFilesFound.RemoveAt(nIndex);
}

void CFileFinder::RemoveAll()
{
	if (GetFileCount() > 0) _aFilesFound.RemoveAll();
}

void CFileFinder::SetCallback(FILEFINDERPROC pFileFinderProc, void *pCustomParam)
{
	_pFileFinderProc = pFileFinderProc;
	_pCustomParam = pCustomParam;
}

void CFileFinder::StopSearch()
{
	_bStopSearch = true;
}

