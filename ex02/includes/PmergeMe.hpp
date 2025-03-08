#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <sstream>
#include <ctime>

class PmergeMe {
public:
    PmergeMe();
    PmergeMe(const PmergeMe &source);
    PmergeMe &operator=(const PmergeMe &original_copy);
    ~PmergeMe();

    void processInput(char **argv);
    void sortVector(std::vector<int> &arr);
    void sortDeque(std::deque<int> &arr);

private:
    void mergeInsertionSort(std::vector<int> &arr); // FordJohnSon_algo
    void mergeInsertionSort(std::deque<int> &arr);
};

#endif
