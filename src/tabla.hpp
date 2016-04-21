#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

class Table {
private:
	int rows;
	int cols;
	map<string, int> rowHash;	    // devuelve en qué fila estamos trabajando (Atacar | Huir ...)
	map<string, int> colHash;		  // devuelve en qué columna estamos trabajando (si | no) 
	float** matrix;
	vector<string> options;
	string valueSelected;
public:
	Table(vector<string> colsParameters, vector<string> rowsParameters);
	~Table();
	void setValue (string val);
	void setElement (int c, int r, float e);
	float getElement (string col, string row);
	float getProb (string element);
	vector<string> getOptions();
	string getValue();
	void print();
	void setNextValue ();
};

#endif