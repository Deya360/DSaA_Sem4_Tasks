#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <string>
#include <queue>

struct vertex {
    int weight;
    vertex(int weight) {this->weight = weight;}
};

class Graph {
private:
    static const int NULL_EDGE = 0;
    std::vector<vertex*> vertices;
    std::vector<bool> visited;
    int nmbVertices;
    int maxVertices;
    std::vector<std::vector<int>> edges;

public:
    Graph(int size) {
        nmbVertices = 0;
        maxVertices = size;

        vertices.resize(size);
        for (int i=0;i<size;i++)	// init vertices
            vertices[i] = nullptr;

        edges.resize(size, std::vector<int>(size, 0));
    }

    ~Graph() {
        for (int i=0;i<nmbVertices;i++) {
            delete vertices[i];
        }
    }

    bool isEmpty() {
        return (nmbVertices == 0);
    }

    bool isFull() {
        return (nmbVertices == maxVertices);
    }

    void addVertex(vertex* aVertex) {
        vertices[nmbVertices] = aVertex;
        for (int i=0; i<maxVertices; i++)
        {
            edges[nmbVertices][i] = NULL_EDGE;
            edges[i][nmbVertices] = NULL_EDGE;
        }
        nmbVertices++;
    }

    void addEdge(int fromVertex, int toVertex, int weight) {
        int row = indexIs(vertices[fromVertex]);
        int column = indexIs(vertices[toVertex]);

        edges[row][column] = weight;
    }

    int weightIs(int fromVertex, int toVertex) {
        int row = indexIs(vertices[fromVertex]);
        int column = indexIs(vertices[toVertex]);

        return edges[row][column];
    }

    int indexIs(vertex* aVertex) {
        int i = 0;
        while (i < nmbVertices) {
            if (vertices.at(i) == aVertex)
                return i;
            i++;
        }
        return -1;
    }

    std::vector<std::vector<int>> getAdjMatrix() {
        return edges;
    }

    void setAdjMatrix(const std::vector<std::vector<int> > &value){
        edges = value;
    }

    void utilDFS(vertex* aVertex) {
        int ix,ix2;
        if (aVertex == nullptr) return;

        std::cout << aVertex->weight << " ";
        ix = indexIs(aVertex);

        for (int i=0; i<nmbVertices; i++) {
            ix2 = indexIs(vertices[i]);
            if (edges[ix][ix2] != NULL_EDGE) {
                if (visited[i] == false) utilDFS(vertices[i]);
            }
        }
    }

    void printDFS(int i) {
        visited.clear();
        for (auto v: visited) v = false;
        utilDFS(vertices.at(i));
    }
};

#endif // GRAPH_H


