#ifndef FORWARD_H
#define FORWARD_H

#include "list.h"
#include <cstddef>
#include <stdexcept>

template<typename T>
class ForwardList : public List<T> {
private:
    struct Node {
        T data;
        Node* next = nullptr;

        Node() = default;
        Node(const T& data): data(data) {}
        Node(const T& data, Node* next): data(data), next(next) {}
    };

    Node* head = nullptr;
    size_t nodes = 0;

    ForwardList() = default;

    T& front() override {
        if (head == nullptr) throw std::runtime_error("List is empty");
        return head->data;
    }

    T& back() override {
        if (head == nullptr) throw std::runtime_error("List is empty");
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        return temp;
    }

    void push_front(const T& value) override {
        head = new Node(value, head);
        ++nodes;
    }
    
    void push_back(const T& value) override {
        if (head == nullptr) {
            head = new Node(value);
        } else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = new Node(value);
        }
        ++nodes;
    }

    T pop_front() override {
        if (head == nullptr) throw std::runtime_error("List is empty");
        T data = head->data;
        Node* temp = head->next;
        delete head;
        head = temp;
        --nodes;
    }

    T pop_back() override {
        if (head == nullptr) throw std::runtime_error("List is empty");
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        T data = temp->data;
        delete temp;
        --nodes;
    }
    
    T& insert(const T& value, size_t position) override {
        if (position > nodes) throw std::out_of_range("Insert position out of bounds");
        ++nodes;
        if (position == 0) {
            head = new Node(value, head);
            return head->data;
        }
        Node* temp = head;
        for (size_t i = 0; i < position - 1; i++) {
            temp = temp->next;
        }
        temp->next = new Node(value, temp->next);
        return temp->next->data;
    }
    
    bool remove(size_t position) override {
        if (position >= nodes) { return false; }
        --nodes;
        Node* temp = head;
        if (position == 0) {
            head = head->next;
            delete temp;
            return true;
        }
        for (size_t i = 0; i < position - 1; i++) {
            temp = temp->next;
        }
        Node* toDelete = temp->next;
        temp->next = toDelete->next;
        delete toDelete;
        return true;
    }
    
    T& operator[](size_t position) override {
        Node* temp = head;
        for (size_t i = 0; i < position; i++) {
            temp = temp->next;
        }
        return temp->data;
    }
    
    [[nodiscard]] bool is_empty() const override {
        return nodes == 0;
    }
    
    [[nodiscard]] size_t size() const override {
        return nodes;
    }
    
    void clear() override {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    
    void sort() override {

    }
    
    [[nodiscard]] bool is_sorted() const override {
        Node* temp;
        for (size_t i = 0; i < nodes - 1; i++) {
            if (temp->data > temp->next->data) return false;
            temp = temp->next;
        }
        return true;
    }
    
    void reverse() override {
        Node* prev = nullptr;
        Node* current = head;
        Node* next;

        while (current != nullptr) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
    }
    
    [[nodiscard]] std::string name() const override {
        return "Forward List";
    }
};

#endif
