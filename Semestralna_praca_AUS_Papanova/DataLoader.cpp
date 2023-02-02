#include "DataLoader.h"
#include <iostream>
#include <string>
#include <io.h>
#include <fcntl.h>
#include "../structures/heap_monitor.h"

void DataLoader::loadTeritorialUnit(table& sup, table& table, const string& path, int p_type)
{
	int size = sup.size();

	locale svk("sk_SK.UTF-8");
	wfstream fileStream;
	fileStream.imbue(svk);
	_setmode(_fileno(stdout), _O_U16TEXT);
	std::filebuf file;
	fileStream.open(path);
	if (fileStream.is_open()) {
		wstring line;
		wstring word;
		//structures::ArrayList<wstring*>* atributes = new structures::ArrayList<wstring*>();
		//ARL preto ze sa potrebujem dostat na konkretny index, zaroven postupne pridavat data bez pamatania indexu
		int position = 0;
		wchar_t delim = L';';
		wchar_t space = 65279; //ascii znak
		wchar_t end = '\0'; //ascii znak
		int counter = 0;
		TeritorialUnit* tu = nullptr;
		while (std::getline(fileStream, line)) {
			 tu = new TeritorialUnit();
			tu->setType(p_type);

			for (auto sign : line) {

				if (sign != delim && sign != space) {
					word += sign;
				}
				else  if (sign != space) {

					switch (counter)
					{
					case 0:
						tu->setSortNumber(stoi(word));
						break;
					case 1:
						tu->setCode(word);
						break;
					case 2:
						tu->setOfficialTitle(word);
						break;
					case 3:
						tu->setMediumTitle(word);
						break;
					case 4:
						tu->setShortTitle(word);
						break;
					
					default:
						break;
					}
					word.clear();
					counter++;
				}
			}
				
			tu->setNote(word);
			word.clear();

			wstring space = L", ";
			wstring ofT = tu->getOfficialTitle();
			wstring codee = tu->getCode();
			if (tu->getCode().substr(0, 5) != L"SKZZZ") {
					if (!table.insertBool(tu->getOfficialTitle(),tu) && p_type == 0) {	
						for (auto d : sup) {
							if (tu->getCode().find(d->accessData()->getCode()) == 0) {
								ofT = tu->getOfficialTitle() +  L" (" + d->accessData()->getOfficialTitle() + L")";
							}
						}
						table.insertBool(ofT, tu);
					}
					auto tu = table.find(ofT);
			
				connectUnits(*tu, sup);
			}
			else {
				delete tu;
			}
			ofT.clear();
			counter = 0;
			tu = nullptr;
		}
		fileStream.close(); 
	}

}

void DataLoader::loadInfo(structures::SortedSequenceTable<wstring, structures::Array<int>*>& edu, structures::SortedSequenceTable<wstring, structures::CoherentMatrix<int>*>& age, const string& pathEdu, const string& pathAge)
{
	locale svk("sk_SK.UTF-8");
	wfstream fileStream;
	fileStream.imbue(svk);
	_setmode(_fileno(stdout), _O_U8TEXT);
	fileStream.open(pathEdu);

	wstring line;
	wstring word;
	int position = 0;
	wchar_t delim = L';';
	wchar_t space = 65279; //ascii znak

	if (fileStream.is_open()) {
		int wordIndex = 0;
		structures::Array<int>* education;// = new structures::Array<int>(8);
		while (std::getline(fileStream, line)) {
			education = new structures::Array<int>(8);
			wstring code;
			for (auto sign : line) {

				if (sign != delim && sign != space) {
					word += sign;
				}
				else  if (sign != space) {
					if (wordIndex == 0) {
						code = word;
					}
					else if (wordIndex > 1) {
						wstring infoS = word;
						int info = stoi(infoS);
						education->at(wordIndex - 2) = info;
					}
					wordIndex++;
					word.clear();
				}
			}
			if (code.substr(0, 5) != L"SKZZZ") {
				education->at(wordIndex - 2) = stoi(word);
				edu.insert(code, new structures::Array<int>(*education));
				//wcout << code << L" " << edu.find(code)->at(0) << L" " << edu.find(code)->at(1) << L" " << edu.find(code)->at(2) << L" " << edu.find(code)->at(3) << L" " << edu.find(code)->at(4) << L" " << edu.find(code)->at(5) << L" " << edu.find(code)->at(6) << L" " << edu.find(code)->at(7) << L" " << endl;
				wordIndex = 0;
				word.clear();
			}

			delete education;

		}
		fileStream.close();
	}

	fileStream.open(pathAge);
	if (fileStream.is_open()) {

		int wordIndex = 0;
		//structures::CoherentMatrix<int>* age_t = new structures::CoherentMatrix<int>(2, 202);

		structures::CoherentMatrix<int>* age_t;// = new structures::CoherentMatrix<int>(2, 101);
		int j = 0;
		int i = 0;
		while (std::getline(fileStream, line)) {
			age_t = new structures::CoherentMatrix<int>(2, 202);
			wstring code;
			for (auto sign : line) {
				if (sign != delim && sign != space) {
					word += sign;
				}
				else  if (sign != space) {
					if (wordIndex == 0) {
						code = word;
					}
					else if (wordIndex > 1) {
						int i_age = stoi(word);
						age_t->at(i, j) = i_age;
							j++;
					
					}
					if (j == 101) {
						j = 0;
						i = 1;
					}
					word.clear();
					wordIndex++;
				}

			}
				int a = stoi(word);
				age_t->at(i, j) = a;
				i = 0;
				j = 0;
				age.insert(code, new structures::CoherentMatrix<int>(*age_t));
			delete age_t;
			//wcout << code << L"M " << age.find(code)->at(0, 0) << L" " << age.find(code)->at(0, 1) << L" " << age.find(code)->at(0, 2) << L" " << age.find(code)->at(0, 3) << L" " << age.find(code)->at(0, 4) << L" " << age.find(code)->at(0, 98) << L" " << age.find(code)->at(0, 99) << L" " << age.find(code)->at(0, 100) << L" " << endl;
			//wcout << code << L"Z " << age.find(code)->at(1, 0) << L" " << age.find(code)->at(1, 1) << L" " << age.find(code)->at(1, 2) << L" " << age.find(code)->at(1, 3) << L" " << age.find(code)->at(1, 4) << L" " << age.find(code)->at(1, 98) << L" " << age.find(code)->at(1, 99) << L" " << age.find(code)->at(1, 100) << L" " << endl;
			wordIndex = 0;
			word.clear();
		}
		//delete age_t;
		fileStream.close();
	}

	
}



void DataLoader::connectUnits(TeritorialUnit& tu, table& sup)
{
	int type = tu.getType();
	switch (type) {
	case 0:
		conncetDistToTowns(tu, sup);
		break;
	case 1:
		connectRegToDist(tu, sup);
		break;
	case 2:
		connectRegToState(tu, sup);
		break;
	}
}

void DataLoader::connectInfo(table& towns, structures::SortedSequenceTable<wstring, structures::Array<int>*>& edu, structures::SortedSequenceTable<wstring, structures::CoherentMatrix<int>*>& age)
{
	structures::Array<int>* edu_t = nullptr;
	structures::CoherentMatrix<int>* age_t = nullptr;
	for (auto town : towns) {
		std::wstring code = town->accessData()->getCode();


		if (edu.tryFind(code, edu_t)) {
			town->accessData()->setPtrEducation(*edu_t);
		}
		if (age.tryFind(code, age_t)) {
			town->accessData()->setPtrAge(*age_t);
		}
	}	

}


void DataLoader::connectRegToState(TeritorialUnit& reg, table& state)
{
	TeritorialUnit* slovakia = state.find(L"Slovenska Republika");
	slovakia->getSubgroup().add(&reg);
	reg.setSuperior(*slovakia);
}

void DataLoader::connectRegToDist(TeritorialUnit& dist, table& reg)
{
	wstring key = dist.getCode().substr(0, 5);
	for (auto r : reg) {
		wstring node = r->accessData()->getNote().substr(5, 5);
		if (node == key) {
			r->accessData()->getSubgroup().add(&dist);
			dist.setSuperior(*r->accessData());
			return;
		}
	}
}

void DataLoader::conncetDistToTowns(TeritorialUnit& town, table& dist)
{
	wstring key = town.getCode().substr(0, 6);
	for (auto d : dist) {
		if (d->accessData()->getCode() == key) {
			d->accessData()->getSubgroup().add(&town);
			town.setSuperior(*d->accessData());
			
			return;
		}
	}
}








