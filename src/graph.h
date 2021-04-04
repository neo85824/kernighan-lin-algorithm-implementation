#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Vertex {
public:
    int index = -1;
    unordered_set<int> adj;
    Vertex() {};
    Vertex(int index); 
};

class Graph {
public:
    int n = 0;
    Vertex *vertexs = NULL;
    int **weights = NULL;
    Graph () {}
    Graph(int n);
    ~Graph();
    void AddEdge(int p, int q, int w);
    void PrintAdjacent(int v_index);
};
