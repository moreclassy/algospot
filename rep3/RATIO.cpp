#include <iostream>

using namespace std;

const long long LIMIT = 2000000000;

bool isEnough(long long games, long long wins, long long goal) {
    return wins * 100 / games >= goal;
}

//long long neededGames(long long games, long long wins, long long goal) {
//    if (!isEnough(games + LIMIT, wins + LIMIT, goal)) return -1;
//
//    long long lo = 0, hi = LIMIT;
//
//    while (lo+1 < hi) {
//        long long mid = lo + (hi - lo)/2;
//        if (isEnough(games + mid, wins + mid, goal)) {
//            hi = mid;
//        } else {
//            lo = mid;
//        }
//    }
//
//    return hi;
//}

long long neededGames(long long games, long long wins, long long goal) {
    if (!isEnough(games + LIMIT, wins + LIMIT, goal)) return -1;
    
    long long ret = (goal*games - 100*wins + (100 - goal) - 1) / (100 - goal);
    
    return ret;
}

void solve() {
    long long n, m;
    cin>>n>>m;
    long long goal = m * 100ll / n + 1ll;
    
    cout<<neededGames(n, m, goal)<<endl;
}

int main() {
    int t; cin>>t;
    for (int i = 0; i < t; i++) {
        solve();
    }
    
    return 0;
}
