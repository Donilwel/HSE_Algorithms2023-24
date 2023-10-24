#include <iostream>
#include <algorithm>
#include <vector>

struct Interval {
    int left;
    int right;

    Interval(int first, int second): left(first), right(second){}

    size_t length() {
        auto len = right - left + 1;
        if (right >= left) return len;
        return 0;
    }

    Interval overlap(const Interval& other) {
        if (other.right < left || right < other.left ) return Interval(1,-1);
        if (left == other.left) return Interval(left, std::min(right, other.right));
        if (left < other.left) return Interval(other.left, std::min(right, other.right));
        return Interval(left, other.right);
    }

};

bool compare(Interval& left, Interval& right) {
    if (left.left < right.left) return true;
    if (left.right <= right.right && left.left == right.left ) return true;
    return false;
}
static Interval find_max_overlap (std::vector<Interval> vect) {
    if (vect.size() == 1) return Interval(0, -1);
    if (vect.size() == 2) return vect[0].overlap(vect[1]);
    std::vector<Interval> first_vec;
    auto mider = vect.size()/2;
    std::copy(vect.begin(), vect.begin() + mider, std::back_inserter(first_vec));
    std::vector<Interval> second_vec;
    std::copy(vect.begin() + mider, vect.end(), std::back_inserter(second_vec));

    Interval middle_first = find_max_overlap(first_vec);
    Interval middle_second = find_max_overlap(second_vec);

    int maxim_second = first_vec[0].right;
    Interval maxx = first_vec[0];
    for (const auto& element : first_vec) {
        if (element.right > maxim_second || element.right == maxim_second) {
            maxim_second = element.right;
            maxx = element;
        }
    }

    Interval middle_result = Interval(0, -1);
    int maxim = -1;
    for (const auto& element : second_vec) {
        Interval inter = maxx.overlap(element);
        int lena = inter.length();
        if (lena > maxim) { middle_result = maxx.overlap(element); maxim = middle_result.length();}
    }

    Interval reta = Interval(-1, 0);
    if (middle_first.length() >= middle_second.length() && middle_first.length() >= middle_result.length()) reta = middle_first;
    else if ((middle_result.length() > middle_first.length() || middle_result.length() == middle_first.length()) &&
             (middle_result.length() > middle_second.length() || middle_result.length() == middle_second.length()))
        reta = middle_result;
    else reta = middle_second;
    return reta;
}

int main() {
    int n;
    std::vector<Interval> array;
    array.reserve(n);
    std::cin >> n;
    if (n == 0) std::cout << 0;
    else {
        int first, second;
        for (int i = 0; i < n; ++i) {
            std::cin >> first >> second; array.push_back(Interval(first, second));
        }
        std::sort(array.begin(), array.end(), compare);
        Interval maxim = find_max_overlap(array);
        if (maxim.length() == 0) std::cout<<0;
        else {
            std::cout << maxim.length() << '\n' << maxim.left << ' ' << maxim.right;
        }
    }
//what
    return 0;
}