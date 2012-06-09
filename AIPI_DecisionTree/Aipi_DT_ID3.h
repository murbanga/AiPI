// Aipi_DT_ID3.h: interface for the CAipi_DT_ID3 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_DT_ID3_H__4C13B394_3DF3_49AC_BEAB_16ABC417DF1C__INCLUDED_)
#define AFX_AIPI_DT_ID3_H__4C13B394_3DF3_49AC_BEAB_16ABC417DF1C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Aipi_DT_AVF.h"
#include ".\TreeEditorCtrl\EditTreeCtrl.h"
#include ".\DataFileCSV\CDataFile.h"

#include <algorithm>
#include <numeric>
#include <vector>
#include <map>
#include <stack>
#include <iterator>
#include <functional>
#include <cmath>

#define  UNDECIDED		-1	
#define  LEAF_NODE		-2
#define  NULL_NODE		-3 
#define	 SAME_AV		-4 
#define  NO_PARTITION	-5

class CAipi_DT_ID3  
{
public:
	CAipi_DT_ID3();
	virtual ~CAipi_DT_ID3();

	public:
	//DT_AtributeValuesFreq Class functions
	CAipi_DT_AVF* CAipi_DT_ID3::addNewAVF(tstring id, tstring a, tstring av, int freq);
	tstring CAipi_DT_ID3::getAtributeName( tstring id );
	tstring CAipi_DT_ID3::getAtributeValue( tstring id );
	int     CAipi_DT_ID3::getAtributeValueFreq( tstring id );
	void	fillMapA_AV_F();

	
	//CAIPITreeView Class functions
	HTREEITEM AddSiblingName(CString name);
	HTREEITEM AddChildName(CString name);
	HTREEITEM FindNodeItem(CString name);
	void SelectNodeItem(HTREEITEM hItem);
	void SetFocus();	
	
	//ListCtrl functions
	CString		GetListCtrlClassName();
	CString		GetListCtrlAtributeName(int id);
	int			GetListCtrlClassIndex();
	int			GetListCtrlAtributeIndex(CString a);
	int			GetListCtrlAtributes();

	//Utility functions
	void AddMsgOutputWnd(CString msg);
	void StopTimer(CPerfTimer t, CString msg);
	
	//ID3 Algorithm functions
	int			CopyAtributeValues(int id_A);
	int			CopyClassValues(int id_C);
	int			SetDistinctAtributeValues(int id_D, int id_A);
	int			SetDistinctClassValues(int id_D, int id_C);
	
	int			CreatePartition(int id_D, tstring strA, tstring strAV);
	HTREEITEM   CreateNodeItem(int id_D, int id_NewD, tstring strAV, tstring strNewBA);
	void		SetAV_F( int id_A);
	void		SetAV_C_F(int id_A);
	int			AvailableAtributes(int id_D, int id_NewD, tstring strBA);
	double		CalcClassEntropy(int id_C);
	double      CalcAtributeGain(int id_A, double CE);
	int			SaveAtributesGain(int id_D, int BA, int id_C, double CE);
	tstring		ClassAtributesMode();
	tstring		FindBestPartition();	
	void		ClearAll();
	void        DeletePartitions(int id_D);
	void        Build(); 
	void		BuildTree(int id_D, tstring strBA, int id_C, int nA);
	
private:

/*
NOMENCLATURE :  
A	= Atribute
AV	= Atribute Value
C	= Class Atribute
CV	= Class Atribute Value
BA  = Best Atribute	
F	= Frequency
D   = Data Partition
E	= Entropy

mm	= MultiMap
m	= Map
v	= Vector


*/
	int m_NewId_D;


	std::vector<std::tstring > m_vAV;
	std::vector<std::tstring > m_vDistinctAV;
	std::vector<std::tstring > m_vCV;
	std::vector<std::tstring > m_vDistinctCV;
	
	
	typedef std::multimap<int, int> m_mmD_Pos;
	m_mmD_Pos   mmD_Pos;
	
	typedef std::multimap<tstring, tstring> m_mmA_AV;
	m_mmA_AV	mmA_AV;
	
	typedef std::multimap<int, tstring> m_mmD_A;
	m_mmD_A	mmD_A;
	
	
	//typedef std::map<tstring, tstring> m_mAV_IdAV;
	//m_mAV_IdAV	mAV_IdAV;
	
	
	//typedef std::map<tstring, tstring> m_mCV_IdCV;
	//m_mCV_IdCV	mCV_IdCV;
	
	
	
	typedef std::map<int , tstring> m_mD_BA;
	m_mD_BA	  mD_BA;

	typedef std::map<tstring, int> m_mAV_F;
	m_mAV_F   mAV_F;
	typedef std::map<tstring, int> m_mAV_C_F;
	m_mAV_C_F   mAV_C_F;

	
	typedef std::map<tstring, double> m_mAGain;
	m_mAGain    mAGain;
	
	typedef std::map<int, HTREEITEM> m_mD_Item;
	m_mD_Item    mD_Item;
	

	typedef std::map<int, int> m_mDChild_DParent;
	m_mDChild_DParent    mDChild_DParent;



	typedef std::map<tstring, CAipi_DT_AVF> m_mA_AV_F;
	m_mA_AV_F	mA_AV_F;
	
	

};

#endif // !defined(AFX_AIPI_DT_ID3_H__4C13B394_3DF3_49AC_BEAB_16ABC417DF1C__INCLUDED_)
