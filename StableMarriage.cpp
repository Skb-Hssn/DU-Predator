 /* A person has an integer preference for each of the persons of the opposite
 * sex, produces a matching of each man to some woman. The matching will follow:
 * - Each man is assigned to a different woman (n must be at least m)
 * - No two couples M1W1 and M2W2 will be unstable.
 * Two couples are unstable if (M1 prefers W2 over W1 and W1 prefers M2 over M1)
 * INPUT: m – number of man, n – number of woman (must be at least as large as m)
 * - L[i][]: the list of women in order of decreasing preference of man i
 * - R[j][i]: the attractiveness of i to j.
 * OUTPUTS: - L2R[]: the mate of man i (always between 0 and n-1)
 * - R2L[]: the mate of woman j (or -1 if single)
 */

int m, n, L[MAXM][MAXW], R[MAXW][MAXM], L2R[MAXM], R2L[MAXW], p[MAXM];
void stableMarriage() {
 memset( R2L, -1, sizeof( R2L ) );
 memset( p, 0, sizeof( p ) );
 for( int i = 0; i < m; i++ ) { // Each man proposes...
  int man = i;
  while( man >= 0 ) {
   int wom;
   while( 1 ) {
    wom = L[man][p[man]++];
    if( R2L[wom] < 0 || R[wom][man] > R[wom][R2L[wom]] ) break;
   }
   int hubby = R2L[wom];
   R2L[L2R[man] = wom] = man;
   man = hubby;
  }
 }
}
