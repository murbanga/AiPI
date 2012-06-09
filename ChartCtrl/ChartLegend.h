/*
 *
 *	ChartLegend.h
 *
 *	Written by Cédric Moonen (cedric_moonen@hotmail.com)
 *
 *
 *
 *	This code may be used for any non-commercial and commercial purposes in a compiled form.
 *	The code may be redistributed as long as it remains unmodified and providing that the 
 *	author name and this disclaimer remain intact. The sources can be modified WITH the author 
 *	consent only.
 *	
 *	This code is provided without any garanties. I cannot be held responsible for the damage or
 *	the loss of time it causes. Use it at your own risks
 *
 *	An e-mail to notify me that you are using this code is appreciated also.
 *
 *
 */

#if !defined(AFX_CHARTLEGEND_H__CD72E5A0_8F52_472A_A611_C588F642080B__INCLUDED_)
#define AFX_CHARTLEGEND_H__CD72E5A0_8F52_472A_A611_C588F642080B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ChartObject.h"

#include <string>

class CChartSerie;

class CChartLegend : public CChartObject  
{
	friend CChartCtrl;

public:
//	int SerieIndexFromPoint(CPoint NewPoint) const;
#ifdef _UNICODE
	void SetFont(int iPointSize, std::wstring strFaceName)
	{
		m_iFontSize = iPointSize;
		m_strFontName = strFaceName;
		
	}
#else
	void SetFont(int iPointSize, std::string strFaceName)
	{
		m_iFontSize = iPointSize;
		m_strFontName = strFaceName;
	}
#endif

	CChartLegend(CChartCtrl* pParent);
	virtual ~CChartLegend();


private:
	void Draw(CDC* pDC);
	void SetPosition(int LeftBorder, int TopBorder, CDC* pDC);
	CSize GetSize(CDC* pDC) const;
	int         m_iFontSize;
	int m_iTextHeigh;

#ifdef UNICODE
	std::wstring m_strFontName;
#else
	std::string m_strFontName;
#endif
	
};

#endif // !defined(AFX_CHARTLEGEND_H__CD72E5A0_8F52_472A_A611_C588F642080B__INCLUDED_)
