#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

int graph[26][26];
int visited[26];
string result;

void dfs(int v) {
    visited[v] = 1;
    for (int i = 0; i < 26; i++) if (v != i && graph[v][i] == 1 && visited[i] == 0) {
        dfs(i);
    }
    result.push_back('a' + v);
}

void solve() {
    memset(graph, 0, sizeof(graph));
    memset(visited, 0, sizeof(visited));
    result = "";
    int n; cin>>n;
    
    string prev; cin>>prev;
    for (int i = 0; i < n-1; i++) {
        string cur; cin>>cur;
        for (int j = 0; j < min(prev.size(), cur.size()); j++) {
            if (prev[j] == cur[j]) continue;
            graph[prev[j] - 'a'][cur[j] - 'a'] = 1;
            break;
        }
        prev = cur;
    }
    
    for (int i = 0; i < 26; i++) if (visited[i] == 0) {
        dfs(i);
    }
    
    reverse(result.begin(), result.end());
    
    for (int i = 0; i < 26; i++) {
        for (int j = i + 1; j < 26; j++) {
            if (graph[result[j] - 'a'][result[i] - 'a']) {
                cout<<"INVALID HYPOTHESIS"<<endl;
                return;
            }
        }
    }
    
    cout<<result<<endl;
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++)
        solve();
    
    return 0;
}
