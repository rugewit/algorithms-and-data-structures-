#include <iostream>

//src https://www.geeksforgeeks.org/introduction-of-b-tree-2/

class BTreeNode {
    int* keys;
    int t;
    // An array of child pointers
    BTreeNode** C;
    int n;
    bool leaf;
    
public:
    BTreeNode(int _t, bool _leaf);
    void traverse();
    BTreeNode* search(int k);
    friend class BTree;
};

class BTree {
    BTreeNode* root;
    int t;
public:
    BTree(int _t) {
        root = nullptr;
        t = _t;
    }

    void traverse() {
        if (root) {
            root->traverse();
        }
    }

    BTreeNode* search(int k) {
        return (!root) ? nullptr : root->search(k);
    }
};

BTreeNode::BTreeNode(int _t, bool _leaf) {
    t = _t;
    leaf = _leaf;
    keys = new int[2 * t - 1];
    C = new BTreeNode * [2 * t];
    n = 0;
}

void BTreeNode::traverse() {
    int i;
    for (i = 0; i < n; i++) {
        if (!leaf) {
            C[i]->traverse();
        }
        std::cout << " " << keys[i];
    }
    if (!leaf) {
        C[i]->traverse();
    }
}

BTreeNode* BTreeNode::search(int k) {
    int i = 0;
    while(i < n && k > keys[i]){
        i++;
    }

    if (keys[i] == k) {
        return this;
    }

    if (leaf) {
        return nullptr;
    }

    return C[i]->search(k);
}


int main() {
    
}


