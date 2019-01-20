#include <iostream>
#include <vector>

using namespace std;

struct FenwickTree {
    vector<int> tree;
    FenwickTree(int n) : tree(n+1) {}
    
    int sum(int pos) {
        pos++;
        int ret = 0;
        while (pos > 0) {
            ret += tree[pos];
            pos &= (pos-1);
        }
        return ret;
    }
    
    void add(int pos, int val) {
        pos++;
        while (pos < tree.size()) {
            tree[pos] += val;
            pos += (pos & -pos);
        }
    }
};

long long countMoves(const vector<int>& A) {
    FenwickTree tree(1000000);
    long long ret = 0;
    for (int i = 0; i < A.size(); i++) {
        ret += tree.sum(999999) - tree.sum(A[i]);
        tree.add(A[i], 1);
    }
    return ret;
}

void solve() {
    int n; cin>>n;
    vector<int> A(n);
    for (int i = 0; i < n; i++)
        cin>>A[i];
    cout<<countMoves(A)<<endl;
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
