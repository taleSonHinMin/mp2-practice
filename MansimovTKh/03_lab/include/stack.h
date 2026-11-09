#ifndef STACK_H
#define STACK_H

#include <iostream>

using namespace std;

const int MAX_SIZE = 100000;

template<class T>
class Stack {
private:
	size_t maxSize;
	int topIdx;
	T* pMem;
public:
	Stack(size_t size) {
		if (size > MAX_SIZE || size == 0) throw invalid_argument("Invalid size of a stack");
		this->maxSize = size;
		this->topIdx = -1;
		this->pMem = new T[this->maxSize];
	}
	Stack(const Stack<T>& stack) : maxSize(stack.maxSize), topIdx(stack.topIdx) {
		this->pMem = new T[this->maxSize];
		for (int i = 0; i <= this->topIdx; i++) {
			this->pMem[i] = stack.pMem[i];
		}
	}
	Stack(Stack<T> && stack) : maxSize(stack.maxSize), topIdx(stack.topIdx) {
			this->pMem = stack.pMem;
			stack.pMem = nullptr;
			stack.maxSize = 0; stack.topIdx = -1;
	}
	~Stack(){
		delete[] this->pMem;
	}

	size_t size() { return this->maxSize; }
	int length() { return this->topIdx + 1; }

	const Stack& operator = (const Stack<T>& stack)
	{
		if (this == &stack) return *this;

		if (this->maxSize != stack.maxSize) {
			this->maxSize = stack.maxSize;
			delete[] this->pMem;
			this->pMem = new T[this->maxSize];
		}
		for (int i = 0; i <= stack.topIdx; i++) {
			this->pMem[i] = stack.pMem[i];
		}
		this->topIdx = stack.topIdx;
	}

	bool isEmpty() const {return (this->topIdx == -1);}
	bool isFull() const {return (this -> topIdx == this->maxSize - 1);}

	T Top() const {
		if (isEmpty()) throw out_of_range("The stack is empty");
		return this->pMem[this->topIdx];
	}
	void pop() {
		if (isEmpty()) throw out_of_range("The stack is empty");
		this->topIdx--;
	}
	void push(const T& elem) {
		if (isFull()) throw out_of_range("The stack is  full");
		this->pMem[++this->topIdx] = elem;
	}

	
};

#endif