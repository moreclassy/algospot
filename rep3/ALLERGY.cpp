#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

const int INF = 987654321;
int n, m;
vector<long long> menuEater;
int minVal = INF;
long long allNameSet = 0;

bool canEverybodyEat(const long long nameSet) {
    return nameSet == allNameSet;
}

void selectMenu(int foodCnt, int food, long long nameSet) {
    if (foodCnt >= minVal) return;
    
    if (food == m) {
        if (canEverybodyEat(nameSet))
            minVal = foodCnt;
        return;
    }
    
    if (canEverybodyEat(nameSet)) {
        minVal = foodCnt;
        return;
    }
    
    selectMenu(foodCnt + 1, food + 1, nameSet | menuEater[food]);
    selectMenu(foodCnt, food + 1, nameSet);
}

void solve() {
    cin>>n>>m;
    
    minVal = INF;
    allNameSet = ((1ll << n) - 1);
    
    string name;
    unordered_map<string, int> name2i;
    for (int i = 0; i < n; i++) {
        cin>>name;
        name2i[name] = i;
    }
    
    menuEater = vector<long long>(m, 0);
    for (int i = 0; i < m; i++) {
        int eaterCnt; cin>>eaterCnt;
        for (int j = 0; j < eaterCnt; j++) {
            cin>>name;
            menuEater[i] |= (1ll<<name2i[name]);
        }
    }
    
    selectMenu(0, 0, 0);
    cout<<minVal<<endl;
}

int main() {
    int t; cin>>t;
    for (int i = 0; i < t; i++) {
        solve();
    }
    
    return 0;
}
