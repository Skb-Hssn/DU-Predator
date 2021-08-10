#include<bits/stdc++.h>
using namespace std;

struct Edge {
 int u, v, w;
 Edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}
 bool operator<(Edge& o) {
  return w < o.w;
 }
};

const int N = 1e5+5;
vector<int> par(N), siz(N);
vector<Edge> edges;
vector<Edge> MST;
int cost=0;

int findSet(int u)
{
 if(u == par[u]) return u;
 return par[u] = findSet(par[u]);
}

bool unionSet(int u, int v)
{
 u=findSet(u);
 v=findSet(v);
 if(u != v) {
  if(siz[u] < siz[v]) {
   swap(u, v);
  }
  par[v] = u;
  siz[u] += siz[v];
  return true;
 } else {
  return false;
 }
}


void kruskal(int n)
{
 for(int i = 1; i <= n; i++) {
  par[i] = i, siz[i] = 1;
 }
 sort(edges.begin(), edges.end());
 for(auto e : edges) {
  if(unionSet(e.u, e.v)) {
   cost += e.w;
   MST.push_back(e);
  }
 }
}

int main()
{
 int n, m;
 scanf("%d%d", &n, &m);
 while(m--) {
  int u, v, w;
  scanf("%d%d%d", &u, &v, &w);
  edges.push_back(Edge(u, v, w));
 }
 kruskal(n);
 printf("%d\n", cost);
 for(auto e : MST) {
  printf("%d %d\n", e.u, e.v);
 }
}
