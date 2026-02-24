// Fonctions pour lire le fichier binaire.
#include "lectureFichierJeux.hpp"
#include <fstream>
#include <cstdint>
#include <memory>
#include "cppitertools/range.hpp"
#include "Jeu.hpp"
using namespace std;

using UInt8  = uint8_t;
using UInt16 = uint16_t;

#pragma region "Fonctions de lecture de base"
//TODO: Remplacer lireUint8 et lireUint16 par une seule fonction générique qui permet les deux, mais permettre uniquement des types qui sont is_trivially_copyable_v (un trait de type).
UInt8 lireUint8(istream& fichier)
{
	UInt8 valeur = 0;
	fichier.read(reinterpret_cast<char*>(&valeur), sizeof(valeur));
	return valeur;
}

UInt16 lireUint16(istream& fichier)
{
	UInt16 valeur = 0;
	fichier.read(reinterpret_cast<char*>(&valeur), sizeof(valeur));
	return valeur;
}


string lireString(istream& fichier)
{
	string texte;
	texte.resize(lireUint16(fichier));
	fichier.read(reinterpret_cast<char*>(&texte[0]), streamsize(sizeof(texte[0])) * texte.length());
	return texte;
}
#pragma endregion

shared_ptr<Concepteur> chercherConcepteur(ListeJeux& listeJeux, const string& nom)
{
	//TODO: Compléter la fonction (équivalent de trouverDesigner du TD2).
	for (unsigned int i = 0; i < listeJeux.size(); i++) {
		auto concepteur = listeJeux[i]->trouverConcepteur(nom);
		if (concepteur != nullptr) {
			return concepteur;
		}
		return nullptr;
	}
	
}

shared_ptr<Concepteur> lireConcepteur(ListeJeux& lj, std::istream& f)
{
	string nom              = lireString(f);
	unsigned anneeNaissance = lireUint16(f);
	string pays             = lireString(f);

	//TODO: Compléter la fonction (équivalent de lireDesigner du TD2).
	shared_ptr<Concepteur> existant = chercherConcepteur(lj, nom);
	if (existant != nullptr) {
		return existant; 
	}
	cout << "C: " << nom << endl;  //TODO: Enlever cet affichage temporaire servant à voir que le code fourni lit bien les jeux.
	return make_shared<Concepteur>(nom, anneeNaissance, pays);
}

shared_ptr<Jeu> lireJeu(istream& f, ListeJeux& lj)
{
	string titre          = lireString(f);
	unsigned anneeSortie  = lireUint16(f);
	string developpeur    = lireString(f);
	unsigned nConcepteurs = lireUint8(f);
	//TODO: Compléter la fonction (équivalent de lireJeu du TD2).
	auto jeu = make_shared<Jeu>(titre, anneeSortie, developpeur);
	for (unsigned int i = 0; i < nConcepteurs; i++) {
	        auto concepteur = lireConcepteur(lj, f);
			jeu->getConcepteurs().ajouter(concepteur);
	}
	lj.ajouter(jeu);
	cout << "J: " << titre << endl;  //TODO: Enlever cet affichage temporaire servant à voir que le code fourni lit bien les jeux.
	return jeu;
}

ListeJeux creerListeJeux(const string& nomFichier)
{
	ifstream f(nomFichier, ios::binary);
	f.exceptions(ios::failbit);
	int nElements = lireUint16(f);
	//TODO: Compléter la fonction.
	ListeJeux listeJeux;
	for ([[maybe_unused]] int i : iter::range(nElements))
		lireJeu(f, listeJeux);

	return {};
}
