#pragma once

#include "queue.h"
#include "../list/linked_list.h"

namespace structures
{
	/// <summary> Explicitny front. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych vo fronte. </typepram>
	template<typename T>
	class ExplicitQueue : public Queue<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		ExplicitQueue();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Explicitny front, z ktoreho sa prevezmu vlastnosti. </param>
		ExplicitQueue(ExplicitQueue<T>& other);

		/// <summary> Destruktor. </summary>
		~ExplicitQueue();

		/// <summary> Vrati pocet prvkov vo fronte. </summary>
		/// <returns> Pocet prvkov vo fronte. </returns>
		size_t size() override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Front, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento front nachadza po priradeni. </returns>
		Structure& assign(Structure& other) override;

		/// <summary> Porovnanie struktur. </summary>
		/// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
		/// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
		bool equals(Structure& other) override;

		/// <summary> Vymaze front. </summary>
		void clear() override;

		/// <summary> Prida prvok do frontu. </summary>
		/// <param name = "data"> Pridavany prvok. </param>
		void push(const T& data) override;

		/// <summary> Odstrani prvok z frontu. </summary>
		/// <returns> Prvok na zaciatku frontu. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak je front prazdny. </exception>
		T pop() override;

		/// <summary> Vrati prvok na zaciatku frontu. </summary>
		/// <returns> Prvok na zaciatku frontu. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak je front prazdny. </exception>
		T& peek() override;

	protected:
		/// <summary> Zoznam, pomocou ktoreho je implementovany front. </summary>
		LinkedList<T>* list_;
	};

	template<typename T>
	ExplicitQueue<T>::ExplicitQueue() :
		Queue<T>(),
		list_(new LinkedList<T>())
	{
	}

	template<typename T>
	ExplicitQueue<T>::ExplicitQueue(ExplicitQueue<T>& other) :
		ExplicitQueue()
	{
		assign(other);
	}

	template<typename T>
	ExplicitQueue<T>::~ExplicitQueue()
	{
		//TODO 05: ExplicitQueue
	}

	template<typename T>
	inline Structure& ExplicitQueue<T>::assign(Structure& other)
	{
		//TODO 05: ExplicitQueue
		throw std::runtime_error("ExplicitQueue<T>::assign: Not implemented yet.");
	}

	template<typename T>
	inline bool ExplicitQueue<T>::equals(Structure& other)
	{
		//TODO 05: ExplicitQueue
		throw std::runtime_error("ExplicitQueue<T>::equals: Not implemented yet.");
	}

	template<typename T>
	size_t ExplicitQueue<T>::size()
	{
		//TODO 05: ExplicitQueue
		throw std::runtime_error("ExplicitQueue<T>::size: Not implemented yet.");
	}

	template<typename T>
	inline void ExplicitQueue<T>::clear()
	{
		list_->clear();
	}

	template<typename T>
	inline void ExplicitQueue<T>::push(const T& data)
	{
		list_->add(data);
	}

	template<typename T>
	inline T ExplicitQueue<T>::pop()
	{
		return list_->removeAt(0);
	}

	template<typename T>
	inline T& ExplicitQueue<T>::peek()
	{
		return list_->at(0);
	}
}