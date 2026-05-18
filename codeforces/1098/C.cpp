#include <algorithm>
#include <bits/stdc++.h>
#include <cstdint>
#include <ranges>

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

int64_t n, b[MAXN];
int64_t a;

int64_t rec(vector<int32_t> dg, int32_t k, int64_t cur_numb, int32_t strat) {
  if (k == dg.size()) {
    return abs(cur_numb - a);
  }

  int64_t ans = INT64_MAX;
  if (strat == 0) {
    ans = rec(dg, k + 1, cur_numb * 10LL + b[n - 1], strat);
  } else if (strat == 1) {
    int64_t av_dig[3] = {-1, -1, -1};

    for (size_t i = 0; i < n; i++) {
      if (b[i] < dg[k]) {
        av_dig[0] = b[i];
      } else if (b[i] > dg[k]) {
        av_dig[2] = b[i];
        break;
      } else {
        av_dig[1] = b[i];
      }
    }
    for (size_t i = 0; i < 3; i++) {
      if (av_dig[i] != -1) {
        ans = min(ans, rec(dg, k + 1, cur_numb * 10LL + av_dig[i], i));
      }
    }
  } else {
    ans = rec(dg, k + 1, cur_numb * 10LL + b[0], strat);
  }
  return ans;
}

void solve() {
  int64_t c_a = a;

  vector<int32_t> dg;
  while (c_a > 0) {
    dg.push_back(c_a % 10);
    c_a /= 10;
  }
  if (dg.size() == 0) {
    dg.push_back(0);
  }

  ranges::reverse(dg);

  int64_t ans = INT64_MAX;

  int32_t to_use = -1;
  for (size_t i = 0; i < n; i++) {
    if (b[i] != 0) {
      to_use = b[i];
      break;
    }
  }
  if (to_use != -1) {
    ans = min(ans, rec(dg, 0, to_use, 2));
  }

  ans = min(ans, rec(dg, 0, 0, 1));
  if (dg.size() > 1) {
    ans = min(ans, rec(dg, 1, 0, 0));
  }

  cout << ans << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int32_t t;
  cin >> t;

  while (t--) {
    cin >> a >> n;

    for (size_t i = 0; i < n; i++) {
      cin >> b[i];
    }
    solve();
  }

  return 0;
}
