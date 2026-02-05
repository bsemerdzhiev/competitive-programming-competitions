#include <iostream>
#include <math.h>

using namespace std;

const int32_t MOD = 998244353;
const int32_t MAXN = 2e5 + 5;

namespace MO {
int32_t add(int64_t x, int64_t y) { return (x + y + MOD) % MOD; }
int32_t mul(int64_t x, int64_t y) { return (x * y) % MOD; }
}; // namespace MO

int32_t n;
string a;
bool mark[MAXN];

void solve() {
  for (int i = 1; i <= n; i++) {
    mark[i] = 0;
  }
  a = '#' + a + '#';
  int32_t answer = 0;
  for (int32_t i = 1; i <= n; i++) {
    if (a[i] == '1') {
      mark[i - 1] = mark[i] = mark[i + 1] = 1;
      answer += 1;
    }
  }

  int32_t cnt = 0;
  for (int32_t i = 1; i <= n; i++) {
    if (mark[i] == 0) {
      cnt++;
    } else {
      if (cnt != 0) {
        answer += ceil(cnt / 3.0);
      }
      cnt = 0;
    }
  }

  if (cnt != 0) {
    answer += ceil(cnt / 3.0);
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
    cin >> a;

    solve();
  }

  return 0;
}
