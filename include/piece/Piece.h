#ifndef PIECE_H
#define PIECE_H

#include "Square.h"
#include <iostream>


/** \enum COUELUR */
enum Couleur { BLANC = 1, NOIR = -1 };


using namespace std;

class Echequier;

/// Cette classe représente la notion abstraite de Piece.
/// Elle definit les fonction necessaires à leurs manipulation
/// dont les sous-classes vont hériter.
class Piece 
{
  public:
	
	/// Constructeur.
	/// Parametres differents de sous-class car certains ceux
	/// propres à une piece seront initialisés.
	Piece(Couleur couleur, string nom, Square , int type_de_piece);
	

	/**
	* \return la couleur de la piece.
	**/
	Couleur get_couleur() const;

	/**
	* \return l'entier qui décrit le type de piece. Utile pour **Promotion**.
	**/
	int get_type() const;
	
	/**
	 * \return le nom de la pièce.
	 **/
	string get_nom() const;

	/**
	 * \return la posiion (**Square**) de la piéce sur l'échiquier.
	 **/
	Square get_position();

	/**
	 * \brief Permet de placer un pièce à une à une position dans l'échequier.
	 **/
	virtual void set_position(Square const &position);

	/**
	 * \return un booléen qui indique si cette pièce à déjà bougé.
	 **/
	bool first_mvt();

	/**
	 * \fn Change la valeur de la variable private action pour indiquer que 
	 * la pièce à déjà bougé. Virtual car modifié dans Pion.
	 * \param[in] echequier represente le plateau de jeu.
	 * \param[in] last_pos la dernier position de la piece.
	 * \param[in] prise qui indique s'il y a une prise lors de mouvement.
	 **/
	virtual void mvt(Echequier &echequier, Square last_pos, bool prise);



	/**
	 * \brief fonction virtuel car codée dans les sous-classes.
	 * Elle permet de vérifier si un mouvement respecte les régles du jeu 
	 *
	 * \param[in] cible position où l'on souhaite mettre la piece
	 * \param[in] echequier qui est un pointeur vers la grille du jeu
	 * \param[in] cible_vide booléen qui indique si la case atteindre est vide
	 * \return true si le mouvement respecte les régles du jeu
	 **/
	virtual bool mvt_legal(Square const &cible, Echequier *echequier,
							   bool cible_vide) = 0;

	/// destructeur
	virtual ~Piece();

  private:
	Couleur couleur;
	string nom;
	Square position;
	int type_de_piece;
	bool action;
};

#include "Echequier.h"

#endif