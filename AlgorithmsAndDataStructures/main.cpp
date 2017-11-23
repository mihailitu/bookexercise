#include <iostream>

#include "binarysearch.h"
#include "mystack.h"
#include "expressions.h"
#include "linkedlist.h"

void testExpressionParser()
{
    int r= result("( 1 + ( ( 2 + 3 ) * ( 4 * 5 ) ) )");
    std::cout << r << std::endl;
}

void testLinkedListIterator()
{
    linkedlist<int> ll;
    for(int i : {0, 1, 2, 3, 4, 5})
        ll.push_back(new node<int>(i));
    auto it = ll.begin();
//    while(it != ll.end()) {
//        std::cout << (*it)->data << std::endl;
//    }

}

int main()
{
    testLinkedListIterator();
    return 0;
}
