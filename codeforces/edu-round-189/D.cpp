
#include <bits/stdc++.h>

using namespace std;

const int32_t MOD = 998244353;
const int32_t MAXN = 2e5 + 5;

namespace MO {
int32_t add(int64_t x, int64_t y) { return ((x % MOD) + (y % MOD)) % MOD; }
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

int64_t n, x;

void solve() {
  int64_t ind = x % 4;
  int64_t grp = x / 4;

  int64_t fin_grp = n / 4;
  int64_t fin_el = n % 4;

  int64_t to_left_ones = (grp) + (ind > 1);
  int64_t to_left_zeros = (grp) + 1;

  int64_t to_right_ones = 0;
  int64_t to_right_zeros = 0;

  if (fin_grp == grp) {
    to_right_ones = (ind <= 1 && fin_el >= 1);
    to_right_zeros = (fin_el == 3);

  } else {
    to_right_ones = (ind <= 1) + (fin_grp - grp - 1) + (fin_el >= 1);
    to_right_zeros = (ind <= 3) + (fin_grp - grp - 1) + (fin_el == 3);
  }
  // cout << to_right_ones << "\n";
  cout << MO::add(MO::mul(to_left_zeros, to_right_zeros),
                  MO::mul(to_left_ones, to_right_ones))
       << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int32_t t;
  cin >> t;

  while (t--) {
    cin >> n >> x;

    solve();
  }

  return 0;
}
