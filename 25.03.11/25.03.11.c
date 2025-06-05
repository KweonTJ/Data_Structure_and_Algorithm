#include <stdio.h>
#define LENGTH 6

//void InsertionSort(int* A)
//{
//	for (int j = 1; j < LENGTH; j++)
//	{
//		int key = A[j];
//		int i = j - 1;
//		while ((i >= 0) && (A[i] > key))
//		{
//			A[i + 1] = A[i];
//			i--;
//		}
//		A[i + 1] = key;
//	}
//}

void InsertionSort(int* A)
{
    for (int j = 1; j < LENGTH; j++)
    {
        int key = A[j];
        int i = j - 1;
        while ((i >= 0) && (A[i] < key)) // 내림차순 정렬
        {
            A[i + 1] = A[i];
            i--;
        }
        A[i + 1] = key;

        for (int k = 0; k < LENGTH; k++)
        {
            printf("%d ", A[k]);
        }
        printf("\n");
    }
}

int main()
{
    int A[LENGTH] = { 5, 2, 4, 6, 1, 3 };

    printf("Original array: ");
    for (int i = 0; i < LENGTH; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n\n");

    InsertionSort(A);

    printf("\nSorted array (Descending): ");
    for (int i = 0; i < LENGTH; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");

    return 0;
}
