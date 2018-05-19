#include "B1ContrainteSomme.h"

int ContrainteSomme::calculerSomme(vector<vector<int>> domaines)
{
	int somme = 0;
	///cout << " > somme(";
	for (unsigned int i = 0; i < variablesSomme.size(); i++)
	{
		///cout << domaines[variables[i]][0] << " ";
		somme += domaines[variablesSomme[i]][0];
	}
	///cout << ") = " << somme << endl;
	return somme;
}
