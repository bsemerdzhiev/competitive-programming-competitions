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

int32_t n, a[MAXN];

void solve() {
  int mxs[2] = {0, 0};
  int mns[2] = {MAXN, MAXN};

  for (int32_t i = 0; i < n; i++) {

    mxs[a[i] % 2] = max(mxs[a[i] % 2], a[i]);
    mns[a[i] % 2] = min(mns[a[i] % 2], a[i]);
  }

  int mx_rolling[2] = {0, 0};
  int mn_rolling[2] = {MAXN, MAXN};

  for (int32_t i = n - 1; i >= 0; i--) {
    int k = a[i] % 2;

    mx_rolling[k] = max(mx_rolling[k], a[i]);
    mn_rolling[k] = min(mn_rolling[k], a[i]);

    if (mn_rolling[k] == a[i]) {
      continue;
    }

    if (mxs[k ^ 1] < a[i] && mns[k ^ 1] > mn_rolling[k]) {
      cout << "NO\n";
      return;
    }
  }
  cout << "YES\n";
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
