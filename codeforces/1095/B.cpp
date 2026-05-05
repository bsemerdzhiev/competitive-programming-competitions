#include <bits/stdc++.h>

using namespace std;

const int32_t MOD = 998244353;
const int32_t MAXN = 2e5 + 5;

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

void solve() {
  int32_t ans = 0;
  for (int32_t i = 1; i < n; i++) {
    int32_t max_c = a[i];
    int32_t min_c = a[i];
    int32_t gcd_c = a[i];

    for (int32_t j = i - 1; j >= 0; j--) {
      max_c = max(max_c, a[j]);
      min_c = min(min_c, a[j]);
      gcd_c = __gcd(gcd_c, a[j]);

      if (max_c - min_c == gcd_c) {
        ans++;
      }
      if (gcd_c == 1) {
        break;
      }
    }
  }
  cout << ans << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int32_t t;
  cin >> t;

  while (t--) {
    cin >> n;
    for (int32_t i = 0; i < n; i++) {
      cin >> a[i];
    }
    solve();
  }

  return 0;
}
