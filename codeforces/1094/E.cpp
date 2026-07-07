#include <bits/stdc++.h>
#include <format>

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

int32_t n;

int32_t update(int64_t numb) {
  cout << format("I {}", numb) << endl;

  int32_t ans;
  cin >> ans;

  return ans;
}

int32_t query(int64_t numb) {
  cout << format("Q {}", numb) << endl;

  int32_t ans;
  cin >> ans;

  return ans;
}

void solve() {
  cout << 0 << endl;

  int32_t q1 = update(0);

  if (q1 == 1) {
    // operations is &

    update((1LL << n) - 1);
    int64_t l = 1, r = (1LL << n) - 1;
    int64_t ans = 0;

    while (l <= r) {
      int64_t middle = (l + r) >> 1;

      if (query(middle) > 0) {
        ans = middle;
        l = middle + 1;
      } else {
        r = middle - 1;
      }
    }
    cout << format("A {} {}", 1, ans) << endl;
  } else {
    // operations is | or ^
    int64_t l = 1, r = (1LL << n) - 1;
    int64_t ans = 0;

    while (l <= r) {
      int64_t middle = (l + r) >> 1;

      if (query(middle) > 0) {
        ans = middle;
        l = middle + 1;
      } else {
        r = middle - 1;
      }
    }

    if (ans == (1LL << n) - 1) {
      update((1LL << n) - 2);
      if (query(0) >= 3) {
        cout << format("A {} {}", 3, ans) << endl;
      } else {
        cout << format("A {} {}", 2, ans) << endl;
      }
    } else {
      update((1LL << n) - 1);
      int32_t q2 = query((1LL << n) - 1);

      cout << format("A {} {}", (q2 == 1 ? 2 : 3), ans) << endl;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  size_t t;
  cin >> t;

  while (t--) {
    cin >> n;
    if (n == -1) {
      break;
    }

    solve();
  }

  return 0;
}
