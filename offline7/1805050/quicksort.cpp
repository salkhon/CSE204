# include <iostream>
# include <vector>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void partition(std::vector<int>& integers, int* partitions, int lo, int hi) {
    int pivot = integers[lo];
    int ptrl = lo, ptrg = hi - 1;

    for (int i = lo + 1; i <= ptrg; i++) {
        if (integers[i] < pivot) {
            swap(&integers[i], &integers[ptrl++]);
        } else if (integers[i] > pivot) {
            swap(&integers[i], &integers[ptrg--]);
            i--;
        }
    }

    partitions[0] = ptrl, partitions[1] = ptrg + 1;
}

void _quicksort(std::vector<int>& integers, int* partitions, int lo, int hi) {
    if (hi - lo <= 1) {
        return;
    }
    // std::cout << "working: " << lo << " " << hi << std::endl;
    partition(integers, partitions, lo, hi);
    int lo_end = partitions[0];
    int hi_begin = partitions[1];

    _quicksort(integers, partitions, lo, lo_end);
    _quicksort(integers, partitions, hi_begin, hi);
}


std::vector<int> quicksort(const std::vector<int>& integers) {
    std::vector<int> sorted_ints(integers);
    int partitions[2];
    _quicksort(sorted_ints, partitions, 0, sorted_ints.size());
    return sorted_ints;
}
