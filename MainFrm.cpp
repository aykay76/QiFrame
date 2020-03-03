// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "QiFrame.h"

#include "MainFrm.h"
#include ".\mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_TOOLBOX, OnViewToolbox)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
/*
	if (!m_wndToolBar.CreateEx(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
*/
/*	if (!m_wndDlgBar.Create(this, IDR_MAINFRAME, 
		CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;		// fail to create
	}
*/
	if (!m_wndReBar.Create(this)/* ||
		!m_wndReBar.AddBar(&m_wndToolBar) ||
		!m_wndReBar.AddBar(&m_wndDlgBar)*/)
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}
/*
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
*/
	// enable docking for this the main window
	EnableDocking(CBRS_ALIGN_LEFT | CBRS_ALIGN_RIGHT);

//	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

	m_toolbox.Create(this, (UINT)IDD_TOOLBOX, WS_CHILD | CBRS_ALIGN_LEFT | CBRS_FLOAT_MULTI, AFX_IDW_CONTROLBAR_FIRST + 1);
	m_toolbox.EnableDocking(CBRS_ALIGN_ANY);
	m_toolbox.ShowWindow(SW_SHOW);
	m_toolbox.UpdateData(FALSE);
	m_toolbox.ModifyStyle(WS_BORDER, 0, 0);
	DockControlBar(&m_toolbox, AFX_IDW_DOCKBAR_LEFT);

//	ModifyStyle(WS_BORDER | WS_SYSMENU, 0, 0);
	ModifyStyleEx(WS_EX_CLIENTEDGE, 0, 0);

	CWnd* parent = m_toolbox.GetParent();
	SetClassLongPtr(parent->GetSafeHwnd(), GCLP_HBRBACKGROUND, (LONG_PTR)GetStockObject(WHITE_BRUSH));
	SetClassLongPtr(m_toolbox.GetSafeHwnd(), GCLP_HBRBACKGROUND, (LONG_PTR)GetStockObject(WHITE_BRUSH));

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		 | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE | WS_SYSMENU;

	return TRUE;
}


// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame message handlers


void CMainFrame::OnViewToolbox()
{
	if (m_toolbox.IsWindowVisible())
	{
		m_toolbox.ShowWindow(SW_HIDE);
		RecalcLayout();
	}
	else
	{
		m_toolbox.ShowWindow(SW_SHOW);
		RecalcLayout();
	}
}
