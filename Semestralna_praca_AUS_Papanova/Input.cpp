#include "Application.h"
#include "Type.h"
#include <iostream>
#include <string>
#include <io.h>
#include <fcntl.h>
#include "../structures/heap_monitor.h"
#include "Filtration.h"


int main() {
	initHeapMonitor();
	wcout << L"Nacitavanie dat..." << endl;
	Application* app = new Application();
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	wcout << L"Sèítanie obyvate¾ov, domov a bytov 2021" << endl;
	bool run = true;
	while (run) {

		wcout << L"Pre vyh¾adávanie uzemnej jednotky stlaète - 0 " << endl;
		wcout << L"Pre filtrovanie  údajov o územnej jednotke stlaète - 1" << endl;
		wcout << L"Pre triedenie údajov  - 2" << endl;
		wcout << L"KONIEC  - 3" << endl;

		wstring uloha;
		getline(std::wcin, uloha);
		int ulohaInt = stoi(uloha);
		if (ulohaInt != 3) {


			//Mozno by bolo mozne rozlozit stringy a nemusiet zadat typ
			wcout << L"Zvolte typ územnej jednotky, o ktorej chcete informacie:" << endl;
			wcout << L"  - obec : 0 " << endl;
			wcout << "	 - okres: 1" << endl;
			wcout << "	 - kraj: 2" << endl;
			wcout << "	 - krajina: 3" << endl;

			wstring typ;
			getline(std::wcin, typ);
			int typInt = stoi(typ);
			Type type;
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


			if (ulohaInt == 0) {
				wcout << L"Vyh¾adávanie:" << endl;
				wcout << L"Zadajte názov územnej jednotky, ktorú chcete vyh¾ada:" << endl;

				wstring nazov;
				getline(std::wcin, nazov);
				app->findInfoAbout(type, nazov);
			}
			else if (ulohaInt == 1) {
				wcout << L"Filtrovanie:" << endl;
				app->filterBy(type);
				app->clearTables();
			}
			else if (ulohaInt == 2) {
				wcout << L"Triedenie:" << endl;
				app->sortBy(type);
				app->clearTables();
			}
			
		}
		else {
			run = false;
		}
		
	}
	delete app;
}