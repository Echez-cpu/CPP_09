#include "../includes/RPN.hpp"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: ./RPN \"<RPN expression>\"" << std::endl;
        return 1;
    }

    try {
        RPN calculator;
        std::string expression = argv[1]; 
        std::cout << "Result: " << calculator.evaluate(expression) << std::endl;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
