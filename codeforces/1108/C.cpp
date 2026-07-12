#include <bits/stdc++.h>
#include <map>

using namespace std;

const int32_t MOD = 1e9 + 7;
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
int32_t combs[MAXN];

void solve() {
  map<int32_t, int32_t> mm;
  for (int32_t i{0}; i < n; i++) {
    mm[a[i]]++;
  }

  int32_t prev_comb = 1;
  combs[0] = 1;

  for (int32_t i = 1; i <= n; i++) {
    combs[i] = prev_comb;
    prev_comb = MO::mul(prev_comb, 2);
  }

  int32_t ans = 1;
  for (auto x : mm) {
    ans = MO::mul(ans, combs[x.second]);
  }

  // cout << ans << "\n";

  int32_t fin_ans = ans;
  if (mm.find(-1) != mm.end())
    for (auto x : mm) {
      if (x.first == -1 || mm.find(x.first + 1) == mm.end()) {
        continue;
      }

      int32_t f1 = mm[-1] - 1;
      int32_t f2 = mm[x.first] - 1;
      int32_t f3 = mm[x.first + 1] - 1;

      if (f1 < 0 || f2 < 0 || f3 < 0) {
        continue;
      }

      int32_t temp_ans = ans;

      fin_ans = MO::add(fin_ans, temp_ans);
    }
  cout << fin_ans << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  size_t t;
  cin >> t;

  while (t--) {
    cin >> n;

    for (int32_t i{0}; i < n; i++) {
      cin >> a[i];
    }
    solve();
  }

  return 0;
}
