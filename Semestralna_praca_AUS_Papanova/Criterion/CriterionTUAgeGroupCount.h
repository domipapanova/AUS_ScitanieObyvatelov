#pragma once
#include "CriterionTeritorialUnit.h"

class CriterionTUAgeGroupCount : public CriterionTeritorialUnit <std::wstring> {
	int evaluate(TeritorialUnit& obj);
};

int CriterionTUAgeGroupCount::evaluate(TeritorialUnit& obj)
{
	return 0;
}
