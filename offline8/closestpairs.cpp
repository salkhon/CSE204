# include <iostream>
# include <vector>
# include <algorithm>
# include <math.h>
# include <limits>
# include "Point.hpp"

using PointPair = std::vector<Point>; // array containing 2 points. 
const int UNINITIALIZED = std::numeric_limits<int>::max();

// instead of returning the closest from each recursion, the closest two will be updated
// strip width will be determined from the closest_two array at the end of each recursion

/*
Divide and Conquer closest pair finding algorithm. O(n lgn)
Can also be used to find closest two pairs.
1. Presort the array of points in two arrays, on the basis of increasing x, and another y coordinate.
2. Recurse on the x sorted array, pass in the y sorted array as well, including the boundaries.
    3. If on recursion, the size of the subset of points is <= 3, find closest pair of points comparing all combinations.
    4. Else, partition the points (sorted on x) on the mid point. Linearly partition the y sorted array, such that the points
    in xL are also in yL, points in xR are in yR, but yL and yR is sorted. (Linear time by using the presort of y on the basis of
    mid.x. NO COORDINATE X OR Y CAN MATCH FOR THIS TO WORK UNAMBIGUOUSLY).
    5. Recurse further by parting on [0, mid), [mid, hi].
    6. Using the solutions from both half, make a strip and find if any closer points reside on the strip in increasing y order.
*/

std::vector<PointPair> closest_two_pairs(2);

long long int dist_between_sq(const PointPair& pair) {
    return Point::dist_between_sq(pair[0], pair[1]);
}

bool _is_updating_first_time(const PointPair& pair) {
    return pair[0].x == UNINITIALIZED; // initial points set to max.
}

void _update_closest_two(const Point& p1, const Point& p2) {
    long long int distsq = Point::dist_between_sq(p1, p2);

    // std::cout << "checking points " << p1 << " " << p2 << std::endl;
    if (_is_updating_first_time(closest_two_pairs[0]) ||
        distsq < dist_between_sq(closest_two_pairs[0])) {

        // std::cout << "updating max to " << p1 << " " << p2 << std::endl;
        closest_two_pairs[1] = closest_two_pairs[0];
        closest_two_pairs[0] = PointPair{ p1, p2 };
    } else if (distsq != dist_between_sq(closest_two_pairs[0]) &&
        (_is_updating_first_time(closest_two_pairs[1]) || distsq < dist_between_sq(closest_two_pairs[1]))) {

        // don't update when the dist is equal to the closest one
        // std::cout << "updating 2nd max to " << p1 << " " << p2 << std::endl;
        closest_two_pairs[1] = PointPair{ p1, p2 };
    }
}

void _do_bruteforce(int lo, int hi, const std::vector<Point>& points) {
    // hi - lo <= 3, so const time.
    for (int i = lo; i < hi - 1; i++) {
        for (int j = i + 1; j < hi; j++) {
            _update_closest_two(points[i], points[j]);
        }
    }
}

void _partition(const Point& midpoint, const std::vector<Point>& ysorted,
    std::vector<Point>& yl, std::vector<Point>& yr) {

    int ptrl = 0, ptrr = 0;
    for (const Point& point : ysorted) {
        if (point.x < midpoint.x) {
            // yl[ptrl++] = point;
            yl.push_back(point);
        } else {
            yr.push_back(point);
        }
    }
}

void _search_closer_on_strip(const Point& midpoint, const std::vector<Point>& ysorted) {
    // std::cout << "in strip for lo = " << lo << " hi = " << hi << std::endl;
    const int strip_width = std::ceil(
        std::sqrt(dist_between_sq(closest_two_pairs[1]))
    );

    std::vector<Point> strip;

    std::copy_if(ysorted.begin(), ysorted.end(), std::back_inserter(strip),
        [strip_width, &midpoint](const Point& p) {
            return std::abs(p.x - midpoint.x) < strip_width;
        });

    for (int i = 0; i < int(strip.size()); i++) {
        for (int j = i + 1; j < int(strip.size()) &&
            strip[j].y - strip[i].y < strip_width; j++) {
            
            _update_closest_two(strip[i], strip[j]);
        }
    }
    // std::cout << "strip search complete for lo = " << lo << " hi = " << hi << std::endl;
}

int find_median_right(int lo, int hi, const std::vector<Point>& xsorted) {
    int mid = (lo + hi) / 2;
    Point midpoint = xsorted[mid];
    while (xsorted[mid] == midpoint.x) {
        mid++;
    }
    return mid - 1;
}

void store_closest_two_pair(int lo, int hi, const std::vector<Point>& xsorted,
    const std::vector<Point>& ysorted) {
    if (hi - lo <= 3) {
        // std::cout << "Bruteforce on lo =  " << lo << " hi = " << hi << std::endl;
        _do_bruteforce(lo, hi, xsorted);
    } else {
        // std::cout << "Recursing on lo =  " << lo << " hi = " << hi << std::endl;

        int mid = find_median_right(lo, hi, xsorted); // assuming no other point has x same as mid.x

        std::vector<Point> yl, yr;
        _partition(xsorted[mid], ysorted, yl, yr);

        store_closest_two_pair(lo, mid, xsorted, yl);
        store_closest_two_pair(mid, hi, xsorted, yr);

        _search_closer_on_strip(xsorted[mid], ysorted);
    }
}

void print_results() {
    std::cout << "closest dist " << closest_two_pairs[0][0] << " " << closest_two_pairs[0][1] <<
        " " << Point::dist_between_sq(closest_two_pairs[0][0], closest_two_pairs[0][1]) << std::endl;

    std::cout << "second closest dist " << closest_two_pairs[1][0] << " " << closest_two_pairs[1][1] <<
        " " << Point::dist_between_sq(closest_two_pairs[1][0], closest_two_pairs[1][1]) << std::endl;
}

PointPair find_second_closest_pair(const std::vector<Point>& points) {
    if (points.size() < 3) {
        return PointPair{ points[0], points[1] };
    }

    std::vector<Point> xsorted(points), ysorted(points);

    // presort to maintain monotonic order in array y in linear time in further recursions.
    std::sort(xsorted.begin(), xsorted.end(),
        [](Point& p1, Point& p2) { return p1.x < p2.x; });
    std::sort(ysorted.begin(), ysorted.end(),
        [](Point& p1, Point& p2) { return p1.y < p2.y; });

    // will store in global var instead of returning mins.
    Point temp(UNINITIALIZED, UNINITIALIZED); // marker for uninitialized
    closest_two_pairs[0] = closest_two_pairs[1] = PointPair{ temp, temp };

    store_closest_two_pair(0, points.size(), xsorted, ysorted);

    // print_results();

    return closest_two_pairs[1];
}
