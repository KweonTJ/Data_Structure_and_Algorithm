#include <iostream>
using namespace std;

#define LENGTH 6


void InsertionSort(int* A)
{
       for(int j=1; j<LENGTH; j++)
       {
         int key = A[j];
         //Inser tA[j] into the sorted sequence A[0..j-1]
         int i = j-1;
         while((i >= 0) && (A[i] > key))
         {
             A[i+1] = A[i];
             i--;
         }
         A[i+1]=key;
       }
}

void Input(int* A)
{
	cout << "Input " << LENGTH << " numbers : ");
	for(int i=0; i<LENGTH; i++)
		cin >> A[i];
}

void Output(int* A)
{
	cout << "Result : ";
	for(int i=0; i<LENGTH; i++)
		cout << A[i] << " ";
	cout << "\n";
}

int main()
{
	int A[LENGTH]={0};
	Input(A);
	InsertionSort(A);
	Output(A);
	return 0;
}