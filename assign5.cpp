#include<iostream>
#include<queue>
#include<utility>
#include<string>

using namespace std;

class Node{
public:
    int freq;
    char ch;
    Node *left,*right;
    Node(){
        this->left = nullptr;
        this->right = nullptr;
        this->ch = 'a';
        this->freq = 0;
    }
    Node (int fr,char c){
        this->left = nullptr;
        this->right = nullptr;
        this->freq = fr;
        this->ch = c;
    }
    bool operator < (Node *other){
        if (freq<other->freq) return true;
        return false;
    }
};

class HuffmanTree{
private:
    Node *root;

    void preorder_rec(Node *node){
        if (node==nullptr) return;
        // if (node->ch!='.'){
        cout<<node->ch<<" -> "<<node->freq<<endl;
        // }
        preorder_rec(node->left);
        preorder_rec(node->right);
    }
public:
    HuffmanTree(){
        root = nullptr;
    }

    void preorder_rec(){
        if (root==nullptr) return;
        preorder_rec(root);
        cout<<endl;
    }

    void construct(string s){
        priority_queue<Node *,vector<Node *>,greater<Node *>> pq;
        int arr[26]={0};
        for (char& c:s){
            arr[c-'a']++;
        }
        for (int i=0;i<26;i++){
            if (arr[i]>0){
                Node *newNode = new Node(arr[i],'a'+i);
                pq.push(newNode);
            }
        }

        while (!pq.empty()){
            Node *top = pq.top();
            cout<<top->ch<<" - "<<top->freq<<endl;
            pq.pop();
        }
        
    }
};

int main(){
    
    int arr[26]={0};

    string s;
    cout<<"Enter a string to encode: ";
    cin>>s;

    HuffmanTree ht;
    ht.construct(s);

    return 0;
}