#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <string>
#include <cmath>
#include <set>
#include <queue>
#include <climits>
#include <cfloat>

#define _USE_MATH_DEFINES

using namespace std;

int n; // 컴퓨터 수
int m; // 회선의 수
int const MAX_N = 10000; // 최대 컴퓨터 수
vector<pair<int, double>> adj[MAX_N]; // 간선 (정점 번호, 간선 가중치)

void Reset()
{
    cin>>n;
    for (int i = 0; i < n; i++) {
        adj[i].clear();
    }
}

void GetInput()
{
    cin>>m;
    int u, v;
    double cost;
    for (int i = 0; i < m; i++) {
        cin>>u>>v>>cost;
        adj[u].push_back(make_pair(v, cost));
    }
}

vector<double> dijkstra(int src)
{
    vector<double> dist(n, DBL_MAX);
    dist[src] = 1.0;
    priority_queue<pair<double, int>> pq;
    pq.push(make_pair(-1.0, src));
    
    while (!pq.empty())
    {
        double cost = -pq.top().first;
        int here = pq.top().second;
        pq.pop();
        
        if (dist[here] < cost) continue;
        
        for (int i = 0; i < adj[here].size(); i++) {
            int there = adj[here][i].first;
            double nextDist = cost * adj[here][i].second;
            if (dist[there] > nextDist) {
                dist[there] = nextDist;
                pq.push(make_pair(-nextDist, there));
            }
        }
    }
    
    return dist;
}

void Solve()
{
    Reset();
    GetInput();
    
    vector<double> dist = dijkstra(0);
    cout<<dist[n-1]<<endl;
}

int main(int argc, const char * argv[]) {
    int caseCnt = 0;
    cin>>caseCnt;
    
    cout << fixed; cout.precision(10);
    for (int i = 0; i < caseCnt; i++) {
        Solve();
    }
    
    return 0;
}
