#pragma once
#include <iostream>
#include <stdexcept>

template <typename T>
class Stack
{

private:
	T* data;
	size_t capacity;
	size_t count;

	void resize() {
		size_t newCapacity = capacity * 2;
		T* newData = new T[newCapacity];

		for (size_t i = 0; i < count; ++i)
			newData[i] = data[i];


		delete[] data;

		data = newData;
		capacity = newCapacity;
	}

public:

	Stack(size_t initCapacity = 10) : capacity(initCapacity), count(0) {
		data = new T[capacity];
	}

	~Stack() {
		delete[] data;
	}

	void push(const T& value) {
		if (count == capacity) resize();

		data[count++] = value;
		
	}

	void pop() {
		if (empty())
			throw std::out_of_range("Stack is empty");

		--count;
	}


	T& top() {
		if (empty())
			throw std::out_of_range("Stack is empty");

		return data[count - 1];
	}

	const T& top() const {
		if (empty())
			throw std::out_of_range("Stack is empty");

		return data[count - 1];
	}

	bool empty() const {
		return (count == 0);
	}

	size_t size() const {
		return count;
	}

};

