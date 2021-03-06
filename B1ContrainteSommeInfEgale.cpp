#include "B1ContrainteSommeInfEgale.h"

ContrainteSommeInfEgale::ContrainteSommeInfEgale(vector<unsigned int> variablesSomme, int valeur)
{
	this->valeur = valeur;
	this->variables = variablesSomme;
	this->variablesSomme = variablesSomme;
}

bool ContrainteSommeInfEgale::verifie(const vector<vector<int>> &domaines)
{
	return calculerSomme(domaines) <= valeur;
}