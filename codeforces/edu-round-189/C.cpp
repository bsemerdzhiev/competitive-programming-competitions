#include <bits/stdc++.h>

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

int32_t n;
string a[2];

int32_t T[MAXN];

void solve() {
  T[0] = 0;

  a[0] = "#" + a[0];
  a[1] = "#" + a[1];

  for (int32_t i = 1; i <= n; i++) {
    if (i >= 2) {
      T[i] = T[i - 2] + (a[0][i] != a[0][i - 1]) + (a[1][i] != a[1][i - 1]);
    } else {
      T[i] = MAXN;
    }

    T[i] = min(T[i], T[i - 1] + (a[0][i] != a[1][i]));
  }
  cout << T[n] << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int32_t t;
  cin >> t;

  while (t--) {
    cin >> n;

    cin >> a[0];
    cin >> a[1];

    solve();
  }

  return 0;
}
