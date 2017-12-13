#include <vector>
#include <iostream>
#include <map>
#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;

vector<unordered_map<string, int>> toSort(9);

void preCalcN(int n) {
    if (!toSort[n].empty()) return;
    
    string sorted(n, '0');
    for (int i = 0; i < n; i++) sorted[i] = '1' + i;
    
    queue<string> sq;
    sq.push(sorted);
    toSort[n][sorted] = 0;
    
    while (!sq.empty()) {
        auto cur = sq.front(); sq.pop();
        int cost = toSort[n][cur];
        for (int i = 0; i < n; i++) {
            for (int j = i + 2; j <= n; j++) {
                reverse(cur.begin() + i, cur.begin() + j);
                if (toSort[n].count(cur) == 0) {
                    toSort[n][cur] = cost + 1;
                    sq.push(cur);
                }
                reverse(cur.begin() + i, cur.begin() + j);
            }
        }
    }
}

int solve() {
    int n; cin>>n;
    vector<int> input(n);
    for (int i = 0; i < n; i++)
        cin>>input[i];
    
    string node(n, '0');
    for (int i = 0; i < n; i++) {
        int smaller = 0;
        for (int j = 0; j < n; j++)
            if (input[j] <= input[i])
                smaller++;
        node[i] = '0' + smaller;
    }
    
    preCalcN(n);
    
    return toSort[n][node];
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++)
        cout<<solve()<<endl;
    
    return 0;
}
