#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
const int TFS = 256;
int digit_TFS(int number, int n) {
    for (auto i = 0; i < n; ++i) number /= 256;
    return number % TFS;
}

void sort_TFS_digit(std::vector<int>& v, int n) {
    std::vector<std::queue<int>> bucket(TFS);
    std::for_each(v.begin(), v.end(), [&](int _value) {bucket[digit_TFS(_value, n)].push(_value);});
    int i = 0;
    std::for_each(bucket.begin(), bucket.end(), [&](auto& _value){while(!_value.empty()) v[i++] = _value.front(), _value.pop();});
}

void radixSort(std::vector<int>& vec) {
    std::vector<int> positives;
    std::vector<int> negatives;
    std::for_each(vec.begin(), vec.end(), [&positives](int& _value){ if(_value >= 0) positives.push_back(_value);});
    negatives.reserve(vec.size() - positives.size());
    std::for_each(vec.begin(), vec.end(), [&](int& _value) { if (_value < 0) negatives.push_back(-_value);});
    for (int i = 0; i < 5; ++i) sort_TFS_digit(positives, i), sort_TFS_digit(negatives, i);
    int i = 0;
    std::for_each(negatives.crbegin(), negatives.crend(), [&](int _value) {vec[i++] = -_value;});
    std::for_each(positives.begin(), positives.end(), [&](int & _value){vec[i++] = _value;});
}


int main() {
    int n;
    std::cin >> n;
    std::vector<int> v(n);
    std::for_each(v.begin(), v.end(), [](int &_value){std::cin >> _value;});
    radixSort(v);
    std::for_each(v.begin(), v.end(), [](int &_value){std::cout << _value << " ";});
    return 0;
}