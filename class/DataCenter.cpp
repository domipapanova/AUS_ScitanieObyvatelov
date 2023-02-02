#include "DataCenter.h"
typedef typename structures::SortedSequenceTable<std::wstring, TeritorialUnit*> table;


table* DataCenter::findTable(Type type)
{
	switch (type)
	{
	case obec:
		return township_;
		break;
	case okres:
		return district_;
		break;
	case kraj:
		return region_;
		break;
	case krajina:
		return state_;
		break;
	default:
		return nullptr;
		break;
	}
}

TeritorialUnit* DataCenter::findUnit(table* tab, std::wstring name)
{
	TeritorialUnit* unit = nullptr;
	tab->tryFind(name, unit);
	return unit;
}

DataCenter::DataCenter() :
	township_(new structures::SortedSequenceTable<std::wstring, TeritorialUnit*>()), district_(new structures::SortedSequenceTable<std::wstring, TeritorialUnit*>()),
	region_(new structures::SortedSequenceTable<std::wstring, TeritorialUnit*>()), state_(new table()), education_(new structures::SortedSequenceTable<std::wstring, structures::Array<int>*>()),
	age_(new structures::SortedSequenceTable<std::wstring, structures::CoherentMatrix<int>*>())
{
	loadState();
	loadTRegions();
	loadDistricts();
	loadTowns();
}

DataCenter::~DataCenter()
{	
	for (auto item : *education_) {
		delete item->accessData();
		item = nullptr;
		//delete item;
	}
	delete education_;

	for (auto item : *age_) {
		delete item->accessData();
		item = nullptr;

		//delete item;
	}
	delete age_;

	for (auto item : *township_) {
		delete item->accessData();
		item = nullptr;

		//delete item;
	}
	delete township_;

	for (auto item : *district_) {
		delete item->accessData();
		item = nullptr;

		//delete item;
	}
	delete district_;

	for (auto item : *region_) {
		delete item->accessData();
		item = nullptr;

		//delete item;
	}
	delete region_;


	for (auto item : *state_) {
		delete item->accessData();
		item = nullptr;
	}
	delete state_;
	//delete loader;
	age_ = nullptr;
	state_ = nullptr;
	loader = nullptr;
	state_ = nullptr;
	region_ = nullptr;
	district_ = nullptr;
	township_ = nullptr;


}

const structures::SortedSequenceTable<std::wstring, TeritorialUnit*>& DataCenter::getTownship()
{
	return *township_;
}


const structures::SortedSequenceTable<std::wstring, TeritorialUnit*>& DataCenter::getDistricts()
{
	return *district_;
}

const structures::SortedSequenceTable<std::wstring, TeritorialUnit*>& DataCenter::getRegion()
{
	return *region_;
}

 const structures::SortedSequenceTable<std::wstring, TeritorialUnit*>& DataCenter::getState()
{
	return *state_;
}

void DataCenter::loadTowns()
{

	loader->loadTeritorialUnit(*district_,*township_, "D:\\UNIZA\\letny DRUHAK\\AUS\\Semestralka\\AUS_Semestralna_praca\\obce.csv",0);
	loader->loadInfo(*education_, *age_, "D:\\UNIZA\\letny DRUHAK\\AUS\\Semestralka\\AUS_Semestralna_praca\\vzdelanie.csv",
		"D:\\UNIZA\\letny DRUHAK\\AUS\\Semestralka\\AUS_Semestralna_praca\\vek.csv");
	loader->connectInfo(*township_, *education_, *age_);
	addInfoToSuperior();
}

void DataCenter::loadDistricts()
{
	loader->loadTeritorialUnit(*region_,*district_, "D:\\UNIZA\\letny DRUHAK\\AUS\\Semestralka\\AUS_Semestralna_praca\\okresy.csv",1);
}


void DataCenter::loadTRegions()
{
	loader->loadTeritorialUnit(*state_,*region_, "D:\\UNIZA\\letny DRUHAK\\AUS\\Semestralka\\AUS_Semestralna_praca\\kraje.csv",2);
}
void DataCenter::loadState()
{
	TeritorialUnit* tu = new TeritorialUnit();
	tu->setSortNumber(0);
	tu->setOfficialTitle(L"Slovenska Republika");
	tu->setMediumTitle(L"Slovensko");
	tu->setShortTitle(L"Slovensko");
	tu->setNote(L"0");
	tu->setType(3);
	state_->insert(tu->getOfficialTitle(), tu);
}

void DataCenter::addInfoToSuperior()
{
	structures::Array<int>* edu = nullptr;
	structures::CoherentMatrix<int>* age = nullptr;
	for (auto dist : *district_) {
		auto list = dist->accessData()->getSubgroup();
		 edu = new structures::Array<int>(8);
		 age = new structures::CoherentMatrix<int>(2, 202);

		for (auto twn : list) {

			for (int i = 0; i < edu->size(); i++)
			{
				edu->at(i) += twn->getEduAt(i);
			}

			for (int j = 0; j < age->getRowCount(); j++)
			{
				for (int i = 0; i < age->getColumnCount(); i++)
				{
					age->at(j,i) += twn->getAgeAt(i,j);
				}
			}
			
		}
		dist->accessData()->setEducation(*edu);
		dist->accessData()->setAge(*age);
		delete age;
		delete edu;
	}
	
	
	for (auto reg : *region_) {
		auto list = reg->accessData()->getSubgroup();
		structures::Array<int>* edu = new structures::Array<int>(8);
		structures::CoherentMatrix<int>* age = new structures::CoherentMatrix<int>(2, 202);

		for (auto distr : list) {

			for (int i = 0; i < edu->size(); i++)
			{
				edu->at(i) += distr->getEduAt(i);
			}

			for (int j = 0; j < age->getRowCount(); j++)
			{
				for (int i = 0; i < age->getColumnCount(); i++)
				{
					age->at(j, i) += distr->getAgeAt(i, j);
				}
			}

		}
		reg->accessData()->setEducation(*edu);
		reg->accessData()->setAge(*age);
		delete age;
		delete edu;
		
	}

	for (auto sta : *state_) {
		auto list = sta->accessData()->getSubgroup();
		structures::Array<int>* edu = new structures::Array<int>(8);
		structures::CoherentMatrix<int>* age = new structures::CoherentMatrix<int>(2, 202);

		for (auto regi : list) {

			for (int i = 0; i < edu->size(); i++)
			{
				edu->at(i) += regi->getEduAt(i);
			}

			for (int j = 0; j < age->getRowCount(); j++)
			{
				for (int i = 0; i < age->getColumnCount(); i++)
				{
					age->at(j, i) += regi->getAgeAt(i, j);
				}
			}

		}
		sta->accessData()->setEducation(*edu);
		sta->accessData()->setAge(*age);
		delete age;
		delete edu;
	}

}

