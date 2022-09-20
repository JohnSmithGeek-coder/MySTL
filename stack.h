#ifndef STACK_H_
#define STACK_H_

#include <memory>
#include <cassert>

template<class T>
class stack {
public:
    typedef size_t size_type;
    typedef T      value_type;
    typedef T&     reference;
    typedef T*     pointer;
protected:
    std::allocator<T> alloc;
    pointer top_;
    pointer bottom_;
    pointer end_of_storage_;
    void deallocate() {
        if (bottom_)
            alloc.deallocate(bottom_, end_of_storage_ - bottom_);
    }
public:
    stack(size_type n) { 
        top_ = bottom_ = alloc.allocate(n); 
        end_of_storage_ = bottom_ + n;
    }
    stack(const stack<T>& sx) {
        top_ = bottom_ = alloc.allocate(sx.capacity());
        end_of_storage_ = bottom_ + sx.capacity();
        std::uninitialized_copy(sx.bottom_, sx.top_, bottom_);
    }
    ~stack() {
        while (!empty()) { pop(); } 
        deallocate();
    }
    size_type capacity() const { return end_of_storage_ - bottom_; }
    size_type size() const { return top_ - bottom_; }
    bool empty() const { return top_ == bottom_; }
    void push(const T& x) {
        assert(size() < capacity());
        alloc.construct(top_++, x); }
    void pop() {
        assert(!empty());
        alloc.destroy(--top_); }
    reference top() {
        assert(!empty());
        T* tmp = top_;
        return *(--tmp); }
    stack<T>& operator=(const stack<T>& sx) {
        while (!empty()) { pop(); }
        deallocate();
        top_ = bottom_ = alloc.allocate(sx.capacity());
        end_of_storage_ = bottom_ + sx.capacity();
        std::uninitialized_copy(sx.bottom_, sx.top_, bottom_);
        return *this;
    }
};

#endif