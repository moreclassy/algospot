//
//  Header.h
//  algorithm
//
//  Created by byungha kim on 08/02/2019.
//  Copyright © 2019 byungha kim. All rights reserved.
//

#ifndef KMP_h
#define KMP_h

vector<int> getParitalMatch(const string& N) {
    int m = N.size();
    vector<int> pi(m, 0);
    int begin = 1, matched = 0;
    
    while (begin + matched < m) {
        if (N[begin + matched] == N[matched]) {
            matched++;
            pi[begin + matched - 1] = matched;
        } else {
            if (matched == 0) {
                begin++;
            } else {
                begin += matched - pi[matched-1];
                matched = pi[matched-1];
            }
        }
    }
    
    return pi;
}

vector<int> kmpSearch(const string& H, const string& N) {
    int n = H.size(), m = N.size();
    vector<int> ret;
    vector<int> pi = getParitalMatch(N);
    int begin = 0, matched = 0;
    
    while (begin <= n - m) {
        if (matched < m && H[begin + matched] == N[matched]) {
            matched++;
            if (matched == m) ret.push_back(begin);
        } else {
            if (matched == 0) {
                begin++;
            } else {
                begin += matched - pi[matched-1];
                matched = pi[matched-1];
            }
        }
    }
    
    return ret;
}

#endif /* Header_h */
