#include <utility>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int numOfPpl;
vector<pair<int,int>> box(10000);

void getInput() {
    cin>>numOfPpl;
    for (int i = 0; i < numOfPpl; i++)
        cin>>box[i].second;
    for (int i = 0; i < numOfPpl; i++)
        cin>>box[i].first;
}

void solve() {
    getInput();
    sort(box.begin(), box.begin() + numOfPpl);
    
    int extraTime = box[0].first;
    int curOvenTime = box[0].second;
    for (int i = 1; i < numOfPpl; i++) {
        if (extraTime + curOvenTime < box[i].first) {
            extraTime = box[i].first - curOvenTime;
        }
        curOvenTime += box[i].second;
    }
    
    cout<<curOvenTime + extraTime<<endl;
}

int main() {
    int t;
    cin>>t;
    
    for (int i = 0; i < t; i++)
        solve();
    
    return 0;
}
