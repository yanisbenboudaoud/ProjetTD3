#include <fstream>
#include <type_traits>
#include "lectureFichierJeux.hpp"
#include "cppitertools/range.hpp"

using namespace std;

template <typename T>
T lire(istream& fichier) {
	static_assert(is_trivially_copyable_v<T>, "Le type doit etre trivialement copiable.");
	T valeur;
	fichier.read(reinterpret_cast<char*>(&valeur), sizeof(T));
	return valeur;
}

string lireString(istream& fichier) {
	string texte;
	texte.resize(lire<uint16_t>(fichier)); // Utilise la fonction générique
	fichier.read(reinterpret_cast<char*>(&texte[0]), streamsize(sizeof(texte[0])) * texte.length());
	return texte;
}

shared_ptr<Concepteur> chercherConcepteur(ListeJeux& listeJeux, const string& nom) {
	for (unsigned int i = 0; i < listeJeux.size(); i++) {
		auto concepteur = listeJeux[i]->trouverConcepteur(nom);
		if (concepteur != nullptr) {
			return concepteur;
		}
	}
	return nullptr; // Correction de la logique : on ne retourne nullptr qu'à la fin
}

shared_ptr<Concepteur> lireConcepteur(ListeJeux& lj, istream& f) {
	string nom = lireString(f);
	unsigned anneeNaissance = lire<uint16_t>(f);
	string pays = lireString(f);

	shared_ptr<Concepteur> existant = chercherConcepteur(lj, nom);
	if (existant != nullptr) {
		return existant;
	}
	return make_shared<Concepteur>(nom, anneeNaissance, pays);
}

shared_ptr<Jeu> lireJeu(istream& f, ListeJeux& lj) {
	string titre = lireString(f);
	unsigned anneeSortie = lire<uint16_t>(f);
	string developpeur = lireString(f);
	unsigned nConcepteurs = lire<uint8_t>(f);

	auto jeu = make_shared<Jeu>(titre, anneeSortie, developpeur);
	for ([[maybe_unused]] unsigned int i : iter::range(nConcepteurs)) {
		jeu->getConcepteurs().ajouter(lireConcepteur(lj, f));
	}
	return jeu;
}

unique_ptr<ListeJeux> creerListeJeux(const string& nomFichier) {
	ifstream fichier(nomFichier, ios::binary);
	fichier.exceptions(ios::failbit);
	int nElements = lire<uint16_t>(fichier);
	auto listeJeux = make_unique<ListeJeux>();
	for ([[maybe_unused]] int n : iter::range(nElements)) {
		listeJeux->ajouter(lireJeu(fichier, *listeJeux));
	}
	return listeJeux;
}