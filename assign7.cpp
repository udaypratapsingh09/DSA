#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>
#include<set>

using namespace std;

typedef struct{
    int p1;
    int p2;
    int weight;
} Edge;

bool sort_by_weight(Edge e1,Edge e2){
    return e1.weight <= e2.weight;
}

vector<Edge> kruskal(vector<Edge> edges,int n){
    vector<Edge> min_span_tree;
    int j=0;
    vector<pair<int,int>> visited(n,{-1,0}); // {origin of subtree, 0 if unvisited 1 if visited}
    sort(edges.begin(),edges.end(),sort_by_weight);
    int m = edges.size();
    int i=0;
    while (i<m){
        Edge e = edges[i];
        if (visited[e.p1].second == 0 && visited[e.p2].second == 0){
            // if neither is visited set visited to 1 for both
            // subtree origin is set to e.p1
            visited[e.p1].first = e.p1;
            visited[e.p2].first = e.p1;
            visited[e.p1].second = 1;
            visited[e.p2].second = 1;
            min_span_tree.push_back(e);
        }
        else if (visited[e.p1].second == 0 || visited[e.p2].second == 0){
            // if only 1 is visited;
            // set visited as 1 for both
            // if a visited[e.p1] has -1 as origin set it to be same as visted[e.p2] origin & vice versa
            visited[e.p1].second = 1;
            visited[e.p2].second = 1;
            if (visited[e.p1].first == -1) visited[e.p1].first = visited[e.p2].first;
            else visited[e.p2].first = visited[e.p1].first;
            min_span_tree.push_back(e);
        }
        else if (visited[e.p1].first != visited[e.p2].first){
            // if both are visited but part of separate subtrees
            // set origin of both to a common value
            int target = visited[e.p2].first;
            for (int j=0;j<visited.size();j++){
                if (visited[j].first == target){
                    visited[j].first = visited[e.p1].first;
                }
            }
            min_span_tree.push_back(e);
        }
        i++;
    }
    return min_span_tree;
}

vector<int> prims(vector<Edge> edges,int n,int start){
    sort(edges.begin(),edges.end(),sort_by_weight);
    set<int> nodes;
    vector<int> min_span_tree;
    nodes.insert(start);
    for (int i=0;i<edges.size();i++){
        Edge e = edges[i];
        int u = e.p1;
        int v = e.p2;
        if (nodes.find(u) == nodes.end() && nodes.find(v) != nodes.end()){
            nodes.insert(u);
            min_span_tree.push_back(u);
        }
        else if (nodes.find(u) != nodes.end() && nodes.find(v) == nodes.end()){
            nodes.insert(v);
            min_span_tree.push_back(v);
        }
    }
    return min_span_tree;
}

int main(){
    int n,m;
    vector<Edge> edges;
    cout<<"Enter the number of nodes\n";
    cin>>n;
    cout<<"Enter the number of edges\n";
    cin>>m;
    for (int i=0;i<m;i++){
        int a,b;
        int w;
        cout<<"Enter the edge in this format: v1 v2 weight\n";
        cin>>a>>b>>w;
        edges.push_back({a,b,w});
    }

    vector<Edge> min_span_kruskal = kruskal(edges,n);

    for (int i=0;i<min_span_kruskal.size();i++){
        Edge e = min_span_kruskal[i];
        cout<<e.p1<<" "<<e.p2<<" "<<e.weight<<endl;
    }

    vector<int> min_span_prim = prims(edges,n,0);
    
    return 0;
}