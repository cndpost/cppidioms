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
 
               to compile and link:          g++ singleton.cpp -o singleton
               to run:                        ./singleton


               comments: if you use gcc instead of g++ it may complain missing references to std library functions

 singleton2 - singleton2.cpp. This single file have the singleton class that offers a thread feature to reserve a
              seat index in an array if that seat is not taken. The std::mutex and std:lock_guard requires
              compiler option --std=gnu++11 to work

              to compile and link:            g++ singleton2.cpp -o singleton2 -std=gnu++11

 goroutine  - goroutine.cpp is a singleton class that offers similar functions of goroutine in go language. 
              supporting the multithread launching of parallel function execution is the first step to port
              any go language based programs into C++ programs without major difficulty

 channel    - channel.cpp is a singleton class that offers similar functions of channels in go language 
              that coordinates different goroutine in differnt threads. 



