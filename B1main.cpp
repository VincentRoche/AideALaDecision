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
#include "B1ContrainteSommeRetenue.h"
#include "B1Affichage.h"
using namespace std;

vector<int> methode_triviale(const vector<unsigned int> &variablesAssignees, const vector<vector<int>> &domaines, const unsigned int nbVariables, const vector<Contrainte *> &contraintes);
vector<int> methode_reduction_domaines(const vector<unsigned int> &variablesAssignees, const vector<vector<int>> &domaines, const unsigned int nbVariables, const vector<Contrainte *> &contraintes);

int main(int argc, const char * argv[]) {
	
	// Définition des variables
	unsigned int nbVariables;
	vector<vector<int>> domaines; // Domaine de valeurs de chaque variable (VARIABLES NUMEROTÉES A PARTIR DE 0)
	vector<Contrainte *> contraintes;
	vector<unsigned int> variablesAssignees; // Variables dont les valeurs sont déjà connues

	// Ouverture du fichier
	string nomFichier;
	ifstream infile;
	do {
		cout << "Fichier a lire (en entier, avec son extension) : ";
		//nomFichier = "B1Probleme2.txt"; // Temporaire, pour tester
		cin >> nomFichier;


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
			/*if (valeurs.size() == 1)
				variablesAssignees.push_back(nbres[0]);*/
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
			else if (type >= 10 && type < 20) // Types de 10 à 19 : sommes basiques
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
				else if (type == 11) // Type 11 : somme des variables inférieure ou égale au premier nombre
					contraintes.push_back(new ContrainteSommeInfEgale(variablesSomme, valeur));
			}
			else if (type >= 20) // Types à partir de 20 : autres
			{
				if (type == 20) // Type 20 : somme égale à une variable plus une retenue (nbres[1] = variable, nbres[2] = retenue, chiffres suivants = variables de la somme)
				{
					unsigned int variable = nbres[1];
					unsigned int retenue = nbres[2];
					vector<unsigned int> variablesSomme;
					for (size_t i = 3; i < nbres.size() && nbres[i] >= 0; i++)
					{
						variablesSomme.push_back(nbres[i]);
					}
					contraintes.push_back(new ContrainteSommeRetenue(variablesSomme, variable, retenue));
				}
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


	int choix;
	do
	{
		cout << "Quelle methode tester ?" << endl << "1 : methode triviale" << endl << "2 : methode avec reduction des domaines de valeur" << endl << "Indiquez le numero choisi (ou un autre pour quitter) : ";
		cin >> choix;

		if (choix >= 1 && choix <= 2)
		{
			cout << endl << "Calcul en cours..." << endl;
			vector<int> assignations;
			if (choix == 1)
			{
				assignations = methode_triviale(variablesAssignees, domaines, nbVariables, contraintes);
			}
			else if (choix == 2)
			{
				assignations = methode_reduction_domaines(variablesAssignees, domaines, nbVariables, contraintes);
			}

			// Affichage des résultats
			cout << endl << "Resultats :" << endl;
			if (assignations.size() == 0)
				cout << "Aucun resultat." << endl;
			else
			{
				for (unsigned int i = 0; i < nbVariables; i++)
				{
					cout << "Variable " << i << " = " << assignations[i] << endl;
				}

				if (nomFichier == "B1Probleme1.txt" || nomFichier == "B1Probleme2.txt")
				{
					cout << "Sudoku :" << endl;
					Affichage::afficherGrille(assignations, 9, 3);
				}
				else if (nomFichier == "B1Probleme3.txt")
				{
					cout << assignations[0] << assignations[1] << assignations[2] << assignations[3]
						<< " + " << assignations[4] << assignations[2] << assignations[3] << assignations[5] << assignations[6]
						<< " + " << assignations[4] << assignations[2] << assignations[3] << assignations[5] << assignations[6]
						<< " + " << assignations[7] << assignations[3] << assignations[8] << assignations[0] << assignations[1]
						<< " + " << assignations[7] << assignations[3] << assignations[8] << assignations[0] << assignations[1]
						<< " = " << assignations[4] << assignations[2] << assignations[1] << assignations[9] << assignations[4] << assignations[1] << endl;
				}
			}
		}

	} while (choix >= 1 && choix <= 2);


	return 0;
}

/* Retourne true si toutes les contraintes données sont vérifiées par les domaines (qui contiennent chacun une seule valeur) */
bool verification_des_contraintes(vector<vector<int>> domaines, vector<Contrainte *> contraintes)
{
	/*for (unsigned int i = 0; i < domaines.size(); i++)
	{
		cout << "Variable " << i << " = " << domaines[i][0] << endl;
	}*/
	for (unsigned int i = 0; i < contraintes.size(); i++)
	{
		// Si une contrainte n'est pas vérifiée, on retourne false.
		if (!(*contraintes[i]).verifie(domaines))
		{
			/*cout << "Contrainte non vérifiée : ";
			(*contraintes[i]).print();
			cout << endl << endl;*/
			return false;
		}
	}
	return true;
}

/* Convertit la liste des domaines de valeurs (une valeur dans le domaine de chaque variable) en une simple liste des valeurs assignées à chaque variable */
vector<int> domainesToAssignations(const vector<vector<int>> &domaines)
{
	vector<int> valeurs;
	for (unsigned int i = 0; i < domaines.size(); i++)
	{
		valeurs.insert(valeurs.begin() + i, domaines[i][0]);
	}
	return valeurs;
}

vector<int> methode_triviale(const vector<unsigned int> &variablesAssignees, const vector<vector<int>> &domaines, const unsigned int nbVariables, const vector<Contrainte *> &contraintes)
{
	if (variablesAssignees.size() == nbVariables) // Si toutes les variables ont été assignées
	{
		// Vérification des contraintes
		if (verification_des_contraintes(domaines, contraintes))
		{
			// Succès !
			return domainesToAssignations(domaines);
		}
		else
		{
			return vector<int>(); // Pas de solution
		}
	}
	else
	{
		// Choix d'une variable x parmi celles non assignées
		unsigned int x;
		for (unsigned int i = 0; i < nbVariables; i++)
		{
			if (find(variablesAssignees.begin(), variablesAssignees.end(), i) == variablesAssignees.end()) // Si i n'est pas dans variablesAssignees
			{
				x = i;
				break;
			}
		}

		// Ajout de la variable x choisie aux variables assignées
		vector<unsigned int> nvellesVariablesAssignees = variablesAssignees;
		nvellesVariablesAssignees.push_back(x);

		// Appel récursif pour chaque valeur du domaine de x
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

vector<vector<int>> reduction_des_domaines(const vector<unsigned int>& variablesNonAssignees, const unsigned int variableVerif, const vector<vector<int>>& domaines, const unsigned int nbVariables, const vector<Contrainte*>& contraintes)
{
	vector<vector<int>> nveauxDomaines = domaines;

	// Vérification des contraintes contenant variableVerif et une variable non assignée
	for (Contrainte * c : contraintes)
	{
		vector<unsigned int> varsContrainte = (*c).getVariables();
		if (std::find(varsContrainte.begin(), varsContrainte.end(), variableVerif) != varsContrainte.end()) // Si la contrainte concerne la variable variableVerif
		{
			for (unsigned int var : variablesNonAssignees)
			{
				if (var != variableVerif && std::find(varsContrainte.begin(), varsContrainte.end(), var) != varsContrainte.end()) // Si la contrainte concerne var
				{
					// Création du nouveau domaine de var qui ne contient que les valeurs vérifiant la contrainte
					vector<int> nveauDomaine;
					for (int valTestee : nveauxDomaines[var]) // Test de chaque valeur possible dans le domaine de var
					{
						vector<vector<int>> domainesTest = nveauxDomaines;
						domainesTest[var] = { valTestee };
						if ((*c).verifieDomainesMultiples(domainesTest))
							nveauDomaine.push_back(valTestee);
						else
						{
							cout << "X" << var << "=" << valTestee << " ne vérifie pas ";
							c->print();
							cout << endl;
						}
					}
					nveauxDomaines[var] = nveauDomaine;
					cout << "	Domaine de " << var << " reduit de " << domaines[var].size() << " a " << nveauDomaine.size() << " :";
					for (int v : nveauDomaine)
					{
						cout << " " << v;
					}
					cout << endl;
					// Si le domaine est vide, réduction des branches, pas besoin de continuer
					if (nveauDomaine.size() == 0)
						return nveauxDomaines;
				}
			}
		}
	}

	return nveauxDomaines;
}

/* Returne false si l'un des domaines est vide. */
bool aucun_domaine_vide(const vector<vector<int>>& domaines)
{
	for (vector<int> domaine : domaines)
	{
		if (domaine.empty())
			return false;
	}
	return true;
}

vector<int> methode_reduction_domaines(const vector<unsigned int>& variablesAssignees, const vector<vector<int>>& domaines, const unsigned int nbVariables, const vector<Contrainte*>& contraintes)
{
	cout << variablesAssignees.size() << " variables assignees" << endl;
	if (variablesAssignees.size() == nbVariables) // Si toutes les variables ont été assignées
	{
		// Succès, création d'un tableau des bonnes valeurs
		return domainesToAssignations(domaines);
	}
	else
	{
		// Choix d'une variable x parmi celles non assignées
		unsigned int x;
		for (unsigned int i = 0; i < nbVariables; i++)
		{
			if (find(variablesAssignees.begin(), variablesAssignees.end(), i) == variablesAssignees.end()) // Si i n'est pas dans variablesAssignees
			{
				x = i;
				break;
			}
		}

		// Ajout de la variable x choisie aux variables assignées
		vector<unsigned int> nvellesVariablesAssignees = variablesAssignees;
		nvellesVariablesAssignees.push_back(x);
		// Création de la liste des variables non assignées
		vector<unsigned int> variablesNonAssignees;
		for (unsigned int i = 0; i < nbVariables; i++)
		{
			if (find(nvellesVariablesAssignees.begin(), nvellesVariablesAssignees.end(), i) == nvellesVariablesAssignees.end()) // Si i n'est pas dans nvellesVariablesAssignees
			{
				variablesNonAssignees.push_back(i);
			}
		}

		for (unsigned int i = 0; i < domaines[x].size(); i++)
		{
			int v = domaines[x][i];
			cout << "* Essai de " << x << " = " << v << endl;
			vector<vector<int>> nveauxDomaines = domaines;
			nveauxDomaines[x] = { v }; // Le domaine de x ne contient que v
			nveauxDomaines = reduction_des_domaines(variablesNonAssignees, x, nveauxDomaines, nbVariables, contraintes);
			if (aucun_domaine_vide(nveauxDomaines))
			{
				vector<int> z = methode_reduction_domaines(nvellesVariablesAssignees, nveauxDomaines, nbVariables, contraintes);
				if (z.size() > 0)
					return z;
			}
			cout << "Abandon" << endl;
		}
		return vector<int>();
	}
}
