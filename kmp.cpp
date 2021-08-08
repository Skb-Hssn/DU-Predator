vector<int> cal_pi(string& s) {
  int n = s.size();
  vector<int> pi(n);
  for (int k = 0, i = 1; i < n; ++i) {
    while (k and s[i] != s[k]) {
      k = pi[k-1];
    }
    if (s[i] == s[k])  k++;
    pi[i] = k;
  }
  return pi;
}