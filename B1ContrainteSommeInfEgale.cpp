#include "B1ContrainteSommeInfEgale.h"

ContrainteSommeInfEgale::ContrainteSommeInfEgale(vector<unsigned int> variablesSomme, int valeur)
{
	this->valeur = valeur;
	this->variables = variablesSomme;
}

bool ContrainteSommeInfEgale::verifie(vector<vector<int>> domaines)
{
	return calculerSomme(domaines) <= valeur;
}