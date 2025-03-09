#include "../includes/PmergeMe.hpp"

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << R << "Error: " << RESET << Y << "usage: ./PmergeMe <random ints>" << RESET << std::endl;
        return 1;
    }

    try {
        PmergeMe sorter;
        sorter.processInput(argv);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
