#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <algorithm>

namespace MTL{
    template<class Iterator>
    void bubble_sort(Iterator First, Iterator Last)
    {
        for (auto i = First; i != Last; i++) {
            auto t = ++i; --i;
            for (auto j = t; j != Last; j++) {
                if (*i > *j) {
                    std::iter_swap(i, j);
                }
            }
        }
    }
    template<class Iterator>
    void heapify(Iterator First, int n, int i)
    {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (l < n && *(First + l) > *(First + largest))
            largest = l;

        if (r < n && *(First + r) > *(First + largest))
            largest = r;

        if (largest != i) {
            std::iter_swap(First + i, First + largest);
            heapify(First, n, largest);
        }
    }
    
    template<class Iterator>
    void heap_sort(Iterator First, Iterator Last)
    {
        int n = Last - First;
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(First, n, i);
        for (int i = n - 1; i > 0; i--) {
            std::iter_swap(First, First + i);
            heapify(First, i, 0);
        }
    }

    template<class Iterator>
    int partition (Iterator First, int low, int high)
    {
        auto pivot = *(First + high);
        int i = (low - 1);
        for (int j = low; j <= high- 1; j++) {
            if (*(First + j) < pivot) {
                i++;
                std::iter_swap(First + i, First + j);
            }
        }
        std::iter_swap(First + i + 1, First + high);
        return (i + 1);
    }

    template<class Iterator>
    void quick_sort_aux(Iterator First, int low, int high)
    {
        if (low < high) {
            int pi = partition(First, low, high);
            quick_sort_aux(First, low, pi - 1);
            quick_sort_aux(First, pi + 1, high);
        }
    }

    template<class Iterator>
    void quick_sort(Iterator First, Iterator Last)
    {
        int low = 0;
        int high = low + (Last - First) - 1;
        quick_sort_aux(First, low, high);
    }

    template<class Iterator, class T>
    Iterator find(Iterator First, Iterator Last, const T& value)
    {
        while (*First != value && First != Last)
            First++;
        return First;
    }

    template<class Iterator, class T>
    Iterator binary_search(Iterator First, Iterator Last, const T& value)
    {
        while (First <= Last) {
            auto Middle = First + (Last - First) / 2;
            if (*Middle == value) return Middle;
            *Middle > value ? (Last = Middle) : (First = Middle + 1);
        }
        return Last;
    }
}

#endif