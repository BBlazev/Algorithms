#pragma once
#include <iostream>
#include <stdexcept>

template <typename T>
class CircularSinglyLinkedList {
private:
	struct Node {
		
		T data;
		Node* next;
		Node (const T& value) : data(value), next(nullptr){}

	};

	Node* tail;


public:

	CircularSinglyLinkedList() : tail(nullptr){}
	~CircularSinglyLinkedList() { clear(); }

	CircularSinglyLinkedList(const CircularSinglyLinkedList&) = delete;
	CircularSinglyLinkedList& operator=(const CircularSinglyLinkedList&) = delete;

	void push_back(const T& value) {

		Node* newNode = new Node(value);

		if (empty())
		{
			tail = newNode;
			newNode->next = newNode;
		}

		else 
		{
			newNode->next = tail->next;
			tail->next = newNode;
			tail = newNode;
		}


	}

	void print() const {
		if (empty()) {
			std::cout << "List is empty." << std::endl;
			return;
		}
		Node* current = tail->next; 
		Node* head = tail->next;
		do {
			std::cout << current->data << " <-> ";
			current = current->next;
		} while (current != head);

		std::cout << " (head again) "<< current->data << std::endl;
	}


	void push_front(const T& value) {

		Node* newNode = new Node(value);

		if (empty())
		{
			tail = newNode;
			newNode->next = newNode;
		}
		else
		{
			newNode->next = tail->next;
			tail->next = newNode;
		}

	}
	size_t size() const {
		if (empty())
			return 0;
		size_t count = 0;
		Node* current = tail->next; // Start from head.
		do {
			++count;
			current = current->next;
		} while (current != tail->next);
		return count;
	}
	void pop_back() {
		if (empty())
			throw std::out_of_range("Circular list is empty");

		if (tail->next == tail) {
			delete tail;
			tail = nullptr;
		}

		else
		{
			Node* current = tail->next;
			while (current ->next != tail)
			{
				current = current->next;
			}

			current->next = tail->next;
			delete tail;
			tail = current;

		}


	}

	void pop_front() {

		if (empty())
			throw std::out_of_range("Circular list is empty");

		Node* head = tail->next;
		if (tail == head)
		{
			delete head;
			tail = nullptr;
		}
		else
		{
			tail->next = head->next;
			delete head;
		}

	}

	void clear() {

		while (!empty())
			pop_front();

	}

	bool empty() const {
		return tail == nullptr;
	}
};