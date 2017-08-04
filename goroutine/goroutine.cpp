#include <iostream>
#include <string>
#include <mutex>
#include <vector>
#include <thread>
using namespace std;

class GoRoutine
{
 private:
  //private default constructor (prohibits creation from outside)
  GoRoutine( ){};
  
  // private copy constructor (prohibits copy creation)
  GoRoutine(const GoRoutine&);

  //private assignment operator (prohibits assignment )
  const GoRoutine& operator=(const GoRoutine&);

  // member data: the counter shared by all instances
  int counter;
  std::mutex seatMutex;

public:

  static GoRoutine& GetInstance()
  {
	static GoRoutine sharedGoRoutine;
        return sharedGoRoutine;
  }

  // public methods

  int GetCounter()
  {
     	return counter;
  }

  // it will return the requested counter if set successfully, otherwise it will be ignored and will return the old
  // counter. So we can only increase the number of seats but cannot reduce the number of seats.
  int SetCounter(int inputCounter)
  {
       std::lock_guard<std::mutex>lg(seatMutex);
       counter = inputCounter;
       return counter;
  }

  void Go( void(*GoFunction)(char*), char* args)
  {
             std::thread t (GoFunction, args);
             t.detach();
  }

};

int main()
{
	GoRoutine& Routine = GoRoutine::GetInstance();
	Routine.SetCounter(100);
	cout << "The counter of the GoRoutine is: " ;
        cout << GoRoutine::GetInstance().GetCounter() << endl;
        return 0;
}

