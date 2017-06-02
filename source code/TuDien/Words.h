// C++ program for B-Tree insertion
#include<iostream>
using namespace std;

class Words
{
	char eWord[25];

public:
	Words(char* c);
	Words();
	~Words();
	Words& operator =(Words b);
	bool operator ==(Words const& b);
	bool operator >(Words const& b) const;
	bool operator <(Words const& b) const;
	char* getvalue() {
		return eWord;
	}
};

// A BTree node
class BTreeNode
{
	Words *keys;  // An array of keys
	int t;      // Minimum degree (defines the range for number of keys)
	BTreeNode **C; // An array of child pointers
	int n;     // Current number of keys
	bool leaf; // Is true when node is leaf. Otherwise false
public:
	BTreeNode(int _t, bool _leaf);   // Constructor

									 // A utility function to insert a new key in the subtree rooted with
									 // this node. The assumption is, the node must be non-full when this
									 // function is called
	void insertNonFull(Words k);

	// A utility function to split the child y of this node. i is index of y in
	// child array C[].  The Child y must be full when this function is called
	void splitChild(int i, BTreeNode *y);

	// A function to traverse all nodes in a subtree rooted with this node
	void traverse();

	// A function to search a key in subtree rooted with this node.
	BTreeNode *search(Words k, string &url);   // returns NULL if k is not present.

								// Make BTree friend of this so that we can access private members of this
								// class in BTree functions
	int countNode(int &count);

	int sizeNode();

	int maxKey(int &max);

	int minKey(int &min);

	double fulfill(double &count);

	int countLeaf(int &count);

	int HeightTree(int &h);
	
	friend class BTree;
};

// A BTree
class BTree
{
	BTreeNode *root; // Pointer to root node
	int t;  // Minimum degree
public:
	int getT() {
		return t;
	}

	// Constructor (Initializes tree as empty)
	BTree(int _t)
	{
		root = NULL;  t = _t;
	}

	// function to traverse the tree
	void traverse()
	{
		if (root != NULL) root->traverse();
	}

	// function to search a key in this tree
	BTreeNode* search(Words k, string &url)
	{
		return (root == NULL) ? NULL : root->search(k, url);
	}

	// The main function that inserts a new key in this B-Tree
	void insert(Words k);

	int countNode();

	int sizeNode();

	int maxKey();

	int minKey();

	double Averagefulfill();

	int countLeaf();

	int HeightTree();
};



