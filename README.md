# cppidioms
c++ code idioms for professional use and tutorial purpose

The purpose of this collection of C++ idioms is to make it easier to remember and conveneintly pull out
the implementation and usage of a C++ idiom whenever we need to use it. The
collections can grow indifinitely but the choice would be focused on those idioms that will be frequently used in production code and also for c++ interview preparations

The folder structure are as follows:

  singleton - singleton.cpp. This single file have the singleton class and its
              calling main fucntions all in one file. It is modified from code smaple from a book
              titled "Sams teach yourself C++ in one hour a day" by Siddhartha Rao, 7th Edition, 
              following command will make the program compile and run: 
 
               to compile and link:          g++ singleton.cpp -o singleton.cpp
               to run:                        ./singleton


               comments: if you use gcc instead of g++ it may complain missing references to std library functions
