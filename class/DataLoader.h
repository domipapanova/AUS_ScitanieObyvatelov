#pragma once
#include <fstream>
#include "TeritorialUnit.h"
#include "../structures/table/sorted_sequence_table.h"

using namespace std;
class DataLoader
{
	//structures::ArrayList<wstring>* duplicityKeys;
public:
	DataLoader() {};
	~DataLoader() {};
	typedef typename structures::SortedSequenceTable<std::wstring, TeritorialUnit*> table;
	void loadTeritorialUnit(table& sup, table& table, const string& path, int p_type);
	void loadInfo(structures::SortedSequenceTable<wstring, structures::Array<int>*>& edu, structures::SortedSequenceTable<wstring, structures::CoherentMatrix<int>*>& age, const string& pathEdu, const string& pathAge);

	void connectUnits(TeritorialUnit& tu, table& sup);
	void connectInfo(table& towns, structures::SortedSequenceTable<wstring, structures::Array<int>*>& edu, structures::SortedSequenceTable<wstring, structures::CoherentMatrix<int>*>& age);
private: 
	void connectRegToState(TeritorialUnit& reg, table& state);
	void connectRegToDist(TeritorialUnit& dist, table& reg);
	void conncetDistToTowns(TeritorialUnit& town, table& dist);
	//wstring createWideNameTwn(table& dist, std::wstring* townNode, std::wstring* officialTitle);
};

