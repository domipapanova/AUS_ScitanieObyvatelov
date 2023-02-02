#include "TeritorialUnit.h"

TeritorialUnit::TeritorialUnit() :
	education_(new structures::Array<int>(8)),
	age_(new structures::CoherentMatrix<int>(2, 202)), superior_(nullptr), subgroup_(new structures::ArrayList<TeritorialUnit*>())
{
}

//TeritorialUnit::TeritorialUnit(int sortNumber, std::wstring code, std::wstring officialTitle, std::wstring mediumTitle, std::wstring shortTitle, std::wstring note, int type) :
//		sortNumber_(sortNumber), code_(code), officialTitle_(officialTitle),
//	mediumTitle_(mediumTitle), shortTitle_(shortTitle), note_(note), education_(new structures::Array<int>(8)),
//	age_(new structures::CoherentMatrix<int>(2, 202)), superior_(nullptr), subgroup_(new structures::ArrayList<TeritorialUnit*>())
//{
//}

//TeritorialUnit::TeritorialUnit(int sortNumber, std::wstring& code, std::wstring& officialTitle, std::wstring& mediumTitle, std::wstring& shortTitle, std::wstring& note, int type) :
//
//	sortNumber_(sortNumber), code_(&code), officialTitle_(&officialTitle),
//	//mediumTitle_(&mediumTitle), shortTitle_(&shortTitle), note_(&note), education_(nullptr),
//	//age_(nullptr), type_(type), superior_(nullptr), subgroup_(nullptr)
//	mediumTitle_(&mediumTitle), shortTitle_(&shortTitle), note_(&note), education_(new structures::Array<int>(8)),
//	age_(new structures::CoherentMatrix<int>(2,202)), type_(type), superior_(nullptr), subgroup_(nullptr)
//{
//}

TeritorialUnit::~TeritorialUnit()
{
	if (type_ != 0) {
		delete age_;
		delete education_;
	}
	//delete note_;
	//delete shortTitle_;
	//delete mediumTitle_;
	//delete officialTitle_;
	//delete code_;
	delete subgroup_;
	//delete superior_;

	superior_ = nullptr;
	subgroup_ = nullptr;
	age_ = nullptr;
	education_ = nullptr;
	//note_ = nullptr;
	//shortTitle_ = nullptr;
	//mediumTitle_ = nullptr;
	//officialTitle_ = nullptr;
	//code_ = nullptr;
	sortNumber_ = 0;
	type_ = 0;
}

const int& TeritorialUnit::getSortNumber()
{
	return sortNumber_;
}

const std::wstring& TeritorialUnit::getNote()
{
	return note_;
}

const int& TeritorialUnit::getType()
{
	return type_;
}

const std::wstring& TeritorialUnit::getMediumTitle()
{
	return mediumTitle_;
}

const std::wstring& TeritorialUnit::getOfficialTitle()
{
	return officialTitle_;
}

const std::wstring& TeritorialUnit::getShortTitle()
{
	return shortTitle_;
}

const std::wstring& TeritorialUnit::getCode()
{
	return code_;
}

const int TeritorialUnit::getAgeAt(int col, int row)
{
	return age_->at(row, col);
}

const int TeritorialUnit::getEduAt(int index)
{
	return education_->at(index);

}

TeritorialUnit& TeritorialUnit::getSuperior()
{
	return *superior_;
}

structures::ArrayList<TeritorialUnit*>& TeritorialUnit::getSubgroup()
{
	return *subgroup_;
}

void TeritorialUnit::setSuperior(TeritorialUnit& tu)
{
	superior_ = &tu;
}

void TeritorialUnit::setSubgroup(structures::ArrayList<TeritorialUnit*>* subs)
{
	subgroup_ = subs;
}

 void TeritorialUnit::setSortNumber(int srN)
{
	sortNumber_ = srN;
}

void TeritorialUnit::setType(int type)
{
	type_ = type;
}

void TeritorialUnit::setNote(std::wstring note)
{
	note_ = note;
}

void TeritorialUnit::setMediumTitle(std::wstring note)
{
	mediumTitle_ = note;
}

void TeritorialUnit::setOfficialTitle(std::wstring note)
{
	officialTitle_ = note;
}

void TeritorialUnit::setShortTitle(std::wstring note)
{
	shortTitle_ = note;
}

void TeritorialUnit::setCode(std::wstring note)
{
	code_ = note;
}


void TeritorialUnit::addEducation(int index, int info)
{
	education_->at(index) = info;
}

void TeritorialUnit::addAge(int colum, int row, int info)
{
	age_->at(row, colum) = info;
}

void TeritorialUnit::setPtrEducation(structures::Array<int>& p_education)
{
	delete education_;
	education_ = &p_education;
}




void TeritorialUnit::setPtrAge(structures::CoherentMatrix<int>& p_age)
{
	delete age_;
	age_ = &p_age;
}

void TeritorialUnit::setEducation(structures::Array<int>& p_education)
{
	//delete education_;
	//education_ = new structures::Array<int>(p_education);
	education_->assign(p_education);
}

void TeritorialUnit::setAge(structures::CoherentMatrix<int>& p_age)
{
	//delete age_;
	//age_ = new structures::CoherentMatrix<int>(p_age);
	age_->assign(p_age);
}

int TeritorialUnit::getNumberOfInhabitnEDU()
{
	int sum = 0;
	for (int i = 0; i < education_->size(); i++) {
		sum += education_->at(i);
	}
	if (sum == 0) {
		sum = 1;
	}
	return sum;
	
}

bool TeritorialUnit::isSubNull()
{
	return subgroup_ == nullptr;
}

