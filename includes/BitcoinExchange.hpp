#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <cstdlib>
#include <iomanip>

typedef std::string str;

class BitcoinExchange {
private:
    std::map<str, float> _map;
    int *_input;
    int _inputSize;

    void _parseData(std::ifstream &file);
    void _parseInput(std::ifstream &file);
    void _output(std::ifstream &file);
    int _getInputSize(std::ifstream &file) const;
    
    bool _checkDate(str line);
    bool _checkPositive(str line);
    bool _checkTooLarge(str line);
    void _nearestDate(str &key);

public:
    BitcoinExchange();
    BitcoinExchange(std::ifstream &file, char **av);
    BitcoinExchange(BitcoinExchange const &src);
    ~BitcoinExchange();
    BitcoinExchange &operator=(BitcoinExchange const &rSym);

    void printMap() const;
};

#endif
