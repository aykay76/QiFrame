#pragma once

#include "slider.h"

class Entity;

// CEntityPropertiesDlg dialog
class CEntityPropertiesDlg : public CDialog
{
	DECLARE_DYNAMIC(CEntityPropertiesDlg)

public:
	CEntityPropertiesDlg(int x, int y, CWnd* pParent = NULL);   // standard constructor
	virtual ~CEntityPropertiesDlg();

// Dialog Data
	enum { IDD = IDD_ENTITY_PROPERTIES };

	void moveTo(int x, int y);
	void setEntity(Entity* entity);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	CSlider m_moveX;
	CSlider m_moveY;
	CSlider m_moveZ;

	CSlider m_rotateX;
	CSlider m_rotateY;
	CSlider m_rotateZ;

	CSlider m_scaleX;
	CSlider m_scaleY;
	CSlider m_scaleZ;

	Entity* m_entity;

protected:
	void OnMoveX();
	void OnMoveY();
	void OnMoveZ();
	void OnRotateX();
	void OnRotateY();
	void OnRotateZ();

public:
	int m_x;
	int m_y;

public:
	virtual BOOL OnInitDialog();
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
protected:
	virtual void OnCancel();
	virtual void OnOK();
public:
	afx_msg void OnEnMaxtextXPos();
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
