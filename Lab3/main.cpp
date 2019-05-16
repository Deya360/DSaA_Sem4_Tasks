#include <QCoreApplication>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#include "graph.h"

int V;

int printMST(std::vector<int> parent, std::vector<std::vector<int>> graph) {
    std::cout << "Edge \t\tWeight" << std::endl;
    int sum = 0;
    for (int i = 1; i < V; i++) {
        printf("%d - %d \t\t%d \n", parent[i], i, graph[i][parent[i]]);
        sum += graph[i][parent[i]];
    }

    std::cout << "Tree Weight: " << sum;
}

int minKey(std::vector<int> key, std::vector<bool> mstSet) {
    int min = INT_MAX;
    int min_index;

    for (int ver = 0; ver < V; ver++) {
        if (mstSet.at(ver) == false && (key.at(ver) < min)) {
            min = key.at(ver);
            min_index = ver;
        }
    }

    return min_index;
}

void primMST(Graph &g) {
    std::vector<std::vector<int>> graph = g.getAdjMatrix();
    std::vector<int> parent(V);
    std::vector<int> key(V);
    std::vector<bool> mstSet(V);

    for (int i = 0; i < V; i++) {
        key.at(i) = INT_MAX;
        mstSet.at(i) = false;
    }

    key.at(0) = 0;
    parent.at(0) = -1;

    for (int count = 0; count < V-1; count++) {
        int u = minKey(key, mstSet);
        mstSet[u] = true;

        for (int v = 0; v < V; v++) {

            if (graph.at(u).at(v) && mstSet.at(v) == false && graph.at(u).at(v) < key.at(v)) {
                parent.at(v) = u;
                key.at(v) = graph.at(u).at(v);
            }
        }
    }

    printMST(parent, graph);
}



int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);


//    std::vector<std::vector<int>> adjMatrix = {{0, 4, 4, 6, 6},
//                                               {4, 0, 2, 0, 0},
//                                               {4, 2, 0, 8, 0},
//                                               {6, 0, 8, 0, 9},
//                                               {6, 0, 0, 9, 0}};

    std::vector<std::vector<int>> adjMatrix = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
                                               {4, 0, 8, 0, 0, 0, 0, 11, 0},
                                               {0, 8, 0, 7, 0, 4, 0, 0, 2},
                                               {0, 0, 7, 0, 9, 14, 0, 0, 0},
                                               {0, 0, 0, 9, 0, 10, 0, 0, 0},
                                               {0, 0, 4, 14, 10, 0, 2, 0, 0},
                                               {0, 0, 0, 0, 0, 2, 0, 1, 6},
                                               {8, 11, 0, 0, 0, 0, 1, 0, 7},
                                               {0, 0, 2, 0, 0, 0, 6, 7, 0}};

    V = adjMatrix.size();
    Graph g(V);

    for (int i = 0; i < V; i++) {
        g.addVertex(new vertex(i));
    }

    g.setAdjMatrix(adjMatrix);
    primMST(g);

    return a.exec();
}
