#pragma once
#include "CriterionTeritorialUnit.h"

class CriterionTUEducationCount : public CriterionTeritorialUnit <std::wstring> {
	int evaluate(TeritorialUnit& obj);
};

int CriterionTUEducationCount::evaluate(TeritorialUnit& obj)
{
	return 0;
}
