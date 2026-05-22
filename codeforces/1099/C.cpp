#include <bits/stdc++.h>
#include <cstdint>
#include <unordered_map>

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

int32_t n, a[MAXN];

void solve() {
  unordered_map<int32_t, pair<int32_t, int32_t>> mm;
  unordered_map<int32_t, int32_t> cur_mm;
  int32_t ans = INT32_MAX;

  for (int32_t i = 0; i < n; i++) {
    int32_t cur_numb = a[i];
    int32_t k = 0;
    cur_mm.clear();

    while (cur_numb) {
      for (int32_t z = 0; z < ((cur_numb & 1) + 1); z++) {
        if (!cur_mm.contains(cur_numb + z)) {
          cur_mm[cur_numb + z] = (k + z);
        } else {
          cur_mm[cur_numb + z] = min(cur_mm[cur_numb + z], k + z);
        }
      }
      if (cur_numb == 1) {
        break;
      }
      if (cur_numb & 1) {
        cur_numb++;
        k++;
      }
      k++;
      cur_numb >>= 1;
    }

    for (auto x : cur_mm) {
      mm[x.first].first++;
      mm[x.first].second += x.second;

      if (mm[x.first].first == n) {
        ans = min(ans, mm[x.first].second);
      }
    }
  }
  cout << ans << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int32_t t;
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
