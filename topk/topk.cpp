//Author: John Xu. 6/23/2019
//Initial code drafted on 6/21/2019 on a flight back from Plantation, FL
//
//The initial problem was an Amazon phone screen problem: print out the top K number from a given array of integers
//
//Initally the answer should be simple: take each integer from the array and insert into a priority queue and then
//do a loop to pop from this prioroty queue to print out each of the integer
//
//Then later on, it is asked, what if the array is so big, such as comming from a stream, and does not fit into the memory ?
//My immediate response was: once we reached size K for the priority queue, we remove the last element before insert the
//new element into the priority queue, if the new element is larger than the last element of the priority queue.
//
// Above immediate response has following defects:  
// 
// 1) priority queue does not have a method to access or remove the last element
//    regular queue has push, pop, front, back, size, empty. 
//    dequeue has push_back, push_front, pop_back, pop_front, size, empty
//    priority_queue has push, pop, top, size, empty
//
// 2) over use of priority queue may be too slow. Priority queue better used for cases where the data is really used as
//    a queue structure, where processed elements are gone from the storage, where no need to keep the historical top K
//    element. 
//
// 3) If we want to keep the historical top K element from a unlimited stream inout, it is more efficient to maintain a 
//    dynamic array of size K. Maintain the array sorted from large to small. When new element comes in, if it is smaller
//    than the last one, ignore it. Otherwise, remove the last one, and shift every element one position to next one if that
//    element is smaller than the new one, then insert the new one at the end of the shift. 
//

//example of keep top 3 element from a unlimited stream of integers: top3
// generic cases: topk
//

#include <fstream>
#include <iostream>
#include <filesystem>

#define MIN_INT -65535

void top3(char* filename)
{
    using namespace std;
    namespace fs = std::filesystem;
    fs::path fp {filename};
    if (!fs::exists(fp)) {
        cout << "file " << filename << " not exist" << endl;
        return;
    }

    ifstream fstrm(filename);

    int top1 = MIN_INT, top2=MIN_INT, top3=MIN_INT;
    int number;
    while (! fstrm.eof()) {
        fstrm >> number;
        if (number > top1) {
            top2 = top1;    
            top1 = number;
        }
        else if (number > top2){
            top3 = top2;    
            top2 = number;
        }
        else if (number > top3)
            top3 = number;

    }
    cout << top1 << endl << top2 << endl << top3 << endl;
}

void topk(char* filename, int K)
{
    using namespace std;
    namespace fs = std::filesystem;
    fs::path fp {filename};
    if (!fs::exists(fp)) {
        cout << "file " << filename << " not exist" << endl;
        return;
    }

    ifstream fstrm(filename);

//    int top1 = MIN_INT, top2=MIN_INT, top3=MIN_INT;
    int number;
    int arr[K];

    for (int i=0; i<K; i++)
      arr[i] = MIN_INT;

    while (! fstrm.eof()) {

        fstrm >> number;
        int i = K-1;

        if (number < arr[K-1])
            break;

        for (i=K-1; i>0; i--) {
            if (number <= arr[i])           // arr[i] >= number > arr[i+1]
                break;
            cout << " number = " << number << " i = " << i << endl;     //debug
        }

        int j = K-1;
        for (j=K-1; j>i; j--) {
            arr[j] = arr[j-1];
        }

        arr[j] = number;
    }

    fstrm.close();

    for (int i=0; i<K; i++)
     cout << arr[i] << endl;

}

int main(int argc, char* argv[])
{
    int K = atoi(argv[2]);
    topk(argv[1], K);
    return 0;
}


//above version still have some bugs. a input of 1, 2, 3, 4, 5, 6 with command top example.txt 9
// will output 6, 6, 5, 4, 3, 2, 1, -65535, -65535.  When we expect 6, 5, 4, 3, 2, 1, -65535, -65535
// a input of 5,4,3,2,1,0 with top example2.txt 9 will output 4,3,2,1,0,0,5, -65535, -65535


// A modified version will need to be worked on