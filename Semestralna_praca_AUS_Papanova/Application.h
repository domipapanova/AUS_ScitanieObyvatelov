#pragma once
#include "DataCenter.h"
#include "Filtration.h"
#include "CriterionTU.h"
#include "Education.h"
#include "Type.h"
#include "ANDfilter.h"
#include "Sorting.h"
#include "../structures/heap_monitor.h"
#include <string>
#include <iostream>
#include <fcntl.h>
#include <io.h>
#include "../structures/list/linked_list.h"

class Application
{
	DataCenter* data_;
	Filtration* filter_;
	EduTrans* education_;
	structures::UnsortedSequenceTable<std::wstring, TeritorialUnit*>* result_;
	structures::LinkedList<std::wstring>* indexes_;


public:
	Application();
	~Application();
	void findInfoAbout(Type type, std::wstring name);
	void filterBy(Type type);
	void sortBy(Type type);
	void outputCriterion(structures::UnsortedSequenceTable<std::wstring, TeritorialUnit*>& table);
	void clearTables();
};

