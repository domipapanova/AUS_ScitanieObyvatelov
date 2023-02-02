#include "structure.h"

namespace structures
{
    Structure::~Structure()
    {
    }

    Structure& Structure::operator=(Structure& other)
    {
        return this->assign(other);
    }

    bool Structure::operator==(Structure& other)
    {
        return this->equals(other);
    }

    bool Structure::isEmpty()
    {
        return this->size() == 0;
    }
}