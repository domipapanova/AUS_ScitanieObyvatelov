#pragma once

#include "sort.h"
#include "../../unsorted_sequence_table.h"

namespace structures
{
	/// <summary> Triedenie Radix sort. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class RadixSort : public Sort<K, T>
	{
	public:
		/// <summary> Utriedi tabulku triedenim Radix sort. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		void sort(UnsortedSequenceTable<K, T>& table) override;
	};

	template<typename K, typename T>
	inline void RadixSort<K, T>::sort(UnsortedSequenceTable<K, T>& table)
	{
		throw std::logic_error("Not implemented yet!");
	}

}