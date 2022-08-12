#include "BinarySearchTree.h"
#include "Timer.h"
#include<ctime>
#include<iostream>
#include<vector>

int main()
{
	std::srand(static_cast<unsigned>(std::time(nullptr))); // seed

	pic10b::Tree t1; // empty tree

	for (size_t i = 0; i < 10; ++i) { // add 10 random double's from 0 to 1
		t1.insert(static_cast<double>(std::rand()) / RAND_MAX);
	}

	std::cout << "Elements: "; // and print the elements
	for (auto itr = t1.begin(), past_end = t1.end(); itr != past_end; ++itr) 
	{
		std::cout << *itr << " ";
	}
	std::cout << '\n';
	
	auto past_end = t1.end(); // go past the end
	--past_end; // but decrement to the last element
	std::cout << "Last element is: " << *past_end << '\n'; // show the last element

	std::cout << "Count of elements: " << t1.size() << '\n'; // count elements in t1

	pic10b::Tree t2 = t1; // t2 is a copy of t1

	double low, up; // lower and upper bounds for value removal

	std::cout << "Enter lower and upper values for removal: ";
	std::cin >> low >> up; // read in values
	
	auto itr = t1.begin();
	while (itr != t1.end())
	{ // while not at the end
		if ((low <= *itr) && (*itr <= up))
		{ // check if node value in range
			t1.erase(itr); // if so, erase it
			itr = t1.begin(); // and go back to the beginning
			continue; // repeat the loop, ignoring the increment
		}
		++itr; // if not in range then increment the iterator
	}

	// List all the elements of the two trees
	std::cout << "t1 and t2 elements: " << '\n';
	for (double d : t1) {
		std::cout << d << " ";
	}
	std::cout << '\n';
	for (double d: t2) {
		std::cout << d << " ";
	}

	std::cout << '\n';

	t2 = std::move(pic10b::Tree()); // move a default Tree	
	std::cout << "t2 size now: " << t2.size() << '\n';
	
	t2.insert(3.14); // add two numbers 
	t2.insert(100); 
	t2.insert(100); // this one is redundant

	pic10b::Tree::iterator iter_to_first = t2.begin();

	if (t2.find(3.14) == iter_to_first) { // check if 3.14 in collection and if first
		std::cout << "3.14 first item!" << '\n';
	}

	pic10b::swap(t2, t2); // prove it is available at namespace scope
	constexpr size_t small_n = 50;
	constexpr size_t big_n = 50000;
	std::vector<double> vals_to_insert;
	vals_to_insert.reserve(big_n);
	for (size_t i = 0; i < big_n; ++i) {
		vals_to_insert.push_back(std::rand() / (RAND_MAX + 1.));
	}

	simple_timer::timer<'u'> clock;

	{
		pic10b::Tree timed_tree;

		clock.tick();

		for (size_t i = 0; i < small_n; ++i) {
			timed_tree.insert(vals_to_insert[i]);
		}
		auto small_insert = clock.tock();
		std::cout << "small insert: " << small_insert << '\n';
		clock.tick();
	}
	auto small_destruct = clock.tock();
	std::cout << "small destruct: " << small_destruct << '\n';

	{
		pic10b::Tree timed_tree;

		clock.tick();

		for (size_t i = 0; i < big_n; ++i) {
			timed_tree.insert(vals_to_insert[i]);
		}
		auto big_insert = clock.tock();
		std::cout << "big insert: " << big_insert << '\n';
		clock.tick();
	}
	auto big_destruct = clock.tock();
	std::cout << "big destruct: " << big_destruct << '\n';

	return 0;
}