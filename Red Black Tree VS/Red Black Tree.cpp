#include <iostream>
#include <cassert>

/*
1. Каждый узел является красным или черным.
2. Корень дерева является черным.
3. Каждый лист дерева (NIL)является черным.
4. Если узел — красный, то оба его дочерних узла — черные.
5. Для каждого узла все пути от него до листьев, являющихся потомкамиданного узла, содержат одно и то же количество черных узлов.
*/
// source https://en.wikipedia.org/wiki/Red%E2%80%93black_tree

enum color_t { BLACK, RED };

struct Node {
    Node* parent;
    Node* left;
    Node* right;
    enum color_t color;
    int key;

    Node(int k) {
        key = k;
        parent = nullptr;
        left = nullptr;
        right = nullptr;
        color = RED;
    }
};

// Helper functions:

Node* GetParent(Node* n) {
    // Note that parent is set to null for the root node.
    return n == nullptr ? nullptr : n->parent;
}

Node* GetGrandParent(Node* n) {
    // Note that it will return nullptr if this is root or child of root
    return GetParent(GetParent(n));
}

Node* GetSibling(Node* n) {
    Node* p = GetParent(n);

    // No parent means no sibling.
    if (p == nullptr) {
        return nullptr;
    }

    if (n == p->left) {
        return p->right;
    }
    else {
        return p->left;
    }
}

Node* GetUncle(Node* n) {
    Node* p = GetParent(n);

    // No parent means no uncle
    return GetSibling(p);
}

void RotateLeft(Node* n) {
    Node* nnew = n->right;
    Node* p = GetParent(n);
    assert(nnew != nullptr);  // Since the leaves of a red-black tree are empty,
                              // they cannot become internal nodes.
    n->right = nnew->left;
    nnew->left = n;
    n->parent = nnew;
    // Handle other child/parent pointers.
    if (n->right != nullptr) {
        n->right->parent = n;
    }

    // Initially n could be the root.
    if (p != nullptr) {
        if (n == p->left) {
            p->left = nnew;
        }
        else if (n == p->right) {
            p->right = nnew;
        }
    }
    nnew->parent = p;
}

void RotateRight(Node* n) {
    Node* nnew = n->left;
    Node* p = GetParent(n);
    assert(nnew != nullptr);  // Since the leaves of a red-black tree are empty,
                              // they cannot become internal nodes.

    n->left = nnew->right;
    nnew->right = n;
    n->parent = nnew;

    // Handle other child/parent pointers.
    if (n->left != nullptr) {
        n->left->parent = n;
    }

    // Initially n could be the root.
    if (p != nullptr) {
        if (n == p->left) {
            p->left = nnew;
        }
        else if (n == p->right) {
            p->right = nnew;
        }
    }
    nnew->parent = p;
}

void InsertRepairTree(Node* n);
void InsertRecurse(Node* root,Node* n);

Node* Insert(Node* root, Node* n) {
    // Insert new Node into the current tree.
    InsertRecurse(root, n);

    // Repair the tree in case any of the red-black properties have been violated.
    InsertRepairTree(n);

    // Find the new root to return.
    root = n;
    while (GetParent(root) != nullptr) {
        root = GetParent(root);
    }
    return root;
}

void InsertRecurse(Node* root, Node* n) {
    // Recursively descend the tree until a leaf is found.
    if (root != nullptr)
    {
        if (n->key < root->key) {
            if (root->left != nullptr) {
                InsertRecurse(root->left, n);
                return;
            }
            else {
                root->left = n;
            }
        }
        else { // n->key >= root->key
            if (root->right != nullptr) {
                InsertRecurse(root->right, n);
                return;
            }
            else {
                root->right = n;
            }
        }
    }

    // Insert new Node n.
    n->parent = root;
    n->left = nullptr;
    n->right = nullptr;
    n->color = RED;
}

void InsertCase1(Node* n);
void InsertCase2(Node* n);
void InsertCase3(Node* n);
void InsertCase4(Node* n);

void InsertRepairTree(Node* n) {
    // N is the root node, i.e., first node of red–black tree
    if (GetParent(n) == nullptr) {
        InsertCase1(n);
    }
    // N's parent (P) is black
    else if (GetParent(n)->color == BLACK) {
        InsertCase2(n);
    }
    // P is red (so it can't be the root of the tree) and N's uncle (U) is red
    else if (GetUncle(n) != nullptr && GetUncle(n)->color == RED) {
        InsertCase3(n);
    }
    // P is red and U is black
    else {
        InsertCase4(n);
    }
}

void InsertCase1(Node* n) {
    n->color = BLACK;
}

void InsertCase2(Node* n) {
    // Do nothing since tree is still valid.
    return;
}

void InsertCase3(Node* n) {
    GetParent(n)->color = BLACK;
    GetUncle(n)->color = BLACK;
    GetGrandParent(n)->color = RED;
    InsertRepairTree(GetGrandParent(n));
}

void InsertCase4Step2(Node* n);

void InsertCase4(Node* n) {
    Node* p = GetParent(n);
    Node* g = GetGrandParent(n);

    if (n == p->right && p == g->left) {
        RotateLeft(p);
        n = n->left;
    }
    else if (n == p->left && p == g->right) {
        RotateRight(p);
        n = n->right;
    }

    InsertCase4Step2(n);
}

void InsertCase4Step2(Node* n) {
    Node* p = GetParent(n);
    Node* g = GetGrandParent(n);

    if (n == p->left) {
        RotateRight(g);
    }
    else {
        RotateLeft(g);
    }
    p->color = BLACK;
    g->color = RED;
}

void ReplaceNode(Node* n, Node* child) {
    child->parent = n->parent;
    if (n == n->parent->left) {
        n->parent->left = child;
    }
    else {
        n->parent->right = child;
    }
}

void DeleteCase1(Node* n);
void DeleteCase2(Node* n);
void DeleteCase3(Node* n);
void DeleteCase4(Node* n);
void DeleteCase5(Node* n);
void DeleteCase6(Node* n);


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

// I'm not sure that can be right.

void Remove(Node*& root, int key);
// *** my implementation of deleting two child

void DeleteTwoChild(Node* n) {
    Node* predecessor = Max(n->left);

    // copy value of the predecessor to the current node
    n->key = predecessor->key;

    // recursively delete the predecessor. Note that the
    // predecessor will have at most one child (left child)
    Remove(n->left, predecessor->key);
}
void Remove(Node*& root, int key)
{
    // base case: the key is not found in the tree
    if (root == nullptr) {
        return;
    }

    // if the given key is less than the root node, recur for the left subtree
    if (key < root->key) {
        Remove(root->left, key);
    }

    // if the given key is more than the root node, recur for the right subtree
    else if (key > root->key) {
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
            root->key = predecessor->key;

            // recursively delete the predecessor. Note that the
            // predecessor will have at most one child (left child)
            Remove(root->left, predecessor->key);
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

// *** end of my implementation of deleting two child

void DeleteOneChild(Node* n) {
    // Precondition: n has at most one non-leaf child.
    Node* child = (n->right == nullptr) ? n->left : n->right;
    assert(child);

    ReplaceNode(n, child);
    if (n->color == BLACK) {
        if (child->color == RED) {
            child->color = BLACK;
        }
        else {
            DeleteCase1(child);
        }
    }
    delete n;
}


void DeleteCase1(Node* n) {
    if (n->parent != nullptr) {
        DeleteCase2(n);
    }
}

void DeleteCase2(Node* n) {
    Node* s = GetSibling(n);

    if (s->color == RED) {
        n->parent->color = RED;
        s->color = BLACK;
        if (n == n->parent->left) {
            RotateLeft(n->parent);
        }
        else {
            RotateRight(n->parent);
        }
    }
    DeleteCase3(n);
}

void DeleteCase3(Node* n) {
    Node* s = GetSibling(n);

    if ((n->parent->color == BLACK) && (s->color == BLACK) &&
        (s->left->color == BLACK) && (s->right->color == BLACK)) {
        s->color = RED;
        DeleteCase1(n->parent);
    }
    else {
        DeleteCase4(n);
    }
}

void DeleteCase4(Node* n) {
    Node* s = GetSibling(n);

    if ((n->parent->color == RED) && (s->color == BLACK) &&
        (s->left->color == BLACK) && (s->right->color == BLACK)) {
        s->color = RED;
        n->parent->color = BLACK;
    }
    else {
        DeleteCase5(n);
    }
}

void DeleteCase5(Node* n) {
    Node* s = GetSibling(n);

    // This if statement is trivial, due to case 2 (even though case 2 changed
    // the sibling to a sibling's child, the sibling's child can't be red, since
    // no red parent can have a red child).
    if (s->color == BLACK) {
        // The following statements just force the red to be on the left of the
        // left of the parent, or right of the right, so case six will rotate
        // correctly.
        if ((n == n->parent->left) && (s->right->color == BLACK) &&
            (s->left->color == RED)) {
            // This last test is trivial too due to cases 2-4.
            s->color = RED;
            s->left->color = BLACK;
            RotateRight(s);
        }
        else if ((n == n->parent->right) && (s->left->color == BLACK) &&
            (s->right->color == RED)) {
            // This last test is trivial too due to cases 2-4.
            s->color = RED;
            s->right->color = BLACK;
            RotateLeft(s);
        }
    }
    DeleteCase6(n);
}

void DeleteCase6(Node* n) {
    Node* s = GetSibling(n);

    s->color = n->parent->color;
    n->parent->color = BLACK;

    if (n == n->parent->left) {
        s->right->color = BLACK;
        RotateLeft(n->parent);
    }
    else {
        s->left->color = BLACK;
        RotateRight(n->parent);
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
    if (node->color == RED) {
        postfix += " r";
    }
    else if (node->color == BLACK) {
        postfix += " b";
    }
    else {
        throw new std::logic_error("unknow color in Print");
    }
    std::cout << prefix << node->key << postfix << std::endl;
    Print(node->left, height + 1);
    Print(node->right, height + 1);
}

int main() {
    Node* root = new Node(8);
    root->color = BLACK;

    root = Insert(root, new Node(3));
    root = Insert(root, new Node(1));
    root = Insert(root, new Node(6));
    root = Insert(root, new Node(4));
    root = Insert(root, new Node(7));
    root = Insert(root, new Node(10));
    root = Insert(root, new Node(14));
    root = Insert(root, new Node(13));
   
    Print(root, 0);
    std::cout << root->key << std::endl;
    DeleteTwoChild(root);
    Print(root, 0);
}
