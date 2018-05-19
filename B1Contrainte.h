#ifndef B1_Contrainte_hpp
#define B1_Contrainte_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Contrainte {
protected:
	vector<unsigned int> variables; // Numéros de toutes les variables utilisées par la contrainte
    
public:
	/* Vérifie si les valeurs données vérifient la contrainte (les domaines ne doivent contenir qu'une seule valeur chacun). */
    virtual bool verifie(const vector<vector<int>> &domaines) = 0;

	/* Vérifie si une des valeurs de chaque domaine vérifie la contrainte (teste toutes les valeurs de chaque domaine, renvoie true si au moins une combinaison fonctionne). */
	bool verifieDomainesMultiples(const vector<vector<int>> &domaines);

	/* Affiche la contrainte de manière lisible */
	virtual void print() = 0;

	vector<unsigned int> getVariables()
	{
		return variables;
	}

private:
	/* Incrémente la i-ème valeur de iDomaines pour le parcours des valeurs des domaines (comme si les chiffres de iDomaines représentaient un nombre et qu'on comptait).
	Retourne true si on ne peut plus incrémenter. */
	bool iterationCombinaison(const vector<vector<int>> &domaines, vector<vector<unsigned int>> &iDomaines, int i);
};

#endif /* B1_Contrainte_hpp */
