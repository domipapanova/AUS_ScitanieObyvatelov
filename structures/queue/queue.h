#pragma once

#include "../structure.h"

namespace structures
{
    /// <summary> Front. </summary>
    /// <typeparam name = "T"> Typ dat ukladanych vo fronte. </typepram>
    template<typename T>
    class Queue : public Structure
    {
    public:
        /// <summary> Vymaze front. </summary>
        virtual void clear() = 0;

        /// <summary> Prida prvok do frontu. </summary>
        /// <param name = "data"> Pridavany prvok. </param>
        /// <remarks> Operacia moze vyhodit vynimku v pripade frontu s pevnou kapacitou. </remarks>
        virtual void push(const T& data) = 0;

        /// <summary> Odstrani prvok z frontu. </summary>
        /// <returns> Prvok frontu. </returns>
        /// <exception cref="std::out_of_range"> Vyhodena, ak je front prazdny. </exception>
        virtual T pop() = 0;

        /// <summary> Vrati prvok frontu. </summary>
        /// <returns> Prvok frontu. </returns>
        /// <exception cref="std::out_of_range"> Vyhodena, ak je front prazdny. </exception>
        virtual T& peek() = 0;
    };
}