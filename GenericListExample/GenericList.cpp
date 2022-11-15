#include "GenericList.hpp"

template<class data_t>
GenericList<data_t>::GenericList()
{
	counter = 0;
}

template<class data_t>
GenericList<data_t>::~GenericList()
{
	while(root!=NULL)
	{
		Node* tmp=root;
		root=root->next;
		delete tmp;
	}
}

template<class data_t>
void GenericList<data_t>::removeAt(Node* pointer, Node* previous)
{
	if (previous==NULL) root = root->next;
	else previous->next = pointer->next;
	delete pointer;
	if (counter>0) counter--;
}

template<class data_t>  	
bool GenericList<data_t>::add(data_t newValue)
{
	if (counter==0)
	{
		root = new Node;
		root->next = NULL;
		root->value = newValue;
		counter++;
		return true;
	}
	else if (counter < MaxLength)
	{
		Node *p = root;
		while (p->next!=NULL) p = p->next;
		p->next = new Node;
		p->next->value = newValue;
		p->next->next = NULL; 
		counter++;
		return true;
	}
	else return false;
}

template<class data_t>
bool GenericList<data_t>::addRange(data_t* ptr, uint16_t length)
{
	bool result = true;
	for (uint16_t i=0; i<length; i++)
	{
		result &= add(ptr[i]);
	} 
	return result;
}

template<class data_t>
bool GenericList<data_t>::addRange(const data_t* ptr, uint16_t length)
{
	bool result = true;
	for (uint16_t i=0; i<length; i++)
	{
		result &= add(ptr[i]);
	} 
	return result;
}

template<class data_t>
bool GenericList<data_t>::insertAt(uint16_t index, data_t newValue)
{
	if (index >= counter)
	{
		return add(newValue);
	}
	else if (counter < MaxLength)
	{
		uint16_t indexer = 0;
		Node *p = root;
		Node *previous = NULL;
		while (p->next!=NULL)
		{
			if (indexer == index)
			{
				if (previous == NULL)
				{
					root = new Node();
					root->value = newValue;
					root->next = p;
				}
				else
				{
					previous->next = new Node();
					previous->next->value = newValue;
					previous->next->next = p;
				}
				counter++;
				return true;
			}
			indexer++;
			previous = p;
			p = p->next;
		}
	}
	return false;
}

template<class data_t>
bool GenericList<data_t>::changeValue(uint16_t index, data_t newValue)
{
	if (counter>0 && index < counter)
	{
		uint16_t indexer = 0;
		Node *p = root;
		while (p->next!=NULL)
		{
			if (indexer == index)
			{
				p->value = newValue;
				return true;
			}
			indexer++;
			p = p->next;
		}
		p->value = newValue;
		return true;
	}
	else return false;
}

template<class data_t>	
data_t GenericList<data_t>::get(uint16_t index)
{
	if (counter>0)
	{
		int indexer = 0;
		Node *p = root;
		while (p->next!=NULL)
		{
			if (indexer == index) return p->value;
			indexer++;
			p = p->next;
		}
		return p->value;
	}
	else return 0;
}

template<class data_t>
data_t GenericList<data_t>::getLast()
{
	return get(counter-1);
}

template<class data_t>	
bool GenericList<data_t>::remove(uint16_t index)
{
	if (index < counter)
	{
		uint16_t indexer = 0;
		Node *p = root;
		Node *pr = NULL;
		while (p->next!=NULL)
		{
			if (indexer == index)
			{
				removeAt(p,pr);
				return true;
			} 
			indexer++;
			pr = p;
			p = p->next;
		}
		removeAt(p,pr);		
		return true;
	}
	else return false;
}

template<class data_t>
void GenericList<data_t>::removeLast()
{
	remove(counter-1);
}

template<class data_t>	
void GenericList<data_t>::clear()
{
	while(counter>0) remove(0);
}

template<class data_t>	
void GenericList<data_t>::reverse()
{
	data_t* array = toArray();
	uint16_t len = counter;
	for (uint16_t i=0; i<len/2; i++)
	{
		data_t tmp = array[len-i-1];
		array[len-i-1] = array[i];
		array[i] = tmp;
	}
	clear();
	addRange(array, len);
}

template<class data_t>	
void GenericList<data_t>::toArray(data_t* array, uint16_t length)
{
	uint16_t i=0;
	Node* iterator = root;
	while (i<length && iterator!=NULL) 
	{
		array[i] = iterator->value;
		iterator = iterator->next;
		i++;
	} 
	while (i<length)
	{
		array[i] = 0;
		i++;
	}
}

template<class data_t>		
data_t* GenericList<data_t>::toArray()
{
	data_t* array = new data_t[counter];
	Node* iterator = root;
	for (uint16_t i=0; i < counter; i++) 
	{
		array[i] = iterator->value;
		iterator = iterator->next;
	} 
	return array;
}

template<class data_t>		
data_t* GenericList<data_t>::toArray(data_t endValue)
{
	data_t* array = new data_t[counter+1];
	Node* iterator = root;
	for (uint16_t i=0; i < counter; i++) 
	{
		array[i] = iterator->value;
		iterator = iterator->next;
	} 
	array[counter] = endValue;
	return array;
}

template<class data_t>	
void GenericList<data_t>::sort()
{
	if (counter>0)
	{
		// Complexity O(n*log(n))
		quickRecursively(0, (uint16_t)counter-1);
	}
}

template<class data_t>	
void GenericList<data_t>::swap(uint16_t i, uint16_t j) 
{
	data_t tmp = get(i);
	changeValue(i, get(j));
	changeValue(j, tmp);
}

template<class data_t>	
void GenericList<data_t>::quickRecursively(uint16_t low, uint16_t high)
{
	if (high>counter) high=0;
	if (low < high) 
	{ 
		data_t pivot = get(high);
		uint16_t i = low - 1;   
		for (uint16_t j = low; j <= high-1; j++) 
		{ 
			if (get(j) <= pivot) 
			{ 
				i++;    
				swap(i, j); 
			} 
		} 
		i++;
		swap(i, high); 
		quickRecursively(low, i - 1); 
		quickRecursively(i + 1, high); 
	} 
}

template<class data_t>
data_t& GenericList<data_t>::operator[](uint16_t index)
{
	if (counter>0)
	{
		uint16_t indexer = 0;
		Node *p = root;
		while (p->next!=NULL)
		{
			if (indexer == index) return p->value;
			indexer++;
			p = p->next;
		}
		return p->value;
	}
	else
	{
		static data_t dummy_writable_data = 0;
		return dummy_writable_data;
	}
}

template<class data_t>
GenericList<data_t> GenericList<data_t>::clone()
{
	GenericList<data_t> tmp;
	Node* iterator = root;
	while (iterator != NULL)
	{
		tmp.add(iterator->value);
		iterator = iterator->next;
	}	
	return tmp;
}

template<class data_t>
GenericList<data_t> GenericList<data_t>::intersection(GenericList<data_t> A, GenericList<data_t> B)
{
	// if I'm not mistaken:
	// Complexity time O(n*log(n)+m*log(m)+n+m) pois cada sort O(N*log N) mais duas varreduras de cada lista. 
	// Complexity space O(n+m) devido ao uso de tmp listas.
	GenericList<data_t> result;
	GenericList<data_t> tmpA = A.clone();
	GenericList<data_t> tmpB = B.clone();
	tmpA.sort();
	tmpB.sort();
	Node* iteratorA = tmpA.root;
	Node* iteratorB = tmpB.root;
	while (iteratorA != NULL && iteratorB != NULL)
	{
		if (iteratorA->value < iteratorB->value)
		{
			iteratorA = iteratorA->next;
		}
		else if (iteratorB->value < iteratorA->value)
		{
			iteratorB = iteratorB->next;	
		}
		else
		{
			result.add(iteratorA->value);
			iteratorA = iteratorA->next;
			iteratorB = iteratorB->next;	
		}
	}
	return result;
}

