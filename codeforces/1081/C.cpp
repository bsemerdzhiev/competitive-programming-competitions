#include <bits/stdc++.h>
#include <queue>
#include <set>

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

int64_t n, h, k;
int64_t a[MAXN];

int64_t solve() {
  int64_t total_sum = 0;
  for (int32_t i = 0; i < n; i++) {
    total_sum += a[i];
  }

  int64_t times_zeroed = h / total_sum;

  int64_t time_spent = times_zeroed * (k + n);

  if (h % total_sum != 0) {
    int64_t rem_sum = h % total_sum;

    multiset<int64_t> ms;
    multiset<int64_t> smallest_numb;

    for (int32_t i = 0; i < n; i++) {
      ms.insert(a[i]);
    }

    int64_t cur_sum = 0;
    for (int32_t i = 0; i < n; i++) {
      cur_sum += a[i];
      ms.erase(ms.find(a[i]));

      smallest_numb.insert(a[i]);
      if (ms.empty()) {
        ms.insert(0);
      }

      if (*ms.rbegin() < *smallest_numb.begin()) {
        if (cur_sum >= rem_sum) {
          return time_spent + (i + 1);
        }
      }

      if (cur_sum + *ms.rbegin() - *smallest_numb.begin() >= rem_sum) {
        return time_spent + (i + 1);
      }
    }
  } else {
    time_spent -= k;
    return time_spent;
  }
  return -1;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int32_t t;
  cin >> t;

  while (t--) {
    cin >> n >> h >> k;
    for (int32_t i = 0; i < n; i++) {
      cin >> a[i];
    }
    cout << solve() << "\n";
  }

  return 0;
}
