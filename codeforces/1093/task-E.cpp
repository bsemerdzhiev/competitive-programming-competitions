#include <bits/stdc++.h>

using namespace std;

const int32_t MOD = 998244353;
const int32_t MAXN = 2e5 + 5;
const double INF = 1e6;

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

int32_t n;
string s;
vector<int32_t> graph[MAXN];
double T[MAXN][2];

double rec(int32_t v, int32_t p, bool prev_colored) {
  if (s[v] == '1' && s[p] != '1' && prev_colored == 1) {
    return INF;
  }
  if (T[v][prev_colored] != -1) {
    return T[v][prev_colored];
  }

  vector<double> vv;
  double zero_colored_answer = 0;

  if (s[v] == '1') {
    double answer = 0;
    for (auto x : graph[v]) {
      if (x == p)
        continue;

      answer += rec(x, v, true);
    }
    return answer;
  }

  int32_t start_av = 0;
  int32_t can_col = 0;
  for (auto x : graph[v]) {
    if (x == p)
      continue;

    double colored = rec(x, v, true);

    double not_colored = rec(x, v, false);

    zero_colored_answer += not_colored;

    if (s[x] == '1') {
      start_av++;
    } else {
      can_col++;
      vv.push_back(colored - not_colored);
    }
  }

  sort(vv.begin(), vv.end());

  start_av += prev_colored;
  int32_t K = graph[v].size();
  double answer = INF;

  if (v == p) {
    answer = min(answer, zero_colored_answer + (1.0 * K / K));
  } else {
    answer =
        min(answer, zero_colored_answer + (1.0 * K / (K - (1 - prev_colored))));
  }

  for (int32_t i = 0; i < vv.size(); i++) {

    zero_colored_answer += vv[i];

    bool to_remove = (v == p) ? 0 : (1 - prev_colored);
    double needed_to_color_i = 1.0 * K / (K - to_remove - (i + 1));

    answer = min(answer, zero_colored_answer + needed_to_color_i);
  }

  // cout << v << " " << answer << "\n";
  return T[v][prev_colored] = answer;
}

void solve() {
  for (int32_t i = 1; i <= n; i++) {
    T[i][0] = T[i][1] = -1;
  }
  double answer = rec(1, 1, 0);

  cout << fixed << setprecision(7);
  cout << answer << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int32_t t;
  cin >> t;

  while (t--) {
    cin >> n;

    for (int32_t i = 1; i <= n; i++) {
      graph[i].clear();
    }

    cin >> s;
    s = "#" + s;

    int32_t v, w;
    for (int32_t i = 0; i < n - 1; i++) {
      cin >> v >> w;

      graph[v].push_back(w);
      graph[w].push_back(v);
    }
    solve();
  }

  return 0;
}
