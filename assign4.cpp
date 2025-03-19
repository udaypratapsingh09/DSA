#include<iostream>
#include<iomanip>
#include<ios>
#include<queue>
#include<stack>
#include<algorithm>

using namespace std;

class Node{
public:
    int data;
    Node *left,*right;
    bool leftChild,rightChild;
    Node(){
        this->left = nullptr;
        this->right = nullptr;
        this->leftChild = false;
        this->rightChild = false;
        this->data = 0;
    }
    Node (int data){
        this->left = nullptr;
        this->right = nullptr;
        this->leftChild = false;
        this->rightChild = false;
        this->data = data;
    }
};

class BSTNode {
public:
    int data;
    BSTNode *left,*right;
    BSTNode(){
        this->left = nullptr;
        this->right = nullptr;
        this->data = 0;
    }
    BSTNode (int data){
        this->left = nullptr;
        this->right = nullptr;
        this->data = data;
    }
};

class ThreadedBST{
private:
    Node *root;
    Node *dummy;

public:
    ThreadedBST(){
        root = nullptr;
        dummy = new Node(-1);
        dummy->left = root;
        dummy->leftChild = true;
        dummy->right = dummy;
        dummy->rightChild = false;
    }

    void insertNode(int val){
        cout<<"Inserting "<<val<<endl;
        Node *newNode = new Node(val);
        if (root == nullptr){
            root = newNode;
            root->left = dummy;
            root->right = dummy;
            return;
        }
        Node *parent = root;
        while (parent != nullptr){
            if (val <= parent->data) {
                if (parent->leftChild==true) parent = parent->left;
                else break;
            }
            else {
                if (parent->rightChild==true) parent = parent->right;
                else break;
            }
        }
        if (val<=parent->data){
            newNode->right = parent;
            newNode->left = parent->left;
            parent->left = newNode;
            parent->leftChild = true;
        }
        else {
            newNode->left = parent;
            newNode->right = parent->right;
            parent->right = newNode;
            parent->rightChild = true;
        }
    }

    void inorder(){
        Node *t = root;
        cout<<(t==nullptr)<<endl;
        while (t != dummy){
            // go to the leftmost node from t
            while (t->leftChild == true){
                t = t->left;
            }
            // print the leftmost node;
            cout<<t->data<<" ";
            // follow the rightthread till a node with right child is found
            while (t->rightChild == false){
                if (t->right == dummy) break;
                t = t->right;
                cout<<t->data<<" ";
            }
            t = t->right;
        }
        cout<<endl;
    }

    void preorder(){
        Node *t = root;
        while(t != dummy){
            cout<<t->data<<" ";
            while (t->leftChild == true){
                t = t->left;
                cout<<t->data<<" ";
            }
            while (t->rightChild == false){
                if (t->right != dummy) t = t->right;
                else break;
            }
            t = t->right;
        }
    }
};

class BST{
private:
    BSTNode *root;
public:
    BST(){
        root = nullptr;
    }

    void insertBST(int val){
        BSTNode *newNode = new BSTNode(val);

        if (root==nullptr){
            root = newNode;
            return;
        }
        
        BSTNode *parent;
        BSTNode *t = root;
        while (t != nullptr){
            parent = t;
            if (val <= t->data) {
                t = t->left;
            }
            else {
                t = t->right;
            }
        }

        if (val <= parent->data) {
            parent->left = newNode;
        }
        else {
            parent->right = newNode;
        }
    }

    ThreadedBST toThreadedBST(){
        ThreadedBST thb;
        if (root==nullptr) return thb;
        stack<BSTNode *>st;
        BSTNode *t=root;
        while (t!=nullptr || !st.empty()){
            while (t!=nullptr){
                st.push(t);
                thb.insertNode(t->data);
                t = t->left;
            }
            t = st.top();
            st.pop();
            t = t->right;
        }
        return thb;
    }
};

int main(){
    ThreadedBST b;
    b.insertNode(6);
    b.insertNode(3);
    b.insertNode(1);
    b.insertNode(5);
    b.insertNode(8);
    b.insertNode(7);
    b.insertNode(10);
    b.insertNode(9);
    b.insertNode(12);

    b.inorder();
    b.preorder();

    BST bst;
    bst.insertBST(10);
    bst.insertBST(20);
    bst.insertBST(15);
    bst.insertBST(25);
    bst.insertBST(30);
    bst.insertBST(5);
    bst.insertBST(3);
    bst.insertBST(17);

    ThreadedBST b2 = bst.toThreadedBST();
    cout<<"Inorder"<<endl;
    b2.inorder();
    cout<<"Preorder"<<endl;
    b2.preorder();
}