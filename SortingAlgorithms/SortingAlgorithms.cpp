#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

//---------------------------------------------------------------------------------------------
// Funções auxiliares
//---------------------------------------------------------------------------------------------
/// Print Array
void printArray(int *ptr, int length) 
{
	printf("Array=(%d", *ptr);
	for(int i=1; i<length; i++) printf(", %d", *(ptr+i));
	printf(")\r\n");
}
/// Initialize Array 
void initArray(int *ptr) 
{
	int array[16] = {7,15,9,3,10,4,2,13,14,6,1,12,0,8,11,5};
	for (int i=0; i<16; i++) *(ptr+i)=array[i];
}
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
				printArray(ptr, length);
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
		printArray(ptr, length);
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
		printArray(ptr, length);
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
    	
		printArray(ptr, 16);
    	
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
        }else if (j > end) 
		{
            ptrTmp[k] = ptr[i];
            i++;
        }else if (ptr[i] <= ptr[j]) 
		{
            ptrTmp[k] = ptr[i];
            i++;
        }else 
		{
            ptrTmp[k] = ptr[j];
            j++;
        }
        k++;
    }
	printArray(ptrTmp, length);
    
    for(int i = 0; i < length; i++) 
	{
        ptr[i+start]=ptrTmp[i];
    }
    free(ptrTmp);
	printArray(ptr, 16);
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
      printArray(ptr, 16);
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

// Programa de teste
int main()
{
	int array[16] = {7,15,9,3,10,4,2,13,14,6,1,12,0,8,11,5};
	
	printf("\nBubble Sort\r\nInput");
	initArray(&array[0]);
	printArray(&array[0], 16);	
	BubbleSort(&array[0], 16);
	
	printf("\nSelection Sort\r\nInput");
	initArray(&array[0]);
	printArray(&array[0], 16);	
	SelectionSort(&array[0], 16);
	
	printf("\nInsertion Sort\r\nInput");
	initArray(&array[0]);
	printArray(&array[0], 16);	
	InsertionSort(&array[0], 16);
	
	printf("\nQuick Sort\r\nInput");
	initArray(&array[0]);
	printArray(&array[0], 16);	
	QuickSort(array, 16);
		
	printf("\nMerge Sort\r\nInput");
	initArray(&array[0]);
	printArray(&array[0], 16);	
	MergeSort(array, 16);
	
	
	printf("\nHeap Sort\r\nInput");
	initArray(&array[0]);
	printArray(&array[0], 16);	
	HeapSort(array, 16);
	
	getch();
}
