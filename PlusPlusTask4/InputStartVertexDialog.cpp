// InputStartVertexDialog.cpp: файл реализации
//

#include "pch.h"
#include "PlusPlusTask4.h"
#include "afxdialogex.h"
#include "InputStartVertexDialog.h"


// Диалоговое окно InputStartVertexDialog

IMPLEMENT_DYNAMIC(InputStartVertexDialog, CDialogEx)

InputStartVertexDialog::InputStartVertexDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

InputStartVertexDialog::~InputStartVertexDialog()
{
}

void InputStartVertexDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, input);
}


BEGIN_MESSAGE_MAP(InputStartVertexDialog, CDialogEx)
END_MESSAGE_MAP()


// Обработчики сообщений InputStartVertexDialog
