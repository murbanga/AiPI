// =======================================================
// 
//                      CWndImage.h
//              WndImage class declarations
// 
//           Copyright (C) 2000 Peter Hauptmann
//
//  Can be used and distributed freely 
//          as long as the source copyright stays intact
// 
//  updated version can be found under 
//          http://buerger.metropolis.de/bitbucket/
//
// -------------------------------------------------------
//
//  2000-05-16: Initial Revision
//



#if !defined(AFX_WNDIMAGE_H__18E060C2_DE37_4419_B87A_09ACF6963828__INCLUDED_)
#define AFX_WNDIMAGE_H__18E060C2_DE37_4419_B87A_09ACF6963828__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ==================================================================
//  CWndImage
// ------------------------------------------------------------------

class CWndImage : public CWnd
{
  public:
	virtual    ~CWndImage();
	            CWndImage();

    BOOL        Create(RECT const & r, CWnd * parent, UINT id, 
                       DWORD dwStyle = WS_CHILD | WS_VISIBLE);

	BOOL        CreateFromStatic(CWnd * st);

    void        SetBltMode(int mode);  
    void        SetAlign(int alignX, int alignY); // pass zero to keep value
    void        SetSourceRect(RECT const & r);  
    void        SetSourceRect();                        // use entire image

    void        SetZoom(double zoomX, double zoomY);        
    void        SetZoom(double zoom);                       // zoomx=zoomy

    void        SetOrigin(int origX, int origY);
    void        SetOriginX(int origX);
    void        SetOriginY(int origY);

    void        SetImg(HBITMAP bmp, bool shared = false);
    void        SetImg(CBitmap * bmp);
    bool        SetImg(LPCTSTR resID, HINSTANCE instance = 0);
    bool        SetImg(UINT resID, HINSTANCE instance = 0);
    bool        SetImgFile(LPCTSTR fileName);

    void        SetBackgroundBrush(int sysColorIndex);
    void        SetBackgroundBrush(CBrush & brush);
    void        SetBackgroundBrush(HBRUSH brush);

    int         GetImgSizeX() const      { return m_bmpSize.cx;  }
    int         GetImgSizeY() const      { return m_bmpSize.cy;  }
    int         GetBltMode()  const      { return m_bltMode;     }
    double      GetZoomX()    const      { return m_zoomX;       }
    double      GetZoomY()    const      { return m_zoomY;       }
    int         GetAlignX()   const      { return m_alignX;      }
    int         GetAlignY()   const      { return m_alignY;      }
    int         GetOriginX()  const      { return m_origin.x;    }
    int         GetOriginY()  const      { return m_origin.y;    }
    HBITMAP     GetBitmap(bool detach = false);


  protected:

    void        Recalc(bool invalidateWnd = true);


    CBitmap     m_bmp;              // the bitmap we wanna blit
    HBRUSH      m_backBrush;        // background brush
    CSize       m_bmpSize;          // size of the bitmap
    bool        m_shared;           // the bitmap is shared (don't delete upon destruction/replacement)

    // paint style:
    int         m_bltMode;          // blit mode
    int         m_alignX;           // y alignment
    int         m_alignY;           // y alignment

    CRect       m_srcRect;          // source 'window' rect (as selected by user)

    // custom parameters
    double      m_zoomX;            // custom X zoom factor
    double      m_zoomY;            // custom Y zoom factor
    CPoint      m_origin;           // custom origin (in WndImage coordinates, may be  <0


        // internal vars - for "quick" recalc & change
    CRect       m_dstRect;          // true destination rect
    

  public:
    enum __bltmodes 
    {
      bltCustom     =       1,      // custom source, zoom
      bltNormal     =       2,      // left upper corner
      bltStretch    =       3,      // blit stretched to fit entire frame
      bltFitX       =       4,      // stretch to fit X coordinate
      bltFitY       =       5,      // stretch to fit Y cooddinate
      bltFitXY      =       6,      // stretch to fit, but keep aspect ratio
      bltFitSm      =       7,      // stretch to fit smaller (larger clipped, keeps a/r)    
      bltTile       =       8,      // blit tiled (origin included)
      blt_MaxMode   =       8,      // blit tiled (origin included)

      bltNoModify   =       0,      // pass a 0 param to not modify current setting
//      bltCustom     =       1,      // custom alignment
      bltLeft       =       2,      // align to left/top
      bltTop        =       2,      
      bltCenter     =       3,      // align to center
      bltRight      =       4,      // align to right / bottom
      bltBottom     =       4,
      blt_MaxAlign  =       4,
    };

	//{{AFX_VIRTUAL(CWndImage)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CWndImage)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WNDIMAGE_H__18E060C2_DE37_4419_B87A_09ACF6963828__INCLUDED_)
