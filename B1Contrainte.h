#ifndef B1_Contrainte_hpp
#define B1_Contrainte_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

class Contrainte {
protected:
	vector<unsigned int> variables; // Numéros des variables utilisées par la contrainte
    
public:
	/* Vérifie si les valeurs données vérifient la contrainte (les domaines ne doivent contenir qu'une seule valeur chacun). */
    virtual bool verifie(vector<vector<int>> domaines) = 0;

	/* Affiche la contrainte de manière lisible */
	virtual void print() = 0;
};

#endif /* B1_Contrainte_hpp */
