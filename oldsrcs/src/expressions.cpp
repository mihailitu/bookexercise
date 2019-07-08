#include "expressions.h"

int result(std::string expr) {
    std::istringstream iss(expr);
    std::string w;

    std::stack<int> vals;
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
            int v = vals.top();
            vals.pop();
            int prevVal = vals.top();
            vals.pop();
            if(op == "+") v = prevVal + v;
            else if (op == "-") v = prevVal - v;
            else if (op == "*") v = prevVal * v;
            else if (op == "/") v = prevVal / v;

            vals.push(v);
        } else {
            vals.push(std::stoi(w));
        }
    }

    return vals.top();
}
