#include <algorithm>
#include <bits/stdc++.h>
#include <functional>

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

int32_t n, d, a[MAXN * 2];
int64_t pref[MAXN * 2];

void solve() {
  vector<pair<int32_t, int32_t>> vv;

  pref[0] = a[0];
  for (int32_t i{1}; i < 2 * n; i++) {
    pref[i] = pref[i - 1] + int64_t(a[i]);
  }

  int64_t ans = 0;
  for (int32_t i{d}; i < n + d; i++) {
    int64_t sum =
        ((2 * d + 1) * a[i]) - (pref[i + d] - (i == d ? 0 : pref[i - d - 1]));
    // cout << (i % n) << " " << sum << "\n";

    if (sum > 0) {
      ans += sum;
    }
  }

  // for (int32_t i = 0; i < n; i++) {
  //   int64_t cur_ans = 0;
  //   int32_t end_ind = (i + d) % n;
  //
  //   for (int32_t j{(i - d + n) % n};; j = (j + 1) % n) {
  //     cur_ans += a[i] - a[j];
  //
  //     if (j == end_ind) {
  //       break;
  //     }
  //   }
  //   if (cur_ans > 0) {
  //     ans += cur_ans;
  //   }
  // }

  cout << ans << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  size_t t;
  cin >> t;

  while (t--) {
    cin >> n >> d;

    for (int32_t i{0}; i < n; i++) {
      cin >> a[i];
      a[i + n] = a[i];
    }
    solve();
  }

  return 0;
}
