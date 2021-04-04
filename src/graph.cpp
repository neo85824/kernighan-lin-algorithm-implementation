#include "graph.h"

using namespace std;

Vertex::Vertex(int index) : index(index) {}

Graph::Graph(int n) : n(n) {
    vertexs = new Vertex[n];
    weights = new int*[n];
    for(int i=0; i<n; i++) {
        vertexs[i].index = i;
        weights[i] = new int[n]();
    }
}

Graph::~Graph() {
    delete [] vertexs;
    for(int i=0; i<n; i++) {
        delete [] weights[i];
    }
    delete [] weights;
}

void Graph::AddEdge(int p, int q, int w) {
    weights[p][q] = w;
    weights[q][p] = w;
    vertexs[p].adj.insert(q);
    vertexs[q].adj.insert(p);
}

void Graph::PrintAdjacent(int v_index) {
    cout << "v: " << v_index << endl;
    for(auto it : vertexs[v_index].adj) {
        cout << "adj: " << it << " , weight: " << weights[v_index][it] << endl;
    }
}
