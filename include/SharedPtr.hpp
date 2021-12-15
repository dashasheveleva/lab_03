// Copyright 2021 Daria <photodoshfy@gmail.com>

#ifndef INCLUDE_SHAREDPTR_HPP_
#define INCLUDE_SHAREDPTR_HPP_

#include <atomic>
#include <iostream>
#include <utility>

template <typename T>
class SharedPtr {
private:
    T* p; //указатель
    std::atomic_uint* c; //счетчик указателей

public:
    SharedPtr();
    explicit SharedPtr(T* ptr);
    SharedPtr(const SharedPtr& r);
    SharedPtr(SharedPtr&& r);
    ~SharedPtr();
    auto operator=(const SharedPtr& r) -> SharedPtr&;
    auto operator=(SharedPtr&& r) -> SharedPtr&;

    // проверяет, указывает ли указатель на объект
    operator bool() const;
    auto operator*() const -> T&;
    auto operator->() const -> T*;

    auto get() -> T*;
    void reset();
    void reset(T* ptr);
    void swap(SharedPtr& r);
    // возвращает количество объектов SharedPtr,
    // которые ссылаются на тот же управляемый объект
    [[nodiscard]] auto use_count() const -> size_t;
};

template<typename T>
SharedPtr<T>::SharedPtr() {
    p = nullptr;
    c = nullptr;
}

template<typename T>
SharedPtr<T>::SharedPtr(T *ptr) {
    p = ptr;
    c = new std::atomic_uint{1};
}

template<typename T>
SharedPtr<T>::SharedPtr(const SharedPtr &r) {
    c = nullptr;
    *this = r;
}

template<typename T>
SharedPtr<T>::SharedPtr(SharedPtr &&r) {
    p = std::move(r.p);
    c = std::move(r.c);
}

template<typename T>
SharedPtr<T>::~SharedPtr() {
    if (c == nullptr)
        return;
    (*c)--;
    if (*c == 0) {
        delete p;
        delete c;
    }
}

template<typename T>
auto SharedPtr<T>::operator=(const SharedPtr &r) -> SharedPtr & {
    if (this == &r)
        return *this;

    this->~SharedPtr();

    p = r.p;
    c = r.c;
    (*c)++;

    return *this;
}

template<typename T>
auto SharedPtr<T>::operator=(SharedPtr &&r) -> SharedPtr & {
    if (this == &r) {
        this->~SharedPtr();
        p = std::move(r.p);
        c = std::move( r.c);
    }
return *this;
}

template<typename T>
SharedPtr<T>::operator bool() const {
    return p != nullptr;
}

template<typename T>
auto SharedPtr<T>::operator*() const -> T & {
    return *p;
}

template<typename T>
auto SharedPtr<T>::operator->() const -> T * {
    return p;
}

template<typename T>
auto SharedPtr<T>::get() -> T * {
    return p;
}

template<typename T>
void SharedPtr<T>::reset() {
    *this = SharedPtr();
}

template<typename T>
void SharedPtr<T>::reset(T *ptr) {
    *this = SharedPtr(ptr);
}

template<typename T>
void SharedPtr<T>::swap(SharedPtr &r) {
    std::swap(p, r.p);
    std::swap(c, r.c);
}

template<typename T>
auto SharedPtr<T>::use_count() const -> size_t {
    if (c != nullptr)
        return *c;
    else
        return 0;
}

#endif // INCLUDE_SHAREDPTR_HPP_
