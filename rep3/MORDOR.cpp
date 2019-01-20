#include <vector>
#include <algorithm>
#include <climits>
#include <iostream>

using namespace std;

class RMQ {
public:
    RMQ(const vector<int>& array) {
        n = (int)array.size();
        rangeMin.resize(n * 4);
        init(array, 0, n-1, 1);
    }
    
    int query(int left, int right) {
        return query(left, right, 1, 0, n-1);
    }
    
    int update(int index, int newValue) {
        return update(index, newValue, 1, 0, n-1);
    }
    
private:
    int n;
    vector<int> rangeMin;
    
    int init(const vector<int>& array, int left, int right, int node) {
        if (left == right) return rangeMin[node] = array[left];
        
        int mid = (left + right) / 2;
        int leftMin = init(array, left, mid, node * 2);
        int rightMin = init(array, mid +1, right, node * 2 +1);
        
        return rangeMin[node] = min(leftMin, rightMin);
    }
    
    int query(int left, int right, int node, int nodeLeft, int nodeRight) {
        if (right < nodeLeft || left > nodeRight) return INT_MAX;
        
        if (left <= nodeLeft && nodeRight <= right) return rangeMin[node];
        
        int mid = (nodeLeft + nodeRight) / 2;
        int leftMin = query(left, right, node*2, nodeLeft, mid);
        int rightMin = query(left, right, node*2 +1, mid +1, nodeRight);
        return min(leftMin, rightMin);
    }
    
    int update(int index, int newValue, int node, int nodeLeft, int nodeRight) {
        if (index < nodeLeft || nodeRight < index) return rangeMin[node];
        
        if (nodeLeft == nodeRight) return rangeMin[node] = newValue;
        
        int mid = (nodeLeft + nodeRight) / 2;
        
        int leftMin = update(index, newValue, node*2, nodeLeft, mid);
        int rightMin = update(index, newValue, node*2 +1, mid +1, nodeRight);
        return min(leftMin, rightMin);
    }
};

void solve() {
    int n; cin>>n;
    int q; cin>>q;
    
    vector<int> signs(n);
    for (int i = 0; i < n; i++) cin>>signs[i];
    auto minq = RMQ(signs);
    
    for (int i = 0; i < n; i++) signs[i] *= -1;
    auto maxq = RMQ(signs);
    
    for (int i = 0; i < q; i++) {
        int left, right;
        cin>>left>>right;
        int lowest = minq.query(left, right);
        int highest = -maxq.query(left, right);
        cout<<abs(highest - lowest)<<endl;
    }
}

int main() {
    int c; cin>>c;
    for (int i = 0 ; i < c; i++) {
        solve();
    }
    
    return 0;
}
