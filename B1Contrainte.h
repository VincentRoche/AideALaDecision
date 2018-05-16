#ifndef B1_Contrainte_hpp
#define B1_Contrainte_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

class Contrainte {
protected:
	vector<unsigned int> variables; // Num�ros de toutes les variables utilis�es par la contrainte
    
public:
	/* V�rifie si les valeurs donn�es v�rifient la contrainte (les domaines ne doivent contenir qu'une seule valeur chacun). */
    virtual bool verifie(const vector<vector<int>> &domaines) = 0;

	/* V�rifie si une des valeurs de chaque domaine v�rifie la contrainte (teste toutes les valeurs de chaque domaine, renvoie true si au moins une combinaison fonctionne). */
	bool verifieDomainesMultiples(const vector<vector<int>> &domaines);

	/* Affiche la contrainte de mani�re lisible */
	virtual void print() = 0;

	vector<unsigned int> getVariables()
	{
		return variables;
	}
};

#endif /* B1_Contrainte_hpp */
