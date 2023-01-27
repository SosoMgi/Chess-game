#ifndef PION_H
#define PION_H

#include "piece/Piece.h"



/// Cette classe représente la pièce du **Pion**.
/// Elle met en place son constructeur et une fonction 
/// qui permet de verifier si une piece de type "Pion"
/// à un mouvement conforme aux régles du jeu.
class Pion : public Piece 
{
  public:

	/**
	 * \fn Constructeur de classe
	 * Seule la couleur et le nom sont demandés. Le reste est initialisé directement par des valeurs par défauts.
	 * \param[in] couleur de la pièce à poser.
	 * \param[in] nom de la pièce à poser.
	 **/
	Pion(Couleur couleur, string nom);


	/**
	 * \fn Vérifie si un mouvement est conforme aux régles du jeu.
	 * \param[in] position où l'on souhaite poser la pièce.
	 * \param[in] echequier est un pointeur vers la grille de jeu.
	 * \param[in] cible_vide indique si la position cible est vide.
	 **/
	virtual bool mvt_legal(Square const &position, Echequier *echequier,
							bool cible_vide);

	/**
	 * \fn place le pion à une position. Virtual pour prendre en compte le double pas
	 * \param[in] echequier represente le plateau de jeu.
	 * \param[in] last_pos la dernier position de la piece.
	 * \param[in] prise qui indique s'il y a une prise lors de mouvement.
	 **/
	virtual void set_position(Square const &position);

	/// Utile pour la prise en passant.
	bool double_pas_fait();

	/**
	 * \fn 
	 * \param[in] echequier represente le plateau de jeu.
	 * \param[in] last_pos la dernier position de la piece.
	 * \param[in] prise qui indique s'il y a une prise lors de mouvement.
	 **/
	virtual void mvt(Echequier &echequier, Square last_pos, bool target_empty);

  private:
	bool double_pas = false;
};

#endif