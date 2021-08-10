/*
   result[i] will contain true if the ith node is an articulation
   */

const int N = 1e5+5;

vector<int> G[N];

int deg[N], n, visited[N], assignedVal;
bool result[N];

int articulation( int u, int depth ) {
 if( visited[u] > 0 ) return visited[u];
 visited[u] = ++assignedVal;
 int mn = visited[u], rootCalled = 0;
 for(int i = 0; i < (int)G[u].size(); i++) {
  int v = G[u][i];
  if( !visited[v] ) {
   if( !depth ) rootCalled++;
   int k = articulation( v, depth + 1 );
   if( k >= visited[u] ) result[u] = true;
  }
  mn = min( mn, visited[v] );
 }
 if( !depth ) result[u] = ( rootCalled >= 2 );
 return visited[u] = mn;
}

void processArticulation() {
 assignedVal = 0;
 memset( result, 0, sizeof( result ) );
 memset( visited, 0, sizeof( visited ) );
 for( int i = 0; i < n; i++ ) if( !visited[i] ) articulation( i, 0 );
}
