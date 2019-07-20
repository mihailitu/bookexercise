#include "gtest.h"

#include "expressions.h"

int int_result(const std::string &expr);

TEST(Fundamentals, Expressions)
{
    std::string expr = "( 1 + 2 * ( 3 + 4 ) )";
    int result = eval<int>(expr);
    ASSERT_EQ(result, 15);

    result = int_result(expr);
    ASSERT_EQ(result, 15);
}

int int_result(const std::string &expr) {
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
