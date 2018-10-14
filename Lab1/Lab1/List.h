#pragma once

template <typename T>
struct ListElem
{
	ListElem<T>* next;
	T value;
	ListElem(T val, ListElem<T>* nextElem = nullptr);
};

template<typename T>
class List
{
private:
	ListElem<T>* head;
	ListElem<T>* getElem(unsigned index);
	unsigned len;
public:
	List();
	~List();
	unsigned length();
	void push(int index, T value);
	void pushBack(T value); // not optimized
	void erase(int index);
	T List<T>::operator[](int index);
};

template<typename T>
inline ListElem<T>::ListElem(T val, ListElem<T>* nextElem)
{
	value = val;
	next = nextElem;
}

template<typename T>
ListElem<T>* List<T>::getElem(unsigned index)
{
	ListElem<T>* current = head;
	for (unsigned i = 0; i < index; ++i)
	{
		current = current->next;
	}
	return current;
}

template<typename T>
T List<T>::operator[](int index)
{
	return getElem(index)->value;
}

template<typename T>
List<T>::List()
{
	head = nullptr;
	len = 0;
}

template<typename T>
List<T>::~List()
{
	if (len == 0)
		return;
	if (len == 1)
	{
		delete head;
	}
	else
	{
		ListElem<T>* nextNode = head->next;
		ListElem<T>* curNode = head;

		while (curNode != nullptr)
		{
			delete curNode;
			curNode = nextNode;
			if(curNode != nullptr)
				nextNode = curNode->next;
		}

	}
}

template<typename T>
void List<T>::push(int index, T value)
{
	ListElem<T>* newElem = new ListElem<T>(value);

	if (index == 0)
	{
		newElem->next = head;
		head = newElem;
	}
	else
	{
		ListElem<T>*prevElem = getElem(index - 1);
		newElem->next = prevElem->next;
		prevElem->next = newElem;
	}
	len++;
}

template<typename T>
void List<T>::pushBack(T value)
{
	push(len, value);
}

template<typename T>
void List<T>::erase(int index)
{
	if (len == 0)
	{
		return;
	}

	if (index == 0)
	{
		ListElem<T>* toErase = head;
		head = head->next;
		delete toErase;
	}
	else
	{
		ListElem<T>* prev = getElem(index - 1);
		ListElem<T>* toErase = getElem(index);
		prev->next = toErase->next;
		delete toErase;

	}
	len--;
}

template<typename T>
unsigned List<T>::length()
{
	return len;
}
