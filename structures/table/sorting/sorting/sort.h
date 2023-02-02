#pragma once

#include "../../unsorted_sequence_table.h"

namespace structures
{
	/// <summary> Triedenie NonortedSequenceTable navrhnuté ako funkèný objekt. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class Sort
	{
	public:
		/// <summary> Destruktor. </summary>
		virtual ~Sort();

		/// <summary> Funkcny operator utriedi tabulku. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		/// <remarks> Využíva metódu sort. </remarks>
		void operator()(UnsortedSequenceTable<K, T>& table);

		/// <summary> Utriedi utriedi tabulku. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		virtual void sort(UnsortedSequenceTable<K, T>& table) = 0;
	};

	template<typename K, typename T>
	inline Sort<K, T>::~Sort()
	{
	}

	template<typename K, typename T>
	inline void Sort<K, T>::operator()(UnsortedSequenceTable<K, T>& table)
	{
		this->sort(table);
	}
}