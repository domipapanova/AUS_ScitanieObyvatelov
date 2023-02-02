#pragma once

#include "matrix.h"
#include <stdexcept>
#include "../array/array.h"
#include "../../structures/heap_monitor.h"


namespace structures
{
	/// <summary> Implementacia matice v nesuvislej pamati. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v matici. </typepram>
	template<typename T>
	class IncoherentMatrix
		: public Matrix<T>
	{
		Array<Array<T>*>* matrix_;
		size_t rowCount_;
		size_t columnCount_;

	public:
		/// <summary>
		///	Konstruktor. Vytvori maticu o danom pocte riadkov a stlpcov.
		/// Polozky su inicializovane na "nulovu" hodnotu typu T.
		/// </summary>
		/// <param name="rowCount"> Pocet riadkov. </param>
		/// <param name="columnCount"> Pocet stlpcov. </param>
		IncoherentMatrix(size_t rowCount, size_t columnCount);

		/// <summary> Inicializuje tuto maticu ako kopiu matice odovzdanej ako parameter. </summary>
		/// <param name = "other"> Odkaz na maticu, z ktorej sa prevezmu vlastnosti. </param>
		IncoherentMatrix(IncoherentMatrix& other);

		/// <summary> Destruktor. </summary>
		~IncoherentMatrix();

		/// <summary>
		/// Ak je to mozne (parametrom je matica, ktora ma rovnake rozmery ako ako aktualna matica),
		/// tak skopiruje vlastnosti z matice odovzdanej ako parameter.
		/// Ak to nie je mozne, vyhodi sa vynimka.
		/// </summary>
		/// <param name = "other"> Odkaz na strukturu, z ktorej maju prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary>
		/// Ak je parametrom matica a obsah porovnavanych matic je rovnaky,
		/// tak vrati hodnotu true. V opacnom pripade vrati hodnotu false.
		/// </summary>
		/// <param name="other"> Odkaz na strukturu, s ktorou sa ma tato matica porovnat. </param>
		/// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
		bool equals(Structure& other) override;

		/// <summary> Pocet vsetkych prvkov v matici. </summary>
		/// <returns> Pocet prvkov v matici. </returns>
		size_t size() override;

		/// <summary> Vrati pocet riadkov v matici. </summary>
		/// <returns> Pocet riadkov matice. </returns>
		size_t getRowCount() override;

		/// <summary> Vrati pocet stlpcov matice. </summary>
		/// <returns> Pocet stlpcov matice. </returns>
		size_t getColumnCount() override;

		/// <summary> Vrati odkaz na prvok v danom riadku a stlpci. </summary>
		/// <param name="rowIndex"> Index riadku. </param>
		/// <param name="columnIndex"> Index stlpca. </param>
		/// <returns> Odkaz na prvok na danych indexoch. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index riadku alebo stlpca nepatri do matice. </exception>
		T& at(int rowIndex, int columnIndex) override;
	};

	template<typename T>
	inline IncoherentMatrix<T>::IncoherentMatrix(size_t rowCount, size_t columnCount) 
	{
		rowCount_ = rowCount;
		columnCount_ = columnCount;
		matrix_ = new Array<Array<T>*>(rowCount);
		for (size_t i = 0; i < rowCount_; i++)
		{
			matrix_->at(i) = new Array<T>(columnCount_);
		}
	}

	template<typename T>
	inline IncoherentMatrix<T>::IncoherentMatrix(IncoherentMatrix& other)
	{
		matrix_ = new Array<Array<T>*>(other.rowCount_);
		rowCount_ = other.rowCount_;
		columnCount_ = other.columnCount_;

		for (size_t i = 0; i < rowCount_; i++)
		{
			matrix_->at(i) = new Array<T>(*other.matrix_->at(i));
		}
	}

	template<typename T>
	inline IncoherentMatrix<T>::~IncoherentMatrix()
	{
		for (size_t i = 0; i < rowCount_; i++)
		{
			delete matrix_->at(i);
			matrix_->at(i) = nullptr;
		}
		delete matrix_;
		matrix_ = nullptr;
		columnCount_ = 0;
		rowCount_ = 0;
	}

	template<typename T>
	inline Structure& IncoherentMatrix<T>::assign(Structure& other)
	{
		if (this != &other) {
			IncoherentMatrix<T>* otherICM = dynamic_cast<IncoherentMatrix<T>*>(&other);
			if (otherICM != nullptr) {
				for (size_t i = 0; i < rowCount_; i++)
				{
					delete matrix_->at(i);
					matrix_->at(i) = nullptr;
				}
				delete matrix_;

				rowCount_ = otherICM->rowCount_;
				columnCount_ = otherICM->columnCount_;
				matrix_ = new Array<Array<T>*>(rowCount_);
			
				for (size_t i = 0; i < rowCount_; i++)
				{
					matrix_->at(i) = new Array<T>(*(otherICM->matrix_->at(i)));
				}
			}
		}
			return *this;
	}

	template<typename T>
	inline bool IncoherentMatrix<T>::equals(Structure& other)
	{
		if (this != &other) {
			IncoherentMatrix<T>* otherICM = dynamic_cast<IncoherentMatrix<T>*>(&other);
			if (otherICM != nullptr) {
				if (otherICM->columnCount_ == columnCount_ && otherICM->rowCount_ == rowCount_) {
					for (size_t i = 0; i < rowCount_; i++)
					{
						Array<T>* row = matrix_->at(i);
						Array<T>* rowOther = otherICM->matrix_->at(i);
						if (!(row->equals(*rowOther))) {
							return false;
						}
						return true;
					}
				}
				return false;
			}
			return false;
		}
		else {
			return true;
		}
	}

	template<typename T>
	inline size_t IncoherentMatrix<T>::size()
	{
		return columnCount_ * rowCount_;
	}

	template<typename T>
	inline size_t IncoherentMatrix<T>::getRowCount()
	{
		return rowCount_;
	}

	template<typename T>
	inline size_t IncoherentMatrix<T>::getColumnCount()
	{
		return columnCount_;
	}

	template<typename T>
	inline T& IncoherentMatrix<T>::at(int rowIndex, int columnIndex)
	{
		Utils::rangeCheckExcept(rowIndex, rowCount_, "Invalid rowindex");
		Utils::rangeCheckExcept(columnIndex, columnCount_, "Invalid columnindex");
		Array<T>* row = matrix_->at(rowIndex);
		return row->at(columnIndex);

	}
}