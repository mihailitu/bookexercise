#include "imap.h"
#include <boost/icl/interval_map.hpp>

void test_interval_map()
{
    boost::icl::interval_map<unsigned int, char> im;
    im.assign
    im.assign(10, 20, 'B');
    im.print();
    im.assign(3, 7, 'C');
    im.print();
    im.assign(9, 20, 'D');
    im.print();
    im.assign(5, 15, 'E');
    im.print();
    im.assign(17, 30, 'X');
    im.print();
    im.assign(20, 50, 'A');
    im.print();
    im.assign(100, 200, 'W');
    im.print();
}
