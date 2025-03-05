#ifndef     BITCOINEXCHANGE_HPP
#define     BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <cstdlib>
#include <iomanip>

typedef std::string str;

class BitcoinExchange {


public:
    BitcoinExchange();
    BitcoinExchange(std::ifstream &file, char **argv);
    BitcoinExchange(BitcoinExchange const &source);
    ~BitcoinExchange();
    BitcoinExchange &operator=(BitcoinExchange const &original_copy);

private:
    std::map<str, float> map_obj;
    int *    input_array;
    int      input_size;

    void   parsing(std::ifstream &file);
    void parse_input(std::ifstream &file);
    void out_put(std::ifstream &file);
    int get_input_size(std::ifstream &file) const;
    
    bool check_date(str line);
    bool check_positive(str line);
    bool check_if_too_large(str line);
    void nearest_date(str &key);

    void printMap() const;
};

#endif
