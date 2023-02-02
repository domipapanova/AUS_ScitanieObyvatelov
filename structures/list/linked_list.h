#pragma once

#include "list.h"
#include "../structure_iterator.h"
#include "../data_item.h"
#include "../utils.h"

namespace structures
{
    /// <summary> Prvok jednostranne zretazeneho zoznamu. </summary>
    /// <typeparam name = "T"> Typ dat ukladanych v prvku. </typepram>
    template<typename T>
    class LinkedListItem : public DataItem<T>
    {
        //neplytva sa miestom, netreba velku suvislu pamat
        //modifikacia je jednoducha na zaciatku na konci
        //zlozita je at()
        //4 byte - 1 smernik, zabera pamat
        //volim zoznam ked neviem kolko prvkov bude

    public:
        /// <summary> Konstruktor. </summary>
        /// <param name = "data"> Data, ktore uchovava. </param>
        LinkedListItem(T data);

        /// <summary> Kopirovaci konstruktor. </summary>
        /// <param name = "other"> Prvok jednstranne zretazeneho zoznamu, z ktoreho sa prevezmu vlastnosti.. </param>
        LinkedListItem(LinkedListItem<T>& other);

        /// <summary> Destruktor. </summary>
        ~LinkedListItem();

        /// <summary> Getter nasledujuceho prvku zretazeneho zoznamu. </summary>
        /// <returns> Nasledujuci prvok zretazeneho zoznamu. </returns>
        LinkedListItem<T>* getNext();

        /// <summary> Setter nasledujuceho prvku zretazeneho zoznamu. </summary>
        /// <param name´= "next"> Novy nasledujuci prvok zretazeneho zoznamu. </param>
        void setNext(LinkedListItem<T>* next);

    private:
        /// <summary> Nasledujuci prvok zretazeneho zoznamu. </summary>
        LinkedListItem<T>* next_;
    };

    /// <summary> Jednostranne zretazeny zoznam. </summary>
    /// <typeparam name = "T"> Typ dat ukladanych v zozname. </typepram>
    template<typename T>
    class LinkedList : public List<T>
    {
    public:
        /// <summary> Konstruktor. </summary>
        LinkedList();

        /// <summary> Kopirovaci konstruktor. </summary>
        /// <param name = "other"> LinkedList, z ktoreho sa prevezmu vlastnosti. </param>
        LinkedList(LinkedList<T>& other);

        /// <summary> Destruktor. </summary>
        ~LinkedList();

        /// <summary> Vrati pocet prvkov v zozname. </summary>
        /// <returns> Pocet prvkov v zozname. </returns>
        size_t size() override;

        /// <summary> Priradenie struktury. </summary>
        /// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
        /// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
        Structure& assign(Structure& other) override;

        /// <summary> Porovnanie struktur. </summary>
        /// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
        /// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
        bool equals(Structure& other) override;

        /// <summary> Vrati adresou prvok na indexe. </summary>
        /// <param name = "index"> Index prvku. </param>
        /// <returns> Adresa prvku na danom indexe. </returns>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        T& at(int index) override;

        /// <summary> Prida prvok do zoznamu. </summary>
        /// <param name = "data"> Pridavany prvok. </param>
        void add(const T& data) override;

        /// <summary> Vlozi prvok do zoznamu na dany index. </summary>
        /// <param name = "data"> Pridavany prvok. </param>
        /// <param name = "index"> Index prvku. </param>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        /// <remarks> Ak je ako index zadana hodnota poctu prvkov (teda prvy neplatny index), metoda insert sa sprava ako metoda add. </remarks>
        void insert(const T& data, int index) override;

        /// <summary> Odstrani prvy vyskyt prvku zo zoznamu. </summary>
        /// <param name = "data"> Odstranovany prvok. </param>
        /// <returns> true, ak sa podarilo prvok zo zoznamu odobrat, false inak. </returns>
        bool tryRemove(const T& data) override;

        /// <summary> Odstrani zo zoznamu prvok na danom indexe. </summary>
        /// <param name = "index"> Index prvku. </param>
        /// <returns> Odstraneny prvok. </returns>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        T removeAt(int index) override;

        /// <summary> Vrati index prveho vyskytu prvku v zozname. </summary>
        /// <param name = "data"> Prvok, ktoreho index sa hlada. </param>
        /// <returns> Index prveho vyskytu prvku v zozname, ak sa prvok v zozname nenachadza, vrati -1. </returns>
        int getIndexOf(const T& data) override;

        /// <summary> Vymaze zoznam. </summary>
        void clear() override;

        /// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
        /// <returns> Iterator na zaciatok struktury. </returns>
        /// <remarks> Zabezpecuje polymorfizmus. </remarks>
        Iterator<T>* getBeginIterator() override;

        /// <summary> Vrati skutocny iterator na koniec struktury </summary>
        /// <returns> Iterator na koniec struktury. </returns>
        /// <remarks> Zabezpecuje polymorfizmus. </remarks>
        Iterator<T>* getEndIterator() override;

    private:
        /// <summary> Pocet prvkov v zozname. </summary>
        size_t size_;
        /// <summary> Prvy prvok zoznamu. </summary>
        LinkedListItem<T>* first_;
        /// <summary> Posledny prvok zoznamu. </summary>
        LinkedListItem<T>* last_;

    private:
        /// <summary> Vrati prvok zoznamu na danom indexe. </summary>
        /// <param name = "index"> Pozadovany index. </summary>
        /// <returns> Prvok zoznamu na danom indexe. </param>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        LinkedListItem<T>* getItemAtIndex(int index);

    private:
        /// <summary> Iterator pre LinkedList. </summary>
        class LinkedListIterator : public Iterator<T>
        {
        public:
            /// <summary> Konstruktor. </summary>
            /// <param name = "position"> Pozicia v zretazenom zozname, na ktorej zacina. </param>
            LinkedListIterator(LinkedListItem<T>* position);

            /// <summary> Destruktor. </summary>
            ~LinkedListIterator();

            /// <summary> Operator priradenia. Priradi do seba hodnotu druheho iteratora. </summary>
            /// <param name = "other"> Druhy iterator. </param>
            /// <returns> Vrati seba po priradeni. </returns>
            Iterator<T>& operator= (Iterator<T>& other) override;

            /// <summary> Porovna sa s druhym iteratorom na nerovnost. </summary>
            /// <param name = "other"> Druhy iterator. </param>
            /// <returns> True, ak sa iteratory nerovnaju, false inak. </returns>
            bool operator!=(Iterator<T>& other) override;

            /// <summary> Vrati data, na ktore aktualne ukazuje iterator. </summary>
            /// <returns> Data, na ktore aktualne ukazuje iterator. </returns>
            T operator*() override;

            /// <summary> Posunie iterator na dalsi prvok v strukture. </summary>
            /// <returns> Iterator na dalsi prvok v strukture. </returns>
            /// <remarks> Zvycajne vrati seba. Ak vrati iny iterator, povodny bude automaticky zruseny. </remarks>
            Iterator<T>& operator++() override;

        private:
            /// <summary> Aktualna pozicia v zozname. </summary>
            LinkedListItem<T>* position_;
        };
    };

    template<typename T>
    inline LinkedListItem<T>::LinkedListItem(T data) :
        DataItem<T>(data),
        next_(nullptr)
    {
    }

    template<typename T>
    inline LinkedListItem<T>::LinkedListItem(LinkedListItem<T>& other) :
        DataItem<T>(other),
        next_(other.next_)
    {
    }

    template<typename T>
    inline LinkedListItem<T>::~LinkedListItem()
    {
        next_ = nullptr;
    }

    template<typename T>
    inline LinkedListItem<T>* LinkedListItem<T>::getNext()
    {
        return next_;
    }

    template<typename T>
    inline void LinkedListItem<T>::setNext(LinkedListItem<T>* next)
    {
        next_ = next;
    }

    template<typename T>
    inline LinkedList<T>::LinkedList() :
        size_(0),
        first_(nullptr),
        last_(nullptr)
    {
    }

    template<typename T>
    inline LinkedList<T>::LinkedList(LinkedList<T>& other):
        LinkedList<T>()
    {
        assign(other);
    }

    template<typename T>
    inline LinkedList<T>::~LinkedList()
    {
        clear();
    }

    template<typename T>
    inline size_t LinkedList<T>::size()
    {
        return size_;
    }

    template<typename T>
    inline Structure& LinkedList<T>::assign(Structure& other)
    {
        if (this != &other) {
            LinkedList<T>& otherList = dynamic_cast<LinkedList<T>&>(other); //ked pouzijem & - dynamiccast sa nepodari tak vyhodi vynimku
            clear();
            LinkedListItem<T>* otherItem = otherList.first_;
            while (otherItem != nullptr) {
                add(otherItem->accessData());
                otherItem = otherItem->getNext();
            }
        }
        return *this;

    }

    template<typename T>
    inline bool LinkedList<T>::equals(Structure& other)
    {
        if (size_ != other.size()) {
            return false;
        }

        if (this == &other) {
            return true;
        }
        LinkedList<T>* otherList = dynamic_cast<LinkedList<T>*>(&other);//dynamic cast + smernik - ked sa nepodari vrati nullptr
        if (otherList == nullptr) {
            return false;
        }

        LinkedListItem<T>* item = first_;
        LinkedListItem<T>* otherItem = otherList->first_;

        while (item != nullptr) {
            if (item->accessData() != otherItem->accessData()) {
                return false;
            }
            item = item->getNext();
            otherItem = otherItem->getNext();
        }
        return true;


    }

    template<typename T>
    inline T& LinkedList<T>::at(int index)
    {
        Utils::rangeCheckExcept(index, size_, "Invalid index");
        return getItemAtIndex(index)->accessData();

    }

    template<typename T>
    inline void LinkedList<T>::add(const T& data)
    {
        //TODO 04: LinkedList
        //vytvorim novy LinkedListItem<T>* -- v stacku sa vymaze po vyskoceni z fukcie, preto * aby siel do haldy aby sa nevymazal sa 

        //zistim ci je prvy: size = 0;
        //ak ano
        //fisrt = novy, last = novy
        //ak nie
        //last->setNext(novy)
        // nakoniec spolu
        //last = novy
        //size++
        LinkedListItem<T>* newItem = new LinkedListItem<T>(data);
        if (size_ != 0) {
            last_->setNext(newItem);
            //(*last_).setNext(nullptr); to iste: pristup k metode cez smernik
        }
        else {
            first_ = newItem;
        }
        last_ = newItem;
        size_++;
    }

    template<typename T>
    inline void LinkedList<T>::insert(const T& data, int index)
    {
        //TODO 04: LinkedList

        //ak nie:
        //rangechcek
        // vytvorim novy LLI
        //ak index == 0, ide na zaciatok
        // novy->setNext(first_)
        //first_ = novy;
        //ak != 0
        //pred = getItemAtIndex(index - 1)
        //novy->setNext(pred->getNext())
        //pred.setNext(novy)

        //size++
        if (index == size_) {
            add(data);
        }
        else {
            Utils::rangeCheckExcept(index, size_, "Invalid index");
            LinkedListItem<T>* newItem = new LinkedListItem<T>(data);
            if (index != 0) {
                LinkedListItem<T>* previous = getItemAtIndex(index - 1);//predcessor
                newItem->setNext(previous -> getNext());
                previous->setNext(newItem);

            }
            else {
                newItem->setNext(first_);
                first_ = newItem;
            }
            size_++;
        }
    }

    template<typename T>
    inline bool LinkedList<T>::tryRemove(const T& data)
    {
        int index = getIndexOf(data);
        if (index == -1) {
            return false;
        }
        else {
            removeAt(index);
            return true;
        }
    }

    template<typename T>
    inline T LinkedList<T>::removeAt(int index)
    {
        // rangeCheck
        // je to posledy ? index == size_ - 1
        // ak ano
                // LLI<T>* DELETEDITEM = last_
        // LLI* pred = getItemAtIndex(index - 1)
        // pred - > setNext(nullptr)
        // last = pred
        // ak nie je prvy ani posledy
        //         // LLI* pred = getItemAtIndex(index - 1)

              // LLI<T>* DELETEDITEM = pred->getNext
        // pred - > setNext(ndeleteditem - > getNext)
        // last = pred
        // 
        // 
        // ak je prvy
        // deletedItem = first
        // first = fisrt->getNext
        // if (delItem == last)
        //      last = nullptr
        // 
        // pre vsetky:
        //T result = DELETEDITEM.accetData;
        //delete DELETEDITEM
        //size--
        //return result;
        Utils::rangeCheckExcept(index, size_, "Invalid index");
        LinkedListItem<T>* deletedItem = nullptr;
        LinkedListItem<T>* previous = nullptr;
   
            if (index == 0) {
                deletedItem = first_;
                first_ = first_->getNext();
                if (deletedItem == last_) {
                    last_ = nullptr;
                }
            }
            else {
                previous = getItemAtIndex(index - 1);
                deletedItem = previous->getNext();
                previous->setNext(deletedItem->getNext());
                if (deletedItem = last_) {
                    last_ = previous;
                }
            }

        T result = deletedItem->accessData();
        delete deletedItem;
        size_--;
        return result;
    }

    template<typename T>
    inline int LinkedList<T>::getIndexOf(const T& data)
    {
        //TODO 04: LinkedList
        //cez fori je neefektivne prehladvat - e^2

        LinkedListItem<T>* current = first_;
        for (size_t i = 0; i < size_; i++) {
            if (current->accessData() == data) {
                return i;
            }
            else {
                current = current->getNext();
            }
        }
        return -1;
    }

    template<typename T>
    inline void LinkedList<T>::clear()
    {
      
        if (size_ != 0) {
            LinkedListItem<T>* deletedItem = first_;
            while (deletedItem != nullptr) {

                LinkedListItem<T>* nextItem = deletedItem->getNext();
                delete deletedItem;
                deletedItem = nextItem;
            }
            size_ = 0;
            first_ = nullptr;
            last_ = nullptr;
        }

    }

    template<typename T>
    inline Iterator<T>* LinkedList<T>::getBeginIterator()
    {
        return new LinkedListIterator(first_);
    }

    template<typename T>
    inline Iterator<T>* LinkedList<T>::getEndIterator()
    {
        return new LinkedListIterator(nullptr);
    }

    template<typename T>
    inline LinkedListItem<T>* LinkedList<T>::getItemAtIndex(int index)
    {
        Utils::rangeCheckExcept(index, size_, "Invalid index");
        if (index != size_ - 1) {
            LinkedListItem<T>* current = first_;

            for (int i = 0; i < index; i++) {
                current = current->getNext();
            }
            return current;
        }
        else {
            return last_;
        }
    }

    template<typename T>
    inline LinkedList<T>::LinkedListIterator::LinkedListIterator(LinkedListItem<T>* position) :
        position_(position)
    {
    }

    template<typename T>
    inline LinkedList<T>::LinkedListIterator::~LinkedListIterator()
    {
       // position_ = 0;
        position_ = nullptr;
        
    }

    template<typename T>
    inline Iterator<T>& LinkedList<T>::LinkedListIterator::operator=(Iterator<T>& other)
    {
       position_ = dynamic_cast<const LinkedListIterator&>(other).position_;
       return *this;
    }

    template<typename T>
    inline bool LinkedList<T>::LinkedListIterator::operator!=(Iterator<T>& other)
    {
       return position_ != dynamic_cast<const LinkedListIterator&>(other).position_;
    }

    template<typename T>
    inline T LinkedList<T>::LinkedListIterator::operator*()
    {
        return position_->accessData();
    }

    template<typename T>
    inline Iterator<T>& LinkedList<T>::LinkedListIterator::operator++()
    {
      /*  position_++;
        return *this;*/
        position_ = position_->getNext();
        return *this;
    }

}