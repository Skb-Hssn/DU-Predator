#include<bits/stdc++.h>
using namespace std;

/*
   - 1 based indexing.
   */

const int MAXN = 100500;
const int DUMMY = 0;
const int INF = (int)1e9;
int U, V;

vector<int> G[MAXN];
int pair_U[MAXN];
int pair_V[MAXN];
int dist[MAXN];

bool bfs()
{
 queue<int> Q;
 for(int i = 1; i <= U; i++) {
  if(pair_U[i] == DUMMY) {
   dist[i] = 0;
   Q.push(i);
  } else {
   dist[i] = INF;
  }
 }
 dist[DUMMY] = INF;
 while(!Q.empty()) {
  int u = Q.front();
  Q.pop();
  if(dist[u] < dist[DUMMY]) {
   for(int to : G[u]) {
    if(dist[pair_V[to]] == INF) {
     dist[pair_V[to]] = dist[u] + 1;
     Q.push(pair_V[to]);
    }
   }
  }
 }
 return dist[DUMMY] != INF;
}

bool dfs(int u)
{
 if(u == DUMMY) return true;
 for(int to : G[u]) {
  if(dist[pair_V[to]] == dist[u] + 1) {
   if(dfs(pair_V[to])) {
    pair_V[to] = u;
    pair_U[u] = to;
    return true;
   }
  }
 }
 dist[u] = INF;
 return false;
}

int hopcroft()
{
 for(int i = 1; i <= U; i++) pair_U[i] = DUMMY;
 for(int i = 1; i <= V; i++) pair_V[i] = DUMMY;
 int matching = 0;
 while(bfs()) {
  for(int i = 1; i <= U; i++) {
   if(pair_U[i] == DUMMY) {
    if(dfs(i)) {
     matching++;
    }
   }
  }
 }
 return matching;
}

int main()
{
 int m;
 scanf("%d%d%d", &U, &V, &m);
 while(m--) {
  int x, y;
  scanf("%d%d", &x, &y); // 1 -> 1, 2 -> 1
  G[x].push_back(y);
 }
 printf("%d\n", hopcroft());
}

