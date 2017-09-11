#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 100000;
int V, adj[500][500];

int delay[500];
int W[500][500];

void solve()
{
	vector<pair<int, int> > order;
	for (int i = 0; i < V; i++) {
		order.push_back(make_pair(delay[i], i));
	}
	sort(order.begin(), order.end());

	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			if (i == j) {
				W[i][j] = 0;
			} else {
				W[i][j] = adj[i][j];
			}
		}
	}

	for (int k = 0; k < V; k++) {
		int w = order[k].second;
		for (int i = 0; i < V; i++) {
			for (int j = 0; j < V; j++) {
				adj[i][j] = min(adj[i][j], adj[i][w] + adj[w][j]);
				W[i][j] = min(W[i][j], adj[i][w] + delay[w] + adj[w][j]);
			}
		}
	}
}

int main()
{
	int E;
	cin >> V >> E;
	for (int i = 0; i < V; i++) {
		cin >> delay[i];
	}
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			if (i == j)
				adj[i][j] = 0;
			else
				adj[i][j] = INF;
		}
	}
	for (int i = 0; i < E; i++) {
		int u, v, t;
		cin >> u >> v >> t;
		adj[u-1][v-1] = t;
		adj[v-1][u-1] = t;
	}
	solve();
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int u, v;
		cin >> u >> v;
		cout << W[u-1][v-1] << endl;
	}
	return 0;
}