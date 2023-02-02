#pragma once

template <typename ObjectType, typename ResultType>
class Criterion 
{
public:
	virtual ResultType evaluate(ObjectType& object) const = 0;
};
