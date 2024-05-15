
// PlusPlusTask4.h: основной файл заголовка для приложения PlusPlusTask4
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CPlusPlusTask4App:
// Сведения о реализации этого класса: PlusPlusTask4.cpp
//

class CPlusPlusTask4App : public CWinAppEx
{
public:
	CPlusPlusTask4App() noexcept;


// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnAssignLayersOfVertexClicked();
};

extern CPlusPlusTask4App theApp;
