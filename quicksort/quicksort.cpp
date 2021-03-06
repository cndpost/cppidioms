#include <iostream>

int partition(int arrayLeft[], int low,  int high);

void quicksort(int arrayLeft[], int left, int right)
{
	if ( left < right ) {
                int index = partition(arrayLeft, left, right);
		quicksort(arrayLeft, left, index-1);
        	quicksort(arrayLeft, index,  right);
	}
}

void swap(int array[], int left, int right)
{
	int tmp = array[left];
	array[left] = array[right];
	array[right] = tmp;
}

int partition(int array[], int low, int high)
{
  	int iLeft=low;
        int iRight = high;
	int pivot = array[(low+high)/2];

	while( iLeft <= iRight) { 
	  	while (array[iLeft] < pivot) 
			iLeft++;	
		while (array[iRight] > pivot)
			iRight--;
		if ( iLeft <= iRight) {
			swap(array, iLeft, iRight);
			iLeft++;
			iRight--;
		} 
        }
	return iLeft;
}

void quicksort(int dataArray[], int N)
{
	int helper[N];
        quicksort(dataArray, 0, N-1);
}

int main()
{
	int dataArray[] = {3,4,7,2,1,5,8,6};
        int N = 8;
        printf("before sort\n");
	for (int i=0; i < N; i++){
                printf("%d ", dataArray[i]);

        }
        printf("\n");

	quicksort(dataArray, N);
        printf("after sort\n");
	for (int i=0; i < N; i++){
		printf("%d ", dataArray[i]);

	}
        printf("\n");
	return 0;
}
