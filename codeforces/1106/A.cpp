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

int32_t n, c, a[MAXN], b[MAXN];

void solve() {
  int64_t ans = 0;
  for (int32_t i{0}; i < n; i++) {
    if (a[i] < b[i]) {
      ans = INT64_MAX;
      break;
    }
    ans += a[i] - b[i];
  }
  sort(a, a + n);
  sort(b, b + n);

  int64_t second_ans = c;
  for (int32_t i{0}; i < n; i++) {
    if (a[i] < b[i]) {
      second_ans = INT64_MAX;
      break;
    }
    second_ans += a[i] - b[i];
  }
  ans = min(ans, second_ans);

  if (ans == INT64_MAX) {
    ans = -1;
  }
  cout << ans << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  size_t t;
  cin >> t;

  while (t--) {
    cin >> n >> c;

    for (int32_t i{0}; i < n; i++) {
      cin >> a[i];
    }

    for (int32_t i{0}; i < n; i++) {
      cin >> b[i];
    }
    solve();
  }

  return 0;
}
