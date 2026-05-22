#include <bits/stdc++.h>
#include <cstdint>

using namespace std;

const int32_t MOD = 998244353;
const int32_t MAXN = 4e5 + 5;

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

struct point {
  int32_t x, y;

  bool operator<(const point &other) const {
    return x < other.x || (x == other.x && y < other.y);
  }
};

int32_t n, m;
point p[MAXN];

int32_t pt[MAXN], ct[MAXN], d[MAXN];

void solve() {
  sort(p, p + n);

  int32_t k = 1;
  for (int32_t i = 1; i < n; i++) {
    if (p[k - 1].y > p[i].y) {
      p[k] = p[i];
      k++;
    }
  }
  n = k;

  auto eval = [](int32_t news_ind, int32_t user_ind) {
    if (news_ind < 0 || news_ind >= n) {
      return INT32_MAX;
    }
    int32_t ff = 0;
    if (p[news_ind].x >= pt[user_ind]) {
      ff = min(p[news_ind].x, pt[user_ind] + d[user_ind]);
    }

    int32_t ss = 0;
    if (p[news_ind].y >= ct[user_ind]) {
      ss = min(p[news_ind].y, ct[user_ind] + d[user_ind]);
    }
    return ff + ss;
  };

  cin >> m;
  for (int32_t i = 0; i < m; i++) {
    cin >> pt[i];
  }
  for (int32_t i = 0; i < m; i++) {
    cin >> ct[i];
  }
  for (int32_t i = 0; i < m; i++) {
    cin >> d[i];
  }
  pt[m] = ct[m] = 0;
  d[m] = INT32_MAX;

  int32_t init_ans = INT32_MAX;
  for (int32_t i = 0; i < n; i++) {
    init_ans = min(init_ans, eval(i, m));
  }
  // cout << init_ans << "\n";

  for (int32_t i = 0; i < m; i++) {
    int32_t ans = init_ans;

    ans = min(eval(0, i), ans);
    ans = min(eval(n - 1, i), ans);

    int32_t l = 0, r = n - 1;
    int32_t break_point = 0;

    while (l <= r) {
      int32_t middle = (l + r) >> 1;

      if (p[middle].x <= pt[i]) {
        break_point = middle;
        l = middle + 1;
      } else {
        r = middle - 1;
      }
    }
    ans = min(eval(break_point + 1, i), ans);
    ans = min(eval(break_point, i), ans);
    ans = min(eval(break_point - 1, i), ans);

    l = 0;
    r = n - 1;
    break_point = 0;
    while (l <= r) {
      int32_t middle = (l + r) >> 1;

      if (p[middle].x <= pt[i] + d[i]) {
        break_point = middle;
        l = middle + 1;
      } else {
        r = middle - 1;
      }
    }

    ans = min(eval(break_point + 1, i), ans);
    ans = min(eval(break_point, i), ans);
    ans = min(eval(break_point - 1, i), ans);
    cout << ans << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> n;

  for (int32_t i = 0; i < n; i++) {
    cin >> p[i].x;
  }

  for (int32_t i = 0; i < n; i++) {
    cin >> p[i].y;
  }
  solve();

  return 0;
}
