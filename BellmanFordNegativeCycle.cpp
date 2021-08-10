#include<bits/stdc++.h>
using namespace std;

/*
   For directed graph. otherwise returns the single edge with
   the negative cycle.
   */

using pii=pair<int,int>;
using vi=vector<int>;

const int INF=1e9+5;
const int N=1e5+5;
vector<pii> G[N];
vi d(N,INF), p(N,-1);

void bellman(int n, int s)
{
 d[s] = 0;
 p[s] = s;
 int x = -1;
 for(int i = 0; i < n; i++) {
  x = -1;
  for(int v = 1; v <= n; v++) {
   for(auto e : G[v]) {
    int to = e.first;
    int w = e.second;
    if(d[to] > d[v] + w) {
     d[to] = max(-INF, d[v] + w);
     p[to] = v;
     x = to;
    }
   }
  }
 }

 if(x == -1) puts("NO");
 else {
  int y = x;
  for(int i = 0;i<n; i++) {
   y = p[y];
  }
  vector<int> path;
  for(int cur=y;;cur=p[cur]) {
   path.push_back(cur);
   if(cur == y && path.size() > 1) break;
  }
  reverse(path.begin(), path.end()); // negative cycle
  printf("Path : \n");
  for(int pp : path) {
   printf("%d ", pp);
  }
  puts("");
 }
}

int main()
{
 int n, m;
 scanf("%d%d", &n, &m);
 while(m--) {
  int u, v, w;
  scanf("%d%d%d", &u, &v, &w);
  G[u].push_back({v, w});
 }

 bellman(n, 1);

 for(int i = 1; i <= n; i++) {
  printf("%d ", d[i]);
 }
 puts("");
}
