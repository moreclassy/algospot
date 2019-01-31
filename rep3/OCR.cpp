#include <iostream>
#include <unordered_map>
#include <cstring>
#include <vector>
#include <cmath>

using namespace std;

const int MAX_WORDS = 500;

int m, q;   // m: 총 가능한 단어 수 1~500, q: 처리할 문장 수 1~20
unordered_map<string, int> wordIdx; // wordIdx[word]: 단어 word의 word[] 에서의 index
string word[MAX_WORDS];    // 총 가능한 단어
double firstPoss[MAX_WORDS];   // firstPoss[i]: i 단어가 처음 나올 확률
double nextPoss[MAX_WORDS][MAX_WORDS];    // nextPoss[a][b]: a 단어 다음 b 단어가 나올 확률
double readPoss[MAX_WORDS][MAX_WORDS];    // readPoss[a][b]: a 단어를 b 단어로 읽을 확률

const int MAX_LEN = 100;

const double NEGINF = -1e200;

int n;  // 분석할 문장의 단어 수 1~100
int read[MAX_LEN];  // read[i]: 분석할 문장의 i번째 단어 인덱스
double cache[MAX_LEN][MAX_WORDS];  // cache[len][lw]: 길이가 len+1 이면서 lw 단어로 끝나는 문장의 확률
int choose[MAX_LEN][MAX_WORDS]; // choose[len][lw]: maxPoss[len][lw]에서 선택한 이전 단어

// 길이가 len+1 이면서 lw 단어로 끝나는 문장의 확률
double maxPoss(int len, int lw) {
    if (len < 0) return NEGINF;
    if (len == 0) return firstPoss[lw] + readPoss[lw][read[len]];
    
    double& ret = cache[len][lw];
    if (ret < 0.5) return ret;
    
    ret = NEGINF;
    
    for (int prev = 0; prev < m; prev++) {
        double ifChoose = maxPoss(len-1, prev) + nextPoss[prev][lw];
        if (ret < ifChoose) {
            ret = ifChoose; choose[len][lw] = prev;
        }
    }
    ret += readPoss[lw][read[len]];
    
    return ret;
}

void recontruct(int len, int lw) {
    if (len < 0) return;
    if (len == 0) {
        cout<<word[lw]<<" ";
        return;
    }
    
    recontruct(len-1, choose[len][lw]);
    cout<<word[lw]<<" ";
    
//    for (int prev = 0; prev < m; prev++) {
//        if (abs(maxPoss(len, lw) - (maxPoss(len-1, prev) + nextPoss[prev][lw] + readPoss[lw][read[len]])) < 0.000001) {
//            recontruct(len-1, prev);
//            cout<<word[lw]<<" ";
//            return;
//        }
//    }
}

int main() {
    cin>>m>>q;
    for (int i = 0; i < m; i++) {
        cin>>word[i]; wordIdx[word[i]] = i;
    }
    
    for (int i = 0; i < m; i++) {
        double input; cin>>input;
        firstPoss[i] = log(input);
    }
    
    for (int r = 0; r < m; r++) {
        for (int c = 0; c < m; c++) {
            double input; cin>>input;
            nextPoss[r][c] = log(input);
        }
    }
    
    for (int r = 0; r < m; r++) {
        for (int c = 0; c < m; c++) {
            double input; cin>>input;
            readPoss[r][c] = log(input);
        }
    }
    
    for (int i = 0; i < q; i++) {
        cin>>n;
        for (int len = 0; len < n; len++) {
            for (int wi = 0; wi < m; wi++) {
                cache[len][wi] = 1.0;
            }
        }
        
        for (int j = 0; j < n; j++) {
            string inStr; cin>>inStr;
            read[j] = wordIdx[inStr];
        }
        
        double possiblity = NEGINF;
        int lw = 0;
        for (int wi = 0; wi < m; wi++) {
            if (possiblity < maxPoss(n-1, wi)) {
                lw = wi;
            }
        }
        
        recontruct(n-1, lw);
        cout<<endl;
    }
    
    return 0;
}
