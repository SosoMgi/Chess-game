#ifndef JEU_H
#define JEU_H

#include "Echequier.h"


class Jeu {
  public:

	/// Constructeur.
	Jeu();

	///Destructeur.
	~Jeu();


	/// Affiche l'état du jeu.
	void print();

	/// Lance le jeu.
	void play();

	/**
	 * \fn Traitement de la châine de caractére et analyse de la
	 * conséquence de cette commande.
	 * \param[in] commande d'entrée.
	 * \param[in] org qui va contenir la position initiale.
	 * \param[in] dest position cible.
	 * \return true si reussite.
	 */
	bool traitement_input(Square const &commande, Square *org, Square *dest);


	/**
	 * \brief verifie si la partie à prit fin.
	 *
	 * \return true si partie en cours.
	 **/
	bool partie_en_cours();

	


	/**
	 * \param[in] couleur de l'équipe si elle est en **echec et mat** .
	 * \return true si echec et mat.
	 */
	bool est_checkmate(Couleur couleur);

	/**
	 * \param[in] couleur de l'équipe à vérifier si **PAT** .
	 * \return true si echec et mat.
	 */
	bool est_pat(Couleur couleur);

  private:
	Echequier echequier;
	bool match;
	Couleur next_team;

};

#endif