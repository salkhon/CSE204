#ifndef OFFLINE5_HEAP_H
#define OFFLINE5_HEAP_H

#include <iostream>
#include <vector>

// MAX HEAP

class Heap {
    int* array;
    size_t arr_size;

    // population + 1
    size_t tail;

public:
    // starts from index 1
    Heap(size_t max_size) : array{new int[max_size + 1]}, arr_size{max_size + 1}, tail{1} {}

    ~Heap() { delete[] this->array; };

    void insert(int n);

    size_t size() const;

    int getMax();

    void deleteKey();

private:
    void swim(size_t index);

    void sink(size_t index);
};

void Heap::swim(size_t index) {
    for (int i = index; i > 1 && this->array[i] > this->array[i / 2]; i /= 2) {
        // swap current node with parent as long as a larger parent is found
        std::swap(this->array[i], this->array[i / 2]);
    }
}

void Heap::sink(size_t index) {
    for (size_t i = index, max_child_index; 2 * i < this->tail; i = max_child_index) {
        // swap with larger child as long as neither of the child is larger than the current node
        max_child_index = 2 * i;
        if (2 * i  + 1 < this->tail && this->array[2 * i + 1] > this->array[2 * i]) {
            max_child_index = 2 * i + 1;
        }

        if (this->array[max_child_index] <= this->array[i]) {
            break;
        }

        std::swap(this->array[i], this->array[max_child_index]);
    }
}

void Heap::insert(int n) {
    if (this->tail < this->arr_size) {
        this->array[this->tail] = n;

        swim(this->tail);
        this->tail++;
    }
}

size_t Heap::size() const {
    return this->tail - 1;
}

int Heap::getMax() {
    int max = 0;
    if (this->tail > 1) {
        max = this->array[1];
    }
    return max;
}

void Heap::deleteKey() {
    if (this->tail > 1) {
        std::swap(this->array[1], this->array[--this->tail]);

        sink(1);
    }
}

void heapsort(std::vector<int>& v) {
    Heap heap{v.size()};
    for (int i : v) {
        heap.insert(i);
    }
    v.clear();

    while (heap.size() != 0) {
        v.push_back(heap.getMax());
        heap.deleteKey();
    }
}

#endif //OFFLINE5_HEAP_H
