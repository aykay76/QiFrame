// QiFrameDoc.h : interface of the CQiFrameDoc class
//


#pragma once

class CQiFrameDoc : public CDocument
{
protected: // create from serialization only
	CQiFrameDoc();
	DECLARE_DYNCREATE(CQiFrameDoc)

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
	virtual ~CQiFrameDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


