#ifndef DOUBLE_H
#define DOUBLE_H_H

#include "list.h"
#include <cstddef>
#include <stdexcept>

template<typename T>
class DoubleList : public List<T> {
private:
    struct Node {
        T data;
        Node* prev = nullptr;
        Node* next = nullptr;

        Node() = default;
        Node(const T& data): data(data) {}
        Node(const T& data, Node* prev, Node* next): data(data), prev(prev), next(next) {}
    };

    Node* head = nullptr;
    Node* tail = nullptr;
    size_t nodes = 0;

    DoubleList() = default;

    T& front() override {
        if (head == nullptr) throw std::runtime_error("List is empty");
        return head->data;
    }

    T& back() override {
        if (tail == nullptr) throw std::runtime_error("List is empty");
        return tail->data;
    }

    void push_front(const T& value) override {
        head = new Node(value, nullptr, head);
        head->next->prev = head;
        ++nodes;
    }
    
    void push_back(const T& value) override {
        tail = new Node(value, tail, nullptr);
        tail->prev->next = tail;
        ++nodes;
    }

    T pop_front() override {
        if (head == nullptr) throw std::runtime_error("List is empty");
        T data = head->data;
        head = head->next;
        delete head->prev;
        --nodes;
        return data;
    }

    T pop_back() override {
        if (tail == nullptr) throw std::runtime_error("List is empty");
        T data = tail->data;
        tail = tail->prev;
        delete tail->next;
        --nodes;
        return data;
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
    } // TODO
    
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
    } // TODO
    
    T& operator[](size_t position) override {
        Node* temp = head;
        for (size_t i = 0; i < position; i++) {
            temp = temp->next;
        }
        return temp->data;
    } // TODO: THROW
    
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

        head = prev;
    } // TODO
    
    [[nodiscard]] std::string name() const override {
        return "Double List";
    }
};

#endif
