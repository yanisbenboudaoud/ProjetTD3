#pragma once
#include <memory>
#include <algorithm>

template <typename T>
class Liste
{
public:
	Liste(unsigned capacite = 0)
		: nElements_(0),
		capacite_(capacite),
		elements_(std::make_unique<std::shared_ptr<T>[]>(capacite))
	{
	}

	Liste(const Liste& autre) : nElements_(autre.nElements_), capacite_(autre.nElements_) {
		elements_ = std::make_unique<std::shared_ptr<T>[]>(capacite_);
		for (unsigned i = 0; i < nElements_; ++i) {
			elements_[i] = autre.elements_[i];
		}
	}

	std::shared_ptr<T>& operator[](unsigned index) { return elements_[index]; }
	const std::shared_ptr<T>& operator[](unsigned index) const { return elements_[index]; }

	void ajouter(const std::shared_ptr<T>& element) {
		if (nElements_ >= capacite_) {
			unsigned nouvelleCapacite = (capacite_ == 0) ? 1 : capacite_ * 2;
			changerCapacite(nouvelleCapacite);
		}
		elements_[nElements_++] = element;
	}

	unsigned size() const { return nElements_; }

	void changerCapacite(unsigned nouvelleCapacite) {
		auto nouveauTableau = std::make_unique<std::shared_ptr<T>[]>(nouvelleCapacite);
		unsigned aCopier = std::min(nouvelleCapacite, nElements_);
		for (unsigned i = 0; i < aCopier; i++) {
			nouveauTableau[i] = std::move(elements_[i]);
		}
		elements_ = std::move(nouveauTableau);
		capacite_ = nouvelleCapacite;
		nElements_ = aCopier;
	}

	template <typename Predicat>
	std::shared_ptr<T> trouver(const Predicat& critere) const {
		for (unsigned i = 0; i < nElements_; i++) {
			if (critere(elements_[i]))
				return elements_[i];
		}
		return nullptr;
	}

private:
	unsigned nElements_ = 0;
	unsigned capacite_ = 0;
	std::unique_ptr<std::shared_ptr<T>[]> elements_;
};