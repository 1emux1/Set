#include <iostream>

template<class T>
class set
{
public:
	// Member types
	using value_type = T;
	using iterator = T * ;
	using const_iterator = const T*;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	// Constructors
	set();
	set(typename set<T>::iterator first, typename set<T>::iterator last);
	set(set<T>& s);

	// Destructor
	~set();

	// Assignment operator
	set<T> &operator=(set<T>& s);

	// Iterators
	iterator begin() noexcept;
	iterator end() noexcept;
	reverse_iterator rbegin() noexcept;
	reverse_iterator rend() noexcept;

	// Capacity
	bool empty() noexcept;
	int size() noexcept;
	int max_size() noexcept;

	// Modifiers
	void insert(const value_type& val);
	void insert(typename set<T>::iterator position, const value_type& val);
	void insert(typename set<T>::iterator first, typename set<T>::iterator last);
	void erase(typename set<T>::iterator position);
	void erase(const value_type& val);
	void erase(typename set<T>::iterator first, typename set<T>::iterator last);
	void clear();

	// Operations
	bool find(const value_type& val) const;
	int count(const value_type& val) const;

	// Binary search tree for storing elements
	class Node
	{
	public:
		T key;
		Node *left, *right;
		Node *newNode(const value_type& val);
		Node *push(Node* node, const value_type& val);
		Node *search(Node* node, const value_type& val);
		Node *minValueNode(Node *node);
		Node *deleteNode(Node *node, const value_type& val);
	};

	void inorder(Node *node); // Inorder traversal of tree
	Node *root; // Root of binary search tree
	Node *n; // Object of Node class
private:
	int set_size;
	T *arr;
};