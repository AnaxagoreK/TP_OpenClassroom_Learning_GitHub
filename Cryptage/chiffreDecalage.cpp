#include <iostream>
#include <string>
#include <vector>
#include <cctype> //std::isupper
#include <algorithm> //std::copy; std::find; std::for_each
#include <iterator> //std::ostream_iterator
using namespace std;

// Foncteur qui effectue un chiffrement par decalage
class ChiffrementDecal {
public:

	// Constructeur prenant le decalage voulu en argument
	ChiffrementDecal(int decalage)
	{
		//Recuperation de la valeur du decalage (prise en compte du cas ou la valeur entree par lutilisateur excede 26)
		m_decalage = decalage % 26;
	}

	/*
	Le foncteur suivant est utilise pour generer la chaine de caractere decryptee.
	En effet ce foncteur sapplique a chaque caractere de la chaine a decrypter. Il
	recupere le caractere associe a literateur courant, et si ce dernier verifie les
	conditions de cryptage, il le modifie (en un caractere crypte).
	*/
	void operator ()(char &caractere) const
	{
		//On verifie si le caractere est une majuscule
		if (isupper(caractere))
		{
			//On incremente literateur jusquau caractere crypte
			int positionCryptee = m_decalage;
			int debut = 'A'; int fin = 'Z'; int it = caractere;

			while (positionCryptee > 0)
			{
				//On gere le cas ou on arrive au dernier caractere de lalphabet 
				if (it != fin)
					++it;
				else
					it = debut;

				--positionCryptee;
			}

			//On recupere le caractere crypte correspondant
			caractere = it;
		}
	}

private:

	int m_decalage; // Le decalage a appliquer au texte
};


int main()
{

	// Le message a crypter
	string texte("BIENVENUE SUR LE MOOC C++ D'OCR !!");

	cout << "Chaine a crypter :" << endl << texte << endl << endl;

	// Demande du decalage a lutilisateur
	cout << "Quel decalage voulez-vous utiliser ? ";
	int decalage;
	cin >> decalage;

	// Creation du foncteur
	ChiffrementDecal foncteur(decalage);

	// Chaine de caracteres pour le message crypter
	string texte_crypte = texte; //Initialisation

	//Cryptage de la chaine
	for_each(texte_crypte.begin(), texte_crypte.end(), foncteur);

	//Affichage des lettres separees par des virgules
	ostream_iterator<char> ic(cout, ",");
	copy(texte_crypte.begin(), texte_crypte.end(), ic);

	cout << endl << endl;
	system("PAUSE");
	return 0;
}

