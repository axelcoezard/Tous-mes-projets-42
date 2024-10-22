/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 18:07:51 by acoezard          #+#    #+#             */
/*   Updated: 2021/12/31 13:31:41 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

template <typename T>
class Array
{
    private:
        unsigned int    _size;
        T               *_items;
    public:
        Array(void) : _size(0)
        {
            this->_items = new T[0];
        }
        
        Array(unsigned int size) : _size(size)
        {
            this->_items = new T[size];
        }

        Array(const Array<T> & copy)
        {
            *this = copy;
        }

        ~Array(void)
        { }

        Array<T>&  operator=(const Array<T> & copy)
        {
            this->_size = copy.size();
            this->_items = new T[this->_size];

            for (unsigned int i = 0; i < this->_size; i++)
                this->_items[i] = copy[i];

            return (*this);
        }
        
        T&     operator[](unsigned int index) const
        {
            if (index < 0 || index >= this->_size)
                throw std::exception();
 
            return (this->_items[index]);
        }

        unsigned int    size(void) const
        {
            return (this->_size);
        }
};

