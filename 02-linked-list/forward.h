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

    }
    
    bool remove(size_t position) override {

    }
    
    T& operator[](size_t position) override {

    }
    
    [[nodiscard]] bool is_empty() const override {
        return head == nullptr;
    }
    
    [[nodiscard]] size_t size() const override {
        return nodes;
    }
    
    void clear() override {

    }
    
    void sort() override {

    }
    
    [[nodiscard]] bool is_sorted() const override {

    }
    
    void reverse() override {

    }
    
    [[nodiscard]] std::string name() const override {
        return "Forward List";
    }
};

#endif
