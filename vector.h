#ifndef VECTOR_H_
#define VECTOR_H_

#include <memory>
#include <algorithm>

template<class T>
class vector
{
public:
    typedef T           value_type;
    typedef value_type* pointer;
    typedef value_type* iterator;
    typedef value_type& reference;
    typedef size_t      size_type;
    typedef ptrdiff_t   difference_type;
    typedef std::bidirectional_iterator_tag iterator_category;
protected:
    std::allocator<value_type> alloc;
    iterator start;
    iterator finish;
    iterator end_of_storage;
    void insert_aux(iterator position, const T& x);
    inline void destroy(iterator first, iterator last) {
        while (first != last)
            alloc.destroy(--last);
    }
    void deallocate() {
        if (start)
            alloc.deallocate(start, end_of_storage - start);
    }
    void fill_initialize(size_type n, const T& value) {
        start = allocate_and_fill(n, value);
        finish = start + n;
        end_of_storage = finish;
    }
public:
    iterator begin() { return start; }
    iterator end() { return finish; }
    size_type size() const { return size_type(this->finish - this->start); }
    size_type capacity() const {
        return size_type(this->end_of_storage - this->start); }
    bool empty() const { return this->start == this->finish; }
    reference operator[](size_type n) { return *(this->start + n); }
    vector() : start(0), finish(0), end_of_storage(0) { }
    vector(size_type n, const T& value) { fill_initialize(n, value); }
    explicit vector(size_type n) { fill_initialize(n, T()); }
    template<class Iterator>
    vector(Iterator first, Iterator last) {
        size_type n = std::distance(first, last);
        start = alloc.allocate(n);
        finish = start;
        end_of_storage = start + n;
        for (auto iter = first; iter != last; iter++) {
            push_back(*iter);
        }
    }
    vector(const pointer first, const pointer last) {
        start = alloc.allocate(last - first);
        finish = start + (last - first);
        end_of_storage = finish;
        std::uninitialized_copy(first, last, start);
    }
    vector(const vector<T>& vx) {
        this->start = alloc.allocate(vx.capacity());
        this->finish = this->start + vx.size();
        this->end_of_storage = this->start + vx.capacity();
        std::uninitialized_copy(vx.start, vx.finish, this->start);
    }
    ~vector() {
        destroy(this->start, this->finish);
        deallocate();
    }
    reference front() { return *begin(); }
    reference back() { return *(end() - 1); }
    void push_back(const T& x) {
        if (finish != end_of_storage) {
            alloc.construct(finish, x);
            ++finish;
        } else {
            insert_aux(end(), x);
        }
    }
    void pop_back() {
        --finish;
        alloc.destroy(finish);
    }
    iterator erase(iterator position) {
        if (position + 1 != this->finish) {
            std::copy(position + 1, finish, position);
        }
        --finish;
        alloc.destroy(finish);
        return position;
    }
    iterator erase(iterator first, iterator last) {
        iterator i = std::copy(last, finish, first);
        destroy(i, finish);
        finish = finish - (last - first);
        return first;
    }
    iterator insert(iterator position, size_type n, const T& x);
    iterator insert(iterator position, const T& x) { return insert(position, 1, x); }
    void resize(size_type new_size, const T& x) {
        if (new_size < size()) {
            erase(begin() + new_size, end());
        } else {
            insert(end(), new_size - size(), x);
        }
    }
    void resize(size_type new_size) { resize(new_size, T()); }
    void clear() {
        erase(this->start, this->finish);
    }
    vector<T>& operator=(const vector<T>& vx) {
        destroy(this->start, this->finish);
        deallocate();
        start = alloc.allocate(vx.capacity());
        this->finish = this->start + vx.size();
        this->end_of_storage = this->start + vx.capacity();
        std::uninitialized_copy(vx.start, vx.finish, this->start);
        return *this;
    }
protected:
    iterator allocate_and_fill(size_type n, const T& x) {
        iterator result = alloc.allocate(n);
        std::uninitialized_fill_n(result, n, x);
        return result;
    }
};

template<class T>
void vector<T>::insert_aux(iterator position, const T& x)
{
    if (finish != end_of_storage) {
        alloc.construct(finish, *(finish - 1));
        ++finish;
        T x_copy = x;
        std::copy_backward(position, finish - 1, finish - 2);
        *position = x_copy;
    } else {
        const size_type old_size = size();
        const size_type len = old_size != 0 ? 2 * old_size : 1;
        iterator new_start = alloc.allocate(len);
        iterator new_finish = new_start;
        new_finish = std::uninitialized_copy(start, position, new_start);
        T x_copy = x;
        alloc.construct(new_finish, x_copy);
        ++new_finish;
        new_finish = std::uninitialized_copy(position, finish, new_finish);
        destroy(start, finish);
        deallocate();
        start = new_start;
        finish = new_finish;
        end_of_storage = new_start + len;
    }
}

template<class T>
typename vector<T>::iterator
vector<T>::insert(iterator position, size_type n, const T& x)
{
    if (n <= 0) return iterator(nullptr);
    T x_copy = x;
    iterator return_position;
    if (size_type(end_of_storage - finish) >= n) {
        const size_type elemts_after = finish - position;
        iterator old_finish = finish;
        if (n >= elemts_after) {
            std::uninitialized_fill_n(finish, n - elemts_after, x_copy);
            finish += n- elemts_after;
            std::uninitialized_copy(position, old_finish, finish);
            finish += elemts_after;
            std::fill(position, old_finish, x_copy);
        }
        else {
            std::uninitialized_copy(finish - n, finish, finish);
            finish += n;
            std::copy_backward(position, old_finish - n, old_finish);
            std::fill(position, position + n, x_copy);
        }
        return_position = position;
    } else {
        const size_type old_size = size();
        const size_type len = old_size + std::max(n, old_size);
        iterator new_start = alloc.allocate(len);
        iterator new_finish = new_start;
        new_finish = std::uninitialized_copy(start, position, new_start);
        return_position = new_finish;
        new_finish = std::uninitialized_fill_n(new_finish, n, x_copy);
        new_finish = std::uninitialized_copy(position, finish, new_finish);
        destroy(start, finish);
        deallocate();
        start = new_start;
        finish = new_finish;
        end_of_storage = new_start + len;
    }
    return return_position;
}

#endif