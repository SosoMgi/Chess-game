#include "piece/Roi.h"
#include <cstdlib>

using namespace std;



Roi::Roi(Couleur couleur, string nom) 
	: Piece(couleur, nom, Square(0,0), 5) 
{}


/*_______________________________________________________________________________________________*/



bool Roi::mvt_legal(Square const &dest, Echequier *echequier,
					bool cible_vide) 
{
	if (abs(dest.get_x() - get_position().get_x()) <= 1 &&
		abs(dest.get_y() - get_position().get_y()) <= 1) 
	{
		return true;
	}
	return false;
}