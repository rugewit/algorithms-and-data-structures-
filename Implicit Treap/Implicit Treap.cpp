#include <iostream>
#include <algorithm>
#include <random>
#include <map>

// source https://youtu.be/MLIbII4sBs0

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
            SetParent(n->left, n);
            SetParent(n->right, n);
        }
    }

    static void SetParent(Node* n,Node* p) {
        if (n) {
            n->parent = p;
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
    // split n : first k should move to a, rest to b
    static void Split(Node* n, int k, Node*& a, Node*& b) {
        if (!n) {
            a = b = nullptr;
            return;
        }

        if (GetSize(n->left) < k) {
            Split(n->right, k - GetSize(n->left) - 1, n->right, b);
            a = n;
        }
        else {
            Split(n->left, k, a, n->left);
            b = n;
        }
        Update(a);
        Update(b);
        SetParent(a, nullptr);
        SetParent(b, nullptr);
    }

    static int GetIndex(Node* n) {
        int index = GetSize(n->left);
        while (n->parent) {
            if (n->parent->right == n) {
                index += GetSize(n->parent->left) + 1;
            }
            n = n->parent;
        }
        return index;
    }


    struct Node {
        int priority;
        int value, size = 1;
        Node* left = nullptr;
        Node* right = nullptr;
        Node* parent = nullptr;
        Node(int value) : priority(generator()), value(value) {}
    };

    std::map<int, Node*> location;

    int Get(int index) {
        Node* less, * equal, * greater;
        Split(root, index, less, greater);
        Split(greater, 1, equal, greater);
        int result = equal->value;
        root = Merge(Merge(less, equal), greater);
        return result;
    }

    void PushBack(int value) {
        location[value] = new Node(value);
        root = Merge(root, location[value]);
    }
    
    /*
    void PushFront(int value) {
        root = Merge(new Node(value), root);
    }
    

    void Insert(int index,int value) {
        Node* less, *greater;
        Split(root, index, less, greater);
        root = Merge(Merge(less, new Node(value)), greater);
    }
    */

    void Erase(int index) {
        Node* less, * equal, * greater;
        Split(root, index, less, greater);
        Split(greater, 1, equal, greater);
        if (equal) {
            location.erase(equal->value);
        }
        root = Merge(less, greater);
    }

    /*
    void Erase(int left,int right) {
        Node* less, * equal, * greater;
        Split(root, left, less, greater);
        Split(greater, right - left + 1, equal, greater);
        root = Merge(less, greater);
    }
    */

    int GetIndex(int value) {
        if (location.count(value)) {
            return GetIndex(location[value]);
        }
        else {
            return -1; 
        }
    }

    int Size() {
        return GetSize(root);
    }
};

std::minstd_rand Treap::generator;


int main() {
    Treap t;

    t.PushBack(3);
    t.PushBack(14);
    t.PushBack(15);
    t.PushBack(92);
    t.PushBack(6);
    
    std::cout << t.GetIndex(3) << std::endl;
    std::cout << t.GetIndex(6) << std::endl;
    std::cout << t.GetIndex(92) << std::endl;
    std::cout << t.GetIndex(123) << std::endl;

    return EXIT_SUCCESS;
}