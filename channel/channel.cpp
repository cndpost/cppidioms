#include <iostream>
#include <string>
#include <mutex>
#include <vector>
#include <thread>
#include <deque>
using namespace std;
class Channel
{
 private:
  //private default constructor (prohibits creation from outside)
  Channel(){};
  
  // private copy constructor (prohibits copy creation)
  Channel(const Channel&);

  //private assignment operator (prohibits assignment )
  const Channel& operator=(const Channel&);

  // member data: the counter shared by all instances
  int counter;
  std::mutex seatMutex;
  std::deque<string> Buffer;
public:

  static Channel& GetInstance()
  {
	static Channel sharedChannel;
        return sharedChannel;
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

  
  void Send(const string& chdata)
  {
      Buffer.push_back(chdata);	
  }

  string Receive()
  {
     string& str = Buffer[0];
     Buffer.pop_front();
     return str;
  }

};

int main()
{
	Channel& channel = Channel::GetInstance();
	channel.SetCounter(100);
	cout << "The counter of the GoRoutine is: " ;
        cout << channel.GetCounter() << endl;
        
        channel.Send(string("hello"));
        cout << channel.Receive() << endl;

        return 0;
}

