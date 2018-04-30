#pragma once

// Just so we can use `cout` later
#include <iostream>
using namespace std;

template<typename T>
class Vector
{
private:
	T* _array;
	unsigned int _size;
public:

	Vector()
	{
		_array = nullptr;
		_size = 0;
	}

	Vector(const Vector& other)
	{
		_size = other._size;

		if (_size == 0)
			_array = nullptr;
		else
		{
			_array = new T[_size];
			for (unsigned int i = 0; i < _size; ++i)
			{
				_array[i] = other._array[i];
			}
		}
	}

	~Vector()
	{
		delete[] _array;
	}

	Vector& operator=(const Vector& other)
	{
		delete[] _array;

		_size = other._size;

		if (_size == 0)
			_array = nullptr;
		else
		{
			_array = new T[_size];
			for (unsigned int i = 0; i < _size; ++i)
			{
				_array[i] = other._array[i];
			}
		}

		// Vector* thisPointer = this;
		return *this;
	}

	void clear()
	{
		delete[] _array;
		_array = nullptr;
		_size = 0;
	}

	void grow(unsigned int newSize)
	{
		if (newSize > _size)
		{
			T* newArray = new T[newSize];
			for (unsigned int i = 0; i < _size; ++i)
			{
				newArray[i] = _array[i];
			}

			delete[] _array;

			_array = newArray;
			_size = newSize;
		}
	}

	void push_back(T newValue)
	{
		grow(_size + 1);
		_array[_size - 1] = newValue;
	}

	void remove_at(unsigned int index)
	{
		if (index >= _size)
		{
			cout << "Error: remove_at() index out of array bounds!" << endl;
			return;
		}

		T* newArray = new T[_size - 1];

		// Copy the array, skipping the chosen index
		for (unsigned int i = 0; i < _size - 1; ++i)
		{
			if(i < index)
				newArray[i] = _array[i];
			else
			{
				newArray[i] = _array[i + 1];
			}
		}

		delete[] _array;
		_array = newArray;

		_size--;
	}

	T& at(unsigned int index)
	{
		if (index >= _size)
		{
			cout << "Error: at() index out of array bounds!" << endl;
			return _array[0];
		}
		return _array[index];
	}

	T& operator[](unsigned int index)
	{
		return at(index);
	}

	unsigned int size()
	{
		return _size;
	}



};