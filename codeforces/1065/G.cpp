#include <algorithm>
#include <bits/stdc++.h>
#include <cstdint>

using namespace std;

const int32_t MOD = int32_t(1e6) + 3;
const int32_t MAXN = 2e5 + 5;

namespace MO {
int32_t add(int64_t x, int64_t y) { return (x + y + MOD) % MOD; }
int32_t mul(int64_t x, int64_t y) { return (x * y) % MOD; }

int32_t pow(int32_t x, int32_t y) {
  int32_t result = 1;

  while (y) {
    if (y & 1) {
      result = mul(result, x);
    }
    x = mul(x, x);

    y >>= 1;
  }
  return result;
}

int32_t inv(int32_t x) { return pow(x, MOD - 2); }
}; // namespace MO

int32_t n;
int64_t a[MAXN], b[MAXN];
int32_t fact[MOD + 5];

void precalc() {
  fact[0] = 1;
  for (int32_t i = 1; i < MOD + 5; i++) {
    fact[i] = MO::mul(fact[i - 1], i);
  }
}

void solve() {
  int64_t min_ans = INT64_MAX;
  int32_t best_comb = 0;

  vector<int32_t> total_sz, denom;
  total_sz.resize(32);
  denom.resize(32);

  for (int32_t i = 0; i < 32; i++) {
    int64_t temp_ans = i;

    for (int32_t j = 0; j < 32; j++) {
      denom[j] = 1;
      total_sz[j] = 0;
    }

    for (int32_t j = 0; j < n; j++) {
      int64_t cur_a = (a[j] << i);

      if (cur_a > b[j]) {
        temp_ans = INT64_MAX;
        break;
      }

      int64_t rem = b[j] - cur_a;

      int64_t start_number = (1LL << i);
      int32_t k = 0;

      while (rem) {
        int64_t cur_c = rem / start_number;

        total_sz[k] += cur_c;
        denom[k] = MO::mul(denom[k], fact[cur_c]);

        temp_ans += cur_c;
        rem -= (cur_c)*start_number;
        start_number >>= 1;
        k++;
      }
    }
    if (temp_ans < min_ans) {
      min_ans = temp_ans;
      int32_t cur_comb = 1;
      for (int32_t j = 0; j < 32; j++) {
        if (total_sz[j] >= MOD) {
          cur_comb = 0;
          break;
        }
        cur_comb =
            MO::mul(cur_comb, MO::mul(fact[total_sz[j]], MO::inv(denom[j])));
      }
      best_comb = cur_comb;
    }
  }
  cout << min_ans << " " << best_comb << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  precalc();
  int32_t t;
  cin >> t;

  while (t--) {
    cin >> n;
    for (int32_t i = 0; i < n; i++) {
      cin >> a[i];
    }
    for (int32_t i = 0; i < n; i++) {
      cin >> b[i];
    }
    solve();
  }

  return 0;
}
