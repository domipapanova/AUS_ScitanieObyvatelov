#pragma once

#include <stdexcept>

namespace structures
{
    /// <summary> Abstraktny predok kazdej udajovej struktury. </summary>
    class Structure
    {
    public:
        /// <summary> Destruktor. </summary>
        virtual ~Structure();

        /// <summary> Priradovaci operator. </summary>
        /// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
        /// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
        virtual Structure& operator=(Structure& other);

        /// <summary> Priradenie struktury. </summary>
        /// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
        /// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
        virtual Structure& assign(Structure& other) = 0;

        /// <summary> Porovnanie struktur. </summary>
        /// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
        /// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
        virtual bool operator==(Structure& other);

        /// <summary> Porovnanie struktur. </summary>
        /// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
        /// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
        virtual bool equals(Structure& other) = 0;

        /// <summary> Zisti, ci je struktura prazdna. </summary>
        /// <returns> true, ak je struktura prazdna, false inak. </returns>
        /// <remarks> Vyuziva metodu size(), co moze byt v niektorych strukturach neefektivne. Take struktury by tuto metodu mali predefinovat. </remarks>
        virtual bool isEmpty();

        /// <summary> Vrati velkost udajovej struktury. </summary>
        /// <returns> Velkost udajovej struktury. </returns>
        virtual size_t size() = 0;
    };
}

