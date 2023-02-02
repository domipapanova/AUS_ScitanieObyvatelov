#pragma once

#include "../data_item.h"
#include "../structure.h"
#include "../structure_iterator.h"
#include "../heap_monitor.h"

namespace structures
{
	/// <summary> Prvok tabulky. </summary>
	/// <typeparam name = "K"> Kluc prvku. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v prvku. </typepram>
	template <typename K, typename T>
	class TableItem : public DataItem<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		/// <param name = "key"> Kluc prvku. </param>
		/// <param name = "data"> Data, ktore uchovava. </param>
		TableItem(const K& key, const T& data);

		/// <summary> Getter atributu kluc. </summary>
		/// <returns> Kluc. </returns>
		K getKey();

	private:
		/// <summary> Kluc prvku. </summary>
		K key_;
	};

	/// <summary> Tabulka. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class Table : public Structure, public Iterable<TableItem<K, T>*>
	{
	public:
		/// <summary> Vymaze tabulku. </summary>
		virtual void clear() = 0;

		/// <summary> Vrati adresou data s danym klucom. </summary>
		/// <param name = "key"> Kluc dat. </param>
		/// <returns> Adresa dat s danym klucom. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak kluc nepatri do tabulky. </exception>
		//virtual T& operator[](const K key) = 0;
		virtual T& find(const K& key) = 0;

		/// <summary> Vlozi data s danym klucom do tabulky. </summary>
		/// <param name = "key"> Kluc vkladanych dat. </param>
		/// <param name = "data"> Vkladane data. </param>
		/// <exception cref="std::logic_error"> Vyhodena, ak tabulka uz obsahuje data s takymto klucom. </exception>
		virtual void insert(const K& key, const T& data) = 0;

		/// <summary> Odstrani z tabulky prvok s danym klucom. </summary>
		/// <param name = "key"> Kluc prvku. </param>
		/// <returns> Odstranene data. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak tabulka neobsahuje data s takymto klucom. </exception>
		virtual T remove(const K& key) = 0;

		/// <summary> Bezpecne ziska data s danym klucom. </summary>
		/// <param name = "key"> Kluc dat. </param>
		/// <param name = "data"> Najdene data (vystupny parameter). </param>
		/// <returns> true, ak sa podarilo najst a naplnit data s danym klucom, false inak. </returns>
		virtual bool tryFind(const K& key, T& value) = 0;

		/// <summary> Zisti, ci tabulka obsahuje data s danym klucom. </summary>
		/// <param name = "key"> Kluc dat. </param>
		/// <returns> true, tabulka obsahuje dany kluc, false inak. </returns>
		virtual bool containsKey(const K& key) = 0;

	protected:
		/// <summary> Porovnanie struktur. Pomocna metoda, ktora prebera pointer, ktoru posle potomok. </summary>
		/// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
		/// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
		bool equalsTable(Table<K, T>* other);
	};

	template<typename K, typename T>
	inline TableItem<K, T>::TableItem(const K& key, const T& data) :
		DataItem<T>(data),
		key_(key)
	{
	}

	template<typename K, typename T>
	inline K TableItem<K, T>::getKey()
	{
		return key_;
	}

	template<typename K, typename T>
	inline bool Table<K, T>::equalsTable(Table<K, T>* other)
	{
		if (other == nullptr)
		{
			return false;
		}

		for (TableItem<K, T>* otherItem : *other)
		{
			T data;
			bool found = this->tryFind(otherItem->getKey(), data);
			if (!found)
			{
				return false;
			}

			if (data != otherItem->accessData())
			{
				return false;
			}
		}
		return true;
	}
}

