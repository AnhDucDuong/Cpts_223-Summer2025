#ifndef SORT_ALGORITHMS_H
#define SORT_ALGORITHMS_H

#include <vector>

template <typename T, typename Comparator>
void insertionSort(std::vector<T>& arr, Comparator comp) {
    for (size_t i = 1; i < arr.size(); ++i) {
        T key = arr[i];
        int j = i - 1;
        while (j >= 0 && comp(key, arr[j])) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

template <typename T, typename Comparator>
void merge(std::vector<T>& arr, int left, int mid, int right, Comparator comp) {
    int n1 = mid - left + 1, n2 = right - mid;
    std::vector<T> L(n1), R(n2);
    for (int i = 0; i < n1; ++i) L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) arr[k++] = comp(L[i], R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

template <typename T, typename Comparator>
void mergeSortHelper(std::vector<T>& arr, int left, int right, Comparator comp) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortHelper(arr, left, mid, comp);
        mergeSortHelper(arr, mid + 1, right, comp);
        merge(arr, left, mid, right, comp);
    }
}

template <typename T, typename Comparator>
void mergeSort(std::vector<T>& arr, Comparator comp) {
    mergeSortHelper(arr, 0, arr.size() - 1, comp);
}

#endif
