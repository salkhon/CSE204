# include <iostream>
# include <fstream>
# include <vector>
# include <string>
# include "closestpairs.cpp"
# include <algorithm>
# include <iomanip>

using PointPair = std::vector<Point>;

std::vector<Point> read_from_file(std::string filename) {
    std::fstream file(filename);

    int n;
    file >> n;
    std::vector<Point> points(n);

    for (int i = 0; i < n; i++) {
        file >> points[i].x >> points[i].y;
    }

    file.close();

    return points;
}

std::vector<Point> read_from_console() {
    int n;
    std::cin >> n;

    std::vector<Point> points(n);

    for (int i = 0; i < n; i++) {
        std::cin >> points[i].x >> points[i].y;
    }

    return points;
}

int main() {
    // std::vector<Point> points = read_from_console();
    // std::vector<Point> points = read_from_file("tests/input_test " + std::to_string(t) + ".txt");
    std::vector<Point> points = read_from_file("tests/input.txt");

    PointPair pair = find_second_closest_pair(points);

    Point point0 = pair[0], point1 = pair[1];

    auto p0_iter = std::find(points.begin(), points.end(), point0);
    auto p1_iter = std::find(points.begin(), points.end(), point1);

    int p0_idx = p0_iter - points.begin();
    int p1_idx = p1_iter - points.begin();

    std::cout << std::fixed;
    std::cout << std::setprecision(4);
    std::cout << p0_idx << " " << p1_idx << std::endl;
    std::cout << std::sqrt(Point::dist_between_sq(point0, point1)) << std::endl;

    return 0;
}

