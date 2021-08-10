/*
   - 1 based indexing
   */
#include<bits/stdc++.h>
using namespace std;

const int N = 1e5+5;

vector<int> G[N], GT[N];
vector<bool> used(N);
vector<int> order, components;
vector<vector<int>> SCC;

void dfs1(int cur)
{
 used[cur] = 1;
 for(int to : G[cur]) {
  if(!used[to]) {
   dfs1(to);
  }
 }
 order.push_back(cur);
}

void dfs2(int cur)
{
 used[cur] = true;
 components.push_back(cur);

 for(int to : GT[cur]) {
  if(!used[to]) {
   dfs2(to);
  }
 }
}

void findSCC(int n)
{
 for(int i = 1; i <= n; i++) {
  if(!used[i]) {
   dfs1(i);
  }
 }

 used.assign(n+1, false);
 reverse(order.begin(), order.end());

 for(int o : order) {
  if(!used[o]) {
   dfs2(o);
   SCC.push_back(components);
   components.clear();
  }
 }
}

int main()
{
 int n, m;
 scanf("%d%d", &n, &m);

 while(m--) {
  int u, v;
  scanf("%d%d", &u, &v);
  G[u].push_back(v);
  GT[v].push_back(u);
 }

 findSCC(n);
}
