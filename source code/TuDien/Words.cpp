#include "Words.h"

// Constructor for BTreeNode class
BTreeNode::BTreeNode(int t1, bool leaf1)
{
	// Copy the given minimum degree and leaf property
	t = t1;
	leaf = leaf1;

	// Allocate memory for maximum number of possible keys
	// and child pointers
	keys = new Words[2 * t - 1];
	C = new BTreeNode *[2 * t];

	// Initialize the number of keys as 0
	n = 0;
}

// Function to traverse all nodes in a subtree rooted with this node
void BTreeNode::traverse()
{
	// There are n keys and n+1 children, travers through n keys
	// and first n children
	int i;
	for (i = 0; i < n; i++)
	{
		// If this is not leaf, then before printing key[i],
		// traverse the subtree rooted with child C[i].
		if (leaf == false)
			C[i]->traverse();
		cout << " " << keys[i].getvalue();
	}
	cout << endl;

	// Print the subtree rooted with last child
	if (leaf == false)
		C[i]->traverse();
}

// Function to search key k in subtree rooted with this node
BTreeNode *BTreeNode::search(Words k, string &url)
{
	// Find the first key greater than or equal to k
	int i = 0;
	while (i < n && k > keys[i])
		i++;
	url+=(i + '0');

	// If the found key is equal to k, return this node
	if (keys[i] == k)
		return this;

	// If key is not found here and this is a leaf node
	if (leaf == true)
		return NULL;

	// Go to the appropriate child
	return C[i]->search(k, url);
}

// The main function that inserts a new key in this B-Tree
void BTree::insert(Words k)
{
	// If tree is empty
	if (root == NULL)
	{
		// Allocate memory for root
		root = new BTreeNode(t, true);
		root->keys[0] = k;  // Insert key
		root->n = 1;  // Update number of keys in root
	}
	else // If tree is not empty
	{
		// If root is full, then tree grows in height
		if (root->n == 2 * t - 1)
		{
			// Allocate memory for new root
			BTreeNode *s = new BTreeNode(t, false);

			// Make old root as child of new root
			s->C[0] = root;

			// Split the old root and move 1 key to the new root
			s->splitChild(0, root);

			// New root has two children now.  Decide which of the
			// two children is going to have new key
			int i = 0;
			if (s->keys[0] < k)
				i++;
			s->C[i]->insertNonFull(k);

			// Change root
			root = s;
		}
		else  // If root is not full, call insertNonFull for root
			root->insertNonFull(k);
	}
}

int BTree::countNode()
{
	int i = 0;
	if (root != NULL) root->countNode(i);
	return i;
}

int BTree::sizeNode()
{
	if (root != NULL) return root->sizeNode();
}

int BTree::maxKey()
{
	int i = 0;
	if (root != NULL) root->maxKey(i);
	return i;
}

int BTree::minKey()
{
	int i;
	if (root != NULL)
	{
		i = root->n;
		root->minKey(i);
	}
	return i;
}

double BTree::Averagefulfill()
{
	double sumFill = 0;
	int totalFill = 0;
	if (root != NULL) {
		root->fulfill(sumFill);
		root->countNode(totalFill);
	}
	return sumFill*1.0 / (totalFill*t*2-1);
}

int BTree::countLeaf()
{
	int i = 0;
	if (root != NULL) root->countLeaf(i);
	return i;
}

int BTree::HeightTree()
{
	//if (root != NULL) return root->HeightTree();
	return 0;
}

// A utility function to insert a new key in this node
// The assumption is, the node must be non-full when this
// function is called
void BTreeNode::insertNonFull(Words k)
{
	// Initialize index as index of rightmost element
	int i = n - 1;

	// If this is a leaf node
	if (leaf == true)
	{
		// The following loop does two things
		// a) Finds the location of new key to be inserted
		// b) Moves all greater keys to one place ahead
		while (i >= 0 && keys[i] > k)
		{
			keys[i + 1] = keys[i];
			i--;
		}

		// Insert the new key at found location
		keys[i + 1] = k;
		n = n + 1;
	}
	else // If this node is not leaf
	{
		// Find the child which is going to have the new key
		while (i >= 0 && keys[i] > k)
			i--;

		// See if the found child is full
		if (C[i + 1]->n == 2 * t - 1)
		{
			// If the child is full, then split it
			splitChild(i + 1, C[i + 1]);

			// After split, the middle key of C[i] goes up and
			// C[i] is splitted into two.  See which of the two
			// is going to have the new key
			if (keys[i + 1] < k)
				i++;
		}
		C[i + 1]->insertNonFull(k);
	}
}

// A utility function to split the child y of this node
// Note that y must be full when this function is called
void BTreeNode::splitChild(int i, BTreeNode *y)
{
	// Create a new node which is going to store (t-1) keys
	// of y
	BTreeNode *z = new BTreeNode(y->t, y->leaf);
	z->n = t - 1;

	// Copy the last (t-1) keys of y to z
	for (int j = 0; j < t - 1; j++)
		z->keys[j] = y->keys[j + t];

	// Copy the last t children of y to z
	if (y->leaf == false)
	{
		for (int j = 0; j < t; j++)
			z->C[j] = y->C[j + t];
	}

	// Reduce the number of keys in y
	y->n = t - 1;

	// Since this node is going to have a new child,
	// create space of new child
	for (int j = n; j >= i + 1; j--)
		C[j + 1] = C[j];

	// Link the new child to this node
	C[i + 1] = z;

	// A key of y will move to this node. Find location of
	// new key and move all greater keys one space ahead
	for (int j = n - 1; j >= i; j--)
		keys[j + 1] = keys[j];

	// Copy the middle key of y to this node
	keys[i] = y->keys[t - 1];

	// Increment count of keys in this node
	n = n + 1;
}

Words::Words(char* c)
{
	int n = strlen(c);

	if (n > 25) n = 25;

	for (int i = 0; i <= n; i++)
	{
		eWord[i] = c[i];
	}
}

Words::Words()
{
}

Words::~Words()
{

}

Words & Words::operator=(Words b)
{
	int n = strlen(b.eWord);

	if (n > 25) n = 25;

	for (int i = 0; i < n; i++)
	{
		eWord[i] = b.eWord[i];
	}
	eWord[n] = '\0';
	return b;
}

//-1:	str1<str2
//0:	str1=str2
//1:	str1>str2
int compare(char const * str1, char const * str2)
{
	int n1 = strlen(str1);
	int n2 = strlen(str2);
	int n = n1 > n2 ? n2 : n1;
	for (int i = 0; i < n; i++)
	{
		if (str1[i] > str2[i])
			return 1;
		if (str1[i] < str2[i])
			return -1;
	}
	if (n1 == n2) return 0;
	if (n1 < n2) return -1; else return 1;
}

bool Words::operator==(Words const & b)
{
	return compare(eWord, b.eWord) == 0;
}

bool Words::operator>(Words const & b) const
{
	return compare(eWord, b.eWord) == 1;
}

bool Words::operator<(Words const & b) const
{
	return compare(eWord, b.eWord) == -1;
}

int BTreeNode::countNode(int &count)
{
	// There are n keys and n+1 children, travers through n keys
	// and first n children
	int i;
	for (i = 0; i < n; i++)
	{
		// traverse the subtree rooted with child C[i].
		if (leaf == false)
			C[i]->countNode(count);
		
	}
	count++;

	// Print the subtree rooted with last child
	if (leaf == false)
		C[i]->countNode(count);
	return count;
}

int BTreeNode::sizeNode()
{
	return sizeof(this);
}

int BTreeNode::maxKey(int &max)
{
	// There are n keys and n+1 children, travers through n keys
	// and first n children
	
	if (n > max) max = n;

	int i;
	for (i = 0; i < n; i++)
	{
		// traverse the subtree rooted with child C[i].
		if (leaf == false)
			C[i]->maxKey(max);
	}

	// Print the subtree rooted with last child
	if (leaf == false)
		C[i]->maxKey(max);
	return max;
}

int BTreeNode::minKey(int &min)
{
	// There are n keys and n+1 children, travers through n keys
	// and first n children

	if (n < min) min = n;

	int i;
	for (i = 0; i < n; i++)
	{
		// traverse the subtree rooted with child C[i].
		if (leaf == false)
			C[i]->minKey(min);
	}

	// Print the subtree rooted with last child
	if (leaf == false)
		C[i]->minKey(min);
	return min;
}

double BTreeNode::fulfill(double &f)
{
	// There are n keys and n+1 children, travers through n keys
	// and first n children
	int i;
	for (i = 0; i < n; i++)
	{
		// traverse the subtree rooted with child C[i].
		if (leaf == false)
			C[i]->fulfill(f);

	}
	f += n;

	// Print the subtree rooted with last child
	if (leaf == false)
		C[i]->fulfill(f);
	return f;
}

int BTreeNode::countLeaf(int &count)
{
	// There are n keys and n+1 children, travers through n keys
	// and first n children
	int i;
	for (i = 0; i < n; i++)
	{
		// traverse the subtree rooted with child C[i].
		if (leaf == false)
			C[i]->countLeaf(count);
	}
	if(leaf == true) count++;

	// Print the subtree rooted with last child
	if (leaf == false)
		C[i]->countLeaf(count);
	return count;
}

int BTreeNode::HeightTree(int &h)
{
	return 0;
}
