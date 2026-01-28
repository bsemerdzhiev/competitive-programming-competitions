#include <bits/stdc++.h>
#include <queue>

using namespace std;

const int32_t MOD = 998244353;
const int32_t MAXN = 1e5 + 5;

namespace MO {
int32_t add(int64_t x, int64_t y) { return (x + y + MOD) % MOD; }
int32_t mul(int64_t x, int64_t y) { return (x * y) % MOD; }
}; // namespace MO

int32_t n;
std::vector<int32_t> doors[MAXN];
int32_t row_sz[MAXN], l[MAXN], r[MAXN], hole[MAXN];

struct layer {
  int32_t layer_ind;
  int32_t element_number;
  int32_t pos;

  bool operator<(const layer &other) const {
    return pos + doors[layer_ind][element_number] >
           other.pos + doors[other.layer_ind][other.element_number];
  }
};

void solve() {
  multiset<int32_t> ups, downs;

  priority_queue<layer> pq;

  for (int32_t i{0}; i < n; i++) {
    if (row_sz[i] != 0)
      pq.push(layer{i, 0, l[i]});
    ups.insert(l[i]);
    downs.insert(l[i] + hole[i]);
  }

  int32_t answer = 0;
  while (!pq.empty()) {
    // check if current set up generate a better answer
    answer = max(answer, *downs.begin() - *ups.rbegin());

    layer cur_best = pq.top();
    pq.pop();

    int32_t size_of_door_to_move =
        doors[cur_best.layer_ind][cur_best.element_number];
    // move the door to the left
    layer new_layer = layer{cur_best.layer_ind, cur_best.element_number + 1,
                            cur_best.pos + size_of_door_to_move};

    if (new_layer.element_number < row_sz[new_layer.layer_ind]) {
      pq.push(new_layer);
    }
    ups.erase(ups.find(cur_best.pos));
    downs.erase(downs.find(cur_best.pos + hole[cur_best.layer_ind]));

    // insert the new element
    ups.insert(cur_best.pos + size_of_door_to_move);
    downs.insert(cur_best.pos + size_of_door_to_move +
                 hole[cur_best.layer_ind]);
  }

  answer = max(answer, *downs.begin() - *ups.rbegin());
  cout << answer << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> n;

  for (int32_t i{0}; i < n; i++) {
    cin >> row_sz[i] >> l[i] >> r[i];
    doors[i].resize(row_sz[i]);
    hole[i] = (r[i] - l[i]);
    for (int32_t j{0}; j < row_sz[i]; j++) {
      cin >> doors[i][j];
      hole[i] -= doors[i][j];
    }
  }

  solve();

  return 0;
}
