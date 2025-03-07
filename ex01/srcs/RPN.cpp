#include "../includes/RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN &source) {
    *this = other;
}

RPN &RPN::operator=(const RPN &original_copy) {
    if (this != &other) {  
        this->stack_obj = other.stack_obj;
    }
    return *this;
}


RPN::~RPN() {}

bool RPN::isOperator(const std::string &token) {
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

int RPN::evaluate(const std::string &expression) {
    std::stack<int> stack;
    std::istringstream iss(expression);
    std::string token;

    while (iss >> token) {
        if (token.length() == 1 && isOperator(token)) {
            if (stack.size() < 2) throw std::runtime_error("Error: Invalid expression.");

            int b = stack.top(); stack.pop();
            int a = stack.top(); stack.pop();

            stack.push(applyOperation(a, b, token[0]));
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

