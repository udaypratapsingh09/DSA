#include<iostream>
#include<deque>
using namespace std;
class node{
    public:
    char data;
    int value;
    node *left,*right;
    node(char data,int value){
        this->data=data;
        this->value=value;
        this->right=nullptr;
        this->left=nullptr;
    }
};
void sorted_insert(deque<node*> &d,node*n){
    if(d.empty()||d.front()->value>n->value){
        d.push_front(n);
        return;
    }
    node *p=d.front();
    d.pop_front();
    sorted_insert(d,n);
    d.push_front(p);
}
void display(deque<node*> d){
    while(!d.empty()){
        cout<<d.front()->data<<" "<<d.front()->value<<endl;
        d.pop_front();
    }
    cout<<endl;
}
void create_huffman(deque<node*> &d){
    node *one=nullptr,*two=nullptr,*three=nullptr;
    while(d.size()>1){
        one=d.front();
        d.pop_front();
        two=d.front();
        d.pop_front();        
        three=new node('%',one->value+two->value);
        three->left=one;
        three->right=two;
        sorted_insert(d,three);
    }
}
void preorder(node *d){
    if(d==nullptr){
        return;
    }
    cout<<d->data<<" "<<d->value<<endl;
    preorder(d->left);
    preorder(d->right);
}
void print(node* d,string s){
    if(d->left==nullptr || d->right==nullptr){
        cout<<d->data<<" "<<s<<endl;
        return;
    }
    print(d->left,s+'0');
    print(d->right,s+'1');
}
int main(){
  char c[]={'a','c','e','h','i'};
  int freq[]={3,5,8,2,7};
  deque<node*> d;
  node *n=nullptr;
  for(int i=0;i<5;i++){
    n=new node(c[i],freq[i]);
    sorted_insert(d,n);
  }
  display(d);
  create_huffman(d);
  node *ans=d.front();
  print(ans,"");
  return 0;
}