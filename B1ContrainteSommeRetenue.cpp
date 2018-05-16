#include "B1ContrainteSommeRetenue.h"

ContrainteSommeRetenue::ContrainteSommeRetenue(vector<unsigned int> variablesSomme, unsigned int variable, unsigned int retenue)
{
	// Enregistrement de toutes les variables
	this->variables = variablesSomme;
	this->variables.push_back(variable);
	this->variables.push_back(retenue);

	// Enregistrement des variables spécifiques à la somme avec retenue
	this->variablesSomme = variablesSomme;
	this->variable = variable;
	this->retenue = retenue;
}

bool ContrainteSommeRetenue::verifie(const vector<vector<int>> &domaines)
{
	return calculerSomme(domaines) == domaines[variable][0] + 10 * domaines[retenue][0];
}