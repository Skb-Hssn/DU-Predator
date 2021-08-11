ll basis[D];
int rnk;

//O(D)
void insert_vector(ll mask){
  for (int i = 0; i < D; ++i){
    if((mask&(1LL<<i)) == 0)  continue;
    if(!basis[i]){
      basis[i] = mask;
      rnk++;
      return;
    } else {
      mask ^= basis[i];
    }
  }
}

// memset(basis, 0, sizeof(basis));
// rnk=0;