#include <bits/stdc++.h>

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

int32_t n, k, a[MAXN], b[MAXN];

void solve() {
  vector<int32_t> ans;
  while (true) {
    int32_t ind = -1;
    for (int32_t j = 0; j < n; j++) {
      if (b[j] == k + 1)
        continue;

      if (ind == -1 || b[j] > b[ind]) {
        ind = j;
      }
    }
    if (ind == -1) {
      break;
    }
    ans.push_back(ind + 1);
    b[ind]++;
  }
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
    for (int32_t i = 1; i <= k; i++) {
      cin >> a[i];
    }
    for (int32_t i = 0; i < n; i++) {
      cin >> b[i];
    }
    solve();
  }

  return 0;
}
