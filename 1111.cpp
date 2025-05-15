#include <iostream>
#include <limits>
#include <optional>
#include <type_traits>
#include <cmath>

template<typename T>
class SafeArithmetic {
    static_assert(std::is_arithmetic<T>::value, "SafeArithmetic only supports arithmetic types.");
public:
    static std::optional<T> add(T a, T b) {
        if constexpr (std::is_integral<T>::value) {
            if ((b > 0 && a > std::numeric_limits<T>::max() - b) ||
                (b < 0 && a < std::numeric_limits<T>::min() - b)) {
                std::cerr << "Addition overflow or underflow detected!" << std::endl;
                return std::nullopt;
            }
            return a + b;
        }
        else if constexpr (std::is_floating_point<T>::value) {
            T result = a + b;
            if (std::isinf(result) || std::isnan(result)) {
                std::cerr << "t" << std::endl;
                return std::nullopt;
            }
            return result;
        }
        return std::nullopt;
    }

    static std::optional<T> subtract(T a, T b) {
        if constexpr (std::is_integral<T>::value) {
            if ((b < 0 && a > std::numeric_limits<T>::max() + b) ||
                (b > 0 && a < std::numeric_limits<T>::min() + b)) {
                std::cerr << "Subtraction overflow or underflow detected!" << std::endl;
                return std::nullopt;
            }
            return a - b;
        }
        else if constexpr (std::is_floating_point<T>::value) {
            T result = a - b;
            if (std::isinf(result) || std::isnan(result)) {
                std::cerr << "Invalid floating point result in subtraction!" << std::endl;
                return std::nullopt;
            }
            return result;
        }
        return std::nullopt;
    }

    static std::optional<T> multiply(T a, T b) {
        if constexpr (std::is_integral<T>::value) {
            if (a == 0 || b == 0) return 0;
            if ((a > 0 && b > 0 && a > std::numeric_limits<T>::max() / b) ||
                (a > 0 && b < 0 && b < std::numeric_limits<T>::min() / a) ||
                (a < 0 && b > 0 && a < std::numeric_limits<T>::min() / b) ||
                (a < 0 && b < 0 && a < std::numeric_limits<T>::max() / b)) {
                std::cerr << "Multiplication overflow or underflow detected!" << std::endl;
                return std::nullopt;
            }
            return a * b;
        }
        else if constexpr (std::is_floating_point<T>::value) {
            T result = a * b;
            if (std::isinf(result) || std::isnan(result)) {
                std::cerr << "Invalid floating point result in multiplication!" << std::endl;
                return std::nullopt;
            }
            return result;
        }
        return std::nullopt;
    }

    static std::optional<T> divide(T a, T b) {
        if (b == 0) {
            std::cerr << "Division by zero!" << std::endl;
            return std::nullopt;
        }

        if constexpr (std::is_integral<T>::value) {
            if (a == std::numeric_limits<T>::min() && b == -1) {
                std::cerr << "Integer division overflow!" << std::endl;
                return std::nullopt;
            }
            return a / b;
        }
        else if constexpr (std::is_floating_point<T>::value) {
            T result = a / b;
            if (std::isinf(result) || std::isnan(result)) {
                std::cerr << "Invalid floating point result in division!" << std::endl;
                return std::nullopt;
            }
            return result;
        }
        return std::nullopt;
    }
};
