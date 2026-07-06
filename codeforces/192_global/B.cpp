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

int32_t n, a[MAXN];

bool solve() {

  multiset<int32_t> ss;
  int32_t cnt = 0;
  int32_t b[4] = {0};

  for (int32_t i{0}; i < n - 1; i++) {
    b[a[i]]++;

    ss.insert(b[1] + b[2] - b[3]);
  }
  b[1] = b[2] = b[3] = 0;

  for (int32_t i{0}; i < n - 2; i++) {
    b[a[i]]++;
    ss.erase(ss.find(b[1] + b[2] - b[3]));

    if (b[1] >= b[2] + b[3] && ss.size() > 0) {
      int32_t from_s = *ss.rbegin();
      // cout << i << " " << from_s << " " << "\n";

      if (from_s - (b[1] + b[2] - b[3]) >= 0) {
        return true;
      }
    }
  }
  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  size_t t;
  cin >> t;

  while (t--) {
    cin >> n;
    for (int32_t i{0}; i < n; i++) {
      cin >> a[i];
    }
    cout << (solve() ? "YES" : "NO") << "\n";
  }

  return 0;
}
