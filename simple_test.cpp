#include "int2048.h"
#include <iostream>

using namespace sjtu;

int main() {
    std::cout << "Test 1: Default constructor\n";
    int2048 a;
    std::cout << "a = " << a << "\n";

    std::cout << "\nTest 2: Constructor from long long\n";
    int2048 b(123456789LL);
    std::cout << "b = " << b << "\n";

    std::cout << "\nTest 3: Constructor from string\n";
    int2048 c("9876543210123456789");
    std::cout << "c = " << c << "\n";

    std::cout << "\nTest 4: Addition\n";
    int2048 d = b + c;
    std::cout << "b + c = " << d << "\n";

    std::cout << "\nTest 5: Subtraction\n";
    int2048 e = c - b;
    std::cout << "c - b = " << e << "\n";

    std::cout << "\nAll tests passed!\n";
    return 0;
}
