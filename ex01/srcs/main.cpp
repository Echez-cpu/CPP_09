#include "../includes/RPN.hpp"
#define Y     "\033[33m"
#define RESET   "\033[0m"
#define G     "\033[32m"


int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << Y << "Usage: ./RPN \"<RPN expression>\"" << RESET << std::endl;
        return 1;
    }

    try {
        RPN calculator;
        std::string expression = argv[1]; 
        std::cout << G << "Result: " << calculator.evaluate(expression) << RESET << std::endl;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
