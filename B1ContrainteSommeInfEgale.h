#pragma once
#include "B1ContrainteSomme.h"

class ContrainteSommeInfEgale :
	public ContrainteSomme
{
	/* Valeur à laquelle la somme doit être inférieure ou égale. */
	int valeur;

public:
	ContrainteSommeInfEgale(vector<unsigned int> variablesSomme, int valeur);

	// Hérité via Contrainte
	virtual bool verifie(const vector<vector<int>> &domaines) override;
	virtual void print() override {
		printSomme();
		cout << " <= '" << valeur << "'";
	}
};

