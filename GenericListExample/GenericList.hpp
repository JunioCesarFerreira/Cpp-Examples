#ifndef GenericList_h
#define GenericList_h

#include <iostream>

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;

// Lista genérica simplificada.
template<class data_t>
class GenericList
{
	public:
		static const uint16_t MaxLength = 1024; // Número máximo de elementos que uma lista pode ter.
		
	private:
		struct Node // Estrutura de nodo da lista.
		{
			data_t value; // Valor do item.
			Node *next;   // Ponteiro para próximo item.
		};
		Node* root; // Nodo raiz da lista.
		uint32_t counter; // Contador de elementos da lista.
		
		// Remove elemento da lista mantendo estrutura vinculada da lista.
		void removeAt(Node* pointer, Node* previous);
		
		void swap(uint16_t i, uint16_t j);
		void quickRecursively(uint16_t left, uint16_t right); 
		
	public:
		// Construtor lista.
		GenericList<data_t>();
		// Destrutor lista.
		~GenericList();
		
		// Acessor do contador de elementos da lista
		inline uint16_t count()
		{ 
			return counter; 
		}
		
		data_t& operator [] (uint16_t index);
		
		// Adiciona novo elemento na lista.
		bool add(data_t newValue);
		
		// Adiciona range de elementos na lista.
		bool addRange(data_t* ptr, uint16_t length);
		bool addRange(const data_t* ptr, uint16_t length);

		// Insere na posição indicada
		bool insertAt(uint16_t index, data_t newValue);
		
		// Pega elemento na posição indicada pelo index.	
		data_t get(uint16_t index);
		
		// Pega o último elemento da lista.
		data_t getLast();
		
		// Modifica o valor do elemento na posição indicada pelo index.
		bool changeValue(uint16_t index, data_t newValue);
		
		// Remove elemento na posição indicada pelo index.
		bool remove(uint16_t index);
		
		// Remove o último elemento da lista.
		void removeLast();
		
		// Limpa a lista.
		void clear();
		
		// Inverte ordem da lista.
		void reverse();
		
		// Ordena lista
		void sort();
				
		// Clona a lista gerando uma nova instância.
		GenericList<data_t> clone();
		
		// Transfere valores da lista para array conforme indicado.
		void toArray(data_t* array, uint16_t length);
		
		// Retorna uma nova instância array da lista.
		data_t* toArray();
		
		// Retorna uma nova instância array da lista com um item finalizador indicado.
		data_t* toArray(data_t endValue);
		
		// Realiza interseção entre listas.
		static GenericList<data_t> intersection(GenericList<data_t> A, GenericList<data_t> B);
};
// Tipos permitidos.
template class GenericList<char>;
template class GenericList<short>;
template class GenericList<unsigned short>;
template class GenericList<int>;
template class GenericList<unsigned int>;
template class GenericList<long>;
template class GenericList<unsigned long>;
template class GenericList<float>;
template class GenericList<double>;


#endif


