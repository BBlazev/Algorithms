#pragma once
#include <iostream>
#include <stdexcept>

template <typename T>
class CircularDoublyLinkedList {

private:
	
	struct Node {

		T data;
		Node* prev;
		Node* next;

		Node (const T& value) : data(value), next(nullptr), prev(nullptr) {}

	};

	Node* tail;

public:

	CircularDoublyLinkedList() : tail(nullptr) {}
	~CircularDoublyLinkedList() { clear(); }

	CircularDoublyLinkedList(const CircularDoublyLinkedList) = delete;
	CircularDoublyLinkedList& operator=(const CircularDoublyLinkedList&) = delete;

	void push_back(const T& value) {

		Node* newNode = new Node(value);

		if (empty())
		{
			newNode->next = newNode;
			newNode->prev = newNode;
			tail = newNode;
		}
		else
		{
			Node* head = tail->next;
			head->prev = newNode;
			tail->next = newNode;
			newNode->next = head;
			newNode->prev = tail;
			tail = newNode;
		}

	}

	void push_front(const T& value) {

		Node* newNode = new Node(value);
		if (empty())
		{
			newNode->next = newNode;
			newNode->prev = newNode;
			tail = newNode;
		}
		else 
		{
			Node* head = tail->next;
			newNode->next = head;
			newNode->prev = tail;
			tail->next = newNode;
			head->prev = newNode;


		}


	}

	void pop_front() {

		if (empty())
			throw std::out_of_range("Circular doubly linked list is empty");

		Node* head = tail->next;
		if (tail == head)
		{
			delete head;
			tail = nullptr;
		}
		else
		{
			Node* newHead = head->next;
			tail->next = newHead;
			newHead->prev = tail;
			delete head;
		}
	}

	void pop_back() {
		if (empty())
			throw std::out_of_range("Circular doubly linked list is empty");

		if (tail->next == tail) {
			delete tail;
			tail = nullptr;
		}
		else {
			Node* newTail = tail->prev;
			Node* head = tail->next;
			head->prev = newTail;
			newTail->next = head;
			delete tail;
			tail = newTail;
		}
	}

	void print_forward() const {

		if (empty()) {
			std::cout << "List is empty." << std::endl;
			return;
		}

		Node* head = tail->next;
		Node* current = head;

		do
		{
			std::cout << current->data << " <-> ";
			current = current->next;

		} while (current != head);

		std::cout << "(back to head) " << current->data << std::endl;

	}

	void print_backward() const {
		if (empty()) {
			std::cout << "List is empty." << std::endl;
			return;
		}
		Node* current = tail;
		Node* head = tail->next;
		do {
			std::cout << current->data << " <-> ";
			current = current->prev;
		} while (current != tail);
		std::cout << "(back to tail)" << current->data << std::endl;
	}

	size_t size() const {
		if (empty())
			return 0;

		size_t count = 0;

		Node* current = tail->next;
		do
		{
			++count;
			current = current->next;

		} while (current != tail->next);
		return count;
	}

	void clear() {

		while (!empty())
			pop_front();
		
	}

	bool empty() const {
		return tail == nullptr;
	}
};