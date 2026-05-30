#include <bits/stdc++.h>
#include <cstdint>

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

int64_t n, a[MAXN];

void solve() {
  int64_t ans = INT64_MAX;
  int64_t excess = 0;

  for (int32_t i = 0; i < n; i++) {
    if (excess + a[i] < ans) {
      int64_t total = (ans * i + (a[i] + excess));

      int64_t cur_height = min(ans, total / (i + 1));

      ans = cur_height;

      excess = total - (cur_height * (i + 1));
    } else {
      excess += a[i] - ans;
    }
    cout << ans << " ";
  }

  cout << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  size_t t;
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
