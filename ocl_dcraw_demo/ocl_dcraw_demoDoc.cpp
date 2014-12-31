// ocl_dcraw_demoDoc.cpp : implementation of the Cocl_dcraw_demoDoc class
//

#include "stdafx.h"
#include "ocl_dcraw_demo.h"

#include "ocl_dcraw_demoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cocl_dcraw_demoDoc

IMPLEMENT_DYNCREATE(Cocl_dcraw_demoDoc, CDocument)

BEGIN_MESSAGE_MAP(Cocl_dcraw_demoDoc, CDocument)
END_MESSAGE_MAP()


// Cocl_dcraw_demoDoc construction/destruction

Cocl_dcraw_demoDoc::Cocl_dcraw_demoDoc()
{
	// TODO: add one-time construction code here

}

Cocl_dcraw_demoDoc::~Cocl_dcraw_demoDoc()
{
}

BOOL Cocl_dcraw_demoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// Cocl_dcraw_demoDoc serialization

void Cocl_dcraw_demoDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// Cocl_dcraw_demoDoc diagnostics

#ifdef _DEBUG
void Cocl_dcraw_demoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void Cocl_dcraw_demoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Cocl_dcraw_demoDoc commands
