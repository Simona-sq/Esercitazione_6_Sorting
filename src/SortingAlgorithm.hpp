#pragma once

#include <iostream>
#include <vector>
#include <queue>


namespace SortLibrary { 


template<typename T>
concept Sortable = requires(T& t) {
    {t < t} -> std::convertible_to<bool>;
};

template<Sortable T>
void BubbleSort(std::vector<T>& v)
{
    const unsigned int n = v.size();

    for(unsigned int i = 0; i < n - 1; i++)
    {
        for(unsigned int j = i+1 ; j < n; j++)
        {
            if(v[j] < v[i])
            {
                T tmp = v[i];
                v[i] = v[j];
                v[j] = tmp;
            }

        }
    }
}

template<typename T>
void heap_enqueue(std::vector<T>& heap, T value)
{
    heap.push_back(value); // inserisci alla fine
    int i = heap.size() - 1;

    // Bubble up
    while (i > 0)
    {
        int parent = (i - 1) / 2;
        if (heap[parent] < heap[i])
        {
            std::swap(heap[parent], heap[i]);
            i = parent;
        }
        else
            break;
    }
}

template<typename T>
T heap_dequeue(std::vector<T>& heap)
{
    if (heap.empty())
        throw std::runtime_error("Heap vuoto!");

    T maxValue = heap[0];

    heap[0] = heap.back();
    heap.pop_back();

    int i = 0;
    int n = heap.size();

    // Bubble down
    while (true)
    {
        int left = 2*i + 1;
        int right = 2*i + 2;
        int largest = i;

        if (left < n && heap[left] > heap[largest])
            largest = left;
        if (right < n && heap[right] > heap[largest])
            largest = right;

        if (largest != i)
        {
            std::swap(heap[i], heap[largest]);
            i = largest;
        }
        else
            break;
    }

    return maxValue;
}

template<typename T>
void HeapSort(std::vector<T>& v)
{
    std::vector<T> heap;

    // Enqueue: costruisco il heap
    for (auto& x : v)
        heap_enqueue(heap, x);

    // Dequeue: estraggo ordinato
    for (int i = v.size()-1; i >= 0; i--)
        v[i] = heap_dequeue(heap);
}
}

