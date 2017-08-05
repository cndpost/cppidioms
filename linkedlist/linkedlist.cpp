#include <iostream>
using namespace std;

class Node;
class Node
{
	public:
        Node* next;
        int data;
	
        Node(int d){
		data = d;
	};

	void appendToTail(int d) {
		Node* end = new Node(d);
		Node* n = this;
		while(n->next != NULL)
			n = n->next;
		n->next = end;
	};
		
};

int main()
{
	Node* node = new Node(1);
	node->appendToTail(2);

	cout << "first few nodes data are " << node->data << " " << node->next->data << endl;
	
	return 0;
}


