#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct Node {
    int key;
    int height;
    Node* left;
    Node* right;

    Node(int val) {
        key = val;
        height = 1;
        left = right = nullptr;
    }
};
int rotation_count=0;
int getHeight(Node* node){
    return node?node->height:0;
}

void updateHeight(Node* node){
    node->height=1+max(getHeight(node->left),getHeight(node->right));
}

int getBalance(Node*node){
    return node?getHeight(node->left)-getHeight(node->right):0;
}

Node* rightRotate(Node*y){
    Node* temp1 = y->left;
    Node* temp2= temp1->right;
    temp1->right = y;
    y->left = temp2;
    updateHeight(y);
    updateHeight(temp1);

    rotation_count++;
    return temp1;
}

Node* leftRotate(Node* x) {
    Node* temp1 = x->right;
    Node* temp2 = temp1->left;
    temp1->left = x;
    x->right = temp2;
    updateHeight(x);
    updateHeight(temp1);

    rotation_count++;
    return temp1;
}

Node* insert(Node*root,int key){
    if(!root)
    return new Node(key);
    if(key<root->key){
        root->left=insert(root->left,key);
    }
    else if(key>root->key){
        root->right=insert(root->right,key);
    }
    else
    return root;
    updateHeight(root);
    int balance=getBalance(root);

    //LL Rotation
    if(balance>1 and key<root->left->key)
    return rightRotate(root);
    //RR Rotation
    if(balance<-1 and key>root->right->key){
        return leftRotate(root);
    }
    //LR Rotation
    if(balance>1 and key>root->left->key){
        root->left=leftRotate(root->left);
        return rightRotate(root);
    }
    //RL Rotation
    if(balance<-1 and key<root->right->key){
        root->right=rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

int main(){
    vector<int> seq = {
        50, 30, 70, 20, 40, 60, 80,10, 5, 15, 25, 27, 26,65, 62, 64, 90, 100, 95     
    };
    Node* root = nullptr;
    for(int x:seq){
        root=insert(root,x);
    }
    cout<<"Root of Final AVL tree:"<<root->key<< "\n";
    cout << "Total rotations: "<< rotation_count ;
         
    return 0;
}