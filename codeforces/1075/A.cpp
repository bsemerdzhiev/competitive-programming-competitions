#include <bits/stdc++.h>

using namespace std;

const int32_t MOD = 998244353;
const int32_t MAXN = 2e5 + 5;

namespace MO {
int32_t add(int64_t x, int64_t y) { return (x + y + MOD) % MOD; }
int32_t mul(int64_t x, int64_t y) { return (x * y) % MOD; }
}; // namespace MO

int32_t n, h, l;
int32_t a[MAXN];

void solve() {
  sort(a, a + n);

  if (h > l) {
    swap(h, l);
  }
  int32_t cnt_one = 0, cnt_two = 0;
  for (int32_t i = 0; i < n; i++) {
    if (a[i] > h && a[i] <= l) {
      cnt_two++;
    } else if (a[i] <= h) {
      cnt_one++;
    }
  }

  int32_t answer = min(cnt_two, cnt_one) + (max(0, cnt_one - cnt_two) / 2);

  cout << answer << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int32_t t;

  cin >> t;

  while (t--) {
    cin >> n >> h >> l;

    for (int32_t i = 0; i < n; i++) {
      cin >> a[i];
    }

    solve();
  }

  return 0;
}
