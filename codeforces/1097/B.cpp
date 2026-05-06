#include <algorithm>
#include <bits/stdc++.h>
#include <cstdint>
#include <mutex>
#include <unordered_map>
#include <vector>

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
  int mx = 0;

  vector<int32_t> vv;
  for (int32_t i = 0; i < n; i++) {
    if (a[i] > a[mx]) {
      mx = i;
    }
    vv.push_back(a[i]);
  }
  // swap(a[mx], a[0]);

  sort(vv.begin(), vv.end());

  vv.erase(unique(vv.begin(), vv.end()), vv.end());

  int64_t ans = 0;

  for (int32_t i = 0; i < vv.size(); i++) {
    if (vv[i] == i) {
      int64_t cur = 1LL * (vv[i] + 2) * (vv[i] + 1) / 2;
      if (i == vv.size() - 1) {
        cur -= vv[i];
        cur += 1LL * (vv[i] + 1) * (n - (i + 1));
      } else {
        cur += 1LL * (vv[i] + 1) * (n - (i + 2));
      }
      ans = max(ans, cur);
    } else {
      break;
    }
  }

  ans += a[mx] * n;

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
