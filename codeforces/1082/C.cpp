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
string a;

void solve() {
  a = "#" + a;

  int32_t sums[2] = {0, 0};
  int32_t bracket_sum = 0;

  int32_t left_ptr = 0;

  int32_t ans = 0;
  int32_t p = 1;
  for (int32_t i{1}; i <= n; i++) {
    if (bracket_sum < 2) {
      sums[0] = 0;
    }

    if (a[i] == ')') {
      bracket_sum--;

      ans = MO::add(ans, MO::add(MO::add(sums[0], sums[1]), 1));

      sums[1] = MO::add(sums[1], sums[1] + sums[0] + 1);

    } else {
      bracket_sum++;

      ans = MO::add(ans, p);

      sums[0] = MO::add(sums[0], sums[0] + sums[1] + 1);
    }
    p = MO::mul(p, 2);
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
    cin >> a;

    solve();
  }

  return 0;
}
