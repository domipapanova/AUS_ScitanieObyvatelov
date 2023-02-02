#pragma once
#include <string>
enum {
	predproduktivni,
	produktivni,
	poproduktivni
};

class AgeGTrans {
public:
	std::wstring ageGroupOUTString(int edu) {
		switch (edu)
		{
		case 0:
			return L"predproduktivni";
		case 1:
			return  L"produktivni";
		case 2:
			return  L"poproduktivni";

		default:
			return L"pod zadanym cislom neevidujeme ziadnu vekovu skupinu";
		}
	}
};
