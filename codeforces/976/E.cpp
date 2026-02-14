#include <bits/stdc++.h>

using namespace std;

const int32_t MOD = 1e9 + 7;
const int32_t MAXN = 2e5 + 5;

namespace MO {
int32_t add(int64_t x, int64_t y) { return (x + y + MOD) % MOD; }
int32_t mul(int64_t x, int64_t y) { return (x * y) % MOD; }

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

int32_t n, a[MAXN], p[MAXN];

int32_t dp[2][1 << 10];

void solve() {
  for (int32_t i = 0; i < 2; i++) {
    for (int32_t j = 0; j < (1 << 10); j++) {
      dp[i][j] = 0;
    }
  }

  int32_t inv_n = MO::inverse(10'000);
  dp[0][a[0]] = MO::mul(p[0], inv_n);
  dp[0][0] = MO::add(1, -MO::mul(p[0], inv_n));
  int32_t k = 1;
  for (int32_t i = 1; i < n; i++) {
    for (int32_t j = 0; j < (1 << 10); j++) {
      dp[k][j] = MO::mul(dp[k ^ 1][j ^ a[i]], MO::mul(p[i], inv_n));
      dp[k][j] = MO::add(
          dp[k][j], MO::mul(dp[k ^ 1][j], MO::add(1, -MO::mul(p[i], inv_n))));
    }
    k ^= 1;
  }

  int32_t answer = 0;
  for (int32_t i = 0; i < (1 << 10); i++) {
    answer = MO::add(answer, MO::mul(dp[k ^ 1][i], MO::mul(i, i)));
  }
  cout << answer << "\n";
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
      cin >> p[i];
    }
    solve();
  }

  return 0;
}
