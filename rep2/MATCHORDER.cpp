#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int numOfPlayer;
vector<int> russian(100);
vector<int> korean(100);

void getInput() {
    cin>>numOfPlayer;
    
    for (int i = 0; i < numOfPlayer; i++)
        cin>>russian[i];
    
    for (int i = 0; i < numOfPlayer; i++)
        cin>>korean[i];
}

void solve() {
    getInput();
    sort(russian.begin(), russian.begin() + numOfPlayer);
    sort(korean.begin(), korean.begin() + numOfPlayer);
    
    int winCnt = 0;
    int l = 0, r = numOfPlayer - 1;
    
    for (int i = numOfPlayer - 1; i >= 0; i--) {
        if (russian[i] > korean[r]) {
            l++;
        } else {
            r--;
            winCnt++;
        }
    }
    
    cout<<winCnt<<endl;
}

int main() {
    int c;
    cin>>c;
    
    for (int i = 0; i < c; i++)
        solve();
    
    return 0;
}
