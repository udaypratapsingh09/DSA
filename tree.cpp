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
    Node(){
        this->left = nullptr;
        this->right = nullptr;
        this->data = 0;
    }
    Node (int data){
        this->left = nullptr;
        this->right = nullptr;
        this->data = data;
    }
    void remove(){
        cout<<"Deleting a node: "<<this->data<<endl;
        delete this;
    }
};

class BinaryTree{
private:
    Node *root;

    void clone(Node *cloneNode,Node *node){
        if (node==nullptr) return;
        cloneNode = new Node(node->data);
        cloneNode->left = node->left;
        cloneNode->right = node->right;

        cout<<"Cloned a node: "<<cloneNode->data<<endl;

        clone(cloneNode->left,node->left);
        clone(cloneNode->right,node->right);

        cout<<"Deleting a node: "<<node->data<<endl;
        node->remove();
        return;
    }
    void level_traversal_rec(queue<Node*> curr_level){
        if (curr_level.empty()) {
            return;
        }
        queue<Node *> next_level;
        Node *curr;
        while (!curr_level.empty()){
            curr = curr_level.front();
            if (curr->left != nullptr) next_level.push(curr->left);
            if (curr->right != nullptr) next_level.push(curr->right);
            cout<<curr->data<<" ";
            curr_level.pop();
        }
        level_traversal_rec(next_level);
    }

    void inorder_rec(Node *node){
        if (node==nullptr) return;
        inorder_rec(node->left);
        cout<<node->data<<" ";
        inorder_rec(node->right);
    }

    void preorder_rec(Node *node){
        if (node==nullptr) return;
        cout<<node->data<<" ";
        preorder_rec(node->left);
        preorder_rec(node->right);
    }
    
    void postorder_rec(Node *node){
        if (node==nullptr) return;
        postorder_rec(node->left);
        postorder_rec(node->right);
        cout<<node->data<<" ";
    }

    void print(queue<Node*> curr_level,int gap){
        if (curr_level.empty()) return;
        cout<<setw(gap/2+1);
        queue<Node *> next_level;
        Node *curr;
        Node *dummy = new Node(-1);
        while (!curr_level.empty()){
            curr = curr_level.front();
            if (curr->data != -1){
                if (curr->left != nullptr) next_level.push(curr->left);
                else next_level.push(dummy);
                if (curr->right != nullptr) next_level.push(curr->right);
                else next_level.push(dummy);
                    cout<<curr->data<<setw(gap+1);
            }
            
            else 
                cout<<" "<<setw(gap+1);
            curr_level.pop();
        }
        cout<<endl;
        print(next_level,gap/2);
    }

    int getHeight(Node *node){
        if(node == nullptr) return 0;
        return max(getHeight(node->left)+1,getHeight(node->right)+1);
    }
public:
    BinaryTree(){
        root = nullptr;
    }

    BinaryTree clone(){
        // create clone of binary tree and return it;
        // erase all nodes in original tree.
        BinaryTree cloneTree;
        clone(cloneTree.root,this->root);
        // this->root = nullptr;
        return cloneTree;
    }

    bool empty(){
        if (root != nullptr) return false;
        cout<<"Tree is empty"<<endl;
        return true;
    }

    void insertNode(int val){
        Node *p = new Node(val);

        if (root==nullptr){
            root = p;
            cout<<"Value "<<val<<" was inserted as root\n";
            return;
        }

        Node *t=root;

        while (t!=nullptr){
            char c;
            cout<<"Left or right of "<<t->data<<" (Enter l/r): ";
            cin>>c;
            if (c=='l'){
                if (t->left==nullptr){
                    t->left = p;
                    break;
                }
                else{
                    t = t->left;
                }
            }
            else{
                if (t->right==nullptr){
                    t->right = p;
                    break;
                }
                else{
                    t = t->right;
                }
            }
        }
    }

    void level_traversal_iter(){
        if (empty()) return;
        Node *curr;
        queue<Node *> q;
        q.push(root);
        while (!q.empty()){
            curr = q.front();
            if (curr->left != nullptr) q.push(curr->left);
            if (curr->right != nullptr) q.push(curr->right);
            cout<<curr->data<<" ";
            q.pop();
        }
        cout<<endl;
    }

    void level_traversal_rec(){
        if (empty()) return;
        queue<Node *> curr_level;
        curr_level.push(root);
        level_traversal_rec(curr_level);
        cout<<endl;
    }

    void inorder_iter(){
        // left, root, right
        if (empty()) return;
        stack<Node *> st;
        Node *t=root;
        st.push(t);
        t = t->left;
        while (t!=nullptr || !st.empty()){
            while (t != nullptr){
                st.push(t);
                t = t->left;
            }
            t = st.top();
            st.pop();
            cout<<t->data<<" ";
            t = t->right;
        }
        cout<<endl;
    }

    void inorder_rec(){
        if (empty()) return;
        inorder_rec(root);
        cout<<endl;
    }

    void preorder_iter(){
        if (empty()) return;
        stack<Node *>st;
        Node *t=root;
        while (t!=nullptr || !st.empty()){
            while (t!=nullptr){
                st.push(t);
                cout<<t->data<<" ";
                t = t->left;
            }
            t = st.top();
            st.pop();
            t = t->right;
        }
        cout<<endl;
    }
    
    void preorder_rec(){
        if (empty()) return;
        preorder_rec(root);
        cout<<endl;
    }

    void postorder_iter(){
        if (empty()) return;
        stack<Node *> st1,st2;
        if (root != nullptr)
            st1.push(root);
        while (!st1.empty()){
            Node *top = st1.top();
            st1.pop();
            st2.push(top);
            if (top->left != nullptr) st1.push(top->left);
            if (top->right != nullptr) st1.push(top->right);  
        }
        while (!st2.empty()){
            cout<<st2.top()->data<<" ";
            st2.pop();
        }
        cout<<endl;
    }

    void postorder_rec(){
        if (empty()) return;
        postorder_rec(root);
        cout<<endl;
    }
    
    void print(){
        if (empty()) return;
        int height = getHeight();
        int gap = 1<<(height);
        gap--;
        queue<Node *> curr_level;
        curr_level.push(root);
        cout<<"printing the tree: "<<endl;
        print(curr_level,gap);
    }

    int getHeight(){
        if (empty()) return 0;
        return getHeight(root);
    }
};

int main(){
    BinaryTree bt;
    cout<<"Inserting 7"<<endl;
    bt.insertNode(7);
    // bt.print();

    cout<<"Inserting 5"<<endl;
    bt.insertNode(5);
    // bt.print();

    cout<<"Inserting 3"<<endl;
    bt.insertNode(3);
    // bt.print();

    cout<<"Inserting 2"<<endl;
    bt.insertNode(2);
    // bt.print();

    cout<<"Inserting 1"<<endl;
    bt.insertNode(1);
    // bt.print();

    cout<<"Inserting 8"<<endl;
    bt.insertNode(8);

    // cout<<"Inserting 9"<<endl;
    // bt.insertNode(9);
    // bt.print();

    // cout<<"LEVEL ORDER TRAVERSAL BY ITERATION: "<<endl;
    // bt.level_traversal_iter();
    // cout<<"LEVEL ORDER TRAVERSAL BY RECURSION: "<<endl;
    // bt.level_traversal_rec();
    // cout<<"INORDER TRAVERSAL BY ITERATION: "<<endl;
    // bt.inorder_iter();
    // cout<<"INORDER TRAVERSAL BY RECURSION: "<<endl;
    // bt.inorder_rec();
    // cout<<"PREORDER TRAVERSAL BY ITERATION: "<<endl;
    // bt.preorder_iter();
    // cout<<"PREORDER TRAVERSAL BY RECURSION: "<<endl;
    // bt.preorder_rec();
    // cout<<"POSTORDER TRAVERSAL BY ITERATION: "<<endl;
    // bt.postorder_iter();
    // cout<<"POSTORDER TRAVERSAL BY RECURSION: "<<endl;
    // bt.postorder_rec();

    bt.print();
    BinaryTree bt2;
    bt2 = bt.clone();
    cout<<"Cloned tree:-"<<endl;
    bt2.print();
    cout<<"Original:-"<<endl;
    bt.print();
    return 0;
}