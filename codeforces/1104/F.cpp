#include <bits/stdc++.h>

using namespace std;

const int32_t MOD = 998244353;
const int32_t MAXN = 5e5 + 5;

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

int32_t n, m;
int32_t a[MAXN];
int32_t pref[MAXN], suff[MAXN], T[MAXN];

void solve() {
  for (int32_t i{0}; i <= n; i++) {
    pref[i] = suff[i] = T[i] = -MAXN;
  }
  pref[0] = 0;

  for (int32_t i{0}; i < n; i++) {
    int32_t temp = suff[i];

    if (i - a[i] >= 0) {
      temp = max(temp, pref[i - a[i]]);
      temp = max(temp, T[i - a[i]]);
    }
    temp++;

    pref[i + 1] = max(pref[i], temp);
    suff[i + 1] = max(suff[i + 1], suff[i]);

    if (i - a[i] >= 0) {
      T[i - a[i]] = max(temp, T[i - a[i]]);
    }
    if (i - a[i] + m <= n) {
      suff[i - a[i] + m] = max(suff[i - a[i] + m], temp);
    }
  }
  cout << n - max(0, suff[n]) << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  size_t t;
  cin >> t;

  while (t--) {
    cin >> n >> m;

    for (int32_t i{0}; i < n; i++) {
      cin >> a[i];
      a[i]--;
    }
    solve();
  }

  return 0;
}
