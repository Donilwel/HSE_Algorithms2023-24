#include <iostream>
#include <string>
#include <algorithm>
#include <utility>
#include <vector>

struct Number {
    std::string digits;
    Number() : digits("0") {}
    explicit Number(std::string str) : digits(std::move(str)) { clear(); }
    void clear() {
        while (!digits.empty() && (digits[0] == '0' || isdigit(digits[0])== false)) {
            digits.erase(0, 1);
        }
        if (digits.empty()) {
            digits = '0';
        }
    }

    std::string stringss(std::string first_num, std::string second_num) const {
        std::vector<int> result(first_num.size() + second_num.size(), 0);
        for (int i = first_num.size() - 1; i >= 0; i--) {
            for (int j = second_num.size() - 1; j >= 0; j--) {
                result[i + j] += ((first_num[i] - '0') * (second_num[j] - '0') + result[i + j + 1]) / 10;
                result[i + j + 1] = ((first_num[i] - '0') * (second_num[j] - '0') + result[i + j + 1]) % 10;
            }
        }
        std::string resultStr;
        for_each(result.begin(), result.end(), [&](int digit) { if (!(resultStr.empty() && digit == 0)) { resultStr.push_back(digit + '0');}});
        if (resultStr.empty()) return "0";
        else return resultStr;
    }

    Number operator+(const Number &other) {
        Number answer = *this;

        int dig = 0;
        size_t maximum = std::max(answer.digits.size(), other.digits.size());
        for (int i = 1; i <= maximum || dig; ++i) {
            if (i > answer.digits.size())
                answer.digits = '0' + answer.digits;
            int a;
            int b;

            if (i <= answer.digits.size()) a = answer.digits[answer.digits.size() - i] - '0';
            else a = 0;

            if (i <= other.digits.size()) b = other.digits[other.digits.size() - i] - '0';
            else b = 0;
            dig += a + b;
            if (dig >= 10) {
                answer.digits[answer.digits.size() - i] = static_cast<char>(dig - 10 + '0');
                dig = 1;
            } else {
                answer.digits[answer.digits.size() - i] = static_cast<char>(dig + '0');
                dig = 0;
            }
        }
        return answer;
    }

    Number operator-(const Number &other) {
        Number result = *this;
        int wigit = 0;
        for (int i = 1; i <= result.digits.size(); ++i) {
            int symbol = result.digits[result.digits.size() - i] - '0';
            int sysymb = i <= other.digits.size() ? other.digits[other.digits.size() - i] - '0' : 0;
            symbol -= wigit;
            wigit = (symbol < sysymb) ? (symbol += 10, 1) : 0; //try this srting
            result.digits[result.digits.size() - i] = static_cast<char>(symbol - sysymb + '0');
        }
        while (result.digits[0] == '0' && result.digits.size() > 1) { result.digits.erase(0, 1);}
        return result;
    }
    Number operator*(const Number &other) const {
        if (digits.size() <= 50 && other.digits.size() <= 50) {
            return Number(stringss(digits, other.digits));
        }

        Number x = *this, y = other;
        Number a_first_half, a_second_half, b_first_half, b_second_half;
        if ((std::max(x.digits.size(), y.digits.size()) / 2) >= x.digits.size()) {
            a_first_half = Number();
            a_second_half = x;
        } else {
            a_first_half = Number(x.digits.substr(0, x.digits.size() - (std::max(x.digits.size(), y.digits.size()) / 2)));
            a_second_half = Number(x.digits.substr(x.digits.size() - (std::max(x.digits.size(), y.digits.size()) / 2)));
        }
        if ((std::max(x.digits.size(), y.digits.size()) / 2) >= y.digits.size()) {
            b_first_half = Number();
            b_second_half = y;
        } else {
            b_first_half = Number(y.digits.substr(0, y.digits.size() - (std::max(x.digits.size(), y.digits.size()) / 2)));
            b_second_half = Number(y.digits.substr(y.digits.size() - (std::max(x.digits.size(), y.digits.size()) / 2)));
        }
        Number a = a_first_half * b_first_half, b = a_second_half * b_second_half, c = (a_first_half + a_second_half) * (b_first_half + b_second_half), d = c - a - b;

        a.digits += std::string(2 * (std::max(x.digits.size(), y.digits.size()) / 2), '0'); a.clear();
        d.digits += std::string((std::max(x.digits.size(), y.digits.size()) / 2), '0'); d.clear();
        return a + d + b;
    }
};

int main() {
    std::string first_digit, second_digit;
    std::cin >> first_digit >> second_digit;
    Number a(first_digit); Number b(second_digit);
    std::cout << (a * b).digits << '\n';
    return 0;
}

