#pragma once
#include "B1ContrainteSomme.h"

class ContrainteSommeRetenue :
	public ContrainteSomme
{
	/* Variable � laquelle la somme doit �tre �gale. */
	int variable;
	/* Retenue � ajouter � la variable. */
	int retenue;

public:
	ContrainteSommeRetenue(vector<unsigned int> variablesSomme, unsigned int variable, unsigned int retenue);

	// H�rit� via Contrainte
	virtual bool verifie(const vector<vector<int>> &domaines) override;
	virtual void print() override {
		printSomme();
		cout << " = " << variable << " + '10' * " << retenue;
	}
};

