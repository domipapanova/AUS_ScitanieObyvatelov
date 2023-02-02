#pragma once

#include "matrix.h"
#include <stdexcept>
#include "../vector/vector.h"
#include "../../structures/heap_monitor.h"


namespace structures
{
	/// <summary> Implementacia matice v suvislej pamati. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v matici. </typepram>
	template<typename T>
	class CoherentMatrix
		: public Matrix<T>
	{
	private:

		Vector* matrix_;
		size_t rowCount_;
		size_t columnCount_;
	public:
		/// <summary>
		///	Konstruktor. Vytvori maticu o danom pocte riadkov a stlpcov.
		/// Polozky su inicializovane na "nulovu" hodnotu typu T.
		/// </summary>
		/// <param name="rowCount"> Pocet riadkov. </param>
		/// <param name="columnCount"> Pocet stlpcov. </param>
		CoherentMatrix(size_t rowCount, size_t columnCount);

		/// <summary> Inicializuje tuto maticu ako kopiu matice odovzdanej ako parameter. </summary>
		/// <param name = "other"> Odkaz na maticu, z ktorej sa prevezmu vlastnosti. </param>
		CoherentMatrix(CoherentMatrix& other);

		/// <summary> Destruktor. </summary>
		~CoherentMatrix();

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
	private:
		/// <summary> Mapovacia funkcia, ktora prevedie index v poli na index vo vektore. </summary>
		/// <param name = "index"> Index v poli. </param>
		/// <returns> Index vo vektore. </returns>
		int mapFunction(int rowIndex, int columnIndex) const;

	
	};

	template<typename T>
	inline CoherentMatrix<T>::CoherentMatrix(size_t rowCount, size_t columnCount) :
		matrix_(new Vector(rowCount* columnCount * sizeof(T))), rowCount_(rowCount), columnCount_(columnCount)
	{
	}

	template<typename T>
	inline CoherentMatrix<T>::CoherentMatrix(CoherentMatrix& other) :
		matrix_(new Vector(*other.matrix_)), columnCount_( other.columnCount_), rowCount_(other.rowCount_)
	{
	}

	template<typename T>
	inline CoherentMatrix<T>::~CoherentMatrix()
	{
		delete matrix_;
		matrix_ = nullptr;
	
		columnCount_ = 0;
		rowCount_ = 0;
	}

	template<typename T>
	inline Structure& CoherentMatrix<T>::assign(Structure& other)
	{
		if (this != &other) {

			CoherentMatrix<T>& otherCoherentMatrix = dynamic_cast<CoherentMatrix<T>&>(other);
			if (columnCount_ == otherCoherentMatrix.getColumnCount() && rowCount_ == otherCoherentMatrix.getRowCount()) {
			
				matrix_->assign((*otherCoherentMatrix.matrix_));
			}
			else {
				throw std::invalid_argument("Matrix sizes differ");
			}
		}
		return *this;
	}

	template<typename T>
	inline bool CoherentMatrix<T>::equals(Structure& other)
	{
		if (this != &other) {
			CoherentMatrix<T>* otherCoherentMatrix = dynamic_cast<CoherentMatrix<T>*>(&other);
			if (otherCoherentMatrix != nullptr) {
				if (rowCount_ == otherCoherentMatrix->rowCount_ && columnCount_ == otherCoherentMatrix->columnCount_) {
					return matrix_->equals(*otherCoherentMatrix->matrix_);
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		return true;	
	}

	template<typename T>
	inline size_t CoherentMatrix<T>::size()
	{
		return rowCount_ * columnCount_;
	}

	template<typename T>
	inline size_t CoherentMatrix<T>::getRowCount()
	{
		return rowCount_;
	}

	template<typename T>
	inline size_t CoherentMatrix<T>::getColumnCount()
	{
		return columnCount_;
	}

	template<typename T>
	inline T& CoherentMatrix<T>::at(int rowIndex, int columnIndex)
	{	
		byte* bytePtr = matrix_->getBytePointer( mapFunction(rowIndex, columnIndex)); //mapFunction vrati index vo vektore
		T* Tptr = reinterpret_cast<T*>(bytePtr);
		return *Tptr;
	}



	template<typename T>
	inline int CoherentMatrix<T>::mapFunction(int rowIndex, int columnIndex) const
	{
		Utils::rangeCheckExcept(rowIndex , rowCount_, "Invalid row index!");
		Utils::rangeCheckExcept(columnIndex, columnCount_, "Invalid  column index!");
		int index = (rowIndex * columnCount_ + columnIndex) * sizeof(T);
		return index;
	}
}