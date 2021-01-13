#pragma once
#include <iostream>

template<class T>
class DynamicArray
{
public:
	DynamicArray(int size = 2) : logSize(0), phsSize(size), _arr(new T[size]) {}
	DynamicArray(const DynamicArray& other) : _arr(nullptr) { *this = other; }
	~DynamicArray() { delete[] _arr; logSize = 0; phsSize = 0; }

	const DynamicArray& operator=(const DynamicArray& other)
	{
		if (this != &other)
		{
			logSize = other.logSize;
			phsSize = other.phsSize;
			delete[] _arr;
			_arr = new T[phsSize];
			for (int i = 0; i < logSize; i++)
				_arr[i] = other._arr[i];
		}

		return *this;
	}
	bool operator==(const DynamicArray& other)
	{
		if (logSize != other.logSize)
			return false;

		for (int i = 0; i < logSize; i++)
			if (_arr[i] != other._arr[i])
				return false;

		return true;
	}
	const T& operator[](int i) const { return _arr[i]; }
	T& operator[](int i) { return _arr[i]; }

	void push_back(const T& value)
	{
		if (logSize == phsSize)
			resize();
		_arr[logSize++] = value;
	}

	const T& front() const { return _arr[0]; }
	int      size()		const { return logSize; }
	int      capacity()	const { return phsSize; }
	bool     empty()	const { return logSize == 0; }
	void     clear() { logSize = 0; }

	template <class Func>
	void applyAll(const Func& func) {
		for (auto itr = begin(); itr != end(); ++itr)
			func(*itr);
	}

	class iterator
	{
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using different_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;

		friend class const_iterator;

		iterator(DynamicArray& arr, int i) : _da(&arr), _i(i) {}
		iterator(const iterator& other) : _da(other._da), _i(other._i) {}

		const iterator& operator=(const iterator& other)
		{
			_da = other._da;
			_i = other._i;
			return *this;
		}
		bool operator==(const iterator& other) const { return (_da == other._da) && (_i == other._i); }
		bool operator!=(const iterator& other) const { return !(*this == other); }
		T& operator*() { return _da->_arr[_i]; }
		T* operator->() { return &_da->_arr[_i]; }
		iterator& operator++()
		{
			++_i;
			return *this;
		}
		iterator operator++(int)
		{
			iterator temp(*this);
			++_i;
			return temp;
		}
		iterator& operator--()
		{
			--_i;
			return *this;
		}
		iterator operator--(int)
		{
			iterator temp(*this);
			--_i;
			return temp;
		}

	private:
		DynamicArray* _da;
		int _i;
	};

	class const_iterator
	{
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using different_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;

		const_iterator(const DynamicArray& arr, int i) : _da(&arr), _i(i) {}
		const_iterator(const iterator& other) : _da(other._da), _i(other._i) {}

		const const_iterator& operator=(const iterator& other)
		{
			_da = other._da;
			_i = other._i;
			return *this;
		}
		bool operator==(const const_iterator& other) const { return (_da == other._da) && (_i == other._i); }
		bool operator!=(const const_iterator& other) const { return !(*this == other); }
		const T& operator*() { return _da->_arr[_i]; }
		const T* operator->() { return &_da->_arr[_i]; }
		const_iterator& operator++()
		{
			++_i;
			return *this;
		}
		const_iterator operator++(int)
		{
			const_iterator temp(*this);
			++_i;
			return temp;
		}
		const_iterator& operator--()
		{
			--_i;
			return *this;
		}
		const_iterator operator--(int)
		{
			const_iterator temp(*this);
			--_i;
			return temp;
		}

	private:
		const DynamicArray* _da;
		int _i;
	};

	class reverse_iterator
	{
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using different_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;

		reverse_iterator(DynamicArray& arr, int i) : _da(arr), _i(i) {}
		reverse_iterator(const reverse_iterator& other) : _da(other._da), _i(other._i) {}

		const reverse_iterator& operator=(const reverse_iterator& other)
		{
			_da = other._da;
			_i = other._i;
			return *this;
		}
		bool operator==(const reverse_iterator& other) const { return (_da == other._da) && (_i == other._i); }
		bool operator!=(const reverse_iterator& other) const { return !(*this == other); }
		T& operator*() { return _da->_arr[_i]; }
		T* operator->() { return &_da->_arr[_i]; }
		reverse_iterator& operator++()
		{
			--_i;
			return *this;
		}
		reverse_iterator operator++(int)
		{
			reverse_iterator temp(*this);
			--_i;
			return temp;
		}
		reverse_iterator& operator--()
		{
			++_i;
			return *this;
		}
		reverse_iterator operator--(int)
		{
			reverse_iterator temp(*this);
			++_i;
			return temp;
		}

	private:
		DynamicArray* _da;
		int _i;
	};

	const iterator& erase(const iterator& itr)
	{
		iterator itr_end = end();
		iterator itr_current = itr;
		iterator itr_next = itr;
		++itr_next;

		while (itr_next != itr_end)
		{
			*itr_current = *itr_next;
			itr_current = itr_next++;
		}

		--logSize;
		return itr;
	}

	const iterator& erase(const iterator& first, const iterator& last)
	{
		int diff = 0;
		iterator itr_end = end();
		iterator itr_current = first;
		iterator itr_next = last;
		const iterator& itr_rtn = first;

		while (itr_next != itr_end)
		{
			*itr_current = *itr_next;
			++itr_current;
			++itr_next;
		}

		while (itr_current != itr_next)
		{
			++diff;
			++itr_current;
		}

		logSize -= diff;
		return itr_rtn;
	}

	iterator begin() { return iterator(*this, 0); }
	iterator end() { return iterator(*this, logSize); }
	const iterator cbegin() const { return iterator(*this, 0); }
	const iterator cend() const { return iterator(*this, logSize); }

	const_iterator begin() const { return const_iterator(*this, 0); }
	const_iterator end() const { return const_iterator(*this, logSize); }

	reverse_iterator rbegin() { return reverse_iterator(*this, 0); }
	reverse_iterator rend() { return reverse_iterator(*this, logSize); }

	void insert(const iterator& pos, const T& val)
	{
		if (logSize == phsSize)
			resize();

		iterator itr_end = end();
		iterator itr_current = itr_end;
		iterator itr_prev = --itr_end;

		while (itr_current != pos)
		{
			*itr_current = *itr_prev;
			itr_current = itr_prev--;
		}

		iterator p = pos;
		*p = val;
		++logSize;
	}

	void resize(int size) {
		phsSize = size;
		logSize = size;
		T* temp = new T[phsSize];

		for (int i = 0; i < logSize; i++)
			temp[i] = _arr[i];

		delete[] _arr;
		_arr = temp;
	}

private:
	void resize() {
		phsSize *= 2;
		T* temp = new T[phsSize];
		for (int i = 0; i < logSize; i++)
			temp[i] = _arr[i];

		delete[] _arr;
		_arr = temp;
	}

	T* _arr;
	int logSize;
	int phsSize;
};