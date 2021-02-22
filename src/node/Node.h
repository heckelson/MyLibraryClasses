
#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include <stdexcept>

#include "../vector/Vector.h"

template<typename T>
class Node {
private:
	T *data;
	Node *left_child;
	Node *right_child;

	/* This function gets called when you call .get_vector(). */
	Vector<T>& _get_vector(Vector<T>*);

public:
	Node();
	Node(T*);

	/* Set the data of this node */
	void set_data(T *data);

	/* Set the child nodes. */
	void set_left(Node*);
	void set_right(Node*);

	/* Recursive functions to print each node. */
	void print_preorder();
	void print_inorder();
	void print_postorder();

	Vector<T>& get_vector();
		/* Print the data of this object. */
	void print_data();

	/* Check if a certain Node has set a certain value. */
	bool has_data();
	bool has_left();
	bool has_right();
	bool is_full();

	/* Access the data associated with this Node. */
	T get();
};



template<typename T>
Node<T>::Node() {
	this->data = nullptr;
	this->left_child = nullptr;
	this->right_child = nullptr;
}

template<typename T>
Node<T>::Node(T *new_data) :
		Node<T>() {
	this->data = new_data;
}

template<typename T>
void Node<T>::set_data(T *new_data) {
	this->data = new_data;
}

template<typename T>
void Node<T>::set_left(Node<T> *node_ptr) {
	if (node_ptr == this) {
		throw std::runtime_error("Cannot set child as itself.");
	}

	if (node_ptr != nullptr) {
		left_child = node_ptr;
	}
}

template<typename T>
void Node<T>::set_right(Node<T> *node_ptr) {
	if (node_ptr == this) {
		throw std::runtime_error("Cannot set child as itself.");
	}

	if (node_ptr != nullptr) {
		right_child = node_ptr;
	}
}

template<typename T>
void Node<T>::print_preorder() {
	if (left_child != nullptr) {
		left_child->print_preorder();
	}

	this->print_data();

	if (right_child != nullptr) {
		right_child->print_preorder();
	}
}

template<typename T>
void Node<T>::print_inorder() {
	this->print_data();

	if (left_child != nullptr) {
		left_child->print_preorder();
	}

	if (right_child != nullptr) {
		right_child->print_preorder();
	}
}

template<typename T>
void Node<T>::print_postorder() {

	if (left_child != nullptr) {
		left_child->print_preorder();
	}

	if (right_child != nullptr) {
		right_child->print_preorder();
	}

	this->print_data();
}


template<typename T>
Vector<T>& Node<T>::get_vector() {
	return this->_get_vector(nullptr);
}

template<typename T>
Vector<T>& Node<T>::_get_vector(Vector<T>* vec){
	if (vec == nullptr) {
		vec = new Vector<T>;
	}

	if (data != nullptr) {
		vec->push_back(*data);
	}

	if (left_child != nullptr) {
		left_child->_get_vector(vec);
	}

	if (right_child != nullptr) {
		right_child->_get_vector(vec);
	}

	return *vec;
}



template<typename T>
void Node<T>::print_data() {
	if (this->has_data()) {
		std::cout << *data << "\n";
	} else {
		std::runtime_error("Cannot dereference null pointer.");
	}
}

template<typename T>
bool Node<T>::has_data() {
	return data != nullptr;
}

template<typename T>
bool Node<T>::has_left() {
	return left_child != nullptr;
}

template<typename T>
bool Node<T>::has_right() {
	return right_child != nullptr;
}

template<typename T>
bool Node<T>::is_full() {
	return (this->has_left() && this->has_right());
}

template<typename T>
T Node<T>::get() {
	if (data != nullptr) {
		return *data;
	}
	else {
		throw std::runtime_error("Cannot dereference nullptr's data.");
	}
}

#endif /* NODE_H_ */
