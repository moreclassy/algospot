#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

const int INF = 987654321;
int n, s;
vector<int> series;
int cache[100][11];
int cache2[100][101];

int subError(int b, int e) {
    int& ret = cache2[b][e];
    if (ret != -1) return ret;
    
    int sum = 0;
    for (int i = b; i < e; i++)
        sum += series[i];
    
    int ave = sum / (e - b);
    
    int error1 = 0;
    for (int i = b; i < e; i++)
        error1 += (series[i] - ave)*(series[i] - ave);
    
    ave++;
    int error2 = 0;
    for (int i = b; i < e; i++)
        error2 += (series[i] - ave)*(series[i] - ave);
    
    return ret = min(error1, error2);
}

int minError(int idx, int qc) {
    if (idx == n) return 0;
    if (qc == 0) return INF;
    
    int& ret = cache[idx][qc];
    if (ret != -1) return ret;
    
    ret = INF;
    for (int i = idx+1; i <= n; i++) {
        ret = min(ret, subError(idx, i) + minError(i, qc-1));
    }
    
    return ret;
}

void solve() {
    memset(cache, -1, sizeof(cache));
    memset(cache2, -1, sizeof(cache2));
    cin>>n>>s;
    series = vector<int>(n);
    for (int i = 0; i < n; i++)
        cin>>series[i];
    
    sort(series.begin(), series.end());
    
    cout<<minError(0, s)<<endl;
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++)
        solve();
    
    return 0;
}
