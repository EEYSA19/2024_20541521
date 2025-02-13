#include <iostream>
#include <sstream>
#include "adder.h"

/**
 * @file main.cpp
 * @brief A simple command-line calculator that adds two integers.
 *
 * This program takes two command-line arguments, converts them into integers,
 * and prints their sum using the `add` function from `adder.h`.
 */

/**
 * @brief Main function for the calculator program.
 *
 * This function reads two integers from command-line arguments,
 * converts them using stringstreams, and prints the sum.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments (expects two integers).
 * @return Returns 0 on success, 1 if invalid input.
 */
int main(int argc, char *argv[]) {
    if (argc != 3) return 1;  ///< Ensure exactly two arguments are provided.

    int a, b;
    
    // Convert input arguments from strings to integers
    std::stringstream ssa(argv[1]);
    std::stringstream ssb(argv[2]);
    ssa >> a;
    ssb >> b;

    // Print the sum of the two numbers
    std::cout << add(a, b) << std::endl;

    return 0;
}

