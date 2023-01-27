#include "piece/Pion.h"



Pion::Pion(Couleur couleur, string nom) 
	: Piece(couleur, nom, Square(0,0), 0) 
{}


/*_______________________________________________________________________________________________*/



bool Pion::mvt_legal(Square const &pos, Echequier *echequier, bool target_empty) 
{
	if (target_empty) 
	{
		if (!this->first_mvt()) 
		{
			if (pos == this->get_position() + Square(0, this->get_couleur() * 2)) 
			{
				return echequier->ligne_vide(get_position(), pos);
			}
		}

		if (pos == this->get_position() + Square(0, this->get_couleur() * 1)) 
		{
			return echequier->ligne_vide(get_position(), pos);
		}

		if ((get_couleur() == BLANC && get_position().get_y() == 3) ||
			(get_couleur() == NOIR && get_position().get_y() == 4)) 
		{

			if (pos == this->get_position() + Square(1, this->get_couleur() * 1) ||
				pos == this->get_position() + Square(-1, this->get_couleur() * 1)) 
			{
				Pion *pion = dynamic_cast<Pion *>(echequier->get(
					Square(pos.get_x(), pos.get_y() - get_couleur())));

				if (pion != nullptr) 
				{
					if (pion->double_pas_fait()) 
					{
						return true;
					}
				}
			}
		}
		return false;
	}

	return pos == this->get_position() + Square(1, this->get_couleur() * 1) ||
		   pos == this->get_position() + Square(-1, this->get_couleur() * 1);
}



/*_______________________________________________________________________________________________*/



void Pion::set_position(Square const &position) 
{
	if (abs(get_position().get_y() - position.get_y()) == 2) 
	{
		double_pas = true;
	}
	Piece::set_position(position);
}



/*_______________________________________________________________________________________________*/



bool Pion::double_pas_fait() 
{
	return double_pas;
}



/*_______________________________________________________________________________________________*/



void Pion::mvt(Echequier &echequier, Square last_pos, bool target_empty) 
{
	// Case of en passant : diag movement but no piece has been taken
	if (last_pos.get_x() != get_position().get_x() && target_empty) 
	{
		// we take the piece below
		echequier.destruction_piece(get_position() + Square(0, -get_couleur()), true);
	}
	Piece::mvt(echequier, last_pos, target_empty);
}