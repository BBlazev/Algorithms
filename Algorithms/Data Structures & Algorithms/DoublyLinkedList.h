#pragma once
#include <iostream>
#include <stdexcept>

template <typename T>
class DoublyLinkedList {
private:

	struct Node {
		T data;
		Node* next;
		Node* prev;
		Node(const T& value) : data(value), next(nullptr), prev(nullptr){}
	};

	Node* head; // pointer to first node
	Node* tail;	// pointer to last node

public:
	DoublyLinkedList() : head(nullptr), tail(nullptr) {}
	~DoublyLinkedList() { clear(); }

	DoublyLinkedList(const DoublyLinkedList&) = delete;
	DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;


	void push_front(const T& value) {
		Node* newNode = new Node(value);
		newNode->next = head;
		newNode->prev = nullptr;

		if (head != nullptr)
			head->prev = newNode;

		head = newNode;

		if (tail == nullptr) // if list is empty
			tail = newNode;

	}

	void push_back(const T& value) {

		Node* newNode = new Node(value);
		newNode->next = nullptr;
		newNode->prev = tail;

		if (tail != nullptr)
			tail->next = newNode;

		tail = newNode;

		if (head == nullptr) // if list is empty
			head = newNode;
	}




	// removing front element
	void pop_front() {
		if (head == nullptr)
			throw std::out_of_range("Doubly linked list is empty");

		Node* temp = head;
		head = head->next;

		if (head != nullptr)
			head->prev = nullptr;
		else
			tail = nullptr;

		delete temp;
	}

	void pop_back() {

		if (tail == nullptr)
			throw std::out_of_range("Doubly linked list is empty");
		
		Node* temp = tail;
		tail = tail->prev;
		if (tail != nullptr)
			tail->next = nullptr;
		else
			head = nullptr;

		delete temp;

	}

	void insert_at(size_t pos, const T& value) {

		size_t listSize = size();
		if (pos > listSize)
			throw std::out_of_range("Position out of range in insert_at()");

		if (pos == 0) {
			push_front(value);
			return;
		}

		if (pos == listSize) {
			push_back(value);
			return;
		}
			
		Node* current = head;
		for (size_t i = 0; i < pos; i++)
			current = current->next;

		Node* newNode = new Node(value);
		newNode->prev = current->prev;
		newNode->next = current;

		if (current->prev)
			current->prev->next = newNode;
		current->prev = newNode;


	}

	void remove_at(size_t pos) {
		size_t listSize = size();
		if (pos >= listSize)
			throw std::out_of_range("Position out of range in remove_at()");
		if (pos == 0) {
			pop_front();
			return;
		}
		if (pos == listSize - 1) {
			pop_back();
			return;
		}

		Node* current = head;
		for (size_t i = 0; i < pos; ++i)
			current = current->next;

		current->prev->next = current->next;
		current->next->prev = current->prev;
		delete current;
	}

	void remove_value(const T& value) {
		Node* current = head;
		while (current != nullptr) {
			if (current->data == value) {
				if (current == head)
					pop_front();
				else if (current == tail)
					pop_back();
				else {
					current->prev->next = current->next;
					current->next->prev = current->prev;
					delete current;
				}
				return;
			}
			current = current->next;
		}
	}

	size_t size() const {

		size_t count = 0;
		Node* current = head;

		while (current != nullptr)
		{
			++count;
			current = current->next;
		}
		return count;

	}

	void clear(){
		while (head != nullptr) 
			pop_front();
		
	
	}

	void print_forward() const {
		Node* current = head;
		while (current != nullptr)
		{
			std::cout << current->data << " <-> ";
			current = current->next;
		}
		std::cout << "NULL" << std::endl;
	}

	void print_backward() const {
		Node* current = tail;
		while (current != nullptr) {
			std::cout << current->data << " <-> ";
			current = current->prev;
		}
		std::cout << "NULL" << std::endl;
	}

	bool empty() const {
		return head == nullptr;
	}

};