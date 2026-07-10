#include <bits/stdc++.h>

using namespace std;

const int32_t MOD = 998244353;
const int32_t MAXN = 5e3 + 5;

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

int32_t n, a[MAXN], b[MAXN], d[MAXN];

void solve() {
  vector<pair<int32_t, int32_t>> vv;
  list<int32_t> ll;

  for (int32_t i{1}; i <= n; i++) {
    vv.push_back(make_pair(a[i], i));
  }
  sort(vv.begin(), vv.end(), greater<pair<int32_t, int32_t>>());

  for (auto x : vv) {
    int32_t ind = x.second;
    // cout << ind << "\n";
    int32_t br = 0;
    for (int32_t j{ind}; j <= n; j++) {
      if (a[j] > a[ind]) {
        br++;
      }
    }
    if (br < d[ind]) {
      cout << "-1\n";
      return;
    }

    auto st = ll.begin();

    // cout << ind << " " << br << " " << br - d[ind] << "\n";
    int32_t needed = br - d[ind];

    for (int32_t j{0}; j < ll.size(); j++) {
      if (needed == 0)
        break;
      if (*st > ind) {
        needed--;
      }
      st = std::next(st);
    }
    ll.insert(st, ind);
  }
  for (int32_t i{1}; i <= n; i++) {
    b[ll.front()] = i;
    ll.pop_front();
  }
  for (int32_t i{1}; i <= n; i++) {
    cout << b[i] << " ";
  }
  cout << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  size_t t;
  cin >> t;

  while (t--) {
    cin >> n;

    for (int32_t i{1}; i <= n; i++) {
      cin >> a[i];
    }

    for (int32_t i{1}; i <= n; i++) {
      cin >> d[i];
    }
    solve();
  }

  return 0;
}
