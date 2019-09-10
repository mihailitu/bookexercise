#include <iostream>
#include <cstdio>

#include <map>
#include <limits>

template<typename K, typename V>
class interval_map {
    std::map<K,V> m_map;
public:
    // constructor associates whole range of K with val by inserting (K_min, val)
    // into the map
    interval_map( V const& val) {
        m_map.insert(m_map.end(),std::make_pair(std::numeric_limits<K>::lowest(),val));
    }

    auto size() const {
        return m_map.size();
    }

    void print() const {
        for(auto const &elem : m_map)
            std::cout << "(" << elem.first << ", " << elem.second << ")" << '\n';
        std::cout << "\n\n";
    }

    bool is_equal(K const &key1, K const &key2) {
        return !((key1 < key2) || (key2 < key1));
    }

    void assign2( K const& keyBegin, K const& keyEnd, V const& val ) {

        printf("assign2: %d %d %c\n", keyBegin, keyEnd, val);
        if (!(keyBegin < keyEnd))
            return;

        if (std::next(m_map.begin()) == m_map.end()) { // if no more elements, just slice the map
            if ((*m_map.begin()).second == val) // keep the map canonical
                return;
            m_map.insert(std::make_pair(keyBegin, val));
            m_map.insert(std::make_pair(keyEnd, (*m_map.begin()).second));
            return;
        }

        auto endInterval = m_map.lower_bound(keyEnd);
        auto beginInterval = m_map.upper_bound(keyBegin);

        if (beginInterval == m_map.end()) {
            V slice_value = (*(--beginInterval)).second;
            if (slice_value == val)
                return;
            m_map.insert(std::make_pair(keyBegin, val));
            m_map.insert(std::make_pair(keyEnd, slice_value));
            return;
        }

        printf("Interval: (%d, %c), (%d, %c)\n", (*beginInterval).first, (*beginInterval).second, (*endInterval).first, (*endInterval).second);

        if(val == (*(--beginInterval)).second)
            return;

        if (endInterval == m_map.end()) {
            if ((*m_map.begin()).second == val) // keep the map canonical
                return;
            m_map.insert(std::make_pair(keyBegin, val));
            m_map.insert(std::make_pair(keyEnd, (*m_map.begin()).second));
            m_map.erase(++m_map.find(keyBegin), m_map.find(keyEnd)); // remove any key in between
            return;
        }

        if((*endInterval).second == val)// another early exit. map must be canonical
            return;

        V slice_value = (*(--endInterval)).second;
        m_map.insert(std::make_pair(keyBegin, val));
        m_map.insert(std::make_pair(keyEnd, slice_value));
        m_map.erase(++m_map.find(keyBegin), m_map.find(keyEnd)); // remove any key in between
    }

    // Assign value val to interval [keyBegin, keyEnd).
    // Overwrite previous values in this interval.
    // Conforming to the C++ Standard Library conventions, the interval
    // includes keyBegin, but excludes keyEnd.
    // If !( keyBegin < keyEnd ), this designates an empty interval,
    // and assign must do nothing.
    void assign1( K const& keyBegin, K const& keyEnd, V const& val ) {

        printf("assign1: %d %d %c\n", keyBegin, keyEnd, val);

        if (!(keyBegin < keyEnd))
            return;


        // auto map_iter = m_map.begin();

        if (std::next(m_map.begin()) == m_map.end()) { // if no more elements, just slice the map
            if ((*m_map.begin()).second == val)
                return; // keep the map canonical
            m_map.insert(std::make_pair(keyBegin, val));
            m_map.insert(std::make_pair(keyEnd, (*m_map.begin()).second));
            return;
        }

        auto endInterval = m_map.lower_bound(keyEnd);
        auto beginInterval = m_map.upper_bound(keyBegin);

        printf("Interval: (%d, %c), (%d, %c)\n", (*beginInterval).first, (*beginInterval).second, (*endInterval).first, (*endInterval).second);

        V slice_value = (*m_map.begin()).second;
        for(auto elem = m_map.begin(); elem != m_map.end(); ++elem) {
            if (keyBegin < (*elem).first) {
                if(slice_value == val) // // early exit. map must be canonical
                    return;

                if (std::next(elem) == m_map.end()) { // if no more elements, just slice the map
                    m_map.insert(std::make_pair(keyBegin, val));
                    m_map.insert(std::make_pair(keyEnd, slice_value));
                    return;
                }

                auto endInterval = elem;
                for(; endInterval != m_map.end(); ++endInterval) { // now, find the end of the interval
                    if ((keyEnd < (*endInterval).first) || is_equal(keyEnd, (*endInterval).first)) {
                        if((*endInterval).second == val)// another early exit. map must be canonical
                            return;
                        m_map.insert(std::make_pair(keyBegin, val));
                        m_map.insert(std::make_pair(keyEnd, slice_value));

                        // remove any key in between
                        auto bbegin = ++m_map.find(keyBegin);
                        auto bend = m_map.find(keyEnd);
                        std::cout << "Erase: " << (*bbegin).first << " " << (*bend).first << std::endl;
                        m_map.erase(++m_map.find(keyBegin), m_map.find(keyEnd));
                        return;
                    }
                    slice_value = (*endInterval).second;
                }

                if (endInterval == m_map.end()) { // if no more elements, just slice the map
                    m_map.insert(std::make_pair(keyBegin, val));
                    m_map.insert(std::make_pair(keyEnd, slice_value));
                    m_map.erase(++m_map.find(keyBegin), m_map.find(keyEnd));
                    return;
                }

            }
            slice_value = (*elem).second;
        }
    }

    void assign( K const& keyBegin, K const& keyEnd, V const& val ) {
        assign2(keyBegin, keyEnd, val);
    }

    // look-up of the value associated with key
    V const& operator[]( K const& key ) const {
        return ( --m_map.upper_bound(key) )->second;
    }
};

#include "imap.h"

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a test function that tests the functionality of
// the interval_map, for example using a map of unsigned int intervals to char.

int main()
{
    test_interval_map();
    {
        interval_map<unsigned, char> im('A');
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

    {
        interval_map<unsigned, char> im('A');
        im.assign(0, 20, 'B');
    }
    std::cout << std::endl << std::endl;
    return 0;
}

/**
Task Description
interval_map<K,V> is a data structure that efficiently associates intervals of keys of type K with values of type V. Your task is to implement the assign member function of this data structure, which is outlined below.

interval_map<K, V> is implemented on top of std::map. In case you are not entirely sure which functions std::map provides, what they do and which guarantees they provide, we provide an excerpt of the C++ standard here:

Each key-value-pair (k,v) in the std::map means that the value v is associated with the interval from k (including) to the next key (excluding) in the std::map.

Example: the std::map (0,'A'), (3,'B'), (5,'A') represents the mapping

0 -> 'A'
1 -> 'A'
2 -> 'A'
3 -> 'B'
4 -> 'B'
5 -> 'A'
6 -> 'A'
7 -> 'A'
... all the way to numeric_limits<int>::max()
The representation in the std::map must be canonical, that is, consecutive map entries must not have the same value: ..., (0,'A'), (3,'A'), ... is not allowed. Initially, the whole range of K is associated with a given initial value, passed to the constructor of the interval_map<K,V> data structure.

Key type K
    * besides being copyable and assignable, is less-than comparable via operator<
    * is bounded below, with the lowest value being std::numeric_limits<K>::lowest()
    * does not implement any other operations, in particular no equality comparison or arithmetic operators

Value type V
    * besides being copyable and assignable, is equality-comparable via operator==
    * does not implement any other operations


Pass Criteria

Type requirements are met: You must adhere to the specification of the key and value type given above.
Correctness: Your program should produce a working interval_map with the behavior described above. In particular, pay attention to the validity of iterators. It is illegal to dereference end iterators. Consider using a checking STL implementation such as the one shipped with Visual C++ or GCC.
Canonicity: The representation in m_map must be canonical.
Running time: Imagine your implementation is part of a library, so it should be big-O optimal. In addition:
Do not make big-O more operations on K and V than necessary, because you do not know how fast operations on K/V are; remember that constructions, destructions and assignments are operations as well.
Do not make more than two operations of amortized O(log N), in contrast to O(1), running time, where N is the number of elements in m_map. Any operation that needs to find a position in the map "from scratch", without being given a nearby position, is such an operation.
Otherwise favor simplicity over minor speed improvements.
You should not take longer than 9 hours, but you may of course be faster. Do not rush, we would not give you this assignment if it were trivial.
*/
