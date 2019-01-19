#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

void print(vector<int>& v) {
    for (int a : v)
        cout<<a<<" ";
    cout<<endl;
}

void printPost(vector<int>& pre, int pi, vector<int>& ino, int ib, int ie) {
    if (ib == ie || pi == pre.size()) return;
    int rval = pre[pi], ri = ib;
    for (int i = ib; i < ie; i++) {
        if (rval == ino[i]) {
            ri = i;
        }
    }
    printPost(pre, pi+1, ino, ib, ri);
    printPost(pre, pi + ri - ib + 1, ino, ri+1, ie);
    cout<<rval<<" ";
}

void solve() {
    int n; cin>>n;
    vector<int> pre(n), ino(n);
    for (int i = 0; i < n; i++) cin>>pre[i];
    for (int i = 0; i < n; i++) cin>>ino[i];
    printPost(pre, 0, ino, 0, n);
    cout<<endl;
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++)
        solve();
    
    return 0;
}
