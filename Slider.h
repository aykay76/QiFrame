#pragma once

#include <gdiplus.h>
#include <string>

// CSlider

class CSlider : public CWnd
{
	DECLARE_DYNAMIC(CSlider)

public:
	CSlider();
	virtual ~CSlider();

protected:
	DECLARE_MESSAGE_MAP()

	Gdiplus::Bitmap* m_inactive;
	Gdiplus::Bitmap* m_hover;
	Gdiplus::Bitmap* m_left;
	Gdiplus::Bitmap* m_right;
	virtual void PreSubclassWindow();

	CPoint m_ptLast;
	CPoint m_ptDown;
	bool m_mouseOver;
	bool m_mouseDown;
	bool m_mouseLeft;
	bool m_mouseRight;
	std::wstring m_imagePrefix;

public:
	void imagePrefix(wchar_t* prefix);

	int m_dx;
	int m_dy;

public:
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};


