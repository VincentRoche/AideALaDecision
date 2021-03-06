#pragma once
#include "B1Contrainte.h"

class ContrainteSomme :
	public Contrainte
{
protected:
	vector<unsigned int> variablesSomme; // Num�ros des variables � additionner dans la somme

public:
	// H�rit� via Contrainte
	virtual bool verifie(const vector<vector<int>> &domaines) = 0;
	virtual void print() = 0;

	/* Retourne la somme des valeurs correspondantes aux variables de la somme. */
	int calculerSomme(vector<vector<int>> domaines);

	/* Affiche somme(variable1 variable2...) */
	void printSomme()
	{
		cout << "somme(";
		for (unsigned int i = 0; i < variablesSomme.size(); i++)
		{
			cout << variablesSomme[i] << " ";
		}
		cout << ")";
	}
};

