#pragma once

#include "TeritorialUnit.h"
#include "../structures/table/unsorted_sequence_table.h"
#include  "Criterion/Criterion.h"

namespace structures
{
	/// <summary> Triedenie Quick sort. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename C, typename ObjectType, typename ResultType>
	class QuickSort 
	{
	public:
		/// <summary> Utriedi tabulku triedenim Quick sort. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		void sort(UnsortedSequenceTable< ResultType, ObjectType*>& table, Criterion<ObjectType,C>* criterion, bool asc);
		~QuickSort();
	private:
		void quick(int min, int max, Criterion<ObjectType, C>* criterion, bool asc);
		UnsortedSequenceTable<ResultType,ObjectType*>* table_;
		Criterion<ObjectType, C>* criterion_;
	};

	template<typename C, typename ObjectType, typename ResultType>
	inline void QuickSort<C, ObjectType, ResultType>::sort(UnsortedSequenceTable< ResultType, ObjectType*>& table, Criterion<ObjectType, C>* criterion, bool asc)
	{
		table_ = &table;
		criterion_ = criterion;
		quick(0, table_->size() - 1, criterion, asc);
	}

	template<typename C, typename ObjectType, typename ResultType>
	inline QuickSort<C, ObjectType, ResultType>::~QuickSort()
	{
		table_ = nullptr;
		delete criterion_;
	}

	template<typename C, typename ObjectType, typename ResultType>
	inline void QuickSort<C, ObjectType, ResultType>::quick(int min, int max, Criterion<ObjectType, C>* criterion, bool asc)
	{
		if (table_->size() != 0) {
			if (asc) {
				int leftIndex = min;
				int rightIndex = max;
				int middleIndex = (min + max) / 2;
				C pivot = (criterion->evaluate(dynamic_cast<ObjectType&>(*table_->getItemAtIndex(middleIndex).accessData())));
				do {

					while (criterion->evaluate(dynamic_cast<ObjectType&>(*table_->getItemAtIndex(leftIndex).accessData())) < pivot) {
						leftIndex++;
					}
					while (criterion->evaluate(dynamic_cast<ObjectType&>(*table_->getItemAtIndex(rightIndex).accessData())) > pivot) {
						rightIndex--;
					}
					if (leftIndex <= rightIndex) {
						table_->swap(leftIndex, rightIndex);
						leftIndex++;
						rightIndex--;
					}
				} while (leftIndex <= rightIndex);

				if (min < rightIndex) {
					quick(min, rightIndex, criterion, true);
				}

				if (leftIndex < max) {

					quick(leftIndex, max, criterion, true);
				}
			}
			else
			{
				int leftIndex = min;
				int rightIndex = max;
				int middleIndex = min + (max - min) / 2;
				C pivot = (criterion->evaluate(dynamic_cast<ObjectType&>(*table_->getItemAtIndex(middleIndex).accessData())));
				do {

					while (criterion->evaluate(dynamic_cast<ObjectType&>(*table_->getItemAtIndex(leftIndex).accessData())) > pivot) {
						leftIndex++;
					}
					while (criterion->evaluate(dynamic_cast<ObjectType&>(*table_->getItemAtIndex(rightIndex).accessData())) < pivot) {
						rightIndex--;
					}
					if (leftIndex <= rightIndex) {
						table_->swap(leftIndex, rightIndex);
						leftIndex++;
						rightIndex--;
					}
				} while (leftIndex <= rightIndex);

				if (min < rightIndex) {
					quick(min, rightIndex, criterion, false);
				}

				if (leftIndex < max) {

					quick(leftIndex, max, criterion, false);
				}
			}
		}
	
	}
	
}