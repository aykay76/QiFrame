// QiFrameDoc.cpp : implementation of the CQiFrameDoc class
//

#include "stdafx.h"
#include "QiFrame.h"

#include "QiFrameDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CQiFrameDoc

IMPLEMENT_DYNCREATE(CQiFrameDoc, CDocument)

BEGIN_MESSAGE_MAP(CQiFrameDoc, CDocument)
END_MESSAGE_MAP()


// CQiFrameDoc construction/destruction

CQiFrameDoc::CQiFrameDoc()
{
	// TODO: add one-time construction code here

}

CQiFrameDoc::~CQiFrameDoc()
{
}

BOOL CQiFrameDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CQiFrameDoc serialization

void CQiFrameDoc::Serialize(CArchive& ar)
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


// CQiFrameDoc diagnostics

#ifdef _DEBUG
void CQiFrameDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CQiFrameDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CQiFrameDoc commands
