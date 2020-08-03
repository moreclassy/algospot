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

struct TreapNode {
    KeyType key;
    int priority, size;
    TreapNode *left, *right;
    
    TreapNode(const KeyType& _key) : key(_key), priority(rand()), size(1), left(NULL), right(NULL) { }
    
    void setLeft(TreapNode* newLeft) {
        left = newLeft;
        calcSize();
    }
    
    void setRight(TreapNode* newRight) {
        right = newRight;
        calcSize();
    }
    
    void calcSize() {
        size = 1;
        if (left) size += left->size;
        if (right) size += right->size;
    }
};

typedef pair<TreapNode*, TreapNode*> TreapNodePair;

TreapNodePair split(TreapNode* root, KeyType key) {
    if (root == NULL) return TreapNodePair(NULL, NULL);
    
    if (root->key < key) {
        TreapNodePair rs = split(root->right, key);
        root->setRight(rs.first);
        return TreapNodePair(root, rs.second);
    }
    
    TreapNodePair ls = split(root->left, key);
    root->setLeft(ls.second);
    return TreapNodePair(ls.first, root);
}

TreapNode* insert(TreapNode* root, TreapNode* TreapNode) {
    if (root == NULL) return TreapNode;
    
    if (root->priority < TreapNode->priority) {
        TreapNodePair splitted = split(root, TreapNode->key);
        TreapNode->setLeft(splitted.first);
        TreapNode->setRight(splitted.second);
        return TreapNode;
    } else if (TreapNode->key < root->key) {
        root->setLeft(insert(root->left, TreapNode));
    } else {
        root->setRight(insert(root->right, TreapNode));
    }
    
    return root;
}

TreapNode* merge(TreapNode* a, TreapNode* b) {
    if (a == NULL) return b;
    if (b == NULL) return a;
    
    if (a->priority < b->priority) {
        b->setLeft(merge(a, b->left));
        return b;
    }
    
    a->setRight(merge(a->right, b));
    return a;
}

TreapNode* erase(TreapNode* root, KeyType key) {
    if (root == NULL) return root;
    
    if (root->key == key) {
        TreapNode* ret = merge(root->left, root->right);
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

TreapNode* kth(TreapNode* root, int k) {
    int leftSize = 0;
    if (root->left != NULL) leftSize = root->left->size;
    if (k <= leftSize) return kth(root->left, k);
    if (k == leftSize + 1) return root;
    return kth(root->right, k - leftSize - 1);
}
#endif /* treap_h */
