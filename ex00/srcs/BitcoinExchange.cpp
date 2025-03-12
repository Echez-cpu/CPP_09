#include "../includes/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() : input_array(NULL), input_size(0) {}

BitcoinExchange::BitcoinExchange(std::ifstream &file, char **argv) {
    (void)argv;
   
    std::ifstream data("data.csv", std::ifstream::in);
    if (!data) {
        std::cerr << "Error: could not open database file.\n";
        exit(1);
    }
    this->parsing(data);
    data.close();

    this->input_size = this->get_input_size(file) - 1;  // deal withe empty file case
    this->input_array = new int[this->input_size]();

    this->parse_input(file);
    
    file.clear();
    file.seekg(0, std::ios::beg);    
   
    this->check_output(file);
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &source) {
    this->map_obj = source.map_obj;
    this->input_size = source.input_size;
    this->input_array = new int[this->input_size];
    for (int i = 0; i < this->input_size; i++)
        this->input_array[i] = source.input_array[i];
}

BitcoinExchange::~BitcoinExchange() {
    delete[] this->input_array;
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &original_copy) {
    if (this != &original_copy) {
        delete[] this->input_array;
        this->map_obj = original_copy.map_obj;
        this->input_size = original_copy.input_size;
        this->input_array = new int[this->input_size];
        for (int i = 0; i < this->input_size; i++)
            this->input_array[i] = original_copy.input_array[i];
    }
    return *this;
}

void BitcoinExchange::parsing(std::ifstream &file) {
    str line, key, value;
    float f;

    getline(file, line); // Skip header
    while (getline(file, line)) {
        std::istringstream s(line);
        if (!getline(s, key, ',') || !getline(s, value))
            continue; 

        f = atof(value.c_str());
        if (!value.empty())
            this->map_obj[key] = f;
    }
}

void BitcoinExchange::parse_input(std::ifstream &file) {
    str line;
    int i = 0;
    getline(file, line); // Skip header

    while (getline(file, line) && i < this->input_size) {
        this->input_array[i] = 0;
        if (!check_positive(line)) this->input_array[i] = 1;
        if (!check_date(line) || line.length() < 11) this->input_array[i] = 2;
        if (this->input_array[i] == 0 && !check_if_too_large(line)) this->input_array[i] = 3;
        i++;
    }
}

void BitcoinExchange::check_output(std::ifstream &file) {
    str line, key, value;
    int i = 0;
    getline(file, line);

    while (i < this->input_size && getline(file, line)) {
        std::istringstream s(line);
        getline(s, key, '|'); key = trim(key);
        getline(s, value, '|'); value = trim(value);

        if (input_array[i] == 0) {
            if (map_obj.find(key) == map_obj.end()) nearest_date(key);
            if (key == "Error: Year too old.")
                std::cout << key << std::endl;
            else
                std::cout << key << " => " << value << " = " << atof(value.c_str()) * map_obj[key] << std::endl;
        } else if (input_array[i] == 1)
            std::cout << "Error: not a positive number." << std::endl;
        else if (input_array[i] == 2)
            std::cout << "Error: bad input => " << key << std::endl;
        else if (input_array[i] == 3)
            std::cout << "Error: too large a number." << std::endl;
        i++;
    }
}

bool BitcoinExchange::check_date(str line) {
    std::istringstream s(line);
    str date;
    int year, month, day;

    getline(s, date, '|');
    date = trim(date);

    if (sscanf(date.c_str(), "%d-%d-%d", &year, &month, &day) != 3)
        return false;

    if (year < 2009 || year > 2023 || month < 1 || month > 12 || day < 1 || day > 31)
        return false;

    static const int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (day > daysInMonth[month - 1] && !(month == 2 && day == 29 && (year % 4 == 0)))
        return false;

    return true;
}

bool BitcoinExchange::check_positive(str line) {
    std::istringstream s(line);
    str value;

    getline(s, value, '|');
    getline(s, value, '|');
    value = trim(value);

    if (value.empty() || value.find('-') != str::npos)
        return false;

    for (size_t i = 0; i < value.size(); i++) {
        if (!isdigit(value[i]) && value[i] != '.' && value[i] != 'f')
            return false;
    }

    float f = atof(value.c_str());
    return (f >= 0);
}



bool BitcoinExchange::check_if_too_large(str line) {
    std::istringstream s(line);
    str value;
    float f;

    getline(s, value, '|');
    getline(s, value, '|');

    f = atof(value.c_str());
    return (f >= 0.0 && f <= 1000.0);
}



void BitcoinExchange::nearest_date(str &key) {
    std::map<str, float>::iterator it = map_obj.lower_bound(key);
    if (it == map_obj.begin()) {  
        key = "Error: Year too old.";
        return;
    }

    if (it == map_obj.end() || it->first != key)
        --it;

    key = it->first;
}


int BitcoinExchange::get_input_size(std::ifstream &file) const {
    int count = 0;
    str line;

    file.clear();
    file.seekg(0, std::ios::beg);

    while (std::getline(file, line)) {
        count++;
    }

    file.clear();
    file.seekg(0, std::ios::beg);

    return count;
}

str		BitcoinExchange::trim(const str & string)
{
    size_t first = string.find_first_not_of(' ');
    if (str::npos == first)
    {
        return string;
    }
    size_t last = string.find_last_not_of(' ');
    return string.substr(first, (last - first + 1));
}


