#pragma once
#include "B1ContrainteSomme.h"

class ContrainteSommeRetenue :
	public ContrainteSomme
{
	/* Variable à laquelle la somme doit être égale. */
	int variable;
	/* Retenue à ajouter à la variable. */
	int retenue;

public:
	ContrainteSommeRetenue(vector<unsigned int> variablesSomme, unsigned int variable, unsigned int retenue);

	// Hérité via Contrainte
	virtual bool verifie(const vector<vector<int>> &domaines) override;
	virtual void print() override {
		printSomme();
		cout << " = " << variable << " + '10' * " << retenue;
	}
};

