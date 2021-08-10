/*
   - 1 based indexing
   */
#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int timer = 0;
vector<int> G[N];
vector<int> low(N), disc(N), par(N), vis(N);
vector<pair<int, int>> ST;
vector<vector<pair<int, int>>> BCC;

void dfs(int cur)
{
 disc[cur] = low[cur] = timer;
 timer++;
 vis[cur] = true;

 int child = 0;

 for(int to : G[cur]) {
  if(!vis[to]) {
   child++;
   ST.push_back({cur, to});
   par[to] = cur;
   dfs(to);
   low[cur] = min(low[cur], low[to]);

   if((par[cur] == 0 && child > 1) || (par[cur] != 0 && low[to] >= disc[cur])) {
    vector<pair<int, int>> temps;
    while(ST.back() != make_pair(cur, to)) {
     temps.push_back(ST.back());
     ST.pop_back();
    }
    temps.push_back(ST.back());
    ST.pop_back();
    BCC.push_back(temps);
   }
  } else if(par[cur] != to && disc[to] < low[cur]) {
   low[cur] = disc[to];
   ST.push_back({cur, to});
  }
 }
}

void findBCC(int n)
{
 for(int i = 1; i <= n; i++) {
  if(vis[i] == false) {
   dfs(i);
   vector<pair<int, int>> temps;
   while(ST.size()) {
    temps.push_back(ST.back());
    ST.pop_back();
   }
   if(temps.size()) {
    BCC.push_back(temps);
   }
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
  G[v].push_back(u);
 }

 findBCC(n);
}

