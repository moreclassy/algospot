#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 987654321;
const double pi = 2.0 * acos(0);
int n;
pair<double, double> ranges[100];

void getInput() {
    cin>>n;
    for (int i = 0; i < n; i++) {
        double x, y, r;
        cin>>y>>x>>r;
        double loc = fmod(2*pi + atan2(y, x), 2*pi);
        double range = 2 * asin(r / 2.0 / 8.0);
        // 감시 시작 범위, 감시 끝 범위 저장
        ranges[i] = make_pair(loc - range, loc + range);
    }
    
    // 감시 시작 위치가 작은 순으로 정렬
    sort(ranges, ranges + n);
}

// [begin, end] 구간을 덮기 위한 최소한의 구간 수 반환
int solveLinear(double begin, double end) {
    int used = 0, idx = 0;
    
    // 덮지 못한 부분이 있는 동안 계속 진행
    while (begin < end) {
        // begin 이전에 시작하는 구간 중 가장 늦게 끝나는 구간을 찾는다.
        double maxCover = -1;
        while (idx < n && ranges[idx].first <= begin) {
            maxCover = max(maxCover, ranges[idx].second);
            idx++;
        }
        
        // 덮을 구간을 찾지 못한 경우
        if (maxCover <= begin) return INF;
        
        // 덮힌 부분의 끝에서 다시 시작
        begin = maxCover;
        used++;
    }
    
    return used;
}

// 0을 덮는 구간을 찾고 나머지는 선형으로 해결한다
int solveCircular() {
    int ret = INF;
    
    for (int i = 0; i < n; i++) {
        // 0을 포함하는 감시탑을 하나씩 선택해 보면서 가장 작은 값 찾기
        if (ranges[i].first <= 0 || ranges[i].second >= 2*pi) {
            double begin = fmod(ranges[i].second, 2*pi);
            double end = fmod(ranges[i].first + 2*pi, 2*pi);
            
            ret = min(ret, 1 + solveLinear(begin, end));
        }
    }
    
    return ret;
}

void solve() {
    getInput();
    
    int ret = solveCircular();
    if (ret < INF)
        cout<<ret<<endl;
    else
        cout<<"IMPOSSIBLE"<<endl;
}

int main() {
    int c;
    cin>>c;
    for (int i = 0; i < c; i++)
        solve();
    
    return 0;
}
