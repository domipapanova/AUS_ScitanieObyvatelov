#pragma once

#include "sort.h"
#include "../../unsorted_sequence_table.h"
#include <random>
#include <chrono>

namespace structures
{
	/// <summary> Pomiesa prvky v tabulke. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class Shuffle : public Sort<K, T>
	{
	public:
		/// <summary> Pomiesa prvky v tabulke. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		void sort(UnsortedSequenceTable<K, T>& table) override;
	};

	template<typename K, typename T>
	inline void Shuffle<K, T>::sort(UnsortedSequenceTable<K, T>& table)
	{
		int size = static_cast<int>(table.size());
		auto seed = std::random_device()();
		std::default_random_engine generator(seed);
		std::uniform_int_distribution<int> uniform(0, size - 1);

		for (int i = 0; i < size * 2; i++)
		{
			table.swap(uniform(generator), uniform(generator));
		}
	}

}