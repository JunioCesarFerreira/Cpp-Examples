#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

//---------------------------------------------------------------------------------------------
// Test class
//---------------------------------------------------------------------------------------------
class TestArray
{
	public:
		const static int length = 20;
		int array[length];
		
		void initArray() 
		{
			int initValues[length] = 
			{
				17,  7, 15,  9, 19,
			 	 3, 20, 10,  4,  2,
				13, 14, 18,  6,  1,
				12,  0,  8, 11,  5
			};
			for (int i=0; i<length; i++) array[i]=initValues[i];
		}
		
		void printArray() 
		{
			printf("Array=(%d", array[0]);
			for(int i=1; i<length; i++) printf(", %d", array[i]);
			printf(")\r\n");
		}
		
		static void printArray(const char* text, int *ptr, int length) 
		{
			printf("%s=(%d", text, *ptr);
			for(int i=1; i<length; i++) printf(", %d", *(ptr+i));
			printf(")\r\n");
		}	
};

/// swap elements
void swap(int *pt1, int *pt2) 
{
	int tmp = *pt1;
	*pt1=*pt2;
	*pt2=tmp;
}

//---------------------------------------------------------------------------------------------
// Sort Algorithms complexity O(N²)
//---------------------------------------------------------------------------------------------
/// Bubble Sort
void BubbleSort(int *ptr, int length) 
{
	for (int i=0; i<length; i++) 
	{
		for (int j=i; j<length; j++) 
		{
			if (ptr[j] < ptr[i])
			{
				swap(ptr+i, ptr+j);
				TestArray::printArray("Array", ptr, length);
			} 
		}
	}
}
/// Insertion Sort
void InsertionSort(int *ptr, int length) 
{
	for (int i=1; i<length; i++) 
	{
		int tmp = ptr[i];
		int j=i-1;
		while (tmp < ptr[j] && j >= 0) 
		{
			ptr[j+1] = ptr[j];
			j--;
		}
		ptr[j+1] = tmp;
		TestArray::printArray("Array", ptr, length);
	}
}
/// Selection Sort
void SelectionSort(int *ptr, int length) 
{
	for (int i=0; i<length; i++) 
	{
		int min = i;
		for (int j=i; j<length; j++) 
		{
			if (ptr[j] < ptr[min]) min = j;
		}
		swap(ptr+min, ptr+i);
		TestArray::printArray("Array", ptr, length);
	}
}

//---------------------------------------------------------------------------------------------
// Sort Algorithms Complexity O(N Log(N))
//---------------------------------------------------------------------------------------------
void quickRecursively(int *ptr, int left, int right); 
void QuickSort(int *ptr, int length) 
{
 	quickRecursively(ptr, 0, length-1);
}
void quickRecursively(int *ptr, int low, int high)
{
	if (low < high) 
	{ 
		printf("pivot=%d\r\n", ptr[high]);
		int i = low - 1;   
		for (int j = low; j <= high- 1; j++) 
		{ 
			if (ptr[j] <= ptr[high]) 
			{ 
				i++;    
				swap(&ptr[i], &ptr[j]); 
			} 
		} 
		i++;
		swap(&ptr[i], &ptr[high]); 
		
		TestArray::printArray("Array", ptr, TestArray::length);
		
		quickRecursively(ptr, low, i - 1); 
		quickRecursively(ptr, i + 1, high); 
	} 
}
 
//---------------------------------------------------------------------------------------------
void mergeRecursively(int *ptr, int start, int end);
void MergeSort(int *ptr, int length) 
{
	mergeRecursively(ptr, 0, length-1);
}
void mergeRecursively(int *ptr, int start, int end) 
{	
	if (start == end) return;	
	
	int half = (start + end)/ 2;
	
	mergeRecursively(ptr, start, half);
	mergeRecursively(ptr, half + 1, end);

	int length = end - start + 1;
	int *ptrTmp = (int *) malloc(sizeof(int) * length);
	
	int i = start;
	int j = half + 1;
	int k = 0;
	while(i <= half || j  <= end) 
	{
		if (i > half) 
		{ 
			ptrTmp[k] = ptr[j];
			j++;
		}
		else if (j > end) 
		{
			ptrTmp[k] = ptr[i];
			i++;
		}
		else if (ptr[i] <= ptr[j]) 
		{
			ptrTmp[k] = ptr[i];
			i++;
		}
		else 
		{
			ptrTmp[k] = ptr[j];
			j++;
		}
		k++;
	}
	TestArray::printArray("Temp", ptrTmp, length);
	
	for(int i = 0; i < length; i++) 
	{
		ptr[i+start]=ptrTmp[i];
	}
	free(ptrTmp);
	TestArray::printArray("Array", ptr, TestArray::length);
}

//---------------------------------------------------------------------------------------------
void heapify(int *ptr, int n, int i) 
{
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	
	if (left < n && ptr[left] > ptr[largest]) largest = left;
	
	if (right < n && ptr[right] > ptr[largest]) largest = right;
	
	if (largest != i) 
	{
		swap(&ptr[i], &ptr[largest]);
		TestArray::printArray("Array", ptr, TestArray::length);
		heapify(ptr, n, largest);
	}
}

void HeapSort(int *ptr, int n) 
{
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		heapify(ptr, n, i);
	}
	
	for (int i = n - 1; i >= 0; i--) 
	{
		swap(&ptr[0], &ptr[i]);
		heapify(ptr, i, 0);
	}
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
// Programa de teste
//---------------------------------------------------------------------------------------------
int main()
{
	TestArray test;
	
	printf("\nBubble Sort\r\nInput ");
	test.initArray();
	test.printArray();	
	BubbleSort(test.array, test.length);
	
	printf("\nSelection Sort\r\nInput");
	test.initArray();
	test.printArray();	
	SelectionSort(test.array, test.length);
	
	printf("\nInsertion Sort\r\nInput");
	test.initArray();
	test.printArray();	
	InsertionSort(test.array, test.length);
	
	printf("\nQuick Sort\r\nInput");
	test.initArray();
	test.printArray();	
	QuickSort(test.array, test.length);
	
	printf("\nMerge Sort\r\nInput");
	test.initArray();
	test.printArray();	
	MergeSort(test.array, test.length);
		
	printf("\nHeap Sort\r\nInput");
	test.initArray();
	test.printArray();	
	HeapSort(test.array, test.length);
	test.printArray();
	
	getch();
}
