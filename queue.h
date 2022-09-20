#ifndef QUEUE_H_
#define QUEUE_H_

#include <memory>
#include <cassert>

template<class T>
class queue {
public:
    typedef T*     pointer;
    typedef T&     reference;
    typedef T      value_type;
    typedef size_t size_type;
protected:
    std::allocator<T> alloc;
    pointer head_, tail_;
    pointer eos_, bos_;
    size_type size_;
    void deallocate() {
        if (bos_) 
            alloc.deallocate(bos_, eos_ - bos_);
    }
public:
    queue(size_type n) { 
        head_ = tail_ = alloc.allocate(n);
        size_ = 0;
        eos_ = head_ + n;
        bos_ = head_;
    }
    queue(const queue<T>& qx) {
        head_ = tail_ = alloc.allocate(qx.capacity());
        bos_ = head_; eos_ = head_ + qx.capacity();
        head_ += qx.head_ - bos_;
        pointer tmp1 = qx.head_, tmp2 = head_;
        while (tmp1 != qx.tail_) {
            *tmp2 = *tmp1;
            tmp1 = (tmp1 + 1 == qx.eos_) ? qx.bos_ : tmp1 + 1;
            tmp2 = (tmp2 + 1 == eos_) ? bos_ : tmp2 + 1;
        }
        tail_ = tmp2;
        size_ = qx.size_;
    }
    ~queue() {
        while (!empty()) { pop(); }
        deallocate();
    }
    size_type capacity() const { return eos_ - bos_; }
    size_type size() const { return size_; }
    bool empty() const { return size_ == 0; }
    reference front() const { assert(!empty()); return *head_; }  
    reference back() const {
        assert(!empty());
        pointer tmp = tail_ == bos_ ? eos_ - 1 : tail_ - 1;
        return *(tmp); }
    void push(const T& x) {
        assert(size() < capacity());
        alloc.construct(tail_, x);
        tail_ = (tail_ + 1 == eos_)? bos_ : tail_ + 1;
        size_++;
    }
    void pop() {
        assert(!empty());
        alloc.destroy(head_);
        head_ = (head_ + 1 == eos_)? bos_ : head_ + 1;
        size_--;
    }
    queue<T>& operator=(const queue<T>& qx) {
        while (!empty()) { pop(); }
        deallocate();
        head_ = alloc.allocate(qx.capacity());
        bos_ = head_; eos_ = head_ + qx.capacity();
        head_ += qx.head_ - qx.bos_;
        pointer tmp1 = qx.head_; 
        pointer tmp2 = head_;
        while (tmp1 != qx.tail_) {
            *tmp2 = *tmp1;
            tmp1 = (tmp1 + 1 == qx.eos_) ? qx.bos_ : tmp1 + 1;
            tmp2 = (tmp2 + 1 == eos_) ? bos_ : tmp2 + 1;
        }
        tail_ = tmp2;
        size_ = qx.size_;
        return *this;
    }
};

#endif