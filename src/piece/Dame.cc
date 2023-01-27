#include "piece/Dame.h"
#include <cstdlib>

using namespace std;



Dame::Dame(Couleur couleur, string nom) 
	: Piece(couleur, nom, Square(0,0), 4),Tour(couleur, nom), Fou(couleur, nom) 
{}


/*_______________________________________________________________________________________________*/

bool Dame::mvt_legal(Square const &dest, Echequier *echequier,
					bool target_empty) 
{
	return Fou::mvt_legal(dest, echequier, target_empty) ||
		   Tour::mvt_legal(dest, echequier, target_empty);
}