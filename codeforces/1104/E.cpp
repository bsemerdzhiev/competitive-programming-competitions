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

int32_t n, a[MAXN], b[MAXN];
bool vis[MAXN];

bool mark(int32_t i) {
  int32_t j{i};

  // cout << i << "\n";
  while (!vis[j]) {
    vis[j] = 1;

    int32_t from_a = a[b[j]];
    int32_t from_b = b[a[j]];

    // cout << from_a << " " << from_b << "\n";

    if (from_b != -1 && from_b != from_a) {
      return false;
    }
    b[a[j]] = from_a;

    j = a[j];
  }
  return true;
}
int32_t c_index[MAXN];
int32_t c_element[MAXN];

int32_t c_size[MAXN];
int32_t c_smallest[MAXN];

void solve() {
  for (int32_t i{1}; i <= n; i++) {
    vis[i] = 0;
  }
  int32_t k = 0;
  map<int32_t, set<int32_t>> avail;

  for (int32_t i{1}; i <= n; i++) {
    if (vis[i]) {
      continue;
    }
    int32_t j{i};
    int32_t cnt = 0;
    int32_t smallest = a[i];

    while (!vis[j]) {
      smallest = min(smallest, a[j]);
      vis[j] = 1;
      c_index[j] = k;
      c_element[a[j]] = k;

      cnt++;

      j = a[j];
    }
    c_size[k] = cnt;
    c_smallest[k] = smallest;

    avail[cnt].insert(smallest);
    // cout << smallest << "\n";

    k++;
  }
  map<int32_t, int32_t> mm;
  for (int32_t i{1}; i <= n; i++) {
    if (b[i] != -1) {
      if (c_size[c_index[i]] != c_size[c_element[b[i]]]) {
        cout << "NO\n";
        return;
      }
      if (mm.count(c_index[i]) && mm[c_index[i]] != c_element[b[i]]) {
        cout << "NO\n";
        return;
      }

      int32_t cycle_index = c_element[b[i]];

      if (!mm.count(c_index[i]) &&
          !avail[c_size[cycle_index]].count(c_smallest[cycle_index])) {
        cout << "NO\n";
        return;
      }
      mm[c_index[i]] = cycle_index;
      avail[c_size[cycle_index]].erase(c_smallest[cycle_index]);
    }
  }

  for (int32_t i{1}; i <= n; i++) {
    if (!mm.count(c_index[i])) {
      int32_t chosen_cycle = c_index[i];
      int32_t cyc_size = c_size[chosen_cycle];

      b[i] = *avail[cyc_size].begin();
      avail[cyc_size].erase(b[i]);
      mm[c_index[i]] = chosen_cycle;
    }
  }
  for (int32_t i{1}; i <= n; i++) {
    vis[i] = 0;
  }

  for (int32_t i{1}; i <= n; i++) {
    if (b[i] != -1) {
      if (!mark(i)) {
        cout << "NO\n";
        return;
      }
    }
  }

  cout << "YES\n";
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
      cin >> b[i];
    }
    solve();
  }

  return 0;
}
