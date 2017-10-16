#include "_5_liniarize_list_of_lists.h"
#include <vector>
/* 5. Have a list of elements, where an element can be either a char or a another list.
 * eg: [[a, b, c, d], [e], [[f], [g]], [[h], i, [j]]]. Liniarize that list as: [a, b, c, d, e, f, g, h, i, j]
 */

struct ListElement {
    enum {list, character} type;
    std::vector<ListElement> chars;
};

void _5_liniarize_list_of_lists()
{
    std::vector<ListElement> list;
}
