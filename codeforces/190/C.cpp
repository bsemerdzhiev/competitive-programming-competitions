#include <bits/stdc++.h>
#include <csignal>

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
  sort(a, a + n, greater<int32_t>());

  // a[0] -= 1;

  int64_t ans = 0;
  int64_t ones = 0;
  int64_t to_fill = 0;
  int64_t k = 0;

  for (int32_t i = 0; i < n; i++) {
    if (a[i] == 1) {
      ones++;
    } else {
      k++;
      ans += a[i];
      to_fill += (a[i] / 2) - 1;
    }
  }
  // cout << ans << "\n";
  ans = ans + min(to_fill + (k == 1), ones);
  if (ans < 3) {
    ans = 0;
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
