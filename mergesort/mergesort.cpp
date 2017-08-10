#include <iostream>

void merge(int arrayLeft[], int helper[], int low, int middle, int high);

void mergesort(int arrayLeft[], int helper[], int left, int right)
{
	if ( left < right ) {
		int middle = (left+right)/2;
		mergesort(arrayLeft, helper, left, middle);
        	mergesort(helper, helper, middle+1, right);
        	merge(arrayLeft, helper, left, middle, right);
	}
}

void merge(int arrayLeft[], int helper[],  int low, int middle, int high)
{
  	int iLeft=low;
  	int iRight = middle+1;
        int N = high - low+1;

        for(int i= low; i < high; i++) {
		helper[i] = arrayLeft[i];
	}

        for(int i=0; i< N; i++ ){

	  	if (arrayLeft[iLeft] < helper[iRight])
    			iLeft++;
  		else {
        		arrayLeft[iLeft] = helper[iRight];        
			iRight++;
        		iLeft++;
 		}

	}

        for (int i=iRight; i < high; i++) {
		arrayLeft[iLeft] = helper[i];
		iLeft++;

	}
}

void mergesort(int dataArray[], int N)
{
	int helper[N];
        mergesort(dataArray, helper, 0, N-1);
}

int main()
{
	int dataArray[] = {3,4,7,2,1,5,8,6};
        int N = 8;
	mergesort(dataArray, N);
	for (int i=0; i < N; i++){
		printf("%d ", dataArray[i]);

	}
        printf("\n");
	return 0;
}
