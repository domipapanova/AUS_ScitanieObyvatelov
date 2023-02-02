#pragma once

#include "../structure.h"

namespace structures
{
	/// <summary> Matica. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v matici. </typepram>
	template<typename T>
	class Matrix
		: public Structure
	{
	public:
		/// <summary> Vrati pocet riadkov matice. </summary>
		/// <returns> Pocet riadkov matice. </returns>
		virtual size_t getRowCount() = 0;

		/// <summary> Vrati pocet stlpcov matice. </summary>
		/// <returns> Pocet stlpcov matice. </returns>
		virtual size_t getColumnCount() = 0;

		/// <summary> Vrati odkaz na prvok v danom riadku a stlpci. </summary>
		/// <param name="rowIndex"> Index riadku. </param>
		/// <param name="columnIndex"> Index stlpca. </param>
		/// <returns> Odkaz na prvok na danych indexoch. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index riadku alebo stlpca nepatri do matice. </exception>
		virtual T& at(int rowIndex, int columnIndex) = 0;
	};
}