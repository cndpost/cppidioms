#include <iostream>
using namespace std;

class Node
{
  public:
  Node *next, *prev;
  int data;
  
    Node() 
    { 
    }
};

#define INVALID -1
class Deque;
class Deque
{
	public:
        Node *head, *tail;
	Deque()
        {
		head = NULL;
                tail = NULL;
        };

	void push_back(int data) {

		Node* newNode = new Node();
                newNode->data = data;
                newNode->next = NULL;
                newNode->prev = tail;
                if (head == NULL)
			head = newNode;
		if (tail == NULL)
			tail = newNode;
                else 
                {
                    tail->next = newNode;
		    tail = newNode;
                }
	};

        void pop_front()
	{
                int data = INVALID;
                if (head != NULL) {
			data = head->data;
			head = head->next;
		}else {
			tail = NULL;
		}
		return;
	}	

        int front()
	{
		if (head != NULL)
			return head->data;
		else
			return INVALID;
	}

        void push_front(int data)
        {
               Node* newNode = new Node();
                newNode->data = data;
		newNode->next = head;
                newNode->prev = NULL;
                if (head != NULL) 
                {        
		head->prev = newNode;
                }
		head = newNode;
                if (tail == NULL)
                        tail = newNode;

        }

        void pop_back()
        {
		Node* tmp = tail->prev;
                delete tmp->next;
		tmp->next = NULL;
		tail = tmp;
        }

        int end()
        {
		if (tail != NULL)
			return tail->data;
		else
			return INVALID;
        }

	
};

int main()
{
	Deque* queue1 = new Deque();
	queue1->push_back(1);
        queue1->push_back(2);
        queue1->push_back(3);

         
	cout << "first few queue data are " <<queue1->front() << endl;
        cout  <<  queue1->front() << endl; queue1->pop_front();
        cout << queue1->front() << endl; queue1->pop_front();
        cout  <<queue1->front() << endl; queue1->pop_front();
	
//        cout << "first few queue data are " <<queue1->peek() << " " << queue1->dequeue() << " " << queue1->dequeue() << " " <<queue1->dequeue() << endl;
	return 0;
}


