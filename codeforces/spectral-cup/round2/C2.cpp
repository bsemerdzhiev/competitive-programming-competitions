#include <bits/stdc++.h>
#include <cstdint>

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

int64_t n, a[MAXN];
int64_t pref_sum[MAXN], pref_sum_rev[MAXN];

void solve() {
  pref_sum[0] = abs(a[0]);
  for (int32_t i = 1; i < n; i++) {
    pref_sum[i] = pref_sum[i - 1] + abs(a[i]);
  }
  pref_sum_rev[n - 1] = a[n - 1];
  for (int32_t i = n - 2; i >= 0; i--) {
    pref_sum_rev[i] = pref_sum_rev[i + 1] + a[i];
  }
  pref_sum_rev[n] = 0;

  int64_t ans = pref_sum_rev[0];
  int32_t chosen_ind = -1;
  for (int32_t i = 1; i < n; i++) {
    if (a[i] < 0) {
      continue;
    }

    int64_t cur_sum = pref_sum[i - 1] - a[i] + pref_sum_rev[i + 1];

    if (cur_sum > ans) {
      ans = cur_sum;
      chosen_ind = i;
    }
  }

  vector<int32_t> moves;
  if (chosen_ind != -1) {
    int32_t cur_sign = 1;
    for (int32_t i = chosen_ind - 1; i >= 0; i--) {
      if (a[i] * cur_sign > 0) {
        moves.push_back(i);
        cur_sign *= -1;
      }
    }
    moves.push_back(chosen_ind);
  }
  cout << moves.size() << "\n";
  for (auto x : moves) {
    cout << x + 1 << " ";
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

    for (size_t i = 0; i < n; i++) {
      cin >> a[i];
    }
    solve();
  }

  return 0;
}
