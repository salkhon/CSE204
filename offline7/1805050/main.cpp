# include <iostream>
# include <vector>
# include <chrono>
# include <functional>
# include "quicksort.cpp"
# include "mergesort.cpp"
# define ASC 2
# define DESC 3

using TIME_UNIT = std::micro;

const int NUM_OF_ITERATION = 1;

const int LO = 0;
const int HI = 1000000;

std::vector<int> get_random_integers(int n, int order) {
    srand(time(0));
    std::vector<int> vec(n);
    int random;
    if (order == ASC) {
        int val = LO; // HI might not be satisfied
        for (int i = 0; i < n; i++) {
            random = rand();
            if (random % 3 == 0) {
                vec[i] = val;
            } else {
                vec[i] = ++val;
            }
        }
    } else if (order == DESC) {
        int val = HI;
        for (int i = 0; i < n; i++) {
            random = rand();
            if (random % 3 == 0) {
                vec[i] = val;
            } else {
                vec[i] = --val;
            }
        }
    } else {
        for (int i = 0; i < n; i++) {
            random = rand() % (HI - LO);
            random += LO;
            vec[i] = random;
        }
    }

    return vec;
}

void time_sort(int n, int order, int num_iter, long double* times) {
    std::vector<std::vector<int>> vecs(num_iter);

    for (int i = 0; i < num_iter; i++) {
        vecs[i] = get_random_integers(n, order);
    }

    auto t0 = std::chrono::high_resolution_clock::now();
    for (int t = 0; t < num_iter; t++) {
        mergesort(vecs[t]);
    }
    auto t1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<long double, TIME_UNIT> mtime = t1 - t0;
    times[0] = mtime.count() / num_iter;

    t0 = std::chrono::high_resolution_clock::now();
    for (int t = 0; t < num_iter; t++) {
        quicksort(vecs[t]);
    }
    t1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<long double, TIME_UNIT> qtime = t1 - t0;
    times[1] = qtime.count() / num_iter;
}

void print(const std::vector<int>& vec) {
    std::cout << "vector<int>: [ ";
    for (int i = 0; i < int(vec.size()); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << "]" << std::endl;
}

void print_sample_sort(int n, int order) {
    const std::vector<int>& sample_vec = get_random_integers(n, order);
    // print(sample_vec);
    const std::vector<int>& msorted_vec = mergesort(sample_vec);
    const std::vector<int>& qsorted_vec = quicksort(sample_vec);
    
    std::cout << "Mergesorted   Quicksorted ";
    for (int i = 0; i < n; i++) {
        std::cout << msorted_vec[i] << "\t" << qsorted_vec[i] << std::endl;
    }
}

int main() {
    int n;
    std::cout << "How many integers to generate? : ";
    std::cin >> n;

    int order;
    std::cout << "In what order? 1. Random 2. Ascending 3. Descending\nSelect: ";
    std::cin >> order;

    long double times[2];
    time_sort(n, order, NUM_OF_ITERATION, times);
    long double mtime = times[0], qtime = times[1];

    print_sample_sort(n, order);
    
    std::cout << "Time taken by mergesort: " << mtime << " units " << std::endl;
    std::cout << "Time taken by quicksort: " << qtime << " units " << std::endl;

    return 0;
}
