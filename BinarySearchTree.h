#ifndef _BINARYSEARCHTREE_
#define _BINARYSEARCHTREE_

#include <iostream>
#include <utility>
#include <stdexcept>

namespace pic10b
{
	//All three classes are declared here in the namespace
	class Tree; class iterator; class node;
	void swap(Tree& one, Tree& another); //declared this up here to be recognized in the namespace
	/**
	@Tree the binary search tree data structure that will store double values written in the pic10b namespace.
	Code should not have any memory leaks.
	*/
	class Tree
	{
	public:
		class iterator; //nested iterator class

		/**
		Default constructor: This default constructor is will store the empty Tree

		@param none
		*/

		Tree() noexcept;


		/**
		Copy construtor: creating a newly constructed object into a copy of another

		@param accepts constructor reference
		*/

		Tree(const Tree& copy);

		/**
		Move constructor: able to modify the value of the object

		@param accepts constructor reference
		*/

		Tree(Tree&& copy) noexcept;

		Tree& operator=(Tree& T)&; //copy assignment
		Tree& operator=(Tree&& T) &noexcept; //move assignment

		/**
		Destructor: clears up all of the object resources

		@param none
		*/
		~Tree();

		/**
		Swap function: this function just swap two trees 

		@param accepts constructor reference
		@return nothing, swaps the trees
		*/
		
		void swap(Tree& one, Tree& another); // swap two Trees: as a member function

		/**
		Insert function: this function allows us to enter values into the tree

		@param double representing the value entered into the tree
		@return type bool, true if nullptr and function is inserted we increment size
		*/

		bool insert(double value); 

		/**
		Erase function: this function removes the node managed by the iterator from the tree (val)

		@param accepts an iterator
		@return true if value is erased successfully, we decrement size
		*/

		bool erase(iterator itr);

		/**
		Begin function: this function returns an iterator to the first node

		@param accepts nothing
		@return iterator of first node
		*/

		iterator begin() const;

		/**
		End function: this function returns an iterator to one past the final node

		@param nothing
		@return iterator of past end node
		*/

		iterator end() const; // iterator to past-the-end position

		/**
		Size function: this function returns the size of the tree

		@param accepts nothing
		@return size of the tree size_t
		*/

		size_t size() const; 

		/**
		Find function: this function returns an iterator to the node being searched for

		@param accepts a double to be searched within the tree
		@return an iterator to the node of the value entered
		*/

		iterator find(double x); // check if contains a string


		friend void swap(Tree& one, Tree& another); //friend declaration for swap


	private:

		class node; // nested node class
		node* root; // the root of the tree
		double val; //values in the tree

		/**
		deleteTree function: this function recursively deletes nodes from the tree. It serves as a helper function
		for the destructor

		@param accepts a node to be deleted from the tree
		@return nothing, just deletes the entered node
		*/

		void deleteTree(node* n);

		/**
		traverseInsert function: this function recursively inserts nodes into the Tree. It serves as helper
		function for the default constructor, the copy constructor, and the insert function

		@param accepts a node to be inserted into the tree
		@return nothing, just enters nodes
		*/

		void traverseInsert(node* n);

		size_t sz; //member variable for the size
	};

	/**
	Overloaded operator ==

	@param accepts two trees
	@return overloads the == meaning between the two trees
	*/
	bool operator==(const Tree::iterator& left,const Tree::iterator& right);

	/**
	Overloaded operator !=

	@param accepts two trees
	@return overloads the != meaning between the two trees
	*/
	bool operator!=(const Tree::iterator& left,const Tree::iterator& right);

	/**
	@node this node class will represent the nodes used in the Tree data structure, it is nested in the Tree class
	*/

	class Tree::node 
	{
		friend Tree; // tree member functions may search through nodes
		friend iterator; // to be able to advance by checking node values
	private:
		node* left, * right; // children nodes
		node* parent; //parent node
		size_t sz; //size variable

		/**
		Constructor: This default constructor is will store the empty nodes

		@param double x storing the nodes to nullptr
		*/

		node(double x); // constructor: take by value and move it

		/**
		Constructor: This default constructor is will store the empty nodes

		@param double x, nodes left, right, parent setting them equal to their private member names
		*/

		node(double x, node* left, node* right, node* parent); 

		/**
		Min function: This function represents the minimum node to be used in the ++ and -- prefix operator

		@param none
		@return the minimum value node
		*/

		node* min() 
		{
			node* curr = this;
			if (left == nullptr) //if left is nullptr then it's min
			{
				return this;
			}
			while (curr->left != nullptr) //if we can go left then continue until we cant
			{
				curr = curr->left;
			}
			return curr->min(); //return the min recursively
		}

		/**
		Max function: This function represents the maximum node to be used in the end() functions

		@param none
		@return the minimum value node
		*/

		node* max() 
		{
			if (right == nullptr) //if we can't go right anyfurther then it's max
			{
				return this; //throw exception
			}
			return right->max(); //return max recursively
		}
		double val; // data value stored

		/**
		insertNode function: This function recursively inserts nodes and serves as a helper function for
		the insert function

		@param node to be inserted
		@return nothing, inserts nodes
		*/

		void insertNode(node* n); // member function for inserting node
	};

	/**
	@iterator this iterator class will represent the iterators used in the Tree data structure, it is nested in the Tree class
	*/
	class Tree::iterator
	{
		// LinkedList may change data of iterator during operations
		friend Tree; // to allow iterator modifications by Tree operations
	private:
		node* curr; // current position
		const Tree* container; // holding container
	public:
		/**
		Constructor: this is a constructor for the iterator taking in a Tree container, used in the find function

		@param Tree container
		*/

		iterator(const Tree* container);

		/**
		Constructor: this is a constructor for the iterator representing the node inside the Tree container

		@param Tree container
		*/

		iterator(node* n, const Tree* ell);

		/**
		Prefix ++ operator to increment in the node by 1 during the printing loop

		@param none
		*/

		iterator& operator++();

		/**
		Postfix ++ operator to increment in the node by 1 during the printing loop

		@param none
		*/

		iterator operator++(int x);

		/**
		Prefix -- operator to increment in the node by 1 during the printing loop

		@param none
		*/

		iterator& operator--();

		/**
		Postfix -- operator to increment in the node by 1 during the printing loop

		@param none
		*/

		iterator operator--(int x);
		const double& operator*() const; // dereference operator
		const double* operator->() const //overloaded -> operator for val
		{ // arrow operator
			return &(curr->val);
		}
		friend bool operator==(const iterator& left, const iterator& right); //comparison operators declared as friend here so
		friend bool operator!=(const iterator& left, const iterator& right); //we can use these private member variables in their definitions
	};
}

#endif

