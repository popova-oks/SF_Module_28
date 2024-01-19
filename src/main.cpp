#include "../headers/merge_sort.h"
#include <iostream>

bool make_thread = true;

int main(int argc, char* argv[]) {
    srand(0);
    long arr_size = 100000000;
    int* array = new int[arr_size];
    for(long i = 0; i < arr_size; i++) {
        array[i] = rand() % 500000;
    }
    time_t start, end;
    // многопоточный запуск
    time(&start);
    MergeSort::merge_sort(array, 0, arr_size-1);
    time(&end);

    double seconds = difftime(end, start);
    printf("The time: %f seconds\n", seconds);

    for(long i = 0; i < arr_size - 1; i++) { 
        if(array[i] > array[i + 1]) {
            std::cout << "Unsorted" << std::endl;
            break;
        }
    }

    for(long i = 0; i < arr_size; i++) {
        array[i] = rand() % 500000;
    }
    // однопоточный запуск
    make_thread = false;
    time(&start);
    MergeSort::merge_sort(array, 0, arr_size-1);
    time(&end);
    seconds = difftime(end, start);
    printf("The time: %f seconds\n", seconds);
    delete[] array;
    return 0;
}