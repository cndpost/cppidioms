#include <iostream>
using namespace std;

class Node
{
  public:
  Node* next;
  int data;
  
    Node(int data1) 
    { 
 	data = data1;
    }
};

#define INVALID -1
class Stack;
class Stack
{
	public:
        Node* top;
	Stack()
        {
		top = NULL;
        };

	void push(int data) {
		Node* newtop = new Node(data);
		newtop->next = top;
                top = newtop;
	};

        int pop()
	{
                int data = INVALID;
                if (top != NULL) {
			data = top->data;
			top = top->next;
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
	Stack* stack1 = new Stack();
	stack1->push(1);
        stack1->push(2);
        stack1->push(3);
       
//following output will have the correct result

       cout << "first few stack data are " <<stack1->peek();
       cout  << stack1->pop();
       cout   << stack1->pop();
       cout   <<stack1->pop() << endl;


// following output will not have the correct result because the cout runs from right to left in its output  
//	cout << "first few stack data are " <<stack1->peek() << " " << stack1->pop() << " " << stack1->pop() << " " <<stack1->pop() << endl;
	
	return 0;
}


