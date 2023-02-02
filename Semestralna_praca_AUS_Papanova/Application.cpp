#include "Application.h"
#include "Type.h"
#include "AgeGroup.h"
using namespace structures;

Application::Application() :
	data_(new DataCenter()), filter_(new Filtration()), education_(new EduTrans()),
	result_(nullptr), indexes_(new structures::LinkedList<std::wstring>())
{
}


Application::~Application()
{
	delete filter_;
	delete education_;
	delete data_;
	//delete result_;
	delete indexes_;
	filter_ = nullptr;
	education_ = nullptr;
	data_ = nullptr;
	result_ = nullptr;
	indexes_ = nullptr;
}

void Application::findInfoAbout(Type type, std::wstring name)
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);

	TeritorialUnit* tu = data_->findUnit(data_->findTable(type),name);
	EduTrans* translator = new EduTrans();
	TypeTrans* translator2 = new TypeTrans();
	AgeGTrans* translatorA = new AgeGTrans();


	if (tu != nullptr) {
		CriterionTUName* name = new CriterionTUName();
		CriterionTUType* type = new CriterionTUType();

		wcout << L"Názov: " << name->evaluate(*tu) << endl;
		wcout << L"Typ územnej jednotky: " << translator2->typeOUTString(type->evaluate(*tu)) << endl;
		wcout << L"Patrí pod:" << endl;

		TeritorialUnit* tu2 = &tu->getSuperior();
		int sup_count = 3 - type->evaluate(*tu);

		for (int i = 0; i < sup_count; i++)
		{
			wcout << translator2->typeOUTString(type->evaluate(*tu2)) << L": " << name->evaluate(*tu2) << endl;
			tu2 = &tu2->getSuperior();
		}
		wcout << L"Vzdelanie: " << endl;
		for (int i = 0; i < 8; i++) {
			CriterionTUEducationCount* count = new CriterionTUEducationCount(i);
			wcout << translator->educationOUTString(i) << L" : " << count->evaluate(*tu) << endl;
			delete count;
		}

		wcout << L"Vekova skupina: " << endl;
		
		for (int i = 0; i < 3; i++) {
			CriterionTUAgeGroupCount* count = new CriterionTUAgeGroupCount(i);
			wcout << translatorA->ageGroupOUTString(i) << L" : " << count->evaluate(*tu) << endl;
			delete count;
		}
		delete name;
		delete type;

	}
	else {
		wcout << L"¼utujeme, zadaná územná jednotka sa nenašla" << endl;
	}
	wcout << endl;

	delete translator;
	delete translator2;
	delete translatorA;

}

void Application::filterBy(Type type)
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);

	structures::SortedSequenceTable<std::wstring, TeritorialUnit*>* table = data_->findTable(type);		
	structures::ArrayList<Filter<TeritorialUnit>*>* user_filters = new structures::ArrayList<Filter<TeritorialUnit>*>();


	bool addFilter = true;
	int kategoria;
	do {
		wcout << L"Vyber si filter z možností: " << endl;

		wcout << L" -> Filter podla prislusnosti: 0 " << endl;
		wcout << L" -> Informacie o poète ¾udí  pre typ vzdelania: 1 " << endl;
		wcout << L" -> Percentualne vyjadrenie poètu ¾udi pre typ vzdelania v škále od-do: 2 " << endl;
		wcout << L" -> Pocet ludo v danom  veku muzov alebo zien v škále od-do: 3 " << endl;
		wcout << L" -> Percentualne vyjadrenie veku muzov alebo zien v škále od-do: 4 " << endl;
		wcout << L" -> Percentualne vyjadrenie vekovej skupiny: 5 " << endl;
		wcout << L" -> Pocet ludi  vo vekovej skupine: 6 " << endl;

		wstring typ;
		getline(std::wcin, typ);
		int typInt = stoi(typ);
		indexes_->add(typ);

		if (typInt == 0) {
			wcout << L"Zadajte typ vyssieho celku" << endl;
			wcout << L"Zvolte typ územnej jednotky, o ktorej chcete informacie:" << endl;
			wcout << L"Pre zadaj:" << endl;
			wcout << "   - obec: 0" << endl;
			wcout << "	 - okres: 1" << endl;
			wcout << "	 - kraj: 2" << endl;
			wcout << "	 - krajina: 3" << endl;
			Type type;
			wstring typ;
			getline(std::wcin, typ);
			int typInt = stoi(typ);
			switch (typInt)
			{
			case 0:
				type = obec;
				break;
			case 1:
				type = okres;
				break;
			case 2:
				type = kraj;
				break;
			case 3:
				type = krajina;
				break;

			}
			auto table = data_->findTable(type);

			wcout << L"Zadajte nazov vyssieho celku" << endl;
			wstring sup;
			getline(std::wcin, sup);
			indexes_->add(sup);
			TeritorialUnit* tu = nullptr;
			if (table->tryFind(sup, tu)) {
				user_filters->add(new FilterAffiliation(*tu));
			}
		} else 
			if (typInt == 1 || typInt == 2) {
				wcout << L" -> Informacie o poète ¾udí  pre typ vzdelania" << endl;
				wcout << L"Vyberte kategoriu: " << endl;
				wcout << L" 0-bez ukonèeného vzdelania, 1-základná vzdelanie, 2-stredné odborné (bez maturity)" << endl;
				wcout << L" 3-úplné stredne vzdelanie(s maturitou), 4-vyššie odborné vzdelanie, 5-vysokoškolské vzdelanie (bez maturity)" << endl;
				wcout << L" 6-bez školského vzdelania ( 15r a viac ), 7-nezistené" << endl;

				wstring edu;
				getline(std::wcin, edu);
				kategoria = stoi(edu);
				indexes_->add(edu);

				wcout << "Interval od: " << endl;
				wstring od;
				getline(std::wcin, od);


				wcout << "Interval do: " << endl;
				wstring doStr;
				getline(std::wcin, doStr);


				if (typInt == 1) {
					int doInt = stoi(doStr);
					int odInt = stoi(od);
					user_filters->add(new FilterEduCount(kategoria, odInt, doInt));

				}
				else {
					double doDouble = stod(doStr);
					double odDouble = stoi(od);
					user_filters->add(new FilterEduPortion(kategoria, odDouble, doDouble));
				}
			}
			else if (typInt == 3 || typInt == 4) {
				wcout << L" -> Informacie o veku pre muzov alebo zeny" << endl;
				wcout << L"Zadajte vek v intervale <0,100>" << endl;
				wstring vekS;
				getline(std::wcin, vekS);
				indexes_->add(vekS);

				int vek = stoi(vekS);
				wcout << L"Vyberte pohlavie:" << endl;
				wcout << L"zena: 1" << endl;
				wcout << L"muz: 0" << endl;

				wstring genderS;
				getline(std::wcin, genderS);
				int gender = stoi(genderS);
				indexes_->add(genderS);

			
				wcout << "Interval od: " << endl;
				wstring od;
				getline(std::wcin, od);

				wcout << "Interval do: " << endl;
				wstring doStr;
				getline(std::wcin, doStr);

				if (typInt == 3) {
					int doInt = stoi(doStr);
					int odInt = stoi(od);
					user_filters->add(new FilterAgeCount(vek, gender, odInt, doInt));

				}
				else {
					double doDouble = stod(doStr);
					double odDouble = stoi(od);
					user_filters->add(new FilterAgePortion(vek, gender, odDouble, doDouble));
				}
			}
			else if (typInt == 5 || typInt == 6) {
				wcout << L" -> Informacie o vekovej skupine" << endl;
				wcout << L"Zadajte vekovu skupinu" << endl;
				wcout << L"predproduktivni - 0" << endl;
				wcout << L"produktivni - 1" << endl;
				wcout << L"poproduktivni - 2" << endl;

				wstring skupinaS;
				getline(std::wcin, skupinaS);
				int skupina = stoi(skupinaS);
				indexes_->add(skupinaS);

				wcout << "Interval od: " << endl;
				wstring od;
				getline(std::wcin, od);

				wcout << "Interval do: " << endl;
				wstring doStr;
				getline(std::wcin, doStr);

				if (typInt == 6) {
					int doInt = stoi(doStr);
					int odInt = stoi(od);
					user_filters->add(new FilterAgeGroupCount(skupina, odInt, doInt));
				}
				else {
					double doDouble = stod(doStr);
					double odDouble = stod(od);
					user_filters->add(new FilterAgeGroupPortion(skupina, odDouble, doDouble));
				}
			}

			wcout << L"Prajete si pridat dalsie filre? - zadaj ano " << endl;
			wcout << L"Pre zobrazenie vysledku filtrovania - zadaj nie" << endl;
			wstring end;
			getline(std::wcin, end);
			if (end == L"nie") {
				addFilter = false;
			}
		

	} while (addFilter);
	
	structures::UnsortedSequenceTable<std::wstring, TeritorialUnit*>* resultTable = nullptr;
	resultTable = &filter_->compositeFiltration(table, user_filters);


	if (resultTable->size() != 0) {
		outputCriterion(*resultTable);

	}
	else {
		wcout << "Filter nenasiel data , ktore by splnali zadane kriteria" << endl;
	}
	
	for (auto item : *user_filters)
	{
		delete item;
	}
	
	delete user_filters;
	result_ = resultTable;
}


void Application::sortBy(Type type)
{
	structures::SortedSequenceTable<std::wstring, TeritorialUnit*>* table = data_->findTable(type);
	//structures::ArrayList<Filter<TeritorialUnit>*>* user_filters = new structures::ArrayList<Filter<TeritorialUnit>*>();
	UnsortedSequenceTable<std::wstring, TeritorialUnit*>* filtredTab = nullptr;


	bool addFilter = true;
	int kategoria;
	wcout << L"Vyberte kritérium pod¾a ktorého chcete triedi " << endl;
	wcout << L" -> Názov územnej jednotky: 7 " << endl;
	wcout << L" -> Pocet vzdelanych v konkretnom type vzdelania:  1 " << endl;
	wcout << L" -> Podiel vzdelanych: v konkretnom type vzdelania: 2 " << endl;
	wcout << L" -> Podiel muzov/zien v danom veku:  4 " << endl;
	wcout << L" -> Vekova skupina pocet  6" << endl;
	
	//TODO KRITERIUM ZVOL  VZDELANIE A ZOSTUPNE TRIEDENIE
	wstring criterion;
	getline(std::wcin, criterion);
	indexes_->add(criterion);
	if (criterion == L"1" || criterion == L"2") {
		wcout << L" -> Informacie o poète ¾udí  pre typ vzdelania" << endl;
		wcout << L"Vyberte kategoriu: " << endl;
		wcout << L" 0-bez ukonèeného vzdelania, 1-základná vzdelanie, 2-stredné odborné (bez maturity)" << endl;
		wcout << L" 3-úplné stredne vzdelanie(s maturitou), 4-vyššie odborné vzdelanie, 5-vysokoškolské vzdelanie (bez maturity)" << endl;
		wcout << L" 6-bez školského vzdelania ( 15r a viac ), 7-nezistené" << endl;

		wstring edu;
		getline(std::wcin, edu);
		kategoria = stoi(edu);
		indexes_->add(edu);

	}

	
	int vek;
	int gender;
	if (criterion == L"4") {
		wcout << L" -> Informacie o veku pre muzov alebo zeny" << endl;
		wcout << L"Zadajte vek v intervale <0,100>" << endl;
		wstring vekS;
		wstring genderS;

		getline(std::wcin, vekS);
		indexes_->add(vekS);

		wcout << L"Vyberte pohlavie:" << endl;
		wcout << L"zena: 1" << endl;
		wcout << L"muz: 0" << endl;

		
		getline(std::wcin, genderS);
		indexes_->add(genderS);

		vek = stoi(vekS);
		gender = stoi(genderS);
	}
	int skupina;

	if (criterion == L"6") {
		wcout << L" -> Informacie o vekovej skupine" << endl;
		wcout << L"Zadajte vekovu skupinu" << endl;
		wcout << L"predproduktivni - 0" << endl;
		wcout << L"produktivni - 1" << endl;
		wcout << L"poproduktivni - 2" << endl;

		wstring skupinaS;
		getline(std::wcin, skupinaS);
		skupina = stoi(skupinaS);
		indexes_->add(skupinaS);
		
	}
	wcout << L" Chcete aplikovat filtre?:" << endl;
	wcout << L"Ano - 0" << endl;
	wcout << L"Nie - 1" << endl;

	wstring f;
	getline(std::wcin, f);
	if (f != L"1") {
		filterBy(type);
		filtredTab = result_;
	}
	else {
		filtredTab = new UnsortedSequenceTable<std::wstring, TeritorialUnit*>();
		for (auto item : *table)
		{
			filtredTab->insert(item->getKey(), item->accessData());
		}
		result_ = filtredTab;
	}

	if (filtredTab->size() != 0) {
		wcout << L"Prajete údaje utriedi vzostupne ? - zadaj ano " << endl;
		wcout << L"zostupne - zadaj nie" << endl;
		wstring srt;
		getline(std::wcin, srt);
		bool sort = true;
		if (srt == L"nie") {
			sort = false;
		}


	

		if (criterion == L"7") {
			QuickSort<std::wstring, TeritorialUnit, std::wstring>* qs = new QuickSort<std::wstring, TeritorialUnit, std::wstring>();
			qs->sort(*filtredTab, new CriterionTUName(), sort);
			delete qs;
		}
		else if (criterion == L"1") {
			QuickSort<int, TeritorialUnit, std::wstring>* qs = new QuickSort<int, TeritorialUnit, std::wstring>();
			qs->sort(*filtredTab, new CriterionTUEducationCount(kategoria), sort);
			delete qs;
		}
		else if (criterion == L"2") {
			QuickSort<double, TeritorialUnit, std::wstring>* qs = new QuickSort<double, TeritorialUnit, std::wstring>();
			qs->sort(*filtredTab, new CriterionTUEducationPortion(kategoria), sort);
			delete qs;
		}
		else if (criterion == L"4") {
			QuickSort<double, TeritorialUnit, std::wstring>* qs = new QuickSort<double, TeritorialUnit, std::wstring>();
			qs->sort(*filtredTab, new CriterionTUAgePortion(vek, gender), sort);
			delete qs;
		}
		else if (criterion == L"6") {
			QuickSort<int, TeritorialUnit, std::wstring>* qs = new QuickSort<int, TeritorialUnit, std::wstring>();
			qs->sort(*filtredTab, new CriterionTUAgeGroupCount(skupina), sort);
			delete qs;
		}
		outputCriterion(*filtredTab);
	}

}

void Application::outputCriterion(structures::UnsortedSequenceTable<std::wstring, TeritorialUnit*>& table)
{
	AgeGTrans* translatorA = new AgeGTrans();
	TypeTrans* trans = new TypeTrans();

	int edu = 0;
	int gender = 0;
	int age = 0;
	int ageGroup = 0;
	CriterionTUName* nameC = new CriterionTUName();
	CriterionTUType* type = new CriterionTUType();
	CriterionTUEducationCount* eduCount;
	CriterionTUEducationPortion* eduPortion;
	
	CriterionTUAgeCount* ageCount;
	CriterionTUAgePortion* agePortion;
	CriterionTUAgeGroupCount* ageGCount;
	CriterionTUAgeGroupPortion* ageGPortion;

	for (auto item : table) {
		wcout << trans->typeOUTString(type->evaluate(*item->accessData())) << ": " << nameC->evaluate(*item->accessData()) << endl;
		for (int i = 0; i < indexes_->size(); i++) {
			std::wstring index = indexes_->at(i);
			int criterion = stoi(index);
			if (criterion == 0) {
				i++;
				std::wstring name = indexes_->at(i);
			
				wcout << L"patri pod: " << name << endl;
			}
			else if (criterion == 1) {
				i++;
				std::wstring edu = indexes_->at(i);
				int e = stoi(edu);
				eduCount = new CriterionTUEducationCount(e);
				wcout << education_->educationOUTString(e) << ": " << eduCount->evaluate(*item->accessData())<<endl;
				delete eduCount;

			}
			else if (criterion == 2) {
				i++;
				std::wstring edu = indexes_->at(i);
				int e = stoi(edu);
				eduPortion = new CriterionTUEducationPortion(e);
				wcout << education_->educationOUTString(e) << ": " << eduPortion->evaluate(*item->accessData()) << endl;
				delete eduPortion;
			}
			else if (criterion == 3) {
				i++;
				std::wstring s = indexes_->at(i);
				int age = stoi(s);
				i++;
				std::wstring g = indexes_->at(i);
				int gender = stoi(g);
				ageCount = new CriterionTUAgeCount(age, gender);
				wcout << age << ": " << ageCount->evaluate(*item->accessData()) << endl;
				delete ageCount;
							
			}
			else if (criterion == 4) {
				i++;
				std::wstring s = indexes_->at(i);
				int age = stoi(s);
				i++;
				std::wstring g = indexes_->at(i);
				int gender = stoi(g);

				agePortion = new CriterionTUAgePortion(age, gender);
				wcout << age << ": " << agePortion->evaluate(*item->accessData()) << endl;
				delete agePortion;
			
			} 
			else if (criterion == 5) {
				i++;
				std::wstring s = indexes_->at(i);
				int ageGroup = stoi(s);
			

				ageGPortion = new CriterionTUAgeGroupPortion(ageGroup);
				wcout << translatorA->ageGroupOUTString(ageGroup) << ": " << ageGPortion->evaluate(*item->accessData()) << endl;
				delete ageGPortion;
			
			}
			else if (criterion == 6) {
				i++;
				std::wstring s = indexes_->at(i);
				int ageGroup = stoi(s);

				ageGCount = new CriterionTUAgeGroupCount(ageGroup);
				wcout << translatorA->ageGroupOUTString(ageGroup) << ": " << ageGCount->evaluate(*item->accessData()) << endl;
				delete ageGCount;
				
			}
		}
	}

	delete nameC;
	delete type;
	delete translatorA;
	delete trans;
	//indexes_->clear();
}



void Application::clearTables()
{
	if (result_ != nullptr) {
		delete result_;
	}
	indexes_->clear();
}


