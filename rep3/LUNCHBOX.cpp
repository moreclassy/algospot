#include <iostream>
#include <utility>
#include <algorithm>

using namespace std;

const int MAX_N = 10000;

int n;
pair<int, int> box[MAX_N];

void solve() {
    cin>>n;
    for (int i = 0; i < n; i++)
        cin>>box[i].second;
    for (int i = 0; i < n; i++)
        cin>>box[i].first;
    
    sort(box, box + n);
    
    int heat = 0, eat = 0;
    for (int i = n-1; i >= 0; i--) {
        heat += box[i].second;
        eat = max(eat - box[i].second, box[i].first);
    }
    
    cout<<heat + eat<<endl;
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
