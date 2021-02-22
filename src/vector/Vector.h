/*
 * Vector.h
 *
 *  Created on: 20.02.2021
 *      Author: alex
 */



#ifndef VECTOR_H_
#define VECTOR_H_

#include <iostream>
#define NOT_FOUND -1


template <typename T>
class Vector {
private:
	static constexpr int DEFAULT_SIZE = 1;
	static constexpr int RESIZE_FACTOR = 2.5;
	const std::string INDEX_ERROR = "Index out of bounds.";

	int size;
	int max_size;
	T *data;

	void resize(int new_size);

public:
	void swap(int, int);

	Vector();
	Vector(int max_size); // sets the max size.
	Vector(Vector& vector); // copy constructor

	Vector(std::initializer_list<T>);


	~Vector(); // destructor

	bool push_back(T value); // adding elements
	bool push_back(std::initializer_list<T>);

	bool remove(T value); // removing the first occurence of an element
	bool remove_all(T value); // remove all occurences.

	void clear(); // remove all elements.

	T& at(int) const; // accessing an index
	T& operator[](int) const; // accessing an index
	bool contains(T) const; // check if value contained in the array.

	int get_size() const;

	void bubble_sort();

	bool operator==(Vector<T>& other);
	bool operator==(const Vector<T>& other) const;

	bool operator!=(Vector<T>& other);
	bool operator!=(const Vector<T>& other) const;

	friend std::ostream& operator<<(std::ostream& os, const Vector<T> &vec) {
		bool first = true;

		os << "[ ";
		for (int i = 0; i < vec.get_size(); ++i) {
			if (!first) {
				os << ", ";
			}
			first = false;
			os << vec[i];
		}
		os << " ]";

		return os;
	}
};

template <typename T>
void Vector<T>::resize(int new_size) {
	/*
	 * Catches the errors:
	 * - reading outside allocated memory
	 * - size overflowing and going negative
	 */
	if (new_size < size || new_size < 0) {
		throw std::runtime_error("New Size is too small!");
	}

	/* Allocate new memory. */
	T *new_data = new T[new_size];
	T *old_data = data;

	/* Copy the old data into the new space. */
	for (int i = 0; i < size; ++i) {
		new_data[i] = old_data[i];
	}

	/* Set the right variables. */
	max_size = new_size;
	data = new_data;

	/* Free the old memory. */
	delete[] old_data;
}

template <typename T>
void Vector<T>::swap(int left_index, int right_index) {
	if (left_index < 0 || left_index >= size) {
		throw std::runtime_error(INDEX_ERROR);
	}

	if (right_index < 0 || left_index >= size) {
		throw std::runtime_error(INDEX_ERROR);
	}

	int left = data[left_index];
	int right = data[right_index];

	data[left_index] = right;
	data[right_index] = left;
}

template <typename T>
Vector<T>::Vector() {
	size = 0;
	max_size = DEFAULT_SIZE;
	data = new T[max_size];
}

template <typename T>
Vector<T>::Vector(int new_max_size) :
	max_size { new_max_size } {

	size = 0;
	if (max_size < DEFAULT_SIZE) {
		max_size = DEFAULT_SIZE;
	}
	data = new int[max_size];
}

template <typename T>
Vector<T>::Vector(Vector &other) {
	size = other.size;
	max_size = other.max_size;

	data = new T[max_size];

	for (int i = 0; i < size; ++i) {
		data[i] = other.data[i];
	}
}

template<typename T>
Vector<T>::Vector(std::initializer_list<T> list) : Vector<T>() {
	this->push_back(list);
}

template <typename T>
Vector<T>::~Vector() {
	delete[] data;
}

template <typename T>
int Vector<T>::get_size() const {
	return size;
}

template <typename T>
bool Vector<T>::push_back(T i) {
	if (size > max_size - 1) {
		resize(max_size * RESIZE_FACTOR + 1);
	}

	data[size] = i;
	size++;

	return true;
}

template<typename T>
bool Vector<T>::push_back(std::initializer_list<T> list) {
	for (T element : list) {
		this->push_back(element);
	}

	return true;
}

template <typename T>
bool Vector<T>::remove(T value) {
	int to_remove = NOT_FOUND;

	/* find the first occurence of the value */
	for (int i = 0; i < size; ++i) {
		if (data[i] == value) {
			to_remove = i;
			break;
		}
	}

	/* if no occurence is found, return false. */
	if (to_remove == NOT_FOUND) {
		return false;
	}
	else {
		/* go through the right side of the array, copying each element to the one left of it. */
		for (int i = to_remove; i < (size - 1); ++i) {
			data[i] = data[i+1];
		}
		/* keep the size up-to-date. */
		size--;
		return true;
	}
}

template <typename T>
bool Vector<T>::remove_all(T value) {
	bool removed = false;
	while(remove(value)) {
		/* if at least one value gets removed, this function will return true. */
		removed = true;
	}
	return removed;
}

template <typename T>
void Vector<T>::clear() {
	delete[] data;
	data = new T[DEFAULT_SIZE];
	size = 0;
}

template <typename T>
bool Vector<T>::contains(T value) const {
	for (int i = 0; i < size; ++i) {
		if (data[i] == value) {
			return true;
		}
	}
	return false;
}

template <typename T>
T& Vector<T>::operator[](int index) const {
	if (index >= size || index < 0) {
		throw std::runtime_error(INDEX_ERROR);
	}

	return data[index];
}

template <typename T>
T& Vector<T>::at(int index) const {
	return operator[](index);
}


template <typename T>
void Vector<T>::bubble_sort() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - (i + 1); j++) {
			if (data[j] > data[j+1]) {
				swap(j, j+1);
			}
		}
	}
}

template<typename T>
bool Vector<T>::operator==(Vector<T>& other) {
	return const_cast<Vector<T>*>(this)->operator == (const_cast<Vector<T>&>(other));
}

template<typename T>
bool Vector<T>::operator==(const Vector<T>& other) const {
	/* If size differs, return false. */
	if (size != other.size) {
		return false;
	}

	/* Content check. */
	for (int i = 0; i < size; i++) {
		if(data[i] != other[i]) {
			return false;
		}
	}

	/* Nothing wrong -> everything right. */
	return true;
}

template<typename T>
bool Vector<T>::operator !=(Vector<T> &other) {
	return !(this->operator==(other));
}

template<typename T>
bool Vector<T>::operator !=(const Vector<T> &other) const {
	return !(this->operator==(other));
}

#endif /* VECTOR_H_ */
