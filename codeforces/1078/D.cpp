#include <bits/stdc++.h>

using namespace std;

const int32_t MOD = 998244353;
const int32_t MAXN = 3e5 + 5;

namespace MO {
int32_t add(int64_t x, int64_t y) { return (x + y + MOD) % MOD; }
int32_t mul(int64_t x, int64_t y) { return (x * y) % MOD; }
}; // namespace MO

int32_t n, m;
vector<int32_t> a[MAXN];

void solve() {
  int32_t total_cnt = 0;
  for (int32_t i = 0; i < n; i++) {
    for (int32_t j = 0; j < m; j++) {
      total_cnt += a[i][j];
    }
  }
  int32_t cnt = 0;
  int32_t row_to_choose = 0;

  for (int32_t i = 0; i < n; i++) {
    for (int32_t j = 0; j < m; j++) {
      cnt += a[i][j];
    }
    if (cnt >= total_cnt / 2) {
      row_to_choose = i;
      break;
    }
  }
  int32_t to_skip = cnt - (total_cnt / 2);

  cout << int64_t(total_cnt / 2) * int64_t(total_cnt - (total_cnt / 2)) << "\n";

  for (int32_t i = 0; i < row_to_choose; i++) {
    cout << "D";
  }
  for (int j = 0; j < m; j++) {
    if (to_skip == 0) {
      to_skip = -1;
      cout << "D";
    }
    to_skip -= a[row_to_choose][j];
    cout << "R";
  }
  if (to_skip == 0) {
    cout << "D";
  }
  for (int32_t i = row_to_choose + 1; i < n; i++) {
    cout << "D";
  }
  cout << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int32_t t;
  cin >> t;

  while (t--) {
    cin >> n >> m;

    for (int32_t i = 0; i < n; i++) {
      a[i].resize(m);
      for (int32_t j = 0; j < m; j++) {
        cin >> a[i][j];
      }
    }
    solve();
  }

  return 0;
}
