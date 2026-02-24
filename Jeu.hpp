
#pragma once
#include <string>
#include "Liste.hpp"
#include "Concepteur.hpp"

class Jeu
{
public:
	//TODO: un constructeur par défaut et un constructeur paramétré.
	Jeu() : anneeSortie_(0) {}

	Jeu(const std::string& titre, unsigned anneeSortie, std::string developpeur)
		:titre_(titre),
		anneeSortie_(anneeSortie),
		developpeur_(developpeur)
	{

	}
	const std::string& getTitre() const     { return titre_; }
	void setTitre(std::string titre)        { titre_ = move(titre); }
	unsigned getAnneeSortie() const         { return anneeSortie_; }
	void setAnneeSortie(unsigned annee)     { anneeSortie_ = annee; }
	const std::string& getDeveloppeur() const { return developpeur_; }
	void setDeveloppeur(std::string developpeur) { developpeur_ = move(developpeur); }

	//TODO: Pouvoir accéder à la liste de concepteurs.
	const Liste<Concepteur>& getConcepteurs() const { return concepteur_; }
	Liste<Concepteur>& getConcepteurs() { return concepteur_; }


	//TODO: Votre méthode pour trouver un concepteur selon un critère donné par une lambda, en utilisant la méthode de Liste.
	std::shared_ptr<Concepteur> trouverConcepteur(const std::string& nom) const {
		return concepteur_.trouver([&](const std::shared_ptr<Concepteur>& c) {
        return c->getNom() == nom; 
    });
	}

private:
	std::string titre_;
	unsigned anneeSortie_;
	std::string developpeur_;
	//TODO: Attribut de la liste des concepteurs du jeu
	Liste<Concepteur> concepteur_;
};

using ListeJeux = Liste<Jeu>;  //TODO: Remplacer cette définition (qui est ici juste pour que le code fourni compile) pour que ListeJeux soit une Liste<Jeu> .