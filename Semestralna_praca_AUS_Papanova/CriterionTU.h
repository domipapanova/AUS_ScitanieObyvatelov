#pragma once
#include "TeritorialUnit.h"
#include <numeric>
#include"Criterion/CriterionTeritorialUnit.h"


//<summary> kriterium PRISLUSNOST
class CriterionTUAffiliation : public CriterionTeritorialUnit<bool> {
	TeritorialUnit* superior_;
public:
	CriterionTUAffiliation(TeritorialUnit& superior);
	bool evaluate(TeritorialUnit& obj) const override;
};

//<summary> kriterium  VEKOVA SKUPINA PODIEL
class CriterionTUAgeGroupPortion : public CriterionTeritorialUnit<double> {
	int ageGroup_;

public:
	CriterionTUAgeGroupPortion(int ageGroup);
	double evaluate(TeritorialUnit& obj) const override;
};

//<SUMMMARY> kriterium vekova skupina pocet
class CriterionTUAgeGroupCount : public CriterionTeritorialUnit<int> {
	int ageGroup_;
public:
	CriterionTUAgeGroupCount(int ageGroup);
	int evaluate(TeritorialUnit& obj) const override;
};
//<summary> kriterium  VEK POCET
class CriterionTUAgeCount : public CriterionTeritorialUnit<int> {
	int age_;
	int gender_;
public:
	CriterionTUAgeCount(int age, int gender);
	int evaluate(TeritorialUnit& obj) const override;
};

//<summary> kriterium VEK PODIEL
class CriterionTUAgePortion : public CriterionTeritorialUnit<double> {
	int age_;
	int gender_;
public:
	CriterionTUAgePortion(int age, int gender);
	double evaluate(TeritorialUnit& obj) const override;
};

//<summary> kriterium VZDELANIE POCET
class CriterionTUEducationCount : public CriterionTeritorialUnit <int> {
	int edu_;
public:
	CriterionTUEducationCount(int education);
	int evaluate(TeritorialUnit& obj) const override;
};

//<summary> kriterium VZDELANIE PODIEL
class CriterionTUEducationPortion : public CriterionTeritorialUnit<double> {
	int education_;
public:
	CriterionTUEducationPortion(int education);
	double evaluate(TeritorialUnit& obj) const override;
};

//<summary> kriterium NAZOV
class CriterionTUName : public CriterionTeritorialUnit<std::wstring> {
public:
	std::wstring evaluate(TeritorialUnit& obj) const override;
};

//<summary> kriterium NADRADENY
class CriterionTUSuperior : public CriterionTeritorialUnit<TeritorialUnit*> {
public:
	TeritorialUnit* evaluate(TeritorialUnit& obj) const override;
};

//<summary> kriterium TYP
class CriterionTUType : public CriterionTeritorialUnit<int> {
public:
	int evaluate(TeritorialUnit& obj) const override;
};

