//
//  ssarray.hpp
//  SSArray
//
//  Created by Ian Ferguson on 9/16/18.
//  Copyright © 2018 Ian Ferguson. All rights reserved.
//

#ifndef ssarray_hpp
#define ssarray_hpp

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
    SSArray & operator=(SSArray && rhs);
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
    
    T* begin() const;
    T* end() const;
    bool operator==(const SSArray& rhs) const;
    bool operator!=(const SSArray& rhs) const;
    bool operator <(const SSArray & rhs) const;
    bool operator <=(const SSArray & rhs) const;
    bool operator >(const SSArray & rhs) const;
    bool operator >=(const SSArray & rhs) const;
    
private:
    T *_array;
    size_type _size;
};

template<typename T>
SSArray<T>::SSArray()
{
    _size = 8;
    _array = new T[_size];

}

template<typename T>
SSArray<T>::~SSArray()
{
    delete []_array;
}

template<typename T>
SSArray<T>::SSArray(const SSArray & copy)
{
    _size = copy._size;
    _array = new value_type[copy._size];
    memcpy(_array, copy._array, sizeof(T) * _size);

}

template<typename T>
SSArray<T>::SSArray(SSArray && rhs):_array(rhs._array)
{
    rhs._array = nullptr;
}

template<typename T>
SSArray<T>::SSArray(size_type size)
{
    if(size <= 0)
    {
        std::cout << "Size cannot be a negative number!" << std::endl;
        std::cout << "Size will default to zero." << std::endl;
        _size = 0;
    }
    _size = size;
}

template<typename T>
SSArray<T>::SSArray(size_type size, T value)
{
    _size = size;
    memset(_array, value, _size*sizeof(_array[value]));
    
}

template<typename T>
T* SSArray<T>::begin() const
{
    return &_array[0];
}

template<typename T>
T* SSArray<T>::end() const
{
    return &_array[_size];
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
    memcpy(_array, copy._array, sizeof(T) * _size);
    return * this;
}

template<typename T>
SSArray<T>& SSArray<T>::operator=(SSArray && rhs)
{
    if(this == &rhs)
    {
        return *this;
    }
    delete _array;
    rhs._array= new T[rhs._size];
    return *this;
}

template<typename T>
bool SSArray<T>::operator==(const SSArray& rhs) const
{
    return true;
}

template<typename T>
bool SSArray<T>::operator!=(const SSArray & rhs) const
{
    return true;
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
