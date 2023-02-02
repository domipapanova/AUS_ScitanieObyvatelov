#pragma once
#include "CompositeFilter.h"

template <typename ObjectType>
class filterAND : public CompositeFilter<ObjectType> {
public:
	bool pass( ObjectType& object) const override;
};

template<typename ObjectType>
inline bool filterAND<ObjectType>::pass(ObjectType& object) const
{
	for (auto filter : *CompositeFilter<ObjectType>::filters_)
	{	

		if (!filter->pass(object)) {
			return false;
		}
	}
	return true;
}
