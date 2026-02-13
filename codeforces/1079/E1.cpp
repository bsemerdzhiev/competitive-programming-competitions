#include <bits/stdc++.h>
#include <format>

using namespace std;

const int32_t MOD = 998244353;
const int32_t MAXN = 33;

namespace MO {
int32_t add(int64_t x, int64_t y) { return (x + y + MOD) % MOD; }
int32_t mul(int64_t x, int64_t y) { return (x * y) % MOD; }
}; // namespace MO

int32_t n;

void query(int32_t k, vector<int32_t> &vv) {
  cout << format("? {}\n", k);
  cout.flush();

  int32_t buf_sz;

  cin >> buf_sz;
  vv.resize(buf_sz);

  int32_t nmb;
  for (int32_t i = 0; i < buf_sz; i++) {
    cin >> vv[i];
  }
}

void report(vector<pair<int32_t, int32_t>> ans) {
  cout << format("! {}\n", ans.size());

  for (const auto &x : ans) {
    cout << x.first << " " << x.second << "\n";
  }
  cout.flush();
}

int32_t node_cnt[MAXN];
bool visited[MAXN];
stack<int32_t> cur_tree;
vector<pair<int32_t, int32_t>> edges;

void solve() {
  for (int32_t i = 0; i <= n; i++) {
    visited[i] = node_cnt[i] = 0;
  }
  while (!cur_tree.empty())
    cur_tree.pop();
  edges.clear();
  if (n == 1) {
    report(edges);
    return;
  }

  int32_t k = 1;
  vector<int32_t> vv;
  cur_tree.push(0);
  int32_t query_cnt = 0;

  cur_tree.push(1);

  while (true) {
    // for (int32_t i = 1; i <= n; i++) {
    //   cout << node_cnt[i] << "\n";
    // }
    if (visited[cur_tree.top()]) {
      k += node_cnt[cur_tree.top()];
    } else {
      k += 1;
    }
    query(k, vv);

    if (vv.size() == 0) {
      break;
    }

    // update the current current tree
    int32_t stop_element = 0;
    if (vv.size() > 1) {
      stop_element = vv[vv.size() - 2];
    }

    int32_t prev = -1;
    while (cur_tree.top() != stop_element) {
      if (prev != -1) {
        node_cnt[cur_tree.top()] += node_cnt[prev];
      }

      if (!visited[cur_tree.top()]) {
        visited[cur_tree.top()] = true;
        node_cnt[cur_tree.top()] += 1;
      }

      prev = cur_tree.top();

      cur_tree.pop();
    }
    if (prev != -1) {
      node_cnt[cur_tree.top()] += node_cnt[prev];
    }

    if (cur_tree.top() != 0) {
      edges.push_back(make_pair(cur_tree.top(), vv[vv.size() - 1]));
    }
    cur_tree.push(vv[vv.size() - 1]);
  }
  report(edges);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int32_t t;
  cin >> t;

  while (t--) {
    cin >> n;

    solve();
  }

  return 0;
}
