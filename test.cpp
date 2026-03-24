#include "int2048.h"
#include <iostream>

using namespace sjtu;

int main() {
    // Test constructors
    int2048 a;
    int2048 b(123456789LL);
    int2048 c("9876543210123456789");

    std::cout << "Testing constructors:\n";
    std::cout << "a = "; a.print(); std::cout << "\n";
    std::cout << "b = "; b.print(); std::cout << "\n";
    std::cout << "c = "; c.print(); std::cout << "\n\n";

    // Test addition
    int2048 d = b + c;
    std::cout << "b + c = "; d.print(); std::cout << "\n";

    // Test subtraction
    int2048 e = c - b;
    std::cout << "c - b = "; e.print(); std::cout << "\n";

    // Test multiplication
    int2048 f = b * c;
    std::cout << "b * c = "; f.print(); std::cout << "\n";

    // Test division
    int2048 g("10000000000000000000");
    int2048 h("3");
    int2048 i = g / h;
    std::cout << g << " / " << h << " = " << i << "\n";

    // Test floor division with negative numbers
    int2048 j(-10LL);
    int2048 k(3LL);
    int2048 l = j / k;
    std::cout << j << " / " << k << " = " << l << "\n";

    int2048 m(10LL);
    int2048 n(-3LL);
    int2048 o = m / n;
    std::cout << m << " / " << n << " = " << o << "\n";

    int2048 p(-10LL);
    int2048 q(-3LL);
    int2048 r = p / q;
    std::cout << p << " / " << q << " = " << r << "\n";

    // Test comparison
    std::cout << "\nComparisons:\n";
    std::cout << b << " < " << c << " = " << (b < c ? "true" : "false") << "\n";
    std::cout << b << " > " << c << " = " << (b > c ? "true" : "false") << "\n";
    std::cout << b << " == " << b << " = " << (b == b ? "true" : "false") << "\n";

    // Test stream operators
    std::cout << "\nStream operators:\n";
    int2048 x, y;
    std::cout << "Enter two numbers: ";
    std::cin >> x >> y;
    std::cout << x << " + " << y << " = " << (x + y) << "\n";
    std::cout << x << " - " << y << " = " << (x - y) << "\n";
    std::cout << x << " * " << y << " = " << (x * y) << "\n";
    std::cout << x << " / " << y << " = " << (x / y) << "\n";
    std::cout << x << " % " << y << " = " << (x % y) << "\n";

    return 0;
}
