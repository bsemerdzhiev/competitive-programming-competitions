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

int64_t n, a[MAXN], c[MAXN];
string s;

void solve() {
  int64_t cur_sum = 0;

  c[0] = 0;
  int32_t last_changable = 0;
  const int64_t MIN_POS = -2e12;

  for (int32_t i = 1; i <= n; i++) {
    cur_sum += a[i];
    if (s[i] == '0') {
      last_changable = i;
    }

    if (c[i] != c[i - 1]) {
      if (cur_sum != c[i]) {
        a[last_changable] += c[i] - cur_sum;
        cur_sum = c[i];
      }
    } else {
      if (cur_sum > c[i]) {
        if (last_changable != 0) {
          a[last_changable] += MIN_POS;
          cur_sum += MIN_POS;
        }
      }
    }
  }
  // for (int32_t i = 1; i <= n; i++) {
  //   cout << a[i] << " ";
  // }
  // cout << "\n";
  cur_sum = 0;
  int64_t max_sum = MIN_POS;
  for (int32_t i = 1; i <= n; i++) {
    cur_sum += a[i];
    max_sum = max(max_sum, cur_sum);

    // cout << i << " " << cur_sum << " " << max_sum << "\n";
    if (max_sum != c[i]) {
      cout << "NO\n";
      return;
    }
  }
  cout << "YES\n";
  for (int32_t i = 1; i <= n; i++) {
    cout << a[i] << " ";
  }
  cout << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  size_t t;
  cin >> t;

  while (t--) {
    cin >> n;
    cin >> s;
    s = "#" + s;

    for (size_t i = 1; i <= n; i++) {
      cin >> a[i];
    }

    for (size_t i = 1; i <= n; i++) {
      cin >> c[i];
    }
    solve();
  }

  return 0;
}
