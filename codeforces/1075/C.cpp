#include <bits/stdc++.h>

using namespace std;

const int32_t MOD = 998244353;
const int32_t MAXN = 2e5 + 5;

namespace MO {
int32_t add(int64_t x, int64_t y) { return (x + y + MOD) % MOD; }
int32_t mul(int64_t x, int64_t y) { return (x * y) % MOD; }
}; // namespace MO

int32_t n;
int32_t a[MAXN];

void solve() {
  a[n - 1] = 1;

  for (int32_t i = n - 2; i >= 0; i--) {
    a[i] = (i + 1) ^ 1;
  }

  int32_t first_one = __countr_zero(n);

  if ((1 << first_one) == n) {
    cout << "-1\n";
    return;
  }
  if (n % 2 == 0) {
    a[0] = n;

    swap(a[0], a[(1 << first_one) - 1]);
  } else {
    a[0] = n - 1;
  }

  for (int32_t i = 0; i < n; i++) {
    cout << a[i] << " ";
  }
  cout << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int32_t t;
  cin >> t;

  while (t--) {
    cin >> n;

    solve();
  }

  return 0;
}
