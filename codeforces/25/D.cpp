#include <bits/stdc++.h>
#include <iostream>

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

int64_t n, k;

void solve() {
  if (n < k || (2 * k > n + 1)) {
    cout << "NO\n";
    return;
  }
  vector<int64_t> ans;
  if (n == k) {
    ans.push_back(1);
  } else {
    ans.push_back(n - k + 1);
    ans.push_back(1);
  }
  cout << "YES\n";
  cout << ans.size() << "\n";
  for (auto x : ans) {
    cout << x << " ";
  }
  cout << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int32_t t;
  cin >> t;

  while (t--) {
    cin >> n >> k;

    solve();
  }

  return 0;
}
