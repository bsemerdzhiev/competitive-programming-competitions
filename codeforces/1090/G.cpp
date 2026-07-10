#include <bits/stdc++.h>

using namespace std;

const int32_t MOD = 676767677;
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

int32_t n, m, b[MAXN];

void solve() {
  map<int32_t, vector<int32_t>> mm;

  for (int32_t i{0}; i < n; i++) {
    mm[b[i]].push_back(i);
  }

  int32_t c_av = 0;
  int32_t c_prev = 0;
  int32_t ans = 1;

  for (int32_t i{0}; i < m; i++) {
    for (auto x : mm[i]) {
      int32_t min_av = MAXN;
      if (x > 0) {
        min_av = min(b[x - 1], min_av);
      }
      if (x < n - 1) {
        min_av = min(b[x + 1], min_av);
      }

      if (min_av + 1 == b[x]) {
        ans = MO::mul(c_av, ans);
      } else if (min_av < b[x]) {
        ans = MO::mul(c_av - c_prev, ans);
      } else if (b[x] != 0 && min_av >= b[x]) {
        ans = 0;
      }
    }
    c_prev = c_av;
    c_av += mm[i].size();
  }
  cout << ans << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  size_t t;
  cin >> t;

  while (t--) {
    cin >> n >> m;

    for (int32_t i{0}; i < n; i++) {
      cin >> b[i];
    }
    solve();
  }

  return 0;
}
