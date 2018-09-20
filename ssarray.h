//
//  ssarray.hpp
//  SSArray
//
//  Created by Ian Ferguson on 9/16/18.
//  Copyright © 2018 Ian Ferguson. All rights reserved.
//

#ifndef ssarray_hpp
#define ssarray_hpp
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>

template<typename T>
class SSArray
{
public:
    //Data Members
    using size_type = std::size_t;
    using value_type = T;

public:
    //Invariants
    //_array any memor allocated, owned by *this
    //Large enough to hold a value_type, by passing size as the value
    
    //Constructors
    
    //Default Constructor
    //Pre:Takes no parameters.
    //Post:Returns a default array of size 8 by default.
    SSArray();
    //Destructor
    //Pre:None.
    //Post:The memory allocated for the array is deleted
    ~SSArray();
    //Copy Constructor
    //Pre:Our begin() and end() functions must be defined.
    //Post:Deallocates the &copy array and reallocates the memory to a new array.
    SSArray(const SSArray & copy);
    //Copy Assignment
    //Pre:Our begin() and end() functions must be defined.
    //Post:Will assign our copy to *this.
    SSArray & operator =(const SSArray & copy);
    //Move Constructor
    SSArray(SSArray && other) noexcept;
    //Move Assignment
    SSArray & operator=(SSArray && other) noexcept;
    //One Parameter Constructor
    //Pre:Takes a size parameter. No other functions needed.
    //Post:
    explicit SSArray(size_type size);
    //Two Parameter Constructor
    explicit SSArray(size_type size, value_type value);
    //Bracket Operator Const.
    //Pre: Calls a const array object.
    //Post:Returns the address of the passed address.
     value_type & operator[](const size_type& index) //Takes a size_type as a parameter. Returning say, an int in this case, would permit implicit type conversions which we do not want.
    {
        return _array[index];
    }
    //Bracket Operator
    //Pre: Calls a const array object.
    //Post:Returns the address of the passed address.
    const value_type & operator[](const size_type& index) const
    {
        return _array[index];
    }
    //Size function; does not take parameters
    //Pre:None.
    //Post:Returns a size_type that represents the size of the SSArray.
    size_type size() const
    {
        return _size;
    }
    //Const begin function; does not take parameters.
    //Pre::Calls a const array.
    //Post:Returns the first element in the const array
    const T* begin() const;
    //Begin function; does not take parameters
    //Pre::Calls a non-const array.
    //Post:Returns the address of the first element in the non-const array.
    T* begin();
    //Begin function; does not take parameters
    //Pre::Calls a non-const array.
    //Post:Returns the address just past the first element of the array.
    const T* end() const;
    //Begin function; does not take parameters
    //Pre::Calls a const array.
    //Post:Returns the address just past the first element of the array.
    T* end();

    
private:
    //Private variables
    //Tied to the data types
     value_type *_array;
     size_type _size;
};

//Template arguments
//Constructors

//Default constructor
template<typename T>
SSArray<T>::SSArray():_size(8), _array(new value_type[8])
{}

//Destructor
template<typename T>
SSArray<T>::~SSArray() //Big Five
{
    delete[] _array;
}

//Copy constructor
template<typename T>
SSArray<T>::SSArray(const SSArray & copy):_size(copy._size), _array(new value_type[copy._size]) //Big Five
{
    std::copy(copy.begin(), copy.end(), _array);
}

//Move constructor
template<typename T>
SSArray<T>::SSArray(SSArray && other) noexcept //Big Five
{

    _array = other._array;
    _size = other._size;
    
    other._size = 0;
    other._array = NULL;

}
//One parameter constructor
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
//Two parameter constructor
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
//Member functions
//Template definitions

//Const begin function
template<typename T>
const T* SSArray<T>::begin() const
{
    return _array; //First element in array.
}
//Non-const begin function
template<typename T>
T* SSArray<T>::begin()
{
    return _array; //First element in array.
}
//Const end function
template<typename T>
const T* SSArray<T>::end() const
{
    return _array + _size;  //One past the last element in the array.
}

//Non-const end function.
template<typename T>
T* SSArray<T>::end()
{
    return _array + _size; //One past the last element in the array.
}

//Assignment Operators

//Copy Assignment
template<typename T>
SSArray<T>& SSArray<T>::operator=(const SSArray &copy)
{
    if(this == &copy)
    {
        return *this;
    }
    delete[] _array;
    _array = new value_type[copy._size];
    _size = copy._size;
    std::copy(copy.begin(), copy.end(), _array);
    return * this;
}
//Move Assignment
template<typename T>
SSArray<T>& SSArray<T>::operator=(SSArray && other) noexcept
{
    if(this == &other)
    {
        return *this;
    }
    std::swap(_size, other._size);
    std::swap(_array, other._array);

    return *this;
}

//Overloaded Operators

//Equality Operator
//Pre: Operator != has to be defined.
//Post: If lhs and rhs equal each other, it will return true;
template<class T>
bool operator==(const SSArray<T> &rhs, const SSArray<T> &lhs)
{
    if(lhs.size() != rhs.size()) //Check that we are comparing arrays of the same size. If not, these cannot be equal.
    {
        return false;
    }
    else
    {
        for(int i=0; i<lhs.size(); i++)
        {
            if(lhs[i] != rhs[i])  //If at any point, a value in one array isn't the same as the other, we will end the loop immediately and return false.
            {
                return false;
            }
        }
        return true;
    }
}

//Inequality Operator
//Pre: Operator == needs to be defined for T
//Post: Returns true if lhs and rhs do not equal each other.
template<class T>
bool operator!=(const SSArray<T> &rhs, const SSArray<T> &lhs)
{
    return !(rhs==lhs); //Canonical
}

//Comparison operators

//Less than operator
//Pre: Operator ==, !=, and [] must be defined.
//Post: Returns true with lhs < rhs.
template<class T>
bool operator<(const SSArray<T> &lhs, const SSArray<T> &rhs)
{
    if(lhs == rhs)
    {
        return false;
    }
    
    for(int i = 0; i <lhs.size(); i++)
    {
        if(i == rhs.size())
        {
            return false;
        }
        
        if(lhs[i] < rhs[i])
        {
            return true;
        }
        else if(lhs[i] > rhs[i])
        {
            return false;
        }
    }
    if(lhs.size() < rhs.size())
    {
        return true;
    }
    return false;

}

//Less than or equals to Operator
//Pre: Operator < and == must be defined to return this canonically.
//Post: Will return true if lhs < rhs or if they are equal to each other.
template<class T>
bool operator<=(const SSArray<T> &lhs, const SSArray<T> &rhs)
{
    return lhs == rhs || lhs < rhs; //Canonical
}
//Greater than Operator
//Pre: Operator <= must be defined (which in this case, means that Operators < and == must be defined as well).
//Post: Will return true if lhs is neither less than or equal to rhs.
template<class T>
bool operator>(const SSArray<T> &lhs, const SSArray<T> &rhs)
{
    return !(lhs<=rhs); //Canonical
}
//Greater than or equal to Operator
//Pre:Greater than and equality Operator must be defined.
//Post: Returns true if lhs is either greater than or equal to rhs.
template<class T>
bool operator >=(const SSArray<T> &lhs, const SSArray<T> &rhs)
{
    return ((lhs > rhs ) || (lhs == rhs)); //Canonical
}


#endif /* ssarray_hpp */
