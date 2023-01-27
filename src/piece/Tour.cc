#include "piece/Tour.h"
#include <cstdlib>

using namespace std;



Tour::Tour(Couleur couleur, string nom) 
	: Piece(couleur, nom, Square(0,0), 3) 
{}


/*_______________________________________________________________________________________________*/



bool Tour::mvt_legal(Square const &dest, Echequier *echequier,
					bool target_empty) 
{

	if (get_position().get_x() == dest.get_x() ||
		get_position().get_y() == dest.get_y()) 
	{
		if (echequier->ligne_vide(get_position(), dest)) 
		{
			return true;
		}
	}
	return false;
}