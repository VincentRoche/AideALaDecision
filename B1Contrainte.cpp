#include "B1Contrainte.h"

bool Contrainte::verifieDomainesMultiples(const vector<vector<int>> &domaines)
{
	vector<vector<int>> domainesTestes = domaines;
	for (unsigned int x : variables)
	{
		do {
			// Si la premi�re valeur du domaine fonctionne, c'est bon
			if (verifie(domainesTestes))
			{
				return true;
			}
			else // Si �a ne fonctionne pas, on retire la valeur des domaines � tester et on teste la suivante
			{
				if (domainesTestes[x].size() > 1)
					domainesTestes[x].erase(domainesTestes[x].begin());
			}
		} while (domainesTestes[x].size() > 1);
	}
	return false;
}
