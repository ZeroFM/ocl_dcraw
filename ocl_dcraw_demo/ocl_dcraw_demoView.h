// ocl_dcraw_demoView.h : interface of the Cocl_dcraw_demoView class
//


#pragma once


class Cocl_dcraw_demoView : public CView
{
protected: // create from serialization only
	Cocl_dcraw_demoView();
	DECLARE_DYNCREATE(Cocl_dcraw_demoView)

// Attributes
public:
	Cocl_dcraw_demoDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~Cocl_dcraw_demoView();


protected:

// Generated message map functions
protected:
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	DECLARE_MESSAGE_MAP()
	bool SetWindowPixelFormat(HDC hDC);
	bool CreateViewGLContext(HDC hDC);
	int m_GLPixelIndex;
	HGLRC m_hGLContext;
	GLuint textName;
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
private:
	float CurSize;
	int image_width;
	int image_height;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	void LoadTex(CString path);
private:
	bool LButtonDown;
	CPoint LBDPoint;
	float xDet;
	float yDet;
	float LxDet;
	float LyDet;
public:
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
private:
	float pro;
};

#ifndef _DEBUG  // debug version in ocl_dcraw_demoView.cpp
inline Cocl_dcraw_demoDoc* Cocl_dcraw_demoView::GetDocument() const
   { return reinterpret_cast<Cocl_dcraw_demoDoc*>(m_pDocument); }
#endif

