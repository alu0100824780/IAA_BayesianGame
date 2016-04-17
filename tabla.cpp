#include "tabla.hpp"



Table::Table(vector<string> colsParameters, vector<string> rowsParameters) {
	rows = rowsParameters.size();
	cols = colsParameters.size();
	options = colsParameters;
	for(int i = 0; i < cols; i++) {
		colHash.insert( pair<string,int> (colsParameters[i],i));
	}
	for(int i = 0; i < rows; i++) {
		rowHash.insert( pair<string,int> (rowsParameters[i],i));
	}
	matrix = new float*[cols];
	for(int i = 0; i < cols; i++) {
		matrix[i] = new float[rows];
	}
}

void Table::setElement(int c, int r, float e) {
	if (e > 1) {
		cout << "Error, el elemento "<<r<<" "<<c<<" es mayor que 1 ("<<e<<")"<<endl;
	}
	matrix[c][r] = e;
}

float Table::getElement(string col, string row) {
	return matrix[colHash[col]][rowHash[row]];
}

vector<string> Table::getOptions() {
	return options;
}

void Table::setValue(string val) {
	valueSelected = val;
}

float Table::getProb(string element){
	return getElement (valueSelected, element);
}

void Table::print() {
	for(int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++){
			cout<<matrix[j][i]<<" ";
		}
		cout<<endl;
	}
}

string Table::getValue(){
	return valueSelected;
}

void Table::setNextValue(){
	int i = 0;
	while (options[i] != valueSelected) {
		i++;
	}
	cout<<"Ñame"<<endl;
	if (i < options.size() - 1 && options[i+1] != string()) {
		valueSelected = options[i+1];
	}else{
		valueSelected = options[0];
	}
}

Table::~Table(){}

