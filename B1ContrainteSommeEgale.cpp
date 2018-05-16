#include "B1ContrainteSommeEgale.h"

ContrainteSommeEgale::ContrainteSommeEgale(vector<unsigned int> variablesSomme, int valeur)
{
	this->valeur = valeur;
	this->variables = variablesSomme;
	this->variablesSomme = variablesSomme;
}

bool ContrainteSommeEgale::verifie(const vector<vector<int>> &domaines)
{
	return calculerSomme(domaines) == valeur;
}