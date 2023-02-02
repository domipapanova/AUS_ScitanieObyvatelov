#pragma once
#include "../structures/table/sorted_sequence_table.h"
#include "../structures/table/unsorted_sequence_table.h"
#include "Filters.h"
#include "CompositeFilter.h"
#include "ANDfilter.h"
class Filtration
{
public:
	structures::UnsortedSequenceTable<std::wstring, TeritorialUnit*>& compositeFiltration(structures::SortedSequenceTable<std::wstring, TeritorialUnit*>* table ,structures::ArrayList<Filter<TeritorialUnit>*>* filters );

};

inline structures::UnsortedSequenceTable<std::wstring, TeritorialUnit*>& Filtration::compositeFiltration(structures::SortedSequenceTable<std::wstring, TeritorialUnit*>* table, structures::ArrayList<Filter<TeritorialUnit>*>* filters)
{
	filterAND<TeritorialUnit>*andFilter = new filterAND<TeritorialUnit>();
	structures::UnsortedSequenceTable<std::wstring, TeritorialUnit*>* result = new  structures::UnsortedSequenceTable<std::wstring, TeritorialUnit*>();

	for (auto filter : *filters) {
		andFilter->registerFilter(filter);
	}

	for (auto item : *table) {
		
		if (andFilter->pass(*item->accessData())) {
			result->insert(item->getKey(), item->accessData());
			
		}
	}
	delete andFilter;

	return *result;
}


