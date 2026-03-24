



// Integer 1:
// Implement a signed big integer class that only needs to support simple addition and subtraction

// Integer 2:
// Implement a signed big integer class that supports addition, subtraction, multiplication, and division, and overload related operators

// Do not use any header files other than the following
#include <complex>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

// Do not use "using namespace std;"

namespace sjtu {
class int2048 {
private:
  bool sign;  // true for negative, false for positive or zero
  std::vector<int> val;  // digits in base 10^9, little-endian order

  // Helper function to remove leading zeros
  void clean();

  // Compare absolute values: returns -1 if |this| < |other|, 0 if equal, 1 if |this| > |other|
  int abs_compare(const int2048 &other) const;

public:
  // Constructors
  int2048();
  int2048(long long);
  int2048(const std::string &);
  int2048(const int2048 &);

  // The parameter types of the following functions are for reference only, you can choose to use constant references or not
  // If needed, you can add other required functions yourself
  // ===================================
  // Integer1
  // ===================================

  // Read a big integer
  void read(const std::string &);
  // Output the stored big integer, no need for newline
  void print();

  // Add a big integer
  int2048 &add(const int2048 &);
  // Return the sum of two big integers
  friend int2048 add(int2048, const int2048 &);

  // Subtract a big integer
  int2048 &minus(const int2048 &);
  // Return the difference of two big integers
  friend int2048 minus(int2048, const int2048 &);

  // ===================================
  // Integer2
  // ===================================

  int2048 operator+() const;
  int2048 operator-() const;

  int2048 &operator=(const int2048 &);

  int2048 &operator+=(const int2048 &);
  friend int2048 operator+(int2048, const int2048 &);

  int2048 &operator-=(const int2048 &);
  friend int2048 operator-(int2048, const int2048 &);

  int2048 &operator*=(const int2048 &);
  friend int2048 operator*(int2048, const int2048 &);

  int2048 &operator/=(const int2048 &);
  friend int2048 operator/(int2048, const int2048 &);

  int2048 &operator%=(const int2048 &);
  friend int2048 operator%(int2048, const int2048 &);

  friend std::istream &operator>>(std::istream &, int2048 &);
  friend std::ostream &operator<<(std::ostream &, const int2048 &);

  friend bool operator==(const int2048 &, const int2048 &);
  friend bool operator!=(const int2048 &, const int2048 &);
  friend bool operator<(const int2048 &, const int2048 &);
  friend bool operator>(const int2048 &, const int2048 &);
  friend bool operator<=(const int2048 &, const int2048 &);
  friend bool operator>=(const int2048 &, const int2048 &);
};
} // namespace sjtu



#include <algorithm>
#include <cmath>

namespace sjtu {

// Constants for digit compression
const int BASE = 1000000000;  // 10^9
const int BASE_DIGITS = 9;

// Helper function to remove leading zeros
void int2048::clean() {
    while (val.size() > 1 && val.back() == 0) {
        val.pop_back();
    }
    if (val.size() == 1 && val[0] == 0) {
        sign = false;  // Zero is not negative
    }
}

// Default constructor
int2048::int2048() : sign(false), val(1, 0) {}

// Constructor from long long
int2048::int2048(long long x) {
    if (x < 0) {
        sign = true;
        x = -x;
    } else {
        sign = false;
    }
    if (x == 0) {
        val = {0};
    } else {
        while (x > 0) {
            val.push_back(x % BASE);
            x /= BASE;
        }
    }
}

// Constructor from string
int2048::int2048(const std::string &s) {
    read(s);
}

// Copy constructor
int2048::int2048(const int2048 &other) : sign(other.sign), val(other.val) {}

// Read from string
void int2048::read(const std::string &s) {
    val.clear();
    sign = false;

    size_t start = 0;
    if (s[0] == '-') {
        sign = true;
        start = 1;
    } else if (s[0] == '+') {
        start = 1;
    }

    // Find first non-zero digit
    while (start < s.size() && s[start] == '0') {
        start++;
    }

    if (start == s.size()) {
        // All zeros
        sign = false;
        val = {0};
        return;
    }

    // Parse digits from right to left
    for (int i = (int)s.size() - 1; i >= (int)start; i -= BASE_DIGITS) {
        int num = 0;
        for (int j = std::max((int)start, i - BASE_DIGITS + 1); j <= i; ++j) {
            num = num * 10 + (s[j] - '0');
        }
        val.push_back(num);
    }

    clean();
}

// Print the big integer
void int2048::print() {
    if (sign) {
        std::cout << '-';
    }
    std::cout << val.back();
    for (int i = (int)val.size() - 2; i >= 0; --i) {
        std::cout.width(BASE_DIGITS);
        std::cout.fill('0');
        std::cout << val[i];
    }
}

// Compare absolute values
int int2048::abs_compare(const int2048 &other) const {
    if (val.size() != other.val.size()) {
        return val.size() < other.val.size() ? -1 : 1;
    }
    for (int i = (int)val.size() - 1; i >= 0; --i) {
        if (val[i] != other.val[i]) {
            return val[i] < other.val[i] ? -1 : 1;
        }
    }
    return 0;
}

// Addition (in-place)
int2048 &int2048::add(const int2048 &other) {
    if (sign == other.sign) {
        // Same sign: add absolute values
        int carry = 0;
        size_t max_len = std::max(val.size(), other.val.size());
        val.resize(max_len);

        for (size_t i = 0; i < max_len || carry; ++i) {
            if (i == val.size()) {
                val.push_back(0);
            }
            long long sum = val[i] + (i < other.val.size() ? other.val[i] : 0) + carry;
            val[i] = sum % BASE;
            carry = sum / BASE;
        }
    } else {
        // Different signs: subtract smaller absolute value from larger
        int cmp = abs_compare(other);
        if (cmp == 0) {
            // Equal absolute values, result is zero
            sign = false;
            val = {0};
        } else if (cmp > 0) {
            // |this| > |other|, keep this's sign
            int borrow = 0;
            for (size_t i = 0; i < val.size(); ++i) {
                long long diff = val[i] - (i < other.val.size() ? other.val[i] : 0) - borrow;
                if (diff < 0) {
                    diff += BASE;
                    borrow = 1;
                } else {
                    borrow = 0;
                }
                val[i] = diff;
            }
            clean();
        } else {
            // |this| < |other|, use other's sign
            int2048 temp = other;
            temp.minus(*this);
            *this = temp;
        }
    }
    return *this;
}

// Return sum of two big integers
int2048 add(int2048 a, const int2048 &b) {
    return a.add(b);
}

// Subtraction (in-place)
int2048 &int2048::minus(const int2048 &other) {
    if (sign != other.sign) {
        // Different signs: add absolute values
        int carry = 0;
        size_t max_len = std::max(val.size(), other.val.size());
        val.resize(max_len);

        for (size_t i = 0; i < max_len || carry; ++i) {
            if (i == val.size()) {
                val.push_back(0);
            }
            long long sum = val[i] + (i < other.val.size() ? other.val[i] : 0) + carry;
            val[i] = sum % BASE;
            carry = sum / BASE;
        }
    } else {
        // Same sign: subtract smaller absolute value from larger
        int cmp = abs_compare(other);
        if (cmp == 0) {
            // Equal absolute values, result is zero
            sign = false;
            val = {0};
        } else if (cmp > 0) {
            // |this| > |other|, sign stays the same
            int borrow = 0;
            for (size_t i = 0; i < val.size(); ++i) {
                long long diff = val[i] - (i < other.val.size() ? other.val[i] : 0) - borrow;
                if (diff < 0) {
                    diff += BASE;
                    borrow = 1;
                } else {
                    borrow = 0;
                }
                val[i] = diff;
            }
            clean();
        } else {
            // |this| < |other|, result has opposite sign
            // Compute |other| - |this|
            int2048 temp = other;
            // Temporarily make both positive for subtraction
            bool temp_sign = temp.sign;
            temp.sign = false;
            int2048 this_abs = *this;
            this_abs.sign = false;

            // Subtract absolute values
            int borrow = 0;
            size_t max_len = std::max(temp.val.size(), this_abs.val.size());
            temp.val.resize(max_len);

            for (size_t i = 0; i < max_len; ++i) {
                long long diff = temp.val[i] - (i < this_abs.val.size() ? this_abs.val[i] : 0) - borrow;
                if (diff < 0) {
                    diff += BASE;
                    borrow = 1;
                } else {
                    borrow = 0;
                }
                temp.val[i] = diff;
            }
            temp.clean();

            // Result has opposite sign of original
            temp.sign = !temp_sign;
            *this = temp;
        }
    }
    return *this;
}

// Return difference of two big integers
int2048 minus(int2048 a, const int2048 &b) {
    return a.minus(b);
}

// Unary plus
int2048 int2048::operator+() const {
    return *this;
}

// Unary minus
int2048 int2048::operator-() const {
    int2048 result = *this;
    if (result.val.size() == 1 && result.val[0] == 0) {
        result.sign = false;
    } else {
        result.sign = !result.sign;
    }
    return result;
}

// Assignment operator
int2048 &int2048::operator=(const int2048 &other) {
    if (this != &other) {
        sign = other.sign;
        val = other.val;
    }
    return *this;
}

// Compound assignment operators
int2048 &int2048::operator+=(const int2048 &other) {
    return add(other);
}

int2048 &int2048::operator-=(const int2048 &other) {
    return minus(other);
}

// Multiplication using simple O(n*m) algorithm (can be optimized with FFT)
int2048 &int2048::operator*=(const int2048 &other) {
    if (val.size() == 1 && val[0] == 0) {
        return *this;
    }
    if (other.val.size() == 1 && other.val[0] == 0) {
        sign = false;
        val = {0};
        return *this;
    }

    bool new_sign = sign ^ other.sign;
    std::vector<int> result(val.size() + other.val.size(), 0);

    for (size_t i = 0; i < val.size(); ++i) {
        long long carry = 0;
        for (size_t j = 0; j < other.val.size() || carry; ++j) {
            long long prod = result[i + j] + (long long)val[i] * (j < other.val.size() ? other.val[j] : 0) + carry;
            result[i + j] = prod % BASE;
            carry = prod / BASE;
        }
    }

    sign = new_sign;
    val = result;
    clean();
    return *this;
}

// Division using long division algorithm
int2048 &int2048::operator/=(const int2048 &other) {
    if (other.val.size() == 1 && other.val[0] == 0) {
        // Division by zero - undefined behavior as per problem statement
        return *this;
    }

    if (val.size() == 1 && val[0] == 0) {
        return *this;
    }

    // Handle special cases
    int cmp = abs_compare(other);
    if (cmp < 0) {
        sign = false;
        val = {0};
        return *this;
    }
    if (cmp == 0) {
        sign = sign ^ other.sign;
        val = {1};
        return *this;
    }

    // Use long division algorithm
    bool new_sign = sign ^ other.sign;
    int2048 abs_this = *this;
    abs_this.sign = false;
    int2048 abs_other = other;
    abs_other.sign = false;

    // Build quotient from most significant to least significant
    std::vector<int> quotient_val;
    int2048 remainder;

    // Process from most significant to least significant
    for (int i = (int)abs_this.val.size() - 1; i >= 0; --i) {
        // Shift remainder left by one digit and add current digit
        // remainder = remainder * BASE + current_digit
        remainder *= int2048(BASE);
        remainder += int2048((long long)abs_this.val[i]);
        remainder.clean();

        // Find the largest digit d such that d * abs_other <= remainder
        int d = 0;
        int lo = 0, hi = BASE - 1;

        while (lo <= hi) {
            int mid = (lo + hi) / 2;

            // Compute mid * abs_other
            long long carry = 0;
            std::vector<int> product;
            for (size_t j = 0; j < abs_other.val.size() || carry; ++j) {
                long long p = carry;
                if (j < abs_other.val.size()) {
                    p += (long long)mid * abs_other.val[j];
                }
                product.push_back(p % BASE);
                carry = p / BASE;
            }

            // Compare product with remainder
            bool less_or_equal = true;
            if (product.size() > remainder.val.size()) {
                less_or_equal = false;
            } else if (product.size() == remainder.val.size()) {
                for (int j = (int)product.size() - 1; j >= 0; --j) {
                    if (product[j] > remainder.val[j]) {
                        less_or_equal = false;
                        break;
                    } else if (product[j] < remainder.val[j]) {
                        break;
                    }
                }
            }

            if (less_or_equal) {
                d = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }

        // Add digit to quotient (will reverse later)
        quotient_val.push_back(d);

        // Subtract d * abs_other from remainder
        if (d > 0) {
            long long carry = 0;
            for (size_t j = 0; j < remainder.val.size(); ++j) {
                long long sub = (long long)remainder.val[j] - carry;
                if (j < abs_other.val.size()) {
                    sub -= (long long)d * abs_other.val[j];
                }
                if (sub < 0) {
                    long long borrow = ((-sub) + BASE - 1) / BASE;
                    carry = borrow;
                    sub += borrow * BASE;
                } else {
                    carry = 0;
                }
                remainder.val[j] = sub;
            }
            remainder.clean();
        }
    }

    // Reverse quotient since we built it from MSB to LSB
    std::reverse(quotient_val.begin(), quotient_val.end());

    sign = new_sign;
    val = quotient_val;
    clean();

    // Floor division adjustment for negative results
    if (new_sign && (val.size() > 1 || val[0] != 0)) {
        // Check if there's a remainder
        int2048 product = *this * abs_other;
        if (product.abs_compare(abs_this) != 0) {
            // There's a remainder, so we need to subtract 1 for floor division
            *this -= int2048(1LL);
        }
    }

    return *this;
}

int2048 &int2048::operator%=(const int2048 &other) {
    int2048 quotient = *this / other;
    *this = *this - quotient * other;
    return *this;
}

// Binary operators
int2048 operator+(int2048 a, const int2048 &b) {
    return a += b;
}

int2048 operator-(int2048 a, const int2048 &b) {
    return a -= b;
}

int2048 operator*(int2048 a, const int2048 &b) {
    return a *= b;
}

int2048 operator/(int2048 a, const int2048 &b) {
    return a /= b;
}

int2048 operator%(int2048 a, const int2048 &b) {
    return a %= b;
}

// Stream operators
std::istream &operator>>(std::istream &is, int2048 &num) {
    std::string s;
    is >> s;
    num.read(s);
    return is;
}

std::ostream &operator<<(std::ostream &os, const int2048 &num) {
    if (num.sign) {
        os << '-';
    }
    os << num.val.back();
    for (int i = (int)num.val.size() - 2; i >= 0; --i) {
        char buf[10];
        std::sprintf(buf, "%09d", num.val[i]);
        os << buf;
    }
    return os;
}

// Comparison operators
bool operator==(const int2048 &a, const int2048 &b) {
    if (a.sign != b.sign) {
        return false;
    }
    if (a.val.size() != b.val.size()) {
        return false;
    }
    for (size_t i = 0; i < a.val.size(); ++i) {
        if (a.val[i] != b.val[i]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const int2048 &a, const int2048 &b) {
    return !(a == b);
}

bool operator<(const int2048 &a, const int2048 &b) {
    if (a.sign != b.sign) {
        return a.sign;  // negative < positive
    }
    int cmp = a.abs_compare(b);
    if (a.sign) {
        return cmp > 0;  // For negative numbers, larger absolute value is smaller
    }
    return cmp < 0;
}

bool operator>(const int2048 &a, const int2048 &b) {
    return b < a;
}

bool operator<=(const int2048 &a, const int2048 &b) {
    return !(a > b);
}

bool operator>=(const int2048 &a, const int2048 &b) {
    return !(a < b);
}

} // namespace sjtu
