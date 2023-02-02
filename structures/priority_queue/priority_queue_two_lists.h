#pragma once

#include "priority_queue.h"
#include "priority_queue_limited_sorted_array_list.h"
#include "../list/linked_list.h"
#include <cmath>

namespace structures
{
	/// <summary> Prioritny front implementovany dvojzoznamom. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prioritnom fronte. </typepram>
	/// <remarks> Implementacia efektivne vyuziva prioritny front implementovany utriednym ArrayList-om s obmedzenou kapacitou a LinkedList. </remarks>
	template<typename T>
	class PriorityQueueTwoLists : public PriorityQueue<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		PriorityQueueTwoLists();

		PriorityQueueTwoLists(PriorityQueueTwoLists<T>& other);
		~PriorityQueueTwoLists();

		/// <summary> Priradenie struktury. </summary>
		/// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary> Vrati pocet prvkov v prioritnom fronte implementovanom dvojzoznamom. </summary>
		/// <returns> Pocet prvkov v prioritnom fronte implementovanom dvojzoznamom. </returns>
		size_t size() override;

		/// <summary> Vymaze obsah prioritneho frontu implementovaneho dvojzoznamom. </summary>
		void clear() override;

		/// <summary> Vlozi prvok s danou prioritou do prioritneho frontu. </summary>
		/// <param name = "priority"> Priorita vkladaneho prvku. </param>
		/// <param name = "data"> Vkladany prvok. </param>
		void push(int priority, const T& data) override;

		/// <summary> Odstrani prvok s najvacsou prioritou z prioritneho frontu implementovaneho dvojzoznamom. </summary>
		/// <returns> Odstraneny prvok. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>
		T pop() override;

		/// <summary> Vrati adresou prvok s najvacsou prioritou. </summary>
		/// <returns> Adresa, na ktorej sa nachadza prvok s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>
		T& peek() override;

		/// <summary> Vrati prioritu prvku s najvacsou prioritou. </summary>
		/// <returns> Priorita prvku s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>
		int peekPriority() override;

	private:
		/// <summary> Smernik na prioritny front ako implementovany utriednym ArrayList-om s obmedzenou kapacitou . </summary>
		/// <remarks> Z pohladu dvojzoznamu sa jedna o kratsi utriedeny zoznam. </remarks>
		PriorityQueueLimitedSortedArrayList<T>* shortList_;

		/// <summary> Smernik na dlhsi neutriedeny zoznam. </summary>
		LinkedList<PriorityQueueItem<T>*>* longList_;

		void fillShortList();
	};

	template<typename T>
	PriorityQueueTwoLists<T>::PriorityQueueTwoLists() :
		shortList_(new PriorityQueueLimitedSortedArrayList<T>()),
		longList_(new LinkedList<PriorityQueueItem<T>*>())
	{
	}

	template<typename T>
	PriorityQueueTwoLists<T>::PriorityQueueTwoLists(PriorityQueueTwoLists<T>& other) :
		PriorityQueueTwoLists<T>()
	{
		assign(other);
	}

	template<typename T>
	PriorityQueueTwoLists<T>::~PriorityQueueTwoLists()
	{
		clear();
		delete shortList_;
		delete longList_;
		longList_ = nullptr;
		shortList_ = nullptr;
	}

	template<typename T>
	Structure& PriorityQueueTwoLists<T>::assign(Structure& other)
	{
		if (this != &other) {
			PriorityQueueTwoLists<T>& otherPQTL = dynamic_cast<PriorityQueueTwoLists<T>&>(other);
			clear();
			shortList_->assign(*(otherPQTL.shortList_));
			for (auto item : *(otherPQTL.longList_)) {
				longList_->add(new PriorityQueueItem<T>(*item));
			}
		}
		return *this;
	}

	template<typename T>
	size_t PriorityQueueTwoLists<T>::size()
	{
		return longList_->size() + shortList_->size();
	}

	template<typename T>
	void PriorityQueueTwoLists<T>::clear()
	{
		shortList_->clear();
		for (auto item : *longList_) {
			delete item;
		}
		longList_->clear();
	}

	template<typename T>
	void PriorityQueueTwoLists<T>::push(int priority, const T& data)
	{
		
		PriorityQueueItem<T>* item = nullptr;
		if (longList_->isEmpty() || shortList_->minPriority() > priority) {
			item = shortList_->pushAndRemove(priority, data);
			if (item != nullptr) {
				longList_->add(item);
			}
		} else {
			item = new structures::PriorityQueueItem<T>(priority, data);
			longList_->add(item);
		}
		int newSize = sqrt(size());
		if (newSize >= 2) {
			shortList_->trySetCapacity(sqrt(size())); //pre amotizovani zlozitost
		}
	}


	template<typename T>
	T PriorityQueueTwoLists<T>::pop()
	{
		T data;
		if (size() != 0) {
			data = shortList_->pop();

			if (shortList_->size() == 0 && longList_->size() != 0) {

				fillShortList();
			}
		}
		else {
			throw std::logic_error("Priority queue two lists is empty!");
		}
	
		return data;
	}

	template<typename T>
	T& PriorityQueueTwoLists<T>::peek()
	{
		return  shortList_->peek();
	}

	template<typename T>
	int PriorityQueueTwoLists<T>::peekPriority()
	{
		return shortList_->peekPriority();
	}

	template<typename T>
	void PriorityQueueTwoLists<T>::fillShortList()
	{
		int newSize = sqrt(size());
		if (newSize >= 2) {
			shortList_->trySetCapacity(newSize);
		}

		auto newLongList = new LinkedList<PriorityQueueItem<T>*>();
		while (!longList_->isEmpty()) {
			//ak je vymazana priorita vyssia nez minimalna - vlozi sa do shortlistu
			//ak nie vlozi sa priamo do longlistu
			auto deletedItem = longList_->removeAt(0);
			auto removedItem = shortList_->pushAndRemove(deletedItem->getPriority(), deletedItem->accessData());
			if (removedItem != nullptr) {
				newLongList->add(removedItem);
			}
		}
	
		delete longList_;
		longList_ = newLongList;
	}
}