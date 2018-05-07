#include "B1Contrainte.h"

bool Contrainte::verifieDomainesMultiples(const vector<vector<int>> &domaines)
{
	vector<vector<int>> domainesTestes = domaines;
	for (unsigned int x : variables)
	{
		do {
			// Si la première valeur du domaine fonctionne, c'est bon
			if (verifie(domainesTestes))
			{
				return true;
			}
			else // Si ça ne fonctionne pas, on retire la valeur des domaines à tester et on teste la suivante
			{
				if (domainesTestes[x].size() > 1)
					domainesTestes[x].erase(domainesTestes[x].begin());
			}
		} while (domainesTestes[x].size() > 1);
	}
	return false;
}
