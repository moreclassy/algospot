#include <iostream>
#include <utility>
#include <cmath>
#include <algorithm>

using namespace std;

const int INF = 987654321;
const double pi = 2.0 * acos(0);

int n;
double y[100], x[100], r[100];
pair<double, double> ranges[100];

void convert2Range() {
    for (int i = 0; i < n; i++) {
        double loc = fmod(2*pi + atan2(y[i], x[i]), 2*pi);
        double range = 2.0 * asin(r[i] / 2.0 / 8.0);
        ranges[i] = make_pair(loc - range, loc + range);
    }
    
    sort(ranges, ranges + n);
}

int solveLinear(double begin, double end) {
    int used = 0, idx = 0;
    
    while (begin < end) {
        double maxCover = -1;
        
        while (idx < n && ranges[idx].first <= begin) {
            maxCover = max(maxCover, ranges[idx].second);
            ++idx;
        }
        
        if (maxCover <= begin) return INF;
        begin = maxCover;
        ++used;
    }
    
    return used;
}

int solveCircular() {
    int ret = INF;
    
    for (int i = 0; i < n; i++) {
        if (ranges[i].first <= 0 || ranges[i].second >= 2*pi) {
            double begin = fmod(ranges[i].second, 2*pi);
            double end = fmod(2*pi + ranges[i].first, 2*pi);
            
            ret = min(ret, 1 + solveLinear(begin, end));
        }
    }
    
    return ret;
}

void solve() {
    cin>>n;
    for (int i = 0; i < n; i++)
        cin>>y[i]>>x[i]>>r[i];
    
    convert2Range();
    
    int ret = solveCircular();
    
    if (ret >= INF)
        cout<<"IMPOSSIBLE"<<endl;
    else
        cout<<ret<<endl;
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
