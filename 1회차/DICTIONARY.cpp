#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <string>
#include <cmath>
#include <set>
#include <queue>
#include <list>

#define _USE_MATH_DEFINES

using namespace std;

vector<vector<bool>> graph;
vector<bool> visited;
string ret;

void Reset()
{
    graph.clear();
    graph = *new vector<vector<bool>>(26, vector<bool>(26, false));
    
    visited.clear();
    visited = *new vector<bool>(26, false);
    
    ret.clear();
}

void setGraph(string s1, string s2)
{
    int len = (int)min(s1.size(), s2.size());
    for (int i = 0; i < len; i++)
    {
        if (s1[i] != s2[i]) {
            graph[s1[i]-'a'][s2[i]-'a'] = true;
            return;
        }
    }
}

void GetInput()
{
    int n;
    cin>>n;
    string a, b;
    cin>>a;
    for (int i = 1; i < n; i++)
    {
        if (i%2) {
            cin>>b; setGraph(a, b);
        } else {
            cin>>a; setGraph(b, a);
        }
    }
}

void dfs(int v)
{
    visited[v] = true;
    
    for (int i = 0; i < 26; i++) {
        if (!visited[i] && graph[v][i])
            dfs(i);
    }
    
    ret += (char)(v + 'a');
}

void printGraph()
{
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            if (graph[i][j])
                cout<<(char)(i+'a')<<" "<<(char)(j+'a')<<endl;
        }
    }
    cout<<endl;
}

void Solve()
{
    Reset();
    GetInput();
    //printGraph();
    
    for (int i = 25; i >= 0; i--)
    {
        if (!visited[i])
            dfs(i);
    }
    
    reverse(ret.begin(), ret.end());
    
    for (int i = 0; i < ret.size(); i++)
    {
        for (int j = i + 1; j < ret.size(); j++)
        {
            if (graph[ret[j]-'a'][ret[i]-'a']) {
                cout<<"INVALID HYPOTHESIS"<<endl;
                return;
            }
        }
    }
    
    cout<<ret<<endl;
}

int main(int argc, const char * argv[]) {
    int caseCnt = 0;
    cin>>caseCnt;
    
    for (int i = 0; i < caseCnt; i++) {
        Solve();
    }
    
    return 0;
}
