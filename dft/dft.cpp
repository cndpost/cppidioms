#include <iostream>
#include <vector>

using namespace std;

class Tree;
class Tree
{
   public:
   char data;
   bool visited;
   std::vector<Tree*> children;
};


void dft(Tree *root)
{

  if (root == NULL) return;
  if ( root->visited) return;
  int Size = root->children.size();
  for (int i=0;i<Size; i++) 
  {
	Tree *tree = root->children[i];
        dft(tree);


  } 
  root->visited  = true;
  printf("%c \n", root->data);
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

        cout << "start doing DFT in one way " << endl;
        dft(root);

        //above lines can also be written as
        delete root;
        root = new Tree();
        root->data = 'a';
        insert(root, 'd');
        insert(root, 'e');        
 

        cout << "start doing DFT in 2nd way" << endl;
        dft(root);
        cout << "done DFT " << endl;
	
	return 0;
}


