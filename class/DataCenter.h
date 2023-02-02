#pragma once
#include <string>
#include "../structures/table/sorted_sequence_table.h"
#include "../structures/list/array_list.h"
#include"../structures/array/array.h"
#include"../structures/matrix/coherent_matrix.h"
#include "../structures/heap_monitor.h"
#include "Type.h"
#include "TeritorialUnit.h"
#include "DataLoader.h"
class DataCenter
{
public:
	typedef typename structures::SortedSequenceTable<std::wstring, TeritorialUnit*> table;
private:

	table* township_; //obce podla mena - bodove vyhladavanie
	table* district_; //okres
	table* region_; //kraj
	table* state_; //stat
	DataLoader* loader;
	structures::SortedSequenceTable<wstring, structures::Array<int>*>* education_;
	structures::SortedSequenceTable<wstring, structures::CoherentMatrix<int>*>* age_;
public:
	table* findTable(Type type);
	TeritorialUnit* findUnit(table* tab, std::wstring name);
	DataCenter();
	~DataCenter();
	const table& getTownship();
	const table& getDistricts();
	const table& getRegion();
	const table& getState();
private:
	void loadTowns();
	void loadDistricts();
	void loadTRegions();
	void loadState();
	void addInfoToSuperior();
};

