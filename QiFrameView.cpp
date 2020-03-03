// QiFrameView.cpp : implementation of the CQiFrameView class
//

#include "stdafx.h"
#include "QiFrame.h"
#include "mainfrm.h"
#include "QiFrameDoc.h"
#include "QiFrameView.h"
#include ".\QiFrameview.h"

#include "entitypropertiesdlg.h"

#include <gl/gl.h>
#include "../winfizz/3ds/3ds.h"
#include "../winfizz/engine/constants.h"
#include "../winfizz/glwindows.h"
#include "../winfizz/engine/engine.h"
#include "../winfizz/engine/actionentity.h"
#pragma comment(lib, "glaux.lib")

#include <gdiplus.h>
#include <float.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CQiFrameView

IMPLEMENT_DYNCREATE(CQiFrameView, CView)

BEGIN_MESSAGE_MAP(CQiFrameView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_KEYDOWN()
	ON_COMMAND(IDC_X_LEFT, OnXLeft)
	ON_COMMAND(IDC_X_RIGHT, OnXRight)
	ON_COMMAND(IDC_Y_LEFT, OnYLeft)
	ON_COMMAND(IDC_Y_RIGHT, OnYRight)
	ON_COMMAND(IDC_Z_LEFT, OnZLeft)
	ON_COMMAND(IDC_Z_RIGHT, OnZRight)
	ON_COMMAND(IDC_MOVE_X_LEFT, OnMoveXLeft)
	ON_COMMAND(IDC_MOVE_X_RIGHT, OnMoveXRight)
	ON_COMMAND(IDC_MOVE_Y_LEFT, OnMoveYLeft)
	ON_COMMAND(IDC_MOVE_Y_RIGHT, OnMoveYRight)
	ON_COMMAND(IDC_MOVE_Z_LEFT, OnMoveZLeft)
	ON_COMMAND(IDC_MOVE_Z_RIGHT, OnMoveZRight)
	ON_COMMAND(IDC_SPHERE, OnSphere)
	ON_COMMAND(IDC_TORUS, OnTorus)
	ON_COMMAND(IDC_LIGHT, OnLight)
	ON_CBN_SELCHANGE(IDC_RELATIVE_TO, OnSelchangeRelativeTo)
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CQiFrameView construction/destruction

CQiFrameView::CQiFrameView()
	: m_width(0)
	, m_height(0)
	, m_relativeTo(0)
	, m_entityProperties(NULL)
	, m_gl(NULL)
{
	// TODO: add construction code here
	
}

CQiFrameView::~CQiFrameView()
{
}

BOOL CQiFrameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CQiFrameView drawing

void CQiFrameView::OnDraw(CDC* pDC)
{
	CQiFrameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	Engine::instance()->step();
//	CRect rc;
//	GetClientRect(rc);

//	Engine::instance()->step(0.1);

//	m_gl->prep();
//	Engine::instance()->drawSetup(GL_RENDER);
//	Engine::instance()->draw(GL_RENDER);
//	m_gl->swap();


/*
	// we need a way of displaying decorations for the selected object(s)
	float* buf = NULL;
	int i = 0;
	Entity* se = Engine::instance()->selectedEntity();
	if (se)
	{
		// TODO: what we draw depends on what mode the object is in. if it's selected
		// in a normal kind of mode we want the usual handles for changing the parameters
		// of the object
#ifdef WIN32
		se->drawOverlays(graphics);
#endif

		if (Engine::instance()->feedbackSelectedMesh(buf, i))
		{
			float x, y;
			float count;
			int j = 0;
			while (j < i)
			{
				int token = (int)buf[j++];
				switch (token)
				{
				case GL_POINT_TOKEN:
					x = buf[j++];
					y = buf[j++];
					pDC->FillSolidRect((int)(x - 1), (int)(m_gl->viewport()[3] - y - 1), 3, 3, RGB(255, 0, 0));
					break;
				case GL_LINE_TOKEN:
				case GL_LINE_RESET_TOKEN:
					x = buf[j++];
					y = buf[j++];
					pDC->FillSolidRect((int)(x - 1), (int)(m_gl->viewport()[3] - y - 1), 3, 3, RGB(255, 0, 0));
					x = buf[j++];
					y = buf[j++];
					pDC->FillSolidRect((int)(x - 1), (int)(m_gl->viewport()[3] - y - 1), 3, 3, RGB(255, 0, 0));
					break;
				case GL_POLYGON_TOKEN:
					count = buf[j++];
					for (int k = 0; k < count; k++)
					{
						x = buf[j++];
						y = buf[j++];

						pDC->FillSolidRect((int)(x - 1), (int)(m_gl->viewport()[3] - y - 1), 3, 3, RGB(255, 0, 0));
					}
					break;
				case GL_BITMAP_TOKEN:
				case GL_DRAW_PIXEL_TOKEN:
				case GL_COPY_PIXEL_TOKEN:
					x = buf[j++];
					y = buf[j++];
					break;
				case GL_PASS_THROUGH_TOKEN:
					x = buf[j++]; // unused, but this is the passthrough value
					break;
				}
			}
		}
	}
*/
}


// CQiFrameView printing

BOOL CQiFrameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CQiFrameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CQiFrameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CQiFrameView diagnostics

#ifdef _DEBUG
void CQiFrameView::AssertValid() const
{
	CView::AssertValid();
}

void CQiFrameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CQiFrameDoc* CQiFrameView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CQiFrameDoc)));
	return (CQiFrameDoc*)m_pDocument;
}
#endif //_DEBUG


// CQiFrameView message handlers

int CQiFrameView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	ModifyStyle(WS_BORDER, 0, 0);
	ModifyStyleEx(WS_EX_CLIENTEDGE, 0, 0);

	return 0;
}

void CQiFrameView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
}

void CQiFrameView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	if (cx && cy)
	{
		if (m_width && m_height)
		{
			// we are using a fixed size so we don't need to resize right now
			if (m_gl) m_gl->resize(cx, cy);

			m_width = cx;
			m_height = cy;
		}
		else
		{
			m_width = cx;
			m_height = cy;

			if (m_gl == NULL)
			{
				m_gl = new GLWindows();
				m_gl->create(GetSafeHwnd(), m_width, m_height, 32, false);
				Engine::instance()->setGL(m_gl);

				// initialise the engine with a default camera and lights etc.
				Camera* c = new Camera;
				c->x(-200.0);
				c->y(125.0);
				c->z(200.0);
				c->rotate(-20 * constants::pi / 180.0, c->position(), Vector(1.0, 0.0, 0.0));
				c->rotate(-45.0 * constants::pi / 180.0, c->position(), Vector(0.0, 1.0, 0.0));

				Engine::instance()->entities().members()[framework::string(std::wstring(L"c1"))] = c;
				Engine::instance()->cameras().members()[framework::string(std::wstring(L"cam1"))] = c;
				Engine::instance()->setActiveCamera(c);

				Engine::instance()->attach(this);
				m_subjects.push_back(Engine::instance());

				Engine::instance()->init();
				Engine::instance()->start(false);
			}

			SetTimer(1, 1, NULL);
		}
	}
}

void CQiFrameView::OnLButtonDown(UINT nFlags, CPoint point)
{
	Engine::instance()->leftButtonDown(point.x, point.y);
	CView::OnLButtonDown(nFlags, point);
}

void CQiFrameView::OnMouseMove(UINT nFlags, CPoint point)
{
	Engine::instance()->mouseMove(point.x, point.y);

	// TODO: we need a mechanism of determining whether the screen needs to be redrawn or not

	CView::OnMouseMove(nFlags, point);
}

void CQiFrameView::OnLButtonUp(UINT nFlags, CPoint point)
{
	Engine::instance()->leftButtonUp(point.x, point.y);

	CView::OnLButtonUp(nFlags, point);
}

BOOL CQiFrameView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void CQiFrameView::OnRButtonDown(UINT nFlags, CPoint point)
{
	Engine::instance()->rightButtonDown(point.x, point.y);
	CView::OnRButtonDown(nFlags, point);
}

void CQiFrameView::OnRButtonUp(UINT nFlags, CPoint point)
{
	Engine::instance()->rightButtonUp(point.x, point.y);
	CView::OnRButtonUp(nFlags, point);
}

void CQiFrameView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
	case VK_LEFT:
		Engine::instance()->camera()->rotate(2.0 * constants::pi / 180.0, 0.0, 1.0, 0.0, 0);
		RedrawWindow();
		break;
	case VK_RIGHT:
		Engine::instance()->camera()->rotate(-2.0 * constants::pi / 180.0, 0.0, 1.0, 0.0, 0);
		RedrawWindow();
		break;
	case VK_UP:
		Engine::instance()->camera()->translate(0.0, 0.0, -1.0, 0);
		RedrawWindow();
		break;
	case VK_DOWN:
		Engine::instance()->camera()->translate(0.0, 0.0, 1.0, 0);
		RedrawWindow();
		break;
	case VK_ESCAPE:
		if (Engine::instance()->selectedEntity() != NULL)
		{
			if (m_entityProperties != NULL) m_entityProperties->ShowWindow(SW_HIDE);
			Engine::instance()->setSelectedEntity(NULL);
			RedrawWindow();
		}
		break;
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CQiFrameView::OnXLeft()
{
	Entity* se = Engine::instance()->selectedEntity();
	if (se)
	{
		se->rotate(10.0f * constants::pi / 180.0f, 1.0, 0.0, 0.0, m_relativeTo);
		RedrawWindow();
	}
}

void CQiFrameView::OnXRight()
{
	Entity* se = Engine::instance()->selectedEntity();
	if (se)
	{
		se->rotate(-10.0f * constants::pi / 180.0f, 1.0, 0.0, 0.0, m_relativeTo);
		RedrawWindow();
	}
}

void CQiFrameView::OnYLeft()
{
	Entity* se = Engine::instance()->selectedEntity();
	if (se)
	{
		se->rotate(-10.0f * constants::pi / 180.0f, 0.0, 1.0, 0.0, m_relativeTo);
		RedrawWindow();
	}
}

void CQiFrameView::OnYRight()
{
	Entity* se = Engine::instance()->selectedEntity();
	if (se)
	{
		se->rotate(10.0f * constants::pi / 180.0f, 0.0f, 1.0f, 0.0f, m_relativeTo);
		RedrawWindow();
	}
}

void CQiFrameView::OnZLeft()
{
	Entity* se = Engine::instance()->selectedEntity();
	if (se)
	{
		se->rotate(10.0f * constants::pi / 180.0f, 0.0f, 0.0f, -1.0f, m_relativeTo);
		RedrawWindow();
	}
}

void CQiFrameView::OnZRight()
{
	Entity* se = Engine::instance()->selectedEntity();
	if (se)
	{
		se->rotate(-10.0f * constants::pi / 180.0f, 0.0f, 0.0f, -1.0f, m_relativeTo);
		RedrawWindow();
	}
}

void CQiFrameView::OnMoveXLeft()
{
	Entity* se = Engine::instance()->selectedEntity();
	if (se)
	{
		se->translate(-1.0f, 0.0f, 0.0f, m_relativeTo);
		RedrawWindow();
	}
}

void CQiFrameView::OnMoveXRight()
{
	Entity* se = Engine::instance()->selectedEntity();
	if (se)
	{
		se->translate(1.0f, 0.0f, 0.0f, m_relativeTo);
		RedrawWindow();
	}
}

void CQiFrameView::OnMoveYLeft()
{
	Entity* se = Engine::instance()->selectedEntity();
	if (se)
	{
		se->translate(0.0f, 1.0f, 0.0f, m_relativeTo);
		RedrawWindow();
	}
}

void CQiFrameView::OnMoveYRight()
{
	Entity* se = Engine::instance()->selectedEntity();
	if (se)
	{
		se->translate(0.0f, -1.0f, 0.0f, m_relativeTo);
		RedrawWindow();
	}
}

void CQiFrameView::OnMoveZLeft()
{
	Entity* se = Engine::instance()->selectedEntity();
	if (se)
	{
		se->translate(0.0f, 0.0f, 1.0f, m_relativeTo);
		RedrawWindow();
	}
}

void CQiFrameView::OnMoveZRight()
{
	Entity* se = Engine::instance()->selectedEntity();
	if (se)
	{
		se->translate(0.0f, 0.0f, -1.0f, m_relativeTo);
		RedrawWindow();
	}
}

void CQiFrameView::OnSelchangeRelativeTo()
{
	m_relativeTo = ((CMainFrame *)AfxGetMainWnd())->m_toolbox.m_relativeTo.GetCurSel();
}

void CQiFrameView::update()
{
	float* buf;
	int i;

	CRect rc;
	GetClientRect(rc);

	float maxy = -FLT_MAX;
	float maxx = -FLT_MAX;
	Entity* se = Engine::instance()->selectedEntity();
	if (se)
	{
		if (Engine::instance()->feedbackBoundingBox(buf, i))
		{
			float x, y;
			float count;
			int j = 0;
			while (j < i)
			{
				int token = (int)buf[j++];
				switch (token)
				{
				case GL_POINT_TOKEN:
					x = buf[j++];
					y = buf[j++];
					if (x > maxx) maxx = x;
					if (y > maxy) maxy = y;
					break;
				case GL_LINE_TOKEN:
				case GL_LINE_RESET_TOKEN:
					x = buf[j++];
					y = buf[j++];
					if (x > maxx) maxx = x;
					if (y > maxy) maxy = y;
					x = buf[j++];
					y = buf[j++];
					if (x > maxx) maxx = x;
					if (y > maxy) maxy = y;
					break;
				case GL_POLYGON_TOKEN:
					count = buf[j++];
					for (int k = 0; k < count; k++)
					{
						x = buf[j++];
						y = buf[j++];

						if (x > maxx) maxx = x;
						if (y > maxy) maxy = y;
					}
					break;
				case GL_BITMAP_TOKEN:
				case GL_DRAW_PIXEL_TOKEN:
				case GL_COPY_PIXEL_TOKEN:
					x = buf[j++];
					y = buf[j++];
					if (x > maxx) maxx = x;
					if (y > maxy) maxy = y;
					break;
				case GL_PASS_THROUGH_TOKEN:
					x = buf[j++]; // unused, but this is the passthrough value
					break;
				}
			}
		}

		maxy = rc.Height() - maxy;

		POINT pt;
		pt.x = (int)(maxx + 2); pt.y = (int)maxy;
		ClientToScreen(&pt);
		if (m_entityProperties == NULL)
		{
			m_entityProperties = new CEntityPropertiesDlg(pt.x, pt.y, this);
			m_entityProperties->Create(IDD_ENTITY_PROPERTIES, this);
			m_entityProperties->ShowWindow(SW_SHOW);
		}
		else
		{
			m_entityProperties->ShowWindow(SW_SHOW);
//			m_entityProperties->moveTo(pt.x, pt.y);
		}

		m_entityProperties->setEntity(se);
	}
	else
	{
		if (m_entityProperties != NULL)
		{
			m_entityProperties->ShowWindow(SW_HIDE);
		}
	}

	RedrawWindow();
}

void CQiFrameView::OnDestroy()
{
	KillTimer(1);

	std::vector<Event *>::iterator it = m_subjects.begin();
	while (it != m_subjects.end())
	{
		(*it)->detach(this);

		++it;
	}

	Engine::destroy();

	m_gl->destroy();
	delete m_gl;

	if (m_entityProperties) 
	{
		m_entityProperties->DestroyWindow();
		delete m_entityProperties;
	}

	__super::OnDestroy();
}

void CQiFrameView::OnSphere()
{
	Mesh m;
	m.fromSphere(5.0, 10, 10);

	Template* t = new Template;
	t->addMesh(m);
	Engine::instance()->templates().members()[framework::string(std::wstring(L"template1"))] = t;

	Entity* e = new Entity;
	e->attach(this);
	m_subjects.push_back(e);
	e->z(0.0f);
	e->prototype(t);
	wchar_t sz[10];
	swprintf(sz, 10, L"Sphere %d", e->m_namecount);
	e->name(std::wstring(sz));
	e->calcAABB();
	Engine::instance()->entities().members()[framework::string(std::wstring(sz))] = e;
	e->m_allowCollisions = true;

	RedrawWindow();
}

void CQiFrameView::OnTorus()
{
	Mesh m;
	m.fromTorus(3.0, 5.0, 10, 10);

	Template* t = new Template;
	t->addMesh(m);
	Engine::instance()->templates().members()[framework::string(std::wstring(L"template2"))] = t;

	Entity* e = new Entity;
	e->attach(this);
	m_subjects.push_back(e);
	e->z(0.0f);
	e->prototype(t);
	wchar_t sz[10];
	swprintf(sz, 10, L"Torus %d", e->m_namecount);
	e->name(std::wstring(sz));
	e->calcAABB();
	Engine::instance()->entities().members()[framework::string(std::wstring(sz))] = e;
	e->m_allowCollisions = true;

	RedrawWindow();
}

void CQiFrameView::OnLight()
{
	Colour col(1.0f, 1.0f, 1.0f, 1.0f);
	Light* l = new Light;
	l->setPosition(Vector(0.0f, 0.0f, 0.0f));
	l->m_direction[0] = 0.0f;
	l->m_direction[1] = -1.0f;
	l->m_direction[2] = 0.0f;
	l->m_cutoff = 45;
	l->m_ambient = col;
	l->m_diffuse = col;
	l->m_specular = col;
	l->calcAABB();

	// TODO: need to come up with a better way than this
	l->attach(this);

	wchar_t sz[10];
	swprintf(sz, 10, L"Light %d", l->m_namecount);
	std::wstring str(sz);
	l->name(str);

	// TODO: shouldn't do this - causes light to be deleted twice
	Engine::instance()->lights().members()[framework::string(str)] = l;
	Engine::instance()->entities().members()[framework::string(str)] = l;

	RedrawWindow();
}

void CQiFrameView::OnTimer(UINT_PTR nIDEvent)
{
//	Engine::instance()->step();

	RedrawWindow();

	double fps = Engine::instance()->fps();
	wchar_t sz[10];
	swprintf(sz, 10, L"%.1f", fps);
	AfxGetMainWnd()->SetWindowText(sz);
	__super::OnTimer(nIDEvent);
}
