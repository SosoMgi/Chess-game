#include "piece/Cavalier.h"
#include <cstdlib>



using namespace std;




Cavalier::Cavalier(Couleur couleur, string nom)  
		: Piece(couleur, nom, Square(0,0), 1) 
{}


/*_______________________________________________________________________________________________*/


bool Cavalier::mvt_legal(Square const &dest, Echequier *echequier,
						bool cible_vide) 
{
	if (abs(dest.get_x() - get_position().get_x()) == 1 &&
		abs(dest.get_y() - get_position().get_y()) == 2) 
	{
		return true;
	}
	
	if (abs(dest.get_x() - get_position().get_x()) == 2 &&
		abs(dest.get_y() - get_position().get_y()) == 1) 
	{
		return true;
	}
	return false;
}