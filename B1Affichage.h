#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

/* Trucs utiles pour l'affichage. */
class Affichage
{
public:

	static void afficherGrille(const vector<int> &valeurs, const unsigned int largeurLignes, const unsigned int largeurSousCarres = 0)
	{
		unsigned int ligne = 0;
		for (unsigned int i = 0; i < valeurs.size(); i++)
		{
			cout << setw(3) << valeurs[i];
			if (largeurSousCarres > 0 && (i + 1) % largeurSousCarres == 0)
				cout << " ";
			if ((i + 1) % largeurLignes == 0) // Si c'est le bout de la ligne
			{
				cout << endl;
				ligne++;
				if (ligne % largeurSousCarres == 0)
					cout << endl;
			}
		}
	}

	/* Affiche une grille de sudoku avec les num�ros des variables */
	static void grilleSudokuNumerottee()
	{
		std::vector<int> valeurs;
		for (int i = 0; i < 81; i++)
			valeurs.push_back(i);
		afficherGrille(valeurs, 9, 3);
	}

	static void fichierProbleme1()
	{
		cout << 81 << endl;

		// Variables
		for (unsigned int i = 0; i < 81; i++)
		{
			cout << i << " " << 9;
			for (unsigned int j = 1; j <= 9; j++)
			{
				cout << " " << j;
			}
			cout << endl;
		}
		// Contraintes
		vector<vector<unsigned int>> inegalites;
		// Diff�rent des variables de la m�me ligne et de la r�gion
		unsigned int numLigne = 0;
		for (unsigned int i = 0; i < 81; i++)
		{
			unsigned int debutLigne = i - i % 9;
			for (unsigned int j = debutLigne; j < debutLigne + 9; j++)
			{
				if (i != j)
					inegalites.push_back({ i, j });
			}

			// Cases de la r�gion qui ne sont pas sur la m�me ligne ou la m�me colonne
			unsigned int sousLigne = numLigne % 3;
			unsigned int sousColonne = i % 3;
			// 9 cas...
			if (sousLigne == 0 && sousColonne == 0)
			{
				inegalites.push_back({ i, i + 9 + 1 });
				inegalites.push_back({ i, i + 9 + 2 });
				inegalites.push_back({ i, i + 9 * 2 + 1 });
				inegalites.push_back({ i, i + 9 * 2 + 2 });
			}
			else if (sousLigne == 0 && sousColonne == 1)
			{
				inegalites.push_back({ i, i + 9 + 1 });
				inegalites.push_back({ i, i + 9 - 1 });
				inegalites.push_back({ i, i + 9 * 2 + 1 });
				inegalites.push_back({ i, i + 9 * 2 - 1 });
			}
			else if (sousLigne == 0 && sousColonne == 2)
			{
				inegalites.push_back({ i, i + 9 - 1 });
				inegalites.push_back({ i, i + 9 - 2 });
				inegalites.push_back({ i, i + 9 * 2 - 1 });
				inegalites.push_back({ i, i + 9 * 2 - 2 });
			}
			else if (sousLigne == 1 && sousColonne == 0)
			{
				inegalites.push_back({ i, i - 9 + 1 });
				inegalites.push_back({ i, i - 9 + 2 });
				inegalites.push_back({ i, i + 9 + 1 });
				inegalites.push_back({ i, i + 9 + 2 });
			}
			else if (sousLigne == 1 && sousColonne == 1)
			{
				inegalites.push_back({ i, i - 9 + 1 });
				inegalites.push_back({ i, i - 9 - 1 });
				inegalites.push_back({ i, i + 9 + 1 });
				inegalites.push_back({ i, i + 9 - 1 });
			}
			else if (sousLigne == 1 && sousColonne == 2)
			{
				inegalites.push_back({ i, i - 9 - 1 });
				inegalites.push_back({ i, i - 9 - 2 });
				inegalites.push_back({ i, i + 9 - 1 });
				inegalites.push_back({ i, i + 9 - 2 });
			}
			else if (sousLigne == 2 && sousColonne == 0)
			{
				inegalites.push_back({ i, i - 9 + 1 });
				inegalites.push_back({ i, i - 9 + 2 });
				inegalites.push_back({ i, i - 9 * 2 + 1 });
				inegalites.push_back({ i, i - 9 * 2 + 2 });
			}
			else if (sousLigne == 2 && sousColonne == 1)
			{
				inegalites.push_back({ i, i - 9 + 1 });
				inegalites.push_back({ i, i - 9 - 1 });
				inegalites.push_back({ i, i - 9 * 2 + 1 });
				inegalites.push_back({ i, i - 9 * 2 - 1 });
			}
			else if (sousLigne == 2 && sousColonne == 2)
			{
				inegalites.push_back({ i, i - 9 - 1 });
				inegalites.push_back({ i, i - 9 - 2 });
				inegalites.push_back({ i, i - 9 * 2 - 1 });
				inegalites.push_back({ i, i - 9 * 2 - 2 });
			}

			// Incr�mentation ligne
			if ((i + 1) % 9 == 0)
			{
				numLigne++;
			}
		}
		// Diff�rent des variables de la m�me colonne
		for (unsigned int i = 0; i < 9; i++)
		{
			for (unsigned int j = i; j <= i + 9 * 8; j += 9)
			{
				for (unsigned int k = i; k <= i + 9 * 8; k += 9)
				{
					if (j != k)
						inegalites.push_back({ j, k });
				}
			}
		}

		// Retrait des doublons (in�galit�s dans les deux sens) et affichage
		vector<vector<unsigned int>> trucsAffiches;
		for (vector<unsigned int> v : inegalites)
		{
			// Recherche dans les trucs d�j� affich�s
			bool affiche = false;
			for (vector<unsigned int> va : trucsAffiches)
			{
				if ((va[0] == v[0] && va[1] == v[1]) || va[0] == v[1] && va[1] == v[0])
				{
					affiche = true;
					break;
				}
			}
			if (!affiche)
			{
				cout << 2 << " " << v[0] << " " << v[1] << endl;
				trucsAffiches.push_back(v);
			}
		}
	}
};

