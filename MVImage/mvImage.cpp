/*----------------------------------------------------------------------+
	mvImage class - image management class 
	uses GDI+ library
	created: 2006.05.04	by		Vasilian Mihai
	www.vasilianm.as.ro
------------------------------------------------------------------------+*/

#include "stdafx.h"
//#include "AIPI.h"
#include "mvImage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//constructor
mvImage::mvImage()
{	
	image = NULL ;			//default image pointer is null
	angle = 0. ;			//default rotation angle is ZERO
	proportion = 100;		//default zoom proportion is 100 %
	constraintType = 1 ;	//default image constraint is best fit
	zoom_status = false;	//initial not zoomed
	//multiframe tiff image , dimensions
	pDimensionIDs = (GUID*)malloc(sizeof(GUID)*2000);//2000 frames
	frameCount = 0 ;		//number of frames inside image
	frameSelected = 0 ;		//current frame selected of multiframe image
	image_loaded = false ;	//no image default loaded in memory
	b_decompressed = false ;//default none in temp dir.
	b_computeImage = false ;//default none compute func. in process;
	b_HSBarVisible = false ;//default none bar is visible
	b_VSBarVisible = false ;//default none bar is visible
}


//destructor
mvImage::~mvImage()
{
   
}


//load image from file
bool mvImage::mvLoadImage(const CString &path)
{	
	//frees previous loaded file, blocked by image pointer :)
	if(image) {
		delete image ;
		image = NULL ;
		image = (Image*) malloc(sizeof(Image)) ;
		
	}
	//delete temp if any ...
	if(b_decompressed == true)	
	{
		mvClearTempFiles() ;
	}
	
	//load desired one ...
	try
	{
		WCHAR *filename=path.AllocSysString();
		image=Image::FromFile(filename);  
	}
	catch(...)
	{
		image_loaded=false;
		
		LANGID dwLanguageID = GetSystemLanguagePrimaryID();
		switch(dwLanguageID)
		{
		case LANG_SPANISH:
			AfxMessageBox(_T("Image load failed !"));
			break;
		default:
			AfxMessageBox(_T("fallo en el proceso de cargar la imagen!"));
			break;
		}
	}


		if(image)
		{		    
		    /*
			UINT count = 0;
		    count = image->GetFrameDimensionsCount();		    
		    image->GetFrameDimensionsList(pDimensionIDs, count);
					   
		    WCHAR strGuid[39];
		    StringFromGUID2(pDimensionIDs[0], strGuid, 39);

		    // Get the number of frames in the first dimension.
		    frameCount = image->GetFrameCount(&pDimensionIDs[0]);
			frameSelected = 0;						
			
			if(frameCount > 1)//tiff multi-page
			{											
				imagePath = path ;
				mvFrameFirst() ;	
				mvStretch_TIF() ;				
				b_decompressed = true ;				
			}else			 //usual image
			{																		
				imagePath = path ;
				mvStretch_TIF() ;												
				b_decompressed  = false ;
			};//else frameCount == 0
			
			
			imagePath = path ;
			mvStretch_TIF() ;												
			b_decompressed  = false ;
		
		  */
			image_loaded=true;	
			//default values				
			angle = 0. ;			//default rotation angle is ZERO
			proportion = 100;		//default zoom proportion is 100 %
			constraintType = 1 ;	//default image constraint is best fit
			zoom_status = false;	//initial not zoomed
			Ox = Oy = 0 ;			//initial scroll bars offset	
		}//end if image

	//return state of image
		
	return image_loaded;
}




//show image in window
bool mvImage::mvShowImage()
{
	
	Graphics g(this->m_hwnd) ;
	if(angle != 0.)	g.RotateTransform(angle, MatrixOrderPrepend ) ; 
	
	g.DrawImage(image, X+Ox , Y+Oy, DW, DH ) ;
	g.Flush(FlushIntentionFlush) ;

	//Repaint the window
	CRect rect ;
	GetClientRect(this->m_hwnd, &rect) ;
	//UpdateWindow(m_hwnd);
	InvalidateRect(m_hwnd, rect, true);
	
		
	return true ;
}

//show image in window and eliminates background
bool mvImage::mvShowImageBackground(bool eraseBackground)
{
	
	Graphics g(this->m_hwnd) ;
	if(angle != 0.)	g.RotateTransform(angle, MatrixOrderPrepend ) ; 
	
	//temporary solution to erase the background
	if(eraseBackground)
	{
		
		Region Rgn;
		g.GetClip(&Rgn);
		SolidBrush grayBrush(Color::White);
		g.FillRegion(&grayBrush, &Rgn);
				
	}
	
	g.DrawImage(image, X+Ox , Y+Oy, DW, DH ) ;
	g.Flush(FlushIntentionFlush) ;
	//UpdateWindow(m_hwnd);

	return true ;
}


//copy constructor
mvImage::mvImage(HWND hwnd)
{
	this->m_hwnd = hwnd;	//need the window where to display image
	image = NULL ;			//default image pointer is null
	angle = 0. ;			//default rotation angle is ZERO
	proportion = 100;		//default zoom proportion is 100 %
	constraintType = 1 ;	//default image constraint is best fit
	zoom_status = false;	//initial the image is displayed not zoomed
	//multiframe tiff image , dimensions
	pDimensionIDs = (GUID*)malloc(sizeof(GUID)*2000);//2000 frames
	image_loaded = false ;	//no image default loaded in memory
	b_decompressed = false ;//default none in temp dir.
	b_computeImage = false ;//default none compute func. in process;	   
	b_HSBarVisible = false ;//default none bar is visible
	b_VSBarVisible = false ;//default none bar is visible
}





//calculates the image coordinates and display it
bool mvImage::mvConstraintAll()
{
	//put constraintType flag indicate CONSTRAINT ALL
	constraintType = 1 ;
	//indicate func. computing image
	b_computeImage = true ;
	//frees the scrollbars
	ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
	ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
	
	if(b_HSBarVisible == true) b_HSBarVisible = false ;
	if(b_VSBarVisible == true) b_VSBarVisible = false ;

	//do the job
	CRect rect ;
	GetClientRect(this->m_hwnd, &rect) ;
	mvGetImageDimensions(&pictureW, &pictureH) ;


	if(angle == 0.)
	{
	//------------------------------------------------------------------+
		//angle ZERO
		DH=rect.Height() ;
		DW=(DH*pictureW)/pictureH ;				
		if(DW>rect.Width())
		{
			DW=rect.Width();
			DH=(DW*pictureH)/pictureW;
		};

		
		X=(rect.Width()  - DW ) / 2;  
		Y=(rect.Height() - DH ) / 2;  

		//scrolls bars offset
		Ox = 0 ;  Oy = 0 ;
		//don't need to put scroll bars in window

	//------------------------------------------------------------------+
	}else if(angle == 90.)
	{	
	//------------------------------------------------------------------+
		//angle 90
		DW=rect.Height();			
		DH=(DW*pictureH)/pictureW;		
		if(DH>rect.Width())
		{
			DH=rect.Width() ;
			DW=(DH*pictureW)/pictureH ;	
		};
		X = (rect.Height() - DW) / 2 ;
		Y = -1*DH -1*(rect.Width() - DH)/2 ;

		//scrolls bars offset
		Ox = 0 ;  Oy = 0 ;
		//don't need to put scroll bars in window

	//------------------------------------------------------------------+
	}else if(angle == 180.)
	{
	//------------------------------------------------------------------+
		//angle 180
		DH=rect.Height() ;				//height of image
		DW=(DH*pictureW)/pictureH ;		//width of image
		if(DW>rect.Width())
		{
			DW=rect.Width();
			DH=(DW*pictureH)/pictureW;
		}
		X = -1*DW - (rect.Width() - DW) / 2 ;
		Y = -1*DH - (rect.Height() - DH) /2 ;

		//scrolls bars offset
		Ox = 0 ;  Oy = 0 ;
		//don't need to put scroll bars in window

	//------------------------------------------------------------------+
	}else if(angle == 270.)
	{
	//------------------------------------------------------------------+
		//angle 270
		DW=rect.Height();			
		DH=(DW*pictureH)/pictureW;	
		
		if(DH>rect.Width())
		{
			DH=rect.Width() ;
			DW=(DH*pictureW)/pictureH ;	
		};
		X = -1*DW - (rect.Height() - DW) /2 ;
		Y = (rect.Width() - DH) / 2 ;

		//scrolls bars offset
		Ox = 0 ;  Oy = 0 ;
		//don't need to put scroll bars in window

	//------------------------------------------------------------------+
	}else{
	//------------------------------------------------------------------+
		//angle ZERO
		DH=rect.Height() ;
		DW=(DH*pictureW)/pictureH ;				
		if(DW>rect.Width())
		{
			DW=rect.Width();
			DH=(DW*pictureH)/pictureW;
		};
		X = (rect.Width() - DW) / 2 ;
		Y = (rect.Height() - DH) / 2;
		//scrolls bars offset
		Ox = 0 ;  Oy = 0 ;
		//don't need to put scroll bars in window
	//------------------------------------------------------------------+
	};//end else
	//------------------------------------------------------------------+
	//terminate the process almost
	b_computeImage = false ;

	//section II
	proportion =  DH * 100. / pictureH  ;
	//if image was zoomed restore the flag
	zoom_status = false ;
	//erase background, show image
	mvShowImageBackground(true);
	//finish mvConstraintAll()
	//------------------------------------------------------------------+
	return true ;
}




//calculates the image coordinates and display it
//in a window ;
//no constraint means display image with original width & height
bool mvImage::mvConstraintNothing()
{
	//put constraintType flag indicate NO CONSTRAINT
	constraintType = 0 ;
	//indicate process is computing an image
	b_computeImage = true ;

	//do the job
constraint_nothing :
	;
	CRect rect ;
	GetClientRect(this->m_hwnd, &rect) ;
	mvGetImageDimensions(&pictureW, &pictureH) ;

	if(angle == 0.)
	{
	//------------------------------------------------------------------+
	//angle zero
		X=0; 
		Y=0;
		DW = pictureW ;
		DH = pictureH ;
		
		//calculate scroll bars position & set info
		int scrollV = 0, scrollH = 0 ;
		//test if image dimensions are great than window's dimensions
		//HORIZONTAL
		if(DW > rect.Width())
		{//scroll offset							
			if(Ox < (rect.Width() - DW -1 - X)) Ox = rect.Width()- DW -1-X ;
			if(Ox > abs(X)) Ox = abs(X) ;
			
			//horizontal scroll bar position
			scrollH = abs(Ox) ;

			m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
			m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
			m_HSInfo.nMin = 0 ;
			m_HSInfo.nMax = DW ;
			m_HSInfo.nPage = rect.Width() ; 
			m_HSInfo.nPos = scrollH ;
			SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
			SetScrollRange(this->m_hwnd, SB_HORZ,0, DW, TRUE);
			SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
			if(b_HSBarVisible == false)
			{
				b_HSBarVisible = true ;
				goto constraint_nothing ;
			};//horz scroll bar
		}else{//if no -no scroll bar is needed
			Ox = 0 ;
			ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
			if(b_HSBarVisible == true)
			{
				b_HSBarVisible = false ;
				goto constraint_nothing ;
			}
		};//else, image less than window

		//VERTICAL
		if(DH > rect.Height())
		{//scroll offset				
			if(Oy < (rect.Height() - DH -1 - Y))  Oy = rect.Height()- DH -1-Y ;
			if(Oy > abs(Y)) Oy = abs(Y) ;
			
			//vertical scroll bar position
			scrollV = abs(Oy) ;

			m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
			m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
			m_VSInfo.nMin = 0 ;
			m_VSInfo.nMax = DH ;	
			m_VSInfo.nPage = rect.Height() ; 		
			m_VSInfo.nPos = scrollV ;
			SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
			SetScrollRange(this->m_hwnd, SB_VERT, 0, DH, TRUE);
			SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
			if(b_VSBarVisible == false)
			{
				b_VSBarVisible = true ;
				goto constraint_nothing ;
			}
		}else{
			Oy = 0 ;
			ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
			if(b_VSBarVisible == true)
			{
				b_VSBarVisible = false ;
				goto constraint_nothing ;
			}
		}
	//------------------------------------------------------------------+
	}else if(angle == 90.)
	{
	//------------------------------------------------------------------+
	//angle 90
		X = 0 ;
		Y = -1*pictureH ;
		DW = pictureW ;
		DH = pictureH ;

		//calculate scroll bars position & set info V-vertical , H-horizontal
		int scrollV = 0, scrollH = 0 ;
		//test if image dimensions are great than window's dimensions
		//VERTICAL
		if(DW > rect.Height())
		{//scroll offset							
			if(Ox < (rect.Height() - DW -1-X)) Ox = rect.Height()- DW -1-X ;
			if(Ox > abs(X)) Ox = abs(X) ;
			
			//vertical scroll bar position
			scrollV = abs(Ox) ;

			m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
			m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
			m_VSInfo.nMin = 0 ;
			m_VSInfo.nMax = DW ;	
			m_VSInfo.nPage = rect.Height() ; 		
			m_VSInfo.nPos = scrollV ;
			SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
			SetScrollRange(this->m_hwnd, SB_VERT, 0, DW, TRUE);
			SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
			if(b_VSBarVisible == false)
			{
				b_VSBarVisible = true ;
				goto constraint_nothing ;
			}
		}else{//if no -no scroll bar is needed
			Ox = 0 ;
			ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
			if(b_VSBarVisible == true)
			{
				b_VSBarVisible = false ;
				goto constraint_nothing ;
			}
		};//else, image less than window

		//HORIZONTAL
		if(DH > rect.Width())
		{//scroll offset				
			if(Oy < (rect.Width() - DH +1 ))  Oy = rect.Width()- DH +1 ;
			if(Oy < 0) Oy = 0 ;
			
			//horizontal scroll bar position
			scrollH = abs(Oy) ;

			m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
			m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
			m_HSInfo.nMin = 0 ;
			m_HSInfo.nMax = DH ;
			m_HSInfo.nPage = rect.Width() ; 
			m_HSInfo.nPos = scrollH ;
			SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
			SetScrollRange(this->m_hwnd, SB_HORZ,0, DH, TRUE);
			SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
			if(b_HSBarVisible == false)
			{
				b_HSBarVisible = true ;
				goto constraint_nothing ;
			};//horz scroll bar
		}else{
			Oy = 0 ;
			ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
			if(b_HSBarVisible == true)
			{
				b_HSBarVisible = false ;
				goto constraint_nothing ;
			}
		}

	//------------------------------------------------------------------+
	}else if(angle == 180.)
	{
	//------------------------------------------------------------------+	
	//angle 180
		X = -1*pictureW  ;
		Y = -1*pictureH  ;
		DW = pictureW ;
		DH = pictureH ;

		//calculate scroll bars position & set info
		int scrollV = 0, scrollH = 0 ;
		//test if image dimensions are great than window's dimensions
		//HORIZONTAL
		if(DW > rect.Width())
		{//scroll offset							
			if(Ox < (rect.Width() - DW +1 )) Ox = rect.Width()- DW +1 ;
			if(Ox < 0 ) Ox = 0  ;
			
			//horizontal scroll bar position
			scrollH = abs(Ox) ;

			m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
			m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
			m_HSInfo.nMin = 0 ;
			m_HSInfo.nMax = DW ;
			m_HSInfo.nPage = rect.Width() ; 
			m_HSInfo.nPos = scrollH ;
			SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
			SetScrollRange(this->m_hwnd, SB_HORZ,0, DW, TRUE);
			SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
			if(b_HSBarVisible == false)
			{
				b_HSBarVisible = true ;
				goto constraint_nothing ;
			};//horz scroll bar
		}else{//if no -no scroll bar is needed
			Ox = 0 ;
			ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
			if(b_HSBarVisible == true)
			{
				b_HSBarVisible = false ;
				goto constraint_nothing ;
			}
		};//else, image less than window

		//VERTICAL
		if(DH > rect.Height())
		{//scroll offset				
			if(Oy < (rect.Height() - DH +1 ))  Oy = rect.Height()- DH +1 ;
			if(Oy < 0) Oy = 0 ;
			
			//vertical scroll bar position
			scrollV = abs(Oy) ;

			m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
			m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
			m_VSInfo.nMin = 0 ;
			m_VSInfo.nMax = DH ;	
			m_VSInfo.nPage = rect.Height() ; 		
			m_VSInfo.nPos = scrollV ;
			SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
			SetScrollRange(this->m_hwnd, SB_VERT, 0, DH, TRUE);
			SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
			if(b_VSBarVisible == false)
			{
				b_VSBarVisible = true ;
				goto constraint_nothing ;
			}
		}else{
			Oy = 0 ;
			ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
			if(b_VSBarVisible == true)
			{
				b_VSBarVisible = false ;
				goto constraint_nothing ;
			}
		}
	//------------------------------------------------------------------+
	}else if(angle == 270.)
	{
	//------------------------------------------------------------------+		
	//angle 270
		X = -1*pictureW ;
		Y = 0 ;
		DW = pictureW ;
		DH = pictureH ;

		//calculate scroll bars position & set info V-vertical , H-horizontal
		int scrollV = 0, scrollH = 0 ;
		//test if image dimensions are great than window's dimensions
		//VERTICAL
		if(DW > rect.Height())
		{//scroll offset							
			if(Ox < (rect.Height() - DW +1 )) Ox = rect.Height()- DW +1 ;
			if(Ox < 0) Ox = 0 ;
			
			//vertical scroll bar position
			scrollV = abs(Ox) ;

			m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
			m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
			m_VSInfo.nMin = 0 ;
			m_VSInfo.nMax = DW ;	
			m_VSInfo.nPage = rect.Height() ; 		
			m_VSInfo.nPos = scrollV ;
			SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
			SetScrollRange(this->m_hwnd, SB_VERT, 0, DW, TRUE);
			SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
			if(b_VSBarVisible == false)
			{
				b_VSBarVisible = true ;
				goto constraint_nothing ;
			};//horz scroll bar
		}else{//if no -no scroll bar is needed
			Ox = 0 ;
			ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
			if(b_VSBarVisible == true)
			{
				b_VSBarVisible = false ;
				goto constraint_nothing ;
			}
		};//else, image less than window

		//HORIZONTAL
		if(DH > rect.Width())
		{//scroll offset				
			if(Oy < (rect.Width() - DH -1-Y ))  Oy = rect.Width()- DH -1-Y ;
			if(Oy > abs(Y)) Oy = abs(Y) ;
			
			//horizontal scroll bar position
			scrollH = abs(Oy) ;

			m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
			m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
			m_HSInfo.nMin = 0 ;
			m_HSInfo.nMax = DH ;
			m_HSInfo.nPage = rect.Width() ; 
			m_HSInfo.nPos = scrollH ;
			SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
			SetScrollRange(this->m_hwnd, SB_HORZ,0, DH, TRUE);
			SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
			if(b_HSBarVisible == false)
			{
				b_HSBarVisible = true ;
				goto constraint_nothing ;
			};//horz scroll bar
		}else{
			Oy = 0 ;
			ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
			if(b_HSBarVisible == true)
			{
				b_HSBarVisible = false ;
				goto constraint_nothing ;
			}
		}
	//------------------------------------------------------------------+
	}else
	{
	//------------------------------------------------------------------+
	//angle zero default
		X = 0 ;
		Y = 0 ;
		DW = pictureW ;
		DH = pictureH ;

		//calculate scroll bars position & set info
		int scrollV = 0, scrollH = 0 ;
		//test if image dimensions are great than window's dimensions
		//HORIZONTAL
		if(DW > rect.Width())
		{//scroll offset							
			if(Ox < (rect.Width() - DW -1 - X)) Ox = rect.Width()- DW -1-X ;
			if(Ox > abs(X)) Ox = abs(X) ;
			
			//horizontal scroll bar position
			scrollH = abs(Ox) ;

			m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
			m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
			m_HSInfo.nMin = 0 ;
			m_HSInfo.nMax = DW ;
			m_HSInfo.nPage = rect.Width() ; 
			m_HSInfo.nPos = scrollH ;
			SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
			SetScrollRange(this->m_hwnd, SB_HORZ,0, DW, TRUE);
			SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
			if(b_HSBarVisible == false)
			{
				b_HSBarVisible = true ;
				goto constraint_nothing ;
			};//horz scroll bar
		}else{//if no -no scroll bar is needed
			Ox = 0 ;
			ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
			if(b_HSBarVisible == true)
			{
				b_HSBarVisible = false ;
				goto constraint_nothing ;
			}
		};//else, image less than window

		//VERTICAL
		if(DH > rect.Height())
		{//scroll offset				
			if(Oy < (rect.Height() - DH -1 - Y))  Oy = rect.Height()- DH -1-Y ;
			if(Oy > abs(Y)) Oy = abs(Y) ;
			
			//vertical scroll bar position
			scrollV = abs(Oy) ;

			m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
			m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
			m_VSInfo.nMin = 0 ;
			m_VSInfo.nMax = DH ;	
			m_VSInfo.nPage = rect.Height() ; 		
			m_VSInfo.nPos = scrollV ;
			SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
			SetScrollRange(this->m_hwnd, SB_VERT, 0, DH, TRUE);
			SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
			if(b_VSBarVisible == false)
			{
				b_VSBarVisible = true ;
				goto constraint_nothing ;
			}
		}else{
			Oy = 0 ;
			ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
			if(b_VSBarVisible == true)
			{
				b_VSBarVisible = false ;
				goto constraint_nothing ;
			}
		}
	//------------------------------------------------------------------+
	}
	//------------------------------------------------------------------+
	//computing the image almost done
	b_computeImage = false ;

	//section II
	//the actual proportion parameter
	proportion =  DH * 100. / pictureH  ;
	//if image was zoomed restore the flag
	zoom_status = false ;

	//display the image, erase the background
	mvShowImageBackground(true);
	//finish mvConstraintNothing()
	//------------------------------------------------------------------+

	return true ;
}





//calculates the image coordinates and display it
//constraint height means display image with height property 
//equal with window height
bool mvImage::mvConstraintHeight()
{
	//put constraintType flag indicate CONSTRAINT HEIGHT
	constraintType = 2 ;
	//set the flag indicate computing an image
	b_computeImage = true ;


	//do the job
constraint_height:
	;
	CRect rect ;
	GetClientRect(this->m_hwnd, &rect) ;
	mvGetImageDimensions(&pictureW, &pictureH) ;
	if(angle == 0.)
	{
	//--------------------------------------------------------------+
	//rotated ZERO
		DH=rect.Height() ;
		DW=(DH*pictureW)/pictureH ;				
		X=(rect.Width()  - DW) / 2;  
		Y=(rect.Height() - DH) / 2;  

		//calculate scroll bars position & set info
		int scrollV = 0, scrollH = 0 ;
		//test if image dimensions are great than window's dimensions
		//HORIZONTAL
		if(DW > rect.Width())
		{//scroll offset							
			if(Ox < (rect.Width() - DW -1 - X)) Ox = rect.Width()- DW -1-X ;
			if(Ox > abs(X)) Ox = abs(X) ;
			
			//horizontal scroll bar position
			scrollH = abs(X + Ox) ;

			m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
			m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
			m_HSInfo.nMin = 0 ;
			m_HSInfo.nMax = DW ;
			m_HSInfo.nPage = rect.Width() ; 
			m_HSInfo.nPos = scrollH ;
			SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
			SetScrollRange(this->m_hwnd, SB_HORZ,0, DW, TRUE);
			SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
			if(b_HSBarVisible == false)
			{
				b_HSBarVisible = true ;
				goto constraint_height ;
			}

		}else{//if no -no scroll bar is needed
			Ox = 0 ;
			ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
			if(b_HSBarVisible == true)
			{
				b_HSBarVisible = false ;
				goto constraint_height ;
			}
		};//else, image less than window

		//VERTICAL
		/*don't need this ...
		source code is intended just for further modifications...
		if(DH > rect.Height())
		{//scroll offset				
			if(Oy < (rect.Height() - DH -1 - Y))  Oy = rect.Height()- DH -1-Y ;
			if(Oy > abs(Y)) Oy = abs(Y) ;
			(Oy < 0) ? scrollV=(-1)*Oy : scrollV=0 ;

			m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
			m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
			m_VSInfo.nMin = 0 ;
			m_VSInfo.nMax = DH ;	
			m_VSInfo.nPage = rect.Height() ; 		
			m_VSInfo.nPos = scrollV ;
			SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
			SetScrollRange(this->m_hwnd, SB_VERT, 0, DH, TRUE);
			SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
		}else{
		*/
			Oy = 0 ;
			ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
			if(b_VSBarVisible == true)
			{
				b_VSBarVisible = false ;
				goto constraint_height ;
			}
		/*}
		*/
	//--------------------------------------------------------------+
	}else if(angle == 90)
	{
	//--------------------------------------------------------------+
	//rotated 90
		DW=rect.Height();			
		DH=(DW*pictureH)/pictureW;	
		X = (rect.Height() - DW) / 2 ;
		Y = -1*DH -1*(rect.Width() - DH)/2 ;
		
		//calculate scroll bars position & set info V-vertical , H-horizontal
		int scrollV = 0, scrollH = 0 ;
		//test if image dimensions are great than window's dimensions
		//VERTICAL
		/*don't need this ...
		source code is intended just for further modifications...
		if(DW > rect.Height())
		{//scroll offset							
			if(Ox < (rect.Height() - DW -1-X)) Ox = rect.Height()- DW -1-X ;
			if(Ox > abs(X)) Ox = abs(X) ;
			
			(Ox < 0) ? scrollV =(-1)*Ox : (scrollV=0) ;

			m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
			m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
			m_VSInfo.nMin = 0 ;
			m_VSInfo.nMax = DW ;	
			m_VSInfo.nPage = rect.Height() ; 		
			m_VSInfo.nPos = scrollV ;
			SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
			SetScrollRange(this->m_hwnd, SB_VERT, 0, DW, TRUE);
			SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
		}else{//if no -no scroll bar is needed
		*/
			Ox = 0 ;
			ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
			if(b_VSBarVisible == true)
			{
				b_VSBarVisible = false ;
				goto constraint_height ;
			}
		/*};//else, image less than window
		*/

		//HORIZONTAL
		if(DH > rect.Width())
		{//scroll offset				
			if(Oy < (rect.Width() -1 + Y))  Oy = rect.Width() -1 + Y ;
			if(Oy < -1*DH - abs(Y)) Oy = -1*DH - abs(Y) ;
			
			//horizontal scroll bar position
			scrollH = abs(Oy + DH + Y) ;

			m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
			m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
			m_HSInfo.nMin = 0 ;
			m_HSInfo.nMax = DH ;
			m_HSInfo.nPage = rect.Width() ; 
			m_HSInfo.nPos = scrollH ;
			SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
			SetScrollRange(this->m_hwnd, SB_HORZ,0, DH, TRUE);
			SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
			if(b_HSBarVisible == false)
			{
				b_HSBarVisible = true ;
				goto constraint_height ;
			}
		}else{
			Oy = 0 ;
			ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
			if(b_HSBarVisible == true)
			{
				b_HSBarVisible = false ;
				goto constraint_height ;
			}		
		}
		//--------------------------------------------------------------+
	}else if(angle == 180)
	{
	//--------------------------------------------------------------+
	//rotated 180
		DH=rect.Height() ;				//height of image
		DW=(DH*pictureW)/pictureH ;		//width of image
		X = -1*DW - (rect.Width() - DW) / 2 ;
		Y = -1*DH - (rect.Height() - DH) /2 ;

		//calculate scroll bars position & set info
		int scrollV = 0, scrollH = 0 ;
		//test if image dimensions are great than window's dimensions
		//HORIZONTAL
		if(DW > rect.Width())
		{//scroll offset							
			if(Ox < (rect.Width() - 1 + X )) Ox = rect.Width() - 1 + X  ;
			if(Ox < -1*DW - abs(X)) Ox = -1*DW - abs(X)  ;
			
			//horizontal scroll bar position
			scrollH = abs(Ox + DW + X) ;

			m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
			m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
			m_HSInfo.nMin = 0 ;
			m_HSInfo.nMax = DW ;
			m_HSInfo.nPage = rect.Width() ; 
			m_HSInfo.nPos = scrollH ;
			SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
			SetScrollRange(this->m_hwnd, SB_HORZ,0, DW, TRUE);
			SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
			if(b_HSBarVisible == false)
			{
				b_HSBarVisible = true ;
				goto constraint_height ;
			}
		}else{//if no -no scroll bar is needed
			Ox = 0 ;
			ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
			if(b_HSBarVisible == true)
			{
				b_HSBarVisible = false ;
				goto constraint_height ;
			}
		};//else, image less than window

		//VERTICAL
		/*don't need this ...
		source code is intended just for further modifications...
		if(DH > rect.Height())
		{//scroll offset				
			if(Oy < (rect.Height() - 1 + Y ))  Oy = rect.Height()- 1 + Y;
			if(Oy < -1*DH - abs(Y) ) Oy = -1*DH - abs(Y) ;
			(Oy < 0) ? scrollV=(-1)*Oy : scrollV=0 ;

			m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
			m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
			m_VSInfo.nMin = 0 ;
			m_VSInfo.nMax = DH ;	
			m_VSInfo.nPage = rect.Height() ; 		
			m_VSInfo.nPos = scrollV ;
			SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
			SetScrollRange(this->m_hwnd, SB_VERT, 0, DH, TRUE);
			SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
		}else{
		*/
			Oy = 0 ;
			ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
			if(b_VSBarVisible == true)
			{
				b_VSBarVisible = false ;
				goto constraint_height ;
			}
		/*}
		*/
		//--------------------------------------------------------------+
	}else if(angle == 270)
	{
	//--------------------------------------------------------------+
	//rotated 270
		DW=rect.Height();			
		DH=(DW*pictureH)/pictureW;	
		X = -1*DW - (rect.Height() - DW) /2 ;
		Y = (rect.Width() - DH) / 2 ;

		//calculate scroll bars position & set info V-vertical , H-horizontal
		int scrollV = 0, scrollH = 0 ;
		//test if image dimensions are great than window's dimensions
		//VERTICAL
		/*don't need this ...
		source code is intended just for further modifications...
		if(DW > rect.Height())
		{//scroll offset							
			if(Ox < (rect.Height() - 1 + X )) Ox = rect.Height() - 1 + X  ;
			if(Ox < -1*DW - abs(X) ) Ox = -1*DW - abs(X) ;
			
			(Ox < 0) ? scrollV =(-1)*Ox : (scrollV=0) ;

			m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
			m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
			m_VSInfo.nMin = 0 ;
			m_VSInfo.nMax = DW ;	
			m_VSInfo.nPage = rect.Height() ; 		
			m_VSInfo.nPos = scrollV ;
			SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
			SetScrollRange(this->m_hwnd, SB_VERT, 0, DW, TRUE);
			SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
		}else{//if no -no scroll bar is needed
		*/
			Ox = 0 ;
			ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
			if(b_VSBarVisible == true)
			{
				b_VSBarVisible = false ;
				goto constraint_height ;
			}
		/*};//else, image less than window
		*/

		//HORIZONTAL
		if(DH > rect.Width())
		{//scroll offset				
			if(Oy < (rect.Width() - DH -1-Y ))  Oy = rect.Width()- DH -1-Y ;
			if(Oy > abs(Y)) Oy = abs(Y) ;
			
			//horizontal scroll bar position
			scrollH = abs(Oy + Y) ;

			m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
			m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
			m_HSInfo.nMin = 0 ;
			m_HSInfo.nMax = DH ;
			m_HSInfo.nPage = rect.Width() ; 
			m_HSInfo.nPos = scrollH ;
			SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
			SetScrollRange(this->m_hwnd, SB_HORZ,0, DH, TRUE);
			SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
			if(b_HSBarVisible == false)
			{
				b_HSBarVisible = true ;
				goto constraint_height ;
			}
		}else{
			Oy = 0 ;
			ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
			if(b_HSBarVisible == true)
			{
				b_HSBarVisible = false ;
				goto constraint_height ;
			}
		}
	//--------------------------------------------------------------+
	}else {
	//--------------------------------------------------------------+
	//default - rotated ZERO
		DH=rect.Height() ;				//height of image
		DW=(DH*pictureW)/pictureH ;		//width of image
		X = (rect.Width() - DW) / 2 ;
		Y = (rect.Height() - DH) / 2;

		//calculate scroll bars position & set info
		int scrollV = 0, scrollH = 0 ;
		//test if image dimensions are great than window's dimensions
		//HORIZONTAL
		if(DW > rect.Width())
		{//scroll offset							
			if(Ox < (rect.Width() - DW -1 - X)) Ox = rect.Width()- DW -1-X ;
			if(Ox > abs(X)) Ox = abs(X) ;
			
			//horizontal scroll bar position
			scrollH = abs(X + Ox) ;

			m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
			m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
			m_HSInfo.nMin = 0 ;
			m_HSInfo.nMax = DW ;
			m_HSInfo.nPage = rect.Width() ; 
			m_HSInfo.nPos = scrollH ;
			SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
			SetScrollRange(this->m_hwnd, SB_HORZ,0, DW, TRUE);
			SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
			if(b_HSBarVisible == false)
			{
				b_HSBarVisible = true ;
				goto constraint_height ;
			}
		}else{//if no -no scroll bar is needed
			Ox = 0 ;
			ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
			if(b_HSBarVisible == true)
			{
				b_HSBarVisible = false ;
				goto constraint_height ;
			}
		};//else, image less than window

		//VERTICAL
		/*don't need this ...
		source code is intended just for further modifications...
		if(DH > rect.Height())
		{//scroll offset				
			if(Oy < (rect.Height() - DH -1 - Y))  Oy = rect.Height()- DH -1-Y ;
			if(Oy > abs(Y)) Oy = abs(Y) ;
			(Oy < 0) ? scrollV=(-1)*Oy : scrollV=0 ;

			m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
			m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
			m_VSInfo.nMin = 0 ;
			m_VSInfo.nMax = DH ;	
			m_VSInfo.nPage = rect.Height() ; 		
			m_VSInfo.nPos = scrollV ;
			SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
			SetScrollRange(this->m_hwnd, SB_VERT, 0, DH, TRUE);
			SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
		}else{
		*/
			Oy = 0 ;
			ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
			if(b_VSBarVisible == true)
			{
				b_VSBarVisible = false ;
				goto constraint_height ;
			}
		/*}
		*/

	//--------------------------------------------------------------+
	};//end else
	//------------------------------------------------------------------+
	//almost done
	b_computeImage = false ;

	//section II
	//the actual proportion parameter
	proportion =  DH * 100. / pictureH  ;
	//if image was zoomed restore the flag
	zoom_status = false ;

	//erase background, show image
	mvShowImageBackground(true);
	//finish mvConstraintHeight()
	
	//------------------------------------------------------------------+

	return true ;
}



//calculates the image coordinates necesary to disply it
//in a window ; thus it does not display it but just gets
//the right values
//constraint width means display image with width property 
//equal with window width
bool mvImage::mvConstraintWidth()
{
	//put constraintType flag indicate CONSTRAINT WIDTH
	constraintType = 3 ;
	//process is computing an image
	b_computeImage = true ;

	//do the job
constraint_width :
	;
	CRect rect ;
	GetClientRect(this->m_hwnd, &rect) ;
	mvGetImageDimensions(&pictureW, &pictureH) ;
	if(angle == 0)
	{
	//---------------------------------------------------------------+
	//rotated 0
		DW = rect.Width() ;
		DH = (DW*pictureH) / pictureW ;
		X=(rect.Width()  - DW ) / 2;  
		Y=(rect.Height() - DH ) / 2;  

		//calculate scroll bars position & set info
		int scrollV = 0, scrollH = 0 ;
		//test if image dimensions are great than window's dimensions
		//HORIZONTAL
		/*don't nedd this ...
		if(DW > rect.Width())
		{//scroll offset							
			if(Ox < (rect.Width() - DW -1 - X)) Ox = rect.Width()- DW -1-X ;
			if(Ox > abs(X)) Ox = abs(X) ;
			
			(Ox < 0) ? scrollH=(-1)*Ox : (scrollH=0) ;

			m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
			m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
			m_HSInfo.nMin = 0 ;
			m_HSInfo.nMax = DW ;
			m_HSInfo.nPage = rect.Width() ; 
			m_HSInfo.nPos = scrollH ;
			SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
			SetScrollRange(this->m_hwnd, SB_HORZ,0, DW, TRUE);
			SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
		}else{//if no -no scroll bar is needed
		*/
			Ox = 0 ;
			ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
			if(b_HSBarVisible == true)
			{
				b_HSBarVisible = false ;
				goto constraint_width ;
			}

		/*};//else, image less than window
		*/

		//VERTICAL
		if(DH > rect.Height())
		{//scroll offset				
			if(Oy < (rect.Height() - DH -1 - Y))  Oy = rect.Height()- DH -1-Y ;
			if(Oy > abs(Y)) Oy = abs(Y) ;

			//vertical scroll bar position
			scrollV = abs(Y + Oy) ;	

			m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
			m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
			m_VSInfo.nMin = 0 ;
			m_VSInfo.nMax = DH ;	
			m_VSInfo.nPage = rect.Height() ; 		
			m_VSInfo.nPos = scrollV ;
			SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
			SetScrollRange(this->m_hwnd, SB_VERT, 0, DH, TRUE);
			SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
			if(b_VSBarVisible == false)
			{
				b_VSBarVisible = true ;
				goto constraint_width ;
			}
		}else{
			Oy = 0 ;
			ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
			if(b_VSBarVisible == true)
			{
				b_VSBarVisible = false ;
				goto constraint_width ;
			}
		}
	//---------------------------------------------------------------+
	}else if(angle == 90)
	{
	//---------------------------------------------------------------+
	//rotated 90
		DH = rect.Width() ;
		DW = (DH*pictureW) / pictureH ;
		X = (rect.Height() - DW) / 2 ;
		Y = -1*DH -1*(rect.Width() - DH)/2 ;

		//calculate scroll bars position & set info V-vertical , H-horizontal
		int scrollV = 0, scrollH = 0 ;
		//test if image dimensions are great than window's dimensions
		//VERTICAL
		if(DW > rect.Height())
		{//scroll offset							
			if(Ox < (rect.Height() - DW -1-X)) Ox = rect.Height()- DW -1-X ;
			if(Ox > abs(X)) Ox = abs(X) ;
			
			//horizontal scroll bar position
			scrollH = abs(Oy + DH + Y) ;

			m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
			m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
			m_VSInfo.nMin = 0 ;
			m_VSInfo.nMax = DW ;	
			m_VSInfo.nPage = rect.Height() ; 		
			m_VSInfo.nPos = scrollV ;
			SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
			SetScrollRange(this->m_hwnd, SB_VERT, 0, DW, TRUE);
			SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
			if(b_VSBarVisible == false)
			{
				b_VSBarVisible = true ;
				goto constraint_width ;
			}
		}else{//if no -no scroll bar is needed
			Ox = 0 ;
			ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
			if(b_VSBarVisible == true)
			{
				b_VSBarVisible = false ;
				goto constraint_width ;
			}
		};//else, image less than window

		//HORIZONTAL
		/*don't need this ...
		source code is intended just for further modifications...
		if(DH > rect.Width())
		{//scroll offset				
			if(Oy < (rect.Width() -1 + Y))  Oy = rect.Width() -1 + Y ;
			if(Oy < -1*DH - abs(Y)) Oy = -1*DH - abs(Y) ;
			
			//vertical scroll bar position
			scrollV = abs(X + Ox) ;

			m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
			m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
			m_HSInfo.nMin = 0 ;
			m_HSInfo.nMax = DH ;
			m_HSInfo.nPage = rect.Width() ; 
			m_HSInfo.nPos = scrollH ;
			SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
			SetScrollRange(this->m_hwnd, SB_HORZ,0, DH, TRUE);
			SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
		}else{
		*/
			Oy = 0 ;
			ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
			if(b_HSBarVisible == true)
			{
				b_HSBarVisible = false ;
				goto constraint_width ;
			}
		/*}
		*/
	//---------------------------------------------------------------+
	}else if(angle == 180)
	{
	//---------------------------------------------------------------+
	//rotated 180
		DW=rect.Width();
		DH=(DW*pictureH)/pictureW;
		X = -1*DW - (rect.Width() - DW) / 2 ;
		Y = -1*DH - (rect.Height() - DH) /2 ;
		
		//calculate scroll bars position & set info
		int scrollV = 0, scrollH = 0 ;
		//test if image dimensions are great than window's dimensions
		//HORIZONTAL
		/*don't need this ...
		source code is intended just for further modifications...
		if(DW > rect.Width())
		{//scroll offset							
			if(Ox < (rect.Width() - 1 + X )) Ox = rect.Width() - 1 + X  ;
			if(Ox < -1*DW - abs(X)) Ox = -1*DW - abs(X)  ;
			
			(Ox < 0) ? scrollH=(-1)*Ox : (scrollH=0) ;

			m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
			m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
			m_HSInfo.nMin = 0 ;
			m_HSInfo.nMax = DW ;
			m_HSInfo.nPage = rect.Width() ; 
			m_HSInfo.nPos = scrollH ;
			SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
			SetScrollRange(this->m_hwnd, SB_HORZ,0, DW, TRUE);
			SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;

		}else{//if no -no scroll bar is needed
		*/
			Ox = 0 ;
			ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
			if(b_HSBarVisible == true)
			{
				b_HSBarVisible = false ;
				goto constraint_width ;
			}
		/*};//else, image less than window
		*/

		//VERTICAL
		if(DH > rect.Height())
		{//scroll offset				
			if(Oy < (rect.Height() - 1 + Y ))  Oy = rect.Height()- 1 + Y;
			if(Oy < -1*DH - abs(Y) ) Oy = -1*DH - abs(Y) ;
			
			//vertical scroll bar position
			scrollV = abs(Oy + DH + Y) ;

			m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
			m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
			m_VSInfo.nMin = 0 ;
			m_VSInfo.nMax = DH ;	
			m_VSInfo.nPage = rect.Height() ; 		
			m_VSInfo.nPos = scrollV ;
			SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
			SetScrollRange(this->m_hwnd, SB_VERT, 0, DH, TRUE);
			SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
			if(b_VSBarVisible == false)
			{
				b_VSBarVisible = true ;
				goto constraint_width ;
			}
		}else{
			Oy = 0 ;
			ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
			if(b_VSBarVisible == true)
			{
				b_VSBarVisible = false ;
				goto constraint_width ;
			}
		}
	//---------------------------------------------------------------+
	}else if(angle == 270)
	{
	//---------------------------------------------------------------+
	//rotated 270
		DH=rect.Width() ;
		DW=(DH*pictureW)/pictureH ;	
		X = -1*DW - (rect.Height() - DW) /2 ;
		Y = (rect.Width() - DH) / 2 ;

		//calculate scroll bars position & set info V-vertical , H-horizontal
		int scrollV = 0, scrollH = 0 ;
		//test if image dimensions are great than window's dimensions
		//VERTICAL
		if(DW > rect.Height())
		{//scroll offset							
			if(Ox < (rect.Height() - 1 + X )) Ox = rect.Height() - 1 + X  ;
			if(Ox < -1*DW - abs(X) ) Ox = -1*DW - abs(X) ;
			
			//vertical scroll bar position
			scrollV = abs(Ox + DW + X) ;

			m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
			m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
			m_VSInfo.nMin = 0 ;
			m_VSInfo.nMax = DW ;	
			m_VSInfo.nPage = rect.Height() ; 		
			m_VSInfo.nPos = scrollV ;
			SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
			SetScrollRange(this->m_hwnd, SB_VERT, 0, DW, TRUE);
			SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
			if(b_VSBarVisible == false)
			{
				b_VSBarVisible = true ;
				goto constraint_width ;
			}
		}else{//if no -no scroll bar is needed
			Ox = 0 ;
			ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
			if(b_VSBarVisible == true)
			{
				b_VSBarVisible = false ;
				goto constraint_width ;
			}
		};//else, image less than window

		//HORIZONTAL
		/*don't need this ...
		source code is intended just for further modifications...
		if(DH > rect.Width())
		{//scroll offset				
			if(Oy < (rect.Width() - DH -1-Y ))  Oy = rect.Width()- DH -1-Y ;
			if(Oy > abs(Y)) Oy = abs(Y) ;
			(Oy < 0) ? scrollV=(-1)*Oy : scrollV=0 ;

			m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
			m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
			m_HSInfo.nMin = 0 ;
			m_HSInfo.nMax = DH ;
			m_HSInfo.nPage = rect.Width() ; 
			m_HSInfo.nPos = scrollH ;
			SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
			SetScrollRange(this->m_hwnd, SB_HORZ,0, DH, TRUE);
			SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
		}else{
		*/
			Oy = 0 ;
			ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
			if(b_HSBarVisible == true)
			{
				b_HSBarVisible = false ;
				goto constraint_width ;
			}
		/*}
		*/
	//---------------------------------------------------------------+
	}else {
	//---------------------------------------------------------------+	
	//default 
		DW=rect.Width();
		DH=(DW*pictureH)/pictureW;
		X = (rect.Width() - DW) / 2 ;
		Y = (rect.Height() - DH) / 2;

		//calculate scroll bars position & set info
		int scrollV = 0, scrollH = 0 ;
		//test if image dimensions are great than window's dimensions
		//HORIZONTAL
		/*don't need this ...
		source code is intended just for further modifications...
		if(DW > rect.Width())
		{//scroll offset							
			if(Ox < (rect.Width() - DW -1 - X)) Ox = rect.Width()- DW -1-X ;
			if(Ox > abs(X)) Ox = abs(X) ;
			
			(Ox < 0) ? scrollH=(-1)*Ox : (scrollH=0) ;

			m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
			m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
			m_HSInfo.nMin = 0 ;
			m_HSInfo.nMax = DW ;
			m_HSInfo.nPage = rect.Width() ; 
			m_HSInfo.nPos = scrollH ;
			SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
			SetScrollRange(this->m_hwnd, SB_HORZ,0, DW, TRUE);
			SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
		}else{//if no -no scroll bar is needed
		*/
			Ox = 0 ;
			ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
			if(b_HSBarVisible == true)
			{
				b_HSBarVisible = false ;
				goto constraint_width ;
			}
		/*};//else, image less than window
		*/

		//VERTICAL
		if(DH > rect.Height())
		{//scroll offset				
			if(Oy < (rect.Height() - DH -1 - Y))  Oy = rect.Height()- DH -1-Y ;
			if(Oy > abs(Y)) Oy = abs(Y) ;
			
			//vertical scroll bar position
			scrollV = abs(Y + Oy) ;

			m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
			m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
			m_VSInfo.nMin = 0 ;
			m_VSInfo.nMax = DH ;	
			m_VSInfo.nPage = rect.Height() ; 		
			m_VSInfo.nPos = scrollV ;
			SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
			SetScrollRange(this->m_hwnd, SB_VERT, 0, DH, TRUE);
			SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
			if(b_VSBarVisible == false)
			{
				b_VSBarVisible = true ;
				goto constraint_width ;
			}
		}else{
			Oy = 0 ;
			ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
			if(b_VSBarVisible == true)
			{
				b_VSBarVisible = false ;
				goto constraint_width ;
			}
		}
	//---------------------------------------------------------------+	
	}
	//------------------------------------------------------------------+
	//computing the image is almost finished
	b_computeImage = false ;

	//section II
	//the actual proportion parameter
	proportion =  DH * 100. / pictureH  ;
	//if image was zoomed restore the flag
	zoom_status = false ;

	//erase background, show image
	mvShowImageBackground(true);
	//finish ConstraintWidth()
	//------------------------------------------------------------------+

	return true ;
}



//gets physical image dimensions and adjust them for deformated images
//fax issued multi-page tiff
//It doesn't test for zoom or other changes of current image
bool mvImage::mvGetImageDimensions(int *imgX, int *imgY)
{
	if(image)
	{
		int x = image->GetWidth() ;
		int y = image->GetHeight() ;
		if(x == 0 || y == 0){
			*imgX = 1 ;
			*imgY = 1 ;
			return true ;
		}

		int resx = (int) image->GetHorizontalResolution() ;
		int resy = (int) image->GetVerticalResolution() ;

		int temp =0 ;
		if(resx != resy) 
			if(resx > resy) 
			{
				temp = (int) (x * resy) / resx ;
				x = temp ;
			}
			else
			{
				temp = (int) (y * resx) / resy ;
				y = temp ;
			}
		//update dimensions pointer
		*imgX = x ;
		*imgY = y ;
		return true ;
	}
	return false ;
}





//mvZoomIn calculates and display image
//according to its new dimensions
bool mvImage::mvZoomIn()
{
	//the process is computing the image
	b_computeImage = true ;

	//--------------------------------------------------------+
	zoom_status = true ;
	mvGetImageDimensions(&pictureW, &pictureH) ;

	double temp = proportion ;
	((temp += 10.) < 500.) ? (proportion = temp) : 0 ;

	int _pictureH = (int) ((pictureH*proportion)/100.) ;
	int _pictureW = (int) ((pictureW*proportion)/100.) ;	
	
	//it must test constraintType and inside test 
	//anoter test - angle value 
	//this part is very like mvConstraint... functions (Nothing, All, Height, Width)
	//image new dimensions (zoomed in) are _pictureW,  _pictureH
	
	if(constraintType == 0)//no  constraint, Original dimensions
	{
		//do the job
zoom_no_constraint:
	;
		CRect rect ;
		GetClientRect(this->m_hwnd, &rect) ;
		
		if(angle == 0)
		{
		//------------------------------------------------------------------+
		//angle zero
			X=0; 
			Y=0;
			DW = _pictureW ;
			DH = _pictureH ;					
			
			//calculate scroll bars position & set info
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//HORIZONTAL
			if(_pictureW > rect.Width())
			{//scroll offset							
				if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
				if(Ox > abs(X)) Ox = abs(X) ;
				
				//horizontal scroll bar position
				scrollH = abs(Ox) ;


				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureW ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;

				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_no_constraint ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;

				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_no_constraint ;
				}
			};//else, image less than window

			//VERTICAL
			if(_pictureH > rect.Height())
			{//scroll offset				
				if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
				if(Oy > abs(Y)) Oy = abs(Y) ;
				
				//vertical scroll bar position
				scrollV = abs(Oy) ;

				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureH ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;

				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_no_constraint ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;

				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_no_constraint ;
				}
			}
	
		//------------------------------------------------------------------+
		}else if(angle == 90)
		{
		//------------------------------------------------------------------+
		//angle 90
			X = 0 ;
			Y = -1*_pictureH ;
			DW = _pictureW ;
			DH = _pictureH ;

			//calculate scroll bars position & set info V-vertical , H-horizontal
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//VERTICAL
			if(_pictureW > rect.Height())
			{//scroll offset							
				if(Ox < (rect.Height() - _pictureW -1-X)) Ox = rect.Height()- _pictureW -1-X ;
				if(Ox > abs(X)) Ox = abs(X) ;
				
				//vertical scroll bar position
				scrollV = abs(Ox) ;

				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureW ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;

				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_no_constraint ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;

				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_no_constraint ;
				}
			};//else, image less than window

			//HORIZONTAL
			if(_pictureH > rect.Width())
			{//scroll offset				
				if(Oy < (rect.Width() - _pictureH +1 ))  Oy = rect.Width()- _pictureH +1 ;
				if(Oy < 0) Oy = 0 ;
				
				//horizontal scroll bar position
				scrollH = abs(Oy) ;

				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureH ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
				if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_no_constraint ;
					};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_no_constraint ;
				}
			}
		//------------------------------------------------------------------+
		}else if(angle == 180)
		{
		//------------------------------------------------------------------+	
		//angle 180
			X = -1*_pictureW  ;
			Y = -1*_pictureH  ;
			DW = _pictureW ;
			DH = _pictureH ;

			//calculate scroll bars position & set info
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//HORIZONTAL
			if(_pictureW > rect.Width())
			{//scroll offset							
				if(Ox < (rect.Width() - _pictureW +1 )) Ox = rect.Width()- _pictureW +1 ;
				if(Ox < 0 ) Ox = 0  ;
				
				//horizontal scroll bar position
				scrollH = abs(Ox) ;

				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureW ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;

				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_no_constraint ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;

				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_no_constraint ;
				}
			};//else, image less than window

			//VERTICAL
			if(_pictureH > rect.Height())
			{//scroll offset				
				if(Oy < (rect.Height() - _pictureH +1 ))  Oy = rect.Height()- _pictureH +1 ;
				if(Oy < 0) Oy = 0 ;
				
				//vertical scroll bar position
				scrollV = abs(Oy) ;				


				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureH ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;

				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_no_constraint ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;

				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_no_constraint ;
				}
			}
		//------------------------------------------------------------------+
		}else if(angle == 270)
		{
		//------------------------------------------------------------------+		
		//angle 270
			X = -1*_pictureW ;
			Y = 0 ;
			DW = _pictureW ;
			DH = _pictureH ;

			//calculate scroll bars position & set info V-vertical , H-horizontal
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//VERTICAL
			if(_pictureW > rect.Height())
			{//scroll offset							
				if(Ox < (rect.Height() - _pictureW +1 )) Ox = rect.Height()- _pictureW +1 ;
				if(Ox < 0) Ox = 0 ;
				
				//vertical scroll bar position
				scrollV = abs(Ox) ;

				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureW ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;

				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_no_constraint ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;

				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_no_constraint ;
				}
			};//else, image less than window

			//HORIZONTAL
			if(_pictureH > rect.Width())
			{//scroll offset				
				if(Oy < (rect.Width() - _pictureH -1-Y ))  
					Oy = rect.Width()- _pictureH -1-Y ;
				if(Oy > abs(Y)) Oy = abs(Y) ;
				
				//horizontal scroll bar position
				scrollH = abs(Oy) ;

				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureH ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;

				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_no_constraint ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
				
				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_no_constraint ;
				}
			}
		//------------------------------------------------------------------+
		}else
		{
		//------------------------------------------------------------------+
		//angle zero default
			X = 0 ;
			Y = 0 ;
			DW = _pictureW ;
			DH = _pictureH ;

			//calculate scroll bars position & set info
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//HORIZONTAL
			if(_pictureW > rect.Width())
			{//scroll offset							
				if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
				if(Ox > abs(X)) Ox = abs(X) ;
				
				//horizontal scroll bar position
				scrollH = abs(Ox) ;

				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureW ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_no_constraint ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_no_constraint ;
				}
			};//else, image less than window

			//VERTICAL
			if(_pictureH > rect.Height())
			{//scroll offset				
				if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
				if(Oy > abs(Y)) Oy = abs(Y) ;
				
				//vertical scroll bar position
				scrollV = abs(Oy) ;

				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureH ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_no_constraint ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_no_constraint ;
				}
			}
		//------------------------------------------------------------------+
		}
	}else if(constraintType == 1)//constraint all - best fit
	{
		//do the job
zoom_constraint_all:
	;
		CRect rect ;
		GetClientRect(this->m_hwnd, &rect) ;
		
		if(angle == 0)
		{
		//------------------------------------------------------------------+
			//angle ZERO
			//new zoomed dimensions
			DH = _pictureH ;
			DW = _pictureW ;
			
			X=(rect.Width()  - DW ) / 2;  
			Y=(rect.Height() - DH ) / 2;  //new positions
			
			//calculate scroll bars position & set info
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//HORIZONTAL
			if(_pictureW > rect.Width())
			{//scroll offset							
				if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
				if(Ox > abs(X)) Ox = abs(X) ;
				
				//horizontal scroll bar position
				scrollH = abs(X + Ox) ;

				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureW ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;

				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_constraint_all ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;

				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_constraint_all ;
				}
			};//else, image less than window

			//VERTICAL
			if(_pictureH > rect.Height())
			{//scroll offset				
				if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
				if(Oy > abs(Y)) Oy = abs(Y) ;
				
				//vertical scroll bar position
				scrollV = abs(Y + Oy) ;

				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureH ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_constraint_all ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_constraint_all ;
				}
			}

		//------------------------------------------------------------------+
		}else if(angle == 90)
		{	
		//------------------------------------------------------------------+
			//angle 90
			//new zoomed dimensions
			DW = _pictureW ;
			DH = _pictureH ;
			X = (rect.Height() - DW) / 2 ;
			Y = -1*DH -1*(rect.Width() - DH)/2 ;

			//calculate scroll bars position & set info V-vertical , H-horizontal
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//VERTICAL
			if(_pictureW > rect.Height())
			{//scroll offset							
				if(Ox < (rect.Height() - _pictureW -1-X)) Ox = rect.Height()- _pictureW -1-X ;
				if(Ox > abs(X)) Ox = abs(X) ;
				
				//vertical scroll bar position
				scrollV = abs(X + Ox) ;	

				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureW ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_constraint_all ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_constraint_all ;
				}
			};//else, image less than window

			//HORIZONTAL
			if(_pictureH > rect.Width())
			{//scroll offset				
				if(Oy < (rect.Width() -1 + Y))  Oy = rect.Width() -1 + Y ;
				if(Oy < -1*_pictureH - abs(Y)) Oy = -1*_pictureH - abs(Y) ;
				
				//horizontal scroll bar position
				scrollH = abs(Oy + DH + Y) ;

				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureH ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;

				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_constraint_all ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;

				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_constraint_all ;
				}
			}
		//------------------------------------------------------------------+
		}else if(angle == 180)
		{
		//------------------------------------------------------------------+
			//angle 180
			//new zoomed dimensions
			DW = _pictureW ;
			DH = _pictureH ;
			X = -1*DW - (rect.Width() - DW) / 2 ;
			Y = -1*DH - (rect.Height() - DH) /2 ;

			//calculate scroll bars position & set info
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//HORIZONTAL
			if(_pictureW > rect.Width())
			{//scroll offset							
				if(Ox < (rect.Width() - 1 + X )) Ox = rect.Width() - 1 + X  ;
				if(Ox < -1*_pictureW - abs(X)) Ox = -1*_pictureW - abs(X)  ;
				
				//horizontal scroll bar position
				scrollH = abs(Ox + DW + X) ;

				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureW ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_constraint_all ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_constraint_all ;
				}
			};//else, image less than window

			//VERTICAL
			if(_pictureH > rect.Height())
			{//scroll offset				
				if(Oy < (rect.Height() - 1 + Y ))  Oy = rect.Height()- 1 + Y;
				if(Oy < -1*_pictureH - abs(Y) ) Oy = -1*_pictureH - abs(Y) ;
				
				//vertical scroll bar position
				scrollV = abs(Oy + DH + Y) ;

				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureH ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_constraint_all ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_constraint_all ;
				}
			}
		//------------------------------------------------------------------+
		}else if(angle == 270)
		{
		//------------------------------------------------------------------+
			//angle 270
			//new zoomed dimensions
			DW = _pictureW ;
			DH = _pictureH ;
			X = -1*DW - (rect.Height() - DW) /2 ;
			Y = (rect.Width() - DH) / 2 ;

			//calculate scroll bars position & set info V-vertical , H-horizontal
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//VERTICAL
			if(_pictureW > rect.Height())
			{//scroll offset							
				if(Ox < (rect.Height() - 1 + X )) Ox = rect.Height() - 1 + X  ;
				if(Ox < -1*_pictureW - abs(X) ) Ox = -1*_pictureW - abs(X) ;
				
				//vertical scroll bar position
				scrollV = abs(Ox + DW + X) ;

				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureW ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_constraint_all ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_constraint_all ;
				}
			};//else, image less than window

			//HORIZONTAL
			if(_pictureH > rect.Width())
			{//scroll offset				
				if(Oy < (rect.Width() - _pictureH -1-Y ))  Oy = rect.Width()- _pictureH -1-Y ;
				if(Oy > abs(Y)) Oy = abs(Y) ;
				
				//horizontal scroll bar position
				scrollH = abs(Oy + Y) ;

				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureH ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_constraint_all ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_constraint_all ;
				}
			}
		//------------------------------------------------------------------+
		}else{
		//------------------------------------------------------------------+
			//angle ZERO
			//new zoomed dimensions
			DW = _pictureW ;
			DH = _pictureH ;
			X = (rect.Width() - DW) / 2 ;
			Y = (rect.Height() - DH) / 2;

			//calculate scroll bars position & set info
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//HORIZONTAL
			if(_pictureW > rect.Width())
			{//scroll offset							
				if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
				if(Ox > abs(X)) Ox = abs(X) ;
				
				//horizontal scroll bar position
				scrollH = abs(X + Ox) ;

				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureW ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_constraint_all ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_constraint_all ;
				}
			};//else, image less than window

			//VERTICAL
			if(_pictureH > rect.Height())
			{//scroll offset				
				if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
				if(Oy > abs(Y)) Oy = abs(Y) ;
				
				//vertical scroll bar position
				scrollV = abs(Y + Oy) ;

				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureH ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_constraint_all ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_constraint_all ;
				}
			}
		//------------------------------------------------------------------+
		};//end else
	}else if(constraintType == 2)//constraint height 
	{
		//do the job
zoom_constraint_height:
	;
		CRect rect ;
		GetClientRect(this->m_hwnd, &rect) ;

		if(angle == 0)
		{
		//--------------------------------------------------------------+
		//rotated ZERO
			/*DH=rect.Height() ;
			DW=(DH*_pictureW)/_pictureH ;*/
			DW = _pictureW ;
			DH = _pictureH ;
			X=(rect.Width()  - DW) / 2;  
			Y=(rect.Height() - DH) / 2;  

			//calculate scroll bars position & set info
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//HORIZONTAL
			if(_pictureW > rect.Width())
			{//scroll offset							
				if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
				if(Ox > abs(X)) Ox = abs(X) ;
				
				//horizontal scroll bar position
				scrollH = abs(X + Ox) ;

				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureW ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;

				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_constraint_height ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;

				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_constraint_height ;
				}
			};//else, image less than window

			//VERTICAL
			if(_pictureH > rect.Height())
			{//scroll offset				
				if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
				if(Oy > abs(Y)) Oy = abs(Y) ;
				
				//horizontal scroll bar position
				scrollV = abs(Y + Oy) ;

				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureH ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_constraint_height ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_constraint_height ;
				}
			}
		//--------------------------------------------------------------+
		}else if(angle == 90)
		{
		//--------------------------------------------------------------+
		//rotated 90
			/*DW=rect.Height();			
			DH=(DW*_pictureH)/_pictureW;*/
			DW = _pictureW ;
			DH = _pictureH ;
			X = (rect.Height() - DW) / 2 ;
			Y = -1*DH -1*(rect.Width() - DH)/2 ;

			//calculate scroll bars position & set info V-vertical , H-horizontal
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//VERTICAL
			if(_pictureW > rect.Height())
			{//scroll offset							
				if(Ox < (rect.Height() - _pictureW -1-X)) Ox = rect.Height()- _pictureW -1-X ;
				if(Ox > abs(X)) Ox = abs(X) ;
				
				//vertical scroll bar position
				scrollV = abs(X + Ox) ;	

				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureW ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_constraint_height ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_constraint_height ;
				}
			};//else, image less than window

			//HORIZONTAL
			if(_pictureH > rect.Width())
			{//scroll offset				
				if(Oy < (rect.Width() -1 + Y))  Oy = rect.Width() -1 + Y ;
				if(Oy < -1*_pictureH - abs(Y)) Oy = -1*_pictureH - abs(Y) ;
				
				//horizontal scroll bar position
				scrollH = abs(Oy + DH + Y) ;

				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureH ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_constraint_height ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_constraint_height ;
				}
			}

		//--------------------------------------------------------------+
		}else if(angle == 180)
		{
		//--------------------------------------------------------------+
		//rotated 180
			/*DH=rect.Height() ;					
			DW=(DH*_pictureW)/_pictureH ;*/
			DW = _pictureW ;
			DH = _pictureH ;
			X = -1*DW - (rect.Width() - DW) / 2 ;
			Y = -1*DH - (rect.Height() - DH) /2 ;

			//calculate scroll bars position & set info
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//HORIZONTAL
			if(_pictureW > rect.Width())
			{//scroll offset							
				if(Ox < (rect.Width() - 1 + X )) Ox = rect.Width() - 1 + X  ;
				if(Ox < -1*_pictureW - abs(X)) Ox = -1*_pictureW - abs(X)  ;
				
				//horizontal scroll bar position
				scrollH = abs(Ox + DW + X) ;

				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureW ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_constraint_height ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_constraint_height ;
				}
			};//else, image less than window

			//VERTICAL
			if(_pictureH > rect.Height())
			{//scroll offset				
				if(Oy < (rect.Height() - 1 + Y ))  Oy = rect.Height()- 1 + Y;
				if(Oy < -1*_pictureH - abs(Y) ) Oy = -1*_pictureH - abs(Y) ;
				
				//vertical scroll bar position
				scrollV = abs(Oy + DH + Y) ;

				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureH ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_constraint_height ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_constraint_height ;
				}
			}

		//--------------------------------------------------------------+
		}else if(angle == 270)
		{
		//--------------------------------------------------------------+
		//rotated 270
			/*DW=rect.Height();			
			DH=(DW*_pictureH)/_pictureW;*/
			DW = _pictureW ;
			DH = _pictureH ;
			X = -1*DW - (rect.Height() - DW) /2 ;
			Y = (rect.Width() - DH) / 2 ;

			//calculate scroll bars position & set info V-vertical , H-horizontal
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//VERTICAL
			if(_pictureW > rect.Height())
			{//scroll offset							
				if(Ox < (rect.Height() - 1 + X )) Ox = rect.Height() - 1 + X  ;
				if(Ox < -1*_pictureW - abs(X) ) Ox = -1*_pictureW - abs(X) ;
				
				//vertical scroll bar position
				scrollV = abs(Ox + DW + X) ;

				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureW ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_constraint_height ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_constraint_height ;
				}
			};//else, image less than window

			//HORIZONTAL
			if(_pictureH > rect.Width())
			{//scroll offset				
				if(Oy < (rect.Width() - _pictureH -1-Y ))  Oy = rect.Width()- _pictureH -1-Y ;
				if(Oy > abs(Y)) Oy = abs(Y) ;
				
				//horizontal scroll bar position
				scrollH = abs(Oy + Y) ;

				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureH ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;

				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_constraint_height ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_constraint_height ;
				}
			}

		//--------------------------------------------------------------+
		}else {
		//--------------------------------------------------------------+
		//default - rotated ZERO
			/*DH=rect.Height() ;				
			DW=(DH*_pictureW)/_pictureH ;*/
			DW = _pictureW ;
			DH = _pictureH ;
			X = (rect.Width() - DW) / 2 ;
			Y = (rect.Height() - DH) / 2;

			//calculate scroll bars position & set info
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//HORIZONTAL
			if(_pictureW > rect.Width())
			{//scroll offset							
				if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
				if(Ox > abs(X)) Ox = abs(X) ;
				
				//horizontal scroll bar position
				scrollH = abs(X + Ox) ;

				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureW ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;

				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_constraint_height ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;

				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_constraint_height ;
				}
			};//else, image less than window

			//VERTICAL
			if(_pictureH > rect.Height())
			{//scroll offset				
				if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
				if(Oy > abs(Y)) Oy = abs(Y) ;
				
				//vertical scroll bar position
				scrollV = abs(Y + Oy) ;	

				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureH ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_constraint_height ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_constraint_height ;
				}
			}

		//--------------------------------------------------------------+
		};//end else
	}else if(constraintType == 3)//constraint width
	{
		//do the job
zoom_constraint_width:
	;
		CRect rect ;
		GetClientRect(this->m_hwnd, &rect) ;
		
		if(angle == 0)
		{
		//---------------------------------------------------------------+
		//rotated 0
			/*DW = rect.Width() ;
			DH = (DW*_pictureH) / _pictureW ;*/
			DW = _pictureW ;
			DH = _pictureH ;
			X=(rect.Width()  - DW ) / 2;  
			Y=(rect.Height() - DH ) / 2;  

			//calculate scroll bars position & set info
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//HORIZONTAL
			if(_pictureW > rect.Width())
			{//scroll offset							
				if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
				if(Ox > abs(X)) Ox = abs(X) ;
				
				//horizontal scroll bar position
				scrollH = abs(X + Ox) ;

				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureW ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_constraint_width ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_constraint_width ;
				}
			};//else, image less than window

			//VERTICAL
			if(_pictureH > rect.Height())
			{//scroll offset				
				if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
				if(Oy > abs(Y)) Oy = abs(Y) ;
				
				//vertical scroll bar position
				scrollV = abs(Y + Oy) ;				


				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureH ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_constraint_width ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_constraint_width ;
				}
			}
		//---------------------------------------------------------------+
		}else if(angle == 90)
		{
		//---------------------------------------------------------------+
		//rotated 90
			/*DH = rect.Width() ;
			DW = (DH*_pictureW) / _pictureH ;*/
			DW = _pictureW ;
			DH = _pictureH ;
			X = (rect.Height() - DW) / 2 ;
			Y = -1*DH -1*(rect.Width() - DH)/2 ;

			//calculate scroll bars position & set info V-vertical , H-horizontal
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//VERTICAL
			if(_pictureW > rect.Height())
			{//scroll offset							
				if(Ox < (rect.Height() - _pictureW -1-X)) Ox = rect.Height()- _pictureW -1-X ;
				if(Ox > abs(X)) Ox = abs(X) ;
				
				//vertical scroll bar position
				scrollV = abs(X + Ox) ;	

				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureW ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_constraint_width ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_constraint_width ;
				}
			};//else, image less than window

			//HORIZONTAL
			if(_pictureH > rect.Width())
			{//scroll offset				
				if(Oy < (rect.Width() -1 + Y))  Oy = rect.Width() -1 + Y ;
				if(Oy < -1*_pictureH - abs(Y)) Oy = -1*_pictureH - abs(Y) ;
				
				//horizontal scroll bar position
				scrollH = abs(Oy + DH + Y) ;

				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureH ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;

				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_constraint_width ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;

				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_constraint_width ;
				}
			}
		//---------------------------------------------------------------+
		}else if(angle == 180)
		{
		//---------------------------------------------------------------+
		//rotated 180
			/*DW=rect.Width();
			DH=(DW*_pictureH)/_pictureW;*/
			DW = _pictureW ;
			DH = _pictureH ;
			X = -1*DW - (rect.Width() - DW) / 2 ;
			Y = -1*DH - (rect.Height() - DH) /2 ;

			//calculate scroll bars position & set info
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//HORIZONTAL
			if(_pictureW > rect.Width())
			{//scroll offset							
				if(Ox < (rect.Width() - 1 + X )) Ox = rect.Width() - 1 + X  ;
				if(Ox < -1*_pictureW - abs(X)) Ox = -1*_pictureW - abs(X)  ;
				
				//horizontal scroll bar position
				scrollH = abs(Ox + DW + X) ;

				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureW ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_constraint_width ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;

				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_constraint_width ;
				}
			};//else, image less than window

			//VERTICAL
			if(_pictureH > rect.Height())
			{//scroll offset				
				if(Oy < (rect.Height() - 1 + Y ))  Oy = rect.Height()- 1 + Y;
				if(Oy < -1*_pictureH - abs(Y) ) Oy = -1*_pictureH - abs(Y) ;
				
				//vertical scroll bar position
				scrollV = abs(Oy + DH + Y) ;

				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureH ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_constraint_width ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_constraint_width ;
				}
			}
		//---------------------------------------------------------------+
		}else if(angle == 270)
		{
		//---------------------------------------------------------------+
		//rotated 270
			/*DH=rect.Width() ;
			DW=(DH*_pictureW)/_pictureH ;*/
			DW = _pictureW ;
			DH = _pictureH ;
			X = -1*DW - (rect.Height() - DW) /2 ;
			Y = (rect.Width() - DH) / 2 ;

			//calculate scroll bars position & set info V-vertical , H-horizontal
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//VERTICAL
			if(_pictureW > rect.Height())
			{//scroll offset							
				if(Ox < (rect.Height() - 1 + X )) Ox = rect.Height() - 1 + X  ;
				if(Ox < -1*_pictureW - abs(X) ) Ox = -1*_pictureW - abs(X) ;
				
				//vertical scroll bar position
				scrollV = abs(Ox + DW + X) ;				

				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureW ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_constraint_width ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_constraint_width ;
				}
			};//else, image less than window

			//HORIZONTAL
			if(_pictureH > rect.Width())
			{//scroll offset				
				if(Oy < (rect.Width() - _pictureH -1-Y ))  Oy = rect.Width()- _pictureH -1-Y ;
				if(Oy > abs(Y)) Oy = abs(Y) ;
				
				//horizontal scroll bar position
				scrollH = abs(Oy + Y) ;

				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureH ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;

				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_constraint_width ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;

				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_constraint_width ;
				}
			}

		//---------------------------------------------------------------+
		}else {
		//---------------------------------------------------------------+	
		//default 
			/*DW=rect.Width();
			DH=(DW*_pictureH)/_pictureW;*/
			DW = _pictureW ;
			DH = _pictureH ;
			X = (rect.Width() - DW) / 2 ;
			Y = (rect.Height() - DH) / 2;

			//calculate scroll bars position & set info
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//HORIZONTAL
			if(_pictureW > rect.Width())
			{//scroll offset							
				if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
				if(Ox > abs(X)) Ox = abs(X) ;
				
				//horizontal scroll bar position
				scrollH = abs(X + Ox) ;

				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureW ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;

				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_constraint_width ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;

				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_constraint_width ;
				}
			};//else, image less than window

			//VERTICAL
			if(_pictureH > rect.Height())
			{//scroll offset				
				if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
				if(Oy > abs(Y)) Oy = abs(Y) ;
				
				//vertical scroll bar position
				scrollV = abs(Y + Oy) ;	

				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureH ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_constraint_width ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_constraint_width ;
				}
			}
		//---------------------------------------------------------------+	
		}
	}else{//constrant all - best fit - default option
		//do the job
zoom_constraint_all2:
	;
		CRect rect ;
		GetClientRect(this->m_hwnd, &rect) ;
		
		if(angle == 0)
		{
		//------------------------------------------------------------------+
			//angle ZERO
			//new zoomed dimensions
			DH = _pictureH ;
			DW = _pictureW ;
			
			X=(rect.Width()  - DW ) / 2;  
			Y=(rect.Height() - DH ) / 2;  //new positions
			
			//calculate scroll bars position & set info
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//HORIZONTAL
			if(_pictureW > rect.Width())
			{//scroll offset							
				if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
				if(Ox > abs(X)) Ox = abs(X) ;
				
				//horizontal scroll bar position
				scrollH = abs(X + Ox) ;

				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureW ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_constraint_all2 ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_constraint_all2 ;
				}
			};//else, image less than window

			//VERTICAL
			if(_pictureH > rect.Height())
			{//scroll offset				
				if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
				if(Oy > abs(Y)) Oy = abs(Y) ;
				
				//vertical scroll bar position
				scrollV = abs(Y + Oy) ;

				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureH ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_constraint_all2 ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_constraint_all2 ;
				}
			}

		//------------------------------------------------------------------+
		}else if(angle == 90)
		{	
		//------------------------------------------------------------------+
			//angle 90
			//new zoomed dimensions
			DW = _pictureW ;
			DH = _pictureH ;
			X = (rect.Height() - DW) / 2 ;
			Y = -1*DH -1*(rect.Width() - DH)/2 ;

			//calculate scroll bars position & set info V-vertical , H-horizontal
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//VERTICAL
			if(_pictureW > rect.Height())
			{//scroll offset							
				if(Ox < (rect.Height() - _pictureW -1-X)) Ox = rect.Height()- _pictureW -1-X ;
				if(Ox > abs(X)) Ox = abs(X) ;
				
				//vertical scroll bar position
				scrollV = abs(X + Ox) ;	

				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureW ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_constraint_all2 ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_constraint_all2 ;
				}
			};//else, image less than window

			//HORIZONTAL
			if(_pictureH > rect.Width())
			{//scroll offset				
				if(Oy < (rect.Width() -1 + Y))  Oy = rect.Width() -1 + Y ;
				if(Oy < -1*_pictureH - abs(Y)) Oy = -1*_pictureH - abs(Y) ;
				
				//horizontal scroll bar position
				scrollH = abs(Oy + DH + Y) ;

				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureH ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_constraint_all2 ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_constraint_all2 ;
				}
			}
		//------------------------------------------------------------------+
		}else if(angle == 180)
		{
		//------------------------------------------------------------------+
			//angle 180
			//new zoomed dimensions
			DW = _pictureW ;
			DH = _pictureH ;
			X = -1*DW - (rect.Width() - DW) / 2 ;
			Y = -1*DH - (rect.Height() - DH) /2 ;

			//calculate scroll bars position & set info
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//HORIZONTAL
			if(_pictureW > rect.Width())
			{//scroll offset							
				if(Ox < (rect.Width() - 1 + X )) Ox = rect.Width() - 1 + X  ;
				if(Ox < -1*_pictureW - abs(X)) Ox = -1*_pictureW - abs(X)  ;
				
				//horizontal scroll bar position
				scrollH = abs(Ox + DW + X) ;

				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureW ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;

				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_constraint_all2 ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;

				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_constraint_all2 ;
				}
			};//else, image less than window

			//VERTICAL
			if(_pictureH > rect.Height())
			{//scroll offset				
				if(Oy < (rect.Height() - 1 + Y ))  Oy = rect.Height()- 1 + Y;
				if(Oy < -1*_pictureH - abs(Y) ) Oy = -1*_pictureH - abs(Y) ;
				
				//vertical scroll bar position
				scrollV = abs(Oy + DH + Y) ;

				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureH ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_constraint_all2 ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_constraint_all2 ;
				}
			}
		//------------------------------------------------------------------+
		}else if(angle == 270)
		{
		//------------------------------------------------------------------+
			//angle 270
			//new zoomed dimensions
			DW = _pictureW ;
			DH = _pictureH ;
			X = -1*DW - (rect.Height() - DW) /2 ;
			Y = (rect.Width() - DH) / 2 ;

			//calculate scroll bars position & set info V-vertical , H-horizontal
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//VERTICAL
			if(_pictureW > rect.Height())
			{//scroll offset							
				if(Ox < (rect.Height() - 1 + X )) Ox = rect.Height() - 1 + X  ;
				if(Ox < -1*_pictureW - abs(X) ) Ox = -1*_pictureW - abs(X) ;
				
				//vertical scroll bar position
				scrollV = abs(Ox + DW + X) ;	

				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureW ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_constraint_all2 ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_constraint_all2 ;
				}
			};//else, image less than window

			//HORIZONTAL
			if(_pictureH > rect.Width())
			{//scroll offset				
				if(Oy < (rect.Width() - _pictureH -1-Y ))  Oy = rect.Width()- _pictureH -1-Y ;
				if(Oy > abs(Y)) Oy = abs(Y) ;
				
				//horizontal scroll bar position
				scrollH = abs(Oy + Y) ;

				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureH ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_constraint_all2 ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_constraint_all2 ;
				}
			}
		//------------------------------------------------------------------+
		}else{
		//------------------------------------------------------------------+
			//angle ZERO
			//new zoomed dimensions
			DW = _pictureW ;
			DH = _pictureH ;
			X = (rect.Width() - DW) / 2 ;
			Y = (rect.Height() - DH) / 2;

			//calculate scroll bars position & set info
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//HORIZONTAL
			if(_pictureW > rect.Width())
			{//scroll offset							
				if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
				if(Ox > abs(X)) Ox = abs(X) ;
				
				//horizontal scroll bar position
				scrollH = abs(X + Ox) ;


				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureW ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_constraint_all2 ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_constraint_all2 ;
				}
			};//else, image less than window

			//VERTICAL
			if(_pictureH > rect.Height())
			{//scroll offset				
				if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
				if(Oy > abs(Y)) Oy = abs(Y) ;
				
				//vertical scroll bar position
				scrollV = abs(Y + Oy) ;	

				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureH ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_constraint_all2 ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_constraint_all2 ;
				}
			}
		//------------------------------------------------------------------+
		};//end else
	};//end else default - constraint all - best fit

	//the process finished computing image
	b_computeImage = false ;

	
		
	//erase the background , display the image
	mvShowImageBackground(true) ;
	
	
	//--------------------------------------------------------+
	return true ;
	//finish mvZoomIn()
}



//mvZoomOut calculate and display the image
bool mvImage::mvZoomOut()
{
	//indicate the process is computing the image
	b_computeImage = true ;

	//--------------------------------------------------------+
	zoom_status = true ;
	mvGetImageDimensions(&pictureW, &pictureH) ;

	double temp = proportion ;
	((temp -= 10.) > 10.) ? (proportion = temp) : 0 ;

	int _pictureH = (int) ((pictureH*proportion)/100.) ;
	int _pictureW = (int) ((pictureW*proportion)/100.) ;	
	
	//it must test constraintType and inside test 
	//anoter test - angle value 
	//this part is very like mvConstraint... functions (Nothing, All, Height, Width)
	//image new dimensions (zoomed in) are _pictureW,  _pictureH
	if(constraintType == 0)//no  constraint, Original dimensions
	{
		//do the job
zoom_no_constraint:
	;
		CRect rect ;
		GetClientRect(this->m_hwnd, &rect) ;
		
		if(angle == 0)
		{
		//------------------------------------------------------------------+
		//angle zero
			X=0; 
			Y=0;
			DW = _pictureW ;
			DH = _pictureH ;					
			
			//calculate scroll bars position & set info
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//HORIZONTAL
			if(_pictureW > rect.Width())
			{//scroll offset							
				if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
				if(Ox > abs(X)) Ox = abs(X) ;
				
				//horizontal scroll bar position
				scrollH = abs(Ox) ;


				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureW ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;

				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_no_constraint ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;

				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_no_constraint ;
				}
			};//else, image less than window

			//VERTICAL
			if(_pictureH > rect.Height())
			{//scroll offset				
				if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
				if(Oy > abs(Y)) Oy = abs(Y) ;
				
				//vertical scroll bar position
				scrollV = abs(Oy) ;

				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureH ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;

				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_no_constraint ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;

				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_no_constraint ;
				}
			}
	
		//------------------------------------------------------------------+
		}else if(angle == 90)
		{
		//------------------------------------------------------------------+
		//angle 90
			X = 0 ;
			Y = -1*_pictureH ;
			DW = _pictureW ;
			DH = _pictureH ;

			//calculate scroll bars position & set info V-vertical , H-horizontal
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//VERTICAL
			if(_pictureW > rect.Height())
			{//scroll offset							
				if(Ox < (rect.Height() - _pictureW -1-X)) Ox = rect.Height()- _pictureW -1-X ;
				if(Ox > abs(X)) Ox = abs(X) ;
				
				//vertical scroll bar position
				scrollV = abs(Ox) ;

				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureW ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;

				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_no_constraint ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;

				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_no_constraint ;
				}
			};//else, image less than window

			//HORIZONTAL
			if(_pictureH > rect.Width())
			{//scroll offset				
				if(Oy < (rect.Width() - _pictureH +1 ))  Oy = rect.Width()- _pictureH +1 ;
				if(Oy < 0) Oy = 0 ;
				
				//horizontal scroll bar position
				scrollH = abs(Oy) ;

				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureH ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
				if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_no_constraint ;
					};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_no_constraint ;
				}
			}
		//------------------------------------------------------------------+
		}else if(angle == 180)
		{
		//------------------------------------------------------------------+	
		//angle 180
			X = -1*_pictureW  ;
			Y = -1*_pictureH  ;
			DW = _pictureW ;
			DH = _pictureH ;

			//calculate scroll bars position & set info
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//HORIZONTAL
			if(_pictureW > rect.Width())
			{//scroll offset							
				if(Ox < (rect.Width() - _pictureW +1 )) Ox = rect.Width()- _pictureW +1 ;
				if(Ox < 0 ) Ox = 0  ;
				
				//horizontal scroll bar position
				scrollH = abs(Ox) ;

				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureW ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;

				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_no_constraint ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;

				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_no_constraint ;
				}
			};//else, image less than window

			//VERTICAL
			if(_pictureH > rect.Height())
			{//scroll offset				
				if(Oy < (rect.Height() - _pictureH +1 ))  Oy = rect.Height()- _pictureH +1 ;
				if(Oy < 0) Oy = 0 ;
				
				//vertical scroll bar position
				scrollV = abs(Oy) ;				


				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureH ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;

				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_no_constraint ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;

				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_no_constraint ;
				}
			}
		//------------------------------------------------------------------+
		}else if(angle == 270)
		{
		//------------------------------------------------------------------+		
		//angle 270
			X = -1*_pictureW ;
			Y = 0 ;
			DW = _pictureW ;
			DH = _pictureH ;

			//calculate scroll bars position & set info V-vertical , H-horizontal
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//VERTICAL
			if(_pictureW > rect.Height())
			{//scroll offset							
				if(Ox < (rect.Height() - _pictureW +1 )) Ox = rect.Height()- _pictureW +1 ;
				if(Ox < 0) Ox = 0 ;
				
				//vertical scroll bar position
				scrollV = abs(Ox) ;

				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureW ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;

				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_no_constraint ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;

				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_no_constraint ;
				}
			};//else, image less than window

			//HORIZONTAL
			if(_pictureH > rect.Width())
			{//scroll offset				
				if(Oy < (rect.Width() - _pictureH -1-Y ))  
					Oy = rect.Width()- _pictureH -1-Y ;
				if(Oy > abs(Y)) Oy = abs(Y) ;
				
				//horizontal scroll bar position
				scrollH = abs(Oy) ;

				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureH ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;

				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_no_constraint ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
				
				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_no_constraint ;
				}
			}
		//------------------------------------------------------------------+
		}else
		{
		//------------------------------------------------------------------+
		//angle zero default
			X = 0 ;
			Y = 0 ;
			DW = _pictureW ;
			DH = _pictureH ;

			//calculate scroll bars position & set info
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//HORIZONTAL
			if(_pictureW > rect.Width())
			{//scroll offset							
				if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
				if(Ox > abs(X)) Ox = abs(X) ;
				
				//horizontal scroll bar position
				scrollH = abs(Ox) ;

				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureW ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_no_constraint ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_no_constraint ;
				}
			};//else, image less than window

			//VERTICAL
			if(_pictureH > rect.Height())
			{//scroll offset				
				if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
				if(Oy > abs(Y)) Oy = abs(Y) ;
				
				//vertical scroll bar position
				scrollV = abs(Oy) ;

				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureH ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_no_constraint ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_no_constraint ;
				}
			}
		//------------------------------------------------------------------+
		}
	}else if(constraintType == 1)//constraint all - best fit
	{
		//do the job
zoom_constraint_all:
	;
		CRect rect ;
		GetClientRect(this->m_hwnd, &rect) ;
		
		if(angle == 0)
		{
		//------------------------------------------------------------------+
			//angle ZERO
			//new zoomed dimensions
			DH = _pictureH ;
			DW = _pictureW ;
			
			X=(rect.Width()  - DW ) / 2;  
			Y=(rect.Height() - DH ) / 2;  //new positions
			
			//calculate scroll bars position & set info
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//HORIZONTAL
			if(_pictureW > rect.Width())
			{//scroll offset							
				if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
				if(Ox > abs(X)) Ox = abs(X) ;
				
				//horizontal scroll bar position
				scrollH = abs(X + Ox) ;

				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureW ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;

				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_constraint_all ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;

				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_constraint_all ;
				}
			};//else, image less than window

			//VERTICAL
			if(_pictureH > rect.Height())
			{//scroll offset				
				if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
				if(Oy > abs(Y)) Oy = abs(Y) ;
				
				//vertical scroll bar position
				scrollV = abs(Y + Oy) ;

				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureH ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_constraint_all ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_constraint_all ;
				}
			}

		//------------------------------------------------------------------+
		}else if(angle == 90)
		{	
		//------------------------------------------------------------------+
			//angle 90
			//new zoomed dimensions
			DW = _pictureW ;
			DH = _pictureH ;
			X = (rect.Height() - DW) / 2 ;
			Y = -1*DH -1*(rect.Width() - DH)/2 ;

			//calculate scroll bars position & set info V-vertical , H-horizontal
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//VERTICAL
			if(_pictureW > rect.Height())
			{//scroll offset							
				if(Ox < (rect.Height() - _pictureW -1-X)) Ox = rect.Height()- _pictureW -1-X ;
				if(Ox > abs(X)) Ox = abs(X) ;
				
				//vertical scroll bar position
				scrollV = abs(X + Ox) ;	

				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureW ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_constraint_all ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_constraint_all ;
				}
			};//else, image less than window

			//HORIZONTAL
			if(_pictureH > rect.Width())
			{//scroll offset				
				if(Oy < (rect.Width() -1 + Y))  Oy = rect.Width() -1 + Y ;
				if(Oy < -1*_pictureH - abs(Y)) Oy = -1*_pictureH - abs(Y) ;
				
				//horizontal scroll bar position
				scrollH = abs(Oy + DH + Y) ;

				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureH ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;

				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_constraint_all ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;

				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_constraint_all ;
				}
			}
		//------------------------------------------------------------------+
		}else if(angle == 180)
		{
		//------------------------------------------------------------------+
			//angle 180
			//new zoomed dimensions
			DW = _pictureW ;
			DH = _pictureH ;
			X = -1*DW - (rect.Width() - DW) / 2 ;
			Y = -1*DH - (rect.Height() - DH) /2 ;

			//calculate scroll bars position & set info
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//HORIZONTAL
			if(_pictureW > rect.Width())
			{//scroll offset							
				if(Ox < (rect.Width() - 1 + X )) Ox = rect.Width() - 1 + X  ;
				if(Ox < -1*_pictureW - abs(X)) Ox = -1*_pictureW - abs(X)  ;
				
				//horizontal scroll bar position
				scrollH = abs(Ox + DW + X) ;

				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureW ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_constraint_all ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_constraint_all ;
				}
			};//else, image less than window

			//VERTICAL
			if(_pictureH > rect.Height())
			{//scroll offset				
				if(Oy < (rect.Height() - 1 + Y ))  Oy = rect.Height()- 1 + Y;
				if(Oy < -1*_pictureH - abs(Y) ) Oy = -1*_pictureH - abs(Y) ;
				
				//vertical scroll bar position
				scrollV = abs(Oy + DH + Y) ;

				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureH ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_constraint_all ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_constraint_all ;
				}
			}
		//------------------------------------------------------------------+
		}else if(angle == 270)
		{
		//------------------------------------------------------------------+
			//angle 270
			//new zoomed dimensions
			DW = _pictureW ;
			DH = _pictureH ;
			X = -1*DW - (rect.Height() - DW) /2 ;
			Y = (rect.Width() - DH) / 2 ;

			//calculate scroll bars position & set info V-vertical , H-horizontal
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//VERTICAL
			if(_pictureW > rect.Height())
			{//scroll offset							
				if(Ox < (rect.Height() - 1 + X )) Ox = rect.Height() - 1 + X  ;
				if(Ox < -1*_pictureW - abs(X) ) Ox = -1*_pictureW - abs(X) ;
				
				//vertical scroll bar position
				scrollV = abs(Ox + DW + X) ;

				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureW ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_constraint_all ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_constraint_all ;
				}
			};//else, image less than window

			//HORIZONTAL
			if(_pictureH > rect.Width())
			{//scroll offset				
				if(Oy < (rect.Width() - _pictureH -1-Y ))  Oy = rect.Width()- _pictureH -1-Y ;
				if(Oy > abs(Y)) Oy = abs(Y) ;
				
				//horizontal scroll bar position
				scrollH = abs(Oy + Y) ;

				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureH ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_constraint_all ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_constraint_all ;
				}
			}
		//------------------------------------------------------------------+
		}else{
		//------------------------------------------------------------------+
			//angle ZERO
			//new zoomed dimensions
			DW = _pictureW ;
			DH = _pictureH ;
			X = (rect.Width() - DW) / 2 ;
			Y = (rect.Height() - DH) / 2;

			//calculate scroll bars position & set info
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//HORIZONTAL
			if(_pictureW > rect.Width())
			{//scroll offset							
				if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
				if(Ox > abs(X)) Ox = abs(X) ;
				
				//horizontal scroll bar position
				scrollH = abs(X + Ox) ;

				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureW ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_constraint_all ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_constraint_all ;
				}
			};//else, image less than window

			//VERTICAL
			if(_pictureH > rect.Height())
			{//scroll offset				
				if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
				if(Oy > abs(Y)) Oy = abs(Y) ;
				
				//vertical scroll bar position
				scrollV = abs(Y + Oy) ;

				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureH ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_constraint_all ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_constraint_all ;
				}
			}
		//------------------------------------------------------------------+
		};//end else
	}else if(constraintType == 2)//constraint height 
	{
		//do the job
zoom_constraint_height:
	;
		CRect rect ;
		GetClientRect(this->m_hwnd, &rect) ;

		if(angle == 0)
		{
		//--------------------------------------------------------------+
		//rotated ZERO
			/*DH=rect.Height() ;
			DW=(DH*_pictureW)/_pictureH ;*/
			DW = _pictureW ;
			DH = _pictureH ;
			X=(rect.Width()  - DW) / 2;  
			Y=(rect.Height() - DH) / 2;  

			//calculate scroll bars position & set info
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//HORIZONTAL
			if(_pictureW > rect.Width())
			{//scroll offset							
				if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
				if(Ox > abs(X)) Ox = abs(X) ;
				
				//horizontal scroll bar position
				scrollH = abs(X + Ox) ;

				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureW ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;

				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_constraint_height ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;

				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_constraint_height ;
				}
			};//else, image less than window

			//VERTICAL
			if(_pictureH > rect.Height())
			{//scroll offset				
				if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
				if(Oy > abs(Y)) Oy = abs(Y) ;
				
				//horizontal scroll bar position
				scrollH = abs(X + Ox) ;

				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureH ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_constraint_height ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_constraint_height ;
				}
			}
		//--------------------------------------------------------------+
		}else if(angle == 90)
		{
		//--------------------------------------------------------------+
		//rotated 90
			/*DW=rect.Height();			
			DH=(DW*_pictureH)/_pictureW;*/
			DW = _pictureW ;
			DH = _pictureH ;
			X = (rect.Height() - DW) / 2 ;
			Y = -1*DH -1*(rect.Width() - DH)/2 ;

			//calculate scroll bars position & set info V-vertical , H-horizontal
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//VERTICAL
			if(_pictureW > rect.Height())
			{//scroll offset							
				if(Ox < (rect.Height() - _pictureW -1-X)) Ox = rect.Height()- _pictureW -1-X ;
				if(Ox > abs(X)) Ox = abs(X) ;
				
				//vertical scroll bar position
				scrollV = abs(X + Ox) ;	

				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureW ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_constraint_height ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_constraint_height ;
				}
			};//else, image less than window

			//HORIZONTAL
			if(_pictureH > rect.Width())
			{//scroll offset				
				if(Oy < (rect.Width() -1 + Y))  Oy = rect.Width() -1 + Y ;
				if(Oy < -1*_pictureH - abs(Y)) Oy = -1*_pictureH - abs(Y) ;
				
				//horizontal scroll bar position
				scrollH = abs(Oy + DH + Y) ;

				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureH ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_constraint_height ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_constraint_height ;
				}
			}

		//--------------------------------------------------------------+
		}else if(angle == 180)
		{
		//--------------------------------------------------------------+
		//rotated 180
			/*DH=rect.Height() ;					
			DW=(DH*_pictureW)/_pictureH ;*/
			DW = _pictureW ;
			DH = _pictureH ;
			X = -1*DW - (rect.Width() - DW) / 2 ;
			Y = -1*DH - (rect.Height() - DH) /2 ;

			//calculate scroll bars position & set info
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//HORIZONTAL
			if(_pictureW > rect.Width())
			{//scroll offset							
				if(Ox < (rect.Width() - 1 + X )) Ox = rect.Width() - 1 + X  ;
				if(Ox < -1*_pictureW - abs(X)) Ox = -1*_pictureW - abs(X)  ;
				
				//horizontal scroll bar position
				scrollH = abs(Ox + DW + X) ;

				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureW ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_constraint_height ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_constraint_height ;
				}
			};//else, image less than window

			//VERTICAL
			if(_pictureH > rect.Height())
			{//scroll offset				
				if(Oy < (rect.Height() - 1 + Y ))  Oy = rect.Height()- 1 + Y;
				if(Oy < -1*_pictureH - abs(Y) ) Oy = -1*_pictureH - abs(Y) ;
				
				//vertical scroll bar position
				scrollV = abs(Oy + DH + Y) ;

				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureH ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_constraint_height ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_constraint_height ;
				}
			}

		//--------------------------------------------------------------+
		}else if(angle == 270)
		{
		//--------------------------------------------------------------+
		//rotated 270
			/*DW=rect.Height();			
			DH=(DW*_pictureH)/_pictureW;*/
			DW = _pictureW ;
			DH = _pictureH ;
			X = -1*DW - (rect.Height() - DW) /2 ;
			Y = (rect.Width() - DH) / 2 ;

			//calculate scroll bars position & set info V-vertical , H-horizontal
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//VERTICAL
			if(_pictureW > rect.Height())
			{//scroll offset							
				if(Ox < (rect.Height() - 1 + X )) Ox = rect.Height() - 1 + X  ;
				if(Ox < -1*_pictureW - abs(X) ) Ox = -1*_pictureW - abs(X) ;
				
				//vertical scroll bar position
				scrollV = abs(Ox + DW + X) ;

				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureW ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_constraint_height ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_constraint_height ;
				}
			};//else, image less than window

			//HORIZONTAL
			if(_pictureH > rect.Width())
			{//scroll offset				
				if(Oy < (rect.Width() - _pictureH -1-Y ))  Oy = rect.Width()- _pictureH -1-Y ;
				if(Oy > abs(Y)) Oy = abs(Y) ;
				
				//horizontal scroll bar position
				scrollH = abs(Oy + Y) ;

				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureH ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;

				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_constraint_height ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_constraint_height ;
				}
			}

		//--------------------------------------------------------------+
		}else {
		//--------------------------------------------------------------+
		//default - rotated ZERO
			/*DH=rect.Height() ;				
			DW=(DH*_pictureW)/_pictureH ;*/
			DW = _pictureW ;
			DH = _pictureH ;
			X = (rect.Width() - DW) / 2 ;
			Y = (rect.Height() - DH) / 2;

			//calculate scroll bars position & set info
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//HORIZONTAL
			if(_pictureW > rect.Width())
			{//scroll offset							
				if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
				if(Ox > abs(X)) Ox = abs(X) ;
				
				//horizontal scroll bar position
				scrollH = abs(X + Ox) ;

				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureW ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;

				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_constraint_height ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;

				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_constraint_height ;
				}
			};//else, image less than window

			//VERTICAL
			if(_pictureH > rect.Height())
			{//scroll offset				
				if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
				if(Oy > abs(Y)) Oy = abs(Y) ;
				
				//vertical scroll bar position
				scrollV = abs(Y + Oy) ;	

				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureH ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_constraint_height ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_constraint_height ;
				}
			}

		//--------------------------------------------------------------+
		};//end else
	}else if(constraintType == 3)//constraint width
	{
		//do the job
zoom_constraint_width:
	;
		CRect rect ;
		GetClientRect(this->m_hwnd, &rect) ;
		
		if(angle == 0)
		{
		//---------------------------------------------------------------+
		//rotated 0
			/*DW = rect.Width() ;
			DH = (DW*_pictureH) / _pictureW ;*/
			DW = _pictureW ;
			DH = _pictureH ;
			X=(rect.Width()  - DW ) / 2;  
			Y=(rect.Height() - DH ) / 2;  

			//calculate scroll bars position & set info
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//HORIZONTAL
			if(_pictureW > rect.Width())
			{//scroll offset							
				if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
				if(Ox > abs(X)) Ox = abs(X) ;
				
				//horizontal scroll bar position
				scrollH = abs(X + Ox) ;

				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureW ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_constraint_width ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_constraint_width ;
				}
			};//else, image less than window

			//VERTICAL
			if(_pictureH > rect.Height())
			{//scroll offset				
				if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
				if(Oy > abs(Y)) Oy = abs(Y) ;
				
				//vertical scroll bar position
				scrollV = abs(Y + Oy) ;				


				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureH ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_constraint_width ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_constraint_width ;
				}
			}
		//---------------------------------------------------------------+
		}else if(angle == 90)
		{
		//---------------------------------------------------------------+
		//rotated 90
			/*DH = rect.Width() ;
			DW = (DH*_pictureW) / _pictureH ;*/
			DW = _pictureW ;
			DH = _pictureH ;
			X = (rect.Height() - DW) / 2 ;
			Y = -1*DH -1*(rect.Width() - DH)/2 ;

			//calculate scroll bars position & set info V-vertical , H-horizontal
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//VERTICAL
			if(_pictureW > rect.Height())
			{//scroll offset							
				if(Ox < (rect.Height() - _pictureW -1-X)) Ox = rect.Height()- _pictureW -1-X ;
				if(Ox > abs(X)) Ox = abs(X) ;
				
				//vertical scroll bar position
				scrollV = abs(X + Ox) ;	

				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureW ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_constraint_width ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_constraint_width ;
				}
			};//else, image less than window

			//HORIZONTAL
			if(_pictureH > rect.Width())
			{//scroll offset				
				if(Oy < (rect.Width() -1 + Y))  Oy = rect.Width() -1 + Y ;
				if(Oy < -1*_pictureH - abs(Y)) Oy = -1*_pictureH - abs(Y) ;
				
				//horizontal scroll bar position
				scrollH = abs(Oy + DH + Y) ;

				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureH ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;

				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_constraint_width ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;

				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_constraint_width ;
				}
			}
		//---------------------------------------------------------------+
		}else if(angle == 180)
		{
		//---------------------------------------------------------------+
		//rotated 180
			/*DW=rect.Width();
			DH=(DW*_pictureH)/_pictureW;*/
			DW = _pictureW ;
			DH = _pictureH ;
			X = -1*DW - (rect.Width() - DW) / 2 ;
			Y = -1*DH - (rect.Height() - DH) /2 ;

			//calculate scroll bars position & set info
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//HORIZONTAL
			if(_pictureW > rect.Width())
			{//scroll offset							
				if(Ox < (rect.Width() - 1 + X )) Ox = rect.Width() - 1 + X  ;
				if(Ox < -1*_pictureW - abs(X)) Ox = -1*_pictureW - abs(X)  ;
				
				//horizontal scroll bar position
				scrollH = abs(Ox + DW + X) ;

				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureW ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_constraint_width ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;

				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_constraint_width ;
				}
			};//else, image less than window

			//VERTICAL
			if(_pictureH > rect.Height())
			{//scroll offset				
				if(Oy < (rect.Height() - 1 + Y ))  Oy = rect.Height()- 1 + Y;
				if(Oy < -1*_pictureH - abs(Y) ) Oy = -1*_pictureH - abs(Y) ;
				
				//vertical scroll bar position
				scrollV = abs(Oy + DH + Y) ;

				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureH ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_constraint_width ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_constraint_width ;
				}
			}
		//---------------------------------------------------------------+
		}else if(angle == 270)
		{
		//---------------------------------------------------------------+
		//rotated 270
			/*DH=rect.Width() ;
			DW=(DH*_pictureW)/_pictureH ;*/
			DW = _pictureW ;
			DH = _pictureH ;
			X = -1*DW - (rect.Height() - DW) /2 ;
			Y = (rect.Width() - DH) / 2 ;

			//calculate scroll bars position & set info V-vertical , H-horizontal
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//VERTICAL
			if(_pictureW > rect.Height())
			{//scroll offset							
				if(Ox < (rect.Height() - 1 + X )) Ox = rect.Height() - 1 + X  ;
				if(Ox < -1*_pictureW - abs(X) ) Ox = -1*_pictureW - abs(X) ;
				
				//vertical scroll bar position
				scrollV = abs(Ox + DW + X) ;				

				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureW ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_constraint_width ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_constraint_width ;
				}
			};//else, image less than window

			//HORIZONTAL
			if(_pictureH > rect.Width())
			{//scroll offset				
				if(Oy < (rect.Width() - _pictureH -1-Y ))  Oy = rect.Width()- _pictureH -1-Y ;
				if(Oy > abs(Y)) Oy = abs(Y) ;
				
				//horizontal scroll bar position
				scrollH = abs(Oy + Y) ;

				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureH ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;

				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_constraint_width ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;

				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_constraint_width ;
				}
			}

		//---------------------------------------------------------------+
		}else {
		//---------------------------------------------------------------+	
		//default 
			/*DW=rect.Width();
			DH=(DW*_pictureH)/_pictureW;*/
			DW = _pictureW ;
			DH = _pictureH ;
			X = (rect.Width() - DW) / 2 ;
			Y = (rect.Height() - DH) / 2;

			//calculate scroll bars position & set info
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//HORIZONTAL
			if(_pictureW > rect.Width())
			{//scroll offset							
				if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
				if(Ox > abs(X)) Ox = abs(X) ;
				
				//horizontal scroll bar position
				scrollH = abs(X + Ox) ;

				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureW ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;

				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_constraint_width ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;

				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_constraint_width ;
				}
			};//else, image less than window

			//VERTICAL
			if(_pictureH > rect.Height())
			{//scroll offset				
				if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
				if(Oy > abs(Y)) Oy = abs(Y) ;
				
				//vertical scroll bar position
				scrollV = abs(Y + Oy) ;	

				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureH ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_constraint_width ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_constraint_width ;
				}
			}
		//---------------------------------------------------------------+	
		}
	}else{//constrant all - best fit - default option
		//do the job
zoom_constraint_all2:
	;
		CRect rect ;
		GetClientRect(this->m_hwnd, &rect) ;
		
		if(angle == 0)
		{
		//------------------------------------------------------------------+
			//angle ZERO
			//new zoomed dimensions
			DH = _pictureH ;
			DW = _pictureW ;
			
			X=(rect.Width()  - DW ) / 2;  
			Y=(rect.Height() - DH ) / 2;  //new positions
			
			//calculate scroll bars position & set info
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//HORIZONTAL
			if(_pictureW > rect.Width())
			{//scroll offset							
				if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
				if(Ox > abs(X)) Ox = abs(X) ;
				
				//horizontal scroll bar position
				scrollH = abs(X + Ox) ;

				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureW ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_constraint_all2 ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_constraint_all2 ;
				}
			};//else, image less than window

			//VERTICAL
			if(_pictureH > rect.Height())
			{//scroll offset				
				if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
				if(Oy > abs(Y)) Oy = abs(Y) ;
				
				//vertical scroll bar position
				scrollV = abs(Y + Oy) ;

				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureH ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_constraint_all2 ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_constraint_all2 ;
				}
			}

		//------------------------------------------------------------------+
		}else if(angle == 90)
		{	
		//------------------------------------------------------------------+
			//angle 90
			//new zoomed dimensions
			DW = _pictureW ;
			DH = _pictureH ;
			X = (rect.Height() - DW) / 2 ;
			Y = -1*DH -1*(rect.Width() - DH)/2 ;

			//calculate scroll bars position & set info V-vertical , H-horizontal
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//VERTICAL
			if(_pictureW > rect.Height())
			{//scroll offset							
				if(Ox < (rect.Height() - _pictureW -1-X)) Ox = rect.Height()- _pictureW -1-X ;
				if(Ox > abs(X)) Ox = abs(X) ;
				
				//vertical scroll bar position
				scrollV = abs(X + Ox) ;	

				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureW ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_constraint_all2 ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_constraint_all2 ;
				}
			};//else, image less than window

			//HORIZONTAL
			if(_pictureH > rect.Width())
			{//scroll offset				
				if(Oy < (rect.Width() -1 + Y))  Oy = rect.Width() -1 + Y ;
				if(Oy < -1*_pictureH - abs(Y)) Oy = -1*_pictureH - abs(Y) ;
				
				//horizontal scroll bar position
				scrollH = abs(Oy + DH + Y) ;

				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureH ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_constraint_all2 ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_constraint_all2 ;
				}
			}
		//------------------------------------------------------------------+
		}else if(angle == 180)
		{
		//------------------------------------------------------------------+
			//angle 180
			//new zoomed dimensions
			DW = _pictureW ;
			DH = _pictureH ;
			X = -1*DW - (rect.Width() - DW) / 2 ;
			Y = -1*DH - (rect.Height() - DH) /2 ;

			//calculate scroll bars position & set info
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//HORIZONTAL
			if(_pictureW > rect.Width())
			{//scroll offset							
				if(Ox < (rect.Width() - 1 + X )) Ox = rect.Width() - 1 + X  ;
				if(Ox < -1*_pictureW - abs(X)) Ox = -1*_pictureW - abs(X)  ;
				
				//horizontal scroll bar position
				scrollH = abs(Ox + DW + X) ;

				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureW ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;

				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_constraint_all2 ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;

				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_constraint_all2 ;
				}
			};//else, image less than window

			//VERTICAL
			if(_pictureH > rect.Height())
			{//scroll offset				
				if(Oy < (rect.Height() - 1 + Y ))  Oy = rect.Height()- 1 + Y;
				if(Oy < -1*_pictureH - abs(Y) ) Oy = -1*_pictureH - abs(Y) ;
				
				//vertical scroll bar position
				scrollV = abs(Oy + DH + Y) ;

				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureH ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_constraint_all2 ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_constraint_all2 ;
				}
			}
		//------------------------------------------------------------------+
		}else if(angle == 270)
		{
		//------------------------------------------------------------------+
			//angle 270
			//new zoomed dimensions
			DW = _pictureW ;
			DH = _pictureH ;
			X = -1*DW - (rect.Height() - DW) /2 ;
			Y = (rect.Width() - DH) / 2 ;

			//calculate scroll bars position & set info V-vertical , H-horizontal
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//VERTICAL
			if(_pictureW > rect.Height())
			{//scroll offset							
				if(Ox < (rect.Height() - 1 + X )) Ox = rect.Height() - 1 + X  ;
				if(Ox < -1*_pictureW - abs(X) ) Ox = -1*_pictureW - abs(X) ;
				
				//vertical scroll bar position
				scrollV = abs(Ox + DW + X) ;	

				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureW ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_constraint_all2 ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_constraint_all2 ;
				}
			};//else, image less than window

			//HORIZONTAL
			if(_pictureH > rect.Width())
			{//scroll offset				
				if(Oy < (rect.Width() - _pictureH -1-Y ))  Oy = rect.Width()- _pictureH -1-Y ;
				if(Oy > abs(Y)) Oy = abs(Y) ;
				
				//horizontal scroll bar position
				scrollH = abs(Oy + Y) ;

				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureH ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_constraint_all2 ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_constraint_all2 ;
				}
			}
		//------------------------------------------------------------------+
		}else{
		//------------------------------------------------------------------+
			//angle ZERO
			//new zoomed dimensions
			DW = _pictureW ;
			DH = _pictureH ;
			X = (rect.Width() - DW) / 2 ;
			Y = (rect.Height() - DH) / 2;

			//calculate scroll bars position & set info
			int scrollV = 0, scrollH = 0 ;
			//test if image dimensions are great than window's dimensions
			//HORIZONTAL
			if(_pictureW > rect.Width())
			{//scroll offset							
				if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
				if(Ox > abs(X)) Ox = abs(X) ;
				
				//horizontal scroll bar position
				scrollH = abs(X + Ox) ;


				m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
				m_HSInfo.nMin = 0 ;
				m_HSInfo.nMax = _pictureW ;
				m_HSInfo.nPage = rect.Width() ; 
				m_HSInfo.nPos = scrollH ;
				SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
				SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
				if(b_HSBarVisible == false)
				{
					b_HSBarVisible = true ;
					goto zoom_constraint_all2 ;
				};//horz scroll bar
			}else{//if no -no scroll bar is needed
				Ox = 0 ;
				ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
				if(b_HSBarVisible == true)
				{
					b_HSBarVisible = false ;
					goto zoom_constraint_all2 ;
				}
			};//else, image less than window

			//VERTICAL
			if(_pictureH > rect.Height())
			{//scroll offset				
				if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
				if(Oy > abs(Y)) Oy = abs(Y) ;
				
				//vertical scroll bar position
				scrollV = abs(Y + Oy) ;	

				m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
				m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
				m_VSInfo.nMin = 0 ;
				m_VSInfo.nMax = _pictureH ;	
				m_VSInfo.nPage = rect.Height() ; 		
				m_VSInfo.nPos = scrollV ;
				SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
				SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
				SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
				ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
				if(b_VSBarVisible == false)
				{
					b_VSBarVisible = true ;
					goto zoom_constraint_all2 ;
				};//horz scroll bar
			}else{
				Oy = 0 ;
				ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
				if(b_VSBarVisible == true)
				{
					b_VSBarVisible = false ;
					goto zoom_constraint_all2 ;
				}
			}
		//------------------------------------------------------------------+
		};//end else
	};//end else default - constraint all - best fit

	//the process finished computing image
	b_computeImage = false ;

	
	//erase the background , display the image
	mvShowImageBackground(true) ;
	
	//--------------------------------------------------------+
	return true ;
	//finish mvZoomOut()
}



//It modifies angle value with 90 degrees counter clockwise direction
//mvRotateRight calculate image coordinates and display the image.
void mvImage::mvRotateLeft()
{
	//process is computing an image
	b_computeImage = true ;

	//modify current angle to new desired value
	(angle == 0) ? (angle = 270) : (angle -= 90) ;

	//test if zoom functions modifyed already the image
	//the image is not zoomed - algorith like in 
	//mvConstraint... functions (Nothing, All, Height, Width)
	if(zoom_status == false)
	{
		//check the constraint type of image displaing mode in window		
		if(constraintType == 0)//no  constraint 
		{
			//do the job
constraint_nothing:
		;
			CRect rect ;
			GetClientRect(this->m_hwnd, &rect) ;
			mvGetImageDimensions(&pictureW, &pictureH) ;
			if(angle == 0)
			{
			//------------------------------------------------------------------+
			//angle zero
				X=0; 
				Y=0;
				DW = pictureW ;
				DH = pictureH ;
					
				
				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = -1*Oy ;
				Oy = temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(DW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - DW -1 - X)) Ox = rect.Width()- DW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = DW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, DW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto constraint_nothing ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto constraint_nothing ;
					}

				};//else, image less than window

				//VERTICAL
				if(DH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - DH -1 - Y))  Oy = rect.Height()- DH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;
					
					//vertical scroll bar position
					scrollV = abs(Oy) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = DH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, DH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto constraint_nothing ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto constraint_nothing ;
					}
				}

			//------------------------------------------------------------------+
			}else if(angle == 90)
			{
			//------------------------------------------------------------------+
			//angle 90
				X = 0 ;
				Y = -1*pictureH ;
				DW = pictureW ;
				DH = pictureH ;

				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;				
				int temp = Ox ;
				Ox = -1*Oy ;
				Oy = temp ;


				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(DW > rect.Height())
				{//scroll offset							
					if(Ox < (-1)*(DW - rect.Height()- 1) )  
						Ox = (-1)*(DW - rect.Height()- 1) ;
					if(Ox > abs(X))  
						Ox = abs(X) ;
					
					//vertical scroll bar position
					scrollV = abs(Ox) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = DW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, DW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto constraint_nothing ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto constraint_nothing ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(DH > rect.Width())
				{//scroll offset				
					if(Oy > (DH - rect.Width()-1))  Oy = (DH - rect.Width()-1) ;
					if(Oy < 0) Oy = 0 ;

					//horizontal scroll bar position
					scrollH = abs(Oy) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = DH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, DH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto constraint_nothing ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto constraint_nothing ;
					}
				}

			//------------------------------------------------------------------+
			}else if(angle == 180)
			{
			//------------------------------------------------------------------+	
			//angle 180
				X = -1*pictureW  ;
				Y = -1*pictureH  ;
				DW = pictureW ;
				DH = pictureH ;

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = -1*Oy ;
				Oy = temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(DW > rect.Width())
				{//scroll offset							
					if(Ox > (DW - rect.Width()-1))  Ox = (DW - rect.Width()-1) ;
					if(Ox < 0 ) Ox = 0  ;
					
					//horizontal scroll bar position
					scrollH = abs(Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = DW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, DW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto constraint_nothing ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto constraint_nothing ;
					}
				};//else, image less than window

				//VERTICAL
				if(DH > rect.Height())
				{//scroll offset				
					if( Oy > DH - rect.Height() - 1 )
						Oy = DH - rect.Height() - 1 ;
					if(Oy < 0)
						Oy = 0 ;

					//vertical scroll bar position
					scrollV = abs(Oy) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = DH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, DH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto constraint_nothing ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto constraint_nothing ;
					}
				}
			//------------------------------------------------------------------+
			}else if(angle == 270)
			{
			//------------------------------------------------------------------+		
			//angle 270
				X = -1*pictureW ;
				Y = 0 ;
				DW = pictureW ;
				DH = pictureH ;

				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = -1*Oy ;
				Oy = temp ;

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(DW > rect.Height())
				{//scroll offset							
					if( Ox > DW - rect.Height() - 1 )
						Ox = DW - rect.Height() - 1 ;
					if(Ox < 0)
						Ox = 0 ;
					
					//vertical scroll bar position
					scrollV = abs(Ox) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = DW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, DW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto constraint_nothing ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto constraint_nothing ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(DH > rect.Width())
				{//scroll offset				
					if(Oy < (rect.Width() - DH -1 -Y))  Oy = rect.Width()- DH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//horizontal scroll bar position
					scrollH = abs(Oy) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = DH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, DH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto constraint_nothing ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto constraint_nothing ;
					}
				}
			//------------------------------------------------------------------+
			}else
			{
			//------------------------------------------------------------------+
			//angle zero default	
				X=0; 
				Y=0;
				DW = pictureW ;
				DH = pictureH ;
					
				
				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = -1*Oy ;
				Oy = temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(DW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - DW -1 - X)) Ox = rect.Width()- DW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = DW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, DW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto constraint_nothing ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto constraint_nothing ;
					}
				};//else, image less than window

				//VERTICAL
				if(DH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - DH -1 - Y))  Oy = rect.Height()- DH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//vertical scroll bar position
					scrollV = abs(Oy) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = DH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, DH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto constraint_nothing ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto constraint_nothing ;
					}
				}
			};//else , default angle zero
			//------------------------------------------------------------------+
		}else if(constraintType == 1)//constraint all - best fit
		{			
			//because of image constraint 'best fit' was performed previously
			//so the scroll bars are hidden
			//do the job
//constraint_all :
//		;
			//scroll bars have been hidden before.
			CRect rect ;
			GetClientRect(this->m_hwnd, &rect) ;
			mvGetImageDimensions(&pictureW, &pictureH) ;
			if(angle == 0)
			{
			//------------------------------------------------------------------+
				//angle ZERO
				DH=rect.Height() ;
				DW=(DH*pictureW)/pictureH ;				
				if(DW>rect.Width())
				{
					DW=rect.Width();
					DH=(DW*pictureH)/pictureW;
				};

				
				X=(rect.Width()  - DW ) / 2;  
				Y=(rect.Height() - DH ) / 2;  //new positions
				//scrolls bars offset
				Ox = 0 ;  Oy = 0 ;
				//don't need to put scroll bars in window
			//------------------------------------------------------------------+
			}else if(angle == 90)
			{	
			//------------------------------------------------------------------+
				//angle 90
				DW=rect.Height();			
				DH=(DW*pictureH)/pictureW;		
				if(DH>rect.Width())
				{
					DH=rect.Width() ;
					DW=(DH*pictureW)/pictureH ;	
				};
				X = (rect.Height() - DW) / 2 ;
				Y = -1*DH -1*(rect.Width() - DH)/2 ;
				//scrolls bars offset
				Ox = 0 ;  Oy = 0 ;
				//don't need to put scroll bars in window
			//------------------------------------------------------------------+
			}else if(angle == 180)
			{
			//------------------------------------------------------------------+
				//angle 180
				DH=rect.Height() ;				//height of image
				DW=(DH*pictureW)/pictureH ;		//width of image
				if(DW>rect.Width())
				{
					DW=rect.Width();
					DH=(DW*pictureH)/pictureW;
				}
				X = -1*DW - (rect.Width() - DW) / 2 ;
				Y = -1*DH - (rect.Height() - DH) /2 ;
				//scrolls bars offset
				Ox = 0 ;  Oy = 0 ;
				//don't need to put scroll bars in window
			//------------------------------------------------------------------+
			}else if(angle == 270)
			{
			//------------------------------------------------------------------+
				//angle 270
				DW=rect.Height();			
				DH=(DW*pictureH)/pictureW;	
				
				if(DH>rect.Width())
				{
					DH=rect.Width() ;
					DW=(DH*pictureW)/pictureH ;	
				};
				X = -1*DW - (rect.Height() - DW) /2 ;
				Y = (rect.Width() - DH) / 2 ;
				//scrolls bars offset
				Ox = 0 ;  Oy = 0 ;
				//don't need to put scroll bars in window
			//------------------------------------------------------------------+
			}else{
			//------------------------------------------------------------------+
				//angle ZERO
				DH=rect.Height() ;
				DW=(DH*pictureW)/pictureH ;				
				if(DW>rect.Width())
				{
					DW=rect.Width();
					DH=(DW*pictureH)/pictureW;
				};
				X = (rect.Width() - DW) / 2 ;
				Y = (rect.Height() - DH) / 2;
				//scrolls bars offset
				Ox = 0 ;  Oy = 0 ;
				//don't need to put scroll bars in window
			//------------------------------------------------------------------+
			};//end else
		//------------------------------------------------------------------+
		}else if(constraintType == 2)//constraint height 
		{
			//do the job
constraint_height:
		;
			CRect rect ;
			GetClientRect(this->m_hwnd, &rect) ;
			mvGetImageDimensions(&pictureW, &pictureH) ;
			if(angle == 0)
			{
			//--------------------------------------------------------------+
			//rotated ZERO
				DH=rect.Height() ;
				DW=(DH*pictureW)/pictureH ;				
				X=(rect.Width()  - DW) / 2;  
				Y=(rect.Height() - DH) / 2;  
	
				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = -1*Oy ;
				Oy = temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(DW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - DW -1 - X)) Ox = rect.Width()- DW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(X + Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = DW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, DW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto constraint_height ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto constraint_height ;
					}
				};//else, image less than window

				//VERTICAL
				if(DH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - DH -1 - Y))  Oy = rect.Height()- DH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//vertical scroll bar position
					scrollV = abs(Y + Oy) ;	

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = DH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, DH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto constraint_height ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto constraint_height ;
					}
				}
			//--------------------------------------------------------------+
			}else if(angle == 90)
			{
			//--------------------------------------------------------------+
			//rotated 90
				DW=rect.Height();			
				DH=(DW*pictureH)/pictureW;	
				X = (rect.Height() - DW) / 2 ;
				Y = -1*DH -1*(rect.Width() - DH)/2 ;


				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = -1*Oy ;
				Oy = temp ;

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(DW > rect.Height())
				{//scroll offset							
					if(Ox < (rect.Height() - DW -1-X)) Ox = rect.Height()- DW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//vertical scroll bar position
					scrollV = abs(X + Ox) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = DW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, DW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto constraint_height ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto constraint_height ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(DH > rect.Width())
				{//scroll offset				
					if(Oy > (-1)*DH + (DH - rect.Width()-1) - Y)
						Oy = (-1)*DH + (DH - rect.Width()-1) - Y ;
					if(Oy < (-1)*DH - Y) 
						Oy = (-1)*DH - Y ;

					//horizontal scroll bar position
					scrollH = abs(Oy + DH + Y) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = DH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, DH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto constraint_height ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto constraint_height ;
					}
				}
			//--------------------------------------------------------------+
			}else if(angle == 180)
			{
			//--------------------------------------------------------------+
			//rotated 180
				DH=rect.Height() ;				//height of image
				DW=(DH*pictureW)/pictureH ;		//width of image
				X = -1*DW - (rect.Width() - DW) / 2 ;
				Y = -1*DH - (rect.Height() - DH) /2 ;

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = -1*Oy ;
				Oy = temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(DW > rect.Width())
				{//scroll offset							
					if(Ox > (-1)*DW + (DW - rect.Width()-1) - X)
						Ox = (-1)*DW + (DW - rect.Width()-1) - X ;
					if(Ox < (-1)*DW - X) 
						Ox = (-1)*DW - X ;

					//horizontal scroll bar position
					scrollH = abs(Ox + DW + X) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = DW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, DW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;

					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto constraint_height ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
		
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto constraint_height ;
					}
				};//else, image less than window

				//VERTICAL
				if(DH > rect.Height())
				{//scroll offset				
					if(Oy >	(-1)*DH + (DH - rect.Height()-1) - Y)
						Oy = (-1)*DH + (DH - rect.Height()-1) - Y ;
					if(Oy < (-1)*DH - Y) 
						Oy = (-1)*DH - Y ;

					//vertical scroll bar position
					scrollV = abs(Oy + DH + Y) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = DH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, DH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto constraint_height ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto constraint_height ;
					}
				}
			//--------------------------------------------------------------+
			}else if(angle == 270)
			{
			//--------------------------------------------------------------+
			//rotated 270
				DW=rect.Height();			
				DH=(DW*pictureH)/pictureW;	
				X = -1*DW - (rect.Height() - DW) /2 ;
				Y = (rect.Width() - DH) / 2 ;

				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = -1*Oy ;
				Oy = temp ;

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(DW > rect.Height())
				{//scroll offset							
					if(Ox >	(-1)*DW + (DW - rect.Height()-1) - X)
						Ox = (-1)*DW + (DW - rect.Height()-1) - X ;
					if(Ox < (-1)*DW - X) 
						Ox = (-1)*DW - X ;
					
					//vertical scroll bar position
					scrollV = abs(Ox + DW + X) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = DW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, DW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto constraint_height ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto constraint_height ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(DH > rect.Width())
				{//scroll offset				
					if(Oy < (rect.Width() - DH -1 -Y))  Oy = rect.Width()- DH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//horizontal scroll bar position
					scrollH = abs(Oy + Y) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = DH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, DH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto constraint_height ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto constraint_height ;
					}
				}
			//--------------------------------------------------------------+
			}else {
			//--------------------------------------------------------------+
			//default - rotated ZERO
				DH=rect.Height() ;				//height of image
				DW=(DH*pictureW)/pictureH ;		//width of image
				X = (rect.Width() - DW) / 2 ;
				Y = (rect.Height() - DH) / 2;
			
				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = -1*Oy ;
				Oy = temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(DW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - DW -1 - X)) Ox = rect.Width()- DW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(X + Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = DW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, DW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto constraint_height ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto constraint_height ;
					}
				};//else, image less than window

				//VERTICAL
				if(DH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - DH -1 - Y))  Oy = rect.Height()- DH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//vertical scroll bar position
					scrollV = abs(Y + Oy) ;	

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = DH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, DH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto constraint_height ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto constraint_height ;
					}
				}					
			//--------------------------------------------------------------+
			};//end else
		}else if(constraintType == 3)//constraint width
		{
			//do the job
constraint_width:
		;
			CRect rect ;
			GetClientRect(this->m_hwnd, &rect) ;
			mvGetImageDimensions(&pictureW, &pictureH) ;
			if(angle == 0)
			{
			//---------------------------------------------------------------+
			//rotated 0
				DW = rect.Width() ;
				DH = (DW*pictureH) / pictureW ;
				X=(rect.Width()  - DW ) / 2;  
				Y=(rect.Height() - DH ) / 2;  

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = -1*Oy ;
				Oy = temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(DW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - DW -1 - X)) Ox = rect.Width()- DW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(X + Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = DW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, DW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto constraint_width ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto constraint_width ;
					}
				};//else, image less than window

				//VERTICAL
				if(DH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - DH -1 - Y))  Oy = rect.Height()- DH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//vertical scroll bar position
					scrollV = abs(Y + Oy) ;	

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = DH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, DH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto constraint_width ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto constraint_width ;
					}
				}
			//---------------------------------------------------------------+
			}else if(angle == 90)
			{
			//---------------------------------------------------------------+
			//rotated 90
				DH = rect.Width() ;
				DW = (DH*pictureW) / pictureH ;
				X = (rect.Height() - DW) / 2 ;
				Y = -1*DH -1*(rect.Width() - DH)/2 ;

				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = -1*Oy ;
				Oy = temp ;

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(DW > rect.Height())
				{//scroll offset							
					if(Ox < (rect.Height() - DW -1-X)) Ox = rect.Height()- DW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//vertical scroll bar position
					scrollV = abs(X + Ox) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = DW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, DW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto constraint_width ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto constraint_width ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(DH > rect.Width())
				{//scroll offset				
					if(Oy > (-1)*DH + (DH - rect.Width()-1) - Y)
						Oy = (-1)*DH + (DH - rect.Width()-1) - Y ;
					if(Oy < (-1)*DH - Y) 
						Oy = (-1)*DH - Y ;

					//horizontal scroll bar position
					scrollH = abs(Oy + DH + Y) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = DH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, DH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto constraint_width ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto constraint_width ;
					}
				}
			//---------------------------------------------------------------+
			}else if(angle == 180)
			{
			//---------------------------------------------------------------+
			//rotated 180
				DW=rect.Width();
				DH=(DW*pictureH)/pictureW;
				X = -1*DW - (rect.Width() - DW) / 2 ;
				Y = -1*DH - (rect.Height() - DH) /2 ;

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = -1*Oy ;
				Oy = temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(DW > rect.Width())
				{//scroll offset							
					if(Ox > (-1)*DW + (DW - rect.Width()-1) - X)
						Ox = (-1)*DW + (DW - rect.Width()-1) - X ;
					if(Ox < (-1)*DW - X) 
						Ox = (-1)*DW - X ;
					
					//horizontal scroll bar position
					scrollH = abs(Ox + DW + X) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = DW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, DW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto constraint_width ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto constraint_width ;
					}
				};//else, image less than window

				//VERTICAL
				if(DH > rect.Height())
				{//scroll offset				
					if(Oy >	(-1)*DH + (DH - rect.Height()-1) - Y)
						Oy = (-1)*DH + (DH - rect.Height()-1) - Y ;
					if(Oy < (-1)*DH - Y) 
						Oy = (-1)*DH - Y ;

					//vertical scroll bar position
					scrollV = abs(Oy + DH + Y) ;	

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = DH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, DH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto constraint_width ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto constraint_width ;
					}
				}
			//---------------------------------------------------------------+
			}else if(angle == 270)
			{
			//---------------------------------------------------------------+
			//rotated 270
				DH=rect.Width() ;
				DW=(DH*pictureW)/pictureH ;	
				X = -1*DW - (rect.Height() - DW) /2 ;
				Y = (rect.Width() - DH) / 2 ;
			
				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = -1*Oy ;
				Oy = temp ;

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(DW > rect.Height())
				{//scroll offset							
					if(Ox >	(-1)*DW + (DW - rect.Height()-1) - X)
						Ox = (-1)*DW + (DW - rect.Height()-1) - X ;
					if(Ox < (-1)*DW - X) 
						Ox = (-1)*DW - X ;
					
					//vertical scroll bar position
					scrollV = abs(Ox + DW + X) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = DW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, DW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto constraint_width ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto constraint_width ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(DH > rect.Width())
				{//scroll offset				
					if(Oy < (rect.Width() - DH -1 -Y))  Oy = rect.Width()- DH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//horizontal scroll bar position
					scrollH = abs(Oy + Y) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = DH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, DH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto constraint_width ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto constraint_width ;
					}
				}
			//---------------------------------------------------------------+
			}else {
			//---------------------------------------------------------------+	
			//default 
				DW=rect.Width();
				DH=(DW*pictureH)/pictureW;
				X = (rect.Width() - DW) / 2 ;
				Y = (rect.Height() - DH) / 2;
			
				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = -1*Oy ;
				Oy = temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(DW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - DW -1 - X)) Ox = rect.Width()- DW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(X + Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = DW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, DW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto constraint_width ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto constraint_width ;
					}
				};//else, image less than window

				//VERTICAL
				if(DH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - DH -1 - Y))  Oy = rect.Height()- DH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//vertical scroll bar position
					scrollV = abs(Y + Oy) ;	

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = DH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, DH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto constraint_width ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto constraint_width ;
					}
				}
			//---------------------------------------------------------------+	
			}
			//------------------------------------------------------------------+
		}else{//constrant all - best fit - default option
			//do the job
//constraint_all2:
//		;						
			CRect rect ;
			GetClientRect(this->m_hwnd, &rect) ;
			mvGetImageDimensions(&pictureW, &pictureH) ;
			if(angle == 0)
			{
			//------------------------------------------------------------------+
				//angle ZERO
				DH=rect.Height() ;
				DW=(DH*pictureW)/pictureH ;				
				if(DW>rect.Width())
				{
					DW=rect.Width();
					DH=(DW*pictureH)/pictureW;
				};

				
				X=(rect.Width()  - DW ) / 2;  
				Y=(rect.Height() - DH ) / 2;  //new positions
				//scrolls bars offset
				Ox = 0 ;  Oy = 0 ;
				//don't need to put scroll bars in window
			//------------------------------------------------------------------+
			}else if(angle == 90)
			{	
			//------------------------------------------------------------------+
				//angle 90
				DW=rect.Height();			
				DH=(DW*pictureH)/pictureW;		
				if(DH>rect.Width())
				{
					DH=rect.Width() ;
					DW=(DH*pictureW)/pictureH ;	
				};
				X = (rect.Height() - DW) / 2 ;
				Y = -1*DH -1*(rect.Width() - DH)/2 ;
				//scrolls bars offset
				Ox = 0 ;  Oy = 0 ;
				//don't need to put scroll bars in window
			//------------------------------------------------------------------+
			}else if(angle == 180)
			{
			//------------------------------------------------------------------+
				//angle 180
				DH=rect.Height() ;				//height of image
				DW=(DH*pictureW)/pictureH ;		//width of image
				if(DW>rect.Width())
				{
					DW=rect.Width();
					DH=(DW*pictureH)/pictureW;
				}
				X = -1*DW - (rect.Width() - DW) / 2 ;
				Y = -1*DH - (rect.Height() - DH) /2 ;
				//scrolls bars offset
				Ox = 0 ;  Oy = 0 ;
				//don't need to put scroll bars in window
			//------------------------------------------------------------------+
			}else if(angle == 270)
			{
			//------------------------------------------------------------------+
				//angle 270
				DW=rect.Height();			
				DH=(DW*pictureH)/pictureW;	
				
				if(DH>rect.Width())
				{
					DH=rect.Width() ;
					DW=(DH*pictureW)/pictureH ;	
				};
				X = -1*DW - (rect.Height() - DW) /2 ;
				Y = (rect.Width() - DH) / 2 ;
				//scrolls bars offset
				Ox = 0 ;  Oy = 0 ;
				//don't need to put scroll bars in window
			//------------------------------------------------------------------+
			}else{
			//------------------------------------------------------------------+
				//angle ZERO
				DH=rect.Height() ;
				DW=(DH*pictureW)/pictureH ;				
				if(DW>rect.Width())
				{
					DW=rect.Width();
					DH=(DW*pictureH)/pictureW;
				};
				X = (rect.Width() - DW) / 2 ;
				Y = (rect.Height() - DH) / 2;
				//scrolls bars offset
				Ox = 0 ;  Oy = 0 ;
				//don't need to put scroll bars in window
			//------------------------------------------------------------------+
			};//end else
		};//end else default - constraint all - best fit

	}//end if, image is not zoomed 
	else{//zoom_status = true, image is zoomed
		//the image is zoomed - algorith like in 
		//mvZoom... functions (In, Out)
		//check the constraint type of image displaing mode in window
		
		mvGetImageDimensions(&pictureW, &pictureH) ;

		int _pictureH = (int) ((pictureH*proportion)/100.) ;
		int _pictureW = (int) ((pictureW*proportion)/100.) ;	
		 
		if(constraintType == 0)//no  constraint
		{
			//do the job
zoom_constraint_nothing:
		;
			CRect rect ;
			GetClientRect(this->m_hwnd, &rect) ;
			
			if(angle == 0)
			{
			//------------------------------------------------------------------+
			//angle zero
				X=0; 
				Y=0;
				DW = _pictureW ;
				DH = _pictureH ;

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = -1*Oy ;
				Oy = temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(_pictureW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - DW -1 - X)) 
						Ox = rect.Width()- DW -1-X ;
					if(Ox > abs(X)) 
						Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_nothing ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_nothing ;
					}
				};//else, image less than window

				//VERTICAL
				if(_pictureH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - DH -1 - Y)) Oy = rect.Height()- DH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//vertical scroll bar position
					scrollV = abs(Oy) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_nothing ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_nothing ;
					}
				}
	
			//------------------------------------------------------------------+
			}else if(angle == 90)
			{
			//------------------------------------------------------------------+
			//angle 90
				X = 0 ;
				Y = -1*_pictureH ;
				DW = _pictureW ;
				DH = _pictureH ;

				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = -1*Oy ;
				Oy = temp ;

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(_pictureW > rect.Height())
				{//scroll offset							
					if(Ox < (-1)*(DW - rect.Height()- 1) )  
						Ox = (-1)*(DW - rect.Height()- 1) ;
					if(Ox > 0) 
						Ox = 0 ;
					
					//vertical scroll bar position
					scrollV = abs(Ox) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_nothing ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_nothing ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(_pictureH > rect.Width())
				{//scroll offset				
					if(Oy > (DH - rect.Width()-1))  Oy = (DH - rect.Width()-1) ;
					if(Oy < 0) Oy = 0 ;

					//horizontal scroll bar position
					scrollH = abs(Oy) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_nothing ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_nothing ;
					}
				}
			//------------------------------------------------------------------+
			}else if(angle == 180)
			{
			//------------------------------------------------------------------+	
			//angle 180
				X = -1*_pictureW  ;
				Y = -1*_pictureH  ;
				DW = _pictureW ;
				DH = _pictureH ;

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = -1*Oy ;
				Oy = temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(_pictureW > rect.Width())
				{//scroll offset							
					if(Ox > (DW - rect.Width()-1))  Ox = (DW - rect.Width()-1) ;
					if(Ox < 0 ) Ox = 0  ;
					
					//horizontal scroll bar position
					scrollH = abs(Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;

					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_nothing ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_nothing ;
					}
				};//else, image less than window

				//VERTICAL
				if(_pictureH > rect.Height())
				{//scroll offset				
					if( Oy > DH - rect.Height() - 1 )
						Oy = DH - rect.Height() - 1 ;
					if(Oy < 0)
						Oy = 0 ;

					//vertical scroll bar position
					scrollV = abs(Oy) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_nothing ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_nothing ;
					}
				}
			//------------------------------------------------------------------+
			}else if(angle == 270)
			{
			//------------------------------------------------------------------+		
			//angle 270
				X = -1*_pictureW ;
				Y = 0 ;
				DW = _pictureW ;
				DH = _pictureH ;

				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = -1*Oy ;
				Oy = temp ;

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(_pictureW > rect.Height())
				{//scroll offset							
					if( Ox > DW - rect.Height() - 1 )
						Ox = DW - rect.Height() - 1 ;
					if(Ox < 0)
						Ox = 0 ;
					
					//vertical scroll bar position
					scrollV = abs(Ox) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_nothing ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_nothing ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(_pictureH > rect.Width())
				{//scroll offset				
					if(Oy < (rect.Width() - DH -1 -Y))  Oy = rect.Width()- DH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//horizontal scroll bar position
					scrollH = abs(Oy) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_nothing ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_nothing ;
					}
				}
			//------------------------------------------------------------------+
			}else
			{
			//------------------------------------------------------------------+
			//angle zero default
				X = 0 ;
				Y = 0 ;
				DW = _pictureW ;
				DH = _pictureH ;

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = -1*Oy ;
				Oy = temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(_pictureW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_nothing ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_nothing ;
					}
				};//else, image less than window

				//VERTICAL
				if(_pictureH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;
			
					//vertical scroll bar position
					scrollV = abs(Oy) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_nothing ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_nothing ;
					}
				}
			//------------------------------------------------------------------+
			}
		}else if(constraintType == 1)//constraint all - best fit
		{
			//do the job
zoom_constraint_all:
		;
			CRect rect ;
			GetClientRect(this->m_hwnd, &rect) ;
			
			if(angle == 0)
			{
			//------------------------------------------------------------------+
				//angle ZERO
				//new zoomed dimensions
				DH = _pictureH ;
				DW = _pictureW ;
				
				X=(rect.Width()  - DW ) / 2;  
				Y=(rect.Height() - DH ) / 2;  //new positions

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = -1*Oy ;
				Oy = temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(_pictureW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(X + Ox) ;


					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_all ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_all ;
					}
				};//else, image less than window

				//VERTICAL
				if(_pictureH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//vertical scroll bar position
					scrollV = abs(Y + Oy) ;				


					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_all ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_all ;
					}
				}
			//------------------------------------------------------------------+
			}else if(angle == 90)
			{	
			//------------------------------------------------------------------+
				//angle 90
				//new zoomed dimensions
				DW = _pictureW ;
				DH = _pictureH ;
				X = (rect.Height() - DW) / 2 ;
				Y = -1*DH - (rect.Width() - DH)/2 ;

				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = -1*Oy ;
				Oy = temp ;

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(_pictureW > rect.Height())
				{//scroll offset							
					if(Ox < (rect.Height() - _pictureW -1-X)) Ox = rect.Height()- _pictureW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//vertical scroll bar position
					scrollV = abs(X + Ox) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_all ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_all ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(_pictureH > rect.Width())
				{//scroll offset				
					if(Oy > (-1)*DH + (DH - rect.Width()-1) - Y)
						Oy = (-1)*DH + (DH - rect.Width()-1) - Y ;
					if(Oy < (-1)*DH - Y) 
						Oy = (-1)*DH - Y ;
					
					//horizontal scroll bar position
					scrollH = abs(Oy + DH + Y) ;


					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_all ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_all ;
					}
				}
			//------------------------------------------------------------------+
			}else if(angle == 180)
			{
			//------------------------------------------------------------------+
				//angle 180
				//new zoomed dimensions
				DW = _pictureW ;
				DH = _pictureH ;
				X = -1*DW - (rect.Width() - DW) / 2 ;
				Y = -1*DH - (rect.Height() - DH) /2 ;

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = -1*Oy ;
				Oy = temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(_pictureW > rect.Width())
				{//scroll offset							
					if(Ox > (-1)*DW + (DW - rect.Width()-1) - X)
						Ox = (-1)*DW + (DW - rect.Width()-1) - X ;
					if(Ox < (-1)*DW - X) 
						Ox = (-1)*DW - X ;
					
					//horizontal scroll bar position
					scrollH = abs(Ox + DW + X) ;


					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_all ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_all ;
					}
				};//else, image less than window

				//VERTICAL
				if(_pictureH > rect.Height())
				{//scroll offset				
					if(Oy >	(-1)*DH + (DH - rect.Height()-1) - Y)
						Oy = (-1)*DH + (DH - rect.Height()-1) - Y ;
					if(Oy < (-1)*DH - Y) 
						Oy = (-1)*DH - Y ;

					//vertical scroll bar position
					scrollV = abs(Oy + DH + Y) ;	

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_all ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_all ;
					}
				}
			//------------------------------------------------------------------+
			}else if(angle == 270)
			{
			//------------------------------------------------------------------+
				//angle 270
				//new zoomed dimensions
				DW = _pictureW ;
				DH = _pictureH ;
				X = -1*DW - (rect.Height() - DW) /2 ;
				Y = (rect.Width() - DH) / 2 ;

				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = -1*Oy ;
				Oy = temp ;

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(_pictureW > rect.Height())
				{//scroll offset							
					if(Ox >	(-1)*DW + (DW - rect.Height()-1) - X)
						Ox = (-1)*DW + (DW - rect.Height()-1) - X ;
					if(Ox < (-1)*DW - X) 
						Ox = (-1)*DW - X ;
					
					//vertical scroll bar position
					scrollV = abs(Ox + DW + X) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_all ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_all ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(_pictureH > rect.Width())
				{//scroll offset				
					if(Oy < (rect.Width() - DH -1 -Y))  Oy = rect.Width()- DH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//horizontal scroll bar position
					scrollH = abs(Oy + Y) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_all ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_all ;
					}
				}
			//------------------------------------------------------------------+
			}else{
			//------------------------------------------------------------------+
				//angle ZERO
				//new zoomed dimensions
				DW = _pictureW ;
				DH = _pictureH ;
				X = (rect.Width() - DW) / 2 ;
				Y = (rect.Height() - DH) / 2;

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = -1*Oy ;
				Oy = temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(_pictureW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(X + Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_all ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_all ;
					}
				};//else, image less than window

				//VERTICAL
				if(_pictureH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;
					
					//vertical scroll bar position
					scrollV = abs(Y + Oy) ;	

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_all ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_all ;
					}
				}
			//------------------------------------------------------------------+
			};//end else
		}else if(constraintType == 2)//constraint height 
		{
			//do the job
zoom_constraint_height:
		;
			CRect rect ;
			GetClientRect(this->m_hwnd, &rect) ;

			if(angle == 0)
			{
			//--------------------------------------------------------------+
			//rotated ZERO
				/*DH=rect.Height() ;
				DW=(DH*_pictureW)/_pictureH ;*/
				DW = _pictureW ;
				DH = _pictureH ;
				X=(rect.Width()  - DW) / 2;  
				Y=(rect.Height() - DH) / 2;  

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = -1*Oy ;
				Oy = temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(_pictureW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(X + Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_height;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_height ;
					}
				};//else, image less than window

				//VERTICAL
				if(_pictureH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//vertical scroll bar position
					scrollV = abs(Y + Oy) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_height ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_height ;
					}
				}
			//--------------------------------------------------------------+
			}else if(angle == 90)
			{
			//--------------------------------------------------------------+
			//rotated 90
				/*DW=rect.Height();			
				DH=(DW*_pictureH)/_pictureW;*/
				DW = _pictureW ;
				DH = _pictureH ;
				X = (rect.Height() - DW) / 2 ;
				Y = -1*DH -1*(rect.Width() - DH)/2 ;

				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = -1*Oy ;
				Oy = temp ;

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(_pictureW > rect.Height())
				{//scroll offset							
					if(Ox < (rect.Height() - DW -1 - X)) 
						Ox = rect.Height() - DW -1 - X ;
					if(Ox > abs(X) ) 
						Ox = abs(X) ;
					
					//vertical scroll bar position
					scrollV = abs(X + Ox) ;	

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_height ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_height ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(_pictureH > rect.Width())
				{//scroll offset				
					if(Oy > (-1)*DH + (DH - rect.Width()-1) - Y)
						Oy = (-1)*DH + (DH - rect.Width()-1) - Y ;
					if(Oy < (-1)*DH - Y) 
						Oy = (-1)*DH - Y ;

					//horizontal scroll bar position
					scrollH = abs(Oy + DH + Y) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_height;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_height ;
					}
				}
			//--------------------------------------------------------------+
			}else if(angle == 180)
			{
			//--------------------------------------------------------------+
			//rotated 180
				/*DH=rect.Height() ;					
				DW=(DH*_pictureW)/_pictureH ;*/
				DW = _pictureW ;
				DH = _pictureH ;
				X = -1*DW - (rect.Width() - DW) / 2 ;
				Y = -1*DH - (rect.Height() - DH) /2 ;

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = -1*Oy ;
				Oy = temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(_pictureW > rect.Width())
				{//scroll offset							
					if(Ox > (-1)*DW + (DW - rect.Width()-1) - X)
						Ox = (-1)*DW + (DW - rect.Width()-1) - X ;
					if(Ox < (-1)*DW - X) 
						Ox = (-1)*DW - X ;
					
					//horizontal scroll bar position
					scrollH = abs(Ox + DW + X) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_height;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_height ;
					}
				};//else, image less than window

				//VERTICAL
				if(_pictureH > rect.Height())
				{//scroll offset				
					if(Oy >	(-1)*DH + (DH - rect.Height()-1) - Y)
						Oy = (-1)*DH + (DH - rect.Height()-1) - Y ;
					if(Oy < (-1)*DH - Y) 
						Oy = (-1)*DH - Y ;

					//vertical scroll bar position
					scrollV = abs(Oy + DH + Y) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_height ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_height ;
					}
				}
			//--------------------------------------------------------------+
			}else if(angle == 270)
			{
			//--------------------------------------------------------------+
			//rotated 270
				/*DW=rect.Height();			
				DH=(DW*_pictureH)/_pictureW;*/
				DW = _pictureW ;
				DH = _pictureH ;
				X = -1*DW - (rect.Height() - DW) /2 ;
				Y = (rect.Width() - DH) / 2 ;

				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = -1*Oy ;
				Oy = temp ;

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(_pictureW > rect.Height())
				{//scroll offset							
					if(Ox >	(-1)*DW + (DW - rect.Height()-1) - X)
						Ox = (-1)*DW + (DW - rect.Height()-1) - X ;
					if(Ox < (-1)*DW - X) 
						Ox = (-1)*DW - X ;
					
					//vertical scroll bar position
					scrollV = abs(Ox + DW + X) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_height ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_height ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(_pictureH > rect.Width())
				{//scroll offset				
					if(Oy < (rect.Width() - DH -1 -Y))  Oy = rect.Width()- DH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//horizontal scroll bar position
					scrollH = abs(Oy + Y) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_height;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_height ;
					}
				}
			//--------------------------------------------------------------+
			}else {
			//--------------------------------------------------------------+
			//default - rotated ZERO
				/*DH=rect.Height() ;				
				DW=(DH*_pictureW)/_pictureH ;*/
				DW = _pictureW ;
				DH = _pictureH ;
				X = (rect.Width() - DW) / 2 ;
				Y = (rect.Height() - DH) / 2;

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = -1*Oy ;
				Oy = temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(_pictureW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(X + Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_height;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_height ;
					}
				};//else, image less than window

				//VERTICAL
				if(_pictureH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//vertical scroll bar position
					scrollV = abs(Y + Oy) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_height ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_height ;
					}
				}
			//--------------------------------------------------------------+
			};//end else
		}else if(constraintType == 3)//constraint width
		{
			//do the job
zoom_constraint_width :
		;
			CRect rect ;
			GetClientRect(this->m_hwnd, &rect) ;
			
			if(angle == 0)
			{
			//---------------------------------------------------------------+
			//rotated 0
				/*DW = rect.Width() ;
				DH = (DW*_pictureH) / _pictureW ;*/
				DW = _pictureW ;
				DH = _pictureH ;
				X=(rect.Width()  - DW ) / 2;  
				Y=(rect.Height() - DH ) / 2;  

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = -1*Oy ;
				Oy = temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(_pictureW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(X + Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_width;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_width ;
					}
				};//else, image less than window

				//VERTICAL
				if(_pictureH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//vertical scroll bar position
					scrollV = abs(Y + Oy) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_width ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_width ;
					}
				}
			//---------------------------------------------------------------+
			}else if(angle == 90)
			{
			//---------------------------------------------------------------+
			//rotated 90
				/*DH = rect.Width() ;
				DW = (DH*_pictureW) / _pictureH ;*/
				DW = _pictureW ;
				DH = _pictureH ;
				X = (rect.Height() - DW) / 2 ;
				Y = -1*DH -1*(rect.Width() - DH)/2 ;

				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = -1*Oy ;
				Oy = temp ;

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(_pictureW > rect.Height())
				{//scroll offset							
					if(Ox < (rect.Height() - _pictureW -1-X)) Ox = rect.Height()- _pictureW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//vertical scroll bar position
					scrollV = abs(X + Ox) ;	

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_width ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_width ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(_pictureH > rect.Width())
				{//scroll offset				
					if(Oy > (-1)*DH + (DH - rect.Width()-1) - Y)
						Oy = (-1)*DH + (DH - rect.Width()-1) - Y ;
					if(Oy < (-1)*DH - Y) 
						Oy = (-1)*DH - Y ;

					//horizontal scroll bar position
					scrollH = abs(Oy + DH + Y) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_width;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_width ;
					}
				}
			//---------------------------------------------------------------+
			}else if(angle == 180)
			{
			//---------------------------------------------------------------+
			//rotated 180
				/*DW=rect.Width();
				DH=(DW*_pictureH)/_pictureW;*/
				DW = _pictureW ;
				DH = _pictureH ;
				X = -1*DW - (rect.Width() - DW) / 2 ;
				Y = -1*DH - (rect.Height() - DH) /2 ;

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = -1*Oy ;
				Oy = temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(_pictureW > rect.Width())
				{//scroll offset							
					if(Ox > (-1)*DW + (DW - rect.Width()-1) - X)
						Ox = (-1)*DW + (DW - rect.Width()-1) - X ;
					if(Ox < (-1)*DW - X) 
						Ox = (-1)*DW - X ;
					
					//horizontal scroll bar position
					scrollH = abs(Ox + DW + X) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_width;
					}

				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_width ;
					}
				};//else, image less than window

				//VERTICAL
				if(_pictureH > rect.Height())
				{//scroll offset				
					if(Oy >	(-1)*DH + (DH - rect.Height()-1) - Y)
						Oy = (-1)*DH + (DH - rect.Height()-1) - Y ;
					if(Oy < (-1)*DH - Y) 
						Oy = (-1)*DH - Y ;

					//vertical scroll bar position
					scrollV = abs(Oy + DH + Y) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_width ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_width ;
					}
				}
			//---------------------------------------------------------------+
			}else if(angle == 270)
			{
			//---------------------------------------------------------------+
			//rotated 270
				/*DH=rect.Width() ;
				DW=(DH*_pictureW)/_pictureH ;*/
				DW = _pictureW ;
				DH = _pictureH ;
				X = -1*DW - (rect.Height() - DW) /2 ;
				Y = (rect.Width() - DH) / 2 ;

				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = -1*Oy ;
				Oy = temp ;

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(_pictureW > rect.Height())
				{//scroll offset							
					if(Ox >	(-1)*DW + (DW - rect.Height()-1) - X)
						Ox = (-1)*DW + (DW - rect.Height()-1) - X ;
					if(Ox < (-1)*DW - X) 
						Ox = (-1)*DW - X ;
					
					//vertical scroll bar position
					scrollV = abs(Ox + DW + X) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_width ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_width ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(_pictureH > rect.Width())
				{//scroll offset				
					if(Oy < (rect.Width() - DH -1 -Y))  Oy = rect.Width()- DH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//horizontal scroll bar position
					scrollH = abs(Oy + Y) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_width;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_width ;
					}
				}
			//---------------------------------------------------------------+
			}else {
			//---------------------------------------------------------------+	
			//default 
				/*DW=rect.Width();
				DH=(DW*_pictureH)/_pictureW;*/
				DW = _pictureW ;
				DH = _pictureH ;
				X = (rect.Width() - DW) / 2 ;
				Y = (rect.Height() - DH) / 2;

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = -1*Oy ;
				Oy = temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(_pictureW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(X + Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_width;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_width ;
					}
				};//else, image less than window

				//VERTICAL
				if(_pictureH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;
					
					//vertical scroll bar position
					scrollV = abs(Y + Oy) ;	

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_width ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_width ;
					}
				}
			//---------------------------------------------------------------+	
			}
		}else{//constrant all - best fit - default option
			//do the job
zoom_constraint_all2:
		;
			CRect rect ;
			GetClientRect(this->m_hwnd, &rect) ;
			
			if(angle == 0)
			{
			//------------------------------------------------------------------+
				//angle ZERO
				//new zoomed dimensions
				DH = _pictureH ;
				DW = _pictureW ;
				
				X=(rect.Width()  - DW ) / 2;  
				Y=(rect.Height() - DH ) / 2;  //new positions

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = -1*Oy ;
				Oy = temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(_pictureW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(X + Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_all2;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_all2 ;
					}
				};//else, image less than window

				//VERTICAL
				if(_pictureH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//vertical scroll bar position
					scrollV = abs(Y + Oy) ;	

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_all2 ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_all2 ;
					}
				}
			//------------------------------------------------------------------+
			}else if(angle == 90)
			{	
			//------------------------------------------------------------------+
				//angle 90
				//new zoomed dimensions
				DW = _pictureW ;
				DH = _pictureH ;
				X = (rect.Height() - DW) / 2 ;
				Y = -1*DH -1*(rect.Width() - DH)/2 ;

				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = -1*Oy ;
				Oy = temp ;

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(_pictureW > rect.Height())
				{//scroll offset							
					if(Ox < (rect.Height() - DW -1 - X)) 
						Ox = rect.Height() - DW -1 - X ;
					if(Ox > abs(X) ) 
						Ox = abs(X) ;
					
					//vertical scroll bar position
					scrollV = abs(X + Ox) ;	

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_all2 ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_all2 ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(_pictureH > rect.Width())
				{//scroll offset				
					if(Oy > (-1)*DH + (DH - rect.Width()-1) - Y)
						Oy = (-1)*DH + (DH - rect.Width()-1) - Y ;
					if(Oy < (-1)*DH - Y) 
						Oy = (-1)*DH - Y ;

					//horizontal scroll bar position
					scrollH = abs(Oy + DH + Y) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_all2;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_all2 ;
					}
				}
			//------------------------------------------------------------------+
			}else if(angle == 180)
			{
			//------------------------------------------------------------------+
				//angle 180
				//new zoomed dimensions
				DW = _pictureW ;
				DH = _pictureH ;
				X = -1*DW - (rect.Width() - DW) / 2 ;
				Y = -1*DH - (rect.Height() - DH) /2 ;
				
				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = -1*Oy ;
				Oy = temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(_pictureW > rect.Width())
				{//scroll offset							
					if(Ox > (-1)*DW + (DW - rect.Width()-1) - X)
						Ox = (-1)*DW + (DW - rect.Width()-1) - X ;
					if(Ox < (-1)*DW - X) 
						Ox = (-1)*DW - X ;
					
					//horizontal scroll bar position
					scrollH = abs(Ox + DW + X) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;

					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_all2;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_all2 ;
					}
				};//else, image less than window

				//VERTICAL
				if(_pictureH > rect.Height())
				{//scroll offset				
					if(Oy >	(-1)*DH + (DH - rect.Height()-1) - Y)
						Oy = (-1)*DH + (DH - rect.Height()-1) - Y ;
					if(Oy < (-1)*DH - Y) 
						Oy = (-1)*DH - Y ;

					//vertical scroll bar position
					scrollV = abs(Oy + DH + Y) ;				


					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_all2 ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_all2 ;
					}
				}
			//------------------------------------------------------------------+
			}else if(angle == 270)
			{
			//------------------------------------------------------------------+
				//angle 270
				//new zoomed dimensions
				DW = _pictureW ;
				DH = _pictureH ;
				X = -1*DW - (rect.Height() - DW) /2 ;
				Y = (rect.Width() - DH) / 2 ;
				
				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = -1*Oy ;
				Oy = temp ;

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(_pictureW > rect.Height())
				{//scroll offset							
					if(Ox >	(-1)*DW + (DW - rect.Height()-1) - X)
						Ox = (-1)*DW + (DW - rect.Height()-1) - X ;
					if(Ox < (-1)*DW - X) 
						Ox = (-1)*DW - X ;
					
					//vertical scroll bar position
					scrollV = abs(Ox + DW + X) ;	

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_all2 ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_all2 ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(_pictureH > rect.Width())
				{//scroll offset				
					if(Oy < (rect.Width() - DH -1 -Y))  Oy = rect.Width()- DH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//horizontal scroll bar position
					scrollH = abs(Oy + Y) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_all2;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_all2 ;
					}
				}

			//------------------------------------------------------------------+
			}else{
			//------------------------------------------------------------------+
				//angle ZERO
				//new zoomed dimensions
				DW = _pictureW ;
				DH = _pictureH ;
				X = (rect.Width() - DW) / 2 ;
				Y = (rect.Height() - DH) / 2;

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = -1*Oy ;
				Oy = temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(_pictureW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(X + Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_all2;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_all2 ;
					}
				};//else, image less than window

				//VERTICAL
				if(_pictureH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//vertical scroll bar position
					scrollV = abs(Y + Oy) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_all2 ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_all2 ;
					}
				}
			//------------------------------------------------------------------+
			};//end else
		};//end else default - constraint all - best fit				
	};//end else- test image , image is zoomed

	//the image was calculated
	b_computeImage = false ;

	//erase the background , display the image
	mvShowImage();
	//finish mvRotateLeft()
	

}


//It modifies angle value with 90 degrees clockwise direction
//mvRotateRight calculate image coordinates and  display the image.
void mvImage::mvRotateRight()
{
	//indicate an image is computed
	b_computeImage = true ;

	//modify current angle to new desired value
	angle == 270 ? angle = 0 : angle += 90 ;
	//test if zoom functions modifyed already the image
	//the image is not zoomed - algorith like in 
	//mvConstraint... functions (Nothing, All, Height, Width)
	if(zoom_status == false)
	{
		//check the constraint type of image displaing mode in window		
		if(constraintType == 0)//no  constraint 
		{
			//do the job
constraint_nothing:
		;
			CRect rect ;
			GetClientRect(this->m_hwnd, &rect) ;
			mvGetImageDimensions(&pictureW, &pictureH) ;
			if(angle == 0)
			{
			//------------------------------------------------------------------+
			//angle zero
				X=0; 
				Y=0;
				DW = pictureW ;
				DH = pictureH ;
					
				
				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = Oy ;
				Oy = -1*temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(DW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - DW -1 - X)) Ox = rect.Width()- DW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = DW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, DW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto constraint_nothing ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto constraint_nothing ;
					}

				};//else, image less than window

				//VERTICAL
				if(DH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - DH -1 - Y))  Oy = rect.Height()- DH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;
					
					//vertical scroll bar position
					scrollV = abs(Oy) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = DH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, DH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto constraint_nothing ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto constraint_nothing ;
					}
				}

			//------------------------------------------------------------------+
			}else if(angle == 90)
			{
			//------------------------------------------------------------------+
			//angle 90
				X = 0 ;
				Y = -1*pictureH ;
				DW = pictureW ;
				DH = pictureH ;

				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;				
				int temp = Ox ;
				Ox = Oy ;
				Oy = -1*temp ;

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(DW > rect.Height())
				{//scroll offset							
					if(Ox < (-1)*(DW - rect.Height()- 1) )  
						Ox = (-1)*(DW - rect.Height()- 1) ;
					if(Ox > abs(X))  
						Ox = abs(X) ;
					
					//vertical scroll bar position
					scrollV = abs(Ox) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = DW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, DW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto constraint_nothing ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto constraint_nothing ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(DH > rect.Width())
				{//scroll offset				
					if(Oy > (DH - rect.Width()-1))  Oy = (DH - rect.Width()-1) ;
					if(Oy < 0) Oy = 0 ;

					//horizontal scroll bar position
					scrollH = abs(Oy) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = DH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, DH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto constraint_nothing ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto constraint_nothing ;
					}
				}

			//------------------------------------------------------------------+
			}else if(angle == 180)
			{
			//------------------------------------------------------------------+	
			//angle 180
				X = -1*pictureW  ;
				Y = -1*pictureH  ;
				DW = pictureW ;
				DH = pictureH ;

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = Oy ;
				Oy = -1*temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(DW > rect.Width())
				{//scroll offset							
					if(Ox > (DW - rect.Width()-1))  Ox = (DW - rect.Width()-1) ;
					if(Ox < 0 ) Ox = 0  ;
					
					//horizontal scroll bar position
					scrollH = abs(Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = DW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, DW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto constraint_nothing ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto constraint_nothing ;
					}
				};//else, image less than window

				//VERTICAL
				if(DH > rect.Height())
				{//scroll offset				
					if( Oy > DH - rect.Height() - 1 )
						Oy = DH - rect.Height() - 1 ;
					if(Oy < 0)
						Oy = 0 ;

					//vertical scroll bar position
					scrollV = abs(Oy) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = DH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, DH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto constraint_nothing ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto constraint_nothing ;
					}
				}
			//------------------------------------------------------------------+
			}else if(angle == 270)
			{
			//------------------------------------------------------------------+		
			//angle 270
				X = -1*pictureW ;
				Y = 0 ;
				DW = pictureW ;
				DH = pictureH ;

				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = Oy ;
				Oy = -1*temp ;

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(DW > rect.Height())
				{//scroll offset							
					if( Ox > DW - rect.Height() - 1 )
						Ox = DW - rect.Height() - 1 ;
					if(Ox < 0)
						Ox = 0 ;
					
					//vertical scroll bar position
					scrollV = abs(Ox) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = DW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, DW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto constraint_nothing ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto constraint_nothing ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(DH > rect.Width())
				{//scroll offset				
					if(Oy < (rect.Width() - DH -1 -Y))  Oy = rect.Width()- DH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//horizontal scroll bar position
					scrollH = abs(Oy) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = DH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, DH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto constraint_nothing ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto constraint_nothing ;
					}
				}
			//------------------------------------------------------------------+
			}else
			{
			//------------------------------------------------------------------+
			//angle zero default	
				X=0; 
				Y=0;
				DW = pictureW ;
				DH = pictureH ;
					
				
				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = Oy ;
				Oy = -1*temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(DW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - DW -1 - X)) Ox = rect.Width()- DW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = DW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, DW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto constraint_nothing ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto constraint_nothing ;
					}
				};//else, image less than window

				//VERTICAL
				if(DH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - DH -1 - Y))  Oy = rect.Height()- DH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//vertical scroll bar position
					scrollV = abs(Oy) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = DH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, DH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto constraint_nothing ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto constraint_nothing ;
					}
				}
			};//else , default angle zero
			//------------------------------------------------------------------+
		}else if(constraintType == 1)//constraint all - best fit
		{			
			//because of image constraint 'best fit' was performed previously
			//so the scroll bars are hidden
			//do the job
//constraint_all :
//		;
			//scroll bars have been hidden before.
			CRect rect ;
			GetClientRect(this->m_hwnd, &rect) ;
			mvGetImageDimensions(&pictureW, &pictureH) ;
			if(angle == 0)
			{
			//------------------------------------------------------------------+
				//angle ZERO
				DH=rect.Height() ;
				DW=(DH*pictureW)/pictureH ;				
				if(DW>rect.Width())
				{
					DW=rect.Width();
					DH=(DW*pictureH)/pictureW;
				};

				
				X=(rect.Width()  - DW ) / 2;  
				Y=(rect.Height() - DH ) / 2;  //new positions
				//scrolls bars offset
				Ox = 0 ;  Oy = 0 ;
				//don't need to put scroll bars in window
			//------------------------------------------------------------------+
			}else if(angle == 90)
			{	
			//------------------------------------------------------------------+
				//angle 90
				DW=rect.Height();			
				DH=(DW*pictureH)/pictureW;		
				if(DH>rect.Width())
				{
					DH=rect.Width() ;
					DW=(DH*pictureW)/pictureH ;	
				};
				X = (rect.Height() - DW) / 2 ;
				Y = -1*DH -1*(rect.Width() - DH)/2 ;
				//scrolls bars offset
				Ox = 0 ;  Oy = 0 ;
				//don't need to put scroll bars in window
			//------------------------------------------------------------------+
			}else if(angle == 180)
			{
			//------------------------------------------------------------------+
				//angle 180
				DH=rect.Height() ;				//height of image
				DW=(DH*pictureW)/pictureH ;		//width of image
				if(DW>rect.Width())
				{
					DW=rect.Width();
					DH=(DW*pictureH)/pictureW;
				}
				X = -1*DW - (rect.Width() - DW) / 2 ;
				Y = -1*DH - (rect.Height() - DH) /2 ;
				//scrolls bars offset
				Ox = 0 ;  Oy = 0 ;
				//don't need to put scroll bars in window
			//------------------------------------------------------------------+
			}else if(angle == 270)
			{
			//------------------------------------------------------------------+
				//angle 270
				DW=rect.Height();			
				DH=(DW*pictureH)/pictureW;	
				
				if(DH>rect.Width())
				{
					DH=rect.Width() ;
					DW=(DH*pictureW)/pictureH ;	
				};
				X = -1*DW - (rect.Height() - DW) /2 ;
				Y = (rect.Width() - DH) / 2 ;
				//scrolls bars offset
				Ox = 0 ;  Oy = 0 ;
				//don't need to put scroll bars in window
			//------------------------------------------------------------------+
			}else{
			//------------------------------------------------------------------+
				//angle ZERO
				DH=rect.Height() ;
				DW=(DH*pictureW)/pictureH ;				
				if(DW>rect.Width())
				{
					DW=rect.Width();
					DH=(DW*pictureH)/pictureW;
				};
				X = (rect.Width() - DW) / 2 ;
				Y = (rect.Height() - DH) / 2;
				//scrolls bars offset
				Ox = 0 ;  Oy = 0 ;
				//don't need to put scroll bars in window
			//------------------------------------------------------------------+
			};//end else
		//------------------------------------------------------------------+
		}else if(constraintType == 2)//constraint height 
		{
			//do the job
constraint_height:
		;
			CRect rect ;
			GetClientRect(this->m_hwnd, &rect) ;
			mvGetImageDimensions(&pictureW, &pictureH) ;
			if(angle == 0)
			{
			//--------------------------------------------------------------+
			//rotated ZERO
				DH=rect.Height() ;
				DW=(DH*pictureW)/pictureH ;				
				X=(rect.Width()  - DW) / 2;  
				Y=(rect.Height() - DH) / 2;  
	
				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = Oy ;
				Oy = -1*temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(DW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - DW -1 - X)) Ox = rect.Width()- DW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(X + Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = DW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, DW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto constraint_height ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto constraint_height ;
					}
				};//else, image less than window

				//VERTICAL
				if(DH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - DH -1 - Y))  Oy = rect.Height()- DH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//vertical scroll bar position
					scrollV = abs(Y + Oy) ;	

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = DH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, DH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto constraint_height ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto constraint_height ;
					}
				}
			//--------------------------------------------------------------+
			}else if(angle == 90)
			{
			//--------------------------------------------------------------+
			//rotated 90
				DW=rect.Height();			
				DH=(DW*pictureH)/pictureW;	
				X = (rect.Height() - DW) / 2 ;
				Y = -1*DH -1*(rect.Width() - DH)/2 ;


				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = Oy ;
				Oy = -1*temp ;

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(DW > rect.Height())
				{//scroll offset							
					if(Ox < (rect.Height() - DW -1-X)) Ox = rect.Height()- DW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//vertical scroll bar position
					scrollV = abs(X + Ox) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = DW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, DW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto constraint_height ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto constraint_height ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(DH > rect.Width())
				{//scroll offset				
					if(Oy > (-1)*DH + (DH - rect.Width()-1) - Y)
						Oy = (-1)*DH + (DH - rect.Width()-1) - Y ;
					if(Oy < (-1)*DH - Y) 
						Oy = (-1)*DH - Y ;

					//horizontal scroll bar position
					scrollH = abs(Oy + DH + Y) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = DH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, DH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto constraint_height ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto constraint_height ;
					}
				}
			//--------------------------------------------------------------+
			}else if(angle == 180)
			{
			//--------------------------------------------------------------+
			//rotated 180
				DH=rect.Height() ;				//height of image
				DW=(DH*pictureW)/pictureH ;		//width of image
				X = -1*DW - (rect.Width() - DW) / 2 ;
				Y = -1*DH - (rect.Height() - DH) /2 ;

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = Oy ;
				Oy = -1*temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(DW > rect.Width())
				{//scroll offset							
					if(Ox > (-1)*DW + (DW - rect.Width()-1) - X)
						Ox = (-1)*DW + (DW - rect.Width()-1) - X ;
					if(Ox < (-1)*DW - X) 
						Ox = (-1)*DW - X ;

					//horizontal scroll bar position
					scrollH = abs(Ox + DW + X) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = DW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, DW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;

					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto constraint_height ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
		
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto constraint_height ;
					}
				};//else, image less than window

				//VERTICAL
				if(DH > rect.Height())
				{//scroll offset				
					if(Oy >	(-1)*DH + (DH - rect.Height()-1) - Y)
						Oy = (-1)*DH + (DH - rect.Height()-1) - Y ;
					if(Oy < (-1)*DH - Y) 
						Oy = (-1)*DH - Y ;

					//vertical scroll bar position
					scrollV = abs(Oy + DH + Y) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = DH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, DH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto constraint_height ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto constraint_height ;
					}
				}
			//--------------------------------------------------------------+
			}else if(angle == 270)
			{
			//--------------------------------------------------------------+
			//rotated 270
				DW=rect.Height();			
				DH=(DW*pictureH)/pictureW;	
				X = -1*DW - (rect.Height() - DW) /2 ;
				Y = (rect.Width() - DH) / 2 ;

				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = Oy ;
				Oy = -1*temp ;

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(DW > rect.Height())
				{//scroll offset							
					if(Ox >	(-1)*DW + (DW - rect.Height()-1) - X)
						Ox = (-1)*DW + (DW - rect.Height()-1) - X ;
					if(Ox < (-1)*DW - X) 
						Ox = (-1)*DW - X ;
					
					//vertical scroll bar position
					scrollV = abs(Ox + DW + X) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = DW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, DW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto constraint_height ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto constraint_height ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(DH > rect.Width())
				{//scroll offset				
					if(Oy < (rect.Width() - DH -1 -Y))  Oy = rect.Width()- DH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//horizontal scroll bar position
					scrollH = abs(Oy + Y) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = DH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, DH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto constraint_height ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto constraint_height ;
					}
				}
			//--------------------------------------------------------------+
			}else {
			//--------------------------------------------------------------+
			//default - rotated ZERO
				DH=rect.Height() ;				//height of image
				DW=(DH*pictureW)/pictureH ;		//width of image
				X = (rect.Width() - DW) / 2 ;
				Y = (rect.Height() - DH) / 2;
			
				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = Oy ;
				Oy = -1*temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(DW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - DW -1 - X)) Ox = rect.Width()- DW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(X + Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = DW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, DW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto constraint_height ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto constraint_height ;
					}
				};//else, image less than window

				//VERTICAL
				if(DH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - DH -1 - Y))  Oy = rect.Height()- DH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//vertical scroll bar position
					scrollV = abs(Y + Oy) ;	

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = DH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, DH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto constraint_height ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto constraint_height ;
					}
				}					
			//--------------------------------------------------------------+
			};//end else
		}else if(constraintType == 3)//constraint width
		{
			//do the job
constraint_width:
		;
			CRect rect ;
			GetClientRect(this->m_hwnd, &rect) ;
			mvGetImageDimensions(&pictureW, &pictureH) ;
			if(angle == 0)
			{
			//---------------------------------------------------------------+
			//rotated 0
				DW = rect.Width() ;
				DH = (DW*pictureH) / pictureW ;
				X=(rect.Width()  - DW ) / 2;  
				Y=(rect.Height() - DH ) / 2;  

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = Oy ;
				Oy = -1*temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(DW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - DW -1 - X)) Ox = rect.Width()- DW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(X + Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = DW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, DW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto constraint_width ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto constraint_width ;
					}
				};//else, image less than window

				//VERTICAL
				if(DH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - DH -1 - Y))  Oy = rect.Height()- DH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//vertical scroll bar position
					scrollV = abs(Y + Oy) ;	

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = DH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, DH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto constraint_width ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto constraint_width ;
					}
				}
			//---------------------------------------------------------------+
			}else if(angle == 90)
			{
			//---------------------------------------------------------------+
			//rotated 90
				DH = rect.Width() ;
				DW = (DH*pictureW) / pictureH ;
				X = (rect.Height() - DW) / 2 ;
				Y = -1*DH -1*(rect.Width() - DH)/2 ;

				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = Oy ;
				Oy = -1*temp ;

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(DW > rect.Height())
				{//scroll offset							
					if(Ox < (rect.Height() - DW -1-X)) Ox = rect.Height()- DW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//vertical scroll bar position
					scrollV = abs(X + Ox) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = DW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, DW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto constraint_width ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto constraint_width ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(DH > rect.Width())
				{//scroll offset				
					if(Oy > (-1)*DH + (DH - rect.Width()-1) - Y)
						Oy = (-1)*DH + (DH - rect.Width()-1) - Y ;
					if(Oy < (-1)*DH - Y) 
						Oy = (-1)*DH - Y ;

					//horizontal scroll bar position
					scrollH = abs(Oy + DH + Y) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = DH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, DH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto constraint_width ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto constraint_width ;
					}
				}
			//---------------------------------------------------------------+
			}else if(angle == 180)
			{
			//---------------------------------------------------------------+
			//rotated 180
				DW=rect.Width();
				DH=(DW*pictureH)/pictureW;
				X = -1*DW - (rect.Width() - DW) / 2 ;
				Y = -1*DH - (rect.Height() - DH) /2 ;

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = Oy ;
				Oy = -1*temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(DW > rect.Width())
				{//scroll offset							
					if(Ox > (-1)*DW + (DW - rect.Width()-1) - X)
						Ox = (-1)*DW + (DW - rect.Width()-1) - X ;
					if(Ox < (-1)*DW - X) 
						Ox = (-1)*DW - X ;
					
					//horizontal scroll bar position
					scrollH = abs(Ox + DW + X) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = DW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, DW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto constraint_width ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto constraint_width ;
					}
				};//else, image less than window

				//VERTICAL
				if(DH > rect.Height())
				{//scroll offset				
					if(Oy >	(-1)*DH + (DH - rect.Height()-1) - Y)
						Oy = (-1)*DH + (DH - rect.Height()-1) - Y ;
					if(Oy < (-1)*DH - Y) 
						Oy = (-1)*DH - Y ;

					//vertical scroll bar position
					scrollV = abs(Oy + DH + Y) ;	

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = DH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, DH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto constraint_width ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto constraint_width ;
					}
				}
			//---------------------------------------------------------------+
			}else if(angle == 270)
			{
			//---------------------------------------------------------------+
			//rotated 270
				DH=rect.Width() ;
				DW=(DH*pictureW)/pictureH ;	
				X = -1*DW - (rect.Height() - DW) /2 ;
				Y = (rect.Width() - DH) / 2 ;
			
				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = Oy ;
				Oy = -1*temp ;

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(DW > rect.Height())
				{//scroll offset							
					if(Ox >	(-1)*DW + (DW - rect.Height()-1) - X)
						Ox = (-1)*DW + (DW - rect.Height()-1) - X ;
					if(Ox < (-1)*DW - X) 
						Ox = (-1)*DW - X ;
					
					//vertical scroll bar position
					scrollV = abs(Ox + DW + X) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = DW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, DW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto constraint_width ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto constraint_width ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(DH > rect.Width())
				{//scroll offset				
					if(Oy < (rect.Width() - DH -1 -Y))  Oy = rect.Width()- DH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//horizontal scroll bar position
					scrollH = abs(Oy + Y) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = DH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, DH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto constraint_width ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto constraint_width ;
					}
				}
			//---------------------------------------------------------------+
			}else {
			//---------------------------------------------------------------+	
			//default 
				DW=rect.Width();
				DH=(DW*pictureH)/pictureW;
				X = (rect.Width() - DW) / 2 ;
				Y = (rect.Height() - DH) / 2;
			
				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = Oy ;
				Oy = -1*temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(DW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - DW -1 - X)) Ox = rect.Width()- DW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(X + Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = DW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, DW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto constraint_width ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto constraint_width ;
					}
				};//else, image less than window

				//VERTICAL
				if(DH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - DH -1 - Y))  Oy = rect.Height()- DH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//vertical scroll bar position
					scrollV = abs(Y + Oy) ;	

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = DH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, DH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto constraint_width ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto constraint_width ;
					}
				}
			//---------------------------------------------------------------+	
			}
			//------------------------------------------------------------------+
		}else{//constrant all - best fit - default option
			//do the job
//constraint_all2:
//		;						
			CRect rect ;
			GetClientRect(this->m_hwnd, &rect) ;
			mvGetImageDimensions(&pictureW, &pictureH) ;
			if(angle == 0)
			{
			//------------------------------------------------------------------+
				//angle ZERO
				DH=rect.Height() ;
				DW=(DH*pictureW)/pictureH ;				
				if(DW>rect.Width())
				{
					DW=rect.Width();
					DH=(DW*pictureH)/pictureW;
				};

				
				X=(rect.Width()  - DW ) / 2;  
				Y=(rect.Height() - DH ) / 2;  //new positions
				//scrolls bars offset
				Ox = 0 ;  Oy = 0 ;
				//don't need to put scroll bars in window
			//------------------------------------------------------------------+
			}else if(angle == 90)
			{	
			//------------------------------------------------------------------+
				//angle 90
				DW=rect.Height();			
				DH=(DW*pictureH)/pictureW;		
				if(DH>rect.Width())
				{
					DH=rect.Width() ;
					DW=(DH*pictureW)/pictureH ;	
				};
				X = (rect.Height() - DW) / 2 ;
				Y = -1*DH -1*(rect.Width() - DH)/2 ;
				//scrolls bars offset
				Ox = 0 ;  Oy = 0 ;
				//don't need to put scroll bars in window
			//------------------------------------------------------------------+
			}else if(angle == 180)
			{
			//------------------------------------------------------------------+
				//angle 180
				DH=rect.Height() ;				//height of image
				DW=(DH*pictureW)/pictureH ;		//width of image
				if(DW>rect.Width())
				{
					DW=rect.Width();
					DH=(DW*pictureH)/pictureW;
				}
				X = -1*DW - (rect.Width() - DW) / 2 ;
				Y = -1*DH - (rect.Height() - DH) /2 ;
				//scrolls bars offset
				Ox = 0 ;  Oy = 0 ;
				//don't need to put scroll bars in window
			//------------------------------------------------------------------+
			}else if(angle == 270)
			{
			//------------------------------------------------------------------+
				//angle 270
				DW=rect.Height();			
				DH=(DW*pictureH)/pictureW;	
				
				if(DH>rect.Width())
				{
					DH=rect.Width() ;
					DW=(DH*pictureW)/pictureH ;	
				};
				X = -1*DW - (rect.Height() - DW) /2 ;
				Y = (rect.Width() - DH) / 2 ;
				//scrolls bars offset
				Ox = 0 ;  Oy = 0 ;
				//don't need to put scroll bars in window
			//------------------------------------------------------------------+
			}else{
			//------------------------------------------------------------------+
				//angle ZERO
				DH=rect.Height() ;
				DW=(DH*pictureW)/pictureH ;				
				if(DW>rect.Width())
				{
					DW=rect.Width();
					DH=(DW*pictureH)/pictureW;
				};
				X = (rect.Width() - DW) / 2 ;
				Y = (rect.Height() - DH) / 2;
				//scrolls bars offset
				Ox = 0 ;  Oy = 0 ;
				//don't need to put scroll bars in window
			//------------------------------------------------------------------+
			};//end else
		};//end else default - constraint all - best fit

	}//end if, image is not zoomed 
	else{//zoom_status = true, image is zoomed
		//the image is zoomed - algorith like in 
		//mvZoom... functions (In, Out)
		//check the constraint type of image displaing mode in window
		
		mvGetImageDimensions(&pictureW, &pictureH) ;

		int _pictureH = (int) ((pictureH*proportion)/100.) ;
		int _pictureW = (int) ((pictureW*proportion)/100.) ;	
		 
		if(constraintType == 0)//no  constraint
		{
			//do the job
zoom_constraint_nothing:
		;
			CRect rect ;
			GetClientRect(this->m_hwnd, &rect) ;
			
			if(angle == 0)
			{
			//------------------------------------------------------------------+
			//angle zero
				X=0; 
				Y=0;
				DW = _pictureW ;
				DH = _pictureH ;

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = Oy ;
				Oy = -1*temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(_pictureW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - DW -1 - X)) 
						Ox = rect.Width()- DW -1-X ;
					if(Ox > abs(X)) 
						Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_nothing ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_nothing ;
					}
				};//else, image less than window

				//VERTICAL
				if(_pictureH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - DH -1 - Y)) Oy = rect.Height()- DH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//vertical scroll bar position
					scrollV = abs(Oy) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_nothing ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_nothing ;
					}
				}
	
			//------------------------------------------------------------------+
			}else if(angle == 90)
			{
			//------------------------------------------------------------------+
			//angle 90
				X = 0 ;
				Y = -1*_pictureH ;
				DW = _pictureW ;
				DH = _pictureH ;

				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = Oy ;
				Oy = -1*temp ;

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(_pictureW > rect.Height())
				{//scroll offset							
					if(Ox < (-1)*(DW - rect.Height()- 1) )  
						Ox = (-1)*(DW - rect.Height()- 1) ;
					if(Ox > 0) 
						Ox = 0 ;
					
					//vertical scroll bar position
					scrollV = abs(Ox) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_nothing ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_nothing ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(_pictureH > rect.Width())
				{//scroll offset				
					if(Oy > (DH - rect.Width()-1))  Oy = (DH - rect.Width()-1) ;
					if(Oy < 0) Oy = 0 ;

					//horizontal scroll bar position
					scrollH = abs(Oy) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_nothing ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_nothing ;
					}
				}
			//------------------------------------------------------------------+
			}else if(angle == 180)
			{
			//------------------------------------------------------------------+	
			//angle 180
				X = -1*_pictureW  ;
				Y = -1*_pictureH  ;
				DW = _pictureW ;
				DH = _pictureH ;

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = Oy ;
				Oy = -1*temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(_pictureW > rect.Width())
				{//scroll offset							
					if(Ox > (DW - rect.Width()-1))  Ox = (DW - rect.Width()-1) ;
					if(Ox < 0 ) Ox = 0  ;
					
					//horizontal scroll bar position
					scrollH = abs(Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;

					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_nothing ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_nothing ;
					}
				};//else, image less than window

				//VERTICAL
				if(_pictureH > rect.Height())
				{//scroll offset				
					if( Oy > DH - rect.Height() - 1 )
						Oy = DH - rect.Height() - 1 ;
					if(Oy < 0)
						Oy = 0 ;

					//vertical scroll bar position
					scrollV = abs(Oy) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_nothing ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_nothing ;
					}
				}
			//------------------------------------------------------------------+
			}else if(angle == 270)
			{
			//------------------------------------------------------------------+		
			//angle 270
				X = -1*_pictureW ;
				Y = 0 ;
				DW = _pictureW ;
				DH = _pictureH ;

				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = Oy ;
				Oy = -1*temp ;

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(_pictureW > rect.Height())
				{//scroll offset							
					if( Ox > DW - rect.Height() - 1 )
						Ox = DW - rect.Height() - 1 ;
					if(Ox < 0)
						Ox = 0 ;
					
					//vertical scroll bar position
					scrollV = abs(Ox) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_nothing ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_nothing ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(_pictureH > rect.Width())
				{//scroll offset				
					if(Oy < (rect.Width() - DH -1 -Y))  Oy = rect.Width()- DH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//horizontal scroll bar position
					scrollH = abs(Oy) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_nothing ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_nothing ;
					}
				}
			//------------------------------------------------------------------+
			}else
			{
			//------------------------------------------------------------------+
			//angle zero default
				X = 0 ;
				Y = 0 ;
				DW = _pictureW ;
				DH = _pictureH ;

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = Oy ;
				Oy = -1*temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(_pictureW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_nothing ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_nothing ;
					}
				};//else, image less than window

				//VERTICAL
				if(_pictureH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;
			
					//vertical scroll bar position
					scrollV = abs(Oy) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_nothing ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_nothing ;
					}
				}
			//------------------------------------------------------------------+
			}
		}else if(constraintType == 1)//constraint all - best fit
		{
			//do the job
zoom_constraint_all:
		;
			CRect rect ;
			GetClientRect(this->m_hwnd, &rect) ;
			
			if(angle == 0)
			{
			//------------------------------------------------------------------+
				//angle ZERO
				//new zoomed dimensions
				DH = _pictureH ;
				DW = _pictureW ;
				
				X=(rect.Width()  - DW ) / 2;  
				Y=(rect.Height() - DH ) / 2;  //new positions

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = Oy ;
				Oy = -1*temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(_pictureW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(X + Ox) ;


					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_all ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_all ;
					}
				};//else, image less than window

				//VERTICAL
				if(_pictureH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//vertical scroll bar position
					scrollV = abs(Y + Oy) ;				


					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_all ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_all ;
					}
				}
			//------------------------------------------------------------------+
			}else if(angle == 90)
			{	
			//------------------------------------------------------------------+
				//angle 90
				//new zoomed dimensions
				DW = _pictureW ;
				DH = _pictureH ;
				X = (rect.Height() - DW) / 2 ;
				Y = -1*DH - (rect.Width() - DH)/2 ;

				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = Oy ;
				Oy = -1*temp ;

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(_pictureW > rect.Height())
				{//scroll offset							
					if(Ox < (rect.Height() - _pictureW -1-X)) Ox = rect.Height()- _pictureW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//vertical scroll bar position
					scrollV = abs(X + Ox) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_all ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_all ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(_pictureH > rect.Width())
				{//scroll offset				
					if(Oy > (-1)*DH + (DH - rect.Width()-1) - Y)
						Oy = (-1)*DH + (DH - rect.Width()-1) - Y ;
					if(Oy < (-1)*DH - Y) 
						Oy = (-1)*DH - Y ;
					
					//horizontal scroll bar position
					scrollH = abs(Oy + DH + Y) ;


					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_all ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_all ;
					}
				}
			//------------------------------------------------------------------+
			}else if(angle == 180)
			{
			//------------------------------------------------------------------+
				//angle 180
				//new zoomed dimensions
				DW = _pictureW ;
				DH = _pictureH ;
				X = -1*DW - (rect.Width() - DW) / 2 ;
				Y = -1*DH - (rect.Height() - DH) /2 ;

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = Oy ;
				Oy = -1*temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(_pictureW > rect.Width())
				{//scroll offset							
					if(Ox > (-1)*DW + (DW - rect.Width()-1) - X)
						Ox = (-1)*DW + (DW - rect.Width()-1) - X ;
					if(Ox < (-1)*DW - X) 
						Ox = (-1)*DW - X ;
					
					//horizontal scroll bar position
					scrollH = abs(Ox + DW + X) ;


					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_all ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_all ;
					}
				};//else, image less than window

				//VERTICAL
				if(_pictureH > rect.Height())
				{//scroll offset				
					if(Oy >	(-1)*DH + (DH - rect.Height()-1) - Y)
						Oy = (-1)*DH + (DH - rect.Height()-1) - Y ;
					if(Oy < (-1)*DH - Y) 
						Oy = (-1)*DH - Y ;

					//vertical scroll bar position
					scrollV = abs(Oy + DH + Y) ;	

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_all ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_all ;
					}
				}
			//------------------------------------------------------------------+
			}else if(angle == 270)
			{
			//------------------------------------------------------------------+
				//angle 270
				//new zoomed dimensions
				DW = _pictureW ;
				DH = _pictureH ;
				X = -1*DW - (rect.Height() - DW) /2 ;
				Y = (rect.Width() - DH) / 2 ;

				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = Oy ;
				Oy = -1*temp ;

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(_pictureW > rect.Height())
				{//scroll offset							
					if(Ox >	(-1)*DW + (DW - rect.Height()-1) - X)
						Ox = (-1)*DW + (DW - rect.Height()-1) - X ;
					if(Ox < (-1)*DW - X) 
						Ox = (-1)*DW - X ;
					
					//vertical scroll bar position
					scrollV = abs(Ox + DW + X) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_all ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_all ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(_pictureH > rect.Width())
				{//scroll offset				
					if(Oy < (rect.Width() - DH -1 -Y))  Oy = rect.Width()- DH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//horizontal scroll bar position
					scrollH = abs(Oy + Y) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_all ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_all ;
					}
				}
			//------------------------------------------------------------------+
			}else{
			//------------------------------------------------------------------+
				//angle ZERO
				//new zoomed dimensions
				DW = _pictureW ;
				DH = _pictureH ;
				X = (rect.Width() - DW) / 2 ;
				Y = (rect.Height() - DH) / 2;

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = Oy ;
				Oy = -1*temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(_pictureW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(X + Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_all ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_all ;
					}
				};//else, image less than window

				//VERTICAL
				if(_pictureH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;
					
					//vertical scroll bar position
					scrollV = abs(Y + Oy) ;	

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_all ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_all ;
					}
				}
			//------------------------------------------------------------------+
			};//end else
		}else if(constraintType == 2)//constraint height 
		{
			//do the job
zoom_constraint_height:
		;
			CRect rect ;
			GetClientRect(this->m_hwnd, &rect) ;

			if(angle == 0)
			{
			//--------------------------------------------------------------+
			//rotated ZERO
				/*DH=rect.Height() ;
				DW=(DH*_pictureW)/_pictureH ;*/
				DW = _pictureW ;
				DH = _pictureH ;
				X=(rect.Width()  - DW) / 2;  
				Y=(rect.Height() - DH) / 2;  

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = Oy ;
				Oy = -1*temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(_pictureW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(X + Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_height;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_height ;
					}
				};//else, image less than window

				//VERTICAL
				if(_pictureH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//vertical scroll bar position
					scrollV = abs(Y + Oy) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_height ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_height ;
					}
				}
			//--------------------------------------------------------------+
			}else if(angle == 90)
			{
			//--------------------------------------------------------------+
			//rotated 90
				/*DW=rect.Height();			
				DH=(DW*_pictureH)/_pictureW;*/
				DW = _pictureW ;
				DH = _pictureH ;
				X = (rect.Height() - DW) / 2 ;
				Y = -1*DH -1*(rect.Width() - DH)/2 ;

				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = Oy ;
				Oy = -1*temp ;

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(_pictureW > rect.Height())
				{//scroll offset							
					if(Ox < (rect.Height() - DW -1 - X)) 
						Ox = rect.Height() - DW -1 - X ;
					if(Ox > abs(X) ) 
						Ox = abs(X) ;
					
					//vertical scroll bar position
					scrollV = abs(X + Ox) ;	

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_height ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_height ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(_pictureH > rect.Width())
				{//scroll offset				
					if(Oy > (-1)*DH + (DH - rect.Width()-1) - Y)
						Oy = (-1)*DH + (DH - rect.Width()-1) - Y ;
					if(Oy < (-1)*DH - Y) 
						Oy = (-1)*DH - Y ;

					//horizontal scroll bar position
					scrollH = abs(Oy + DH + Y) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_height;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_height ;
					}
				}
			//--------------------------------------------------------------+
			}else if(angle == 180)
			{
			//--------------------------------------------------------------+
			//rotated 180
				/*DH=rect.Height() ;					
				DW=(DH*_pictureW)/_pictureH ;*/
				DW = _pictureW ;
				DH = _pictureH ;
				X = -1*DW - (rect.Width() - DW) / 2 ;
				Y = -1*DH - (rect.Height() - DH) /2 ;

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = Oy ;
				Oy = -1*temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(_pictureW > rect.Width())
				{//scroll offset							
					if(Ox > (-1)*DW + (DW - rect.Width()-1) - X)
						Ox = (-1)*DW + (DW - rect.Width()-1) - X ;
					if(Ox < (-1)*DW - X) 
						Ox = (-1)*DW - X ;
					
					//horizontal scroll bar position
					scrollH = abs(Ox + DW + X) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_height;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_height ;
					}
				};//else, image less than window

				//VERTICAL
				if(_pictureH > rect.Height())
				{//scroll offset				
					if(Oy >	(-1)*DH + (DH - rect.Height()-1) - Y)
						Oy = (-1)*DH + (DH - rect.Height()-1) - Y ;
					if(Oy < (-1)*DH - Y) 
						Oy = (-1)*DH - Y ;

					//vertical scroll bar position
					scrollV = abs(Oy + DH + Y) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_height ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_height ;
					}
				}
			//--------------------------------------------------------------+
			}else if(angle == 270)
			{
			//--------------------------------------------------------------+
			//rotated 270
				/*DW=rect.Height();			
				DH=(DW*_pictureH)/_pictureW;*/
				DW = _pictureW ;
				DH = _pictureH ;
				X = -1*DW - (rect.Height() - DW) /2 ;
				Y = (rect.Width() - DH) / 2 ;

				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = Oy ;
				Oy = -1*temp ;

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(_pictureW > rect.Height())
				{//scroll offset							
					if(Ox >	(-1)*DW + (DW - rect.Height()-1) - X)
						Ox = (-1)*DW + (DW - rect.Height()-1) - X ;
					if(Ox < (-1)*DW - X) 
						Ox = (-1)*DW - X ;
					
					//vertical scroll bar position
					scrollV = abs(Ox + DW + X) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_height ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_height ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(_pictureH > rect.Width())
				{//scroll offset				
					if(Oy < (rect.Width() - DH -1 -Y))  Oy = rect.Width()- DH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//horizontal scroll bar position
					scrollH = abs(Oy + Y) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_height;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_height ;
					}
				}
			//--------------------------------------------------------------+
			}else {
			//--------------------------------------------------------------+
			//default - rotated ZERO
				/*DH=rect.Height() ;				
				DW=(DH*_pictureW)/_pictureH ;*/
				DW = _pictureW ;
				DH = _pictureH ;
				X = (rect.Width() - DW) / 2 ;
				Y = (rect.Height() - DH) / 2;

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = Oy ;
				Oy = -1*temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(_pictureW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(X + Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_height;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_height ;
					}
				};//else, image less than window

				//VERTICAL
				if(_pictureH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//vertical scroll bar position
					scrollV = abs(Y + Oy) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_height ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_height ;
					}
				}
			//--------------------------------------------------------------+
			};//end else
		}else if(constraintType == 3)//constraint width
		{
			//do the job
zoom_constraint_width :
		;
			CRect rect ;
			GetClientRect(this->m_hwnd, &rect) ;
			
			if(angle == 0)
			{
			//---------------------------------------------------------------+
			//rotated 0
				/*DW = rect.Width() ;
				DH = (DW*_pictureH) / _pictureW ;*/
				DW = _pictureW ;
				DH = _pictureH ;
				X=(rect.Width()  - DW ) / 2;  
				Y=(rect.Height() - DH ) / 2;  

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = Oy ;
				Oy = -1*temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(_pictureW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(X + Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_width;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_width ;
					}
				};//else, image less than window

				//VERTICAL
				if(_pictureH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//vertical scroll bar position
					scrollV = abs(Y + Oy) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_width ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_width ;
					}
				}
			//---------------------------------------------------------------+
			}else if(angle == 90)
			{
			//---------------------------------------------------------------+
			//rotated 90
				/*DH = rect.Width() ;
				DW = (DH*_pictureW) / _pictureH ;*/
				DW = _pictureW ;
				DH = _pictureH ;
				X = (rect.Height() - DW) / 2 ;
				Y = -1*DH -1*(rect.Width() - DH)/2 ;

				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = Oy ;
				Oy = -1*temp ;

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(_pictureW > rect.Height())
				{//scroll offset							
					if(Ox < (rect.Height() - _pictureW -1-X)) Ox = rect.Height()- _pictureW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//vertical scroll bar position
					scrollV = abs(X + Ox) ;	

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_width ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_width ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(_pictureH > rect.Width())
				{//scroll offset				
					if(Oy > (-1)*DH + (DH - rect.Width()-1) - Y)
						Oy = (-1)*DH + (DH - rect.Width()-1) - Y ;
					if(Oy < (-1)*DH - Y) 
						Oy = (-1)*DH - Y ;

					//horizontal scroll bar position
					scrollH = abs(Oy + DH + Y) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_width;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_width ;
					}
				}
			//---------------------------------------------------------------+
			}else if(angle == 180)
			{
			//---------------------------------------------------------------+
			//rotated 180
				/*DW=rect.Width();
				DH=(DW*_pictureH)/_pictureW;*/
				DW = _pictureW ;
				DH = _pictureH ;
				X = -1*DW - (rect.Width() - DW) / 2 ;
				Y = -1*DH - (rect.Height() - DH) /2 ;

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = Oy ;
				Oy = -1*temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(_pictureW > rect.Width())
				{//scroll offset							
					if(Ox > (-1)*DW + (DW - rect.Width()-1) - X)
						Ox = (-1)*DW + (DW - rect.Width()-1) - X ;
					if(Ox < (-1)*DW - X) 
						Ox = (-1)*DW - X ;
					
					//horizontal scroll bar position
					scrollH = abs(Ox + DW + X) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_width;
					}

				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_width ;
					}
				};//else, image less than window

				//VERTICAL
				if(_pictureH > rect.Height())
				{//scroll offset				
					if(Oy >	(-1)*DH + (DH - rect.Height()-1) - Y)
						Oy = (-1)*DH + (DH - rect.Height()-1) - Y ;
					if(Oy < (-1)*DH - Y) 
						Oy = (-1)*DH - Y ;

					//vertical scroll bar position
					scrollV = abs(Oy + DH + Y) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_width ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_width ;
					}
				}
			//---------------------------------------------------------------+
			}else if(angle == 270)
			{
			//---------------------------------------------------------------+
			//rotated 270
				/*DH=rect.Width() ;
				DW=(DH*_pictureW)/_pictureH ;*/
				DW = _pictureW ;
				DH = _pictureH ;
				X = -1*DW - (rect.Height() - DW) /2 ;
				Y = (rect.Width() - DH) / 2 ;

				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = Oy ;
				Oy = -1*temp ;

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(_pictureW > rect.Height())
				{//scroll offset							
					if(Ox >	(-1)*DW + (DW - rect.Height()-1) - X)
						Ox = (-1)*DW + (DW - rect.Height()-1) - X ;
					if(Ox < (-1)*DW - X) 
						Ox = (-1)*DW - X ;
					
					//vertical scroll bar position
					scrollV = abs(Ox + DW + X) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_width ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_width ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(_pictureH > rect.Width())
				{//scroll offset				
					if(Oy < (rect.Width() - DH -1 -Y))  Oy = rect.Width()- DH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//horizontal scroll bar position
					scrollH = abs(Oy + Y) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_width;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_width ;
					}
				}
			//---------------------------------------------------------------+
			}else {
			//---------------------------------------------------------------+	
			//default 
				/*DW=rect.Width();
				DH=(DW*_pictureH)/_pictureW;*/
				DW = _pictureW ;
				DH = _pictureH ;
				X = (rect.Width() - DW) / 2 ;
				Y = (rect.Height() - DH) / 2;

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = Oy ;
				Oy = -1*temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(_pictureW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(X + Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_width;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_width ;
					}
				};//else, image less than window

				//VERTICAL
				if(_pictureH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;
					
					//vertical scroll bar position
					scrollV = abs(Y + Oy) ;	

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_width ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_width ;
					}
				}
			//---------------------------------------------------------------+	
			}
		}else{//constrant all - best fit - default option
			//do the job
zoom_constraint_all2:
		;
			CRect rect ;
			GetClientRect(this->m_hwnd, &rect) ;
			
			if(angle == 0)
			{
			//------------------------------------------------------------------+
				//angle ZERO
				//new zoomed dimensions
				DH = _pictureH ;
				DW = _pictureW ;
				
				X=(rect.Width()  - DW ) / 2;  
				Y=(rect.Height() - DH ) / 2;  //new positions

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = Oy ;
				Oy = -1*temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(_pictureW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(X + Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_all2;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_all2 ;
					}
				};//else, image less than window

				//VERTICAL
				if(_pictureH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//vertical scroll bar position
					scrollV = abs(Y + Oy) ;	

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_all2 ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_all2 ;
					}
				}
			//------------------------------------------------------------------+
			}else if(angle == 90)
			{	
			//------------------------------------------------------------------+
				//angle 90
				//new zoomed dimensions
				DW = _pictureW ;
				DH = _pictureH ;
				X = (rect.Height() - DW) / 2 ;
				Y = -1*DH -1*(rect.Width() - DH)/2 ;

				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = Oy ;
				Oy = -1*temp ;

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(_pictureW > rect.Height())
				{//scroll offset							
					if(Ox < (rect.Height() - DW -1 - X)) 
						Ox = rect.Height() - DW -1 - X ;
					if(Ox > abs(X) ) 
						Ox = abs(X) ;
					
					//vertical scroll bar position
					scrollV = abs(X + Ox) ;	

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_all2 ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_all2 ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(_pictureH > rect.Width())
				{//scroll offset				
					if(Oy > (-1)*DH + (DH - rect.Width()-1) - Y)
						Oy = (-1)*DH + (DH - rect.Width()-1) - Y ;
					if(Oy < (-1)*DH - Y) 
						Oy = (-1)*DH - Y ;

					//horizontal scroll bar position
					scrollH = abs(Oy + DH + Y) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_all2;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_all2 ;
					}
				}
			//------------------------------------------------------------------+
			}else if(angle == 180)
			{
			//------------------------------------------------------------------+
				//angle 180
				//new zoomed dimensions
				DW = _pictureW ;
				DH = _pictureH ;
				X = -1*DW - (rect.Width() - DW) / 2 ;
				Y = -1*DH - (rect.Height() - DH) /2 ;
				
				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = Oy ;
				Oy = -1*temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(_pictureW > rect.Width())
				{//scroll offset							
					if(Ox > (-1)*DW + (DW - rect.Width()-1) - X)
						Ox = (-1)*DW + (DW - rect.Width()-1) - X ;
					if(Ox < (-1)*DW - X) 
						Ox = (-1)*DW - X ;
					
					//horizontal scroll bar position
					scrollH = abs(Ox + DW + X) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;

					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_all2;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_all2 ;
					}
				};//else, image less than window

				//VERTICAL
				if(_pictureH > rect.Height())
				{//scroll offset				
					if(Oy >	(-1)*DH + (DH - rect.Height()-1) - Y)
						Oy = (-1)*DH + (DH - rect.Height()-1) - Y ;
					if(Oy < (-1)*DH - Y) 
						Oy = (-1)*DH - Y ;

					//vertical scroll bar position
					scrollV = abs(Oy + DH + Y) ;				


					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_all2 ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_all2 ;
					}
				}
			//------------------------------------------------------------------+
			}else if(angle == 270)
			{
			//------------------------------------------------------------------+
				//angle 270
				//new zoomed dimensions
				DW = _pictureW ;
				DH = _pictureH ;
				X = -1*DW - (rect.Height() - DW) /2 ;
				Y = (rect.Width() - DH) / 2 ;
				
				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = Oy ;
				Oy = -1*temp ;

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(_pictureW > rect.Height())
				{//scroll offset							
					if(Ox >	(-1)*DW + (DW - rect.Height()-1) - X)
						Ox = (-1)*DW + (DW - rect.Height()-1) - X ;
					if(Ox < (-1)*DW - X) 
						Ox = (-1)*DW - X ;
					
					//vertical scroll bar position
					scrollV = abs(Ox + DW + X) ;	

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_all2 ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_all2 ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(_pictureH > rect.Width())
				{//scroll offset				
					if(Oy < (rect.Width() - DH -1 -Y))  Oy = rect.Width()- DH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//horizontal scroll bar position
					scrollH = abs(Oy + Y) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_all2;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_all2 ;
					}
				}

			//------------------------------------------------------------------+
			}else{
			//------------------------------------------------------------------+
				//angle ZERO
				//new zoomed dimensions
				DW = _pictureW ;
				DH = _pictureH ;
				X = (rect.Width() - DW) / 2 ;
				Y = (rect.Height() - DH) / 2;

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;
				int temp = Ox ;
				Ox = Oy ;
				Oy = -1*temp ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(_pictureW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(X + Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_all2;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_all2 ;
					}
				};//else, image less than window

				//VERTICAL
				if(_pictureH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//vertical scroll bar position
					scrollV = abs(Y + Oy) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_all2 ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_all2 ;
					}
				}
			//------------------------------------------------------------------+
			};//end else
		};//end else default - constraint all - best fit				
	};//end else- test image , image is zoomed

	//the image was calculated
	b_computeImage = false ;

	//erase the background , display the image
	mvShowImage() ;
	//finish RotateRight()
	
}










//mvOnVScroll(...) has to calculate new coordinates of image that
//was scrolled, new scroll bars position (if necessary)
void mvImage::mvOnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar)
{

	//if not modified than do not modify offset Ox, Oy 
	//positions of scroll bars
	bool modified=false;
	//default value of horizontal scroll bar position
	int scrollV = 0 ;	
	//get window sizes
	CRect rect ;
	GetClientRect(this->m_hwnd, &rect) ;
	
	//test nSBCode which is part of :
	//WM_VSCROLL 
	//nScrollCode = (int) LOWORD(wParam);  // scroll bar value 
	//nPos = (short int) HIWORD(wParam);   // scroll box position 

	switch(nSBCode)
	{
		case SB_LINELEFT:
			if(angle == 0)		 {Oy += 30 ;	modified = true ;}
			else if(angle == 90) {Ox += 30 ;	modified = true ;}
			else if(angle == 180){Oy -= 30 ;	modified = true ;}
			else if(angle == 270){Ox -= 30 ;	modified = true ;}
			break;

		case SB_LINERIGHT:
			if(angle == 0)		 {Oy -= 30 ;	modified = true ;}
			else if(angle == 90) {Ox -= 30 ;	modified = true ;}
			else if(angle == 180){Oy += 30 ;	modified = true ;}
			else if(angle == 270){Ox += 30 ;	modified = true ;}
			break;

		case SB_PAGELEFT:
			if(angle == 0)		 {Oy += rect.Width() ;	modified = true ;}
			else if(angle == 90) {Ox += rect.Width() ;	modified = true ;}
			else if(angle == 180){Oy -= rect.Width() ;	modified = true ;}
			else if(angle == 270){Ox -= rect.Width() ;	modified = true ;}
			break;

		case SB_PAGERIGHT:
			if(angle == 0)		 {Oy -= rect.Width() ;	modified = true ;}
			else if(angle == 90) {Ox -= rect.Width() ;	modified = true ;}
			else if(angle == 180){Oy += rect.Width() ;	modified = true ;}
			else if(angle == 270){Ox += rect.Width() ;	modified = true ;}
			break;

		case SB_THUMBPOSITION:
			/*
			if(m_bMaptoImageScroll)
			{
				Ox= (int) nPos*(int)((windowW-DW-1-X-abs(X)) / (DW - windowW+1)) + abs(X) ;
				modified = true ;
				m_bMaptoImageScroll=false ;
				break ;
			}
			else return ;
			*/
			break ;

		case SB_THUMBTRACK:
			if(constraintType == 0)
			{	
				if(angle == 0) 
				{//0º	
					Oy = -1*nPos ;
					modified = true ;
				}else if(angle == 90)
				{//90º	
					Ox = -1*nPos ;
					modified = true ;
				}else if(angle == 180)
				{//180º
					Oy = nPos ;
					modified = true ;
				}else if(angle == 270)
				{//270º
					Ox = nPos ;
					modified = true ;
				}					
			}else if(constraintType == 1)//constraint all , 'best fit' to window
			{
				if(angle == 0) 
				{//0º		
					Oy = abs(Y) - nPos ;
					modified = true ;
				}else if(angle == 90)
				{//90º
					Ox = abs(X) - nPos ;
					modified = true ;
				}else if(angle == 180)
				{//180º
					Oy = abs(Y) + nPos - DH ;
					modified = true ;
				}else if(angle == 270)
				{//270º
					Ox = abs(X) + nPos - DW ;
					modified = true ;
				}			
			}else if(constraintType == 2)//constraint height 
			{
				if(angle == 0) 
				{//0º		
					Oy = abs(Y) - nPos ;
					modified = true ;
				}else if(angle == 90)
				{//90º
					Ox = abs(X) - nPos ;
					modified = true ;
				}else if(angle == 180)
				{//180º
					Oy = abs(Y) + nPos - DH ;
					modified = true ;
				}else if(angle == 270)
				{//270º
					Ox = abs(X) + nPos - DW ;
					modified = true ;
				}		
			}else if(constraintType == 3)//constraint width
			{
				if(angle == 0) 
				{//0º		
					Oy = abs(Y) - nPos ;
					modified = true ;
				}else if(angle == 90)
				{//90º
					Ox = abs(X) - nPos ;
					modified = true ;
				}else if(angle == 180)
				{//180º
					Oy = abs(Y) + nPos - DH ;
					modified = true ;
				}else if(angle == 270)
				{//270º
					Ox = abs(X) + nPos - DW ;
					modified = true ;
				}		
			};//else constraintType = 3, constraint width

			break;

		case SB_LEFT:
			//break;
			return ;

		case SB_RIGHT:
			//break;
			return ;

		case SB_ENDSCROLL:
			//break;
			return ;
			
	}

	if(modified)
	{
		//no constraint for the image
		if(constraintType == 0)
		{	
			if(angle == 0) 
			{//0º				
				if(Oy < (rect.Height() - DH -1 - Y)) Oy = rect.Height()- DH -1-Y ;
				if(Oy > abs(Y)) Oy = abs(Y) ;	
				//vertical scroll bar position
				scrollV = abs(Oy) ;				
				
			}else if(angle == 90)
			{//90º
				if(Ox < (-1)*(DW - rect.Height()- 1) )  
					Ox = (-1)*(DW - rect.Height()- 1) ;
				if(Ox > 0) 
					Ox = 0 ;
				//vertical scroll bar position
				scrollV = abs(Ox) ;				

			}else if(angle == 180)
			{//180º
				if( Oy > DH - rect.Height() - 1 )
					Oy = DH - rect.Height() - 1 ;
				if(Oy < 0)
					Oy = 0 ;
				//vertical scroll bar position
				scrollV = abs(Oy) ;				

			}else if(angle == 270)
			{//270º
				if( Ox > DW - rect.Height() - 1 )
					Ox = DW - rect.Height() - 1 ;
				if(Ox < 0)
					Ox = 0 ;
				//vertical scroll bar position
				scrollV = abs(Ox) ;	
			}			
		}else if(constraintType == 1)//constraint all , 'best fit' to window
		{
			if(angle == 0) 
			{//0º				
				if(Oy < (rect.Height() - DH -1 - Y)) 
					Oy = rect.Height() - DH -1 - Y ;
				if(Oy > abs(Y)) 
					Oy = abs(Y) ;	
				//vertical scroll bar position
				scrollV = abs(Y + Oy) ;				

			}else if(angle == 90)
			{//90º				
				if(Ox < (rect.Height() - DW -1 - X)) 
					Ox = rect.Height() - DW -1 - X ;
				if(Ox > abs(X) ) 
					Ox = abs(X) ;
				//vertical scroll bar position
				scrollV = abs(X + Ox) ;				

			}else if(angle == 180)
			{//180º
				if(Oy >	(-1)*DH + (DH - rect.Height()-1) - Y)
					Oy = (-1)*DH + (DH - rect.Height()-1) - Y ;
				if(Oy < (-1)*DH - Y) 
					Oy = (-1)*DH - Y ;
				//vertical scroll bar position
				scrollV = abs(Oy + DH + Y) ;				

			}else if(angle == 270)
			{//270º
				if(Ox >	(-1)*DW + (DW - rect.Height()-1) - X)
					Ox = (-1)*DW + (DW - rect.Height()-1) - X ;
				if(Ox < (-1)*DW - X) 
					Ox = (-1)*DW - X ;
				//vertical scroll bar position
				scrollV = abs(Ox + DW + X) ;				

			}
		}else if(constraintType == 2)//constraint height 
		{
			if(angle == 0) 
			{//0º				
				if(Oy < (rect.Height() - DH -1 - Y)) 
					Oy = rect.Height() - DH -1 - Y ;
				if(Oy > abs(Y)) 
					Oy = abs(Y) ;	
				//vertical scroll bar position
				scrollV = abs(Y + Oy) ;				

			}else if(angle == 90)
			{//90º				
				if(Ox < (rect.Height() - DW -1 - X)) 
					Ox = rect.Height() - DW -1 - X ;
				if(Ox > abs(X) ) 
					Ox = abs(X) ;
				//vertical scroll bar position
				scrollV = abs(X + Ox) ;				

			}else if(angle == 180)
			{//180º
				if(Oy >	(-1)*DH + (DH - rect.Height()-1) - Y)
					Oy = (-1)*DH + (DH - rect.Height()-1) - Y ;
				if(Oy < (-1)*DH - Y) 
					Oy = (-1)*DH - Y ;
				//vertical scroll bar position
				scrollV = abs(Oy + DH + Y) ;				

			}else if(angle == 270)
			{//270º
				if(Ox >	(-1)*DW + (DW - rect.Height()-1) - X)
					Ox = (-1)*DW + (DW - rect.Height()-1) - X ;
				if(Ox < (-1)*DW - X) 
					Ox = (-1)*DW - X ;
				//vertical scroll bar position
				scrollV = abs(Ox + DW + X) ;				

			}
		}else if(constraintType == 3)//constraint width
		{
			if(angle == 0) 
			{//0º				
				if(Oy < (rect.Height() - DH -1 - Y)) 
					Oy = rect.Height() - DH -1 - Y ;
				if(Oy > abs(Y)) 
					Oy = abs(Y) ;	
				//vertical scroll bar position
				scrollV = abs(Y + Oy) ;				

			}else if(angle == 90)
			{//90º				
				if(Ox < (rect.Height() - DW -1 - X)) 
					Ox = rect.Height() - DW -1 - X ;
				if(Ox > abs(X) ) 
					Ox = abs(X) ;
				//vertical scroll bar position
				scrollV = abs(X + Ox) ;				

			}else if(angle == 180)
			{//180º
				if(Oy >	(-1)*DH + (DH - rect.Height()-1) - Y)
					Oy = (-1)*DH + (DH - rect.Height()-1) - Y ;
				if(Oy < (-1)*DH - Y) 
					Oy = (-1)*DH - Y ;
				//vertical scroll bar position
				scrollV = abs(Oy + DH + Y) ;				

			}else if(angle == 270)
			{//270º
				if(Ox >	(-1)*DW + (DW - rect.Height()-1) - X)
					Ox = (-1)*DW + (DW - rect.Height()-1) - X ;
				if(Ox < (-1)*DW - X) 
					Ox = (-1)*DW - X ;
				//vertical scroll bar position
				scrollV = abs(Ox + DW + X) ;				

			};//else 270º
		};//else constraintType = 3, constraint width
		        
		SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
	};//if modified is true

	//do not erase the background & display the image
	mvShowImageBackground(false) ;

}




//mvOnVScroll(...) has to calculate new coordinates of image that
//was scrolled, new scroll bars position (if necessary)
void mvImage::mvOnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar)
{
	//if not modified than do not modify offset Ox, Oy 
	//positions of scroll bars
	bool modified=false;
	//default value of horizontal scroll bar position
	int scrollH = 0 ;	
	//get window sizes
	CRect rect ;
	GetClientRect(this->m_hwnd, &rect) ;
	
	//test nSBCode which is part of :
	//WM_HSCROLL 
	//nScrollCode = (int) LOWORD(wParam);  // scroll bar value 
	//nPos = (short int) HIWORD(wParam);   // scroll box position 

	switch(nSBCode)
	{
		case SB_LINELEFT:
			if(angle == 0)		 {Ox += 30 ;	modified = true ;}
			else if(angle == 90) {Oy -= 30 ;	modified = true ;}
			else if(angle == 180){Ox -= 30 ;	modified = true ;}
			else if(angle == 270){Oy += 30 ;	modified = true ;}
			break;

		case SB_LINERIGHT:
			if(angle == 0)		 {Ox -= 30 ;	modified = true ;}
			else if(angle == 90) {Oy += 30 ;	modified = true ;}
			else if(angle == 180){Ox += 30 ;	modified = true ;}
			else if(angle == 270){Oy -= 30 ;	modified = true ;}
			break;

		case SB_PAGELEFT:
			if(angle == 0)		 {Ox += rect.Width() ;	modified = true ;}
			else if(angle == 90) {Oy -= rect.Width() ;	modified = true ;}
			else if(angle == 180){Ox -= rect.Width() ;	modified = true ;}
			else if(angle == 270){Oy += rect.Width() ;	modified = true ;}
			break;

		case SB_PAGERIGHT:
			if(angle == 0)		 {Ox -= rect.Width() ;	modified = true ;}
			else if(angle == 90) {Oy += rect.Width() ;	modified = true ;}
			else if(angle == 180){Ox += rect.Width() ;	modified = true ;}
			else if(angle == 270){Oy -= rect.Width() ;	modified = true ;}
			break;

		case SB_THUMBPOSITION:
			/*
			if(m_bMaptoImageScroll)
			{
				Ox= (int) nPos*(int)((windowW-DW-1-X-abs(X)) / (DW - windowW+1)) + abs(X) ;
				modified = true ;
				m_bMaptoImageScroll=false ;
				break ;
			}
			else return ;
			*/
			break ;

		case SB_THUMBTRACK:
			if(constraintType == 0)
			{	
				if(angle == 0) 
				{//0º
					Ox = -1*nPos ;
					modified = true ;
				}else if(angle == 90)
				{//90º	
					Oy = nPos ;
					modified = true ;
				}else if(angle == 180)
				{//180º
					Ox = nPos ;
					modified = true ;
				}else if(angle == 270)
				{//270º			
					Oy = -1*nPos ;
					modified = true ;
				}			
			}else if(constraintType == 1)//constraint all , 'best fit' to window
			{
				if(angle == 0) 
				{//0º		
					Ox = abs(X) - nPos ;
					modified = true ;
				}else if(angle == 90)
				{//90º
					Oy = nPos - DH - Y ;
					modified = true ;
				}else if(angle == 180)
				{//180º
					Ox = nPos - DW - X ;
					modified = true ;
				}else if(angle == 270)
				{//270º
					Oy = abs(Y) - nPos  ;
					modified = true ;
				}
			}else if(constraintType == 2)//constraint height 
			{			
				if(angle == 0) 
				{//0º		
					Ox = abs(X) - nPos ;
					modified = true ;
				}else if(angle == 90)
				{//90º	
					Oy = nPos - DH - Y ;
					modified = true ;
				}else if(angle == 180)
				{//180º
					Ox = nPos - DW - X ;
					modified = true ;
				}else if(angle == 270)
				{//270º
					Oy = abs(Y) - nPos  ;
					modified = true ;
				}
			}else if(constraintType == 3)//constraint width
			{
				if(angle == 0) 
				{//0º				
					Ox = abs(X) - nPos ;
					modified = true ;
				}else if(angle == 90)
				{//90º				
					Oy = nPos - DH - Y ;
					modified = true ;
				}else if(angle == 180)
				{//180º
					Ox = nPos - DW - X ;
					modified = true ;
				}else if(angle == 270)
				{//270º
					Oy = abs(Y) - nPos  ;
					modified = true ;
				}
			};//constraintType 3

			break;

		case SB_LEFT:
			//break;
			return ;

		case SB_RIGHT:
			//break;
			return ;

		case SB_ENDSCROLL:
			//break;
			return ;
			
	}




	if(modified)
	{
		//no constraint for the image
		if(constraintType == 0)
		{	
			if(angle == 0) 
			{//0º				
				if(Ox < (rect.Width() - DW -1 - X)) 
					Ox = rect.Width()- DW -1-X ;
				if(Ox > abs(X)) 
					Ox = abs(X) ;
				//horizontal scroll bar position
				scrollH = abs(Ox) ;

			}else if(angle == 90)
			{//90º
				if(Oy > (DH - rect.Width()-1))  Oy = (DH - rect.Width()-1) ;
				if(Oy < 0) Oy = 0 ;
				//horizontal scroll bar position
				scrollH = abs(Oy) ;

			}else if(angle == 180)
			{//180º
				if(Ox > (DW - rect.Width()-1))  Ox = (DW - rect.Width()-1) ;
				if(Ox < 0 ) Ox = 0  ;
				//horizontal scroll bar position
				scrollH = abs(Ox) ;

			}else if(angle == 270)
			{//270º
				if(Oy < (rect.Width() - DH -1 -Y))  Oy = rect.Width()- DH -1-Y ;
				if(Oy > abs(Y)) Oy = abs(Y) ;
				//horizontal scroll bar position
				scrollH = abs(Oy) ;

			}
			
		}else if(constraintType == 1)//constraint all , 'best fit' to window
		{
			if(angle == 0) 
			{//0º				
				if(Ox < (rect.Width() - DW -1 - X)) Ox = rect.Width()- DW -1-X ;
				if(Ox > abs(X)) Ox = abs(X) ;	
				//horizontal scroll bar position
				scrollH = abs(X + Ox) ;

			}else if(angle == 90)
			{//90º				
				if(Oy > (-1)*DH + (DH - rect.Width()-1) - Y)
					Oy = (-1)*DH + (DH - rect.Width()-1) - Y ;
				if(Oy < (-1)*DH - Y) 
					Oy = (-1)*DH - Y ;
				//horizontal scroll bar position
				scrollH = abs(Oy + DH + Y) ;

			}else if(angle == 180)
			{//180º
				if(Ox > (-1)*DW + (DW - rect.Width()-1) - X)
					Ox = (-1)*DW + (DW - rect.Width()-1) - X ;
				if(Ox < (-1)*DW - X) 
					Ox = (-1)*DW - X ;
				//horizontal scroll bar position
				scrollH = abs(Ox + DW + X) ;

			}else if(angle == 270)
			{//270º
				if(Oy < (rect.Width() - DH -1 -Y))  Oy = rect.Width()- DH -1-Y ;
				if(Oy > abs(Y)) Oy = abs(Y) ;
				//horizontal scroll bar position
				scrollH = abs(Oy + Y) ;

			}
		}else if(constraintType == 2)//constraint height 
		{			
			if(angle == 0) 
			{//0º				
				if(Ox < (rect.Width() - DW -1 - X)) Ox = rect.Width()- DW -1-X ;
				if(Ox > abs(X)) Ox = abs(X) ;	
				//horizontal scroll bar position
				scrollH = abs(X + Ox) ;

			}else if(angle == 90)
			{//90º				
				if(Oy > (-1)*DH + (DH - rect.Width()-1) - Y)
					Oy = (-1)*DH + (DH - rect.Width()-1) - Y ;
				if(Oy < (-1)*DH - Y) 
					Oy = (-1)*DH - Y ;
				//horizontal scroll bar position
				scrollH = abs(Oy + DH + Y) ;

			}else if(angle == 180)
			{//180º
				if(Ox > (-1)*DW + (DW - rect.Width()-1) - X)
					Ox = (-1)*DW + (DW - rect.Width()-1) - X ;
				if(Ox < (-1)*DW - X) 
					Ox = (-1)*DW - X ;
				//horizontal scroll bar position
				scrollH = abs(Ox + DW + X) ;

			}else if(angle == 270)
			{//270º
				if(Oy < (rect.Width() - DH -1 -Y))  Oy = rect.Width()- DH -1-Y ;
				if(Oy > abs(Y)) Oy = abs(Y) ;
				//horizontal scroll bar position
				scrollH = abs(Oy + Y) ;

			}
		}else if(constraintType == 3)//constraint width
		{
			if(angle == 0) 
			{//0º				
				if(Ox < (rect.Width() - DW -1 - X)) Ox = rect.Width()- DW -1-X ;
				if(Ox > abs(X)) Ox = abs(X) ;	
				//horizontal scroll bar position
				scrollH = abs(X + Ox) ;

			}else if(angle == 90)
			{//90º				
				if(Oy > (-1)*DH + (DH - rect.Width()-1) - Y)
					Oy = (-1)*DH + (DH - rect.Width()-1) - Y ;
				if(Oy < (-1)*DH - Y) 
					Oy = (-1)*DH - Y ;
				//horizontal scroll bar position
				scrollH = abs(Oy + DH + Y) ;

			}else if(angle == 180)
			{//180º
				if(Ox > (-1)*DW + (DW - rect.Width()-1) - X)
					Ox = (-1)*DW + (DW - rect.Width()-1) - X ;
				if(Ox < (-1)*DW - X) 
					Ox = (-1)*DW - X ;
				//horizontal scroll bar position
				scrollH = abs(Ox + DW + X) ;

			}else if(angle == 270)
			{//270º
				if(Oy < (rect.Width() - DH -1 -Y))  Oy = rect.Width()- DH -1-Y ;
				if(Oy > abs(Y)) Oy = abs(Y) ;
				//horizontal scroll bar position
				scrollH = abs(Oy + Y) ;

			};//else 270
		};//constraintType 3
       
		SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
	};//if modified

	//do not erase the background & display the image
	mvShowImageBackground(false) ;
	//finish mvOnHSCroll(UINT, int, int)
	
}



//mvOnSize provide functionality for WM_SIZE message
//that is received by the window when it is resized
//it is convenient to call this function from main program
//view (normally),
//it makes calculations to put image in right pos.
void mvImage::mvOnSize(UINT nType, int cx, int cy)
{
	if(image_loaded == false || m_hwnd == 0x000000 || image == 0x000000)
		return ;
	//if another process generates WM_SIZE message
	//while computing the image don't interfere 
	if(b_computeImage == true)
		return ;
	else b_computeImage = true ;
	
	//test if zoom functions modifyed already the image
	//the image is not zoomed - algorith like in 
	//mvConstraint... functions (Nothing, All, Height, Width)
	if(zoom_status == false)
	{
		//check the constraint type of image displaing mode in window		
		if(constraintType == 0)//no  constraint 
		{
			//do the job
constraint_nothing:
		;
			CRect rect ;
			GetClientRect(this->m_hwnd, &rect) ;
			mvGetImageDimensions(&pictureW, &pictureH) ;
			if(angle == 0)
			{
			//------------------------------------------------------------------+
			//angle zero
				X=0; 
				Y=0;
				DW = pictureW ;
				DH = pictureH ;
					
				
				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(DW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - DW -1 - X)) Ox = rect.Width()- DW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = DW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, DW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto constraint_nothing ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto constraint_nothing ;
					}

				};//else, image less than window

				//VERTICAL
				if(DH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - DH -1 - Y))  Oy = rect.Height()- DH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;
					
					//vertical scroll bar position
					scrollV = abs(Oy) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = DH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, DH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto constraint_nothing ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto constraint_nothing ;
					}
				}

			//------------------------------------------------------------------+
			}else if(angle == 90)
			{
			//------------------------------------------------------------------+
			//angle 90
				X = 0 ;
				Y = -1*pictureH ;
				DW = pictureW ;
				DH = pictureH ;

				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;				

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(DW > rect.Height())
				{//scroll offset							
					if(Ox < (-1)*(DW - rect.Height()- 1) )  
						Ox = (-1)*(DW - rect.Height()- 1) ;
					if(Ox > abs(X))  
						Ox = abs(X) ;
					
					//vertical scroll bar position
					scrollV = abs(Ox) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = DW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, DW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto constraint_nothing ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto constraint_nothing ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(DH > rect.Width())
				{//scroll offset				
					if(Oy > (DH - rect.Width()-1))  Oy = (DH - rect.Width()-1) ;
					if(Oy < 0) Oy = 0 ;

					//horizontal scroll bar position
					scrollH = abs(Oy) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = DH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, DH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto constraint_nothing ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto constraint_nothing ;
					}
				}

			//------------------------------------------------------------------+
			}else if(angle == 180)
			{
			//------------------------------------------------------------------+	
			//angle 180
				X = -1*pictureW  ;
				Y = -1*pictureH  ;
				DW = pictureW ;
				DH = pictureH ;

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(DW > rect.Width())
				{//scroll offset							
					if(Ox > (DW - rect.Width()-1))  Ox = (DW - rect.Width()-1) ;
					if(Ox < 0 ) Ox = 0  ;
					
					//horizontal scroll bar position
					scrollH = abs(Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = DW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, DW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto constraint_nothing ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto constraint_nothing ;
					}
				};//else, image less than window

				//VERTICAL
				if(DH > rect.Height())
				{//scroll offset				
					if( Oy > DH - rect.Height() - 1 )
						Oy = DH - rect.Height() - 1 ;
					if(Oy < 0)
						Oy = 0 ;

					//vertical scroll bar position
					scrollV = abs(Oy) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = DH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, DH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto constraint_nothing ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto constraint_nothing ;
					}
				}
			//------------------------------------------------------------------+
			}else if(angle == 270)
			{
			//------------------------------------------------------------------+		
			//angle 270
				X = -1*pictureW ;
				Y = 0 ;
				DW = pictureW ;
				DH = pictureH ;

				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(DW > rect.Height())
				{//scroll offset							
					if( Ox > DW - rect.Height() - 1 )
						Ox = DW - rect.Height() - 1 ;
					if(Ox < 0)
						Ox = 0 ;
					
					//vertical scroll bar position
					scrollV = abs(Ox) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = DW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, DW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto constraint_nothing ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto constraint_nothing ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(DH > rect.Width())
				{//scroll offset				
					if(Oy < (rect.Width() - DH -1 -Y))  Oy = rect.Width()- DH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//horizontal scroll bar position
					scrollH = abs(Oy) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = DH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, DH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto constraint_nothing ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto constraint_nothing ;
					}
				}
			//------------------------------------------------------------------+
			}else
			{
			//------------------------------------------------------------------+
			//angle zero default	
				X=0; 
				Y=0;
				DW = pictureW ;
				DH = pictureH ;
					
				
				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(DW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - DW -1 - X)) Ox = rect.Width()- DW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = DW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, DW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto constraint_nothing ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto constraint_nothing ;
					}
				};//else, image less than window

				//VERTICAL
				if(DH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - DH -1 - Y))  Oy = rect.Height()- DH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//vertical scroll bar position
					scrollV = abs(Oy) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = DH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, DH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto constraint_nothing ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto constraint_nothing ;
					}
				}
			};//else , default angle zero
			//------------------------------------------------------------------+
		}else if(constraintType == 1)//constraint all - best fit
		{			
			//because of image constraint 'best fit' was performed previously
			//so the scroll bars are hidden
			//do the job
//constraint_all :
//		;
			//scroll bars have been hidden before.
			CRect rect ;
			GetClientRect(this->m_hwnd, &rect) ;
			mvGetImageDimensions(&pictureW, &pictureH) ;
			if(angle == 0)
			{
			//------------------------------------------------------------------+
				//angle ZERO
				DH=rect.Height() ;
				DW=(DH*pictureW)/pictureH ;				
				if(DW>rect.Width())
				{
					DW=rect.Width();
					DH=(DW*pictureH)/pictureW;
				};

				
				X=(rect.Width()  - DW ) / 2;  
				Y=(rect.Height() - DH ) / 2;  //new positions
				//scrolls bars offset
				Ox = 0 ;  Oy = 0 ;
				//don't need to put scroll bars in window
			//------------------------------------------------------------------+
			}else if(angle == 90)
			{	
			//------------------------------------------------------------------+
				//angle 90
				DW=rect.Height();			
				DH=(DW*pictureH)/pictureW;		
				if(DH>rect.Width())
				{
					DH=rect.Width() ;
					DW=(DH*pictureW)/pictureH ;	
				};
				X = (rect.Height() - DW) / 2 ;
				Y = -1*DH -1*(rect.Width() - DH)/2 ;
				//scrolls bars offset
				Ox = 0 ;  Oy = 0 ;
				//don't need to put scroll bars in window
			//------------------------------------------------------------------+
			}else if(angle == 180)
			{
			//------------------------------------------------------------------+
				//angle 180
				DH=rect.Height() ;				//height of image
				DW=(DH*pictureW)/pictureH ;		//width of image
				if(DW>rect.Width())
				{
					DW=rect.Width();
					DH=(DW*pictureH)/pictureW;
				}
				X = -1*DW - (rect.Width() - DW) / 2 ;
				Y = -1*DH - (rect.Height() - DH) /2 ;
				//scrolls bars offset
				Ox = 0 ;  Oy = 0 ;
				//don't need to put scroll bars in window
			//------------------------------------------------------------------+
			}else if(angle == 270)
			{
			//------------------------------------------------------------------+
				//angle 270
				DW=rect.Height();			
				DH=(DW*pictureH)/pictureW;	
				
				if(DH>rect.Width())
				{
					DH=rect.Width() ;
					DW=(DH*pictureW)/pictureH ;	
				};
				X = -1*DW - (rect.Height() - DW) /2 ;
				Y = (rect.Width() - DH) / 2 ;
				//scrolls bars offset
				Ox = 0 ;  Oy = 0 ;
				//don't need to put scroll bars in window
			//------------------------------------------------------------------+
			}else{
			//------------------------------------------------------------------+
				//angle ZERO
				DH=rect.Height() ;
				DW=(DH*pictureW)/pictureH ;				
				if(DW>rect.Width())
				{
					DW=rect.Width();
					DH=(DW*pictureH)/pictureW;
				};
				X = (rect.Width() - DW) / 2 ;
				Y = (rect.Height() - DH) / 2;
				//scrolls bars offset
				Ox = 0 ;  Oy = 0 ;
				//don't need to put scroll bars in window
			//------------------------------------------------------------------+
			};//end else
		//------------------------------------------------------------------+
		}else if(constraintType == 2)//constraint height 
		{
			//do the job
constraint_height:
		;
			CRect rect ;
			GetClientRect(this->m_hwnd, &rect) ;
			mvGetImageDimensions(&pictureW, &pictureH) ;
			if(angle == 0)
			{
			//--------------------------------------------------------------+
			//rotated ZERO
				DH=rect.Height() ;
				DW=(DH*pictureW)/pictureH ;				
				X=(rect.Width()  - DW) / 2;  
				Y=(rect.Height() - DH) / 2;  
	
				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(DW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - DW -1 - X)) Ox = rect.Width()- DW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(X + Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = DW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, DW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto constraint_height ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto constraint_height ;
					}
				};//else, image less than window

				//VERTICAL
				if(DH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - DH -1 - Y))  Oy = rect.Height()- DH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//vertical scroll bar position
					scrollV = abs(Y + Oy) ;	

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = DH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, DH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto constraint_height ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto constraint_height ;
					}
				}
			//--------------------------------------------------------------+
			}else if(angle == 90)
			{
			//--------------------------------------------------------------+
			//rotated 90
				DW=rect.Height();			
				DH=(DW*pictureH)/pictureW;	
				X = (rect.Height() - DW) / 2 ;
				Y = -1*DH -1*(rect.Width() - DH)/2 ;


				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(DW > rect.Height())
				{//scroll offset							
					if(Ox < (rect.Height() - DW -1-X)) Ox = rect.Height()- DW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//vertical scroll bar position
					scrollV = abs(X + Ox) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = DW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, DW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto constraint_height ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto constraint_height ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(DH > rect.Width())
				{//scroll offset				
					if(Oy > (-1)*DH + (DH - rect.Width()-1) - Y)
						Oy = (-1)*DH + (DH - rect.Width()-1) - Y ;
					if(Oy < (-1)*DH - Y) 
						Oy = (-1)*DH - Y ;

					//horizontal scroll bar position
					scrollH = abs(Oy + DH + Y) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = DH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, DH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto constraint_height ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto constraint_height ;
					}
				}
			//--------------------------------------------------------------+
			}else if(angle == 180)
			{
			//--------------------------------------------------------------+
			//rotated 180
				DH=rect.Height() ;				//height of image
				DW=(DH*pictureW)/pictureH ;		//width of image
				X = -1*DW - (rect.Width() - DW) / 2 ;
				Y = -1*DH - (rect.Height() - DH) /2 ;

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(DW > rect.Width())
				{//scroll offset							
					if(Ox > (-1)*DW + (DW - rect.Width()-1) - X)
						Ox = (-1)*DW + (DW - rect.Width()-1) - X ;
					if(Ox < (-1)*DW - X) 
						Ox = (-1)*DW - X ;

					//horizontal scroll bar position
					scrollH = abs(Ox + DW + X) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = DW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, DW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;

					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto constraint_height ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
		
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto constraint_height ;
					}
				};//else, image less than window

				//VERTICAL
				if(DH > rect.Height())
				{//scroll offset				
					if(Oy >	(-1)*DH + (DH - rect.Height()-1) - Y)
						Oy = (-1)*DH + (DH - rect.Height()-1) - Y ;
					if(Oy < (-1)*DH - Y) 
						Oy = (-1)*DH - Y ;

					//vertical scroll bar position
					scrollV = abs(Oy + DH + Y) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = DH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, DH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto constraint_height ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto constraint_height ;
					}
				}
			//--------------------------------------------------------------+
			}else if(angle == 270)
			{
			//--------------------------------------------------------------+
			//rotated 270
				DW=rect.Height();			
				DH=(DW*pictureH)/pictureW;	
				X = -1*DW - (rect.Height() - DW) /2 ;
				Y = (rect.Width() - DH) / 2 ;

				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(DW > rect.Height())
				{//scroll offset							
					if(Ox >	(-1)*DW + (DW - rect.Height()-1) - X)
						Ox = (-1)*DW + (DW - rect.Height()-1) - X ;
					if(Ox < (-1)*DW - X) 
						Ox = (-1)*DW - X ;
					
					//vertical scroll bar position
					scrollV = abs(Ox + DW + X) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = DW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, DW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto constraint_height ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto constraint_height ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(DH > rect.Width())
				{//scroll offset				
					if(Oy < (rect.Width() - DH -1 -Y))  Oy = rect.Width()- DH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//horizontal scroll bar position
					scrollH = abs(Oy + Y) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = DH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, DH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto constraint_height ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto constraint_height ;
					}
				}
			//--------------------------------------------------------------+
			}else {
			//--------------------------------------------------------------+
			//default - rotated ZERO
				DH=rect.Height() ;				//height of image
				DW=(DH*pictureW)/pictureH ;		//width of image
				X = (rect.Width() - DW) / 2 ;
				Y = (rect.Height() - DH) / 2;
			
				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(DW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - DW -1 - X)) Ox = rect.Width()- DW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(X + Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = DW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, DW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto constraint_height ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto constraint_height ;
					}
				};//else, image less than window

				//VERTICAL
				if(DH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - DH -1 - Y))  Oy = rect.Height()- DH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//vertical scroll bar position
					scrollV = abs(Y + Oy) ;	

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = DH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, DH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto constraint_height ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto constraint_height ;
					}
				}					
			//--------------------------------------------------------------+
			};//end else
		}else if(constraintType == 3)//constraint width
		{
			//do the job
constraint_width:
		;
			CRect rect ;
			GetClientRect(this->m_hwnd, &rect) ;
			mvGetImageDimensions(&pictureW, &pictureH) ;
			if(angle == 0)
			{
			//---------------------------------------------------------------+
			//rotated 0
				DW = rect.Width() ;
				DH = (DW*pictureH) / pictureW ;
				X=(rect.Width()  - DW ) / 2;  
				Y=(rect.Height() - DH ) / 2;  

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(DW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - DW -1 - X)) Ox = rect.Width()- DW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(X + Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = DW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, DW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto constraint_width ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto constraint_width ;
					}
				};//else, image less than window

				//VERTICAL
				if(DH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - DH -1 - Y))  Oy = rect.Height()- DH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//vertical scroll bar position
					scrollV = abs(Y + Oy) ;	

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = DH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, DH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto constraint_width ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto constraint_width ;
					}
				}
			//---------------------------------------------------------------+
			}else if(angle == 90)
			{
			//---------------------------------------------------------------+
			//rotated 90
				DH = rect.Width() ;
				DW = (DH*pictureW) / pictureH ;
				X = (rect.Height() - DW) / 2 ;
				Y = -1*DH -1*(rect.Width() - DH)/2 ;

				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(DW > rect.Height())
				{//scroll offset							
					if(Ox < (rect.Height() - DW -1-X)) Ox = rect.Height()- DW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//vertical scroll bar position
					scrollV = abs(X + Ox) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = DW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, DW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto constraint_width ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto constraint_width ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(DH > rect.Width())
				{//scroll offset				
					if(Oy > (-1)*DH + (DH - rect.Width()-1) - Y)
						Oy = (-1)*DH + (DH - rect.Width()-1) - Y ;
					if(Oy < (-1)*DH - Y) 
						Oy = (-1)*DH - Y ;

					//horizontal scroll bar position
					scrollH = abs(Oy + DH + Y) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = DH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, DH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto constraint_width ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto constraint_width ;
					}
				}
			//---------------------------------------------------------------+
			}else if(angle == 180)
			{
			//---------------------------------------------------------------+
			//rotated 180
				DW=rect.Width();
				DH=(DW*pictureH)/pictureW;
				X = -1*DW - (rect.Width() - DW) / 2 ;
				Y = -1*DH - (rect.Height() - DH) /2 ;

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(DW > rect.Width())
				{//scroll offset							
					if(Ox > (-1)*DW + (DW - rect.Width()-1) - X)
						Ox = (-1)*DW + (DW - rect.Width()-1) - X ;
					if(Ox < (-1)*DW - X) 
						Ox = (-1)*DW - X ;
					
					//horizontal scroll bar position
					scrollH = abs(Ox + DW + X) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = DW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, DW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto constraint_width ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto constraint_width ;
					}
				};//else, image less than window

				//VERTICAL
				if(DH > rect.Height())
				{//scroll offset				
					if(Oy >	(-1)*DH + (DH - rect.Height()-1) - Y)
						Oy = (-1)*DH + (DH - rect.Height()-1) - Y ;
					if(Oy < (-1)*DH - Y) 
						Oy = (-1)*DH - Y ;

					//vertical scroll bar position
					scrollV = abs(Oy + DH + Y) ;	

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = DH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, DH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto constraint_width ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto constraint_width ;
					}
				}
			//---------------------------------------------------------------+
			}else if(angle == 270)
			{
			//---------------------------------------------------------------+
			//rotated 270
				DH=rect.Width() ;
				DW=(DH*pictureW)/pictureH ;	
				X = -1*DW - (rect.Height() - DW) /2 ;
				Y = (rect.Width() - DH) / 2 ;
			
				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(DW > rect.Height())
				{//scroll offset							
					if(Ox >	(-1)*DW + (DW - rect.Height()-1) - X)
						Ox = (-1)*DW + (DW - rect.Height()-1) - X ;
					if(Ox < (-1)*DW - X) 
						Ox = (-1)*DW - X ;
					
					//vertical scroll bar position
					scrollV = abs(Ox + DW + X) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = DW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, DW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto constraint_width ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto constraint_width ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(DH > rect.Width())
				{//scroll offset				
					if(Oy < (rect.Width() - DH -1 -Y))  Oy = rect.Width()- DH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//horizontal scroll bar position
					scrollH = abs(Oy + Y) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = DH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, DH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto constraint_width ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto constraint_width ;
					}
				}
			//---------------------------------------------------------------+
			}else {
			//---------------------------------------------------------------+	
			//default 
				DW=rect.Width();
				DH=(DW*pictureH)/pictureW;
				X = (rect.Width() - DW) / 2 ;
				Y = (rect.Height() - DH) / 2;
			
				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(DW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - DW -1 - X)) Ox = rect.Width()- DW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(X + Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = DW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, DW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto constraint_width ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto constraint_width ;
					}
				};//else, image less than window

				//VERTICAL
				if(DH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - DH -1 - Y))  Oy = rect.Height()- DH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//vertical scroll bar position
					scrollV = abs(Y + Oy) ;	

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = DH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, DH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto constraint_width ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto constraint_width ;
					}
				}
			//---------------------------------------------------------------+	
			}
			//------------------------------------------------------------------+
		}else{//constrant all - best fit - default option
			//do the job
//constraint_all2:
//		;						
			CRect rect ;
			GetClientRect(this->m_hwnd, &rect) ;
			mvGetImageDimensions(&pictureW, &pictureH) ;
			if(angle == 0)
			{
			//------------------------------------------------------------------+
				//angle ZERO
				DH=rect.Height() ;
				DW=(DH*pictureW)/pictureH ;				
				if(DW>rect.Width())
				{
					DW=rect.Width();
					DH=(DW*pictureH)/pictureW;
				};

				
				X=(rect.Width()  - DW ) / 2;  
				Y=(rect.Height() - DH ) / 2;  //new positions
				//scrolls bars offset
				Ox = 0 ;  Oy = 0 ;
				//don't need to put scroll bars in window
			//------------------------------------------------------------------+
			}else if(angle == 90)
			{	
			//------------------------------------------------------------------+
				//angle 90
				DW=rect.Height();			
				DH=(DW*pictureH)/pictureW;		
				if(DH>rect.Width())
				{
					DH=rect.Width() ;
					DW=(DH*pictureW)/pictureH ;	
				};
				X = (rect.Height() - DW) / 2 ;
				Y = -1*DH -1*(rect.Width() - DH)/2 ;
				//scrolls bars offset
				Ox = 0 ;  Oy = 0 ;
				//don't need to put scroll bars in window
			//------------------------------------------------------------------+
			}else if(angle == 180)
			{
			//------------------------------------------------------------------+
				//angle 180
				DH=rect.Height() ;				//height of image
				DW=(DH*pictureW)/pictureH ;		//width of image
				if(DW>rect.Width())
				{
					DW=rect.Width();
					DH=(DW*pictureH)/pictureW;
				}
				X = -1*DW - (rect.Width() - DW) / 2 ;
				Y = -1*DH - (rect.Height() - DH) /2 ;
				//scrolls bars offset
				Ox = 0 ;  Oy = 0 ;
				//don't need to put scroll bars in window
			//------------------------------------------------------------------+
			}else if(angle == 270)
			{
			//------------------------------------------------------------------+
				//angle 270
				DW=rect.Height();			
				DH=(DW*pictureH)/pictureW;	
				
				if(DH>rect.Width())
				{
					DH=rect.Width() ;
					DW=(DH*pictureW)/pictureH ;	
				};
				X = -1*DW - (rect.Height() - DW) /2 ;
				Y = (rect.Width() - DH) / 2 ;
				//scrolls bars offset
				Ox = 0 ;  Oy = 0 ;
				//don't need to put scroll bars in window
			//------------------------------------------------------------------+
			}else{
			//------------------------------------------------------------------+
				//angle ZERO
				DH=rect.Height() ;
				DW=(DH*pictureW)/pictureH ;				
				if(DW>rect.Width())
				{
					DW=rect.Width();
					DH=(DW*pictureH)/pictureW;
				};
				X = (rect.Width() - DW) / 2 ;
				Y = (rect.Height() - DH) / 2;
				//scrolls bars offset
				Ox = 0 ;  Oy = 0 ;
				//don't need to put scroll bars in window
			//------------------------------------------------------------------+
			};//end else
		};//end else default - constraint all - best fit

	}//end if, image is not zoomed 
	else{//zoom_status = true, image is zoomed
		//the image is zoomed - algorith like in 
		//mvZoom... functions (In, Out)
		//check the constraint type of image displaing mode in window
		
		mvGetImageDimensions(&pictureW, &pictureH) ;

		int _pictureH = (int) ((pictureH*proportion)/100.) ;
		int _pictureW = (int) ((pictureW*proportion)/100.) ;	
		 
		if(constraintType == 0)//no  constraint
		{
			//do the job
zoom_constraint_nothing:
		;
			CRect rect ;
			GetClientRect(this->m_hwnd, &rect) ;
			
			if(angle == 0)
			{
			//------------------------------------------------------------------+
			//angle zero
				X=0; 
				Y=0;
				DW = _pictureW ;
				DH = _pictureH ;

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(_pictureW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - DW -1 - X)) 
						Ox = rect.Width()- DW -1-X ;
					if(Ox > abs(X)) 
						Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_nothing ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_nothing ;
					}
				};//else, image less than window

				//VERTICAL
				if(_pictureH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - DH -1 - Y)) Oy = rect.Height()- DH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//vertical scroll bar position
					scrollV = abs(Oy) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_nothing ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_nothing ;
					}
				}
	
			//------------------------------------------------------------------+
			}else if(angle == 90)
			{
			//------------------------------------------------------------------+
			//angle 90
				X = 0 ;
				Y = -1*_pictureH ;
				DW = _pictureW ;
				DH = _pictureH ;

				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(_pictureW > rect.Height())
				{//scroll offset							
					if(Ox < (-1)*(DW - rect.Height()- 1) )  
						Ox = (-1)*(DW - rect.Height()- 1) ;
					if(Ox > 0) 
						Ox = 0 ;
					
					//vertical scroll bar position
					scrollV = abs(Ox) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_nothing ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_nothing ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(_pictureH > rect.Width())
				{//scroll offset				
					if(Oy > (DH - rect.Width()-1))  Oy = (DH - rect.Width()-1) ;
					if(Oy < 0) Oy = 0 ;

					//horizontal scroll bar position
					scrollH = abs(Oy) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_nothing ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_nothing ;
					}
				}
			//------------------------------------------------------------------+
			}else if(angle == 180)
			{
			//------------------------------------------------------------------+	
			//angle 180
				X = -1*_pictureW  ;
				Y = -1*_pictureH  ;
				DW = _pictureW ;
				DH = _pictureH ;

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(_pictureW > rect.Width())
				{//scroll offset							
					if(Ox > (DW - rect.Width()-1))  Ox = (DW - rect.Width()-1) ;
					if(Ox < 0 ) Ox = 0  ;
					
					//horizontal scroll bar position
					scrollH = abs(Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;

					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_nothing ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_nothing ;
					}
				};//else, image less than window

				//VERTICAL
				if(_pictureH > rect.Height())
				{//scroll offset				
					if( Oy > DH - rect.Height() - 1 )
						Oy = DH - rect.Height() - 1 ;
					if(Oy < 0)
						Oy = 0 ;

					//vertical scroll bar position
					scrollV = abs(Oy) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_nothing ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_nothing ;
					}
				}
			//------------------------------------------------------------------+
			}else if(angle == 270)
			{
			//------------------------------------------------------------------+		
			//angle 270
				X = -1*_pictureW ;
				Y = 0 ;
				DW = _pictureW ;
				DH = _pictureH ;

				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(_pictureW > rect.Height())
				{//scroll offset							
					if( Ox > DW - rect.Height() - 1 )
						Ox = DW - rect.Height() - 1 ;
					if(Ox < 0)
						Ox = 0 ;
					
					//vertical scroll bar position
					scrollV = abs(Ox) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_nothing ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_nothing ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(_pictureH > rect.Width())
				{//scroll offset				
					if(Oy < (rect.Width() - DH -1 -Y))  Oy = rect.Width()- DH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//horizontal scroll bar position
					scrollH = abs(Oy) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_nothing ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_nothing ;
					}
				}
			//------------------------------------------------------------------+
			}else
			{
			//------------------------------------------------------------------+
			//angle zero default
				X = 0 ;
				Y = 0 ;
				DW = _pictureW ;
				DH = _pictureH ;

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(_pictureW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_nothing ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_nothing ;
					}
				};//else, image less than window

				//VERTICAL
				if(_pictureH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;
			
					//vertical scroll bar position
					scrollV = abs(Oy) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_nothing ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_nothing ;
					}
				}
			//------------------------------------------------------------------+
			}
		}else if(constraintType == 1)//constraint all - best fit
		{
			//do the job
zoom_constraint_all:
		;
			CRect rect ;
			GetClientRect(this->m_hwnd, &rect) ;
			
			if(angle == 0)
			{
			//------------------------------------------------------------------+
				//angle ZERO
				//new zoomed dimensions
				DH = _pictureH ;
				DW = _pictureW ;
				
				X=(rect.Width()  - DW ) / 2;  
				Y=(rect.Height() - DH ) / 2;  //new positions

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(_pictureW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(X + Ox) ;


					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_all ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_all ;
					}
				};//else, image less than window

				//VERTICAL
				if(_pictureH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//vertical scroll bar position
					scrollV = abs(Y + Oy) ;				


					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_all ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_all ;
					}
				}
			//------------------------------------------------------------------+
			}else if(angle == 90)
			{	
			//------------------------------------------------------------------+
				//angle 90
				//new zoomed dimensions
				DW = _pictureW ;
				DH = _pictureH ;
				X = (rect.Height() - DW) / 2 ;
				Y = -1*DH - (rect.Width() - DH)/2 ;

				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(_pictureW > rect.Height())
				{//scroll offset							
					if(Ox < (rect.Height() - _pictureW -1-X)) Ox = rect.Height()- _pictureW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//vertical scroll bar position
					scrollV = abs(X + Ox) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_all ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_all ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(_pictureH > rect.Width())
				{//scroll offset				
					if(Oy > (-1)*DH + (DH - rect.Width()-1) - Y)
						Oy = (-1)*DH + (DH - rect.Width()-1) - Y ;
					if(Oy < (-1)*DH - Y) 
						Oy = (-1)*DH - Y ;
					
					//horizontal scroll bar position
					scrollH = abs(Oy + DH + Y) ;


					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_all ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_all ;
					}
				}
			//------------------------------------------------------------------+
			}else if(angle == 180)
			{
			//------------------------------------------------------------------+
				//angle 180
				//new zoomed dimensions
				DW = _pictureW ;
				DH = _pictureH ;
				X = -1*DW - (rect.Width() - DW) / 2 ;
				Y = -1*DH - (rect.Height() - DH) /2 ;

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(_pictureW > rect.Width())
				{//scroll offset							
					if(Ox > (-1)*DW + (DW - rect.Width()-1) - X)
						Ox = (-1)*DW + (DW - rect.Width()-1) - X ;
					if(Ox < (-1)*DW - X) 
						Ox = (-1)*DW - X ;
					
					//horizontal scroll bar position
					scrollH = abs(Ox + DW + X) ;


					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_all ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_all ;
					}
				};//else, image less than window

				//VERTICAL
				if(_pictureH > rect.Height())
				{//scroll offset				
					if(Oy >	(-1)*DH + (DH - rect.Height()-1) - Y)
						Oy = (-1)*DH + (DH - rect.Height()-1) - Y ;
					if(Oy < (-1)*DH - Y) 
						Oy = (-1)*DH - Y ;

					//vertical scroll bar position
					scrollV = abs(Oy + DH + Y) ;	

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_all ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_all ;
					}
				}
			//------------------------------------------------------------------+
			}else if(angle == 270)
			{
			//------------------------------------------------------------------+
				//angle 270
				//new zoomed dimensions
				DW = _pictureW ;
				DH = _pictureH ;
				X = -1*DW - (rect.Height() - DW) /2 ;
				Y = (rect.Width() - DH) / 2 ;

				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(_pictureW > rect.Height())
				{//scroll offset							
					if(Ox >	(-1)*DW + (DW - rect.Height()-1) - X)
						Ox = (-1)*DW + (DW - rect.Height()-1) - X ;
					if(Ox < (-1)*DW - X) 
						Ox = (-1)*DW - X ;
					
					//vertical scroll bar position
					scrollV = abs(Ox + DW + X) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_all ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_all ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(_pictureH > rect.Width())
				{//scroll offset				
					if(Oy < (rect.Width() - DH -1 -Y))  Oy = rect.Width()- DH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//horizontal scroll bar position
					scrollH = abs(Oy + Y) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_all ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_all ;
					}
				}
			//------------------------------------------------------------------+
			}else{
			//------------------------------------------------------------------+
				//angle ZERO
				//new zoomed dimensions
				DW = _pictureW ;
				DH = _pictureH ;
				X = (rect.Width() - DW) / 2 ;
				Y = (rect.Height() - DH) / 2;

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(_pictureW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(X + Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_all ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_all ;
					}
				};//else, image less than window

				//VERTICAL
				if(_pictureH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;
					
					//vertical scroll bar position
					scrollV = abs(Y + Oy) ;	

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_all ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_all ;
					}
				}
			//------------------------------------------------------------------+
			};//end else
		}else if(constraintType == 2)//constraint height 
		{
			//do the job
zoom_constraint_height:
		;
			CRect rect ;
			GetClientRect(this->m_hwnd, &rect) ;

			if(angle == 0)
			{
			//--------------------------------------------------------------+
			//rotated ZERO
				/*DH=rect.Height() ;
				DW=(DH*_pictureW)/_pictureH ;*/
				DW = _pictureW ;
				DH = _pictureH ;
				X=(rect.Width()  - DW) / 2;  
				Y=(rect.Height() - DH) / 2;  

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(_pictureW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(X + Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_height;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_height ;
					}
				};//else, image less than window

				//VERTICAL
				if(_pictureH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//vertical scroll bar position
					scrollV = abs(Y + Oy) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_height ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_height ;
					}
				}
			//--------------------------------------------------------------+
			}else if(angle == 90)
			{
			//--------------------------------------------------------------+
			//rotated 90
				/*DW=rect.Height();			
				DH=(DW*_pictureH)/_pictureW;*/
				DW = _pictureW ;
				DH = _pictureH ;
				X = (rect.Height() - DW) / 2 ;
				Y = -1*DH -1*(rect.Width() - DH)/2 ;

				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(_pictureW > rect.Height())
				{//scroll offset							
					if(Ox < (rect.Height() - DW -1 - X)) 
						Ox = rect.Height() - DW -1 - X ;
					if(Ox > abs(X) ) 
						Ox = abs(X) ;
					
					//vertical scroll bar position
					scrollV = abs(X + Ox) ;	

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_height ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_height ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(_pictureH > rect.Width())
				{//scroll offset				
					if(Oy > (-1)*DH + (DH - rect.Width()-1) - Y)
						Oy = (-1)*DH + (DH - rect.Width()-1) - Y ;
					if(Oy < (-1)*DH - Y) 
						Oy = (-1)*DH - Y ;

					//horizontal scroll bar position
					scrollH = abs(Oy + DH + Y) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_height;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_height ;
					}
				}
			//--------------------------------------------------------------+
			}else if(angle == 180)
			{
			//--------------------------------------------------------------+
			//rotated 180
				/*DH=rect.Height() ;					
				DW=(DH*_pictureW)/_pictureH ;*/
				DW = _pictureW ;
				DH = _pictureH ;
				X = -1*DW - (rect.Width() - DW) / 2 ;
				Y = -1*DH - (rect.Height() - DH) /2 ;

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(_pictureW > rect.Width())
				{//scroll offset							
					if(Ox > (-1)*DW + (DW - rect.Width()-1) - X)
						Ox = (-1)*DW + (DW - rect.Width()-1) - X ;
					if(Ox < (-1)*DW - X) 
						Ox = (-1)*DW - X ;
					
					//horizontal scroll bar position
					scrollH = abs(Ox + DW + X) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_height;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false;
						goto zoom_constraint_height;
					}
				};//else, image less than window

				//VERTICAL
				if(_pictureH > rect.Height())
				{//scroll offset				
					if(Oy >	(-1)*DH + (DH - rect.Height()-1) - Y)
						Oy = (-1)*DH + (DH - rect.Height()-1) - Y;
					if(Oy < (-1)*DH - Y) 
						Oy = (-1)*DH - Y;

					//vertical scroll bar position
					scrollV = abs(Oy + DH + Y);

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureH;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_height ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_height ;
					}
				}
			//--------------------------------------------------------------+
			}else if(angle == 270)
			{
			//--------------------------------------------------------------+
			//rotated 270
				/*DW=rect.Height();			
				DH=(DW*_pictureH)/_pictureW;*/
				DW = _pictureW ;
				DH = _pictureH ;
				X = -1*DW - (rect.Height() - DW) /2 ;
				Y = (rect.Width() - DH) / 2 ;

				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(_pictureW > rect.Height())
				{//scroll offset							
					if(Ox >	(-1)*DW + (DW - rect.Height()-1) - X)
						Ox = (-1)*DW + (DW - rect.Height()-1) - X ;
					if(Ox < (-1)*DW - X) 
						Ox = (-1)*DW - X ;
					
					//vertical scroll bar position
					scrollV = abs(Ox + DW + X) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_height ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_height ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(_pictureH > rect.Width())
				{//scroll offset				
					if(Oy < (rect.Width() - DH -1 -Y))  Oy = rect.Width()- DH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//horizontal scroll bar position
					scrollH = abs(Oy + Y) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_height;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_height ;
					}
				}
			//--------------------------------------------------------------+
			}else {
			//--------------------------------------------------------------+
			//default - rotated ZERO
				/*DH=rect.Height() ;				
				DW=(DH*_pictureW)/_pictureH ;*/
				DW = _pictureW ;
				DH = _pictureH ;
				X = (rect.Width() - DW) / 2 ;
				Y = (rect.Height() - DH) / 2;

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(_pictureW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(X + Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_height;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_height ;
					}
				};//else, image less than window

				//VERTICAL
				if(_pictureH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//vertical scroll bar position
					scrollV = abs(Y + Oy) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_height ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_height ;
					}
				}
			//--------------------------------------------------------------+
			};//end else
		}else if(constraintType == 3)//constraint width
		{
			//do the job
zoom_constraint_width :
		;
			CRect rect ;
			GetClientRect(this->m_hwnd, &rect) ;
			
			if(angle == 0)
			{
			//---------------------------------------------------------------+
			//rotated 0
				/*DW = rect.Width() ;
				DH = (DW*_pictureH) / _pictureW ;*/
				DW = _pictureW ;
				DH = _pictureH ;
				X=(rect.Width()  - DW ) / 2;  
				Y=(rect.Height() - DH ) / 2;  

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(_pictureW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(X + Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_width;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_width ;
					}
				};//else, image less than window

				//VERTICAL
				if(_pictureH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//vertical scroll bar position
					scrollV = abs(Y + Oy) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_width ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_width ;
					}
				}
			//---------------------------------------------------------------+
			}else if(angle == 90)
			{
			//---------------------------------------------------------------+
			//rotated 90
				/*DH = rect.Width() ;
				DW = (DH*_pictureW) / _pictureH ;*/
				DW = _pictureW ;
				DH = _pictureH ;
				X = (rect.Height() - DW) / 2 ;
				Y = -1*DH -1*(rect.Width() - DH)/2 ;

				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(_pictureW > rect.Height())
				{//scroll offset							
					if(Ox < (rect.Height() - _pictureW -1-X)) Ox = rect.Height()- _pictureW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//vertical scroll bar position
					scrollV = abs(X + Ox) ;	

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_width ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_width ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(_pictureH > rect.Width())
				{//scroll offset				
					if(Oy > (-1)*DH + (DH - rect.Width()-1) - Y)
						Oy = (-1)*DH + (DH - rect.Width()-1) - Y ;
					if(Oy < (-1)*DH - Y) 
						Oy = (-1)*DH - Y ;

					//horizontal scroll bar position
					scrollH = abs(Oy + DH + Y) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_width;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_width ;
					}
				}
			//---------------------------------------------------------------+
			}else if(angle == 180)
			{
			//---------------------------------------------------------------+
			//rotated 180
				/*DW=rect.Width();
				DH=(DW*_pictureH)/_pictureW;*/
				DW = _pictureW ;
				DH = _pictureH ;
				X = -1*DW - (rect.Width() - DW) / 2 ;
				Y = -1*DH - (rect.Height() - DH) /2 ;

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(_pictureW > rect.Width())
				{//scroll offset							
					if(Ox > (-1)*DW + (DW - rect.Width()-1) - X)
						Ox = (-1)*DW + (DW - rect.Width()-1) - X ;
					if(Ox < (-1)*DW - X) 
						Ox = (-1)*DW - X ;
					
					//horizontal scroll bar position
					scrollH = abs(Ox + DW + X) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_width;
					}

				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_width ;
					}
				};//else, image less than window

				//VERTICAL
				if(_pictureH > rect.Height())
				{//scroll offset				
					if(Oy >	(-1)*DH + (DH - rect.Height()-1) - Y)
						Oy = (-1)*DH + (DH - rect.Height()-1) - Y ;
					if(Oy < (-1)*DH - Y) 
						Oy = (-1)*DH - Y ;

					//vertical scroll bar position
					scrollV = abs(Oy + DH + Y) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_width ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_width ;
					}
				}
			//---------------------------------------------------------------+
			}else if(angle == 270)
			{
			//---------------------------------------------------------------+
			//rotated 270
				/*DH=rect.Width() ;
				DW=(DH*_pictureW)/_pictureH ;*/
				DW = _pictureW ;
				DH = _pictureH ;
				X = -1*DW - (rect.Height() - DW) /2 ;
				Y = (rect.Width() - DH) / 2 ;

				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(_pictureW > rect.Height())
				{//scroll offset							
					if(Ox >	(-1)*DW + (DW - rect.Height()-1) - X)
						Ox = (-1)*DW + (DW - rect.Height()-1) - X ;
					if(Ox < (-1)*DW - X) 
						Ox = (-1)*DW - X ;
					
					//vertical scroll bar position
					scrollV = abs(Ox + DW + X) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_width ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_width ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(_pictureH > rect.Width())
				{//scroll offset				
					if(Oy < (rect.Width() - DH -1 -Y))  Oy = rect.Width()- DH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//horizontal scroll bar position
					scrollH = abs(Oy + Y) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_width;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_width ;
					}
				}
			//---------------------------------------------------------------+
			}else {
			//---------------------------------------------------------------+	
			//default 
				/*DW=rect.Width();
				DH=(DW*_pictureH)/_pictureW;*/
				DW = _pictureW ;
				DH = _pictureH ;
				X = (rect.Width() - DW) / 2 ;
				Y = (rect.Height() - DH) / 2;

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(_pictureW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(X + Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_width;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_width ;
					}
				};//else, image less than window

				//VERTICAL
				if(_pictureH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;
					
					//vertical scroll bar position
					scrollV = abs(Y + Oy) ;	

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_width ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_width ;
					}
				}
			//---------------------------------------------------------------+	
			}
		}else{//constrant all - best fit - default option
			//do the job
zoom_constraint_all2:
		;
			CRect rect ;
			GetClientRect(this->m_hwnd, &rect) ;
			
			if(angle == 0)
			{
			//------------------------------------------------------------------+
				//angle ZERO
				//new zoomed dimensions
				DH = _pictureH ;
				DW = _pictureW ;
				
				X=(rect.Width()  - DW ) / 2;  
				Y=(rect.Height() - DH ) / 2;  //new positions

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(_pictureW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(X + Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_all2;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_all2 ;
					}
				};//else, image less than window

				//VERTICAL
				if(_pictureH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//vertical scroll bar position
					scrollV = abs(Y + Oy) ;	

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_all2 ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_all2 ;
					}
				}
			//------------------------------------------------------------------+
			}else if(angle == 90)
			{	
			//------------------------------------------------------------------+
				//angle 90
				//new zoomed dimensions
				DW = _pictureW ;
				DH = _pictureH ;
				X = (rect.Height() - DW) / 2 ;
				Y = -1*DH -1*(rect.Width() - DH)/2 ;

				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(_pictureW > rect.Height())
				{//scroll offset							
					if(Ox < (rect.Height() - DW -1 - X)) 
						Ox = rect.Height() - DW -1 - X ;
					if(Ox > abs(X) ) 
						Ox = abs(X) ;
					
					//vertical scroll bar position
					scrollV = abs(X + Ox) ;	

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_all2 ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_all2 ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(_pictureH > rect.Width())
				{//scroll offset				
					if(Oy > (-1)*DH + (DH - rect.Width()-1) - Y)
						Oy = (-1)*DH + (DH - rect.Width()-1) - Y ;
					if(Oy < (-1)*DH - Y) 
						Oy = (-1)*DH - Y ;

					//horizontal scroll bar position
					scrollH = abs(Oy + DH + Y) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_all2;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_all2 ;
					}
				}
			//------------------------------------------------------------------+
			}else if(angle == 180)
			{
			//------------------------------------------------------------------+
				//angle 180
				//new zoomed dimensions
				DW = _pictureW ;
				DH = _pictureH ;
				X = -1*DW - (rect.Width() - DW) / 2 ;
				Y = -1*DH - (rect.Height() - DH) /2 ;
				
				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(_pictureW > rect.Width())
				{//scroll offset							
					if(Ox > (-1)*DW + (DW - rect.Width()-1) - X)
						Ox = (-1)*DW + (DW - rect.Width()-1) - X ;
					if(Ox < (-1)*DW - X) 
						Ox = (-1)*DW - X ;
					
					//horizontal scroll bar position
					scrollH = abs(Ox + DW + X) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;

					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_all2;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_all2 ;
					}
				};//else, image less than window

				//VERTICAL
				if(_pictureH > rect.Height())
				{//scroll offset				
					if(Oy >	(-1)*DH + (DH - rect.Height()-1) - Y)
						Oy = (-1)*DH + (DH - rect.Height()-1) - Y ;
					if(Oy < (-1)*DH - Y) 
						Oy = (-1)*DH - Y ;

					//vertical scroll bar position
					scrollV = abs(Oy + DH + Y) ;				


					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_all2 ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_all2 ;
					}
				}
			//------------------------------------------------------------------+
			}else if(angle == 270)
			{
			//------------------------------------------------------------------+
				//angle 270
				//new zoomed dimensions
				DW = _pictureW ;
				DH = _pictureH ;
				X = -1*DW - (rect.Height() - DW) /2 ;
				Y = (rect.Width() - DH) / 2 ;
				
				//calculate scroll bars position & set info V-vertical , H-horizontal
				int scrollV = 0, scrollH = 0 ;

				//test if image dimensions are great than window's dimensions
				//VERTICAL
				if(_pictureW > rect.Height())
				{//scroll offset							
					if(Ox >	(-1)*DW + (DW - rect.Height()-1) - X)
						Ox = (-1)*DW + (DW - rect.Height()-1) - X ;
					if(Ox < (-1)*DW - X) 
						Ox = (-1)*DW - X ;
					
					//vertical scroll bar position
					scrollV = abs(Ox + DW + X) ;	

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureW ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_all2 ;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_all2 ;
					}
				};//else, image less than window

				//HORIZONTAL
				if(_pictureH > rect.Width())
				{//scroll offset				
					if(Oy < (rect.Width() - DH -1 -Y))  Oy = rect.Width()- DH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//horizontal scroll bar position
					scrollH = abs(Oy + Y) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureH ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_all2;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_all2 ;
					}
				}

			//------------------------------------------------------------------+
			}else{
			//------------------------------------------------------------------+
				//angle ZERO
				//new zoomed dimensions
				DW = _pictureW ;
				DH = _pictureH ;
				X = (rect.Width() - DW) / 2 ;
				Y = (rect.Height() - DH) / 2;

				//calculate scroll bars position & set info
				int scrollV = 0, scrollH = 0 ;

				//test if image dimensions are great than window's dimensions
				//HORIZONTAL
				if(_pictureW > rect.Width())
				{//scroll offset							
					if(Ox < (rect.Width() - _pictureW -1 - X)) Ox = rect.Width()- _pictureW -1-X ;
					if(Ox > abs(X)) Ox = abs(X) ;
					
					//horizontal scroll bar position
					scrollH = abs(X + Ox) ;

					m_HSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_HSInfo.fMask  = SIF_PAGE | SIF_RANGE  | SIF_POS ; 
					m_HSInfo.nMin = 0 ;
					m_HSInfo.nMax = _pictureW ;
					m_HSInfo.nPage = rect.Width() ; 
					m_HSInfo.nPos = scrollH ;
					SetScrollInfo(this->m_hwnd, SB_HORZ, &m_HSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_HORZ,0, _pictureW, TRUE);
					SetScrollPos(this->m_hwnd, SB_HORZ, scrollH, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, TRUE) ;
					if(b_HSBarVisible == false)
					{
						b_HSBarVisible = true ;
						goto zoom_constraint_all2;
					}
				}else{//if no -no scroll bar is needed
					Ox = 0 ;
					ShowScrollBar(this->m_hwnd, SB_HORZ, FALSE) ;
					if(b_HSBarVisible == true)
					{
						b_HSBarVisible = false ;
						goto zoom_constraint_all2 ;
					}
				};//else, image less than window

				//VERTICAL
				if(_pictureH > rect.Height())
				{//scroll offset				
					if(Oy < (rect.Height() - _pictureH -1 - Y))  Oy = rect.Height()- _pictureH -1-Y ;
					if(Oy > abs(Y)) Oy = abs(Y) ;

					//vertical scroll bar position
					scrollV = abs(Y + Oy) ;

					m_VSInfo.cbSize = sizeof(SCROLLINFO) ;
					m_VSInfo.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS ; 
					m_VSInfo.nMin = 0 ;
					m_VSInfo.nMax = _pictureH ;	
					m_VSInfo.nPage = rect.Height() ; 		
					m_VSInfo.nPos = scrollV ;
					SetScrollInfo(this->m_hwnd, SB_VERT, &m_VSInfo, TRUE) ;
					SetScrollRange(this->m_hwnd, SB_VERT, 0, _pictureH, TRUE);
					SetScrollPos(this->m_hwnd, SB_VERT, scrollV, TRUE) ;
					ShowScrollBar(this->m_hwnd, SB_VERT, TRUE) ;
					if(b_VSBarVisible == false)
					{
						b_VSBarVisible = true ;
						goto zoom_constraint_all2 ;
					}
				}else{
					Oy = 0 ;
					ShowScrollBar(this->m_hwnd, SB_VERT, FALSE) ;
					if(b_VSBarVisible == true)
					{
						b_VSBarVisible = false ;
						goto zoom_constraint_all2 ;
					}
				}
			//------------------------------------------------------------------+
			};//end else
		};//end else default - constraint all - best fit				
	};//end else- test image , image is zoomed


	//----------------------------------------------------------------+
	//finished computing the image
	b_computeImage  = false ;

	//erase the background , display the image
	mvShowImage();
	//finish mvOnSize(UINT, int, int, )
	//return true ;	
}



//mvOnPaint provide functionality for WM_PAINT message
//that is received by the window when it is resized
//it is the poorest way to implement paint method, lack of time ... sorry for this
//after-thought, clipping regions desired for fast painting. 
void mvImage::mvOnPaint()
{
	if(image_loaded != true || m_hwnd == 0x000000 || image == 0x000000)
		return ;
			
	if(b_computeImage == true) return ;
	//else ...
	b_computeImage = true ;//processing the image
	//simply show image
	mvShowImageBackground(false);
	UpdateWindow(m_hwnd);
	//processing the image is finished.
	b_computeImage = false ;
	
}


//select first page from a multi-page tiff image
//as current page
//mvGoToFrame display the image instead...
void mvImage::mvFrameFirst()
{
	if(frameCount>1)
	{
		frameSelected = 0;
		mvGoToFrame(frameSelected) ;		
	}
}


//select last page from a multi-page image
//as current page
//mvGoToFrame display the image instead...
void mvImage::mvFrameLast()
{
	if(frameCount>1)
	{
		frameSelected = frameCount-1;
		mvGoToFrame(frameSelected) ;		
	}
}


//navigate in multi-page image
void mvImage::mvGoToFrame(UINT frame)
{		
	if(frameCount>1 && frame < frameCount && frame >= 0)
	{
		frameSelected = frame ;
		CString tempDir ="";					
		GetTempPath(255, tempDir.GetBuffer(255)) ;
		
		CString temp_file ="" ;
		temp_file.Format(_T("%s%s%c%s"), 
						tempDir, 
						_T("~DFFS5E_"),		//forever in temp									
						'.',
						_T("tmp")) ; 

		
		WCHAR wcfile_name [255] ;					
		MultiByteToWideChar(
			  CP_THREAD_ACP,        // code page
			  MB_PRECOMPOSED,       // character-type options
			  (LPCSTR) temp_file.GetBuffer(255),	// address of string to map
			  -1,      // number of bytes in string
			  (WCHAR*) wcfile_name,  // (LPWSTR)  address of wide-character buffer
			  255        // size of buffer
			);
		
		
		//frees image file, blocked by image pointer :)
		if(image) {
			delete image ;
			image = NULL ;
			image = (Image*) malloc(sizeof(Image)) ;
		}
		//delete temp if any ...
		if(b_decompressed == true)	
		{
			mvClearTempFiles() ;
		}
		
		//load desired one ...
		try
		{
			WCHAR *filename = imagePath.AllocSysString();
			image=Image::FromFile(filename);  
		}
		catch(...)
		{
			image_loaded=false;
			
			LANGID dwLanguageID = GetSystemLanguagePrimaryID();
			switch(dwLanguageID)
			{
			case LANG_SPANISH:
				AfxMessageBox(_T("Image load failed !"));
				break;
			default:
				AfxMessageBox(_T("fallo en el proceso de cargar la imagen!"));
				break;
			}
		}



		image->SelectActiveFrame(&pDimensionIDs[0], frameSelected) ;
		CLSID  encoderClsid;
		mvGetEncoderClsid(L"image/bmp", &encoderClsid);
		//save frame as bmp format in temp dir				
		Status st = image->Save(wcfile_name , &encoderClsid, NULL);					
		if (st != Ok)
		{
			LANGID dwLanguageID = GetSystemLanguagePrimaryID();
			
			switch(dwLanguageID)
			{
			case LANG_SPANISH:
				AfxMessageBox(_T("Salvando error en imagen")) ;
				break;
			default:
				AfxMessageBox(_T("Saving image error")) ;
				break;
			}
		}

		//load desired one ...
		try
		{
			WCHAR *filename=temp_file.AllocSysString();
			image=Image::FromFile(filename);  
		}
		catch(...)
		{
			image_loaded=false;	
			LANGID dwLanguageID = GetSystemLanguagePrimaryID();
			switch(dwLanguageID)
			{
			case LANG_SPANISH:
				AfxMessageBox(_T("Image load failed !"));
				break;
			default:
				AfxMessageBox(_T("Fallo en el proceso de cargar la imagen!"));
				break;
			}
		}
		mvStretch_TIF() ;
		
		//erase background, show image
		mvShowImageBackground(true);
		//finish mvGoToFrame() 
		

	};//if
}




//select next page from a multi-page tiff image
//as current page, and test limit value
void mvImage::mvFrameNext()
{
	if(frameCount>1)
	if(frameSelected < frameCount-1)
	{
		frameSelected++;
		mvGoToFrame(frameSelected) ;		
	}
}





//select previous frame from a multiframe image
//as current frame, and test limit value
void mvImage::mvFramePrevious()
{
	if(frameCount>1)
	if(frameSelected > 0)
	{
		frameSelected--;
		mvGoToFrame(frameSelected) ;		
	}
}


//return the file name
//path="h:\opera\subfolder\arrows\image2008.tif"
//file name="image2008"
CString mvImage::mvGetFileName(CString filePath)
{
	int extIndex = filePath.ReverseFind('.') ;
	int slashIndex = filePath.ReverseFind('\\') ;
	CString file_name = filePath.Mid(slashIndex+1, extIndex - slashIndex -1) ;
	return file_name ;
}




//return the file extension
//path="h:\opera\subfolder\arrows\image2008.tif"
//file ext="tif"
CString mvImage::mvGetFileExtension(CString filePath)
{
	int extIndex = filePath.ReverseFind('.') ;
	CString file_ext = filePath.Right(filePath.GetLength() - extIndex - 1) ;
	return file_ext ;	
}




//gets the local installed encoder for image 'format'
int mvImage::mvGetEncoderClsid(const WCHAR *format, CLSID *pClsid)
{
   UINT  num = 0;          // number of image encoders
   UINT  size = 0;         // size of the image encoder array in bytes

   ImageCodecInfo* pImageCodecInfo = NULL;

   GetImageEncodersSize(&num, &size);
   if(size == 0)
      return -1;  // Failure

   pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
   if(pImageCodecInfo == NULL)
      return -1;  // Failure

   GetImageEncoders(num, size, pImageCodecInfo);

   for(UINT j = 0; j < num; ++j)
   {
      if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
      {
         *pClsid = pImageCodecInfo[j].Clsid;
         free(pImageCodecInfo);
         return j;  // Success
      }    
   }

   free(pImageCodecInfo);
   return -1;  // Failure
}



//clear image file from temp directory 
//which corespond to multiframe image at imagePath path
void mvImage::mvClearTempFiles()
{
	CString tempDir ="";					
	GetTempPath(255, tempDir.GetBuffer(255)) ;
	
	CString temp_file =_T("");
	temp_file.Format( _T("%s%s%c%s"), 
					tempDir, 
					_T("~DFFS5E_"),										
					'.',
					_T("tmp")) ; 	

	if( _tunlink( temp_file ) == -1 )
	{
		LPVOID lpMsgBuf;
		FormatMessage( 
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM | 
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,
			0,
			NULL 
		);

		LANGID dwLanguageID = GetSystemLanguagePrimaryID();
		
		switch(dwLanguageID)
		{
		case LANG_SPANISH:
			MessageBox( NULL, (LPCTSTR)lpMsgBuf, _T("Borrar fichero temporal"), MB_OK | MB_ICONINFORMATION );
			break;
		default:
			MessageBox( NULL, (LPCTSTR)lpMsgBuf, _T("Delete temporary file"), MB_OK | MB_ICONINFORMATION );
			break;
		}
		
		LocalFree( lpMsgBuf );

	};//if unlink;

}



//make a 'great' discovery
//if U rotate graphics once 90º clockwise and once counter clockwise
//the tif image scrolls fastest than before ; Microsoft :(
DWORD WINAPI Stretch_TIF_Thread(LPVOID param);//thread needed here
void mvImage::mvStretch_TIF()
{	
	DWORD ID;
	threadHandle = ::CreateThread(NULL,0,Stretch_TIF_Thread,this,0,&ID);
	
	LANGID dwLanguageID = GetSystemLanguagePrimaryID();
	
	switch(dwLanguageID)
	{
	case LANG_SPANISH:
		if(!threadHandle)MessageBox(NULL, _T("Hilo no fue creado"),_T("Fatal error"),MB_OK);
		break;
	default:
		if(!threadHandle)MessageBox(NULL, _T("Thread not created"),_T("Fatal error"),MB_OK);
		break;
	}

}



/***********************************************
 *	Thread for stretching image in memory      *
 ***********************************************/
DWORD WINAPI Stretch_TIF_Thread(LPVOID param)
{
	mvImage *mvImg = (mvImage*) param ;
	mvImg->mvStretch_TIFF_InMemory() ;
	return 0 ;
}
/*	end StretchThread function*/




//do something weird (I don't know why)
//and the image will work in good condition, it is not 100 % truth
bool mvImage::mvStretch_TIFF_InMemory()
{
	CWnd wnd_class ;
	LPCTSTR	lpszClassName = _T("BUTTON") ;
	LPCTSTR	lpszWindowName = _T("window") ;
	DWORD dwStyle =	WS_CHILD ;
	RECT rect = {0, 0, 1000, 1000} ;
	CWnd* pParentWnd = AfxGetApp()->GetMainWnd() ;
	UINT nID = 1000 ;

	wnd_class.Create(
			lpszClassName,	//(LPCTSTR) class name
			lpszWindowName, // LPCTSTR window name
			dwStyle,		//DWORD window style
			rect  ,		//const RECT& rect
			pParentWnd,		//parent window
			nID	) ;			//The ID of the child window
			//CCreateContext* pContext = NULL
			//);

	wnd_class.ShowWindow(SW_HIDE) ;

	Graphics g(wnd_class.m_hWnd) ;

	INT pictX = 0, pictY  = 0;
	mvGetImageDimensions(&pictX, &pictY) ;	
	g.RotateTransform(90, MatrixOrderPrepend ) ; 
	g.DrawImage(image, 0, -1*pictY, pictX, pictY) ;
	
	wnd_class.DestroyWindow() ;
	return true ;
}



//true-is a valid image pointer, false -invalid image pointer
bool mvImage::mvIsValidImage()
{
	if(m_hwnd != 0x000000 && image != NULL && image_loaded)
	{
		return true ;
	}
	else
	{
		//AfxMessageBox(TEXT("La imágen no es válida"));
		return false ;
	}
}
