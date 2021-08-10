/*
1. For each node (except the root), look for the minimum weight incoming edge.
2. Look for cycles, if there's no cycle, we already have a tree (which is an MST) goto End
3. Pick one cycle and find an edge p->q, p is in set (not part of the cycle). q is in set
(s part of the cycle). Pick this p and q such that: cost of (p->q + sum of all edges in the
cycle) - the minimum incoming edge to q (computed in step 1) is minimum. Return to step 2.

4. if an edge is u -> v with cost w;
G[v].push_back(edge(u, w))
5. find parant from pr[]
*/

#include<bits/stdc++.h>
using namespace std;

struct edge { // Caution: The vertices should be reachable from the root
 int v, w;
 edge(int _v, int _w) : v(_v), w(_w) {}
 bool operator < ( const edge &v ) const { return w > v.w; }
};

const int N = 1e5 + 5;

vector <edge > G[N];
// For saving incoming edges and their costs
int DMST( int n, int root ) {
 // 1 indexed
 int i, res=0, pr[N], cost[N], sub[N], sn[N], visited[N];
 vector <int> ::iterator v, it;
 vector <int> node[N];
 for(i = 0; i <= n; i++) {
  node[i].clear(); node[i].push_back( i );
  sn[i] = i, sub[i] = pr[i] = 0;
 }
 for(i = 1; i <= n; i++) if( i != root ) {
  sort( G[i].begin(), G[i].end() ); // sorted in descending order of w
  pr[i] = G[i].back().v;
  cost[i] = sub[i] = G[i].back().w;
  res += cost[i];
 }
 bool cycle = true;
 while( cycle ) {
  cycle = false;
  memset( visited, 0, sizeof( visited ) );
  for(i = 1; i <= n; i++) {
   if( visited[i] || sn[i] != i ) continue;
   int cur = i;
   do {
    visited[cur] = i;
    cur = pr[cur];
   }while( cur > 0 && !visited[ cur ] );
   if( cur > 0 && visited[ cur ] == i ) {
    cycle = true;
    int start = cur; // assert( sn[start] == start ) ;
    do{
     if( *node[cur].begin() != cur ) break;
     for( it = node[cur].begin(); it != node[cur].end(); it++)
     {
      sn[ *it ] = start;
      if( cur != start ) node[ start ].push_back ( *it );
     }
     if( cur != start ) node[ cur ].clear();
     cur = pr[ cur ];
    }while( cur != start );
    int best = INT_MAX;
    for( v = node[start].begin(); v!=node[start].end(); v++) {
     while( !G[*v].empty() && sn[G[*v].back().v] == start)
      G[ *v ].pop_back();
     if( !G[*v].empty() ) {
      int tcost = G[*v].back().w - sub[ *v ];
      if( tcost < best ) best = tcost, pr[ start ] =
       G[*v].back().v;
     }
    } //assert( best >= 0 && best < INT_N );
    cost[ start ] = best;
    for( v = node[start].begin(); v != node[start].end(); v++
      )sub[*v] += best;
    res += best;
   }
  }
  for(i = 1; i <= n; i++) pr[i] = sn[ pr[i] ];
 }
 for(int i = 1; i <= n; i++) {
  printf("%d ", pr[i]);
 }
 puts("");
 return res;
}

int main()
{
 int n, m;
 scanf("%d%d", &n, &m);
 while(m--) {
  int u, v, w;
  scanf("%d%d%d", &u, &v, &w);
  G[v].push_back(edge(u, w));
 }
 printf("%d\n", DMST(n, 1));
}
