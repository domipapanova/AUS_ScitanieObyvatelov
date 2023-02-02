#include "utils.h"
#include <stdexcept>

namespace structures
{
    void Utils::rangeCheckExcept(const int index, const size_t size, const std::string& exceptionMessage)
    {
        if (index < 0 || index >= size)
        {
            throw std::out_of_range(exceptionMessage);
        }
    }
}