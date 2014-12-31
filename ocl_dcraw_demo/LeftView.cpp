// LeftView.cpp : implementation of the CLeftView class
//

#include "stdafx.h"
#include "ocl_dcraw_demo.h"

#include "ocl_dcraw_demoDoc.h"
#include "LeftView.h"
#include "ocl_dcraw_demoView.h"
#include "MainFrm.h"
#include  <io.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CLeftView::OnNMDblclk)
END_MESSAGE_MAP()


// CLeftView construction/destruction

CLeftView::CLeftView()
{
	// TODO: add construction code here
}

CLeftView::~CLeftView()
{
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying the CREATESTRUCT cs

	return CTreeView::PreCreateWindow(cs);
}

void CLeftView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: You may populate your TreeView with items by directly accessing
	//  its tree control through a call to GetTreeCtrl().

	CTreeCtrl &treectrl=(CTreeCtrl&)GetTreeCtrl();
	LPITEMIDLIST pidl;
	LPMALLOC pShellMalloc;
	TCHAR szDir[200];
	LPWIN32_FIND_DATAW findresult;

	DWORD dwDrives; 
	char a; 
	dwDrives = GetLogicalDrives(); 
	a = 'A'; 
	char path[]="A:";
	while (dwDrives > 0) 
	{ 
		if (dwDrives % 2 == 1) 
		{ 
			HTREEITEM root=treectrl.InsertItem((CString)path, NULL, NULL, TVI_ROOT, TVI_LAST); 
			ListDir(path,root);
		} 
		a++; 
		path[0]=a;
		dwDrives /= 2; 
	} 



	//HTREEITEM h=treectrl.InsertItem(_T("DDD"),0,0,0,0);
	//ListDir("E:",h);
	//treectrl.InsertItem(_T("fsfs"),0,0,h,0);

}
#define MAXLEN 1024
void CLeftView::ListDir(const char* pchData, HTREEITEM root)  {  
	_finddata_t   fdata;                      //定义文件查找结构对象      
	long   done;         
	char tempdir[MAXLEN]={0};                 //定义一个临时字符数组，存储目录     
	strcat(tempdir, pchData);                 //连接字符串     
	strcat(tempdir, "\\*");            
	
	CTreeCtrl &treectrl=(CTreeCtrl&)GetTreeCtrl();

	done   =  _findfirst(tempdir, &fdata);  
	//开始查找文件     
	if (done != -1)                       //是否查找成功  
	{          
		int ret = 0;          
		while  (ret != -1)              //定义一个循环        
		{              
			if (fdata.attrib != _A_SUBDIR)    //判断文件属性          
			{                  
				if (strcmp(fdata.name,"...")  != 0 &&       
					strcmp(fdata.name,"..") != 0 &&                    
					strcmp(fdata.name,".") != 0)  //过滤                 
				{                      
					treectrl.InsertItem(CString(fdata.name),0,0,root,0);           
				}          
			}         
			else if (fdata.attrib == _A_SUBDIR && ret  != -1)     //判断文件属性，如果是目录，则递归调用            
			{                  
				if (strcmp(fdata.name,"...")  != 0 &&            
					strcmp(fdata.name,"..") != 0 &&                  
					strcmp(fdata.name,".") != 0)  //过滤                 
				{                     
					char pdir[MAXLEN]=  {0};      
					strcat(pdir,pchData);               
					strcat(pdir , "\\");              
					strcat(pdir,fdata.name);           
					HTREEITEM node=treectrl.InsertItem(CString(fdata.name),0,0,root,0);     
					ListDir(pdir,node);                    
					//递归调用                
				}             
			}          
			ret = _findnext(done, &fdata);      //查找下一个文件             
		}     
	}  
} 


// CLeftView diagnostics

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

Cocl_dcraw_demoDoc* CLeftView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cocl_dcraw_demoDoc)));
	return (Cocl_dcraw_demoDoc*)m_pDocument;
}
#endif //_DEBUG


// CLeftView message handlers

void CLeftView::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	CTreeCtrl &treectrl=(CTreeCtrl&)GetTreeCtrl();
	HTREEITEM hSel=treectrl.GetSelectedItem();
	if(hSel==NULL) return;
	CString name=treectrl.GetItemText(hSel);
	if(name.Right(4)!=".NEF" && name.Right(4)!=".DNG")
		return;
	hSel=treectrl.GetParentItem(hSel);
	while(hSel!=NULL)
	{
		name=treectrl.GetItemText(hSel)+CString("\\")+name;
		hSel=treectrl.GetParentItem(hSel);
	}
	Cocl_dcraw_demoView* demoView=(Cocl_dcraw_demoView*)((CMainFrame*)theApp.m_pMainWnd)->m_wndSplitter.GetPane(0,1);
	demoView->LoadTex(	name);
	demoView->OnPaint();
	*pResult = 0;
}
