#pragma once
#include <stdexcept>
#include <utility>
#include <functional>

template<typename T, typename Compare = std::less<T>>
class PriorityQueue {

private:
	T* data;
	size_t capacity;
	size_t count;
	Compare comp;

	void resize() {

		size_t newCapacity = capacity * 2;
		T* newData = new T[newCapacity];

		for (size_t i = 0; i < count; i++)
			newData[i] = data[i];

		delete[] data;
		data = newData;
		capacity = newCapacity;
	}

	void heapify_up(size_t index) {
		while (index > 0)
		{
			size_t parent = (index - 1) / 2;
			if (comp(data[parent], data[index]))
			{
				std::swap(data[index], data[parent]);
				index = parent;

			}
			else {
				break;
			}
		}
	}

	void heapify_down(size_t index) {
		while (true)
		{


			size_t left_child = 2 * index + 1;
			size_t right_child = 2 * index + 2;
			size_t target = index;

			if (left_child < count && comp(data[target], data[left_child]))
				target = left_child;

			if (right_child < count && comp(data[target], data[right_child]))
				target = right_child;

			if (target != index)
			{
				std::swap(data[index], data[target]);
				index = target;
			}
			else
				break;
		}
	}

public:
	PriorityQueue(size_t initCapacity = 10, Compare c = Compare()) : capacity(initCapacity), count(0), comp(c) {
		data = new T[capacity];
	}

	~PriorityQueue() { delete[] data; }

	void push(const T& val) {

		if (count == capacity)
			resize();

		data[count] = val;
		heapify_up(count);
		++count;
	}

	void pop() {
		if (empty())
			throw std::out_of_range("PriorityQueue is empty");

		data[0] = data[count - 1];
		--count;
		heapify_down(0);
	}

	T& top() {
		if (empty())
			throw std::out_of_range("PriorityQueue is empty");

		return data[0];
	}

	const T& top() const {
		if (empty())
			throw std::out_of_range("PriorityQueue is empty");

		return data[0];
	}


	bool empty() const {
		return count == 0;
	}

	size_t size() const {
		return count;
	}

};