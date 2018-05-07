#include "B1ContrainteSommeRetenue.h"

ContrainteSommeRetenue::ContrainteSommeRetenue(vector<unsigned int> variablesSomme, unsigned int variable, unsigned int retenue)
{
	this->variables = variablesSomme;
	this->variable = variable;
	this->retenue = retenue;
}

bool ContrainteSommeRetenue::verifie(const vector<vector<int>> &domaines)
{
	return calculerSomme(domaines) == domaines[variable][0] + 10 * domaines[retenue][0];
}