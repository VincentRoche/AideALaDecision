#pragma once
#include "B1ContrainteSomme.h"

class ContrainteSommeEgale :
	public ContrainteSomme
{
	/* Valeur à laquelle la somme doit être égale. */
	int valeur;

public:
	ContrainteSommeEgale(vector<unsigned int> variablesSomme, int valeur);

	// Hérité via Contrainte
	virtual bool verifie(const vector<vector<int>> &domaines) override;
	virtual void print() override {
		printSomme();
		cout << " = " << valeur;
	}
};

