#include <iostream>
#include <vector>
#include <algorithm>
#include "graph.h"

using namespace std;

class KL {
public:
    int n;  // number of vertex
    int **D; // D: 2d matrix, which will be sorted in accending order
            // D[i][0] stands for the D value of the vertex
            // D[i][1] stands for index of the vertex
    int *gv, *av, *bv;  
    bool *lock, *is_A; // is_A: determine the vertex is in A set or not
    Graph *graph;

    KL(Graph &g) {
        graph = &g;
        n = graph->n;
        is_A = new bool[n]();

        // initial partition
        for(int i=0; i<n/2; i++) is_A[i] = true;
        
        D = new int*[n]();
        for(int i=0; i<n; i++) 
            D[i] = new int[2]();
        gv = new int[n/2]();
        av = new int[n/2]();
        bv = new int[n/2]();
        lock = new bool[n]();
    }

    ~KL() {
        for(int i=0; i<n; i++) 
            delete [] D[i];
        delete [] D;
        delete [] gv;
        delete [] av;
        delete [] bv;
        delete [] lock;
        delete [] is_A;
    }

    vector<bool> Solve() {
        int G_k = INT_MAX;
        
        while(G_k > 0) {
            cout << "Curent cost: " << GetCutCost();

            
            Initialization(); // unlock the vertices
            ComputeD();
            for(int i=0; i<n/2; i++) {
                vector<int> &&res = FindMaxG();  // find pair (a, b) with maximum g 
                int g = res[0], a = res[1], b = res[2];
                lock[a] = true;  
                lock[b] = true;
                gv[i] = g;
                av[i] = a;
                bv[i] = b;
                UpdateD(a, b);
            }

            // find k for maximum g
            int k = -1;
            int partial_sum = 0;
            G_k = INT_MIN;
            for(int i=0; i<n/2; i++) {
                partial_sum += gv[i];
                if(partial_sum > G_k) {
                    G_k = partial_sum;
                    k = i;
                }
            }

            cout << ",  G_k: " << G_k << endl;

            if(G_k > 0) {
                for(int i=0; i<=k; i++) {
                    // swap vertices
                    is_A[av[i]] = false;
                    is_A[bv[i]] = true;
                }
            }
        }
        cout << "---------------------------------------------------------------------------------------------------" << endl;
        cout << "Final cost: " << GetCutCost() << endl;

        return vector<bool>(is_A, is_A + n/2);
    }

    void Initialization() {
        // unlock vertices
        for(int i=0; i<n; i++) lock[i] = false;
    }

    void ComputeD() {
        for(int i=0; i<n; i++) {
            bool cur_set = is_A[i];
            int I = 0;
            int E = 0;
            for(auto adj_index : graph->vertexs[i].adj) {
                if(is_A[adj_index] == cur_set)  I += graph->weights[i][adj_index];
                else E += graph->weights[i][adj_index];
            }
            D[i][0] = E - I;
            D[i][1] = i;

            // insertion sort to make sure D is in accending order
            int k = D[i][0];
            for(int j=i-1; j>=0; j--) {
                if(D[j][0] > k) swap(D[j], D[j+1]);
                else break;
            }
        }
    }

    vector<int> FindMaxG() {
        int max_g = INT_MIN;
        int max_a = -1, max_b = -1;

        // start with the maximum value of D i.e. the last value of D, then calculate g. 
        // If g is less than max_g, we can early break.
        for(int i=n-1; i>=1; i--)  {
            int p_idx = D[i][1];
            if(lock[p_idx])
                continue;

            int j = i-1;
            // find first vertex of differenet set
            while(j >= 0 && (is_A[p_idx] == is_A[D[j][1]] || lock[D[j][1]])) { 
                j--;
            }       

            // if less than mag_g -> early stop 
            if(j < 0 || D[i][0] + D[j][0] - 2*graph->weights[D[i][1]][D[j][1]]< max_g)  {  
                break;
            }
                
            // j is the first vertex of differenet set that passes the threshold 
            for(; j>=0; j--) {
                int q_idx = D[j][1];
                if(is_A[p_idx] == is_A[q_idx] || lock[q_idx])
                    continue;
                    
                int g = D[i][0] + D[j][0] - 2*graph->weights[p_idx][q_idx]; 
                if(g < max_g) // early break
                    break;
                else if(g > max_g) {
                    max_g = g;
                    max_a = is_A[p_idx] ? p_idx : q_idx;
                    max_b = is_A[p_idx] ? q_idx : p_idx;
                }
            }
        }
        return vector<int>{max_g, max_a, max_b};
    }

    void UpdateD(int p, int q) {
        for(int i=0; i<n; i++) {
            int idx = D[i][1];
            if(!lock[idx]) {
                if(is_A[idx]) D[i][0] = D[i][0] + 2 * graph->weights[idx][p] - 2 * graph->weights[idx][q];
                else D[i][0] = D[i][0] + 2 * graph->weights[idx][q] - 2 * graph->weights[idx][p];
            
                // insertion sort to make sure D is in accending order
                int k = D[i][0];
                for(int j=i-1; j>=0; j--) {
                    if(D[j][0] > k) swap(D[j], D[j+1]);
                    else break;
                }   
            }
        }
    }

    int GetCutCost() {
        int cost = 0;       
        for(int i=0; i<n; i++) {
            for(auto adj_index : graph->vertexs[i].adj) {
                if(is_A[i] != is_A[adj_index]) cost += graph->weights[i][adj_index];
            }
        }
        return cost/2;
    }

    void PrintD() {
        cout << "D: " << endl;
        for(int i=0; i<n; i++) cout << "( "<< D[i][0] << ", " << D[i][1] << " ) " ;
        cout << endl;
    }
 };


