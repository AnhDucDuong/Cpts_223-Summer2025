#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <numeric>
#include <cmath>
using namespace std;

// Insertion Sort (Given)
void insertionSort(vector<int> &arr)
{
    for (size_t i = 1; i < arr.size(); ++i)
    {
        int key = arr[i];
        size_t j = i;
        while (j > 0 && arr[j - 1] > key)
        {
            arr[j] = arr[j - 1];
            --j;
        }
        arr[j] = key;
    }
}

// Quicksort 
int partition(vector<int> &arr, int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j)
    {
        if (arr[j] < pivot)
        {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSortHelper(vector<int> &arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSortHelper(arr, low, pi - 1);
        quickSortHelper(arr, pi + 1, high);
    }
}

void quickSort(vector<int> &arr)
{
    quickSortHelper(arr, 0, arr.size() - 1);
}

// Shell Sort 
void shellSort(vector<int> &arr)
{

    vector<int> gaps;
    for (int k = 1; (1 << k) - 1 < arr.size(); ++k)
        gaps.push_back((1 << k) - 1);

    for (auto it = gaps.rbegin(); it != gaps.rend(); ++it)
    {
        int gap = *it;
        for (size_t i = gap; i < arr.size(); ++i)
        {
            int temp = arr[i];
            size_t j = i;
            while (j >= gap && arr[j - gap] > temp)
            {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}

//  Heap Sort 
void heapify(vector<int> &arr, int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; --i)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; --i)
    {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// Statistics 
void printStatistics(const vector<double> &durations)
{
    double minTime = *min_element(durations.begin(), durations.end());
    double maxTime = *max_element(durations.begin(), durations.end());
    double avgTime = accumulate(durations.begin(), durations.end(), 0.0) / durations.size();
    double variance = 0.0;
    for (double t : durations)
    {
        variance += (t - avgTime) * (t - avgTime);
    }
    double stdDev = sqrt(variance / durations.size());
    cout << "\n=== Statistics ===\n";
    cout << "Min Time: " << minTime << " ms\n";
    cout << "Max Time: " << maxTime << " ms\n";
    cout << "Average Time: " << avgTime << " ms\n";
    cout << "Standard Deviation: " << stdDev << " ms\n";
}

//  Benchmarking 
void benchmarkSort(void (*sortFunc)(vector<int> &), const string &name)
{
    const int N = 10000;
    const int MAX_VAL = 100000;
    const int TRIALS = 10;
    vector<double> durations;

    cout << "\n--- " << name << " ---\n";
    for (int trial = 0; trial < TRIALS; ++trial)
    {
        vector<int> data(N);
        for (int i = 0; i < N; ++i)
            data[i] = rand() % (MAX_VAL + 1);

        auto start = chrono::high_resolution_clock::now();
        sortFunc(data);
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double, milli> elapsed = end - start;
        durations.push_back(elapsed.count());
        cout << "Trial " << trial + 1 << " duration: " << elapsed.count() << " ms\n";
    }
    printStatistics(durations);
}

int main()
{
    srand(static_cast<unsigned>(time(nullptr)));

    benchmarkSort(insertionSort, "Insertion Sort");
    benchmarkSort(quickSort, "Quick Sort");
    benchmarkSort(shellSort, "Shell Sort (Hibbard's Sequence)");
    benchmarkSort(heapSort, "Heap Sort");

    return 0;
}
