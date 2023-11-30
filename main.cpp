#include <iostream>
#include <vector>
#include "algorithm"
void swap(int &first, int &second){
    int tmp = first;
    first = second;
    second = tmp;
}
void heapify(std::vector<int>& arr, int size, int root_Index) {
    int largest_Index = root_Index;
    int left_Child_Index = 2 * root_Index + 1;
    int right_Child_Index = 2 * root_Index + 2;
    if (left_Child_Index < size && arr[left_Child_Index] > arr[largest_Index]) largest_Index = left_Child_Index;
    if (right_Child_Index < size && arr[right_Child_Index] > arr[largest_Index]) largest_Index = right_Child_Index;
    if (largest_Index != root_Index) swap(arr[root_Index], arr[largest_Index]), heapify(arr, size, largest_Index);
}

void buildHeap(std::vector<int>& arr) {
    int size = arr.size();
    for (int i = size / 2 - 1; i >= 0; --i) heapify(arr, size, i);
}

void heapSort(std::vector<int>& arr) {
    int size = arr.size();
    buildHeap(arr);
    for (int i = size - 1; i > 0; --i) swap(arr[0], arr[i]), heapify(arr, i, 0);
}

int main() {
    int n; std::cin >> n;
    std::vector<int> arr(n);
    std::for_each(arr.begin(), arr.end(), [](int &_value){std::cin >> _value;});
    heapSort(arr);
    std::for_each(arr.begin(), arr.end(), [](int &_value){std::cout << _value << " ";});
}