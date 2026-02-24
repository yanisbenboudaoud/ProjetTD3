#include <iostream>
#include <fstream>
#include "Liste.hpp"
#include "Concepteur.hpp"
#include "Jeu.hpp"
#include "lectureFichierJeux.hpp"
#include "bibliotheque_cours.hpp"

using namespace std;

// Point 6: Surcharges d'opérateurs <<
ostream& operator<<(ostream& os, const Concepteur& c) {
	return os << c.getNom() << ", " << c.getAnneeNaissance() << ", " << c.getPays();
}

ostream& operator<<(ostream& os, const Jeu& j) {
	os << "Titre: " << j.getTitre() << " (" << j.getAnneeSortie() << ")" << endl;
	os << "  Developpeur: " << j.getDeveloppeur() << endl;
	os << "  Concepteurs: ";
	for (unsigned int i = 0; i < j.getConcepteurs().size(); i++) {
		os << (i == 0 ? "" : ", ") << *j.getConcepteurs()[i];
	}
	return os;
}

template <typename T>
ostream& operator<<(ostream& os, const Liste<T>& liste) {
	for (unsigned int i = 0; i < liste.size(); i++) {
		os << *liste[i] << endl;
	}
	return os;
}

int main() {
	bibliotheque_cours::activerCouleursAnsi();

	ListeJeux lj = creerListeJeux("jeux.bin");

	static const string ligneSeparation = "\n\033[92m══════════════════════════════════════════════\033[0m\n";

	// Point 6: Affichage console et fichier
	cout << "CONTENU DE LA LISTE DE JEUX :" << endl;
	cout << lj << ligneSeparation << endl;

	ofstream fichierSortie("sortie.txt");
	if (fichierSortie) {
		fichierSortie << lj;
	}

	cout << "TEST DE LA COPIE (Point 7) :" << endl;
	if (lj.size() >= 3) {
		Jeu copieJeu = *lj[2]; 

		
		if (copieJeu.getConcepteurs().size() >= 2 && (lj)[0]->getConcepteurs().size() >= 1) {
			copieJeu.getConcepteurs()[1] = (lj)[0]->getConcepteurs()[0];
		}

		cout << "Jeu original à l'indice 2 :" << endl << *lj[2] << endl;
		cout << "Copie modifiée :" << endl << copieJeu << endl;

		cout << "Verification des adresses du premier concepteur :" << endl;
		cout << "Original: " << lj[2]->getConcepteurs()[0].get() << endl;
		cout << "Copie   : " << copieJeu.getConcepteurs()[0].get() << endl;
		cout << "Ce sont les memes adresses (partage de shared_ptr)." << endl;
	}

	return 0;
//TODO: Compléter le main avec les tests demandés.
//TODO: S'assurer qu'aucune ligne de code est non couverte.
//NOTE: Il n'est pas nécessaire de couvrir les getters/setters simples fournis; il faut tester si vous en ajoutez ou les modifiez.
//NOTE: Pour Liste, qui est générique, on demande de couvrir uniquement pour Liste<Jeu>, pas pour tous les types.
}