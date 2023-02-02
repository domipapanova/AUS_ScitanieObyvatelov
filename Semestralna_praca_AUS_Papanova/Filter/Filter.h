#pragma once
template <typename ObjectType>
class Filter {
public:
	virtual ~Filter() = default;
	virtual bool pass(ObjectType& object) const  = 0;
	//virtual Criterion<ObjectType, ValueType>& getCriterion() const = 0;
};
