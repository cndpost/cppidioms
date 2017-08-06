#include <iostream>
using namespace std;

class Node
{
  public:
  Node* next;
  int data;
  
    Node() 
    { 
    }
};

#define INVALID -1
class Queue;
class Queue
{
	public:
     //   Node* top, bottom;   //this declaration is wrong
        Node *top; Node *bottom;
	Queue()
        {
		top = NULL;
                bottom = NULL;
        };

	void enqueue(int data) {

		Node* newNode = new Node();
                newNode->data = data;
                newNode->next = NULL;
                if (top == NULL)
			top = newNode;
		if (bottom == NULL)
			bottom = newNode;
                else 
                {
                    bottom->next = newNode;
		    bottom = newNode;
                }
	};

        int dequeue()
	{
                int data = INVALID;
                if (top != NULL) {
			data = top->data;
			top = top->next;
		}else {
			bottom = NULL;
		}
		return data;
	}	

        int peek()
	{
		if (top != NULL)
			return top->data;
		else
			return INVALID;
	}	
};

int main()
{
	Queue* queue1 = new Queue();
	queue1->enqueue(1);
        queue1->enqueue(2);
        queue1->enqueue(3);

         
	cout << "first few queue data are " <<queue1->peek() << endl;
        cout  <<  queue1->dequeue() << endl;
        cout << queue1->dequeue() << endl;
        cout  <<queue1->dequeue() << endl;
	
//        cout << "first few queue data are " <<queue1->peek() << " " << queue1->dequeue() << " " << queue1->dequeue() << " " <<queue1->dequeue() << endl;
	return 0;
}


