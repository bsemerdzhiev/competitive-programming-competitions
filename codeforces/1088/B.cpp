#include <bits/stdc++.h>

using namespace std;

const int32_t MOD = 676767677;
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

int32_t x, y;

void solve() {
  int32_t ans = 0;
  int32_t orig_x = x, orig_y = y;
  if (x > y) {
    x -= y;
    for (int32_t i = 1; i <= x; i++) {
      if (x % i == 0) {
        ans++;
      }
    }
  } else {
    y -= x;
    for (int32_t i = 1; i <= y; i++) {
      if (y % i == 0) {
        ans++;
      }
    }
  }
  cout << max(1, ans) << "\n";

  for (int32_t i = 0; i < orig_x; i++) {
    cout << "1 ";
  }
  for (int32_t i = 0; i < orig_y; i++) {
    cout << "-1 ";
  }
  cout << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int32_t t;
  cin >> t;

  while (t--) {
    cin >> x >> y;

    solve();
  }

  return 0;
}
