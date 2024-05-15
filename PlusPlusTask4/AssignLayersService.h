#ifndef GRAPH_LAYERS_H
#define GRAPH_LAYERS_H

#include <vector>
#include <queue>
#include <afx.h>


struct Vertex {
    int number = 0;
    std::vector<int> adjacentVertices;
};

void readGraph(const CString& graphStr, std::vector<Vertex>& graph) {
    int pos = 0;

    while (pos < graphStr.GetLength()) {
        int vertexNum = _ttoi(graphStr.Mid(pos));
        pos = graphStr.Find(':') + 1;

        Vertex vertex;
        vertex.number = vertexNum;

        while (pos < graphStr.GetLength() && graphStr[pos] != ';') {
            int adjVertex = _ttoi(graphStr.Mid(pos));
            vertex.adjacentVertices.push_back(adjVertex);

            pos = graphStr.Find(',', pos) + 1;
        }

        graph.push_back(vertex);

        pos = graphStr.Find('\n', pos) + 1;
    }
}


CString printVerticesByLayers(std::vector<Vertex>& graph, int startVertex) {
    std::vector<int> layer;
    std::vector<int> visited(graph.size(), false);
    visited[startVertex] = true;
    layer.push_back(startVertex);

    CString result;

    while (!layer.empty()) {
        std::vector<int> nextLayer;

        for (int vertex : layer) {
            CString strVertex;
            strVertex.Format(_T("%d"), graph[vertex].number);
            result += strVertex;
            result += _T(" ");

            for (int adjVertex : graph[vertex].adjacentVertices) {
                if (!visited[adjVertex]) {
                    visited[adjVertex] = true;
                    nextLayer.push_back(adjVertex);
                }
            }
        }

        result += _T("\n");

        layer = nextLayer;
    }

    return result;
}

#endif  // GRAPH_LAYERS_H