#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <string>
#include <cmath>
#include <set>
#include <queue>

#define _USE_MATH_DEFINES

using namespace std;

const int MAX_V = 1000;

int g, h;
vector<vector<int>> adj;
vector<bool> visited;

const int UNWATCHED = 0;
const int WATCHED = 1;
const int INSTALLED = 2;

int installed;

void Reset()
{
    installed = 0;
    adj = vector<vector<int>>(MAX_V, vector<int>());
}

void GetInput()
{
    cin>>g>>h;
    visited = vector<bool>(g, false);
    int u, v;
    for (int i = 0; i < h; i++) {
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

// here로부터 깊이 우선 탐색을 하고, here의 정보를 반환한다.
// 0:unwatched, 1:watched, 2:installed
int dfs(int here)
{
    visited[here] = true;
    // 각 타입(unwatched/watched/installed)의 자식 노드 수
    int children[3] = {0,0,0};
    
    for (int i = 0; i < adj[here].size(); i++) {
        int there = adj[here][i];
        if (!visited[there])
            ++children[dfs(there)];
    }
    
    // 자식 노드 중 감시되지 않는 노드가 있을 경우 카메라 설치
    if (children[UNWATCHED]) {
        ++installed;
        return INSTALLED;
    }
    
    // 자식 노드 중 카메라가 설치된 노드가 있을 경우 설치할 필요가 없다
    if (children[INSTALLED]) {
        return WATCHED;
    }
    return UNWATCHED;
}

void Solve()
{
    Reset();
    GetInput();
    
    for (int i = 0; i < g; i++) {
        if (!visited[i] && dfs(i) == UNWATCHED)
            ++installed;
    }
    
    cout<<installed<<endl;
}

int main(int argc, const char * argv[]) {
    int caseCnt = 0;
    cin>>caseCnt;
    
    for (int i = 0; i < caseCnt; i++) {
        Solve();
    }
    
    return 0;
}
