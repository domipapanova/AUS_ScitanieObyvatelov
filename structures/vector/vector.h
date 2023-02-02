#pragma once

#include "../structure.h"
#include "../types.h"

namespace structures
{
	/// <summary> Vektor. </summary>
	class Vector : public Structure
	{
	public:
		/// <summary> Konstruktor vytvori vektor o velkosti size bytov. </summary>
		/// <param name = "size"> Pocet bytov vo vytvorenom vektore. </param>
		Vector(size_t size);

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Zdrojovy vektor. </param>
		Vector(Vector& other);

		/// <summary> Destruktor. </summary>
		~Vector();

		/// <summary> Vrati pocet bytov vo vektore. </summary>
		/// <returns> Pocet bytov vo vektore. </returns>
		size_t size() override;

		/// <summary> Priradenie struktury. </summary>
		/// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary> Porovnanie struktur. </summary>
		/// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
		/// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
		bool equals(Structure& other) override;

		/// <summary> Vrati adresou byte na indexe. </summary>
		/// <param name = "index"> Index byte-u. </param>
		/// <returns> Adresa byte-u na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do vektoru. </exception>
		byte& operator[](int index);

		/// <summary> Vrati adresou byte na indexe. </summary>
		/// <param name = "index"> Index byte-u. </param>
		/// <returns> Adresa byte-u na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do vektoru. </exception>
		byte& at(int index);

		/// <summary> Vrati ukazovatel na byte na danom indexe. </summary>
		/// <param name = "index"> Index byte-u. </param>
		/// <returns> Ukazovatel na byte na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do vektoru. </exception>
		byte* getBytePointer(int index);

		/// <summary> Skopiruje length bytov z vektora src od pozicie srcStartIndex do vektora dest od pozicie destStartIndex. </summary>
		/// <param name = "src"> Zdrojovy vektor. </param>
		/// <param name = "srcStartIndex"> Index byte-u vo vektore src, od ktoreho sa zacne citat. </param>
		/// <param name = "dest"> Cielovy vektor. </param>
		/// <param name = "destStartIndex"> Index byte-u vo vektore dest, od ktoreho sa zacne zapisovat. </param>
		/// <param name = "length"> Pocet bytov, ktore budu skopirovane z vektora src od pozicie srcStartIndex do vektora dest od pozicie destStartIndex. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak zaciatocne alebo koncove indexy nepatria do prislusnych vektorov. </exception>
		static void copy(Vector& src, int srcStartIndex, Vector& dest, int destStartIndex, int length);

	private:
		/// <summary> Ukazovatel na zaciatok pamate patriacej vektoru. </summary>
		void* memory_;
		/// <summary> Pocet bytov vo vektore. </summary>
		size_t size_;
	};

}