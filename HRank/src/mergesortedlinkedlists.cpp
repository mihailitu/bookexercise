#include "gtest/gtest.h"
#include <forward_list>
/**
 * @brief TEST MergeSortedLinkedList
 * Given two sorted linked lists, merge the two lists in a sorted results.
 * Consider implementing with and without memory restraint
 */

template <typename T>
std::forward_list<T> MergeSortedLinkedListsSTD(std::forward_list<T> &l1, std::forward_list<T> &l2)
{
    std::forward_list<T> ll;
    auto begin = ll.before_begin();
    auto current = begin;
    auto l1begin = l1.begin();
    auto l2begin = l2.begin();
    while( (l1begin != l1.end()) && (l2begin != l2.end())) {
        if (*l1begin < *l2begin) {
            current = ll.emplace_after(current, l1.front());
            l1.pop_front();
            l1begin = l1.begin();
        } else {
            current = ll.insert_after(current, l2.front());
            l2.pop_front();
            l2begin = l2.begin();
        }
    }

    if (!l1.empty()) {
        ll.merge(l1);
    } else if(!l2.empty()) {
        ll.merge(l2);
    }

    return ll;
}

TEST(HRank, MergeSortedLinkedListSTD)
{
    std::forward_list<int> l1 = {4, 6, 8, 12};
    std::forward_list<int> l2 = {1, 3, 7, 9, 11, 12, 17};

    std::cout << "Sorted list STD:\n";
    auto ll = MergeSortedLinkedListsSTD<int>(l1, l2);
    for(const auto &it : ll) {
        std::cout << it << ' ';
    }
}

template<typename T>
struct Node {
    T data;
    Node *next = nullptr;
};

template<typename T>
class List
{

private:
    Node<T> *head = nullptr;
    Node<T> *current = nullptr;
public:
    void insert(T val) {
        if(isEmpty()) {
            head = new Node<T>;
            head->data = val;
            current = head;
            return;
        }
        Node<T> *tmp = new Node<T>;
        tmp->data = val;
        current->next = tmp;
        current = tmp;
    }
    bool isEmpty() const {
        return head == nullptr;
    }

    Node<T>* begin() const {
        return head;
    }

    ~List() {
        while(head != nullptr) {
            Node<T> *tmp = head->next;
            delete head;
            head = tmp;
        }
    }
};

template <typename T>
List<T> MergeSortedLinkedLists(const List<T> &l1, const List<T> &l2) {
    List<T> ll;
    Node<T> *l1h = l1.begin();
    Node<T> *l2h = l2.begin();
    while((l1h != nullptr) && (l2h != nullptr)) {
        if (l1h->data < l2h->data) {
            ll.insert(l1h->data);
            l1h = l1h->next;
        } else {
            ll.insert(l2h->data);
            l2h = l2h->next;
        }
    }
    Node<T> *remaining = (l1h != nullptr) ? l1h : l2h;

    while (remaining != nullptr) {
        ll.insert(remaining->data);
        remaining = remaining->next;
    }
    return ll;
}

TEST(HRank, MergeSortedLinkedList)
{

    std::vector<int> l1v = {4, 6, 8, 12};
    std::vector<int> l2v = {1, 3, 7, 9, 11, 12, 17};

    List<int> l1;
    List<int> l2;
    for(const auto &it : l1v) {
        l1.insert(it);
    }
    for(const auto &it : l2v) {
        l2.insert(it);
    }

    std::cout << "Sorted list no STD:\n";
    auto ll = MergeSortedLinkedLists<int>(l1, l2);
    Node<int> *merged = ll.begin();
    while(merged != nullptr) {
        std::cout << merged->data << ' ';
        merged = merged->next;
    }
}
