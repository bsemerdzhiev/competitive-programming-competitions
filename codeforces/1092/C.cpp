#include <bits/stdc++.h>
#include <cstdint>

using namespace std;

const int32_t MOD = 998244353;
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

int64_t n, k, p, q;
int64_t a[MAXN], sum[3][MAXN];

void solve() {
  if (p > q) {
    swap(p, q);
  }

  int64_t best_ans = INT64_MAX;

  for (int32_t i = 1; i <= n; i++) {
    sum[1][i] = sum[1][i - 1] + (a[i] % p);
    sum[2][i] = sum[2][i - 1] + ((a[i] % q) % p);
  }

  int64_t answer = 0;
  for (int32_t i = 1; i <= n; i++) {
    answer += min(a[i] % p, (a[i] % q) % p);
    sum[0][i] = answer;
  }
  for (int32_t i = k; i <= n; i++) {
    best_ans = min(best_ans, (answer - (sum[0][i] - sum[0][i - k])) +
                                 min(sum[1][i] - sum[1][i - k],
                                     sum[2][i] - sum[2][i - k]));
  }

  cout << best_ans << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int32_t t;
  cin >> t;

  while (t--) {
    cin >> n >> k >> p >> q;

    for (int32_t i = 1; i <= n; i++) {
      cin >> a[i];
    }

    solve();
  }

  return 0;
}
