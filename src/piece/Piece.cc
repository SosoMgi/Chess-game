#include "piece/Piece.h"



Piece::Piece(Couleur couleur, string nom, Square position, int type_de_piece)
	: couleur(couleur), nom(nom), position(position),type_de_piece(type_de_piece), action(false) 
{}


/*_______________________________________________________________________________________________*/



Couleur Piece::get_couleur() const 
{
	return this->couleur;
}



/*_______________________________________________________________________________________________*/



string Piece::get_nom() const
{
	return this->nom;
}


/*_______________________________________________________________________________________________*/



int Piece::get_type() const
{
	return this->type_de_piece;
}



/*_______________________________________________________________________________________________*/



Square Piece::get_position() 
{
	return this->position;
}


/*_______________________________________________________________________________________________*/


void Piece::set_position(Square const &position) 
{
	this->position.set(position);
}



/*_______________________________________________________________________________________________*/


bool Piece::first_mvt() 
{
	return this->action;
}



/*_______________________________________________________________________________________________*/



void Piece::mvt(Echequier &echequier, Square last_pos, bool target_empty) 
{
	this->action = true;
}


/*_______________________________________________________________________________________________*/


Piece::~Piece() 
{}
