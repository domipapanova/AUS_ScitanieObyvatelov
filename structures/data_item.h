#pragma once

namespace structures
{
    /// <summary> Prvok uchovavajuci data. </summary>
    /// <typeparam name = "T"> Typ dat ukladanych v prvku. </typepram>
    /// <remarks> Pouziva sa ako predok pre vnotorne prvky struktur (napr. zretazeny zoznam, tabulka..). </remarks>
    template <typename T>
    class DataItem
    {
    public:
        /// <summary> Spristupni data. </summary>
        /// <returns> Data. </returns>
        T& accessData();

    protected:
        /// <summary> Konstruktor. </summary>
        /// <param name = "data"> Data, ktore uchovava. </param>
        DataItem(const T& data);

        /// <summary> Kopirovaci konstruktor. </summary>
        /// <param name = "other"> Prvok uchovavajuci data, z ktoreho sa prevezmu vlastnosti. </param>
        DataItem(const DataItem<T>& other);

        /// <summary> Destruktor. </summary>
        virtual ~DataItem();

    private:
        /// <summary> Data. </summary>
        T data_;
    };

    template<typename T>
    inline T& DataItem<T>::accessData()
    {
        return data_;
    }

    template<typename T>
    inline DataItem<T>::DataItem(const T& data) :
        data_(data)
    {
    }

    template<typename T>
    inline DataItem<T>::DataItem(const DataItem<T>& other) :
        DataItem(other.data_)
    {
    }

    template<typename T>
    inline DataItem<T>::~DataItem()
    {
    }
}