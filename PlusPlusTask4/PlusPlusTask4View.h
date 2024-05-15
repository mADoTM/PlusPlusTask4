// PlusPlusTask4View.h: интерфейс класса CPlusPlusTask4View
//

#pragma once


class CPlusPlusTask4View : public CView
{
protected: // создать только из сериализации
	CPlusPlusTask4View() noexcept;
	DECLARE_DYNCREATE(CPlusPlusTask4View)


// Атрибуты
public:
	CPlusPlusTask4Doc* GetDocument() const;

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Реализация
public:
	virtual ~CPlusPlusTask4View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Созданные функции схемы сообщений
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // версия отладки в PlusPlusTask4View.cpp
inline CPlusPlusTask4Doc* CPlusPlusTask4View::GetDocument() const
   { return reinterpret_cast<CPlusPlusTask4Doc*>(m_pDocument); }
#endif

