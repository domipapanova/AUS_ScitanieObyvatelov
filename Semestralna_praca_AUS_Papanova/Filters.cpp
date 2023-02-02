#include "Filters.h"
//<summary> filter TYP
FilterType::FilterType(int type) :
	FilterValueCheck(new CriterionTUType(), type)
{
}

//<summary> filter PRISLUSNOST
FilterAffiliation::FilterAffiliation(TeritorialUnit& sup) :
	FilterValueCheck(new CriterionTUAffiliation(sup), true)
{
}

//<summary> filter VZDELANIE POCET
FilterEduCount::FilterEduCount(int edu, int min, int max) :
	FilterInterval(new CriterionTUEducationCount(edu), min, max)
{
}


//<summary> filter VZDELANIE PODIEL
FilterEduPortion::FilterEduPortion(int edu, double min, double max) :
	FilterInterval(new CriterionTUEducationPortion(edu), min, max)
{
}

FilterAgePortion::FilterAgePortion(int age, int gender, double min, double max) :
	FilterInterval(new CriterionTUAgePortion(age, gender), min, max)
{
}

FilterAgeCount::FilterAgeCount(int age, int gender, int min, int max) :
	FilterInterval(new CriterionTUAgeCount(age, gender), min, max)

{
}

FilterAgeGroupPortion::FilterAgeGroupPortion(int ageG, double min, double max) :
	FilterInterval(new CriterionTUAgeGroupPortion(ageG), min, max)

{
}

FilterAgeGroupCount::FilterAgeGroupCount(int ageG, int min, int max) :
	FilterInterval(new CriterionTUAgeGroupCount(ageG), min, max)

{
}

