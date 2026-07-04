#include <bits/stdc++.h>

using namespace std;

const int32_t MOD = 998244353;
const int32_t MAXN = 5e2 + 5;

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
int16_t T[2][MAXN][MAXN];

void solve() {
  for (int32_t i{0}; i < 2; i++) {
    for (int32_t j{0}; j < MAXN; j++) {
      for (int32_t z{0}; z < MAXN; z++) {
        T[i][j][z] = 4 * MAXN;
      }
    }
  }

  int16_t ans = 0;
  T[0][0][0] = 0;

  bool k = 0;
  for (int32_t i{1}; i <= n; i++) {
    for (int16_t w{0}; w <= i; w++) {
      for (int16_t pref{0}; pref <= i; pref++) {
        if (a[i] != 'T') {
          T[k ^ 1][w + 1][pref + 1] = min(
              T[k ^ 1][w + 1][pref + 1], max(T[k][w][pref], int16_t(pref + 1)));
        }
        if (a[i] != 'F') {
          T[k ^ 1][w][max(pref - 1, 0)] =
              min(T[k][w][pref], T[k ^ 1][w][max(pref - 1, 0)]);
        }
      }
    }
    k ^= 1;
  }
  for (int16_t i{0}; i <= n; i++) {
    for (int16_t j{0}; j <= n; j++) {
      ans = max(ans, int16_t(i - T[k][i][j]));
    }
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
    a = "#" + a;

    solve();
  }

  return 0;
}
