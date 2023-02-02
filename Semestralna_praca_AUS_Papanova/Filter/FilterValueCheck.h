#pragma once
#include "FilterWithCriterion.h"
#include "../CriterionTU.h"
#include "../Type.h"
template <typename ObjectType, typename	ValueType>
class FilterValueCheck : public FilterWithCriterion <ObjectType, ValueType> {
	ValueType parameter_;
public:
	FilterValueCheck(Criterion<ObjectType, ValueType>* criterion, ValueType parameter);
protected:
	bool passFilter(ValueType value) const override;
};

template<typename ObjectType, typename ValueType>
inline FilterValueCheck<ObjectType, ValueType>::FilterValueCheck(Criterion<ObjectType, ValueType>* criterion, ValueType parameter) :
	FilterWithCriterion<ObjectType,ValueType>(criterion), parameter_(parameter)
{
}

template<typename ObjectType, typename ValueType>
inline bool FilterValueCheck<ObjectType, ValueType>::passFilter(ValueType value) const
{
	return value == parameter_;
}





