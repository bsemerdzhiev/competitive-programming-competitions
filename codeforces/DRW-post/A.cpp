#include <cstdlib>
#include <ios>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

constexpr int32_t MAXN = 2e5 + 5;

struct Edge {
  int32_t w, weight, next_edge;

  Edge(int32_t _v, int32_t _weight, int32_t _next_edge)
      : w(_v), weight(_weight), next_edge(_next_edge) {}
};

int32_t N, S;
int32_t source, sink;

std::vector<int32_t> graph[MAXN];
std::vector<Edge> all_edges;
int32_t level[MAXN];

bool bfs(int32_t v, int32_t target) {
  std::queue<int32_t> q;
  q.push(v);

  for (std::size_t i{0}; i <= sink; i++) {
    level[i] = -1;
  }

  level[v] = 0;

  while (!q.empty()) {
    int32_t cur_node = q.front();
    q.pop();

    for (const auto &child_ind : graph[cur_node]) {
      Edge &cur_edge = all_edges[child_ind];
      if (cur_edge.weight > 0 && level[cur_edge.w] == -1) {
        level[cur_edge.w] = level[cur_node] + 1;
        q.push(cur_edge.w);
      }
    }
  }
  return level[target] != -1;
}

int32_t remember[MAXN];

int32_t dfs(int32_t v, int32_t target, int32_t flow) {
  if (v == target) {
    return flow;
  }
  for (int32_t start = remember[v]; start < graph[v].size(); start++) {
    remember[v] = start;
    Edge &cur_edge = all_edges[graph[v][start]];

    if (cur_edge.weight > 0 && level[cur_edge.w] == level[v] + 1) {
      int32_t returned_flow =
          dfs(cur_edge.w, target, std::min(flow, cur_edge.weight));
      if (returned_flow > 0) {
        cur_edge.weight -= returned_flow;
        all_edges[cur_edge.next_edge].weight += returned_flow;
        return returned_flow;
      }
    }
  }
  return 0;
}

bool dinitz(const int32_t N) {
  int32_t answer = 0, delta = 0;
  while (bfs(source, sink)) {
    do {
      for (int32_t i{0}; i <= sink; i++) {
        remember[i] = 0;
      }

      delta = dfs(source, sink, N);
      answer += delta;
    } while (delta > 0);
  }
  return answer == N;
}

void add_edge(int32_t v, int32_t w, int32_t weight) {
  int32_t current_edges = all_edges.size();

  all_edges.push_back(Edge{w, weight, current_edges + 1});
  all_edges.push_back(Edge{v, 0, current_edges});

  graph[v].push_back(current_edges);
  graph[w].push_back(current_edges + 1);
}

int main() {

  std::cin.tie(NULL);
  std::ios_base::sync_with_stdio(false);
  std::cin >> N >> S;

  all_edges.reserve(N + (2 * N) + S);

  source = N + S;
  sink = N + S + 1;

  for (int i = 0; i < N; i++) {
    int32_t first = (rand() % S);
    int32_t sec = (rand() % S);

    while (sec == first) {
      sec = (rand() % S);
    }

    add_edge(i, first + N, 1);
    add_edge(i, sec + N, 1);

    add_edge(source, i, 1);
  }

  for (int32_t i{0}; i < S; i++) {
    add_edge(i + N, sink, 1);
  }

  std::cout << dinitz(N) << std::endl;

  return 0;
}
