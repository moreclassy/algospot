#include <iostream>
#include <string>

using namespace std;

string input;
int idx;

string reverse() {
	if (idx >= input.size()) return "";
	if (input[idx] != 'x') {
		return string(1, input[idx++]);
	}
	idx++;
	string ul = reverse();
	string ur = reverse();
	string dl = reverse();
	string dr = reverse();
	return "x" + dl + dr + ul + ur;
}

int main()
{
	int rep;
	cin>>rep;
	for (int i = 0; i < rep; i++) {
		idx = 0;
		cin >> input;
		cout << reverse() << endl;
	}
	return 0;
}