#include <iostream>
#include<vector>
#include <algorithm>
using namespace std;
int rotationCount = 0;
struct Node {
    int key;
    Node *left, *right;
    int height;
    Node(int k) {
        key = k;
        left = right = nullptr;
        height = 1;
    }
};
int getHeight(Node* node) {
    return (node == nullptr) ? 0 : node->height;
}
void updateHeight(Node* node) {
    if (node)
        node->height = 1 + max(getHeight(node->left),
                               getHeight(node->right));
}
int getBalance(Node* node) {
    return (node == nullptr) ? 0 :
           getHeight(node->left) - getHeight(node->right);
}
Node* rightRotate(Node* y) {
    rotationCount++;
    Node* temp1 = y->left;
    Node* temp2 = temp1->right;
    temp1->right = y;
    y->left = temp2;
    updateHeight(y);
    updateHeight(temp1);
    return temp1;
}
Node* leftRotate(Node* x) {
    rotationCount++;
    Node* temp1 = x->right;
    Node* temp2 = temp1->left;
    temp1->left = x;
    x->right = temp2;
    updateHeight(x);
    updateHeight(temp1);

    return temp1;
}
Node* insert(Node* root, int key) {
    if (root == nullptr)
        return new Node(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else
        return root;
    updateHeight(root);
    int balance = getBalance(root);
    // LL
    if (balance > 1 && key < root->left->key)
        return rightRotate(root);
    // RR
    if (balance < -1 && key > root->right->key)
        return leftRotate(root);
    // LR
    if (balance > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    // RL
    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}
Node* minValueNode(Node* node) {
    Node* curr = node;
    while (curr->left)
        curr = curr->left;
    return curr;
}
Node* deleteNode(Node* root, int key) {
    if (root == nullptr)
        return root;
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // 0 or 1 child
        if (root->left == nullptr || root->right == nullptr) {

            Node* temp =
                root->left ? root->left : root->right;

            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            }
            else {
                *root = *temp;
            }

            delete temp;
        }
        // 2 children
        else {
            Node* temp =
                minValueNode(root->right);
            root->key = temp->key;
            root->right =
                deleteNode(root->right, temp->key);
        }
    }
    if (root == nullptr)
        return root;
    updateHeight(root);
    int balance = getBalance(root);
    // LL
    if (balance > 1 &&
        getBalance(root->left) >= 0)
        return rightRotate(root);
    // LR
    if (balance > 1 &&
        getBalance(root->left) < 0) {
        root->left =
            leftRotate(root->left);
        return rightRotate(root);
    }
    // RR
    if (balance < -1 &&
        getBalance(root->right) <= 0)
        return leftRotate(root);
    // RL
    if (balance < -1 &&
        getBalance(root->right) > 0) {
        root->right =
            rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

int main() {
    int insertKeys[] = {
        50,30,70,20,40,60,80,10,5,15,25,27,26,65,62,64,90,100,95
    };       
    int deleteKeys[] = {
        70,20,50,10,90
    };
    Node* root = nullptr;
    for (int key : insertKeys)
        root = insert(root, key);
    cout << "Root after insertions: "
         << root->key << endl;
    cout << "Rotations during insertions: "
         << rotationCount << endl;
    int insertionRotations = rotationCount;
    for (int key : deleteKeys)
        root = deleteNode(root, key);
    cout << "Root after deletions: "
         << root->key << endl;
    cout << "Rotations during deletions: "
         << rotationCount - insertionRotations
         << endl;
    cout << "Total rotations: "
         << rotationCount << endl;

    return 0;
}