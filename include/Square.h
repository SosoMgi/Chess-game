#ifndef POSITION_H
#define POSITION_H

#include <iostream>
#include <regex>

using namespace std;

#define NONE 0
#define GRAND_ROQUE 1
#define PETIT_ROQUE 2

using namespace std;


/// Classe qui représente une case sur la grille.
class Square 
{
  public:

	/// Constructeur par défaut.
	Square();

	/// Constructeur.
	Square(int x, int y);

	/// \return la valeur de la lettre.
	int get_x() const;

	/// \return la valeur de la ligne.
	int get_y() const;


	/**
	 * \brief convertie la chaîne de caractére en entrée en notation algébrique : **parsage** .
	 * \param[in] org est un pointeur vers les coordonnées de départ (eg:**a2**a4).
	 * \param[in] dest est un pointeur vers les coordonnées de départ (eg:a2**a4**).
	 * \return booléen.
	 */
	bool to_alg(Square *org, Square *dest);


	/**
	 * \brief notation algébrique --> chaîne de caractére.
	 * \return booléen.
	 */
	void to_string();

	/**
	 * \brief pose ces coordonnées à cette position.
	 * \param[in] x colonne (lettre a,b...h).
	 * \param[in] y ligne (valeur numérique).
	 */
	void set(int x, int y);

	/// \brief Pose ces coordonnées depuis une autre position.
	void set(Square const &position);


	/// chaîne qui va contenir l'entrée du terminal.
	string str;

	/// Valeur qui indique si str est un roque et si oui lequel.
	int roque;

  private:
	int x, y;
};


/// Surcharge +.
const Square operator+(Square const &pos1, Square const &pos2);
/// Surcharge ==.
const bool operator==(Square const &pos1, Square const &pos2);
/// Surcharge !=.
const bool operator!=(Square const &pos1, Square const &pos2);
ostream &operator<<(ostream &out, Square const &pos);

#endif