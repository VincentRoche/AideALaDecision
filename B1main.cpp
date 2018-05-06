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
#include "B1ContrainteSommeInfEgale.h"
using namespace std;

vector<int> methode_triviale(const vector<unsigned int> &variablesAssignees, const vector<vector<int>> &domaines, const unsigned int nbVariables, const vector<Contrainte *> &contraintes);

int main(int argc, const char * argv[]) {

	// D�finition des variables
	unsigned int nbVariables;
	vector<vector<int>> domaines; // Domaine de valeurs de chaque variable (VARIABLES NUMEROT�ES A PARTIR DE 0)
	vector<Contrainte *> contraintes;

	// Ouverture du fichier
	ifstream infile;
	do {
		cout << "Fichier � lire (en entier, avec son extension) : ";
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

		if (nbres[0] < 0) // Si c'est la ligne "-1", on s'arr�te
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
			if (type == 1) // Type 1 : variables �gales
				contraintes.push_back(new ContrainteEgal(nbres[1], nbres[2]));
			else if (type == 2) // Type 2 : variables diff�rentes
				contraintes.push_back(new ContrainteDifferent(nbres[1], nbres[2]));
			else if (type == 3) // Type 3 : variable inf�rieure ou �gale � une autre
				contraintes.push_back(new ContrainteInfEgal(nbres[1], nbres[2]));
			else if (type == 4) // Type 4 : variable sup�rieure ou �gale � une autre
				contraintes.push_back(new ContrainteSupEgal(nbres[1], nbres[2]));
			else if (type >= 10 && type < 20) // Types de 10 � 19 : sommes basiques
			{
				int valeur = nbres[1];
				// Cr�ation d'un vecteur des num�ros des variables � prendre en compte dans la somme
				vector<unsigned int> variablesSomme;
				for (size_t i = 2; i < nbres.size() && nbres[i] >= 0; i++)
				{
					variablesSomme.push_back(nbres[i]);
				}
				if (type == 10) // Type 10 : somme des variables �gale au premier nombre
					contraintes.push_back(new ContrainteSommeEgale(variablesSomme, valeur));
				else if (type == 11) // Type 11 : somme des variables inf�rieure ou �gale au premier nombre
					contraintes.push_back(new ContrainteSommeInfEgale(variablesSomme, valeur));
			}
		}
	}


	// Affichage des donn�es
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



	vector<int> assignations = methode_triviale(vector<unsigned int>(), domaines, nbVariables, contraintes);
	// Affichage des r�sultats
	cout << endl << "R�sultats :" << endl;
	if (assignations.size() == 0)
		cout << "Aucun r�sultat." << endl;
	else
	{
		for (unsigned int i = 0; i < nbVariables; i++)
		{
			cout << "Variable " << i << " = " << assignations[i] << endl;
		}
	}


	return 0;
}

/* Retourne true si toutes les contraintes donn�es sont v�rifi�es par les domaines (qui contiennent chacun une seule valeur) */
bool verification_des_contraintes(vector<vector<int>> domaines, vector<Contrainte *> contraintes)
{
	/*for (unsigned int i = 0; i < domaines.size(); i++)
	{
		cout << "Variable " << i << " = " << domaines[i][0] << endl;
	}*/
	for (unsigned int i = 0; i < contraintes.size(); i++)
	{
		// Si une contrainte n'est pas v�rifi�e, on retourne false.
		if (!(*contraintes[i]).verifie(domaines))
		{
			/*cout << "Contrainte non v�rifi�e : ";
			(*contraintes[i]).print();
			cout << endl << endl;*/
			return false;
		}
	}
	return true;
}

vector<int> methode_triviale(const vector<unsigned int> &variablesAssignees, const vector<vector<int>> &domaines, const unsigned int nbVariables, const vector<Contrainte *> &contraintes)
{
	if (variablesAssignees.size() == nbVariables) // Si toutes les variables ont �t� assign�es
	{
		if (verification_des_contraintes(domaines, contraintes))
		{
			// Succ�s, cr�ation d'un tableau des bonnes valeurs
			vector<int> valeurs(nbVariables);
			for (unsigned int i = 0; i < domaines.size(); i++)
			{
				valeurs.insert(valeurs.begin() + i, domaines[i][0]);
			}
			return valeurs;
		}
		else
		{
			return vector<int>();
		}
	}
	else
	{
		// Choix d'une variable x parmi celles non assign�es
		unsigned int x;
		for (unsigned int i = 0; i < nbVariables; i++)
		{
			if (find(variablesAssignees.begin(), variablesAssignees.end(), i) == variablesAssignees.end()) // Si i n'est pas dans variablesAssignees
			{
				x = i;
				break;
			}
		}

		vector<unsigned int> nvellesVariablesAssignees = variablesAssignees;
		nvellesVariablesAssignees.push_back(x);

		// Appel r�cursif pour chaque valeur du domaine de x
		for (unsigned int i = 0; i < domaines[x].size(); i++)
		{
			int v = domaines[x][i];
			vector<vector<int>> nveauxDomaines = domaines;
			nveauxDomaines[x] = { v }; // Le domaine de x ne contient que v
			vector<int> z = methode_triviale(nvellesVariablesAssignees, nveauxDomaines, nbVariables, contraintes);
			if (z.size() > 0)
				return z;
		}
		return vector<int>();
	}
}