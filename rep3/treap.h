//
//  treap.h
//  algorithm
//
//  Created by byungha kim on 11/02/2019.
//  Copyright © 2019 byungha kim. All rights reserved.
//

#ifndef treap_h
#define treap_h

#include <cstdlib>
#include <utility>

using namespace std;

typedef int KeyType;

struct TreaNode {
    KeyType key;
    int priority, size;
    TreaNode *left, *right;
    
    TreaNode(const KeyType& _key) : key(_key), priority(rand()), size(1), left(NULL), right(NULL) { }
    
    void setLeft(TreaNode* newLeft) {
        left = newLeft;
        calcSize();
    }
    
    void setRight(TreaNode* newRight) {
        right = newRight;
        calcSize();
    }
    
    void calcSize() {
        size = 1;
        if (left) size += left->size;
        if (right) size += right->size;
    }
};

typedef pair<TreaNode*, TreaNode*> TreaNodePair;

TreaNodePair split(TreaNode* root, KeyType key) {
    if (root == NULL) return TreaNodePair(NULL, NULL);
    
    if (root->key < key) {
        TreaNodePair rs = split(root->right, key);
        root->setRight(rs.first);
        return TreaNodePair(root, rs.second);
    }
    
    TreaNodePair ls = split(root->left, key);
    root->setLeft(ls.second);
    return TreaNodePair(ls.first, root);
}

TreaNode* insert(TreaNode* root, TreaNode* TreaNode) {
    if (root == NULL) return TreaNode;
    
    if (root->priority < TreaNode->priority) {
        TreaNodePair splitted = split(root, TreaNode->key);
        TreaNode->setLeft(splitted.first);
        TreaNode->setRight(splitted.second);
        return TreaNode;
    } else if (TreaNode->key < root->key) {
        root->setLeft(insert(root->left, TreaNode));
    } else {
        root->setRight(insert(root->right, TreaNode));
    }
    
    return root;
}

TreaNode* merge(TreaNode* a, TreaNode* b) {
    if (a == NULL) return b;
    if (b == NULL) return a;
    
    if (a->priority < b->priority) {
        b->setLeft(merge(a, b->left));
        return b;
    }
    
    a->setRight(merge(a->right, b));
    return a;
}

TreaNode* erase(TreaNode* root, KeyType key) {
    if (root == NULL) return root;
    
    if (root->key == key) {
        TreaNode* ret = merge(root->left, root->right);
        delete root;
        return ret;
    }
    
    if (key < root->key) {
        root->setLeft(erase(root->left, key));
    } else {
        root->setRight(erase(root->right, key));
    }
    
    return root;
}

TreaNode* kth(TreaNode* root, int k) {
    int leftSize = 0;
    if (root->left != NULL) leftSize = root->left->size;
    if (k <= leftSize) return kth(root->left, k);
    if (k == leftSize + 1) return root;
    return kth(root->right, k - leftSize - 1);
}
#endif /* treap_h */
