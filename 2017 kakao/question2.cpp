#include<vector>
using namespace std;

bool solution(vector<int> arr)
{
    int num = 0;
    for (int i = 0; i < arr.size(); i++) {
        num ^= i + 1;
        num ^= arr[i];
    }
    return num == 0;
}
