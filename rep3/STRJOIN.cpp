#include <iostream>
#include <queue>

using namespace std;

int n;

void solve() {
    cin>>n;
    priority_queue<int> pq;
    for (int i = 0; i < n; i++) {
        int input; cin>>input;
        pq.push(-input);
    }
    
    int ret = 0;
    while (pq.size() > 1) {
        int sum = pq.top(); pq.pop();
        sum += pq.top(); pq.pop();
        ret -= sum;
        pq.push(sum);
    }
    
    cout<<ret<<endl;
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
