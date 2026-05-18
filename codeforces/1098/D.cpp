#include <bits/stdc++.h>
#include <format>
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
// #pragma GCC target("avx2")

using namespace std;

const int32_t MOD = 998244353;
const int32_t MAXN = 2e6 + 5;

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

struct Point {
  int32_t x, y;

  bool operator<(const Point &other) const {
    return y < other.y || (y == other.y && x < other.x);
  }
};

int32_t n;
Point p[MAXN];
int32_t tree[MAXN];
int32_t mps[2][MAXN];

int32_t query(int32_t l, int32_t r) {
  if (l > r) {
    return 0;
  }
  return tree[r] - tree[l - 1];
}

void solve() {
  for (int32_t i = 1; i <= n; i++) {
    tree[i] = 0;
    for (size_t j = 0; j < 2; j++) {
      mps[j][i] = 0;
    }
  }

  sort(p, p + n);

  int32_t l[2] = {n, n};
  int32_t r[2] = {0, 0};

  for (int32_t i = 0; i < n; i++) {
    if (mps[0][p[i].x] == 0) {
      tree[p[i].x]++;
    }

    mps[0][p[i].x]++;

    l[0] = min(l[0], p[i].x);
    r[0] = max(r[0], p[i].x);
  }
  for (int32_t i = 1; i <= n; i++) {
    tree[i] += tree[i - 1];
  }

  int32_t prev_y = 0;

  int64_t ans = 0;

  for (size_t i = 0; i < n; i++) {
    if (prev_y != p[i].y) {
      if (l[0] < r[0] && l[1] < r[1]) {
        int32_t l_f = l[0];
        int32_t r_f = r[0] - 1;

        int32_t l_s = l[1];
        int32_t r_s = r[1] - 1;

        ans += query(max(l_f, l_s), min(r_f, r_s));
      }
    }

    mps[0][p[i].x]--;

    while (l[0] <= n && mps[0][l[0]] == 0) {
      l[0]++;
    }

    while (r[0] >= 1 && mps[0][r[0]] == 0) {
      r[0]--;
    }

    mps[1][p[i].x]++;

    l[1] = min(l[1], p[i].x);
    r[1] = max(r[1], p[i].x);

    prev_y = p[i].y;
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
    for (size_t i = 0; i < n; i++) {
      cin >> p[i].x >> p[i].y;
    }
    solve();
  }

  return 0;
}
