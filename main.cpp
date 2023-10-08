#include <iostream>
#include <string>
#include <stack>

std::string Decode(const std::string& input, size_t& i) {
    std::string res;
    while (i < input.size() && input[i] != ']') {
        if (isdigit(input[i])) {
            int counter = input[i] - 48;
            i += 2;
            std::string sub = Decode(input, i);
            for (int j = 0; j < counter; ++j) res += sub;
        } else {
            res += input[i];
            ++i;
        }
    }
    ++i;
    return res;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::string input;
    getline(std::cin, input);
    size_t i = 0;
    std::cout << Decode(input, i);
    return 0;
}
//finally version (little short)