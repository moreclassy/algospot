#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

int price[20];
int favor[20];
int kindOfSushi;
int budget;

void getInput() {
	cin>>kindOfSushi;
	cin>>budget;
	budget /= 100;
	
	for (int i = 0; i < kindOfSushi; i++) {
		cin>>price[i]>>favor[i];
		price[i] /= 100;
	}
}

void solve() {
	getInput();
	
	int dp[201];
	memset(dp, -1, sizeof(dp));
	dp[0] = 0;
	
	for (int b = 1; b <= budget; b++) {
		for (int sushi = 0; sushi < kindOfSushi; sushi++) {
			if (b - price[sushi] < 0) continue;
			dp[b%201] = max(dp[b%201], dp[(b - price[sushi])%201] + favor[sushi]);
		}
	}
	
	int maxFavor = 0;
	for (int i = 0; i <= min(budget, 200); i++)
		maxFavor = max(maxFavor, dp[i]);
	
	cout<<maxFavor<<endl;
}

int main() {
	int c;
	cin>>c;
	for (int i = 0; i < c; i++)
		solve();
	
	return 0;
}