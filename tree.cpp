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

    Node *clone(Node *node){
        if (node == nullptr) return nullptr;

        Node *newNode = new Node(node->data);
        newNode->left = clone(node->left);
        newNode->right = clone(node->right);

        // delete node;
        // node = nullptr;

        return newNode;
    }

    Node *mirror(Node *node){
        if (node == nullptr) return nullptr;

        Node *newNode = new Node(node->data);
        newNode->left = mirror(node->right);
        newNode->right = mirror(node->left);

        return newNode;
    }

    Node *searchBST(Node *node, int key){
        if (node == nullptr) return nullptr;

        if (key == node->data) return node;
        if (key < node->data) return searchBST(node->left,key);
        return searchBST(node->right,key);
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
        int flag = 0;
        if (curr_level.empty()) return;
        cout<<setw(gap/2+1);
        queue<Node *> next_level;
        Node *curr;
        Node *dummy = new Node(-1);
        while (!curr_level.empty()){
            curr = curr_level.front();
            if (curr->data > 0){
                flag = 1;
                if (curr->left != nullptr) next_level.push(curr->left);
                else next_level.push(dummy);
                if (curr->right != nullptr) next_level.push(curr->right);
                else next_level.push(dummy);
                    cout<<curr->data<<setw(gap+1);
            }
            
            else {
                next_level.push(dummy);
                next_level.push(dummy);
                cout<<" "<<setw(gap+1);
            }
            curr_level.pop();
        }
        cout<<endl;
        if (flag)
            print(next_level,gap/2);
    }

    int getHeight(Node *node){
        if(node == nullptr) return 0;
        return max(getHeight(node->left)+1,getHeight(node->right)+1);
    }

    bool checkEqual(Node *r1, Node *r2){
        if (r1 == nullptr && r2 == nullptr) return true;
        if (r1 == nullptr || r2 == nullptr) return false;
        if (r1->data != r2->data) return false;
        return checkEqual(r1->left,r2->left);
        return checkEqual(r1->right,r2->right);
    }
public:
    BinaryTree(){
        root = nullptr;
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

    BinaryTree clone(){
        // create clone of binary tree and return it;
        // erase all nodes in original tree.
        BinaryTree cloneTree;
        cloneTree.root = clone(this->root);

        cout<<cloneTree.root->data;
        cout<<"Same roots: "<<(cloneTree.root == this->root)<<endl;

        return cloneTree;
    }

    BinaryTree mirror(){
        BinaryTree mirrorTree;
        mirrorTree.root = mirror(this->root);

        return mirrorTree;
    }

    bool checkEqual(BinaryTree& other){
        return checkEqual(this->root,other.root);
    }

    // check if binary tree is empty
    bool empty(){
        if (root != nullptr) return false;
        cout<<"Tree is empty"<<endl;
        return true;
    }
// BST FUNCTIONS
    // inserting a value in binary search tree
    void insertBST(int val){
        Node *newNode = new Node(val);

        if (root==nullptr){
            root = newNode;
            return;
        }
        Node *parent;
        Node *t = root;
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

    Node *searchBST(int key){
        Node *found = searchBST(this->root,key);
        if (found == nullptr) cout<<"Value: "<<key<<" was NOT FOUND in the BST"<<endl;
        else cout<<"Value: "<<key<<" was FOUND in the BST"<<endl;
        return found;
    }

    void deleteNodeBST(int key){
        if (root == nullptr) {
            cout<<"Value: "<<key<<" is not present in BST"<<endl;
            return;
        }

        Node *parent=nullptr;
        Node *t = root;
        while (t != nullptr){
            if (key == t->data){
                break;
            }
            parent = t;
            if (key < t->data){
                t = t->left;
            }
            else {
                t = t->right;
            }
        }
        if (t==nullptr){
            cout<<"Value: "<<key<<" is not present in BST"<<endl;
            return;
        }
        // Case 1: t has no children
        if (t->left == nullptr && t->right == nullptr){
            // adjust left/right of parent as applicable
            if (parent == nullptr) return; // this is true if the element to be deleted is root
            if (key < parent->data) {
                parent->left = nullptr;
            }
            else{
                parent->right = nullptr;
            }
            cout<<"Found and deleted: "<<key<<" from BST"<<endl;
            delete t;
            return;
        }
        // Case 2: t has right child only
        if (t->left == nullptr) {
            if (parent == nullptr) return; // this is true if the element to be deleted is root
            if (key < parent->data) {
                parent->left = t->right;
            }
            else{
                parent->right = t->right;
            }
            cout<<"Found and deleted: "<<key<<" from BST"<<endl;
            delete t;
            return;
        }
        // Case 3: If there is only left child
        if (t->right == nullptr){
            if (parent == nullptr) return; // this is true if the element to be deleted is root
            if (key < parent->data) {
                parent->left = t->left;
            }
            else{
                parent->right = t->left;
            }
            cout<<"Found and deleted: "<<key<<" from BST"<<endl;
            delete t;
            return;
        }
        // Case 4: If there are two children
        // find the smallest element in right subtree of t
        cout<<"Found and deleted: "<<key<<" from BST"<<endl;
        Node *mn=t->right;
        Node *prtmn = t;
        while (mn->left!=nullptr){
            prtmn = mn;
            mn = mn->left;
        }
        t->data = mn->data;
        // Now delete mn
        prtmn->left = mn->right;
        delete mn;
    }
    // insert to binary tree
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

    // traversals
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

    Node *constructBST(vector<int> preorder,vector<int> inorder,int instart,int inend){
        static int i = 0;
        int index = -1;

        Node *newNode = new Node(preorder[i]);

        if (instart>inend) {
            return nullptr;
        }

        for (index = instart;index<inend;index++){
            if (inorder[index] == preorder[i]) break;
        }
        if (index==-1) return nullptr;

        i++;
        newNode->left = constructBST(preorder,inorder,instart,index-1);
        newNode->right = constructBST(preorder,inorder,index+1,inend);

        this->root = newNode;
        i--;
        return newNode;
    }
};

int main(){
    BinaryTree bt;
    cout<<"Inserting 7"<<endl;
    bt.insertNode(7);
    bt.print();

    cout<<"Inserting 5"<<endl;
    bt.insertNode(5);
    bt.print();

    cout<<"Inserting 3"<<endl;
    bt.insertNode(3);
    bt.print();

    cout<<"Inserting 2"<<endl;
    bt.insertNode(2);
    bt.print();

    cout<<"Inserting 1"<<endl;
    bt.insertNode(1);
    bt.print();

    cout<<"Inserting 8"<<endl;
    bt.insertNode(8);
    bt.print();

    cout<<"Inserting 9"<<endl;
    bt.insertNode(9);
    bt.print();

    cout<<"LEVEL ORDER TRAVERSAL BY ITERATION: "<<endl;
    bt.level_traversal_iter();
    cout<<"LEVEL ORDER TRAVERSAL BY RECURSION: "<<endl;
    bt.level_traversal_rec();
    cout<<"INORDER TRAVERSAL BY ITERATION: "<<endl;
    bt.inorder_iter();
    cout<<"INORDER TRAVERSAL BY RECURSION: "<<endl;
    bt.inorder_rec();
    cout<<"PREORDER TRAVERSAL BY ITERATION: "<<endl;
    bt.preorder_iter();
    cout<<"PREORDER TRAVERSAL BY RECURSION: "<<endl;
    bt.preorder_rec();
    cout<<"POSTORDER TRAVERSAL BY ITERATION: "<<endl;
    bt.postorder_iter();
    cout<<"POSTORDER TRAVERSAL BY RECURSION: "<<endl;
    bt.postorder_rec();

    BinaryTree bt2;
    bt2 = bt.clone();
    cout<<"Cloned tree:-"<<endl;
    bt2.print();
    cout<<"Original:-"<<endl;
    bt.print();
    cout<<"Are trees equal: "<<(bt.checkEqual(bt2));
    BinaryTree bt3;
    bt3 = bt2.mirror();
    cout<<"Mirrored tree: "<<endl;
    bt3.print();
    cout<<"Are trees equal: "<<(bt.checkEqual(bt3));

    BinaryTree bst;
    bst.insertBST(20);
    bst.insertBST(12);
    bst.insertBST(8);
    bst.insertBST(30);
    bst.insertBST(48);
    bst.insertBST(36);
    bst.insertBST(9);
    bst.insertBST(23);
    bst.insertBST(11);
    bst.insertBST(15);
    bst.print();

    bst.searchBST(15);
    bst.searchBST(11);
    bst.searchBST(10);

    bst.deleteNodeBST(15);
    bst.print();

    bst.deleteNodeBST(30);
    bst.print();

    bst.deleteNodeBST(8);
    bst.print();

    bst.inorder_rec();
    bst.preorder_rec();
    vector<int> preorder = {20,12,8,9,11,15,30,23,48,36};
    vector<int> inorder = {8,9,11,12,15,20,23,30,36,48};
    BinaryTree bst2;
    bst2.constructBST(preorder,inorder,0,preorder.size()-1);
    bst2.print();
    return 0;
}