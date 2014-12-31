// ocl_dcraw_demo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ocl_dcraw_demo.h"
#include "MainFrm.h"

#include "ocl_dcraw_demoDoc.h"
#include "LeftView.h"
#include "ocl_dcraw_demoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cocl_dcraw_demoApp

BEGIN_MESSAGE_MAP(Cocl_dcraw_demoApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &Cocl_dcraw_demoApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &OnFileOpen)
END_MESSAGE_MAP()


// Cocl_dcraw_demoApp construction

Cocl_dcraw_demoApp::Cocl_dcraw_demoApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only Cocl_dcraw_demoApp object

Cocl_dcraw_demoApp theApp;


// Cocl_dcraw_demoApp initialization

BOOL Cocl_dcraw_demoApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)
	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(Cocl_dcraw_demoDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(Cocl_dcraw_demoView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);



	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// call DragAcceptFiles only if there's a suffix
	//  In an SDI app, this should occur after ProcessShellCommand
	return TRUE;
}



// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// App command to run the dialog
void Cocl_dcraw_demoApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

void Cocl_dcraw_demoApp::OnFileOpen()
{
	CFileDialog fileDlg(TRUE);
	if(fileDlg.DoModal()==IDOK)
	{
		Cocl_dcraw_demoView* demoView=(Cocl_dcraw_demoView*)((CMainFrame*)theApp.m_pMainWnd)->m_wndSplitter.GetPane(0,1);
		demoView->LoadTex(fileDlg.GetPathName());
			//m_wndStatusBar.SetPaneText(0,fileDlg.GetPathName());
	}
}

// Cocl_dcraw_demoApp message handlers

