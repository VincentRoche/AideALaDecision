#pragma once
#include "B1ContrainteSomme.h"

class ContrainteSommeEgale :
	public ContrainteSomme
{
	/* Valeur � laquelle la somme doit �tre �gale. */
	int valeur;

public:
	ContrainteSommeEgale(vector<unsigned int> variablesSomme, int valeur);

	// H�rit� via Contrainte
	virtual bool verifie(const vector<vector<int>> &domaines) override;
	virtual void print() override {
		printSomme();
		cout << " = " << valeur;
	}
};

