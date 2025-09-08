#ifndef LIST_H
#define LIST_H

#include <cstddef>
#include <string>

template<typename T>
class List {
public:
    virtual T& front() = 0;
    virtual T& back() = 0;
    virtual void push_front(const T& value) = 0;
    virtual void push_back(const T& value) = 0;
    virtual T pop_front() = 0;
    virtual T pop_back() = 0;
    virtual T& insert(const T& value, size_t position) = 0;
    virtual bool remove(size_t position) = 0;
    virtual T& operator[](size_t position) = 0;
    [[nodiscard]] virtual bool is_empty() const = 0;
    [[nodiscard]] virtual size_t size() const = 0;
    virtual void clear() = 0;
    virtual void sort() = 0;
    [[nodiscard]] virtual bool is_sorted() const = 0;
    virtual void reverse() = 0;
    [[nodiscard]] virtual std::string name() const = 0;
    virtual ~List() = default;
};

#endif

