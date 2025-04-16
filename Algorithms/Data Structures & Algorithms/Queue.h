#pragma once
#include <stdexcept>


template<typename T>
class Queue {

private:
	T* data;
	size_t capacity;
	size_t count;
	size_t head;

	void resize() {
		size_t newCapacity = capacity * 2;
		T* newData = new T[newCapacity];

		for (size_t i = 0; i < count; ++i)
			newData[i] = data[(head + i) % capacity];

		delete[] data;
		data = newData;
		capacity = newCapacity;
		head = 0;

	}

public:
	Queue(size_t initCapacity = 10) : capacity(initCapacity), count(0), head(0) {
		data = new T[capacity];
	}

	~Queue() { delete[] data; }

	void add(const T& value) {
		if (count == capacity)
			resize();

		data[(head + count) % capacity] = value;
		++count;
	}

	void pop() {
		if (empty())
			throw std::out_of_range("Queue is empty");

		head = (head + 1) % capacity;
		--count;
	}

	T& front() {
		if (empty())
			throw std::out_of_range("Queue is empty");

		return data[head];
	}

	const T& front() const{
		if (empty())
			throw std::out_of_range("Queue is empty");

		return data[head];
	}

	bool empty() const {
		return count == 0;
	}

	size_t size() const {
		return count;
	}
};