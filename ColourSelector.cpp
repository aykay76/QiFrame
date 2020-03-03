// ColourSelector.cpp : implementation file
//

#include "stdafx.h"
#include "QiFrame.h"
#include "ColourSelector.h"
#include "fontmanager.h"

#include "../winfizz/glwindows.h"

// CColourSelector

IMPLEMENT_DYNAMIC(CColourSelector, CWnd)

CColourSelector::CColourSelector()
	: m_width(0)
	, m_height(0)
	, m_gl(NULL)
	, m_r(0.0f)
	, m_g(0.0f)
	, m_b(0.0f)
	, leftButtonDown(false)
	, m_blueClicked(false)
	, m_paletteClicked(false)
{

}

CColourSelector::~CColourSelector()
{
}


BEGIN_MESSAGE_MAP(CColourSelector, CWnd)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_EN_KILLFOCUS(1, OnKillFocusR)
	ON_EN_KILLFOCUS(2, OnKillFocusG)
	ON_EN_KILLFOCUS(3, OnKillFocusB)
END_MESSAGE_MAP()



// CColourSelector message handlers



void CColourSelector::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	if (cx && cy)
	{
		if (m_width && m_height)
		{
			m_gl->resize(cx, cy);
		}
		else
		{
			m_gl = new GLWindows();
			m_gl->create(GetSafeHwnd(), cx, cy, 32, false);

			gluOrtho2D(0.0, cx, 0.0, cy);
		}

		m_width = cx;
		m_height = cy;
	}
}

BOOL CColourSelector::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return CWnd::OnEraseBkgnd(pDC);
}

void CColourSelector::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	if (m_gl == NULL)
	{
		CRect rc;
		GetClientRect(rc);

		m_gl = new GLWindows();
		m_gl->create(GetSafeHwnd(), rc.Width(), rc.Height(), 32, false);

		m_gl->prep();

		gluOrtho2D(0.0, rc.Width(), 0.0, rc.Height());

		m_width = rc.Width();
		m_height = rc.Height();

		paletteRect = CRect(10, 10, 110, 110);
		blueRect = CRect(120, 10, 130, 110);
		swatchRect = CRect(150, 90, 190, 110);

		HFONT f = FontManager::getFont(L"Tahoma", 8.0f);
		r.Create(WS_BORDER | WS_VISIBLE, CRect(150, 10, 190, 27), this, 1);
		r.SendMessage(WM_SETFONT, (WPARAM)f, 1);
		g.Create(WS_BORDER | WS_VISIBLE, CRect(150, 37, 190, 54), this, 2);
		g.SendMessage(WM_SETFONT, (WPARAM)f, 1);
		b.Create(WS_BORDER | WS_VISIBLE, CRect(150, 64, 190, 81), this, 3);
		b.SendMessage(WM_SETFONT, (WPARAM)f, 1);

		wchar_t sz[10];
		swprintf(sz, 10, L"%.0f", m_r * 255.0);
		r.SetWindowTextW(sz);

		swprintf(sz, 10, L"%.0f", m_g * 255.0);
		g.SetWindowTextW(sz);

		swprintf(sz, 10, L"%.0f", m_b * 255.0);
		b.SetWindowTextW(sz);
	}

	m_gl->prep();

	glDisable(GL_LIGHTING);
	glBegin(GL_QUADS);

	// draw the palette
	glColor3f(0.0f, 0.0f, m_b);
	glVertex2i(paletteRect.left, m_height - paletteRect.bottom);
	glColor3f(1.0f, 0.0f, m_b);
	glVertex2i(paletteRect.right, m_height - paletteRect.bottom);
	glColor3f(1.0f, 1.0f, m_b);
	glVertex2i(paletteRect.right, m_height - paletteRect.top);
	glColor3f(0.0f, 1.0f, m_b);
	glVertex2i(paletteRect.left, m_height - paletteRect.top);

	// draw the blue rectangle
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2i(blueRect.left, m_height - blueRect.bottom);
	glVertex2i(blueRect.right, m_height - blueRect.bottom);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2i(blueRect.right, m_height - blueRect.top);
	glVertex2i(blueRect.left, m_height - blueRect.top);

	// draw the swatch
	glColor3f(m_r, m_g, m_b);
	glVertex2i(swatchRect.left, m_height - swatchRect.bottom);
	glVertex2i(swatchRect.right, m_height - swatchRect.bottom);
	glVertex2i(swatchRect.right, m_height - swatchRect.top);
	glVertex2i(swatchRect.left, m_height - swatchRect.top);

	glEnd();

	glDisable(GL_LINE_SMOOTH);
	glDisable(GL_POLYGON_SMOOTH);

	glBegin(GL_LINE_LOOP);
	// draw an indicator over the blue bit
	glColor3ub(192, 192, 192);
	int y = m_height - blueRect.bottom + m_b * blueRect.Height();
	glVertex2i(blueRect.left - 1, y - 1);
	glVertex2i(blueRect.right + 1, y - 1);
	glVertex2i(blueRect.right + 1, y + 1);
	glVertex2i(blueRect.left - 1, y + 1);
	glEnd();

	int x = paletteRect.left + m_r * paletteRect.Width();
	y = m_height - paletteRect.bottom + m_g * paletteRect.Height();
	glBegin(GL_TRIANGLES);
	glVertex2i(x + 1, y + 1);
	glVertex2i(x + 4, y + 1);
	glVertex2i(x + 1, y + 4);

	glVertex2i(x - 1, y + 1);
	glVertex2i(x - 1, y + 4);
	glVertex2i(x - 4, y + 1);

	glVertex2i(x + 1, y - 1);
	glVertex2i(x + 1, y - 4);
	glVertex2i(x + 4, y - 1);

	glVertex2i(x - 1, y - 1);
	glVertex2i(x - 4, y - 1);
	glVertex2i(x - 1, y - 4);

	glEnd();

	m_gl->swap();
}

void CColourSelector::OnDestroy()
{
	CWnd::OnDestroy();

	if (m_gl != NULL) 
	{
		m_gl->destroy();
		delete m_gl;
	}
}

void CColourSelector::PreSubclassWindow()
{
	CRect rc;
	GetClientRect(rc);

	CWnd::PreSubclassWindow();
}

void CColourSelector::OnMouseMove(UINT nFlags, CPoint point)
{
	if (this != GetCapture())
	{
		SetCapture();
	}
	else
	{
		CRect rc;
		GetClientRect(rc);

		if (leftButtonDown)
		{
			if (m_blueClicked)
			{
				int y = max(0, min(point.y - blueRect.top, blueRect.Height()));
				m_b = 1.0f - (float)y / (float)blueRect.Height();
				RedrawWindow();

				wchar_t sz[10];
				swprintf(sz, 10, L"%.0f", m_b * 255.0);
				b.SetWindowTextW(sz);
			}

			if (m_paletteClicked)
			{
				int x = max(0, min(point.x - paletteRect.left, paletteRect.Width()));
				int y = max(0, min(point.y - paletteRect.top, paletteRect.Height()));

				m_r = (float)x / (float)paletteRect.Width();
				m_g = 1.0f - (float)y / (float)paletteRect.Height();
				RedrawWindow();

				wchar_t sz[10];
				swprintf(sz, 10, L"%.0f", m_r * 255.0);
				r.SetWindowTextW(sz);

				swprintf(sz, 10, L"%.0f", m_g * 255.0);
				g.SetWindowTextW(sz);
			}
		}
		else
		{
			if (GetCapture() == this) ReleaseCapture();
		}
	}

	CWnd::OnMouseMove(nFlags, point);
}

void CColourSelector::OnLButtonDown(UINT nFlags, CPoint point)
{
	leftButtonDown = true;
	if (blueRect.PtInRect(point))
	{
		m_b = 1.0f - (float)(point.y - blueRect.top) / (float)blueRect.Height();
		m_blueClicked = true;
		RedrawWindow();
	}
	if (paletteRect.PtInRect(point))
	{
		m_r = (float)(point.x - paletteRect.left) / (float)paletteRect.Width();
		m_g = 1.0f - (float)(point.y - paletteRect.top) / (float)paletteRect.Height();
		m_paletteClicked = true;
		RedrawWindow();
	}

	CWnd::OnLButtonDown(nFlags, point);
}

void CColourSelector::OnLButtonUp(UINT nFlags, CPoint point)
{
	leftButtonDown = false;
	if (GetCapture() == this) ReleaseCapture();

	m_blueClicked = false;
	m_paletteClicked = false;

	CWnd::OnLButtonUp(nFlags, point);
}

void CColourSelector::OnKillFocusR()
{
	wchar_t* cp = 0;
	wchar_t sz[10];
	r.GetWindowTextW(sz, 10);
	m_r = (double)wcstol(sz, &cp, 10) / 255.0;
	RedrawWindow();
}

void CColourSelector::OnKillFocusG()
{
	wchar_t* cp = 0;
	wchar_t sz[10];
	g.GetWindowTextW(sz, 10);
	m_g = (double)wcstol(sz, &cp, 10) / 255.0;
	RedrawWindow();
}

void CColourSelector::OnKillFocusB()
{
	wchar_t* cp = 0;
	wchar_t sz[10];
	b.GetWindowTextW(sz, 10);
	m_b = (double)wcstol(sz, &cp, 10) / 255.0;
	RedrawWindow();
}