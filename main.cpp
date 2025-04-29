#include <cmath> 
#include <iostream>
#include <numeric> 
#include <iostream>
#include <sstream>
#include <chrono> 

#include "SortingAlgorithm.hpp"
using namespace std;

//SE VOGLIIO VISUALIZZARE I VETTORI POSSO CONVERTIRLI FACILMENTE IN STRINGHE GRAZIE ALLA SEGUENTE FUNZIONE
/*
template<typename T>
string ArrayToString(const vector<T>& v)
{
    string str;
    ostringstream toString;
    toString << "[ ";
    for (const T& e: v)
        toString << e << " ";
    toString << "]";

    return toString.str();
}
*/

struct ClassObj{
    double value;
};

inline bool operator< (const ClassObj& lhs, const ClassObj& rhs) { return lhs.value < rhs.value; }

int main(int argc, char *argv[]) //Posso dare degli input al programma quando lancio l'eseguibile
{

    cout << "Argomenti inseriti: " << argc << endl; //argc: conta gli argomenti, compreso l'eseguibile
    for(int a = 0; a < argc; a++)
        cout << argv[a] << " ";
    cout << endl;


    //Assegno un valore di default: 10
    size_t default_value = 10;
    if(argc > 1) //se inserisco un input
    {
        istringstream convert(argv[1]);
        convert >> default_value;
        cout << "Uso il valore: "  << default_value << endl; //default_value è uguale al primo argomento inserito (dopo l'eseguibile)
    }
    else
        cerr << "Uso il valore di default: "  << default_value << endl; //non non inserisco argomenti uso il valore di default (10)

    vector<int> v1(default_value); //crea v1 di dimensione default_value
    std::iota(v1.begin(), v1.end(), -4); //l'ultimo argomento è il valore di partenza: il vettore v1 avrà default_value numeri consecutivi a partire da -4
    
    //cout << "v1: " << ArrayToString(v1) << endl;

    srand(2); //inizializza il generatore random con seme fisso
    vector<double> v2(default_value); //inizializza il vettore di dimensione default_values
    for(size_t i = 0; i < default_value; i++)
        v2[i] = rand() / ((double)RAND_MAX); //ottengo un numero tra 0 e 1

    //cout << "v2: " << ArrayToString(v2) << endl;

    vector<int> v3(default_value, 0); //inizializza il vettore di default_value zeri
    for(size_t i = floor(default_value * 0.5) + 1; i < default_value; i++) //riempie la seconda metà del vettore con numeri casuali tra 0 e 999
        v3[i] = rand() % 1000;

    copy(v1.begin(), v1.begin() + floor(default_value * 0.5) + 1, v3.begin()); //copia la prima metà (+1) dal vettore v1 e la sovrascrive alla prima metà (+1) di v3
    // ho ottenuto un vettore che ha la prima metà uguale a v1 e la seconda metà formata da numeri casuali da 0 a 999
    //cout << "v3: " << ArrayToString(v3) << endl;


    unsigned int num_experiments = 100;

    //Calcolo il tempo impiegato dal bubble sort su v1
    double time_bubble_v1 = 0.0;
    for(unsigned int t = 0; t < num_experiments; t++) //ripeti per il numero di esperimenti che voglio fare
    {
        vector<int> v(v1); //copia v1 in v

        std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now(); //definisce il tempo di inizio
        SortLibrary::BubbleSort<int>(v); //applica il selection sort
        std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now(); //definisce il tempo di fine
        time_bubble_v1 += std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count(); //conta il tempo dei 100 esperimenti
    }
    time_bubble_v1 /= num_experiments; //tempo medio (più affidabile)

    cout << "Bubble Sort - v1: " << time_bubble_v1 << endl;

    //Calcolo il tempo impiegato dal bubble sort su v2
    double time_bubble_v2 = 0.0;
    for(unsigned int t = 0; t < num_experiments; t++)
    {
        vector<double> v(v2);

        std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
        SortLibrary::BubbleSort<double>(v);
        std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
        time_bubble_v2 += std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    }
    time_bubble_v2 /= num_experiments;

    cout << "Bubble Sort - v2: " << time_bubble_v2 << endl;


    //Calcolo il tempo impiegato dal bubble sort su v3
    double time_bubble_v3 = 0.0;
    for(unsigned int t = 0; t < num_experiments; t++)
    {
        vector<int> v(v3);

        std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
        SortLibrary::BubbleSort<int>(v);
        std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
        time_bubble_v3 += std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    }
    time_bubble_v3 /= num_experiments;

    cout << "Bubble Sort - v3: " << time_bubble_v3 << endl;

    
    //Calcolo il tempo impiegato dall'heap sort su v1
    double time_heap_v1 = 0.0;
    for(unsigned int t = 0; t < num_experiments; t++)
    {
        vector<int> v(v1);

        std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
        SortLibrary::HeapSort<int>(v);
        std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
        time_heap_v1 += std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    }
    time_heap_v1 /= num_experiments;

    cout << "Heap Sort - v1: " << time_heap_v1 << endl;

    //Calcolo il tempo impiegato dall'heap sort su v2
    double time_heap_v2 = 0.0;
    for(unsigned int t = 0; t < num_experiments; t++)
    {
        vector<double> v(v2);

        std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
        SortLibrary::HeapSort<double>(v);
        std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
        time_heap_v2 += std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    }
    time_heap_v2 /= num_experiments;

    cout << "Heap Sort - v2: " << time_heap_v2 << endl;

    //Calcolo il tempo impiegato dall'heap sort su v3
    double time_heap_v3 = 0.0;
    for(unsigned int t = 0; t < num_experiments; t++)
    {
        vector<int> v(v3);

        std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
        SortLibrary::HeapSort<int>(v);
        std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
        time_heap_v3 += std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    }
    time_heap_v3 /= num_experiments;

    cout << "Heap Sort - v3: " << time_heap_v3 << endl;
    
    return 0;
}




