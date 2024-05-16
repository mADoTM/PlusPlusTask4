#pragma once
#include "afxdialogex.h"


// Диалоговое окно InputStartVertexDialog

class InputStartVertexDialog : public CDialogEx
{
	DECLARE_DYNAMIC(InputStartVertexDialog)

public:
	CString input;
	InputStartVertexDialog(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~InputStartVertexDialog();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:

	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
};
