#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include "B1Contrainte.h"
#include "B1ContrainteEgal.h"
#include "B1ContrainteDifferent.h"
#include "B1ContrainteInfEgal.h"
#include "B1ContrainteSupEgal.h"
#include "B1ContrainteSommeEgale.h"
using namespace std;

int main(int argc, const char * argv[]) {

	// Définition des variables
	unsigned int nbVariables;
	vector<vector<int>> domaines; // Domaine de valeurs de chaque variable (VARIABLES NUMEROTÉES A PARTIR DE 0)
	vector<Contrainte *> contraintes;

	// Ouverture du fichier
	ifstream infile;
	do {
		cout << "Fichier à lire (en entier, avec son extension) : ";
		string nomFichier;
		nomFichier = "B1Exemple.txt"; // Temporaire, pour tester
		//cin >> nomFichier;


		// Ouverture du fichier
		cout << "Lecture du fichier " << nomFichier << "..." << endl;
		infile = ifstream(nomFichier.c_str());
		if (!infile)
		{
			cout << "Impossible d'ouvir " << nomFichier << "." << endl;
		}
	} while (!infile);

	// Lecture du fichier
	string line;
	for (unsigned int l = 0; getline(infile, line); l++)
	{
		// Extraction des nombres dans nbres
		std::stringstream ss(line);
		std::vector<int> nbres;

		for (int i = 0; ss >> i; )
		{
			nbres.push_back(i);
		}

		if (nbres[0] < 0) // Si c'est la ligne "-1", on s'arrête
			break;
		else if (l == 0) // 1re ligne : nombre de variables
		{
			nbVariables = nbres[0];
		}
		else if (l <= nbVariables) // Lignes suivantes : variables et domaines de valeurs
		{
			vector<int> valeurs;
			// Lecture des valeurs du domaine
			for (int j = 2; j < nbres[1] + 2 && nbres[j] >= 0; j++)
			{
				valeurs.push_back(nbres[j]);
			}
			domaines.insert(domaines.begin() + nbres[0], valeurs);
		}
		else // Autres lignes : contraintes
		{
			int type = nbres[0];
			if (type == 1) // Type 1 : variables égales
				contraintes.push_back(new ContrainteEgal(nbres[1], nbres[2]));
			else if (type == 2) // Type 2 : variables différentes
				contraintes.push_back(new ContrainteDifferent(nbres[1], nbres[2]));
			else if (type == 3) // Type 3 : variable inférieure ou égale à une autre
				contraintes.push_back(new ContrainteInfEgal(nbres[1], nbres[2]));
			else if (type == 4) // Type 4 : variable supérieure ou égale à une autre
				contraintes.push_back(new ContrainteSupEgal(nbres[1], nbres[2]));
			else if (type == 10 && type < 20) // Types de 10 à 19 : sommes basiques
			{
				int valeur = nbres[1];
				// Création d'un vecteur des numéros des variables à prendre en compte dans la somme
				vector<unsigned int> variablesSomme;
				for (size_t i = 2; i < nbres.size() && nbres[i] >= 0; i++)
				{
					variablesSomme.push_back(nbres[i]);
				}
				if (type == 10) // Type 10 : somme des variables égale au premier nombre
					contraintes.push_back(new ContrainteSommeEgale(variablesSomme, valeur));
			}
		}
	}


	// Affichage des données
	cout << "Variables et valeurs possibles :" << endl;
	for (unsigned int i = 0; i < nbVariables; i++)
	{
		cout << "Variable " << i << " :";
		vector<int> domaine = domaines[i];
		for (unsigned int j = 0; j < domaine.size(); j++)
		{
			cout << " " << domaine[j];
		}
		cout << endl;
	}
	cout << "Contraintes :" << endl;
	for (unsigned int i = 0; i < contraintes.size(); i++)
	{
		(*contraintes[i]).print();
		cout << endl;
	}

	return 0;
}
