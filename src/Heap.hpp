#pragma once
#include <queue>
template<class T,class Container = std::vector<T>, class Compare = std::greater<typename Container::value_type> >
class Heap : public std::priority_queue<T, Container, Compare>
{
public:
    typedef typename
    std::priority_queue<T,Container,Compare>::container_type::const_iterator const_iterator;


    const_iterator cend() const
    {
        return this->c.cend();
    }
    const_iterator cbegin() const
    {
        return this->c.cbegin();
    }

    const_iterator find(const T& val) const
    {
        auto first = this->c.cbegin();
        auto last = this->c.cend();
        while (first != last) {
            if (*first == val) 
                return first;
            ++first;
        }
        return last;
    }
};