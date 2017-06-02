#include "FileBtree.h"

// Driver program to test above functions
int main()
{
	BTree t(5); // A B-Tree with minium degree 3
	readFile(t);

	//cout << "Traversal of the constucted tree is ";
	//t.traverse();

	writeFile(t);

	return 0;
}