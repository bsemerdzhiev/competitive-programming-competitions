#include <bits/stdc++.h>
#include <cstdint>

using namespace std;

const int32_t MOD = 998244353;
const int32_t MAXN = 1e6 + 5;

namespace MO {
int32_t add(int64_t x, int64_t y) {
  return ((x % MOD) + (y % MOD) + MOD) % MOD;
}
int32_t mul(int64_t x, int64_t y) { return ((x % MOD) * (y % MOD)) % MOD; }

int32_t pow(int32_t x, int32_t y) {
  int32_t res = 1;

  while (y) {
    if (y & 1) {
      res = mul(res, x);
    }
    x = mul(x, x);
    y >>= 1;
  }
  return res;
}

int32_t inverse(int32_t x) { return pow(x, MOD - 2); }
}; // namespace MO

int32_t n, a[MAXN];
int32_t fact[MAXN], inv_fact[MAXN];

int32_t comb(int32_t i, int32_t j) {
  return MO::mul(fact[i], MO::mul(inv_fact[i - j], inv_fact[j]));
}

void solve() {
  if (n == 1) {
    cout << "0\n";
    return;
  }
  vector<int32_t> cnt(30);

  for (int32_t i{0}; i < n; i++) {
    for (int32_t j{0}; j < 30; j++) {
      if (a[i] & (1 << j)) {
        cnt[j]++;
      }
    }
  }
  int32_t ans = 1;

  for (int32_t i{29}; i >= 0; i--) {
    if (cnt[i] & 1) {
      ans = cnt[i];
      break;
    }
  }
  cout << ans << "\n";
}

void precalc() {
  fact[0] = 1;
  inv_fact[0] = MO::inverse(1);

  for (int32_t i{1}; i < MAXN; i++) {
    fact[i] = MO::mul(fact[i - 1], i);
    inv_fact[i] = MO::inverse(fact[i]);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  size_t t;
  cin >> t;

  precalc();

  while (t--) {
    cin >> n;
    for (int32_t i{0}; i < n; i++) {
      cin >> a[i];
    }
    solve();
  }

  return 0;
}
