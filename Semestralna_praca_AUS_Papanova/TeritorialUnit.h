#pragma once
#include  "../structures/list/array_list.h"
#include  "../structures/matrix/coherent_matrix.h"
#include "../structures/heap_monitor.h"
//#include <numeric>
class TeritorialUnit
{
	//const int MUZI = 0;
	//const int ZENY = 1;
	static const int COUNT_OF_EDUCATION_ATRIBUTES = 8;
	static const int COUNT_OF_AGE_ATRIBUTES = 202;

	int sortNumber_;
	std::wstring code_;
	std::wstring officialTitle_;
	std::wstring mediumTitle_;
	std::wstring shortTitle_;
	std::wstring note_;
	// 0 - township, 1 - distinct, 2 - region
	int type_;

	TeritorialUnit* superior_; // nadriadeny uzemny celok
	structures::ArrayList<TeritorialUnit*>* subgroup_; // podriadeny uzemny celok
	structures::Array<int>* education_;  // pocet v danej kategorii vzdelania pre danu uzemnu jednotku
	structures::CoherentMatrix<int>* age_; // 0- riadok muzi, 1-riadok zeny , stlpce vek od 0 po 100

public:
	TeritorialUnit();
	//TeritorialUnit(int sortNumber, std::wstring code, std::wstring officialTitle, std::wstring mediumTitle, std::wstring shortTitle, std::wstring note, int type);
	~TeritorialUnit();
	const int& getSortNumber();
	const int& getType();
	const std::wstring& getNote();
	const std::wstring& getMediumTitle();
	const std::wstring& getOfficialTitle();
	const std::wstring& getShortTitle();
	const std::wstring& getCode();
	const int getAgeAt(int col, int row);
	const int getEduAt(int index);
	TeritorialUnit& getSuperior(); // nie je const aby som sa dostala k nazvu
	//const structures::ArrayList<TeritorialUnit*>& getSubgroup();
	 structures::ArrayList<TeritorialUnit*>& getSubgroup();

	void setSuperior(TeritorialUnit& tu);
	void setSubgroup(structures::ArrayList<TeritorialUnit*>* subs);
	void setSortNumber(int srN);
	void setType(int type);
	void setNote(std::wstring note);
	void setMediumTitle(std::wstring note);
	void setOfficialTitle(std::wstring note);
	void setShortTitle(std::wstring note);
	void setCode(std::wstring note);


	//const structures::Array<int>& getEducation();
	//const structures::CoherentMatrix<int>& getAge();
	void addEducation(int index, int info);
	void addAge(int colum, int row, int info);
	void setPtrEducation(structures::Array<int>& p_education);
	void setPtrAge(structures::CoherentMatrix<int>& p_age);
	void setEducation(structures::Array<int>& p_education);
	void setAge(structures::CoherentMatrix<int>& p_age);
	int getNumberOfInhabitnEDU();
	int getNumberOfInhabitnAGE();

	bool isSubNull();
};



