#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <stack>

namespace utils {
    template <typename T>
    // returns true if the vector contains the element
    bool contains(const std::vector<T>& vec, const T& elem) {
        return std::find(vec.begin(), vec.end(), elem) != vec.end();
    }
    template <typename T>
    bool contains(const std::stack<T>& stack, const T& elem) {
        return std::find(stack.begin(), stack.end(), elem) != stack.end();
    }
    template <typename T>
    std::vector<T> flip(const std::vector<T>& vec) {
        std::vector<T> flipped;
        for (int i = vec.size() - 1; i >= 0; i--) {
            flipped.push_back(vec[i]);
        }
        return flipped;
    }
}

#endif // UTILS_HPP