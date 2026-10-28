
#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int key;
    bool red;  // true = Red, false = Black
    Node* left;
    Node* right;
    Node* parent;

    Node(int val) {
        key = val;
        red = true;  // Every new node is initially Red
        left = right = parent = nullptr;
    }
};

int rotation_count = 0;

// Left Rotation
void leftRotate(Node*& root, Node* x) {
    Node* y = x->right;

    x->right = y->left;

    if (y->left != nullptr)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == nullptr)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;

    rotation_count++;
}

// Right Rotation
void rightRotate(Node*& root, Node* y) {
    Node* x = y->left;

    y->left = x->right;

    if (x->right != nullptr)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == nullptr)
        root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;

    rotation_count++;
}

// Fix Red-Black Tree after insertion
void fixInsert(Node*& root, Node* z) {
    while (z != root && z->parent->red) {

        Node* parent = z->parent;
        Node* grandparent = parent->parent;

        // Parent is the left child of grandparent
        if (parent == grandparent->left) {

            Node* uncle = grandparent->right;

            // Case 1: Uncle is Red
            if (uncle != nullptr && uncle->red) {
                parent->red = false;
                uncle->red = false;
                grandparent->red = true;

                z = grandparent;
            }
            else {
                // Case 2: Triangle (Left-Right)
                if (z == parent->right) {
                    z = parent;
                    leftRotate(root, z);

                    parent = z->parent;
                    grandparent = parent->parent;
                }

                // Case 3: Line (Left-Left)
                parent->red = false;
                grandparent->red = true;

                rightRotate(root, grandparent);
            }
        }

        // Parent is the right child of grandparent
        else {
            Node* uncle = grandparent->left;

            // Case 1: Uncle is Red
            if (uncle != nullptr && uncle->red) {
                parent->red = false;
                uncle->red = false;
                grandparent->red = true;

                z = grandparent;
            }
            else {
                // Case 2: Triangle (Right-Left)
                if (z == parent->left) {
                    z = parent;
                    rightRotate(root, z);

                    parent = z->parent;
                    grandparent = parent->parent;
                }

                // Case 3: Line (Right-Right)
                parent->red = false;
                grandparent->red = true;

                leftRotate(root, grandparent);
            }
        }
    }

    // Root must always be Black
    root->red = false;
}

// Insert a new node
Node* insert(Node*& root, int key) {

    Node* parent = nullptr;
    Node* current = root;

    // Normal BST insertion search
    while (current != nullptr) {
        parent = current;

        if (key < current->key)
            current = current->left;
        else if (key > current->key)
            current = current->right;
        else
            return root;  // Ignore duplicate keys
    }

    // Create new Red node
    Node* z = new Node(key);
    z->parent = parent;

    if (parent == nullptr)
        root = z;
    else if (key < parent->key)
        parent->left = z;
    else
        parent->right = z;

    // Restore Red-Black Tree properties
    fixInsert(root, z);

    return root;
}

int main() {
    vector<int> seq = {
        50, 30, 70, 20, 40, 60, 80,
        10, 5, 15, 25, 27, 26, 65,
        62, 64, 90, 100, 95
    };

    Node* root = nullptr;

    for (int x : seq) {
        insert(root, x);
    }

    cout << "Root of Final Red-Black tree: "
         << root->key << "\n";

    cout << "Total rotations: "
         << rotation_count << "\n";

    return 0;
}
