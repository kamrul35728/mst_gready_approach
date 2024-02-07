#include<bits/stdc++.h>
using namespace std;
vector<pair<int,int>> g[100];
vector<int> tree[100];
int vis[100];
int vis2[100];
void printTree(int n) {
    cout << "Tree:" << endl;
    for(int i = 1; i <= n; ++i) {
        cout << "Node " << i << " -> ";
        for(auto node : tree[i]) {
            cout << node << " ";
        }
        cout << endl;
    }
}
void checkcycle(int src,int &flag,int par=-1){
     vis[src]=1;
     for(auto child:tree[src]){

         if(vis[child]&&child==par) continue;
         if(vis[child]){
            flag= 1;
            return;
         }
         checkcycle(child,flag,src);
     }
}
int MST(int src,multimap<int,pair<int,int>> &mp,int &cost){
    int flag=0;
    vis2[src]=1;
    for(auto it: g[src]){
        if(!vis2[it.first]){
            mp.insert({it.second, {src, it.first}});
        }
    }
    for(auto it: mp){
        cout<<"map: "<<it.first<<" "<<it.second.first<<" " <<it.second.second<<endl;
    }
    auto it=mp.begin();
    tree[it->second.first].push_back(it->second.second);
    tree[it->second.second].push_back(it->second.first);

    checkcycle(it->second.first,flag);
    memset(vis,0,sizeof(vis));
         if(flag){
            tree[it->second.first].pop_back();
            tree[it->second.second].pop_back();
            flag=0;
            cout<<"cost: "<<cost<<endl;
         }
         else{
            cost+=it->first;
         }
         int x=it->second.second;
        mp.erase(it);
        return x;

}
int main (){
    int n,e;
    cin>>n>>e;
    multimap<int,pair<int,int>> mp;
    for(int i=0;i<e;i++){
        int x,y,w; 
        cin>>x>>y>>w;
        g[x].push_back({y,w});
        g[y].push_back({x,w});
        //mp.insert({w,{x,y}});
    }
    int cost=0;
    int x=1;
    for (int i = 1; i <= n; i++){
        if(!vis2[x]){
            x= MST(x,mp,cost);
        }
        
    }
    cout<<cost<<endl;
    printTree(n);
    
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
