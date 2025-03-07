#include "../includes/RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN &source) {
    *this = source;
}

RPN &RPN::operator=(const RPN &original_copy) {
    if (this != &original_copy) {  
        this->stack_obj = original_coy.stack_obj;
    }
    return *this;
}

RPN::~RPN() {}

bool RPN::confirm_op(const str &token) {
    return (token == "+" || token == "-" || token == "*" || token == "/");
}

int RPN::apply_operator(int a, int b, char op) {
    if (op == '+') return a + b;
    if (op == '-') return a - b;
    if (op == '*') return a * b;
    if (op == '/') {
        if (b == 0) throw std::runtime_error("Error: Division by zero.");
        return a / b;
    }
    throw std::runtime_error("Error: Invalid operator.");
}

int RPN::evaluate(const str &expression) {
    std::stack<int> stack;
    std::istringstream istream_str(expression);
    std::string token;

    while (istream_str >> token) {
        if (token.length() == 1 && confirm_op(token)) {
            if (stack.size() < 2) throw std::runtime_error("Error: Invalid expression.");

            int b = stack.top(); stack.pop();
            int a = stack.top(); stack.pop();

            stack.push(apply_operator(a, b, token[0]));
        } 
        else if (token.length() == 1 && isdigit(token[0])) {
            stack.push(token[0] - '0');
        } 
        else {
            throw std::runtime_error("Error: Invalid token.");
        }
    }

    if (stack.size() != 1) throw std::runtime_error("Error: Invalid expression.");
    
    return stack.top();
}

