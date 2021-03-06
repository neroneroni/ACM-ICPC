template<int MOD = 998244353, int kPrimRoot = 3>
void ntt(Integral<MOD> A[], int n, int inv) {
  // inv == 1: ntt, == -1: intt

  // MOD == a * b ^ k + 1, n <= b ^ k.
  // 998244353 == (7 * 17) * 2 ^ 23 + 1.
  // This code works only when b == 2.
  Integral<MOD> w = 1, d = Integral<MOD>(kPrimRoot).power((MOD - 1) / n), t;
  int i, j, c, s;
  if (inv == -1) {
    for (i = 1, j = n - 1; i < j; ++i, --j) std::swap(A[i], A[j]);
    for (t = Integral<MOD>(n).inv(), i = 0; i < n; ++i) A[i] = A[i] * t;
  }
  for (s = n >> 1; s; s >>= 1, w = 1, d = d * d) {
    for (c = 0; c < s; ++c, w = w * d) {
      for (i = c; i < n; i += s << 1) {
        A[i | s] = (A[i] - (t = A[i | s])) * w;
        A[i] += t;
      }
    }
  }
  for (i = 1; i < n; ++i) {
    for (j = 0, s = i, c = n >> 1; c; c >>= 1, s >>= 1) j = j << 1 | (s & 1);
    if (i < j) std::swap(A[i], A[j]);
  }
}
