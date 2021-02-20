#include <iostream>
#include <algorithm>
#include <random>

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

    }

    struct Node {
        int priority;
        int value, size = 1;
        Node* left = nullptr;
        Node* right = nullptr;
        Node(int value) : priority(generator()), value(value) {}
    };

    int Get(int index) {
        Node* less, * equal, * greater;
        Split(root, index, less, greater);
        Split(greater, 1, equal, greater);
        int result = equal->value;
        root = Merge(Merge(less, equal), greater);
        return result;
    }

    void PushBack(int value) {
        root = Merge(root, new Node(value));
    }

    void PushFront(int value) {
        root = Merge(new Node(value), root);
    }

    void Insert(int index,int value) {
        Node* less, *greater;
        Split(root, index, less, greater);
        root = Merge(Merge(less, new Node(value)), greater);
    }

    void Erase(int index) {
        Node* less, * equal, * greater;
        Split(root, index, less, greater);
        Split(greater, 1, equal, greater);
        root = Merge(less, greater);
    }

    void Erase(int left,int right) {
        Node* less, * equal, * greater;
        Split(root, left, less, greater);
        Split(greater, right - left + 1, equal, greater);
        root = Merge(less, greater);
    }

    int Size() {
        return GetSize(root);
    }
};

std::minstd_rand Treap::generator;


int main() {
    Treap t;

    t.PushBack(333);
    t.PushBack(111);
    t.PushBack(888);
    t.PushBack(777);
    t.PushBack(555);
    for (int i = 0; i < t.Size(); i++) {
        std::cout << t.Get(i) << " ";
    }
    std::cout << std::endl;

    t.PushFront(222);

    for (int i = 0; i < t.Size(); i++) {
        std::cout << t.Get(i) << " ";
    }
    std::cout << std::endl;

    t.Insert(3, 0);

    for (int i = 0; i < t.Size(); i++) {
        std::cout << t.Get(i) << " ";
    }
    std::cout << std::endl;
    return EXIT_SUCCESS;
}