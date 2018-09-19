//
//  ssarray.hpp
//  SSArray
//
//  Created by Ian Ferguson on 9/16/18.
//  Copyright © 2018 Ian Ferguson. All rights reserved.
//

#ifndef ssarray_hpp
#define ssarray_hpp
#include <vector>
#include <algorithm>
#include <iostream>

template<class T>
class SSArray
{
public:
    using size_type = std::size_t;
    using value_type = T;

public:
    SSArray();
    ~SSArray();
    SSArray(const SSArray & copy);
    SSArray & operator =(const SSArray & copy);
    SSArray(SSArray && other);
    SSArray & operator=(SSArray && other);
    SSArray(size_type size);
    SSArray(size_type size, T value);
    value_type & operator[](size_type index)
    {
        return _array[index];
    }
    const value_type & operator[](size_type index) const
    {
        return _array[index];
    }
    size_type size() const
    {
        return _size;
    }
    
    const T* begin() const;
    T* begin();
    const T* end() const;
    T* end();
    friend bool operator==(const SSArray& rhs, const SSArray & lhs)
    {
        if(rhs._array != lhs._array)
        {
            return false;
        }
        if(rhs._size == lhs._size)
        {
            std::sort(rhs.begin(), rhs.end());
            std::sort(lhs.begin(), lhs.end());
            for(int i=0; i<lhs._size; i++)
            {
                if(rhs._array[i] != lhs._array[i])
                {
                    return false;
                }
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    friend bool operator!=(const SSArray& rhs, const SSArray & lhs)
    {
        if(rhs._array != lhs._array)
        {
            return true;
        }
        if(rhs._size == lhs._size)
        {
            std::sort(rhs.begin(), rhs.end());
            std::sort(lhs.begin(), lhs.end());
            for(int i=0; i<lhs._size; i++)
            {
                if(rhs._array[i] != lhs._array[i])
                {
                    return true;
                }
            }
            return false;
        }
        else
        {
            return true;
        }
    }
    bool operator <(const SSArray & rhs) const;
    bool operator <=(const SSArray & rhs) const;
    bool operator >(const SSArray & rhs) const;
    bool operator >=(const SSArray & rhs) const;
    
private:
    value_type *_array;
    size_type _size;
};

template<typename T>
SSArray<T>::SSArray()
{
    _size = 8;
    _array = new value_type[8];

}

template<typename T>
SSArray<T>::~SSArray()
{
    delete[] _array;
}

template<typename T>
SSArray<T>::SSArray(const SSArray & copy)
{
    _array = new value_type[copy._size];
    _size = copy._size;
    std::copy(begin(), end(), _array);

}

template<typename T>
SSArray<T>::SSArray(SSArray && other)
{
    _array = other._array;
    _size = other._size;
    
    other._array = nullptr;
    other._size = 0;
}

template<typename T>
SSArray<T>::SSArray(size_type size)
{
    if(size <= 0)
    {
        _size = 0;
    }
    _size = size;
    _array = new value_type[_size];
}

template<typename T>
SSArray<T>::SSArray(size_type size, value_type value)
{
    if (size <= 0)
    {
        size = 0;
    }
    _size = size;
    _array= new value_type[_size];
    std::fill(begin(), end(), value);
}

template<typename T>
const T* SSArray<T>::begin() const
{
    return _array;
}
template<typename T>
T* SSArray<T>::begin()
{
    return _array;
}

template<typename T>
const T* SSArray<T>::end() const
{
    return _array + _size;
}

template<typename T>
T* SSArray<T>::end()
{
    return _array + _size;
}

template<typename T>
SSArray<T>& SSArray<T>::operator=(const SSArray &copy)
{
    if(this == &copy)
    {
        return *this;
    }
    _array = new T[copy._size];
    _size = copy._size;
    std::copy(begin(), end(), copy._array);
    return * this;
}

template<typename T>
SSArray<T>& SSArray<T>::operator=(SSArray && rhs)
{
    if(this == &rhs)
    {
        return *this;
    }
    rhs._array= new T[rhs._size];
    return *this;
}




template<typename T>
bool SSArray<T>::operator<(const SSArray &rhs) const
{
    return true;
}

template<typename T>
bool SSArray<T>::operator<=(const SSArray &rhs) const
{
    return true;
}

template<typename T>
bool SSArray<T>::operator>(const SSArray &rhs) const
{
    return true;
}

template<typename T>
bool SSArray<T>::operator >=(const SSArray &Rhs) const
{
    return true;
}


#endif /* ssarray_hpp */
