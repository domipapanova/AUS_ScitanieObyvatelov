#pragma once
#include "Filter/FilterValueCheck.h"
#include "FilterInterval.h"
#include "Education.h"
#include "CriterionTU.h"
class FilterType : public FilterValueCheck<TeritorialUnit, int> {
public:
	FilterType(int type);
};

class FilterAffiliation : public FilterValueCheck<TeritorialUnit, bool> {
public:
	FilterAffiliation(TeritorialUnit& sup);
};

class FilterEduCount : public FilterInterval<TeritorialUnit, int> {
public:
	FilterEduCount(int edu, int min, int max);
};

class FilterEduPortion : public FilterInterval<TeritorialUnit, double> {
public:
	FilterEduPortion(int edu, double min, double max);

};

class FilterAgeCount : public FilterInterval<TeritorialUnit, int> {
public:
	FilterAgeCount(int age,int gender,  int min, int max);
};

class FilterAgePortion : public FilterInterval<TeritorialUnit, double> {
public:
	FilterAgePortion(int age, int gender,  double min, double max);

};

//class FilterAgeCount : public FilterInterval<TeritorialUnit, int> {
//public:
//	FilterAgeCount(int age, int gender, int min, int max);
//};
//
class FilterAgeGroupPortion : public FilterInterval<TeritorialUnit, double> {
public:
	FilterAgeGroupPortion(int ageG, double min, double max);

};

class FilterAgeGroupCount : public FilterInterval<TeritorialUnit, int> {
public:
	FilterAgeGroupCount(int ageG, int min, int max);
};