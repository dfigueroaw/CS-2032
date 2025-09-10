#ifndef CIRCULAR_H
#define CIRCULAR_H

#include "list.h"
#include <cstddef>
#include <stdexcept>

template<typename T>
class CircularList : public List<T> {
private:
    struct Node {
        T data;
        Node* prev = nullptr;
        Node* next = nullptr;

        Node() = default;
        Node(const T& data): data(data) {}
        Node(const T& data, Node* prev, Node* next): data(data), prev(prev), next(next) {}
    };

    Node* head;
    size_t nodes = 0;

public:
    CircularList(): head(new Node(static_cast<T>(0), head, head) {}

    T& front() override {
        if (head->next == head) throw std::runtime_error("List is empty");
        return head->next->data;
    }

    T& back() override {
        if (head->prev == head) throw std::runtime_error("List is empty");
        return head->prev->data;
    }

    void push_front(const T& value) override {
        head->next = new Node(value, head, head->next);
        head->next->next->prev = head->next;
        ++nodes;
    }
    
    void push_back(const T& value) override {
        head->prev = new Node(value, head->prev, head);
        head->prev->prev->next = head->prev;
        ++nodes;
    }

    T pop_front() override {
        if (head->next == head) throw std::runtime_error("List is empty");
        T data = head->next->data;
        head->next = head->next->next;
        delete head->next->prev;
        head->next->prev = head;
        --nodes;
        return data;
    }

    T pop_back() override {
        if (head->prev == head) throw std::runtime_error("List is empty");
        T data = head->prev->data;
        head->prev = head->prev->prev;
        delete head->prev->next;
        head->prev->next = head;
        --nodes;
        return data;
    }
    
    T& insert(const T& value, size_t position) override {
        if (position > nodes) throw std::out_of_range("Insert position out of bounds");
        ++nodes;
        Node* temp = head;
        for (size_t i = 0; i < position; i++) {
            temp = temp->next;
        }
        temp->next = new Node(value, temp, temp->next);
        temp->next->next->prev = temp->next;
        return temp->next->data;
    }
    
    bool remove(size_t position) override {
        if (position >= nodes) { return false; }
        --nodes;
        Node* temp = head;
        for (size_t i = 0; i <= position; i++) {
            temp = temp->next;
        }
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;
        return true;
    }
    
    T& operator[](size_t position) override {
        if (position >= nodes) { throw std::out_of_range("Index out of bounds"); }
        Node* temp = head;
        for (size_t i = 0; i <= position; i++) {
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
        while (head->next != head) {
            Node* temp = head->next;
            head->next = head->next->next;
            delete temp;
        }
    }
    
    void sort() override {

    }
    
    [[nodiscard]] bool is_sorted() const override {
        Node* temp->next;
        for (size_t i = 0; i < nodes; i++) {
            if (temp->data > temp->next->data) return false;
            temp = temp->next;
        }
        return true;
    }
    
    void reverse() override {
        Node* temp = head;
        for (size_t i = 0; i <= nodes; i++) {
            Node* tempNext = temp->next;
            temp->next = temp->prev;
            temp->prev = tempNext;
            temp = temp->prev;
        }
    }
    
    [[nodiscard]] std::string name() const override {
        return "Double List";
    }

    ~CircularList() {
        clear();
    }
};

#endif
