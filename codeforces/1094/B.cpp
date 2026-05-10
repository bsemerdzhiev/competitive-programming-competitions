#include <bits/stdc++.h>
#include <queue>

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

int32_t n, m;
int32_t a[MAXN], b[MAXN];

void solve() {
  priority_queue<int32_t> vv[2];
  for (int32_t i = 0; i < n; i++) {
    vv[i % 2].push(a[i]);
  }
  bool have_popped[2] = {0, 0};

  for (int32_t i = 0; i < m; i++) {
    if (!vv[b[i] % 2].empty()) {
      if (vv[b[i] % 2].top() > 0 || !have_popped[b[i] % 2]) {
        vv[b[i] % 2].pop();
      }

      have_popped[b[i] % 2] = 1;
    }
  }
  int64_t ans = 0;

  for (int32_t i = 0; i < 2; i++) {
    while (!vv[i].empty()) {
      ans += vv[i].top();
      vv[i].pop();
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
    cin >> n >> m;
    for (int32_t i = 0; i < n; i++) {
      cin >> a[i];
    }

    for (int32_t i = 0; i < m; i++) {
      cin >> b[i];
      b[i]--;
    }
    solve();
  }

  return 0;
}
