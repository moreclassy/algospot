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
    
    void printNodes() {
        cout<<"print0:"<<rangeMin[0]<<endl;
        for (int i = 0; i < rangeMin.size(); i++)
            cout<<rangeMin[i]<<" ";
        cout<<endl;
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

const int MAX_N = 100000;

class solver {
public:
    solver(int n) {
        for (int i = 1; i < n; i++) {
            int parent; cin>>parent;
            if (parent != i)
                child[parent].push_back(i);
        }
        
        prepareRMQ();
    }
    
    int distance(int u, int v) {
        int lu = locInTrip[u], lv = locInTrip[v];
        if (lu > lv) swap(lu, lv);
        int lca = serial2no[rmq->query(lu, lv)];
        return depth[u] + depth[v] - 2 * depth[lca];
    }
    
private:
    vector<int> child[MAX_N];
    int no2serial[MAX_N], serial2no[MAX_N];
    int locInTrip[MAX_N], depth[MAX_N];
    int nextSerial = 0;
    RMQ* rmq;
    
    void prepareRMQ() {
        nextSerial = 0;
        vector<int> trip;
        traverse(0, 0, trip);
        rmq = new RMQ(trip);
    }
    
    void traverse(int here, int d, vector<int>& trip) {
        no2serial[here] = nextSerial;
        serial2no[nextSerial] = here;
        ++nextSerial;
        depth[here] = d;
        locInTrip[here] = (int)trip.size();
        trip.push_back(no2serial[here]);
        
        for (int i = 0; i < child[here].size(); i++) {
            traverse(child[here][i], d + 1, trip);
            trip.push_back(no2serial[here]);
        }
    }
};

void solve() {
    int n, q; cin>>n>>q;
    auto s = solver(n);
    for (int i = 0; i < q; i++) {
        int u, v; cin>>u>>v;
        cout<<s.distance(u, v)<<endl;
    }
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++)
        solve();
    
    return 0;
}
