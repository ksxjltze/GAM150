/******************************************************************************/
/*!
\title		Captain Stealth
\file		Heap.hpp
\author 	Ho Yi Guan
\par    	email: Yiguan.ho@digipen.edu
\date   	April 08, 2021
\brief
           Contains a implementation of templated Heap 

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
*/
/******************************************************************************/



#pragma once
#include <queue>

template<class T,class Container = std::vector<T>, class Compare = std::greater<typename Container::value_type> >
class Heap : public std::priority_queue<T, Container, Compare>
{
public:
    typedef typename
    std::priority_queue<T,Container,Compare>::container_type::const_iterator const_iterator;

    /*!*************************************************************************
    ****
        \brief
           Get the constant iterator to the end of the container
        \return
            returns the constant iterator to the end of the container
    ****************************************************************************
    ***/
    const_iterator cend() const
    {
        return this->c.cend();
    }

    /*!*************************************************************************
     ****
         \brief
            Get the constant iterator to the start of the container
         \return
             returns the constant iterator to the start of the container
     ****************************************************************************
     ***/
    const_iterator cbegin() const
    {
        return this->c.cbegin();
    }

    /*!*************************************************************************
     ****
         \brief
            Find a the location of a given value in the container
         \param val
            The value to find
         \return
            returns the constant iterator to the location of param val in the container
            if not found returns the constant iterator to the end of the container
     ****************************************************************************
     ***/
    const_iterator find(const T& val) const
    {
        const_iterator first = this->c.cbegin();
        const_iterator last = this->c.cend();
        while (first != last) {
            if (*first == val) 
                return first;
            ++first;
        }
        return last;
    }
};