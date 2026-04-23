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

int32_t n, a[MAXN], b[MAXN];

void solve() {
  int32_t ans = 0;

  for (int32_t i = 0; i < n; i++) {
    if (i == 0) {
      int32_t desired = gcd(a[i], a[i + 1]);
      if (desired != a[i]) {
        ans++;
      }
    } else if (i == n - 1) {
      int32_t desired = gcd(a[i], a[i - 1]);
      if (desired != a[i]) {
        ans++;
      }
    } else {
      int64_t desired_left = gcd(a[i], a[i - 1]);
      int64_t desired_right = gcd(a[i], a[i + 1]);

      int64_t wanted =
          desired_left * desired_right / gcd(desired_left, desired_right);

      if (wanted != a[i]) {
        ans++;
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
    for (int32_t i = 0; i < n; i++) {
      cin >> b[i];
    }
    solve();
  }

  return 0;
}
