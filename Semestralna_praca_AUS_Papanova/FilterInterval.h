#pragma once
#pragma once
#include "../Semestralna_praca_AUS_Papanova/Filter/FilterWithCriterion.h"
#include "../structures/heap_monitor.h"
#include "Criterion/Criterion.h"
template <typename ObjectType, typename	ValueType>
class FilterInterval : public FilterWithCriterion<ObjectType, ValueType>
{
private:
	ValueType min_;
	ValueType max_;
protected:
	bool passFilter(ValueType value)  const override;
public:
	FilterInterval(Criterion<ObjectType, ValueType>* criterion, ValueType min, ValueType max);
};


template<typename ObjectType, typename ValueType>
inline bool FilterInterval<ObjectType, ValueType>::passFilter(ValueType value) const
{
	return  value >= min_ && value <= max_;
}

template<typename ObjectType, typename ValueType>
inline FilterInterval<ObjectType, ValueType>::FilterInterval(Criterion<ObjectType, ValueType>* criterion, ValueType min, ValueType max) :
	FilterWithCriterion<ObjectType, ValueType>(criterion), min_(min), max_(max)
{
}
