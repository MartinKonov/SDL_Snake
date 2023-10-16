#pragma once

template<typename T>
struct Node
{
	T data;
	Node<T>* next;
	Node() {
		this->next = nullptr;
	}
	Node(T element) {
		this->data = element;
		this->next = nullptr;
	}
};

template<typename T>
class List
{
	Node<T>* head;
	Node<T>* tail;
	int size;

public:
	List()
	{
		this->head = nullptr;
		this->tail = nullptr;
		this->size = 0;
	}

	List(T element)
	{
		Node<T>* toAdd = new Node<T>(element);
		head = toAdd;
		tail = head;
		size = 1;
	}

	~List()
	{
		Node<T>* current = tail;
		while (current != nullptr)
		{
			Node<T>* toDel = current->next;
			delete current;
			current = toDel;
		}
	}

	void push_back(T toPush)
	{
		Node<T>* toAdd = new Node<T>(toPush);
		if (size == 0)
		{
			head = toAdd;
			tail = head;
			size = 1;
			return;
		}
		toAdd->next = this->tail;
		this->tail = toAdd;
		this->size += 1;
	}

	void push_front(T toPush)
	{
		Node<T>* toAdd = new Node<T>(toPush);
		if (size == 0)
		{
			head = toAdd;
			tail = head;
			size = 1;
			return;
		}
		this->head->next = toAdd;
		this->head = toAdd;
		this->size += 1;
	}

	void pop_back()
	{
		if (size == 0)
		{
			return;
		}
		Node<T>* newTail = this->tail->next;
		delete this->tail;
		this->tail = newTail;
		size--;

	}

	Node<T>* getTail()
	{
		return this->tail;
	}

	Node<T>* gethead()
	{
		return this->head;
	}

	int getSize()
	{
		return this->size;
	}

};


// tail -- []->[]->[] --head