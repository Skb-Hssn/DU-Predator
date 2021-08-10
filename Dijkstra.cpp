#include<bits/stdc++.h>
using namespace std;

using pii=pair<int,int>;
using vi=vector<int>;

const int INF=1e9+5;
const int N=1e5+5;
vector<pii> G[N];
vi d(N,INF), p(N,-1);

void dijk(int s){
 d[s]=0;
 priority_queue<pii> PQ;
 PQ.push({0, s});
 while(!PQ.empty()){
  pii it = PQ.top(); PQ.pop();
  int v = it.second;
  int d_v = it.first;
  d_v = -d_v;
  if(d_v != d[v]) continue;
  for(pii e : G[v]){
   int to = e.first;
   int len = e.second;
   if(d[v]+len < d[to]) {
    d[to] = d[v]+len;
    p[to] = v;
    PQ.push({-d[to], to});
   }
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
  G[u].push_back({v, w});
  G[v].push_back({u, w});
 }

 dijk(1);

 for(int i = 1; i <= n; i++) {
  printf("%d ", d[i]);
 }
 puts("");
}
