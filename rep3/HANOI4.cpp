#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

const int POLLS = 4;
const int MAX_DISCS = 12;

int get(int state, int index) {
    return (state >> (index * 2)) & 3;
}

int set(int state, int index, int value) {
    return (state & ~(3 << (index * 2))) | (value << (index * 2));
}

int c[1 << (MAX_DISCS * 2)];

int sgn(int x) {
    if (!x) return 0;
    return x > 0 ? 1 : -1;
}

int incr(int x) {
    return x < 0 ? x - 1 : x + 1;
}

int bidir(int discs, int begin, int end) {
    if (begin == end) return 0;
    
    queue<int> q;
    memset(c, 0, sizeof(c));
    
    q.push(begin); c[begin] = 1;
    q.push(end); c[end] = -1;
                   
    while (!q.empty()) {
        int here = q.front();
        q.pop();

        int top[POLLS];
        memset(top, -1, sizeof(top));
        for (int i = discs - 1; i >= 0; i--) {
           top[get(here, i)] = i;
        }

        for (int i = 0; i < POLLS; i++) {
            if (top[i] != -1) {
                for (int j = 0; j < POLLS; j++) {
                    if (i == j) continue;
                    if (top[j] != -1 && top[i] > top[j]) continue;
                    int there = set(here, top[i], j);
                    if (c[there] == 0) {
                        c[there] = incr(c[here]);
                        q.push(there);
                    } else if (sgn(c[there]) != sgn(c[here])) {
                        return abs(c[there]) + abs(c[here]) - 1;
                    }
                }
            }
        }
    }
    
    return -1;
}

void solve() {
    int n;
    cin>>n;
    int begin = 0;
    for (int i = 0; i < POLLS; i++) {
        int nums; cin>>nums;
        for (int j = 0; j < nums; j++) {
            int disc; cin>>disc;
            begin = set(begin, disc - 1, i);
        }
    }
    
    int end = (1 << (n * 2)) - 1;
    
    cout<<bidir(n, begin, end)<<endl;
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
