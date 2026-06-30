#include <bits/stdc++.h>
#include <vector>

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

void solve() {
  int32_t ans = -1;
  int32_t cur_n = n;

  for (int32_t i{2}; i <= sqrt(n); i++) {
    if (cur_n % i == 0) {
      ans++;
      int32_t br = 0;

      while (cur_n % i == 0) {
        cur_n /= i;
        ans++;
      }
    }
  }
  if (cur_n > 1) {
    ans += 2;
  }
  cout << ans << "\n";
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
