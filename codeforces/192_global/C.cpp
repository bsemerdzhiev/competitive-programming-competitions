#include <bits/stdc++.h>

using namespace std;

const int32_t MOD = 998244353;
const int32_t MAXN = 3e5 + 5;

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

int32_t n, k, a[MAXN];

void solve() {
  vector<int32_t> vv;

  int32_t cnt = 1;
  int64_t sm = 0;

  for (int32_t i{1}; i < n; i++) {
    if (a[i] != a[i - 1]) {
      sm += cnt;
      vv.push_back(cnt);
      cnt = 0;
    }
    cnt++;
  }
  sm += cnt;
  vv.push_back(cnt);
  sort(vv.begin(), vv.end());

  int32_t ans = 0;

  int32_t br = vv.size();

  for (int32_t i{0}; i < vv.size(); i++) {

    int64_t new_sum = sm - (1LL * (vv[i] - 1) * br);

    if (new_sum <= k && (k - new_sum) % br == 0) {
      ans++;
    }

    int32_t new_i = i;
    for (int32_t j{i}; j < vv.size(); j++) {
      if (vv[i] == vv[j]) {
        br--;
        sm -= vv[j];
        new_i = j;
      } else {
        break;
      }
    }
    i = new_i;
  }

  cout << ans << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  size_t t;
  cin >> t;

  while (t--) {
    cin >> n >> k;
    for (int32_t i{0}; i < n; i++) {
      cin >> a[i];
    }
    solve();
  }

  return 0;
}
