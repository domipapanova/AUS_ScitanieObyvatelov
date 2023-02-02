#pragma once

#include "../structure.h"

namespace structures
{
    /// <summary> Zasobník. </summary>
    /// <typeparam name = "T"> Typ dat ukladanych v zasobniku. </typepram>
    template<typename T>
    class Stack : public Structure
    {
    public:
        /// <summary> Vymaze zasobnik. </summary>
        virtual void clear() = 0;

        /// <summary> Prida prvok do zasobnika. </summary>
        /// <param name = "data"> Pridavany prvok. </param>
        virtual void push(const T& data) = 0;

        /// <summary> Odstrani prvok na vrchole zasobnika. </summary>
        /// <returns> Prvok na vrchole zasobnika. </returns>
        /// <exception cref="std::out_of_range"> Vyhodena, ak je zasobnik prazdny. </exception>
        virtual T pop() = 0;

        /// <summary> Vrati prvok na vrchole zasobnika. </summary>
        /// <returns> Prvok na vrchole zasobnika. </returns>
        /// <exception cref="std::out_of_range"> Vyhodena, ak je zasobnik prazdny. </exception>
        virtual T& peek() = 0;
    };
}