
// PlusPlusTask4Doc.cpp: реализация класса CPlusPlusTask4Doc 
//

#include "pch.h"
#include "framework.h"
#include <vector>
#include <afxwin.h>
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "PlusPlusTask4.h"
#include "AssignLayersService.h"
#include <string>
#include <chrono>
#include <ctime>
#endif

#include "PlusPlusTask4Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPlusPlusTask4Doc

IMPLEMENT_DYNCREATE(CPlusPlusTask4Doc, CDocument)

BEGIN_MESSAGE_MAP(CPlusPlusTask4Doc, CDocument)
	ON_COMMAND(ID_32773, &CPlusPlusTask4Doc::OnAssignLayersClick)
END_MESSAGE_MAP()


// Создание или уничтожение CPlusPlusTask4Doc

CPlusPlusTask4Doc::CPlusPlusTask4Doc() noexcept
{
	// TODO: добавьте код для одноразового вызова конструктора

}

CPlusPlusTask4Doc::~CPlusPlusTask4Doc()
{
}

BOOL CPlusPlusTask4Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: добавьте код повторной инициализации
	// (Документы SDI будут повторно использовать этот документ)
	return TRUE;
}




// Сериализация CPlusPlusTask4Doc

void CPlusPlusTask4Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar.WriteString(_fileText);
	}
	else
	{
		CString buf;
		while (ar.ReadString(buf))
		{
			_fileText.Append(buf);
			_fileText.Append("\n");
		}
		
		_logText.Format("Received file with size %d", _fileText.GetLength());
		logInfo(_logText, "INFO");
	}
}

#ifdef SHARED_HANDLERS

// Поддержка для эскизов
void CPlusPlusTask4Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Измените этот код для отображения данных документа
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Поддержка обработчиков поиска
void CPlusPlusTask4Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// Задание содержимого поиска из данных документа.
	// Части содержимого должны разделяться точкой с запятой ";"

	// Например:  strSearchContent = _T("точка;прямоугольник;круг;объект ole;");
	SetSearchContent(strSearchContent);
}

void CPlusPlusTask4Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Диагностика CPlusPlusTask4Doc

#ifdef _DEBUG
void CPlusPlusTask4Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPlusPlusTask4Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Команды CPlusPlusTask4Doc


void CPlusPlusTask4Doc::OnAssignLayersClick()
{
	if (_fileText.GetLength() > 0)
	{
		try 
		{
			assignLayers();
			_logText.Format("Succsefuly assign layers");
			logInfo(_logText, "INFO");
			auto pos = theApp.GetFirstDocTemplatePosition();
			auto pDocTemplate = theApp.GetNextDocTemplate(pos);
			if (pDocTemplate)
			{
				auto doc = dynamic_cast<CPlusPlusTask4Doc*>(pDocTemplate->CreateNewDocument());
				doc->SetText(_layersText);
				auto chld = pDocTemplate->CreateNewFrame(
					doc,
					dynamic_cast<CFrameWnd*>(theApp.GetMainWnd())
				);
				chld->ShowWindow(true);
			}
		}
		catch (const std::exception& e) 
		{
			_logText.Format("%s. See log file", e.what());
			MessageBox(NULL, _logText, _T("Warning"), MB_ICONWARNING);
		}
		
	}
	else 
	{
		MessageBox(NULL, _T("No text in doc. Open file with text and retry..."), _T("Message"), MB_OK);
	}
}

CString CPlusPlusTask4Doc::GetText()
{
	return _fileText;
}

void CPlusPlusTask4Doc::SetText(CString text)
{
	_fileText = text;
}

void CPlusPlusTask4Doc::assignLayers() 
{
	CString delimiter = _T("\n");
	int position = 0;

	CString token = _fileText.Tokenize(delimiter, position);
	_logText.Format("Read config line from file: \"%s\"", token);
	logInfo(_logText, "INFO");

	auto config = splitString((LPCTSTR)token);
	if (config.size() != 3)
	{
		_logText.Format("Entered wrong value in Config line. Stop Process. Line: \"%s\"", token);
		logInfo(_logText, "WARN");
		throw std::invalid_argument("Entered wrong value in Config line. Stop Process");
	}
		

	const int count_connections = config[0];
	const int start_vertex = config[1];
	const int count_vertices = config[2];
	
	if (count_connections < 0 || start_vertex < 0 || count_vertices < 0)
	{
		_logText.Format("Found negative number in Config line. Stop Process");
		logInfo(_logText, "WARN");
		throw std::invalid_argument("Found negative number in Config line. Stop Process");
	}
		

	if (count_vertices < 1 || count_connections < count_vertices)
	{
		_logText.Format("Entered wrong relation between Vertices and Connection. Stop Process");
		logInfo(_logText, "WARN");
		throw std::invalid_argument("Entered wrong relation between Vertices and Connection. Stop Process");
	}
		

	Vertex* graph = new Vertex[count_vertices];

	for (int i = 0; i < count_connections; i++)
	{
		token = _fileText.Tokenize(delimiter, position);
		auto vertices = splitString((LPCTSTR)token);

		if (vertices.size() != 2)
		{
			_logText.Format("Found no correct relation in line: %d line: \"%s\"", (i+1), token);
			logInfo(_logText, "WARN");
			throw std::invalid_argument("Found no correct relation in line " + (i + 1));
		}


		if (vertices[0] < 0 || vertices[1] < 0)
		{
			_logText.Format("Found negative vertices in line: %d line \"%s\"", (i + 1), token);
			logInfo(_logText, "WARN");
			throw std::invalid_argument("Found negative vertices in line " + (i + 1));
		}


		if (vertices[0] == vertices[1])
		{
			_logText.Format("Can not assign relation between same vertices in line: \"%s\" ", token);
			logInfo(_logText, "WARN");
			throw std::invalid_argument("Can not assign relation between same vertices in line " + (i + 1));
		}
			

		graph[vertices[0]].number = vertices[0];
		graph[vertices[1]].number = vertices[1];

		graph[vertices[0]].adjacentVertices.push_back(vertices[1]);
		graph[vertices[1]].adjacentVertices.push_back(vertices[0]);

		_logText.Format("Received relation betwen vertices %d-%d", vertices[1], vertices[0]);
		logInfo(_logText, "INFO");
	}

	std::queue<Vertex> currentLayerQueue;
	std::queue<Vertex> nextLayerQueue;
	currentLayerQueue.push(graph[start_vertex]);
	int layer = 0;

	std::vector<std::vector<Vertex>> assignmentLayersVerteces;

	while (!currentLayerQueue.empty())
	{
		auto vertex = currentLayerQueue.front();

		if (graph[vertex.number].layer == -1)
		{
			graph[vertex.number].layer = layer;

			if (assignmentLayersVerteces.size() == layer)
			{
				std::vector<Vertex> tmp;
				assignmentLayersVerteces.push_back(tmp);
			}
			assignmentLayersVerteces[layer].push_back(graph[vertex.number]);

			for (auto connected_vertex : vertex.adjacentVertices)
			{
				auto tmp = graph[connected_vertex];
				if (tmp.layer == -1)
				{
					nextLayerQueue.push(tmp);
				}
			}
		}

		currentLayerQueue.pop();
		if (currentLayerQueue.empty())
		{
			layer++;
			currentLayerQueue = nextLayerQueue;
			while (!nextLayerQueue.empty())
			{
				nextLayerQueue.pop();
			}
		}
	}

	for (int i = 0; i < layer; i++)
	{
		if (assignmentLayersVerteces[i].size() > 0)
		{
			CString tmp;
			tmp.Format(_T("Layer#%d"), i);
			_layersText.Append(tmp);
			_layersText.Append(": ");

			for (int j = 0; j < assignmentLayersVerteces[i].size(); j++)
			{
				CString tmpInner;
				tmpInner.Format(_T("Vertex №%d"), assignmentLayersVerteces[i][j].number);
				_layersText.Append(tmpInner);
				if (j < assignmentLayersVerteces[i].size() - 1)
					_layersText.Append(", ");
			}
			_layersText.Append("\n");
		}
	}

}

std::vector<int> CPlusPlusTask4Doc::splitString(const std::string& str) {
	try
	{
		std::stringstream iss(str);

		int number;
		std::vector<int> myNumbers;
		while (iss >> number)
			myNumbers.push_back(number);

		return myNumbers;
	}
	catch (const std::exception& e) {
		throw std::invalid_argument("Entered a non integer value in string");
	}
	
}

void CPlusPlusTask4Doc::logInfo(CString message, CString type)
{
	CString logFilePath = _T("log.txt");
	CString fullMessageWithTypeAndTime;

	CStdioFile logFile;

	CTime currentTime = CTime::GetCurrentTime();

	int year = currentTime.GetYear();
	int month = currentTime.GetMonth();
	int day = currentTime.GetDay();
	int hour = currentTime.GetHour();
	int minute = currentTime.GetMinute();
	int second = currentTime.GetSecond();

	CString timeString;
	timeString.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"), year, month, day, hour, minute, second);

	fullMessageWithTypeAndTime.Append(timeString);
	fullMessageWithTypeAndTime.Append("\t");
	fullMessageWithTypeAndTime.Append(type);
	fullMessageWithTypeAndTime.Append("\t");
	fullMessageWithTypeAndTime.Append(message);
	fullMessageWithTypeAndTime.Append("\n");

	if (logFile.Open(logFilePath, CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate)) {
		logFile.SeekToEnd();

		logFile.WriteString(fullMessageWithTypeAndTime);

		logFile.Close();
	}
}
