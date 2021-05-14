#include <iostream>
#include "Lab1_Kuznetsov.h"

int main()
{
	auto a = new Map<string, string>();
	a->insert("Kuznetsov", "Director");
	a->insert("Potapov", "Programmer");
	a->insert("Shishkin", "Bloger");
	a->insert("Aptekin", "Designer");
	a->remove("Aptekin");
	std::cout << "Shiskin is " << a->find("Shishkin") << std::endl;
	std::cout << "Peoples:" << std::endl;
	a->print();
	return 0;
}
