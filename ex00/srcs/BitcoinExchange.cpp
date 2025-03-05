#include "../include/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() : input_arr(NULL), input_size(0) {}

BitcoinExchange::BitcoinExchange(std::ifstream &file, char **argv) {
    std::ifstream data("data.csv", std::ifstream::in);
    if (!data) {
        std::cerr << "Error: could not open database file.\n";
        exit(1);
    }
    this->parsing(data);
    data.close();

    this->input_size = this->get_input_size(file) - 1;
    this->input_arr = new int[this->input_size]();

    this->parse_input(file);
    this->out_put(file);
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &src) {
    this->map_obj = src.map_obj;
    this->input_size = src.input_size;
    this->input_arr = new int[this->_inputSize];
    for (int i = 0; i < this->_inputSize; i++)
        this->_input[i] = src._input[i];
}

BitcoinExchange::~BitcoinExchange() {
    delete[] this->_input;
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &rSym) {
    if (this != &rSym) {
        delete[] this->_input;
        this->_map = rSym._map;
        this->_inputSize = rSym._inputSize;
        this->_input = new int[this->_inputSize];
        for (int i = 0; i < this->_inputSize; i++)
            this->_input[i] = rSym._input[i];
    }
    return *this;
}

void BitcoinExchange::_parseData(std::ifstream &file) {
    str line, key, value;
    float f;

    getline(file, line); // Skip header
    while (getline(file, line)) {
        std::istringstream s(line);
        if (!getline(s, key, ',') || !getline(s, value))
            continue; 

        f = atof(value.c_str());
        if (!value.empty())
            this->_map[key] = f;
    }
}

void BitcoinExchange::_parseInput(std::ifstream &file) {
    str line;
    int i = 0;
    getline(file, line); // Skip header

    while (getline(file, line) && i < this->_inputSize) {
        this->_input[i] = 0;
        if (!_checkPositive(line)) this->_input[i] = 1;
        if (!_checkDate(line) || line.length() < 11) this->_input[i] = 2;
        if (!_checkTooLarge(line)) this->_input[i] = 3;
        i++;
    }
}

void BitcoinExchange::_output(std::ifstream &file) {
    str line, key, value;
    int i = 0;
    getline(file, line);

    while (i < this->_inputSize && getline(file, line)) {
        std::istringstream s(line);
        getline(s, key, '|'); key = ::trim(key);
        getline(s, value, '|'); value = ::trim(value);

        if (_input[i] == 0) {
            if (_map.find(key) == _map.end()) _nearestDate(key);
            if (key == "Error: Year too old.")
                std::cout << key << std::endl;
            else
                std::cout << key << " => " << value << " = " << atof(value.c_str()) * _map[key] << std::endl;
        } else if (_input[i] == 1)
            std::cout << "Error: not a positive number." << std::endl;
        else if (_input[i] == 2)
            std::cout << "Error: bad input => " << key << std::endl;
        else if (_input[i] == 3)
            std::cout << "Error: too large a number." << std::endl;
        i++;
    }
}

bool BitcoinExchange::_checkDate(str line) {
    std::istringstream s(line);
    str date;
    int year, month, day;

    getline(s, date, '|');
    date = ::trim(date);

    if (sscanf(date.c_str(), "%d-%d-%d", &year, &month, &day) != 3)
        return false;

    if (year < 2009 || year > 2023 || month < 1 || month > 12 || day < 1 || day > 31)
        return false;

    static const int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (day > daysInMonth[month - 1] && !(month == 2 && day == 29 && (year % 4 == 0)))
        return false;

    return true;
}

bool BitcoinExchange::_checkPositive(str line) {
    std::istringstream s(line);
    str value;

    getline(s, value, '|');
    getline(s, value, '|');
    value = ::trim(value);

    if (value.empty() || value.find('-') != str::npos)
        return false;

    for (size_t i = 0; i < value.size(); i++) {
        if (!isdigit(value[i]) && value[i] != '.' && value[i] != 'f')
            return false;
    }

    float f = atof(value.c_str());
    return (f > 0);
}

bool BitcoinExchange::_checkTooLarge(str line) {
    std::istringstream s(line);
    str value;
    float f;

    getline(s, value, '|');
    getline(s, value, '|');

    f = atof(value.c_str());
    return (f < static_cast<float>(__INT_MAX__));
}

void BitcoinExchange::_nearestDate(str &key) {
    std::map<str, float>::iterator it = _map.lower_bound(key);
    if (it == _map.begin()) {
        key = "Error: Year too old.";
        return;
    }
    --it;
    key = it->first;
}
