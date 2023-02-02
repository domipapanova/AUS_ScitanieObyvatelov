#pragma once
#include "CriterionTeritorialUnit.h"

class CriterionTUAffiliation : public CriterionTeritorialUnit <std::wstring> {
public:
	bool evaluate(TeritorialUnit& obj);
};

bool CriterionTUAffiliation::evaluate(TeritorialUnit& obj)
{
	return false;
}
