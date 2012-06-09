// PageFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "PageFileDlg.h"
#include "PageInsertDlg.h"
#include "InductionTabView.h"


#include "MainFrm.h"

#include ".\GridCtrl\GridCtrl.h"
#include ".\DataFileCSV\CDataFile.h"
#include ".\BasicExcel\BasicExcelVC6.hpp"




#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageFileDlg dialog


CPageFileDlg::CPageFileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPageFileDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPageFileDlg)
	
	
	//}}AFX_DATA_INIT
	//ASSERT(pParent != NULL);

}


void CPageFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageFileDlg)
	DDX_Control(pDX, IDC_STATIC_NROWS, m_nRows);
	DDX_Control(pDX, IDC_STATIC_NCOLS, m_nCols);
	
	DDX_Control(pDX, IDC_CHECK_VIEWTABLES, m_chkTables);
	DDX_Control(pDX, IDC_CHECK_VIEWQUERY, m_chkQuery);
	DDX_Control(pDX, IDC_CHECK_VIEWDATA, m_chkData);
	DDX_Control(pDX, IDC_CHECK_TABLEV, m_chkVTables);
	
	DDX_Control(pDX, IDC_STATIC_SEPARATOR02, m_stcSeparator02);
	DDX_Control(pDX, IDC_STATIC_SEPARATOR03, m_stcSeparator03);
	DDX_Control(pDX, IDC_STATIC_SEPARATOR04, m_stcSeparator04);
	DDX_Control(pDX, IDC_STATIC_SEPARATOR05, m_stcSeparator05);
	DDX_Control(pDX, IDC_STATIC_SEPARATOR, m_stcSeparator);
	
	DDX_Control(pDX, IDC_BTN_OPENFILE, m_btnOpenFile);
	DDX_Control(pDX, IDC_BTN_CONNECTDB, m_btnConnectDB);
	DDX_Control(pDX, IDC_BTN_EXECQUERY, m_btnExecQuery);
	DDX_Control(pDX, IDC_CHK_VIRTUALMODE, m_chkVirtualMode);
	DDX_Control(pDX, IDC_CHK_CALLBACKFUNCTION, m_chkCallback);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageFileDlg, CDialog)
	//{{AFX_MSG_MAP(CPageFileDlg)
	ON_BN_CLICKED(IDC_BTN_OPENFILE, OnBtnOpenFile)
	ON_BN_CLICKED(IDC_BTN_CONNECTDB, OnBtnConnectDB)
	
	
	ON_BN_CLICKED(IDC_BTN_SAVEAS, OnBtnSaveAs)
	ON_BN_CLICKED(IDC_CHECK_VIEWQUERY, OnCheckViewQuery)
	ON_BN_CLICKED(IDC_CHECK_VIEWTABLES, OnCheckViewTables)
	ON_BN_CLICKED(IDC_CHECK_VIEWDATA, OnCheckViewData)
	ON_BN_CLICKED(IDC_CHECK_TABLEV, OnCheckTableV)
	ON_BN_CLICKED(IDC_BTN_EXECQUERY, OnBtnExecQuery)

	ON_BN_CLICKED(IDC_CHK_VIRTUALMODE, OnChkVirtualMode)
	ON_BN_CLICKED(IDC_CHK_CALLBACKFUNCTION, OnChkCallback)
	//}}AFX_MSG_MAP


END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPageFileDlg message handlers

/*
void CPageFileDlg::SelectGrid()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	switch(pMainFrame->m_CurrentGrid)
	{
			case GRID_INDUCTION:
				m_pGrid = &pMainFrame->m_GridInduction;
				break;
			case GRID_PM:
				m_pGrid = &pMainFrame->m_GridPM;
				break;
				case GRID_WM:
				m_pGrid = &pMainFrame->m_GridWM;
				break;
			case GRID_AGENDA:
				m_pGrid = &pMainFrame->m_GridAgenda;
				break;
			case GRID_AM:
				m_pGrid = &pMainFrame->m_GridAM;
				break;
			case GRID_BM:
				m_pGrid = &pMainFrame->m_GridBM;
				break;
			case GRID_RETE:
				m_pGrid = &pMainFrame->m_GridRETE;
				break;
	
	}


}

*/


int CPageFileDlg::LA_isNumeric(CString t)
{
	
	if( t == _T("0") || t == _T("1") || t == _T("2") || t == _T("3") || t == _T("4") || 
		t == _T("5") || t == _T("6") || t == _T("7") || t == _T("8") || t == _T("9") || 
		t == _T("-") || t == _T("+") )
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
}


void CPageFileDlg::StopTimer(CPerfTimer t, CString msg)
{
	CString str;
	t.Stop();
	str.Format(msg + _T("%0.4f"),t.Elapsed());
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndOutputTabView.IsVisible())
	{
		pMainFrame->m_wndOutputTabView.m_TabViewContainer.SetActivePageIndex(0);
		pMainFrame->m_wndOutputTabView.AddMsg1(str);
		
	}
	
}



/*
void CPageFileDlg::OnBtnOpenFile() 
{
	
	const static _TCHAR BASED_CODE szFilter[] = _T("Data Files (*.csv)|*.csv|All Files (*.*)|*.*||");

	CFileDialog Fdlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);
	
	//Set progress bar
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 0, 0);
	pMainFrame->m_wndStatusBar.SetUpBar(1, TRUE, TRUE);
	
	
 	if(Fdlg.DoModal() == IDOK)
 	{
 		
		CString str;
		SelectGrid();
		m_pGrid->ShowWindow(SW_HIDE);
				
		CPerfTimer T;
		T.Start(TRUE);
		
		CAipi_DT_ID3 dt;
		dt.ClearAll();
		
		pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Copying data to Memory..."), RGB(0,0,0), TRUE);
		pMainFrame->m_wndStatusBar.ResetBar(1);
		
				
		//Delete previous data
		m_pListCtrl1->DeleteAllItems();
		m_pListCtrl2->DeleteAllItems();
		m_pGrid->DeleteAllItems();
		g_df.ClearData();

		UnCheckListCtrl1();	
			
		UpdateData();
		
		
		TCHAR sBuffer[BUFF_SIZE];
		CString sPath = Fdlg.GetPathName();
		CString szValue = _T("");
		int iLength = 0;
		
		
				
		g_df.SetReadFlags(DF::RF_READ_AS_STRING);
		if(!g_df.ReadFile(sPath))
		{
			MessageBox(g_df.GetLastError());
			return;
		}
		
		
		int dfMaxCols = g_df.GetNumberOfVariables();
		int dfMaxRows = g_df.GetNumberOfSamples(0);

			
		if( dfMaxRows && dfMaxCols == 0 )
		{
			MessageBox(g_df.GetLastError());
		}

		
		

		CInductionTabView tab;
		if( tab.m_RollupCtrl.IsPageExpanded(2) == true)
		{
			

			pInsertPage->m_nMaxCols = dfMaxCols + 1;
			pInsertPage->m_nMaxRows = dfMaxRows + 1;
			pInsertPage->m_nMaxFixCols = pMainFrame->m_wndInductionTabView.m_nFixCols;
			pInsertPage->m_nMaxFixRows = pMainFrame->m_wndInductionTabView.m_nFixRows + 1;
			pInsertPage->UpdateData(false);

		
			str.Format(_T("%d Rws."), pInsertPage->m_nMaxRows);
			m_nRows.SetWindowText(str);
			str.Format(_T("%d Cols."), pInsertPage->m_nMaxCols);
			m_nCols.SetWindowText(str);

				
			
			TRY 
			{
				m_pGrid->SetRowCount(pInsertPage->m_nMaxRows);
				m_pGrid->SetColumnCount(pInsertPage->m_nMaxCols);
				m_pGrid->SetFixedRowCount(pInsertPage->m_nMaxFixRows);
				m_pGrid->SetFixedColumnCount(pInsertPage->m_nMaxFixCols);
	
			}
			CATCH (CMemoryException, e)
			{
	    	
				e->ReportError();
    			return;
			}
			END_CATCH
				
		
			pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Loading data..."), RGB(0,0,0), TRUE);		
		
			//Fill rows/cols with text
			for (int col = 0; col < pInsertPage->m_nMaxCols; ++col)
			{
			
				pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, col*100/dfMaxCols);
			

				//Fill ListCtrl1 with header name
				if( col < dfMaxCols )
				{
				
					iLength = g_df.GetVariableName(col, szValue.GetBuffer(BUFF_SIZE));
					if(iLength == -1 )
					{
						MessageBox((LPCTSTR)g_df.GetLastError());
						return;
					}
					wsprintf(sBuffer, szValue);
				
					m_pGrid->SetItemText(pMainFrame->m_wndInductionTabView.m_nFixCols, col+1, szValue);
				
					LVITEM  Item;
				
					Item = AddListItem1(col, 0, sBuffer);
					CString strNo = _itot(col, sBuffer, 10);
					LPTSTR lpszNo = strNo.GetBuffer(BUFF_SIZE);
					AddListSubItem1(Item, col, 1, _T("Input"));
				
					std::tstring strValue = _T("");
					iLength = g_df.GetData(col, 0, strValue);
					if(iLength == -1 )
					{
						MessageBox(g_df.GetLastError());
						return;
					}
					else
					{
						//Check for missing data to avoid crash with GetAt()
						szValue = strValue.data();
						int row = 0;
						if(szValue.IsEmpty())
						{
							for(int i = 1; i<pInsertPage->m_nMaxRows; i++)
							{
								iLength = g_df.GetData(col, i, strValue);
								if(iLength == -1 )
								{
									MessageBox(g_df.GetLastError());
									return;
								}
								szValue = strValue.data();
								if(!szValue.IsEmpty())
								{
									break;
									row++;
								}

							}
						}
						//If there is no data in all the table
						if(row == pInsertPage->m_nMaxRows)
						{
							AddListSubItem1(Item, col, 2, _T("Unknown"));
							AddListSubItem1(Item, col, 3, lpszNo);
						}
						else
						{
							if(LA_isNumeric(szValue.GetAt(0)))
								AddListSubItem1(Item, col, 2, _T("Numeric"));
							else 
								AddListSubItem1(Item, col, 2, _T("Nominal"));
						}
					
					}
				
					AddListSubItem1(Item, col, 3, lpszNo);
			
				
				}		
			
				//Populate grid control
				for (int row = 0; row < pInsertPage->m_nMaxRows; ++row)
				{ 
               	
					if( col < dfMaxCols && row < dfMaxRows )
					{
					
						//Fill data
						iLength = g_df.GetData(col, row, szValue.GetBuffer(BUFF_SIZE));
						if(iLength == -1 )
						{
							MessageBox(g_df.GetLastError());
							return;
						}
						wsprintf(sBuffer, szValue);
						m_pGrid->SetItemText(row+2, col+1, szValue);
					
					}

					if (row < pMainFrame->m_wndInductionTabView.m_nFixRows)
					{
						//Set Column Number
						str.Format(_T("C%d"),col);
						m_pGrid->SetItemText(row, col, str);
					
		
					
					}
					else if (col < pMainFrame->m_wndInductionTabView.m_nFixCols)
					{
						//Set Row Number
						str.Format(_T("R%d"), row);
						m_pGrid->SetItemText(row, col, str);
					
					
					}
                							
	    		}
			}

	
		}//End m_RollupCtrl Expanded if
		
		szValue.ReleaseBuffer();
		m_pGrid->AutoSize();
		m_pGrid->ShowWindow(SW_SHOW);
				
			
		
		str.Format(_T("Elapsed Seconds: %0.4f"), T.Elapsed());
		
		
		if ( !pMainFrame->m_wndOutputTabView.IsVisible())
		{
			pMainFrame->m_wndOutputTabView.ShowWindow(TRUE);
			pMainFrame->m_wndOutputTabView.m_TabViewContainer.SetActivePageIndex(0);
			pMainFrame->m_wndOutputTabView.AddMsg1(str);
		
		}
		
		T.Stop();

		pMainFrame->m_wndStatusBar.ResetBar(1, TRUE);
		pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Process finished"), RGB(0,0,0), TRUE);
		
				
		pMainFrame->m_wndInductionTabView.Init_Data_Page2();
		m_chkQuery.EnableWindow(FALSE);
		m_chkTables.EnableWindow(FALSE);
		m_chkVTables.EnableWindow(FALSE);
		m_chkData.EnableWindow(FALSE);
		m_btnExecQuery.EnableWindow(FALSE);

		m_chkData.SetCheck(FALSE);
		m_chkQuery.SetCheck(FALSE);
		m_chkTables.SetCheck(FALSE);
					
		
	}
 	
	
 			
}
*/


void CPageFileDlg::OnBtnOpenFile() 
{
	
	const static _TCHAR BASED_CODE szFilter[] = _T("Data Files (*.csv)|*.csv|All Files (*.*)|*.*||");

	CFileDialog Fdlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);
	
	//Set progress bar
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 0, 0);
	pMainFrame->m_wndStatusBar.SetUpBar(1, TRUE, TRUE);
	
	
 	if(Fdlg.DoModal() == IDOK)
 	{
 		
		CString str;
		pMainFrame->SelectGrid();
		m_pGrid->ShowWindow(SW_HIDE);
				
		CPerfTimer T;
		T.Start();
		
		CAipi_DT_ID3 dt;
		dt.ClearAll();
		
		pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Copying data to Memory..."), RGB(0,0,0), TRUE);
		pMainFrame->m_wndStatusBar.ResetBar(1);
		
				
		//Delete previous data
		m_pListCtrl1->DeleteAllItems();
		m_pListCtrl2->DeleteAllItems();
		m_pGrid->DeleteAllItems();
		g_df.ClearData();

		UnCheckListCtrl1();	
			
		UpdateData();
		
		
		TCHAR sBuffer[BUFF_SIZE];
		CString sPath = Fdlg.GetPathName();
		CString szValue = _T("");
		int iLength = 0;
		
		
				
		g_df.SetReadFlags(DF::RF_READ_AS_STRING);
		if(!g_df.ReadFile(sPath))
		{
			MessageBox(g_df.GetLastError());
			return;
		}
		
		
		int dfMaxCols = g_df.GetNumberOfVariables();
		int dfMaxRows = g_df.GetNumberOfSamples(0);

			
		if( dfMaxRows && dfMaxCols == 0 )
		{
			MessageBox(g_df.GetLastError());
		}

		
		
		
		
			

		g_iColumn = dfMaxCols + 1;
		g_iRow = dfMaxRows + 1;
		g_iFixColumn = pMainFrame->m_wndInductionTabView.m_nFixCols;
		g_iFixRow = pMainFrame->m_wndInductionTabView.m_nFixRows + 1;
		
		
		str.Format(_T("%d Rws."), g_iRow -1);
		m_nRows.SetWindowText(str);
		str.Format(_T("%d Cols."), g_iColumn -1);
		m_nCols.SetWindowText(str);

		
		
		
		
			
		TRY 
		{
		    m_pGrid->SetRowCount(g_iRow);
		    m_pGrid->SetColumnCount(g_iColumn);
		    m_pGrid->SetFixedRowCount(g_iFixRow);
		    m_pGrid->SetFixedColumnCount(g_iFixColumn);
	
	    }
	    CATCH (CMemoryException, e)
	    {
	    	
			e->ReportError();
    		return;
	    }
        END_CATCH
				
		
		pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Loading data..."), RGB(0,0,0), TRUE);		
		
		//Fill rows/cols with text
	    for (int col = 0; col < g_iColumn; ++col)
        {
			
			pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, col*100/dfMaxCols);
			

			//Fill ListCtrl1 with header name
			if( col < dfMaxCols )
			{
				
				iLength = g_df.GetVariableName(col, szValue.GetBuffer(BUFF_SIZE));
				if(iLength == -1 )
				{
					MessageBox((LPCTSTR)g_df.GetLastError());
					return;
				}
				wsprintf(sBuffer, szValue);
				
				m_pGrid->SetItemText(pMainFrame->m_wndInductionTabView.m_nFixCols, col+1, szValue);
				
				LVITEM  Item;
				
				Item = AddListItem1(col, 0, sBuffer);
				CString strNo = _itot(col+1, sBuffer, 10);
				LPTSTR lpszNo = strNo.GetBuffer(BUFF_SIZE);
				AddListSubItem1(Item, col+1, 1, _T("Input"));
				
				std::tstring strValue = _T("");
				iLength = g_df.GetData(col, 0, strValue);
				if(iLength == -1 )
				{
					MessageBox(g_df.GetLastError());
					return;
				}
				else
				{
					//Check for missing data to avoid crash with GetAt()
					szValue = strValue.data();
					int row = 0;
					if(szValue.IsEmpty())
					{
						for(int r = 1; r<g_iRow; r++)
						{
							iLength = g_df.GetData(col, r, strValue);
							if(iLength == -1 )
							{
								MessageBox(g_df.GetLastError());
								return;
							}
							szValue = strValue.data();
							if(!szValue.IsEmpty())
							{
								break;
								row++;
							}
							

						}
					}
					//If there is no data in all the table
					if(row == g_iRow)
					{
						AddListSubItem1(Item, col, 2, _T("Unknown"));
						AddListSubItem1(Item, col, 3, lpszNo);
					}
					else
					{
						if(LA_isNumeric(szValue.GetAt(0)))
							AddListSubItem1(Item, col, 2, _T("Numeric"));
						else 
							AddListSubItem1(Item, col, 2, _T("Nominal"));
					}
					
				}
				
				AddListSubItem1(Item, col, 3, lpszNo);
			
				
			}		
			
			//Populate grid control
			for (int row = 0; row < g_iRow; ++row)
		    { 
               	
				if( col < dfMaxCols && row < dfMaxRows )
				{
					
					//Fill data
					iLength = g_df.GetData(col, row, szValue.GetBuffer(BUFF_SIZE));
					if(iLength == -1 )
					{
						MessageBox(g_df.GetLastError());
						return;
					}
					wsprintf(sBuffer, szValue);
					m_pGrid->SetItemText(row+2, col+1, szValue);
					
					
				}

				if (row < pMainFrame->m_wndInductionTabView.m_nFixRows)
				{
                    //Set Column Number
					str.Format(_T("C%d"),col);
					m_pGrid->SetItemText(row, col, str);
									
				}
                else if (col < pMainFrame->m_wndInductionTabView.m_nFixCols)
				{
                    //Set Row Number
					str.Format(_T("R%d"), row);
					m_pGrid->SetItemText(row, col, str);
					
					
				}
                							
	    	}
        }

	
		
		
		szValue.ReleaseBuffer();
		m_pGrid->AutoSize();
		m_pGrid->ShowWindow(SW_SHOW);
				
			
		StopTimer(T, _T("File opening elapsed seconds... "));
		
		

		pMainFrame->m_wndStatusBar.ResetBar(1, TRUE);
		pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Process finished"), RGB(0,0,0), TRUE);
		
				
		pMainFrame->m_wndInductionTabView.Init_Data_Page2();
		m_chkQuery.EnableWindow(FALSE);
		m_chkTables.EnableWindow(FALSE);
		m_chkVTables.EnableWindow(FALSE);
		m_chkData.EnableWindow(FALSE);
		m_btnExecQuery.EnableWindow(FALSE);

		m_chkData.SetCheck(FALSE);
		m_chkQuery.SetCheck(FALSE);
		m_chkTables.SetCheck(FALSE);
					
		
	}
 	
	
 			
}

void CPageFileDlg::OnBtnSaveAs() 
{

	const static _TCHAR BASED_CODE szFilter[] = _T("Data Files (*.csv)|*.csv|All Files (*.*)|*.*||");
	

	CFileDialog Fdlg(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);

	if(Fdlg.DoModal() == IDOK)
 	{
		UpdateData();		
		
		CString szPath = Fdlg.GetPathName() + _T(".csv");
		CString szValue = _T("");
		CString szColName = _T("");
		int iLength = 0;
		int iSize = 0;
			
		CDataFile df(DF::RF_READ_AS_STRING);

		iLength =	m_pGrid->GetColumnCount() - m_pGrid->GetFixedColumnCount();
		iSize =		m_pGrid->GetRowCount() - m_pGrid->GetFixedRowCount();
		
		
		//Get data from GridCtrl
		for( int col = 0; col<iLength; col++)
		{
			
			szColName = m_pGrid->GetItemText(1, col + m_pGrid->GetFixedColumnCount());
			if(!df.CreateVariable(szColName.GetBuffer(BUFF_SIZE), _T(""), iSize))
			{
				MessageBox(df.GetLastError());
				return;
			}
			
				szColName.ReleaseBuffer();
		
			
			for(int row = 0; row<iSize; row++)
			{
				szValue = m_pGrid->GetItemText(row + m_pGrid->GetFixedRowCount() , col + m_pGrid->GetFixedColumnCount());
				if(!df.SetData(col  , row , szValue.GetBuffer(BUFF_SIZE)))
				{
					MessageBox(df.GetLastError());
					return;
				}
				
				szValue.ReleaseBuffer();
			}
			
		}

		//Write file
		if(!df.WriteFile(szPath.GetBuffer(BUFF_SIZE), _T(",")) )
		{
			MessageBox(df.GetLastError());
			return;
		}
		
		//Clear data
		df.ClearData();	
	}
	
		
}


void CPageFileDlg::OnBtnConnectDB() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	
	int iDBtype = 0;
		

	if ( pMainFrame->m_wndInductionTabView.IsVisible() )
	{
		CPerfTimer T;
		T.Start();
		
		pMainFrame->m_wndInductionTabView.OnOpenDatabaseConnection(MS_ACCESS);
		
		StopTimer(T, _T("Data Base Connection Elapsed Seconds... "));
		
		pMainFrame->m_wndInductionTabView.Init_Query_Tables_Data_Page2();
	}
	
	m_chkQuery.EnableWindow(TRUE);
	m_chkTables.EnableWindow(TRUE);
	m_chkVTables.EnableWindow(TRUE);
	m_chkData.EnableWindow(TRUE);
	m_btnExecQuery.EnableWindow(TRUE);

	m_chkData.SetCheck(TRUE);
	m_chkQuery.SetCheck(TRUE);
	m_chkTables.SetCheck(TRUE);

	
	

}

void CPageFileDlg::UnCheckListCtrl1()
{
	HDITEM hdItem;
	hdItem.mask = HDI_IMAGE | HDI_FORMAT;
	VERIFY( m_pListCtrl1->m_checkHeadCtrl.GetItem(0, &hdItem) );
	hdItem.iImage = 1;
	hdItem.fmt |= HDF_IMAGE;
	VERIFY( m_pListCtrl1->m_checkHeadCtrl.SetItem(0, &hdItem) );
}




BOOL CPageFileDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_chkQuery.EnableWindow(FALSE);
	m_chkTables.EnableWindow(FALSE);
	m_chkVTables.EnableWindow(FALSE);
	m_chkData.EnableWindow(FALSE);
	m_btnExecQuery.EnableWindow(FALSE);

	/*
	CRect rect;
	GetClientRect(rect);
	rect.left = rect.right - 100;
	rect.top += 60;
	rect.right -= 0;
	rect.bottom -= 130;

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CInductionTabView tab;

	BOOL bSuccess;
	bSuccess = tab.m_RollupCtrl.Create(WS_CHILD | WS_DLGFRAME | WS_VISIBLE, rect,  &pMainFrame->m_wndInductionTabView, IDC_ROLLUPCTRL);
	ASSERT(bSuccess);

	
	
	//Create CRollupCtrl Pages	
	pInsertPage = new CPageInsertDlg;
	m_pGrid = &pMainFrame->m_GridInduction;
	bSuccess = pInsertPage->Create(IDD_PAGEINSERT_DLG, &tab.m_RollupCtrl);
	tab.m_RollupCtrl.InsertPage(_T("Insert"), pInsertPage);
*/
	
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}




LVITEM CPageFileDlg::AddListItem1( int iItem, int iSubItem, LPTSTR szText)
{
	
	//Fills the first column
	LVITEM item;
	item.iItem = iItem;
	item.iSubItem = iSubItem;
	item.mask = LVIF_TEXT;
	item.pszText = szText;
	m_pListCtrl1->InsertItem(&item);

	return item;

}

LVITEM CPageFileDlg::AddListItem2( int iItem, int iSubItem, LPTSTR szText, int iImage)
{
	
	//Fills the first column
	LVITEM item;
	item.iItem = iItem;
	item.iSubItem = iSubItem;
	item.mask = LVIF_TEXT|LVIF_IMAGE;
	item.pszText = szText;
	item.iImage = iImage;
	m_pListCtrl2->InsertItem(&item);

	return item;

}

void CPageFileDlg::AddListSubItem1( LVITEM item, int iItem, int iSubItem, LPTSTR szText)
{
	//Fills the rest columns
	item.iSubItem = iSubItem;
	item.mask = LVIF_TEXT;
	item.pszText = szText;
	m_pListCtrl1->SetItem(&item);

	return;

}
	  
void CPageFileDlg::AddListSubItem2( LVITEM item, int iItem, int iSubItem, LPTSTR szText)
{
	//Fills the rest columns
	item.iSubItem = iSubItem;
	item.mask = LVIF_TEXT;
	item.pszText = szText;
	m_pListCtrl2->SetItem(&item);

	return;

}



void CPageFileDlg::ChangeInterfacesPage2()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		
		
	if (BST_CHECKED == m_chkQuery.GetCheck() && BST_CHECKED != m_chkTables.GetCheck()  && BST_CHECKED != m_chkData.GetCheck())
	{
		pMainFrame->m_wndInductionTabView.Init_Query_Page2();
		m_chkVTables.EnableWindow(FALSE);
		m_chkVTables.SetCheck(FALSE);
			
	}
	else if(BST_CHECKED != m_chkQuery.GetCheck() && BST_CHECKED == m_chkTables.GetCheck()  && BST_CHECKED != m_chkData.GetCheck())
	{
		pMainFrame->m_wndInductionTabView.Init_Tables_Page2();
		m_chkVTables.EnableWindow(FALSE);
		m_chkVTables.SetCheck(FALSE);

		
	}
	else if(BST_CHECKED != m_chkQuery.GetCheck() && BST_CHECKED != m_chkTables.GetCheck()  && BST_CHECKED == m_chkData.GetCheck())
	{
		pMainFrame->m_wndInductionTabView.Init_Data_Page2();
		m_chkVTables.EnableWindow(FALSE);
		m_chkVTables.SetCheck(FALSE);

		
	}
	
	
	
	
	else if(BST_CHECKED == m_chkQuery.GetCheck() && BST_CHECKED != m_chkTables.GetCheck()  && BST_CHECKED == m_chkData.GetCheck())
	{
		pMainFrame->m_wndInductionTabView.Init_Query_Data_Page2();
		m_chkVTables.EnableWindow(FALSE);
		m_chkVTables.SetCheck(FALSE);

		
	}
	else if(BST_CHECKED == m_chkQuery.GetCheck() && BST_CHECKED == m_chkTables.GetCheck() && BST_CHECKED != m_chkVTables.GetCheck() && BST_CHECKED != m_chkData.GetCheck())
	{
		pMainFrame->m_wndInductionTabView.Init_Query_Tables_Page2();
		m_chkVTables.EnableWindow(TRUE);
		
	}
	else if(BST_CHECKED == m_chkQuery.GetCheck() && BST_CHECKED == m_chkTables.GetCheck()  && BST_CHECKED != m_chkData.GetCheck())
	{
		pMainFrame->m_wndInductionTabView.Init_Query_Tables_Page2();
		m_chkVTables.EnableWindow(FALSE);
		
	}
	else if(BST_CHECKED != m_chkQuery.GetCheck() && BST_CHECKED == m_chkTables.GetCheck() && BST_CHECKED == m_chkVTables.GetCheck() && BST_CHECKED == m_chkData.GetCheck())
	{
		pMainFrame->m_wndInductionTabView.Init_VTables_Data_Page2();
		m_chkVTables.EnableWindow(TRUE);
		
	}
	else if(BST_CHECKED != m_chkQuery.GetCheck() && BST_CHECKED == m_chkTables.GetCheck() && BST_CHECKED != m_chkVTables.GetCheck() && BST_CHECKED == m_chkData.GetCheck())
	{
		pMainFrame->m_wndInductionTabView.Init_Tables_Data_Page2();
		m_chkVTables.EnableWindow(TRUE);
		
	}
	else if(BST_CHECKED == m_chkQuery.GetCheck() && BST_CHECKED == m_chkTables.GetCheck() && BST_CHECKED == m_chkVTables.GetCheck() && BST_CHECKED == m_chkData.GetCheck())
	{
		pMainFrame->m_wndInductionTabView.Init_Query_VTables_Data_Page2();
		m_chkVTables.EnableWindow(TRUE);
		
	}
	else if(BST_CHECKED == m_chkQuery.GetCheck() && BST_CHECKED == m_chkTables.GetCheck() && BST_CHECKED != m_chkVTables.GetCheck() && BST_CHECKED == m_chkData.GetCheck())
	{
		pMainFrame->m_wndInductionTabView.Init_Query_Tables_Data_Page2();
		m_chkVTables.EnableWindow(TRUE);
		
	}
	else if(BST_CHECKED != m_chkQuery.GetCheck() && BST_CHECKED != m_chkTables.GetCheck() && BST_CHECKED != m_chkData.GetCheck())
	{
		pMainFrame->m_wndInductionTabView.Init_Data_Page2();
		m_chkVTables.EnableWindow(FALSE);
		m_chkData.SetCheck(TRUE);
		m_chkVTables.SetCheck(FALSE);

	}

	else
	{
		AfxMessageBox(_T("ERROR: No se dió ningun caso"));
	}



}
void CPageFileDlg::OnCheckViewQuery() 
{
	ChangeInterfacesPage2();	
}

void CPageFileDlg::OnCheckViewTables() 
{
	ChangeInterfacesPage2();	
}

void CPageFileDlg::OnCheckViewData() 
{
	
	ChangeInterfacesPage2();	
}



void CPageFileDlg::OnCheckTableV() 
{
	ChangeInterfacesPage2();	
}

void CPageFileDlg::OnBtnExecQuery() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CString str;

	CPerfTimer T;
	T.Start();

	pMainFrame->m_wndInductionTabView.RunQuery();

	StopTimer(T, _T("Executing Query Elapsed Seconds... "));
		
	
	g_iRow = pMainFrame->m_GridInduction.GetRowCount()-1;
	g_iColumn = pMainFrame->m_GridInduction.GetColumnCount()-1;
	g_iFixRow = pMainFrame->m_GridInduction.GetFixedRowCount();
	g_iFixColumn = pMainFrame->m_GridInduction.GetFixedColumnCount();

	
	str.Format(_T("%d Rws."), g_iRow);
	m_nRows.SetWindowText(str);
	str.Format(_T("%d Cols."), g_iColumn);
	m_nCols.SetWindowText(str);
	
	UpdateData(false);	
}



void CPageFileDlg::OnChkVirtualMode() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_bVirtualMode = !pMainFrame->m_bVirtualMode;
	
	UpdateData();
	pMainFrame->SelectGrid();

/*	
	int dfMaxCols = g_df.GetNumberOfVariables();
	CString szHeader = _T("");

	for(int col = 0; col<dfMaxCols; ++col)
	{
		int iLength = g_df.GetVariableName(col, szHeader.GetBuffer(BUFF_SIZE));
		if(iLength == -1 )
		{
			//MessageBox(g_df.GetLastError());
			return;
		}
		m_pGrid->SetItemText(0, col, szHeader);
		
	}
	MessageBox(szHeader);
	szHeader.ReleaseBuffer();
*/
	
	
	m_pGrid->SetVirtualMode(pMainFrame->m_bVirtualMode);
	

    
    if (pMainFrame->m_bVirtualMode)
    {
        
		m_pGrid->SetCallbackFunc(pMainFrame->m_bCallback? GridCallback : NULL, 0);
		
		TRY {
			
		    m_pGrid->SetRowCount(g_iRow);
		    m_pGrid->SetColumnCount(g_iColumn);
		    m_pGrid->SetFixedRowCount(g_iFixRow);
		    m_pGrid->SetFixedColumnCount(g_iFixColumn);
			
	    }
	    CATCH (CMemoryException, e)
	    {
	    	e->ReportError();
    		return;
	    }
        END_CATCH
    }
    else
    {
        
	    TRY {
		    
			m_pGrid->SetRowCount(g_iRow);
		    m_pGrid->SetColumnCount(g_iColumn);
		    m_pGrid->SetFixedRowCount(g_iFixRow);
		    m_pGrid->SetFixedColumnCount(g_iFixColumn);
			
	    }
	    CATCH (CMemoryException, e)
	    {
	    	e->ReportError();
    		return;
	    }
        END_CATCH


	    // Set col/row width and height to its initial state
	    for (int row = 0; row < m_pGrid->GetRowCount(); row++)
        {
	    	for (int col = 0; col < m_pGrid->GetColumnCount(); col++)
		    { 
                
				CString str;

			    GV_ITEM Item;

    			Item.mask = GVIF_TEXT;
	    		Item.row = row;
		    	Item.col = col;

			    if (row < g_iFixRow - 1)
                    str.Format(_T("Column %d"),col);
                else if (col < g_iFixColumn) 
                    str.Format(_T("Row %d"), row);
                
				Item.strText = str;
				
				
				m_pGrid->SetItem(&Item);
				m_pGrid->SetColumnWidth(col, 80);
				m_pGrid->SetRowHeight(row, 18);
	    	
			}
        }
    
	
	}

    m_pGrid->GetDefaultCell(FALSE,FALSE)->SetFormat(DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_NOPREFIX|DT_END_ELLIPSIS);
    m_pGrid->GetDefaultCell(TRUE, FALSE)->SetFormat(DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_NOPREFIX|DT_END_ELLIPSIS);

    // Having weird Autosize problems with CE 2.11 - possibly just an emulation problem
#if !defined(_WIN32_WCE) || (_WIN32_WCE < 211)
	//m_pGrid->AutoSize();
#endif
	
    UpdateData(FALSE);	
}




void CPageFileDlg::OnChkCallback() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	pMainFrame->m_bCallback = !pMainFrame->m_bCallback;
    pMainFrame->SelectGrid();
	m_pGrid->SetCallbackFunc(pMainFrame->m_bCallback? GridCallback : NULL, 0);
    m_pGrid->Refresh();
    
}

BOOL CALLBACK CPageFileDlg::GridCallback(GV_DISPINFO *pDispInfo, LPARAM /*lParam*/) 
{
    pDispInfo->item.strText.Format(_T("Callback %d,%d"),pDispInfo->item.row, pDispInfo->item.col);
    
	return TRUE;
}





