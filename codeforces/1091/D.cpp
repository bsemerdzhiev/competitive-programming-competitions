#include <bits/stdc++.h>
#include <iostream>
#include <semaphore>

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

int32_t n, k, a[MAXN], p[MAXN];

void solve() {
  int32_t cnt = 0;
  int32_t z = 0;

  int32_t total_s = 0;
  int32_t prev = a[p[0]];
  int32_t max_s = 0;

  for (int32_t i = 0; i < n; i++) {
    if (a[i] != prev) {
      cnt++;
    }
    prev = a[i];

    if (z < k && p[z] == i) {
      total_s += cnt;
      max_s = max(max_s, cnt);
      cnt = 0;

      z++;
    }
  }
  if (a[p[0]] != prev) {
    cnt++;
  }
  total_s += cnt;
  max_s = max(max_s, cnt);

  int32_t ans = max(total_s / 2, max_s);
  cout << ans << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int32_t t;
  cin >> t;

  while (t--) {
    cin >> n >> k;
    for (int32_t i = 0; i < n; i++) {
      cin >> a[i];
    }
    for (int32_t i = 0; i < k; i++) {
      cin >> p[i];
      p[i]--;
    }
    solve();
  }

  return 0;
}
