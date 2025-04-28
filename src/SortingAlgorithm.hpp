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
                std::swap(v[j], v[i]);
            }

        }
    }
}

/* 
    Ora implemento le operazioni di enqueue e dequeue:
    - heap_enqueue: inserisce un nuovo valore nell’heap mantenendo la proprietà di heap.
    - heap_dequeue: estrae il valore massimo (la radice) dall’heap, mantenendo la proprietà di heap.
*/

template<Sortable T>
void heap_enqueue(std::vector<T>& heap, T value) //heap iff coda con priorità
{
    heap.push_back(value); // inserisci il valore alla fine
    int i = heap.size() - 1; //i: indice dell'elemento appena inserito

    //Riordino in modo da avere la struttura di heap
    while (i > 0)
    {
        int padre = (i - 1) / 2;
        if (heap[padre] < heap[i])
        {
            std::swap(heap[padre], heap[i]);
            i = padre;
        }
        else
            break;
    }
}

template<Sortable T>
T heap_dequeue(std::vector<T>& heap)
{
    if (heap.empty())
        throw std::runtime_error("L'heap è vuoto!");

    T maxValue = heap[0];

    heap[0] = heap.back(); //Sostituisce la radice (heap[0]) con l’ultimo elemento.
    heap.pop_back(); //Rimuove l'ultimo elemento (la radice spostata prima)

    int i = 0;
    int n = heap.size();

    //Sistemo la struttura di heap
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


//L'heapsort utilizza heap_enqueue(..) e heap_dequeue(..)
template<Sortable T>
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

