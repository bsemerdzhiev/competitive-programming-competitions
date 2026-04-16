#include <bits/stdc++.h>
#include <cstdint>
#include <iostream>

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

int64_t n;

void solve() {
  int32_t cnt = 0;
  for (int64_t p = 2; p < 40; p++) {
    for (int64_t b = 1; b <= sqrt(n) + 10; b++) {
      bool to_break_earlier = false;
      for (int32_t z = 0; z < (p == 2 ? 2 : 1); z++) {
        int64_t to_use = b;

        if (z == 1) {
          if (n % b != 0) {
            break;
          }
          to_use = (n / b) - 1;
        }
        if (to_use <= 1 || (z == 1 && to_use <= sqrt(n) + 10))
          continue;

        int64_t first_term = 0;
        int64_t mult = 1;

        for (int32_t i = 0; i < p; i++) {
          first_term += mult;
          if (first_term > n) {
            break;
          }

          mult *= to_use;
        }
        if (first_term > n) {
          to_break_earlier = true;
          continue;
        }
        if (n % first_term != 0) {
          continue;
        }

        int64_t rem = n / first_term;
        int64_t pp = pow(to_use, p);

        bool not_valid = false;
        while (rem > 0) {
          int64_t nmb = rem % pp;
          if (nmb >= to_use) {
            not_valid = true;
            break;
          }

          rem /= pp;
        }

        if (!not_valid) {
          cnt++;
        }
      }
      if (to_break_earlier) {
        break;
      }
    }
  }
  cout << cnt << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int32_t t;
  cin >> t;

  while (t--) {
    cin >> n;

    solve();
  }

  return 0;
}
