
Sk Tawkir Ahmed
#include <bits/stdc++.h>
using namespace std;
bool dfs(int node, vector<vector<int>> &adj, vector<bool> &visited, int parent){
    visited[node] = true;
    for (auto &it : adj[node]){
        if (!visited[it]){
            if (dfs(it, adj, visited, node)){
                return true;
            }
        }
        else if (it != parent){
            return true;
        }
    }
    return false;
}
bool hasCycle(int V, vector<vector<int>> &adj,int src){
    vector<bool> visited(V + 1, false);
    return dfs(src, adj, visited, -1);
}
int minimum_spanning_tree_cost(int V, multimap<int, pair<int, int>> &mp, vector<vector<int>> &adj){
    int minWeight = 0;
    int cnt = 0;
    int z;
    vector<int> v;
    for (auto it = mp.begin(); it != mp.end(); it++){
        // Temporarily add the edge
        int node = it->second.first;
        int adjNode = it->second.second;
        int wg = it->first;
        adj[node].push_back(adjNode);
        adj[adjNode].push_back(node);
        if (!hasCycle(V, adj,node)){
            cnt++;
            if (cnt == V-1){
                z=wg;
                adj[node].pop_back();
                adj[adjNode].pop_back();
                // cout<<z<<endl;
                break;
            }
                minWeight += wg;
            // v.push_back(wg);
        }
        else{
            adj[node].pop_back();
            adj[adjNode].pop_back();
        }
    }
// ----------------------------------------------
    auto t = mp.upper_bound(z);
    // cout<<t->first<<endl;
    if (t != mp.end()){
        for (auto x = t; x != mp.end(); x++){
            int n = x->second.first;
            int aN = x->second.second;
            int w = x->first;
            adj[n].push_back(aN);
            adj[aN].push_back(n);
            if (!hasCycle(V, adj,n)){
                // v.push_back(w);
                minWeight += w;
                break;
            }else{
                adj[n].pop_back();
                adj[aN].pop_back();
                // cout<<"*"<<endl;
            }
        }
    }else{
        return -1;
    }
    return minWeight;
}
int main(){
    int V, E;
    cin >> V >> E;
    vector<vector<int>> adj(V + 1);
    multimap<int, pair<int, int>> mp;
    for (int i = 1; i <= E; i++){
        int u, v, w;
        cin >> u >> v >> w;
        mp.insert({w, {u, v}});
    }
    string vec;
    // vector<int> v = minimum_spanning_tree_cost(V, mp, adj);
    // cout << "Minimum Spanning Tree is: "<< endl;
    // for (auto &it : v){
    //     vec+=to_string(it)+"+";
    // }
    // vec.resize(vec.size()-1);
    // cout<<vec<<endl<<endl;
    int weight = minimum_spanning_tree_cost(V, mp, adj);
    cout << "Minimum Spanning Tree is: " << weight << endl;
    return 0;
}
// 5 8
// 1 2 2
// 2 3 3
// 3 5 1
// 4 5 2
// 1 4 5
// 2 4 2
// 1 5 3
// 3 4 4


// 5 8
// 1 2 2
// 2 3 5
// 3 5 1
// 4 5 2
// 1 4 5
// 2 4 3
// 1 5 4
// 2 5 3
