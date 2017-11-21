#include <iostream>

// #include "binarysearch.h"
// #include "mystack.h"
#include "expressions.h"

int main()
{
    int r= result("( 1 + ( ( 2 + 3 ) * ( 4 * 5 ) ) )");
    std::cout << r << std::endl;
    return 0;
}
