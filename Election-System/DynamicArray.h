#pragma once
#include <iostream>

template <class T>
class DynamicArray
{
public:
	class iterator;
	class const_iterator;
	class reverse_iterator;
	class const_reverse_iterator;

public:
	DynamicArray(int size = 10) : _size(0), _capacity(size), _arr(new T[size]) {}
	DynamicArray(const DynamicArray& other) : _arr(nullptr) { *this = other; }
	~DynamicArray() { delete[] _arr; }

public:
	void push_back(const T& value);
	int size() const { return _size; };
	int capacity() const { return _capacity; };
	bool empty() const { return _size == 0; };
	void clear() { _size = 0; };
	const T& front() const { return _arr[0]; };
	void print() const;

public:
	const DynamicArray& operator=(const DynamicArray& other);
	const T& operator[](int i) const { return _arr[i]; };
	T& operator[](int i) { return _arr[i]; }

public:
	iterator begin() { return iterator(*this, 0); };
	iterator end() { return iterator(*this, _size); };
	const_iterator begin() const { return const_iterator(*this, 0); }
	const_iterator end() const { return const_iterator(*this, _size); }

	const_iterator cbegin() { return const_iterator(*this, 0); };
	const_iterator cend() { return const_iterator(*this, _size); };
	const_iterator cbegin() const { return const_iterator(*this, 0); }
	const_iterator cend() const { return const_iterator(*this, _size); }

	reverse_iterator rbegin() { return reverse_iterator(*this, _size - 1); };
	reverse_iterator rend() { return reverse_iterator(*this, -1); };
	const_reverse_iterator rbegin() const { return const_reverse_iterator(*this, _size - 1); }
	const_reverse_iterator rend() const { return const_reverse_iterator(*this, -1); }

	void insert(const iterator& iter, const T& val);
	void insert(const const_iterator& iter, const T& val);

	const iterator& erase(const iterator& iter)
	{
		iterator endIter = end();

		if (iter == endIter)
			return endIter;

		iterator temp = iter;

		iterator prev = iter;
		iterator curr = ++temp;

		while (curr != endIter)
		{
			*prev = *curr;
			++prev;
			++curr;
		}

		--_size;

		return iter;
	}
	const iterator& erase(const iterator& first, const iterator& last)
	{
		iterator f = first;
		iterator l = last;

		--l;

		while (l != f)
		{
			erase(l);
			--l;
		}

		erase(l);

		return l;
	}
private:
	void resize();
	T* _arr;
	int _size;
	int _capacity;
};

template <typename T>
const DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& other)
{
	if (this != &other) {
		_size = other._size;
		_capacity = other._capacity;
		delete[] _arr;
		_arr = new T[_capacity];
		for (int i = 0; i < _size; i++)
			_arr[i] = other._arr[i];
	}
	return *this;
}

template<class T>
void DynamicArray<T>::resize()
{
	_capacity *= 2;

	T* temp = new T[_capacity];

	for (int i = 0; i < _size; i++)
		temp[i] = _arr[i];

	delete[] _arr;

	_arr = temp;
}

template<typename T>
void DynamicArray<T>::push_back(const T& value)
{
	if (_size == _capacity)
		resize();
	_arr[_size++] = value;
}

template<class T>
void DynamicArray<T>::insert(const iterator& iter, const T& val)
{
	if (_size == _capacity)
		resize();

	iterator endIter = end();
	iterator curr = endIter;
	iterator  prev = --endIter;

	while (curr != iter)
	{
		*curr = *prev;
		--curr;
		--prev;
	}

	iterator temp = iter;
	*temp = val;
	++_size;
}

template <class T>
void DynamicArray<T>::insert(const const_iterator& iter, const T& val)
{
	if (_size == _capacity)
		resize();

	const_iterator endIter = cend();
	const_iterator curr = endIter;
	const_iterator prev = --endIter;

	while (curr != iter)
	{
		*curr = *prev;
		--curr;
		--prev;
	}

	const_iterator temp = iter;
	*temp = val;
	++_size;
}

template <class T>
void DynamicArray<T>::print() const
{
	for (int i = 0; i < _size; i++)
		std::cout << _arr[i] << " ";
	std::cout << std::endl;
}


//////////////////////////////////////////////////////////////////
////////////////////////// ITERATOR //////////////////////////////
//////////////////////////////////////////////////////////////////

template<typename T>
class DynamicArray<T>::iterator
{
public:
	using iterator_category = std::bidirectional_iterator_tag;
	using different_type = std::ptrdiff_t;
	using value_type = T;
	using pointer = T*;
	using reference = T&;

public:
	iterator(DynamicArray& arr, int index) : _arr(&arr), _index(index) {}
	iterator(const iterator& other) : _arr(other._arr), _index(other._index) {}

public:
	const iterator& operator=(const iterator& other) { _arr = other._arr; _index = other._index; return *this; }
	bool operator==(const iterator& other) const { return (_arr == other._arr) && (_index == other._index); }
	bool operator!=(const iterator& other) const { return !(*this == other); }
	T& operator*() { return _arr->_arr[_index]; }
	T* operator->() { return &_arr->_arr[_index]; }
	iterator& operator++() { ++_index; return *this; }
	iterator operator++(int) { iterator temp(*this); ++_index; return temp; }
	iterator& operator--() { --_index; return *this; }
	iterator operator--(int) { iterator temp(*this); --_index; return temp; }

private:
	DynamicArray* _arr;
	int	_index;
	friend const_iterator;
};


//////////////////////////////////////////////////////////////////
////////////////////////// CONST_ITERATOR ////////////////////////
//////////////////////////////////////////////////////////////////

template<typename T>
class DynamicArray<T>::const_iterator
{
public:
	using iterator_category = std::bidirectional_iterator_tag;
	using different_type = std::ptrdiff_t;
	using value_type = T;
	using pointer = T*;
	using reference = T&;

public:
	const_iterator(DynamicArray<T>& arr, int index) : _arr(&arr), _index(index) {}
	const_iterator(const const_iterator& other) : _arr(other._arr), _index(other._index) {}
	const_iterator(const iterator& other) : _arr(other._arr), _index(other._index) {}

public:
	const const_iterator& operator=(const const_iterator& other) { _arr = other._arr; _index = other._index; return *this; }
	const const_iterator& operator=(const iterator& other) { _arr = other._arr; _index = other._index; return *this; }
	bool operator==(const const_iterator& other) const { return (_arr == other._arr) && (_index == other._index); }
	bool operator!=(const const_iterator& other) const { return !(*this == other); }
	const T& operator*() { return _arr->_arr[_index]; }
	const T* operator->() { return &_arr->_arr[_index]; }
	const_iterator& operator++() { ++_index; return *this; }
	const_iterator operator++(int) { const_iterator temp(*this); ++_index; return temp; }
	const_iterator& operator--() { --_index; return *this; }
	const_iterator operator--(int) { const_iterator temp(*this); --_index; return temp; }

private:
	const DynamicArray* _arr;
	int	_index;
};


//////////////////////////////////////////////////////////////////
////////////////////////// REVERSE_ITERATOR //////////////////////
//////////////////////////////////////////////////////////////////

template<typename T>
class DynamicArray<T>::reverse_iterator
{
public:
	using iterator_category = std::bidirectional_iterator_tag;
	using different_type = std::ptrdiff_t;
	using value_type = T;
	using pointer = T*;
	using reference = T&;

public:
	reverse_iterator(DynamicArray& arr, int index) : _arr(&arr), _index(index) {}
	reverse_iterator(const reverse_iterator& other) : _arr(other._arr), _index(other._index) {}

public:
	const reverse_iterator& operator=(const reverse_iterator& other) { _arr = other._arr; _index = other._index; return *this; }
	bool operator==(const reverse_iterator& other) const { return (_arr == other._arr) && (_index == other._index); }
	bool operator!=(const reverse_iterator& other) const { return !(*this == other); }
	T& operator*() { return _arr->_arr[_index]; }
	T* operator->() { return &_arr->_arr[_index]; }
	reverse_iterator& operator++() { --_index; return *this; }
	reverse_iterator operator++(int) { reverse_iterator temp(*this); --_index; return temp; }
	reverse_iterator& operator--() { ++_index; return *this; }
	reverse_iterator operator--(int) { reverse_iterator temp(*this); ++_index; return temp; }

private:
	DynamicArray* _arr;
	int	_index;
	friend const_reverse_iterator;
};


//////////////////////////////////////////////////////////////////
////////////////////////// CONST_REVERSE_ITERATOR ////////////////
//////////////////////////////////////////////////////////////////

template<typename T>
class DynamicArray<T>::const_reverse_iterator
{
public:
	using iterator_category = std::bidirectional_iterator_tag;
	using different_type = std::ptrdiff_t;
	using value_type = T;
	using pointer = T*;
	using reference = T&;

public:
	const_reverse_iterator(DynamicArray& arr, int index) : _arr(&arr), _index(index) {}
	const_reverse_iterator(const const_reverse_iterator& other) : _arr(other._arr), _index(other._index) {}
	const_reverse_iterator(const reverse_iterator& other) : _arr(other._arr), _index(other._index) {}

public:
	const const_reverse_iterator& operator=(const const_reverse_iterator& other) { _arr = other._arr; _index = other._index; return *this; }
	const const_reverse_iterator& operator=(const reverse_iterator& other) { _arr = other._arr; _index = other._index; return *this; }
	bool operator==(const const_reverse_iterator& other) const { return (_arr == other._arr) && (_index == other._index); }
	bool operator!=(const const_reverse_iterator& other) const { return !(*this == other); }
	const T& operator*() { return _arr->_arr[_index]; }
	const T* operator->() { return &_arr->_arr[_index]; }
	const_reverse_iterator& operator++() { --_index; return *this; }
	const_reverse_iterator operator++(int) { const_reverse_iterator temp(*this); --_index; return temp; }
	const_reverse_iterator& operator--() { ++_index; return *this; }
	const_reverse_iterator operator--(int) { const_reverse_iterator temp(*this); ++_index; return temp; }

private:
	const DynamicArray* _arr;
	int	_index;
};
