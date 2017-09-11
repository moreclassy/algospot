#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> fs;

int maxSquare(int s, int e) {
	if (s == e) return fs[s];
	int mid = s + (e - s) / 2;
	int ret = max(maxSquare(s, mid), maxSquare(mid + 1, e));
	int l = mid;
	int r = mid + 1;
	int h = 987654321;
	while (l >= s && r <= e) {
		h = min(h, min(fs[l], fs[r]));
		ret = max(ret, (r - l + 1)*h);
		if (r >= e || (l > s && fs[l-1] > fs[r+1])) {
			l--;
		} else {
			r++;
		}
	}
	return ret;
}

int main()
{
	int rep;
	cin>>rep;
	for (int i = 0; i < rep; i++) {
		int len;
		cin>>len;
		fs = vector<int>(len);
		for (int j = 0; j < len; j++) {
			cin>>fs[j];
		}
		cout<<maxSquare(0, len - 1)<<endl;
	}

	return 0;
}