#pragma once
#include <memory>

//TODO: Rentdre la liste générique.
template <typename T>


class Liste
{
public:
	//TODO: Constructeurs et surcharges d'opérateurs
	Liste(unsigned capacite = 0)
		: nElements_(0),
		capacite_(capacite),
		elements_(std::make_unique<std::shared_ptr<T>[]>(capacite))
	{
	}
	std::shared_ptr<T>& operator[](unsigned index) {
		return elements_[index];
	}
	const std::shared_ptr<T>& operator[](unsigned index) {
		return elements_[index];
	}

	//TODO: Méthode pour ajouter un élément à la liste
	void ajouterListe(const std::shared_ptr<T>& jeu) {
		if (nElements_ >= capacite_) {
			return;
		}
		else {
			elements_[nElements_] = jeu;
			nElements_++;
		}
	}

	// Pour size, on utilise le même nom que les accesseurs de la bibliothèque standard, qui permet d'utiliser certaines fonctions de la bibliotheque sur cette classe.
	unsigned size() const { return nElements_; }
	unsigned getCapacite() const { return capacite_; }

	//TODO: Méthode pour changer la capacité de la liste
	void changerCapacite(unsigned nouvelleCapacite) {
		auto nouveauTableau = std::make_unique<std::shared_ptr<T>[]>(nouvelleCapacite); //creer un nouveau tableau avec une nouvelle capacite 

		unsigned elementsCopier = min(nouvelleCapacite, nElements_)
		for (unsigned i = 0; i < elementsCopier; i++) {
			nouveauTableau[i] = std::move(elements_[i]);
		}

		elements_ = std::move(nouveauTableau);
		capacite_ = nouvelleCapacite;
		nElements_ = elementsCopier; 
	}

	//TODO: Méthode pour trouver un élément selon un critère (lambda).
	template <typename Predicat>
	std::shared_ptr<T> trouver(const Predicat& critere) const {
		for (unsigned i = 0; i < nElements_; i++) {
			if (critere(elements[i]))
				return elements[i];
		}
		return nullptr; 
	}
	

private:
	unsigned nElements_ = 0;
	unsigned capacite_ = 0;
	//TODO: Attribut contenant les éléments de la liste.
	std::unique_ptr<std::shared_ptr<T>[]> elements_;
};
