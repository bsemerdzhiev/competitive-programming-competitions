#include <bits/stdc++.h>
#include <iostream>

using namespace std;

const int32_t MOD = 998244353;
const int32_t MAXN = 5e5 + 5;

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

int32_t n, a[2][MAXN];
int32_t pos[2][MAXN];
int32_t longest[MAXN];

void solve() {

  for (int32_t j = 0; j < 2; j++) {
    for (int32_t i = 1; i <= n + 1; i++) {
      pos[j][i] = n;
    }
  }
  longest[n] = n - 1;

  int64_t answer = 0;
  for (int32_t i = n - 1; i >= 0; i--) {
    pos[0][a[0][i]] = i;
    pos[1][a[1][i]] = i;

    int32_t nxt_f = pos[0][a[0][i] + 1];
    int32_t nxt_s = pos[1][a[1][i] + 1];

    int32_t safe = min(nxt_f, nxt_s) - 1;

    if (a[0][i] == a[1][i]) {
      if (nxt_f == nxt_s) {
        longest[i] = longest[nxt_f];
      } else {
        longest[i] = safe;
      }
    } else {
      longest[i] = i;
    }

    nxt_f = pos[0][1];
    nxt_s = pos[1][1];

    safe = min(nxt_f, nxt_s) - 1;

    if (nxt_f == nxt_s) {
      int64_t cur_len = (longest[nxt_f] - i + 1);
      answer += cur_len;
    } else {
      answer += max(0, safe - i + 1);
    }
  }

  cout << answer << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int32_t t;
  cin >> t;

  while (t--) {
    cin >> n;

    for (int32_t i = 0; i < n; i++) {
      cin >> a[0][i];
    }

    for (int32_t i = 0; i < n; i++) {
      cin >> a[1][i];
    }
    solve();
  }

  return 0;
}
