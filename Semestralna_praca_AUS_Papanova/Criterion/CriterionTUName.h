#pragma once
#include "CriterionTeritorialUnit.h"

class CriterionTUName : public CriterionTeritorialUnit <std::wstring>  {
	std::wstring evaluate(TeritorialUnit& obj);
};

std::wstring CriterionTUName::evaluate(TeritorialUnit& obj)
{
	return obj.getMediumTitle();
}
