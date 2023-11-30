#include <iostream>
#include "algorithm"
#include "vector"
void countingSort(std::vector<int> &a){
    int maxim = *std::max_element(a.begin(), a.end());
    int minim = *std::min_element(a.begin(), a.end());
    std::vector<int> c(maxim - minim + 1);
    std::for_each(a.begin(), a.end(), [&c, &minim](int &_value){++c[_value - minim];});
    int i = 0;
    for (int j = minim; j <= maxim; ++j) {
        while (c[j - minim] != 0) {
            a[i] = j;
            c[j - minim]--;
            i++;
        }
    }
    std::for_each(a.begin(), a.end(), [](int &_value){ std::cout << _value << " ";});
}
int main() {
    int n; std::cin >> n;
    if(n == 0 || n == '\0') return 0;
    std::vector <int> a(n);
    std::for_each(a.begin(), a.end(), [&a](int &_value){ std::cin >> _value;});
    countingSort(a);
}