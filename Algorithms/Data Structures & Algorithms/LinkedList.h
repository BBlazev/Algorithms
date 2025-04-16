#pragma once
#include <iostream>
#include <stdexcept>

template<typename T>
class LinkedList {
private:
    // Node for singly linked list
    struct Node {
        T data;
        Node* next;
        Node(const T& d) : data(d), next(nullptr) {}
    };

    Node* head; // Pointer to the first node in the list

public:
    LinkedList() : head(nullptr) {}

    ~LinkedList() { clear(); }

    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;

    // Insert at the front
    void push_front(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }

    // Insert at the back
    void push_back(const T& value) {
        Node* newNode = new Node(value);
        if (!head)
            head = newNode;
        else {
            Node* temp = head;
            while (temp->next)
                temp = temp->next;
            temp->next = newNode;
        }
    }

    // Remove the first element
    void pop_front() {
        if (!head)
            throw std::out_of_range("Linked list is empty");
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    // Remove all elements
    void clear() {
        while (head)
            pop_front();
    }

    // Return the current size of the list by traversing
    size_t size() const {
        size_t count = 0;
        Node* current = head;
        while (current) {
            ++count;
            current = current->next;
        }
        return count;
    }

    // Print all elements
    void print() const {
        Node* current = head;
        while (current) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "NULL" << std::endl;
    }

=
    // Insert an element at an arbitrary position.
    // Valid positions are 0 <= pos <= size().
    // If pos == 0, it's equivalent to push_front.
    // If pos == size(), it's equivalent to push_back.
    void insert_at(size_t pos, const T& value) {
        if (pos > size())
            throw std::out_of_range("Position out of range in insert_at()");
        if (pos == 0) {
            push_front(value);
            return;
        }
        // For positions > 0, stop at the node just before pos.
        Node* newNode = new Node(value);
        Node* current = head;
        for (size_t i = 0; i < pos - 1; i++) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    // Remove the node at an arbitrary position.
    // Valid positions are 0 <= pos < size().
    // If pos == 0, it's equivalent to pop_front.
    void remove_at(size_t pos) {
        if (!head || pos >= size())
            throw std::out_of_range("Position out of range in remove_at()");
        if (pos == 0) {
            pop_front();
            return;
        }
        // Stop at the node right before the one to be removed.
        Node* current = head;
        for (size_t i = 0; i < pos - 1; i++) {
            current = current->next;
        }
        Node* node_to_remove = current->next;
        current->next = node_to_remove->next;
        delete node_to_remove;
    }

    // Remove the first node with the specified value.
    // If the value is not found, the list remains unchanged.
    void remove_value(const T& value) {
        if (!head)
            return;
        if (head->data == value) {
            pop_front();
            return;
        }
        Node* current = head;
        while (current->next && current->next->data != value) {
            current = current->next;
        }
        if (current->next) {
            Node* temp = current->next;
            current->next = temp->next;
            delete temp;
        }
    }

    bool empty() const {
        return head == nullptr;
    }
};
