#include <bits/stdc++.h>
#include <functional>

using namespace std;

const int32_t MOD = 998244353;
const int32_t MAXN = 3e3 + 5;

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

struct Parabole {
  int64_t a, b, c;

  bool intersects(const Parabole &rhs) const {
    if (a == rhs.a) {
      if (b == rhs.b) {
        return c == rhs.c;
      }
      return true;
    }

    int64_t res = (rhs.b - b) * (rhs.b - b) - 4 * (a - rhs.a) * (c - rhs.c);

    return res >= 0;
  }
};

int32_t n;
Parabole f[MAXN];
bool mark[MAXN][MAXN];

void solve() {
  vector<int32_t> good_cnt(n, 0);

  for (int32_t i{0}; i < n; i++) {
    mark[i][i] = 0;
    for (int32_t j{i + 1}; j < n; j++) {
      if (f[i].intersects(f[j])) {
        mark[i][j] = mark[j][i] = 1;
      } else {
        mark[i][j] = mark[j][i] = 0;
        good_cnt[i]++;
        good_cnt[j]++;
      }
    }
  }

  vector<bool> vis(n, 0);
  vector<int32_t> save_cnt = good_cnt;

  for (int32_t i{0}; i < n; i++) {
    for (int32_t z{0}; z < n; z++) {
      vis[z] = 0;
    }

    vis[i] = 1;
    for (int32_t z{0}; z < n; z++) {
      if (mark[i][z]) {
        vis[z] = 1;
      }
    }

    int32_t ans = 1;

    for (int32_t k{0}; k < n - 1; k++) {
    }
    cout << ans << " ";
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
      cin >> f[i].a >> f[i].b >> f[i].c;
    }
    solve();
  }

  return 0;
}
