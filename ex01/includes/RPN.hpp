#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <sstream>
#include <stdexcept>

typedef std::string str;

class RPN {
public:
    RPN();                     
    RPN(const RPN &source);   
    RPN &operator=(const RPN &original_copy);
    ~RPN();

    int RPN_algorithm(const str &expression);

private:
    std::stack<int> stack_obj;
    bool confirm_op(const str &token); 
    int apply_operator(int a, int b, char op); 
};

#endif
