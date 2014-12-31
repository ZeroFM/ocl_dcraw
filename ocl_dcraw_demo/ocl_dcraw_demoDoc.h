// ocl_dcraw_demoDoc.h : interface of the Cocl_dcraw_demoDoc class
//


#pragma once


class Cocl_dcraw_demoDoc : public CDocument
{
protected: // create from serialization only
	Cocl_dcraw_demoDoc();
	DECLARE_DYNCREATE(Cocl_dcraw_demoDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~Cocl_dcraw_demoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


