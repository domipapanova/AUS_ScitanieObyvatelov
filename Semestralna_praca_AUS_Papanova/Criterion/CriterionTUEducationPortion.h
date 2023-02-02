#pragma once
#include "CriterionTeritorialUnit.h"

class CriterionTUEducationPortion : public CriterionTeritorialUnit <std::wstring> {
	double evaluate(TeritorialUnit& obj);
};

double CriterionTUEducationPortion::evaluate(TeritorialUnit& obj)
{
	return 0;
}
