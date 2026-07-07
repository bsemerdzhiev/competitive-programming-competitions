#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

const int32_t MOD = 998244353;
const int32_t MAXN = 2e5 + 5;
const int64_t INF = 1e18;

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

void solve() {
  int32_t max_el = max_element(a, a + n) - a;

  // cout << max_el << "\n";
  vector<int64_t> ls(n, 0), rs(n, 0);

  stack<pair<int64_t, int64_t>> ss;
  ss.push({INF, 0});

  for (int32_t i{1}; i < n; i++) {
    int32_t cur_i = (max_el + i) % n;

    int64_t cur_s = ls[cur_i] + a[cur_i], br = 1;

    while (ss.top().first <= a[cur_i]) {
      cur_s += (a[cur_i] - ss.top().first) * ss.top().second;
      br += ss.top().second;

      ss.pop();
    }
    ls[(cur_i + 1) % n] = cur_s;
    ss.push({a[cur_i], br});
  }

  ss = stack<pair<int64_t, int64_t>>();
  ss.push({INF, 0});

  for (int32_t i{1}; i < n; i++) {
    int32_t cur_i = (max_el - i + n) % n;

    int64_t cur_s = rs[(cur_i + 1) % n] + a[cur_i], br = 1;

    while (ss.top().first <= a[cur_i]) {
      cur_s += (a[cur_i] - ss.top().first) * ss.top().second;
      br += ss.top().second;

      ss.pop();
    }
    rs[cur_i] = cur_s;
    ss.push({a[cur_i], br});
  }

  for (int32_t i{0}; i < n; i++) {
    cout << ls[i] + rs[i] << " ";
  }
  cout << "\n";
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
