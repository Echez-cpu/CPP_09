#include "../includes/PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &source) { (void)source; }

PmergeMe &PmergeMe::operator=(const PmergeMe &original_copy) {
    (void)original_copy;
    return *this;
}

PmergeMe::~PmergeMe() {}

void PmergeMe::FordJohnSon_Algo(std::vector<int> &arr) {
    if (arr.size() <= 1) return;

    std::vector<int> mainChain, secondaryChain;

    for (size_t i = 0; i + 1 < arr.size(); i += 2) {
        if (arr[i] > arr[i + 1]) {
            mainChain.push_back(arr[i]);
            secondaryChain.push_back(arr[i + 1]);
        } else {
            mainChain.push_back(arr[i + 1]);
            secondaryChain.push_back(arr[i]);
        }
    }

    if (arr.size() % 2 != 0) {
        mainChain.push_back(arr.back());
    }

    std::sort(mainChain.begin(), mainChain.end());

    for (size_t i = 0; i < secondaryChain.size(); i++) {
        std::vector<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), secondaryChain[i]);
        mainChain.insert(pos, secondaryChain[i]);
    }

    arr = mainChain;
}

void PmergeMe::FordJohnSon_Algo(std::deque<int> &arr) {
    if (arr.size() <= 1) return;

    std::deque<int> mainChain, secondaryChain;

    for (size_t i = 0; i + 1 < arr.size(); i += 2) {
        if (arr[i] > arr[i + 1]) {
            mainChain.push_back(arr[i]);
            secondaryChain.push_back(arr[i + 1]);
        } else {
            mainChain.push_back(arr[i + 1]);
            secondaryChain.push_back(arr[i]);
        }
    }

    if (arr.size() % 2 != 0) {
        mainChain.push_back(arr.back());
    }

    std::sort(mainChain.begin(), mainChain.end());

    for (size_t i = 0; i < secondaryChain.size(); i++) {
        std::deque<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), secondaryChain[i]);
        mainChain.insert(pos, secondaryChain[i]);
    }

    arr = mainChain;
}

void PmergeMe::sortVectorTime(std::vector<int> &arr) {
    clock_t start = clock();
    FordJohnSon_Algo(arr);
    clock_t end = clock();
    std::cout << "Time to process a range of " << arr.size() << G << " elements with std::vector: " 
              << (double)(end - start) / CLOCKS_PER_SEC * 1000000 << " us" << RESET << std::endl;
}

void PmergeMe::sortDequeTime(std::deque<int> &arr) {
    clock_t start = clock();
    FordJohnSon_Algo(arr);
    clock_t end = clock();
    std::cout << "Time to process a range of " << arr.size() << Y << " elements with std::deque: " 
              << (double)(end - start) / CLOCKS_PER_SEC * 1000000 << " us" << RESET << std::endl;
}

void PmergeMe::processInput(char **argv) {
    std::vector<int> vec;
    std::deque<int> deq;

    for (int i = 1; argv[i]; i++) {
        std::istringstream istream_str(argv[i]);
        int num;
        if (!(istream_str >> num) || num <= 0) {
            std::cerr << R << "Error" << RESET << std::endl;
            return;
        }
        vec.push_back(num);
        deq.push_back(num);
    }

    std::cout << R << "Before: " << RESET << Y << RESET;
    for (size_t i = 0; i < vec.size(); i++) std::cout << vec[i] << " ";
    std::cout << std::endl;

    FordJohnSon_Algo(vec);
    
    std::cout << G << "After: " << RESET;
    for (size_t i = 0; i < vec.size(); i++) std::cout << vec[i] << " ";
    std::cout << std::endl;

    sortVectorTime(vec);
    sortDequeTime(deq);

}
