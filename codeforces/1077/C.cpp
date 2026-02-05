#include <bits/stdc++.h>

using namespace std;

const int32_t MOD = 998244353;
const int32_t MAXN = 2e5 + 5;

namespace MO {
int32_t add(int64_t x, int64_t y) { return (x + y + MOD) % MOD; }
int32_t mul(int64_t x, int64_t y) { return (x * y) % MOD; }
}; // namespace MO

int32_t n, a[MAXN], b[MAXN];

void solve() {
  for (int32_t i = 0; i < n; i++) {
    b[i] = a[i];
  }
  sort(b, b + n);

  vector<int32_t> vv;
  int32_t l = b[0], r = b[n - 1];
  for (int32_t i = 0; i < n; i++) {
    if (a[i] != b[i]) {
      vv.push_back(a[i]);
    }
  }
  if (vv.size() == 0) {
    cout << "-1\n";
    return;
  }

  vv.push_back(l);
  vv.push_back(l);
  sort(vv.begin(), vv.end());

  int32_t answer = 0;
  int32_t k = vv.size();

  for (int32_t i = 1; i < k; i++) {
    answer = max(answer, min(vv[i] - l, r - vv[i - 1]));
  }
  cout << answer << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int32_t t;

  cin >> t;

  while (t--) {
    cin >> n;
    for (int32_t i = 0; i < n; i++) {
      cin >> a[i];
    }
    solve();
  }

  return 0;
}
