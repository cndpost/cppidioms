# cppidioms
c++ code idioms for professional use and tutorial purpose

The purpose of this collection of C++ idioms is to make it easier to remember and conveneintly pull out
the implementation and usage of a C++ idiom whenever we need to use it. The
collections can grow indifinitely but the choice would be focused on those idioms that will be frequently used in production code and also for c++ interview preparations

The folder structure are as follows:

  singleton - singleton.cpp. This single file has the singleton class and its
              calling main fucntions all in one file. It is modified from code smaple from a book
              titled "Sams teach yourself C++ in one hour a day" by Siddhartha Rao, 7th Edition, 
              following command will make the program compile and run: 
 
               to compile and link:          g++ singleton.cpp -o singleton
               to run:                        ./singleton


               comments: if you use gcc instead of g++ it may complain missing references to std library functions

 singleton2 - singleton2.cpp. This single file has the singleton class that offers a thread feature to reserve a
              seat index in an array if that seat is not taken. The std::mutex and std:lock_guard requires
              compiler option --std=gnu++11 to work

              to compile and link:            g++ singleton2.cpp -o singleton2 -std=gnu++11

 goroutine  - goroutine.cpp is a singleton class that offers similar functions of goroutine in go language. 
              supporting the multithread launching of parallel function execution is the first step to port
              any go language based programs into C++ programs without major difficulty

 channel    - channel.cpp is a singleton class that offers similar functions of channels in go language 
              that coordinates different goroutine in differnt threads. 


              to compile and link:   g++ channel.cpp -o channel

 linkedlist  - linkedlist.cpp.  This single file has the C++ implementation of a linkedlist from scratch without
              using the STL library for built-in linked list. The code was a rewrite based on the Java code of
              a book titled "Cracking the Coding Interview" by Gayle L McDowell. 5th edition. I also added a simple
              main function to do a basic test of it.

              to compile and link:   g++ linkedlist.cpp -o linkedlist


 producerconsumer - producerconsumer.cpp. This single file has the C++ implementation of a producer consumer use case
              where the producer generates input to a queue and the consumer consumer and extract the output from the
              queue. The key is to demonstrate the pattern of using lock and mutex to coordinate two threads that share
              the access to a queue data structure. This code is adopted from https://gist.github.com/iikuy/8115191.
              We added the missing includes and following instruction shows that we also need to add pthread library
              for the program to pass compile and link

              to compile and link:  g++ producerconsumer.cpp -lpthread -o producerconsumer -std=gnu++11


stack -       stack.cpp.  This single file has the C++ implementation of the stack from scratch. The code is modified
              from the Java code of "Cracking the coding interview" like the linkedlist implementation above.
              pay attention to the commented cout line which may not output the stack elements as expected because
              cout may not execute consecutive arguments from left to right but run from right to left.


              to compile and link:           g++ stack.cpp -o stack -std=gnu++11

queue -       queue.cpp. This single file has the C++ implementation of the queue from scrtach.  The code is modified
              from the Java code of "Cracking the coding interview" like the linkedlist implementation above.
              1) pay attention to the commented code in Node* top, bottom which declares bottom not as Node*; 
              2) pay attention to the commented out cout lines. It may not output as expected since cout will output
              the arguments from right to left, causing the dequeue calls are executed from right to left order.
              3) pay attention to the difference between stack and queue. Queue need two pointers where stack just need one.

              to compile and link:   g++ queue.cpp -o queue -std=gnu++11


DFT -         dft.cpp. This single file has the C++ implementation of a depth first traversal algorithm of a tree. It uses an unsorted vector
              to store the children of each node. Each node stores a character as node data;


              to compile and link:   g++ dft.cpp -o dft -std=gnu++11



BFT -         bft.cpp. This single file has the C++ implementation of a breadth first travelsal algorithm of a tree. It uses an unsorted vector
              to store the children of each node.


              to compile and link:   g++ bft.cpp -o bft -std=gnu++11



BFT2  -       bft.cpp. This single file has the C++ implementation of a breadth first travelsal algorith of a tree. I uses an undsorted vector
              to store the children of each node. The difference with above BFT is the BFT2 uses std::deque instead of std::queue. So the methods
              are push_back(), top() and pop_front() instead of push(), top() and pop();


              to compile and link:   g++ bft.cpp -o bft -std=gnu++11



deque -       deque.cpp.  This single file has the C++ implementation of a dequeue from scratch. It is modified from above queue program which is a single 
              header queue.


              to compile and link:   g++ deque.cpp -o deque -std=gnu++11

priorityqueu - priorityque.cpp.  This single file has the C++ implementation of a priority queue whose elements are integers.

        
              to compile and link:   g++ priorityqueue.cpp -o priorityqueue -std=gnu++11

fibonacci    -  fibonacci.cpp.   This single file has the C++ implementation of a recursive fibonacci algorithm and a cached array is used to save
		repeatitive calculations.  An alternative question related to fibonacci would look like: if you can walk one or two steps at a time
                when you walk upstairs, how many possible ways you can walk up to a floor with N steps ? 

		to compile and link:   g++ fibonacci.cpp -o fibonacci -std=gnu++11

mergesort     - mergesort.cpp.  This single file has the C++ implementation of a mergesort algorithm. Code adopted from a book titled "Cracking the code
               Interview" by Gayle Laakmann McDowell, 5th edition.

quicksort     - quicksort.cpp.  This single file has the C++ implementation of a quicksort algorithm. Code adopted from a book titled "Cracking the code
               Interview" by Gayle Laakmann McDowell, 5th edition.

binarysearch     - binarysearch.cpp.  This single file has the C++ implementation of a binary algorithm. Code adopted from a book titled "Cracking the code
               Interview" by Gayle Laakmann McDowell, 5th edition.



frameproducerconsumer - fprodconsumer.cpp.  This single file has the C++ implementation of a more sophisticated producer 
		consumer scenario: the producer will continuously capturing the images from a scanner and pass it
        	in as a frame data buffer, there will be no shared queues as in the previous simple producerconsumer 
                case, instead here the frames are immediatly copied into three consumer queues: one is a GUI display, one 
                is a file saving directory, and one is an image processing routine. Queues are implemented as thread safe
                queues.

               	the original requirement is in a readme.txt file in the project folder. In our test we do not have a 
               	physical scanner connected so we will simulate the scanner driver using a file reader to fetch the images
               	from the folder 'images'. We will then save it to another folder called 'savedImages', display it on Windows
               	as the images updated, and pass the image data to a dummy processing routine called imageprocessor() which
               	will compress the image into 1/2 x 1/2 size of the original size and displays the image in another window.  
 
               	to compile and link:   g++ fprodconsumer.cpp -o prodconsumer -std=gnu++11

               	to run the program in place:   ./fprodconsumer images savedImages 

               	the program will continuously read the images cyclically from folder 'images' and to stop the process
               	just press Ctl_C key

               	as a cppidioms project, we try not to use anything depend on libraries other than standard libraries, so
               	the first phase of this project will not have GUI and Image processing functions. In the 2nd phase we will
               	use OpenCV and Qt libraries to make it a really demoable program



