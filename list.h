#ifndef LIST_H_
#define LIST_H_

#include <algorithm>
#include <memory>

template<class T>
struct __list_node
{
    __list_node<T>* prev;
    __list_node<T>* next;
    T data;
};

template<class T>
struct __list_iterator
{
    typedef __list_iterator<T> self;
    typedef __list_iterator<T> iterator;

    typedef std::bidirectional_iterator_tag iterator_category;
    typedef T                  value_type;
    typedef T*                 pointer;
    typedef T&                 reference;
    typedef __list_node<T>*    link_type;
    typedef size_t             size_type;
    typedef std::ptrdiff_t     difference_type;

    link_type node;

    __list_iterator(link_type x) : node(x) { }
    __list_iterator() { }
    __list_iterator(const iterator& x) : node(x.node) { }

    bool operator==(const self& x) const { return node == x.node; }
    bool operator!=(const self& x) const { return node != x.node; }
    reference operator*() const { return node->data; }
    pointer operator->() const { return &(operator*()); }

    self& operator++() {
        node = node->next;
        return *this;
    }

    self operator++(int) {
        self tmp = *this;
        ++*this;
        return tmp;
    }
    self& operator--() {
        node = node->prev;
        return *this;
    }
    self operator--(int) {
        self tmp = *this;
        --*this;
        return tmp;
    }
};

template<class T>
class list
{
protected:
    typedef __list_node<T> list_node;
public:
    typedef __list_iterator<T> iterator;
    typedef T&                 reference;
    typedef list_node*         link_type;
    typedef size_t             size_type;
protected:
    link_type node;
    std::allocator<list_node> alloc;
    link_type get_node() { return alloc.allocate(1); }
    void put_node(link_type p) { alloc.deallocate(p, 1); }
    link_type create_node(const T& x) {
        link_type p = get_node();
        alloc.construct(&(p->data), x);
        return p;
    }
    void destroy_node(link_type p) {
        alloc.destroy(p);
        put_node(p);
    }
    void empty_initialize() {
        node = get_node();
        node->next = node;
        node->prev = node;
    }
    template<typename InputIterator>
    void initialize_dispatch(InputIterator first, InputIterator last) {
        for ( ; first != last; first++) {
            push_back(*first);
        }
    }
    void fill_initialize(size_type n, const T& x) {
        for ( ; n ; n--) {
            push_back(x);
        }
    }
    void transfer(iterator position, iterator first, iterator last) {
        if (position != last) {
            position.node->prev->next = first.node;
            first.node->prev->next = last.node;
            link_type tmp = first.node->prev;
            first.node->prev = position.node->prev;
            last.node->prev->next = position.node;
            position.node->prev = last.node->prev;
            last.node->prev = tmp;
        }
    }
public:
    list() { empty_initialize(); }
    list(size_type n, const T& x) {
        empty_initialize();
        fill_initialize(n, x);
    }
    
    list(const list<T>& lx) {
        empty_initialize();
        initialize_dispatch(lx.cbegin(), lx.cend());
    }

    list(const T* first, const T* last) {
        empty_initialize();
        while (first != last) {
            push_back(*first++);
        }
    }

    template<class Iterator>
    list(Iterator first, Iterator last) {
        empty_initialize();
        while (first != last) {
            push_back(*first++);
        }
    }

    ~list() { 
        clear();
        alloc.deallocate(node, 1);
    }
    iterator begin() { return node->next; }
    iterator end() { return node; }
    iterator cbegin() const { return node->next; }
    iterator cend() const { return node; }
    bool empty() { return begin() == end(); }
    size_type size() {
        size_type result = std::distance(begin(), end());
        return  result;
    }
    reference front() { return *begin(); }
    reference back() { return *(--end()); }
    void insert(iterator position, const T& x) {
        link_type tmp = create_node(x);
        tmp->next = position.node;
        tmp->prev = position.node->prev;
        (position.node->prev)->next = tmp;
        position.node->prev = tmp;
    }
    void push_back(const T& x) { insert(end(), x); }
    void push_front(const T& x) { insert(begin(), x); }
    iterator erase(iterator position) {
        link_type prev_node = position.node->prev;
        link_type next_node = position.node->next;
        prev_node->next = next_node;
        next_node->prev = prev_node;
        destroy_node(position.node);
        return iterator(next_node);
    }
    void pop_back() { iterator tmp = end();  erase(--tmp); }
    void pop_front() { erase(begin()); }
    void clear() {
        link_type cur = (link_type)node->next;
        link_type tmp;
        while (cur != node) {
            tmp = cur->next;
            destroy_node(cur);
            cur = tmp;
        }
        node->next = node;
        node->prev = node;
    }
    void remove(const T& value) {
        iterator first= begin();
        iterator last = end();
        iterator next;
        while (first != last) {
            next = first;
            next++;
            if (*first == value) {
                erase(first);
            }
            first = next;
        }
    }
    void unique() {
        iterator first = begin();
        iterator last = end();
        if (first == last) return;
        iterator next = first;
        while(++next != last) {
            if (*first == *next) {
                erase(next);
            } else {
                first = next;
            }
            next = first;
        }
    } 
    void splice(iterator position, list<T>& x) {
        if (!x.empty()) {
            transfer(position, x.begin(), x.end());
        }
    }
    void splice(iterator position, list<T>&, iterator i) {
        iterator j = i;
        ++j;
        if (j == position || i == position) return;
        transfer(position, i, j);
    }
    void splice(iterator position, list<T>&, iterator first, iterator last) {
        if (first != last) {
            transfer(position, first, last);
        }
    }
    void merge(list<T>& x) {
        iterator index = begin();
        iterator x_index = x.begin();
        while (index != end() && x_index != x.end()) {
            if (*index < *x_index) {
                index++;
            } else {
                splice(index, x, x_index++);
            }
        }
        if (x_index != x.end()) {
            splice(index, x, x_index, x.end());
        }
    }
    void reverse() {
        if (node->next == node->prev) return;
        iterator index = begin();
        ++index;
        while (index != end()) {
            splice(begin(), *this, index++);
        }
    }
    list<T>& operator=(const list<T>& lx) {
        clear();
        initialize_dispatch(lx.cbegin(), lx.cend());
        return *this;
    }
};

#endif