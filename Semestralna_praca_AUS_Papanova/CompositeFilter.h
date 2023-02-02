#pragma once
#include "Filter/Filter.h"
#include "../structures/list/array_list.h"

template <typename ObjectType>
class CompositeFilter : public Filter<ObjectType> {
public:
	CompositeFilter();
	void registerFilter(Filter<ObjectType>* filter);
	//structures::ArrayList<Filter<ObjectType>*>&  getFilters();
	~CompositeFilter();
protected:
	structures::ArrayList<Filter<ObjectType>*>* filters_;
};

template<typename ObjectType>
inline CompositeFilter<ObjectType>::CompositeFilter() :
	filters_(new structures::ArrayList<Filter<ObjectType>*>())
{
}

template<typename ObjectType>
inline void CompositeFilter<ObjectType>::registerFilter(Filter<ObjectType>* filter)
{
	filters_->add(filter);
}

//template<typename ObjectType>
//inline structures::ArrayList<Filter<ObjectType>*>& CompositeFilter<ObjectType>::getFilters()
//{
//	return filters_;
//}

template<typename ObjectType>
inline CompositeFilter<ObjectType>::~CompositeFilter()
{
	delete filters_;
	filters_ = nullptr;
}
