#include <iostream>
#include <list>

using namespace std;

struct ListNode {
    int val;
    ListNode *prev, *next;
    ListNode(int val_, ListNode* prev_ = NULL, ListNode* next_ = NULL) : val(val_), prev(prev_), next(next_) { }
    ListNode* erase() {
        this->prev->next = this->next;
        this->next->prev = this->prev;
        auto ret = this->prev;
        this->next = NULL;
        this->prev = NULL;
        return ret;
    }
};

void print(list<int>& li) {
    for (int i : li)
        cout<<i<<" ";
    cout<<endl;
}

void josephus(int n, int k) {
    ListNode* head = new ListNode(1);
    auto nodeEnd = head;
    for (int i = 2; i <= n; i++) {
        nodeEnd->next = new ListNode(i, nodeEnd);
        nodeEnd = nodeEnd->next;
    }
    nodeEnd->next = head;
    head->prev = nodeEnd;
    while (n > 2) {
        head = head->erase();
        n--;
        int iter = k % n;
        for (int i = 0; i < iter; i++)
            head = head->next;
    }
    int a = head->val, b = head->next->val;
    if (a > b)
        cout<<b<<" "<<a<<endl;
    else
        cout<<a<<" "<<b<<endl;
}

void solve() {
    int n, k;
    cin>>n>>k;
    
    josephus(n, k);
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
