#include "Jeu.h"
#include <iostream>
#include <typeinfo>

using namespace std;

Jeu::Jeu() : echequier(), match(true), next_team(BLANC) 
{}

/*_______________________________________________________________________________________________*/


Jeu::~Jeu() 
{
	echequier.dispose();
}

/*_______________________________________________________________________________________________*/


bool Jeu::partie_en_cours() 
{
	return this->match;
}

/*_______________________________________________________________________________________________*/



void Jeu::print() 
{
	this->echequier.affiche();
}




/*_______________________________________________________________________________________________*/


void Jeu::play() 
{
	Square input;

	if (echequier.roi_en_echec(next_team)) 
	{
		if (est_checkmate(next_team)) 
		{
			match = false;
			cout << "Checkmate !" << endl;
			cout << "Winner is " << (next_team == BLANC ? "black " : "white ")
				 << "team." << endl;
			echequier.canonical_position();
			return;
		} 

		else 
		{
			cout << "Check to the "
				 << (next_team == BLANC ? "white " : "black ") << "king ! "
				 << endl;
		}
	} 

	if (!echequier.roi_en_echec(next_team)) 
	{
		if(est_pat(next_team))
		{
			match = false;
			cout << "PAT: match nul" << endl;
			echequier.canonical_position();
			return;
		}
	}

	cout << (next_team == BLANC ? "white" : "black") << " team, your move."
		 << endl;


	Square org(0,0);
	Square dest(0,0);

	bool fin = false;
	while (!fin) 
	{
		if (input.to_alg(&org,&dest)) 
		{
			if (this->traitement_input(input, &org, &dest)) 
			{
				fin = true;
			}
		} else 
		{
			cerr << "Invalid input. Please try again." << endl;
		}
	}

	next_team = next_team == BLANC ? NOIR : BLANC;
}



/*_______________________________________________________________________________________________*/






bool Jeu::traitement_input(Square const &input, Square *org, Square *dest) 
{
	int type;
	

	if (input.str == "/quit") 
	{
		this->echequier.canonical_position();
		this->match = false;
		return true;
	}
	if (input.str.at(0)=='O' || input.str.at(0)=='o')
	{
		if (input.roque == NONE) 
			return false;
		
		return echequier.roque(input.roque , next_team);
	}



	if (this->echequier.get(*org) != nullptr &&
		this->echequier.get(*org)->get_couleur() != next_team) {
		cerr << "select a valid piece" << endl;
		return false;
	}

	Echequier tmp_echequier = Echequier(echequier);
	bool mvt_correct = tmp_echequier.mvt(*org, *dest, false);
	bool ret;

	if (mvt_correct) 
	{
		if (tmp_echequier.roi_en_echec(next_team)) 
		{
			cerr << "king is still checked" << endl;
			return false;
		} 

		else
			ret = this->echequier.mvt(*org, *dest, true);

		type = this->echequier.get(*dest)->get_type();

		if (type == 0)
		{
			if (this->echequier.get(*dest)->get_couleur() == BLANC)
			{
				if ((*dest).get_y() == 7)
				{
					cout << "Change your pawn in one of those class:\n"
						 << "Queen, Knight, Bishop, Rook"
						 << endl;
					this->echequier.promotion(*dest, BLANC);
				}
			}

			if (this->echequier.get(*dest)->get_couleur() == NOIR)
			{
				if ((*dest).get_y() == 0)
				{
					cout << "Change your pawn in one of those class:\n"
						 << "Queen, Knight, Bishop, Rook"
						 << endl;
					this->echequier.promotion(*dest, NOIR);
				}
			}
		}
		return ret;
	} 
	
	else 
	{
		cerr << "illegal move" << endl;
		return false;
	}
}




/*_______________________________________________________________________________________________*/






bool Jeu::est_checkmate(Couleur couleur) 
{
	vector<Piece *> pieces = echequier.get_pieces(couleur);

	if (!echequier.roi_en_echec(couleur))
		return false;

	Echequier tmp_echequier;
	for (auto &piece : pieces) 
	{
		for (size_t i = 0; i < 8; i++) 
		{
			for (size_t j = 0; j < 8; j++) 
			{
				tmp_echequier = Echequier(echequier);		
				tmp_echequier.update_position();	

				Square target_pos = Square(i, j);

				if (target_pos == piece->get_position())	
					continue;

				if (piece->mvt_legal(target_pos, &tmp_echequier,tmp_echequier.get(target_pos) == nullptr)) 	
				{
					if (tmp_echequier.mvt(piece->get_position(), target_pos,false)) 
					{
						if (!tmp_echequier.roi_en_echec(couleur))		
						{
							return false;
						}
					}
				}
			}
		}
	}

	return true;
}



/*_______________________________________________________________________________________________*/



bool Jeu::est_pat(Couleur couleur) 
{
	vector<Piece *> pieces = echequier.get_pieces(couleur);

	if (echequier.roi_en_echec(couleur))
		return false;

	Echequier tmp_echequier;
	for (auto &piece : pieces) 
	{
		for (size_t i = 0; i < 8; i++) 
		{
			for (size_t j = 0; j < 8; j++) 
			{
				tmp_echequier = Echequier(echequier);		
				tmp_echequier.update_position();	

				Square target_pos = Square(i, j);

				if (target_pos == piece->get_position())
					continue;

				if (piece->mvt_legal(target_pos, &tmp_echequier,tmp_echequier.get(target_pos) == nullptr)) 	
				{
					if (tmp_echequier.mvt(piece->get_position(), target_pos,false)) 
					{
						if (!tmp_echequier.roi_en_echec(couleur))		
						{
							return false;
						}
					}
				}
			}
		}
	}

	return true;
}

