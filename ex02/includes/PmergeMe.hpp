#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <sstream>
#include <ctime>

#define RESET   "\033[0m"
#define G   "\033[32m"
#define R     "\033[31m"
#define Y     "\033[33m"

class PmergeMe {
public:
    PmergeMe();
    PmergeMe(const PmergeMe &source);
    PmergeMe &operator=(const PmergeMe &original_copy);
    ~PmergeMe();

    void processInput(char **argv);
    void sortVectorTime(std::vector<int> &arr);
    void sortDequeTime(std::deque<int> &arr);

private:
    void FordJohnSon_Algo(std::vector<int> &arr);
    void FordJohnSon_Algo(std::deque<int> &arr);
};

#endif
