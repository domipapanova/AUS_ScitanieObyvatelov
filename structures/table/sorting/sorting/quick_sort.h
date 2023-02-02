#pragma once

#include "sort.h"
#include "../../unsorted_sequence_table.h"

namespace structures
{
	/// <summary> Triedenie Quick sort. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class QuickSort : public Sort<K, T>
	{
	public:
		/// <summary> Utriedi tabulku triedenim Quick sort. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		void sort(UnsortedSequenceTable<K, T>& table) override;
	private:
		void quick(int min, int max);
		UnsortedSequenceTable<K, T>* table_;
	};

	template<typename K, typename T>
	inline void QuickSort<K, T>::sort(UnsortedSequenceTable<K, T>& table)
	{
		quick(0, table.size() - 1);
	}

	template<typename K, typename T>
	inline void QuickSort<K, T>::quick(int min, int max)
	{
		if (table_->size()!=0) {
			int leftIndex = min;
			int rightIndex = max;
			int middleIndex = (min + max) / 2;
			K* pivot = table_->getItemAtIndex(middleIndex).getKey();

			do {

				while (table_->getItemAtIndex(leftIndex).getKey() < pivot) {
					leftIndex++;
				}
				while (table_->getItemAtIndex(rightIndex).getKey() > pivot) {
					leftIndex++;
				}
				if (leftIndex <= rightIndex) {
					Utils::swap(leftIndex, rightIndex);
					leftIndex++;
					rightIndex--;
				}
			} while (leftIndex <= rightIndex);
			if (min < rightIndex) {
				quick(min, rightIndex)
			}
			if (rightIndex < max) {
				quick(leftIndex, max);
			}


		}
	}
	
}