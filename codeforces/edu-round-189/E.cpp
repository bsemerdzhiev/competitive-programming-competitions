#include <bits/stdc++.h>
#include <iostream>
#include <iterator>

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

struct pnt_strc {
  double x, y;

  double distance(const pnt_strc &other) {
    double ds_one = (x - other.x) * (x - other.x);
    double ds_two = (y - other.y) * (y - other.y);

    return sqrt(ds_one + ds_two);
  }

  bool operator<(const pnt_strc &other) const {
    return y < other.y || (y == other.y && x < other.x);
  }
} pnt[MAXN];

int32_t n, r;

void solve() {
  double x_cords[2] = {MAXN, -MAXN};
  double y_cords[2] = {MAXN, -MAXN};

  for (int32_t i = 0; i < n; i++) {
    x_cords[0] = min(x_cords[0], pnt[i].x);
    x_cords[1] = max(x_cords[1], pnt[i].x);

    y_cords[0] = min(y_cords[0], pnt[i].y);
    y_cords[1] = max(y_cords[1], pnt[i].y);
  }

  sort(pnt, pnt + n);

  pnt_strc cur_pnt = pnt_strc{x_cords[0], y_cords[1]};

  pnt_strc start_point = pnt_strc{x_cords[0], y_cords[1]};

  int32_t z = n - 1;
  vector<pnt_strc> ans;

  while (true) {
    while (z >= 0 && abs(pnt[z].y - cur_pnt.y) > r) {
      z--;
    }

    bool is_incl = false;
    for (int32_t i = z; i >= 0; i--) {
      if (cur_pnt.distance(pnt[i]) <= r) {
        is_incl = true;
      }

      if (cur_pnt.y - pnt[i].y > r) {
        break;
      }
    }
    // cout << "Cur p " << cur_pnt.x << " " << cur_pnt.y << " " << "\n";
    if (is_incl) {
      ans.push_back(cur_pnt);
    }

    cur_pnt.x += 2 * r;
    if (cur_pnt.x - x_cords[1] > r) {
      cur_pnt = start_point;

      cur_pnt.y -= int32_t(1.0 * sqrt(3) * r) + 1;
      cur_pnt.x = start_point.x - r;

      start_point = cur_pnt;
    }

    if (y_cords[0] - cur_pnt.y > r) {
      break;
    }
  }

  cout << ans.size() << "\n";
  for (auto x : ans) {
    cout << x.x << " " << x.y << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> n >> r;

  for (int32_t i = 0; i < n; i++) {
    cin >> pnt[i].x >> pnt[i].y;
  }

  solve();

  return 0;
}
