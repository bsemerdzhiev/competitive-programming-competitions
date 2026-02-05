#include <bits/stdc++.h>

using namespace std;

const int32_t MOD = int32_t(1e9 + 7);
const int32_t MAXN = 2e5 + 5;

namespace MO {
int32_t add(int64_t x, int64_t y, int32_t MOD_TO_USE) {
  return (x + y + MOD_TO_USE) % MOD_TO_USE;
}
int32_t mul(int64_t x, int64_t y, int32_t MOD_TO_USE) {
  return (x * y) % MOD_TO_USE;
}
}; // namespace MO

int32_t n, c;
string a;

int32_t solve() {
  int32_t ans = 1;
  int32_t div_check = 1;

  if (a[0] == '0' || a[n - 1] == '0') {
    return -1;
  }

  for (int32_t i = 1; i < n; i++) {
    if (a[i] == '1') {
      ans = MO::mul(ans, 2, MOD);
      div_check = MO::mul(div_check, 2, c);

    } else {
      ans = MO::mul(ans, i, MOD);
      div_check = MO::mul(div_check, i, c);
    }
  }

  if (div_check == 0) {
    return -1;
  }

  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int32_t t;

  cin >> t;

  while (t--) {
    cin >> n >> c;
    cin >> a;

    cout << solve() << "\n";
  }

  return 0;
}
