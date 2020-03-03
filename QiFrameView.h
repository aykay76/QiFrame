// QiFrameView.h : interface of the CQiFrameView class
//


#pragma once

#include "../winfizz/engine/observer.h"
#include "../winfizz/engine/event.h"
#include <vector>
//#include "splitter.h"
//#include "topview.h"
//#include "leftview.h"
//#include "frontview.h"
//#include "3dview.h"
class GLWindows;
class CEntityPropertiesDlg;

class CQiFrameView : public CView, public Observer
{
protected: // create from serialization only
	CQiFrameView();
	DECLARE_DYNCREATE(CQiFrameView)

// Attributes
public:
	CQiFrameDoc* GetDocument() const;

enum Mode
{
	None, MovingObject, MovingVertex, Rotating
};

// Observer interface
public:
	virtual void update();

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
	virtual ~CQiFrameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
//	CSplitter m_splitter;
//	CTopView m_topView;
//	CLeftView m_leftView;
//	CFrontView m_frontView;
//	C3DView m_3dView;
	GLWindows* m_gl;
	int m_width;
	int m_height;
	int m_relativeTo;

	std::vector<Event *> m_subjects;

	CEntityPropertiesDlg* m_entityProperties;

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnXLeft();
	afx_msg void OnXRight();
	afx_msg void OnYLeft();
	afx_msg void OnYRight();
	afx_msg void OnZLeft();
	afx_msg void OnZRight();
	afx_msg void OnMoveXLeft();
	afx_msg void OnMoveXRight();
	afx_msg void OnMoveYLeft();
	afx_msg void OnMoveYRight();
	afx_msg void OnMoveZLeft();
	afx_msg void OnMoveZRight();
	afx_msg void OnSphere();
	afx_msg void OnTorus();
	afx_msg void OnLight();
	afx_msg void OnSelchangeRelativeTo();
public:
	afx_msg void OnDestroy();
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // debug version in QiFrameView.cpp
inline CQiFrameDoc* CQiFrameView::GetDocument() const
   { return reinterpret_cast<CQiFrameDoc*>(m_pDocument); }
#endif

