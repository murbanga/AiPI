/*----------------------------------------------------------------------+
	mvImage class - image management class 
	uses GDI+ library
	created: 2006.05.04	by		Vasilian Mihai
	www.vasilianm.as.ro
------------------------------------------------------------------------+*/

#if !defined   __mvImage_h__
#define		   __mvImage_h__

//#include "Mainfrm.h"

//typedef unsigned __int64 ULONG_PTR;//gdi+ :-(
//#include ".\\ImplementationGDIPLUS\\gdiplus.h"
using namespace Gdiplus;




class mvImage  
{
/*methods*/
public:	
	bool mvIsValidImage();
	friend DWORD WINAPI Stretch_TIF_Thread(LPVOID param) ;
	void mvFramePrevious();
	void mvFrameNext();
	void mvGoToFrame(UINT frame);
	void mvFrameLast();
	void mvFrameFirst();
	void mvOnPaint();
	void mvOnSize(UINT nType, int cx=0, int cy =0);
	void mvOnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	void mvOnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	bool mvZoomOut();
	bool mvZoomIn();
	void mvRotateRight();
	void mvRotateLeft();
	bool mvConstraintWidth();
	bool mvConstraintHeight();
	bool mvConstraintNothing();
	bool mvConstraintAll();
	bool mvLoadImage(const CString &path);

	mvImage(HWND hwnd);
	mvImage();
	virtual ~mvImage();

/*methods*/
private:
	bool mvShowImage();
	bool mvShowImageBackground(bool eraseBackground);
	bool mvGetImageDimensions(int *imgX, int *imgY);
	CString mvGetFileExtension(CString filePath);
	CString mvGetFileName(CString filePath);
	int mvGetEncoderClsid(const WCHAR *format, CLSID *pClsid);
	void mvClearTempFiles();
	bool mvStretch_TIFF_InMemory();
	void mvStretch_TIF();




/*members*/
private:
	bool b_VSBarVisible; //true - vertical scroll bar visible, false - hidden
	bool b_HSBarVisible; //true - horizontal scroll bar visible, false - hidden
	bool b_computeImage; //true - scroll, rotate, constraint, zoom : in process
						 //false - none of above func. in process;
	bool b_decompressed; //true-image is decompressed in temp,false otherwise 
	HANDLE threadHandle; //thread used to stretch or rotate the image in memory	
	CString imagePath;	//original image path , not that decompresed in Temp directory
	GUID* pDimensionIDs;//used in multiframe images
	UINT frameCount;	//frames in multiframe tiff image
	UINT frameSelected;	//currently selected tiff frame
	bool zoom_status;	//default false; 
						//constraintType 1 with zoomed need scroll bars otherwise none;
						//it has to be tested to decide scroll bars appearance
	double proportion;	//express zoom raport, ranged from 10% to 500%
	int Ox;				//horizontal offset of image coresp. to horiz. scroll bar offset
	int Oy;				//vertical offset of image coresp. to vert. scroll bar offset
	SCROLLINFO m_HSInfo;//maintain information about horizontal bar
	SCROLLINFO m_VSInfo;//maintain information about vertical   bar 
	int constraintType;	//0 - original dimensions (no constraint)
						//1 - constraint all , best fit (default)
						//2 - constraint height
						//3 - constraint width
	float angle;		//rotation angle [0-360]
	HWND m_hwnd;		//window handle
	Image* image;		//image pointer
	bool image_loaded;	//true-loaded ; false-not loaded;
	int X ;				//oriented alog X axis , depend on rotation angle
	int	Y ;				//oriented alog Y axis , depend on rotation angle
	int	DW ;			//lenght of image alog X axis , depend on rotation angle
	int	DH ;			//lenght of image alog Y axis , depend on rotation angle
	int pictureW ;		//phisical width dimension of image, not rotated, not zoomed, etc
	int pictureH ;		//phisical height dimension of image, not rotated, not zoomed, etc

};

#endif 
