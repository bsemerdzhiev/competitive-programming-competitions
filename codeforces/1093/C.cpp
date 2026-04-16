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

const int32_t MAX_SUM = 3e8;

pair<int32_t, int32_t> calc(const int64_t wanted_sum, int32_t p, int32_t q) {
  for (int64_t i = 3; i <= sqrt(wanted_sum) + 10; i += 2) {
    if (wanted_sum % i == 0) {
      int64_t rem = wanted_sum / i;
      if (rem % 2 == 1 && rem >= 1) {
        int64_t n = (i - 1) / 2;
        int64_t m = (rem - 1) / 2;

        if (p >= abs(n - m)) {
          return {n, m};
        }
      }
    }
  }
  return {-1, -1};
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int32_t t;
  cin >> t;

  int32_t n, m;
  while (t--) {
    cin >> n >> m;

    int64_t wanted_sum = n + 2 * m;
    wanted_sum = wanted_sum * 2 + 1;

    pair<int32_t, int32_t> res = calc(wanted_sum, n, m);

    if (res.first == -1) {
      cout << "-1\n";
    } else {
      cout << res.first << " " << res.second << "\n";
    }
  }
  return 0;
}
