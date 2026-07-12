#include <bits/stdc++.h>

using namespace std;

const int32_t MOD = 998244353;
const int32_t MAXN = (1 << 20) + 1;
const int64_t INF = 1e17;

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

int32_t n, a[MAXN];
int64_t calced[MAXN][21];

void solve() {
  int64_t ans = INF;

  for (int32_t z{0}; z < 21; z++) {
    int64_t temp_ans = 0;
    for (int32_t i{0}; i < n; i++) {
      temp_ans += calced[a[i]][z];
    }
    temp_ans -= z * n;

    ans = std::min(ans, temp_ans + z);
  }

  cout << ans << "\n";
}

void precalc() {
  vector<int32_t> vv(21, 0);
  vector<int32_t> vv_times(21, 0);

  for (int32_t i{MAXN - 1}; i >= 1; i--) {
    int32_t numb = i;
    int32_t cnt = 0;
    int32_t cnt_before_one = -1;

    while (numb) {
      if (numb & 1) {
        numb ^= 1;
        if (cnt_before_one == -1)
          cnt_before_one = cnt;
      } else {
        numb >>= 1;
      }
      cnt++;
    }
    vv[cnt_before_one] = i;
    vv_times[cnt_before_one] = cnt;

    int64_t best = INF;
    for (int32_t z{20}; z >= 0; z--) {
      calced[i][z] = std::min(best, int64_t((vv[z] - i) + vv_times[z]));
      best = std::min(best, calced[i][z]);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  size_t t;
  cin >> t;

  precalc();

  while (t--) {
    cin >> n;

    for (int32_t i{0}; i < n; i++) {
      cin >> a[i];
    }
    solve();
  }

  return 0;
}
