#pragma once

#include "sort.h"
#include "../../unsorted_sequence_table.h"
//do sorrtera atribut vzostupne alebo zostupne a atribut kriterium oidka jr sa bude triedit

namespace structures
{
	/// <summary> Triedenie Bubble sort. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class BubbleSort : public Sort<K, T>
	{
	public:
		/// <summary> Utriedi tabulku triedenim Bubble sort. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		void sort(UnsortedSequenceTable<K, T>& table) override;
	};

	template<typename K, typename T>
	inline void BubbleSort<K, T>::sort(UnsortedSequenceTable<K, T>& table)
	{
		throw std::logic_error("Not implemented yet!");
	}

}