#include <bits/stdc++.h>
#include <queue>

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
  int32_t ans = 1;
  priority_queue<int32_t> pq;

  for (int32_t i = 1; i <= n; i++) {
    if (a[i] <= i) {
      pq.push(-(n + 1));
    } else {
      pq.push(-a[i]);
    }

    while (!pq.empty() && -pq.top() <= i)
      pq.pop();

    ans = max(ans, (int32_t)pq.size());
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
    for (int32_t i = 1; i <= n; i++) {
      cin >> a[i];
    }
    solve();
  }

  return 0;
}
