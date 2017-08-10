#include <iostream>

void merge(int arrayLeft[], int helper[], int low, int middle, int high);

void mergesort(int arrayLeft[], int helper[], int left, int right)
{
	if ( left < right ) {
		int middle = (left+right)/2;
		mergesort(arrayLeft, helper, left, middle);
        	mergesort(arrayLeft, helper, middle+1, right);
        	merge(arrayLeft, helper, left, middle, right);
	}
}

void merge(int arrayLeft[], int helper[],  int low, int middle, int high)
{
  	int iLeft=low;
  	int iRight = middle+1;
	int current = low;
        for(int i= low; i <= high; i++) {
		helper[i] = arrayLeft[i];
	}

	while( (iLeft <= middle) && (iRight <= high)) { 
	  	if (helper[iLeft] <= helper[iRight]) {
			arrayLeft[current] = helper[iLeft];
    			iLeft++;
		}
  		else {
	       		arrayLeft[current] = helper[iRight];        
			iRight++;
        	
 		}
		current++;
	}

	//hit following case must be iRight > high but still have iLeft <= middle, i.e. right side used but left side not yet
	if ( iLeft <= middle) {
	        for (int i=iLeft; i <= middle; i++) {
			arrayLeft[current] = helper[i];
			current++;
		}
	}

        //is it still need to consider a scenario where iLfet > middle but iRight <= high ? i.e. left side used but right side not yet
        //such as following code ?   It is safe logically to do so, but not necessary because helper was originally from arrayLeft
 	if ( iRight <= high) {
                for (int i=iRight; i <= high; i++) {
                        arrayLeft[current] = helper[i];
                        current++;
                }
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
        printf("before sort\n");
	for (int i=0; i < N; i++){
                printf("%d ", dataArray[i]);

        }
        printf("\n");

	mergesort(dataArray, N);
        printf("after sort\n");
	for (int i=0; i < N; i++){
		printf("%d ", dataArray[i]);

	}
        printf("\n");
	return 0;
}
