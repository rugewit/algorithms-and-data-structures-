#include <iostream>
#include <bitset>

// DST are like BST



int getDigit(int key,int digit) {
    const size_t bitLength = 5;
    return std::bitset<bitLength>(key)[bitLength - 1 - digit];
}

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

Node* Find(Node* node, int data, int curDigit) {
    if (!node) {
        return nullptr;
    }
    
    if (data == node->data || !node) {
        return node;
    }
    else if (getDigit(data, curDigit) == 0) {
        return Find(node->left, data, curDigit + 1);
    }
    else {
        return Find(node->right, data, curDigit + 1);
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

void Print(Node* node, int height) {
    if (node == nullptr) {
        return;
    }
    std::string prefix;
    for (int i = 0; i < height; i++) {
        prefix += ' ';
    }
    std::string postfix;
    if (node->parent && node->parent->left == node) {
        postfix += " (l)";
    }
    else if (node->parent && node->parent->right == node) {
        postfix += " (r)";
    }
    std::cout << prefix << (char) node->data << postfix << std::endl;
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
Node* Insert(Node* node, int data, int curDigit) {
    if (!node) {
        return new Node(data);
    }
    if (getDigit(data,curDigit) == 0) {
        node->left = Insert(node->left, data, curDigit + 1);
    }
    else {
        node->right = Insert(node->right, data, curDigit + 1);
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

void Remove(Node*& root, int key, int curDigit)
{
    // base case: the key is not found in the tree
    if (root == nullptr) {
        return;
    }

    // key found
    if (key == root->data)
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
            Remove(root->left, predecessor->data, curDigit);
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

    // if the given key is less than the root node, recur for the left subtree
    else if (getDigit(key, curDigit) == 0) {
        Remove(root->left, key, curDigit + 1);
    }

    // if the given key is more than the root node, recur for the right subtree
    else {
        Remove(root->right, key, curDigit + 1);
    }
}


int main() {
    Node* a = new Node('A');
    /*
    
    Node* b = new Node(3);
    Node* c = new Node(1);
    Node* d = new Node(6);
    Node* e = new Node(4);
    Node* f = new Node(7);
    Node* g = new Node(10);
    Node* h = new Node(14);
    Node* i = new Node(13);
    */
    const int digitBegin = 0;
    const int heightBegin = 0;

    Insert(a, 'E', digitBegin);
    Insert(a, 'S', digitBegin);
    Insert(a, 'C',digitBegin);
    Insert(a, 'H', digitBegin);
    Insert(a, 'R', digitBegin);
    Insert(a, 'X', digitBegin);
    Insert(a, 'N', digitBegin);
    Insert(a, 'G', digitBegin);
    GetParents(a);
    Print(a, heightBegin);
    Remove(a, 6, digitBegin);
    Print(a, heightBegin);
	return EXIT_SUCCESS;
}

