#ifndef MAP_H_
#define MAP_H_

#include <memory>
#include "vector.h"

template<class T1, class T2>
struct pair{
    T1 first;
    T2 second;
    pair(): first(T1()), second(T2()) { }
    pair(const T1& a, const T2& b): first(a), second(b) { }
    bool operator==(const pair<T1, T2>& x) {
        return first == x.first ? true : false;
    }
    bool operator!=(const pair<T1, T2>& x) {
        return first != x.first ? true : false;
    }
    bool operator<(const pair<T1, T2>& x) {
        return first < x.first ? true : false;
    }
    bool operator>(const pair<T1, T2>& x) {
        return first > x.first ? true : false;
    }
};

template<class Key, class T>
class map
{
public:
    typedef Key key_type;
    typedef T data_type;
    typedef T mapped_type;
    typedef pair<Key, T> value_type;
public:
    typedef typename vector<pair<Key, T>>::pointer pointer;
    typedef typename vector<pair<Key, T>>::reference reference;
    typedef typename vector<pair<Key, T>>::iterator iterator;
    typedef typename vector<pair<Key, T>>::size_type size_type;
    map() { }
    map(const map<Key, T>& x): t(x.t) { }
    map<Key, T>& operator=(const map<Key, T>& x) {
        t = x.t;
        return *this;
    }
    iterator begin() { return t.begin(); }
    iterator end() { return t.end(); }
    bool empty() const { return t.empty(); }
    size_type size() const { return t.size(); }
    void clear() { t.clear(); }
    void insert(const value_type& x) {
        auto iter = biSearch(x.first);
        if (iter == t.end() || *iter != x) { t.insert(iter, x); }
    }
    void erase(const key_type& x) {
        auto iter = biSearch(x);
        if (iter != t.end()) {
            t.erase(iter);
        }
    }
    iterator find(const key_type& x) {
        auto iter = biSearch(x);
        return iter;
    }
    T& operator[](const key_type& k) {
        auto iter = biSearch(k);
        if (iter == t.end() || iter->first != k) {
            iter = t.insert(iter, value_type(k, T()));
        }
        return iter->second;
    }
private:
    typedef vector<pair<Key, T>> rep_type;
    rep_type t;
    iterator biSearch(const key_type& x) {
        auto x_copy = x;
        auto start = t.begin();
        auto finish = t.end();
        while (start != finish) {
            auto mid = start + (finish - start) / 2;
            if (mid->first == x_copy) {
                return mid;
            } else {
                mid->first > x_copy ? (finish = mid) : (start = mid + 1);
                if (start == t.end() || start->first > x_copy) return start;
                if ((finish- 1)->first < x_copy) return finish;
            }
        }
        return t.end();
    }
};

#endif