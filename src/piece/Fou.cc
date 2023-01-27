#include "piece/Fou.h"
#include <cstdlib>

using namespace std;



Fou::Fou(Couleur couleur, string nom) 
	: Piece(couleur, nom, Square(0,0), 2) 
{}


/*_______________________________________________________________________________________________*/


bool Fou::mvt_legal(Square const &dest, Echequier *echequier,
					bool target_empty) 
{
	if (abs(dest.get_x() - get_position().get_x()) ==
		abs(dest.get_y() - get_position().get_y())) {
		return echequier->diag_vide(this->get_position(), dest);
	}
	return false;
}