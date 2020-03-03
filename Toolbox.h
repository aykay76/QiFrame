#pragma once

#include "colourselector.h"

// CToolbox

class CToolbox : public CDialogBar
{
	DECLARE_DYNAMIC(CToolbox)

public:
	CToolbox();
	virtual ~CToolbox();

	CComboBox m_relativeTo;
	CColourSelector m_colour;

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


