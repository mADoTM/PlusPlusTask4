
// PlusPlusTask4View.cpp: реализация класса CPlusPlusTask4View
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "PlusPlusTask4.h"
#endif

#include "PlusPlusTask4Doc.h"
#include "PlusPlusTask4View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlusPlusTask4View

IMPLEMENT_DYNCREATE(CPlusPlusTask4View, CView)

BEGIN_MESSAGE_MAP(CPlusPlusTask4View, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// Создание или уничтожение CPlusPlusTask4View

CPlusPlusTask4View::CPlusPlusTask4View() noexcept
{
	// TODO: добавьте код создания

}

CPlusPlusTask4View::~CPlusPlusTask4View()
{
}

BOOL CPlusPlusTask4View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование CPlusPlusTask4View

void CPlusPlusTask4View::OnDraw(CDC* pDC)
{
	CPlusPlusTask4Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	RECT r;
	this->GetClientRect(&r);

	pDC->DrawText(pDoc->GetText(), &r, 0);
	
}

void CPlusPlusTask4View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPlusPlusTask4View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Диагностика CPlusPlusTask4View

#ifdef _DEBUG
void CPlusPlusTask4View::AssertValid() const
{
	CView::AssertValid();
}

void CPlusPlusTask4View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlusPlusTask4Doc* CPlusPlusTask4View::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlusPlusTask4Doc)));
	return (CPlusPlusTask4Doc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CPlusPlusTask4View
