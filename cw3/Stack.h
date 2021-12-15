#pragma once
#include "MathUnit.h"

class Stack
{
private:
	struct Elem {
		Elem* next = nullptr;
		Elem* prev = nullptr;
		MathUnit* data = nullptr;
	};

	Elem* first = nullptr;

public:
	// Default constructor (empty stack)
	Stack() {

	}

	// Construct queue with one given element
	Stack(MathUnit* data) {
		first = new Elem;
		first->data = data;
	}

	~Stack() {
		while (!empty()) {
			pop();
		}
	}

	bool empty() {
		return (first == nullptr);
	}

	// Push front new element
	void push(MathUnit* data) {
		Elem* new_first = new Elem;
		new_first->data = data;
		if (first != nullptr) {
			new_first->next = first;
			first->prev = new_first;
		}
		first = new_first;
	}

	// Pop front element
	MathUnit* pop() {
		if (empty()) {
			return nullptr;
		}
		MathUnit* data = first->data;
		if (first->next != nullptr) {
			first = first->next;
			first->prev = nullptr;
		}
		else { // If stack turns empty
			first = nullptr;
		}
		return data;
	}

	MathUnit* last() {
		if (empty()) {
			return nullptr;
		}
		return first->data;
	}

	Stack* reverse() {
		Stack* copy = new Stack(*this);
		Stack* rev = new Stack();
		while (MathUnit* u = copy->pop()) {
			rev->push(u);
		}
		return rev;
	}
};

