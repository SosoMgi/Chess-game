#ifndef ECHEQUIER_H
#define ECHEQUIER_H

#include "piece/Piece.h"
#include "Square.h"
#include <vector>

using namespace std;

class Echequier {
  public:
	Echequier();

	/// Affcihe l'échequier.
	void affiche();
	
	/**
	 * \fn Pose une piece dans une case precise.
	 *
	 * \param[in] position est la case cible.
	 * \param[in] piece est un pointeur vers la pièce à deplacer.
	 **/
	void poser(Square const &position, Piece *piece);

	/**
	 * \fn récupére un pointeur vers la position de la piece en entrée.
	 *
	 * \param[in] position position de la piéce à récupérer.
	 * \return un pointeur vers la piece récupérer.
	 **/
	Piece *get(Square const &position) const;

	/**
	 * \fn bouge une piece d'une position à une autre.
	 * S'il y a une piéce ennemie, celle-ci est detruite.
	 * \param[in] org position de depart.
	 * \param[in] dest position cible.
	 * \return true si reussite.
	 */
	bool mvt(Square const &org, Square const &dest, bool move_effective);

	/**
	 * \fn détruit la piece qui se trouve à la position en entrée.
	 * \param[in] position de la piece à detruire.
	 * \param[in] free la memoire si true.
	 */
	void destruction_piece(Square const &position, bool free);

	/**
	 * \fn verifie si une ligne non diagonale entre deux positions est vide.
	 * \param[in] org position de depart.
	 * \param[in] dest position d'arrivée.
	 * \return true si vide.
	 */
	bool ligne_vide(Square const &org, Square const &dest) const;

	/**
	 * \fn verifie si une diagonale entre deux positions est vide.
	 * \param[in] org position de depart.
	 * \param[in] dest position d'arrivée.
	 * \return true si vide.
	 */
	bool diag_vide(Square const &org, Square const &dest) const;

	/**
	 * \fn recupere le roi d'une couleur voulu.
	 * \param[in] couleur du roi voulu.
	 * \return la piece roi en question.
	 */
	Piece *get_roi(Couleur couleur);

	/**
	 * \fn récupére l'ensemble des pièces d'une couleur encore sur le jeu.
	 * \param[in] couleur des pieces à recuperer.
	 * \return liste des pieces encore présente sur l'echequier de la couleur en entrée.
	 */
	vector<Piece *> get_pieces(Couleur couleur);

	/**
	 * \fn verifie si un roi est en echec.
	 * \param[in] couleur du roi dont il faut verifier l'échec.
	 * \return true si echec.
	 */
	bool roi_en_echec(Couleur couleur);



	/**
	 * \brief utile pour canonicaal_position
	 */
	string pgn_piece_name(string const name, bool view_Pion, bool view_color) const;


	/**
	 * \return les pieces encore sur la grille.
	 **/
	string canonical_position() const ;


	/**
	 * \brief transforme un pion ayant atteint la 1ere ligne adverse.
	 *
	 * \param[in] position ou mettre la nouvelle piece.
	 * \param[in] joueur represente la coulour de la piece à promouvoire.
	 **/
	bool promotion(Square position, Couleur joueur);


	/**
	 * \fn effectue le roque.
	 * \param[in] roque est un entier qui represente le type de roque à faire.
	 * \param[in] couleur du camps ou le roque doit être fait.
	 * \return true si reussite.
	 */
	bool roque(int roque, Couleur couleur);

	
	/**
	 * \brief udapte les position sur l'échequier.
	 */
	void update_position();

	/**
	 * \brief free la mémoire de toutes les pièces créée.
	 */
	void dispose();

  private:
	Piece *grille[8][8];
	vector<Piece *> pieces_noires;
	vector<Piece *> pieces_blanches;
	Piece *roi_noir;
	Piece *roi_blanc;
};

#endif