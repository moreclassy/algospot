#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

const int MAX_V = 500;
const int INF = 1000000;
int V, adj[MAX_V][MAX_V];
int delay[MAX_V];
int W[MAX_V][MAX_V];

void calculateW() {
    vector<pair<int, int>> order;
    for (int i = 0; i < V; i++)
        order.push_back(make_pair(delay[i], i));
    sort(order.begin(), order.end());
    
    for (int k = 0; k < V; k++) {
        int w = order[k].second;
        
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                adj[i][j] = min(adj[i][j], adj[i][w] + adj[w][j]);
                W[i][j] = min(W[i][j], adj[i][w] + delay[w] + adj[w][j]);
            }
        }
    }
}

int main() {
    int e;
    cin>>V>>e;
    
    for (int i = 0; i < V; i++) cin>>delay[i];
    
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i == j) W[i][j] = adj[i][j] = 0;
            else W[i][j] = adj[i][j] = INF;
        }
    }
    
    for (int i = 0; i < e; i++) {
        int a, b, c;
        cin>>a>>b>>c;
        W[a-1][b-1] = W[b-1][a-1] = adj[a-1][b-1] = adj[b-1][a-1] = c;
    }
    
    calculateW();
    
    int t; cin>>t;
    for (int i = 0; i < t; i++) {
        int start, target;
        cin>>start>>target;
        cout<<W[start-1][target-1]<<endl;
    }
    
    return 0;
}
