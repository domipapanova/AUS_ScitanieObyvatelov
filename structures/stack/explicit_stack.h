#pragma once

#include "stack.h"
#include "../list/linked_list.h"

namespace structures
{
    /// <summary> Explicitny zasobník. </summary>
    /// <typeparam name = "T"> Typ dat ukladanych v zasobniku. </typepram>
    template<typename T>
    class ExplicitStack : public Stack<T>
    {
    public:
        /// <summary> Konstruktor. </summary>
        ExplicitStack();

        /// <summary> Kopirovaci konstruktor. </summary>
        /// <param name = "other"> Explicitny zasobník, z ktoreho sa prevezmu vlastnosti. </param>
        ExplicitStack(ExplicitStack<T>& other);

        /// <summary> Destruktor. </summary>
        ~ExplicitStack();

        /// <summary> Vrati pocet prvkov v zasobniku. </summary>
        /// <returns> Pocet prvkov v zasobniku. </returns>
        size_t size() override;

        /// <summary> Operator priradenia. </summary>
        /// <param name = "other"> Zasobnik, z ktoreho ma prebrat vlastnosti. </param>
        /// <returns> Adresa, na ktorej sa tento zasobnik nachadza po priradeni. </returns>
        Structure& assign(Structure& other) override;

        /// <summary> Porovnanie struktur. </summary>
        /// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
        /// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
        bool equals(Structure& other) override;

        /// <summary> Vymaze zasobnik. </summary>
        void clear() override;

        /// <summary> Prida prvok do zasobnika. </summary>
        /// <param name = "data"> Pridavany prvok. </param>
        void push(const T& data) override;

        /// <summary> Odstrani prvok na vrchole zasobnika. </summary>
        /// <returns> Prvok na vrchole zasobnika. </returns>
        /// <exception cref="std::out_of_range"> Vyhodena, ak je zasobnik prazdny. </exception>
        T pop() override;

        /// <summary> Vrati prvok na vrchole zasobnika. </summary>
        /// <returns> Prvok na vrchole zasobnika. </returns>
        /// <exception cref="std::out_of_range"> Vyhodena, ak je zasobnik prazdny. </exception>
        T& peek() override;

    protected:
        /// <summary> Zoznam, pomocou ktoreho je implementovany zasobnik. </summary>
        LinkedList<T>* list_;
    };

    template<typename T>
    ExplicitStack<T>::ExplicitStack() :
        Stack<T>(),
        list_(new LinkedList<T>())
    {
    }

    template<typename T>
    ExplicitStack<T>::ExplicitStack(ExplicitStack<T>& other) :
        ExplicitStack()
    {
        assign(other);
    }

    template<typename T>
    ExplicitStack<T>::~ExplicitStack()
    {
        delete list_;
    }

    template<typename T>
    inline Structure& ExplicitStack<T>::assign(Structure& other)
    {
        if (this != &other) {
            ExplicitStack<T>& otherStack = dynamic_cast<ExplicitStack<T>&>(other);
            list_->assign(*otherStack.list_);
        }
        return *this;
    }

    template<typename T>
    inline bool ExplicitStack<T>::equals(Structure& other)
    {
        ExplicitStack<T>* otherStack = dynamic_cast<ExplicitStack<T>*>(&other);

        if (otherStack != nullptr) {
            return list_->equals(*otherStack->list_);
        }
        else {
            return false;
        }
    }

    template<typename T>
    size_t ExplicitStack<T>::size()
    {
        return list_->size();
    }

    template<typename T>
    inline void ExplicitStack<T>::clear()
    {
        list_->clear();
    }

    template<typename T>
    inline void ExplicitStack<T>::push(const T& data)
    {
        list_->insert(data, 0);
    }

    template<typename T>
    inline T ExplicitStack<T>::pop()
    {
        return list_->removeAt(0);
    }

    template<typename T>
    inline T& ExplicitStack<T>::peek()
    {
        return list_->at(0);
    }
}