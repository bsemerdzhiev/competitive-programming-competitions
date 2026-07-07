#include <bits/stdc++.h>

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

int32_t n, a[MAXN];

bool swap_and_test(int32_t k1, int32_t k2) {
  if (k1 < 0 || k2 < 0 || k1 >= n || k2 >= n) {
    return false;
  }
  swap(a[k1], a[k2]);

  set<int32_t> ss;
  for (int32_t i{0}; i < n; i++) {
    int32_t br = 0;

    for (int32_t j{i}; j < n; j++) {
      if (a[j] != a[i]) {
        break;
      }
      br++;
    }
    if (ss.count(a[i])) {
      swap(a[k1], a[k2]);
      return false;
    }
    ss.insert(a[i]);
    i += br - 1;
  }
  swap(a[k1], a[k2]);
  // cout << k1 << " " << k2 << "\n";
  return true;
}

bool solve() {
  map<int32_t, vector<pair<int32_t, int32_t>>> mm;

  for (int32_t i{0}; i < n; i++) {
    int32_t br = 0;

    for (int32_t j{i}; j < n; j++) {
      if (a[j] != a[i]) {
        break;
      }
      br++;
    }
    mm[a[i]].push_back(make_pair(i, i + br - 1));
    i += br - 1;
  }
  for (auto x : mm) {
    int32_t k = x.second.size();
    if (k > 1) {
      if (k == 2) {
        int32_t ls[2] = {x.second[0].first, x.second[1].first};
        int32_t rs[2] = {x.second[0].second, x.second[1].second};

        bool answer = false;
        answer |= swap_and_test(ls[0], ls[1] - 1);
        answer |= swap_and_test(ls[0], rs[1] + 1);

        answer |= swap_and_test(rs[1], ls[0] - 1);
        answer |= swap_and_test(rs[1], rs[0] + 1);

        // cout << "DAS" << "\n";
        return answer;
      } else if (k == 3) {
        int32_t ls[3] = {x.second[0].first, x.second[1].first,
                         x.second[2].first};
        int32_t rs[3] = {x.second[0].second, x.second[1].second,
                         x.second[2].second};

        bool answer = false;
        for (size_t z = 0; z < 3; z++) {
          int32_t prev = (z + 2) % 3;
          int32_t nxt = (z + 1) % 3;

          if (rs[z] - ls[z] == 0) {
            answer |= swap_and_test(ls[z], ls[prev] - 1);
            answer |= swap_and_test(ls[z], rs[prev] + 1);

            answer |= swap_and_test(ls[z], ls[nxt] - 1);
            answer |= swap_and_test(ls[z], rs[nxt] + 1);
          }
        }
        return answer;
      } else {
        return false;
      }
    }
  }
  return true;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  size_t t;
  cin >> t;

  while (t--) {
    cin >> n;
    for (int32_t i{0}; i < n; i++) {
      cin >> a[i];
    }
    cout << (solve() ? "YES" : "NO") << "\n";
  }

  return 0;
}
