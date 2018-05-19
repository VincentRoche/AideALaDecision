#include "B1Contrainte.h"

bool Contrainte::iterationCombinaison(const vector<vector<int>> &domaines, vector<vector<unsigned int>> &iDomaines, int i)
{
	// Si on a tout compt�, on arr�te
	if (i < 0)
		return true;
	// Incr�mentation
	iDomaines[i][1]++;
	if (iDomaines[i][1] >= domaines[iDomaines[i][0]].size()) // Incr�mentation � gauche si d�passement de la limite
	{
		iDomaines[i][1] = 0;
		return iterationCombinaison(domaines, iDomaines, i - 1);
	}
	return false;
}

bool Contrainte::verifieDomainesMultiples(const vector<vector<int>> &domaines)
{
	/*for (unsigned int v : variables)
	{
		cout << "Domaine " << v << " :";
		for (int i : domaines[v])
		{
			cout << " " << i;
		}
		cout << endl;
	}*/

	vector<vector<unsigned int>> iDomaines; // {variable, i}
	for (unsigned int var : variables) // Initialisation avec des z�ros
	{
		iDomaines.push_back({ var, 0 });
	}
	bool stop = false;
	while (!stop)
	{
		// V�rification avec les valeurs voulues
		vector<vector<int>> domainesVerif = domaines;
		for (vector<unsigned int> vect : iDomaines)
		{
			unsigned int var = vect[0];
			unsigned int i = vect[1];
			domainesVerif[var] = { domaines[var][i] };
		}
		if (verifie(domainesVerif))
			return true;

		// Incr�mentation (passage � la combinaison de valeurs suivante)
		stop = iterationCombinaison(domaines, iDomaines, iDomaines.size() - 1); // On commence par le dernier
	}
	return false;
}
