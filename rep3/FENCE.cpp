#include <iostream>
#include <algorithm>

using namespace std;

int n;
int height[20000];

int maxArea(int b, int e) {
    if (b >= e) return 0;
    if (b+1 == e) return height[b];
    
    int mid = b + (e - b)/2;
    int ret = max(maxArea(b, mid), maxArea(mid, e));
    
    int l = mid, r = mid+1, curh = height[mid];
    while(b < l || r < e) {
        if (r >= e) {
            curh = min(curh, height[--l]);
        } else if (b >= l) {
            curh = min(curh, height[r++]);
        } else if(height[l-1] > height[r]) {
            curh = min(curh, height[--l]);
        } else {
            curh = min(curh, height[r++]);
        }
        
        ret = max(ret, curh * (r - l));
    }
    
    return ret;
}

void solve() {
    cin>>n;
    for (int i = 0; i < n; i++)
        cin>>height[i];
    cout<<endl;
    cout<<maxArea(0, n)<<endl;
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
