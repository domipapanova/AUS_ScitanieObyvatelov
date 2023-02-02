#pragma once
#include "Filter.h"
#include "../Criterion/CriterionTeritorialUnit.h"

template <typename ObjectType, typename	ValueType>
class FilterWithCriterion : public Filter <ObjectType> {
	Criterion<ObjectType,ValueType>* criterion_;
public:
	FilterWithCriterion(Criterion<ObjectType, ValueType>* criterion);
	~FilterWithCriterion();
	bool pass(ObjectType& obj) const override;
	//Criterion<ObjectType, ValueType>& getCriterion() const override;
protected:
	virtual bool passFilter(const ValueType value) const= 0;
};

template<typename ObjectType, typename ValueType>
inline FilterWithCriterion<ObjectType, ValueType>::FilterWithCriterion(Criterion<ObjectType, ValueType>* criterion) :
	 criterion_(criterion)
{
}

template<typename ObjectType, typename ValueType>
inline FilterWithCriterion<ObjectType, ValueType>::~FilterWithCriterion()
{
	delete criterion_;
	criterion_ = nullptr;
}

template<typename ObjectType, typename ValueType>
inline bool FilterWithCriterion<ObjectType, ValueType>::pass(ObjectType& obj) const
{
	return passFilter(criterion_->evaluate(obj));
}

//template<typename ObjectType, typename ValueType>
//inline Criterion<ObjectType, ValueType>& FilterWithCriterion<ObjectType, ValueType>::getCriterion() const
//{
//	return criterion_;
//}




