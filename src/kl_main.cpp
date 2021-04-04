#include <iostream>
#include "kl.cpp"
#include <fstream>
using namespace std;

int main(int argc, char** argv) {
    int n, e;
    cin >> n >>  e;
    int v = n & 1 ? n+1 : n;  // dummy vertex for non equal size of subsets a & b
    Graph graph(v);
    cout << "number of vertices : "  << n << endl;

    for(int i=0; i<e; i++) {
        int a, b;
        cin >> a >> b ;
        graph.AddEdge(a-1, b-1, 1);
    }
    
    KL kl(graph);
    vector<bool> &&is_A = kl.Solve();
    vector<int> A, B;

    ofstream out_file(argv[1]);
    for(int i=0; i<n; i++) {
        if(is_A[i]) A.push_back(i+1);
        else B.push_back(i+1);
    }
    if(argc > 1) {
        out_file << "Group A = {";
        for(auto a : A) {
            out_file << a << " ";
        }
        out_file << "}" <<endl;

        out_file << "Group B = {";
        for(auto b : B) {
            out_file << b << " ";
        }
        out_file << "}" <<endl;

        out_file << "Cut-size = " << kl.GetCutCost() << endl;

        out_file.close();
    }
}