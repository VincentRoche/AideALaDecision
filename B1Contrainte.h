#ifndef B1_Contrainte_hpp
#define B1_Contrainte_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

class Contrainte {
protected:
	vector<unsigned int> variables; // Num�ros des variables utilis�es par la contrainte
    
public:
	/* V�rifie si les valeurs donn�es v�rifient la contrainte (les domaines ne doivent contenir qu'une seule valeur chacun). */
    virtual bool verifie(vector<vector<int>> domaines) = 0;

	/* Affiche la contrainte de mani�re lisible */
	virtual void print() = 0;
};

#endif /* B1_Contrainte_hpp */
