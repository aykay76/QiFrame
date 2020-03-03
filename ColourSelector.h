#pragma once


// CColourSelector
class GLWindows;

class CColourSelector : public CWnd
{
	DECLARE_DYNAMIC(CColourSelector)

public:
	CColourSelector();
	virtual ~CColourSelector();

	int m_width;
	int m_height;
	GLWindows* m_gl;

	CRect paletteRect;
	bool m_paletteClicked;
	CRect blueRect;
	bool m_blueClicked;
	CRect swatchRect;

	CEdit r;
	CEdit g;
	CEdit b;

	float m_r;
	float m_g;
	float m_b;

	bool leftButtonDown;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
	afx_msg void OnPaint();
public:
	afx_msg void OnDestroy();
protected:
	virtual void PreSubclassWindow();
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKillFocusR();
	afx_msg void OnKillFocusG();
	afx_msg void OnKillFocusB();
};


