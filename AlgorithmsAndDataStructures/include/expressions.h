#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#include <string>
#include <stack>

template<class T>
T eval(const std::string &expr)
{
    std::istringstream iss(expr);
    std::string w;

    std::stack<T> vals;
    std::stack<std::string> ops;

    while(iss >> w) {
        if(w == "(")
            continue;
        if(w == "+" ||
                w == "-" ||
                w == "*" ||
                w == "/")
            ops.push(w);
        else if(w == ")") {
            std::string op = ops.top();
            ops.pop();
            T v = vals.top();
            vals.pop();
            T prevVal = vals.top();
            vals.pop();
            if(op == "+") v = prevVal + v;
            else if (op == "-") v = prevVal - v;
            else if (op == "*") v = prevVal * v;
            else if (op == "/") v = prevVal / v;
            else if (op == "%") v = prevVal % v;
            vals.push(v);
        } else {
            vals.push(std::stoi(w));
        }
    }

    return vals.top();

}

#endif // EXPRESSIONS_H
