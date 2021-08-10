/*
- 0 based indexing.
- 2*u for u
- 2*u+1 for u'
- n *= 2
- To add a single edge:
- add the edge
- also add the contrapositive of the edge(must)
 */

#include<bits/stdc++.h>
using namespace std;

const int N = 1'000'005;

vector<int> G[N];
vector<int> GT[N];
vector<bool> vis;
vector<int> colors;
vector<int> order;
vector<int> assignment;

void dfs1(int cur)
{
 vis[cur] = true;
 for(int to : G[cur]) {
  if(!vis[to]) {
   dfs1(to);
  }
 }
 order.push_back(cur);
}

void dfs2(int cur, int col)
{
 colors[cur] = col;
 for(int to : GT[cur]) {
  if(colors[to] == 0) {
   dfs2(to, col);
  }
 }
}

bool sat(int n)
{
 for(int i = 0; i < n; i++) {
  if(!vis[i]) {
   dfs1(i);
  }
 }

 reverse(order.begin(), order.end());

 int col = 1;
 for(int i = 0; i < n; i++) {
  if(colors[order[i]] == 0) {
   dfs2(order[i], col++);
  }
 }

 for(int i = 0; i < n; i+=2) {
  if(colors[i] == colors[i+1]) {
   return false;
  }
  assignment[i/2] = colors[i] > colors[i+1];
 }

 return true;
}

void addEdge(int u, int v)
{
 G[u].push_back(v);
 GT[v].push_back(u);
}

void addOr(int u, int v)
{
 addEdge(u^1, v);
 addEdge(v^1, u);
}

void addXor(int u, int v)
{
 addOr(u, v);
 addOr(u^1, v^1);
}

void init(int n)
{
 for(int i = 0; i < n; i++) {
  G[i].clear();
  GT[i].clear();
 }
 vis = vector<bool>(n);
 colors = vector<int>(n);
 assignment = vector<int>(n);
 order.clear();
}


