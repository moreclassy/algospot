#include <iostream>
#include <bitset>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 12;
const int MAXM = 10;
const int INF = 987654321;

int n, k, m, l; // 전공 과목 수, 들어야 할 과목 수, 학기 수, 학기당 최대로 들을 수 있는 과목 수
int prerequisite[MAXN]; // 선수과목
int classes[MAXM];  // 학기 당 개설 과목
int cache[MAXM][1<<MAXN];   // dp table [학기][들은과목]

int bitCount(int num) {
    return (int)bitset<MAXN>(num).count();
}

void getInput() {
    cin>>n>>k>>m>>l;
    
    for (int i = 0; i < n; i++) {
        int r;  // 선수 과목 수
        cin>>r;
        int pre = 0;
        for (int j = 0; j < r; j++) {
            int tmp;
            cin>>tmp;
            pre |= (1<<tmp);
        }
        prerequisite[i] = pre;
    }
    
    for (int i = 0; i < m; i++) {
        int c;
        cin>>c;
        int cl = 0;
        for (int j = 0; j < c; j++) {
            int tmp;
            cin>>tmp;
            cl |= (1<<tmp);
        }
        classes[i] = cl;
    }
    
    memset(cache, -1, sizeof(cache));
}

int graduate(int semester, int taken) {
    if (bitCount(taken) >= k) return 0;
    if (semester == m) return INF;
    
    int &ret = cache[semester][taken];
    if (ret != -1) return ret;
    ret = INF;
    
    int canTake = (classes[semester] & ~taken);
    
    for (int i = 0; i < n; i++)
        if ((canTake & (1<<i)) && ((taken & prerequisite[i]) != prerequisite[i]))
            canTake &= ~(1<<i);
    
    for (int take = canTake; take > 0; take = ((take - 1) & canTake)) {
        if (bitCount(take) > l) continue;
        ret = min(ret, graduate(semester + 1, taken | take) + 1);
    }
    
    ret = min(ret, graduate(semester + 1, taken));
    
    return ret;
}

void solve() {
    getInput();
    
    int ret = graduate(0, 0);
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
