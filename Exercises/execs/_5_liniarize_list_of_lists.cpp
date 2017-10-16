#include "_5_liniarize_list_of_lists.h"
#include <vector>
#include <iostream>

/* 5. Have a list of elements, where an element can be either a char or a another list.
 * eg: [[a, b, c, d], [e], [[f], [g]], [[h], i, [j]]]. Liniarize that list as: [a, b, c, d, e, f, g, h, i, j]
 */

struct ListElement {
    enum {list, character} type = character;
    std::vector<ListElement> elements;
    char c;
    ListElement(char el) : type(character), c(el) {}
    ListElement(std::vector<ListElement> el) : type(list), elements(el) {}
};

void parse(ListElement le, std::vector<char> &output)
{
    if (le.type == ListElement::character)
        output.push_back(le.c);
    else
        for(auto i : le.elements)
            parse(i, output);
}

void _5_liniarize_list_of_lists()
{
    typedef std::vector<ListElement> LLE;
    std::vector<ListElement> list;
    LLE abcd = {ListElement('a'), ListElement('b'), ListElement('c'), ListElement('d')};
    ListElement first(abcd);
    list.push_back(first);
    list.push_back(ListElement('e'));

    LLE fl = { ListElement('f') };

    LLE gl = { ListElement('g') };

    LLE fg;
    fg.push_back(fl);
    fg.push_back(gl);

    list.push_back(fg);

    LLE hij;
    LLE h = { ListElement('h') };
    hij.push_back(h);
    hij.push_back(ListElement('i'));

    LLE j = { ListElement('j') };
    hij.push_back(j);

    list.push_back(hij);

    std::vector<char> output;

    for( auto i : list)
        parse(i, output);

    for(auto c : output)
        std::cout << c << ' ';
    std::cout << std::endl;
}
