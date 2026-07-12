#include <bits/stdc++.h>

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

int32_t n;
int64_t ans[55];

void solve() {
  if (n == 2) {
    cout << "-1\n";
    return;
  }
  ans[1] = 1;
  ans[2] = 2;

  int64_t sum = 3;

  for (int32_t i = 3; i <= n; i++) {
    ans[i] = sum;
    sum += sum;
  }
  for (int32_t i = 1; i <= n; i++) {
    cout << ans[i] << " ";
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
    solve();
  }

  return 0;
}
