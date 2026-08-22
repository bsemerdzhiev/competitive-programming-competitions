#include <algorithm>
#include <cstdint>
#include <ios>
#include <iostream>
#include <vector>

struct Point {
  int32_t _x, _y, _original_ind;

  Point(int32_t x, int32_t y, int32_t original_ind)
      : _x(x), _y(y), _original_ind(original_ind) {}

  int64_t cross_product(const Point &p1, const Point &p2) const {
    int64_t area = (int64_t)_x * (int64_t)(p1._y - p2._y) +
                   (int64_t)p1._x * (int64_t)(p2._y - _y) +
                   (int64_t)p2._x * (int64_t)(_y - p1._y);

    return area;
  }

  int64_t is_angle_less_than_90(const Point &p1, const Point &p2) {
    int64_t dot_product = int64_t(p1._x - _x) * int64_t(p2._x - _x) +
                          int64_t(p1._y - _y) * int64_t(p2._y - _y);

    return dot_product > 0;
  }

  int32_t get_orientation(const Point &p1, const Point &p2) const {
    int64_t area = cross_product(p1, p2);

    if (area < 0) {
      return -1;
    } else if (area > 0) {
      return 1;
    } else {
      return 0;
    }
  }
};

int32_t n;
std::vector<Point> all_points;

void solve() {
  size_t removed = 0;
  std::vector<int32_t> conv_hull;
  conv_hull.reserve(n + 1);
  size_t cur_point = 0;

  while (n - removed >= 3) { // keep removing points that cause trouble
    Point p0 = *std::min_element(all_points.begin(), all_points.end() - removed,
                                 [](const Point p1, const Point p2) {
                                   return p1._y < p2._y ||
                                          (p1._y == p2._y && p1._x < p2._x);
                                 });

    // std::cout << p0._original_ind << "\n";
    std::sort(all_points.begin(), all_points.end() - removed,
              [&p0](const Point &p1, const Point &p2) {
                int32_t orientation = p0.get_orientation(p1, p2);

                if (orientation == 0) {
                  return int64_t(p0._x - p1._x) * int64_t(p0._x - p1._x) +
                             int64_t(p0._y - p1._y) * int64_t(p0._y - p1._y) <
                         int64_t(p0._x - p2._x) * int64_t(p0._x - p2._x) +
                             int64_t(p0._y - p2._y) * int64_t(p0._y - p2._y);
                } else if (orientation == -1)
                  return true;
                else
                  return false;
              });

    // make a convex hull with the current points
    cur_point = 0;
    for (size_t i = 0; i < all_points.size() - removed; i++) {
      while (cur_point >= 2 &&
             all_points[conv_hull[cur_point - 2]].get_orientation(
                 all_points[conv_hull[cur_point - 1]], all_points[i]) != -1) {
        cur_point--;
      }
      conv_hull[cur_point++] = i;
    }

    std::vector<int32_t> to_remove;
    for (size_t i = 0; i < cur_point; i++) {
      int32_t prev = (i == 0 ? conv_hull[cur_point - 1] : conv_hull[i - 1]);
      int32_t next = (i == cur_point - 1 ? conv_hull[0] : conv_hull[i + 1]);

      if (all_points[conv_hull[i]].is_angle_less_than_90(all_points[prev],
                                                         all_points[next])) {
        // add the current point to the list of points to be removed
        to_remove.push_back(conv_hull[i]);
      }
    }
    std::sort(to_remove.begin(), to_remove.end(), std::greater<int32_t>());
    // remove the points
    for (const int &ind : to_remove) {
      std::swap(all_points[ind], all_points[n - removed - 1]);
      removed++;
    }
    // return;

    if (to_remove.empty()) {
      // we found a solution
      std::cout << cur_point << "\n";
      for (size_t i = 0; i < cur_point; i++) {
        std::cout << all_points[conv_hull[i]]._original_ind << " ";
      }
      std::cout << "\n";
      return;
    }
  }
  std::cout << "impossible\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  std::cin >> n;

  int32_t x, y;
  for (int32_t i = 0; i < n; i++) {
    std::cin >> x >> y;

    all_points.push_back(Point(x, y, i + 1));
  }

  solve();

  return 0;
}
