#include <iostream>

#include "binarysearch.h"
#include "mystack.h"
#include "expressions.h"
#include "linkedlist.h"
#include "ringbuffer.h"
#include "movetofront.h"
#include "insertionsort.h"
#include "selectionsort.h"

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
    std::vector<int> a = {7, 5, 10, 2, 4, 6, 1, 3};
    selectionSort(a);

    for(auto i : a)
        std::cout << i << ' ';
    std::cout << std::endl;
    return 0;
}
