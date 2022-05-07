# include <iostream>
# include <vector>

void _merge(std::vector<int>& integers, std::vector<int>& aux, int lo, int mid, int hi) {
    // sorted elements exist on integers
    // mid is exclusive for left subarray
    int ptrl = lo, ptrr = mid;
    int i = lo;
    while (i < hi) {
        if (ptrl == mid) {
            aux[i++] = integers[ptrr++];
        } else if (ptrr == hi) {
            aux[i++] = integers[ptrl++];
        } else if (integers[ptrr] < integers[ptrl]) {
            aux[i++] = integers[ptrr++];
        } else {
            aux[i++] = integers[ptrl++];
        }
    }
}

void _mergesort(std::vector<int>& integers, std::vector<int>& aux, int lo, int hi) {
    if (hi - lo <= 1) {
        return;
    }

    int mid = (lo + hi) / 2; // exclusive for left, inclusive for right

    _mergesort(aux, integers, lo, mid); // merged in integers
    _mergesort(aux, integers, mid, hi);

    _merge(integers, aux, lo, mid, hi); // merge in aux
}

std::vector<int> mergesort(const std::vector<int>& integers) {
    std::vector<int> sorted_ints(integers);
    std::vector<int> aux(integers);
    _mergesort(sorted_ints, aux, 0, sorted_ints.size());
    std::copy(aux.begin(), aux.end(), sorted_ints.begin());
    return sorted_ints;
}
