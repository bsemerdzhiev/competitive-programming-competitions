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

int64_t a[MAXN];

void solve() {
  int64_t answer = 0;

  int64_t ac = min(a[0], a[2]);

  a[2] -= ac;
  a[0] -= ac;

  answer += ac * 4;

  int64_t ab = min(a[0] / 2, a[1]);
  a[0] -= ab * 2;
  a[1] -= ab;

  answer += ab * 7;

  ab = min(a[0], a[1]);
  a[0] -= ab;
  a[1] -= ab;

  answer += ab * 5;

  if (a[0] > 0) {
    answer += 3 + (a[0] - 1) * 2;
  }
  answer += (a[1] + a[2]) * 3;

  cout << answer << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int32_t t;
  cin >> t;

  while (t--) {
    for (int32_t i = 0; i < 3; i++) {
      cin >> a[i];
    }
    solve();
  }

  return 0;
}
