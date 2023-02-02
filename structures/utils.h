#pragma once

#include <string>

namespace structures
{
    class Utils
    {
    public:
        /// <summary> Skontroluje, ci index patri do intervalu [0, size). Ak nie, vyhodi vynimku std::out_of_range. </summary>
        /// <param name = "index"> Testovaný index. </param>
        /// <param name = "size"> Pocet prvkov v kolekcii. </param>
        /// <param name = "exceptionMessage"> Text vynimky, ktora je vyhodena v pripade chyby. </param>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do intervalu [0, size). </exception>
        static void rangeCheckExcept(const int index, const size_t size, const std::string& exceptionMessage);

        /// <summary> Vymeni obsah dvoch premennych rovnakeho typu. </summary>
        /// <param name = "a"> Prva premenna. </param>
        /// <param name = "b"> Druha premenna. </param>
        template<typename T>
        static void swap(T& a, T& b);
    };

    template<typename T>
    void Utils::swap(T& a, T& b)
    {
        T temp = a;
        a = b;
        b = temp;
    }
}