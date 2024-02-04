#include <bits/stdc++.h>
using namespace std;

bool dfs(int node, vector<vector<int>> &adj, vector<bool> &visited, int parent)
{
    visited[node] = true;
    for (auto &it : adj[node])
    {
        if (!visited[it])
        {
            if (dfs(it, adj, visited, node))
            {
                return true;
            }
        }
        else if (it != parent)
        {
            return true;
        }
    }
    return false;
}

bool hasCycle(int V, vector<vector<int>> &adj)
{
    vector<bool> visited(V + 1, false);
    return dfs(1, adj, visited, -1);
}

int minimum_spanning_tree(int V, multimap<int, pair<int, int>> &mp, vector<vector<int>> &adj)
{
    int minWeight = 0;
    int cnt = 0;
    for (auto it = mp.begin(); it != mp.end(); it++)
    {
        cnt++;
        // Temporarily add the edge
        int node = it->second.first;
        int adjNode = it->second.second;
        int wg = it->first;
        adj[node].push_back(adjNode);
        adj[adjNode].push_back(node);

        // Check if adding the edge creates a cycle
        if (!hasCycle(V, adj))
        {
            minWeight += wg;
        }
        else
        {
            // Remove the edge
            adj[node].pop_back();
            adj[adjNode].pop_back();
        }

        if (cnt == V - 1)
        {
            break;
        }
    }
    return minWeight;
}

int main()
{
    int V, E;
    cin >> V >> E;
    vector<vector<int>> adj(V + 1); // Adjacency list

    multimap<int, pair<int, int>> mp;
    for (int i = 1; i <= E; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        mp.insert({w, {u, v}});
    }

    int weight = minimum_spanning_tree(V, mp, adj);
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