#include <bits/stdc++.h>

using namespace std;

const int32_t MOD = 998244353;
const int32_t MAXN = 2e5 + 5;

namespace MO {
int32_t add(int64_t x, int64_t y) { return (x + y + MOD) % MOD; }
int32_t mul(int64_t x, int64_t y) { return (x * y) % MOD; }
}; // namespace MO

struct leap {
  int64_t a, b, c;

  leap() {}
  leap(int32_t _a, int32_t _b, int32_t _c) : a(_a), b(_b), c(_c) {}
};

int32_t n;
int64_t x;

leap jmps[MAXN];

int64_t solve() {
  int64_t max_possible = 0;
  for (int32_t i = 0; i < n; i++) {
    max_possible += jmps[i].a * (jmps[i].b - 1);
  }
  if (max_possible >= x) {
    return 0;
  }

  int64_t rem = x - max_possible;
  int64_t answer = INT64_MAX;
  for (int32_t i = 0; i < n; i++) {
    if (jmps[i].a * jmps[i].b - jmps[i].c <= 0)
      continue;

    int64_t tmp = (jmps[i].a * jmps[i].b) - jmps[i].c;
    answer = min(answer, (rem + tmp - 1) / tmp);
  }
  if (answer == INT64_MAX) {
    answer = -1;
  }
  return answer;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int32_t t;
  cin >> t;

  int32_t a, b, c;
  while (t--) {
    cin >> n >> x;

    for (int32_t i = 0; i < n; i++) {
      cin >> a >> b >> c;
      jmps[i] = leap{a, b, c};
    }
    cout << solve() << "\n";
  }

  return 0;
}
