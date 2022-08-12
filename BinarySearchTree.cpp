#include <iostream>
#include <utility>
#include <stdexcept>
#include <string>

#include "BinarySearchTree.h"

using namespace pic10b;

///////*****TREE CLASS DEFINITIONS*****///////

Tree::Tree() noexcept : root(nullptr), sz(0) //default constructor initializing the root to null and the size to 0 
{
	traverseInsert(root); //call this function to insert the root node into the tree, then we build off of it
}

Tree::Tree(const Tree& copy) : root(nullptr), sz(0) //copy constructor doing the same thing as the default but just with copy
{
	traverseInsert(copy.root);
}

Tree::Tree(Tree&& copy) noexcept : Tree()  //move constructor just gives the swap command when moving one tree to another
{
	swap(*this, copy);
}

Tree& Tree::operator=(Tree& T)& //copy assignment 
{
	swap(*this, T);
	return *this;
}
Tree& Tree::operator=(Tree&& T) &noexcept //move assignment
{
	swap(*this, T);
	T.root = nullptr; //set the new root to null
	return *this;
}
Tree::~Tree()
{
	deleteTree(root); //we're just deleting nodes here in the destructor
}

void Tree::swap(Tree& one, Tree& another) 
{
	//this swap function just swaps two trees, so we swap their contents root and size
	std::swap(one.root, another.root); 
	std::swap(one.sz, another.sz);
}

bool Tree::insert(double value)
{
	sz += 1; //increment the size in this function because when it's true the size adds
	if (!root) { // if the root is empty
	// make a new node and set this to be root
		root = new node(value);
		return true; //return true if successfull
	}
	else { // otherwise
		node* n = new node(value); // create a new node
		// and recursively pass it node to node until in place
		root->insertNode(n);
		return true; //return true if successfull
	}
	return false; //return false for all other conditions insert fails
}

size_t Tree::size() const
{
	return sz; //this just returns the size
}

bool Tree::erase(iterator itr)
{
	if (itr.curr == nullptr) //if we aren't moving anymore then erasing is finished or false
	{
		return false;
	}
	node* n = itr.curr;
	node* tmp;

	if (n->right == nullptr && n->left != nullptr)  //if we can't go right but we can go left
	{
		if (n == root) //if the node is the root,
		{
			root = n->left;
			root->parent = nullptr; //set the parent to nullptr and delete the node
			delete n;
			return true;
			--sz; //decrement the size
		}
		//get max of the left
		tmp = n->left->max();
		n->val = tmp->val;
		if (tmp == n->left) //if left is the max value we go left until we can't
		{
			n->left = tmp->left;
		}
		else 
		{
			//board case
			tmp->parent->right = tmp->left;
		}
	}
	else if (n->right != nullptr) //go right until we can't
	{
		//Do same things as before but swap left/right and min/max
		if (n == root)
		{
			root = n->right;
			root->parent = nullptr;
			delete n;
			return true;
			--sz; //decrement size
		}
		//get max of the left
		tmp = n->right->min();
		n->val = tmp->val;
		if (tmp == n->right) 
		{
			n->right = tmp->right;
		}
		else 
		{
			//board case
			tmp->parent->left = tmp->right;
		}
	}
	else 
	{
		//No children -> just delete the node
		tmp = n;
		if (tmp->parent->left == tmp)
		{
			tmp->parent->left = nullptr;
		}
		else
		{
			tmp->parent->right = nullptr;
		}
		tmp->parent = nullptr;
	}
	delete tmp;

	return true;
	--sz;
}

Tree::iterator Tree::begin() const 
{ // return type requires scope
	if (root == nullptr) 
	{ // if root is null then tree empty
		return iterator(nullptr, this); // return iterator that is null
	}
	node* n = root; // start at the root
	while (n->left != nullptr) 
	{ // while we can still go left (to lower value)
		n = n->left;// go left
	}
	return iterator(n, this); // return iterator for node of smallest value
}
// end iterator means “past the end” and should store null
Tree::iterator Tree::end() const 
{
	return iterator(nullptr, this);
}

Tree::iterator Tree::find(double x) 
{
	node* curr = root;
	while (curr != nullptr) //while the node is occupied
	{
		if (x == curr->val) //if the double entered is the value the node is one, return it
		{
			return iterator(curr, this);
		}
		else if (x < curr->val) //if the value entered is less than the value of the current node
		{
			curr = curr->left; //go left until value is found
		}
		else //other cases for when the value entered is greater than the value of the current node, 
		{
			curr = curr->right; //go right until value is found
		}
	}
	return iterator(this);
}

void Tree::traverseInsert(node* n) 
{
	//compare then go left or right
	if (n != nullptr)
	{
		insert(n->val);
		if (n->left != nullptr)
		{
			//n->left = new node(val);
			//n->left->parent = n;
			traverseInsert(n->left);
		}
		//right stuff
		if (n->right != nullptr)
		{
			//n->right = new node(val);
			//n->right->parent = n;
			traverseInsert(n->right);
		}
	}
}

void Tree::deleteTree(node* n)
{
	if (n == NULL) //if n is null then it's been deleted, do nothing
	{
		return;
	}
	if (n)
	{
		//recursively delete nodes to the left and to the right
		deleteTree(n->left); 
		deleteTree(n->right);
		delete n;
	}
}

//////////////////////*****NODE CLASS DEFINITIONS*****/////////////////////////////

Tree::node::node(double x) : val(x), left(nullptr), right(nullptr), parent(nullptr)
{}
Tree::node::node(double x, node* left, node* right, node* parent) : val(x),
left(left), right(right), parent(parent) {}


void Tree::node::insertNode(node* n)
{
	// if this value is less than new node value, new node should go right
	if (val < n->val)
	{
		if (right) 
		{ // if this node has a right child
			right->insertNode(n); // recurse on the right child
		}
		else 
		{ // if the right child is null
			right = n; // make this the right child
			n->parent = this;
		}
	}
	else if (val > n->val) //same stuff just the other way around with the left nodes
	{
		if(left)
		{
			left->insertNode(n);
		}
		else
		{
			left = n;
			n->parent = this;
		}
	}
	else
	{
		delete n;
	}

}

//////////////////////*****ITERATOR CLASS DEFINITIONS*****/////////////////////////////

Tree::iterator::iterator(const Tree* container) : curr(nullptr), container(container)
{}
Tree::iterator::iterator(node* start, const Tree* container) : curr(start),
container(container) {}

Tree::iterator& Tree::iterator::operator++()// prefix ++
{
	//node* p;
	if (curr == nullptr)
	{
		curr = container->root->min();
		return *this; //throw exception
	}
	//If we can go right, then go to the min on the right
	if (curr->right != nullptr)
	{
		curr = curr->right->min();
	}
	//If we can't go right anymore and left child, then go to parent
	//If we can't go right anymore and right child, go up until we hit right parent
	else 
	{
		//If node is a right child, keep going up until it is a left child
		while (curr->parent != nullptr && curr->parent->right == curr)
		{
			curr = curr->parent;
		}
		curr = curr->parent;
	}
	return *this;
}


Tree::iterator Tree::iterator::operator++(int x)
{
	iterator copy(*this);
	++(*this); // or this->operator--();
	return copy;
}// postfix ++
Tree::iterator& Tree::iterator::operator--()
{
	
	if (curr == nullptr) //if current node is null then it is the max
	{
		curr = container->root->max();
		return *this;
	}
	if (container->root->min() == curr) //if we are at the min then we are finished
	{
		return *this;
	}
	if (curr->left != nullptr) //if we can go left, continue until curr hits the min
	{
		curr = curr->left->max();
	}
	else
	{//while curr is still occupied parent and we can go left, the curr parent
		while (curr->parent != nullptr && curr->parent->left == curr)
		{
			curr = curr->parent;
		}
		curr = curr->parent;
	}
	return *this;
}// prefix - -
Tree::iterator Tree::iterator::operator--(int x)
{
	iterator copy(*this);
	--(*this); // or this->operator--();
	return copy;
}// postfix - -*/
const double& Tree::iterator::operator*() const
{
	if (curr == nullptr) //if curr is null return null, but we are simply returning values here
	{
		return NULL;
	}
	return curr->val;
}

///////////////////////*******NON-MEMBER DEFINTIONS********//////////////////////////////

bool pic10b::operator==(const Tree::iterator& left, const Tree::iterator& right)
{//here just return the equals result
	return ((left.curr == right.curr) && (left.container == right.container));
}
// != defined by negating ==
bool pic10b::operator!=(const Tree::iterator& left, const Tree::iterator& right)
{
	return ((left.curr != right.curr) || (left.container != right.container));
}
void pic10b::swap(Tree& one, Tree& another)
{
	std::swap(one.root, another.root);
	std::swap(one.root, another.root);
}//redefined for namespace


