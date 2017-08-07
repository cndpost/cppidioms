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
class pQueue;
class pQueue
{
	public:
        Node *head,*tail;
	pQueue()
        {
		head = NULL;
                tail = NULL;
        };

	void push(int data) {

		Node* newNode = new Node();
                newNode->data = data;
                if (head == NULL) {
			head = newNode;
			tail = newNode;
		}
                else {
		    if ( data <= head->data )
                    { //insert before head
			newNode->next = head;
			head = newNode;
                    } else 
                    {
			Node *tmp = head;
			if ( tmp->next == NULL )
			{
				newNode->next = NULL;
				tmp->next = newNode;
				tail= newNode;
				return;
			}

			while( tmp->next != NULL)
			{
				if ( data > tmp->next->data)
				{
                                        if ( tmp->next != NULL) {
						tmp = tmp->next;
						continue;
					}
					else // we are at end
					{
						newNode->next = NULL;
						tmp->next = newNode;
						tail = newNode;
					}
				} else //	( data <= tmp->next->data) 
				{
					newNode->next = tmp->next;
					tmp->next = newNode;
					break;
				}

			}
		    }	

		}
	};

        void pop()
	{
                if (head != NULL) {
			head = head->next;
		}else {
			tail = NULL;
		}
	}	

        int top()
	{
		if (head != NULL)
			return head->data;
		else
			return INVALID;
	}	
};

int main()
{
	pQueue* queue1 = new pQueue();
	queue1->push(1);
        queue1->push(3);
        queue1->push(2);

         
	cout << "first few queue data are " <<queue1->top() << endl;
        cout  <<  queue1->top() << endl; queue1->pop();
        cout << queue1->top() << endl; queue1->pop();
        cout  <<queue1->top() << endl; queue1->pop();
	
	return 0;
}


