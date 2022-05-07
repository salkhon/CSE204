//
// Created by Salman Khondker on 03-Apr-21.
//
#include <iostream>
#include <vector>
#include "heap.h"

int main() {
    const int TEST_SIZE = 1000;
    Heap heap{TEST_SIZE};
    std::vector<int> vec;

    for (int i = 0; i < TEST_SIZE; i++) {
        int rand = std::rand();
        std::cout << "Inserting " << rand << std::endl;
        vec.push_back(rand);
        heap.insert(rand);
    }

    std::cout << "Inorder: " << std::endl;

    bool is_working = true;
    int prev = heap.getMax();
    while (heap.size() != 0) {
        if (prev < heap.getMax()) {
            is_working = false;
        }

        std::cout << heap.getMax() << " ";
        heap.deleteKey();
    }
    std::cout << std::endl;

    std::cout << "working: " << is_working << std::endl;

    heapsort(vec);

    std::cout << "Sorted:" << std::endl;
    for (int i : vec) {
        std::cout << i << " ";
    }
}
