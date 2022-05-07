struct Point {
    int x, y;

    Point(int x = 0, int y = 0) : x(x), y(y) {}

    bool operator==(const Point& other) const { return x == other.x && y == other.y; }

    bool operator!=(const Point& other) const { return x != other.x || y != other.y; }

    static long long int dist_between_sq(const Point& p1, const Point& p2) {
        long long int x2 = p1.x - p2.x;
        x2 *= x2;

        long long int y2 = p1.y - p2.y;
        y2 *= y2;

        return x2 + y2;
    }
};

std::ostream& operator<<(std::ostream& ostrm, const Point& p) {
    return (ostrm << "(" << p.x << ", " << p.y << ")");
}
