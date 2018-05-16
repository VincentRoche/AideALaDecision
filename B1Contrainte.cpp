#include "B1Contrainte.h"

bool Contrainte::verifieDomainesMultiples(const vector<vector<int>> &domaines)
{
	vector<vector<int>> domainesTestes = domaines;
	bool sauterSuivant = false;
	for (unsigned int x : variables)
	{
		if (!sauterSuivant || domainesTestes[x].size() > 1) // S'il n'y a qu'une seule variable � tester et qu'on a d�ja fait un test avec la combinaison actuelle, on passe � la variable suivante
		{
			bool stop = false;
			while (!stop) {
				/*cout << "Domaine 2 : ";
				for (int v : domainesTestes[2])
				{
					cout << v << " ";
				}
				cout << endl;*/
				// Si la premi�re valeur du domaine fonctionne, c'est bon
				if (verifie(domainesTestes))
				{
					///cout << "TRUE" << endl;
					return true;
				}
				else // Si �a ne fonctionne pas, on retire la valeur des domaines � tester et on teste la suivante
				{
					///cout << domainesTestes[x].size() << endl;
					if (domainesTestes[x].size() > 1)
					{
						domainesTestes[x].erase(domainesTestes[x].begin());
						sauterSuivant = false;
					}
					else
					{
						stop = true;
						sauterSuivant = true;
					}
				}
			}
		}
	}
	///cout << "FALSE" << endl;
	return false;
}
