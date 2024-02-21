#include <bits/stdc++.h>
using namespace std;
int prims(vector<pair<int, int>> g[], vector<int> &vis){
    int ans = 0;
    multiset<pair<int, int>> st;
    st.insert({0, 0}); // weight,vertex
    while (!st.empty()){
        auto it = st.begin();
        st.erase(it);
        if (!vis[it->second]){
            ans += it->first;
            vis[it->second] = 1;
            for (auto &child : g[it->second]){
                if (!vis[child.second]){
                    st.insert({child.first, child.second});
                }
            }
        }
    }
    return ans;
}
int main(){
    vector<pair<int, int>> g[100];
    vector<int> vis(100, 0);
    int n, e, ans = 0;
    cin >> n >> e;
    for (int i = 0; i < e; i++){
        int x, y, w;
        cin >> x >> y >> w;
        g[x].push_back({w, y});
        g[y].push_back({w, x});
    }
    cout << prims(g, vis) << endl;
    return 0;
}

// 5 8
// 0 1 2
// 0 4 6
// 0 3 7
// 1 4 4
// 1 2 1
// 2 4 2
// 2 3 3
// 4 3 5
