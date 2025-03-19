#include<iostream>
#include<utility>
#include<stack>
#include<vector>
#include<queue>

using namespace std;

void dfs_nr(vector<vector<int>> G,int n,int i){
    vector<int> visited(n,0);
    int components = 0;
    stack<int> s;
    int j;
    int flag=1;
    s.push(i);
    while (flag){
        components++;
        while (!s.empty()){
            i = s.top();
            s.pop();
            if (visited[i]!=1){
                cout<<i<<" ";
                visited[i] = 1;

                for (j=0;j<n;j++){
                    if (visited[j] != 1 && G[i][j]==1){
                        s.push(j);
                    }
                }
            }
        }
        flag = 0;
        for (j=0;j<n;j++){
            if (visited[j]!=1) {
                flag = 1;
                s.push(j);
            }
        }
    }
    cout<<"\nNo of components: "<<components;
}

void dft(vector<vector<int>> G,int n,int i){
    static vector<int> visited(n,0);
    static int depth;
    static int components;
    if (components==0) components = 1;
    depth++;
    int j;
    cout<<i<<" ";
    visited[i] = 1;
    for (j=0;j<n;j++){
        if (visited[j]==0 && G[i][j]==1){
            dft(G,n,j);
        }
    }
    depth--;
    int k = -1;
    if (depth==0){
        for (j=0;j<n;j++){
            if (!visited[j]){
                components++;
                k=j;
                break;
            }
        }
        if (k>=0) dft(G,n,k);
        else{
            cout<<"\nNo of components: "<<components;
            depth = 0;
            components = 0;
            visited.clear();
            visited.resize(n,0);
        }
    }
}

void bft(vector<vector<int>> G,int n,int i){
    vector<int> visited(n,0);
    int components = 0;
    int flag = 1;
    queue<int> q;
    q.push(i);
    cout<<i<<" ";
    visited[i]=1;
    while (flag){
        components++;
        while (!q.empty()){
            i = q.front();
            q.pop();
            for (int j=0;j<n;j++){
                if (visited[j]!=1 && G[i][j]==1) {
                    visited[j]=1;
                    cout<<j<<" ";
                    q.push(j);
                }
            }
        }
        flag = 0;
        for (int j=0;j<n;j++){
            if (visited[j]!=1) {
                flag = 1;
                q.push(j);
            }
        }
    }
    cout<<"\nNo of components: "<<components;
}

int main(){
    vector<vector<int>> G;
    int n,m;

    int ch=1;
    while (ch!=0){
        cout<<"Enter your choice\n";
        cout<<"0. Exit\n";
        cout<<"1. Enter a graph\n";
        cout<<"2. Add an edge\n";
        cout<<"3. Remove an edge\n";
        cout<<"4. DFS non recursive\n";
        cout<<"5. DFS recursive\n";
        cout<<"6. BFS\n";
        cout<<"\n******************************\n";
        cin>>ch;
        if (ch==1){
            cout<<"********CREATING GRAPH*******\n";
            cout<<"Enter number of vertex: ";
            cin>>n;
            cout<<"Enter number of edges: ";
            cin>>m;
            int a,b;
            G.resize(n,vector<int>(n,0));
            for (int i=0;i<m;i++){
                cout<<"Enter edge connection: "<<endl;
                cin>>a>>b;
                G[a][b] = 1;
                G[b][a] = 1;
            }
        }
        else if (ch==2){
            cout<<"**********Add Edge***********\n";
            int a,b;
            cout<<"Enter the edge connection: "<<endl;
            cin>>a>>b;
            G[a][b] = 1;
            G[b][a] = 1;
        }
        else if (ch==3){
            cout<<"********Delete edge*********\n";
            int a,b;
            cout<<"Enter the edge connection: "<<endl;
            cin>>a>>b;
            G[a][b] = 0;
            G[b][a] = 0;
        }
        else if (ch==4){
            cout<<"*******DFS Non Recursive*******\n";
            dfs_nr(G,n,0);
            cout<<"\n*****************************\n";
        }
        else if (ch==5){
            cout<<"********DFS Recursive*********\n";
            dft(G,n,0);
            cout<<"\n****************************\n";
        }
        else if (ch==6){
            cout<<"************BFS**************\n";
            bft(G,n,0);
            cout<<"\n***************************\n";
        }
        else break;
    }
}