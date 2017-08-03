#include <iostream>
#include <string>
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

  void SetCounter(int inputCounter)
  {
       counter = inputCounter;
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

