#include "Set.h"

template<class T>
set<T>::set()
{
	set_size = 0;
	root = NULL;
	n = new Node;
	arr = new T[10000];
}

template<class T>
set<T>::set(typename set<T>::iterator first, typename set<T>::iterator last)
{
	set_size = 0;
	root = NULL;
	n = new Node;
	arr = new T[10000];
	set<T>::iterator i;
	for (i = first; i != last; ++i)
		// Add element to the set if element is not in the set
		if (!find(*i))
			insert(*i);
}

template<class T>
set<T>::set(set<T>& s)
{
	set_size = 0;
	root = NULL;
	n = new Node;
	arr = new T[10000];
	set<T>::iterator i;
	for (i = s.begin(); i != s.end(); ++i)
		insert(*i);
}

// Destructor
template<class T>
set<T>::~set()
{
	delete[] arr;
	clear();
}

template<class T>
set<T> &set<T>::operator=(set<T>& s)
{
	set_size = 0;
	root = NULL;
	n = new Node;
	arr = new T[10000];
	set<T>::iterator i;
	for (i = s.begin(); i != s.end(); ++i)
		insert(*i);
	return *this;
}

template<class T>
typename set<T>::iterator set<T>::begin() noexcept
{
	return arr;
}

template<class T>
typename set<T>::iterator set<T>::end() noexcept
{
	return arr + set_size;
}

template<class T>
typename set<T>::reverse_iterator set<T>::rbegin() noexcept
{
	return reverse_iterator(arr + set_size);
}

template<class T>
typename set<T>::reverse_iterator set<T>::rend() noexcept
{
	return reverse_iterator(arr);
}

template<class T>
bool set<T>::empty() noexcept
{
	if (set_size == 0) return true;
	return false;
}

template<class T>
int set<T>::size() noexcept
{
	return set_size;
}

template<class T>
int set<T>::max_size() noexcept
{
	return INT_MAX;
}
template<class T>
void set<T>::insert(const value_type& val)
{
	bool flag = 0;
	// If binary tree is empty, make this value root of the tree
	if (root == NULL) {
		flag = 1;
		root = n->push(root, val);
	}
	else if (!find(val)) {
		flag = 1;
		n->push(root, val);
	}
	if (flag) {
		delete[] arr;
		arr = new T[10000];
		set_size = 0;
		inorder(root);
	}
}

template<class T>
void set<T>::insert(typename set<T>::iterator position, const value_type& val)
{
	bool flag = 0;
	// If binary tree is empty, make this value root of the tree
	if (root == NULL) {
		flag = 1;
		root = n->push(root, val);
	}
	else if (!find(val)) {
		flag = 1;
		n->push(root, val);
	}
	if (flag) {
		delete[] arr;
		arr = new T[10000];
		set_size = 0;
		inorder(root);
	}
}

template<class T>
void set<T>::insert(typename set<T>::iterator first, typename set<T>::iterator last)
{
	bool flag = 0;
	set<T>::iterator i;
	for (i = first; i != last; ++i) {
		// If the element is not in the set, insert it into the set
		if (!find(*i)) {
			n->push(root, *i);
			flag = 1;
		}
	}
	if (flag) {
		delete[] arr;
		arr = new T[200];
		set_size = 0;
		inorder(root);
	}
}

template<class T>
void set<T>::erase(typename set<T>::iterator position)
{
	const value_type val = *position;
	if (find(val)) {
		root = n->deleteNode(root, val);
		delete[] arr;
		arr = new T[10000];
		set_size = 0;
		inorder(root);
	}
}

template<class T>
void set<T>::erase(const value_type& val)
{
	if (find(val))
	{
		root = n->deleteNode(root, val);
		delete[] arr;
		arr = new T[10000];
		set_size = 0;
		inorder(root);
	}
}

template<class T>
void set<T>::erase(typename set<T>::iterator first, typename set<T>::iterator last)
{
	set<T>::iterator i;
	for (i = first; i != last; ++i) {
		root = n->deleteNode(root, *i);
	}
	delete[] arr;
	arr = new T[10000];
	set_size = 0;
	inorder(root);
}

template<class T>
void set<T>::clear()
{
	arr = NULL;
	set_size = 0;
	root = NULL;
}

template<class T>
bool set<T>::find(const value_type& val) const
{
	if (n->search(root, val) == NULL) return false;
	return true;
}

template<class T>
int set<T>::count(const value_type& val) const
{
	if (n->search(root, val) == NULL) return false;
	return true;
}

template<class T>
typename set<T>::Node *set<T>::Node::newNode(const value_type& val)
{
	set<T>::Node *temp = new set<T>::Node;
	temp->key = val;
	temp->left = temp->right = NULL;
	return temp;
}

template<class T>
typename set<T>::Node *set<T>::Node::push(Node* node, const value_type& val)
{
	// If the tree is empty, return a new node
	if (node == NULL) return newNode(val);

	// Otherwise, recur down the tree
	if (val < node->key)
		node->left = push(node->left, val);
	else if (val > node->key)
		node->right = push(node->right, val);

	// Return the (unchanged) node pointer
	return node;
}

template<class T>
typename set<T>::Node *set<T>::Node::search(Node* node, const value_type& val)
{
	// Base	Cases: node is null or value is present at node
	if (node == NULL || node->key == val)
		return node;

	// Value is greater than node's key
	if (node->key < val)
		return search(node->right, val);

	// Value is smaller than node's key
	return search(node->left, val);
}

template<class T>
typename set<T>::Node *set<T>::Node::minValueNode(Node *node)
{
	Node *current = node;

	// Loop down to find the leftmost leaf
	while (current && current->left != NULL)
		current = current->left;

	return current;
}

template<class T>
typename set<T>::Node *set<T>::Node::deleteNode(Node *node, const value_type& val)
{
	// Base case
	if (node == NULL) return node;

	// If the value to be deleted is smaller than the node's key, then it lies in left subtree
	if (val < node->key)
		node->left = deleteNode(node->left, val);

	//If the value to be deleted is greater than the node's key, then it lies in right subtree
	else if (val > node->key)
		node->right = deleteNode(node->right, val);

	// If the value is same as node's key,then this is the node to be deleted
	else
	{
		// node with only one child or no child
		if (node->left == NULL)
		{
			Node *temp = node->right;
			free(node);
			return temp;
		}
		else if (node->right == NULL)
		{
			Node *temp = node->left;
			free(node);
			return temp;
		}

		// Node with 2 children: Get the inorder successor (smallest in the right subtree)
		Node *temp = minValueNode(node->right);

		// Copy the inorder successor's content to this node
		node->key = temp->key;

		// Delete the inroder successor
		node->right = deleteNode(node->right, temp->key);
	}
	return node;
}

template<class T>
void set<T>::inorder(Node *node)
{
	if (node != NULL)
	{
		inorder(node->left);
		arr[set_size++] = node->key;
		//std::cout << node->key << " ";
		inorder(node->right);
	}
}

template class set<int>;
template class set<char>;
template class set<double>;
template class set<float>; 
