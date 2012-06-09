//////////////////////////////////////////////////////////////////////////////////
// CimageProcess.cpp
// Author : BAla
//////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CimageProcess.h"

/////////////////////////////////////////////////////////////////////////////////////////////////
// Method name	: CImageProcess
// Arguments	: void
// Return type	: None
// Description	: Initializes Microsoft Windows GDI+
// Precondition	: Should be gdiplus.dll in currnet system
// Postcondition: After finishing work gdiplus should be shutdown
/////////////////////////////////////////////////////////////////////////////////////////////////
CImageProcess::CImageProcess()
{
	GdiplusStartup(&m_gdiplusToken, &m_gdiplusStartupInput, NULL);	
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Method name	: GetImageWidth
// Arguments	: void
// Return type	: int
// Description	: Gets the image Width, in pixels, of this image
// Precondition	: Image should be load
// Postcondition: None
/////////////////////////////////////////////////////////////////////////////////////////////////
int CImageProcess::GetImageWidth()
{
	return m_nWidth;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Method name	: GetImageHeight
// Arguments	: void
// Return type	: int
// Description	: Gets the image Height, in pixels, of this image
// Precondition	: Image should be load
// Postcondition:
/////////////////////////////////////////////////////////////////////////////////////////////////
int CImageProcess::GetImageHeight()
{
	return m_nHeight;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Method name	: LoadImage
// Arguments	: 
//	1) HDC hDC -- Screen Device context 
//	2) unsigned short *pszImageName -- File name (GDI+ support BMP, Graphics Interchange Format (GIF), JPEG, PNG, TIFF, and EMF)
//	3) RECT &r -- Rectangle size
// Return type	: HDC -- Load image into memory. Return memory device context.
// Description	: Loads an image into memory. That image file should be the following format.
//				  BMP, Graphics Interchange Format (GIF), JPEG, PNG, TIFF, and EMF
// Precondition	: gdiplus should be intialize
// Postcondition: It's return memory DC(Device Context). Call DeleteDC when you finish.
/////////////////////////////////////////////////////////////////////////////////////////////////
HDC CImageProcess::LoadImage(HDC hDC, unsigned short *pszImageName, RECT &r)
{
	if (m_hBitmap)
	{
		DeleteObject(m_hBitmap);
		m_hBitmap = NULL;
	}
	
	HDC hMemDC = CreateCompatibleDC(hDC);	
	//Image image(pszImageName);
	Bitmap image(pszImageName);

	m_nWidth  = image.GetWidth();
	m_nHeight = image.GetHeight();

	m_hBitmap = CreateCompatibleBitmap(hDC, m_nWidth, m_nHeight);
	SelectObject(hMemDC, m_hBitmap);

	Graphics g(hMemDC);
	CachedBitmap cachedBitmap(&image, &g);
	
	Rect rect(0, 0, m_nWidth, m_nHeight);
	
	//temporary solution to erase the background
	Region Rgn;
	g.GetClip(&Rgn);
	SolidBrush grayBrush(Color::White);
	g.FillRegion(&grayBrush, &Rgn);
	g.DrawCachedBitmap(&cachedBitmap, 0, 0);
	//g.DrawImage(&image, rect);
	g.Flush(FlushIntentionFlush) ;		

	
	RECT tmpRect = r;
	tmpRect.right += 0;
	tmpRect.bottom += 0;
	
	InvalidateRect(GetActiveWindow(), &tmpRect, FALSE);

	return hMemDC;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Method name	: DisplayBrightness
// Arguments	: 
//	1) HDC hMemDC	-- Device context
//	2) RECT &r		-- Rectangle position
//	3) int nRedVal	-- Red color Value. If it have +ve, it's going to Dark RED. 
//						If it's -ve , it's going to Light RED
//	4) int nGreenVal-- Green color Value. If it have +ve, it's going to Dark Green . 
//						If it's -ve , it's going to Light Green 
//	5) int nBlueVal	-- Blue color Value. If it have +ve, it's going to Dark Blue. 
//						If it's -ve , it's going to Light Blue
//		These Red,Green,Blue value between -255 to 255
// Return type	: void
// Description	: Brightness have 2 types. 1) Dark 2) light.
// Formula		:  Color = Color + nColorVal; (ex) Red = Red + nRedVal; Blue = Blue + nBlueVal
// Precondition	: 1)gdiplus should be intialize 2) Image should be load
// Postcondition: None
/////////////////////////////////////////////////////////////////////////////////////////////////
void CImageProcess::DisplayBrightness(HDC hMemDC, RECT &r, int nRedVal, int nGreenVal, int nBlueVal)
{
	BITMAPINFO bi;
	BOOL bRes;
	char *buf;
	
	// Bitmap header
	bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
	bi.bmiHeader.biWidth = m_nWidth;
	bi.bmiHeader.biHeight = m_nHeight;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 32;
	bi.bmiHeader.biCompression = BI_RGB;
	bi.bmiHeader.biSizeImage = m_nWidth * 4 * m_nHeight;
	bi.bmiHeader.biClrUsed = 0;
	bi.bmiHeader.biClrImportant = 0;

	// Buffer
	buf = (char *) malloc(m_nWidth * 4 * m_nHeight);

	// Don't use getPixel and SetPixel.It's very slow.
	// Get the all scanline.
	bRes = GetDIBits(hMemDC, m_hBitmap, 0, m_nHeight, buf, &bi,
					   DIB_RGB_COLORS);	
	long nCount=0;	
	for (int i=0; i<m_nHeight; ++i)
	{
		for (int j=0; j<m_nWidth; ++j)
		{
			long lVal=0;
			memcpy(&lVal, &buf[nCount], 4);

			// Get the reverse order
			int b = GetRValue(lVal);
			int g = GetGValue(lVal);
			int r = GetBValue(lVal);
			
			// Red
			r += nRedVal;
			if (r >255)
			{
				r = 255;
			}
			if (r <0)
			{
				r = 0;
			}

			// Green
			g += nGreenVal;
			if (g>255)
			{
				g = 255;
			}
			if (g<0)
			{
				g = 0;
			}

			// Blue
			b += nBlueVal;
			if (b >255)
			{
				b = 255;
			}
			if (b<0)
			{
				b = 0;
			}
			
			// Store reverse order
			lVal = RGB(b, g, r);
			memcpy(&buf[nCount], &lVal, 4);

			// Increment with 4. RGB color take 4 bytes.The high-order byte must be zero
			// See in MSDN COLORREF
			nCount+=4;
		}
	}

	// Set again
	SetDIBits(hMemDC, m_hBitmap, 0, bRes, buf,  &bi,
					   DIB_RGB_COLORS);	
	free(buf);

	RECT tmpRect = r;
	tmpRect.right += 16;
	tmpRect.bottom += 16;	

	InvalidateRect(GetActiveWindow(), &tmpRect, FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Method name	: DisplayContrast
// Arguments	:
//	1) HDC hMemDC		-- Device context
//	2) RECT &r			-- Rectangle position
//	3) int nContrastVal -- Contrast value(Value between 0 to 200)
// Return type	: void
// Description  : It have 2 type. 1) Low contrast 2) High contrast
// Formula		: Color = ((Color-128)*nContrastVal)/100 +128;
// Precondition	: 1)gdiplus should be intialize 2) Image should be load
// Postcondition: 
/////////////////////////////////////////////////////////////////////////////////////////////////
void CImageProcess::DisplayContrast(HDC hMemDC, RECT &r, int nContrastVal)
{
	BITMAPINFO bi;
	BOOL bRes;
	char *buf;
	
	// Bitmap header
	bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
	bi.bmiHeader.biWidth = m_nWidth;
	bi.bmiHeader.biHeight = m_nHeight;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 32;
	bi.bmiHeader.biCompression = BI_RGB;
	bi.bmiHeader.biSizeImage = m_nWidth * 4 * m_nHeight;
	bi.bmiHeader.biClrUsed = 0;
	bi.bmiHeader.biClrImportant = 0;

	buf = (char *) malloc(m_nWidth * 4 * m_nHeight);
	bRes = GetDIBits(hMemDC, m_hBitmap, 0, m_nHeight, buf, &bi,
					   DIB_RGB_COLORS);	

	long nCount=0;	
	for (int i=0; i<m_nHeight; ++i)
	{
		for (int j=0; j<m_nWidth; ++j)
		{			
			long lVal=0;
			memcpy(&lVal, &buf[nCount], 4);
			// Get from buffer in reverse order
			int b = GetRValue(lVal);
			int g = GetGValue(lVal);
			int r = GetBValue(lVal);

			r = ((r-128)*nContrastVal)/100 +128;
			g = ((g-128)*nContrastVal)/100 +128;
			b = ((b-128)*nContrastVal)/100 +128;			
			
			// Red
			if (r >255)
			{
				r = 255;
			}
			if (r <0)
			{
				r = 0;
			}
			
			// Green
			if (g>255)
			{
				g = 255;
			}
			if (g<0)
			{
				g = 0;
			}

			// Blue			
			if (b >255)
			{
				b = 255;
			}
			if (b<0)
			{
				b = 0;
			}

			// Store in reverse order			
			lVal = RGB((int)b, (int)g, (int)r);
			
			memcpy(&buf[nCount], &lVal, 4);

			nCount+=4;
		}
	}

	SetDIBits(hMemDC, m_hBitmap, 0, bRes, buf,  &bi,
					   DIB_RGB_COLORS);
	free(buf);

	RECT tmpRect = r;
	tmpRect.right += 16;
	tmpRect.bottom += 16;
	
	InvalidateRect(GetActiveWindow(), &tmpRect, FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Method name	: DisplayBlackAndWhite
// Arguments	: 
//	1) HDC hMemDC	-- Device context
//	2) RECT &r		-- Rectangle poisition
// Return type	: void
// Description	: If Red, Green, Blue value is same, that picture look like black and white.
// Formula		: lVal = (R+G+B)/3; R = lVal; G=lVal; B=lVal;
// Precondition	: 1)gdiplus should be intialize
// Postcondition: None
/////////////////////////////////////////////////////////////////////////////////////////////////
void CImageProcess::DisplayBlackAndWhite(HDC hMemDC, RECT &r)
{
	BITMAPINFO bi;
	BOOL bRes;
	char *buf;
	
	// Bitmap header
	bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
	bi.bmiHeader.biWidth = m_nWidth;
	bi.bmiHeader.biHeight = m_nHeight;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 32;
	bi.bmiHeader.biCompression = BI_RGB;
	bi.bmiHeader.biSizeImage = m_nWidth * 4 * m_nHeight;
	bi.bmiHeader.biClrUsed = 0;
	bi.bmiHeader.biClrImportant = 0;

	buf = (char *) malloc(m_nWidth * 4 * m_nHeight);
	bRes = GetDIBits(hMemDC, m_hBitmap, 0, m_nHeight, buf, &bi,
					   DIB_RGB_COLORS);	
	long nCount=0;	
	for (int i=0; i<m_nHeight; ++i)
	{
		for (int j=0; j<m_nWidth; ++j)
		{
			long lVal=0;
			memcpy(&lVal, &buf[nCount], 4);
			// Get the color value from buffer
			int b = GetRValue(lVal);
			int g = GetGValue(lVal);
			int r = GetBValue(lVal);

			// get the average color value
			lVal = (r+g+b)/3;

			// assign to RGB color			
			lVal = RGB(lVal, lVal, lVal);
			memcpy(&buf[nCount], &lVal, 4);

			nCount+=4;
		}
	}

	SetDIBits(hMemDC, m_hBitmap, 0, bRes, buf,  &bi,
					   DIB_RGB_COLORS);
	
	free(buf);

	RECT tmpRect = r;
	tmpRect.right += 16;
	tmpRect.bottom += 16;
	
	InvalidateRect(GetActiveWindow(), &tmpRect, FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Method name	: DisplayInvertColor
// Arguments	:
//	1) HDC hMemDC	-- Device context
//	2) RECT &r		-- Rectangle poisition
// Return type	: void
// Formula		: Color = 255 - Color; if (Color<0) color = 0; if (Color>255) Color = 255;
// Precondition	: 1)gdiplus should be intialize
// Postcondition: None
/////////////////////////////////////////////////////////////////////////////////////////////////
void CImageProcess::DisplayInvertColor(HDC hMemDC, RECT &r)
{
	BITMAPINFO bi;
	BOOL bRes;
	char *buf;
	// Bitmap header
	bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
	bi.bmiHeader.biWidth = m_nWidth;
	bi.bmiHeader.biHeight = m_nHeight;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 32;
	bi.bmiHeader.biCompression = BI_RGB;
	bi.bmiHeader.biSizeImage = m_nWidth * 4 * m_nHeight;
	bi.bmiHeader.biClrUsed = 0;
	bi.bmiHeader.biClrImportant = 0;

	buf = (char *) malloc(m_nWidth * 4 * m_nHeight);
	bRes = GetDIBits(hMemDC, m_hBitmap, 0, m_nHeight, buf, &bi,
					   DIB_RGB_COLORS);	
	long nCount=0;	
	for (int i=0; i<m_nHeight; ++i)
	{
		for (int j=0; j<m_nWidth; ++j)
		{
			long lVal=0;
			memcpy(&lVal, &buf[nCount], 4);
			int b = 255-GetRValue(lVal);
			int g = 255-GetGValue(lVal);
			int r = 255-GetBValue(lVal);
			
			lVal = RGB(b, g, r);
			
			memcpy(&buf[nCount], &lVal, 4);

			nCount+=4;
		}
	}

	SetDIBits(hMemDC, m_hBitmap, 0, bRes, buf,  &bi,
					   DIB_RGB_COLORS);		
	free(buf);

	RECT tmpRect = r;
	tmpRect.right += 16;
	tmpRect.bottom+= 16;
	
	InvalidateRect(GetActiveWindow(), &tmpRect, FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Method name	: DisplayBlur
// Arguments	:
//	1) HDC hMemDC -- Device context
//	2) RECT &r    -- Rectangle position
// Return type	: void
// Formula		: (C1+C2+C3+C4+C5)/5 (Get the nearby pixel. add and get the average)
// Precondition	: 1)gdiplus should be intialize
// Postcondition: None
/////////////////////////////////////////////////////////////////////////////////////////////////
void CImageProcess::DisplayBlur(HDC hMemDC, RECT &r)
{
	BITMAPINFO bi;
	BOOL bRes;
	char *pOriBuf; // pointer to a original buffer
	// Bitmap header
	bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
	bi.bmiHeader.biWidth = m_nWidth;
	bi.bmiHeader.biHeight = m_nHeight;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 32;
	bi.bmiHeader.biCompression = BI_RGB;
	bi.bmiHeader.biSizeImage = m_nWidth * 4 * m_nHeight;
	bi.bmiHeader.biClrUsed = 0;
	bi.bmiHeader.biClrImportant = 0;
	
	pOriBuf = (char *) malloc(m_nWidth * 4 * m_nHeight);
	// Store new value into tempravary buffer
	char *tmpBuf = (char *) malloc(m_nWidth * 4 * m_nHeight);
	bRes = GetDIBits(hMemDC, m_hBitmap, 0, m_nHeight, pOriBuf, &bi,
					   DIB_RGB_COLORS);	
	long nCount=0;
	long c1, c2, c3, c4, c5;

	// Retrive from original buffer
	// Caluculate the value and store new value into tmpBuf
	for (int i=0; i<m_nHeight; ++i)
	{
		for (int j=0; j<m_nWidth; ++j)
		{
			long lVal=0;
			memcpy(&lVal, &pOriBuf[nCount], 4);
			int b = GetRValue(lVal);
			int g = GetGValue(lVal);
			int r = GetBValue(lVal);

			c1 = r;
			// Red
			if ((nCount < ((m_nHeight-1)*m_nWidth*4l)) && (nCount > (m_nWidth*4)))
			{
				memcpy(&lVal, &pOriBuf[nCount-(m_nWidth*4l)], 4);
				c2 = GetBValue(lVal);

				memcpy(&lVal, &pOriBuf[nCount+4], 4);
				c3 = GetBValue(lVal);

				memcpy(&lVal, &pOriBuf[(nCount+(m_nWidth*4l))], 4);
				c4 = GetBValue(lVal);

				memcpy(&lVal, &pOriBuf[nCount-4], 4);
				c5 = GetBValue(lVal);
				
				r = (c1+c2+c3+c4+c5)/5;
			}

			// Green
			c1 = g;
			if ((nCount < ((m_nHeight-1)*m_nWidth*4l)) && (nCount > (m_nWidth*4)))
			{
				memcpy(&lVal, &pOriBuf[(nCount-(m_nWidth*4l))], 4);
				c2 = GetGValue(lVal);

				memcpy(&lVal, &pOriBuf[nCount+4], 4);
				c3 = GetGValue(lVal);

				memcpy(&lVal, &pOriBuf[(nCount+(m_nWidth*4l))], 4);
				c4 = GetGValue(lVal);

				memcpy(&lVal, &pOriBuf[nCount-4], 4);
				c5 = GetGValue(lVal);

				g = (c1+c2+c3+c4+c5)/5;
			}

			// Blue
			c1 = b;
			if ((nCount < ((m_nHeight-1)*m_nWidth*4l)) && (nCount > (m_nWidth*4)))
			{
				memcpy(&lVal, &pOriBuf[(nCount-(m_nWidth*4l))], 4);
				c2 = GetRValue(lVal);

				memcpy(&lVal, &pOriBuf[nCount+4], 4);
				c3 = GetRValue(lVal);

				memcpy(&lVal, &pOriBuf[(nCount+(m_nWidth*4l))], 4);
				c4 = GetRValue(lVal);

				memcpy(&lVal, &pOriBuf[nCount-4], 4);
				c5 = GetRValue(lVal);

				b = (c1+c2+c3+c4+c5)/5;
			}

			// Store in reverse order
			lVal = RGB(b, g, r);
			
			memcpy(&tmpBuf[nCount], &lVal, 4);

			nCount+=4;
		}
	}

	// Store tmpBuf
	SetDIBits(hMemDC, m_hBitmap, 0, bRes, tmpBuf,  &bi,
					   DIB_RGB_COLORS);		
	free(pOriBuf);
	free(tmpBuf);

	RECT tmpRect = r;
	tmpRect.right += 16;
	tmpRect.bottom+= 16;
	
	InvalidateRect(GetActiveWindow(), &tmpRect, FALSE);

	
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Method name	: DisplaySharpness
// Arguments	:
//	1) HDC hMemDC -- Device context
//	2) RECT &r    -- Rectangle position
// Return type	: void
// Formula		: (C1*5) - (C2+C3+C4+C5)
// Precondition	: 1)gdiplus should be intialize
// Postcondition: None
/////////////////////////////////////////////////////////////////////////////////////////////////
void CImageProcess::DisplaySharpness(HDC hMemDC, RECT &r)
{
	BITMAPINFO bi;
	BOOL bRes;
	char *pOriBuf; // Original buffer
	// Bitmap header
	bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
	bi.bmiHeader.biWidth = m_nWidth;
	bi.bmiHeader.biHeight = m_nHeight;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 32;
	bi.bmiHeader.biCompression = BI_RGB;
	bi.bmiHeader.biSizeImage = m_nWidth * 4 * m_nHeight;
	bi.bmiHeader.biClrUsed = 0;
	bi.bmiHeader.biClrImportant = 0;
	
	pOriBuf = (char *) malloc(m_nWidth * 4 * m_nHeight);
	char *tmpBuf = (char *) malloc(m_nWidth * 4 * m_nHeight);

	bRes = GetDIBits(hMemDC, m_hBitmap, 0, m_nHeight, pOriBuf, &bi,
					   DIB_RGB_COLORS);	
	long nCount=0;
	long c1, c2, c3, c4, c5;

	// Retrive from original buffer
	// Caluculate the value and store new value into tmpBuf
	for (int i=0; i<m_nHeight; ++i)
	{
		for (int j=0; j<m_nWidth; ++j)
		{
			long lVal=0;
			memcpy(&lVal, &pOriBuf[nCount], 4);
			int b = GetRValue(lVal);
			int g = GetGValue(lVal);
			int r = GetBValue(lVal);

			c1 = r;
			// Red
			if ((nCount < ((m_nHeight-1)*m_nWidth*4l)) && (nCount > (m_nWidth*4)))
			{
				memcpy(&lVal, &pOriBuf[nCount-(m_nWidth*4l)], 4);
				c2 = GetBValue(lVal);

				memcpy(&lVal, &pOriBuf[nCount+4], 4);
				c3 = GetBValue(lVal);

				memcpy(&lVal, &pOriBuf[(nCount+(m_nWidth*4l))], 4);
				c4 = GetBValue(lVal);

				memcpy(&lVal, &pOriBuf[nCount-4], 4);
				c5 = GetBValue(lVal);
				
				r = (c1*5) - (c2+c3+c4+c5);
			}

			// Green
			c1 = g;
			if ((nCount < ((m_nHeight-1)*m_nWidth*4l)) && (nCount > (m_nWidth*4)))
			{
				memcpy(&lVal, &pOriBuf[(nCount-(m_nWidth*4l))], 4);
				c2 = GetGValue(lVal);

				memcpy(&lVal, &pOriBuf[nCount+4], 4);
				c3 = GetGValue(lVal);

				memcpy(&lVal, &pOriBuf[(nCount+(m_nWidth*4l))], 4);
				c4 = GetGValue(lVal);

				memcpy(&lVal, &pOriBuf[nCount-4], 4);
				c5 = GetGValue(lVal);

				g = (c1*5) - (c2+c3+c4+c5);
			}

			// Blue
			c1 = b;
			if ((nCount < ((m_nHeight-1)*m_nWidth*4l)) && (nCount > (m_nWidth*4)))
			{
				memcpy(&lVal, &pOriBuf[(nCount-(m_nWidth*4l))], 4);
				c2 = GetRValue(lVal);

				memcpy(&lVal, &pOriBuf[nCount+4], 4);
				c3 = GetRValue(lVal);

				memcpy(&lVal, &pOriBuf[(nCount+(m_nWidth*4l))], 4);
				c4 = GetRValue(lVal);

				memcpy(&lVal, &pOriBuf[nCount-4], 4);
				c5 = GetRValue(lVal);

				b = (c1*5) - (c2+c3+c4+c5);
			}

			// Red
			if (r >255)
			{
				r = 255;
			}
			if (r <0)
			{
				r = 0;
			}
			
			// Green
			if (g>255)
			{
				g = 255;
			}
			if (g<0)
			{
				g = 0;
			}

			// Blue			
			if (b >255)
			{
				b = 255;
			}
			if (b<0)
			{
				b = 0;
			}

			// Store in reverse order
			lVal = RGB(b, g, r);
			
			memcpy(&tmpBuf[nCount], &lVal, 4);

			nCount+=4;
		}
	}

	// Store tmpBuf
	SetDIBits(hMemDC, m_hBitmap, 0, bRes, tmpBuf,  &bi,
					   DIB_RGB_COLORS);		
	free(pOriBuf);
	free(tmpBuf);

	RECT tmpRect = r;
	tmpRect.right += 16;
	tmpRect.bottom+= 16;
	
	InvalidateRect(GetActiveWindow(), &tmpRect, FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Method name	: ~CImageProcess
// Arguments	: Destructor
// Return type	: None
// Precondition	: gdiplus should be intialize
// Postcondition: None
/////////////////////////////////////////////////////////////////////////////////////////////////
CImageProcess::~CImageProcess()
{
	Gdiplus::GdiplusShutdown(m_gdiplusToken);
}