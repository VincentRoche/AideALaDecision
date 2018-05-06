#include "B1ContrainteSomme.h"

int ContrainteSomme::calculerSomme(vector<vector<int>> domaines)
{
	int somme = 0;
	for (unsigned int i = 0; i < variables.size(); i++)
	{
		somme += domaines[variables[i]][0];
	}
	return somme;
}
