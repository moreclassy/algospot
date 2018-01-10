#include <vector>
#include <iostream>
#include <unordered_map>
#include <queue>
#include <climits>

using namespace std;

void solve() {
    int n; cin>>n;
    vector<vector<pair<int, double>>> edge(n);
    vector<double> cost(n, 1000000*(double)LLONG_MIN);
    
    int m; cin>>m;
    for (int i = 0; i < m; i++) {
        int s; cin>>s;
        int e; cin>>e;
        double w; cin>>w;
        edge[s].push_back({e, w});
        edge[e].push_back({s, w});
    }
    
    priority_queue<pair<double, int>> pq;
    pq.push({-1.0, 0});
    vector<bool> visited(n, false);
    
    while (!pq.empty()) {
        int curNode = pq.top().second;
        double curCost = pq.top().first;
        pq.pop();
        
        if (visited[curNode]) continue;
        visited[curNode] = true;
        cost[curNode] = curCost;
        
        for (auto e : edge[curNode]) {
            int nextNode = e.first;
            double nextCost = curCost * e.second;
            
            if (!visited[nextNode]) pq.push({nextCost, nextNode});
        }
    }
    
    cout<<-cost.back()<<endl;
}

int main() {
    cout<<fixed;
    cout.precision(10);
    
    int c; cin>>c;
    for (int i = 0; i < c; i++) solve();
    
    return 0;
}
