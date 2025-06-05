#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <vector>

void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - 1 - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            std::swap(arr[++i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

void mergeSort(std::vector<int>& arr, int l, int r) {
    if (l >= r) return;
    int m = (l + r) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);

    std::vector<int> tmp(r - l + 1);
    int i = l, j = m + 1, k = 0;

    for (; i <= m && j <= r; ++k) tmp[k] = (arr[i] < arr[j]) ? arr[i++] : arr[j++];
    for (; i <= m; ++i, ++k) tmp[k] = arr[i];
    for (; j <= r; ++j, ++k) tmp[k] = arr[j];

    for (k = 0; k < tmp.size(); ++k) arr[l + k] = tmp[k];
}

void maxHeapify(std::vector<int>& arr, int i, int heapSize)
{
    int largest = i;
    int left = 2 * i;
    int right = 2 * i + 1;

    if (left < heapSize && arr[left] > arr[largest])
        largest = left;
    if (right < heapSize && arr[right] > arr[largest])
        largest = right;
    if (largest != i)
    {
        std::swap(arr[i], arr[largest]);
        maxHeapify(arr, largest, heapSize);
    }
}

void buildMaxHeap(std::vector<int>& arr)
{
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; --i)
    {
        maxHeapify(arr, i, n);
    }
}

void heapSort(std::vector<int>& arr)
{
    int heapSize = arr.size();

    buildMaxHeap(arr);

    for (int i = heapSize - 1; i > 0; --i)
    {
        std::swap(arr[0], arr[i]);
        heapSize--;
        maxHeapify(arr, 0, heapSize);
    }
}

void printArray(const std::vector<int>& arr)
{
    for (int num : arr)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main()
{
    std::srand(std::time(0));

    std::vector<int> arr(100);
    for (int i = 0; i < 100; ++i)
    {
        arr[i] = std::rand() % 100 + 1;
    }

    std::cout << "정렬 전 배열: ";
    printArray(arr);

    int choice;
    std::cout << "1. Insertion Sort\n";
    std::cout << "2. Bubble Sort\n";
    std::cout << "3. Merge Sort\n";
    std::cout << "4. Quick Sort\n";
    std::cout << "5. Heap Sort\n";
    std::cout << "선택: ";
    std::cin >> choice;

    auto start = std::chrono::high_resolution_clock::now();

    if (choice == 1)
    {
        insertionSort(arr);
        std::cout << "Inertion Sort 후 배열: ";
    }
    else if (choice == 2)
    {
        bubbleSort(arr);
        std::cout << "Bubble Sort 후 배열: ";
    }
    else if (choice == 3)
    {
        mergeSort(arr, 0, arr.size() - 1);
        std::cout << "Merge Sort 후 배열: ";
    }
    else if (choice == 4)
    {
        quickSort(arr, 0, arr.size() - 1);
        std::cout << "Quick Sort 후 배열: ";
    }
    else if (choice == 5)
    {
        heapSort(arr);
        std::cout << "Heap Sort 후 배열: ";
    }
    else
    {
        std::cout << "잘못된 선택입니다.\n";
        return 1;
    }

    printArray(arr);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "소요된 시간: " << duration.count() << "초\n";

    return 0;
}