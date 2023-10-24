#include <iostream>
#include <cmath>
#include <cfloat>
#include <fstream>
#include <vector>
#include <algorithm>

class Point
{
public:
    int64_t x, y;
};

float distance(Point p1, Point p2)
{
    return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) +
                     (p1.y - p2.y) * (p1.y - p2.y));
}

float Simple_Algos(Point* P, int64_t n)
{
    float minimum = FLT_MAX;
    for (int64_t i = 0; i < n; ++i)
    {
        for (int64_t j = i + 1; j < n; ++j)
        {
            if (distance(P[i], P[j]) < minimum)
            {
                minimum = distance(P[i], P[j]);
            }
        }
    }
    return minimum;
}

float closePointss(Point* P, int64_t n)
{
    if (n <= 3)
    {
        return Simple_Algos(P, n);
    }

    int64_t middle = n / 2;
    Point middle_point = P[middle];

    float dl = closePointss(P, middle);
    float dr = closePointss(P + middle, n - middle);
    float d = std::min(dl, dr);

    std::vector<Point> strip;
    for (int64_t i = 0; i < n; i++)
    {
        if (std::abs(P[i].x - middle_point.x) < d)
        {
            strip.push_back(P[i]);
        }
    }

    std::sort(strip.begin(), strip.end(), [](const Point& p1, const Point& p2) {
        return p1.y < p2.y;
    });

    float min_distance = d;
    int64_t strip_size = strip.size();
    for (int64_t i = 0; i < strip_size; ++i)
    {
        for (int64_t j = i + 1; j < strip_size && (strip[j].y - strip[i].y) < min_distance; ++j)
        {
            if (distance(strip[i], strip[j]) < min_distance)
            {
                min_distance = distance(strip[i], strip[j]);
            }
        }
    }

    return min_distance;
}

float closest(Point* P, int64_t n)
{
    std::sort(P, P + n, [](const Point& p1, const Point& p2) {
        return p1.x < p2.x;
    });
    return closePointss(P, n);
}

int main()
{
    std::ifstream in("input.txt");
    int64_t a, b;
    std::vector<Point> points;
    while (in >> a)
    {
        in >> b;
        Point p;
        p.x = a;
        p.y = b;
        points.push_back(p);
    }
    in.close();

    int64_t n = points.size();
    Point* P = new Point[n];
    for (int64_t i = 0; i < n; ++i)
    {
        P[i] = points[i];
    }
    std::cout << int64_t(closest(P, n));

    delete[] P;
    return 0;
}