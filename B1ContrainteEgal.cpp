#include "B1ContrainteEgal.h"

ContrainteEgal::ContrainteEgal(unsigned int var1, unsigned int var2)
{
	// Ajout des variables à la contrainte
	variables.push_back(var1);
	variables.push_back(var2);
}

bool ContrainteEgal::verifie(vector<vector<int>> domaines)
{
	return domaines[variables[0]][0] == domaines[variables[1]][0];
}