#include <iostream>
#include <string>
#include <vector>

// src https://habr.com/ru/post/150732/


namespace AvlTree {
    struct Node {
        int key;
        unsigned char height;
        Node* left;
        Node* right;
        Node(int k) {
            key = k;
            left = right = nullptr;
            height = 1;
        }
    };

    unsigned char height(Node* p) {
        return p ? p->height:0;
    }

    int bFactor(Node* p) {
        return height(p->right) - height(p->left);
    }

    void fixHeight(Node* p) {
        unsigned char hl = height(p->left);
        unsigned char hr = height(p->right);
        p->height = (hl > hr ? hl : hr) + 1;
    }

    Node* rotateRight(Node* p) {
        Node* q = p->left;
        p->left = q->right;
        q->right = p;
        fixHeight(p);
        fixHeight(q);
        return q;
    }

    Node* rotateLeft(Node* q) {
        Node* p = q->right;
        q->right = p->left;
        p->left = q;
        fixHeight(q);
        fixHeight(p);
        return p;
    }

    Node* balance(Node* p) {
        fixHeight(p);
        if(bFactor(p) == 2) {
            if( bFactor(p->right) < 0 )
                p->right = rotateRight(p->right);
            return rotateLeft(p);
        }
        if(bFactor(p) == -2) {
            if( bFactor(p->left) > 0  )
                p->left = rotateLeft(p->left);
            return rotateRight(p);
        }
        return p;
    }

    Node* insert(Node* p, int k) {
        if(!p) return new Node(k);
        if(k < p->key)
            p->left = insert(p->left,k);
        else {
            p->right = insert(p->right,k);
        }
        return balance(p);
    }

    Node* findMin(Node* p) {
        return p->left ? findMin(p->left) : p;
    }

    Node* removeMin(Node* p) {
        if(p->left == nullptr) {
            return p->right;
        }
        p->left = removeMin(p->left);
        return balance(p);
    }


    Node* remove(Node* p, int k) {
        if (!p) return nullptr;
        if (k < p->key) {
            p->left = remove(p->left, k);
        } else if (k > p->key) {
            p->right = remove(p->right, k);
        } else {
            Node *q = p->left;
            Node *r = p->right;
            delete p;
            if (!r) return q;
            Node *min = findMin(r);
            min->right = removeMin(r);
            min->left = q;
            return balance(min);
        }
        return balance(p);
    }

    enum direction {
        left,
        right,
        node
    };

    void print(Node* p, int height, direction dir) {
        if (!p) {
            return;
        }
        std::string indent;
        for(int i = 0;i < height; i++) {
            indent += '_';
        }
        std::string postfix = " ";
        if (dir == left) {
            postfix += 'l';
        }
        else if (dir == right) {
            postfix += 'r';
        }
        std::cout << indent << p->key << postfix << std::endl;
        print(p->left,height + 1,left);
        print(p->right,height + 1,right);
    }
}


int main() {
    auto* a = new AvlTree::Node(7);

    int num;
    std::vector<int> numbers;
    while(std::cin >> num) {
        numbers.push_back(num);
    }

    for(auto el : numbers) {
        std::cout << "is inserting " + std::to_string(el) << std::endl;
        a = AvlTree::insert(a,el);
        AvlTree::print(a, 0, AvlTree::direction::node);
        std::cout << "***************************************" << std::endl;
    }

    return 0;
}
