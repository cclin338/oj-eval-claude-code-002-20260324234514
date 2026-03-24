#include "int2048.h"
#include <iostream>

using namespace sjtu;

int main() {
    std::cout << "Test 1: Simple division\n";
    int2048 a("10000000000000000000");
    int2048 b("3");
    int2048 c = a / b;
    std::cout << a << " / " << b << " = " << c << "\n";

    std::cout << "\nTest 2: Division with negative numbers\n";
    int2048 d(-10LL);
    int2048 e(3LL);
    int2048 f = d / e;
    std::cout << d << " / " << e << " = " << f << "\n";

    int2048 g(10LL);
    int2048 h(-3LL);
    int2048 i = g / h;
    std::cout << g << " / " << h << " = " << i << "\n";

    int2048 j(-10LL);
    int2048 k(-3LL);
    int2048 l = j / k;
    std::cout << j << " / " << k << " = " << l << "\n";

    std::cout << "\nAll division tests passed!\n";
    return 0;
}
