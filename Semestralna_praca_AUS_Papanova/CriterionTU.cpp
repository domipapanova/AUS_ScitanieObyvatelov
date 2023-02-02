#include "CriterionTU.h"
using namespace std;


CriterionTUAffiliation::CriterionTUAffiliation(TeritorialUnit& superior) :
	superior_(&superior)
{
}

bool CriterionTUAffiliation::evaluate(TeritorialUnit& obj) const
{
	if (superior_->getType() == 3) {
		return true;
	}
	else if (superior_->getType() == 2) {
		int finded = obj.getCode().find(superior_->getNote().substr(6, 5));
		return finded != -1;
	}
	else {
		int finded = obj.getCode().find(superior_->getCode());
		return finded != -1;
	}

}

 CriterionTUAgeCount::CriterionTUAgeCount(int age, int gender) :
	age_(age), gender_(gender)
{
}

int CriterionTUAgeCount::evaluate(TeritorialUnit& obj)  const
{
	return obj.getAgeAt(age_, gender_);

}



CriterionTUAgeGroupPortion::CriterionTUAgeGroupPortion(int ageGroup) :
	ageGroup_(ageGroup)
{

}

double CriterionTUAgeGroupPortion::evaluate(TeritorialUnit& obj) const
{
	double sum = 0;

	if (ageGroup_ == 0) {

		for (int i = 0; i < 15; i++)
		{
			sum += static_cast<double>(obj.getAgeAt(i, 0));
			sum += static_cast<double>(obj.getAgeAt(i, 1));
		}
	}
	else if (ageGroup_ == 1) {

		for (int i = 15; i < 65; i++)
		{
			sum += static_cast<double>(obj.getAgeAt(i, 0));
			sum += static_cast<double>(obj.getAgeAt(i, 1));

		}
	}
	else if (ageGroup_ == 2) {

		for (int i = 65; i < 101; i++)
		{
			sum += static_cast<double>(obj.getAgeAt(i, 0));
			sum += static_cast<double>(obj.getAgeAt(i, 1));

		}
	}

	return sum / static_cast<double>(obj.getNumberOfInhabitnAGE()) * 100;
}



CriterionTUAgePortion::CriterionTUAgePortion(int age, int gender) :
	age_(age), gender_(gender)
{
}

double CriterionTUAgePortion::evaluate(TeritorialUnit& obj) const
{
	return (static_cast<double>(obj.getAgeAt(age_, gender_)) / static_cast<double>(obj.getNumberOfInhabitnEDU())) * 100;
}

CriterionTUEducationCount::CriterionTUEducationCount(int education) :
	edu_(education)
{
}
int CriterionTUEducationCount::evaluate(TeritorialUnit& obj) const
{
	return obj.getEduAt(edu_);
}



CriterionTUEducationPortion::CriterionTUEducationPortion(int education) :
	education_(education)
{
}

double CriterionTUEducationPortion::evaluate(TeritorialUnit& obj) const
{
	return (static_cast<double>(obj.getEduAt(education_)) / static_cast<double>(obj.getNumberOfInhabitnEDU())) * 100;
}



std::wstring CriterionTUName::evaluate(TeritorialUnit& obj) const
{
	return obj.getOfficialTitle();
}


TeritorialUnit* CriterionTUSuperior::evaluate(TeritorialUnit& obj) const
{
	return &obj.getSuperior();
}


int CriterionTUType::evaluate(TeritorialUnit& obj) const
{
	return obj.getType();
}

CriterionTUAgeGroupCount::CriterionTUAgeGroupCount(int ageGroup) :
	ageGroup_(ageGroup)
{
}

int CriterionTUAgeGroupCount::evaluate(TeritorialUnit& obj) const
{
	int sum = 0;

	if (ageGroup_ == 0) {

		for (int i = 0; i < 15; i++)
		{
			sum += obj.getAgeAt(i, 0);
			sum += obj.getAgeAt(i, 1);

		}
	}
	else if (ageGroup_ == 1) {

		for (int i = 15; i < 65; i++)
		{
			sum += obj.getAgeAt(i, 0);
			sum += obj.getAgeAt(i, 1);

		}
	}
	else if (ageGroup_ == 2) {

		for (int i = 65; i < 101; i++)
		{
			sum += obj.getAgeAt(i, 0);
			sum += obj.getAgeAt(i, 1);

		}
	}
	return sum;
}
