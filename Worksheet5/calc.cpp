#include <iostream>
#include <sstream>
#include "adder.h"

int main(int argc, char *argv[]) {
    if (argc != 3) return 1;

    int a, b;
    std::stringstream ssa(argv[1]);
    std::stringstream ssb(argv[2]);
    ssa >> a;
    ssb >> b;

    std::cout << add(a, b) << std::endl;
    return 0;
}

