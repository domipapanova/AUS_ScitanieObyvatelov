#pragma once

#include "../structure.h"
#include "../data_item.h"
#include <stdexcept>

namespace structures
{
	/// <summary> Prvok prioritneho frontu. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prvku. </typepram>
	template<typename T>
	class PriorityQueueItem : public DataItem<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		/// <param name = "priority"> Priorita dat uchovavanych v prvku. </param>
		/// <param name = "data"> Data, ktore uchovava. </param>
		PriorityQueueItem(int priority, T data);

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Prvok prioritneho frontu, z ktoreho sa prevezmu vlastnosti. </param>
		PriorityQueueItem(PriorityQueueItem<T>& other);

		/// <summary> Getter vracajuci hodnotu priority daneho prvku. </summary>
		/// <returns> Priorita daneho prvku. </returns>
		int getPriority();

	private:
		/// <summary> Priorita daneho prvku. </summary>
		int priority_;
	};

	/// <summary> Prioritny front. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prioritnom fronte. </typepram>
	template<typename T>
	class PriorityQueue : public Structure
	{
	public:
		/// <summary> Vymaze obsah prioritneho frontu implementovaneho zoznamom. </summary>
		virtual void clear() = 0;

		/// <summary> Porovnanie struktur. </summary>
		/// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
		/// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
		/// <exception cref="std::logic_error">Vyhodena vzdy. Prioritne fronty nie je mozne porovnat.</exception>
		bool equals(Structure& other) override;

		/// <summary> Vlozi prvok s danou prioritou do prioritneho frontu. </summary>
		/// <param name = "priority"> Priorita vkladaneho prvku. </param>
		/// <param name = "data"> Vkladany prvok. </param>
		virtual void push(int priority, const T& data) = 0;

		/// <summary> Odstrani prvok s najvacsou prioritou z prioritneho frontu. </summary>
		/// <returns> Odstraneny prvok. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front prazdny. </exception>
		virtual T pop() = 0;

		/// <summary> Vrati adresou prvok s najvacsou prioritou. </summary>
		/// <returns> Adresa, na ktorej sa nachadza prvok s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front prazdny. </exception>
		virtual T& peek() = 0;

		/// <summary> Vrati prioritu prvku s najvacsou prioritou. </summary>
		/// <returns> Priorita prvku s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front prazdny. </exception>
		virtual int peekPriority() = 0;
	};

	template<typename T>
	inline PriorityQueueItem<T>::PriorityQueueItem(int priority, T data) :
		DataItem<T>(data),
		priority_(priority)
	{
	}

	template<typename T>
	inline PriorityQueueItem<T>::PriorityQueueItem(PriorityQueueItem<T>& other) :
		DataItem<T>(other),
		priority_(other.priority_)
	{
	}

	template<typename T>
	inline int PriorityQueueItem<T>::getPriority()
	{
		return priority_;
	}

	template<typename T>
	inline bool PriorityQueue<T>::equals(Structure&)
	{
		throw std::logic_error("Prioritne fronty nie je mozne porovnat!");
	}
}
