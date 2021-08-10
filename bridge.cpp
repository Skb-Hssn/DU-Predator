/* 
   prints the bridges in arbitrary order
   */

const int N = 1e5+5;
vector<int> G[N];

int deg[N], n, visited[N], assignedVal;
int bridge( int u, int parent ) {
 visited[u] = ++assignedVal;
 int mn = visited[u];
 for( int i = 0; i < (int)G[u].size(); i++ ) if( G[u][i] != parent ) {
  int v = G[u][i];
  if( !visited[v] ) {
   int k = bridge( v, u );
   if( k > visited[u] ) printf("%d - %d\n", u, v);
  }
  mn = min( mn, visited[v] );
 }
 return visited[u] = mn;
}
void processBridge() {
 assignedVal = 0;
 memset( visited, 0, sizeof( visited ) );
 for( int i = 0; i < n; i++ ) if( !visited[i] ) bridge( i, -1 );
}
