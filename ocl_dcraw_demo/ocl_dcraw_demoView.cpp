// ocl_dcraw_demoView.cpp : implementation of the Cocl_dcraw_demoView class
//

#include "stdafx.h"
#include "ocl_dcraw_demo.h"

#include "ocl_dcraw_demoDoc.h"
#include "ocl_dcraw_demoView.h"
#include "MainFrm.h"


#include "ocl_dcraw_dll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cocl_dcraw_demoView

IMPLEMENT_DYNCREATE(Cocl_dcraw_demoView, CView)

BEGIN_MESSAGE_MAP(Cocl_dcraw_demoView, CView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// Cocl_dcraw_demoView construction/destruction


Cocl_dcraw_demoView::Cocl_dcraw_demoView()
: m_GLPixelIndex(0)
, textName(0)
, CurSize(1)
, image_width(0)
, image_height(0)
, LButtonDown(false)
, LBDPoint(0)
, xDet(0)
, yDet(0)
, LxDet(0)
, LyDet(0)
, pro(0)
{
	// TODO: add construction code here
	this->m_hGLContext = NULL;
	//image_name="";
}

Cocl_dcraw_demoView::~Cocl_dcraw_demoView()
{
}


BOOL Cocl_dcraw_demoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style |= (WS_CLIPCHILDREN | WS_CLIPSIBLINGS);
	return CView::PreCreateWindow(cs);
}

// CmfctestView drawing

void Cocl_dcraw_demoView::OnDraw(CDC* /*pDC*/)
{
	//Cocl_dcraw_demoDoc* pDoc = GetDocument();
	//ASSERT_VALID(pDoc);
	//if (!pDoc)
	//	return;

	// TODO: add draw code for native data here
}


// CmfctestView printing

BOOL Cocl_dcraw_demoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void Cocl_dcraw_demoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void Cocl_dcraw_demoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}








bool Cocl_dcraw_demoView::SetWindowPixelFormat(HDC hDC)
{
	PIXELFORMATDESCRIPTOR pixelDesc=
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		
		PFD_TYPE_RGBA,
		24,
		0,0,0,0,0,0,
		0,
		0,
		0,
		0,0,0,0,
		32,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0,0,0
	};

	this->m_GLPixelIndex=ChoosePixelFormat(hDC,&pixelDesc);
	if(this->m_GLPixelIndex==0)
	{
		this->m_GLPixelIndex = 1;
		if(DescribePixelFormat(hDC,this->m_GLPixelIndex,sizeof(PIXELFORMATDESCRIPTOR),&pixelDesc)==0)
		{
			return false;
		}
	}

	if(SetPixelFormat(hDC,this->m_GLPixelIndex,&pixelDesc)==false)
		return false;

	return true;
}

bool Cocl_dcraw_demoView::CreateViewGLContext(HDC hDC)
{
	this->m_hGLContext = wglCreateContext(hDC);
	if(this->m_hGLContext == NULL)
	{
		return false;
	}

	if(wglMakeCurrent(hDC,this->m_hGLContext) == false)
		return false;

	return true;
}

int Cocl_dcraw_demoView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	HWND hWnd = this->GetSafeHwnd();
	HDC hDC= ::GetDC(hWnd);
	if(this->SetWindowPixelFormat(hDC) == false)
	{
		return 0;
	}

	if(this->CreateViewGLContext(hDC) == false)
		return 0;

	glClearColor(1,1,1,0);
	OclInit();
	
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);


	
	return 0;
}
extern Cocl_dcraw_demoApp theApp;
void Cocl_dcraw_demoView::LoadTex(CString path)
{
	char** arg=(char**)malloc(7*sizeof(char*));
	arg[0]="";
	arg[1]="-T";
	arg[2]="-w";
	arg[3]="-W";
	arg[4]="-b";
	arg[5]="4.0";
	path.ReleaseBuffer();
	int m = path.GetLength(); 
	arg[6]=(char *)malloc((m+1)*sizeof(char));
	for(int i=0;i<m;++i)
		arg[6][i]=path[i];
	arg[6][m]=0;
	short* image;
	int t=InterpolateImage(7,(const char**)arg,&image,&image_width,&image_height);

	if(textName!=0)
		glDeleteTextures(1,&textName);
	glPixelStorei(GL_UNPACK_ALIGNMENT,2);
	glGenTextures(1,&textName);
	glBindTexture(GL_TEXTURE_2D,textName);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,image_width,image_height,0,GL_RGBA,GL_UNSIGNED_SHORT,image);

	
	CString text;
	text.Format(_T("interpolate finish in %dms"),t);
	((CMainFrame*)theApp.m_pMainWnd)->m_wndStatusBar.SetPaneText(0,text);

	CRect rect;
	GetWindowRect(&rect);
	xDet=yDet=LxDet=LyDet=0;
	OnSize(0,rect.Width(),rect.Height());
}

void Cocl_dcraw_demoView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: Add your message handler code here
	if(wglGetCurrentContext() != NULL)
	{
		wglMakeCurrent(NULL,NULL);
	}
	if(this->m_hGLContext!=NULL)
	{
		wglDeleteContext(this->m_hGLContext);
		this->m_hGLContext = NULL;
	}
}

void Cocl_dcraw_demoView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here

	glViewport(0,0,cx,cy);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	if(image_width*cy>image_height*cx)
	{
		float aspect=1.0*image_width*cy/(image_height*cx);
		pro=1.0*cx/image_width;
		gluOrtho2D(-1.0, 1.0, -aspect, aspect);//*
	}
	else
	{
		float aspect=1.0*image_height*cx/(image_width*cy);
		pro=1.0*cy/image_height;
		gluOrtho2D( -aspect, aspect, -1.0, 1.0);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	xDet=yDet=LxDet=LyDet=0;
	//OnPaint();
}

void Cocl_dcraw_demoView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CView::OnPaint() for painting messages
	//glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0,0.0); glVertex2f(-CurSize+xDet,CurSize-yDet);
		glTexCoord2f(0.0,1.0); glVertex2f(-CurSize+xDet,-CurSize-yDet);
		glTexCoord2f(1.0,1.0); glVertex2f(CurSize+xDet,-CurSize-yDet);
		glTexCoord2f(1.0,0.0); glVertex2f(CurSize+xDet,CurSize-yDet);
	glEnd();
	
	glFlush();
	SwapBuffers(wglGetCurrentDC());
}

BOOL Cocl_dcraw_demoView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default
	if(zDelta>0)
	{
		if(CurSize<=16)
		{
			CurSize*=2;
			xDet*=2;
			yDet*=2;
		}
	}
	else if(zDelta<0)
	{
		if(CurSize>0.1)
		{
			CurSize/=2;
			xDet/=2;
			yDet/=2;
		}
	}
	if(CurSize==1.0)
	{
		xDet=0;
		yDet=0;
	}
	
	if(pro!=0)
	{
		CString text;
		text.Format(_T("%d%%"),(int)(100*pro*CurSize));
		((CMainFrame*)theApp.m_pMainWnd)->m_wndStatusBar.SetPaneText(0,text);
	}

	OnPaint();
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}



void Cocl_dcraw_demoView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	LButtonDown=true;
	LBDPoint=point;
	LxDet=xDet;
	LyDet=yDet;



	CView::OnLButtonDown(nFlags, point);
}


void Cocl_dcraw_demoView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if(nFlags & MK_LBUTTON )
	{
		CRect rect;
		GetWindowRect(&rect);
		xDet=LxDet + 1.0*(point.x-LBDPoint.x)/rect.Width();
		yDet=LyDet + 1.0*(point.y-LBDPoint.y)/rect.Height();
		HCURSOR m_cursorCur = LoadCursor(NULL, MAKEINTRESOURCE(IDC_POINTER_COPY));//AfxGetApp()->m_hInstance
		::SetCursor(m_cursorCur);
		OnPaint();
	}

	CView::OnMouseMove(nFlags, point);
}

BOOL Cocl_dcraw_demoView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
		
	return CView::OnSetCursor(pWnd, nHitTest, message);
}
void Cocl_dcraw_demoView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	LButtonDown=false;
	CView::OnLButtonUp(nFlags, point);
}
