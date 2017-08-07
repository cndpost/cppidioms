#include <iostream>
#include <vector>
#include <deque>

using namespace std;

class Tree;
class Tree
{
   public:
   char data;
   bool visited;
   std::vector<Tree*> children;
};


void bft(Tree *root)
{

  if (root == NULL) return;
  if ( root->visited) return;
  root->visited  = true;
  printf("%c \n", root->data);
  std::deque<Tree *> *newQue = new std::deque<Tree *>();
  int Size = root->children.size();
  for (int i=0;i<Size; i++) 
  {
	Tree *child = root->children[i];
        if (child != NULL)
        newQue->push_back(child);
  } 

  for (int i=0; i<Size; i++)
  {
	Tree* child = newQue->front();
        if (child != NULL)
        bft(child);
        newQue->pop_front();
  }

//  root->visited  = true;
//  printf("%c \n", root->data);
  return;

};

void insert(Tree *root, char data)
{
  Tree *newTree = new Tree();
  newTree->data = data;
  newTree->visited = false;
  //newTree->children = NULL;
  root->children.push_back(newTree);
  return;
};

int main()
{
	Tree* root = new Tree();
	root->data = 'a';

        Tree* leftChild = new Tree{};
        leftChild->data = 'b';
        Tree* rightChild = new Tree();
        rightChild->data = 'c';
        root->children.push_back(leftChild);
        root->children.push_back(rightChild);

        cout << "start doing BFT in one way " << endl;
        bft(root);

        //above lines can also be written as
        delete root;
        root = new Tree();
        root->data = 'a';
        insert(root, 'd');
        insert(root, 'e');        
 

        cout << "start doing BFT in 2nd way" << endl;
        bft(root);
        cout << "done DFT " << endl;
	
	return 0;
}


