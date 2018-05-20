#pragma once
#include "B1ContrainteSomme.h"

class ContrainteSommeInfEgale :
	public ContrainteSomme
{
	/* Valeur � laquelle la somme doit �tre inf�rieure ou �gale. */
	int valeur;

public:
	ContrainteSommeInfEgale(vector<unsigned int> variablesSomme, int valeur);

	// H�rit� via Contrainte
	virtual bool verifie(const vector<vector<int>> &domaines) override;
	virtual void print() override {
		printSomme();
		cout << " <= '" << valeur << "'";
	}
};

