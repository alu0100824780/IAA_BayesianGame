#include "bot.hpp"


/* Construye la tabla t+1, las tablas de cada parámetro y 
 * le pregunta al usuario los valores de dichos parámetros
 */
Bot::Bot(ifstream* fich){
	int nParameters;
	*fich >> nParameters;
	string auxName;
	for (int i = 0; i < nParameters; i++) {
		*fich >> auxName;
		parametersNames.push_back(auxName);
	}
	stPLUS1 = new Table(parametersNames,parametersNames);
	float auxValue;
	for (int i = 0; i < nParameters; i++) {
		for(int j = 0; j < nParameters; j++) {
			*fich >> auxValue;
			stPLUS1->setElement(j,i,auxValue);
		}
	}	
	//stPLUS1->print();
	while(!fich->eof()){
		*fich >> auxName;
		*fich >> auxValue;
		string auxOptionName;
		vector<string> options (auxValue);
		for (int i = 0; i < options.size(); i++) {
			*fich >> auxOptionName;
			options[i] = auxOptionName;
		}
		float acumulator = 0;
		Table* auxTable = new Table (options, parametersNames);
		for (int i = 0; i < parametersNames.size(); i++) {
			acumulator = 0;
			for (int j = 0; j < options.size(); j++) {
				*fich >> auxValue;
				acumulator += auxValue;
				auxTable->setElement(j,i,auxValue);
			}
			if(acumulator != 1) {
				cout<<"Error, los elementos de la fila "<<i<<" no suman 1 (suman "<<acumulator<<")"<<endl;
			}
		}
		parametersTables.insert(pair<string, Table*> (auxName, auxTable));
		cout<<"Introduce el valor para "<<auxName<<endl;
		for(int j = 0; j < auxTable->getOptions().size(); j++) {
			cout<<"["<<j<<"]"<<auxTable->getOptions()[j]<<endl;
		}
		float userValue;
		cin>>userValue;
		tablesNames.push_back(auxName);
		auxTable->setValue(auxTable->getOptions()[userValue]);
		userParameters.insert( pair<string, float> (auxName, userValue));
	}
	cout<<"Introduce el estado en el que se encuentra el bot (en porcentaje): "<<endl;
	auxValue = -1;
	float acumulator = 0;
	float max = 0;
	float minInterval = 0;
	for(int j = 0; j < parametersNames.size(); j++) {
		if(j == parametersNames.size() - 1)
			minInterval = 100 - acumulator;
		while(auxValue < minInterval || auxValue > 100 - acumulator) { 
			cout<< parametersNames[j] << "["<<minInterval<<","<<100 - acumulator<<"] : "<<flush;
			cin >> auxValue;
		}
		if (auxValue > max) {
			max = auxValue;
			principalState = parametersNames[j];
		}
		stZERO.insert (pair<string, float> (parametersNames[j], auxValue / 100));
		acumulator += auxValue;
		auxValue = -1;
	}
}

Bot::~Bot(){

}

// Genera los valores finales
void Bot::exe() {
	OLDprincipalState = principalState;
	double sum = 0;				// suma de productos
	double maxValue = 0;
	for (string  name : parametersNames) {
		double product = 1;
		for (string tName : tablesNames) {
			product *= parametersTables[tName]->getProb(name);
		}
		product *= stPLUS1->getElement(name,principalState);
		stZERO[name] = product;
		if(product > maxValue) {
			maxValue = product;
			principalState = name;	
		}
		sum += product;
	}
	for (string name : parametersNames) {
		stZERO[name] /= sum;
	}
	
}

void Bot::printActualState() {
	system("clear");
	for (string tName : tablesNames) {
		cout<<setw(20)<<tName<<" : "<<parametersTables[tName]->getValue()<<"\n";
	}
	cout<<endl<<endl;
	for (string name : parametersNames) {
		cout<<"Para "<<setw(12)<<name<<" la probabilidad es "<<stZERO[name] * 100<<" %"<<endl;
	}
	cout<<endl<<endl<<"El estado del bot cambia de "<<OLDprincipalState<<" a "<<principalState<<endl<<endl;
}

void Bot::modifyEnvironment(){
	int selector = 1;
	int index = 0;
	while (selector < 4 && selector > 0) {
		printActualState();
		cout<<"Actualizando el entorno del agente. 1 y 2 para moverte, 3 para\n"
				"seleccionar y otro para salir"<<endl<<endl;
		for (int i = 0; i < tablesNames.size(); i++) {
			if(i == index)
				cout<<"["<<setw(20)<<tablesNames[i]<<"] : ";
			else
				cout<<setw(20)<<tablesNames[i]<<"  : ";
			cout<<parametersTables[tablesNames[i]]->getValue()<<endl;
		}
		cin >> selector;
		if (selector == 1 && index > 0)
			index--;
		else if (selector == 2 && index < parametersNames.size())
			index++;
		else if (selector == 3)
			parametersTables[tablesNames[index]]->setNextValue();
		else
			break;
	}

}