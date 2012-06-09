//////////////////////////////////////////////////////////////////////////////////
// CimageProcess.h
// Author : BAla
//////////////////////////////////////////////////////////////////////////////////

#ifndef _CIMAGEPROCESS_H_
#define _CIMAGEPROCESS_H_

#include <windows.h>

// Load GDI plus
#if !defined (_GDIPLUS_H)
	//#include "..\gdiplus\Include\GdiPlus.h"
	#include	".\\ImplementationGDIPLUS\\gdiplus.h"
	#pragma comment(lib, "GdiPlus")
	using namespace Gdiplus;
#endif

// Image Processing class
class CImageProcess
{
public:
	// Constructor
	CImageProcess();
	
	// Get the Image width
	int GetImageWidth();
	// Get the Image Height
	int GetImageHeight();

	// Load the image
	HDC LoadImage(HDC hDC, unsigned short *pszImageName, RECT &r);

	// Image processing
	void DisplayBlur(HDC hDC, RECT &r);
	void DisplaySharpness(HDC hDC, RECT &r);
	void DisplayInvertColor(HDC hDC, RECT &r);
	void DisplayBlackAndWhite(HDC hDC, RECT &r);
	void DisplayContrast(HDC hDC, RECT &r, int nContrastVal);	
	void DisplayBrightness(HDC hDC, RECT &r, int nRedVal, int nGreenVal, int nBlueVal);
	
	// Destructor
	~CImageProcess();

private:
	// For GDI plus
	GdiplusStartupInput m_gdiplusStartupInput;
	ULONG_PTR	m_gdiplusToken;

	// Memory bitmap
	HBITMAP m_hBitmap;

	// Image width and height
	int m_nWidth;
	int m_nHeight;
};

#endif
