#pragma once
#pragma once

template<typename T>

class List
{
public:
	List();
	virtual ~List();
	List(const List& other);
	List& operator=(const List& other);
	void insertAt(int pos, const T& element) throw(...);
	T getAt(int pos) const throw(...);
	void removeAt(int pos) throw(...);
	bool removeElement(const T& element);
	bool findElement(const T& toFind) const;
	int length() const;
	void getAll(T arr[], int cap) throw(...);

private:
	class Node
	{
	public:
		T element;
		Node* next;
		Node(const T& element)
		{
			this->element = element;
			this->next = nullptr;
		}
		~Node()
		{
			//empty
		}
	};

	int nrOfNodes;
	Node* first;



};

template<typename T>
inline List<T>::List()
{
	this->nrOfNodes = 0;
	this->first = nullptr;
}

template<typename T>
inline List<T>::~List()

{
	Node* walker = first;
	while (walker != nullptr)
	{
		Node* remove = walker;
		walker = walker->next;
		delete remove;
	}


}

template<typename T>
inline List<T>::List(const List & other)
{
	if (other.first == nullptr)
	{
		this->first = nullptr;
	}
	else
	{
		this->nrOfNodes = other.nrOfNodes;
		this->first = new Node(other.first->element);
		Node* walker = first;
		Node* otherWalker = other.first;
		while (otherWalker->next != nullptr)
		{
			walker->next = new Node(otherWalker->next->element);
			otherWalker = otherWalker->next;
			walker = walker->next;
		}
	}
}

template<typename T>
inline List<T> & List<T>::operator=(const List & other)
{
	if (this != &other)
	{
		this->~List();

		if (other.first == nullptr)
		{
			this->first = nullptr;
			this->nrOfNodes = 0;
		}
		else
		{
			this->nrOfNodes = other.nrOfNodes;
			this->first = new Node(other.first->element);
			Node* walker = first;
			Node* otherWalker = other.first;
			while (otherWalker->next != nullptr)
			{
				walker->next = new Node(otherWalker->next->element);
				otherWalker = otherWalker->next;
				walker = walker->next;
			}
		}

	}

	return *this;
}



template<typename T>
inline void List<T>::insertAt(int pos, const T & element) throw(...)
{
	if ((pos>this->nrOfNodes) || (pos<0))
	{
		throw "Invalid position..";
	}

	Node* temp = new Node(element);
	if (pos == 0)
	{
		temp->next = first;
		first = temp;
	}

	else
	{
		Node* walker = first;
		for (int i = 0; i < pos - 1; i++)
		{
			walker = walker->next;
		}
		temp->next = walker->next;
		walker->next = temp;
	}

	this->nrOfNodes++;
}

template<typename T>
inline T List<T>::getAt(int pos) const throw(...)
{
	if (pos>this->nrOfNodes || pos<0)
	{
		throw "Invalid position..";
	}
	if (this->nrOfNodes == 0)
	{
		throw"The list is empty..";
	}

	T retVal;
	if (pos == 0)
	{
		retVal = first->element;
	}
	else
	{
		Node* walker = first;
		for (int i = 0; i < pos; i++)
		{
			walker = walker->next;
		}


		retVal = walker->element;
	}
	return retVal;
}

template<typename T>
inline void List<T>::removeAt(int pos) throw(...)
{
	if (pos>this->nrOfNodes - 1 || pos<0)
	{
		throw "Invalid position..";
	}
	Node* current = first;
	if (pos == 0)
	{
		first = current->next;
	}

	else
	{

		Node* previous = nullptr;
		for (int i = 0; i < pos; i++)
		{
			previous = current;
			current = current->next;
		}
		previous->next = current->next;


	}
	delete current;

	nrOfNodes--;
}

template<typename T>
inline bool List<T>::removeElement(const T & element)
{
	bool removed = false;
	bool excist = this->findElement(element);
	if (excist)
	{
		Node* walker = first;
		if (walker->element == element)
		{
			first = walker->next;
			removed = true;
		}
		else {
			Node* previous = nullptr;
			for (int i = 0; i < nrOfNodes - 1; i++)
			{
				previous = walker;
				walker = walker->next;
				if (walker->element == element)
				{
					previous->next = walker->next;
					removed = true;
					i = nrOfNodes;
				}

			}
		}
		delete walker;
		nrOfNodes--;
	}

	return removed;
}

template<typename T>
inline bool List<T>::findElement(const T & toFind) const
{
	bool found = false;
	if (first != nullptr)
	{
		Node* walker = first;
		if (walker->element == toFind)
		{
			found = true;
		}
		else {

			for (int i = 0; i < nrOfNodes - 1; i++)
			{
				walker = walker->next;
				if (walker->element == toFind)
				{
					found = true;
					i = nrOfNodes;
				}

			}
		}
	}
	return found;
}

template<typename T>
inline int List<T>::length() const
{
	return this->nrOfNodes;
}

template<typename T>
inline void List<T>::getAll(T arr[], int cap) throw(...)
{
	if (cap<this->nrOfNodes || cap<0)
	{
		throw "Array capacity to low";
	}
	Node* walker = first;

	for (int i = 0; i < nrOfNodes; i++)
	{
		arr[i] = walker->element;
		walker = walker->next;
	}

}
