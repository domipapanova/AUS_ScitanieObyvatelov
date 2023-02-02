#pragma once

#include "../list/array_list.h"
#include "sequence_table.h"

namespace structures
{

	/// <summary> Utriedena sekvencna tabulka. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class SortedSequenceTable : public SequenceTable<K, T>
	{
		//Na semestralku TAB.SEKV.UTRIED.ARRAYlIST, KEY-STRING
	public:
		/// <summary> Konstruktor. </summary>
		SortedSequenceTable();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> SortedSequenceTable, z ktorej sa prevezmu vlastnosti. </param>
		SortedSequenceTable(SortedSequenceTable<K, T>& other);

		/// <summary> Priradenie struktury. </summary>
		/// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
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

		//<summary> Vlozi data s danym klucom do tabulky. AK sa operacia podari vrati true, ak nie vrati false; 
		bool insertBool(const K& key, const T& data);

	protected:
		/// <summary> Najde prvok tabulky s danym klucom. </summary>
		/// <param name = "key"> Hladany kluc. </param>
		/// <returns> Prvok tabulky s danym klucom, ak neexistuje, vrati nullptr. </returns>
		TableItem<K, T>* findTableItem(const K& key) override;

	private:
		/// <summary> Najde index prvku s danym klucom. Kontroluje rozsah [indexStart, indexEnd). Pracuje na principe bisekcie. </summary>
		/// <param name = "key"> Hladany kluc. </param>
		/// <param name = "indexStart"> Pociatocny index prehladavanej sekvencie. </param>
		/// <param name = "indexEnd"> Koncovy index prehladavanej sekvencie. </param>
		/// <param name = "found"> Vystupny parameter, ktory indikuje, ci sa kluc nasiel. </param>
		/// <returns> Index prvku s danym klucom. Ak sa kluc v tabulke nenachadza, vrati index, kde by sa mal prvok s takym klucom nachadzat. </returns>
		int indexOfKey(K key, int indexStart, int indexEnd, bool& found);
	};

	template<typename K, typename T>
	inline SortedSequenceTable<K, T>::SortedSequenceTable() :
		SequenceTable<K, T>(new ArrayList<TableItem<K, T>*>())
	{
	}

	template<typename K, typename T>
	inline SortedSequenceTable<K, T>::SortedSequenceTable(SortedSequenceTable<K, T>& other) :
		SortedSequenceTable()
	{
		assign(other);
	}

	template<typename K, typename T>
	inline Structure& SortedSequenceTable<K, T>::assign(Structure& other)
	{
		return SequenceTable<K, T>::assignSequenceTable(dynamic_cast<SortedSequenceTable<K, T>&>(other));
	}

	template<typename K, typename T>
	inline bool SortedSequenceTable<K, T>::equals(Structure& other)
	{
		return Table<K, T>::equalsTable(dynamic_cast<SortedSequenceTable<K, T>*>(&other));
	}

	template<typename K, typename T>
	inline void SortedSequenceTable<K, T>::insert(const K& key, const T& data)
	{

		bool found = false;
		int index = indexOfKey(key, 0, this->size() - 1, found);

		if (!found) { // ked sme si isty ze kluc je unikatny mozme obist kontrolu
			SequenceTable<K, T>::list_->insert(new TableItem<K, T>(key, data),index);
		}
		else {
			throw std::logic_error("table alredy contains a key");
		}
	}

	template<typename K, typename T>
	inline bool SortedSequenceTable<K, T>::insertBool(const K& key, const T& data)
	{

		bool found = false;
		int index = indexOfKey(key, 0, this->size() - 1, found);

		if (!found) { // ked sme si isty ze kluc je unikatny mozme obist kontrolu
			SequenceTable<K, T>::list_->insert(new TableItem<K, T>(key, data), index);
			return true;
		}
		else {
			return false;
		}
	}

	template<typename K, typename T>
	inline TableItem<K, T>* SortedSequenceTable<K, T>::findTableItem(const K& key)
	{
		bool found = false;
		int index = indexOfKey(key, 0, this->size() - 1, found);

		return found ? SequenceTable<K, T>::list_->at(index) : nullptr;
	}

	template<typename K, typename T>
	inline int SortedSequenceTable<K, T>::indexOfKey(K key, int indexStart, int indexEnd, bool& found)
	{
		//TODO 08: SortedSequenceTable
		// TABULKA - THIS
		//KLUC - BISEKCIA < KLUC - RETURN INDEX + 1
		//MAT FUNKCNY BIANRNY STROM"||||\
		throw std::runtime_error("SortedSequenceTable<K, T>::indexOfKey: Not implemented yet.");
		if (indexEnd == -1) {
			found = false;
			return 0;
		}

	/*	if (indexStart == SequenceTable<K, T>::size()) {
			found = false;
			return indexStart;
		}*/
		int indexMiddle = (indexStart + indexEnd) / 2;
		//K keyMiddle = (*list_)[indexMiddle]->getKey();
		K keyMiddle = SortedSequenceTable<K, T>::list_->at(indexMiddle)->getKey();

		if (keyMiddle == key) {
			found = true;
			return indexMiddle;
		}
		else {
			if (indexStart == indexEnd) {
				found = false;
				return key < keyMiddle ? indexMiddle : indexMiddle + 1;
			}
			else {
				if (keyMiddle < key) {
					indexStart = indexMiddle + 1;
				}
				else {
					indexEnd = indexMiddle;// -1
				}
				return indexOfKey(key, indexStart, indexEnd, found);
			}
		}
	}
	
}