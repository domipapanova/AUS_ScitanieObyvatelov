#pragma once

#include "priority_queue_list.h"
#include "../list/array_list.h"
#include <stdexcept>

namespace structures
{
	/// <summary> Prioritny front implementovany utriednym ArrayList-om. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prioritnom fronte. </typepram>
	template<typename T>
	class PriorityQueueSortedArrayList : public PriorityQueueList<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		PriorityQueueSortedArrayList();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Prioritny front implementovany utriednym ArrayList-om, z ktoreho sa prevezmu vlastnosti. </param>
		PriorityQueueSortedArrayList(PriorityQueueSortedArrayList<T>& other);

		/// <summary> Priradenie struktury. </summary>
		/// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary> Vlozi prvok s danou prioritou do prioritneho frontu implementovaneho utriednym ArrayList-om. </summary>
		/// <param name = "priority"> Priorita vkladaneho prvku. </param>
		/// <param name = "data"> Vkladany prvok. </param>
		void push(int priority, const T& data) override;

	protected:
		/// <summary> Vrati index v utriedenom ArrayList-e, na ktorom sa nachadza prvok s najvacsou prioritou. </summary>
		/// <returns> Index prvku s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je zoznam prazdny. </exception>
		int indexOfPeek() override;
	private:
		int findIndex(int priority, int indexStart, int indexEnd, bool& found) const;
	};

	template<typename T>
	inline PriorityQueueSortedArrayList<T>::PriorityQueueSortedArrayList() :
		PriorityQueueList<T>(new ArrayList<PriorityQueueItem<T>*>())
	{
	}

	template<typename T>
	inline PriorityQueueSortedArrayList<T>::PriorityQueueSortedArrayList(PriorityQueueSortedArrayList<T>& other) :
		PriorityQueueSortedArrayList<T>()
	{
		assign(other);
	}

	template<typename T>
	inline Structure& PriorityQueueSortedArrayList<T>::assign(Structure& other)
	{
		return PriorityQueueList<T>::assignPrioQueueList(dynamic_cast<PriorityQueueList<T>&>(other));
	}

	template<typename T>
	inline void PriorityQueueSortedArrayList<T>::push(int priority, const T& data)
	{
		if (list_->isEmpty() || priority <= peekPriority()) {
			list_->add(new PriorityQueueItem<T>(priority, data));
		}
		else if (priority >= (list_->at(0))->getPriority() || size() == 1) {
			PriorityQueueList<T>::list_->insert(new structures::PriorityQueueItem<T>(priority, data), 0);
		}
		else {

			bool found = false;
			int pushIndex = findIndex(priority, 0, PriorityQueueList<T>::list_->size() - 1, found);

			if (!found) {
				PriorityQueueList<T>::list_->insert(new structures::PriorityQueueItem<T>(priority, data), pushIndex);
			}
		}
	}

	template<typename T>
	inline int PriorityQueueSortedArrayList<T>::indexOfPeek()
	{
		return  PriorityQueueList<T>::list_->size() - 1;

	}

	template<typename T>
	inline int PriorityQueueSortedArrayList<T>::findIndex(int priority, int indexStart, int indexEnd, bool& found) const
	{
		int indexMiddle = (indexStart + indexEnd) / 2;
		auto item = PriorityQueueList<T>::list_->at(indexMiddle);
		auto priorityMiddle = item->getPriority();

		if (indexStart == PriorityQueueList<T>::list_->size()) {
			found = false;
			return indexStart;
		}

		if (priorityMiddle == priority) {
		
			found = false;
			return indexMiddle;
		}
		else {
			if (indexStart == indexEnd) {
				found = false;
				return  priority < priorityMiddle ? indexMiddle + 1 : indexMiddle;

			}
			else {
				if (priorityMiddle < priority) {
					indexEnd = indexMiddle;// -1;
				}
				else {
					indexStart = indexMiddle + 1;
				}
				return findIndex(priority, indexStart, indexEnd, found);
			}
		}
	}



}