#include <bits/stdc++.h>

using namespace std;

const int32_t MOD = 998244353;
const int32_t MAXN = 2e3 + 5;
const int32_t MAXK = 1e7 + 5;

namespace MO {
int32_t add(int64_t x, int64_t y) { return ((x) + (y) + MOD) % MOD; }
int32_t mul(int64_t x, int64_t y) { return ((x) * (y)) % MOD; }

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

mt19937 rnd(312312);
int32_t n, a[MAXN], b[MAXN];

struct frac {
  int64_t x, y;

  bool operator<(frac other) const { return x * other.y > y * other.x; }
};

void solve() {
  vector<frac> vv;
  for (int32_t i = 1; i < n; i++) {
    for (int32_t j = 0; j < i; j++) {
      vv.push_back({a[i], a[j]});
    }
  }
  sort(vv.begin(), vv.end());

  int32_t ans = 0;

  for (int32_t i = 0; i < n; i++) {
    for (int32_t j = 0; j < n; j++) {
      if (i == j)
        continue;

      ans = MO::add(ans, vv.size() - distance(vv.begin(),
                                              upper_bound(vv.begin(), vv.end(),
                                                          frac{b[i], b[j]})));
    }
  }

  ans = MO::mul(ans, MO::inverse(MO::mul(n, n - 1)));

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
