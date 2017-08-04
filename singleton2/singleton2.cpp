#include <iostream>
#include <string>
#include <mutex>
#include <vector>
using namespace std;

class SingletonCounter
{
 private:
  //private default constructor (prohibits creation from outside)
  SingletonCounter( ){};
  
  // private copy constructor (prohibits copy creation)
  SingletonCounter(const SingletonCounter&);

  //private assignment operator (prohibits assignment )
  const SingletonCounter& operator=(const SingletonCounter&);

  // member data: the counter shared by all instances
  int counter;
  std::vector<string>seats;
  std::mutex seatMutex;

public:

  static SingletonCounter& GetInstance()
  {
	static SingletonCounter sharedSingletonCounter;
        return sharedSingletonCounter;
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
       if (counter > seats.size()) {
	int N=seats.size();
        for (int i=N; i++; i<counter) {
 		seats.push_back("");
        }
       }
       return counter;
  }

  bool BookSeat(int seatIndex, string &customerId)
  {
      std::lock_guard<std::mutex>lg(seatMutex);
      if (counter > seatIndex) {
         if (seats[seatIndex] == "")
             seats[seatIndex] = customerId;
             return true;
      }	
      return false;
  }

  bool CancelSeat(int seatIndex)
  {
	std::lock_guard<std::mutex> lg(seatMutex);
        if (counter > seatIndex) {
           if (seats[seatIndex] == "")
            return false; //nothing to cancel
           else {
            seats[seatIndex] == "";
            return true; // successfully cancelled the seat
           }
               
        }

  }
};

int main()
{
	SingletonCounter& OnlySingletonCounter = SingletonCounter::GetInstance();
	OnlySingletonCounter.SetCounter(100);
	cout << "The counter of the SingletonCounter is: " ;
        cout << SingletonCounter::GetInstance().GetCounter() << endl;
        return 0;
}

