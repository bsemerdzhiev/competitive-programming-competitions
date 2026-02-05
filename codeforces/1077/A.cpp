#include <iostream>

using namespace std;

const int32_t MOD = 998244353;
const int32_t MAXN = 2e5 + 5;

namespace MO {
int32_t add(int64_t x, int64_t y) { return (x + y + MOD) % MOD; }
int32_t mul(int64_t x, int64_t y) { return (x * y) % MOD; }
}; // namespace MO

int32_t n;
int32_t a[MAXN];
bool used[MAXN];

void solve() {
  for (int32_t i = 0; i <= n; i++) {
    used[i] = 0;
  }
  a[n - 1] = 1;
  used[1] = 1;
  for (int32_t i = n - 2; i >= 0; i--) {
    int32_t wanted = i + 1;

    for (int32_t j = 1; j <= n; j++) {
      if (!used[j] && (a[i + 1] - j) % wanted == 0) {
        used[j] = 1;
        a[i] = j;
        break;
      }
    }
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
