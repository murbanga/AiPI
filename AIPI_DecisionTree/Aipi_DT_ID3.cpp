// Aipi_DT_ID3.cpp: implementation of the CAipi_DT_ID3 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../AIPI.h"
#include "../AIPITreeView.h"
#include "../MainFrm.h"
#include "../ChildFrm.h"
#include "../InductionTabView.h"
#include "../OutputTabView.h"

#include "Aipi_DT_ID3.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAipi_DT_ID3::CAipi_DT_ID3()
{

}

CAipi_DT_ID3::~CAipi_DT_ID3()
{

}


HTREEITEM CAipi_DT_ID3::AddSiblingName(CString name)
{
	CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
	CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
	CAIPITreeView* pView = (CAIPITreeView*) pChild->GetActiveView();
	ASSERT(pView);
	pView->m_etc.OnAddSiblingName(name);
	
	return pView->m_etc.GetSelectedItem();

}

HTREEITEM CAipi_DT_ID3::AddChildName(CString name)
{
	CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
	CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
	CAIPITreeView* pView = (CAIPITreeView*) pChild->GetActiveView();
	ASSERT(pView);
	
	pView->m_etc.OnAddChildName(name);
	
	return pView->m_etc.GetSelectedItem();
	
}



HTREEITEM CAipi_DT_ID3::FindNodeItem(CString name)
{
	CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
	CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
	CAIPITreeView* pView = (CAIPITreeView*) pChild->GetActiveView();
	ASSERT(pView);
	HTREEITEM hItem = pView->m_etc.OnFindItem(name);
	
	return hItem;
}




void CAipi_DT_ID3::SelectNodeItem(HTREEITEM hItem)
{
	CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
	CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
	CAIPITreeView* pView = (CAIPITreeView*) pChild->GetActiveView();
	ASSERT(pView);
	pView->m_etc.SelectItem(hItem);
}


void CAipi_DT_ID3::SetFocus()
{
	CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
	CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
	CAIPITreeView* pView = (CAIPITreeView*) pChild->GetActiveView();
	ASSERT(pView);
	pView->SetFocus();
}


void CAipi_DT_ID3::AddMsgOutputWnd(CString msg)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndOutputTabView.AddMsg1(msg);

}

void CAipi_DT_ID3::StopTimer(CPerfTimer t, CString msg)
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




int CAipi_DT_ID3::GetListCtrlAtributeIndex(CString name)
{
	LVFINDINFO pFindInfo;
	pFindInfo.flags = LVFI_PARTIAL|LVFI_STRING;
	pFindInfo.psz = name;
	
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	int pos = pMainFrame->m_wndInductionTabView.m_ListCtrl1.FindItem(&pFindInfo, -1);
	if( pos == -1)
	{
		AfxMessageBox(_T("ERROR: The atribute was not found."));
	}
	
	return pos; 
	
}

CString CAipi_DT_ID3::GetListCtrlAtributeName(int idAtribute)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	return pMainFrame->m_wndInductionTabView.m_ListCtrl1.GetItemText(idAtribute, 0);

}


CString CAipi_DT_ID3::GetListCtrlClassName()
{
	CString szNotFound = _T("NULL");

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	int n = pMainFrame->m_wndInductionTabView.m_ListCtrl1.GetItemCount();
	bool bAtributeCheck = false;
	
	//Check if data is load
	if( n > 0 )
	{
		
		for( int i = 0; i<n; ++i)
		{
			CString szClasifier = pMainFrame->m_wndInductionTabView.m_ListCtrl1.GetItemText(i, 1);
			bAtributeCheck = pMainFrame->m_wndInductionTabView.m_ListCtrl1.GetCheck(i);
			if( szClasifier == _T("Output") && bAtributeCheck == true )
			{
				return pMainFrame->m_wndInductionTabView.m_ListCtrl1.GetItemText(i, 0);
			}
		}
		
		if( bAtributeCheck == false)
			AfxMessageBox(_T("ERROR: No atributes were selected."));
		else
			AfxMessageBox(_T("ERROR: You must define a classifier atribute."));
	}
	else
	{
		AfxMessageBox(_T("ERROR: No atributes were loaded."));
	}
	
	return szNotFound; 
	
}

int CAipi_DT_ID3::GetListCtrlClassIndex()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	int n = pMainFrame->m_wndInductionTabView.m_ListCtrl1.GetItemCount();
	bool bAtributeCheck = false;

	if( n > 0 )
	{
		for( int i = 0; i<n; ++i)
		{
			CString szClasifier = pMainFrame->m_wndInductionTabView.m_ListCtrl1.GetItemText(i, 1);
			bAtributeCheck = pMainFrame->m_wndInductionTabView.m_ListCtrl1.GetCheck(i);
			if( szClasifier == _T("Output") && bAtributeCheck == true  )
			{
				return i;
			}
							
		}
	
		if( bAtributeCheck == false)
			AfxMessageBox(_T("ERROR: No atributes were selected."));
		else
			AfxMessageBox(_T("ERROR: You must define an output classifier atribute."));
	}
	else
	{
		AfxMessageBox(_T("ERROR: No atributes were loaded."));
	}
	
	return -1; 
	
}


int CAipi_DT_ID3::GetListCtrlAtributes()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	int n = pMainFrame->m_wndInductionTabView.m_ListCtrl1.GetItemCount();	
	int nAtributes = 0;
	if( n > 0 )
	{
		CString szClass = GetListCtrlClassName();
		
		for(int i = 0; i<n; i++)
		{
			
			BOOL AtributeChecked = pMainFrame->m_wndInductionTabView.m_ListCtrl1.GetCheck(i);
			if( AtributeChecked )
			{
				nAtributes++;
				CString szAtribute = pMainFrame->m_wndInductionTabView.m_ListCtrl1.GetItemText(i, 0);
				if(szAtribute != szClass)
				{
					std::tstring strAtribute = szAtribute.GetBuffer(BUFF_SIZE);
					//m_vA.push_back(strAtribute); 
					mmD_A.insert(m_mmD_A::value_type(UNDECIDED, strAtribute)); 
					
				}
				//szAtribute.ReleaseBuffer();
			}
		
		}
		szClass.ReleaseBuffer();
		
	}
	else
	{
		AfxMessageBox(_T("No atributes were selected"));
	}

/*
	CString str;
	str.Format(_T("NUMBER OF ATRIBUTES LEFT:  %d"), m_vA.size());
	pMainFrame->m_wndOutputTabView.AddMsg1(str);
*/

/*
	for(int i = 0; i<m_vA.size(); ++i)
	{
		tstring str = m_vA.at(i);
		pMainFrame->m_wndOutputTabView.AddMsg1(str.data());

	}
*/

return nAtributes;
}








int CAipi_DT_ID3::SetDistinctAtributeValues(int id_D, int id_A)
{
	
	//CPerfTimer T;
	//T.Start();
	
	
	m_vAV.clear();
	m_vDistinctAV.clear();	
	
	vector<tstring> vTempAV;
	
	tstring strAV; 
	m_mmD_Pos::iterator iter;
	pair <m_mmD_Pos::iterator, m_mmD_Pos::iterator>  p;
	p = mmD_Pos.equal_range(id_D);
	
	int cont = 0;
  
  for(iter = p.first; iter != p.second; ++iter)
  {
		
		g_df.GetData(id_A, iter->second, strAV);
		m_vAV.push_back(strAV);
		
		if(m_vAV.size() != 0)
		{
			tstring strFirstAV = m_vAV.front();
			if( strFirstAV == strAV)
				cont++;
		}
		
		/*
		CString str;
		str.Format(_T("Position...%d  " ),iter1->second);
		pMainFrame->m_wndOutputTabView.AddMsg1((LPCTSTR)szAV);
		pMainFrame->m_wndOutputTabView.AddMsg1(str);
		*/
  }
	

 
	
	tstring strA;
	g_df.GetVariableName(id_A, strA);
	
	m_mmA_AV::const_iterator it;
	pair <m_mmA_AV::iterator, m_mmA_AV::iterator>  av;
  	av = mmA_AV.equal_range(strA);
					
		
	for(it = av.first; it != av.second; ++it)
	{
		m_vDistinctAV.push_back(it->second);
	}
	
	//copy(m_vAV.begin(), m_vAV.end(), back_inserter(vTempAV));		
	//sort(vTempAV.begin(), vTempAV.end());
	//unique_copy(vTempAV.begin(), vTempAV.end(), back_inserter(m_vDistinctAV));

	//StopTimer(T, _T("Time SetDistinctAtributeValue... "));
	
/*	
	CString str;
	str.Format(_T("ATRIBUTE SIZE : %d"), m_vAV.size());
	AddMsgOutputWnd(str);
	
	for(int i = 0; i<m_vAV.size(); ++i)
		AddMsgOutputWnd(m_vAV.at(i).data());

	str.Format(_T("Distinct Atribute SIZE : %d"), m_vDistinctAV.size());
	AddMsgOutputWnd(str);
*/	
	
	if(mmD_Pos.count(id_D) == cont)
		return SAME_AV;

	return 0;
   
}


int CAipi_DT_ID3::SetDistinctClassValues(int id_D, int id_C)
{
	m_vCV.clear();
	//m_vDistinctCV.clear();	
	
	vector<tstring> vTempCV;
	
	tstring strCV; 
	m_mmD_Pos::iterator iter;
	pair <m_mmD_Pos::iterator, m_mmD_Pos::iterator>  p;
	p = mmD_Pos.equal_range(id_D);
	
  
  for(iter = p.first; iter != p.second; ++iter)
  {
		g_df.GetData(id_C, iter->second, strCV);
		m_vCV.push_back(strCV);
		
		/*
		CString str;
		str.Format(_T("Position...%d  " ),iter1->second);
		pMainFrame->m_wndOutputTabView.AddMsg1((LPCTSTR)szCV);
		pMainFrame->m_wndOutputTabView.AddMsg1(str);
		*/
  }
  	
  if( mmD_Pos.count(id_D) == 0 )
	 return NULL_NODE;
  	
		
	//copy(m_vCV.begin(), m_vCV.end(), back_inserter(vTempCV));		
	//sort(vTempCV.begin(), vTempCV.end());
	//unique_copy(vTempCV.begin(), vTempCV.end(), back_inserter(m_vDistinctCV));
	
	
/*	
	CString str;
	str.Format(_T("CLASS SIZE : %d"), m_vCV.size());
	AddMsgOutputWnd(str);
	
	for(int i = 0; i<m_vCV.size(); ++i)
		AddMsgOutputWnd(m_vCV.at(i).data());

	str.Format(_T("Distinct Atribute SIZE : %d"), m_vDistinctCV.size());
	AddMsgOutputWnd(str);
*/	

	return 0;
   
}







CAipi_DT_AVF* CAipi_DT_ID3::addNewAVF(tstring id, tstring a, tstring av, int freq)
{
	CAipi_DT_AVF *pObject = new CAipi_DT_AVF();
    try
	{
		pObject->setAtributeName(a);
		pObject->setAtributeValue(av);
		pObject->setAtributeValueFreq(freq);
		
		mA_AV_F.insert(m_mA_AV_F::value_type(id, *pObject));
		
	}
	catch( CMemoryException* pErr)
	{
		AfxMessageBox(_T("Out of memory!!!"), MB_ICONSTOP | MB_OK);

		if(pObject)
		{
			delete pObject;
			pObject = NULL;
		}
		pErr->Delete();
	}
	
	return pObject;
}

tstring CAipi_DT_ID3::getAtributeName( tstring id )
{
	m_mA_AV_F::iterator iter;
    iter = mA_AV_F.find(id);
  	CAipi_DT_AVF a = (CAipi_DT_AVF)iter->second;
 	
	return a.getAtributeName(); 
			

}


tstring CAipi_DT_ID3::getAtributeValue( tstring id )
{
	m_mA_AV_F::iterator iter;
    iter = mA_AV_F.find(id);
  	CAipi_DT_AVF av = (CAipi_DT_AVF)iter->second;
 	
	return av.getAtributeValue();  
			

}

int CAipi_DT_ID3::getAtributeValueFreq( tstring id )
{
	m_mA_AV_F::iterator iter;
    iter = mA_AV_F.find(id);
  	CAipi_DT_AVF freq = (CAipi_DT_AVF)iter->second;
 	
	return freq.getAtributeValueFreq();  

}

void CAipi_DT_ID3::fillMapA_AV_F()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	int n = pMainFrame->m_wndInductionTabView.m_ListCtrl1.GetItemCount();
	int nSel = 0;	
	if( n > 0 )
	{
		for( int i = 0; i<n; ++i)
		{
			if( pMainFrame->m_wndInductionTabView.m_ListCtrl1.GetCheck(i) == true )
			{
				nSel++;
				CString szA = GetListCtrlAtributeName(i);
				tstring strA = szA.GetBuffer(BUFF_SIZE);

				CopyAtributeValues(i);
				for(int j = 0; j<m_vDistinctAV.size(); ++j)
				{
					int freq = 0;
					tstring strAV = m_vDistinctAV.at(j);
					tstring strID = strA + strAV;
					freq = count(m_vAV.begin(), m_vAV.end(), strAV);
					addNewAVF(strID, strA, strAV, freq);
					
				}
				szA.ReleaseBuffer();
			}
		}
	}
	else
	{
		AfxMessageBox(_T("ERROR: No atributes were found."));
	}

	if( nSel == 0 )
		AfxMessageBox(_T("ERROR: No atributes were selected."));


//Print map container
	for( m_mA_AV_F::const_iterator iter = mA_AV_F.begin(); iter!= mA_AV_F.end(); ++iter)
	{
		pMainFrame->m_wndOutputTabView.AddMsg1(iter->first.data());
		tstring a = getAtributeName(iter->first);
		tstring av = getAtributeValue(iter->first);
		int fr = getAtributeValueFreq(iter->first);
		CString f;
		f.Format(_T("Freq ...%d"), fr);
		pMainFrame->m_wndOutputTabView.AddMsg1(a.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(av.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(f);
	}
	

}


void CAipi_DT_ID3::ClearAll()
{
	
	m_vAV.clear();
	m_vCV.clear();
	m_vDistinctAV.clear();
	m_vDistinctCV.clear();
	mA_AV_F.clear();
	//mAV_IdAV.clear();
	//mCV_IdCV.clear();
	mAGain.clear();
	mAV_C_F.clear();
	mAV_F.clear();
	mD_BA.clear();
	mD_Item.clear();
	mDChild_DParent.clear();
	mmA_AV.clear();
	mmD_A.clear();
	mmD_Pos.clear();
	
}

void CAipi_DT_ID3::DeletePartitions(int id_D)
{
	
	int static minLim;
	int maxLim = id_D;

	for( int i = minLim; i<= maxLim; ++i)
	{
		mmD_Pos.erase(i);
		mmD_A.erase(i);
		mD_Item.erase(i);
		
	}
	
	minLim = maxLim;
	

/*
	for( int i = 0; i<= id_D; ++i)
	{
		mmD_Pos.erase(i);
		mmD_A.erase(i);
		mD_Item.erase(i);
	}
	*/
}



HTREEITEM CAipi_DT_ID3::CreateNodeItem(int id_D, int id_NewD,  tstring strAV, tstring strNewBA)
{
	
	
	tstring nodeName = strAV + _T(":") + strNewBA;
	HTREEITEM hItem = NULL;
	
	if( id_NewD == UNDECIDED)
	{
		nodeName = strNewBA;
		hItem = AddChildName(nodeName.data());
		mD_Item.insert(m_mD_Item::value_type(id_NewD, hItem));
	}
	else
	{
				
				m_mD_Item::iterator iter;
				iter = mD_Item.find(id_D);
				HTREEITEM hOldItem = iter->second;
				SelectNodeItem(hOldItem);
				
				if( hOldItem != 0)
				{
					hItem = AddChildName(nodeName.data());
					mD_Item.insert(m_mD_Item::value_type(id_NewD, hItem));
				}
				else
				{
					
					AfxMessageBox(_T("Item No Encontrado"));
					
				}		
					
				
	}
	

//Print Map Values
/*	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		for( m_mD_Node::iterator it = mD_Node.begin(); it!= mD_Node.end(); ++it)
		{
			CString str;
			str.Format(_T("NODE:  Memory Partition...%d  " ),it->first);
			pMainFrame->m_wndOutputTabView.AddMsg1(str);
			pMainFrame->m_wndOutputTabView.AddMsg1(it->second.data());
			
		}
*/		
	return hItem;
}




int CAipi_DT_ID3::CreatePartition(int id_D , tstring strA, tstring strAV)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	
	static int NewId_D = id_D;
	NewId_D++;
	
	//m_NewId_D++;
	
	tstring strNewAV;
	int cont = 0;
	
	int iNew_A = g_df.GetVariableIndex(strA.data());
	
	m_mmD_Pos::iterator iterD;
	pair <m_mmD_Pos::iterator, m_mmD_Pos::iterator>  p;
  
	
	p = mmD_Pos.equal_range(id_D);
	int n = mmD_Pos.count(id_D);

	
  if( id_D != UNDECIDED ) 
  {
	  //AfxMessageBox(_T("Estoy en create partition"));
	  	  
	  //pMainFrame->m_wndOutputTabView.AddMsg1(_T("++++++++"));
	  //pMainFrame->m_wndOutputTabView.AddMsg1(new_AV.data());
	  //pMainFrame->m_wndOutputTabView.AddMsg1(_T("++++++++"));
	  
		

	  for(iterD = p.first; iterD != p.second; ++iterD)
	  {
			
		    int pos = iterD->second;
			g_df.GetData(iNew_A, pos, strNewAV);
		

			//CString str;
			//str.Format(_T("Position...%d  " ),iterD->second);
			//pMainFrame->m_wndOutputTabView.AddMsg1((LPCTSTR)szNewAV);
			//pMainFrame->m_wndOutputTabView.AddMsg1(str);
				
			if( strNewAV == strAV )
			{
				
				mmD_Pos.insert(m_mmD_Pos::value_type(NewId_D, pos));
				//mmD_Pos.insert(m_mmD_Pos::value_type(m_NewId_D, pos));
				
				//if(p.second == mmD_Pos.upper_bound(id_D))
				//break;	
				
			
				cont++;
				if( cont > n )
					break;
			
			}

			
	  }
  }
  else
  {
	  
	  for(int i = 0; i<g_df.GetNumberOfSamples(iNew_A)-1; ++i)
	  {
		  g_df.GetData(iNew_A, i, strNewAV);
		  
		  if( strNewAV == strAV )
		  {
			 mmD_Pos.insert(m_mmD_Pos::value_type(NewId_D, i));
			 //mmD_Pos.insert(m_mmD_Pos::value_type(m_NewId_D, i));
				//cont++;
				//if( cont > n )
					//break;
			
		  }
	    
	  }
	  
  }
  
  
  

  //szNewAV.ReleaseBuffer();

  
//Print map container
/*	
	for( m_mmD_Pos::const_iterator i = mmD_Pos.begin(); i!= mmD_Pos.end(); ++i)
	{
		CString str;
		str.Format(_T("ID ... %d Position...%d  " ),i->first, i->second);
		pMainFrame->m_wndOutputTabView.AddMsg2(str);
	}

	pMainFrame->m_wndOutputTabView.AddMsg2(_T("****************************************"));
*/

return NewId_D;

//return m_NewId_D;			

}









double CAipi_DT_ID3::CalcClassEntropy( int id_C)
{
	//CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	int freq = 0;	
	double Entropy = 0;
	double log2 = 0;
	double n = (double)m_vCV.size();

	
	for(int i = 0; i<m_vDistinctCV.size(); ++i)
	{
		freq = 0;
		std::tstring strClassValue = m_vDistinctCV.at(i);
		
		freq = count(m_vCV.begin(), m_vCV.end(), strClassValue);
		if( freq == 0 )
		{
			log2 = 0;
		}
		else
		{
			log2 = log10f( freq/n )/log10f( 2 );
			Entropy -= freq/n*log2;
		}

		/*
		CString str;
		str.Format(_T("Freq  %d  Class Entropy  %0.4f"), freq, Entropy);
		pMainFrame->m_wndOutputTabView.AddMsg1(str);
		*/
	}


	/*
	CString str;
	str.Format(_T("CLASS ENTROPY:  %0.4f"), Entropy);
	pMainFrame->m_wndOutputTabView.AddMsg1(str);
	AfxMessageBox(_T("Ver Class Entropy..."));
    */
	if( Entropy == 0 )
		return LEAF_NODE;
	else
		return Entropy;

}




double CAipi_DT_ID3::CalcAtributeGain( int id_A, double CE)
{
	
	//CPerfTimer T;
	//T.Start();

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	m_mAV_F::iterator iter1;
	m_mAV_C_F::iterator iter2;
	
	
	mAV_F.clear();
	mAV_C_F.clear();
	SetAV_F( id_A);
	SetAV_C_F( id_A);

	

	if(m_vAV.size() == 0 || mAV_C_F.size() == 0)
	{
		AfxMessageBox(_T("ERROR1: There is no data in the vector"));
		return -1;
	}

	
	int nClass = m_vDistinctCV.size();
	int nAtributes = m_vDistinctAV.size();
	
	if( nClass == 0 || nAtributes == 0 )
	{
		AfxMessageBox(_T("ERROR2: There is no atributes values in the data"));
		return -1;
	}
	




	double Entropy = 0;
	double SumEntropy = 0;
	double log2 = 0;
	double n = 0;
	int freq = 0;
	int cont = 0;
	


	for(iter1 = mAV_F.begin(); iter1 != mAV_F.end(); ++iter1)
	{
		tstring av_key = iter1->first;
		
		n = (double)iter1->second;
		
		for(iter2 = mAV_C_F.begin(); iter2 != mAV_C_F.end(); ++iter2)
		{
			std::tstring key = iter2->first;
			
			if( key.find(av_key) != std::tstring::npos )
			{
				cont++;
				
				//AfxMessageBox(_T("Entro"));
				//AfxMessageBox(iter1->first.data());
				//AfxMessageBox(iter2->first.data());

				freq = (double)iter2->second;
				if( freq == 0 )
				{
					log2 = 0;
				}
				else
				{
					log2 = log10f( freq/n )/log10f( 2 );
					Entropy -= freq/n*log2;
					
					/*
					CString str;
					str.Format(_T("Entropy ....   %0.4f"), Entropy);
					pMainFrame->m_wndOutputTabView.AddMsg1(str);
					*/
					
				}
				
				if( cont >= nClass )
				{
					
					SumEntropy -= Entropy*n;
					
					/*
					CString str;
					str.Format(_T("SumEntropy x n....   %0.4f"), SumEntropy);
					pMainFrame->m_wndOutputTabView.AddMsg1(iter2->first.data());
					pMainFrame->m_wndOutputTabView.AddMsg1(str);
					*/

					cont = 0;
					Entropy = 0;
					
				}
							
			}

			
				
		}
	}

	int iSize = m_vAV.size();

	double InfoGain = SumEntropy/iSize;
	double Gain = CE + InfoGain;

	//StopTimer(T, _T("Time CalcAtributeGain... "));
	
/*
	CString str;
	str.Format(_T("\n*** InfoGain***  %0.4f   *** Gain ***  %0.4f"), InfoGain, Gain);
	pMainFrame->m_wndOutputTabView.AddMsg1(iter2->first.data());
	pMainFrame->m_wndOutputTabView.AddMsg1(str);
*/
	
	//Print map container
/*
	for( m_mAV_C_F::const_iterator iter = mAV_C_F.begin(); iter!= mAV_C_F.end(); ++iter)
	{
		pMainFrame->m_wndOutputTabView.AddMsg1(iter->first.data());
		CString str;
		str.Format(_T("** Entropy:....  %0.4f" ),iter->second);
		pMainFrame->m_wndOutputTabView.AddMsg1(str);
	}
*/
	
	
	return Gain;

}


tstring CAipi_DT_ID3::ClassAtributesMode()
{
	tstring strLeaf = m_vDistinctCV.at(0);
	int max = 1;
	for(int i = 0; i<m_vDistinctCV.size(); ++i)
	{
		tstring strTemp = m_vDistinctCV.at(i);
		int temp = count(m_vCV.begin(), m_vCV.end(), strTemp);
		if( temp > max )
		{
			max = temp;
			strLeaf = strTemp;
		}
	}

return strLeaf;
}



tstring CAipi_DT_ID3::FindBestPartition()
{
	
	//CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	
	//Find the greater gain atribute
	m_mAGain::const_iterator iter;
	iter = mAGain.begin();
	
	double maxGain = iter->second;
	std::tstring strBestAtribute = iter->first;
	

	for(iter = mAGain.begin(); iter != mAGain.end(); ++iter)
	{
		if( iter->second > maxGain )
		{
			maxGain = iter->second;
			strBestAtribute = iter->first;
			
		}
		
	}
	
	//Optional case
	if(maxGain == 0 )
	{
		
		return _T("NO_GAIN");
	}

	

	//Print bestAtribute	
/*	
	CString str;
	str = strBestAtribute.data();
	str.MakeUpper();
	pMainFrame->m_wndOutputTabView.AddMsg1(str);
	str.Format(_T("MAX GAIN.........:  %0.4f" ),maxGain);
	pMainFrame->m_wndOutputTabView.AddMsg1(str);


//Print map container

	for( iter= mAGain.begin(); iter!= mAGain.end(); ++iter)
	{
		pMainFrame->m_wndOutputTabView.AddMsg1(iter->first.data());
		CString str;
		str.Format(_T("GAIN:  %0.4f" ),iter->second);
		pMainFrame->m_wndOutputTabView.AddMsg1(str);
	}
*/
/*
//Print Atributes Values ID's

	for( m_mAV_ID::const_iterator it1 = mAV_ID.begin(); it1!= mAV_ID.end(); ++it1)
	{
		pMainFrame->m_wndOutputTabView.AddMsg1(it1->first.data());
		CString str;
		str.Format(_T("Atribute Value ID:  %d" ),it1->second);
		pMainFrame->m_wndOutputTabView.AddMsg1(str);
	}
	

//Print Node Atributes Values
	for( m_mmA_AV::const_iterator it2 = mmA_AV.begin(); it2!= mmA_AV.end(); ++it2)
	{
		pMainFrame->m_wndOutputTabView.AddMsg1(it2->first.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(it2->second.data());
	}
	
*/	
	
	

return strBestAtribute;

}



int CAipi_DT_ID3::AvailableAtributes(int id_D, int id_NewD, tstring strBA)
{
	int nPartition = id_D;


	//AddMsgOutputWnd(_T("ATRIBUTES ADDED IN MULTIMAP"));
	
	m_mDChild_DParent::iterator it;
	it = mDChild_DParent.find(id_NewD);
	
	if(it != mDChild_DParent.end())
	{
		nPartition = it->second;
	}
	

	m_mmD_A::iterator iter;
	pair <m_mmD_A::iterator, m_mmD_A::iterator>  pDA;
  
	pDA = mmD_A.equal_range(nPartition);
	int nAtributes = mmD_A.count(nPartition);
	int cont = 0;

	 for(iter = pDA.first; iter!= pDA.second; ++iter)
	 {	
		cont++;
		if( cont > nAtributes)
		{
			break;
		}
		tstring strAtribute = iter->second;
		if( strAtribute != strBA)
		{
			mmD_A.insert(m_mmD_A::value_type(id_NewD, strAtribute)); 
			/*	
			CString str;
			str.Format(_T("Insertado en MultiMap mmD_A:  %d" ), id_NewD);
			AddMsgOutputWnd(str);
			AddMsgOutputWnd(strAtribute.data());
			AfxMessageBox(_T("Insertado en MultiMap mmD_A"));
			*/
		}
		
	}
		
	
	 CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();		
/*
	for( m_mmD_A::iterator it2 = mmD_A.begin(); it2!= mmD_A.end(); ++it2)
	{
		
		CString str;
		str.Format(_T("MEMORY ID:  %d" ),it2->first);
		pMainFrame->m_wndOutputTabView.AddMsg2(str);
		pMainFrame->m_wndOutputTabView.AddMsg2(it2->second.data());
		
	}
	
*/	
	 return mmD_A.count(id_NewD);

	 

}


void CAipi_DT_ID3::Build()
{
	//Set progress bar
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 0, 0);
	//pMainFrame->m_wndStatusBar.SetPaneInfo( 1, nID, nStyle, 100);
	pMainFrame->m_wndStatusBar.SetUpBar(1, TRUE, TRUE);
	
	HTREEITEM hItem;

	

	CPerfTimer T;
	T.Start();
	
	
	int nA = GetListCtrlAtributes();
	
	int id_C = GetListCtrlClassIndex();

	if (id_C == -1)
	{
		AfxMessageBox(_T("ERROR: Problems with the Classifier Index.Process stopped."));
		return;
	}
	
	int t = CopyClassValues(id_C);
	if ( t == NULL_NODE )
	{
		hItem = CreateNodeItem(UNDECIDED, UNDECIDED, _T("NULL"), _T("NULL"));
		return;
	}
	
	
	
	double CE = CalcClassEntropy( id_C);
	if ( CE == LEAF_NODE )
	{
		
		tstring strLeaf = m_vDistinctCV.at(0);
		hItem = CreateNodeItem(UNDECIDED, UNDECIDED, _T("NULL"), strLeaf);
		return;
	}
	
	
	
	int e = SaveAtributesGain(UNDECIDED, UNDECIDED, id_C, CE);
	if( e == SAME_AV)
	{
		tstring strLeaf =	ClassAtributesMode();
		hItem = CreateNodeItem(UNDECIDED, UNDECIDED, _T("NULL"), strLeaf);
		return;	
	}
	if( e == NO_PARTITION )
	{
		//AfxMessageBox(_T("No se inserto ningun dato en GAIN MAP"));
		return;
				
	}
	else
	{	
		tstring strBestA = FindBestPartition();
		if( strBestA == _T("NO_GAIN"))
		{
			tstring strLeaf =	ClassAtributesMode();
			hItem = CreateNodeItem(UNDECIDED, UNDECIDED, _T("NULL"), strLeaf);
			return;			
		}
		
		

		hItem = AddSiblingName(strBestA.data());
		mD_Item.insert(m_mD_Item::value_type(UNDECIDED, hItem));
		BuildTree(UNDECIDED, strBestA, id_C, nA);
	}

	StopTimer(T, _T("Time building the decision tree... "));

	SetFocus();

	pMainFrame->m_wndStatusBar.ResetBar(1, TRUE);
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Process finished"), RGB(0,0,0), TRUE);
		
}



void CAipi_DT_ID3::BuildTree(int id_D, tstring strBA, int id_C, int nA)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Building Decision Tree..."), RGB(0,0,0), TRUE);
	pMainFrame->m_wndStatusBar.ResetBar(1);
	
	HTREEITEM hItem;

	
	for(m_mDChild_DParent::iterator it = mDChild_DParent.begin(); it!= mDChild_DParent.end(); ++it)
	{
		
		if(it->second == id_D)
		{
			return;
		}
	}
	
	int nAtributes = mmD_A.count(id_D);
	

	pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, (nA - nAtributes)*100/nA);


	if( nAtributes > 0 )
	{	
		
		m_mmA_AV::const_iterator iter;
		pair <m_mmA_AV::iterator, m_mmA_AV::iterator>  av;
  		av = mmA_AV.equal_range(strBA);
					
		
		for(iter = av.first; iter != av.second; ++iter)
		{
			tstring strAV = iter->second;
					
			int id_NewD = CreatePartition(id_D, strBA, strAV );
			
					
			mDChild_DParent.insert(m_mDChild_DParent::value_type(id_NewD, id_D));
			/*
				for( m_mDChild_DParent::iterator it1 = mDChild_DParent.begin(); it1!= mDChild_DParent.end(); ++it1)
				{
					CString str;
					str.Format(_T("MEMORY ID:  %d" ),it1->second);
					pMainFrame->m_wndOutputTabView.AddMsg2(str);
					str.Format(_T("SUBMEMORY ID:  %d" ),it1->first);
					pMainFrame->m_wndOutputTabView.AddMsg2(str);
				}
			*/
			AvailableAtributes(id_D, id_NewD, strBA);
			
			int idBestA = g_df.GetVariableIndex(strBA.data());
					
			int t = SetDistinctClassValues(id_NewD, id_C);

			if ( t == NULL_NODE )
			{
				hItem = CreateNodeItem(id_D, id_NewD, strAV, _T("NULL"));
				continue;
			}
			
			double CE = CalcClassEntropy( id_C);
			
			if ( CE == LEAF_NODE )
			{
				tstring strLeaf;
				m_mmD_Pos::iterator iterD;
				iterD = mmD_Pos.find(id_NewD);
				g_df.GetData(id_C, iterD->second, strLeaf);
				hItem = CreateNodeItem(id_D, id_NewD, strAV, strLeaf);
				continue;
			}
			
			
			
			int e = SaveAtributesGain(id_NewD, idBestA, id_C, CE);
			if( e == SAME_AV)
			{
				tstring strLeaf =	ClassAtributesMode();
				hItem = CreateNodeItem(id_D, id_NewD, strAV, strLeaf);
				//AfxMessageBox(_T("SAME_AV"));
				continue;	
			}
			if( e == NO_PARTITION )
			{
				continue;
			}
			else
			{

				tstring strNewBestA = FindBestPartition();
				if( strNewBestA == _T("NO_GAIN"))
				{
					tstring strLeaf =	ClassAtributesMode();
					hItem = CreateNodeItem(id_D, id_NewD, strAV, strLeaf);
					continue;			
				}
				mD_BA.insert(m_mD_BA::value_type(id_NewD, strNewBestA));
				hItem = CreateNodeItem(id_D, id_NewD, strAV, strNewBestA);
			}
								
			
		}
		
		
		if(hItem == NULL )
		{
			//return;
		}
		else
		{
				DeletePartitions(id_D);
			
				for( m_mD_BA::iterator it = mD_BA.begin(); it!= mD_BA.end(); ++it)
				{
					BuildTree(it->first, it->second, id_C, nA);
					
				}
		}
	
	}
	
	
}


int CAipi_DT_ID3::SaveAtributesGain(int id_D, int BA, int id_C, double CE)
{
	
	//CPerfTimer T;
	//T.Start();


	m_mmD_A::iterator iter;
	pair <m_mmD_A::iterator, m_mmD_A::iterator>  pDA;
  	pDA = mmD_A.equal_range(id_D);
	
	int n = mmD_A.count(id_D);
	int cont = 0;
	
			
	mAGain.clear();	



	for(iter = pDA.first; iter!= pDA.second; ++iter)
	{	
		tstring strAtribute = iter->second;
		int id_A = g_df.GetVariableIndex(strAtribute.data()); 
		if( BA != UNDECIDED)
		{
			int r = SetDistinctAtributeValues(id_D, id_A);
			if( r == SAME_AV )
			{
				cont++;	
			}
							
		}
		else
		{
			int r = CopyAtributeValues(id_A);
			if( r == SAME_AV )
			{
				cont++;	
			}
							
		}
		
		double gain = CalcAtributeGain(id_A, CE);
		mAGain.insert(m_mAGain::value_type(strAtribute, gain));
		
	}
	
	//StopTimer(T, _T("Time SAVE ATRIBUTES GAIN... "));
	int partSize = mmD_Pos.count(id_D);
	
	if(cont == n && partSize > 1)
	{
		return SAME_AV;
						
	}

	if( mAGain.size() == 0 )
	{
		return NO_PARTITION;
	}


	
return 0;		
}


void CAipi_DT_ID3::SetAV_C_F(  int id_A )
{
	
	//CPerfTimer T;
	//T.Start();
	
	tstring strAtributeValue, strClassValue, strAtributeName;
	std::vector<std::tstring> v_strAtributeValue;
	
	g_df.GetVariableName(id_A, strAtributeName);
	
	int AVSize = m_vAV.size();
	int CVSize = m_vCV.size();
	
	int nAtribute = m_vDistinctAV.size();
	int nClass = m_vDistinctCV.size();
	
	if( AVSize != CVSize )
	{
		AfxMessageBox(_T("ERROR: The sizes of the vectors ( Atribute-Class ) are different."));
		return;
	}
		
	
	for(int i =0; i<nAtribute; ++i)
	{
		strAtributeValue = m_vDistinctAV.at(i);

		for(int j = 0; j<nClass; ++j)
		{
			strClassValue = m_vDistinctCV.at(j);
			tstring strId = strAtributeName +  strAtributeValue  +  strClassValue;
			mAV_C_F.insert(m_mAV_C_F::value_type(strId, 0));	
						
		}
	}

	
	m_mAV_C_F::iterator iter;

	for(int k = 0; k<AVSize; ++k)
	{
		tstring strTempAtributeValue = m_vAV.at(k);
		tstring strTempClassValue = m_vCV.at(k);
		
		tstring strId = strAtributeName + strTempAtributeValue + strTempClassValue;
		iter = mAV_C_F.find(strId);
		int iFreq = iter->second;
		iter->second = ++iFreq; 
	}

	//StopTimer(T, _T("Time SetAV_C_F... "));
	



	//Print map container
	/*
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( m_mAV_C_F::iterator ite = mAV_C_F.begin(); ite!= mAV_C_F.end(); ++ite)
	{
		pMainFrame->m_wndOutputTabView.AddMsg1(ite->first.data());
		CString str;
		str.Format(_T("Freq  %d" ),ite->second);
		pMainFrame->m_wndOutputTabView.AddMsg1(str);
	}
*/
	

}


void CAipi_DT_ID3::SetAV_F(int idAtribute)
{
	tstring strAtributeName;
	
	g_df.GetVariableName(idAtribute, strAtributeName);  
	

	for (int i = 0; i< m_vDistinctAV.size(); ++i) 
	{
		int freq = 0;
		tstring strAtributeValue = m_vDistinctAV.at(i);
		tstring strId = strAtributeName + strAtributeValue;
		freq = count(m_vAV.begin(), m_vAV.end(), strAtributeValue);
		mAV_F.insert(m_mAV_F::value_type(strId, freq));	
	}
				
//Print map container
/*
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	  
	for( m_mAV_F::const_iterator iter = mAV_F.begin(); iter!= mAV_F.end(); ++iter)
	{
		CString str;
		str.Format(_T("Freq...%d  " ),iter->second);
		
		pMainFrame->m_wndOutputTabView.AddMsg1(iter->first.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(str);
	}
*/

}


int CAipi_DT_ID3::CopyAtributeValues(int id_A)
{
	
	//CPerfTimer T;
	//T.Start();
	
	m_vAV.clear();
	m_vDistinctAV.clear();		
	
	vector<tstring> vTempAV;
	
	int iLength = g_df.GetData(id_A, m_vAV);
	if(iLength == -1 )
	{
		AfxMessageBox(g_df.GetLastError());
		return -1;
	}
	
	m_vAV.erase( m_vAV.end( ) - 1 );
	
	copy(m_vAV.begin(), m_vAV.end(), back_inserter(vTempAV));
	sort(vTempAV.begin(), vTempAV.end());
	unique_copy(vTempAV.begin(), vTempAV.end(), back_inserter(m_vDistinctAV));
	
	vTempAV.clear();

	tstring strAtributeName; 
	g_df.GetVariableName(id_A, strAtributeName);
	
	for(int i = 0; i<m_vDistinctAV.size(); ++i)
	{
		tstring strId = strAtributeName + m_vDistinctAV.at(i);
		mmA_AV.insert(m_mmA_AV::value_type(strAtributeName, m_vDistinctAV.at(i)));
	}

	//StopTimer(T, _T("Time CopyAtributesValues... "));
	if(m_vDistinctAV.size() == 1)
	{
		

		return SAME_AV;
	}	
	
	return 0;
   
}

int CAipi_DT_ID3::CopyClassValues(int id_C)
{
	m_vCV.clear();
	m_vDistinctCV.clear();	
	
	vector<tstring> vTempCV;
	
	//Copy atribute values in a temporal vector m_vAV		
	int iLength = g_df.GetData(id_C, m_vCV);
	if(iLength == -1 )
	{
		AfxMessageBox(g_df.GetLastError());
		return -1;
	}
	
	//Erase last element (empty)
	m_vCV.erase( m_vCV.end( ) - 1 );
	copy(m_vCV.begin(), m_vCV.end(), back_inserter(vTempCV));
	sort(vTempCV.begin(), vTempCV.end());
	
	//Puts one copy of each atribute 
	unique_copy(vTempCV.begin(), vTempCV.end(), back_inserter(m_vDistinctCV));

	vTempCV.clear();

	if(m_vDistinctCV.size() == 0 )
		return NULL_NODE;

	return 0;
   
}


