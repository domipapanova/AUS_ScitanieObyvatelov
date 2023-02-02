#pragma once

#include "binary_search_tree.h"
#include <random>

namespace structures
{
	/// <summary> Prvok treap-u. </summary>
	/// <typeparam name = "K"> Kluc prvku. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v prvku. </typepram>
	template <typename K, typename T>
	class TreapItem : public TableItem<K, T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		/// <param name = "key"> Kluc prvku. </param>
		/// <param name = "data"> Data, ktore uchovava. </param>
		/// <param name = "priority"> Priorita. </param>
		TreapItem(K key, T data, int priority);

		/// <summary> Getter atributu priorita. </summary>
		/// <returns> Priorita. </returns>
		int getPriority();

		/// <summary> Nastavi minimalnu prioritu. </summary>
		void minimizePriority();
	private:
		/// <summary> Kluc prvku. </summary>
		int priority_;
	};

	/// <summary> Treap. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class Treap : public BinarySearchTree<K, T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		Treap();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Treap, z ktoreho sa prevezmu vlastnosti. </param>
		Treap(Treap<K, T>& other);

		/// <summary> Destruktor. </summary>
		~Treap();

		/// <summary> Porovnanie struktur. </summary>
		/// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
		/// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
		Structure& assign(Structure& other) override;

		/// <summary> Porovnanie struktur. </summary>
		/// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
		/// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
		bool equals(Structure& other) override;

		/// <summary> Vlozi data s danym klucom do tabulky. </summary>
		/// <param name = "key"> Kluc vkladanych dat. </param>
		/// <param name = "data"> Vkladane data. </param>
		/// <exception cref="std::logic_error"> Vyhodena, ak tabulka uz obsahuje data s takymto klucom. </exception>
		void insert(const K& key, const T& data) override;

		/// <summary> Odstrani z tabulky prvok s danym klucom. </summary>
		/// <param name = "key"> Kluc prvku. </param>
		/// <returns> Odstranene data. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak tabulka neobsahuje data s takymto klucom. </exception>
		T remove(const K& key) override;

	private:
		/// <summary> Generator nahodnej priority. </summary>
		std::default_random_engine* generator_;

		/// <summary> Skontroluje, ci je haldove usporiadanie prvkov okolo vrcholu OK. </summary>
		/// <param name = "node"> Vrchol, ktoreho susedstvo sa kontroluje. </param>
		/// <returns> true, ak je haldove usporiadanie prvkov okolo vrcholu OK, false inak. </returns>
		bool isHeapOK(BinarySearchTree<K, T>::BSTTreeNode* node);

		/// <summary> Vytiahne prioritu z vrcholu stromu. </summary>
		/// <param name = "node"> Vrchol, ktoreho priorita ma byt zistena. </param>
		/// <returns> Priorita vrcholu. Ak je vrchol nullptr, vrati -1. </returns>
		int extractPriority(BinarySearchTree<K, T>::BSTTreeNode* node);

		/// <summary> Spravi lavu rotaciu vrchola okolo otca. </summary>
		/// <param name = "node"> Vrchol, ktory sa bude rotovat. </param>
		/// <remarks>
		/// Musi byt pravym synom otca!
		/// Zaujme miesto svojho otca.
		/// Otec sa stane lavym synom tohto vrchola.
		/// Potencialny lavy syn tohto vrchola sa stane pravym synom otca.
		/// </remarks>
		void rotateLeftOverParent(BinarySearchTree<K, T>::BSTTreeNode* node);

		/// <summary> Spravi pravu rotaciu vrchola okolo otca. </summary>
		/// <param name = "node"> Vrchol, ktory sa bude rotovat. </param>
		/// <remarks>
		/// Musi byt lavym synom otca!
		/// Zaujme miesto svojho otca.
		/// Otec sa stane pravym synom tohto vrchola.
		/// Potencialny pravy syn tohto vrchola sa stane lavym synom otca.
		/// </remarks>
		void rotateRightOverParent(BinarySearchTree<K, T>::BSTTreeNode* node);
	};

	template<typename K, typename T>
	inline TreapItem<K, T>::TreapItem(K key, T data, int priority):
		TableItem<K, T>(key, data),
		priority_(priority)
	{
	}

	template<typename K, typename T>
	inline int TreapItem<K, T>::getPriority()
	{
		return priority_;
	}

	template<typename K, typename T>
	inline void TreapItem<K, T>::minimizePriority()
	{
		priority_ = INT_MAX;
	}

	template<typename K, typename T>
	inline Treap<K, T>::Treap() :
		BinarySearchTree<K, T>(),
		generator_(new std::default_random_engine())
	{
	}

	template<typename K, typename T>
	inline Treap<K, T>::Treap(Treap<K, T>& other) :
		Treap()
	{
		assign(other);
	}

	template<typename K, typename T>
	inline Treap<K, T>::~Treap()
	{
		//TODO 10: Treap
	}

	template<typename K, typename T>
	inline Structure& Treap<K, T>::assign(Structure& other)
	{
		//TODO 10: Treap
		throw std::runtime_error("Treap<K, T>::assign: Not implemented yet.");
	}

	template<typename K, typename T>
	inline bool Treap<K, T>::equals(Structure& other)
	{
		return Table<K, T>::equalsTable(dynamic_cast<Treap<K, T>*>(&other));
	}

	template<typename K, typename T>
	inline void Treap<K, T>::insert(const K& key, const T& data)
	{
		//TODO 10: Treap
		throw std::runtime_error("Treap<K, T>::insert: Not implemented yet.");
	}

	template<typename K, typename T>
	inline T Treap<K, T>::remove(const K& key)
	{
		//TODO 10: Treap
		throw std::runtime_error("Treap<K, T>::remove: Not implemented yet.");
	}

	template<typename K, typename T>
	inline bool Treap<K, T>::isHeapOK(BinarySearchTree<K, T>::BSTTreeNode* node)
	{
		//TODO 10: Treap
		throw std::runtime_error("Treap<K, T>::isHeapOK: Not implemented yet.");
	}

	template<typename K, typename T>
	inline int Treap<K, T>::extractPriority(BinarySearchTree<K, T>::BSTTreeNode * node)
	{
		//TODO 10: Treap
		throw std::runtime_error("Treap<K, T>::extractPriority: Not implemented yet.");
	}

	template<typename K, typename T>
	inline void Treap<K, T>::rotateLeftOverParent(BinarySearchTree<K, T>::BSTTreeNode * node)
	{
		//TODO 10: Treap
		throw std::runtime_error("Treap<K, T>::rotateLeftOverParent: Not implemented yet.");
	}

	template<typename K, typename T>
	inline void Treap<K, T>::rotateRightOverParent(BinarySearchTree<K, T>::BSTTreeNode * node)
	{
		//TODO 10: Treap
		throw std::runtime_error("Treap<K, T>::rotateRightOverParent: Not implemented yet.");
	}
}