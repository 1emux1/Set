#include "Set.h"
#include <iostream>
int main()
{

	// SET

	// Set iterator
	set<int>::iterator i;

	// Set Initialization
	set<int>s1;
	s1.insert(5);
	s1.insert(4);
	s1.insert(7);
	set<int>s2(s1.begin(), s1.end());
	set<int>s3(s2);

	// Assignment
	set<int>s4 = s3;

	// Iterators
	std::cout << *s4.begin() << std::endl;
	std::cout << *s4.rbegin() << std::endl;

	// Capacity
	if (!s1.empty()) std::cout << "True" << std::endl;
	std::cout << s1.size() << std::endl;
	std::cout << s1.max_size() << std::endl;

	// Modifiers
	s4.insert(5);
	s4.insert(15);
	s4.erase(7);


	// Operations
	if (s4.find(5)) std::cout << "True" << std::endl;
	std::cout << s4.count(5) << std::endl;
	for (i = s4.begin(); i != s4.end(); ++i)
		std::cout << *i << " ";

	std::cin.get();
	return 0;
}