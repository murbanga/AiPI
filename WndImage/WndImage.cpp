// =======================================================
// 
//                    CWndImage.cpp
//             WndImage class implementation
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

#include "stdafx.h"
#include "WndImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// ==================================================================
//  CTor / DTor
// ------------------------------------------------------------------

CWndImage::CWndImage()
{
  m_shared = false;
  m_bmpSize = CSize(0,0);
  m_bltMode = bltNormal;
  m_alignX = bltLeft;
  m_alignY = bltTop;
  m_srcRect.SetRectEmpty();
  m_dstRect.SetRectEmpty();

  m_zoomX   = 1.0;
  m_zoomY   = 1.0;
  m_origin.x = 0;
  m_origin.y = 0;

  m_backBrush = (HBRUSH) (COLOR_3DFACE+1);
}


CWndImage::~CWndImage()
{
  SetImg((HBITMAP) 0);
}


BEGIN_MESSAGE_MAP(CWndImage, CWnd)
	//{{AFX_MSG_MAP(CWndImage)
	ON_WM_PAINT()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// ==================================================================
//  OnPaint
// ------------------------------------------------------------------

void CWndImage::OnPaint() 
{
  DWORD style = GetStyle();
  if (!(style & WS_VISIBLE)) return;

  CPaintDC dc(this); 
  CRect r;
  GetClientRect(&r);

  CDC memdc;
  memdc.CreateCompatibleDC( &dc );
  CBitmap * prev = memdc.SelectObject(&m_bmp);

  dc.SetStretchBltMode(HALFTONE);  // works only under NT/2000, anyway..

  CRect & src = m_srcRect;
  CRect & dst = m_dstRect;

  if (m_bltMode == bltTile) 
  {
    if (!src.IsRectEmpty()) {
      for(int x=m_origin.x; x < r.right; x+=src.Width()) {
        if (x>-r.right) {
          for(int y=m_origin.y; y<r.bottom; y+=src.right) {
            if (y>-r.bottom) {
              dc.BitBlt(x, y, src.Width(), src.Height(), &memdc, src.left, src.top, 
                        SRCCOPY);
            }
          }
        }
      }
    }
  }

  else {
    dc.StretchBlt(dst.left, dst.top, dst.Width(), dst.Height(),
                  &memdc, 
                  src.left, src.top, src.Width(), src.Height(),
                  SRCCOPY);

      // clean background
    CRect wipe;
    if (dst.left > 0) {
      wipe.SetRect(0,0, dst.left, r.bottom);
     ::FillRect(dc.m_hDC, &wipe, m_backBrush);
    }

    if (dst.top > 0) {
      wipe.SetRect(dst.left, 0, dst.right, dst.top);
     ::FillRect(dc.m_hDC, &wipe, m_backBrush);
    }

    if (dst.right < r.right) {
      wipe.SetRect(dst.right, 0, r.right, r.bottom);
     ::FillRect(dc.m_hDC, &wipe, m_backBrush);
    }

    if (dst.bottom < r.bottom) {
      wipe.SetRect(dst.left, dst.bottom, dst.right, r.bottom);
     ::FillRect(dc.m_hDC, &wipe, m_backBrush);
    }
  }
  memdc.SelectObject( prev );
}


// ==================================================================
//  Create
// ------------------------------------------------------------------

BOOL CWndImage::Create(RECT const & r, CWnd * parent, UINT id, DWORD dwStyle)
{
  BOOL ok = CWnd::Create(NULL, NULL, dwStyle, r, parent, id, NULL);
  return ok;
}


// ==================================================================
//  CreateFromStatic
// ------------------------------------------------------------------

BOOL CWndImage::CreateFromStatic(CWnd * sc)
{
   // _ASSERTE(!::IsWindow(m_hWnd));          // image control already created
  if (!sc || !::IsWindow(sc->m_hWnd)) return false;
  CWnd * dlg = sc->GetParent();
  if (!dlg || !::IsWindow(dlg->m_hWnd)) return false;

  CRect r;
  sc->GetWindowRect(&r);
  dlg->ScreenToClient(&r);
  CString s;
  DWORD style   = sc->GetStyle();
  DWORD exstyle = sc->GetExStyle();
  sc->GetWindowText(s);
  UINT dlgID = sc->GetDlgCtrlID();

  HBITMAP bmp = (HBITMAP) sc->SendMessage(STM_GETIMAGE, IMAGE_BITMAP, 0);
  if (bmp)
     sc->SendMessage(STM_SETIMAGE, IMAGE_BITMAP, 0);

  sc->DestroyWindow();
  CreateEx(exstyle, NULL, s,  style, r, dlg, dlgID);

  if (bmp) {
    SetImg(bmp, false);
    SetBltMode(bltFitXY);
  }
  return true;
}


// ==================================================================
//  SetImage
// ------------------------------------------------------------------

void CWndImage::SetImg(HBITMAP bmp, bool shared)
{
  HGDIOBJ prev = m_bmp.Detach();
  if ((HBITMAP) prev == bmp) return;

  if (prev && m_shared) DeleteObject(prev);

  m_bmp.Attach(bmp);

  if (bmp != 0) {
    BITMAP bmp;
    m_bmp.GetBitmap(&bmp);
    m_bmpSize.cx = bmp.bmWidth;
    m_bmpSize.cy = bmp.bmHeight;
  }
  else 
    m_bmpSize = CSize(0,0);

  SetSourceRect();      // use entire new image
  Recalc();
  return;
}

// ==================================================================
//  SetImage Clones
// ------------------------------------------------------------------

void CWndImage::SetImg(CBitmap * bmp)
{
  SetImg(bmp ? (HBITMAP) (bmp->m_hObject) : 0);
}

bool CWndImage::SetImg(LPCTSTR resID, HINSTANCE instance)
{
  if (!instance) 
    instance = AfxGetResourceHandle();

  HBITMAP bmp = ::LoadBitmap(instance, resID);
  SetImg(bmp, false);
  return bmp != 0;
}

bool CWndImage::SetImg(UINT resID, HINSTANCE instance)
{
  return SetImg(MAKEINTRESOURCE(resID), instance);
}


bool CWndImage::SetImgFile(LPCTSTR fileName)
{
  HBITMAP bmp = (HBITMAP) ::LoadImage(NULL, fileName, IMAGE_BITMAP, 0,0, LR_LOADFROMFILE);
  SetImg(bmp);
  return bmp != 0;
}

// ==================================================================
//  SetBltMode
// ------------------------------------------------------------------

void CWndImage::SetBltMode(int mode)
{
  if (mode <=0 || mode >  blt_MaxMode) mode = bltNormal;
  if (mode == m_bltMode) return;
  m_bltMode = mode;
  Recalc();
}

// ==================================================================
//  SetAlign
// ------------------------------------------------------------------

void CWndImage::SetAlign(int alignX, int alignY)
{
  if (alignX < 0 || alignX > blt_MaxAlign || alignX == m_alignX) alignX = 0;
  if (alignY < 0 || alignY > blt_MaxAlign || alignY == m_alignY) alignY = 0;

  if (alignX == 0 && alignY == 0) return;  // no change

  if (alignX) m_alignX = alignX;
  if (alignY) m_alignY = alignY;
  Recalc();
}

// ==================================================================
//  SetSourceRect
// ------------------------------------------------------------------

void CWndImage::SetSourceRect(RECT const & r)
{
  CRect bmpRect(0,0, m_bmpSize.cx, m_bmpSize.cy);
  m_srcRect.IntersectRect(&r, &bmpRect);
  Recalc();
}

// ==================================================================
//  SetSourceRect
// ------------------------------------------------------------------

void CWndImage::SetSourceRect()
{
  m_srcRect.SetRect(0,0, m_bmpSize.cx, m_bmpSize.cy);
  Recalc();
}


// ==================================================================
//  Recalc
// ------------------------------------------------------------------

void CWndImage::Recalc(bool invalidate)
{
  if (!::IsWindow(m_hWnd)) return;

  CRect & src = m_srcRect;
  CRect & dst = m_dstRect;
  CRect r;

  GetClientRect(&r);
  CSize wndSize = r.Size();

  if (wndSize.cx == 0 || wndSize.cy == 0 || src.IsRectEmpty()) 
    dst.SetRectEmpty();
  else {

    dst.left = dst.top = 0;
    switch (m_bltMode) 
    {
      default           :
      case bltNormal    :  dst.right = src.Width(); dst.bottom = src.Height(); break;
      case bltStretch   :  dst.right = wndSize.cx; dst.bottom = wndSize.cy; break;
      case bltCustom    :  dst.right  = (int)(src.Width() * m_zoomX);
                           dst.bottom = (int)(src.Height() * m_zoomY);
                           break;

      case bltFitX      :
      case bltFitY      :
      case bltFitXY     :
      case bltFitSm     : {
                            double zoom = 1;
                            double zoomX = ((double) wndSize.cx) / src.Width();
                            double zoomY = ((double) wndSize.cy) / src.Height();

                            if (m_bltMode == bltFitX) zoom = zoomX;
                            else if (m_bltMode == bltFitY) zoom = zoomY;
                            else    // for stretchXY take smaller, for stretchSm take larger:
                              zoom = ((m_bltMode == bltFitXY) ^ (zoomX > zoomY)) ? 
                                                zoomX : zoomY;  

                            m_zoomX = m_zoomY = zoom;       // so user can query these values

                            dst.right  = (int)(src.Width() * zoom);
                            dst.bottom = (int)(src.Height() * zoom);
                            break;
                        }
      case bltTile      :   break;

    }

    switch (m_alignX) 
    {
      case bltCenter :  m_origin.x = (wndSize.cx-dst.Width()) / 2; break;
      case bltRight  :  m_origin.x =  wndSize.cx-dst.Width();      break;
      case bltLeft   :  m_origin.x =  0;      break;
    }
    dst.left += m_origin.x;
    dst.right += m_origin.x;

    switch (m_alignY) 
    {
      case bltCenter :  m_origin.y = (wndSize.cy-dst.Height()) / 2; break;
      case bltRight  :  m_origin.y =  wndSize.cy-dst.Height();      break;
      case bltTop    :  m_origin.y = 0; break;
    }
    dst.top += m_origin.y;
    dst.bottom += m_origin.y;
  }

  if (m_bltMode == bltTile) {
    dst.SetRect(0,0, wndSize.cx, wndSize.cy);
  }

  if (invalidate)
      Invalidate();

}


void CWndImage::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
    Recalc();
}

// ==================================================================
//  SetZoom, origin
// ------------------------------------------------------------------

void CWndImage::SetZoom(double zoomX, double zoomY)
{
  m_zoomX = zoomX;
  m_zoomY = zoomY;
  m_bltMode = bltCustom;
  Recalc();
}

void CWndImage::SetZoom(double zoom)
{
  SetZoom(zoom, zoom);
}

void CWndImage::SetOrigin(int origX, int origY)
{
  SetOriginX(origX);
  SetOriginY(origY);
}

void CWndImage::SetOriginX(int origX)
{
  m_origin.x = origX; 
  m_alignX = bltCustom;
  Recalc();
}

void CWndImage::SetOriginY(int origY)
{
  m_origin.y = origY;
  m_alignY = bltCustom;
  Recalc();

}

// ==================================================================
//  GetBitmap
// ------------------------------------------------------------------

HBITMAP CWndImage::GetBitmap(bool detach)
{
  HBITMAP ret = (HBITMAP) m_bmp.m_hObject;
  if (detach) {
    m_shared = true;
    SetImg((HBITMAP)0);
  }
  return ret;
}

// ==================================================================
//  SetbackBrush
// ------------------------------------------------------------------

void CWndImage::SetBackgroundBrush(int sysColorIndex)
{
  if (sysColorIndex == 0)
    m_backBrush = (HBRUSH) ::GetStockObject(HOLLOW_BRUSH);
  else
    m_backBrush = (HBRUSH) (sysColorIndex+1);
  Invalidate();
}

void CWndImage::SetBackgroundBrush(CBrush & brush)
{
  m_backBrush = (HBRUSH) brush.m_hObject;
  Invalidate();
}

void CWndImage::SetBackgroundBrush(HBRUSH brush)
{
  m_backBrush = brush;
  Invalidate();
}



