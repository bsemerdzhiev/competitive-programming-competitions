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

int32_t n, a[2][MAXN];

bool check(int32_t x) {
  int32_t cnt[2] = {0, 0};
  bool prev = false;

  for (int32_t i = 0; i < n; i++) {
    if (a[0][i] < x && a[1][i] < x) {
      if (!prev) {
        cnt[0]++;
        prev = true;
      }
    } else if (a[0][i] >= x && a[1][i] >= x) {
      cnt[1]++;
      prev = false;
    }
  }
  return cnt[1] > cnt[0];
}

void solve() {
  int32_t l = 1, r = 2 * n;
  int32_t ans = 1;

  // cout << check(8) << "\n";

  while (l <= r) {
    int32_t middle = (l + r) >> 1;

    if (check(middle)) {
      ans = middle;
      l = middle + 1;
    } else {
      r = middle - 1;
    }
  }
  cout << ans << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  size_t t;
  cin >> t;

  while (t--) {
    cin >> n;
    for (size_t i = 0; i < n; i++) {
      cin >> a[0][i];
    }
    for (size_t i = 0; i < n; i++) {
      cin >> a[1][i];
    }
    solve();
  }

  return 0;
}
