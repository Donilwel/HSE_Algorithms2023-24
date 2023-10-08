#include <algorithm>
#include <vector>
#include <iostream>

size_t CountArrayRotations(std::vector<int>& array) {
    std::vector<int> array_b = array;
    std::vector<std::vector<int>> vec_of_vecs;
    std::vector<int> coun;
    for(size_t i = 0; i < array_b.size(); ++i) {
        size_t counter_unique = 0;
        std::rotate(array_b.rbegin(), array_b.rbegin()+1, array_b.rend());
        vec_of_vecs.push_back(array_b);
        //for(size_t j = 0; j < array_b.size(); ++j){
        //    if(array_b[j] != array[j]) {
        //        counter_unique++;
        //    }
        //}
        //coun.push_back(counter_unique);
    }
    std::sort(vec_of_vecs.begin(), vec_of_vecs.end());
    auto last = std::unique(vec_of_vecs.begin(), vec_of_vecs.end());
    vec_of_vecs.erase(last, vec_of_vecs.end());
    for(size_t i = 0; i < vec_of_vecs.size(); ++i) {
        size_t counter_unique = 0;
        for(int j = 0; j < array_b.size(); ++j) {
            if(vec_of_vecs[i][j] != array_b[j]) {
                counter_unique++;
            }
        }
        coun.push_back(counter_unique);
    }
    int max_element = coun[0];
    int count = 0;

    for (int i = 1; i < coun.size(); i++) {
        if (coun[i] > max_element) {
            max_element = coun[i];
        }
    }
    for(int i = 0; i < coun.size(); i++) {
        if (coun[i] == max_element) {
            count++;
        }
    }
    return count;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    size_t size;
    std::cin >> size;
    std::vector<int> array(size);
    for (size_t i = 0; i < size; ++i) {
        std::cin >> array[i];
    }
    std::cout << CountArrayRotations(array);
    return 0;
}
