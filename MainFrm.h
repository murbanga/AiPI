// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__A7CE49D9_98D8_442F_BFFE_ED0F0E4EB30F__INCLUDED_)
#define AFX_MAINFRM_H__A7CE49D9_98D8_442F_BFFE_ED0F0E4EB30F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//Includes for AIPI engine
#include "AIPI_Engine/Aipi_WM.h"
#include "AIPI_Engine/Aipi_RETE_TK.h"
#include "AIPI_Engine/Aipi_RETE_JNode.h"
#include "AIPI_Engine/Aipi_RETE_DNode.h"	
#include "AIPI_Engine/Aipi_RETE_PNode.h"
#include "AIPI_Engine/Aipi_RETE_NNode.h"
#include "AIPI_Engine/Aipi_RETE_Vars.h"
#include "AIPI_Engine/Aipi_RETE_NumVars.h"
#include "AIPI_Engine/Aipi_RETE_Links.h"
#include "AIPI_Engine/Aipi_RETE_Cond.h"
#include "AIPI_Engine/Aipi_RETE_NodeCond.h"
#include "AIPI_Engine/Aipi_RETE_Operations.h"
#include "AIPI_Engine/Aipi_RepCond.h" 

#include "AIPI_Engine/Aipi_RETE_TypeDouble.h"
#include "AIPI_Engine/Aipi_RETE_TypeFloat.h"
#include "AIPI_Engine/Aipi_RETE_TypeInt.h"
#include "AIPI_Engine/Aipi_RETE_TypeLong.h"
#include "AIPI_Engine/Aipi_RETE_TypeString.h"

//Include conflict resolution strategy
#include "AIPI_Engine/Aipi_CR_Recency.h"
#include "AIPI_Engine/Aipi_CR_RecencyTags.h"
#include "AIPI_Engine/Aipi_CR_Specificity.h"
#include "AIPI_Engine/Aipi_CR_Priority.h"
#include "AIPI_Engine/Aipi_CR_MEA.h"
#include "AIPI_Engine/Aipi_CR_LEX.h"
#include "AIPI_Engine/Aipi_CmdLocation.h"



//include for Workspace structures
#include "WorkspaceTree1.h"
#include "WorkspaceLocation.h"


//includes for AIPI interperter
#include "Aipi_Lexer.h"
#include "Aipi_ParserFile.h"
#include "Aipi_ParserGUI.h"
#include "Aipi_Parser.h"
#include "Aipi_Tokenizer.h"
#include "Aipi_Error.h"
#include "Aipi_SymbolTable.h"
#include "Aipi_STableLiteral.h"
#include "Aipi_STableGlobalLiteral.h"
#include "Aipi_STableLocalLiteral.h"
#include "Aipi_STableNumeric.h"
#include "Aipi_STableGlobalNumeric.h"
#include "Aipi_STableLocalNumeric.h"
#include "Aipi_STableClass.h"
#include "Aipi_ScriptCode.h"
#include "Aipi_ScriptLocation.h"

#include <map>
#include <set>
#include <vector>
#include <functional>

//include for GridCtrl
#include ".\GridCtrl\GridCtrl.h"


//includes for ToolBox
#include "OXSkinnedView.h"
#include "OXCustomizeManager.h"
#include "OXEdit.h"
#include "OXWorkspaceState.h"
#include "OXRegistryItem.h"

#include "OXSkinnedComboBox.h"
#include "OXBitmapMenuOrganizer.h"
#include "OXCoolToolbar.h"
#include "OXMenuBar.h"

#include "OXSizeDockBar.h"
#include "OXSizeDlgBar.h"
#include "OXFrameWndDock.h"
#include "OXTabClientWnd.h"
#include "XStatus4.h"




//includes for Controls
#include "CommandDlgBar.h"
#include "OutputTabView.h"
#include "WorkspaceTabView.h"
#include "PropertiesBar.h"
#include "InductionTabView.h"
#include "AIPITabView.h"	


#include "JukeBoxDlg.h"
#include "MediaPlayerDlg.h"
#include "ImageDlg.h"
#include "DxfCadDlg.h" 
#include "ImageFilterDlg.h"
#include "CalendarDlg.h"
#include "OleDBDlg.h" 

#include "ImageCtrl.h"
#include "InfoCtrl.h"
#include "EditInfoCtrl.h"
#include "ListOptionCtrl.h"
#include "ListMultiOptionCtrl.h"
#include "NSChartBarCtrl.h"
#include "ChartBarCtrl.h"
#include "GraphBarCtrl.h"
#include "StaticMeterCtrl.h"


//includes for the new project wizard
#include "NewProjectSheet.h"
#include "NewProjectIntroPage.h"
#include "NewProjectPage1.h"
#include "NewProjectPage2.h"
#include "NewProjectEndPage.h"


//includes for Project Properties
#include "FunctionProperties.h"

//////////////////////////////////////////////////////////////////////////////////////
	/// CustomManagerDlg ////
//////////////////////////////////////////////////////////////////////////////////////
/*
class CCustomTBExtendedEdit : public COXCustomTBButtonWnd<COXEdit>
{
public:
	virtual COXCustomTBButtonTemplate* CBCreateNewInstance() const;
	virtual void CBCopyContents(COXCustomTBButtonTemplate* pCBTemplate) const
};
*/

#define MainFrameWnd COXMDIFrameWndSizeDock

class CMainFrame : public COXMenuBarFrame<MainFrameWnd, COXSizeDockBar>
{

	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:
	

///---------------------------------------------------------------------------------------
///  AIPI Data Estructures ///
///---------------------------------------------------------------------------------------
	/*
	
	**** Symbols ***
	
	*** Expert System Elemetns ***  
	PM	= Production Memory
	WM	= Working Memory
	LHS = Left Hand Side
	RHS = Right Hand Side

	*** RETE Algorithm Elements ***
	AM	= Alpha Memory  
	BM	= Beta Memory
	TK  = Token (Beta Memory Token)
	JN	= Join Node
	PN	= Production Node
	NN	= Negated Node (from Negated Conditions)
	NCC	= Negated Conjunctive Conditions
	 
	
	*/

	/*

	*** Nomenclature ***

	g			= Global Variable
	m			= Map
	mm			= Multimap
	v			= Vector
	Cond		= Condition
	Parent		= Parent Node
	Child		= Child Node
	N			= Node	
	PartnerN	= Partner Node


  */

/////////////////////////////////////////////////////////////////
	
	/// *** PM = Production Memory *** ///

	//Key	= Production Memory Index
	//Val	= Production Memory Object Parameters
	typedef std::map<long, CAipi_PM> g_mPM;
	g_mPM	gmPM;
	
	//Key	= Production Memory Index
	//Val	= Conditions
	typedef std::multimap<long, int> g_mmPM_Cond;
	g_mmPM_Cond	gmmPM_Cond;

	//Key	= Production Memory Index
	//Val	= Facts
	typedef std::multimap<long, int> g_mmPM_Fact;
	g_mmPM_Fact	gmmPM_Fact;

		
	//Key	= Production Memory Index
	//Val	= Relational Conditions
	typedef std::multimap<long, int> g_mmPM_RelCond;
	g_mmPM_RelCond	gmmPM_RelCond;

	
	//Key	= Production Memory Index
	//Val	= Beta Memories
	typedef std::multimap<long, int> g_mmPM_BM;
	g_mmPM_BM	gmmPM_BM;

	//Key	= Production Memory Index
	//Val	= Production Node
	typedef std::map<long, int> g_mPM_PNode;
	g_mPM_PNode	gmPM_PNode;


	//This structures saves the temporary data of the sets:
	//g_sIVar, g_sAVar, g_sVVar
	/////////////////////////////////////////////////	
	//Key	= Production Memory Index
	//Val	= Identifier Variables
	typedef std::multimap<long, tstring> g_mmPM_IVar;
	g_mmPM_IVar	gmmPM_IVar;

	//Key	= Production Memory Index
	//Val	= Attributes Variables
	typedef std::multimap<long, tstring> g_mmPM_AVar;
	g_mmPM_AVar	gmmPM_AVar;

	//Key	= Production Memory Index
	//Val	= Value Variables
	typedef std::multimap<long, tstring> g_mmPM_VVar;
	g_mmPM_VVar	gmmPM_VVar;

	///////////////////////////////////////////////////
	/// IForm of previous structs  ///
	//////////////////////////////////////////////////
	
	//Key	= Production Memory Index
	//Val	= Identifier Variables
	typedef std::multimap<long, long> g_mmPM_IVarIForm;
	g_mmPM_IVarIForm	gmmPM_IVarIForm;

	//Key	= Production Memory Index
	//Val	= Attributes Variables
	typedef std::multimap<long, long> g_mmPM_AVarIForm;
	g_mmPM_AVarIForm	gmmPM_AVarIForm;

	//Key	= Production Memory Index
	//Val	= Value Variables
	typedef std::multimap<long, long> g_mmPM_VVarIForm;
	g_mmPM_VVarIForm	gmmPM_VVarIForm;
	
	

////////////////////////////////////////////////////////////////////////////
	
	
/////////////////////////////////////////////////////////////////////////////
	
	/// *** Operations Variables *** /// 
	
	//Key	= Index of the Production Memory
	//Val	= Operation Object
	typedef std::multimap<int, CAipi_RETE_Operations> g_mmPM_Operation;
	g_mmPM_Operation	gmmPM_Operation;

	//Key	= Attribute
	//Val	= Attribute Value Type
	typedef std::map<tstring, int> g_mAttr_Type;
	g_mAttr_Type	gmAttr_Type;
	
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
	
	/// *** WM = Working Memory *** ///
	
	//Key	= Index of the Working Memory Element
	//Val	= Working Memory Object
	typedef std::map<int, CAipi_WM> g_mWM;
	g_mWM	gmWM;



/*
	Symbols:
	I	= Identifier (Id)   
	A	= Atribute (Attr)  
	V	= Value (Val)
	e	= Don`t care
	
	LT	= Lesser than
	LE	= Lesser or Equal than
	GT	= Greater than 
	GE	= Greater or Equal than
	EQ	= Equal than
	NE	= Not Equal than (Different)
	*/


	//**** Equality ****//
	//Key	= Index of the Working Memory Element
	//Val	= Index of the Condition
	typedef std::multimap<int, int> g_mmEQ_WM_Cond;
	g_mmEQ_WM_Cond	gmmEQ_WM_Cond;

	//Key	= Index of the Condition
	//Val	= Index of the Working Memory Element
	typedef std::map<int, int> g_mEQ_Cond_WM;
	g_mEQ_Cond_WM	gmEQ_Cond_WM;

	//**** Equal Than ****//
	//Key	= Index of the Working Memory Element
	//Val	= Index of the Condition
	typedef std::multimap<int, int> g_mmET_WM_Cond;
	g_mmET_WM_Cond	gmmET_WM_Cond;

	//Key	= Index of the Condition
	//Val	= Index of the Working Memory Element
	typedef std::map<int, int> g_mET_Cond_WM;
	g_mET_Cond_WM	gmET_Cond_WM;

	//**** Non Equality ****//
	//Key	= Index of the Working Memory Element
	//Val	= Index of the Condition
	typedef std::multimap<int, int> g_mmNE_WM_Cond;
	g_mmNE_WM_Cond	gmmNE_WM_Cond;

	//Key	= Index of the Condition
	//Val	= Index of the Working Memory Element
	typedef std::map<int, int> g_mNE_Cond_WM;
	g_mNE_Cond_WM	gmNE_Cond_WM;

	//**** Greater Than ****//
	//Key	= Index of the Working Memory Element
	//Val	= Index of the Condition
	typedef std::multimap<int, int> g_mmGT_WM_Cond;
	g_mmGT_WM_Cond	gmmGT_WM_Cond;

	//Key	= Index of the Condition
	//Val	= Index of the Working Memory Element
	typedef std::map<int, int> g_mGT_Cond_WM;
	g_mGT_Cond_WM	gmGT_Cond_WM;

	//**** Greater or Equal Than ****//
	//Key	= Index of the Working Memory Element
	//Val	= Index of the Condition
	typedef std::multimap<int, int> g_mmGE_WM_Cond;
	g_mmGE_WM_Cond	gmmGE_WM_Cond;

	//Key	= Index of the Condition
	//Val	= Index of the Working Memory Element
	typedef std::map<int, int> g_mGE_Cond_WM;
	g_mGE_Cond_WM	gmGE_Cond_WM;

	//**** Lesser Than ****//
	//Key	= Index of the Working Memory Element
	//Val	= Index of the Condition
	typedef std::multimap<int, int> g_mmLT_WM_Cond;
	g_mmLT_WM_Cond	gmmLT_WM_Cond;

	//Key	= Index of the Condition
	//Val	= Index of the Working Memory Element
	typedef std::map<int, int> g_mLT_Cond_WM;
	g_mLT_Cond_WM	gmLT_Cond_WM;

	//**** Lesser or Equal Than ****//
	//Key	= Index of the Working Memory Element
	//Val	= Index of the Condition
	typedef std::multimap<int, int> g_mmLE_WM_Cond;
	g_mmLE_WM_Cond	gmmLE_WM_Cond;

	//Key	= Index of the Condition
	//Val	= Index of the Working Memory Element
	typedef std::map<int, int> g_mLE_Cond_WM;
	g_mLE_Cond_WM	gmLE_Cond_WM;

	
	//**** Assignation ****//
	//Key	= Index of the Working Memory Element
	//Val	= Index of the Condition
	typedef std::multimap<int, int> g_mmAS_WM_Cond;
	g_mmAS_WM_Cond	gmmAS_WM_Cond;

	//Key	= Index of the Condition
	//Val	= Index of the Working Memory Element
	typedef std::map<int, int> g_mAS_Cond_WM;
	g_mAS_Cond_WM	gmAS_Cond_WM;




	
////////////////////////////////////////////////////////////////////////////
	
	
/////////////////////////////////////////////////////////////////////////////
	
	/// *** LHS = Left Hand Side *** /// 
	
	//Key	= Index of the Condition Element
	//Val	= Working Memory Object
	typedef std::map<int, CAipi_LHS> g_mLHS;
	g_mLHS	gmLHS;

////////////////////////////////////////////////////////////////////////////
	
	
/////////////////////////////////////////////////////////////////////////////
	
	/// *** RHS = Right Hand Side *** /// 
	
	//Key	= Index of the RHS Fact Element
	//Val	= Working Memory Object
	typedef std::map<int, CAipi_RHS> g_mRHS;
	g_mRHS	gmRHS;

	//Key	= Index of the RHS Fact Element
	//Val	= Working Memory Object
	typedef std::multimap<int, CAipi_RHSCmd> g_mmRHSCmd;
	g_mmRHSCmd	gmmRHSCmd;

	//Key	= PM Identifier
	//Val	= CAipi_CmdLocation Object
	typedef std::multimap<long, CAipi_CmdLocation> g_mmCmdLocation;
	g_mmCmdLocation	gmmCmdLocation;


	

////////////////////////////////////////////////////////////////////////////
	
	
/////////////////////////////////////////////////////////////////////////////
	

	//// *** Repeated Conditions **** ////
	
	//Key	= Index of the Initial Condition that is repeated 
	//Val	= Index of Repeated Conditions
	typedef std::multimap<int, CAipi_RepCond> g_mmRepCond;
	g_mmRepCond	gmmRepCond;


	//Key	= Index of all Repeated Condition 
	//Val	= Index of all Repeated Conditions
	typedef std::multimap<int, CAipi_RepCond> g_mmRepCondEx;
	g_mmRepCondEx	gmmRepCondEx;




////////////////////////////////////////////////////////////////////////////
	
	
/////////////////////////////////////////////////////////////////////////////
	
	/// *** Vars = LHS Variables *** /// 


	//Key	= Variable Name
	//Val	= Variable Object Information for Identifier
	typedef std::multimap<tstring, CAipi_RETE_Vars> g_mmVar_I;
	g_mmVar_I		gmmVar_I;

	//Key	= Variable Name
	//Val	= Variable Object Information for Attribute
	typedef std::multimap<tstring, CAipi_RETE_Vars> g_mmVar_A;
	g_mmVar_A		gmmVar_A;

	//Key	= Variable Name
	//Val	= Variable Object Information for Value
	typedef std::multimap<tstring, CAipi_RETE_Vars> g_mmVar_V;
	g_mmVar_V		gmmVar_V;





////////////////////////////////////////////////////////////////////////////
	
	
/////////////////////////////////////////////////////////////////////////////
	
	/// *** NumNode = Numeric Node  ||  NumVars = Numeric Variables *** /// 


   //  +++ Number Variables Types +++  //
	
	//Key	= Variable Name
	//Val	= Integer Data Value Type Object
	typedef std::multimap<tstring, CAipi_RETE_TypeInt> g_mmVar_Int;
	g_mmVar_Int		gmmVar_Int;
	
	//Key	= Variable Name
	//Val	= Long Integer Data Value Type Object
	typedef std::multimap<tstring, CAipi_RETE_TypeLong> g_mmVar_Long;
	g_mmVar_Long		gmmVar_Long;

	//Key	= Variable Name
	//Val	= Float Data Value Type Object
	typedef std::multimap<tstring, CAipi_RETE_TypeFloat> g_mmVar_Float;
	g_mmVar_Float		gmmVar_Float;

	//Key	= Variable Name
	//Val	= Double Data Value Type Object
	typedef std::multimap<tstring, CAipi_RETE_TypeDouble> g_mmVar_Double;
	g_mmVar_Double		gmmVar_Double;

	//Key	= Variable Name
	//Val	= Double Data Value Type Object
	typedef std::multimap<tstring, CAipi_RETE_TypeString> g_mmVar_String;
	g_mmVar_String		gmmVar_String;



	//Key	= Variable Name
	//Val	= Beta Memory
	typedef std::map<tstring, int> g_mNumVar_BM;
	g_mNumVar_BM	gmNumVar_BM;





	//Key	= Parent Token Index of the data value
	//Val	= Left NumVar Object 
	typedef std::map<int, CAipi_RETE_NumVars> g_mTK_LeftV;
	g_mTK_LeftV	gmTK_LeftV;

	
	//Key	= Parent Token Index of the data value
	//Val	= Right NumVar Object 
	typedef std::map<int, CAipi_RETE_NumVars> g_mTK_RightV;
	g_mTK_RightV	gmTK_RightV;




//This structures saves temporarily the variable elements of the LHS
//The use of sets its because we don´t want repeated variables saved.
//This data is passed to the multimaps g_mmPM_IVar, g_mmPM_AVar, g_mmPM_VVar	

	//Key	= Variable Name for Identifier
	typedef std::set<tstring> g_sIVar;
	g_sIVar	gsIVar;

	//Key	= Variable Name for Attribute
	typedef std::set<tstring> g_sAVar;
	g_sAVar	gsAVar;

	//Key	= Variable Name for Value
	typedef std::set<tstring> g_sVVar;
	g_sVVar	gsVVar;

/////////////////////////////////////////////////////
	/// IForm of the strutures below /////
//////////////////////////////////////////////////////
	
	//Key	= Variable Name for Identifier
	typedef std::set<long> g_sIVarIForm;
	g_sIVarIForm	gsIVarIForm;

	//Key	= Variable Name for Attribute
	typedef std::set<long> g_sAVarIForm;
	g_sAVarIForm	gsAVarIForm;

	//Key	= Variable Name for Value
	typedef std::set<long> g_sVVarIForm;
	g_sVVarIForm	gsVVarIForm;
	


////////////////////////////////////////////////////////////////////////////
	
	
/////////////////////////////////////////////////////////////////////////////
	
	/// *** Links = Conditions Links according to Variable Binding *** /// 

	//Key	= Variable Name
	//Val	= Value Working Memory Element
	typedef std::multimap<int, CAipi_RETE_Links> g_mmLink;
	g_mmLink	gmmLink;






////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////

	/// *** AM = Alpha Memory *** /// 
	
	//Key	= Index of the Alpha Memory Element
	//Val	= Index of the Working Memory Element
	typedef std::multimap<int, int> g_mmAM_WM;
	g_mmAM_WM	gmmAM_WM;

	//Key	= Index of Working Memory Element
	//Val	= Index of the Alpha Memory Element
	typedef std::multimap<int, int> g_mmWM_AM;
	g_mmWM_AM	gmmWM_AM;
	//typedef std::map<int, int> g_mWM_AM;
	//g_mWM_AM	gmWM_AM;


	
	//Key	= Index of the Condition Element
	//Val	= Index of the Alpha Memory Element
	typedef std::map<int, int> g_mCond_AM;
	g_mCond_AM	gmCond_AM;

	//Key	= Index of the Alpha Memory Element
	//Val	= Index of the Condition Element
	typedef std::multimap<int, int> g_mmAM_Cond;
	g_mmAM_Cond	gmmAM_Cond;

	/*
	Symbols:
	I	= Identifier (Id)   
	A	= Atribute (Attr)  
	V	= Value (Val)
	e	= Don`t care
	
	EQ	= Equality (Strings)
	
	Numeric operations
	
	LT	= Lesser than
	LE	= Lesser or Equal than
	GT	= Greater than 
	GE	= Greater or Equal than
	ET	= Equal than
	NE	= Not Equal than (Different)
	AS  = Assignation 
	*/

	//(EQ)Structures for "Equality" Test (Strings)
	
	//Key	= Identifier, Attribute or Value
	//Value = Alpha Memory Index
	typedef std::multimap<tstring, int> g_mmEQ_I_A_V;
	g_mmEQ_I_A_V	gmmEQ_I_A_V;
	typedef std::multimap<tstring, int> g_mmEQ_I_A_K;
	g_mmEQ_I_A_K	gmmEQ_I_A_K;
	typedef std::multimap<tstring, int> g_mmEQ_I_K_V;
	g_mmEQ_I_K_V	gmmEQ_I_K_V;
	typedef std::multimap<tstring, int> g_mmEQ_I_K_K;
	g_mmEQ_I_K_K	gmmEQ_I_K_K;
	typedef std::multimap<tstring, int> g_mmEQ_K_A_V;
	g_mmEQ_K_A_V	gmmEQ_K_A_V;
	typedef std::multimap<tstring, int> g_mmEQ_K_A_K;
	g_mmEQ_K_A_K	gmmEQ_K_A_K;
	typedef std::multimap<tstring, int> g_mmEQ_K_K_V;
	g_mmEQ_K_K_V	gmmEQ_K_K_V;
	typedef std::multimap<tstring, int> g_mmEQ_K_K_K;
	g_mmEQ_K_K_K	gmmEQ_K_K_K;

	
	//(ET)Structures for "Equal Than" Test ( == )
	
	//Key	= Identifier, Attribute or Value
	//Value = Alpha Memory Index
	typedef std::multimap<tstring, int> g_mmET_I_A_V;
	g_mmET_I_A_V	gmmET_I_A_V;
	typedef std::multimap<tstring, int> g_mmET_I_A_K;
	g_mmET_I_A_K	gmmET_I_A_K;
	typedef std::multimap<tstring, int> g_mmET_I_K_V;
	g_mmET_I_K_V	gmmET_I_K_V;
	typedef std::multimap<tstring, int> g_mmET_I_K_K;
	g_mmET_I_K_K	gmmET_I_K_K;
	typedef std::multimap<tstring, int> g_mmET_K_A_V;
	g_mmET_K_A_V	gmmET_K_A_V;
	typedef std::multimap<tstring, int> g_mmET_K_A_K;
	g_mmET_K_A_K	gmmET_K_A_K;
	typedef std::multimap<tstring, int> g_mmET_K_K_V;
	g_mmET_K_K_V	gmmET_K_K_V;
	typedef std::multimap<tstring, int> g_mmET_K_K_K;
	g_mmET_K_K_K	gmmET_K_K_K;

	

	//(NE)Structures for "Not Equal Than" Test ( <> )
	
	//Key	= Identifier, Attribute or Value
	//Value = Alpha Memory Index
	typedef std::multimap<tstring, int> g_mmNE_I_A_V;
	g_mmNE_I_A_V	gmmNE_I_A_V;
	typedef std::multimap<tstring, int> g_mmNE_I_A_K;
	g_mmNE_I_A_K	gmmNE_I_A_K;
	typedef std::multimap<tstring, int> g_mmNE_I_K_V;
	g_mmNE_I_K_V	gmmNE_I_K_V;
	typedef std::multimap<tstring, int> g_mmNE_I_K_K;
	g_mmNE_I_K_K	gmmNE_I_K_K;
	typedef std::multimap<tstring, int> g_mmNE_K_A_V;
	g_mmNE_K_A_V	gmmNE_K_A_V;
	typedef std::multimap<tstring, int> g_mmNE_K_A_K;
	g_mmNE_K_A_K	gmmNE_K_A_K;
	typedef std::multimap<tstring, int> g_mmNE_K_K_V;
	g_mmNE_K_K_V	gmmNE_K_K_V;
	typedef std::multimap<tstring, int> g_mmNE_K_K_K;
	g_mmNE_K_K_K	gmmNE_K_K_K;

	//(LT)Structures for "Less Than" Test ( < )
	
	//Key	= Identifier, Attribute or Value
	//Value = Alpha Memory Index
	typedef std::multimap<tstring, int> g_mmLT_I_A_V;
	g_mmLT_I_A_V	gmmLT_I_A_V;
	typedef std::multimap<tstring, int> g_mmLT_I_A_K;
	g_mmLT_I_A_K	gmmLT_I_A_K;
	typedef std::multimap<tstring, int> g_mmLT_I_K_V;
	g_mmLT_I_K_V	gmmLT_I_K_V;
	typedef std::multimap<tstring, int> g_mmLT_I_K_K;
	g_mmLT_I_K_K	gmmLT_I_K_K;
	typedef std::multimap<tstring, int> g_mmLT_K_A_V;
	g_mmLT_K_A_V	gmmLT_K_A_V;
	typedef std::multimap<tstring, int> g_mmLT_K_A_K;
	g_mmLT_K_A_K	gmmLT_K_A_K;
	typedef std::multimap<tstring, int> g_mmLT_K_K_V;
	g_mmLT_K_K_V	gmmLT_K_K_V;
	typedef std::multimap<tstring, int> g_mmLT_K_K_K;
	g_mmLT_K_K_K	gmmLT_K_K_K;

	//(LE)Structures for "Less or Equal Than" Test ( <= )
	
	//Key	= Identifier, Attribute or Value
	//Value = Alpha Memory Index
	typedef std::multimap<tstring, int> g_mmLE_I_A_V;
	g_mmLE_I_A_V	gmmLE_I_A_V;
	typedef std::multimap<tstring, int> g_mmLE_I_A_K;
	g_mmLE_I_A_K	gmmLE_I_A_K;
	typedef std::multimap<tstring, int> g_mmLE_I_K_V;
	g_mmLE_I_K_V	gmmLE_I_K_V;
	typedef std::multimap<tstring, int> g_mmLE_I_K_K;
	g_mmLE_I_K_K	gmmLE_I_K_K;
	typedef std::multimap<tstring, int> g_mmLE_K_A_V;
	g_mmLE_K_A_V	gmmLE_K_A_V;
	typedef std::multimap<tstring, int> g_mmLE_K_A_K;
	g_mmLE_K_A_K	gmmLE_K_A_K;
	typedef std::multimap<tstring, int> g_mmLE_K_K_V;
	g_mmLE_K_K_V	gmmLE_K_K_V;
	typedef std::multimap<tstring, int> g_mmLE_K_K_K;
	g_mmLE_K_K_K	gmmLE_K_K_K;

	//(GT)Structures for "Greater Than" Test ( > )
	
	//Key	= Identifier, Attribute or Value
	//Value = Alpha Memory Index
	typedef std::multimap<tstring, int> g_mmGT_I_A_V;
	g_mmGT_I_A_V	gmmGT_I_A_V;
	typedef std::multimap<tstring, int> g_mmGT_I_A_K;
	g_mmGT_I_A_K	gmmGT_I_A_K;
	typedef std::multimap<tstring, int> g_mmGT_I_K_V;
	g_mmGT_I_K_V	gmmGT_I_K_V;
	typedef std::multimap<tstring, int> g_mmGT_I_K_K;
	g_mmGT_I_K_K	gmmGT_I_K_K;
	typedef std::multimap<tstring, int> g_mmGT_K_A_V;
	g_mmGT_K_A_V	gmmGT_K_A_V;
	typedef std::multimap<tstring, int> g_mmGT_K_A_K;
	g_mmGT_K_A_K	gmmGT_K_A_K;
	typedef std::multimap<tstring, int> g_mmGT_K_K_V;
	g_mmGT_K_K_V	gmmGT_K_K_V;
	typedef std::multimap<tstring, int> g_mmGT_K_K_K;
	g_mmGT_K_K_K	gmmGT_K_K_K;

	//(GE)Structures for "Greater or Equal Than" Test ( >= )
	
	//Key	= Identifier, Attribute or Value
	//Value = Alpha Memory Index
	typedef std::multimap<tstring, int> g_mmGE_I_A_V;
	g_mmGE_I_A_V	gmmGE_I_A_V;
	typedef std::multimap<tstring, int> g_mmGE_I_A_K;
	g_mmGE_I_A_K	gmmGE_I_A_K;
	typedef std::multimap<tstring, int> g_mmGE_I_K_V;
	g_mmGE_I_K_V	gmmGE_I_K_V;
	typedef std::multimap<tstring, int> g_mmGE_I_K_K;
	g_mmGE_I_K_K	gmmGE_I_K_K;
	typedef std::multimap<tstring, int> g_mmGE_K_A_V;
	g_mmGE_K_A_V	gmmGE_K_A_V;
	typedef std::multimap<tstring, int> g_mmGE_K_A_K;
	g_mmGE_K_A_K	gmmGE_K_A_K;
	typedef std::multimap<tstring, int> g_mmGE_K_K_V;
	g_mmGE_K_K_V	gmmGE_K_K_V;
	typedef std::multimap<tstring, int> g_mmGE_K_K_K;
	g_mmGE_K_K_K	gmmGE_K_K_K;

	//(AS)Structures for "Assignation" Test ( = )
	
	//Key	= Identifier, Attribute or Value
	//Value = Alpha Memory Index
	typedef std::multimap<tstring, int> g_mmAS_I_A_V;
	g_mmAS_I_A_V	gmmAS_I_A_V;
	typedef std::multimap<tstring, int> g_mmAS_I_A_K;
	g_mmAS_I_A_K	gmmAS_I_A_K;
	typedef std::multimap<tstring, int> g_mmAS_I_K_V;
	g_mmAS_I_K_V	gmmAS_I_K_V;
	typedef std::multimap<tstring, int> g_mmAS_I_K_K;
	g_mmAS_I_K_K	gmmAS_I_K_K;
	typedef std::multimap<tstring, int> g_mmAS_K_A_V;
	g_mmAS_K_A_V	gmmAS_K_A_V;
	typedef std::multimap<tstring, int> g_mmAS_K_A_K;
	g_mmAS_K_A_K	gmmAS_K_A_K;
	typedef std::multimap<tstring, int> g_mmAS_K_K_V;
	g_mmAS_K_K_V	gmmAS_K_K_V;
	typedef std::multimap<tstring, int> g_mmAS_K_K_K;
	g_mmAS_K_K_K	gmmAS_K_K_K;


//////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////

	/// *** BM = Beta Memory **** /// 


	//Key	= Index of Beta Memory
	//Val	= Beta Memory Object (Working Memory Element)
	typedef std::multimap<int, CAipi_RETE_BM> g_mmBM;
	g_mmBM	gmmBM;

	//Key	= Index of Beta Memory
	//Val	= Beta Memory Element Information Object 
	typedef std::map<int, CAipi_RETE_BME> g_mBM_Info;
	g_mBM_Info	gmBM_Info;


	//Key	= Index of Beta Memory
	//Val	= Linked Conditions Elements ( content of each Beta Memory)
	typedef std::multimap<int, CAipi_RETE_BMCond> g_mmBM_Cond;
	g_mmBM_Cond	gmmBM_Cond;
	

	//Key	= Index of Beta Memory
	//Val	= Working Memory Elements ( content of each Beta Memory)
	typedef std::multimap<int, int> g_mmBM_WM;
	g_mmBM_WM	gmmBM_WM;
	

	//Tokens in Beta Memory
	//std::vector <int> g_vBM_TK;

	
	
	

	
///////////////////////////////////////////////////////////////////////////////////	


//////////////////////////////////////////////////////////////////////////////////
	
	/// *** TK = Token *** ///

	//Key	= Index of the Child Token Element
	//Val	= Token Object (includes Parent Token)
	typedef std::map<int, CAipi_RETE_TK> g_mTK;
	g_mTK	gmTK;

	//Key	= Index of the Working Memory Element
	//Val	= Parent Token Index
	typedef std::multimap<int, int> g_mmWM_ParentTK;
	g_mmWM_ParentTK	gmmWM_ParentTK;

	//Key	= Index of the Working Memory Element
	//Val	= Child Token Index
	typedef std::multimap<int, int> g_mmWM_ChildTK;
	g_mmWM_ChildTK	gmmWM_ChildTK;
	
	//Key	= Index of Parent Token
	//Val	= Token Index
	typedef std::multimap<int, int> g_mmTKParent_TKChild;
	g_mmTKParent_TKChild	gmmTKParent_TKChild;
	

	//Key	= Index of Parent Token
	//Val	= Linked Child Tokens to the Parent Token   
	typedef std::multimap<int, int> g_mmTKParent_TKLink;
	g_mmTKParent_TKLink	gmmTKParent_TKLink;


	
/////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////


	
	/// *** Node = Node *** ///

	//Key	= Index of Node Element
	//Val	= Node Object
	typedef std::map<int, CAipi_RETE_Node> g_mNode;
	g_mNode	gmNode;



	/// *** JNode = Join Node *** /// 

	//Key	= Index of Join Node Element
	//Val	= Join Node Object
	typedef std::map<int, CAipi_RETE_JNode> g_mJNode;
	g_mJNode	gmJNode;

	//Key	= Index of Beta Memory Element
	//Val	= Index of Join Node Element
	typedef std::multimap<int, int> g_mmBM_ChildJN;
	g_mmBM_ChildJN	gmmBM_ChildJN;

	//Vector of Repeated BM Child JN
	std::vector <int> g_vBMChildJN;



/////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////

	//// **** Conditions **** ////


	//Key	= Index of Condition Element
	//Val	= Condition Object
	typedef std::multimap<int, CAipi_RETE_Cond> g_mmCond1;
	g_mmCond1	gmmCond1;

	//Key	= Index of Condition Element
	//Val	= Condition Object
	typedef std::map<int, CAipi_RETE_Cond> g_mCond2;
	g_mCond2	gmCond2;
	
	//This structure saves other conditions that create matches in the BM
	//besides the one that are tested in the createBM function
	//Key	= Index of Condition1
	//Val	= Index of Condition2
	typedef std::map<int, int> g_mPreCondBind;
	g_mPreCondBind	gmPreCondBind;
	


/////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////

	//// **** Join Conditions  == NodeCond **** ////


	//Key	= Index of Node Element
	//Val	= Conditions Object inludes parent condition and child condtion
	typedef std::multimap<int, CAipi_RETE_NodeCond> g_mmNodeCond;
	g_mmNodeCond	gmmNodeCond;


	
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////

	/// *** Negated Node = NNode **** ////
	//Special node for negated conditions


	//Key	= Index of NOT Node Element
	//Val	= NotNode Object
	typedef std::map<int, CAipi_RETE_NNode> g_mNNode;
	g_mNNode	gmNNode;
	
	//Key	= Index of Condition Element
	//Val	= Index of NotNode Element
	typedef std::map<int, int> g_mCond_NN;
	g_mCond_NN	gmCond_NN;

	
	//Key	= Index of NOT Node Element
	//Val	= Index of Token Element
	typedef std::multimap<int, int> g_mmNN_TK;
	g_mmNN_TK	gmmNN_TK;
	

	//Key	= Index of Token Element
	//Val	= Index of Token Object
	//typedef std::multimap<int, RETE_Token> g_mTokenNN;
	//g_mTokenNN	gmTokenNN;


	//No se usa
	//Key	= Index of Working Memory Element
	//Val	= Index of NotNode Element
	typedef std::multimap<int, int> g_mmNN_WM;
	g_mmNN_WM	gmmNN_WM;

	//Key	= Index of NotNode Element
	//Val	= Index of Working Memory Element
	typedef std::map<int, int> g_mWM_NN;
	g_mWM_NN	gmWM_NN;


/////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////
	
	/// *** NCC = Negated Conjuction Conditions *** ///
	//Special nodes for negated conjunction conditions
	
	//Key	= Index of NCC
	//Val	= NCC Object 
	typedef std::map<int, CAipi_RETE_NCCNode> g_mNCCNode;
	g_mNCCNode	gmNCCNode;


	//Key	= Index of NCC
	//Val	= Index Condition
	typedef std::multimap<int, int> g_mmNCC_Cond;
	g_mmNCC_Cond	gmmNCC_Cond;

	//Key	= Index of Condition
	//Val	= Index of NCC
	typedef std::multimap<int, int> g_mmCond_NCC;
	g_mmCond_NCC	gmmCond_NCC;

	
	//Key	= Index of NCC Node
	//Val	= Index of BM
	typedef std::map<int, int> g_mNCCN_BM;
	g_mNCCN_BM	gmNCCN_BM;

	
	//Key	= Index of NCC Partner Node
	//Val	= Index of BM
	typedef std::map<int, int > g_mNCCPartnerN_BM;
	g_mNCCPartnerN_BM	gmNCCPartnerN_BM;

	//Key	= Index of NCC Element
	//Val	= Index of Token Element
	typedef std::multimap<int, int> g_mmNCCPartnerN_TK;
	g_mmNCCPartnerN_TK	gmmNCCPartnerN_TK;
	

	
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////

	/// *** DNode = Dummy Node *** ////
	//This is a fake node generated at the beginning of RETE net
	//It is the first node created for the RETE Network

	//Key	= Index of Dummy Node Condition Element
	//Val	= Production Memory Index
	typedef std::map<int, CAipi_RETE_DNode> g_mDNode;
	g_mDNode	gmDNode;
	




/////////////////////////////////////////////////////////////////////////////////////////

	
////////////////////////////////////////////////////////////////////////////////////////

	/// *** PN = Production Node *** /// 
	//The production node represents the conflict set.
	//This node is the result node of the matching process of a production  
	
	//Key	= Index of Production Node
	//Val	= Production Node Object
	typedef std::map<int, CAipi_RETE_PNode> g_mPNode;
	g_mPNode	gmPNode;

	//Vector of Production Memories that must fired
	std::vector <long> g_vFiredPM;

	/// Production Refraction ////
	//Vector saves all fired productions to check that PM elements that
	//were fired previously will not fired again
	//std::vector <long> g_vRefractionPM;
	//Key	= Fired Production Memory
	typedef std::set<long> g_sRefractionPM;
	g_sRefractionPM	gsRefractionPM;



//////////////////////////////////////////////////////////////////////////////////////////

			/// CONFLICT RESOLUTION STRATEGY ///

////////////////////////////////////////////////////////////////////////////////////////////

	/// *** Strategy: Recency *** ///
	//Key	= Recency Time Tag
	//Val	= Conflict Resolution Recency Object
	typedef std::multimap<int, CAipi_CR_Recency> g_mmCR_Recency;
	g_mmCR_Recency	gmmCR_Recency;
	//Key	= Sum of Recency Time Tags
	//Val	= Conflict Resolution Recency Tags Object
	typedef std::multimap<int, CAipi_CR_RecencyTags> g_mmCR_RecencyTags;
	g_mmCR_RecencyTags	gmmCR_RecencyTags;


	
	/// *** Strategy: Specificity *** ///
	//Key	= Number of Conditions
	//Val	= Conflict Resolution Specificity Object
	typedef std::multimap<int, CAipi_CR_Specificity> g_mmCR_Specificity;
	g_mmCR_Specificity	gmmCR_Specificity;
	
	
	
	/// *** Strategy: Priority *** ///
	//Key	= Production Weight or Priority
	//Val	= Conflict Resolution Priority Object
	typedef std::multimap<int, CAipi_CR_Priority> g_mmCR_Priority;
	g_mmCR_Priority	gmmCR_Priority;
	
	
	
	/// *** Strategy: MEA *** ///
	//Key	= First Condition Recency Time Tag
	//Val	= Conflict Resolution MEA Object
	typedef std::multimap<int, CAipi_CR_MEA> g_mmCR_MEA;
	g_mmCR_MEA	gmmCR_MEA;
	
	
	/// Production Agenda ////
	std::vector <long> g_vAgendaPM;

	



//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

public:

	//Current Grid Control in use
	int						m_CurrentGrid;
	
	//Key	= GridControl Variable Name
	//Val	= Boolean State ofthe Variable
	typedef std::map<tstring, bool> g_mGridVar_State;
	g_mGridVar_State	gmGridVar_State;


//AIPITabView
	CGridCtrl				m_GridLHS;
	CGridCtrl				m_GridRHS;
	CGridCtrl				m_GridWM;
	CGridCtrl				m_GridCondLink;
	CGridCtrl				m_GridAgenda;
	CGridCtrl				m_GridAM;
	CGridCtrl				m_GridBM;
	CGridCtrl				m_GridBM_TK;
	CGridCtrl				m_GridRETE;
//InductionTabView

	CGridCtrl				m_GridInduction;
	
//Grid Variables
//CPageFileDlg
	BOOL	m_bVirtualMode;
	BOOL	m_bCallback;
    BOOL    m_bTables;
	BOOL    m_bQuery;
	BOOL    m_bData;
	BOOL    m_bVTables;	

//CPageEditDlg
	BOOL	m_bEditablePM;
	BOOL	m_bEditableWM;
	BOOL    m_bEditable;
	
//CPageInsertDlg

//CPageCellSizeDlg
	BOOL	m_bFitGrid;
	BOOL	m_bColumnResize;
	BOOL	m_bRowResize;

	
//CPageFormatDlg
	BOOL	m_bHorizontal;
	BOOL	m_bVertical;
	BOOL    m_bItalic;
	BOOL    m_bBold;
	BOOL    m_bNormal;
	BOOL    m_bVerticalHeader;
	BOOL    m_bTitleTips;
	
//CPageOptionsDlg	
	BOOL	m_bSort;
	BOOL	m_bToolTips;
	BOOL	m_bCellSelect;
	

///_______________________________________________________________________________/////

////////////////////////////////////////////////////////////////////////////////////////
	//// AIPI Interpreter Structures ////
////////////////////////////////////////////////////////////////////////////////////////
/*
	Symbols:
	IntForm		= Internal form (iform)   
	Pos			= Cursor Position  
	Op			= Operator

*/


/// Handle Tokenizer Struct  ////

	typedef std::vector	<CAipi_Tokenizer> g_vTokenizer;
	g_vTokenizer	gvTokenizer;


/// Handle Script Codes ////

	//Key	= ScriptId
	//Val	= CAipi_ScriptCode Object
	typedef std::map<long, CAipi_ScriptCode> g_mScriptCode;
	g_mScriptCode	gmScriptCode;

	//Key	= PM Identifier
	//Val	= CAipi_ScriptLocation Object
	typedef std::multimap<long, CAipi_ScriptLocation> g_mmScriptLocation;
	g_mmScriptLocation	gmmScriptLocation;



/// Handle DataBase Connection Parameters ////
	//Key	= DataBase Name
	//Val	= CAipi_DBInfo Object
	


/// Handle Symbol Table ////

///Global Declarations	
	//Key	= Symbol Identifier
	//Val	= CAipi_SymbolTable Object
	typedef std::map<long, CAipi_STableGlobalNumeric> g_mSTableGlobalNumeric;
	g_mSTableGlobalNumeric		gmSTableGlobalNumeric;

	//Key	= Symbol Identifier
	//Val	= CAipi_SymbolTable Object
	typedef std::map<long, CAipi_STableGlobalLiteral> g_mSTableGlobalLiteral;
	g_mSTableGlobalLiteral			gmSTableGlobalLiteral;

///Local Declarations	
	//Key	= Symbol Identifier
	//Val	= CAipi_SymbolTable Object
	typedef std::map<long, CAipi_STableLocalNumeric> g_mSTableLocalNumeric;
	g_mSTableLocalNumeric		gmSTableLocalNumeric;

	//Key	= Symbol Identifier
	//Val	= CAipi_SymbolTable Object
	typedef std::map<long, CAipi_STableLocalLiteral> g_mSTableLocalLiteral;
	g_mSTableLocalLiteral			gmSTableLocalLiteral;


///////////////////////////////////////////////////////////////
	//Key	= Symbol Function Identifier
	//Val	= CAipi_SymbolTable Object
	typedef std::map<long, CAipi_SymbolTable> g_mSTableFunc;
	g_mSTableFunc			gmSTableFunc;


	//Key	= Symbol Attribute Class Identifier
	//Val	= CAipi_SymbolTableClass Object
	typedef std::multimap<long, CAipi_STableClass> g_mmSTableClass;
	g_mmSTableClass		gmmSTableClass;


	//Key	= Symbol Function Parameters
	//Val	= CAipi_SymbolTable Object
	//typedef std::multimap<long, CAipi_SymbolTable> g_mmSTableFuncParam;
	//g_mmSTableFuncParam		gmmSTableFuncParam;
	

	//Key	= Symbol Class Parameters
	//Val	= CAipi_SymbolTable Object
	//typedef std::multimap<long, CAipi_SymbolTable> g_mmSTableClassParam;
	//g_mmSTableClassParam	gmmSTableClassParam;
	
	
		

	
///  Handle Symbols Internal Form  ////

	//Key	= KeyWord 
	//Val	= KeyWord Index
	typedef std::map<tstring, long> g_mKeyWord;
	g_mKeyWord	gmKeyWord;

	//Key	= KeyWord Index
	//Val	= KeyWord 
	typedef std::map<long, tstring> g_mIdKeyWord;
	g_mIdKeyWord	gmIdKeyWord;


	//Key	= Doble or Triple KeyWord Index
	//Val	= Doble or Triple KeyWord (Doble or Triple string operator keyword )
	typedef std::map<int, tstring> g_mOperator;
	g_mOperator	gmOperator;

	
////  Handle Identifiers Information  ////	
	
	//Key	= Identifier 
	//Val	= Identifier Index
	typedef std::map<tstring, double> g_mId_IntForm;
	g_mId_IntForm	gmId_IntForm;


	

	
/// Handle AIPI Error messages ////

	//Key	= Error Index
	//Val	= Error Description Message
	typedef std::map<int, CAipi_Error> g_mError;
	g_mError	gmError;



// Vector of file directives
	std::vector <CString> g_vDirectives;


/////////////////////////////////////////////////////////////
	/// Workspace Global Vars
////////////////////////////////////////////////////////////

	


/// Workspace Tree Structure
	
	//Key	= Node Text
	//Val	= Node Object
	typedef std::map<CString, CWorkspaceTree1> g_mWSPTree1;
	g_mWSPTree1	gmWSPTree1;
	typedef std::map<CString, HTREEITEM> g_mWSPTree2;
	g_mWSPTree2	gmWSPTree2;
	typedef std::map<CString, HTREEITEM> g_mWSPTree3;
	g_mWSPTree3	gmWSPTree3;

	typedef std::map<CString, CFunctionProperties> g_mFuncProp;
	g_mFuncProp  gmFuncProp;

	typedef std::map<HTREEITEM, CWorkspaceLocation> g_mWSPLocation;
	g_mWSPLocation	gmWSPLocation;


///////////////////////////////////////////////////////////////////////////////////////////////////////////


// Operations
public:
	void	StopTimer(CPerfTimer t, CString msg);	
	void	SaveWorkspace();
	void	LoadWorkspace();

	void	ProjFileWrite(CString proj_name, CString proj_author, CString proj_desc, CString proj_root, CString proj_date, CString proj_inf, CString proj_resource [4]);
	void	ProjFileRead(CString proj_name, CString proj_root);
	int		ProjFileFind(CString proj_name, CString proj_root, CString txt);
	void	WSPTree1Write(CString filePath, CString hTRoot, CString hTClass, CString hTFunc, CString hTQuery, CString hTRule, CString Var);
	void	WSPTree1Read(CString proj_name, CString proj_root);

	void    PoblateRuleView();

	void	CheckMenuSkinType(); 
	void	CustomizeApp();
	void	SetToolBarArrows();
	void	AddComboItem(CString word, int item);
	

protected:
	void CreateComboToolBar();
	BOOL CreateOutputTabView();
	BOOL CreateWorkspaceTabView();
	BOOL CreatePropertiesBar();
	BOOL CreateInductionTabView();
	BOOL CreateAIPITabView();
	BOOL CreateCommandDlgBar();
	BOOL CreateJukeBoxDlg();
	BOOL CreateMediaPlayerDlg();
	BOOL CreateCalendarDlg();
	BOOL CreateImageDlg();
	BOOL CreateDxfCadDlg();
	BOOL CreateImageFilterDlg();
	BOOL CreateOleDBDlg();


	BOOL CreateImageCtrl();
	BOOL CreateEditInfoCtrl();
	BOOL CreateInfoCtrl();
	BOOL CreateListOptionCtrl();
	BOOL CreateListMultiOptionCtrl();
	BOOL CreateNSChartBarCtrl();
	BOOL CreateChartBarCtrl();
	BOOL CreateGraphBarCtrl();
	BOOL CreateStaticMeterCtrl();



	BOOL CreateStatusBar();
	BOOL CreateStandardToolBar();

	//BOOL CreateProjectToolBar();
	//BOOL CreateImageDlgToolBar();
	//BOOL CreateCalendarDlgToolBar();
	//BOOL CreateNSChartBarCtrlToolBar();
	//BOOL CreateChartBarCtrlToolBar();
	//BOOL CreateGraphBarCtrlToolBar();
	//BOOL CreateStaticMeterCtrlToolBar();
	//BOOL CreateImageCtrlToolBar();
	//BOOL CreateListOptionCtrlToolBar();

public:
	//Others command instructions
	void Cmd_OpenCommandDlgBar();
	void Cmd_CloseCommandDlgBar();
	
	void Cmd_OpenJukeBoxDlg();
	void Cmd_CloseJukeBoxDlg();
	void Cmd_PlayJukeBoxDlg();
	void Cmd_PathJukeBoxDlg(CString strPath);
	
	void Cmd_OpenMediaPlayerDlg();
	void Cmd_CloseMediaPlayerDlg();
	void Cmd_PlayMediaPlayerDlg();
	void Cmd_PathMediaPlayerDlg(CString strPath);
	
	void Cmd_OpenListOptionCtrl();
	void Cmd_CloseListOptionCtrl();
	void Cmd_InsertListOptionCtrl(LPCTSTR lpcItem, LPCTSTR lpcTip);
	
	void Cmd_OpenImageFilterDlg();
	void Cmd_CloseImageFilterDlg();
	void Cmd_PathImageFilterDlg(CString strPath);
	
	void Cmd_OpenOleDBDlg();
	void Cmd_CloseOleDBDlg();

	
public:
	//Grid Controls Functions
	int		SelectGrid();
	bool	FindGridVarState(tstring var);
	void	InitGridVars();
	void	CreateGridVarState(tstring var, bool state);
	void	ChangeGridVarState(tstring var, bool state);
	void	UpdateGridStates(int grid);
	void	PrintGrid();



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:  // control bar embedded members
	//DialogBar for user inputs
	CCommandDlgBar			m_wndCommandDlgBar;
	COutputTabView			m_wndOutputTabView;
	CWorkspaceTabView		m_wndWorkspaceTabView;
	CPropertiesBar			m_wndPropertiesBar;
	CInductionTabView		m_wndInductionTabView;
	CAIPITabView			m_wndAIPITabView;
	
	
	CJukeBoxDlg				m_wndJukeBoxDlg;
	CMediaPlayerDlg			m_wndMediaPlayerDlg;
	CImageDlg				m_wndImageDlg;
	CDxfCadDlg				m_wndDxfCadDlg;
	CImageFilterDlg			m_wndImageFilterDlg;
	CCalendarDlg			m_wndCalendarDlg;
	COleDBDlg				m_wndOleDBDlg;
	
	CImageCtrl				m_wndImageCtrl;
	CInfoCtrl				m_wndInfoCtrl;
	CEditInfoCtrl			m_wndEditInfoCtrl;
	CListOptionCtrl			m_wndListOptionCtrl;
	CListMultiOptionCtrl	m_wndListMultiOptionCtrl;
	CNSChartBarCtrl			m_wndNSChartBarCtrl;
	CChartBarCtrl			m_wndChartBarCtrl;
	CGraphBarCtrl			m_wndGraphBarCtrl;
	CStaticMeterCtrl		m_wndStaticMeterCtrl;
	


public:	
	
	
	COXCoolToolBar		m_wndToolBar;
	COXCoolToolBar		m_wndToolBarProject;
	
	/*
	COXCoolToolBar		m_wndToolBarListOptionCtrl;
	COXCoolToolBar		m_wndToolBarMultiOptionCtrl;	
	COXCoolToolBar		m_wndToolBarImageCtrl;
	COXCoolToolBar		m_wndToolBarImageDlg;
	COXCoolToolBar		m_wndToolBarImageFilterDlg;
	COXCoolToolBar		m_wndToolBarCalendarDlg;	
	COXCoolToolBar		m_wndToolBarJukeBox;
	COXCoolToolBar		m_wndToolBarMediaPlayer; 
	COXCoolToolBar		m_wndToolBarStaticMeterCtrl;	
	COXCoolToolBar		m_wndToolBarNSChartBarCtrl;	
	COXCoolToolBar		m_wndToolBarChartBarCtrl;
	COXCoolToolBar		m_wndToolBarGraphBarCtrl;
	COXCoolToolBar		m_wndToolBarCronometer;
*/
	/*
	CToolBar		m_wndToolBarListOptionCtrl;
	CToolBar		m_wndToolBarMultiOptionCtrl;	
	CToolBar		m_wndToolBarImageCtrl;
	CToolBar		m_wndToolBarImageDlg;
	CToolBar		m_wndToolBarImageFilterDlg;
	CToolBar		m_wndToolBarCalendarDlg;	
	CToolBar		m_wndToolBarJukeBox;
	CToolBar		m_wndToolBarMediaPlayer; 
	CToolBar		m_wndToolBarStaticMeterCtrl;	
	CToolBar		m_wndToolBarNSChartBarCtrl;	
	CToolBar		m_wndToolBarChartBarCtrl;
	CToolBar		m_wndToolBarGraphBarCtrl;
	CToolBar		m_wndToolBarCronometer;
*/


	COXTabClientWnd		m_MTIClientWnd;
	COXStatusBar		m_wndStatusBar;
	COXCustomizeManager	m_customizeManager; // customize manager
	
	// Custom buttons for the toolbar
	COXCustomTBComboBox<COXSkinnedComboBox> m_FindCombo;

	
	
// Generated message map functions
public:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	afx_msg void OnSysColorChange();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnUpdateLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDoc(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStyle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFold(CCmdUI* pCmdUI);
	afx_msg void OnUpdateInsert(CCmdUI* pCmdUI);
	afx_msg void OnViewOutputTabView();
	afx_msg void OnUpdateViewOutputTabView(CCmdUI* pCmdUI);
	afx_msg void OnViewCommandDlgBar();
	afx_msg void OnUpdateViewCommandDlgBar(CCmdUI* pCmdUI);
	afx_msg void OnSettingsCustomize();
	afx_msg void OnViewCtrlJukeBoxDlg();
	afx_msg void OnUpdateViewCtrlJukeBoxDlg(CCmdUI* pCmdUI);
	afx_msg void OnViewCtrlMediaPlayerDlg();
	afx_msg void OnUpdateViewCtrlMediaPlayerDlg(CCmdUI* pCmdUI);
	afx_msg void OnViewCtrlImageDlg();
	afx_msg void OnUpdateViewCtrlImageDlg(CCmdUI* pCmdUI);
	afx_msg void OnViewCtrlImageCtrl();
	afx_msg void OnUpdateViewCtrlImageCtrl(CCmdUI* pCmdUI);
	afx_msg void OnViewCtrlListOptionCtrl();
	afx_msg void OnUpdateViewCtrlListOptionCtrl(CCmdUI* pCmdUI);
	afx_msg void OnViewCtrlNSChartBarCtrl();
	afx_msg void OnUpdateViewCtrlNSChartBarCtrl(CCmdUI* pCmdUI);
	afx_msg void OnViewCtrlChartBarCtrl();
	afx_msg void OnUpdateViewCtrlChartBarCtrl(CCmdUI* pCmdUI);
	afx_msg void OnViewCtrlCalendarDlg();
	afx_msg void OnUpdateViewCtrlCalendarDlg(CCmdUI* pCmdUI);
	afx_msg void OnViewCtrlStaticMeterCtrl();
	afx_msg void OnUpdateViewCtrlStaticMeterCtrl(CCmdUI* pCmdUI);
	afx_msg void OnViewCtrlImageFilterDlg();
	afx_msg void OnUpdateViewCtrlImageFilterDlg(CCmdUI* pCmdUI);
	afx_msg void OnViewCtrlListMultiOptionCtrl();
	afx_msg void OnUpdateViewCtrlListMultiOptionCtrl(CCmdUI* pCmdUI);
	afx_msg void OnViewCtrlGraphBarCtrl();
	afx_msg void OnUpdateViewCtrlGraphBarCtrl(CCmdUI* pCmdUI);
	afx_msg void OnViewCtrlEditInfoBar();
	afx_msg void OnUpdateViewCtrlEditInfoBar(CCmdUI* pCmdUI);
	afx_msg void OnViewCtrlInfoCtrl();
	afx_msg void OnUpdateViewCtrlInfoCtrl(CCmdUI* pCmdUI);
	afx_msg void OnViewWorkSpaceTabView();
	afx_msg void OnUpdateViewWorkSpaceTabView(CCmdUI* pCmdUI);
	afx_msg void OnViewCtrlOleDBDlg();
	afx_msg void OnUpdateViewCtrlOleDBDlg(CCmdUI* pCmdUI);
	afx_msg void OnViewCtrlDxfCadDlg();
	afx_msg void OnUpdateViewCtrlDxfCadDlg(CCmdUI* pCmdUI);
	afx_msg void OnSettingsSkinClassic();
	afx_msg void OnSettingsSkinOfficeXP();
	afx_msg void OnSettingsSkinOffice2003();
	afx_msg void OnViewInductionFrameDlg();
	afx_msg void OnUpdateViewInductionFrameDlg(CCmdUI* pCmdUI);
	afx_msg void OnViewAipiFrameDlg();
	afx_msg void OnUpdateViewAipiFrameDlg(CCmdUI* pCmdUI);
	afx_msg void OnProjOpen();
	afx_msg void OnProjNew();
	afx_msg void OnFileSaveAll();
	afx_msg void OnViewPropertiesBar();
	afx_msg void OnUpdateViewPropertiesBar(CCmdUI* pCmdUI);
	afx_msg void OnProjClose();
	afx_msg void OnProjSave();
	afx_msg void OnUpdateFileSaveAll(CCmdUI* pCmdUI);
	afx_msg void OnAppExit();
	//}}AFX_MSG

	afx_msg void OnDropDown(NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnSelChangeCombo();
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__A7CE49D9_98D8_442F_BFFE_ED0F0E4EB30F__INCLUDED_)
