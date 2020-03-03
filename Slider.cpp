// Slider.cpp : implementation file
//

#include "stdafx.h"
#include "QiFrame.h"
#include "Slider.h"

#include "imagemanager.h"

using namespace Gdiplus;

// CSlider

IMPLEMENT_DYNAMIC(CSlider, CWnd)

CSlider::CSlider()
	: m_mouseOver(false)
	, m_mouseDown(false)
	, m_mouseLeft(false)
	, m_mouseRight(false)
	, m_imagePrefix(L"b-")
{

}

CSlider::~CSlider()
{
}


BEGIN_MESSAGE_MAP(CSlider, CWnd)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()



// CSlider message handlers

void CSlider::imagePrefix(wchar_t* prefix)
{
	m_imagePrefix = prefix;

	m_inactive = ImageManager::loadImage(m_imagePrefix + std::wstring(L"inactive.png"));
	m_hover = ImageManager::loadImage(m_imagePrefix + std::wstring(L"hover.png"));
	m_left = ImageManager::loadImage(m_imagePrefix + std::wstring(L"left.png"));
	m_right = ImageManager::loadImage(m_imagePrefix + std::wstring(L"right.png"));
}

void CSlider::PreSubclassWindow()
{
	CWnd::PreSubclassWindow();
}

void CSlider::OnPaint()
{
	CPaintDC dc(this);

	Graphics* g = Graphics::FromHWND(GetSafeHwnd());
	if (m_mouseOver)
	{
		if (m_mouseLeft)
		{
			g->DrawImage(m_left, 0, 0);
		}
		else if (m_mouseRight)
		{
			g->DrawImage(m_right, 0, 0);
		}
		else
		{
			g->DrawImage(m_hover, 0, 0);
		}
	}
	else
	{
		g->DrawImage(m_inactive, 0, 0);
	}

	delete g;
}

void CSlider::OnMouseMove(UINT nFlags, CPoint point)
{
	CRect rc;
	GetClientRect(rc);

	if (rc.PtInRect(point) == FALSE && !(nFlags & MK_LBUTTON))
	{
		ReleaseCapture();
		m_mouseOver = false;
		m_mouseLeft = false;
		m_mouseRight = false;
		RedrawWindow();
		return;
	}

	if (this != GetCapture())
	{
		SetCapture();
		m_mouseOver = true;
	}
	else
	{
		if (m_mouseDown)
		{
			m_dx = point.x - m_ptLast.x;
			m_dy = point.y - m_ptLast.y;

			if (point.x - m_ptLast.x < 0)
			{
				m_mouseLeft = true;

				GetParent()->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), 0), (LPARAM)GetSafeHwnd());
			}
			else
			{
				m_mouseLeft = false;
			}

			if (point.x - m_ptLast.x > 0)
			{
				m_mouseRight = true;

				GetParent()->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), 0), (LPARAM)GetSafeHwnd());
			}
			else
			{
				m_mouseRight = false;
			}

			POINT pt;
			pt.x = m_ptLast.x; pt.y = m_ptLast.y;
			ClientToScreen(&pt);
			SetCursorPos(pt.x, pt.y);
		}
	}

	RedrawWindow();

	CWnd::OnMouseMove(nFlags, point);
}

void CSlider::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_mouseDown = true;
	m_ptLast = point;
	
	m_ptDown = point;

	ShowCursor(FALSE);
}

void CSlider::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_mouseDown = false;
	m_mouseLeft = false;
	m_mouseRight = false;
	RedrawWindow();

	POINT pt; pt.x = m_ptDown.x; pt.y = m_ptDown.y;
	ClientToScreen(&pt);
	SetCursorPos(pt.x, pt.y);

	ShowCursor(TRUE);

	CWnd::OnLButtonUp(nFlags, point);
}

BOOL CSlider::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
//	SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_HAND)));
	return TRUE;
}
