#pragma once
#include "B1Contrainte.h"

class ContrainteDifferent :
	public Contrainte
{
public:
	ContrainteDifferent(unsigned int var1, unsigned int var2);

	// Hérité via Contrainte
	virtual bool verifie(const vector<vector<int>> &domaines) override;
	virtual void print() override {
		cout << variables[0] << " != " << variables[1];
	}
};

