#include <bits/stdc++.h>
#include <cstring>

using namespace std;

const int32_t MOD = 998244353;
const int32_t MAXN = 5e3 + 5;

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

string a[2];
int32_t aa[2][MAXN];
int32_t T[MAXN][MAXN];

int32_t rec(int32_t i, int32_t j) {
  if (i == a[0].length() || j == a[1].length()) {
    if (i != a[0].length() || j != a[1].length()) {
      return -MAXN;
    }
    // cout << i << " " << j << "\n";
    return 0;
  }
  if (T[i][j] != -1) {
    return T[i][j];
  }

  int32_t comb_ans = -MAXN;
  if (aa[0][i] == aa[1][j]) {
    comb_ans = 1 + rec(i + 1, j + 1);
  }

  return T[i][j] = max(max(rec(i + 1, j), rec(i, j + 1)), comb_ans);
}

void solve() {
  for (int32_t z = 0; z < 2; z++) {
    aa[z][0] = a[z][0] - '0';
    for (int32_t i = 1; i < a[z].length(); i++) {
      aa[z][i] = (aa[z][i - 1] + (a[z][i] - '0')) % 10;
    }
  }
  for (int32_t i{0}; i < a[0].length(); i++) {
    for (int32_t j{0}; j < a[1].length(); j++) {
      T[i][j] = -1;
    }
  }

  cout << max(-1, rec(0, 0)) << "\n";

  return;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  size_t t;
  cin >> t;

  while (t--) {

    cin >> a[0];
    cin >> a[1];
    solve();
  }

  return 0;
}
