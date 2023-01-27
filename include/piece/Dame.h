#ifndef DAME_HPP
#define DAME_HPP

#include "piece/Fou.h"
#include "piece/Piece.h"
#include "piece/Tour.h"

/// Cette classe représente la pièce **Dame**.\n
/// Elle met en place son constructeur et une fonction 
/// qui permet de verifier si une piece de type "Dame"
/// à un mouvement conforme aux régles du jeu. \n
/// Ses mouvement sont un mixte du fou et de la tour.
/// Donc, elle herite de ces classes pour allger mvt_legal()
class Dame : public Tour, public Fou 
{
  public:

	/**
	 * \fn Constructeur de classe
	 * Seule la couleur et le nom sont demandés. Le reste est initialisé directement par des valeurs par défauts.
	 * \param[in] couleur de la pièce à poser.
	 * \param[in] nom de la pièce à poser.
	 **/
	Dame(Couleur couleur, string nom);


	/**
	 * \fn Vérifie si un mouvement est conforme aux régles du jeu.
	 * \param[in] position où l'on souhaite poser la pièce.
	 * \param[in] echequier est un pointeur vers la grille de jeu.
	 * \param[in] cible_vide indique si la position cible est vide
	 **/
	virtual bool mvt_legal(Square const &position, Echequier *echequier,
							bool cible_vide);
};

#endif