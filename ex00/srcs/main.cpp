#include "../includes/BitcoinExchange.hpp"

str		trim(const str & string)
{
    size_t first = string.find_first_not_of(' ');
    if (str::npos == first)
    {
        return string;
    }
    size_t last = string.find_last_not_of(' ');
    return string.substr(first, (last - first + 1));
}



void testInput(std::ifstream &file, int argc, char **argv) {
    if (argc != 2)
        throw std::runtime_error("Error: Usage: ./btc [filename.txt]");
    
    file.open(argv[1], std::ifstream::in);
    if (!file.is_open())
        throw std::runtime_error("Error: Could not open file: " + str(argv[1]));

    str line;
    bool isEmpty = true;
    
    while (getline(file, line)) {
        if (!line.empty())
            isEmpty = false;
    }
    
    if (isEmpty)
        throw std::runtime_error("Error: Empty line in input file.");
    
    file.clear();       
    file.seekg(0, std::ios::beg);
}



int	main(int argc, char **argv) {
	std::ifstream		file;
	BitcoinExchange *	exchange;
	
	try {
		testInput(file, argc, argv);
		exchange = new BitcoinExchange(file, argv);
	}
	catch (const std::exception & e) {
		std::cout << e.what() << std::endl;
		return 1;
	}

	delete exchange;
	return 0;
}
