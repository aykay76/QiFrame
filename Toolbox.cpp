// Toolbox.cpp : implementation file
//

#include "stdafx.h"
#include "QiFrame.h"
#include "Toolbox.h"
#include ".\toolbox.h"


// CToolbox

IMPLEMENT_DYNAMIC(CToolbox, CDialogBar)
CToolbox::CToolbox()
{
}

CToolbox::~CToolbox()
{
}


BEGIN_MESSAGE_MAP(CToolbox, CDialogBar)
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CToolbox message handlers


void CToolbox::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_RELATIVE_TO, m_relativeTo);
	DDX_Control(pDX, IDC_COLOUR, m_colour);

	CDialogBar::DoDataExchange(pDX);
}

void CToolbox::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDialogBar::OnLButtonDown(nFlags, point);
}

BOOL CToolbox::OnEraseBkgnd(CDC* pDC)
{
	CRect rc;
	GetClientRect(&rc);

	pDC->FillSolidRect(rc, RGB(255, 255, 255));

	rc.left = rc.right - 5;
	pDC->FillSolidRect(rc, RGB(0, 0, 255));

	return TRUE;
}
int CToolbox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	return 0;
}
