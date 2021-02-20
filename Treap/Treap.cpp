#include <iostream>
#include <algorithm>
#include <random>

// source https://youtu.be/68mMGJl5F8s

class Treap {
public:
    static std::minstd_rand generator;
    
    struct Node;

    Node* root = nullptr;

    static int GetSize(Node* n) {
        return n ? n->size : 0;
    }

    static void Update(Node* n) {
        if (n) {
            n->size = GetSize(n->left) + 1 + GetSize(n->right);
        }
    }

    // all keys in a are less than in b
    static Node* Merge(Node* a, Node* b) {
        if (!a || !b) {
            return a ? a : b;
        }
        if (a->priority > b->priority) {
            a->right = Merge(a->right, b);
            Update(a);
            return a;
        }
        else {
            b->left = Merge(a, b->left);
            Update(b);
            return b;
        }
    }

    static void Split(Node* n, int key, Node*& a,Node*& b) {
        if (!n) {
            a = b = nullptr;
            return;
        }
        
        if (n->key < key) {
            Split(n->right, key, n->right, b);
            a = n;
        }
        else {
            Split(n->left, key, a, n->left);
            b = n;
        }
        Update(a);
        Update(b);

    }

    struct Node {
        int key, priority;
        int value, size = 1;
        Node* left = nullptr;
        Node* right = nullptr;
        Node(int key,int value) : key(key), priority(generator()), value(value) {}
    };

    bool Contains(int key) {
        Node* less, *equal, *greater;
        Split(root, key, less, greater);
        Split(greater, key + 1, equal, greater);
        bool result = equal;
        root = Merge(Merge(less, equal), greater);
        return result;
    }

    void Insert(int key,int value) {
        Node* less,*greater;
        Split(root, key, less, greater);
        root = Merge(Merge(less, new Node(key,value)), greater);
    }

    void Erase(int key) {
        Node* less, *equal, *greater;
        Split(root, key, less, greater);
        Split(greater, key + 1, equal, greater);
        root = Merge(less, greater);
    }
};

std::minstd_rand Treap::generator;


int main() {
    Treap treap;
    treap.Insert(8,0);
    treap.Insert(7,0);
    treap.Insert(13,0);
    treap.Insert(10,0);
    treap.Insert(14,0);

    Treap::Node* less = nullptr, *greater = nullptr;
    const int separateKey = 10;
    treap.Split(treap.root, separateKey, less, greater);
    
    return 0;
}