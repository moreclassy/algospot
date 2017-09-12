#include <iostream>
#include <vector>

using namespace std;

double prob(vector<vector<int>> &graph, vector<int> &rank, vector<vector<double>> &dp, int day, int node) {
	double &ret = dp[day][node];
	if (ret > -1.0) return ret;
	ret = 0;
	for (int i = 0; i < graph.size(); i++) {
		if (i == node || graph[node][i] == 0) continue;
		ret += prob(graph, rank, dp, day -1, i) / (double)rank[i];
	}
	return ret;
}

void solve() {
	int n, d, p;	// n:마을수, d:경과일, p:교도소위치
	cin>>n>>d>>p;
	vector<vector<int>> graph(n, vector<int>(n));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin>> graph[i][j];
		}
	}

	vector<int> rank(n, 0);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (graph[i][j]) {
				rank[i]++;
			}
		}
	}
	
	vector<vector<double>> dp(d+1, vector<double>(n, -10));
	for (int i = 0; i < n; i++) {
		dp[0][i] = 0;
	}
	dp[0][p] = 1;

	int t;
	cin>>t;
	for (int i = 0; i < t; i++) {
		int q;
		cin>>q;
		cout<<prob(graph, rank, dp, d, q)<<" ";
	}
	cout<<endl;
}

int main() {
	int c;
	cin>>c;
	cout << fixed;         //소수점 고정
	cout.precision(8);
	for (int i = 0; i < c; i++) {
		solve();
	}

	return 0;
}