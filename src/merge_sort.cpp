#include "../headers/merge_sort.h"
#include <condition_variable>
#include <future>

// void MergeSort::merge_sort(int array[], size_t size)
void MergeSort::merge_sort(int array[], int l, int r) {
    if(l >= r) {
        return;
    }
    int m = (l + r) / 2;

    if(make_thread == true && (m - l > 10000)) {
        std::future<void> left_future =
            std::async(std::launch::async, [&] { merge_sort(array, l, m); });
        
        merge_sort(array, m + 1, r);
        try {
            left_future.get();
        } catch (const std::exception &ex) {
            std::cerr << "Error: " << ex.what() << std::endl;
        }
        merge(array, l, m, r);
    } else {
        merge_sort(array, l, m);
        merge_sort(array, m + 1, r);

        merge(array, l, m, r);
    }
}

void MergeSort::merge(int array[], int l, int m, int r) {
    int nl = m - l + 1;
    int nr = r - m;

    // создаем временные массивы
    int* left = new int[nl];
    int* right = new int[nr];

    // копируем данные во временные массивы
    for(int i = 0; i < nl; i++)
        left[i] = array[l + i];
    for(int j = 0; j < nr; j++)
        right[j] = array[m + 1 + j];

    int i = 0, j = 0;
    int k = l; // начало левой части

    while(i < nl && j < nr) {
        // записываем минимальные элементы обратно во входной массив
        if(left[i] <= right[j]) {
            array[k] = left[i];
            i++;
        } else {
            array[k] = right[j];
            j++;
        }
        k++;
    }
    // записываем оставшиеся элементы левой части
    while(i < nl) {
        array[k] = left[i];
        i++;
        k++;
    }
    // записываем оставшиеся элементы правой части
    while(j < nr) {
        array[k] = right[j];
        j++;
        k++;
    }
    delete[] left;
    delete[] right;
}