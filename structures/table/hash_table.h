#pragma once

#include "table.h"
#include "linked_table.h"
#include "../array/array.h"
#include "../structure_iterator.h"
#include <stdexcept>

namespace structures
{

	/// <summary> Hashovacia tabulka. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class HashTable : public Table<K, T>
	{
	private:
		static const int DATA_ARRAY_SIZE = 100;

	public:
		/// <summary> Konstruktor. </summary>
		HashTable();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> HashTable, z ktorej sa prevezmu vlastnosti. </param>
		HashTable(HashTable<K, T>& other);

		/// <summary> Destruktor. </summary>
		~HashTable();

		/// <summary> Vrati pocet prvkov v tabulke. </summary>
		/// <returns> Pocet prvkov v tabulke. </returns>
		size_t size() override;

		/// <summary> Porovnanie struktur. </summary>
		/// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
		/// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
		Structure& assign(Structure& other) override;

		/// <summary> Porovnanie struktur. </summary>
		/// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
		/// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
		bool equals(Structure& other) override;

		/// <summary> Vrati adresou data s danym klucom. </summary>
		/// <param name = "key"> Kluc dat. </param>
		/// <returns> Adresa dat s danym klucom. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak kluc nepatri do tabulky. </exception>
		T& find(const K& key) override;

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

		/// <summary> Bezpecne ziska data s danym klucom. </summary>
		/// <param name = "key"> Kluc dat. </param>
		/// <param name = "data"> Najdene data (vystupny parameter). </param>
		/// <returns> true, ak sa podarilo najst a naplnit data s danym klucom, false inak. </returns>
		bool tryFind(const K& key, T& data) override;

		/// <summary> Zisti, ci tabulka obsahuje data s danym klucom. </summary>
		/// <param name = "key"> Kluc dat. </param>
		/// <returns> true, tabulka obsahuje dany kluc, false inak. </returns>
		bool containsKey(const K& key) override;

		/// <summary> Vymaze tabulku. </summary>
		void clear() override;

		/// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
		/// <returns> Iterator na zaciatok struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<TableItem<K, T>*>* getBeginIterator() override;

		/// <summary> Vrati skutocny iterator na koniec struktury </summary>
		/// <returns> Iterator na koniec struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<TableItem<K, T>*>* getEndIterator() override;

	protected:
		/// <summary> Pole s datami. </summary>
		Array<Table<K, T>*>* data_;
		/// <summary> Pocet prvkov v binarnom vyhladavacom strome. </summary>
		size_t size_;

	private:
		/// <summary> Hashovacia funkcia zahashuje kluc na indexu v poli dat. </summary>
		/// <param name = "key"> Kluc dat. </param>
		/// <returns> Index do pola dat, ktory vznikol zahashovanim kluca. </returns>
		int hashFunction(K key);

	private:
		/// <summary> Iterator pre HashTable. </summary>
		class HashTableIterator : public Iterator<TableItem<K, T>*>
		{
		public:
			/// <summary> Konstruktor. </summary>
			/// <param name = "hashTable"> Hashovacia tabulka, cez ktoru iteruje. </param>
			/// <param name = "position"> Pozicia, na ktorej zacina. </param>
			HashTableIterator(HashTable<K, T>* hashTable, int position);

			/// <summary> Destruktor. </summary>
			~HashTableIterator();

			/// <summary> Operator priradenia. Priradi do seba hodnotu druheho iteratora. </summary>
			/// <param name = "other"> Druhy iterator. </param>
			/// <returns> Vrati seba po priradeni. </returns>
			Iterator<TableItem<K, T>*>& operator=(Iterator<TableItem<K, T>*>& other) override;

			/// <summary> Porovna sa s druhym iteratorom na nerovnost. </summary>
			/// <param name = "other"> Druhy iterator. </param>
			/// <returns> True, ak sa iteratory nerovnaju, false inak. </returns>
			bool operator!=(Iterator<TableItem<K, T>*>& other) override;

			/// <summary> Vrati data, na ktore aktualne ukazuje iterator. </summary>
			/// <returns> Data, na ktore aktualne ukazuje iterator. </returns>
			TableItem<K, T>* operator*() override;

			/// <summary> Posunie iterator na dalsi prvok v strukture. </summary>
			/// <returns> Iterator na dalsi prvok v strukture. </returns>
			/// <remarks> Zvycajne vrati seba. Ak vrati iny iterator, povodny bude automaticky zruseny. </remarks>
			Iterator<TableItem<K, T>*>& operator++() override;

		private:
			/// <summary> Hashovacia tabulka, cez ktoru iteruje. </summary>
			HashTable<K, T>* hashTable_;
			/// <summary> Aktualna pozicia v poli v tabulke. </summary>
			int position_;
			/// <summary> Aktualmy iterator preplnovacej tabulky v poli. </summary>
			Iterator<TableItem<K, T>*>* iterCurr_;
			/// <summary> Koncovy iterator preplnovacej tabulky v poli. </summary>
			Iterator<TableItem<K, T>*>* iterLast_;

			/// <summary>
			/// Zmeni hodnotu v atribute position_ na najblizsiu preplnovaciu tabulku v poli tabuliek.
			/// Ak sa taka tabulka najde, nastavi iterCurr_ a iterLast_.
			/// </summary>
			void movePositionInArray();
		};
	};

	template<typename K, typename T>
	inline HashTable<K, T>::HashTable():
		Table<K, T>(),
		data_(new Array<Table<K, T>*>(DATA_ARRAY_SIZE)),
		size_(0)
	{
	}

	template<typename K, typename T>
	inline HashTable<K, T>::HashTable(HashTable<K, T>& other):
		HashTable()
	{
		assign(other);
	}

	template<typename K, typename T>
	inline HashTable<K, T>::~HashTable()
	{
		//TODO 08: HashTable
	}

	template<typename K, typename T>
	inline size_t HashTable<K, T>::size()
	{
		//TODO 08: HashTable
		throw std::runtime_error("HashTable<K, T>::size: Not implemented yet.");
	}

	template<typename K, typename T>
	inline Structure& HashTable<K, T>::assign(Structure& other)
	{
		//TODO 08: HashTable
		throw std::runtime_error("HashTable<K, T>::assign: Not implemented yet.");
	}

	template<typename K, typename T>
	inline bool HashTable<K, T>::equals(Structure& other)
	{
		return Table<K, T>::equalsTable(dynamic_cast<HashTable<K, T>*>(&other));
	}

	template<typename K, typename T>
	inline T& HashTable<K, T>::find(const K& key)
	{
		//TODO 08: HashTable
		throw std::runtime_error("HashTable<K, T>::find: Not implemented yet.");
	}

	template<typename K, typename T>
	inline void HashTable<K, T>::insert(const K& key, const T& data)
	{
		//TODO 08: HashTable
		throw std::runtime_error("HashTable<K, T>::insert: Not implemented yet.");
	}

	template<typename K, typename T>
	inline T HashTable<K, T>::remove(const K& key)
	{
		//TODO 08: HashTable
		throw std::runtime_error("HashTable<K, T>::remove: Not implemented yet.");
	}

	template<typename K, typename T>
	inline bool HashTable<K, T>::tryFind(const K& key, T & data)
	{
		//TODO 08: HashTable
		throw std::runtime_error("HashTable<K, T>::tryFind: Not implemented yet.");
	}

	template<typename K, typename T>
	inline bool HashTable<K, T>::containsKey(const K& key)
	{
		//TODO 08: HashTable
		throw std::runtime_error("HashTable<K, T>::containsKey: Not implemented yet.");
	}

	template<typename K, typename T>
	inline void HashTable<K, T>::clear()
	{
		//TODO 08: HashTable
		throw std::runtime_error("HashTable<K, T>::clear: Not implemented yet.");
	}

	template<typename K, typename T>
	inline Iterator<TableItem<K, T>*>* HashTable<K, T>::getBeginIterator()
	{
		return new HashTableIterator(this, 0);
	}

	template<typename K, typename T>
	inline Iterator<TableItem<K, T>*>* HashTable<K, T>::getEndIterator()
	{
		return new HashTableIterator(this, static_cast<int>(DATA_ARRAY_SIZE));
	}

	template<typename K, typename T>
	inline int HashTable<K, T>::hashFunction(K key)
	{
		// Knuth Variant on Division: h(k) = k(k + 3) mod m.
		return (key * (key + 3)) % DATA_ARRAY_SIZE;
	}

	template<typename K, typename T>
	inline HashTable<K, T>::HashTableIterator::HashTableIterator(HashTable<K, T>* hashTable, int position):
		Iterator<TableItem<K, T>*>(),
		hashTable_(hashTable),
		position_(position),
		iterCurr_(nullptr),
		iterLast_(nullptr)
	{
		movePositionInArray();
	}

	template<typename K, typename T>
	inline HashTable<K, T>::HashTableIterator::~HashTableIterator()
	{
		//TODO 08: HashTable<K, T>::HashTableIterator
	}

	template<typename K, typename T>
	inline Iterator<TableItem<K, T>*>& HashTable<K, T>::HashTableIterator::operator=(Iterator<TableItem<K, T>*>& other)
	{
		//TODO 08: HashTable<K, T>::HashTableIterator
		throw std::runtime_error("HashTable<K, T>::HashTableIterator::operator=: Not implemented yet.");
	}

	template<typename K, typename T>
	inline bool HashTable<K, T>::HashTableIterator::operator!=(Iterator<TableItem<K, T>*>& other)
	{
		//TODO 08: HashTable<K, T>::HashTableIterator
		throw std::runtime_error("HashTable<K, T>::HashTableIterator::operator!=: Not implemented yet.");
	}

	template<typename K, typename T>
	inline TableItem<K, T>* HashTable<K, T>::HashTableIterator::operator*()
	{
		//TODO 08: HashTable<K, T>::HashTableIterator
		throw std::runtime_error("HashTable<K, T>::HashTableIterator::operator*: Not implemented yet.");
	}

	template<typename K, typename T>
	inline Iterator<TableItem<K, T>*>& HashTable<K, T>::HashTableIterator::operator++()
	{
		//TODO 08: HashTable<K, T>::HashTableIterator
		throw std::runtime_error("HashTable<K, T>::HashTableIterator::operator++: Not implemented yet.");
	}

	template<typename K, typename T>
	inline void HashTable<K, T>::HashTableIterator::movePositionInArray()
	{
		//TODO 08: HashTable<K, T>::HashTableIterator
		throw std::runtime_error("HashTable<K, T>::HashTableIterator::movePositionInArray: Not implemented yet.");
	}

}