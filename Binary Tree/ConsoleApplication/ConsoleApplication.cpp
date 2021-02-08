#include <iostream>
#include <string>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node* parent;

    Node(int data_) {
        data = data_;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
};

Node* Find(Node* node,int data) {
    if (!node) {
        return nullptr;
    }
    if (data < node->data) {
        return Find(node->left, data);
    }
    else if (data == node->data || !node) {
        return node;
    }
    else {
        return Find(node->right, data);
    }
}

Node* Min(Node* node) {
    if (node == nullptr) {
        return nullptr;
    }
    if (node->left == nullptr) {
        return node;
    }
    else {
        return Min(node->left);
    }
}

Node* Max(Node* node) {
    if (node == nullptr) {
        return nullptr;
    }
    if (node->right == nullptr) {
        return node;
    }
    else {
        return Max(node->right);
    }
}

void Print(Node* node,int height) {
    if (node == nullptr) {
        return;
    }
    std::string prefix;
    for (int i = 0; i < height; i++) {
        prefix += ' ';
    }
    std::cout << prefix << node->data << std::endl;
    Print(node->left, height + 1);
    Print(node->right, height + 1);
}


Node* Successor(Node* node) {
    if (node == nullptr) {
        return nullptr;
    }
    if (node->right != nullptr) {
        return Min(node->right);
    }
    Node* y = node->parent;
    while (y != nullptr && node == y->right) {
        node = y;
        y = y->parent;
    }
    return y;
}


// from http://cslibrary.stanford.edu/110/BinaryTrees.html
Node* Insert(Node* node,int data) {
    if (!node) {
        return new Node(data);
    }
    if (data < node->data) {
        node->left = Insert(node->left, data);
    }
    else {
        node->right = Insert(node->right, data);
    }
    return node;
}

void GetParents(Node* node) {
    if (node->left) {
        node->left->parent = node;
        GetParents(node->left);
    }
    if (node->right) {
        node->right->parent = node;
        GetParents(node->right);
    }
}

void Remove(Node*& root, int key)
{
    // base case: the key is not found in the tree
    if (root == nullptr) {
        return;
    }

    // if the given key is less than the root node, recur for the left subtree
    if (key < root->data) {
        Remove(root->left, key);
    }

    // if the given key is more than the root node, recur for the right subtree
    else if (key > root->data) {
        Remove(root->right, key);
    }

    // key found
    else
    {
        // Case 1: node to be deleted has no children (it is a leaf node)
        if (root->left == nullptr && root->right == nullptr)
        {
            // deallocate the memory and update root to null
            delete root;
            root = nullptr;
        }

        // Case 2: node to be deleted has two children
        else if (root->left && root->right)
        {
            // find its inorder predecessor node
            Node* predecessor = Max(root->left);

            // copy value of the predecessor to the current node
            root->data = predecessor->data;

            // recursively delete the predecessor. Note that the
            // predecessor will have at most one child (left child)
            Remove(root->left, predecessor->data);
        }

        // Case 3: node to be deleted has only one child
        else
        {
            // choose a child node
            Node* child = (root->left) ? root->left : root->right;
            Node* curr = root;

            root = child;

            // deallocate the memory
            delete curr;
        }
    }
}


int main()
{
    Node* a = new Node(8);
    Node* b = new Node(3);
    Node* c = new Node(1);
    Node* d = new Node(6);
    Node* e = new Node(4);
    Node* f = new Node(7);
    Node* g = new Node(10);
    Node* h = new Node(14);
    Node* i = new Node(13);

    /*
    a->left = b;
    a->right = g;
    b->parent = a;
    g->parent = a;

    b->left = c;
    b->right = d;
    c->parent = b;
    d->parent = b;

    d->left = e;
    d->right = f;
    e->parent = d;
    f->parent = d;

    g->right = h;
    h->parent = g;

    h->left = i;
    i->parent = h;
    */

    Insert(a, 3);
    Insert(a, 1);
    Insert(a, 6);
    Insert(a, 4);
    Insert(a, 7);
    Insert(a, 10);
    Insert(a, 14);
    Insert(a, 13);
    GetParents(a);
    Print(a, 0);
    Remove(a,6);
    Print(a, 0);
}
