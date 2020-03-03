// EntityPropertiesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "QiFrame.h"
#include "EntityPropertiesDlg.h"

#include "../winfizz/engine/entity.h"
#include "../winfizz/engine/vector.h"

#include "../winfizz/engine/constants.h"

#include <gdiplus.h>

// CEntityPropertiesDlg dialog

IMPLEMENT_DYNAMIC(CEntityPropertiesDlg, CDialog)

CEntityPropertiesDlg::CEntityPropertiesDlg(int x, int y, CWnd* pParent /*=NULL*/)
	: CDialog(CEntityPropertiesDlg::IDD, pParent)
	, m_x(x)
	, m_y(y)
{

}

CEntityPropertiesDlg::~CEntityPropertiesDlg()
{
}

void CEntityPropertiesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEntityPropertiesDlg, CDialog)
	ON_WM_ERASEBKGND()
	ON_COMMAND(IDC_MOVE_X, OnMoveX)
	ON_COMMAND(IDC_MOVE_Y, OnMoveY)
	ON_COMMAND(IDC_MOVE_Z, OnMoveZ)
	ON_COMMAND(IDC_ROTATE_X, OnRotateX)
	ON_COMMAND(IDC_ROTATE_Y, OnRotateY)
	ON_COMMAND(IDC_ROTATE_Z, OnRotateZ)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CEntityPropertiesDlg message handlers

BOOL CEntityPropertiesDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_moveX.SubclassDlgItem(IDC_MOVE_X, this);
	m_moveY.SubclassDlgItem(IDC_MOVE_Y, this);
	m_moveZ.SubclassDlgItem(IDC_MOVE_Z, this);
	m_moveX.imagePrefix(L"x-");
	m_moveY.imagePrefix(L"y-");
	m_moveZ.imagePrefix(L"z-");

	m_rotateX.SubclassDlgItem(IDC_ROTATE_X, this);
	m_rotateY.SubclassDlgItem(IDC_ROTATE_Y, this);
	m_rotateZ.SubclassDlgItem(IDC_ROTATE_Z, this);
	m_rotateX.imagePrefix(L"x-");
	m_rotateY.imagePrefix(L"y-");
	m_rotateZ.imagePrefix(L"z-");

	m_scaleX.SubclassDlgItem(IDC_SCALE_X, this);
	m_scaleY.SubclassDlgItem(IDC_SCALE_Y, this);
	m_scaleZ.SubclassDlgItem(IDC_SCALE_Z, this);
	m_scaleX.imagePrefix(L"x-");
	m_scaleY.imagePrefix(L"y-");
	m_scaleZ.imagePrefix(L"z-");

	CRect rc;
	GetWindowRect(rc);
	int w = rc.Width();
	int h = rc.Height();
	MoveWindow(m_x, m_y, w, h);

	return TRUE;
}

void CEntityPropertiesDlg::moveTo(int x, int y)
{
	m_x = x; m_y = y;

	CRect rc;
	GetWindowRect(rc);
	int w = rc.Width();
	int h = rc.Height();
	MoveWindow(m_x, m_y, w, h);
}

BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam)
{
	HRGN rgn = (HRGN)lParam;

	RECT rc;
	GetWindowRect(hwnd, &rc);
	POINT ptTopLeft; ptTopLeft.x = rc.left; ptTopLeft.y = rc.top;
	POINT ptBottomRight; ptBottomRight.x = rc.right; ptBottomRight.y = rc.bottom;
	ScreenToClient(GetParent(hwnd), &ptTopLeft);
	ScreenToClient(GetParent(hwnd), &ptBottomRight);

	HRGN ex = CreateRectRgn(ptTopLeft.x, ptTopLeft.y, ptBottomRight.x, ptBottomRight.y);
	CombineRgn(rgn, rgn, ex, RGN_XOR);
	DeleteObject(ex);

	return TRUE;
}

BOOL CEntityPropertiesDlg::OnEraseBkgnd(CDC* pDC)
{
	CRect rc;
	GetClientRect(rc);

	HRGN rgn = CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);
	EnumChildWindows(GetSafeHwnd(), EnumChildProc, (LPARAM)rgn);
	FillRgn(pDC->GetSafeHdc(), rgn, (HBRUSH)GetStockObject(WHITE_BRUSH));
	DeleteObject(rgn);

	return TRUE;
}

void CEntityPropertiesDlg::OnCancel()
{
	ShowWindow(SW_HIDE);
}

void CEntityPropertiesDlg::OnOK()
{
}

void CEntityPropertiesDlg::setEntity(Entity *entity)
{
	m_entity = entity;
	if (m_entity)
	{
		wchar_t sz[20];
		Vector v = m_entity->position();
		swprintf(sz, 20, L"%.02f", v.m_values[0]);
		GetDlgItem(IDC_X_POS)->SetWindowTextW(sz);

		swprintf(sz, 20, L"%.02f", v.m_values[1]);
		GetDlgItem(IDC_Y_POS)->SetWindowTextW(sz);

		swprintf(sz, 20, L"%.02f", v.m_values[2]);
		GetDlgItem(IDC_Z_POS)->SetWindowTextW(sz);

		float x, y, z;
		m_entity->matrix().getAngles(&x, &y, &z);

		swprintf(sz, 20, L"%.02f", x);
		GetDlgItem(IDC_X_ANGLE)->SetWindowTextW(sz);

		swprintf(sz, 20, L"%.02f", y);
		GetDlgItem(IDC_Y_ANGLE)->SetWindowTextW(sz);

		swprintf(sz, 20, L"%.02f", z);
		GetDlgItem(IDC_Z_ANGLE)->SetWindowTextW(sz);
	}

	RedrawWindow();
}

void CEntityPropertiesDlg::OnMoveX()
{
	int dx = m_moveX.m_dx;
	if (m_entity)
	{
		m_entity->translate(0.5f * (float)dx, 0.0f, 0.0f, 2);
	}
}

void CEntityPropertiesDlg::OnMoveY()
{
	int dx = m_moveY.m_dx;
	if (m_entity)
	{
		m_entity->translate(0.0f, 0.5f * (float)dx, 0.0f, 2);
	}
}

void CEntityPropertiesDlg::OnMoveZ()
{
	int dx = m_moveZ.m_dx;
	if (m_entity)
	{
		m_entity->translate(0.0f, 0.0f, 0.5f * (float)dx, 2);
	}
}

void CEntityPropertiesDlg::OnRotateX()
{
	int dx = m_rotateX.m_dx;
	if (m_entity)
	{
		m_entity->rotate(0.5f * (float)dx * constants::pi / 180.0, 1.0, 0.0, 0.0, 2);
	}
}

void CEntityPropertiesDlg::OnRotateY()
{
	int dx = m_rotateY.m_dx;
	if (m_entity)
	{
		m_entity->rotate(0.5f * (float)dx * constants::pi / 180.0, 0.0, 1.0, 0.0, 2);
	}
}

void CEntityPropertiesDlg::OnRotateZ()
{
	int dx = m_rotateZ.m_dx;
	if (m_entity)
	{
		m_entity->rotate(0.5f * (float)dx * constants::pi / 180.0, 0.0, 0.0, 1.0, 2);
	}
}

void CEntityPropertiesDlg::OnEnMaxtextXPos()
{
	wchar_t c[1];
	wchar_t sz[10];

	GetDlgItem(IDC_X_POS)->GetWindowTextW(sz, 10);
	float x = (float)wcstod(sz, (wchar_t **)&c);

	GetDlgItem(IDC_Y_POS)->GetWindowTextW(sz, 10);
	float y = (float)wcstod(sz, (wchar_t **)&c);

	GetDlgItem(IDC_Z_POS)->GetWindowTextW(sz, 10);
	float z = (float)wcstod(sz, (wchar_t **)&c);

	m_entity->matrix().m_values[12] = x;
	m_entity->matrix().m_values[13] = y;
	m_entity->matrix().m_values[14] = z;

	m_entity->notify();
}

void CEntityPropertiesDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	SendMessage(WM_SYSCOMMAND, 0xf012, 0);

	CDialog::OnLButtonDown(nFlags, point);
}
