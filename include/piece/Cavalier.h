#ifndef CAVALIER_H
#define CAVALIER_H

#include "piece/Piece.h"


/// Cette classes représente la pièce du **Cavalier**. \n
/// Elle met en place son constructeur et une fonction 
/// qui permet de verifier si une pièce de type "Cavalier"
/// à un mouvement conforme aux régles du jeu.
class Cavalier : public Piece 
{
  public:
	
	/**
	 * \fn Constructeur de classe
	 * Seule la couleur et le nom sont demandés. Le reste est initialisé directement par des valeurs par défauts.
	 * \param[in] couleur de la pièce à poser.
	 * \param[in] nom de la pièce à poser.
	 **/
	Cavalier(Couleur couleur, string nom);

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