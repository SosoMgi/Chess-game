#ifndef ROI_H
#define ROI_H

#include "piece/Piece.h"


/// Cette classe représente la pièce du **Roi**.
/// Elle met en place son constructeur et une fonction 
/// qui permet de verifier si une piece de type "Roi"
/// à un mouvement conforme aux régles du jeu.
class Roi : public Piece 
{
  public:

	/**
	 * \fn Constructeur de classe
	 * Seule la couleur et le nom sont demandés. Le reste est initialisé directement par des valeurs par défauts.
	 * \param[in] couleur de la pièce à poser.
	 * \param[in] nom de la pièce à poser.
	 **/
	Roi(Couleur couleur, string nom);
	

	/**
	 * \fn Vérifie si un mouvement est conforme aux régles du jeu.
	 * \param[in] position où l'on souhaite poser la pièce.
	 * \param[in] echequier est un pointeur vers la grille de jeu.
	 * \param[in] cible_vide indique si la position cible est vide.
	 **/
	virtual bool mvt_legal(Square const &position, Echequier *echequier,
							   bool cible_vide);
};

#endif