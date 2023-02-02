#pragma once
#include <string>
 enum Type
{
	obec,
	okres,
	kraj,
	krajina,
	neznamy

};

 class TypeTrans {
 public:
	 std::wstring typeOUTString(int type) {
		 switch (type)
		 {
		 case 0:
			 return L"obec";
		 case 1:
			 return  L"okres";
		 case 2:
			 return  L"kraj";
		 case 3:
			 return L"krajina";
		 default:
			 return L"not found";
		 }
	 }
 };
