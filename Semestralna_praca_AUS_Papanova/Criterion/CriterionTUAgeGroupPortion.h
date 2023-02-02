#pragma once
#include "CriterionTeritorialUnit.h"

class CriterionTUAgeGroupPortion : public CriterionTeritorialUnit <std::wstring> {
	double evaluate(TeritorialUnit& obj);
};

double CriterionTUAgeGroupPortion::evaluate(TeritorialUnit& obj)
{
	return 0;
}