#include <cmath> // contiene floor
#include <iostream>
#include <numeric> // contiene iota
#include <iostream>
#include <sstream>
#include <chrono> // https://en.cppreference.com/w/cpp/chrono

#include "SortingAlgorithm.hpp"
using namespace std;

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

struct ClassObj{
    double value;

    // bool operator< (const ClassObj& rhs) { return value < rhs.value; }
};

inline bool operator< (const ClassObj& lhs, const ClassObj& rhs) { return lhs.value < rhs.value; }

int main(int argc, char *argv[]) //posso dare degli input al programma
{

    cout << "argc: " << argc << endl; //argc: conta gli argomenti, compreso l'eseguibile
    for(int a = 0; a < argc; a++)
        cout << argv[a] << " ";
    cout << endl;

    size_t m = 10;
    if(argc > 1) //se inserisco un input
    {
        istringstream convert(argv[1]);
        convert >> m;
        cout << "use value: "  << m << endl; //m è uguale al primo argomento inserito (dopo l'eseguibile)
    }
    else
        cerr << "use default value: "  << m << endl; //non non inserisco argomenti uso il valore di default (10)

    vector<int> v1(m); //crea v1 di dimensione m
    std::iota(v1.begin(), v1.end(), -4); //l'ultimo argomento è il valore di partenza: il vettore v1 avrà m numeri consecutivi a partire da -4

    //cout << "v1: " << endl;
    //cout << ArrayToString(v1) << endl;

    srand(2); //inizializza il generatore random con seme fisso
    vector<double> v2(m); //inizializza il vettore di dimensione m
    for(size_t i = 0; i < m; i++)
        v2[i] = rand() / ((double)RAND_MAX); //ottengo un numero tra 0 e 1

    // cout << "v2: " << endl;
    // cout << ArrayToString(v2) << endl;

    vector<int> v3(m, 0); //inizializza il vettore di m zeri
    for(size_t i = floor(m * 0.5) + 1; i < m; i++) //riempie la seconda metà del vettore con numeri casuali tra 0 e 999
        v3[i] = rand() % 1000;

    copy(v1.begin(), v1.begin() + floor(m * 0.5) + 1, v3.begin()); //copia la prima metà (+1) dal vettore v1 e la sovrascrive alla prima metà (+1) di v3
    // ho ottenuto un vettore che ha la prima metà uguale a v1 e la seconda metà formata da numeri casuali da 0 a 999
    // cout << "v3: " << endl;
    // cout << ArrayToString(v3) << endl;


    // https://www.epochconverter.com/
    const auto today_time = std::chrono::system_clock::now();
    std::cout << "Tempo trascorso dal 1 gennaio 1970: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     today_time.time_since_epoch()).count() << " milliseconds" <<endl;


    unsigned int num_experiment = 100;

    // Try commenting out the overloading of the "<" operator and uncommenting the two lines below:
    // an error will be reported because ClassObj is not "Sortable"

    // vector<ClassObj> v;
    // SortLibrary::SelectionSort<ClassObj>(v); // ATTENZIONE: il vettore è non inizializzato -> non eseguire


    double time_elapsed_bubble_v1 = 0.0;
    for(unsigned int t = 0; t < num_experiment; t++) //ripeti per il numero di esperimenti che voglio fare
    {
        vector<int> v(v1); //copia v1 in v

        std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now(); //definisce il tempo di inizio
        SortLibrary::BubbleSort<int>(v); //applica il selection sort
        std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now(); //definisce il tempo di fine
        time_elapsed_bubble_v1 += std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count(); //conta il tempo dei 100 esperimenti
    }
    time_elapsed_bubble_v1 /= num_experiment; //tempo medio (più affidabile)

    cout << "Bubble Sort - v1: " << time_elapsed_bubble_v1 << endl;

    //Stesso con v2 - ss
    double time_elapsed_bubble_v2 = 0.0;
    for(unsigned int t = 0; t < num_experiment; t++)
    {
        vector<double> v(v2);

        std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
        SortLibrary::BubbleSort<double>(v);
        std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
        time_elapsed_bubble_v2 += std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    }
    time_elapsed_bubble_v2 /= num_experiment;

    cout << "Bubble Sort - v2: " << time_elapsed_bubble_v2 << endl;


    //stesso con v3 - ss
    double time_elapsed_bubble_v3 = 0.0;
    for(unsigned int t = 0; t < num_experiment; t++)
    {
        vector<int> v(v3);

        std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
        SortLibrary::BubbleSort<int>(v);
        std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
        time_elapsed_bubble_v3 += std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    }
    time_elapsed_bubble_v3 /= num_experiment;

    cout << "Bubble Sort - v3: " << time_elapsed_bubble_v3 << endl;

    
    //stesso con v1 - is
    double time_elapsed_heap_v1 = 0.0;
    for(unsigned int t = 0; t < num_experiment; t++)
    {
        vector<int> v(v1);

        std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
        SortLibrary::HeapSort<int>(v);
        std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
        time_elapsed_heap_v1 += std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    }
    time_elapsed_heap_v1 /= num_experiment;

    cout << "Heap Sort - v1: " << time_elapsed_heap_v1 << endl;

    //stesso con v2 - is
    double time_elapsed_heap_v2 = 0.0;
    for(unsigned int t = 0; t < num_experiment; t++)
    {
        vector<double> v(v2);

        std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
        SortLibrary::HeapSort<double>(v);
        std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
        time_elapsed_heap_v2 += std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    }
    time_elapsed_heap_v2 /= num_experiment;

    cout << "Heap Sort - v2: " << time_elapsed_heap_v2 << endl;

    //stesso con v3 - is
    double time_elapsed_heap_v3 = 0.0;
    for(unsigned int t = 0; t < num_experiment; t++)
    {
        vector<int> v(v3);

        std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
        SortLibrary::HeapSort<int>(v);
        std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
        time_elapsed_heap_v3 += std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    }
    time_elapsed_heap_v3 /= num_experiment;

    cout << "Heap Sort - v3: " << time_elapsed_heap_v3 << endl;
    return 0;
}




