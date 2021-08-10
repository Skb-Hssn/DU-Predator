#include<bits/stdc++.h>
using namespace std;

const int N = 1e5+5;
vector<int> G[N];
vector<bool> vis(N);
vector<int> order;

void dfs(int cur)
{
 vis[cur] = true;
 for(int to : G[cur]) {
  if(!vis[to]) {
   dfs(to);
  }
 }
 order.push_back(cur);
}

void topSort(int n)
{
 for(int i = 1; i <= n; i++) {
  if(!vis[i]) {
   dfs(i);
  }
 }
 reverse(order.begin(), order.end());
}
