#include <iostream>
#include "IniFIle.h"
using namespace std;

int main(){

	IniFile ini;
	ini.load("main.ini");

	ini.show();
	ini.save("main.ini");
	return 0;
}