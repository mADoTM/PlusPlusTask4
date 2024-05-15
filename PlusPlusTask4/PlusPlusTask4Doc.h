#include <vector>
#include <queue>
#include <afx.h>
#include <sstream>
// PlusPlusTask4Doc.h: интерфейс класса CPlusPlusTask4Doc 
//



#pragma once

class CPlusPlusTask4Doc : public CDocument
{
protected: // создать только из сериализации
	CPlusPlusTask4Doc() noexcept;
	DECLARE_DYNCREATE(CPlusPlusTask4Doc)
	CString _text;
	CString _fileText;
	CString _layersText;
	CString _logText;

	struct Vertex {
		int number = -1;
		int layer = -1;
		std::vector<int> adjacentVertices;
	};


// Атрибуты
public:

// Операции
public:

// Переопределение
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Реализация
public:
	virtual ~CPlusPlusTask4Doc();

	virtual CString GetText();
	virtual void SetText(CString text);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
protected:
	virtual void assignLayers();
	virtual std::vector<int> splitString(const std::string & str);
	virtual void logInfo(CString message, CString type);

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP();

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnAssignLayersClick();
};
