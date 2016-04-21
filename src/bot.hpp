#ifndef BOT_H
#define BOT_H

#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "tabla.hpp"


using namespace std;

class Bot{
private: 
	vector<string> parametersNames;									
	vector<string> tablesNames;
	string principalState;
	string OLDprincipalState;
	map<string, float> stZERO;
	Table* stPLUS1;																	// Tabla st + 1
	map<string, Table*> parametersTables;						// Contiene las tablas accesibles por su nombre
	map<string, float>  userParameters;							// Parámetros que se le piden al usuario
public:
	Bot(ifstream* fich);
	~Bot();
	void exe();
	void printActualState();
	void modifyEnvironment();
};


#endif 