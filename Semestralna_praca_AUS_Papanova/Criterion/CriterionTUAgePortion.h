#pragma once
#include "CriterionTeritorialUnit.h"

class CriterionTUAgePortion : public CriterionTeritorialUnit <std::wstring> {
	double evaluate(TeritorialUnit& obj);
};

double CriterionTUAgePortion::evaluate(TeritorialUnit& obj)
{
	return 0;
}