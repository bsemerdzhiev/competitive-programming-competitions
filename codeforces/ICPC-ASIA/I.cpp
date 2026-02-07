#include <bits/stdc++.h>

using namespace std;

const int32_t MOD = 998244353;
const int32_t MAXN = 2e5 + 5;

const double PI = acos(-1);

namespace MO {
int32_t add(int64_t x, int64_t y) { return (x + y + MOD) % MOD; }
int32_t mul(int64_t x, int64_t y) { return (x * y) % MOD; }
}; // namespace MO

struct Point {
  int64_t x, y;

  double calc_dist_no_root(const Point &other) const {
    return ((int64_t(other.x - x) * int64_t(other.x - x)) +
            (int64_t(other.y - y) * int64_t(other.y - y)));
  }

  Point operator+(const Point &other) const {
    return Point{x + other.x, y + other.y};
  }

  Point operator-(const Point &other) const {
    return Point{x - other.x, y - other.y};
  }
  Point operator*(int64_t scale) const { return Point{x * scale, y * scale}; }
};

int32_t ccw(const Point &a, const Point &b, const Point &c) {
  double v = a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);

  if (v < 0) {
    return -1;
  } else if (v > 0) {
    return 1;
  } else {
    return 0;
  }
}

double ccw_size(const Point &a, const Point &b, const Point &c) {
  double v = a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
  return abs(v);
}

int64_t n, r;
std::vector<Point> points;

double calc_cut(const Point &p1, const Point &p2) {
  // find intersection points
  Point unit_vector = Point{p2.x - p1.x, p2.y - p1.y} * 2 * r;
  Point center = Point{0, 0};

  if (ccw(p1 - unit_vector, Point{0, 0}, p2 + unit_vector) < 0 || n == 1) {
    return PI * (r * r) / 2;
  }

  double dist_to_cent =
      ccw_size(p1, center, p2) / sqrt(p1.calc_dist_no_root(p2));

  double theta = 2.0 * acos(dist_to_cent / r);
  double a_small = (int64_t(r) * int64_t(r)) * (theta - sin(theta)) / 2;

  return a_small;
}

double solve() {
  Point p0 = *min_element(points.begin(), points.end(),
                          [](const Point &first, const Point &second) {
                            return (first.x < second.x) ||
                                   (first.x == second.x && first.y < second.y);
                          });

  sort(points.begin(), points.end(),
       [&p0](const Point &first, const Point &second) {
         int32_t orientation = ccw(p0, first, second);

         if (orientation == 0) {
           return p0.calc_dist_no_root(first) < p0.calc_dist_no_root(second);
         }
         return orientation < 0;
       });

  std::vector<Point> new_points;
  new_points.resize(n + 10);

  int32_t k = 0;
  for (int32_t i = 0; i < n; i++) {
    while (k > 1 && ccw(new_points[k - 2], new_points[k - 1], points[i]) >= 0) {
      k--;
    }
    new_points[k++] = points[i];
  }

  new_points[k++] = new_points[0];

  const Point center_p = Point{0, 0};

  double answer = 0;
  for (int32_t i = 0; i < k - 1; i++) {
    Point &p1 = new_points[i];
    Point &p2 = new_points[i + 1];

    // calculate the answer for this line
    answer = max(answer, calc_cut(p1, p2));
  }
  return answer;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cout << std::fixed << setprecision(6);

  cin >> n >> r;
  points.resize(n);

  for (int32_t i = 0; i < n; i++) {
    cin >> points[i].x >> points[i].y;
  }

  cout << solve() << "\n";

  return 0;
}
